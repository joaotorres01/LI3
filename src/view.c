#include "../Include/view.h"

void printTop (){
    printf ("╔═════════════════════════════════════════════════════╗\n");
}

void printTopSplit2 (){
    printf ("╠════════════════════════╦════════════════════════════╣\n");
}

void printTopSplit3 (){
    printf ("╠════════════════════════╦═══════════════════════╦════╣\n");
}

void printMidSplit3 (){
    printf ("╠════════════════════════╬═══════════════════════╬════╣\n");
}


void printMidSplit2 (){
    printf ("╠════════════════════════╬════════════════════════════╣\n");
}

void printMid (){
    printf ("╠═════════════════════════════════════════════════════╣\n");
}

void printBotSplit3 (){
    printf ("╠════════════════════════╩═══════════════════════╩════╣\n");
}

void printBotSplit2(){
    printf ("╠════════════════════════╩════════════════════════════╣\n");
}

void printBot (){
    printf ("╚═════════════════════════════════════════════════════╝\n");
}

void printEmptyLine (){
    printf ("║                                                     ║\n");
}

void printEmptyLineSplit2 (){
    printf ("║                        ║                            ║\n");
}

void printEmptyLineSplit3 (){
    printf ("║                        ║                       ║    ║\n");
}

void printQuit (int num,int help){
    if (help == 1)printf("║\x1b[1;34m          CLICK C FOR COMMAND MODE         \x1b[0m║");
    if (help == 2)printf("║\x1b[1;34m       ⚠️   SGR is not loaded yet   ⚠️       \x1b[0m║");
    if (!num) printf("   EXIT  ║\n");
    else      printf ("\x1b[1;31m   EXIT  \x1b[0m║\n");
    printf("╚═══════════════════════════════════════════╩═════════╝\n");
}


void printFrase (char *s,int mode,int color){
    int len = strlen (s); 
    int total = color ? COMCOR - len : SEMCOR - len;
    printf ("║ ");
    printf("%*c", total/2, ' ');
    if (mode) printf (PISCAR"%s"RESET,s);
    else printf ("%s",s);
    printf("%*c", total/2, ' ');
    if (total%2 != 0) putchar (' ');
    printf (RESET"║\n");
}

void printfInfoSplit2 (GPtrArray *array, int index,int num){
    for (int i = 0; i < num;i++){
        char *str = g_ptr_array_index (array,index + i);
        printf ("║");
        if ((index + i)%2 == 0)printf (" %.22s ",str);
        else {
            int len = strlen (str);
            int total = 28 - strlen (str);
            if (len >= 27) printf (" %.26s ",str);
            else {
                printf("%*c", total/2, ' ');
                printf ("%s",str);
                printf("%*c", total/2, ' ');
                if (total%2 != 0) putchar (' ');
            }
        }
    }
    printf ("║\n");
}


void printInfoSplit3 (GPtrArray* arrray, int index){
    char *str = g_ptr_array_index (arrray,index);
    printf ("║ %.22s ║",str);
    str = g_ptr_array_index (arrray,index + 1);
    int len = strlen (str);
    int total = 23 - strlen (str);
    if (len >= 22) printf (" %.21s ",str);
    else {
        printf("%*c", total/2, ' ');
        printf ("%s",str);
        printf("%*c", total/2, ' ');
        if (total%2 != 0) putchar (' ');
    }
    str = g_ptr_array_index (arrray,index + 2);
    printf ("║ %s║\n",str);

}


void printTituloSplit3 (char*s1,char *s2){
    printf ("║"COR_B_VERMELHO);
    int len1 = (24 - strlen(s1)) / 2;
    printf("%*s%s%*s", len1, "", s1, len1+1, "");
    printf (COR_RESET"║"COR_B_VERMELHO);
    int len2 = (23 - strlen(s2)) / 2;
    printf("%*s%s%*s", len2, "", s2, len2, "");
    printf (COR_RESET" ║ ⭐ ");
    printf ("║\n");
}


