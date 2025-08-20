//CREDITS
//TheXaman:             https://github.com/TheXaman/pokeemerald/tree/tx_debug_system
//CODE USED FROM:
//ketsuban:             https://github.com/pret/pokeemerald/wiki/Add-a-debug-menu
//Pyredrid:             https://github.com/Pyredrid/pokeemerald/tree/debugmenu
//AsparagusEduardo:     https://github.com/AsparagusEduardo/pokeemerald/tree/InfusedEmerald_v2
//Ghoulslash:           https://github.com/ghoulslash/pokeemerald
//Jaizu:                https://jaizu.moe/
#include "global.h"
#include "battle.h"
#include "battle_setup.h"
#include "berry.h"
#include "coins.h"
#include "credits.h"
#include "data.h"
#include "daycare.h"
#include "debug.h"
#include "debug_pokemon_creator.h"
#include "clock.h"
#include "event_data.h"
#include "event_object_movement.h"
#include "event_scripts.h"
#include "field_message_box.h"
#include "field_screen_effect.h"
#include "field_weather.h"
#include "international_string_util.h"
#include "item.h"
#include "item_icon.h"
#include "list_menu.h"
#include "m4a.h"
#include "main.h"
#include "main_menu.h"
#include "malloc.h"
#include "map_name_popup.h"
#include "menu.h"
#include "money.h"
#include "naming_screen.h"
#include "new_game.h"
#include "overworld.h"
#include "palette.h"
#include "party_menu.h"
#include "pokedex.h"
#include "pokemon.h"
#include "pokemon_icon.h"
#include "pokemon_storage_system.h"
#include "random.h"
#include "region_map.h"
#include "script.h"
#include "script_pokemon_util.h"
#include "sound.h"
#include "strings.h"
#include "string_util.h"
#include "task.h"
#include "pokemon_summary_screen.h"
#include "wild_encounter.h"
#include "constants/abilities.h"
#include "constants/battle_ai.h"
#include "constants/battle_frontier.h"
#include "constants/coins.h"
#include "constants/flags.h"
#include "constants/items.h"
#include "constants/map_groups.h"
#include "constants/rgb.h"
#include "constants/songs.h"
#include "constants/species.h"
#include "constants/weather.h"

#if TX_DEBUG_SYSTEM_ENABLE == TRUE

// *******************************
enum DebugMenu
{
    DEBUG_MENU_ITEM_UTILITIES,
    DEBUG_MENU_ITEM_PARTY,
    DEBUG_MENU_ITEM_BAG,
    DEBUG_MENU_ITEM_FLAGVAR,
    DEBUG_MENU_ITEM_BATTLE,
    DEBUG_MENU_ITEM_PC,
    DEBUG_MENU_ITEM_POKEMON_CREATOR,
    DEBUG_MENU_ITEM_SOUND,
    DEBUG_MENU_ITEM_SCRIPTS,
};

enum UtilDebugMenu
{
    DEBUG_MENU_ITEM_UTIL_FLY,
    DEBUG_MENU_ITEM_UTIL_WARP,
    DEBUG_MENU_ITEM_UTIL_TRAINER_FUNCTIONS,
    DEBUG_MENU_ITEM_UTIL_BERRY_FUNCTIONS,
    DEBUG_MENU_ITEM_UTIL_WEATHER,
    DEBUG_MENU_ITEM_UTIL_CHECKWALLCLOCK,
    DEBUG_MENU_ITEM_UTIL_SETWALLCLOCK,
    DEBUG_MENU_ITEM_UTIL_SAVEBLOCK,
    DEBUG_MENU_ITEM_UTIL_CHEAT,
    DEBUG_MENU_ITEM_UTIL_WATCHCREDITS,
};

enum TrainerDebugMenu
{
    DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_NAME,
    DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_GENDER,
    DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_ID,
};

enum BerryFunctionsDebugMenu
{
    DEBUG_MENU_ITEM_BERRY_FUNCTIONS_CLEAR_ALL,
    DEBUG_MENU_ITEM_BERRY_FUNCTIONS_READY,
    DEBUG_MENU_ITEM_BERRY_FUNCTIONS_NEXT_STAGE,
};

enum ScriptDebugMenu
{
    DEBUG_MENU_ITEM_SCRIPT_1,
    DEBUG_MENU_ITEM_SCRIPT_2,
    DEBUG_MENU_ITEM_SCRIPT_3,
    DEBUG_MENU_ITEM_SCRIPT_4,
    DEBUG_MENU_ITEM_SCRIPT_5,
    DEBUG_MENU_ITEM_SCRIPT_6,
    DEBUG_MENU_ITEM_SCRIPT_7,
    DEBUG_MENU_ITEM_SCRIPT_8,
};

enum FlagsVarsDebugMenu
{
    DEBUG_MENU_ITEM_FLAGVAR_FLAGS,
    DEBUG_MENU_ITEM_FLAGVAR_VARS,
    DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_ALL,
    DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_RESET,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKEDEX,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_NATDEX,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKENAV,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_RUN_SHOES,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_LOCATIONS,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BADGES_ALL,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_FRONTIER_PASS,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_GAME_CLEAR,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BATTLE_DMG,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_COLLISION,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_ENCOUNTER,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_TRAINER_SEE,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BAG_USE,
    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_CATCHING,
};

enum BattleDebugMenu
{
    DEBUG_MENU_ITEM_BATTLE_START_WILD,
    DEBUG_MENU_ITEM_BATTLE_START_SINGLE,
    DEBUG_MENU_ITEM_BATTLE_START_DOUBLE,
    DEBUG_MENU_ITEM_BATTLE_START_PARTNER,
    DEBUG_MENU_ITEM_BATTLE_ENEMY_PARTY,
    DEBUG_MENU_ITEM_BATTLE_HEAL_ENEMY_PARTY,
    DEBUG_MENU_ITEM_BATTLE_CLEAR_ENEMY_PARTY,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS,
    DEBUG_MENU_ITEM_BATTLE_TERRAIN,
};

enum BattleAIFlagsDebugMenu
{
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_00,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_01,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_02,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_03,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_04,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_05,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_06,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_07,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_08,
    DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_09,
};

enum BattleTerrainDebugMenu
{
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_0,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_1,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_2,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_3,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_4,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_5,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_6,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_7,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_8,   
    DEBUG_MENU_ITEM_BATTLE_TERRAIN_9,
};

enum BagDebugMenu
{
    DEBUG_MENU_ITEM_BAG_GIVE_ITEM,
    DEBUG_MENU_ITEM_BAG_GIVE_ALL_TMS,
    DEBUG_MENU_ITEM_BAG_GIVE_ALL_HMS,
    DEBUG_MENU_ITEM_BAG_GIVE_ALL_ITEMS,
    DEBUG_MENU_ITEM_BAG_GIVE_ALL_BALLS,
    DEBUG_MENU_ITEM_BAG_GIVE_ALL_BERRIES,
    DEBUG_MENU_ITEM_BAG_GIVE_ALL_KEY_ITEMS,
    DEBUG_MENU_ITEM_BAG_MAX_MONEY,
    DEBUG_MENU_ITEM_BAG_MAX_COINS,
    DEBUG_MENU_ITEM_BAG_MAX_BATTLE_POINTS,
    DEBUG_MENU_ITEM_BAG_CLEAR
};

enum PartyDebugMenu
{
    DEBUG_MENU_ITEM_PARTY_HEAL_PARTY,
    DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_SIMPLE,
    DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_COMPLEX,
    DEBUG_MENU_ITEM_PARTY_CLEAR_PARTY,
    DEBUG_MENU_ITEM_PARTY_TRIGGER_DAYCARE_EGG,
    DEBUG_MENU_ITEM_PARTY_HATCH_EGG,
    DEBUG_MENU_ITEM_PARTY_MOVE_REMINDER,
};

enum PkmCreatorDebugMenu
{
    DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_ADD,               // Add to party
    DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT,              // Edit party
    DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT_DRAFT,        // Edit party (copies draft mon)
    DEBUG_MENU_ITEM_PKM_CREATOR_PC_EDIT,                 // Edit PC Box
    DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_ADD,         // Add to enemy party
    DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT,        // Edit enemy party
    DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT_DRAFT,  // Edit enemy party (copies draft mon)
    DEBUG_MENU_ITEM_PKM_CREATOR_TESTING,                 // Testing mode (doesn't modify parties)
    DEBUG_MENU_ITEM_PKM_CREATOR_TESTING_COPY,            // Testing mode (doesn't modify parties, copy first mon in party)
};

enum PCDebugMenu
{
    DEBUG_MENU_ITEM_PC_ACCESS,
    DEBUG_MENU_ITEM_PC_FILL_BOXES_SAME,
    DEBUG_MENU_ITEM_PC_FILL_BOXES_DIVERSE,
    DEBUG_MENU_ITEM_PC_FILL_ITEMS,
    DEBUG_MENU_ITEM_PC_CLEAR,
};

enum SoundDebugMenu
{
    DEBUG_MENU_ITEM_SOUND_SE,
    DEBUG_MENU_ITEM_SOUND_MUSIC,
    DEBUG_MENU_ITEM_SOUND_TOGGLE_MAP_MUSIC,
};


// *******************************
// Constants
#define DEBUG_MENU_WIDTH_MAIN 17
#define DEBUG_MENU_HEIGHT_MAIN 9

#define DEBUG_MENU_WIDTH_EXTRA 10
#define DEBUG_MENU_HEIGHT_EXTRA 4

#define DEBUG_MENU_WIDTH_WEATHER 15
#define DEBUG_MENU_HEIGHT_WEATHER 3

#define DEBUG_MENU_WIDTH_SOUND 20
#define DEBUG_MENU_HEIGHT_SOUND 6

#define DEBUG_MENU_WIDTH_FLAGVAR 4
#define DEBUG_MENU_HEIGHT_FLAGVAR 2

#define DEBUG_NUMBER_DIGITS_FLAGS 4
#define DEBUG_NUMBER_DIGITS_VARIABLES 5
#define DEBUG_NUMBER_DIGITS_VARIABLE_VALUE 5
#define DEBUG_NUMBER_DIGITS_ITEMS 4
#define DEBUG_NUMBER_DIGITS_ITEM_QUANTITY 3

#define DEBUG_NUMBER_ICON_X 210
#define DEBUG_NUMBER_ICON_Y 50

#define DEBUG_MENU_FONT FONT_NORMAL

#define DEBUG_MENU_MAX_LIST_ITEMS 30
#define DEBUG_MENU_MAX_LIST_ITEM_NAME_LENGTH 26

#define DEBUG_MENU_INVALID_FLAG_VALUE 0xFF

// *******************************
struct DebugMonData
{
    u16 species;
    u8 level;
    bool8 isShiny;
    u8 nature;
    u8 abilityNum;
    u8 monIVs[NUM_STATS];
    u8 monEVs[NUM_STATS];
    u16 monMoves[MAX_MON_MOVES];
};

struct DebugMenuListData
{
    struct ListMenuItem listItems[DEBUG_MENU_MAX_LIST_ITEMS];
    u8 itemNames[DEBUG_MENU_MAX_LIST_ITEMS][DEBUG_MENU_MAX_LIST_ITEM_NAME_LENGTH];
};

struct DebugBattleData
{
    u8 battleType;
    u8 battleTerrain;
    bool8 aiFlags[AI_FLAG_COUNT];
};

// EWRAM
static EWRAM_DATA struct DebugMonData *sDebugMonData = NULL;
static EWRAM_DATA struct DebugMenuListData *sDebugMenuListData = NULL;
static EWRAM_DATA struct DebugBattleData sDebugBattleData = {0};
EWRAM_DATA bool8 gIsDebugBattle = FALSE;
EWRAM_DATA u32 gDebugAIFlags = 0;

// *******************************
// General functions
static u8 Debug_ShowMenu(void (*HandleInput)(u8), struct ListMenuTemplate LMtemplate);
static void Debug_DestroyMenu(u8 taskId);
static void Debug_DestroyMenu_Full(u8 taskId);
static void DebugAction_DestroyExtraWindow(u8 taskId);

// *******************************
// Main menu functions
static void Debug_ReShowMainMenu(void);
static void DebugAction_OpenUtilitiesMenu(u8 taskId);
static void DebugAction_OpenScriptsMenu(u8 taskId);
static void DebugAction_OpenFlagsVarsMenu(u8 taskId);
static void DebugAction_OpenBattleMenu(u8 taskId);
static void DebugAction_OpenBagMenu(u8 taskId);
static void DebugAction_OpenPartyMenu(u8 taskId);
static void DebugAction_OpenPokemonCreator(u8 taskId);
static void DebugAction_OpenPCMenu(u8 taskId);
static void DebugAction_OpenSoundMenu(u8 taskId);
static void DebugTask_HandleMenuInput_Main(u8 taskId);
static void DebugTask_HandleMenuInput_Utilities(u8 taskId);
static void DebugTask_HandleMenuInput_Scripts(u8 taskId);
static void DebugTask_HandleMenuInput_FlagsVars(u8 taskId);
static void DebugTask_HandleMenuInput_Battle(u8 taskId);
static void DebugTask_HandleMenuInput_Bag(u8 taskId);
static void DebugTask_HandleMenuInput_Party(u8 taskId);
static void DebugTask_HandleMenuInput_PkmCreator(u8 taskId);
static void DebugTask_HandleMenuInput_PC(u8 taskId);
static void DebugTask_HandleMenuInput_Sound(u8 taskId);

// *******************************
// Utilities menu functions
static void DebugAction_Util_Fly(u8 taskId);
static void DebugAction_Util_Warp(u8 taskId);
static void DebugAction_Util_Warp_SelectMapGroup(u8 taskId);
static void DebugAction_Util_Warp_SelectMap(u8 taskId);
static void DebugAction_Util_Warp_SelectWarp(u8 taskId);
static void DebugAction_Util_CheckSaveBlock(u8 taskId);
static void DebugAction_Util_Weather(u8 taskId);
static void DebugAction_Util_Weather_SelectId(u8 taskId);
static void DebugAction_Util_CheckWallClock(u8 taskId);
static void DebugAction_Util_SetWallClock(u8 taskId);
static void DebugAction_Util_WatchCredits(u8 taskId);
static void DebugAction_Util_BerryFunctions(u8 taskId);
static void DebugAction_Util_TrainerFunctions(u8 taskId);
static void DebugAction_Util_CheatStart(u8 taskId);
static void DebugAction_TrainerFunctions_Name(u8 taskId);
static void DebugAction_TrainerFunctions_Gender(u8 taskId);
static void DebugAction_TrainerFunctions_Id(u8 taskId);
static void DebugAction_BerryFunctions_ClearAll(u8 taskId);
static void DebugAction_BerryFunctions_Ready(u8 taskId);
static void DebugAction_BerryFunctions_NextStage(u8 taskId);
static void DebugTask_HandleMenuInput_TrainerFunctions(u8 taskId);
static void DebugTask_HandleMenuInput_BerryFunctions(u8 taskId);

// *******************************
// Scripts menu functions
static void DebugAction_Script_1(u8 taskId);
static void DebugAction_Script_2(u8 taskId);
static void DebugAction_Script_3(u8 taskId);
static void DebugAction_Script_4(u8 taskId);
static void DebugAction_Script_5(u8 taskId);
static void DebugAction_Script_6(u8 taskId);
static void DebugAction_Script_7(u8 taskId);
static void DebugAction_Script_8(u8 taskId);

// *******************************
// Flags & Vars menu functions
static void Debug_RedrawFlagsVarsMenu(u8 taskId);
static void Debug_RefreshFlagsVarsListItems();
static void DebugAction_FlagsVars_Flags(u8 taskId);
static void DebugAction_FlagsVars_FlagsSelect(u8 taskId);
static void DebugAction_FlagsVars_Vars(u8 taskId);
static void DebugAction_FlagsVars_Select(u8 taskId);
static void DebugAction_FlagsVars_SetValue(u8 taskId);
static void DebugAction_FlagsVars_PokedexFlags_All(u8 taskId);
static void DebugAction_FlagsVars_PokedexFlags_Reset(u8 taskId);
static void DebugAction_FlagsVars_SwitchDex(u8 taskId);
static void DebugAction_FlagsVars_SwitchNatDex(u8 taskId);
static void DebugAction_FlagsVars_SwitchPokeNav(u8 taskId);
static void DebugAction_FlagsVars_RunningShoes(u8 taskId);
static void DebugAction_FlagsVars_ToggleFlyFlags(u8 taskId);
static void DebugAction_FlagsVars_ToggleBadgeFlags(u8 taskId);
static void DebugAction_FlagsVars_ToggleFrontierPass(u8 taskId);
static void DebugAction_FlagsVars_ToggleGameClear(u8 taskId);
static void DebugAction_FlagsVars_BattleDmgOnOff(u8 taskId);
static void DebugAction_FlagsVars_CollisionOnOff(u8 taskId);
static void DebugAction_FlagsVars_EncounterOnOff(u8 taskId);
static void DebugAction_FlagsVars_TrainerSeeOnOff(u8 taskId);
static void DebugAction_FlagsVars_BagUseOnOff(u8 taskId);
static void DebugAction_FlagsVars_CatchingOnOff(u8 taskId);

// *******************************
// Battle menu functions
static void Debug_InitializeBattle(u8 taskId);
static void Debug_RefreshEnemyPartyListItems();
static void Debug_RefreshAIFlagsListItems();
static void Debug_RefreshTerrainListItems();
static void DebugAction_Battle_InitializeWildBattle(u8 taskId);
static void DebugAction_Battle_InitializeSingleBattle(u8 taskId);
static void DebugAction_Battle_InitializeDoubleBattle(u8 taskId);
static void DebugAction_Battle_InitializePartnerBattle(u8 taskId);
static void DebugAction_Battle_OpenEnemyPartyMenu(u8 taskId);
static void DebugAction_Battle_HealEnemyPartyMenu(u8 taskId);
static void DebugAction_Battle_ClearEnemyPartyMenu(u8 taskId);
static void DebugAction_Battle_OpenAIFlagsMenu(u8 taskId);
static void DebugAction_Battle_OpenTerrainMenu(u8 taskId);
static void Debug_RedrawBattleEnemyPartyMenu(u8 taskId);
static void Debug_RedrawBattleAIFlagsMenu(u8 taskId);
static void Debug_RedrawBattleTerrainMenu(u8 taskId);
static void DebugTask_HandleMenuInput_Battle_EnemyParty(u8 taskId);
static void DebugTask_HandleMenuInput_Battle_AIFlags(u8 taskId);
static void DebugTask_HandleMenuInput_Battle_Terrain(u8 taskId);

// *******************************
// Bag menu functions
static void DebugAction_Bag_Give_Item(u8 taskId);
static void DebugAction_Bag_Give_Item_SelectId(u8 taskId);
static void DebugAction_Bag_Give_Item_SelectQuantity(u8 taskId);
static void DebugAction_Bag_Give_All_TMs(u8 taskId);
static void DebugAction_Bag_Give_All_HMs(u8 taskId);
static void DebugAction_Bag_Give_All_Items(u8 taskId);
static void DebugAction_Bag_Give_All_PokeBalls(u8 taskId);
static void DebugAction_Bag_Give_All_Berries(u8 taskId);
static void DebugAction_Bag_Give_All_KeyItems(u8 taskId);
static void DebugAction_Bag_MaxMoney(u8 taskId);
static void DebugAction_Bag_MaxCoins(u8 taskId);
static void DebugAction_Bag_MaxBattlePoints(u8 taskId);
static void DebugAction_Bag_Clear(u8 taskId);

// *******************************
// Party menu functions
static void DebugAction_Party_HealParty(u8 taskId);
static void DebugAction_Party_GivePokemonSimple(u8 taskId);
static void DebugAction_Party_GivePokemonComplex(u8 taskId);
static void DebugAction_Party_GivePokemon_SelectId(u8 taskId);
static void DebugAction_Party_GivePokemon_SelectLevel(u8 taskId);
static void DebugAction_Party_GivePokemon_SelectShiny(u8 taskId);
static void DebugAction_Party_GivePokemon_SelectNature(u8 taskId);
static void DebugAction_Party_GivePokemon_SelectAbility(u8 taskId);
static void DebugAction_Party_GivePokemon_SelectIVs(u8 taskId);
static void DebugAction_Party_GivePokemon_SelectEVs(u8 taskId);
static void DebugAction_Party_GivePokemon_ComplexCreateMon(u8 taskId);
static void DebugAction_Party_GivePokemon_Moves(u8 taskId);
static void DebugAction_Party_ClearParty(u8 taskId);
static void DebugAction_Party_TriggerDaycareEgg(u8 taskId);
static void DebugAction_Party_HatchAnEgg(u8 taskId);
static void DebugAction_Party_MoveReminder(u8 taskId);

// *******************************
// Pokemon Creator menu functions
static void DebugAction_PkmCreator_Party_Add(u8 taskid);
static void DebugAction_PkmCreator_Party_Edit(u8 taskid);
static void DebugAction_PkmCreator_PC_Edit(u8 taskid);
static void DebugAction_PkmCreator_Enemy_Party_Edit(u8 taskId);
static void DebugAction_PkmCreator_Enemy_Party_Edit_Draft(u8 taskId);
static void DebugAction_PkmCreator_Party_Edit_Draft(u8 taskid);
static void DebugAction_PkmCreator_Enemy_Party_Add(u8 taskid);
static void DebugAction_PkmCreator_Testing(u8 taskid);
static void DebugAction_PkmCreator_Testing_Copy(u8 taskid); 

// *******************************
// PC menu functions
static void DebugAction_PC_Access(u8 taskId);
static void DebugAction_PC_FillBoxesSame(u8 taskId);
static void DebugAction_PC_FillBoxesDiverse(u8 taskId);
static void DebugAction_PC_FillItemStorage(u8 taskId);
static void DebugAction_PC_Clear(u8 taskId);

// *******************************
// Sound menu functions
static void DebugAction_Sound_SE(u8 taskId);
static void DebugAction_Sound_SE_SelectId(u8 taskId);
static void DebugAction_Sound_Music(u8 taskId);
static void DebugAction_Sound_Music_SelectId(u8 taskId);
static void DebugAction_Sound_ToggleMapMusic(u8 taskId);

extern u8 Debug_Script_1[];
extern u8 Debug_Script_2[];
extern u8 Debug_Script_3[];
extern u8 Debug_Script_4[];
extern u8 Debug_Script_5[];
extern u8 Debug_Script_6[];
extern u8 Debug_Script_7[];
extern u8 Debug_Script_8[];

extern u8 Debug_ShowFieldMessageStringVar4[];
extern u8 Debug_CheatStart[];
extern u8 Debug_HatchAnEgg[];
extern u8 DebugScript_DaycareMonsNotCompatible[];
extern u8 DebugScript_OneDaycareMons[];
extern u8 DebugScript_ZeroDaycareMons[];
extern u8 PlayersHouse_2F_EventScript_SetWallClock[];
extern u8 PlayersHouse_2F_EventScript_CheckWallClock[];
extern u8 FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon[];

#define ABILITY_NAME_LENGTH 12
extern const u8 gAbilityNames[][ABILITY_NAME_LENGTH + 1];


// *******************************
//Maps per map group COPY FROM /include/constants/map_groups.h
static const u8 MAP_GROUP_COUNT[] = {57, 5, 5, 6, 7, 8, 9, 7, 7, 14, 8, 17, 10, 23, 13, 15, 15, 2, 2, 2, 3, 1, 1, 1, 108, 61, 89, 2, 1, 13, 1, 1, 3, 1, 0};

