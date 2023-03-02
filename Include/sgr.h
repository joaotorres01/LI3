
#ifndef ____SGR____
#define ____SGR____

#include <glib.h>
#include <stdio.h>
#include "review.h"
#include "business.h"
#include "user.h"
#include <ctype.h>
#include "BusinessCatalog.h"
#include "UserCatalog.h"
#include "ReviewCatalog.h"
#include "stats.h"
#include "table.h"
#include "define.h"

/**
 * @brief Definição da struct sgr
 */
typedef struct sgr* SGR;


int load_sgr (SGR sgr,int with_friends);

SGR init_sgr ();

void free_sgr (SGR sgr);

char* getPathBusiness (SGR sgr);

char* getPathUsers (SGR sgr);

char* getPathReviews (SGR sgr);

void setPathBusiness (SGR sgr,char *pathBus);

void setPathUser (SGR sgr,char *pathUser);

void setPathReviews (SGR sgr,char *pathReviews);

TABLE query2 (SGR sgr, char letter);

TABLE query3 (SGR sgr, char *id);

TABLE query4 (char* id, SGR sgr);

TABLE query5 (char *cidade,float stars,SGR sgr);

TABLE query6 (int num,SGR sgr);

TABLE query7 (SGR sgr);

TABLE query8 (int n, char* category, SGR sgr);

TABLE query9 (char * word, SGR sgr);

#endif