void printTituloSplit2 (char *s1,char *s2){
    printf ("║"COR_B_VERMELHO);
    int len1 = (24 - strlen(s1)) / 2;
    printf("%*s%s%*s", len1, "", s1, len1+1, "");
    printf (COR_RESET"║"COR_B_VERMELHO);
    int len2 = (27- strlen(s2)) / 2;
    printf("%*s%s%*s", len2, "", s2, len2+2, "");
    printf (COR_RESET"║\n");
}

void printTituloParte (int n){
    if (n == 0)printf("║\x1b[1;36m        ███████╗ ██████╗ ██████╗           \x1b[0m");
    if (n == 1)printf("║\x1b[1;36m        ██╔════╝██╔════╝ ██╔══██╗          \x1b[0m");
    if (n == 2)printf("║\x1b[1;36m        ███████╗██║  ███╗██████╔╝          \x1b[0m");
    if (n == 3)printf("║\x1b[1;36m        ╚════██║██║   ██║██╔══██╗          \x1b[0m");
    if (n == 4)printf("║\x1b[1;36m        ███████║╚██████╔╝██║  ██║          \x1b[0m");
    if (n == 5)printf("║\x1b[1;36m        ╚══════╝ ╚═════╝ ╚═╝  ╚═╝          \x1b[0m");

}

void printTextoParte (int n, int query){
    if (n == 5 && query != 10){printf ("║\x1b[1;34m                DESCRIPTION                "COR_RESET);return;}
    else if (n == 5) {         printf ("║\x1b[1;34m                  MADE BY                  "COR_RESET);return;}
    if (n == 6 && query != 10){printf ("║\x1b[1;34m                   INPUT                   "COR_RESET);return;}
    if (n == 7 && query != 10){printf ("║\x1b[1;34m                   OUTPUT                  "COR_RESET);return;}
    switch (query)
    {
    case 1:
        if (n == 0)      printf ("║                 Load SGR                  ");
        else if (n == 1) printf ("║         Path to files (optional)          ");
        else             printf ("║                                           ");
    break;
    case 2:
        if (n == 0)      printf ("║        Businesses Started by Letter       ");
        else if (n == 1) printf ("║                  Letter                   ");
        else if (n == 2) printf ("║               Name | Total                ");
        else             printf ("║                                           ");
    break;
    case 3:
        if (n == 0)      printf ("║              Business's info              ");
        else if (n == 1) printf ("║               Business's ID               ");
        else if (n == 2) printf ("║    Name | City | State | Stars | Total    ");
        else             printf ("║                                           ");
    break;
    case 4:
        if (n == 0)      printf ("║        Businesses Reviewed by User        ");
        else if (n == 1) printf ("║                 User's ID                 ");
        else if (n == 2) printf ("║                 Name | ID                 ");
        else             printf ("║                                           ");
    break;   
    case 5:
        if (n == 0)      printf ("║       Businesses with stars and City      ");
        else if (n == 1) printf ("║          Number of stars | city           ");
        else if (n == 2) printf ("║                 Name | ID                 ");
        else             printf ("║                                           ");
    break; 
    case 6:
        if (n == 0)      printf ("║           Top Businesses By City          ");
        else if (n == 1) printf ("║           Number of Businesses            ");
        else if (n == 2) printf ("║             Name | ID | Stars             ");
        else             printf ("║                                           ");
    break;  
    case 7:
        if (n == 0)      printf ("║            International Users            ");
        else if (n == 2) printf ("║                 ID | Total                ");
        else             printf ("║                                           ");  
    break;
    case 8:
        if (n == 0)      printf ("║       Top Businesses With Category        ");
        else if (n == 1) printf ("║      Number of Businesses | Category      ");
        else if (n == 2) printf ("║             Name | ID | Stars             ");
        else             printf ("║                                           ");
    break;
    case 9:
        if (n == 0)      printf ("║             Reviews With Word             ");
        else if (n == 1) printf ("║                    Word                   ");
        else if (n == 2) printf ("║                     ID                    ");
        else             printf ("║                                           ");
    break;
    case 10:
        if (n == 0)      printf ("║               Diogo Vieira                ");
        else if (n == 1) printf ("║             António Fernandes             ");
        else if (n == 2) printf ("║                João Torres                ");
        else             printf ("║                                           ");
    break;
    default:
        printf ("║                                           ");
        break;
    }
}

                                           