// Text
// General
static const u8 sDebugText_True[] =          _("TRUE");
static const u8 sDebugText_False[] =         _("FALSE");
static const u8 sDebugText_Colored_True[] =  _("{COLOR GREEN}TRUE");
static const u8 sDebugText_Colored_False[] = _("{COLOR RED}FALSE");
static const u8 sDebugText_Dashes[] =        _("---");
static const u8 sDebugText_Empty[] =         _("");
static const u8 sDebugText_Continue[] =      _("Continue…{CLEAR_TO 110}{RIGHT_ARROW}");
// Main Menu
static const u8 sDebugText_Utilities[] =  _("Utilities…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Scripts[] =    _("Scripts…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_FlagsVars[] =  _("Flags & Vars…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Battle[] =     _("Battle Test…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Bag[] =        _("Bag…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Party[] =      _("Party…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_PkmCreator[] = _("Pokémon Creator…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_PC[] =         _("PC…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Sound[] =      _("Sound…{CLEAR_TO 110}{RIGHT_ARROW}");
// Script menu
static const u8 sDebugText_Script_1[] = _("Script 1");
static const u8 sDebugText_Script_2[] = _("Script 2");
static const u8 sDebugText_Script_3[] = _("Script 3");
static const u8 sDebugText_Script_4[] = _("Script 4");
static const u8 sDebugText_Script_5[] = _("Script 5");
static const u8 sDebugText_Script_6[] = _("Script 6");
static const u8 sDebugText_Script_7[] = _("Script 7");
static const u8 sDebugText_Script_8[] = _("Script 8");
// Util Menu
static const u8 sDebugText_Util_Fly[] =                      _("Fly to Map…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_WarpToMap[] =                _("Warp to Map Warp…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_WarpToMap_SelectMapGroup[] = _("Group: {STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n\n{STR_VAR_3}{CLEAR_TO 90}");
static const u8 sDebugText_Util_WarpToMap_SelectMap[] =      _("Map: {STR_VAR_1}{CLEAR_TO 90}\nMapSec:{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}\n{STR_VAR_3}{CLEAR_TO 90}");
static const u8 sDebugText_Util_WarpToMap_SelectWarp[] =     _("Warp:{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_3}{CLEAR_TO 90}");
static const u8 sDebugText_Util_WarpToMap_SelMax[] =         _("{STR_VAR_1} / {STR_VAR_2}");
static const u8 sDebugText_Util_SaveBlockSpace[] =           _("SaveBlock Space…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_Weather[] =                  _("Set Weather…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_Weather_ID[] =               _("Weather Id: {STR_VAR_3}\n{STR_VAR_1}\n{STR_VAR_2}");
static const u8 sDebugText_Util_CheckWallClock[] =           _("Check Wall Clock…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_SetWallClock[] =             _("Set Wall Clock…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_WatchCredits[] =             _("Watch Credits…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_Trainer_Functions[] =        _("Trainer Functions…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_Berry_Functions[] =          _("Berry Functions…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Util_CheatStart[] =               _("Cheat Start");
// Trainer Functions Menu
static const u8 sDebugText_TrainerFunctions_Name[] =   _("Set Trainer Name…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_TrainerFunctions_Gender[] = _("Toggle Trainer Gender");
static const u8 sDebugText_TrainerFunctions_Id[] =     _("New Trainer Id");
// Berry Functions Menu
static const u8 sDebugText_BerryFunctions_ClearAll[] =  _("Clear Trees");
static const u8 sDebugText_BerryFunctions_Ready[] =     _("Ready Trees");
static const u8 sDebugText_BerryFunctions_NextStage[] = _("Grow Trees");
// Flags/Vars Menu
static const u8 sDebugText_FlagsVars_Flags[] =              _("Set Flag…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_FlagsVars_Flag[] =               _("Flag: {STR_VAR_1}{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}\n{STR_VAR_3}");
static const u8 sDebugText_FlagsVars_FlagHex[] =            _("{STR_VAR_1}{CLEAR_TO 90}\n0x{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_FlagsVars_Vars[] =               _("Set Var…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_FlagsVars_VariableHex[] =        _("{STR_VAR_1}{CLEAR_TO 90}\n0x{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_FlagsVars_Variable[] =           _("Var: {STR_VAR_1}{CLEAR_TO 90}\nVal: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_2}");
static const u8 sDebugText_FlagsVars_VariableValueSet[] =   _("Var: {STR_VAR_1}{CLEAR_TO 90}\nVal: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_2}");
static const u8 sDebugText_FlagsVars_PokedexFlags_All[] =   _("Pokédex Flags All");
static const u8 sDebugText_FlagsVars_PokedexFlags_Reset[] = _("Pokédex Flags Reset");
static const u8 sDebugText_FlagsVars_SwitchDex[] =          _("Toggle {STR_VAR_1}Pokédex");
static const u8 sDebugText_FlagsVars_SwitchNationalDex[] =  _("Toggle {STR_VAR_1}NatDex");
static const u8 sDebugText_FlagsVars_SwitchPokeNav[] =      _("Toggle {STR_VAR_1}PokéNav");
static const u8 sDebugText_FlagsVars_RunningShoes[] =       _("Toggle {STR_VAR_1}Running Shoes");
static const u8 sDebugText_FlagsVars_ToggleFlyFlags[] =     _("Toggle {STR_VAR_1}Fly Flags");
static const u8 sDebugText_FlagsVars_ToggleAllBadges[] =    _("Toggle {STR_VAR_1}All badges");
static const u8 sDebugText_FlagsVars_ToggleFrontierPass[] = _("Toggle {STR_VAR_1}Frontier Pass");
static const u8 sDebugText_FlagsVars_ToggleGameClear[] =    _("Toggle {STR_VAR_1}Game Clear");
static const u8 sDebugText_FlagsVars_BattleDmg[] =          _("Toggle {STR_VAR_1}BattleDmg OFF");
static const u8 sDebugText_FlagsVars_SwitchCollision[] =    _("Toggle {STR_VAR_1}Collision OFF");
static const u8 sDebugText_FlagsVars_SwitchEncounter[] =    _("Toggle {STR_VAR_1}Encounter OFF");
static const u8 sDebugText_FlagsVars_SwitchTrainerSee[] =   _("Toggle {STR_VAR_1}TrainerSee OFF");
static const u8 sDebugText_FlagsVars_SwitchBagUse[] =       _("Toggle {STR_VAR_1}BagUse OFF");
static const u8 sDebugText_FlagsVars_SwitchCatching[] =     _("Toggle {STR_VAR_1}Catching OFF");
// Battle
static const u8 sDebugText_Battle_Start_Wild[]      = _("Start Wild…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Battle_Start_Single[]    = _("Start Single…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Battle_Start_Double[]    = _("Start Double…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Battle_Start_Partner[]   = _("Start Partner…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Battle_EnemyParty[]      = _("Enemy Party…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Battle_HealEnemyParty[]  = _("Heal Enemy Party");
static const u8 sDebugText_Battle_ClearEnemyParty[] = _("Clear Enemy Party");
static const u8 sDebugText_Battle_AIFlags[]         = _("AI Flags…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Battle_Terrain[]         = _("Terrain…{CLEAR_TO 110}{RIGHT_ARROW}");

static const u8 sDebugText_Battle_AIFlag_00[] = _("{STR_VAR_1}Check bad move");
static const u8 sDebugText_Battle_AIFlag_01[] = _("{STR_VAR_1}Try to faint");
static const u8 sDebugText_Battle_AIFlag_02[] = _("{STR_VAR_1}Check viability");
static const u8 sDebugText_Battle_AIFlag_03[] = _("{STR_VAR_1}Setup first turn");
static const u8 sDebugText_Battle_AIFlag_04[] = _("{STR_VAR_1}Risky");
static const u8 sDebugText_Battle_AIFlag_05[] = _("{STR_VAR_1}Prefer power extremes");
static const u8 sDebugText_Battle_AIFlag_06[] = _("{STR_VAR_1}Prefer baton pass");
static const u8 sDebugText_Battle_AIFlag_07[] = _("{STR_VAR_1}Double battle");
static const u8 sDebugText_Battle_AIFlag_08[] = _("{STR_VAR_1}Hp aware");
static const u8 sDebugText_Battle_AIFlag_09[] = _("{STR_VAR_1}Try sunny day start");

static const u8 sDebugText_Battle_Terrain_0[] = _("Grass");
static const u8 sDebugText_Battle_Terrain_1[] = _("Long grass");
static const u8 sDebugText_Battle_Terrain_2[] = _("Sand");
static const u8 sDebugText_Battle_Terrain_3[] = _("Underwater");
static const u8 sDebugText_Battle_Terrain_4[] = _("Water");
static const u8 sDebugText_Battle_Terrain_5[] = _("Pond");
static const u8 sDebugText_Battle_Terrain_6[] = _("Mountain");
static const u8 sDebugText_Battle_Terrain_7[] = _("Cave");
static const u8 sDebugText_Battle_Terrain_8[] = _("Building");
static const u8 sDebugText_Battle_Terrain_9[] = _("Plain");
// Bag menu
static const u8 sDebugText_Bag_Give_Item[] =          _("Give item…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Bag_Give_All_TMs[] =       _("Give all TMs");
static const u8 sDebugText_Bag_Give_All_HMs[] =       _("Give all HMs");
static const u8 sDebugText_Bag_Give_All_Items[] =     _("Give all Items");
static const u8 sDebugText_Bag_Give_All_PokeBalls[] = _("Give all PokeBalls");
static const u8 sDebugText_Bag_Give_All_Berries[] =   _("Give all Berries");
static const u8 sDebugText_Bag_Give_All_KeyItems[] =  _("Give all KeyItems");
static const u8 sDebugText_Bag_Give_MaxMoney[] =      _("Give Max Money");
static const u8 sDebugText_Bag_Give_MaxCoins[] =      _("Give Max Coins");
static const u8 sDebugText_Bag_Give_BattlePoints[] =  _("Give Max Battle Points");
static const u8 sDebugText_Bag_Clear[] =              _("Clear Bag");
static const u8 sDebugText_ItemQuantity[] =           _("Quantity:{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n\n{STR_VAR_2}");
static const u8 sDebugText_ItemID[] =                 _("Item Id: {STR_VAR_3}\n{STR_VAR_1}{CLEAR_TO 90}\n\n{STR_VAR_2}");
// Party menu
static const u8 sDebugText_Party_HealParty[] =          _("Heal Party");
static const u8 sDebugText_Party_GivePokemonSimple[] =  _("Give Pkm (Simple)…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Party_GivePokemonComplex[] = _("Give Pkm (Complex)…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_PokemonID[] =                _("Species: {STR_VAR_3}\n{STR_VAR_1}{CLEAR_TO 90}\n\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonLevel[] =             _("Level:{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonShiny[] =             _("Shiny:{CLEAR_TO 90}\n   {STR_VAR_2}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{CLEAR_TO 90}");
static const u8 sDebugText_PokemonNature[] =            _("NatureId: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonAbility[] =           _("AbilityNum: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonIVs[] =               _("IV {STR_VAR_1}:{CLEAR_TO 90}\n    {STR_VAR_3}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonEVs[] =               _("EV {STR_VAR_1}:{CLEAR_TO 90}\n    {STR_VAR_3}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonMove_0[] =            _("Move 0: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonMove_1[] =            _("Move 1: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonMove_2[] =            _("Move 2: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_PokemonMove_3[] =            _("Move 3: {STR_VAR_3}{CLEAR_TO 90}\n{STR_VAR_1}{CLEAR_TO 90}\n{CLEAR_TO 90}\n{STR_VAR_2}{CLEAR_TO 90}");
static const u8 sDebugText_Party_ClearParty[] =         _("Clear Party");
static const u8 sDebugText_Party_DaycareEgg[] =         _("Trigger Daycare Egg");
static const u8 sDebugText_Party_HatchAnEgg[] =         _("Hatch Egg…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Party_MoveReminder[] =       _("Move Reminder…{CLEAR_TO 110}{RIGHT_ARROW}");
// Pokemon Creator
static const u8 sDebugText_PkmCreator_Party_Add[] =              _("Party add");
static const u8 sDebugText_PkmCreator_Party_Edit[] =             _("Party edit");
static const u8 sDebugText_PkmCreator_PC_Edit[] =                _("PC edit");
static const u8 sDebugText_PkmCreator_Enemy_Party_Edit[] =       _("Enemy edit");
static const u8 sDebugText_PkmCreator_Enemy_Party_Edit_Draft[] = _("Enemy edit (copy draft)");
static const u8 sDebugText_PkmCreator_Party_Edit_Draft[] =       _("Party edit (copy draft)");
static const u8 sDebugText_PkmCreator_Enemy_Party_Add[] =        _("Enemy add");
static const u8 sDebugText_PkmCreator_Testing[] =                _("Testing");
static const u8 sDebugText_PkmCreator_Testing_Copy[] =           _("Testing (copy party 1st)");
// PC Menu
static const u8 sDebugText_PC_Access[] =           _("Access PC…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_PC_FillBoxesSame[] =    _("Fill Boxes (Same)");
static const u8 sDebugText_PC_FillBoxesDiverse[] = _("Fill Boxes (Diverse)");
static const u8 sDebugText_PC_FillItemStorage[] =  _("Fill Item Storage");
static const u8 sDebugText_PC_Clear[] =            _("Clear Boxes");
// Sound Mneu
static const u8 sDebugText_Sound_SE[] =             _("Effects…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Sound_SE_ID[] =          _("Sound Id: {STR_VAR_3}\n{STR_VAR_1}    \n{STR_VAR_2}");
static const u8 sDebugText_Sound_Music[] =          _("Music…{CLEAR_TO 110}{RIGHT_ARROW}");
static const u8 sDebugText_Sound_Music_ID[] =       _("Music Id: {STR_VAR_3}\n{STR_VAR_1}    \n{STR_VAR_2}");
static const u8 sDebugText_Sound_ToggleMapMusic[] = _("Toggle Map Music");

static const u8 digitInidicator_1[] =        _("{LEFT_ARROW}+1{RIGHT_ARROW}        ");
static const u8 digitInidicator_10[] =       _("{LEFT_ARROW}+10{RIGHT_ARROW}       ");
static const u8 digitInidicator_100[] =      _("{LEFT_ARROW}+100{RIGHT_ARROW}      ");
static const u8 digitInidicator_1000[] =     _("{LEFT_ARROW}+1000{RIGHT_ARROW}     ");
static const u8 digitInidicator_10000[] =    _("{LEFT_ARROW}+10000{RIGHT_ARROW}    ");
static const u8 digitInidicator_100000[] =   _("{LEFT_ARROW}+100000{RIGHT_ARROW}   ");
static const u8 digitInidicator_1000000[] =  _("{LEFT_ARROW}+1000000{RIGHT_ARROW}  ");
static const u8 digitInidicator_10000000[] = _("{LEFT_ARROW}+10000000{RIGHT_ARROW} ");
const u8 * const gText_DigitIndicator[] =
{
    digitInidicator_1,
    digitInidicator_10,
    digitInidicator_100,
    digitInidicator_1000,
    digitInidicator_10000,
    digitInidicator_100000,
    digitInidicator_1000000,
    digitInidicator_10000000
};
static const s32 sPowersOfTen[] =
{
             1,
            10,
           100,
          1000,
         10000,
        100000,
       1000000,
      10000000,
     100000000,
    1000000000,
};

// *******************************
// List Menu Items
static const struct ListMenuItem sDebugMenu_Items_Main[] =
{
    [DEBUG_MENU_ITEM_UTILITIES]       = {sDebugText_Utilities,  DEBUG_MENU_ITEM_UTILITIES},
    [DEBUG_MENU_ITEM_PARTY]           = {sDebugText_Party,      DEBUG_MENU_ITEM_PARTY},
    [DEBUG_MENU_ITEM_BAG]             = {sDebugText_Bag,        DEBUG_MENU_ITEM_BAG},
    [DEBUG_MENU_ITEM_FLAGVAR]         = {sDebugText_FlagsVars,  DEBUG_MENU_ITEM_FLAGVAR},
    [DEBUG_MENU_ITEM_BATTLE]          = {sDebugText_Battle,     DEBUG_MENU_ITEM_BATTLE},
    [DEBUG_MENU_ITEM_PC]              = {sDebugText_PC,         DEBUG_MENU_ITEM_PC},
    [DEBUG_MENU_ITEM_POKEMON_CREATOR] = {sDebugText_PkmCreator, DEBUG_MENU_ITEM_POKEMON_CREATOR},
    [DEBUG_MENU_ITEM_SOUND]           = {sDebugText_Sound,      DEBUG_MENU_ITEM_SOUND},
    [DEBUG_MENU_ITEM_SCRIPTS]         = {sDebugText_Scripts,    DEBUG_MENU_ITEM_SCRIPTS},
};
static const struct ListMenuItem sDebugMenu_Items_Utilities[] =
{
    [DEBUG_MENU_ITEM_UTIL_FLY]               = {sDebugText_Util_Fly,               DEBUG_MENU_ITEM_UTIL_FLY},
    [DEBUG_MENU_ITEM_UTIL_WARP]              = {sDebugText_Util_WarpToMap,         DEBUG_MENU_ITEM_UTIL_WARP},
    [DEBUG_MENU_ITEM_UTIL_TRAINER_FUNCTIONS] = {sDebugText_Util_Trainer_Functions, DEBUG_MENU_ITEM_UTIL_TRAINER_FUNCTIONS},
    [DEBUG_MENU_ITEM_UTIL_BERRY_FUNCTIONS]   = {sDebugText_Util_Berry_Functions,   DEBUG_MENU_ITEM_UTIL_BERRY_FUNCTIONS},
    [DEBUG_MENU_ITEM_UTIL_WEATHER]           = {sDebugText_Util_Weather,           DEBUG_MENU_ITEM_UTIL_WEATHER},
    [DEBUG_MENU_ITEM_UTIL_CHECKWALLCLOCK]    = {sDebugText_Util_CheckWallClock,    DEBUG_MENU_ITEM_UTIL_CHECKWALLCLOCK},
    [DEBUG_MENU_ITEM_UTIL_SETWALLCLOCK]      = {sDebugText_Util_SetWallClock,      DEBUG_MENU_ITEM_UTIL_SETWALLCLOCK},
    [DEBUG_MENU_ITEM_UTIL_SAVEBLOCK]         = {sDebugText_Util_SaveBlockSpace,    DEBUG_MENU_ITEM_UTIL_SAVEBLOCK},
    [DEBUG_MENU_ITEM_UTIL_CHEAT]             = {sDebugText_Util_CheatStart,        DEBUG_MENU_ITEM_UTIL_CHEAT},
    [DEBUG_MENU_ITEM_UTIL_WATCHCREDITS]      = {sDebugText_Util_WatchCredits,      DEBUG_MENU_ITEM_UTIL_WATCHCREDITS},
};
static const struct ListMenuItem sDebugMenu_Items_TrainerFunctions[] =
{
    [DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_NAME]   = {sDebugText_TrainerFunctions_Name,   DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_NAME},
    [DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_GENDER] = {sDebugText_TrainerFunctions_Gender, DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_GENDER},
    [DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_ID]     = {sDebugText_TrainerFunctions_Id,     DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_ID},
};
static const struct ListMenuItem sDebugMenu_Items_BerryFunctions[] =
{
    [DEBUG_MENU_ITEM_BERRY_FUNCTIONS_CLEAR_ALL]  = {sDebugText_BerryFunctions_ClearAll,  DEBUG_MENU_ITEM_BERRY_FUNCTIONS_CLEAR_ALL},
    [DEBUG_MENU_ITEM_BERRY_FUNCTIONS_READY]      = {sDebugText_BerryFunctions_Ready,     DEBUG_MENU_ITEM_BERRY_FUNCTIONS_READY},
    [DEBUG_MENU_ITEM_BERRY_FUNCTIONS_NEXT_STAGE] = {sDebugText_BerryFunctions_NextStage, DEBUG_MENU_ITEM_BERRY_FUNCTIONS_NEXT_STAGE},
};
static const struct ListMenuItem sDebugMenu_Items_Scripts[] =
{
    [DEBUG_MENU_ITEM_SCRIPT_1] = {sDebugText_Script_1, DEBUG_MENU_ITEM_SCRIPT_1},
    [DEBUG_MENU_ITEM_SCRIPT_2] = {sDebugText_Script_2, DEBUG_MENU_ITEM_SCRIPT_2},
    [DEBUG_MENU_ITEM_SCRIPT_3] = {sDebugText_Script_3, DEBUG_MENU_ITEM_SCRIPT_3},
    [DEBUG_MENU_ITEM_SCRIPT_4] = {sDebugText_Script_4, DEBUG_MENU_ITEM_SCRIPT_4},
    [DEBUG_MENU_ITEM_SCRIPT_5] = {sDebugText_Script_5, DEBUG_MENU_ITEM_SCRIPT_5},
    [DEBUG_MENU_ITEM_SCRIPT_6] = {sDebugText_Script_6, DEBUG_MENU_ITEM_SCRIPT_6},
    [DEBUG_MENU_ITEM_SCRIPT_7] = {sDebugText_Script_7, DEBUG_MENU_ITEM_SCRIPT_7},
    [DEBUG_MENU_ITEM_SCRIPT_8] = {sDebugText_Script_8, DEBUG_MENU_ITEM_SCRIPT_8},
};
static const struct ListMenuItem sDebugMenu_Items_FlagsVars[] =
{
    [DEBUG_MENU_ITEM_FLAGVAR_FLAGS]                = {sDebugText_FlagsVars_Flags,              DEBUG_MENU_ITEM_FLAGVAR_FLAGS},
    [DEBUG_MENU_ITEM_FLAGVAR_VARS]                 = {sDebugText_FlagsVars_Vars,               DEBUG_MENU_ITEM_FLAGVAR_VARS},
    [DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_ALL]         = {sDebugText_FlagsVars_PokedexFlags_All,   DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_ALL},
    [DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_RESET]       = {sDebugText_FlagsVars_PokedexFlags_Reset, DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_RESET},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKEDEX]       = {sDebugText_FlagsVars_SwitchDex,          DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKEDEX},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_NATDEX]        = {sDebugText_FlagsVars_SwitchNationalDex,  DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_NATDEX},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKENAV]       = {sDebugText_FlagsVars_SwitchPokeNav,      DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKENAV},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_RUN_SHOES]     = {sDebugText_FlagsVars_RunningShoes,       DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_RUN_SHOES},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_LOCATIONS]     = {sDebugText_FlagsVars_ToggleFlyFlags,     DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_LOCATIONS},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BADGES_ALL]    = {sDebugText_FlagsVars_ToggleAllBadges,    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BADGES_ALL},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_FRONTIER_PASS] = {sDebugText_FlagsVars_ToggleFrontierPass, DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_FRONTIER_PASS},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_GAME_CLEAR]    = {sDebugText_FlagsVars_ToggleGameClear,    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_GAME_CLEAR},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BATTLE_DMG]    = {sDebugText_FlagsVars_BattleDmg,          DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BATTLE_DMG},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_COLLISION]     = {sDebugText_FlagsVars_SwitchCollision,    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_COLLISION},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_ENCOUNTER]     = {sDebugText_FlagsVars_SwitchEncounter,    DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_ENCOUNTER},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_TRAINER_SEE]   = {sDebugText_FlagsVars_SwitchTrainerSee,   DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_TRAINER_SEE},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BAG_USE]       = {sDebugText_FlagsVars_SwitchBagUse,       DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BAG_USE},
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_CATCHING]      = {sDebugText_FlagsVars_SwitchCatching,     DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_CATCHING},
};
static const struct ListMenuItem sDebugMenu_Items_Battle[] =
{
    [DEBUG_MENU_ITEM_BATTLE_START_WILD]        = {sDebugText_Battle_Start_Wild,      DEBUG_MENU_ITEM_BATTLE_START_WILD},
    [DEBUG_MENU_ITEM_BATTLE_START_SINGLE]      = {sDebugText_Battle_Start_Single,    DEBUG_MENU_ITEM_BATTLE_START_SINGLE},
    [DEBUG_MENU_ITEM_BATTLE_START_DOUBLE]      = {sDebugText_Battle_Start_Double,    DEBUG_MENU_ITEM_BATTLE_START_DOUBLE},
    [DEBUG_MENU_ITEM_BATTLE_START_PARTNER]     = {sDebugText_Battle_Start_Partner,   DEBUG_MENU_ITEM_BATTLE_START_PARTNER},
    [DEBUG_MENU_ITEM_BATTLE_ENEMY_PARTY]       = {sDebugText_Battle_EnemyParty,      DEBUG_MENU_ITEM_BATTLE_ENEMY_PARTY},
    [DEBUG_MENU_ITEM_BATTLE_HEAL_ENEMY_PARTY]  = {sDebugText_Battle_HealEnemyParty,  DEBUG_MENU_ITEM_BATTLE_HEAL_ENEMY_PARTY},
    [DEBUG_MENU_ITEM_BATTLE_CLEAR_ENEMY_PARTY] = {sDebugText_Battle_ClearEnemyParty, DEBUG_MENU_ITEM_BATTLE_CLEAR_ENEMY_PARTY},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS]          = {sDebugText_Battle_AIFlags,         DEBUG_MENU_ITEM_BATTLE_AI_FLAGS},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN]           = {sDebugText_Battle_Terrain,         DEBUG_MENU_ITEM_BATTLE_TERRAIN},
};
static const struct ListMenuItem sDebugMenu_Items_Battle_AIFlags[] =
{
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_00] = {sDebugText_Battle_AIFlag_00, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_00},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_01] = {sDebugText_Battle_AIFlag_01, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_01},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_02] = {sDebugText_Battle_AIFlag_02, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_02},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_03] = {sDebugText_Battle_AIFlag_03, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_03},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_04] = {sDebugText_Battle_AIFlag_04, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_04},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_05] = {sDebugText_Battle_AIFlag_05, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_05},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_06] = {sDebugText_Battle_AIFlag_06, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_06},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_07] = {sDebugText_Battle_AIFlag_07, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_07},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_08] = {sDebugText_Battle_AIFlag_08, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_08},
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_09] = {sDebugText_Battle_AIFlag_09, DEBUG_MENU_ITEM_BATTLE_AI_FLAGS_09},
};
static const struct ListMenuItem sDebugMenu_Items_Battle_Terrain[] =
{
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_0] = {sDebugText_Battle_Terrain_0, DEBUG_MENU_ITEM_BATTLE_TERRAIN_0},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_1] = {sDebugText_Battle_Terrain_1, DEBUG_MENU_ITEM_BATTLE_TERRAIN_1},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_2] = {sDebugText_Battle_Terrain_2, DEBUG_MENU_ITEM_BATTLE_TERRAIN_2},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_3] = {sDebugText_Battle_Terrain_3, DEBUG_MENU_ITEM_BATTLE_TERRAIN_3},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_4] = {sDebugText_Battle_Terrain_4, DEBUG_MENU_ITEM_BATTLE_TERRAIN_4},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_5] = {sDebugText_Battle_Terrain_5, DEBUG_MENU_ITEM_BATTLE_TERRAIN_5},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_6] = {sDebugText_Battle_Terrain_6, DEBUG_MENU_ITEM_BATTLE_TERRAIN_6},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_7] = {sDebugText_Battle_Terrain_7, DEBUG_MENU_ITEM_BATTLE_TERRAIN_7},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_8] = {sDebugText_Battle_Terrain_8, DEBUG_MENU_ITEM_BATTLE_TERRAIN_8},
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN_9] = {sDebugText_Battle_Terrain_9, DEBUG_MENU_ITEM_BATTLE_TERRAIN_9},
};
static const struct ListMenuItem sDebugMenu_Items_Bag[] =
{
    [DEBUG_MENU_ITEM_BAG_GIVE_ITEM]          = {sDebugText_Bag_Give_Item,          DEBUG_MENU_ITEM_BAG_GIVE_ITEM},
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_TMS]       = {sDebugText_Bag_Give_All_TMs,       DEBUG_MENU_ITEM_BAG_GIVE_ALL_TMS},
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_HMS]       = {sDebugText_Bag_Give_All_HMs,       DEBUG_MENU_ITEM_BAG_GIVE_ALL_HMS},
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_ITEMS]     = {sDebugText_Bag_Give_All_Items,     DEBUG_MENU_ITEM_BAG_GIVE_ALL_ITEMS},
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_BALLS]     = {sDebugText_Bag_Give_All_PokeBalls, DEBUG_MENU_ITEM_BAG_GIVE_ALL_BALLS},
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_BERRIES]   = {sDebugText_Bag_Give_All_Berries,   DEBUG_MENU_ITEM_BAG_GIVE_ALL_BERRIES},
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_KEY_ITEMS] = {sDebugText_Bag_Give_All_KeyItems,  DEBUG_MENU_ITEM_BAG_GIVE_ALL_KEY_ITEMS},
    [DEBUG_MENU_ITEM_BAG_MAX_MONEY]          = {sDebugText_Bag_Give_MaxMoney,      DEBUG_MENU_ITEM_BAG_MAX_MONEY},
    [DEBUG_MENU_ITEM_BAG_MAX_COINS]          = {sDebugText_Bag_Give_MaxCoins,      DEBUG_MENU_ITEM_BAG_MAX_COINS},
    [DEBUG_MENU_ITEM_BAG_MAX_BATTLE_POINTS]  = {sDebugText_Bag_Give_BattlePoints,  DEBUG_MENU_ITEM_BAG_MAX_BATTLE_POINTS},
    [DEBUG_MENU_ITEM_BAG_CLEAR]              = {sDebugText_Bag_Clear,              DEBUG_MENU_ITEM_BAG_CLEAR},
};
static const struct ListMenuItem sDebugMenu_Items_Party[] =
{
    [DEBUG_MENU_ITEM_PARTY_HEAL_PARTY]             = {sDebugText_Party_HealParty,          DEBUG_MENU_ITEM_PARTY_HEAL_PARTY},
    [DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_SIMPLE]    = {sDebugText_Party_GivePokemonSimple,  DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_SIMPLE},
    [DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_COMPLEX]   = {sDebugText_Party_GivePokemonComplex, DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_COMPLEX},
    [DEBUG_MENU_ITEM_PARTY_CLEAR_PARTY]            = {sDebugText_Party_ClearParty,         DEBUG_MENU_ITEM_PARTY_CLEAR_PARTY},
    [DEBUG_MENU_ITEM_PARTY_TRIGGER_DAYCARE_EGG]    = {sDebugText_Party_DaycareEgg,         DEBUG_MENU_ITEM_PARTY_TRIGGER_DAYCARE_EGG},
    [DEBUG_MENU_ITEM_PARTY_HATCH_EGG]              = {sDebugText_Party_HatchAnEgg,         DEBUG_MENU_ITEM_PARTY_HATCH_EGG},
    [DEBUG_MENU_ITEM_PARTY_MOVE_REMINDER]          = {sDebugText_Party_MoveReminder,       DEBUG_MENU_ITEM_PARTY_MOVE_REMINDER},
};
static const struct ListMenuItem sDebugMenu_Items_PkmCreator[] =
{
    [DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_ADD]              = {sDebugText_PkmCreator_Party_Add,              DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_ADD},
    [DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT]             = {sDebugText_PkmCreator_Party_Edit,             DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT},
    [DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT_DRAFT]       = {sDebugText_PkmCreator_Party_Edit_Draft,       DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT_DRAFT},
    [DEBUG_MENU_ITEM_PKM_CREATOR_PC_EDIT]                = {sDebugText_PkmCreator_PC_Edit,                DEBUG_MENU_ITEM_PKM_CREATOR_PC_EDIT},
    [DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_ADD]        = {sDebugText_PkmCreator_Enemy_Party_Add,        DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_ADD},
    [DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT]       = {sDebugText_PkmCreator_Enemy_Party_Edit,       DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT},
    [DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT_DRAFT] = {sDebugText_PkmCreator_Enemy_Party_Edit_Draft, DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT_DRAFT},
    [DEBUG_MENU_ITEM_PKM_CREATOR_TESTING]                = {sDebugText_PkmCreator_Testing,                DEBUG_MENU_ITEM_PKM_CREATOR_TESTING},
    [DEBUG_MENU_ITEM_PKM_CREATOR_TESTING_COPY]           = {sDebugText_PkmCreator_Testing_Copy,           DEBUG_MENU_ITEM_PKM_CREATOR_TESTING_COPY},
};
static const struct ListMenuItem sDebugMenu_Items_PC[] =
{
    [DEBUG_MENU_ITEM_PC_ACCESS]             = {sDebugText_PC_Access,           DEBUG_MENU_ITEM_PC_ACCESS},
    [DEBUG_MENU_ITEM_PC_FILL_BOXES_SAME]    = {sDebugText_PC_FillBoxesSame,    DEBUG_MENU_ITEM_PC_FILL_BOXES_SAME},
    [DEBUG_MENU_ITEM_PC_FILL_BOXES_DIVERSE] = {sDebugText_PC_FillBoxesDiverse, DEBUG_MENU_ITEM_PC_FILL_BOXES_DIVERSE},
    [DEBUG_MENU_ITEM_PC_FILL_ITEMS]         = {sDebugText_PC_FillItemStorage,  DEBUG_MENU_ITEM_PC_FILL_ITEMS},
    [DEBUG_MENU_ITEM_PC_CLEAR]              = {sDebugText_PC_Clear,            DEBUG_MENU_ITEM_PC_CLEAR},

};
static const struct ListMenuItem sDebugMenu_Items_Sound[] =
{
    [DEBUG_MENU_ITEM_SOUND_SE]               = {sDebugText_Sound_SE,             DEBUG_MENU_ITEM_SOUND_SE},
    [DEBUG_MENU_ITEM_SOUND_MUSIC]            = {sDebugText_Sound_Music,          DEBUG_MENU_ITEM_SOUND_MUSIC},
    [DEBUG_MENU_ITEM_SOUND_TOGGLE_MAP_MUSIC] = {sDebugText_Sound_ToggleMapMusic, DEBUG_MENU_ITEM_SOUND_TOGGLE_MAP_MUSIC},
};

