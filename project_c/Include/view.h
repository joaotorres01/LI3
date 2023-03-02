#ifndef ____VIEW____
#define ____VIEW____

#include "table.h"
#include "stats.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h> 
#include "define.h"

void menuInicial ();

void prinMenu (int n, int total);

void menuInicial ();

void printMenuQuery (int n, int option);

void printMessageHelp (int n);

void printQuit (int num,int help);

void printCommandLine ();

void loadingScreen ();

void loadComplete (int num,double timeSpent);

void buttonsQuery ();

void displayQuery2 (TABLE table,int page,int totalpages);

void displayQuery3 (TABLE table);

void displayQuery4 (TABLE table, int page, int totalpages);

void displayQuery5 (TABLE table,int page,int totalpages);   

void displayQuery6 (TABLE table,int city,int page);

void displayQuery7 (TABLE table,int page,int totalpages);

void displayQuery8 (TABLE table, int page, int totalpages, char *category); 

void displayQuery9 (TABLE table, int page, int totalPages, char*word);

void printHelp ();

void printEnter ();

void printQuestionFriends ();

void invalidInput ();

void genericTable (TABLE table,int page, int totalPage);

#endif