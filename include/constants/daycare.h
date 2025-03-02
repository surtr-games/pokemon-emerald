#ifndef GUARD_DAYCARE_CONSTANTS_H
#define GUARD_DAYCARE_CONSTANTS_H

// Parent compatibility scores
#define PARENTS_INCOMPATIBLE       0
#define PARENTS_LOW_COMPATIBILITY  30
#define PARENTS_MED_COMPATIBILITY  60
#define PARENTS_MAX_COMPATIBILITY  80

// Daycare state
#define DAYCARE_NO_MONS     0
#define DAYCARE_EGG_WAITING 1
#define DAYCARE_ONE_MON     2
#define DAYCARE_TWO_MONS    3

#define EGG_STEP_CYCLE_LENGTH 200
#define EGG_HATCH_LEVEL 1
#define EGG_GENDER_MALE 0x8000  // used to create a male egg from a female-only parent species (e.g. Nidoran)

#define DAYCARE_LEVEL_MENU_EXIT 5
#define DAYCARE_EXITED_LEVEL_MENU 2 // would be redundant with above if GF had used the same value

// Array buffers
#define EGG_MOVES_ARRAY_COUNT           10
#define EGG_LVL_UP_MOVES_ARRAY_COUNT    (MAX_LEVEL_UP_MOVES > 50 ? MAX_LEVEL_UP_MOVES : 50)

// Shiny Inheritance Chances
#define EGG_SHINY_CHANCE_0_SHINY_PARENTS 4
#define EGG_SHINY_CHANCE_1_SHINY_PARENTS 20
#define EGG_SHINY_CHANCE_2_SHINY_PARENTS 60

// IV Inheritance Chances
#define EGG_IV_INC_CHANCE  80
#define EGG_IV_KEEP_CHANCE 10
#define EGG_IV_INC_CHANCE_MODIFIER_COMPAT_LOW -20
#define EGG_IV_INC_CHANCE_MODIFIER_COMPAT_MED -10
#define EGG_IV_INC_MAX 6
#define EGG_IV_INC_MIN 2
#define EGG_IV_DEC_MAX 5
#define EGG_IV_DEC_MIN 1

// Ability Inheritance
#define EGG_ABILITY_INHERIT_CHANCE 70

#endif //GUARD_DAYCARE_CONSTANTS_H
