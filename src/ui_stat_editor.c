#include "global.h"
#include "ui_stat_editor.h"
#include "strings.h"
#include "bg.h"
#include "data.h"
#include "decompress.h"
#include "event_data.h"
#include "field_weather.h"
#include "gpu_regs.h"
#include "graphics.h"
#include "item.h"
#include "item_menu.h"
#include "item_menu_icons.h"
#include "list_menu.h"
#include "item_icon.h"
#include "item_use.h"
#include "international_string_util.h"
#include "main.h"
#include "malloc.h"
#include "menu.h"
#include "menu_helpers.h"
#include "palette.h"
#include "party_menu.h"
#include "scanline_effect.h"
#include "script.h"
#include "sound.h"
#include "string_util.h"
#include "strings.h"
#include "task.h"
#include "text_window.h"
#include "overworld.h"
#include "event_data.h"
#include "constants/items.h"
#include "constants/field_weather.h"
#include "constants/songs.h"
#include "constants/rgb.h"
#include "pokemon_icon.h"
#include "pokedex.h"
#include "trainer_pokemon_sprites.h"
#include "field_effect.h"
#include "field_screen_effect.h"

 
//==========DEFINES==========//
struct StatEditorResources
{
    MainCallback savedCallback;     // determines callback to run when we exit. e.g. where do we want to go after closing the menu
    u8 gfxLoadState;
    u8 mode;
    u8 monIconSpriteId;
    u16 speciesID;
    u16 selectedStat;
    u16 selectorSpriteId;
    u16 selector_y;
    u32 editingStat;
    u16 normalTotal;
    u16 evTotal;
    u16 initialEvStats[6];
    u16 initialEvTotal;
    u16 partyid;
    u16 inputMode;
};

#define INPUT_SELECT_STAT 0
#define INPUT_EDIT_STAT   1

enum WindowIds
{
    WINDOW_1,
    WINDOW_2,
    WINDOW_3,
    WINDOW_4,
};

//==========EWRAM==========//
static EWRAM_DATA struct StatEditorResources *sStatEditorDataPtr = NULL;
static EWRAM_DATA u8 *sBg1TilemapBuffer = NULL;

//==========STATIC=DEFINES==========//
static void StatEditor_RunSetup(void);
static bool8 StatEditor_DoGfxSetup(void);
static bool8 StatEditor_InitBgs(void);
static void StatEditor_FadeAndBail(void);
static bool8 StatEditor_LoadGraphics(void);
static void StatEditor_InitWindows(void);
static void PrintTitleToWindowMainState();
static void Task_StatEditorWaitFadeIn(u8 taskId);
static void Task_StatEditorMain(u8 taskId);
static void Task_MenuEditingStat(u8 taskId);
static void SampleUi_DrawMonIcon(u16 dexNum);
static void PrintMonStats(void);
static void SelectorCallback(struct Sprite *sprite);
static struct Pokemon *GetMon();
static void InitializeMonStats();
static void UndoStatChanges();
static u8 CreateSelector();
static void DestroySelector();
static void UpdateSelectorAnim();

//==========CONST=DATA==========//
static const struct BgTemplate sStatEditorBgTemplates[] =
{
    {
        .bg = 0,    // windows, etc
        .charBaseIndex = 0,
        .mapBaseIndex = 30,
        .priority = 1
    }, 
    {
        .bg = 1,    // this bg loads the UI tilemap
        .charBaseIndex = 3,
        .mapBaseIndex = 28,
        .priority = 2
    },
    {
        .bg = 2,    // this bg loads the UI tilemap
        .charBaseIndex = 0,
        .mapBaseIndex = 26,
        .priority = 0
    }
};

static const struct WindowTemplate sMenuWindowTemplates[] = 
{
    [WINDOW_1] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 1,   // position from left (per 8 pixels)
        .tilemapTop = 0,    // position from top (per 8 pixels)
        .width = 30,        // width (per 8 pixels)
        .height = 2,        // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1,     // tile start in VRAM
    },
    [WINDOW_2] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 11,   // position from left (per 8 pixels)
        .tilemapTop = 2,    // position from top (per 8 pixels)
        .width = 22,        // width (per 8 pixels)
        .height = 17,        // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1 + 60,     // tile start in VRAM
    },
    [WINDOW_3] = 
    {
        .bg = 0,            // which bg to print text on
        .tilemapLeft = 1,   // position from left (per 8 pixels)
        .tilemapTop = 11,    // position from top (per 8 pixels)
        .width = 8,        // width (per 8 pixels)
        .height = 9,        // height (per 8 pixels)
        .paletteNum = 15,   // palette index to use for text
        .baseBlock = 1 + 60 + 374,     // tile start in VRAM
    },
    DUMMY_WIN_TEMPLATE
};

