#include "../Include/controller.h"

void clrscr (){
    printf("\033[1;1H\033[2J");
}

char * getVariable (char *str){
    for (int i = 0; str[i];i++)
        if (isspace (str[i]) || ispunct (str[i])) return NULL;
    return str;
}

int getCommand (char *str){
    printf ("%s\n",str);
    if (!strcmp (str,"init_sgr"))                       return 0;
    if (!strcmp (str,"load_sgr"))                       return 1;
    if (!strcmp (str,"businesses_started_by_letter"))   return 2;
    if (!strcmp (str,"business_info"))                  return 3;
    if (!strcmp (str,"businesses_reviewed"))            return 4;
    if (!strcmp (str,"businesses_with_stars_and_city")) return 5;
    if (!strcmp (str,"top_businesses_by_city"))         return 6;
    if (!strcmp (str,"international_users"))            return 7;
    if (!strcmp (str,"top_businesses_with_category"))   return 8;
    if (!strcmp (str,"reviews_with_word"))              return 9;
    if (!strcmp (str,"fromCSV"))                        return 10;
    if (!strcmp (str,"filter"))                         return 11;
    if (!strcmp (str,"proj"))                           return 12;
    return -1;
}


int validLetter (char *str){
    if (strlen (str) != 3)return 0;
    if (str[0] == '"' && str[2] == '"' && isalpha (str[1])) return 1;
    return 0;
}

int validID (char *str){
    if (strlen (str)== 22)return 1;
    return 0;
}

int validStars (float stars){
    if (stars >= 0 && stars <= 5) return 1;
    return 0;
}



char* validArgument (char *str){
    char *result;
    if (strchr (str,'"')){
        char * rest = strtok (str,"\"");
        if (strchr (rest,'"'))     
            result = strtok (NULL,"\"");
        else result =NULL;
    }
    return result;
}

void waitEnter (int num,double timeSpent){
    char buffer = 0;
    while (buffer != ENTER)
    {
        clrscr ();
        if(num == 1)buttonsQuery ();
        loadComplete (num,timeSpent);
        system("/bin/stty raw");
        buffer = getchar();
        system("/bin/stty cooked");    
    }
}


int waitInvalid (){
    char buffer = 0;
    while (buffer != 'z' && buffer != ENTER)
    {
        clrscr ();
        invalidInput ();
        system("/bin/stty raw");
        buffer = getchar();
        system("/bin/stty cooked");
    }
    if (buffer == ENTER) return 1;
    return 0;
}

void enterToProceed (){
    char buffer = 0;
    while (buffer != ENTER)
    {
        printEnter();
        system("/bin/stty raw");
        buffer = getchar();
        system("/bin/stty cooked");    
        clrscr(); 
    }
    
}

int canRight (TABLE table, int city,int page){
    GPtrArray * array = getInfo (table);
    DisplayQ6 dis = g_ptr_array_index (array,city);
    int total = Q6getlength (dis);
    int totalpages = total/3/LINESFORINFO;
    if (total/3%LINESFORINFO == 0) totalpages--;
    return page < totalpages ;
}

int getColumn (TABLE table,char* colname,int numColunas){
    GPtrArray *info = getInfo (table);
    for (int i = 0; i < numColunas;i++){
        char *str = g_ptr_array_index (info,i);
        if (!(strcmp (colname,str))) return i;
    }
    return -1; 
}

void addHeaders (GPtrArray* array, TABLE table){
    GPtrArray*info = getInfo (table);
    int numColunas = tableGetNrCol (table);
    for (int i = numColunas -1; i >= 0;i--){
        char *str = g_ptr_array_index (info,i);
        g_ptr_array_add (array,strdup (str));
    }
}

typedef struct variables{
    char *var_name;
    TABLE table;
    int menu;
    int numColunas;
    char *var_arg;
}*Variables;


Variables initVar (char *name,TABLE table,int menu,int nrColunas){
    Variables new = malloc (sizeof (struct variables));
    new->var_name = strdup (name);
    new->table = table;
    new->menu = menu;
    new->var_arg = NULL;
    new->numColunas = nrColunas;
    return new;
}

void setVarArg (Variables vars,char *varArg){
    vars->var_arg = strdup (varArg);
}

void freeVar (void * data){
    Variables vars = (Variables) data;
    free (vars->var_name); 
    clearTable (vars->table);
    free (vars->var_arg);
}


TABLE getTableVar (GPtrArray* array, char*name,int size,int *menu, char *arg){
    for (int i = 0; i < size;i++){
        Variables vars = g_ptr_array_index (array,i);
        if (!strcmp (vars->var_name,name)) {
            *menu = vars->menu;
            arg = vars->var_arg;
            TABLE table =vars->table;
            return table;
        }
    }
    return NULL;
}

