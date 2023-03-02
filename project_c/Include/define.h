#ifndef __DEFINE__
#define __DEFINE__


#define ESCONDE_CURSOR "\x1B[?25l"
#define MOSTRA_CURSOR "\x1B[?25h"

#define UP 'A'
#define DOWN 'B'
#define RIGHT 'C'
#define LEFT 'D'

#define ENTER 13

#define COR_N_AZUL "\x1b[0;34m"
#define COR_N_CIANO "\x1b[0;36m"
#define COR_N_VERDE "\x1b[0;32m"
#define COR_N_MAGENTA "\x1b[0;35m"
#define COR_N_VERMELHO "\x1b[0;31m"
#define COR_N_AMARELO "\x1b[0;33m"

#define COR_B_AZUL "\x1b[1;34m"
#define COR_B_CIANO "\x1b[1;36m"
#define COR_B_VERDE "\x1b[1;32m"
#define COR_B_MAGENTA "\x1b[1;35m"
#define COR_B_VERMELHO "\x1b[1;31m"
#define COR_B_AMARELO "\x1b[1;33m"

#define COR_RESET "\x1b[0m"

#define PISCAR "\033[5m"
#define RESET "\033[0m"


#define COMCOR 59
#define SEMCOR 52

#define LINESFORINFO 10

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

char *strdup (const char *s);


#endif