static const u32 sStatEditorBgTiles[] = INCBIN_U32("graphics/ui_menu/background_tileset.4bpp.lz");
static const u32 sStatEditorBgTilemap[] = INCBIN_U32("graphics/ui_menu/background_tileset.bin.lz");
static const u16 sStatEditorBgPalette[] = INCBIN_U16("graphics/ui_menu/background_pal.gbapal");

enum Colors
{
    FONT_BLACK,
    FONT_WHITE,
    FONT_RED,
    FONT_BLUE,
};

static const u8 sMenuWindowFontColors[][3] = 
{
    [FONT_BLACK] = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_DARK_GRAY,  TEXT_COLOR_LIGHT_GRAY},
    [FONT_WHITE] = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_WHITE,      TEXT_COLOR_DARK_GRAY},
    [FONT_RED]   = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_RED,        TEXT_COLOR_DARK_GRAY},
    [FONT_BLUE]  = {TEXT_COLOR_TRANSPARENT,  TEXT_COLOR_BLUE,       TEXT_COLOR_LIGHT_GRAY},
};

#define TAG_SELECTOR 30004

static const u16 sSelector_Pal[]  = INCBIN_U16("graphics/ui_menu/selector.gbapal");
static const u32 sSelector_Gfx[]  = INCBIN_U32("graphics/ui_menu/selector.4bpp.lz");
static const u8 sDPad_ButtonGfx[] = INCBIN_U8("graphics/ui_menu/dpad_button.4bpp");

static const struct OamData sOamData_Selector =
{
    .size = SPRITE_SIZE(32x32),
    .shape = SPRITE_SHAPE(32x32),
    .priority = 0,
};

static const struct CompressedSpriteSheet sSpriteSheet_Selector =
{
    .data = sSelector_Gfx,
    .size = 32*32*4/2,
    .tag = TAG_SELECTOR,
};

static const struct SpritePalette sSpritePal_Selector =
{
    .data = sSelector_Pal,
    .tag = TAG_SELECTOR
};

