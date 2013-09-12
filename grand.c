/*
 * Generate some random numbers. Takes an optional length and some other arguments.
 *
 * Copyright (C) Eron Hennessey, 2013
 */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define GUID    0x00000001
#define HEX     0x00000002
#define ALPHA   0x00000004
#define NUMERIC 0x00000008
#define SYMBOL  0x00000010

#define NUM_CHARS "0123456789"
#define HEX_CHARS (NUM_CHARS "abcdef")
#define ALPHA_CHARS "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
#define SYMBOL_CHARS "~`!@#$%^&*()-_+=[]{}|\\:;\"\'<>,.?/"

/* The usage */
void show_help()
{
   printf("\n"
      "grand - generate random characters\n"
      "==================================\n"
      "\n"
      "Usage: grand [-switches] [length]\n"
      "\n"
      "Switches:\n"
      "---------\n"
      " -a     include alphabetic characters\n"
      " -n     include numeric characters\n"
      " -s     include symbol characters\n"
      " -x     generate hexadecimal characters\n"
      " -g     generate a GUID\n"
      " -h|-?  print this help\n"
      "\n"
      "If no arguments are specified, '-an 8' is assumed, which will generate a\n"
      "random 8-character alphanumeric string.\n"
      "\n"
      "Notes regarding usage:\n"
      "----------------------\n"
      " * Switches can be combined. For example, '-ans' specifies alpha + numeric\n"
      "   + symbols.\n"
      " * Any argument without a '-' character is assumed to be the output length.\n"
      " * If '-x' is specified, any other character types (-a,-n,-s) are ignored.\n"
      " * If '-g' is specified, *all* other arguments are ignored.\n"
      " * GUIDs are always printed in lower-case. Don't whine, convert it to\n"
      "   upper-case if you wish.\n"
   "\n");
}

/* The program */
int main(int argc, char **argv)
{
   int length = 8; /* default to 8 characters */
   unsigned int switches = 0;
   srand(time(0));

   if(argc > 1)
   {
      /* skip the first argument */
      for(int i = 1; i < argc; i++)
      {
         if(argv[i][0] == '-')
         {
            for(int j = 0; j < strlen(argv[i]); j++)
            {
               switch(argv[i][j])
               {
               case 'g': /* make a guid */
                  switches |= GUID;
                  switches |= HEX;
                  length = 32;
                  break;
               case 'x': /* hexadecimal */
                  switches |= HEX;
                  break;
               case 'a': /* include alpha chars*/
                  switches |= ALPHA;
                  break;
               case 'n': /* include numeric chars */
                  switches |= NUMERIC;
                  break;
               case 's': /* include symbols */
                  switches |= SYMBOL;
                  break;
               case '?': case 'h':
                  show_help();
                  return(0);
               default:
                  break;
               }
            }
         }
         else if(!(switches & GUID))
            length = atoi(argv[i]);
      }
   }

   /* if no character classes were chosen, default to alphanumeric */
   if(!(switches & (HEX | ALPHA | NUMERIC | SYMBOL)))
      switches |= (ALPHA | NUMERIC);

   char* chars = 0;

   /* if hex is switched on, ignore other character types */
   if(switches & HEX)
   {
      chars = malloc(sizeof(char) * (strlen(HEX_CHARS) + 1));
      strcpy(chars, HEX_CHARS);
   }
   else
   {
      chars = malloc(sizeof(char) * (
         ((switches & ALPHA) ? strlen(ALPHA_CHARS) : 0) +
         ((switches & NUMERIC) ? strlen(NUM_CHARS) : 0) +
         ((switches & SYMBOL) ? strlen(SYMBOL_CHARS) : 0) + 1));

      sprintf(chars, "%s%s%s",
         (switches & NUMERIC) ? NUM_CHARS : "",
         (switches & ALPHA) ? ALPHA_CHARS : "",
         (switches & SYMBOL) ? SYMBOL_CHARS : "");
   }

   char* rand_str = calloc(sizeof(char), length+1);
   int num_chars = strlen(chars);

   for(int i = 0; i < length; i++)
      rand_str[i] = chars[(int)((rand() / (double)RAND_MAX) * num_chars)];

   /* If a GUID, print in a special guid-y way. Otherwise, just print the string. */
   if(switches & GUID)
      printf("%.8s-%.4s-%.4s-%.4s-%.12s\n", rand_str, rand_str+8, rand_str+12, rand_str+16, rand_str+20);
   else
      printf("%s\n", rand_str);

   free(rand_str);
   free(chars);
   return(0);
}

