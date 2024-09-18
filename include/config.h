#ifndef GUARD_CONFIG_H
#define GUARD_CONFIG_H

// In the Generation 3 games, Asserts were used in various debug builds.
// Ruby/Sapphire and Emerald do not have these asserts while Fire Red
// still has them in the ROM. This is because the developers forgot
// to define NDEBUG before release, however this has been changed as
// Ruby's actual debug build does not use the AGBPrint features.
#define NDEBUG

// To enable printf debugging, comment out "#define NDEBUG". This allows
// the various AGBPrint functions to be used. (See include/gba/isagbprint.h).
// See below for enabling different pretty printing versions.

#ifndef NDEBUG

#define PRETTY_PRINT_MINI_PRINTF (0)
#define PRETTY_PRINT_LIBC (1)

#define LOG_HANDLER_AGB_PRINT (0)
#define LOG_HANDLER_NOCASH_PRINT (1)
#define LOG_HANDLER_MGBA_PRINT (2)

// Use this switch to choose a handler for pretty printing.
// NOTE: mini_printf supports a custom pretty printing formatter to display preproc encoded strings. (%S)
//       some libc distributions (especially dkp arm-libc) will fail to link pretty printing.
#define PRETTY_PRINT_HANDLER (PRETTY_PRINT_MINI_PRINTF)

// Use this switch to choose a handler for printf output.
// NOTE: These will only work on the respective emulators and should not be used in a productive environment.
//       Some emulators or real hardware might (and is allowed to) crash if they are used.
//       AGB_PRINT is supported on respective debug units.

#define LOG_HANDLER (LOG_HANDLER_MGBA_PRINT)
#endif

#define ENGLISH

#ifdef ENGLISH
#define UNITS_IMPERIAL
#define CHAR_DEC_SEPARATOR CHAR_PERIOD // Period is used as a decimal separator only in the UK and the US.
#else
#define UNITS_METRIC
#define CHAR_DEC_SEPARATOR CHAR_COMMA
#endif

// Uncomment to fix some identified minor bugs
#define BUGFIX

// Various undefined behavior bugs may or may not prevent compilation with
// newer compilers. So always fix them when using a modern compiler.
#if MODERN || defined(BUGFIX)
#ifndef UBFIX
#define UBFIX
#endif
#endif

// Debug options
#define TX_DEBUG_SYSTEM_ENABLE         TRUE               // Enables a overworld debug menu for changing flags, variables, giving pokemon and more, accessed by holding R and pressing START while in the overworld by default.
#define TX_DEBUG_SYSTEM_HELD_KEYS      (R_BUTTON)         // The keys required to be held to open the debug menu.
#define TX_DEBUG_SYSTEM_TRIGGER_EVENT  pressedStartButton // The event that opens the menu when holding the key(s) defined in DEBUG_SYSTEM_HELD_KEYS.
#define TX_DEBUG_SYSTEM_IN_MENU        FALSE              // Replaces the overworld debug menu button combination with a start menu entry (above Pokédex).

#endif // GUARD_CONFIG_H
