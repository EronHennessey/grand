grand - generate random characters
==================================

Usage: `grand [-switches] [length]`

Switches:
---------
 -a     include alphabetic characters
 -n     include numeric characters
 -s     include symbol characters
 -x     generate hexadecimal characters
 -g     generate a GUID
 -h|-?  print this help

If no arguments are specified, '-an 8' is assumed, which will generate a
random 8-character alphanumeric string.

Notes regarding usage:
----------------------
 * Switches can be combined. For example, '-ans' specifies alpha + numeric
   + symbols.
 * Any argument without a '-' character is assumed to be the output length.
 * If '-x' is specified, any other character types (-a,-n,-s) are ignored.
 * If '-g' is specified, *all* other arguments are ignored.
 * GUIDs are always printed in lower-case. Don't whine, convert it to
   upper-case if you wish.