// *******************************
// Menu Actions
static void (*const sDebugMenu_Actions_Main[])(u8) =
{
    [DEBUG_MENU_ITEM_UTILITIES]       = DebugAction_OpenUtilitiesMenu,
    [DEBUG_MENU_ITEM_PARTY]           = DebugAction_OpenPartyMenu,
    [DEBUG_MENU_ITEM_BAG]             = DebugAction_OpenBagMenu,
    [DEBUG_MENU_ITEM_FLAGVAR]         = DebugAction_OpenFlagsVarsMenu,
    [DEBUG_MENU_ITEM_BATTLE]          = DebugAction_OpenBattleMenu,
    [DEBUG_MENU_ITEM_PC]              = DebugAction_OpenPCMenu,
    [DEBUG_MENU_ITEM_POKEMON_CREATOR] = DebugAction_OpenPokemonCreator,
    [DEBUG_MENU_ITEM_SOUND]           = DebugAction_OpenSoundMenu,
    [DEBUG_MENU_ITEM_SCRIPTS]         = DebugAction_OpenScriptsMenu,
};
static void (*const sDebugMenu_Actions_Utilities[])(u8) =
{
    [DEBUG_MENU_ITEM_UTIL_FLY]               = DebugAction_Util_Fly,
    [DEBUG_MENU_ITEM_UTIL_WARP]              = DebugAction_Util_Warp,
    [DEBUG_MENU_ITEM_UTIL_TRAINER_FUNCTIONS] = DebugAction_Util_TrainerFunctions,
    [DEBUG_MENU_ITEM_UTIL_CHECKWALLCLOCK]    = DebugAction_Util_CheckWallClock,
    [DEBUG_MENU_ITEM_UTIL_BERRY_FUNCTIONS]   = DebugAction_Util_BerryFunctions,
    [DEBUG_MENU_ITEM_UTIL_WEATHER]           = DebugAction_Util_Weather,
    [DEBUG_MENU_ITEM_UTIL_SAVEBLOCK]         = DebugAction_Util_CheckSaveBlock,
    [DEBUG_MENU_ITEM_UTIL_SETWALLCLOCK]      = DebugAction_Util_SetWallClock,
    [DEBUG_MENU_ITEM_UTIL_CHEAT]             = DebugAction_Util_CheatStart,
    [DEBUG_MENU_ITEM_UTIL_WATCHCREDITS]      = DebugAction_Util_WatchCredits,
};
static void (*const sDebugMenu_Actions_TrainerFunctions[])(u8) =
{
    [DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_NAME]   = DebugAction_TrainerFunctions_Name,
    [DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_GENDER] = DebugAction_TrainerFunctions_Gender,
    [DEBUG_MENU_ITEM_TRAINER_FUNCTIONS_ID]     = DebugAction_TrainerFunctions_Id,
};
static void (*const sDebugMenu_Actions_BerryFunctions[])(u8) =
{
    [DEBUG_MENU_ITEM_BERRY_FUNCTIONS_CLEAR_ALL]  = DebugAction_BerryFunctions_ClearAll,
    [DEBUG_MENU_ITEM_BERRY_FUNCTIONS_READY]      = DebugAction_BerryFunctions_Ready,
    [DEBUG_MENU_ITEM_BERRY_FUNCTIONS_NEXT_STAGE] = DebugAction_BerryFunctions_NextStage,
};
static void (*const sDebugMenu_Actions_Scripts[])(u8) =
{
    [DEBUG_MENU_ITEM_SCRIPT_1] = DebugAction_Script_1,
    [DEBUG_MENU_ITEM_SCRIPT_2] = DebugAction_Script_2,
    [DEBUG_MENU_ITEM_SCRIPT_3] = DebugAction_Script_3,
    [DEBUG_MENU_ITEM_SCRIPT_4] = DebugAction_Script_4,
    [DEBUG_MENU_ITEM_SCRIPT_5] = DebugAction_Script_5,
    [DEBUG_MENU_ITEM_SCRIPT_6] = DebugAction_Script_6,
    [DEBUG_MENU_ITEM_SCRIPT_7] = DebugAction_Script_7,
    [DEBUG_MENU_ITEM_SCRIPT_8] = DebugAction_Script_8,
};
static void (*const sDebugMenu_Actions_Flags[])(u8) =
{
    [DEBUG_MENU_ITEM_FLAGVAR_FLAGS]                = DebugAction_FlagsVars_Flags,
    [DEBUG_MENU_ITEM_FLAGVAR_VARS]                 = DebugAction_FlagsVars_Vars,
    [DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_ALL]         = DebugAction_FlagsVars_PokedexFlags_All,
    [DEBUG_MENU_ITEM_FLAGVAR_DEXFLAGS_RESET]       = DebugAction_FlagsVars_PokedexFlags_Reset,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKEDEX]       = DebugAction_FlagsVars_SwitchDex,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_NATDEX]        = DebugAction_FlagsVars_SwitchNatDex,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKENAV]       = DebugAction_FlagsVars_SwitchPokeNav,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_RUN_SHOES]     = DebugAction_FlagsVars_RunningShoes,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_LOCATIONS]     = DebugAction_FlagsVars_ToggleFlyFlags,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BADGES_ALL]    = DebugAction_FlagsVars_ToggleBadgeFlags,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_FRONTIER_PASS] = DebugAction_FlagsVars_ToggleFrontierPass,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_GAME_CLEAR]    = DebugAction_FlagsVars_ToggleGameClear,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BATTLE_DMG]    = DebugAction_FlagsVars_BattleDmgOnOff,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_COLLISION]     = DebugAction_FlagsVars_CollisionOnOff,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_ENCOUNTER]     = DebugAction_FlagsVars_EncounterOnOff,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_TRAINER_SEE]   = DebugAction_FlagsVars_TrainerSeeOnOff,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BAG_USE]       = DebugAction_FlagsVars_BagUseOnOff,
    [DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_CATCHING]      = DebugAction_FlagsVars_CatchingOnOff,
};
static void (*const sDebugMenu_Actions_Bag[])(u8) =
{
    [DEBUG_MENU_ITEM_BAG_GIVE_ITEM]          = DebugAction_Bag_Give_Item,
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_TMS]       = DebugAction_Bag_Give_All_TMs,
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_HMS]       = DebugAction_Bag_Give_All_HMs,
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_ITEMS]     = DebugAction_Bag_Give_All_Items,
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_BALLS]     = DebugAction_Bag_Give_All_PokeBalls,
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_BERRIES]   = DebugAction_Bag_Give_All_Berries,
    [DEBUG_MENU_ITEM_BAG_GIVE_ALL_KEY_ITEMS] = DebugAction_Bag_Give_All_KeyItems,
    [DEBUG_MENU_ITEM_BAG_MAX_MONEY]          = DebugAction_Bag_MaxMoney,
    [DEBUG_MENU_ITEM_BAG_MAX_COINS]          = DebugAction_Bag_MaxCoins,
    [DEBUG_MENU_ITEM_BAG_MAX_BATTLE_POINTS]  = DebugAction_Bag_MaxBattlePoints,
    [DEBUG_MENU_ITEM_BAG_CLEAR]              = DebugAction_Bag_Clear,
};
static void (*const sDebugMenu_Actions_Party[])(u8) =
{
    [DEBUG_MENU_ITEM_PARTY_HEAL_PARTY]           = DebugAction_Party_HealParty,
    [DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_SIMPLE]  = DebugAction_Party_GivePokemonSimple,
    [DEBUG_MENU_ITEM_PARTY_GIVE_POKEMON_COMPLEX] = DebugAction_Party_GivePokemonComplex,
    [DEBUG_MENU_ITEM_PARTY_CLEAR_PARTY]          = DebugAction_Party_ClearParty,
    [DEBUG_MENU_ITEM_PARTY_TRIGGER_DAYCARE_EGG]  = DebugAction_Party_TriggerDaycareEgg,
    [DEBUG_MENU_ITEM_PARTY_HATCH_EGG]            = DebugAction_Party_HatchAnEgg,
    [DEBUG_MENU_ITEM_PARTY_MOVE_REMINDER]        = DebugAction_Party_MoveReminder,
};
static void (*const sDebugMenu_Actions_PkmCreator[])(u8) =
{
    [DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_ADD]              = DebugAction_PkmCreator_Party_Add,
    [DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT]             = DebugAction_PkmCreator_Party_Edit,
    [DEBUG_MENU_ITEM_PKM_CREATOR_PARTY_EDIT_DRAFT]       = DebugAction_PkmCreator_Party_Edit_Draft,
    [DEBUG_MENU_ITEM_PKM_CREATOR_PC_EDIT]                = DebugAction_PkmCreator_PC_Edit,
    [DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_ADD]        = DebugAction_PkmCreator_Enemy_Party_Add,
    [DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT]       = DebugAction_PkmCreator_Enemy_Party_Edit,
    [DEBUG_MENU_ITEM_PKM_CREATOR_ENEMY_PARTY_EDIT_DRAFT] = DebugAction_PkmCreator_Enemy_Party_Edit_Draft,
    [DEBUG_MENU_ITEM_PKM_CREATOR_TESTING]                = DebugAction_PkmCreator_Testing,
    [DEBUG_MENU_ITEM_PKM_CREATOR_TESTING_COPY]           = DebugAction_PkmCreator_Testing_Copy,
};
static void (*const sDebugMenu_Actions_PC[])(u8) =
{
    [DEBUG_MENU_ITEM_PC_ACCESS]             = DebugAction_PC_Access,
    [DEBUG_MENU_ITEM_PC_FILL_BOXES_SAME]    = DebugAction_PC_FillBoxesSame,
    [DEBUG_MENU_ITEM_PC_FILL_BOXES_DIVERSE] = DebugAction_PC_FillBoxesDiverse,
    [DEBUG_MENU_ITEM_PC_FILL_ITEMS]         = DebugAction_PC_FillItemStorage,
    [DEBUG_MENU_ITEM_PC_CLEAR]              = DebugAction_PC_Clear,
};
static void (*const sDebugMenu_Actions_Sound[])(u8) =
{
    [DEBUG_MENU_ITEM_SOUND_SE]               = DebugAction_Sound_SE,
    [DEBUG_MENU_ITEM_SOUND_MUSIC]            = DebugAction_Sound_Music,
    [DEBUG_MENU_ITEM_SOUND_TOGGLE_MAP_MUSIC] = DebugAction_Sound_ToggleMapMusic,
};
static void (*const sDebugMenu_Actions_Battle[])(u8) =
{
    [DEBUG_MENU_ITEM_BATTLE_START_WILD]        = DebugAction_Battle_InitializeWildBattle,
    [DEBUG_MENU_ITEM_BATTLE_START_SINGLE]      = DebugAction_Battle_InitializeSingleBattle,
    [DEBUG_MENU_ITEM_BATTLE_START_DOUBLE]      = DebugAction_Battle_InitializeDoubleBattle,
    [DEBUG_MENU_ITEM_BATTLE_START_PARTNER]     = DebugAction_Battle_InitializePartnerBattle,
    [DEBUG_MENU_ITEM_BATTLE_ENEMY_PARTY]       = DebugAction_Battle_OpenEnemyPartyMenu,
    [DEBUG_MENU_ITEM_BATTLE_HEAL_ENEMY_PARTY]  = DebugAction_Battle_HealEnemyPartyMenu,
    [DEBUG_MENU_ITEM_BATTLE_CLEAR_ENEMY_PARTY] = DebugAction_Battle_ClearEnemyPartyMenu,
    [DEBUG_MENU_ITEM_BATTLE_AI_FLAGS]          = DebugAction_Battle_OpenAIFlagsMenu,
    [DEBUG_MENU_ITEM_BATTLE_TERRAIN]           = DebugAction_Battle_OpenTerrainMenu,
};


// *******************************
// Windows
static const struct WindowTemplate sDebugMenuWindowTemplateMain =
{
    .bg = 0,
    .tilemapLeft = 1,
    .tilemapTop = 1,
    .width = DEBUG_MENU_WIDTH_MAIN,
    .height = 2 * DEBUG_MENU_HEIGHT_MAIN,
    .paletteNum = 15,
    .baseBlock = 1,
};
static const struct WindowTemplate sDebugMenuWindowTemplateExtra =
{
    .bg = 0,
    .tilemapLeft = 30 - DEBUG_MENU_WIDTH_EXTRA - 1,
    .tilemapTop = 1,
    .width = DEBUG_MENU_WIDTH_EXTRA,
    .height = 2 * DEBUG_MENU_HEIGHT_EXTRA,
    .paletteNum = 15,
    .baseBlock = 1,
};
static const struct WindowTemplate sDebugMenuWindowTemplateWeather =
{
    .bg = 0,
    .tilemapLeft = 30 - DEBUG_MENU_WIDTH_WEATHER - 1,
    .tilemapTop = 1,
    .width = DEBUG_MENU_WIDTH_WEATHER,
    .height = 2 * DEBUG_MENU_HEIGHT_WEATHER,
    .paletteNum = 15,
    .baseBlock = 1,
};
static const struct WindowTemplate sDebugMenuWindowTemplateSound =
{
    .bg = 0,
    .tilemapLeft = 30 - DEBUG_MENU_WIDTH_SOUND - 1,
    .tilemapTop = 1,
    .width = DEBUG_MENU_WIDTH_SOUND,
    .height = DEBUG_MENU_HEIGHT_SOUND,
    .paletteNum = 15,
    .baseBlock = 1,
};
static const struct WindowTemplate sDebugMenuWindowTemplateFlagsVars =
{
    .bg = 0,
    .tilemapLeft = 30 - DEBUG_MENU_WIDTH_FLAGVAR - 1,
    .tilemapTop = 1,
    .width = DEBUG_MENU_WIDTH_FLAGVAR,
    .height = DEBUG_MENU_HEIGHT_FLAGVAR,
    .paletteNum = 15,
    .baseBlock = 1 + DEBUG_MENU_WIDTH_MAIN * DEBUG_MENU_HEIGHT_MAIN * 2,
};

// *******************************
// List Menu Templates
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Main =
{
    .items = sDebugMenu_Items_Main,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Main),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Utilities =
{
    .items = sDebugMenu_Items_Utilities,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Utilities),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_TrainerFunctions =
{
    .items = sDebugMenu_Items_TrainerFunctions,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_TrainerFunctions),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_BerryFunctions =
{
    .items = sDebugMenu_Items_BerryFunctions,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_BerryFunctions),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Scripts =
{
    .items = sDebugMenu_Items_Scripts,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Scripts),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_FlagsVars =
{
    .items = sDebugMenu_Items_FlagsVars,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_FlagsVars),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Battle =
{
    .items = sDebugMenu_Items_Battle,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Battle),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Bag =
{
    .items = sDebugMenu_Items_Bag,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Bag),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Battle_AIFlags =
{
    .items = sDebugMenu_Items_Battle_AIFlags,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Battle_AIFlags),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Battle_EnemyParty =
{
    .items = NULL,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = PARTY_SIZE,
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Battle_Terrain =
{
    .items = sDebugMenu_Items_Battle_Terrain,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Battle_Terrain),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Party =
{
    .items = sDebugMenu_Items_Party,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Party),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_PkmCreator =
{
    .items = sDebugMenu_Items_PkmCreator,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_PkmCreator),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_PC =
{
    .items = sDebugMenu_Items_PC,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_PC),
};
static const struct ListMenuTemplate sDebugMenu_ListTemplate_Sound =
{
    .items = sDebugMenu_Items_Sound,
    .moveCursorFunc = ListMenuDefaultCursorMoveFunc,
    .totalItems = ARRAY_COUNT(sDebugMenu_Items_Sound),
};

#define tMenuTaskId   data[0]
#define tWindowId     data[1]
#define tSubWindowId  data[2]
#define tInput        data[3]
#define tDigit        data[4]

// *******************************
// General functions
static u8 Debug_ShowMenu(void (*HandleInput)(u8), struct ListMenuTemplate menuTemplate)
{
    u8 windowId;
    u8 menuTaskId;
    u8 inputTaskId;

    // create window
    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateMain);
    DrawStdWindowFrame(windowId, FALSE);

    // create list menu
    menuTemplate.maxShowed = DEBUG_MENU_HEIGHT_MAIN;
    menuTemplate.windowId = windowId;
    menuTemplate.header_X = 0;
    menuTemplate.item_X = 8;
    menuTemplate.cursor_X = 0;
    menuTemplate.upText_Y = 1;
    menuTemplate.cursorPal = 2;
    menuTemplate.fillValue = 1;
    menuTemplate.cursorShadowPal = 3;
    menuTemplate.lettersSpacing = 1;
    menuTemplate.itemVerticalPadding = 0;
    menuTemplate.scrollMultiple = LIST_NO_MULTIPLE_SCROLL;
    menuTemplate.fontId = DEBUG_MENU_FONT;
    menuTemplate.cursorKind = 0;
    menuTaskId = ListMenuInit(&menuTemplate, 0, 0);

    // create input handler task
    inputTaskId = CreateTask(HandleInput, 3);
    gTasks[inputTaskId].tMenuTaskId = menuTaskId;
    gTasks[inputTaskId].tWindowId = windowId;
    gTasks[inputTaskId].tSubWindowId = 0;

    // draw everything
    CopyWindowToVram(windowId, COPYWIN_FULL);

    // return taskId for use right after
    return inputTaskId;
}

static void Debug_DestroyMenu(u8 taskId)
{
    DestroyListMenuTask(gTasks[taskId].tMenuTaskId, NULL, NULL);
    RemoveWindow(gTasks[taskId].tWindowId);
    DestroyTask(taskId);
}

static void Debug_DestroyMenu_Full(u8 taskId)
{
    if (gTasks[taskId].tSubWindowId != 0)
    {
        ClearStdWindowAndFrame(gTasks[taskId].tSubWindowId, FALSE);
        DebugAction_DestroyExtraWindow(taskId);
    }
    DestroyListMenuTask(gTasks[taskId].tMenuTaskId, NULL, NULL);
    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);
    DestroyTask(taskId);
    UnfreezeObjectEvents();
    Free(sDebugMenuListData);
}

static void Debug_DestroyMenu_Full_Script(u8 taskId, const u8 *script)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    FreezeObjectEvents();
    ScriptContext_SetupScript(script);
}

static void Debug_HandleInput_Numeric(u8 taskId, s32 min, s32 max, u32 digits)
{
    if (JOY_NEW(DPAD_UP))
    {
        gTasks[taskId].tInput += sPowersOfTen[gTasks[taskId].tDigit];
        if (gTasks[taskId].tInput > max)
            gTasks[taskId].tInput = max;
    }
    if (JOY_NEW(DPAD_DOWN))
    {
        gTasks[taskId].tInput -= sPowersOfTen[gTasks[taskId].tDigit];
        if (gTasks[taskId].tInput < min)
            gTasks[taskId].tInput = min;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        if (gTasks[taskId].tDigit > 0)
            gTasks[taskId].tDigit -= 1;
    }
    if (JOY_NEW(DPAD_RIGHT))
    {
        if (gTasks[taskId].tDigit < digits - 1)
            gTasks[taskId].tDigit += 1;
    }
}

static void DebugAction_DestroyExtraWindow(u8 taskId)
{
    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    ClearStdWindowAndFrame(gTasks[taskId].tSubWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tSubWindowId);

    DestroyListMenuTask(gTasks[taskId].tMenuTaskId, NULL, NULL);
    DestroyTask(taskId);
    ScriptContext_Enable();
    UnfreezeObjectEvents();
}

static void DebugTask_HandleMenuInput_General(u8 taskId, void (*const actions[])(u8), void (*callbackInput)(u8), struct ListMenuTemplate callbackMenuTemplate)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuTaskId);

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if ((func = actions[input]) != NULL)
            func(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMenu(callbackInput, callbackMenuTemplate);
    }
}

// *******************************
// Main menu functions
void Debug_ShowMainMenu(void)
{
    sDebugMenuListData = AllocZeroed(sizeof(*sDebugMenuListData));

    Debug_ShowMenu(DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void Debug_ReShowMainMenu(void)
{
    Debug_ShowMenu(DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugAction_OpenUtilitiesMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_Utilities, sDebugMenu_ListTemplate_Utilities);
}

static void DebugAction_OpenScriptsMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_Scripts, sDebugMenu_ListTemplate_Scripts);
}

static void DebugAction_OpenFlagsVarsMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);

    gMultiuseListMenuTemplate = sDebugMenu_ListTemplate_FlagsVars;
    Debug_RefreshFlagsVarsListItems();
    gMultiuseListMenuTemplate.items = sDebugMenuListData->listItems;

    Debug_ShowMenu(DebugTask_HandleMenuInput_FlagsVars, gMultiuseListMenuTemplate);
}