void menuInicial (){
    printTop ();
    for (int i = 0; i < 3; i++)printEmptyLine();
    printf("║\x1b[1;36m               ███████╗ ██████╗ ██████╗              \x1b[0m║\n");
    printf("║\x1b[1;36m               ██╔════╝██╔════╝ ██╔══██╗             \x1b[0m║\n");
    printf("║\x1b[1;36m               ███████╗██║  ███╗██████╔╝             \x1b[0m║\n");
    printf("║\x1b[1;36m               ╚════██║██║   ██║██╔══██╗             \x1b[0m║\n");
    printf("║\x1b[1;36m               ███████║╚██████╔╝██║  ██║             \x1b[0m║\n");
    printf("║\x1b[1;36m               ╚══════╝ ╚═════╝ ╚═╝  ╚═╝             \x1b[0m║\n");
    printEmptyLine ();
    printFrase ("\x1b[1;36mSISTEMA DE GESTAO DE RECOMENDACOES",0,1);
    for (int i = 0; i < 3; i++)printEmptyLine();
    printMid(); 
    printEmptyLine ();
    printFrase ("\x1b[1;36mCLICK ENTER TO BEGIN",1,1);
    printEmptyLine ();
    printBot ();
}
                 
void prinMenu (int n, int total){
    int titulo = -1, mid = 4, end = total - 1, start = 1;
    printf ("╔═══════════════════════════════════════════╦═════════╗\n");
    for (int i = 0; i < total;i++){
        if (i == start) titulo = 0;
        if (titulo >= 0 && titulo < 6) printTituloParte (titulo++);
        else if (n != 9)printTextoParte (i,-1);
        else if (i > 4) printTextoParte(i,10);
        else printTextoParte(-1,10);
        printf("║");
        if (i == n) 
            printf (COR_B_VERMELHO" QUERY %d "COR_RESET,i + 1);
        else 
            printf (" QUERY %d ",i + 1);
        printf("║\n");
        if (i == mid) printf ("╠═══════════════════════════════════════════╬═════════╣\n");
        else if (i >= start && i < mid) printTituloParte (titulo++);
        else if (i < end)  printTextoParte (i - mid -1 ,n + 1);
        if ( i < end && i != mid)printf ("╠═════════╣\n");

    }
    printf ("╠═══════════════════════════════════════════╬═════════╣\n");
}

void printTituloQuery (int n){
    printf ("╔═════════════════════════════════════════════════════╗\n");
    switch (n)
    {
    case 1:
    printFrase ("\x1b[1;36mLOAD SGR",0,1);
    //printf ("║\x1b[1;36m                     LOAD SGR                        \x1b[0m║\n");
    printf ("╠═════════════════════════════════════════════════════╣\n");
    break;
    
    default:
        break;
    }
}

void printMessageQuery (int n){
    switch (n)
    {
    case 1:
        printf ("║                 Load SGR from files                 ║\n");
        printf ("║      Path File Business:business_full.csv           ║\n");
        printf ("║      Path File Users   :users_full.csv              ║\n");
        printf ("║      Path File Reviews :reviews_1M.csv              ║\n");
    break;         

    default:
        break;
    }
}
void printInputOption (int n, int option){
    switch (n)
    {
    case 1:
        if (option == 1) printFrase ("\x1b[1;31mChange Paths",0,1);
        else             printFrase ("Change Paths",0,0);
        printMid ();
        if (option == 2) printFrase ("\x1b[1;31mRun",0,1);
        else             printFrase ("Run",0,0);
        printMid ();
        if (option == 3) printFrase ("\x1b[1;31mBack to Menu",0,1);
        else             printFrase ("Back to Menu",0,0);
    break;
    
    default:
        break;
    }
}