static const union AnimCmd sSpriteAnim_Selector0[] =
{
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_FRAME(0, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSpriteAnim_Selector1[] =
{
    ANIMCMD_FRAME(32, 32),
    ANIMCMD_FRAME(32, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSpriteAnim_Selector2[] =
{
    ANIMCMD_FRAME(16, 32),
    ANIMCMD_FRAME(16, 32),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd sSpriteAnim_Selector3[] =
{
    ANIMCMD_FRAME(48, 10),
    ANIMCMD_FRAME(48, 10),
    ANIMCMD_JUMP(0),
};

static const union AnimCmd *const sSpriteAnimTable_Selector[] =
{
    sSpriteAnim_Selector0,
    sSpriteAnim_Selector1,
    sSpriteAnim_Selector2,
    sSpriteAnim_Selector3,
};

static const struct SpriteTemplate sSpriteTemplate_Selector =
{
    .tileTag = TAG_SELECTOR,
    .paletteTag = TAG_SELECTOR,
    .oam = &sOamData_Selector,
    .anims = sSpriteAnimTable_Selector,
    .images = NULL,
    .affineAnims = gDummySpriteAffineAnimTable,
    .callback = SelectorCallback
};

#define EDIT_INPUT_INCREASE_STATE           0
#define EDIT_INPUT_MAX_INCREASE_STATE       1
#define EDIT_INPUT_DECREASE_STATE           2
#define EDIT_INPUT_MAX_DECREASE_STATE       3

#define EV_STAT_MINIMUM       0
#define EV_MAX_SINGLE_STAT    255
#define EV_MAX_TOTAL          510

// Scripting
static void Task_OpenStatEditorFromScript(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        StatEditor_Init(CB2_ReturnToField);
        gFieldCallback = FieldCB_ContinueScriptHandleMusic;
        DestroyTask(taskId);
    }
}

void OpenEvEditorFromScript(void)
{
    LockPlayerFieldControls();
    CreateTask(Task_OpenStatEditorFromScript, 10);
}

// Begin Generic UI Initialization Code
void Task_OpenStatEditorFromStartMenu(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        CleanupOverworldWindowsAndTilemaps();
        StatEditor_Init(CB2_ReturnToFieldWithOpenMenu);
        DestroyTask(taskId);
    }
}

// This is our main initialization function if you want to call the menu from elsewhere
void StatEditor_Init(MainCallback callback)
{
    if ((sStatEditorDataPtr = AllocZeroed(sizeof(struct StatEditorResources))) == NULL)
    {
        SetMainCallback2(callback);
        return;
    }
    
    // initialize stuff
    sStatEditorDataPtr->gfxLoadState = 0;
    sStatEditorDataPtr->savedCallback = callback;
    sStatEditorDataPtr->selectorSpriteId = 0xFF;
    sStatEditorDataPtr->partyid = gSpecialVar_0x8004;
    
    SetMainCallback2(StatEditor_RunSetup);
}

static void StatEditor_RunSetup(void)
{
    while (1)
    {
        if (StatEditor_DoGfxSetup() == TRUE)
            break;
    }
}

static void StatEditor_MainCB(void)
{
    RunTasks();
    AnimateSprites();
    BuildOamBuffer();
    DoScheduledBgTilemapCopiesToVram();
    UpdatePaletteFade();
}

static void StatEditor_VBlankCB(void)
{
    LoadOam();
    ProcessSpriteCopyRequests();
    TransferPlttBuffer();
}

static bool8 StatEditor_DoGfxSetup(void)
{
    switch (gMain.state)
    {
    case 0:
        DmaClearLarge16(3, (void *)VRAM, VRAM_SIZE, 0x1000)
        SetVBlankHBlankCallbacksToNull();
        ResetVramOamAndBgCntRegs();
        ClearScheduledBgCopiesToVram();
        gMain.state++;
        break;
    case 1:
        ScanlineEffect_Stop();
        FreeAllSpritePalettes();
        ResetPaletteFade();
        ResetSpriteData();
        ResetTasks();
        gMain.state++;
        break;
    case 2:
        if (StatEditor_InitBgs())
        {
            sStatEditorDataPtr->gfxLoadState = 0;
            gMain.state++;
        }
        else
        {
            StatEditor_FadeAndBail();
            return TRUE;
        }
        break;
    case 3:
        if (StatEditor_LoadGraphics() == TRUE)
            gMain.state++;
        break;
    case 4:
        InitializeMonStats();
        FreeMonIconPalettes();
        LoadMonIconPalettes();
        LoadCompressedSpriteSheet(&sSpriteSheet_Selector);
        LoadSpritePalette(&sSpritePal_Selector);
        SampleUi_DrawMonIcon(sStatEditorDataPtr->speciesID);
        gMain.state++;
        break;
    case 5:
        StatEditor_InitWindows();
        PrintTitleToWindowMainState();
        sStatEditorDataPtr->inputMode = INPUT_SELECT_STAT;
        PrintMonStats();
        CreateSelector();
        gMain.state++;
        break;
    case 6:
        CreateTask(Task_StatEditorWaitFadeIn, 0);
        BlendPalettes(0xFFFFFFFF, 16, RGB_BLACK);
        gMain.state++;
        break;
    case 7:
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 16, 0, RGB_BLACK);
        gMain.state++;
        break;
    default:
        SetVBlankCallback(StatEditor_VBlankCB);
        SetMainCallback2(StatEditor_MainCB);
        return TRUE;
    }
    return FALSE;
}

#define try_free(ptr) ({        \
    void ** ptr__ = (void **)&(ptr);   \
    if (*ptr__ != NULL)                \
        Free(*ptr__);                  \
})

static void StatEditor_FreeResources(void)
{
    DestroySelector();
    FreeResourcesAndDestroySprite(&gSprites[sStatEditorDataPtr->monIconSpriteId], sStatEditorDataPtr->monIconSpriteId);
    try_free(sStatEditorDataPtr);
    try_free(sBg1TilemapBuffer);
    FreeAllWindowBuffers();
}


static void Task_StatEditorWaitFadeAndBail(u8 taskId)
{
    if (!gPaletteFade.active)
    {
        SetMainCallback2(sStatEditorDataPtr->savedCallback);
        StatEditor_FreeResources();
        DestroyTask(taskId);
    }
}

static void StatEditor_FadeAndBail(void)
{
    BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
    CreateTask(Task_StatEditorWaitFadeAndBail, 0);
    SetVBlankCallback(StatEditor_VBlankCB);
    SetMainCallback2(StatEditor_MainCB);
}

static bool8 StatEditor_InitBgs(void)
{
    ResetAllBgsCoordinates();
    sBg1TilemapBuffer = Alloc(0x800);
    if (sBg1TilemapBuffer == NULL)
        return FALSE;
    
    memset(sBg1TilemapBuffer, 0, 0x800);
    ResetBgsAndClearDma3BusyFlags(0);
    InitBgsFromTemplates(0, sStatEditorBgTemplates, NELEMS(sStatEditorBgTemplates));
    SetBgTilemapBuffer(1, sBg1TilemapBuffer);
    ScheduleBgCopyTilemapToVram(1);
    SetGpuReg(REG_OFFSET_DISPCNT, DISPCNT_OBJ_ON | DISPCNT_OBJ_1D_MAP);
    ShowBg(0);
    ShowBg(1);
    ShowBg(2);
    return TRUE;
}