static void DebugAction_OpenBattleMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_Battle, sDebugMenu_ListTemplate_Battle);
}

static void DebugAction_OpenBagMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_Bag, sDebugMenu_ListTemplate_Bag);
}

static void DebugAction_OpenPartyMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_Party, sDebugMenu_ListTemplate_Party);
}

static void DebugAction_OpenPokemonCreator(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_PkmCreator, sDebugMenu_ListTemplate_PkmCreator);
}

static void DebugAction_OpenPCMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_PC, sDebugMenu_ListTemplate_PC);
}

static void DebugAction_OpenSoundMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_Sound, sDebugMenu_ListTemplate_Sound);
}

static void DebugTask_HandleMenuInput_Main(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuTaskId);

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenu_Actions_Main[input]) != NULL)
            func(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu_Full(taskId);
        ScriptContext_Enable();
    }
}

static void DebugTask_HandleMenuInput_Utilities(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_Utilities, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugTask_HandleMenuInput_Scripts(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_Scripts, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugTask_HandleMenuInput_FlagsVars(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuTaskId);

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if ((func = sDebugMenu_Actions_Flags[input]) != NULL)
        {
            if (input == DEBUG_MENU_ITEM_FLAGVAR_FLAGS || input == DEBUG_MENU_ITEM_FLAGVAR_VARS)
            {
                func(taskId);
            }
            else
            {
                func(taskId);
                Debug_RedrawFlagsVarsMenu(taskId);
            }
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ReShowMainMenu();
    }
}

static void DebugTask_HandleMenuInput_Battle(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_Battle, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugTask_HandleMenuInput_Bag(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_Bag, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugTask_HandleMenuInput_Party(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_Party, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugTask_HandleMenuInput_PkmCreator(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_PkmCreator, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugTask_HandleMenuInput_PC(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_PC, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

static void DebugTask_HandleMenuInput_Sound(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_Sound, DebugTask_HandleMenuInput_Main, sDebugMenu_ListTemplate_Main);
}

// *******************************
// Utilities menu functions
static void DebugAction_Util_Fly(u8 taskId)
{
    FlagSet(FLAG_VISITED_LITTLEROOT_TOWN);
    FlagSet(FLAG_VISITED_OLDALE_TOWN);
    FlagSet(FLAG_VISITED_DEWFORD_TOWN);
    FlagSet(FLAG_VISITED_LAVARIDGE_TOWN);
    FlagSet(FLAG_VISITED_FALLARBOR_TOWN);
    FlagSet(FLAG_VISITED_VERDANTURF_TOWN);
    FlagSet(FLAG_VISITED_PACIFIDLOG_TOWN);
    FlagSet(FLAG_VISITED_PETALBURG_CITY);
    FlagSet(FLAG_VISITED_SLATEPORT_CITY);
    FlagSet(FLAG_VISITED_MAUVILLE_CITY);
    FlagSet(FLAG_VISITED_RUSTBORO_CITY);
    FlagSet(FLAG_VISITED_FORTREE_CITY);
    FlagSet(FLAG_VISITED_LILYCOVE_CITY);
    FlagSet(FLAG_VISITED_MOSSDEEP_CITY);
    FlagSet(FLAG_VISITED_SOOTOPOLIS_CITY);
    FlagSet(FLAG_VISITED_EVER_GRANDE_CITY);
    FlagSet(FLAG_LANDMARK_POKEMON_LEAGUE);
    FlagSet(FLAG_LANDMARK_BATTLE_FRONTIER);
    Debug_DestroyMenu_Full(taskId);
    SetMainCallback2(CB2_OpenFlyMap);
}

#define tMapGroup  data[5]
#define tMapNum    data[6]
#define tWarp      data[7]

#define LAST_MAP_GROUP (MAP_GROUPS_COUNT - 1)

static void DebugAction_Util_Warp(u8 taskId)
{
    u8 windowId;

    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateExtra);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, 3);
    ConvertIntToDecimalStringN(gStringVar2, LAST_MAP_GROUP, STR_CONV_MODE_LEADING_ZEROS, 3);
    StringExpandPlaceholders(gStringVar1, sDebugText_Util_WarpToMap_SelMax);
    StringCopy(gStringVar3, gText_DigitIndicator[0]);
    StringExpandPlaceholders(gStringVar4, sDebugText_Util_WarpToMap_SelectMapGroup);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);

    gTasks[taskId].func = DebugAction_Util_Warp_SelectMapGroup;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = 0;
    gTasks[taskId].tDigit = 0;
    gTasks[taskId].tMapGroup = 0;
    gTasks[taskId].tMapNum = 0;
    gTasks[taskId].tWarp = 0;
}

static void DebugAction_Util_Warp_SelectMapGroup(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 0, LAST_MAP_GROUP, 3);

        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, 3);
        ConvertIntToDecimalStringN(gStringVar2, LAST_MAP_GROUP, STR_CONV_MODE_LEADING_ZEROS, 3);
        StringExpandPlaceholders(gStringVar1, sDebugText_Util_WarpToMap_SelMax);
        StringCopy(gStringVar3, gText_DigitIndicator[gTasks[taskId].tDigit]);
        StringExpandPlaceholders(gStringVar4, sDebugText_Util_WarpToMap_SelectMapGroup);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        gTasks[taskId].tMapGroup = gTasks[taskId].tInput;
        gTasks[taskId].tInput = 0;
        gTasks[taskId].tDigit = 0;

        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, (MAP_GROUP_COUNT[gTasks[taskId].tMapGroup] - 1 >= 100) ? 3 : 2);
        ConvertIntToDecimalStringN(gStringVar2, MAP_GROUP_COUNT[gTasks[taskId].tMapGroup] - 1, STR_CONV_MODE_LEADING_ZEROS, (MAP_GROUP_COUNT[gTasks[taskId].tMapGroup] - 1 >= 100) ? 3 : 2);
        StringExpandPlaceholders(gStringVar1, sDebugText_Util_WarpToMap_SelMax);
        GetMapName(gStringVar2, Overworld_GetMapHeaderByGroupAndId(gTasks[taskId].tMapGroup, gTasks[taskId].tInput)->regionMapSectionId, 0);
        StringCopy(gStringVar3, gText_DigitIndicator[gTasks[taskId].tDigit]);
        StringExpandPlaceholders(gStringVar4, sDebugText_Util_WarpToMap_SelectMap);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);

        gTasks[taskId].func = DebugAction_Util_Warp_SelectMap;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void DebugAction_Util_Warp_SelectMap(u8 taskId)
{
    u8 max_value = MAP_GROUP_COUNT[gTasks[taskId].tMapGroup]; //maps in the selected map group

    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 0, max_value - 1, 3);

        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, (max_value >= 100) ? 3 : 2);
        ConvertIntToDecimalStringN(gStringVar2, MAP_GROUP_COUNT[gTasks[taskId].tMapGroup] - 1, STR_CONV_MODE_LEADING_ZEROS, (max_value >= 100) ? 3 : 2);
        StringExpandPlaceholders(gStringVar1, sDebugText_Util_WarpToMap_SelMax);
        GetMapName(gStringVar2, Overworld_GetMapHeaderByGroupAndId(gTasks[taskId].tMapGroup, gTasks[taskId].tInput)->regionMapSectionId, 0);
        StringCopy(gStringVar3, gText_DigitIndicator[gTasks[taskId].tDigit]);
        StringExpandPlaceholders(gStringVar4, sDebugText_Util_WarpToMap_SelectMap);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        gTasks[taskId].tMapNum = gTasks[taskId].tInput;
        gTasks[taskId].tInput = 0;
        gTasks[taskId].tDigit = 0;

        StringCopy(gStringVar3, gText_DigitIndicator[gTasks[taskId].tDigit]);
        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, 3);
        StringExpandPlaceholders(gStringVar4, sDebugText_Util_WarpToMap_SelectWarp);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
        gTasks[taskId].func = DebugAction_Util_Warp_SelectWarp;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void DebugAction_Util_Warp_SelectWarp(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        if (JOY_NEW(DPAD_UP))
        {
            gTasks[taskId].tInput += sPowersOfTen[gTasks[taskId].tDigit];
            if (gTasks[taskId].tInput > 10)
                gTasks[taskId].tInput = 10;
        }
        if (JOY_NEW(DPAD_DOWN))
        {
            gTasks[taskId].tInput -= sPowersOfTen[gTasks[taskId].tDigit];
            if (gTasks[taskId].tInput < 0)
                gTasks[taskId].tInput = 0;
        }

        StringCopy(gStringVar3, gText_DigitIndicator[gTasks[taskId].tDigit]);
        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, 3);
        StringExpandPlaceholders(gStringVar4, sDebugText_Util_WarpToMap_SelectWarp);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        gTasks[taskId].tWarp = gTasks[taskId].tInput;
        //If there's no warp with the number available, warp to the center of the map.
        SetWarpDestinationToMapWarp(gTasks[taskId].tMapGroup, gTasks[taskId].tMapNum, gTasks[taskId].tWarp);
        DoWarp();
        ResetInitialPlayerAvatarState();
        DebugAction_DestroyExtraWindow(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

#undef tMapGroup
#undef tMapNum
#undef tWarp

static void DebugAction_Util_CheckSaveBlock(u8 taskId)
{
    static const u8 sDebugText_SaveBlockSize[] =  _("SaveBlock1 is {STR_VAR_1} bytes long.\nMax size is 15872 bytes.\pSaveBlock2 is {STR_VAR_2} bytes long.\nMax size is 3968 bytes.\pPokemonStorage is {STR_VAR_3} bytes long.\nMax size is 35712 bytes.");

    ConvertIntToDecimalStringN(gStringVar1, sizeof(struct SaveBlock1), STR_CONV_MODE_LEFT_ALIGN, 6);
    ConvertIntToDecimalStringN(gStringVar2, sizeof(struct SaveBlock2), STR_CONV_MODE_LEFT_ALIGN, 6);
    ConvertIntToDecimalStringN(gStringVar3, sizeof(struct PokemonStorage), STR_CONV_MODE_LEFT_ALIGN, 6);
    StringExpandPlaceholders(gStringVar4, sDebugText_SaveBlockSize);

    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    ScriptContext_SetupScript(Debug_ShowFieldMessageStringVar4);
}

static const u8 sWeatherNames[WEATHER_COUNT][24] = {
    [WEATHER_NONE]               = _("NONE"),
    [WEATHER_SUNNY_CLOUDS]       = _("SUNNY CLOUDS"),
    [WEATHER_SUNNY]              = _("SUNNY"),
    [WEATHER_RAIN]               = _("RAIN"),
    [WEATHER_SNOW]               = _("SNOW"),
    [WEATHER_RAIN_THUNDERSTORM]  = _("RAIN THUNDERSTORM"),
    [WEATHER_FOG_HORIZONTAL]     = _("FOG HORIZONTAL"),
    [WEATHER_VOLCANIC_ASH]       = _("VOLCANIC ASH"),
    [WEATHER_SANDSTORM]          = _("SANDSTORM"),
    [WEATHER_FOG_DIAGONAL]       = _("FOG DIAGONAL"),
    [WEATHER_UNDERWATER]         = _("UNDERWATER"),
    [WEATHER_SHADE]              = _("SHADE"),
    [WEATHER_DROUGHT]            = _("DROUGHT"),
    [WEATHER_DOWNPOUR]           = _("DOWNPOUR"),
    [WEATHER_UNDERWATER_BUBBLES] = _("UNDERWATER BUBBLES"),
    [WEATHER_ABNORMAL]           = _("ABNORMAL(NOT WORKING)"),
    [WEATHER_ROUTE119_CYCLE]     = _("ROUTE119 CYCLE"),
    [WEATHER_ROUTE123_CYCLE]     = _("ROUTE123 CYCLE"),
};

static const u8 sDebugText_WeatherNotDefined[] = _("NOT DEFINED!!!");
static void DebugAction_Util_Weather(u8 taskId)
{
    u8 windowId;

    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateWeather);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    //Display initial ID
    StringCopy(gStringVar2, gText_DigitIndicator[0]);
    ConvertIntToDecimalStringN(gStringVar3, 1, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringCopyPadded(gStringVar1, sWeatherNames[0], CHAR_SPACE, 30);
    StringExpandPlaceholders(gStringVar4, sDebugText_Util_Weather_ID);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);

    gTasks[taskId].func = DebugAction_Util_Weather_SelectId;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = 0;
    gTasks[taskId].tDigit = 0;
}

static void DebugAction_Util_Weather_SelectId(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, WEATHER_NONE, WEATHER_COUNT - 1, 3);

        StringCopy(gStringVar2, gText_DigitIndicator[gTasks[taskId].tDigit]);
        ConvertIntToDecimalStringN(gStringVar3, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, 2);

        if (gTasks[taskId].tInput <= 15 || gTasks[taskId].tInput >= 20)
            StringCopyPadded(gStringVar1, sWeatherNames[gTasks[taskId].tInput], CHAR_SPACE, 30);
        else
            StringCopyPadded(gStringVar1, sDebugText_WeatherNotDefined, CHAR_SPACE, 30);

        StringExpandPlaceholders(gStringVar4, sDebugText_Util_Weather_ID);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        if (gTasks[taskId].tInput <= 14 || gTasks[taskId].tInput >= 20)
        {
            gTasks[taskId].data[5] = gTasks[taskId].tInput;
            SetWeather(gTasks[taskId].data[5]);
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void DebugAction_Util_CheckWallClock(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, PlayersHouse_2F_EventScript_CheckWallClock);
}

static void DebugAction_Util_SetWallClock(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, PlayersHouse_2F_EventScript_SetWallClock);
}

static void DebugAction_Util_WatchCredits(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    SetMainCallback2(CB2_StartCreditsSequence);
}

static void DebugAction_TrainerFunctions_Name(u8 taskId)
{
    DoNamingScreen(NAMING_SCREEN_PLAYER, gSaveBlock2Ptr->playerName, gSaveBlock2Ptr->playerGender, 0, 0, CB2_ReturnToFieldContinueScript);
}

static void DebugAction_TrainerFunctions_Gender(u8 taskId)
{
    if (gSaveBlock2Ptr->playerGender == MALE)
        gSaveBlock2Ptr->playerGender = FEMALE;
    else
        gSaveBlock2Ptr->playerGender = MALE;
    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();
}

static void DebugAction_TrainerFunctions_Id(u8 taskId)
{
    u32 trainerId = Random32();
    SetTrainerId(trainerId, gSaveBlock2Ptr->playerTrainerId);
    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();
}

static void DebugAction_Util_TrainerFunctions(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_TrainerFunctions, sDebugMenu_ListTemplate_TrainerFunctions);
}

static void DebugTask_HandleMenuInput_TrainerFunctions(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_TrainerFunctions, DebugTask_HandleMenuInput_Utilities, sDebugMenu_ListTemplate_Utilities);
}

static void DebugAction_Util_BerryFunctions(u8 taskId)
{
    Debug_DestroyMenu(taskId);
    Debug_ShowMenu(DebugTask_HandleMenuInput_BerryFunctions, sDebugMenu_ListTemplate_BerryFunctions);
}

static void DebugAction_Util_CheatStart(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_CheatStart);
}

static void DebugTask_HandleMenuInput_BerryFunctions(u8 taskId)
{
    DebugTask_HandleMenuInput_General(taskId, sDebugMenu_Actions_BerryFunctions, DebugTask_HandleMenuInput_Utilities, sDebugMenu_ListTemplate_Utilities);
}

static void DebugAction_BerryFunctions_ClearAll(u8 taskId)
{
    u8 i;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].movementType == MOVEMENT_TYPE_BERRY_TREE_GROWTH)
        {
            RemoveBerryTree(GetObjectEventBerryTreeId(i));
            SetBerryTreeJustPicked(gObjectEvents[i].localId, gSaveBlock1Ptr->location.mapNum, gSaveBlock1Ptr->location.mapGroup);
        }
    }

    ScriptContext_Enable();
    Debug_DestroyMenu_Full(taskId);
}

static void DebugAction_BerryFunctions_Ready(u8 taskId)
{
    u8 i;
    struct BerryTree *tree;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].movementType == MOVEMENT_TYPE_BERRY_TREE_GROWTH)
        {
            tree = &gSaveBlock1Ptr->berryTrees[GetObjectEventBerryTreeId(i)];
            if (tree->stage != BERRY_STAGE_NO_BERRY)
            {
                tree->stage = BERRY_STAGE_BERRIES - 1;
                BerryTreeGrow(tree);
            }
        }
    }

    ScriptContext_Enable();
    Debug_DestroyMenu_Full(taskId);
}

static void DebugAction_BerryFunctions_NextStage(u8 taskId)
{
    u8 i;
    struct BerryTree *tree;

    for (i = 0; i < OBJECT_EVENTS_COUNT; i++)
    {
        if (gObjectEvents[i].movementType == MOVEMENT_TYPE_BERRY_TREE_GROWTH)
        {
            tree = &gSaveBlock1Ptr->berryTrees[GetObjectEventBerryTreeId(i)];
            BerryTreeGrow(tree);
        }
    }

    ScriptContext_Enable();
    Debug_DestroyMenu_Full(taskId);
}

// *******************************
// Scripts menu functions
static void DebugAction_Script_1(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_1);
}

static void DebugAction_Script_2(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_2);
}

static void DebugAction_Script_3(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_3);
}

static void DebugAction_Script_4(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_4);
}

static void DebugAction_Script_5(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_5);
}

static void DebugAction_Script_6(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_6);
}

static void DebugAction_Script_7(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_7);
}

static void DebugAction_Script_8(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_Script_8);
}

// *******************************
// Flags & Vars menu functions
static void Debug_RedrawFlagsVarsMenu(u8 taskId)
{
    Debug_RefreshFlagsVarsListItems();
    RedrawListMenu(gTasks[taskId].tMenuTaskId);
}

static u8 Debug_GetFlagValue(u8 id)
{
    switch (id)
    {
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKEDEX:
            return FlagGet(FLAG_SYS_POKEDEX_GET);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_NATDEX:
            return IsNationalPokedexEnabled();
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_POKENAV:
            return FlagGet(FLAG_SYS_POKENAV_GET);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_RUN_SHOES:
            return FlagGet(FLAG_SYS_B_DASH);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_LOCATIONS:
            return FlagGet(FLAG_VISITED_LITTLEROOT_TOWN) &&
                FlagGet(FLAG_VISITED_OLDALE_TOWN) &&
                FlagGet(FLAG_VISITED_DEWFORD_TOWN) &&
                FlagGet(FLAG_VISITED_LAVARIDGE_TOWN) &&
                FlagGet(FLAG_VISITED_FALLARBOR_TOWN) &&
                FlagGet(FLAG_VISITED_VERDANTURF_TOWN) &&
                FlagGet(FLAG_VISITED_PACIFIDLOG_TOWN) &&
                FlagGet(FLAG_VISITED_PETALBURG_CITY) &&
                FlagGet(FLAG_VISITED_SLATEPORT_CITY) &&
                FlagGet(FLAG_VISITED_MAUVILLE_CITY) &&
                FlagGet(FLAG_VISITED_RUSTBORO_CITY) &&
                FlagGet(FLAG_VISITED_FORTREE_CITY) &&
                FlagGet(FLAG_VISITED_LILYCOVE_CITY) &&
                FlagGet(FLAG_VISITED_MOSSDEEP_CITY) &&
                FlagGet(FLAG_VISITED_SOOTOPOLIS_CITY) &&
                FlagGet(FLAG_VISITED_EVER_GRANDE_CITY) &&
                FlagGet(FLAG_LANDMARK_POKEMON_LEAGUE) &&
                FlagGet(FLAG_LANDMARK_BATTLE_FRONTIER);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BADGES_ALL:
            return FlagGet(FLAG_BADGE01_GET) &&
                FlagGet(FLAG_BADGE02_GET) &&
                FlagGet(FLAG_BADGE03_GET) &&
                FlagGet(FLAG_BADGE04_GET) &&
                FlagGet(FLAG_BADGE05_GET) &&
                FlagGet(FLAG_BADGE06_GET) &&
                FlagGet(FLAG_BADGE07_GET) &&
                FlagGet(FLAG_BADGE08_GET);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_FRONTIER_PASS:
            return FlagGet(FLAG_SYS_FRONTIER_PASS);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_GAME_CLEAR:
            return FlagGet(FLAG_SYS_GAME_CLEAR);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BATTLE_DMG:
            return FlagGet(FLAG_SYS_NO_BATTLE_DMG);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_COLLISION:
            return FlagGet(FLAG_SYS_NO_COLLISION);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_ENCOUNTER:
            return FlagGet(FLAG_SYS_NO_ENCOUNTER);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_TRAINER_SEE:
            return FlagGet(FLAG_SYS_NO_TRAINER_SEE);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_BAG_USE:
            return FlagGet(FLAG_SYS_NO_BAG_USE);
        case DEBUG_MENU_ITEM_FLAGVAR_TOGGLE_CATCHING:
            return FlagGet(FLAG_SYS_NO_CATCHING);
        default:
            return DEBUG_MENU_INVALID_FLAG_VALUE;
    }

    return DEBUG_MENU_INVALID_FLAG_VALUE;
}

static void Debug_RefreshFlagsVarsListItems()
{
    const u8 sColor_Red[] = _("{COLOR RED}");
    const u8 sColor_Green[] = _("{COLOR GREEN}");
    u32 i;
    u8 flagValue;

    for (i = 0; i < sDebugMenu_ListTemplate_FlagsVars.totalItems; i++)
    {
        flagValue = Debug_GetFlagValue(i);

        if (flagValue == DEBUG_MENU_INVALID_FLAG_VALUE)
        {
            StringCopy(&sDebugMenuListData->itemNames[i][0], sDebugMenu_Items_FlagsVars[i].name);
        }
        else if (flagValue)
        {
            StringCopy(gStringVar1, sColor_Green);
            StringExpandPlaceholders(gStringVar4, sDebugMenu_Items_FlagsVars[i].name);
            StringCopy(&sDebugMenuListData->itemNames[i][0], gStringVar4);
        }
        else
        {
            StringCopy(gStringVar1, sColor_Red);
            StringExpandPlaceholders(gStringVar4, sDebugMenu_Items_FlagsVars[i].name);
            StringCopy(&sDebugMenuListData->itemNames[i][0], gStringVar4);
        }

        sDebugMenuListData->listItems[i].name = &sDebugMenuListData->itemNames[i][0];
        sDebugMenuListData->listItems[i].id = i;
    }
}

static void Debug_Display_FlagInfo(u32 flag, u32 digit, u8 windowId)
{
    ConvertIntToDecimalStringN(gStringVar1, flag, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_FLAGS);
    ConvertIntToHexStringN(gStringVar2, flag, STR_CONV_MODE_LEFT_ALIGN, 3);
    StringExpandPlaceholders(gStringVar1, COMPOUND_STRING("{STR_VAR_1}{CLEAR_TO 90}\n0x{STR_VAR_2}{CLEAR_TO 90}"));
    if (FlagGet(flag))
        StringCopyPadded(gStringVar2, sDebugText_True, CHAR_SPACE, 15);
    else
        StringCopyPadded(gStringVar2, sDebugText_False, CHAR_SPACE, 15);
    StringCopy(gStringVar3, gText_DigitIndicator[digit]);
    StringExpandPlaceholders(gStringVar4, sDebugText_FlagsVars_Flag);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_FlagsVars_Flags(u8 taskId)
{
    u8 windowId;

    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateExtra);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    // Display initial flag
    Debug_Display_FlagInfo(FLAG_TEMP_1, 0, windowId);

    gTasks[taskId].func = DebugAction_FlagsVars_FlagsSelect;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = FLAG_TEMP_1;
    gTasks[taskId].tDigit = 0;
}

static void DebugAction_FlagsVars_FlagsSelect(u8 taskId)
{
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        FlagToggle(gTasks[taskId].tInput);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
        return;
    }

    Debug_HandleInput_Numeric(taskId, 1, FLAGS_COUNT - 1, DEBUG_NUMBER_DIGITS_FLAGS);

    if (JOY_NEW(DPAD_ANY) || JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        Debug_Display_FlagInfo(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }
}

#define tVarValue  data[5]

static void DebugAction_FlagsVars_Vars(u8 taskId)
{
    u8 windowId;

    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateExtra);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    // Display initial var
    ConvertIntToDecimalStringN(gStringVar1, VARS_START, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
    ConvertIntToHexStringN(gStringVar2, VARS_START, STR_CONV_MODE_LEFT_ALIGN, 4);
    StringExpandPlaceholders(gStringVar1, sDebugText_FlagsVars_VariableHex);
    ConvertIntToDecimalStringN(gStringVar3, 0, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
    StringCopyPadded(gStringVar3, gStringVar3, CHAR_SPACE, 15);
    StringCopy(gStringVar2, gText_DigitIndicator[0]);
    StringExpandPlaceholders(gStringVar4, sDebugText_FlagsVars_Variable);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);

    gTasks[taskId].func = DebugAction_FlagsVars_Select;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = VARS_START;
    gTasks[taskId].tDigit = 0;
    gTasks[taskId].tVarValue = 0;
}