void printMessageHelp (int n){
    printMid();
    if (n == 1)printFrase ("\x1b[1;34mSelect an option",0,1);
    if (n == 2)printFrase ("\x1b[1;34m⚠️       SGR is already loaded       ⚠️",0,1);
    printBot ();
}

void printMenuQuery (int n,int option){
    printTituloQuery (n);
    for (int i = 0; i < 4;i++)printEmptyLine ();
    printMessageQuery (n); 
    for (int i = 0; i < 3;i++)printEmptyLine ();
    printMid ();
    printInputOption (n,option);
}

void printCommandLine (){
    printf (COR_B_AZUL"CommandLine$"COR_RESET);
}


void printInt (int num){
    char s[20];
    sprintf(s, "%d", num);
    int len = strlen (s); 
    int total = SEMCOR - len;
    printf ("║ ");
    printf("%*c", total/2, ' ');
    printf ("%s",s);
    printf("%*c", total/2, ' ');
    if (total%2 != 0) putchar (' ');
    printf (RESET"║\n");
}

void printFloat (int casasDecimais,float num){
    char s[20];
    sprintf(s, "%.*f",casasDecimais,num);
    int len = strlen (s); 
    int total = SEMCOR - len;
    printf ("║ ");
    printf("%*c", total/2, ' ');
    printf ("%s",s);
    printf("%*c", total/2, ' ');
    if (total%2 != 0) putchar (' ');
    printf (RESET"║\n");
}

// QUERIES
int lenHelper(unsigned x) {
    if (x >= 1000000000) return 10;
    if (x >= 100000000)  return 9;
    if (x >= 10000000)   return 8;
    if (x >= 1000000)    return 7;
    if (x >= 100000)     return 6;
    if (x >= 10000)      return 5;
    if (x >= 1000)       return 4;
    if (x >= 100)        return 3;
    if (x >= 10)         return 2;
    return 1;
}


void printPage (int page, int totalpages){
    int total = SEMCOR - lenHelper (page) - lenHelper (totalpages) -1;
    printf ("║");
    printf("%*c", total,' ');
    printf ("%d/%d ║\n",page,totalpages);
}



void displayQuery2 (TABLE table, int page, int totalpages){
    GPtrArray* array = getInfo (table);
    int total = tableGetLength (table);
    printTop ();
    printFrase ("\x1b[1;36mBUSINESSES STARTED BY LETTER",0,1);
    printMid ();
    char *titulo = g_ptr_array_index (array,0);
    printFrase (titulo,0,0);
    printMid ();
    int numColunas = tableGetNrCol (table);
    for (int i = numColunas; i < LINESFORINFO; i++){
        int index = i + LINESFORINFO *page;
        if (index < total){
            char *str = g_ptr_array_index (array,index);
            //printFrase (str,0,0);
            int len = strlen (str);
            if (len >= 51) printf ("║ %.51s ║\n",str);
            else printFrase (str,0,0);
        }
        else printEmptyLine ();
    }
    printMid ();
    printPage(page,totalpages);
    printMid ();
    printFrase ("\x1b[1;31mTOTAL",0,1);
    printInt (total-1);
    printBot ();
}


