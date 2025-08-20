#ifndef GUARD_DEBUG_H
#define GUARD_DEBUG_H

#if TX_DEBUG_SYSTEM_ENABLE == TRUE
void Debug_ShowMainMenu(void);
void Debug_OnEnemyPartyEditFinished(void);

extern EWRAM_DATA bool8 gIsDebugBattle;
extern EWRAM_DATA u32 gDebugAIFlags;
#endif

#endif // GUARD_DEBUG_H