static void DebugAction_FlagsVars_Select(u8 taskId)
{
    Debug_HandleInput_Numeric(taskId, VARS_START, VARS_END, DEBUG_NUMBER_DIGITS_VARIABLES);

    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);

        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
        ConvertIntToHexStringN(gStringVar2, gTasks[taskId].tInput, STR_CONV_MODE_LEFT_ALIGN, 4);
        StringExpandPlaceholders(gStringVar1, sDebugText_FlagsVars_VariableHex);
        if (VarGetIfExist(gTasks[taskId].tInput) == 0xFFFF)
            gTasks[taskId].tVarValue = 0;
        else
            gTasks[taskId].tVarValue = VarGet(gTasks[taskId].tInput);
        ConvertIntToDecimalStringN(gStringVar3, gTasks[taskId].tVarValue, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
        StringCopy(gStringVar2, gText_DigitIndicator[gTasks[taskId].tDigit]);

        //Combine str's to full window string
        StringExpandPlaceholders(gStringVar4, sDebugText_FlagsVars_Variable);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }

    if (JOY_NEW(A_BUTTON))
    {
        gTasks[taskId].tDigit = 0;

        PlaySE(SE_SELECT);

        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
        ConvertIntToHexStringN(gStringVar2, gTasks[taskId].tInput, STR_CONV_MODE_LEFT_ALIGN, 4);
        StringExpandPlaceholders(gStringVar1, sDebugText_FlagsVars_VariableHex);
        if (VarGetIfExist(gTasks[taskId].tInput) == 0xFFFF)
            gTasks[taskId].tVarValue = 0;
        else
            gTasks[taskId].tVarValue = VarGet(gTasks[taskId].tInput);
        ConvertIntToDecimalStringN(gStringVar3, gTasks[taskId].tVarValue, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
        StringCopyPadded(gStringVar3, gStringVar3, CHAR_SPACE, 15);
        StringCopy(gStringVar2, gText_DigitIndicator[gTasks[taskId].tDigit]);
        StringExpandPlaceholders(gStringVar4, sDebugText_FlagsVars_VariableValueSet);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);

        gTasks[taskId].data[6] = gTasks[taskId].data[5]; //New value selector
        gTasks[taskId].func = DebugAction_FlagsVars_SetValue;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
        return;
    }
}

static void DebugAction_FlagsVars_SetValue(u8 taskId)
{
    if (JOY_NEW(DPAD_UP))
    {
        if (gTasks[taskId].data[6] + sPowersOfTen[gTasks[taskId].tDigit] <= 32000)
            gTasks[taskId].data[6] += sPowersOfTen[gTasks[taskId].tDigit];
        else
            gTasks[taskId].data[6] = 32000 - 1;

        if (gTasks[taskId].data[6] >= 32000)
            gTasks[taskId].data[6] = 32000 - 1;
    }
    if (JOY_NEW(DPAD_DOWN))
    {
        gTasks[taskId].data[6] -= sPowersOfTen[gTasks[taskId].tDigit];
        if (gTasks[taskId].data[6] < 0)
            gTasks[taskId].data[6] = 0;
    }
    if (JOY_NEW(DPAD_LEFT))
    {
        gTasks[taskId].tDigit -= 1;
        if (gTasks[taskId].tDigit < 0)
            gTasks[taskId].tDigit = 0;
    }
    if (JOY_NEW(DPAD_RIGHT))
    {
        gTasks[taskId].tDigit += 1;
        if (gTasks[taskId].tDigit > 4)
            gTasks[taskId].tDigit = 4;
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        VarSet(gTasks[taskId].tInput, gTasks[taskId].data[6]);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
        return;
    }

    if (JOY_NEW(DPAD_ANY) || JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        ConvertIntToDecimalStringN(gStringVar1, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
        ConvertIntToHexStringN(gStringVar2, gTasks[taskId].tInput, STR_CONV_MODE_LEFT_ALIGN, 4);
        StringExpandPlaceholders(gStringVar1, sDebugText_FlagsVars_VariableHex);
        StringCopyPadded(gStringVar1, gStringVar1, CHAR_SPACE, 15);
        ConvertIntToDecimalStringN(gStringVar3, gTasks[taskId].data[6], STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_VARIABLES);
        StringCopyPadded(gStringVar3, gStringVar3, CHAR_SPACE, 15);
        StringCopy(gStringVar2, gText_DigitIndicator[gTasks[taskId].tDigit]);
        StringExpandPlaceholders(gStringVar4, sDebugText_FlagsVars_VariableValueSet);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }
}

#undef tVarValue

static void DebugAction_FlagsVars_PokedexFlags_All(u8 taskId)
{
    u16 i;
    for (i = 0; i < NATIONAL_DEX_COUNT; i++)
    {
        GetSetPokedexFlag(i + 1, FLAG_SET_CAUGHT);
        GetSetPokedexFlag(i + 1, FLAG_SET_SEEN);
    }
}

static void DebugAction_FlagsVars_PokedexFlags_Reset(u8 taskId)
{
    int boxId, boxPosition, partyId;
    u16 species;

    // Reset Pokedex to emtpy
    memset(&gSaveBlock2Ptr->pokedex.owned, 0, sizeof(gSaveBlock2Ptr->pokedex.owned));
    memset(&gSaveBlock2Ptr->pokedex.seen, 0, sizeof(gSaveBlock2Ptr->pokedex.seen));

    // Add party Pokemon to Pokedex
    for (partyId = 0; partyId < PARTY_SIZE; partyId++)
    {
        if (GetMonData(&gPlayerParty[partyId], MON_DATA_SANITY_HAS_SPECIES))
        {
            species = GetMonData(&gPlayerParty[partyId], MON_DATA_SPECIES);
            GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_CAUGHT);
            GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_SEEN);
        }
    }

    // Add box Pokemon to Pokedex
    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            if (GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_SANITY_HAS_SPECIES))
            {
                species = GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_SPECIES);
                GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_CAUGHT);
                GetSetPokedexFlag(SpeciesToNationalPokedexNum(species), FLAG_SET_SEEN);
            }
        }
    }
}

static void DebugAction_FlagsVars_SwitchDex(u8 taskId)
{
    if (FlagGet(FLAG_SYS_POKEDEX_GET))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_POKEDEX_GET);
}

static void DebugAction_FlagsVars_SwitchNatDex(u8 taskId)
{
    if (IsNationalPokedexEnabled())
    {
        DisableNationalPokedex();
        PlaySE(SE_PC_OFF);
    }
    else
    {
        EnableNationalPokedex();
        PlaySE(SE_PC_LOGIN);
    }
}

static void DebugAction_FlagsVars_SwitchPokeNav(u8 taskId)
{
    if (FlagGet(FLAG_SYS_POKENAV_GET))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_POKENAV_GET);
}

static void DebugAction_FlagsVars_RunningShoes(u8 taskId)
{
    if (FlagGet(FLAG_SYS_B_DASH))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_B_DASH);
}

static void DebugAction_FlagsVars_ToggleFlyFlags(u8 taskId)
{
    if (FlagGet(FLAG_LANDMARK_BATTLE_FRONTIER))
    {
        PlaySE(SE_PC_OFF);

        FlagClear(FLAG_VISITED_LITTLEROOT_TOWN);
        FlagClear(FLAG_VISITED_OLDALE_TOWN);
        FlagClear(FLAG_VISITED_DEWFORD_TOWN);
        FlagClear(FLAG_VISITED_LAVARIDGE_TOWN);
        FlagClear(FLAG_VISITED_FALLARBOR_TOWN);
        FlagClear(FLAG_VISITED_VERDANTURF_TOWN);
        FlagClear(FLAG_VISITED_PACIFIDLOG_TOWN);
        FlagClear(FLAG_VISITED_PETALBURG_CITY);
        FlagClear(FLAG_VISITED_SLATEPORT_CITY);
        FlagClear(FLAG_VISITED_MAUVILLE_CITY);
        FlagClear(FLAG_VISITED_RUSTBORO_CITY);
        FlagClear(FLAG_VISITED_FORTREE_CITY);
        FlagClear(FLAG_VISITED_LILYCOVE_CITY);
        FlagClear(FLAG_VISITED_MOSSDEEP_CITY);
        FlagClear(FLAG_VISITED_SOOTOPOLIS_CITY);
        FlagClear(FLAG_VISITED_EVER_GRANDE_CITY);
        FlagClear(FLAG_LANDMARK_POKEMON_LEAGUE);
        FlagClear(FLAG_LANDMARK_BATTLE_FRONTIER);
    }
    else
    {
        PlaySE(SE_PC_LOGIN);
    
        FlagSet(FLAG_VISITED_LITTLEROOT_TOWN);
        FlagSet(FLAG_VISITED_OLDALE_TOWN);
        FlagSet(FLAG_VISITED_DEWFORD_TOWN);
        FlagSet(FLAG_VISITED_LAVARIDGE_TOWN);
        FlagSet(FLAG_VISITED_FALLARBOR_TOWN);
        FlagSet(FLAG_VISITED_VERDANTURF_TOWN);
        FlagSet(FLAG_VISITED_PACIFIDLOG_TOWN);
        FlagSet(FLAG_VISITED_PETALBURG_CITY);
        FlagSet(FLAG_VISITED_SLATEPORT_CITY);
        FlagSet(FLAG_VISITED_MAUVILLE_CITY);
        FlagSet(FLAG_VISITED_RUSTBORO_CITY);
        FlagSet(FLAG_VISITED_FORTREE_CITY);
        FlagSet(FLAG_VISITED_LILYCOVE_CITY);
        FlagSet(FLAG_VISITED_MOSSDEEP_CITY);
        FlagSet(FLAG_VISITED_SOOTOPOLIS_CITY);
        FlagSet(FLAG_VISITED_EVER_GRANDE_CITY);
        FlagSet(FLAG_LANDMARK_POKEMON_LEAGUE);
        FlagSet(FLAG_LANDMARK_BATTLE_FRONTIER);
    }
}

static void DebugAction_FlagsVars_ToggleBadgeFlags(u8 taskId)
{
    if (FlagGet(FLAG_BADGE08_GET))
    {
        PlaySE(SE_PC_OFF);

        FlagClear(FLAG_BADGE01_GET);
        FlagClear(FLAG_BADGE02_GET);
        FlagClear(FLAG_BADGE03_GET);
        FlagClear(FLAG_BADGE04_GET);
        FlagClear(FLAG_BADGE05_GET);
        FlagClear(FLAG_BADGE06_GET);
        FlagClear(FLAG_BADGE07_GET);
        FlagClear(FLAG_BADGE08_GET);
    }
    else
    {
        PlaySE(SE_PC_LOGIN);

        FlagSet(FLAG_BADGE01_GET);
        FlagSet(FLAG_BADGE02_GET);
        FlagSet(FLAG_BADGE03_GET);
        FlagSet(FLAG_BADGE04_GET);
        FlagSet(FLAG_BADGE05_GET);
        FlagSet(FLAG_BADGE06_GET);
        FlagSet(FLAG_BADGE07_GET);
        FlagSet(FLAG_BADGE08_GET);
    }
}


static void DebugAction_FlagsVars_ToggleGameClear(u8 taskId)
{
    if (FlagGet(FLAG_SYS_GAME_CLEAR))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_GAME_CLEAR);
}

static void DebugAction_FlagsVars_ToggleFrontierPass(u8 taskId)
{
    if (FlagGet(FLAG_SYS_FRONTIER_PASS))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_FRONTIER_PASS);
}

static void DebugAction_FlagsVars_BattleDmgOnOff(u8 taskId)
{
    if (FlagGet(FLAG_SYS_NO_BATTLE_DMG))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_NO_BATTLE_DMG);
}

static void DebugAction_FlagsVars_CollisionOnOff(u8 taskId)
{
    if (FlagGet(FLAG_SYS_NO_COLLISION))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_NO_COLLISION);
}

static void DebugAction_FlagsVars_EncounterOnOff(u8 taskId)
{
    if (FlagGet(FLAG_SYS_NO_ENCOUNTER))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_NO_ENCOUNTER);
}

static void DebugAction_FlagsVars_TrainerSeeOnOff(u8 taskId)
{
    if (FlagGet(FLAG_SYS_NO_TRAINER_SEE))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_NO_TRAINER_SEE);
}

static void DebugAction_FlagsVars_BagUseOnOff(u8 taskId)
{
    if (FlagGet(FLAG_SYS_NO_BAG_USE))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_NO_BAG_USE);
}

static void DebugAction_FlagsVars_CatchingOnOff(u8 taskId)
{
    if (FlagGet(FLAG_SYS_NO_CATCHING))
        PlaySE(SE_PC_OFF);
    else
        PlaySE(SE_PC_LOGIN);
    FlagToggle(FLAG_SYS_NO_CATCHING);
}

// *******************************
// Battle menu functions
static void Debug_InitializeBattle(u8 taskId)
{
    u32 i;
    gBattleTypeFlags = 0;

    // Set main battle flags
    switch (sDebugBattleData.battleType)
    {
    case DEBUG_MENU_ITEM_BATTLE_START_WILD:
        break;
    case DEBUG_MENU_ITEM_BATTLE_START_SINGLE:
        gBattleTypeFlags = (BATTLE_TYPE_TRAINER);
        break;
    case DEBUG_MENU_ITEM_BATTLE_START_DOUBLE:
        gBattleTypeFlags = (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_TRAINER);
        break;
    case DEBUG_MENU_ITEM_BATTLE_START_PARTNER:
        gBattleTypeFlags = (BATTLE_TYPE_DOUBLE | BATTLE_TYPE_TWO_OPPONENTS | BATTLE_TYPE_TRAINER | BATTLE_TYPE_INGAME_PARTNER);
        break;
    }

    // Set terrain
    gBattleEnvironment = sDebugBattleData.battleTerrain;

    // Set AI flags
    for (i = 0; i < ARRAY_COUNT(sDebugBattleData.aiFlags); i++)
    {
        if (sDebugBattleData.aiFlags[i])
            gDebugAIFlags |= (1 << i);
    }

    gIsDebugBattle = TRUE;
    BattleSetup_StartTrainerBattle_Debug();

    Debug_DestroyMenu_Full(taskId);
}

static void DebugAction_Battle_InitializeWildBattle(u8 taskId)
{
    sDebugBattleData.battleType = DEBUG_MENU_ITEM_BATTLE_START_WILD;
    Debug_InitializeBattle(taskId);
}

static void DebugAction_Battle_InitializeSingleBattle(u8 taskId)
{
    sDebugBattleData.battleType = DEBUG_MENU_ITEM_BATTLE_START_SINGLE;
    Debug_InitializeBattle(taskId);
}

static void DebugAction_Battle_InitializeDoubleBattle(u8 taskId)
{
    sDebugBattleData.battleType = DEBUG_MENU_ITEM_BATTLE_START_DOUBLE;
    Debug_InitializeBattle(taskId);
}

static void DebugAction_Battle_InitializePartnerBattle(u8 taskId)
{
    sDebugBattleData.battleType = DEBUG_MENU_ITEM_BATTLE_START_PARTNER;
    Debug_InitializeBattle(taskId);
}

static void DebugAction_Battle_OpenEnemyPartyMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);

    gMultiuseListMenuTemplate = sDebugMenu_ListTemplate_Battle_EnemyParty;
    Debug_RefreshEnemyPartyListItems();
    gMultiuseListMenuTemplate.items = sDebugMenuListData->listItems;

    Debug_ShowMenu(DebugTask_HandleMenuInput_Battle_EnemyParty, gMultiuseListMenuTemplate);
}

static void DebugAction_Battle_HealEnemyPartyMenu(u8 taskId)
{
    PlaySE(SE_USE_ITEM);
    HealEnemyParty();
}

static void DebugAction_Battle_ClearEnemyPartyMenu(u8 taskId)
{
    PlaySE(SE_EXIT);
    ZeroEnemyPartyMons();
}

static void DebugAction_Battle_OpenAIFlagsMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);

    gMultiuseListMenuTemplate = sDebugMenu_ListTemplate_Battle_AIFlags;
    Debug_RefreshAIFlagsListItems();
    gMultiuseListMenuTemplate.items = sDebugMenuListData->listItems;

    Debug_ShowMenu(DebugTask_HandleMenuInput_Battle_AIFlags, gMultiuseListMenuTemplate);
}

static void DebugAction_Battle_OpenTerrainMenu(u8 taskId)
{
    Debug_DestroyMenu(taskId);

    gMultiuseListMenuTemplate = sDebugMenu_ListTemplate_Battle_Terrain;
    Debug_RefreshTerrainListItems();
    gMultiuseListMenuTemplate.items = sDebugMenuListData->listItems;

    Debug_ShowMenu(DebugTask_HandleMenuInput_Battle_Terrain, gMultiuseListMenuTemplate);
}

static void Debug_RedrawBattleEnemyPartyMenu(u8 taskId)
{
    Debug_RefreshEnemyPartyListItems();
    RedrawListMenu(gTasks[taskId].tMenuTaskId);
}

static void Debug_RedrawBattleAIFlagsMenu(u8 taskId)
{
    Debug_RefreshAIFlagsListItems();
    RedrawListMenu(gTasks[taskId].tMenuTaskId);
}

static void Debug_RedrawBattleTerrainMenu(u8 taskId)
{
    Debug_RefreshTerrainListItems();
    RedrawListMenu(gTasks[taskId].tMenuTaskId);
}

static void Debug_RefreshEnemyPartyListItems()
{
    u16 species;
    u32 i;
    for (i = 0; i < sDebugMenu_ListTemplate_Battle_EnemyParty.totalItems; i++)
    {
        if (GetMonData(&gEnemyParty[i], MON_DATA_SANITY_HAS_SPECIES))
        {
            species = GetMonData(&gEnemyParty[i], MON_DATA_SPECIES);
            StringCopy(gStringVar1, gSpeciesNames[species]);
            StringCopy(&sDebugMenuListData->itemNames[i][0], gStringVar1);
        }
        else
        {
            StringCopy(&sDebugMenuListData->itemNames[i][0], sDebugText_Dashes);
        }

        sDebugMenuListData->listItems[i].name = &sDebugMenuListData->itemNames[i][0];
        sDebugMenuListData->listItems[i].id = i;
    }
}

static void Debug_RefreshAIFlagsListItems()
{
    const u8 sColor_Red[] = _("{COLOR RED}");
    const u8 sColor_Green[] = _("{COLOR GREEN}");
    u32 i;

    for (i = 0; i < sDebugMenu_ListTemplate_Battle_AIFlags.totalItems; i++)
    {
        if (sDebugBattleData.aiFlags[i])
        {
            StringCopy(gStringVar1, sColor_Green);
            StringExpandPlaceholders(gStringVar4, sDebugMenu_Items_Battle_AIFlags[i].name);
            StringCopy(&sDebugMenuListData->itemNames[i][0], gStringVar4);
        }
        else
        {
            StringCopy(gStringVar1, sColor_Red);
            StringExpandPlaceholders(gStringVar4, sDebugMenu_Items_Battle_AIFlags[i].name);
            StringCopy(&sDebugMenuListData->itemNames[i][0], gStringVar4);
        }

        sDebugMenuListData->listItems[i].name = &sDebugMenuListData->itemNames[i][0];
        sDebugMenuListData->listItems[i].id = i;
    }
}

static void Debug_RefreshTerrainListItems()
{
    const u8 sHighlight[] = _("{HIGHLIGHT LIGHT_GREEN}");
    u32 i;

    for (i = 0; i < sDebugMenu_ListTemplate_Battle_Terrain.totalItems; i++)
    {
        if (sDebugBattleData.battleTerrain == i)
        {
            StringCopy(&sDebugMenuListData->itemNames[i][0], sHighlight);
            StringAppend(&sDebugMenuListData->itemNames[i][0], sDebugMenu_Items_Battle_Terrain[i].name);
        }
        else
        {
            StringCopy(&sDebugMenuListData->itemNames[i][0], sDebugMenu_Items_Battle_Terrain[i].name);
        }

        sDebugMenuListData->listItems[i].name = &sDebugMenuListData->itemNames[i][0];
        sDebugMenuListData->listItems[i].id = i;
    }
}

static void DebugTask_HandleMenuInput_Battle_EnemyParty(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuTaskId);

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        if (GetMonData(&gEnemyParty[input], MON_DATA_SANITY_HAS_SPECIES))
        {
            Debug_DestroyMenu(taskId);
            DebugPkmCreator_Init(MODE_BATTLE_DEBUG_MENU_ENEMY_PARTY_EDIT_INDEX, input);
        }
        else
        {
            Debug_DestroyMenu(taskId);
            DebugPkmCreator_Init(MODE_BATTLE_DEBUG_MENU_ENEMY_PARTY_EDIT, 0xFF);
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMenu(DebugTask_HandleMenuInput_Battle, sDebugMenu_ListTemplate_Battle);
    }
}

static void DebugTask_HandleMenuInput_Battle_AIFlags(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuTaskId);

    if (JOY_NEW(A_BUTTON))
    {
        if (sDebugBattleData.aiFlags[input])
            PlaySE(SE_PC_OFF);
        else
            PlaySE(SE_PC_LOGIN);

        sDebugBattleData.aiFlags[input] = !sDebugBattleData.aiFlags[input];
        Debug_RedrawBattleAIFlagsMenu(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMenu(DebugTask_HandleMenuInput_Battle, sDebugMenu_ListTemplate_Battle);
    }
}

static void DebugTask_HandleMenuInput_Battle_Terrain(u8 taskId)
{
    void (*func)(u8);
    u32 input = ListMenu_ProcessInput(gTasks[taskId].tMenuTaskId);

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);
        sDebugBattleData.battleTerrain = input;
        Debug_RedrawBattleTerrainMenu(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Debug_DestroyMenu(taskId);
        Debug_ShowMenu(DebugTask_HandleMenuInput_Battle, sDebugMenu_ListTemplate_Battle);
    }
}

void Debug_OnEnemyPartyEditFinished(void)
{
    gMultiuseListMenuTemplate = sDebugMenu_ListTemplate_Battle_EnemyParty;
    Debug_RefreshEnemyPartyListItems();
    gMultiuseListMenuTemplate.items = sDebugMenuListData->listItems;

    Debug_ShowMenu(DebugTask_HandleMenuInput_Battle_EnemyParty, gMultiuseListMenuTemplate);
}

// *******************************
// Bag menu functions
#define ITEM_TAG 0xFDF3
#define tItemId    data[5]
#define tSpriteId  data[6]

static void Debug_Display_ItemInfo(u32 itemId, u32 digit, u8 windowId)
{
    StringCopy(gStringVar2, gText_DigitIndicator[digit]);
    ConvertIntToDecimalStringN(gStringVar3, itemId, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_ITEMS);
    CopyItemName(itemId, gStringVar1);
    StringCopyPadded(gStringVar1, gStringVar1, CHAR_SPACE, 15);
    StringExpandPlaceholders(gStringVar4, sDebugText_ItemID);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Bag_Give_Item(u8 taskId)
{
    u8 windowId;

    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateExtra);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    // Display initial item
    Debug_Display_ItemInfo(1, 0, windowId);

    gTasks[taskId].func = DebugAction_Bag_Give_Item_SelectId;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = 1;
    gTasks[taskId].tDigit = 0;
    gTasks[taskId].tSpriteId = AddItemIconSprite(ITEM_TAG, ITEM_TAG, gTasks[taskId].tInput);
    gSprites[gTasks[taskId].tSpriteId].x2 = DEBUG_NUMBER_ICON_X+10;
    gSprites[gTasks[taskId].tSpriteId].y2 = DEBUG_NUMBER_ICON_Y+10;
    gSprites[gTasks[taskId].tSpriteId].oam.priority = 0;
}

static void Debug_DestroyItemIcon(u8 taskId)
{
    FreeSpriteTilesByTag(ITEM_TAG);
    FreeSpritePaletteByTag(ITEM_TAG);
    FreeSpriteOamMatrix(&gSprites[gTasks[taskId].tSpriteId]);
    DestroySprite(&gSprites[gTasks[taskId].tSpriteId]);
}