void printVars (GPtrArray* array,int size){
    for (guint i = 0; i < size;i++){
        Variables vars = g_ptr_array_index (array,i);
        printf ("name->%s\n",vars->var_name);
    }
}



TABLE filterTable (TABLE table, int column,int numColumns,char* cmp_value,int operator,GPtrArray *new){
    int new_length = 0;
    GPtrArray* array = getInfo (table);
    int size = tableGetLength (table) -numColumns;
    for (int i = numColumns;i < size;i+=numColumns){
        char *value = g_ptr_array_index (array,i+column);
        int oper_result =strcmp (cmp_value,value);
        if ((operator == 0 && !oper_result) || (operator == -1 && oper_result > 0) || (operator == 1 && oper_result < 0)){
            for (int index = 0; index < numColumns;index++){
                char *temp = g_ptr_array_index (array,index + i);
                g_ptr_array_add (new,strdup (temp));
                new_length++;                
            }
        }

    }
    TABLE result = NULL;
    if (new_length)result = initTable (new,new_length,numColumns);
    return result;
}

TABLE projTable (TABLE table,int column, int numColumns){
    GPtrArray* array = getInfo (table);
    GPtrArray* new = g_ptr_array_new_with_free_func (free);
    int new_len = 0;
    int length = tableGetLength (table);
    for (int i = numColumns;i < length;i += numColumns){
        char*temp = g_ptr_array_index (array,i + column);
        g_ptr_array_add (new,strdup (temp));
        new_len++;
    }
    TABLE result = initTable (new,new_len + 1,1);
    return result;
}


int getOperator (char *name){
    if (!strcmp (name,"LT")) return -1;
    if (!strcmp (name,"EQ")) return 0;
    if (!strcmp (name,"GT")) return 1;
    return 2;
}

//readCSV

//writeCSV

void toCSV (TABLE table,char* delim,char *filepath){
    GPtrArray *info = getInfo (table);
    int numColunas = tableGetNrCol (table);
    FILE *fp;
    fp = fopen (filepath,"w+");
    int size = tableGetLength (table);
    for (int i = 0; i < size; i+= numColunas){
        for (int u = 0; u < numColunas;u++){
            char *str = g_ptr_array_index (info,i*numColunas + u);
            fprintf (fp,"%s",str);
            if (u < numColunas -1) fprintf (fp,";");
            else fprintf (fp,"\n");
        }
    }
    fclose (fp);
}

int askFriend (){
    char auxStr[500];
    int out = 0;
    int with_friends = 0;
    clrscr ();
    while (out != 1)
    {
        printQuestionFriends ();
        if (fgets (auxStr,sizeof(auxStr),stdin));
        if (strlen (auxStr) == 2){
            if (auxStr[0] == 'Y') {
                with_friends = 1;
                out = 1;
            }
            if (auxStr[0] == 'N') {
                with_friends = 0; 
                out = 1;
            }
        }
    }
    return with_friends;
}


