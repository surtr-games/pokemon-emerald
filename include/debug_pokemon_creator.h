#ifndef GUARD_DEBUG_POKEMON_CREATOR_H
#define GUARD_DEBUG_POKEMON_CREATOR_H

#if TX_DEBUG_SYSTEM_ENABLE == TRUE

#define MODIFY_DIGITS_MAX 4

void CB2_Debug_Pokemon(void);
void DebugPkmCreator_Init(u8 mode, u8 index);

#endif

#endif // GUARD_DEBUG_POKEMON_CREATOR_H