static void Debug_Display_ItemQuantity(u32 quantity, u32 digit, u8 windowId)
{
    StringCopy(gStringVar2, gText_DigitIndicator[digit]);
    ConvertIntToDecimalStringN(gStringVar1, quantity, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_ITEM_QUANTITY);
    StringCopyPadded(gStringVar1, gStringVar1, CHAR_SPACE, 15);
    StringExpandPlaceholders(gStringVar4, sDebugText_ItemQuantity);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Bag_Give_Item_SelectId(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 1, ITEMS_COUNT - 1, DEBUG_NUMBER_DIGITS_ITEMS);
        Debug_Display_ItemInfo(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
        Debug_DestroyItemIcon(taskId);
        gTasks[taskId].tSpriteId = AddItemIconSprite(ITEM_TAG, ITEM_TAG, gTasks[taskId].tInput);
        gSprites[gTasks[taskId].tSpriteId].x2 = DEBUG_NUMBER_ICON_X+10;
        gSprites[gTasks[taskId].tSpriteId].y2 = DEBUG_NUMBER_ICON_Y+10;
        gSprites[gTasks[taskId].tSpriteId].oam.priority = 0;
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        gTasks[taskId].tItemId = gTasks[taskId].tInput;
        gTasks[taskId].tInput = 1;
        gTasks[taskId].tDigit = 0;
        Debug_Display_ItemQuantity(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
        gTasks[taskId].func = DebugAction_Bag_Give_Item_SelectQuantity;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        Debug_DestroyItemIcon(taskId);

        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void DebugAction_Bag_Give_Item_SelectQuantity(u8 taskId)
{
    u32 itemId = gTasks[taskId].tItemId;

    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 1, MAX_BAG_ITEM_CAPACITY, MAX_ITEM_DIGITS);
        Debug_Display_ItemQuantity(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }

    if (JOY_NEW(A_BUTTON))
    {
        Debug_DestroyItemIcon(taskId);

        PlaySE(MUS_OBTAIN_ITEM);
        AddBagItem(itemId, gTasks[taskId].tInput);
        DebugAction_DestroyExtraWindow(taskId);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        Debug_DestroyItemIcon(taskId);

        PlaySE(SE_SELECT);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

#undef tItemId
#undef tSpriteId

static void DebugAction_Bag_Give_All_TMs(u8 taskId)
{
    u16 i;
    PlayFanfare(MUS_OBTAIN_TMHM);
    for (i = ITEM_TM01; i <= ITEM_TM50; i++)
        if (!CheckBagHasItem(i, 1))
            AddBagItem(i, 1);
}

static void DebugAction_Bag_Give_All_HMs(u8 taskId)
{
    u16 i;
    PlayFanfare(MUS_OBTAIN_TMHM);
    for (i = ITEM_HM01; i <= ITEM_HM08; i++)
        if (!CheckBagHasItem(i, 1)) 
            AddBagItem(i, 1);
}

static void DebugAction_Bag_Give_All_Items(u8 taskId)
{
    u16 itemId;
    PlaySE(MUS_OBTAIN_ITEM);
    for (itemId = 1; itemId < ITEMS_COUNT; itemId++)
    {
        if (GetItemPocket(itemId) == POCKET_ITEMS && CheckBagHasSpace(itemId, MAX_BAG_ITEM_CAPACITY))
            AddBagItem(itemId, MAX_BAG_ITEM_CAPACITY);
    }
}

static void DebugAction_Bag_Give_All_PokeBalls(u8 taskId)
{
    u16 ballId;
    PlaySE(MUS_OBTAIN_ITEM);
    for (ballId = FIRST_BALL; ballId <= LAST_BALL; ballId++)
    {
        if (CheckBagHasSpace(ballId, MAX_BAG_ITEM_CAPACITY))
            AddBagItem(ballId, MAX_BAG_ITEM_CAPACITY);
    }
}

static void DebugAction_Bag_Give_All_Berries(u8 taskId)
{
    u16 itemId;
    PlaySE(MUS_OBTAIN_ITEM);
    for (itemId = FIRST_BERRY_INDEX; itemId < LAST_BERRY_INDEX; itemId++)
    {
        if (CheckBagHasSpace(itemId, MAX_BERRY_CAPACITY))
            AddBagItem(itemId, MAX_BERRY_CAPACITY);
    }
}

static void DebugAction_Bag_Give_All_KeyItems(u8 taskId)
{
    u16 itemId;
    PlaySE(MUS_OBTAIN_ITEM);
    for (itemId = 1; itemId < ITEMS_COUNT; itemId++)
    {
        if (GetItemPocket(itemId) == POCKET_KEY_ITEMS && CheckBagHasSpace(itemId, 1))
            AddBagItem(itemId, 1);
    }
}

static void DebugAction_Bag_MaxMoney(u8 taskId)
{
    SetMoney(&gSaveBlock1Ptr->money, MAX_MONEY);
}

static void DebugAction_Bag_MaxCoins(u8 taskId)
{
    SetCoins(MAX_COINS);
}

static void DebugAction_Bag_MaxBattlePoints(u8 taskId)
{
    gSaveBlock2Ptr->frontier.battlePoints = MAX_BATTLE_FRONTIER_POINTS;
}

static void DebugAction_Bag_Clear(u8 taskId)
{
    PlaySE(SE_EXIT);
    ClearBag();
}

// *******************************
// Party menu functions
static void DebugAction_Party_HealParty(u8 taskId)
{
    PlaySE(SE_USE_ITEM);
    HealPlayerParty();
    ScriptContext_Enable();
    Debug_DestroyMenu_Full(taskId);
}

//Pokemon
static void ResetMonDataStruct(struct DebugMonData *sDebugMonData)
{
    u32 i;

    sDebugMonData->species          = 1;
    sDebugMonData->level            = 1;
    sDebugMonData->isShiny          = FALSE;
    sDebugMonData->nature           = 0;
    sDebugMonData->abilityNum       = 0;

    for (i = 0; i < NUM_STATS; i++)
    {
        sDebugMonData->monIVs[i] = 0;
        sDebugMonData->monEVs[i] = 0;
    }
}

#define tIsComplex  data[5]
#define tSpriteId   data[6]
#define tIterator   data[7]

static void Debug_Display_SpeciesInfo(u32 species, u32 digit, u8 windowId)
{
    StringCopy(gStringVar2, gText_DigitIndicator[digit]);
    ConvertIntToDecimalStringN(gStringVar3, species, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_ITEMS);
    StringCopy(gStringVar1, gSpeciesNames[species]);
    StringCopyPadded(gStringVar1, gStringVar1, CHAR_SPACE, 15);
    StringExpandPlaceholders(gStringVar4, sDebugText_PokemonID);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Party_GivePokemonSimple(u8 taskId)
{
    u8 windowId;

    //Mon data struct
    sDebugMonData = AllocZeroed(sizeof(struct DebugMonData));
    ResetMonDataStruct(sDebugMonData);

    //Window initialization
    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateExtra);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    // Display initial Pokémon
    Debug_Display_SpeciesInfo(sDebugMonData->species, 0, windowId);

    //Set task data
    gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectId;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = sDebugMonData->species;
    gTasks[taskId].tDigit = 0;
    gTasks[taskId].tIsComplex = FALSE;

    FreeMonIconPalettes();
    LoadMonIconPalette(gTasks[taskId].tInput);
    gTasks[taskId].tSpriteId = CreateMonIcon(gTasks[taskId].tInput, SpriteCB_MonIcon, DEBUG_NUMBER_ICON_X, DEBUG_NUMBER_ICON_Y, 4, 0, TRUE);
    gSprites[gTasks[taskId].tSpriteId].oam.priority = 0;
}

static void DebugAction_Party_GivePokemonComplex(u8 taskId)
{
    u8 windowId;

    //Mon data struct
    sDebugMonData = AllocZeroed(sizeof(struct DebugMonData));
    ResetMonDataStruct(sDebugMonData);

    //Window initialization
    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateExtra);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    // Display initial Pokémon
    Debug_Display_SpeciesInfo(sDebugMonData->species, 0, windowId);

    gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectId;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = 1;
    gTasks[taskId].tDigit = 0;
    gTasks[taskId].tIsComplex = TRUE;

    FreeMonIconPalettes();
    LoadMonIconPalette(gTasks[taskId].tInput);
    gTasks[taskId].tSpriteId = CreateMonIcon(gTasks[taskId].tInput, SpriteCB_MonIcon, DEBUG_NUMBER_ICON_X, DEBUG_NUMBER_ICON_Y, 4, 0, TRUE);
    gSprites[gTasks[taskId].tSpriteId].oam.priority = 0;
    gTasks[taskId].tIterator = 0;
}

static void Debug_Display_Level(u32 level, u32 digit, u8 windowId)
{
    StringCopy(gStringVar2, gText_DigitIndicator[digit]);
    ConvertIntToDecimalStringN(gStringVar1, level, STR_CONV_MODE_LEADING_ZEROS, 3);
    StringCopyPadded(gStringVar1, gStringVar1, CHAR_SPACE, 15);
    StringExpandPlaceholders(gStringVar4, sDebugText_PokemonLevel);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Party_GivePokemon_SelectId(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 1, NUM_SPECIES - 1, DEBUG_NUMBER_DIGITS_ITEMS);
        Debug_Display_SpeciesInfo(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);

        FreeAndDestroyMonIconSprite(&gSprites[gTasks[taskId].tSpriteId]);
        FreeMonIconPalettes();
        LoadMonIconPalette(gTasks[taskId].tInput);
        gTasks[taskId].tSpriteId = CreateMonIcon(gTasks[taskId].tInput, SpriteCB_MonIcon, DEBUG_NUMBER_ICON_X, DEBUG_NUMBER_ICON_Y, 4, 0, TRUE);
        gSprites[gTasks[taskId].tSpriteId].oam.priority = 0;
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        sDebugMonData->species = gTasks[taskId].tInput;
        gTasks[taskId].tInput = 1;
        gTasks[taskId].tDigit = 0;

        Debug_Display_Level(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);

        gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectLevel;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        FreeMonIconPalettes();
        FreeAndDestroyMonIconSprite(&gSprites[gTasks[taskId].tSpriteId]);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void Debug_Display_TrueFalse(bool32 value, u8 windowId, const u8 *titleStr)
{
    ConvertIntToDecimalStringN(gStringVar3, value, STR_CONV_MODE_LEADING_ZEROS, 0);
    StringCopyPadded(gStringVar3, gStringVar3, CHAR_SPACE, 15);
    StringCopyPadded(gStringVar2, value ? sDebugText_True : sDebugText_False, CHAR_SPACE, 15);
    StringExpandPlaceholders(gStringVar4, titleStr);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Party_GivePokemon_SelectLevel(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 1, MAX_LEVEL, 3);
        Debug_Display_Level(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }

    if (JOY_NEW(A_BUTTON))
    {
        FreeMonIconPalettes();
        FreeAndDestroyMonIconSprite(&gSprites[gTasks[taskId].tSpriteId]);
        if (gTasks[taskId].tIsComplex == FALSE)
        {
            PlaySE(MUS_LEVEL_UP);
            ScriptGiveMon(sDebugMonData->species, gTasks[taskId].tInput, ITEM_NONE, 0,0,0);
            // Set flag for user convenience
            FlagSet(FLAG_SYS_POKEMON_GET);
            Free(sDebugMonData);            DebugAction_DestroyExtraWindow(taskId);
        }
        else
        {
            PlaySE(SE_SELECT);

            sDebugMonData->level = gTasks[taskId].tInput;
            gTasks[taskId].tInput = 0;
            gTasks[taskId].tDigit = 0;

            Debug_Display_TrueFalse(gTasks[taskId].tInput, gTasks[taskId].tSubWindowId, sDebugText_PokemonShiny);
            gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectShiny;
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        FreeMonIconPalettes();
        FreeAndDestroyMonIconSprite(&gSprites[gTasks[taskId].tSpriteId]);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void Debug_Display_Nature(u32 natureId, u32 digit, u8 windowId)
{
    StringCopy(gStringVar2, gText_DigitIndicator[digit]);
    ConvertIntToDecimalStringN(gStringVar3, natureId, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringCopyPadded(gStringVar3, gStringVar3, CHAR_SPACE, 15);
    StringCopy(gStringVar1, gNatureNamePointers[natureId]);
    StringExpandPlaceholders(gStringVar4, sDebugText_PokemonNature);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Party_GivePokemon_SelectShiny(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        gTasks[taskId].tInput ^= JOY_NEW(DPAD_UP | DPAD_DOWN) > 0;
        Debug_Display_TrueFalse(gTasks[taskId].tInput, gTasks[taskId].tSubWindowId, sDebugText_PokemonShiny);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        sDebugMonData->isShiny = gTasks[taskId].tInput;
        gTasks[taskId].tInput = 0;
        gTasks[taskId].tDigit = 0;

        Debug_Display_Nature(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
        gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectNature;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void Debug_Display_Ability(u8 abilityId, u32 digit, u8 windowId)
{
    StringCopy(gStringVar2, gText_DigitIndicator[digit]);
    ConvertIntToDecimalStringN(gStringVar3, abilityId, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringCopyPadded(gStringVar3, gStringVar3, CHAR_SPACE, 15);
    StringCopy(gStringVar1, gAbilityNames[abilityId]);
    StringExpandPlaceholders(gStringVar4, sDebugText_PokemonAbility);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Party_GivePokemon_SelectNature(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);

        if (JOY_NEW(DPAD_UP))
        {
            gTasks[taskId].tInput += sPowersOfTen[gTasks[taskId].tDigit];
            if (gTasks[taskId].tInput > NUM_NATURES - 1)
                gTasks[taskId].tInput = NUM_NATURES - 1;
        }
        if (JOY_NEW(DPAD_DOWN))
        {
            gTasks[taskId].tInput -= sPowersOfTen[gTasks[taskId].tDigit];
            if (gTasks[taskId].tInput < 0)
                gTasks[taskId].tInput = 0;
        }

        Debug_Display_Nature(gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }

    if (JOY_NEW(A_BUTTON))
    {
        u8 abilityId = GetAbilityBySpecies(sDebugMonData->species, 0);
        PlaySE(SE_SELECT);

        sDebugMonData->nature = gTasks[taskId].tInput;
        gTasks[taskId].tInput = 0;
        gTasks[taskId].tDigit = 0;

        Debug_Display_Ability(abilityId, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);

        gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectAbility;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void Debug_Display_StatInfo(const u8* text, u32 stat, u32 value, u32 digit, u8 windowId)
{
    StringCopy(gStringVar1, gStatNamesTable[stat]);
    StringCopy(gStringVar2, gText_DigitIndicator[digit]);
    ConvertIntToDecimalStringN(gStringVar3, value, STR_CONV_MODE_LEADING_ZEROS, 2);
    StringCopyPadded(gStringVar3, gStringVar3, CHAR_SPACE, 15);
    StringExpandPlaceholders(gStringVar4, text);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Party_GivePokemon_SelectAbility(u8 taskId)
{
    u8 abilityId;
    u8 abilityCount = 2 - 1; //-1 for proper iteration
    u8 i = 0;

    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);

        if (JOY_NEW(DPAD_UP))
        {
            gTasks[taskId].tInput += sPowersOfTen[gTasks[taskId].tDigit];
            if (gTasks[taskId].tInput > abilityCount)
                gTasks[taskId].tInput = abilityCount;
        }
        if (JOY_NEW(DPAD_DOWN))
        {
            gTasks[taskId].tInput -= sPowersOfTen[gTasks[taskId].tDigit];
            if (gTasks[taskId].tInput < 0)
                gTasks[taskId].tInput = 0;
        }

        while (GetAbilityBySpecies(sDebugMonData->species, gTasks[taskId].tInput - i) == ABILITY_NONE)
        {
            i++;
        }
        abilityId = GetAbilityBySpecies(sDebugMonData->species, gTasks[taskId].tInput - i);
        Debug_Display_Ability(abilityId, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        sDebugMonData->abilityNum = gTasks[taskId].tInput - i;
        gTasks[taskId].tInput = 0;
        gTasks[taskId].tDigit = 0;

        Debug_Display_StatInfo(sDebugText_PokemonIVs, gTasks[taskId].tIterator, gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
        gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectIVs;
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void DebugAction_Party_GivePokemon_SelectIVs(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 0, MAX_PER_STAT_IVS, 3);
        Debug_Display_StatInfo(sDebugText_PokemonIVs, gTasks[taskId].tIterator, gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }

    //If A or B button
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        // Set IVs for stat
        sDebugMonData->monIVs[gTasks[taskId].tIterator] = gTasks[taskId].tInput;

        //Check if all IVs set
        if (gTasks[taskId].tIterator != NUM_STATS - 1)
        {
            gTasks[taskId].tIterator++;
            gTasks[taskId].tInput = 0;
            gTasks[taskId].tDigit = 0;

            Debug_Display_StatInfo(sDebugText_PokemonIVs, gTasks[taskId].tIterator, gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
            gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectIVs;
        }
        else
        {
            gTasks[taskId].tInput = 0;
            gTasks[taskId].tDigit = 0;
            gTasks[taskId].tIterator = 0;

            Debug_Display_StatInfo(sDebugText_PokemonIVs, gTasks[taskId].tIterator, gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
            gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectEVs;
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static u32 GetDebugPokemonTotalEV(void)
{
    u32 i;
    u32 totalEVs = 0;

    for (i = 0; i < NUM_STATS; i++)
        totalEVs += sDebugMonData->monEVs[i];
    return totalEVs;
}

static void Debug_Display_MoveInfo(u32 moveId, u32 iteration, u32 digit, u8 windowId)
{
    StringCopy(gStringVar1, gMoveNames[moveId]);
    StringCopyPadded(gStringVar1, gStringVar1, CHAR_SPACE, 15);
    StringCopy(gStringVar4, COMPOUND_STRING("Move "));
    ConvertIntToDecimalStringN(gStringVar3, iteration, STR_CONV_MODE_LEADING_ZEROS, 1);
    StringAppend(gStringVar4, gStringVar3);
    StringAppend(gStringVar4, COMPOUND_STRING(": "));
    ConvertIntToDecimalStringN(gStringVar3, moveId, STR_CONV_MODE_LEADING_ZEROS, 3);
    StringAppend(gStringVar4, gStringVar3);
    StringAppend(gStringVar4, COMPOUND_STRING("{CLEAR_TO 90}\n"));
    StringAppend(gStringVar4, gStringVar1);
    StringAppend(gStringVar4, COMPOUND_STRING("{CLEAR_TO 90}\n{CLEAR_TO 90}\n"));
    StringAppend(gStringVar4, gText_DigitIndicator[digit]);
    StringAppend(gStringVar4, COMPOUND_STRING("{CLEAR_TO 90}"));
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
}

static void DebugAction_Party_GivePokemon_SelectEVs(u8 taskId)
{
    u16 totalEV = GetDebugPokemonTotalEV();

    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 0, MAX_PER_STAT_EVS, 4);
        Debug_Display_StatInfo(sDebugText_PokemonEVs, gTasks[taskId].tIterator, gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }

    //If A or B button
    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        // Set EVs for stat
        sDebugMonData->monEVs[gTasks[taskId].tIterator] = gTasks[taskId].tInput;

        //Check if all EVs set
        if (gTasks[taskId].tIterator != NUM_STATS - 1)
        {
            gTasks[taskId].tIterator++;
            gTasks[taskId].tInput = 0;
            gTasks[taskId].tDigit = 0;
            Debug_Display_StatInfo(sDebugText_PokemonEVs, gTasks[taskId].tIterator, gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
            gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectEVs;
        }
        else
        {
            u32 i;

            gTasks[taskId].tInput = 0;
            gTasks[taskId].tDigit = 0;
            gTasks[taskId].tIterator = 0;

            if (totalEV > MAX_TOTAL_EVS)
            {
                for (i = 0; i < NUM_STATS; i++)
                {
                    sDebugMonData->monEVs[i] = 0;
                }

                PlaySE(SE_FAILURE);
                Debug_Display_StatInfo(sDebugText_PokemonEVs, gTasks[taskId].tIterator, gTasks[taskId].tInput, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
                gTasks[taskId].func = DebugAction_Party_GivePokemon_SelectEVs;
            }
            else
            {
                Debug_Display_MoveInfo(gTasks[taskId].tInput, gTasks[taskId].tIterator, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
                gTasks[taskId].func = DebugAction_Party_GivePokemon_Moves;
            }
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void DebugAction_Party_GivePokemon_Moves(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        PlaySE(SE_SELECT);
        Debug_HandleInput_Numeric(taskId, 0, MOVES_COUNT - 1, 4);

        Debug_Display_MoveInfo(gTasks[taskId].tInput, gTasks[taskId].tIterator, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
    }

    if (JOY_NEW(A_BUTTON))
    {
        PlaySE(SE_SELECT);

        // Set current value
        sDebugMonData->monMoves[gTasks[taskId].tIterator] = gTasks[taskId].tInput;

        // If MOVE_NONE selected, stop asking for additional moves
        if (gTasks[taskId].tInput == MOVE_NONE)
            gTasks[taskId].tIterator = MAX_MON_MOVES;

        //If NOT last move or selected MOVE_NONE ask for next move, else make mon
        if (gTasks[taskId].tIterator < MAX_MON_MOVES - 1)
        {
            gTasks[taskId].tIterator++;
            gTasks[taskId].tInput = 0;
            gTasks[taskId].tDigit = 0;

            Debug_Display_MoveInfo(gTasks[taskId].tInput, gTasks[taskId].tIterator, gTasks[taskId].tDigit, gTasks[taskId].tSubWindowId);
            gTasks[taskId].func = DebugAction_Party_GivePokemon_Moves;
        }
        else
        {
            gTasks[taskId].tInput = 0;
            gTasks[taskId].tDigit = 0;

            PlaySE(MUS_LEVEL_UP);
            gTasks[taskId].func = DebugAction_Party_GivePokemon_ComplexCreateMon;
        }
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        Free(sDebugMonData);
        DebugAction_DestroyExtraWindow(taskId);
    }
}

static void DebugAction_Party_GivePokemon_ComplexCreateMon(u8 taskId) //https://github.com/ghoulslash/pokeemerald/tree/custom-givemon
{
    u16 nationalDexNum;
    int sentToPc;
    struct Pokemon mon;
    u8 i;
    u16 moves[MAX_MON_MOVES];
    u8 IVs[NUM_STATS];
    u8 iv_val;
    u8 EVs[NUM_STATS];
    u8 ev_val;
    u16 species     = sDebugMonData->species;
    u8 level        = sDebugMonData->level;
    bool8 isShiny   = sDebugMonData->isShiny;
    u8 nature       = sDebugMonData->nature;
    u8 abilityNum   = sDebugMonData->abilityNum;
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        moves[i] = sDebugMonData->monMoves[i];
    }
    for (i = 0; i < NUM_STATS; i++)
    {
        EVs[i] = sDebugMonData->monEVs[i];
        IVs[i] = sDebugMonData->monIVs[i];
    }

    //Nature
    if (nature == NUM_NATURES || nature == 0xFF)
        nature = Random() % NUM_NATURES;

    //Shininess
    if (isShiny == TRUE)
    {
        u32 personality;
        u32 playerTrainerId = GetTrainerId(gSaveBlock2Ptr->playerTrainerId);
        u32 playerTrainerIdXor = (HIHALF(playerTrainerId) ^ LOHALF(playerTrainerId));

        do
        {
            personality = (Random2() << 16) | (Random());
            personality = ((((Random() % SHINY_ODDS) ^ playerTrainerIdXor) ^ LOHALF(personality)) << 16) | LOHALF(personality);
        } while (nature != GetNatureFromPersonality(personality) || personality == 0);
        
        CreateMon(&mon, species, level, USE_RANDOM_IVS, TRUE, personality, OT_ID_PRESET, playerTrainerId);
    }
    else
    {
        CreateMonWithNature(&mon, species, level, USE_RANDOM_IVS, nature);
    }

    //IVs
    for (i = 0; i < NUM_STATS; i++)
    {
        iv_val = IVs[i];
        if (iv_val != USE_RANDOM_IVS && iv_val != 0xFF)
            SetMonData(&mon, MON_DATA_HP_IV + i, &iv_val);
    }

    //EVs
    for (i = 0; i < NUM_STATS; i++)
    {
        ev_val = EVs[i];
        if (ev_val)
            SetMonData(&mon, MON_DATA_HP_EV + i, &ev_val);
    }

    //Moves
    for (i = 0; i < MAX_MON_MOVES; i++)
    {
        if (moves[i] == MOVE_NONE || moves[i] >= MOVES_COUNT)
            continue;

        SetMonMoveSlot(&mon, moves[i], i);
    }

    //Ability
    if (abilityNum == 0xFF || GetAbilityBySpecies(species, abilityNum) == ABILITY_NONE)
    {
        do {
            abilityNum = Random() % 3;  // includes hidden abilities
        } while (GetAbilityBySpecies(species, abilityNum) == ABILITY_NONE);
    }

    SetMonData(&mon, MON_DATA_ABILITY_NUM, &abilityNum);

    //Update mon stats before giving it to the player
    CalculateMonStats(&mon);

    // give player the mon
    SetMonData(&mon, MON_DATA_OT_NAME, gSaveBlock2Ptr->playerName);
    SetMonData(&mon, MON_DATA_OT_GENDER, &gSaveBlock2Ptr->playerGender);
    for (i = 0; i < PARTY_SIZE; i++)
    {
        if (GetMonData(&gPlayerParty[i], MON_DATA_SPECIES, NULL) == SPECIES_NONE)
            break;
    }

    if (i >= PARTY_SIZE)
    {
        sentToPc = CopyMonToPC(&mon);
    }
    else
    {
        sentToPc = MON_GIVEN_TO_PARTY;
        CopyMon(&gPlayerParty[i], &mon, sizeof(mon));
        gPlayerPartyCount = i + 1;
    }

    //Pokedex entry
    nationalDexNum = SpeciesToNationalPokedexNum(species);
    switch(sentToPc)
    {
    case MON_GIVEN_TO_PARTY:
    case MON_GIVEN_TO_PC:
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_SEEN);
        GetSetPokedexFlag(nationalDexNum, FLAG_SET_CAUGHT);
        break;
    case MON_CANT_GIVE:
        break;
    }

    // Set flag for user convenience
    FlagSet(FLAG_SYS_POKEMON_GET);

    Free(sDebugMonData);
    DebugAction_DestroyExtraWindow(taskId); //return sentToPc;
}

#undef tIsComplex
#undef tSpriteId
#undef tIterator

static void DebugAction_Party_ClearParty(u8 taskId)
{
    ZeroPlayerPartyMons();
    ScriptContext_Enable();
    Debug_DestroyMenu_Full(taskId);
}

static void DebugAction_Party_TriggerDaycareEgg(u8 taskId)
{
    s32 emptySlot = Daycare_FindEmptySpot(&gSaveBlock1Ptr->daycare);
    if (emptySlot == 0) // no daycare mons
        Debug_DestroyMenu_Full_Script(taskId, DebugScript_ZeroDaycareMons);
    else if (emptySlot == 1) // 1 daycare mon
        Debug_DestroyMenu_Full_Script(taskId, DebugScript_OneDaycareMons);
    else if (GetDaycareCompatibilityScore(&gSaveBlock1Ptr->daycare) == PARENTS_INCOMPATIBLE) // not compatible parents
        Debug_DestroyMenu_Full_Script(taskId, DebugScript_DaycareMonsNotCompatible);
    else // 2 pokemon which can have a pokemon baby together
        TriggerPendingDaycareEgg();

    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();
}

static void DebugAction_Party_HatchAnEgg(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, Debug_HatchAnEgg);
}

static void DebugAction_Party_MoveReminder(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, FallarborTown_MoveRelearnersHouse_EventScript_ChooseMon);
}

// *******************************
// Pokemon Creator menu functions
static void DebugAction_PkmCreator_Party_Add(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_PARTY_ADD, 0xFF);
}
static void DebugAction_PkmCreator_Party_Edit(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_PARTY_EDIT, 0xFF);
}
static void DebugAction_PkmCreator_PC_Edit(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_PC_EDIT, 0xFF);
}
static void DebugAction_PkmCreator_Enemy_Party_Edit(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_ENEMY_PARTY_EDIT, 0xFF);
}
static void DebugAction_PkmCreator_Enemy_Party_Edit_Draft(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_ENEMY_PARTY_EDIT_DRAFT, 0xFF);
}
static void DebugAction_PkmCreator_Party_Edit_Draft(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_PARTY_EDIT_DRAFT, 0xFF);
}
static void DebugAction_PkmCreator_Enemy_Party_Add(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_ENEMY_PARTY_ADD, 0xFF);
}
static void DebugAction_PkmCreator_Testing(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_TESTING, 0xFF);
}
static void DebugAction_PkmCreator_Testing_Copy(u8 taskId)
{
    Debug_DestroyMenu_Full(taskId);
    LockPlayerFieldControls();
    DebugPkmCreator_Init(MODE_TESTING_COPY, 0xFF);
}

// *******************************
// PC menu functions
static void DebugAction_PC_Access(u8 taskId)
{
    Debug_DestroyMenu_Full_Script(taskId, EventScript_PC);
}

static void DebugAction_PC_FillBoxesSame(u8 taskId) //Credit: Sierraffinity
{
    int boxId, boxPosition;
    struct BoxPokemon boxMon;

    CreateBoxMon(&boxMon, SPECIES_BULBASAUR, 100, 32, FALSE, 0, OT_ID_PLAYER_ID, 0);

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            if (!GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_SANITY_HAS_SPECIES))
            {
                gPokemonStoragePtr->boxes[boxId][boxPosition] = boxMon;
            }
        }
    }

    // Set flag for user convenience
    FlagSet(FLAG_SYS_POKEMON_GET);

    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();
}

static void DebugAction_PC_FillBoxesDiverse(u8 taskId)
{
    int boxId, boxPosition;
    struct BoxPokemon boxMon;
    u32 species = SPECIES_BULBASAUR;

    for (boxId = 0; boxId < TOTAL_BOXES_COUNT; boxId++)
    {
        for (boxPosition = 0; boxPosition < IN_BOX_COUNT; boxPosition++)
        {
            if (!GetBoxMonData(&gPokemonStoragePtr->boxes[boxId][boxPosition], MON_DATA_SANITY_HAS_SPECIES))
            {
                CreateBoxMon(&boxMon, species, 100, 32, FALSE, 0, OT_ID_PLAYER_ID, 0);

                if (species < SPECIES_CELEBI)
                    species += 1;
                else if (species == SPECIES_CELEBI)
                    species = SPECIES_TREECKO;
                else if (species < SPECIES_CHIMECHO)
                    species += 1;
                else
                    species = 1;

                gPokemonStoragePtr->boxes[boxId][boxPosition] = boxMon;
            }
        }
    }

    // Set flag for user convenience
    FlagSet(FLAG_SYS_POKEMON_GET);

    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();
}

static void DebugAction_PC_FillItemStorage(u8 taskId)
{
    u16 itemId;

    for (itemId = 1; itemId < ITEMS_COUNT; itemId++)
    {
        if (!CheckPCHasItem(itemId, MAX_PC_ITEM_CAPACITY))
            AddPCItem(itemId, MAX_PC_ITEM_CAPACITY);
    }

    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();
}

static void DebugAction_PC_Clear(u8 taskId)
{
    PlaySE(SE_EXIT);

    ResetPokemonStorageSystem();

    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();
}

// *******************************
// Sound menu functions
static const u8 *const sBGMNames[];
static const u8 *const sSENames[];

#define tCurrentSong  data[5]

static void DebugAction_Sound_SE(u8 taskId)
{
    u8 windowId;

    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateSound);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    // Display initial sound effect
    StringCopy(gStringVar2, gText_DigitIndicator[0]);
    ConvertIntToDecimalStringN(gStringVar3, 1, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_ITEMS);
    StringCopyPadded(gStringVar1, sSENames[0], CHAR_SPACE, 35);
    StringExpandPlaceholders(gStringVar4, sDebugText_Sound_SE_ID);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);

    StopMapMusic(); //Stop map music to better hear sounds

    gTasks[taskId].func = DebugAction_Sound_SE_SelectId;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = 1;
    gTasks[taskId].tDigit = 0;
    gTasks[taskId].tCurrentSong = gTasks[taskId].tInput;
}

static void DebugAction_Sound_SE_SelectId(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        Debug_HandleInput_Numeric(taskId, 1, END_SE, DEBUG_NUMBER_DIGITS_ITEMS);

        StringCopy(gStringVar2, gText_DigitIndicator[gTasks[taskId].tDigit]);
        StringCopyPadded(gStringVar1, sSENames[gTasks[taskId].tInput - 1], CHAR_SPACE, 35);
        ConvertIntToDecimalStringN(gStringVar3, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_ITEMS);
        StringExpandPlaceholders(gStringVar4, sDebugText_Sound_SE_ID);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }

    if (JOY_NEW(A_BUTTON))
    {
        m4aSongNumStop(gTasks[taskId].tCurrentSong);
        gTasks[taskId].tCurrentSong = gTasks[taskId].tInput;
        m4aSongNumStart(gTasks[taskId].tInput);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        m4aSongNumStop(gTasks[taskId].tCurrentSong);
        Overworld_PlaySpecialMapMusic();
        DebugAction_DestroyExtraWindow(taskId);
    }
    else if (JOY_NEW(START_BUTTON))
    {
        m4aSongNumStop(gTasks[taskId].tCurrentSong);
    }
}

static void DebugAction_Sound_Music(u8 taskId)
{
    u8 windowId;

    ClearStdWindowAndFrame(gTasks[taskId].tWindowId, TRUE);
    RemoveWindow(gTasks[taskId].tWindowId);

    HideMapNamePopUpWindow();
    LoadMessageBoxAndBorderGfx();
    windowId = AddWindow(&sDebugMenuWindowTemplateSound);
    DrawStdWindowFrame(windowId, FALSE);

    CopyWindowToVram(windowId, COPYWIN_FULL);

    // Display initial song
    StringCopy(gStringVar2, gText_DigitIndicator[0]);
    ConvertIntToDecimalStringN(gStringVar3, START_MUS, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_ITEMS);
    StringCopyPadded(gStringVar1, sBGMNames[0], CHAR_SPACE, 35);
    StringExpandPlaceholders(gStringVar4, sDebugText_Sound_Music_ID);
    AddTextPrinterParameterized(windowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);

    StopMapMusic(); //Stop map music to better hear new music

    gTasks[taskId].func = DebugAction_Sound_Music_SelectId;
    gTasks[taskId].tSubWindowId = windowId;
    gTasks[taskId].tInput = START_MUS;
    gTasks[taskId].tDigit = 0;
    gTasks[taskId].tCurrentSong = gTasks[taskId].tInput;
}

static void DebugAction_Sound_Music_SelectId(u8 taskId)
{
    if (JOY_NEW(DPAD_ANY))
    {
        Debug_HandleInput_Numeric(taskId, START_MUS, END_MUS, DEBUG_NUMBER_DIGITS_ITEMS);

        StringCopy(gStringVar2, gText_DigitIndicator[gTasks[taskId].tDigit]);
        StringCopyPadded(gStringVar1, sBGMNames[gTasks[taskId].tInput - START_MUS], CHAR_SPACE, 35);
        ConvertIntToDecimalStringN(gStringVar3, gTasks[taskId].tInput, STR_CONV_MODE_LEADING_ZEROS, DEBUG_NUMBER_DIGITS_ITEMS);
        StringExpandPlaceholders(gStringVar4, sDebugText_Sound_Music_ID);
        AddTextPrinterParameterized(gTasks[taskId].tSubWindowId, DEBUG_MENU_FONT, gStringVar4, 0, 0, 0, NULL);
    }

    if (JOY_NEW(A_BUTTON))
    {
        m4aSongNumStop(gTasks[taskId].tCurrentSong);
        gTasks[taskId].tCurrentSong = gTasks[taskId].tInput;
        m4aSongNumStart(gTasks[taskId].tInput);
    }
    else if (JOY_NEW(B_BUTTON))
    {
        PlaySE(SE_SELECT);
        m4aSongNumStop(gTasks[taskId].tCurrentSong);
        Overworld_PlaySpecialMapMusic();
        DebugAction_DestroyExtraWindow(taskId);
    }
    else if (JOY_NEW(START_BUTTON))
    {
        m4aSongNumStop(gTasks[taskId].tCurrentSong);
    }
}

#undef tCurrentSong

#undef tMenuTaskId
#undef tWindowId
#undef tSubWindowId
#undef tInput
#undef tDigit

static void DebugAction_Sound_ToggleMapMusic(u8 taskId)
{
    if (GetCurrentMapMusic() == 0)
    {
        Overworld_PlaySpecialMapMusic();
    }
    else
    {
        StopMapMusic();
    }

    Debug_DestroyMenu_Full(taskId);
    ScriptContext_Enable();    
}

#define SOUND_LIST_BGM \
    X(MUS_LITTLEROOT_TEST, "MUS-LITTLEROOT-TEST") \
    X(MUS_GSC_ROUTE38, "MUS-GSC-ROUTE38") \
    X(MUS_CAUGHT, "MUS-CAUGHT") \
    X(MUS_VICTORY_WILD, "MUS-VICTORY-WILD") \
    X(MUS_VICTORY_GYM_LEADER, "MUS-VICTORY-GYM-LEADER") \
    X(MUS_VICTORY_LEAGUE, "MUS-VICTORY-LEAGUE") \
    X(MUS_C_COMM_CENTER, "MUS-C-COMM-CENTER") \
    X(MUS_GSC_PEWTER, "MUS-GSC-PEWTER") \
    X(MUS_C_VS_LEGEND_BEAST, "MUS-C-VS-LEGEND-BEAST") \
    X(MUS_ROUTE101, "MUS-ROUTE101") \
    X(MUS_ROUTE110, "MUS-ROUTE110") \
    X(MUS_ROUTE120, "MUS-ROUTE120") \
    X(MUS_PETALBURG, "MUS-PETALBURG") \
    X(MUS_OLDALE, "MUS-OLDALE") \
    X(MUS_GYM, "MUS-GYM") \
    X(MUS_SURF, "MUS-SURF") \
    X(MUS_PETALBURG_WOODS, "MUS-PETALBURG-WOODS") \
    X(MUS_LEVEL_UP, "MUS-LEVEL-UP") \
    X(MUS_HEAL, "MUS-HEAL") \
    X(MUS_OBTAIN_BADGE, "MUS-OBTAIN-BADGE") \
    X(MUS_OBTAIN_ITEM, "MUS-OBTAIN-ITEM") \
    X(MUS_EVOLVED, "MUS-EVOLVED") \
    X(MUS_OBTAIN_TMHM, "MUS-OBTAIN-TMHM") \
    X(MUS_LILYCOVE_MUSEUM, "MUS-LILYCOVE-MUSEUM") \
    X(MUS_ROUTE122, "MUS-ROUTE122") \
    X(MUS_OCEANIC_MUSEUM, "MUS-OCEANIC-MUSEUM") \
    X(MUS_EVOLUTION_INTRO, "MUS-EVOLUTION-INTRO") \
    X(MUS_EVOLUTION, "MUS-EVOLUTION") \
    X(MUS_MOVE_DELETED, "MUS-MOVE-DELETED") \
    X(MUS_ENCOUNTER_GIRL, "MUS-ENCOUNTER-GIRL") \
    X(MUS_ENCOUNTER_MALE, "MUS-ENCOUNTER-MALE") \
    X(MUS_ABANDONED_SHIP, "MUS-ABANDONED-SHIP") \
    X(MUS_FORTREE, "MUS-FORTREE") \
    X(MUS_BIRCH_LAB, "MUS-BIRCH-LAB") \
    X(MUS_B_TOWER_RS, "MUS-B-TOWER-RS") \
    X(MUS_ENCOUNTER_SWIMMER, "MUS-ENCOUNTER-SWIMMER") \
    X(MUS_CAVE_OF_ORIGIN, "MUS-CAVE-OF-ORIGIN") \
    X(MUS_OBTAIN_BERRY, "MUS-OBTAIN-BERRY") \
    X(MUS_AWAKEN_LEGEND, "MUS-AWAKEN-LEGEND") \
    X(MUS_SLOTS_JACKPOT, "MUS-SLOTS-JACKPOT") \
    X(MUS_SLOTS_WIN, "MUS-SLOTS-WIN") \
    X(MUS_TOO_BAD, "MUS-TOO-BAD") \
    X(MUS_ROULETTE, "MUS-ROULETTE") \
    X(MUS_LINK_CONTEST_P1, "MUS-LINK-CONTEST-P1") \
    X(MUS_LINK_CONTEST_P2, "MUS-LINK-CONTEST-P2") \
    X(MUS_LINK_CONTEST_P3, "MUS-LINK-CONTEST-P3") \
    X(MUS_LINK_CONTEST_P4, "MUS-LINK-CONTEST-P4") \
    X(MUS_ENCOUNTER_RICH, "MUS-ENCOUNTER-RICH") \
    X(MUS_VERDANTURF, "MUS-VERDANTURF") \
    X(MUS_RUSTBORO, "MUS-RUSTBORO") \
    X(MUS_POKE_CENTER, "MUS-POKE-CENTER") \
    X(MUS_ROUTE104, "MUS-ROUTE104") \
    X(MUS_ROUTE119, "MUS-ROUTE119") \
    X(MUS_CYCLING, "MUS-CYCLING") \
    X(MUS_POKE_MART, "MUS-POKE-MART") \
    X(MUS_LITTLEROOT, "MUS-LITTLEROOT") \
    X(MUS_MT_CHIMNEY, "MUS-MT-CHIMNEY") \
    X(MUS_ENCOUNTER_FEMALE, "MUS-ENCOUNTER-FEMALE") \
    X(MUS_LILYCOVE, "MUS-LILYCOVE") \
    X(MUS_ROUTE111, "MUS-ROUTE111") \
    X(MUS_HELP, "MUS-HELP") \
    X(MUS_UNDERWATER, "MUS-UNDERWATER") \
    X(MUS_VICTORY_TRAINER, "MUS-VICTORY-TRAINER") \
    X(MUS_TITLE, "MUS-TITLE") \
    X(MUS_INTRO, "MUS-INTRO") \
    X(MUS_ENCOUNTER_MAY, "MUS-ENCOUNTER-MAY") \
    X(MUS_ENCOUNTER_INTENSE, "MUS-ENCOUNTER-INTENSE") \
    X(MUS_ENCOUNTER_COOL, "MUS-ENCOUNTER-COOL") \
    X(MUS_ROUTE113, "MUS-ROUTE113") \
    X(MUS_ENCOUNTER_AQUA, "MUS-ENCOUNTER-AQUA") \
    X(MUS_FOLLOW_ME, "MUS-FOLLOW-ME") \
    X(MUS_ENCOUNTER_BRENDAN, "MUS-ENCOUNTER-BRENDAN") \
    X(MUS_EVER_GRANDE, "MUS-EVER-GRANDE") \
    X(MUS_ENCOUNTER_SUSPICIOUS, "MUS-ENCOUNTER-SUSPICIOUS") \
    X(MUS_VICTORY_AQUA_MAGMA, "MUS-VICTORY-AQUA-MAGMA") \
    X(MUS_CABLE_CAR, "MUS-CABLE-CAR") \
    X(MUS_GAME_CORNER, "MUS-GAME-CORNER") \
    X(MUS_DEWFORD, "MUS-DEWFORD") \
    X(MUS_SAFARI_ZONE, "MUS-SAFARI-ZONE") \
    X(MUS_VICTORY_ROAD, "MUS-VICTORY-ROAD") \
    X(MUS_AQUA_MAGMA_HIDEOUT, "MUS-AQUA-MAGMA-HIDEOUT") \
    X(MUS_SAILING, "MUS-SAILING") \
    X(MUS_MT_PYRE, "MUS-MT-PYRE") \
    X(MUS_SLATEPORT, "MUS-SLATEPORT") \
    X(MUS_MT_PYRE_EXTERIOR, "MUS-MT-PYRE-EXTERIOR") \
    X(MUS_SCHOOL, "MUS-SCHOOL") \
    X(MUS_HALL_OF_FAME, "MUS-HALL-OF-FAME") \
    X(MUS_FALLARBOR, "MUS-FALLARBOR") \
    X(MUS_SEALED_CHAMBER, "MUS-SEALED-CHAMBER") \
    X(MUS_CONTEST_WINNER, "MUS-CONTEST-WINNER") \
    X(MUS_CONTEST, "MUS-CONTEST") \
    X(MUS_ENCOUNTER_MAGMA, "MUS-ENCOUNTER-MAGMA") \
    X(MUS_INTRO_BATTLE, "MUS-INTRO-BATTLE") \
    X(MUS_WEATHER_KYOGRE, "MUS-WEATHER-KYOGRE") \
    X(MUS_WEATHER_GROUDON, "MUS-WEATHER-GROUDON") \
    X(MUS_SOOTOPOLIS, "MUS-SOOTOPOLIS") \
    X(MUS_CONTEST_RESULTS, "MUS-CONTEST-RESULTS") \
    X(MUS_HALL_OF_FAME_ROOM, "MUS-HALL-OF-FAME-ROOM") \
    X(MUS_TRICK_HOUSE, "MUS-TRICK-HOUSE") \
    X(MUS_ENCOUNTER_TWINS, "MUS-ENCOUNTER-TWINS") \
    X(MUS_ENCOUNTER_ELITE_FOUR, "MUS-ENCOUNTER-ELITE-FOUR") \
    X(MUS_ENCOUNTER_HIKER, "MUS-ENCOUNTER-HIKER") \
    X(MUS_CONTEST_LOBBY, "MUS-CONTEST-LOBBY") \
    X(MUS_ENCOUNTER_INTERVIEWER, "MUS-ENCOUNTER-INTERVIEWER") \
    X(MUS_ENCOUNTER_CHAMPION, "MUS-ENCOUNTER-CHAMPION") \
    X(MUS_CREDITS, "MUS-CREDITS") \
    X(MUS_END, "MUS-END") \
    X(MUS_B_FRONTIER, "MUS-B-FRONTIER") \
    X(MUS_B_ARENA, "MUS-B-ARENA") \
    X(MUS_OBTAIN_B_POINTS, "MUS-OBTAIN-B-POINTS") \
    X(MUS_REGISTER_MATCH_CALL, "MUS-REGISTER-MATCH-CALL") \
    X(MUS_B_PYRAMID, "MUS-B-PYRAMID") \
    X(MUS_B_PYRAMID_TOP, "MUS-B-PYRAMID-TOP") \
    X(MUS_B_PALACE, "MUS-B-PALACE") \
    X(MUS_RAYQUAZA_APPEARS, "MUS-RAYQUAZA-APPEARS") \
    X(MUS_B_TOWER, "MUS-B-TOWER") \
    X(MUS_OBTAIN_SYMBOL, "MUS-OBTAIN-SYMBOL") \
    X(MUS_B_DOME, "MUS-B-DOME") \
    X(MUS_B_PIKE, "MUS-B-PIKE") \
    X(MUS_B_FACTORY, "MUS-B-FACTORY") \
    X(MUS_VS_RAYQUAZA, "MUS-VS-RAYQUAZA") \
    X(MUS_VS_FRONTIER_BRAIN, "MUS-VS-FRONTIER-BRAIN") \
    X(MUS_VS_MEW, "MUS-VS-MEW") \
    X(MUS_B_DOME_LOBBY, "MUS-B-DOME-LOBBY") \
    X(MUS_VS_WILD, "MUS-VS-WILD") \
    X(MUS_VS_AQUA_MAGMA, "MUS-VS-AQUA-MAGMA") \
    X(MUS_VS_TRAINER, "MUS-VS-TRAINER") \
    X(MUS_VS_GYM_LEADER, "MUS-VS-GYM-LEADER") \
    X(MUS_VS_CHAMPION, "MUS-VS-CHAMPION") \
    X(MUS_VS_REGI, "MUS-VS-REGI") \
    X(MUS_VS_KYOGRE_GROUDON, "MUS-VS-KYOGRE-GROUDON") \
    X(MUS_VS_RIVAL, "MUS-VS-RIVAL") \
    X(MUS_VS_ELITE_FOUR, "MUS-VS-ELITE-FOUR") \
    X(MUS_VS_AQUA_MAGMA_LEADER, "MUS-VS-AQUA-MAGMA-LEADER") \
    X(MUS_RG_FOLLOW_ME, "MUS-RG-FOLLOW-ME") \
    X(MUS_RG_GAME_CORNER, "MUS-RG-GAME-CORNER") \
    X(MUS_RG_ROCKET_HIDEOUT, "MUS-RG-ROCKET-HIDEOUT") \
    X(MUS_RG_GYM, "MUS-RG-GYM") \
    X(MUS_RG_JIGGLYPUFF, "MUS-RG-JIGGLYPUFF") \
    X(MUS_RG_INTRO_FIGHT, "MUS-RG-INTRO-FIGHT") \
    X(MUS_RG_TITLE, "MUS-RG-TITLE") \
    X(MUS_RG_CINNABAR, "MUS-RG-CINNABAR") \
    X(MUS_RG_LAVENDER, "MUS-RG-LAVENDER") \
    X(MUS_RG_HEAL, "MUS-RG-HEAL") \
    X(MUS_RG_CYCLING, "MUS-RG-CYCLING") \
    X(MUS_RG_ENCOUNTER_ROCKET, "MUS-RG-ENCOUNTER-ROCKET") \
    X(MUS_RG_ENCOUNTER_GIRL, "MUS-RG-ENCOUNTER-GIRL") \
    X(MUS_RG_ENCOUNTER_BOY, "MUS-RG-ENCOUNTER-BOY") \
    X(MUS_RG_HALL_OF_FAME, "MUS-RG-HALL-OF-FAME") \
    X(MUS_RG_VIRIDIAN_FOREST, "MUS-RG-VIRIDIAN-FOREST") \
    X(MUS_RG_MT_MOON, "MUS-RG-MT-MOON") \
    X(MUS_RG_POKE_MANSION, "MUS-RG-POKE-MANSION") \
    X(MUS_RG_CREDITS, "MUS-RG-CREDITS") \
    X(MUS_RG_ROUTE1, "MUS-RG-ROUTE1") \
    X(MUS_RG_ROUTE24, "MUS-RG-ROUTE24") \
    X(MUS_RG_ROUTE3, "MUS-RG-ROUTE3") \
    X(MUS_RG_ROUTE11, "MUS-RG-ROUTE11") \
    X(MUS_RG_VICTORY_ROAD, "MUS-RG-VICTORY-ROAD") \
    X(MUS_RG_VS_GYM_LEADER, "MUS-RG-VS-GYM-LEADER") \
    X(MUS_RG_VS_TRAINER, "MUS-RG-VS-TRAINER") \
    X(MUS_RG_VS_WILD, "MUS-RG-VS-WILD") \
    X(MUS_RG_VS_CHAMPION, "MUS-RG-VS-CHAMPION") \
    X(MUS_RG_PALLET, "MUS-RG-PALLET") \
    X(MUS_RG_OAK_LAB, "MUS-RG-OAK-LAB") \
    X(MUS_RG_OAK, "MUS-RG-OAK") \
    X(MUS_RG_POKE_CENTER, "MUS-RG-POKE-CENTER") \
    X(MUS_RG_SS_ANNE, "MUS-RG-SS-ANNE") \
    X(MUS_RG_SURF, "MUS-RG-SURF") \
    X(MUS_RG_POKE_TOWER, "MUS-RG-POKE-TOWER") \
    X(MUS_RG_SILPH, "MUS-RG-SILPH") \
    X(MUS_RG_FUCHSIA, "MUS-RG-FUCHSIA") \
    X(MUS_RG_CELADON, "MUS-RG-CELADON") \
    X(MUS_RG_VICTORY_TRAINER, "MUS-RG-VICTORY-TRAINER") \
    X(MUS_RG_VICTORY_WILD, "MUS-RG-VICTORY-WILD") \
    X(MUS_RG_VICTORY_GYM_LEADER, "MUS-RG-VICTORY-GYM-LEADER") \
    X(MUS_RG_VERMILLION, "MUS-RG-VERMILLION") \
    X(MUS_RG_PEWTER, "MUS-RG-PEWTER") \
    X(MUS_RG_ENCOUNTER_RIVAL, "MUS-RG-ENCOUNTER-RIVAL") \
    X(MUS_RG_RIVAL_EXIT, "MUS-RG-RIVAL-EXIT") \
    X(MUS_RG_DEX_RATING, "MUS-RG-DEX-RATING") \
    X(MUS_RG_OBTAIN_KEY_ITEM, "MUS-RG-OBTAIN-KEY-ITEM") \
    X(MUS_RG_CAUGHT_INTRO, "MUS-RG-CAUGHT-INTRO") \
    X(MUS_RG_PHOTO, "MUS-RG-PHOTO") \
    X(MUS_RG_GAME_FREAK, "MUS-RG-GAME-FREAK") \
    X(MUS_RG_CAUGHT, "MUS-RG-CAUGHT") \
    X(MUS_RG_NEW_GAME_INSTRUCT, "MUS-RG-NEW-GAME-INSTRUCT") \
    X(MUS_RG_NEW_GAME_INTRO, "MUS-RG-NEW-GAME-INTRO") \
    X(MUS_RG_NEW_GAME_EXIT, "MUS-RG-NEW-GAME-EXIT") \
    X(MUS_RG_POKE_JUMP, "MUS-RG-POKE-JUMP") \
    X(MUS_RG_UNION_ROOM, "MUS-RG-UNION-ROOM") \
    X(MUS_RG_NET_CENTER, "MUS-RG-NET-CENTER") \
    X(MUS_RG_MYSTERY_GIFT, "MUS-RG-MYSTERY-GIFT") \
    X(MUS_RG_BERRY_PICK, "MUS-RG-BERRY-PICK") \
    X(MUS_RG_SEVII_CAVE, "MUS-RG-SEVII-CAVE") \
    X(MUS_RG_TEACHY_TV_SHOW, "MUS-RG-TEACHY-TV-SHOW") \
    X(MUS_RG_SEVII_ROUTE, "MUS-RG-SEVII-ROUTE") \
    X(MUS_RG_SEVII_DUNGEON, "MUS-RG-SEVII-DUNGEON") \
    X(MUS_RG_SEVII_123, "MUS-RG-SEVII-123") \
    X(MUS_RG_SEVII_45, "MUS-RG-SEVII-45") \
    X(MUS_RG_SEVII_67, "MUS-RG-SEVII-67") \
    X(MUS_RG_POKE_FLUTE, "MUS-RG-POKE-FLUTE") \
    X(MUS_RG_VS_DEOXYS, "MUS-RG-VS-DEOXYS") \
    X(MUS_RG_VS_MEWTWO, "MUS-RG-VS-MEWTWO") \
    X(MUS_RG_VS_LEGEND, "MUS-RG-VS-LEGEND") \
    X(MUS_RG_ENCOUNTER_GYM_LEADER, "MUS-RG-ENCOUNTER-GYM-LEADER") \
    X(MUS_RG_ENCOUNTER_DEOXYS, "MUS-RG-ENCOUNTER-DEOXYS") \
    X(MUS_RG_TRAINER_TOWER, "MUS-RG-TRAINER-TOWER") \
    X(MUS_RG_SLOW_PALLET, "MUS-RG-SLOW-PALLET") \
    X(MUS_RG_TEACHY_TV_MENU, "MUS-RG-TEACHY-TV-MENU") \
    X(PH_TRAP_BLEND, "PH-TRAP-BLEND") \
    X(PH_TRAP_HELD, "PH-TRAP-HELD") \
    X(PH_TRAP_SOLO, "PH-TRAP-SOLO") \
    X(PH_FACE_BLEND, "PH-FACE-BLEND") \
    X(PH_FACE_HELD, "PH-FACE-HELD") \
    X(PH_FACE_SOLO, "PH-FACE-SOLO") \
    X(PH_CLOTH_BLEND, "PH-CLOTH-BLEND") \
    X(PH_CLOTH_HELD, "PH-CLOTH-HELD") \
    X(PH_CLOTH_SOLO, "PH-CLOTH-SOLO") \
    X(PH_DRESS_BLEND, "PH-DRESS-BLEND") \
    X(PH_DRESS_HELD, "PH-DRESS-HELD") \
    X(PH_DRESS_SOLO, "PH-DRESS-SOLO") \
    X(PH_FLEECE_BLEND, "PH-FLEECE-BLEND") \
    X(PH_FLEECE_HELD, "PH-FLEECE-HELD") \
    X(PH_FLEECE_SOLO, "PH-FLEECE-SOLO") \
    X(PH_KIT_BLEND, "PH-KIT-BLEND") \
    X(PH_KIT_HELD, "PH-KIT-HELD") \
    X(PH_KIT_SOLO, "PH-KIT-SOLO") \
    X(PH_PRICE_BLEND, "PH-PRICE-BLEND") \
    X(PH_PRICE_HELD, "PH-PRICE-HELD") \
    X(PH_PRICE_SOLO, "PH-PRICE-SOLO") \
    X(PH_LOT_BLEND, "PH-LOT-BLEND") \
    X(PH_LOT_HELD, "PH-LOT-HELD") \
    X(PH_LOT_SOLO, "PH-LOT-SOLO") \
    X(PH_GOAT_BLEND, "PH-GOAT-BLEND") \
    X(PH_GOAT_HELD, "PH-GOAT-HELD") \
    X(PH_GOAT_SOLO, "PH-GOAT-SOLO") \
    X(PH_THOUGHT_BLEND, "PH-THOUGHT-BLEND") \
    X(PH_THOUGHT_HELD, "PH-THOUGHT-HELD") \
    X(PH_THOUGHT_SOLO, "PH-THOUGHT-SOLO") \
    X(PH_CHOICE_BLEND, "PH-CHOICE-BLEND") \
    X(PH_CHOICE_HELD, "PH-CHOICE-HELD") \
    X(PH_CHOICE_SOLO, "PH-CHOICE-SOLO") \
    X(PH_MOUTH_BLEND, "PH-MOUTH-BLEND") \
    X(PH_MOUTH_HELD, "PH-MOUTH-HELD") \
    X(PH_MOUTH_SOLO, "PH-MOUTH-SOLO") \
    X(PH_FOOT_BLEND, "PH-FOOT-BLEND") \
    X(PH_FOOT_HELD, "PH-FOOT-HELD") \
    X(PH_FOOT_SOLO, "PH-FOOT-SOLO") \
    X(PH_GOOSE_BLEND, "PH-GOOSE-BLEND") \
    X(PH_GOOSE_HELD, "PH-GOOSE-HELD") \
    X(PH_GOOSE_SOLO, "PH-GOOSE-SOLO") \
    X(PH_STRUT_BLEND, "PH-STRUT-BLEND") \
    X(PH_STRUT_HELD, "PH-STRUT-HELD") \
    X(PH_STRUT_SOLO, "PH-STRUT-SOLO") \
    X(PH_CURE_BLEND, "PH-CURE-BLEND") \
    X(PH_CURE_HELD, "PH-CURE-HELD") \
    X(PH_CURE_SOLO, "PH-CURE-SOLO") \
    X(PH_NURSE_BLEND, "PH-NURSE-BLEND") \
    X(PH_NURSE_HELD, "PH-NURSE-HELD") \
    X(PH_NURSE_SOLO, "PH-NURSE-SOLO") \

#define SOUND_LIST_SE \
    X(SE_USE_ITEM, "SE-USE-ITEM") \
    X(SE_PC_LOGIN, "SE-PC-LOGIN") \
    X(SE_PC_OFF, "SE-PC-OFF") \
    X(SE_PC_ON, "SE-PC-ON") \
    X(SE_SELECT, "SE-SELECT") \
    X(SE_WIN_OPEN, "SE-WIN-OPEN") \
    X(SE_WALL_HIT, "SE-WALL-HIT") \
    X(SE_DOOR, "SE-DOOR") \
    X(SE_EXIT, "SE-EXIT") \
    X(SE_LEDGE, "SE-LEDGE") \
    X(SE_BIKE_BELL, "SE-BIKE-BELL") \
    X(SE_NOT_EFFECTIVE, "SE-NOT-EFFECTIVE") \
    X(SE_EFFECTIVE, "SE-EFFECTIVE") \
    X(SE_SUPER_EFFECTIVE, "SE-SUPER-EFFECTIVE") \
    X(SE_BALL_OPEN, "SE-BALL-OPEN") \
    X(SE_FAINT, "SE-FAINT") \
    X(SE_FLEE, "SE-FLEE") \
    X(SE_SLIDING_DOOR, "SE-SLIDING-DOOR") \
    X(SE_SHIP, "SE-SHIP") \
    X(SE_BANG, "SE-BANG") \
    X(SE_PIN, "SE-PIN") \
    X(SE_BOO, "SE-BOO") \
    X(SE_BALL, "SE-BALL") \
    X(SE_CONTEST_PLACE, "SE-CONTEST-PLACE") \
    X(SE_A, "SE-A") \
    X(SE_I, "SE-I") \
    X(SE_U, "SE-U") \
    X(SE_E, "SE-E") \
    X(SE_O, "SE-O") \
    X(SE_N, "SE-N") \
    X(SE_SUCCESS, "SE-SUCCESS") \
    X(SE_FAILURE, "SE-FAILURE") \
    X(SE_EXP, "SE-EXP") \
    X(SE_BIKE_HOP, "SE-BIKE-HOP") \
    X(SE_SWITCH, "SE-SWITCH") \
    X(SE_CLICK, "SE-CLICK") \
    X(SE_FU_ZAKU, "SE-FU-ZAKU") \
    X(SE_CONTEST_CONDITION_LOSE, "SE-CONTEST-CONDITION-LOSE") \
    X(SE_LAVARIDGE_FALL_WARP, "SE-LAVARIDGE-FALL-WARP") \
    X(SE_ICE_STAIRS, "SE-ICE-STAIRS") \
    X(SE_ICE_BREAK, "SE-ICE-BREAK") \
    X(SE_ICE_CRACK, "SE-ICE-CRACK") \
    X(SE_FALL, "SE-FALL") \
    X(SE_UNLOCK, "SE-UNLOCK") \
    X(SE_WARP_IN, "SE-WARP-IN") \
    X(SE_WARP_OUT, "SE-WARP-OUT") \
    X(SE_REPEL, "SE-REPEL") \
    X(SE_ROTATING_GATE, "SE-ROTATING-GATE") \
    X(SE_TRUCK_MOVE, "SE-TRUCK-MOVE") \
    X(SE_TRUCK_STOP, "SE-TRUCK-STOP") \
    X(SE_TRUCK_UNLOAD, "SE-TRUCK-UNLOAD") \
    X(SE_TRUCK_DOOR, "SE-TRUCK-DOOR") \
    X(SE_BERRY_BLENDER, "SE-BERRY-BLENDER") \
    X(SE_CARD, "SE-CARD") \
    X(SE_SAVE, "SE-SAVE") \
    X(SE_BALL_BOUNCE_1, "SE-BALL-BOUNCE-1") \
    X(SE_BALL_BOUNCE_2, "SE-BALL-BOUNCE-2") \
    X(SE_BALL_BOUNCE_3, "SE-BALL-BOUNCE-3") \
    X(SE_BALL_BOUNCE_4, "SE-BALL-BOUNCE-4") \
    X(SE_BALL_TRADE, "SE-BALL-TRADE") \
    X(SE_BALL_THROW, "SE-BALL-THROW") \
    X(SE_NOTE_C, "SE-NOTE-C") \
    X(SE_NOTE_D, "SE-NOTE-D") \
    X(SE_NOTE_E, "SE-NOTE-E") \
    X(SE_NOTE_F, "SE-NOTE-F") \
    X(SE_NOTE_G, "SE-NOTE-G") \
    X(SE_NOTE_A, "SE-NOTE-A") \
    X(SE_NOTE_B, "SE-NOTE-B") \
    X(SE_NOTE_C_HIGH, "SE-NOTE-C-HIGH") \
    X(SE_PUDDLE, "SE-PUDDLE") \
    X(SE_BRIDGE_WALK, "SE-BRIDGE-WALK") \
    X(SE_ITEMFINDER, "SE-ITEMFINDER") \
    X(SE_DING_DONG, "SE-DING-DONG") \
    X(SE_BALLOON_RED, "SE-BALLOON-RED") \
    X(SE_BALLOON_BLUE, "SE-BALLOON-BLUE") \
    X(SE_BALLOON_YELLOW, "SE-BALLOON-YELLOW") \
    X(SE_BREAKABLE_DOOR, "SE-BREAKABLE-DOOR") \
    X(SE_MUD_BALL, "SE-MUD-BALL") \
    X(SE_FIELD_POISON, "SE-FIELD-POISON") \
    X(SE_ESCALATOR, "SE-ESCALATOR") \
    X(SE_THUNDERSTORM, "SE-THUNDERSTORM") \
    X(SE_THUNDERSTORM_STOP, "SE-THUNDERSTORM-STOP") \
    X(SE_DOWNPOUR, "SE-DOWNPOUR") \
    X(SE_DOWNPOUR_STOP, "SE-DOWNPOUR-STOP") \
    X(SE_RAIN, "SE-RAIN") \
    X(SE_RAIN_STOP, "SE-RAIN-STOP") \
    X(SE_THUNDER, "SE-THUNDER") \
    X(SE_THUNDER2, "SE-THUNDER2") \
    X(SE_ELEVATOR, "SE-ELEVATOR") \
    X(SE_LOW_HEALTH, "SE-LOW-HEALTH") \
    X(SE_EXP_MAX, "SE-EXP-MAX") \
    X(SE_ROULETTE_BALL, "SE-ROULETTE-BALL") \
    X(SE_ROULETTE_BALL2, "SE-ROULETTE-BALL2") \
    X(SE_TAILLOW_WING_FLAP, "SE-TAILLOW-WING-FLAP") \
    X(SE_SHOP, "SE-SHOP") \
    X(SE_CONTEST_HEART, "SE-CONTEST-HEART") \
    X(SE_CONTEST_CURTAIN_RISE, "SE-CONTEST-CURTAIN-RISE") \
    X(SE_CONTEST_CURTAIN_FALL, "SE-CONTEST-CURTAIN-FALL") \
    X(SE_CONTEST_ICON_CHANGE, "SE-CONTEST-ICON-CHANGE") \
    X(SE_CONTEST_ICON_CLEAR, "SE-CONTEST-ICON-CLEAR") \
    X(SE_CONTEST_MONS_TURN, "SE-CONTEST-MONS-TURN") \
    X(SE_SHINY, "SE-SHINY") \
    X(SE_INTRO_BLAST, "SE-INTRO-BLAST") \
    X(SE_MUGSHOT, "SE-MUGSHOT") \
    X(SE_APPLAUSE, "SE-APPLAUSE") \
    X(SE_VEND, "SE-VEND") \
    X(SE_ORB, "SE-ORB") \
    X(SE_DEX_SCROLL, "SE-DEX-SCROLL") \
    X(SE_DEX_PAGE, "SE-DEX-PAGE") \
    X(SE_POKENAV_ON, "SE-POKENAV-ON") \
    X(SE_POKENAV_OFF, "SE-POKENAV-OFF") \
    X(SE_DEX_SEARCH, "SE-DEX-SEARCH") \
    X(SE_EGG_HATCH, "SE-EGG-HATCH") \
    X(SE_BALL_TRAY_ENTER, "SE-BALL-TRAY-ENTER") \
    X(SE_BALL_TRAY_BALL, "SE-BALL-TRAY-BALL") \
    X(SE_BALL_TRAY_EXIT, "SE-BALL-TRAY-EXIT") \
    X(SE_GLASS_FLUTE, "SE-GLASS-FLUTE") \
    X(SE_M_THUNDERBOLT, "SE-M-THUNDERBOLT") \
    X(SE_M_THUNDERBOLT2, "SE-M-THUNDERBOLT2") \
    X(SE_M_HARDEN, "SE-M-HARDEN") \
    X(SE_M_NIGHTMARE, "SE-M-NIGHTMARE") \
    X(SE_M_VITAL_THROW, "SE-M-VITAL-THROW") \
    X(SE_M_VITAL_THROW2, "SE-M-VITAL-THROW2") \
    X(SE_M_BUBBLE, "SE-M-BUBBLE") \
    X(SE_M_BUBBLE2, "SE-M-BUBBLE2") \
    X(SE_M_BUBBLE3, "SE-M-BUBBLE3") \
    X(SE_M_RAIN_DANCE, "SE-M-RAIN-DANCE") \
    X(SE_M_CUT, "SE-M-CUT") \
    X(SE_M_STRING_SHOT, "SE-M-STRING-SHOT") \
    X(SE_M_STRING_SHOT2, "SE-M-STRING-SHOT2") \
    X(SE_M_ROCK_THROW, "SE-M-ROCK-THROW") \
    X(SE_M_GUST, "SE-M-GUST") \
    X(SE_M_GUST2, "SE-M-GUST2") \
    X(SE_M_DOUBLE_SLAP, "SE-M-DOUBLE-SLAP") \
    X(SE_M_DOUBLE_TEAM, "SE-M-DOUBLE-TEAM") \
    X(SE_M_RAZOR_WIND, "SE-M-RAZOR-WIND") \
    X(SE_M_ICY_WIND, "SE-M-ICY-WIND") \
    X(SE_M_THUNDER_WAVE, "SE-M-THUNDER-WAVE") \
    X(SE_M_COMET_PUNCH, "SE-M-COMET-PUNCH") \
    X(SE_M_MEGA_KICK, "SE-M-MEGA-KICK") \
    X(SE_M_MEGA_KICK2, "SE-M-MEGA-KICK2") \
    X(SE_M_CRABHAMMER, "SE-M-CRABHAMMER") \
    X(SE_M_JUMP_KICK, "SE-M-JUMP-KICK") \
    X(SE_M_FLAME_WHEEL, "SE-M-FLAME-WHEEL") \
    X(SE_M_FLAME_WHEEL2, "SE-M-FLAME-WHEEL2") \
    X(SE_M_FLAMETHROWER, "SE-M-FLAMETHROWER") \
    X(SE_M_FIRE_PUNCH, "SE-M-FIRE-PUNCH") \
    X(SE_M_TOXIC, "SE-M-TOXIC") \
    X(SE_M_SACRED_FIRE, "SE-M-SACRED-FIRE") \
    X(SE_M_SACRED_FIRE2, "SE-M-SACRED-FIRE2") \
    X(SE_M_EMBER, "SE-M-EMBER") \
    X(SE_M_TAKE_DOWN, "SE-M-TAKE-DOWN") \
    X(SE_M_BLIZZARD, "SE-M-BLIZZARD") \
    X(SE_M_BLIZZARD2, "SE-M-BLIZZARD2") \
    X(SE_M_SCRATCH, "SE-M-SCRATCH") \
    X(SE_M_VICEGRIP, "SE-M-VICEGRIP") \
    X(SE_M_WING_ATTACK, "SE-M-WING-ATTACK") \
    X(SE_M_FLY, "SE-M-FLY") \
    X(SE_M_SAND_ATTACK, "SE-M-SAND-ATTACK") \
    X(SE_M_RAZOR_WIND2, "SE-M-RAZOR-WIND2") \
    X(SE_M_BITE, "SE-M-BITE") \
    X(SE_M_HEADBUTT, "SE-M-HEADBUTT") \
    X(SE_M_SURF, "SE-M-SURF") \
    X(SE_M_HYDRO_PUMP, "SE-M-HYDRO-PUMP") \
    X(SE_M_WHIRLPOOL, "SE-M-WHIRLPOOL") \
    X(SE_M_HORN_ATTACK, "SE-M-HORN-ATTACK") \
    X(SE_M_TAIL_WHIP, "SE-M-TAIL-WHIP") \
    X(SE_M_MIST, "SE-M-MIST") \
    X(SE_M_POISON_POWDER, "SE-M-POISON-POWDER") \
    X(SE_M_BIND, "SE-M-BIND") \
    X(SE_M_DRAGON_RAGE, "SE-M-DRAGON-RAGE") \
    X(SE_M_SING, "SE-M-SING") \
    X(SE_M_PERISH_SONG, "SE-M-PERISH-SONG") \
    X(SE_M_PAY_DAY, "SE-M-PAY-DAY") \
    X(SE_M_DIG, "SE-M-DIG") \
    X(SE_M_DIZZY_PUNCH, "SE-M-DIZZY-PUNCH") \
    X(SE_M_SELF_DESTRUCT, "SE-M-SELF-DESTRUCT") \
    X(SE_M_EXPLOSION, "SE-M-EXPLOSION") \
    X(SE_M_ABSORB_2, "SE-M-ABSORB-2") \
    X(SE_M_ABSORB, "SE-M-ABSORB") \
    X(SE_M_SCREECH, "SE-M-SCREECH") \
    X(SE_M_BUBBLE_BEAM, "SE-M-BUBBLE-BEAM") \
    X(SE_M_BUBBLE_BEAM2, "SE-M-BUBBLE-BEAM2") \
    X(SE_M_SUPERSONIC, "SE-M-SUPERSONIC") \
    X(SE_M_BELLY_DRUM, "SE-M-BELLY-DRUM") \
    X(SE_M_METRONOME, "SE-M-METRONOME") \
    X(SE_M_BONEMERANG, "SE-M-BONEMERANG") \
    X(SE_M_LICK, "SE-M-LICK") \
    X(SE_M_PSYBEAM, "SE-M-PSYBEAM") \
    X(SE_M_FAINT_ATTACK, "SE-M-FAINT-ATTACK") \
    X(SE_M_SWORDS_DANCE, "SE-M-SWORDS-DANCE") \
    X(SE_M_LEER, "SE-M-LEER") \
    X(SE_M_SWAGGER, "SE-M-SWAGGER") \
    X(SE_M_SWAGGER2, "SE-M-SWAGGER2") \
    X(SE_M_HEAL_BELL, "SE-M-HEAL-BELL") \
    X(SE_M_CONFUSE_RAY, "SE-M-CONFUSE-RAY") \
    X(SE_M_SNORE, "SE-M-SNORE") \
    X(SE_M_BRICK_BREAK, "SE-M-BRICK-BREAK") \
    X(SE_M_GIGA_DRAIN, "SE-M-GIGA-DRAIN") \
    X(SE_M_PSYBEAM2, "SE-M-PSYBEAM2") \
    X(SE_M_SOLAR_BEAM, "SE-M-SOLAR-BEAM") \
    X(SE_M_PETAL_DANCE, "SE-M-PETAL-DANCE") \
    X(SE_M_TELEPORT, "SE-M-TELEPORT") \
    X(SE_M_MINIMIZE, "SE-M-MINIMIZE") \
    X(SE_M_SKETCH, "SE-M-SKETCH") \
    X(SE_M_SWIFT, "SE-M-SWIFT") \
    X(SE_M_REFLECT, "SE-M-REFLECT") \
    X(SE_M_BARRIER, "SE-M-BARRIER") \
    X(SE_M_DETECT, "SE-M-DETECT") \
    X(SE_M_LOCK_ON, "SE-M-LOCK-ON") \
    X(SE_M_MOONLIGHT, "SE-M-MOONLIGHT") \
    X(SE_M_CHARM, "SE-M-CHARM") \
    X(SE_M_CHARGE, "SE-M-CHARGE") \
    X(SE_M_STRENGTH, "SE-M-STRENGTH") \
    X(SE_M_HYPER_BEAM, "SE-M-HYPER-BEAM") \
    X(SE_M_WATERFALL, "SE-M-WATERFALL") \
    X(SE_M_REVERSAL, "SE-M-REVERSAL") \
    X(SE_M_ACID_ARMOR, "SE-M-ACID-ARMOR") \
    X(SE_M_SANDSTORM, "SE-M-SANDSTORM") \
    X(SE_M_TRI_ATTACK, "SE-M-TRI-ATTACK") \
    X(SE_M_TRI_ATTACK2, "SE-M-TRI-ATTACK2") \
    X(SE_M_ENCORE, "SE-M-ENCORE") \
    X(SE_M_ENCORE2, "SE-M-ENCORE2") \
    X(SE_M_BATON_PASS, "SE-M-BATON-PASS") \
    X(SE_M_MILK_DRINK, "SE-M-MILK-DRINK") \
    X(SE_M_ATTRACT, "SE-M-ATTRACT") \
    X(SE_M_ATTRACT2, "SE-M-ATTRACT2") \
    X(SE_M_MORNING_SUN, "SE-M-MORNING-SUN") \
    X(SE_M_FLATTER, "SE-M-FLATTER") \
    X(SE_M_SAND_TOMB, "SE-M-SAND-TOMB") \
    X(SE_M_GRASSWHISTLE, "SE-M-GRASSWHISTLE") \
    X(SE_M_SPIT_UP, "SE-M-SPIT-UP") \
    X(SE_M_DIVE, "SE-M-DIVE") \
    X(SE_M_EARTHQUAKE, "SE-M-EARTHQUAKE") \
    X(SE_M_TWISTER, "SE-M-TWISTER") \
    X(SE_M_SWEET_SCENT, "SE-M-SWEET-SCENT") \
    X(SE_M_YAWN, "SE-M-YAWN") \
    X(SE_M_SKY_UPPERCUT, "SE-M-SKY-UPPERCUT") \
    X(SE_M_STAT_INCREASE, "SE-M-STAT-INCREASE") \
    X(SE_M_HEAT_WAVE, "SE-M-HEAT-WAVE") \
    X(SE_M_UPROAR, "SE-M-UPROAR") \
    X(SE_M_HAIL, "SE-M-HAIL") \
    X(SE_M_COSMIC_POWER, "SE-M-COSMIC-POWER") \
    X(SE_M_TEETER_DANCE, "SE-M-TEETER-DANCE") \
    X(SE_M_STAT_DECREASE, "SE-M-STAT-DECREASE") \
    X(SE_M_HAZE, "SE-M-HAZE") \
    X(SE_M_HYPER_BEAM2, "SE-M-HYPER-BEAM2") \
    X(SE_RG_DOOR, "SE-RG-DOOR") \
    X(SE_RG_CARD_FLIP, "SE-RG-CARD-FLIP") \
    X(SE_RG_CARD_FLIPPING, "SE-RG-CARD-FLIPPING") \
    X(SE_RG_CARD_OPEN, "SE-RG-CARD-OPEN") \
    X(SE_RG_BAG_CURSOR, "SE-RG-BAG-CURSOR") \
    X(SE_RG_BAG_POCKET, "SE-RG-BAG-POCKET") \
    X(SE_RG_BALL_CLICK, "SE-RG-BALL-CLICK") \
    X(SE_RG_SHOP, "SE-RG-SHOP") \
    X(SE_RG_SS_ANNE_HORN, "SE-RG-SS-ANNE-HORN") \
    X(SE_RG_HELP_OPEN, "SE-RG-HELP-OPEN") \
    X(SE_RG_HELP_CLOSE, "SE-RG-HELP-CLOSE") \
    X(SE_RG_HELP_ERROR, "SE-RG-HELP-ERROR") \
    X(SE_RG_DEOXYS_MOVE, "SE-RG-DEOXYS-MOVE") \
    X(SE_RG_POKE_JUMP_SUCCESS, "SE-RG-POKE-JUMP-SUCCESS") \
    X(SE_RG_POKE_JUMP_FAILURE, "SE-RG-POKE-JUMP-FAILURE") \
    X(SE_PHONE_CALL, "SE-PHONE-CALL") \
    X(SE_PHONE_CLICK, "SE-PHONE-CLICK") \
    X(SE_ARENA_TIMEUP1, "SE-ARENA-TIMEUP1") \
    X(SE_ARENA_TIMEUP2, "SE-ARENA-TIMEUP2") \
    X(SE_PIKE_CURTAIN_CLOSE, "SE-PIKE-CURTAIN-CLOSE") \
    X(SE_PIKE_CURTAIN_OPEN, "SE-PIKE-CURTAIN-OPEN") \
    X(SE_SUDOWOODO_SHAKE, "SE-SUDOWOODO-SHAKE") \

// Create BGM list
#define X(songId, name) static const u8 sBGMName_##songId[] = _(name);
SOUND_LIST_BGM
#undef X

#define X(songId, name) sBGMName_##songId,
static const u8 *const sBGMNames[] =
{
SOUND_LIST_BGM
};
#undef X

// Create SE list
#define X(songId, name) static const u8 sSEName_##songId[] = _(name);
SOUND_LIST_SE
#undef X

#define X(songId, name) sSEName_##songId,
static const u8 *const sSENames[] =
{
SOUND_LIST_SE
};
#undef X

#endif
