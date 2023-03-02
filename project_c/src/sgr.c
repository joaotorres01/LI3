#include "../Include/sgr.h"

struct sgr {
    char* pathBusiness;
    BusinessCatalog AllBusiness;
    char* pathUsers;
    UserCatalog AllUsers;
    char* pathReviews;
    ReviewCatalog AllReviews;
    Stats stats;
};


void setPathBusiness (SGR sgr,char *pathBus){
    if (sgr->pathBusiness) free (sgr->pathBusiness);
    sgr->pathBusiness = strdup (pathBus);
}

void setPathUser (SGR sgr,char *pathUser){
    if (sgr->pathUsers) free (sgr->pathUsers);
    sgr->pathUsers = strdup (pathUser);
}

void setPathReviews (SGR sgr,char *pathReviews){
    if (sgr->pathReviews) free (sgr->pathReviews);
    sgr->pathReviews= strdup (pathReviews);
}

char * getPathBusiness (SGR sgr){
    return strdup(sgr->pathBusiness);
}

char * getPathUsers (SGR sgr){
    return strdup(sgr->pathBusiness);
}

char * getPathReviews (SGR sgr){
    return strdup(sgr->pathReviews);
} 

void free_sgr (SGR sgr){
    destroyBCatalog (sgr->AllBusiness);
    destroyUCatalog (sgr->AllUsers);
    destroyRCatalog (sgr->AllReviews);
    free (sgr->pathBusiness);
    free (sgr->pathUsers);
    free (sgr->pathReviews);
    destroyStats (sgr->stats);
    free (sgr);
}

SGR init_sgr (){
    SGR sgr = malloc (sizeof (struct sgr));
    sgr->AllBusiness = initBCatalog ();
    sgr->pathBusiness = strdup("../input_files/business_full.csv");
    sgr->AllUsers = initUCatalog ();
    sgr->pathUsers = strdup ("../input_files/users_full.csv");
    sgr->AllReviews = initRCatalog ();
    sgr->pathReviews = strdup ("../input_files/reviews_1M.csv");
    sgr->stats = initStats ();
    return sgr;
}

void ler_Business (SGR sgr, FILE *fp){
    BusinessCatalog Bcatalog = sgr->AllBusiness;
    size_t buffsize = INT_MAX; // a pensar
    char *line = malloc (sizeof (char)* INT_MAX); 
    if (!fgets (line,buffsize,fp)); //IGNORAR PRIMEIRA LINHA
    int size = 0;
    for (int i = 0; 1;i++){
        if (!fgets (line,buffsize,fp)) break;
        line = strtok (line,"\n");
        Business business = strToBusiness (line);
        insertBusiness (Bcatalog,business);
        updateCityStat (sgr->stats,business);
        size++;
    }
    fclose (fp);
    free (line);
}


void ler_Reviews(SGR sgr,FILE *fp){
    ReviewCatalog RCatalog = sgr->AllReviews;
    size_t buffsize = INT_MAX;
    char *line = malloc (sizeof (char)* INT_MAX);
    if (!fgets (line,buffsize,fp)); //IGNORAR PRIMEIRA LINHA
    int size = 0;
    for (int i = 0;1;i++){
        if (!fgets (line,buffsize,fp)) break;
        line = strtok (line,"\n");
        Review review = strToReview (line);
        gboolean valid = validateReview (review,sgr->AllBusiness,sgr->AllUsers);
        if (valid){
            insertReview (RCatalog,review);
            updateStats (sgr->stats,review);
            size++;
        }
    }
    free(line);
    fclose (fp);
}

void ler_Users (SGR sgr,FILE *fp, int with_friends){
    UserCatalog UCatalog = sgr->AllUsers;
    size_t buffsize = INT_MAX;
    char *line = malloc (sizeof (char)* INT_MAX);
    int size = 0;
    if (!fgets (line,buffsize,fp)); //IGNORAR PRIMEIRA LINHA
    for (int i = 0;1;i++){
        if (!fgets (line,buffsize,fp)) break;
        line = strtok (line,"\n");
        User user = strToUser (line,with_friends);
        insertUser (UCatalog,user);
        size++;
    }
    free (line);
    fclose (fp);
}


int load_sgr (SGR sgr,int with_friends){
    FILE *fp1,*fp2,*fp3;
    fp1 = fopen (sgr->pathBusiness,"r");
    fp2 = fopen (sgr->pathUsers,"r");
    fp3 = fopen (sgr->pathReviews,"r");
    if (!fp1) return 1;
    if (!fp2) return 2;
    if (!fp3) return 3;
    ler_Business   (sgr,fp1);
    ler_Users      (sgr,fp2,with_friends);
    ler_Reviews    (sgr,fp3);
    return 0;
}


gboolean sgrContainsUser (SGR sgr, char *user_id){
    return containsUser (sgr->AllUsers,user_id);
}


//Determinar a lista de nomes de negócios e o número total de negócios cujo nome inicia por uma dada letra. Note que a procura não deverá ser case sensitive.

//TABLE: 1 coluna com nomes de negócios + Total