int controller (){
    printf(ESCONDE_CURSOR);
    char buffer = '\0';
    int out = 0;
    int option = 0,total_option = 9;
    int menu = 0, is_loaded = 0,is_init = 0;
    int help = 1;
    int page, totalpages, total;
    SGR sgr;
    char auxStr[512];
    GPtrArray* varsArray = g_ptr_array_new_with_free_func (freeVar);
    int sizeVarsArray = 0;
    TABLE table = NULL;
    char *sgr_name = "sgr";
    int commandLine = 0, input_ready = 0;
    int len = 0;
    clock_t begin, end;
    double timeSpent;
    char letter; 
    char*variable;
    int do_query = 0, show_result = 0;
    char *arg1 = NULL;
    float argFloat;
    int argInt;
    int with_friends = 0;
    char *tempVar;
    while (out != 1)
    {
        clrscr();
            switch (menu)
            {
            case 0:
                menuInicial();
                system("/bin/stty raw");
                buffer = getchar();
                system("/bin/stty cooked");
                if (buffer == ENTER) {
                    with_friends = askFriend ();
                    sgr = init_sgr ();
                    clrscr();
                    loadingScreen ();
                    begin = clock();
                    sgr = init_sgr();
                    if (load_sgr(sgr,with_friends) > 0){
                        clrscr();
                        printf ("INPUT FILES NEEDED\n");
                        enterToProceed ();
                        menu = 1;
                        break;
                    }
                    end = clock ();
                    clrscr ();
                    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                    waitEnter (0,timeSpent);
                    is_init = 1;
                    is_loaded = 1;
                    menu = 1;
                }
                break;
                case 1:
                prinMenu (option, total_option);
                if (option == 9) printQuit (1,help);
                else  printQuit (0,help);
                if (help != 1) help = 1;
                system("/bin/stty raw");
                buffer = getchar();
                system("/bin/stty cooked");
                if (buffer =='c') menu = -1; 
                if (option == 9 && buffer == ENTER) {
                    out = 1;
                    break;
                }
                else if (buffer == ENTER) {
                    if (!option || is_loaded){
                        menu = 2 + option;
                        option = 1; 
                        do_query = 1;
                        input_ready = 0;
                        show_result = 1;
                    }
                    else help = 2;
                }
                if (buffer == UP && option != 0)option--;
                if (buffer == DOWN && option < total_option )option++;
            break;
            case 2:
                printMenuQuery (menu - 1,option);   
                printMessageHelp (help);      
                if(help != 1) help = 1;     
                system("/bin/stty raw");
                buffer = getchar();
                system("/bin/stty cooked");
                if (buffer == UP && option != 1)option--;
                if (buffer == DOWN && option != 3)option++;
                if (buffer == '.') out = 1; 
                if (buffer == ENTER){
                    switch (option)
                    {
                    case 1:
                        clrscr ();
                        loadingScreen ();
                        begin = clock();
                        if (is_loaded)free_sgr (sgr);
                        end = clock();
                        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                        clrscr ();
                        waitEnter (2,timeSpent);
                        clrscr();
                        is_init = 1;
                        is_loaded = 0;
                        sgr=init_sgr ();
                        printf ("Business Path:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        if (strlen (auxStr)>1) setPathBusiness (sgr,auxStr);
                        printf ("User Path:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        if (strlen (auxStr)>1) setPathUser (sgr,auxStr);
                        printf ("Review Path:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        if (strlen (auxStr)>1) setPathReviews (sgr,auxStr);
                        break;
                    case 2:
                        if (!is_loaded){
                            with_friends = askFriend ();
                            clrscr();
                            loadingScreen ();
                            begin = clock();
                            sgr = init_sgr();
                            is_init = 1;
                            load_sgr(sgr,with_friends);
                            end = clock ();
                            clrscr ();
                            timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                            waitEnter (0,timeSpent);
                            is_loaded = 1;
                        }
                        else help = 2;
                        break;
                    case 3:
                        menu = 1;
                        option = 0;
                        break;
                    default:
                        break;
                    }
                }
                if (buffer == ENTER && option == 3){
                    menu = 1;
                    option = 0;
                }
                if (buffer == ENTER && option == 2){
                }
            break;
            case 3:
                if (do_query){
                    if (!input_ready){
                        printf(MOSTRA_CURSOR);
                        printf ("LETTER:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        if (strlen (auxStr)== 2 && isalpha(auxStr[0]))
                            letter = auxStr[0];
                        else{
                            if (waitInvalid () == 1) break;
                            else menu =1;
                            break;
                        }
                    }
                    else letter = arg1[1];
                    loadingScreen ();
                    begin = clock ();
                    table = query2 (sgr,letter);
                    end = clock ();
                    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                    if (commandLine){
                        Variables var = initVar (variable,table,menu,1);
                        g_ptr_array_add (varsArray,var);
                        sizeVarsArray++;
                    }
                    printf (ESCONDE_CURSOR);
                    waitEnter (1,timeSpent);
                }
                if (show_result){
                    page = 0;
                    int numColunas = tableGetNrCol (table);
                    total = tableGetLength(table)-numColunas;
                    totalpages = total/LINESFORINFO;
                    if (total %LINESFORINFO == 0) totalpages--;
                    buffer = 0;
                    printf(ESCONDE_CURSOR);
                    while (buffer != 'z')
                    {
                        clrscr ();
                        displayQuery2(table,page,totalpages);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == RIGHT && page < totalpages)page++;
                        if (buffer == LEFT && page > 0)page--;
                        if (buffer == 'p'){
                            printf(MOSTRA_CURSOR);
                            clrscr ();
                            displayQuery2(table,page,totalpages);
                            printf ("PAGE:");
                            int temppage;
                            scanf ("%d",&temppage);
                            if (temppage >= 0 && temppage <= totalpages) page = temppage;
                            printf (ESCONDE_CURSOR);
                        }
                    }
                }
                if (commandLine)menu = -1;
                else menu = 1;   
            break;
            case 4:
                if (do_query){
                    if (!input_ready){
                        printf (MOSTRA_CURSOR);
                        printf ("Business ID:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        printf (ESCONDE_CURSOR);
                        len = strlen (auxStr); 
                        auxStr [len -1] = 0;
                        arg1 = auxStr;
                    }
                    loadingScreen();
                    begin = clock ();
                    table = query3 (sgr,arg1);
                    end = clock ();
                    if (table){
                        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                        if (commandLine){
                            Variables var = initVar (variable,table,menu,1);
                            g_ptr_array_add (varsArray,var);
                            sizeVarsArray++;
                        }
                        waitEnter (1,timeSpent);
                    }
                    else {
                        if (waitInvalid () == 1) break;
                        else show_result = 0;
                    }
                }
                if (show_result){
                    buffer = 0;
                    while (buffer != ENTER){
                        printf (ESCONDE_CURSOR);
                        clrscr ();
                        displayQuery3 (table);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                    }
                }
                if (commandLine)menu = -1;
                else menu = 1;    
            break;
            case 5:
                if (do_query){
                    if (!input_ready){
                        printf (MOSTRA_CURSOR);
                        printf("User's ID:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        len = strlen (auxStr); 
                        auxStr [len -1] = 0;
                        arg1 = auxStr;
                    }
                    printf (ESCONDE_CURSOR);
                    page = 0;
                    loadingScreen ();
                    begin = clock ();
                    table = query4 (arg1,sgr);
                    end = clock ();
                    if (table){
                        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                        if (commandLine){
                            Variables var = initVar (variable,table,menu,2);
                            g_ptr_array_add (varsArray,var);
                            sizeVarsArray++;                            
                        }
                        waitEnter (1,timeSpent);
                    }
                    else
                    {
                        if (waitInvalid () == 1) break;
                        else show_result = 0;
                    }
                    
                }
                if (show_result){
                    page = 0;
                    int numColunas = tableGetNrCol (table);
                    len = tableGetLength (table)-numColunas;
                    totalpages = (len/2)/LINESFORINFO;
                    if (len/2%LINESFORINFO == 0) totalpages--;
                    buffer = 0;
                    printf (ESCONDE_CURSOR);
                    while (buffer != 'z'){
                        clrscr ();
                        displayQuery4 (table,page,totalpages);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == RIGHT && page < totalpages) page++;
                        if (buffer == LEFT && page > 0) page--; 
                        if (buffer == 'p'){
                            printf (MOSTRA_CURSOR);
                            clrscr ();
                            displayQuery4 (table,page,totalpages);
                            printf ("PAGE:");
                            int temppage;
                            scanf ("%d",&temppage);
                            if (temppage >= 0 && temppage <= totalpages) page = temppage;
                            printf (ESCONDE_CURSOR);
                        }
                    }
                }
                if (commandLine)menu = -1;
                else menu = 1;   
                break;
                case 6:
                if (do_query){
                    if (!input_ready){
                        printf (MOSTRA_CURSOR);
                        printf ("Cidade:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        len = strlen (auxStr); 
                        auxStr [len -1] = 0;
                        float stars;
                        printf ("Stars:");
                        scanf ("%f",&stars);
                        printf (ESCONDE_CURSOR);
                        arg1 =auxStr;
                        argFloat = stars;
                    }
                    loadingScreen ();
                    begin = clock ();
                    table = query5(arg1,argFloat,sgr);
                    end = clock ();
                    if (table){
                        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                        if (commandLine){
                            Variables var = initVar (variable,table,menu,2);
                            g_ptr_array_add (varsArray,var);
                            sizeVarsArray++;                            
                        }
                        waitEnter (1,timeSpent);
                    }
                    else{
                        if (waitInvalid () == 1) break;
                        else show_result = 0;
                    } 
                }
                if (show_result){
                    page = 0, total = tableGetLength (table)-len;
                    totalpages = total/2/LINESFORINFO;
                    if (total/2 %LINESFORINFO == 0)totalpages--;
                    printf (ESCONDE_CURSOR);
                    while (buffer != 'z')
                    {
                        clrscr ();
                        displayQuery5(table,page,totalpages);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == RIGHT && page < totalpages) page++;
                        if (buffer == LEFT && page > 0) page--;      
                            if (buffer == 'p'){
                                printf (MOSTRA_CURSOR);
                                clrscr ();
                                displayQuery5(table,page,totalpages);
                                printf ("PAGE:");
                                int temppage;
                                scanf ("%d",&temppage);
                                if (temppage >= 0 && temppage <= totalpages) page = temppage;
                                printf (ESCONDE_CURSOR);
                            }                    
                    }
                }
                if (commandLine)menu = -1;
                else menu = 1;   
            break;
            case 7:
                if (do_query){
                    if (!input_ready){
                        printf (MOSTRA_CURSOR);
                        printf ("Number of businesses:");
                        int num;
                        scanf ("%d",&num);
                        argInt = num;
                    }
                    clrscr ();
                    loadingScreen ();
                    begin = clock ();
                    table = query6(argInt,sgr);
                    end = clock ();
                    if (table){
                        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                        printf (ESCONDE_CURSOR);
                        if (commandLine){
                            Variables var = initVar (variable,table,menu,3);
                            g_ptr_array_add (varsArray,var);
                            sizeVarsArray++;                            
                        }
                        waitEnter (1,timeSpent);
                    }
                    else{
                        if (waitInvalid () == 1) break;
                        else show_result = 0;
                    } 
                }        
                if (show_result){
                    int numColunas = tableGetNrCol (table);
                    page = 0,totalpages = tableGetLength (table);
                    int city = 0;
                    buffer = 0;
                    printf (ESCONDE_CURSOR);
                    while (buffer != 'z'){
                        clrscr ();
                        printf ("%d | %d   | UP/DOWN to change city\n",city,totalpages-1);
                        displayQuery6 (table,city,page);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == DOWN && city < totalpages -1) {city++;page = 0;}
                        if (buffer == UP && city > 0) {city--;page = 0;} 
                        if (buffer == LEFT && page > 0) page--;
                        if (buffer == RIGHT) page += canRight (table,city,page); 
                    }   
                }
                if (commandLine)menu = -1;
                else menu = 1;       
            break;
            case 8:
                if (do_query){
                    clrscr ();
                    loadingScreen ();
                    begin = clock ();
                    table = query7 (sgr);
                    end = clock ();
                    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                    if (commandLine){
                        Variables var = initVar (variable,table,menu,1);
                        g_ptr_array_add (varsArray,var);
                        sizeVarsArray++;                            
                    }
                    waitEnter (1,timeSpent);
                }
                if (show_result){
                    int numColunas = tableGetNrCol (table);
                    total = tableGetLength (table) -numColunas;
                    page = 0,totalpages = tableGetLength (table)/LINESFORINFO;
                    buffer = 0;
                    printf (ESCONDE_CURSOR);
                    while (buffer != 'z')
                    {
                        clrscr ();
                        displayQuery7 (table,page,totalpages);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == LEFT && page > 0) page--;
                        if (buffer == RIGHT&& page < totalpages)page++;
                        if (buffer == 'p'){
                            printf (MOSTRA_CURSOR);
                            clrscr ();
                            displayQuery7(table,page,totalpages);
                            printf ("PAGE:");
                            int temppage;
                            scanf ("%d",&temppage);
                            if (temppage >= 0 && temppage <= totalpages) page = temppage;
                            printf (ESCONDE_CURSOR);
                        }
                    }
                }
                if (commandLine)menu = -1;
                else menu = 1;   
            break;
            case 9: 
                if (do_query){
                    if (!input_ready){
                        printf (MOSTRA_CURSOR);
                        printf ("Category:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        printf ("Number of Businesses:");
                        int number;
                        scanf ("%d",&number);
                        printf (ESCONDE_CURSOR);
                        len = strlen (auxStr); 
                        auxStr [len -1] = 0;
                        argInt = number;
                        arg1 = auxStr;
                    }
                    clrscr ();
                    loadingScreen ();
                    begin = clock ();
                    table = query8(argInt,arg1,sgr);
                    end = clock ();
                    if (table){
                        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                        if (commandLine){
                            Variables var = initVar (variable,table,menu,3);
                            g_ptr_array_add (varsArray,var);
                            sizeVarsArray++;           
                            setVarArg (var,arg1);                 
                        }
                        waitEnter (1,timeSpent);
                    }
                    else{
                        if (waitInvalid () == 1) break;
                        else show_result = 0;
                    } 
                }
                if (show_result){
                    int numColunas = tableGetNrCol (table);
                    total = tableGetLength (table) -numColunas;
                    page = 0,totalpages = total/3/LINESFORINFO;
                    if ((total/3)%LINESFORINFO == 0)totalpages--;
                    buffer = 0;
                    while (buffer != 'z')
                    {
                        clrscr ();
                        displayQuery8(table,page,totalpages,arg1);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == LEFT && page > 0) page--;
                        if (buffer == RIGHT&& page < totalpages)page++;
                        if (buffer == 'p'){
                            printf (MOSTRA_CURSOR);
                            clrscr ();
                            displayQuery8(table,page,totalpages,arg1);
                            printf ("PAGE:");
                            int temppage;
                            scanf ("%d",&temppage);
                            if (temppage >= 0 && temppage <= totalpages) page = temppage;
                            printf (ESCONDE_CURSOR);
                        }
                    }    
                }
                if (commandLine)menu = -1;
                else menu = 1;             
            break;
            case 10:
                if (do_query){
                    if (!input_ready){
                        printf (MOSTRA_CURSOR);
                        printf ("Word:");
                        if (fgets (auxStr,sizeof(auxStr),stdin));
                        len = strlen (auxStr); 
                        auxStr [len -1] = 0;
                        arg1 = auxStr;
                        printf (ESCONDE_CURSOR);
                    }
                    clrscr ();
                    loadingScreen ();
                    begin = clock ();
                    table = query9 (arg1,sgr);
                    end = clock ();
                    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                    if (commandLine){
                        Variables var = initVar (variable,table,menu,1);
                        g_ptr_array_add (varsArray,var);
                        sizeVarsArray++;       
                        setVarArg (var,arg1);                     
                    }
                    waitEnter (1,timeSpent);
                }
                if (show_result){
                    total = tableGetLength (table);
                    page = 0,totalpages = total/LINESFORINFO;
                    if (total%LINESFORINFO == 0)totalpages--;
                    buffer = 0;
                    while (buffer != 'z')
                    {
                        clrscr ();
                        displayQuery9(table,page,totalpages,arg1);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == LEFT && page > 0) page--;
                        if (buffer == RIGHT&& page < totalpages)page++;
                        if (buffer == 'p'){
                            printf (MOSTRA_CURSOR);
                            clrscr ();
                            displayQuery9(table,page,totalpages,arg1);
                            printf ("PAGE:");
                            scanf ("%d",&page);
                            printf(ESCONDE_CURSOR);
                        }
                    }    
                }
                if (commandLine)menu = -1;
                else menu = 1;   
            break;
            case -1:
                commandLine = 1;
                printf (MOSTRA_CURSOR);
                printCommandLine ();
                if (fgets (auxStr,sizeof(auxStr),stdin));
                if (!strchr (auxStr,';')) {
                    printf ("need ;\n");
                    enterToProceed ();
                    break;
                }
                char *line = strtok (auxStr,";");
                if (strchr (line,'=')){
                    variable = getVariable (strtok (line,"="));
                    if (!variable){
                        break;
                    }
                    char *rest = strtok (NULL,"");
                    if (strchr (rest,'(')){
                        char*strcommand = strtok (rest,"(");
                        int command = getCommand (strcommand);
                        if (command != -1){
                            rest = strtok (NULL,"");
                            switch (command)
                            {
                            case 0:
                            if (!is_init){
                                sgr = init_sgr ();
                                sgr_name = strdup (variable);
                                is_init = 1;
                                printf (ESCONDE_CURSOR);
                                enterToProceed ();
                                printf (MOSTRA_CURSOR);
                            }
                            //0 arguments
                            break;
                            case 1: 
                            if (!is_loaded){
                                if (!is_init) {
                                    //ERROR MESSAGE
                                    printf ("SGR is not initialized\n");
                                    break;
                                }
                                if (sgr_name){
                                    if (strcmp (sgr_name,variable))break;//errorMessage
                                }
                                else {
                                    if (strlen (rest) == 1){
                                        with_friends = askFriend ();
                                        clrscr ();
                                        printf(ESCONDE_CURSOR);
                                        loadingScreen ();
                                        begin = clock ();
                                        load_sgr (sgr,with_friends);
                                        end= clock();
                                        timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
                                        waitEnter (0,timeSpent);
                                        is_loaded = 1;
                                        printf (MOSTRA_CURSOR);
                                        break;
                                    }
                                    char *usersPath =   strtok (rest,",");
                                    char *busPath =     strtok (NULL,",");
                                    char *revPath =     strtok (NULL,")");
                                    setPathBusiness (sgr,busPath);
                                    setPathUser (sgr,usersPath);
                                    setPathReviews(sgr,revPath);
                                    with_friends = askFriend ();
                                    if (!load_sgr (sgr,with_friends)) is_loaded = 1;
                                    else {
                                        //printErrorMessage
                                        free_sgr (sgr);
                                        sgr = init_sgr ();
                                    }
                                }
                            }
                            //3 arguments 
                            break;
                            case 2:
                                if (is_loaded){
                                    if (strchr (rest,',')){
                                        char*tempSgrName = strtok (rest,",");
                                        char*letter = strtok (NULL,")");
                                        if (!strcmp (tempSgrName,sgr_name) && validLetter (letter)){
                                            arg1 = letter;
                                            menu = 3;
                                            input_ready = 1;
                                            do_query = 1;
                                            show_result = 0;
                                        }
                                    }
                                }   
                                else printf ("SGR IS NOT LOADED YET\n");
                            //2x arguments
                            break;
                            case 3:
                                if (is_loaded){
                                    if (strchr (rest,',')){
                                        char*tempSgrName = strtok (rest,",");
                                        char*bus_id = strtok (NULL,")");  
                                        if (!strcmp (tempSgrName,sgr_name) && validID (bus_id)){
                                            arg1 = bus_id;
                                            menu = 4;
                                            input_ready =1;
                                            do_query = 1; 
                                            show_result = 0;
                                        }
                                        else printf ("INVALID\n");
                                    }
                                }
                                else printf ("SGR IS NOT LOADED YET\n");
                            //2 arguments
                            break;
                            case 4:
                                if (is_loaded){
                                    if (strchr (rest,',')){
                                        char*tempSgrName = strtok (rest,",");
                                        char*user_id = strtok (NULL,")");  
                                        if (!strcmp (tempSgrName,sgr_name) && validID (user_id)){
                                            arg1 = user_id;
                                            menu = 5;
                                            input_ready =1;
                                            do_query = 1; 
                                            show_result = 0;
                                        }
                                        else printf ("INVALID\n");
                                    }
                                }
                                else printf ("SGR IS NOT LOADED YET\n");                           
                            //2 arguments
                            break;
                            case 5:
                                if (is_loaded){
                                    if (strchr (rest,',')){
                                        char*tempSgrName = strtok (rest,",");
                                        float stars = atof (strtok (NULL,","));
                                        char*city = strtok (NULL,")");  
                                        if (!strcmp (tempSgrName,sgr_name) && validStars (stars) && city){
                                            arg1 = city;
                                            argFloat = stars;
                                            menu = 6;
                                            input_ready =1;
                                            do_query = 1; 
                                            show_result = 0;
                                        }
                                        else printf ("INVALID\n");
                                    }
                                }
                                else printf ("SGR IS NOT LOADED YET\n");                               
                            //3 arguments
                            break;
                            case 6:
                                if (is_loaded){
                                    if (strchr (rest,',')){
                                        char*tempSgrName = strtok (rest,",");
                                        int tempInt = atoi(strtok (NULL,")"));  
                                        if (!strcmp (tempSgrName,sgr_name) && tempInt){
                                            argInt = tempInt; 
                                            menu = 7;
                                            input_ready =1;
                                            do_query = 1; 
                                            show_result = 0;
                                        }
                                        else printf ("INVALID\n");
                                    }
                                }
                                else printf ("SGR IS NOT LOADED YET\n");    
                            //2 arguments
                            break;
                            case 7:
                                if (is_loaded){
                                    if (strchr (rest,')')){
                                        char*tempSgrName = strtok (rest,")");
                                        if (!strcmp (tempSgrName,sgr_name)){
                                            menu = 8;
                                            do_query = 1; 
                                            show_result = 0;
                                        }
                                        else printf ("INVALID\n");
                                    }
                                }
                                else printf ("SGR IS NOT LOADED YET\n");   
                            //1 arguments
                            break;
                            case 8:
                                if (is_loaded){
                                    if (strchr (rest,')')){
                                        char*tempSgrName = strtok (rest,",");
                                        int tempInt = atoi (strtok (NULL,","));
                                        char *category = strtok (NULL,")");
                                        if (!strcmp (tempSgrName,sgr_name) && tempInt && category){
                                            arg1 = category;
                                            argInt = tempInt;
                                            menu = 9;
                                            do_query = 1; 
                                            show_result = 0;
                                            input_ready = 1;
                                        }
                                        else printf ("INVALID\n");
                                    }
                                }
                                else printf ("SGR IS NOT LOADED YET\n");   
                            //3 arguments
                            break;
                            case 9:
                                if (is_loaded){
                                    if (strchr (rest,')')){
                                        char*tempSgrName = strtok (rest,",");
                                        char *word = strtok (NULL,")");
                                        if (!strcmp (tempSgrName,sgr_name)  && word){
                                            arg1 = word;
                                            menu = 10;
                                            do_query = 1; 
                                            show_result = 0;
                                            input_ready = 1;
                                        }
                                        else printf ("INVALID\n");
                                    }
                                }
                                else printf ("SGR IS NOT LOADED YET\n");   
                            //3 arguments
                            break;
                            case 10:
                            //2 arguments
                            break;
                            case 11:
                            if (rest){
                                tempVar = strtok (rest,",");
                                char *colname = strtok (NULL,",");
                                char *value = strtok (NULL,","); 
                                char *oper = strtok (NULL,")");
                                char *argTemp = NULL;
                                int tempMenu = 0;
                                if (tempVar && colname && value && oper){
                                    TABLE temp = getTableVar (varsArray,tempVar,sizeVarsArray,&tempMenu,argTemp);
                                    int numColunas = tableGetNrCol (temp);
                                    int colNum = getColumn (table,colname,numColunas);
                                    int operator = getOperator (oper);
                                    if (colNum != -1){
                                        GPtrArray *new = g_ptr_array_new_with_free_func (free);
                                        addHeaders (new,table);
                                        TABLE result = filterTable (temp,colNum,numColunas,value,operator,new);
                                        if (result){
                                            Variables var = initVar (variable,result,11,numColunas);
                                            g_ptr_array_add (varsArray,var);
                                            sizeVarsArray++;
                                        }
                                    }
                                }
                                else {
                                    if (waitInvalid () == 1) break;
                                    else show_result = 0;
                                }
                            }
                            //4 arguments
                            break;  
                            case 12: 
                                tempVar = strtok (rest,",");
                                int col = atoi (strtok (NULL,")"));
                                int tempMenu = 0;
                                char *tempArg;
                                table = getTableVar (varsArray,tempVar,sizeVarsArray,&tempMenu,tempArg);
                                int numColunas = tableGetNrCol (table);
                                if (col < numColunas){
                                    TABLE result = projTable (table,col,numColunas);
                                    if (result){
                                        GPtrArray*info = getInfo (table);
                                        char* title = g_ptr_array_index (info,col);
                                        info = getInfo (result);
                                        g_ptr_array_insert (info,0,strdup(title));
                                        Variables var = initVar (variable,result,11,1);
                                        g_ptr_array_add (varsArray,var);
                                        sizeVarsArray++;
                                    }
                                }
                               printf ("Command proj is not implemented\n");
                            break;                        
                            default:
                                break;
                            }
                        }
                    }
                }
                page = 0;
                if (strstr (auxStr,"toCSV(")){
                    strtok (auxStr,"(");
                    tempVar = strtok (NULL,",");
                    char *tempDelim = strtok (NULL,",");
                    char *filepath = strtok (NULL,")");
                    char *tempArg;
                    int tempMenu;
                    if (tempVar && tempDelim && filepath){
                        TABLE temp = getTableVar (varsArray,tempVar,sizeVarsArray,&tempMenu,tempArg);
                        toCSV (temp,tempDelim,filepath);
                    }
                }
                //select command
                if (!strcmp ("quit",auxStr)) {
                   printf (ESCONDE_CURSOR);
                   menu = 1;
                   option =9;
                   commandLine = 0;
                }
                if (!strcmp ("help",auxStr)){
                    printf (ESCONDE_CURSOR);
                    buffer = 0;
                    while (buffer != ENTER)
                    {
                        clrscr ();
                        printHelp (page);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == RIGHT && !page) page++;
                        if (buffer == LEFT && page)page--;
                    }       
                }
                char*rest = strtok (line,"(");
                if (!strcmp (rest,"show")){
                    char *tempVar = strtok (NULL,")");
                    int tempMenu;
                    char *tempArg;
                    table = getTableVar (varsArray,tempVar,sizeVarsArray,&tempMenu,tempArg);
                    if (table){
                        if (tempArg) arg1 = tempArg;
                        printf (ESCONDE_CURSOR);
                        menu = tempMenu;
                        show_result = 1;
                        do_query = 0;
                    }
                }
                printf (ESCONDE_CURSOR);
                enterToProceed ();
                break;
            case 11:
                if (table){
                    page = 0;
                    int numColunas = tableGetNrCol (table);
                    int total = tableGetLength (table);
                    totalpages = (total-numColunas)/numColunas/LINESFORINFO;
                    if ((total-numColunas)/numColunas%LINESFORINFO == 0)totalpages--;
                    while (buffer != 'z')
                    {
                        clrscr ();
                        genericTable (table,page,totalpages);
                        system("/bin/stty raw");
                        buffer = getchar();
                        system("/bin/stty cooked");
                        if (buffer == RIGHT && page < totalpages)page++;
                        if (buffer == LEFT && page > 0)page--;
                        if (buffer == 'p'){
                            printf(MOSTRA_CURSOR);
                            clrscr ();
                            genericTable (table,page,totalpages);
                            printf ("PAGE:");
                            int temppage;
                            scanf ("%d",&temppage);
                            if (temppage >= 0 && temppage <= totalpages) page = temppage;
                            printf (ESCONDE_CURSOR);
                        }
                        if (buffer == 'z') menu = 1; 
                     }
                }
            break;
            case 12:

            break;
            default:
                break;
            }
        }
    begin = clock();
    clrscr ();
    loadingScreen ();
    if (is_loaded)free_sgr (sgr);
    g_ptr_array_free (varsArray,TRUE);
    end = clock();
    timeSpent = (double)(end - begin) / CLOCKS_PER_SEC;
    clrscr ();
    waitEnter (2,timeSpent);
    printf(MOSTRA_CURSOR);
    return 0;
}
            




/* 


Alterar  argumentos da tabela para, caso sejam strings se encontrarem dentro de aspas

Caso sejam variaveis ou números podem não ter aspas





*/