void displayQuery3 (TABLE table){
    GPtrArray* array = getInfo (table);
    printTop ();
    printFrase ("\x1b[1;36mBUSINESS'S INFORMATION",0,1);
    printMid ();
    char*bus_id =           (char *)g_ptr_array_index (array,6);
    char*nome =             (char *)g_ptr_array_index (array,7);
    char*city =             (char *)g_ptr_array_index (array,8);
    char*state =            (char *)g_ptr_array_index (array,9);
    float*stars =           (float *)g_ptr_array_index (array,10);
    int*totalReviews =      (int *)g_ptr_array_index (array,11);
    printFrase ("\x1b[1;31mBUSINESS ID:",0,1);
    printFrase (bus_id,0,0);
    printFrase ("\x1b[1;31mName:",0,1);
    printFrase (nome,0,0);
    printFrase ("\x1b[1;31mCity:",0,1);
    printFrase (city,0,0);
    printFrase ("\x1b[1;31mState:",0,1);
    printFrase (state,0,0); 
    printFrase ("\x1b[1;31mStars:",0,1);
    printFloat (1,*stars); 
    printFrase ("\x1b[1;31mTotalReviews:",0,1);
    printInt (*totalReviews);  
    printMid ();
    printFrase ("\x1b[1;34mPRESS ENTER TO GO BACK TO MENU",0,1);
    printBot();
}


void displayQuery4 (TABLE table, int page, int totalpages){
    GPtrArray* array = getInfo (table);
    int numColunas = tableGetNrCol (table);
    int total = tableGetLength (table);
    printTop ();
    printFrase ("\x1b[1;36mUSER'S REVIEWS",0,1);
    printTopSplit2 ();
    printTituloSplit2("business_id","name");
    printMidSplit2 ();
    for (int i = 0; i < LINESFORINFO;i++){
        int index = 1+ i + LINESFORINFO *page;
        if (index*2 +1 < total)printfInfoSplit2 (array,index*2,2);
        else printEmptyLineSplit2();
    }
    printBotSplit2 ();
    printPage (page,totalpages);
    printMid ();
    printFrase ("\x1b[1;31mTOTAL",0,1);
    printInt ((total-numColunas)/2);
    printBot ();
}

void displayQuery5 (TABLE table,int page,int totalpages){
    GPtrArray *array = getInfo (table);
    int total = tableGetLength (table);
    printTop ();
    printFrase ("\x1b[1;36mBUSINESSES WITH STARS AND CITY",0,1);
    printTopSplit2 ();
    printTituloSplit2 ("business_id","name");
    printMidSplit2 ();
    for (int i = 0; i < LINESFORINFO;i++){
        int index = 1 + i + LINESFORINFO  * page;
        if (index * 2 + 1 < total) printfInfoSplit2 (array,index *2,2);
        else printEmptyLineSplit2 ();
    }
    printBotSplit2 ();
    printPage (page,totalpages);
    printBot ();
}


void displayQuery6 (TABLE table,int city, int page){
    GPtrArray *cityArray = getInfo (table);
    DisplayQ6 display = g_ptr_array_index (cityArray,city);
    int total = Q6getlength (display);
    int totalPages = total/3/LINESFORINFO;
    if ((total/3)%LINESFORINFO == 0)totalPages--;
    char *cidade = Q6getCidade (display); 
    GPtrArray * array = Q6getInfo (display);
    printTop ();
    printFrase ("\x1b[1;36mTOP BUSINESSES BY CITY",0,1);
    printMid ();
    printFrase (cidade,0,0); 
    printTopSplit3();
    printTituloSplit3 ("business_id","name");
    printMidSplit3 ();
    for (int i = 0; i < LINESFORINFO;i++){
        int index = (LINESFORINFO * page + i) * 3;
        if (index < total)printInfoSplit3 (array,index);
        else printEmptyLineSplit3();
    }
    printBotSplit3 ();
    printPage (page,totalPages);
    printBot ();
}


void displayQuery7 (TABLE table, int page, int totalpages){
    GPtrArray* array = getInfo (table);
    int total = tableGetLength (table);
    int numColunas = tableGetNrCol (table);
    printTop ();
    printFrase ("\x1b[1;36mINTERNATIONAL USERS",0,1);
    printMid();
    printFrase ("\x1b[1;31muser_id",0,1);
    printMid();
    for (int i = 0; i < LINESFORINFO; i++){
        int index = numColunas + i + LINESFORINFO *page;
        if (index < total){
            char *str = g_ptr_array_index (array,index);
            printFrase (str,0,0);
        }
        else printEmptyLine ();
    }
    printMid ();
    printPage(page,totalpages);
    printMid ();
    printFrase ("\x1b[1;31mTOTAL",0,1);
    printInt (total-1);
    printBot ();
}


