#ifndef GUARD_DEBUG_POKEMON_CREATOR_H
#define GUARD_DEBUG_POKEMON_CREATOR_H

#if TX_DEBUG_SYSTEM_ENABLE == TRUE

enum PkmCreatorMode
{
    MODE_PARTY_ADD,               // Add to party
    MODE_PARTY_EDIT,              // Edit party
    MODE_PARTY_EDIT_DRAFT,        // Edit party (copies draft mon)
    MODE_PC_EDIT,                 // Edit PC Box
    MODE_ENEMY_PARTY_ADD,         // Add to enemy party
    MODE_ENEMY_PARTY_EDIT,        // Edit enemy party
    MODE_ENEMY_PARTY_EDIT_DRAFT,  // Edit enemy party (copies draft mon)
    MODE_TESTING,                 // Testing mode (doesn't modify parties)
    MODE_TESTING_COPY,            // Testing mode (doesn't modify parties, copy first mon in party)
    MODE_BATTLE_DEBUG_MENU_ENEMY_PARTY_EDIT,        // For battle debug menu: edit enemy party
    MODE_BATTLE_DEBUG_MENU_ENEMY_PARTY_EDIT_INDEX,  // For battle debug menu: edit enemy party at specified index
};

#define MODIFY_DIGITS_MAX 4

void CB2_Debug_Pokemon(void);
void DebugPkmCreator_Init(enum PkmCreatorMode mode, u8 index);

#endif

#endif // GUARD_DEBUG_POKEMON_CREATOR_H