static bool8 StatEditor_LoadGraphics(void)
{
    switch (sStatEditorDataPtr->gfxLoadState)
    {
    case 0:
        ResetTempTileDataBuffers();
        DecompressAndCopyTileDataToVram(1, sStatEditorBgTiles, 0, 0, 0);
        sStatEditorDataPtr->gfxLoadState++;
        break;
    case 1:
        if (FreeTempTileDataBuffersIfPossible() != TRUE)
        {
            LZDecompressWram(sStatEditorBgTilemap, sBg1TilemapBuffer);
            sStatEditorDataPtr->gfxLoadState++;
        }
        break;
    case 2:
        LoadPalette(sStatEditorBgPalette, 0, 32);
        sStatEditorDataPtr->gfxLoadState++;
        break;
    default:
        sStatEditorDataPtr->gfxLoadState = 0;
        return TRUE;
    }
    return FALSE;
}

static void StatEditor_InitWindows(void)
{
    InitWindows(sMenuWindowTemplates);
    DeactivateAllTextPrinters();
    ScheduleBgCopyTilemapToVram(0);
    
    FillWindowPixelBuffer(WINDOW_1, 0);
    PutWindowTilemap(WINDOW_1);
    CopyWindowToVram(WINDOW_1, 3);
    
    ScheduleBgCopyTilemapToVram(2);
}

static void Task_StatEditorWaitFadeIn(u8 taskId)
{
    if (!gPaletteFade.active)
        gTasks[taskId].func = Task_StatEditorMain;
}

static void Task_StatEditorTurnOff(u8 taskId)
{
    // s16 *data = gTasks[taskId].data;

    if (!gPaletteFade.active)
    {
        SetMainCallback2(sStatEditorDataPtr->savedCallback);
        StatEditor_FreeResources();
        DestroyTask(taskId);
    }
}

//
//       Stat Editor Code
//  End of UI setup code, beginning of stat editor specific code
//
static struct Pokemon *GetMon()
{
    return &gPlayerParty[sStatEditorDataPtr->partyid];
}

#define MON_ICON_X     32 + 8
#define MON_ICON_Y     32 + 24
static void SampleUi_DrawMonIcon(u16 dexNum)
{
    u16 speciesId = dexNum;
    sStatEditorDataPtr->monIconSpriteId = CreateMonPicSprite_Affine(speciesId, 0, 0x8000, TRUE, MON_ICON_X, MON_ICON_Y, 0, TAG_NONE);

    gSprites[sStatEditorDataPtr->monIconSpriteId].oam.priority = 0;
}

static u8 CreateSelector()
{
    if (sStatEditorDataPtr->selectorSpriteId == 0xFF)
        sStatEditorDataPtr->selectorSpriteId = CreateSprite(&sSpriteTemplate_Selector, 203, 30, 0);

    gSprites[sStatEditorDataPtr->selectorSpriteId].invisible = FALSE;
    StartSpriteAnim(&gSprites[sStatEditorDataPtr->selectorSpriteId], 0);
    return sStatEditorDataPtr->selectorSpriteId;
}

static void DestroySelector()
{
    if (sStatEditorDataPtr->selectorSpriteId != 0xFF)
        DestroySprite(&gSprites[sStatEditorDataPtr->selectorSpriteId]);
    sStatEditorDataPtr->selectorSpriteId = 0xFF;
}

#define DISTANCE_BETWEEN_STATS_Y 16
#define SECOND_COLUMN ((8 * 4))
#define THIRD_COLUMN ((8 * 8))
#define STARTING_X 75
#define STARTING_Y 26

struct MonPrintData {
    u16 x;
    u16 y;
};

static const struct MonPrintData StatPrintData[] =
{
    [MON_DATA_MAX_HP] = {STARTING_X, STARTING_Y},
    [MON_DATA_HP_EV] = {STARTING_X + SECOND_COLUMN, STARTING_Y},

    [MON_DATA_ATK] = {STARTING_X, STARTING_Y + DISTANCE_BETWEEN_STATS_Y},
    [MON_DATA_ATK_EV] = {STARTING_X + SECOND_COLUMN, STARTING_Y + DISTANCE_BETWEEN_STATS_Y},

    [MON_DATA_DEF] = {STARTING_X, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 2)},
    [MON_DATA_DEF_EV] = {STARTING_X + SECOND_COLUMN, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 2)},

    [MON_DATA_SPATK] = {STARTING_X, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 3)},
    [MON_DATA_SPATK_EV] = {STARTING_X + SECOND_COLUMN, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 3)},

    [MON_DATA_SPDEF] = {STARTING_X, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 4)},
    [MON_DATA_SPDEF_EV] = {STARTING_X + SECOND_COLUMN, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 4)},

    [MON_DATA_SPEED] = {STARTING_X, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 5)},
    [MON_DATA_SPEED_EV] = {STARTING_X + SECOND_COLUMN, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 5)},
};