void displayQuery8 (TABLE table, int page, int totalPages, char *category){
    GPtrArray *array = getInfo (table);
    int total = tableGetLength (table);
    printTop ();
    printFrase ("\x1b[1;36mTOP BUSINESSES BY CATEGORY",0,1);
    printMid ();
    printFrase (category,0,0); 
    printTopSplit3();
    printTituloSplit3 ("business_id","name");
    printMidSplit3 ();
    for (int i = 0; i < LINESFORINFO;i++){
        int index = (LINESFORINFO * page + i + 1) * 3;
        if (index < total)printInfoSplit3 (array,index);
        else printEmptyLineSplit3();
    }
    printBotSplit3 ();
    printPage (page,totalPages);
    printBot ();
}



void displayQuery9 (TABLE table, int page, int totalPages, char*word){
    GPtrArray* array = getInfo (table);
    int numColunas = tableGetNrCol (table);
    int total = tableGetLength (table)-numColunas;
    printTop ();
    printFrase ("\x1b[1;36mREVIEWS WITH WORD",0,1);
    printMid ();
    printFrase (word,0,0);
    printMid ();
    printFrase ("\x1b[1;31mreview_id",0,1);
    for (int i = 0; i < LINESFORINFO; i++){
        int index = numColunas +i + LINESFORINFO *page;
        if (index < total){
            char *str = g_ptr_array_index (array,index);
            printFrase (str,0,0);
        }
        else printEmptyLine ();
    }
    printMid ();
    printPage(page,totalPages);
    printMid ();
    printFrase ("\x1b[1;31mTOTAL",0,1);
    printInt (total-1);
    printBot ();
}


void loadingScreen (){
    printTop ();
    printEmptyLine ();
    printFrase ("\x1b[1;31mLOADING",1,1);
    printEmptyLine ();
    printBot ();
}

void loadComplete (int num,double timeSpent){
    printTop ();
    printEmptyLine ();
    printFrase ("\x1b[1;31mLOADING COMPLETED",0,1);
    printEmptyLine();
    if (num == 0) printFrase ("\x1b[0;31mThe seconds spent to load SGR were:",0,1);
    if (num == 1) printFrase ("\x1b[0;31mThe seconds spent to do the query were:",0,1);
    if (num == 2) printFrase ("\x1b[0;31mThe seconds spent to destroy SGR were:",0,1);
    printFloat (6,timeSpent);
    printEmptyLine ();
    printMid ();
    printFrase ("\x1b[1;34mPRESS ENTER TO CONTINUE",0,1);
    printBot();
}


void printHelp (int page){
    if (page == 0){
        printTop ();
        printFrase ("\x1b[1;34mDetails about a query",0,1);
        printFrase ("help(num_query);",0,0);
        printMid();
        printFrase ("\x1b[1;34mStore query results in variable",0,1);
        printFrase ("x=businesses_started_by_letter(sgr, \"A\";)",0,0);
        printMid ();
        printFrase ("\x1b[1;34mVizualize variable's result",0,1); 
        printFrase ("show(x);",0,0);
        printMid ();
        printFrase ("\x1b[1;34mWrite a variable's content to a .csv file",0,1);
        printFrase ("toCSV(x,delim,filepath);",0,0);
        printMid ();
        printFrase ("\x1b[1;34mRead the content of a .csv file to a variable",0,1);
        printFrase ("x=fromCSV(filepath,delim);",0,0);
        printMid ();
        printPage (page,1);
        printMid ();
        printFrase ("\x1b[1;31mPRESS ENTER TO GO BACK TO COMMAND LINE",0,1);
        printBot ();
    }
    else{
        printTop ();
        printFrase ("\x1b[1;34mResults's filter",0,1);
        printFrase ("y=filter(x,column_name,value,operator);",0,0);
        printEmptyLine ();
        printFrase ("\x1b[1;34mNOTE:",0,1);
        printFrase ("operator can be:",0,0);
        printFrase ("LT - less than ",0,0);
        printFrase ("EQ - equal ",0,0);
        printFrase ("GT - greater than",0,0);
        printMid ();
        printFrase ("\x1b[1;34mGet the subset of a column",0,1);
        printFrase ("y=proj(x,cols);",0,0);
        printMid();
        printFrase ("\x1b[1;34mGet content from a position",0,1);
        printFrase ("z=x[1][1];",0,0);
        printMid ();
        printPage (page,1);
        printMid ();
        printFrase ("\x1b[1;31mPRESS ENTER TO GO BACK TO COMMAND LINE",0,1);
        printBot ();
    }
}