TABLE query2 (SGR sgr, char letter){
    int length = 0;
    GPtrArray* array = startedByLetter (sgr->AllBusiness,letter,&length);
    g_ptr_array_insert (array,0,strdup ("business_id"));
    TABLE table = initTable (array,length + 1,1);
    return table;
}

//Dado um id de negócio, determinar a sua informação: nome, cidade, estado, stars, e número total reviews.

//TABLE: Informação de negócio (nome,cidade,estado,stars,número total de Reviews)

TABLE query3 (SGR sgr, char *id){
    BusinessCatalog BCatalog = sgr->AllBusiness;
    Business bus;
    GPtrArray *info = g_ptr_array_new_with_free_func(free);
    TABLE table = NULL;
    if ((bus = getBusiness (BCatalog,id))){
        float *mediaStars = malloc (sizeof (float));
        int *totalReviews = malloc (sizeof (int));
        *mediaStars = getMediaStars (sgr->stats,id);
        *totalReviews = getTotalReviews (sgr->stats,id);
        g_ptr_array_add (info,strdup("business_id"));
        g_ptr_array_add (info,strdup("name"));
        g_ptr_array_add (info,strdup("city"));
        g_ptr_array_add (info,strdup("state"));
        g_ptr_array_add (info,strdup("stars"));
        g_ptr_array_add (info,strdup("totalReviews"));
        g_ptr_array_add (info,strdup(id));
        g_ptr_array_add (info,Bget_name (bus));
        g_ptr_array_add (info,Bget_city (bus));
        g_ptr_array_add (info,Bget_state (bus));
        g_ptr_array_add (info,mediaStars);
        g_ptr_array_add (info,totalReviews);
        table = initTable (info,12,6); 
    }
    return table;
}

//Dado um id de utilizador, determinar a lista de negócios aos quais fez review. A informação associada a cada negócio deve ser o id e o nome.

//TABLE: 2 colunas Business(ID | Nome)

TABLE query4 (char *id, SGR sgr){
    BusinessCatalog BCatalog = sgr->AllBusiness;
    int length = 0;
    GPtrArray* array = userReviews (id,sgr->stats,BCatalog,&length);
    if (!array) return NULL;
    g_ptr_array_insert (array,0,strdup("business_id"));
    g_ptr_array_insert (array,1,strdup("name"));
    TABLE table = initTable (array,length + 2,2);
    return table;
}

//Dado um número n de stars e uma cidade, determinar a lista de negócios com n ou mais stars na dada cidade. A informação associada a cada negócio deve ser o seu id enome.

//TABLE: 2 colunas com Business (ID | nome) 

TABLE query5 (char *cidade,float stars,SGR sgr){
    BusinessCatalog BCatalog = sgr->AllBusiness;
    int length = 0;
    GPtrArray *array =  businessWithStartCity (sgr->stats,BCatalog,cidade,stars, &length);
    if (!array) return NULL;
    g_ptr_array_insert (array,0,strdup("business_id"));
    g_ptr_array_insert (array,1,strdup("name"));
    TABLE table = initTable (array,length + 2,2);
    return table;
}

//Dado um número inteiro n, determinar a lista dos top n negócios (tendo em conta o número médio de stars) em cada cidade. A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.

//TABLE: 3 colunas com Business (ID | nome | stars)

TABLE query6 (int num,SGR sgr){
    BusinessCatalog BCatalog = sgr->AllBusiness;
    int length = 0;
    GPtrArray* array = topBusinessEveryCity(sgr->stats,num,BCatalog,&length);
    TABLE table = initTable (array,length,3);
    return table;
}


//Determinar a lista de ids de utilizadores e o número total de utilizadores que tenham visitado mais de um estado, i.e. que tenham feito reviews em negócios de diferentes estados.

//TABLE: Lista de utilizadores | Total

TABLE query7 (SGR sgr){
    BusinessCatalog BCatalog = sgr->AllBusiness;
    int length = 0;
    GPtrArray* array = internationalUsers(sgr->stats,BCatalog,&length);
    g_ptr_array_insert (array,0,strdup("user_id"));
    TABLE table = initTable (array,length,1);
    return table;
}

// Dado um número inteiro n e uma categoria, determinar a lista dos top n negócios (tendo em conta o número médio de stars) que pertencem a uma determinada categoria. A informação associada a cada negócio deve ser o seu id, nome, e número de estrelas.

//TABLE: 3 colunas com Business (ID | Nome | Stars)


TABLE query8 (int n, char* category, SGR sgr){
    BusinessCatalog BCatalog = sgr->AllBusiness;
    int length = 0;
    GPtrArray* array = topBusinessWithCategory(sgr->stats,BCatalog,n,category,&length);
    if (!array) return NULL;
    g_ptr_array_insert (array,0,strdup("business_id"));
    g_ptr_array_insert (array,1,strdup("name"));
    g_ptr_array_insert (array,2,strdup("stars"));
    TABLE table = initTable (array,length + 3,3);
    return table;
}


TABLE query9 (char* word, SGR sgr){
    int length = 0;
    GPtrArray* array = reviewsWithWord (sgr->AllReviews,word,&length);
    if (!array) return NULL;
    g_ptr_array_insert (array,0,strdup("review_id"));
    TABLE table = initTable (array,length + 1,1);
    return table;
}