static const u16 statsToPrintActual[] = {
    MON_DATA_MAX_HP, MON_DATA_ATK, MON_DATA_DEF, MON_DATA_SPEED, MON_DATA_SPATK, MON_DATA_SPDEF,
};

static const u16 statsToPrintEVs[] = {
    MON_DATA_HP_EV, MON_DATA_ATK_EV, MON_DATA_DEF_EV, MON_DATA_SPEED_EV, MON_DATA_SPATK_EV, MON_DATA_SPDEF_EV,
};

static const u16 selectedStatToStatEnum[] = {
    MON_DATA_HP_EV, MON_DATA_ATK_EV, MON_DATA_DEF_EV, MON_DATA_SPATK_EV, MON_DATA_SPDEF_EV, MON_DATA_SPEED_EV
};

static const u8 sGenderColors[2][3] =
{
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_BLUE, TEXT_COLOR_BLUE},
    {TEXT_COLOR_TRANSPARENT, TEXT_COLOR_LIGHT_RED, TEXT_COLOR_RED}
};

static const u8 sText_MenuTitle[] = _("EV Tutor");
static const u8 sText_MenuHP[] = _("HP");
static const u8 sText_MenuAttack[] = _("Attack");
static const u8 sText_MenuSpAttack[] = _("Sp. Atk");
static const u8 sText_MenuDefense[] = _("Defense");
static const u8 sText_MenuSpDefense[] = _("Sp. Def");
static const u8 sText_MenuSpeed[] = _("Speed");
static const u8 sText_MenuTotal[] = _("Total");
static const u8 sText_MenuStat[] = _("Stat");
static const u8 sText_MenuActual[] = _("Actual");
static const u8 sText_MenuEV[] = _("EV");
static const u8 sText_MonLevel[] = _("Lv.{CLEAR 1}{STR_VAR_1}");

static const u8 sText_MenuCycleMonTextMain[]   = _("{PKMN}");
static const u8 sText_MenuUndoTextMain[]    = _("{SELECT_BUTTON} Undo");
static const u8 sText_MenuBackTextMain[]    = _("{B_BUTTON} Back");
static const u8 sText_MenuEditTextMain[]    = _("{A_BUTTON} Edit");
static const u8 sText_MenuChangeStatTextMain[] = _("Change Stat");

static bool8 CanIncreaseStat()
{
    return sStatEditorDataPtr->editingStat < EV_MAX_SINGLE_STAT
        && sStatEditorDataPtr->evTotal < sStatEditorDataPtr->initialEvTotal
        && sStatEditorDataPtr->evTotal < EV_MAX_TOTAL;
}

static bool8 AreStatsValid()
{
    return sStatEditorDataPtr->evTotal == sStatEditorDataPtr->initialEvTotal;
}

static bool8 WereEVsChanged()
{
    int i;

    for (i = 0; i < NUM_STATS; i++)
        if (sStatEditorDataPtr->initialEvStats[i] != GetMonData(GetMon(), selectedStatToStatEnum[i], 0))
            return TRUE;

    return FALSE;
}