void printEnter (){
    printTop();
    printFrase ("\x1b[1;31mPRESS ENTER TO PROCEED",0,1);
    printBot ();
}


void buttonsQuery (){
    printTop ();
    printFrase ("\x1b[1;31mUseful buttons for query",0,1);
    printMid ();
    printFrase ("Input page -\x1b[1;34m P",0,1);
    printFrase ("Exit -\x1b[1;34m Z",0,1);
    printFrase ("Change page -\x1b[1;34m Horizontal Arrows",0,1);
    printBot ();
}



void printQuestionFriends (){
    printTop ();
    printFrase ("Do you want to load the user's friend into SGR?",0,0);
    printEmptyLine ();
    printFrase ("\x1b[1;31mNOTE",0,1);
    printFrase ("Friends are really useless (in SGR)",0,0);
    printFrase ("They will decrease queries and load times",0,0);
    printFrase ("Will not be used in any query",0,0);
    printBot ();
    printf (COR_B_AZUL"Answer(Y/N):"COR_RESET); 
}



void invalidInput (){
    printTop ();
    printEmptyLine ();
    printFrase ("\x1b[1;31mTHE QUERY WAS NOT SUCESSUFUL",0,1);
    printEmptyLine ();
    printFrase ("The input was invalid",0,0);
    printEmptyLine ();
    printFrase ("\x1b[1;34mPRESS ENTER TO TRY AGAIN OR Z TO GO TO MENU",0,1);
    printBot ();
}


void genericTable (TABLE table,int page, int totalPage){
    int numColunas = tableGetNrCol (table);
    GPtrArray *info = getInfo (table);
    int length = tableGetLength (table);
    printf ("╔");
    for (int i = 0; i < numColunas;i++){
        printf ("════════════════════════");
        if (i < numColunas - 1) printf ("╦");
    }
    printf ("╗\n");
    printf ("║");
    for (int i = 0; i < numColunas;i++){
        char *str = g_ptr_array_index (info,i);
        int len = strlen (str);
        printf (COR_B_VERMELHO"%s"COR_RESET,str);
        printf("%*c", 24 -len, ' ');
        printf ("║");
    }
    printf ("\n");
    int initPage = numColunas + numColunas*LINESFORINFO *page;
    for (int i = initPage; i < initPage + (LINESFORINFO*numColunas) && i < length;i+=numColunas){
        printf ("║");
        for (int u = 0; u < numColunas;u++){
            int index = i + u;
            char *str = g_ptr_array_index (info,index);
            int len = strlen (str);
            if (len > 22)printf ("%.23s ",str);
            else {
                printf ("%s",str);
                printf("%*c", 24 -len, ' ');
            }
            printf ("║");
        }
        printf ("\n");
    }
    printf ("╚");
    for (int i = 0; i < numColunas;i++){
        printf ("════════════════════════");
        if (i < numColunas - 1) printf ("╩");
    }
    printf ("╝\n");
    printf ("PAGE:%d/%d\n",page,totalPage);
}