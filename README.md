## grand - generate random characters

Usage: `grand [-switches] [length]`

### Switches:

<table>
  <tr> <td>-a</td> <td>include alphabetic characters</td> </tr>
  <tr> <td>-n</td> <td>include numeric characters</td> </tr>
  <tr> <td>-s</td> <td>include symbol characters</td> </tr>
  <tr> <td>-x</td> <td>generate hexadecimal characters</td> </tr>
  <tr> <td>-g</td> <td>generate a GUID</td> </tr>
  <tr> <td>-h | -?</td> <td>print this help</td> </tr>
</table>

If no arguments are specified, '-an 8' is assumed, which will generate a
random 8-character alphanumeric string.

You can use it to generate passwords:

    $ grand -ans 10
    Ppzx4w~fdU

or GUIDs:

    $ grand -g
    83010e18-8a3a-57b0-33f7-b3235c67ce6b

or whatever you like...

### Building it:

Build it by running `make` in the `grand` directory (substitute my example location with the one in which
you've placed the source):

    $ cd ~/src/grand
    $ make
    cc -std=c99 -o grand grand.c

Of course, you'll need [make](http://www.gnu.org/software/make/), and a [C99](http://en.wikipedia.org/wiki/C99) compiler
to do so. [GCC](http://gcc.gnu.org/) works well. ;)

If you don't have `make`, simply use the final line of the above output as your command:

    $ cc -std=c99 -o grand grand.c

### Installing it:

Install it by moving it to a directory in your `PATH`. For example:

    $ mv grand ~/bin

### Notes regarding usage:

 * Switches can be combined. For example, '-ans' specifies alpha + numeric + symbols.

 * Any argument without a '-' character is assumed to be the output length.

 * If '-x' is specified, any other character types (-a,-n,-s) are ignored.

 * If '-g' is specified, *all* other arguments are ignored.

 * GUIDs are always printed in lower-case. Don't whine, convert it to upper-case if you wish.