static void PrintTitleToWindowMainState()
{
    FillWindowPixelBuffer(WINDOW_1, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    
    AddTextPrinterParameterized4(WINDOW_1, FONT_NORMAL, 1, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuTitle);
    AddTextPrinterParameterized4(WINDOW_1, FONT_NORMAL, 84, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuEditTextMain);
    AddTextPrinterParameterized4(WINDOW_1, FONT_NORMAL, 127, 0, 0, 0, sMenuWindowFontColors[AreStatsValid() ? FONT_WHITE : FONT_RED], TEXT_SKIP_DRAW, sText_MenuBackTextMain);
    AddTextPrinterParameterized4(WINDOW_1, FONT_NORMAL, 171, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuUndoTextMain);

    PutWindowTilemap(WINDOW_1);
    CopyWindowToVram(WINDOW_1, 3);
}

static void PrintTitleToWindowEditState()
{
    FillWindowPixelBuffer(WINDOW_1, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    
    AddTextPrinterParameterized4(WINDOW_1, FONT_NORMAL, 1, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuTitle);

    BlitBitmapToWindow(WINDOW_1, sDPad_ButtonGfx, 88, 4, 24, 8);
    AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 115, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuChangeStatTextMain);

    AddTextPrinterParameterized4(WINDOW_1, FONT_NARROW, 184, 0, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, sText_MenuBackTextMain);

    PutWindowTilemap(WINDOW_1);
    CopyWindowToVram(WINDOW_1, 3);
}

static void PrintMonStats()
{
    u8 i;
    u16 currentStat;
    u16 nature;
    u8 text[2];
    u16 level = GetMonData(GetMon(), MON_DATA_LEVEL);
    u16 personality = GetMonData(GetMon(), MON_DATA_PERSONALITY);
    u16 gender = GetGenderFromSpeciesAndPersonality(sStatEditorDataPtr->speciesID, personality);

    FillWindowPixelBuffer(WINDOW_2, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));
    FillWindowPixelBuffer(WINDOW_3, PIXEL_FILL(TEXT_COLOR_TRANSPARENT));

    sStatEditorDataPtr->normalTotal = 0;
    sStatEditorDataPtr->evTotal = 0;

    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 31, 7, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuStat);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, STARTING_X - 6, 7, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuActual);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, STARTING_X + SECOND_COLUMN + 4, 7, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuEV);

    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 37, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 0), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuHP);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 25, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 1), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuAttack);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 25, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 2), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuDefense);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 25, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 3), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuSpAttack);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 25, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 4), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuSpDefense);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 29, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 5), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuSpeed);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NARROW, 29, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 6), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, sText_MenuTotal);

    // Print Mon Stats
    for(i = 0; i < 6; i++)
    {
        currentStat = GetMonData(GetMon(), statsToPrintActual[i]);
        sStatEditorDataPtr->normalTotal += currentStat;
        ConvertIntToDecimalStringN(gStringVar2, currentStat, STR_CONV_MODE_RIGHT_ALIGN, 3);
        AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, StatPrintData[statsToPrintActual[i]].x, StatPrintData[statsToPrintActual[i]].y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);
    }

    for(i = 0; i < 6; i++)
    {
        currentStat = GetMonData(GetMon(), statsToPrintEVs[i]);
        sStatEditorDataPtr->evTotal += currentStat;
        ConvertIntToDecimalStringN(gStringVar2, currentStat, STR_CONV_MODE_RIGHT_ALIGN, 3);
        AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, StatPrintData[statsToPrintEVs[i]].x, StatPrintData[statsToPrintEVs[i]].y, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);
    }

    // Calc Totals
    ConvertIntToDecimalStringN(gStringVar2, sStatEditorDataPtr->normalTotal, STR_CONV_MODE_RIGHT_ALIGN, 4);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, STARTING_X - 6, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 6), 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    ConvertIntToDecimalStringN(gStringVar2, sStatEditorDataPtr->evTotal, STR_CONV_MODE_RIGHT_ALIGN, 3);
    AddTextPrinterParameterized4(WINDOW_2, FONT_NORMAL, STARTING_X + SECOND_COLUMN, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 6), 0, 0, sMenuWindowFontColors[AreStatsValid() ? FONT_WHITE : FONT_RED], 0xFF, gStringVar2);

    if (sStatEditorDataPtr->evTotal != sStatEditorDataPtr->initialEvTotal)
    {
        if (sStatEditorDataPtr->evTotal > sStatEditorDataPtr->initialEvTotal)
        {
            gStringVar2[0] = CHAR_PLUS;
            ConvertIntToDecimalStringN(gStringVar2 + sizeof(u8), sStatEditorDataPtr->evTotal - sStatEditorDataPtr->initialEvTotal, STR_CONV_MODE_LEFT_ALIGN, 4);
        }
        else if (sStatEditorDataPtr->evTotal < sStatEditorDataPtr->initialEvTotal)
        {
            gStringVar2[0] = CHAR_HYPHEN;
            ConvertIntToDecimalStringN(gStringVar2 + sizeof(u8), sStatEditorDataPtr->initialEvTotal - sStatEditorDataPtr->evTotal, STR_CONV_MODE_LEFT_ALIGN, 4);
        }

        AddTextPrinterParameterized4(WINDOW_2, FONT_SMALL_NARROW, STARTING_X + SECOND_COLUMN + 22, STARTING_Y + (DISTANCE_BETWEEN_STATS_Y * 6), 0, 0, sMenuWindowFontColors[FONT_RED], 0xFF, gStringVar2);
    }

    // Print ability / nature / name / level / gender
    StringCopy(gStringVar2, gSpeciesNames[sStatEditorDataPtr->speciesID]);

    AddTextPrinterParameterized4(WINDOW_3, FONT_NARROW, 4, 2, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    ConvertIntToDecimalStringN(gStringVar1, level, STR_CONV_MODE_RIGHT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar2, sText_MonLevel);
    AddTextPrinterParameterized4(WINDOW_3, FONT_SMALL_NARROW, 4, 18, 0, 0, sMenuWindowFontColors[FONT_WHITE], TEXT_SKIP_DRAW, gStringVar2);

    StringCopy(text, gText_MaleSymbol);
    if (gender != MON_GENDERLESS)
    {
        if (gender == MON_FEMALE)
            StringCopy(text, gText_FemaleSymbol);
        else
            StringCopy(text, gText_MaleSymbol);
        AddTextPrinterParameterized4(WINDOW_3, FONT_NORMAL, 41 + 8, 19, 0, 0, sGenderColors[(gender == MON_FEMALE)], TEXT_SKIP_DRAW, text);
    }

    nature = GetNature(GetMon());
    StringCopy(gStringVar2, gNatureNamePointers[nature]);
    AddTextPrinterParameterized4(WINDOW_3, FONT_SMALL_NARROW, 4, 50, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    StringCopy(gStringVar2, gAbilityNames[gSpeciesInfo[sStatEditorDataPtr->speciesID].abilities[GetMonData(GetMon(), MON_DATA_ABILITY_NUM)]]);
    AddTextPrinterParameterized4(WINDOW_3, FONT_SMALL_NARROW, 4, 34, 0, 0, sMenuWindowFontColors[FONT_WHITE], 0xFF, gStringVar2);

    PutWindowTilemap(WINDOW_3);
    CopyWindowToVram(WINDOW_3, 3);

    PutWindowTilemap(WINDOW_2);
    CopyWindowToVram(WINDOW_2, 3);
}

struct SpriteCordsStruct {
    u8 x;
    u8 y;
};

static void SelectorCallback(struct Sprite *sprite)
{
    struct SpriteCordsStruct spriteCords[6] = {
        {203, 30 + 20},
        {203, 46 + 20},
        {203, 62 + 20},
        {203, 78 + 20},
        {203, 94 + 20},
        {203, 110 + 20},
    };

    if(sStatEditorDataPtr->inputMode == INPUT_EDIT_STAT)
    {
        if(sprite->data[0] == 32)
        {
            sprite->invisible = TRUE;
        }
        if(sprite->data[0] >= 48)
        {
            sprite->invisible = FALSE;
            sprite->data[0] = 0;
        }
        sprite->data[0]++;
    }
    else
    {
        sprite->invisible = FALSE;
        sprite->data[0] = 0;
    }

    sStatEditorDataPtr->selectedStat = sStatEditorDataPtr->selector_y;

    sprite->x = spriteCords[sStatEditorDataPtr->selector_y].x;
    sprite->y = spriteCords[sStatEditorDataPtr->selector_y].y;
}

static void UpdateSelectorAnim()
{
    const bool8 canDecrement = sStatEditorDataPtr->editingStat != 0; 
    const bool8 canIncrement = CanIncreaseStat();

    if (canDecrement && canIncrement)
        StartSpriteAnim(&gSprites[sStatEditorDataPtr->selectorSpriteId], 0);
    else if (!canDecrement && !canIncrement)
        StartSpriteAnim(&gSprites[sStatEditorDataPtr->selectorSpriteId], 3);
    else if (!canDecrement)
        StartSpriteAnim(&gSprites[sStatEditorDataPtr->selectorSpriteId], 1);
    else if (!canIncrement)
        StartSpriteAnim(&gSprites[sStatEditorDataPtr->selectorSpriteId], 2);
}

static void Task_StatEditorMain(u8 taskId) // input control when first loaded into menu
{
    if (JOY_NEW(A_BUTTON))
    {
        sStatEditorDataPtr->editingStat = GetMonData(GetMon(), selectedStatToStatEnum[sStatEditorDataPtr->selectedStat]);
        PlaySE(SE_SELECT);
        PrintTitleToWindowEditState();
        sStatEditorDataPtr->inputMode = INPUT_EDIT_STAT;
        gTasks[taskId].func = Task_MenuEditingStat;
        UpdateSelectorAnim();
        return;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        if (!AreStatsValid())
        {
            PlaySE(SE_BOO);
            return;
        }

        PlaySE(SE_SUCCESS);
        BeginNormalPaletteFade(0xFFFFFFFF, 0, 0, 16, RGB_BLACK);
        gSpecialVar_0x8004 = WereEVsChanged();
        gTasks[taskId].func = Task_StatEditorTurnOff;
    }
    else if (JOY_NEW(SELECT_BUTTON))
    {
        PlaySE(SE_FLEE);
        UndoStatChanges();
    }
    else if (JOY_NEW(DPAD_UP))
    {
        if (sStatEditorDataPtr->selector_y == 0)
            sStatEditorDataPtr->selector_y = 5;
        else
            sStatEditorDataPtr->selector_y--;
    }
    else if (JOY_NEW(DPAD_DOWN))
    {
        if (sStatEditorDataPtr->selector_y == 5)
            sStatEditorDataPtr->selector_y = 0;
        else
            sStatEditorDataPtr->selector_y++;
    }
}

static void ChangeAndUpdateStat(u16 stat, u32 statValue)
{
    u16 currentStatEnum = selectedStatToStatEnum[stat];
    u32 currentHP = 0;
    u32 oldMaxHP = 0;
    u32 amountHPLost = 0;
    s32 tempDifference = 0;
    u32 newDifference = 0;

    if (currentStatEnum == MON_DATA_HP_EV)
    {
        currentHP = GetMonData(GetMon(), MON_DATA_HP);
        oldMaxHP = GetMonData(GetMon(), MON_DATA_MAX_HP);
        amountHPLost = oldMaxHP - currentHP;
    }

    SetMonData(GetMon(), currentStatEnum, &(statValue));
    CalculateMonStats(GetMon());

    if ((amountHPLost > 0) && (currentHP != 0))
    {
        tempDifference = GetMonData(GetMon(), MON_DATA_MAX_HP) - amountHPLost;
        if (tempDifference < 0)
            tempDifference = 0;
        newDifference = (u32) tempDifference;
        SetMonData(GetMon(), MON_DATA_HP, &newDifference);
    }
}

static void HandleEditingStatInput(u32 input)
{
    bool8 canEdit = TRUE;
    if((input <= EDIT_INPUT_MAX_INCREASE_STATE) && !CanIncreaseStat())
        canEdit = FALSE;

    if((input >= EDIT_INPUT_DECREASE_STATE) && (sStatEditorDataPtr->editingStat == EV_STAT_MINIMUM))
        canEdit = FALSE;

    if (!canEdit)
    {
        UpdateSelectorAnim();
        return;
    }

    switch(input)
    {
        case EDIT_INPUT_DECREASE_STATE:
            if(sStatEditorDataPtr->editingStat != EV_STAT_MINIMUM)
                sStatEditorDataPtr->editingStat--;
            break;

        case EDIT_INPUT_MAX_DECREASE_STATE:
            sStatEditorDataPtr->editingStat = EV_STAT_MINIMUM;
            break;

        case EDIT_INPUT_INCREASE_STATE:
            if(CanIncreaseStat())
                sStatEditorDataPtr->editingStat++;
            break;

        case EDIT_INPUT_MAX_INCREASE_STATE:
            sStatEditorDataPtr->editingStat += min(sStatEditorDataPtr->initialEvTotal - sStatEditorDataPtr->evTotal, EV_MAX_SINGLE_STAT - sStatEditorDataPtr->editingStat);
            break;
    }

    ChangeAndUpdateStat(sStatEditorDataPtr->selectedStat, sStatEditorDataPtr->editingStat);
    PrintMonStats();

    UpdateSelectorAnim();
}

static void Task_MenuEditingStat(u8 taskId) // This function should be refactored to not be a hot mess
{
    if (JOY_NEW(B_BUTTON))
    {
        gTasks[taskId].func = Task_StatEditorMain;
        StartSpriteAnim(&gSprites[sStatEditorDataPtr->selectorSpriteId], 0);
        PlaySE(SE_SELECT);
        sStatEditorDataPtr->inputMode = INPUT_SELECT_STAT;
        PrintTitleToWindowMainState();
        return;
    }

    if (JOY_NEW(DPAD_LEFT))
        HandleEditingStatInput(EDIT_INPUT_DECREASE_STATE);
    else if (JOY_NEW(DPAD_RIGHT))
        HandleEditingStatInput(EDIT_INPUT_INCREASE_STATE);
    else if (JOY_NEW(DPAD_UP))
        HandleEditingStatInput(EDIT_INPUT_MAX_INCREASE_STATE);
    else if (JOY_NEW(DPAD_DOWN))
        HandleEditingStatInput(EDIT_INPUT_MAX_DECREASE_STATE);
}

static void InitializeMonStats()
{   
    u8 i;

    sStatEditorDataPtr->speciesID = GetMonData(GetMon(), MON_DATA_SPECIES);

    sStatEditorDataPtr->initialEvTotal = 0;

    for (i = 0; i < 6; i++)
    {
        sStatEditorDataPtr->initialEvStats[i] = GetMonData(GetMon(), selectedStatToStatEnum[i]);
        sStatEditorDataPtr->initialEvTotal += sStatEditorDataPtr->initialEvStats[i];
    }

    sStatEditorDataPtr->evTotal = sStatEditorDataPtr->initialEvTotal;
}

static void UndoStatChanges()
{
    u16 i;
    for (i = 0; i < 6; i++)
    {
        ChangeAndUpdateStat(i, sStatEditorDataPtr->initialEvStats[i]);
    }

    PrintMonStats();
    PrintTitleToWindowMainState();
}
