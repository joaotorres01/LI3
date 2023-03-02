#include "../Include/stats.h"


struct stats {
    GHashTable* UserStats;      // key: user_id         value:UserStat
    GHashTable* BusStats;       // key: business_id     value:BusStat
    GHashTable* CityStats;      // key: city            value:CidadeStat
    GHashTable* CategoryStats;  // key: category        value:CategoryStat 
};

typedef struct busStat
{
    float stars;
    int numReviews;
    GHashTable *info; //key:review_id       
} *BusStat;


typedef struct userStat
{
    GHashTable *info; //key:review_id       
    int numReviews;
} *UserStat;


typedef struct cityStat
{
    GHashTable *info; //key: business_id    
} *CityStat;

typedef struct categoryStat
{
    GHashTable *info; //key: business_id 
} *CategoryStat;

//CategoryStat

void freeCategoryStat (void *data){
    CategoryStat catStat = (CategoryStat) data;
    g_hash_table_destroy (catStat->info);
    free (catStat);
}


CategoryStat initCategoryStat (){
    CategoryStat new= malloc (sizeof (struct categoryStat));
    new->info = g_hash_table_new_full (g_str_hash,g_str_equal,free,NULL);
    return new;
}

void insertyCategoryStat (CategoryStat catStat, Business business){
    char *bus_id = Bget_business_id (business);
    g_hash_table_add (catStat->info,bus_id);
}

//CityStat 

void freeCityStat (void *data){
    CityStat cStat = (CityStat) data;
    g_hash_table_destroy (cStat->info);
    free (cStat);
}

CityStat initCityStat (){
    CityStat new = malloc (sizeof (struct cityStat)); 
    new->info = g_hash_table_new_full (g_str_hash,g_str_equal,free,NULL);
    return new; 
}

void insertCityStat (CityStat cStat, Business business){
    char*bus_id = Bget_business_id (business);
    g_hash_table_add (cStat->info,bus_id);
}

//BusStat

void freeBusStat (void *data){
    BusStat bRev = (BusStat) data;
    g_hash_table_destroy (bRev->info);
    free (bRev);
}

BusStat initBusStat (){
    BusStat new = malloc (sizeof (struct busStat));
    new->info = g_hash_table_new_full (g_str_hash,g_str_equal,free,NULL);
    new->stars = 0; 
    new->numReviews = 0; 
    return new;
}

void insertBusStat (BusStat bRev,Review review){
    g_hash_table_add (bRev->info,Rget_review_id (review));
    bRev->stars += Rget_stars (review);
    bRev->numReviews += 1;
}


//UserStat

void freeUserStat (void *data){
    UserStat uRev = (UserStat) data;
    g_hash_table_destroy (uRev->info);
    free (uRev);
}


UserStat initUserStat (){
    UserStat new = malloc (sizeof (struct userStat));
    new->info = g_hash_table_new_full (g_str_hash,g_str_equal,free,NULL);
    new->numReviews = 0;
    return new;
}

void insertUserStat (UserStat uRev,Review review){
    char *bus_id = Rget_business_id (review);
    uRev->numReviews += 1;
    if (!g_hash_table_contains (uRev->info,bus_id)){
        g_hash_table_add (uRev->info,bus_id);
    }
    else free (bus_id);
}


//STATS 

Stats initStats (){
    Stats new = malloc (sizeof (struct stats));
    new->BusStats       = g_hash_table_new_full (g_str_hash,g_str_equal,free,freeBusStat);
    new->UserStats      = g_hash_table_new_full (g_str_hash,g_str_equal,free,freeUserStat);
    new->CityStats      = g_hash_table_new_full (g_str_hash,g_str_equal,free,freeCityStat);
    new->CategoryStats  = g_hash_table_new_full (g_str_hash,g_str_equal,free,freeCategoryStat);
    return new;
}

void destroyStats (Stats stats){
    g_hash_table_destroy (stats->BusStats); 
    g_hash_table_destroy (stats->UserStats); 
    g_hash_table_destroy (stats->CityStats);
    g_hash_table_destroy (stats->CategoryStats);
    free (stats);
}

void StatAddBusStat (Stats st, Review review, char *bus_id){
    int need_free = 1;
    if (!g_hash_table_contains (st->BusStats,bus_id)){
        BusStat new = initBusStat ();
        g_hash_table_insert (st->BusStats,bus_id,new);
        need_free = 0;
    }
    BusStat bRev =(BusStat) g_hash_table_lookup (st->BusStats,bus_id);
    insertBusStat (bRev,review);
    if (need_free) free (bus_id);
}

void StatAddUserStat (Stats st,Review review, char *user_id){
    int need_free = 1;
    if (!g_hash_table_contains (st->UserStats,user_id)){
        UserStat new = initUserStat ();
        g_hash_table_insert (st->UserStats,user_id,new);
        need_free = 0;
    }
    UserStat uRev = (UserStat) g_hash_table_lookup (st->UserStats,user_id);
    insertUserStat (uRev,review);
    if (need_free) free (user_id);
}

void StatAddCityStat (Stats st, Business bus){
    int need_free = 1;
    char *city = Bget_city (bus);
    if (!g_hash_table_contains (st->CityStats,city)){
        CityStat new = initCityStat ();
        g_hash_table_insert (st->CityStats,city,new);
        need_free = 0;
    }
    CityStat cStat = (CityStat) g_hash_table_lookup  (st->CityStats,city);
    insertCityStat (cStat,bus);
    if (need_free) free (city);
}


void StatAddCategoryStat (Stats st, Business bus){
    int length = Bget_numCategories (bus);
    GPtrArray*array = Bget_categories (bus);
    for (int i = 0; i < length;i++){
        char *category = (char *)g_ptr_array_index (array,i);
        if (!g_hash_table_contains (st->CategoryStats,category)){
            CategoryStat new = initCategoryStat ();
            g_hash_table_insert (st->CategoryStats,strdup(category),new);
        }
        CategoryStat catStat = (CategoryStat) g_hash_table_lookup (st->CategoryStats,category);
        insertyCategoryStat (catStat,bus);
    }
}

void updateStats (Stats st, Review review){
    StatAddBusStat (st,review,Rget_business_id(review));
    StatAddUserStat (st,review,Rget_user_id(review));
}

void updateCityStat (Stats st,Business bus){
    StatAddCityStat (st,bus);
    StatAddCategoryStat (st,bus);
}


float getMediaStars (Stats stats, char *bus_id){
    BusStat bStat = g_hash_table_lookup (stats->BusStats,bus_id);
    return bStat ? bStat->stars/(float)bStat->numReviews : 0;
}

int getTotalReviews (Stats stats,char *bus_id){
    BusStat bStat = g_hash_table_lookup (stats->BusStats,bus_id);
    return bStat->numReviews;
}



int validateReview (Review review, BusinessCatalog BCatalog, UserCatalog UCatalog){
    int valid = 1;
    char *user_id = Rget_user_id (review);
    char *business_id = Rget_business_id(review);
    if (!containsUser (UCatalog,user_id)) valid = 0;
    if (valid && !containsBusiness( BCatalog,business_id))valid = 0;
    free (user_id);
    free (business_id);
    return valid;
}

GPtrArray* userReviews (char *id,Stats stats,BusinessCatalog BCatalog,int *size){
    UserStat reviews = (UserStat) g_hash_table_lookup (stats->UserStats,id);
    guint length = 0;
    gpointer* gKeysArray = g_hash_table_get_keys_as_array (reviews->info,&length);
    GPtrArray* array = g_ptr_array_new ();
    char** keysArray = (char**)gKeysArray;
    for (guint i = 0; i < length;i++){
        Business bus = getBusiness (BCatalog,keysArray[i]);
        g_ptr_array_add (array,Bget_business_id(bus));
        g_ptr_array_add (array,Bget_name(bus));
        *size += 2;
    }
    return array;
}


GPtrArray* businessWithStartCity (Stats stats,BusinessCatalog BCatalog, char *cidade, float stars, int *size){
    CityStat cityBus = (CityStat) g_hash_table_lookup (stats->CityStats,cidade);
    guint length = 0;
    gpointer* gKeysArray = g_hash_table_get_keys_as_array(cityBus->info,&length);
    char** keysArray = (char**)gKeysArray;
    GPtrArray *array = g_ptr_array_new_with_free_func (free);
    for (guint i = 0; i < length; i++){
        char *bus_id = keysArray[i];
        float busStars = getMediaStars (stats,bus_id);
        if (busStars > stars){
            Business bus = getBusiness (BCatalog,bus_id);
            char *name = Bget_name (bus);
            g_ptr_array_add (array,strdup (bus_id));
            g_ptr_array_add (array,name);
            *size += 2;
            }
        }   
    return array;
}


struct displayQ6 {
    char *cidade;
    GPtrArray* info;
    int length; 
};

char *Q6getCidade (DisplayQ6 display){
    return display->cidade;
}

GPtrArray* Q6getInfo (DisplayQ6 display){
    return display->info;
}

int Q6getlength (DisplayQ6 display){
    return display->length;
}

void freeDisplayQ6 (void * data){
    DisplayQ6 display = (DisplayQ6) data;
    g_ptr_array_free (display->info,TRUE);
    free (display->cidade);
    free (display);
}

DisplayQ6 initQ6 (){
    DisplayQ6 new = malloc (sizeof (struct displayQ6));
    new->info = g_ptr_array_new_with_free_func (free);
    new->length = 0;
    return new;
}
gint compareCity (gconstpointer a,gconstpointer b){
    DisplayQ6 q1 = *((DisplayQ6*) a);
    DisplayQ6 q2 = *((DisplayQ6*) b);
    char *cidade1 = (q1->cidade);
    char *cidade2 = (q2->cidade);
    return (strcmp (cidade1,cidade2));
}


gint compareStars (gconstpointer a,gconstpointer b, gpointer user_data){
    GHashTable* busStat = (GHashTable *) user_data;
    char* str1 = *((char**)a);
    char* str2 = *((char**)b);
    BusStat first =     g_hash_table_lookup (busStat,str1);
    BusStat second =    g_hash_table_lookup (busStat,str2);
    float fstmedia = 0,sndmedia= 0;
    if (first)     fstmedia = first->stars/first->numReviews;
    if (second)    sndmedia =second->stars/second->numReviews;
    if (fstmedia == sndmedia && fstmedia){
        if (first->numReviews > second->numReviews) return 1;
        if (first->numReviews < second->numReviews) return -1;
    }
    if (fstmedia > sndmedia) return 1;
    if (fstmedia < sndmedia) return -1;
    return 0;
}

void charArraytoPtrArray (char**cArray, GPtrArray* ptrArray,guint length){
    for (guint i = 0; i < length;i++)
        g_ptr_array_add(ptrArray,cArray[i]);
}


GPtrArray* topBusinessEveryCity (Stats stats,int num,BusinessCatalog BCatalog,int *size){
    GHashTable* AllCityStat = stats->CityStats;
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter,AllCityStat);
    GPtrArray *resultArray = g_ptr_array_new_with_free_func (freeDisplayQ6);
    while (g_hash_table_iter_next(&iter,&key,&value))
    {
        GPtrArray *array = g_ptr_array_new ();
        DisplayQ6 display = initQ6 ();
        char*cidade = (char *) key;
        display->cidade = strdup (cidade);
        CityStat cityStat = (CityStat) value;
        guint length = 0;
        char** char_array = (char **)g_hash_table_get_keys_as_array (cityStat->info,&length);
        charArraytoPtrArray (char_array,array,length);
        g_ptr_array_sort_with_data (array,compareStars,stats->BusStats);
        int insert = 0;
        for (int i = length -1, u = 0; i >= 0 && u < num; i--,u++){
            char *bus_id = g_ptr_array_index (array,i);
            Business bus = getBusiness (BCatalog,bus_id);
            char *name = Bget_name (bus);
            float mediaStars = getMediaStars (stats,bus_id);
            if (mediaStars){
                insert = 1;
                GPtrArray *displayArray = display->info;
                char *number = malloc (sizeof (char) *4);
                sprintf(number, "%.1f", mediaStars);
                g_ptr_array_add (displayArray,strdup (bus_id));
                g_ptr_array_add (displayArray,name);
                g_ptr_array_add (displayArray,number);
                display->length += 3;
            }
        }
        free (char_array);
        if (insert){
            g_ptr_array_add (resultArray,display);
            *size += 1;
        }
        else freeDisplayQ6 (display);
        g_ptr_array_free (array,FALSE);
    }
    g_ptr_array_sort (resultArray,compareCity);
    return resultArray;
}


GPtrArray* internationalUsers (Stats stats,BusinessCatalog BCatalog,int *size){
    GHashTable* users = stats->UserStats;
    GHashTableIter iter;
    gpointer key, value;
    GPtrArray *resultArray = g_ptr_array_new_with_free_func (free);
    g_hash_table_iter_init (&iter,users);
    while (g_hash_table_iter_next(&iter,&key,&value)){
        UserStat uStat = (UserStat) value;
        char *user_id = (char*) key;
        guint length = 0;
        char **array = (char **)g_hash_table_get_keys_as_array(uStat->info,&length);
        if (length){
            Business bus = getBusiness (BCatalog,array[0]);
            char *state = Bget_state (bus);
            for (int i = 1;i < length;i++){
                Business other_bus = getBusiness (BCatalog,array[i]);
                char * other_state = Bget_state (other_bus);
                if (strcmp (state,other_state)){
                    g_ptr_array_add (resultArray,strdup (user_id));
                    *size += 1;
                    break;
                }
            }
        }
    }
    return resultArray;
}



GPtrArray* topBusinessWithCategory(Stats stats,BusinessCatalog BCatalog, int num, char *category,int *size){
    GHashTable *categories = stats->CategoryStats;
    CategoryStat catStat = g_hash_table_lookup (categories,category);
    if (!catStat) return NULL;
    guint length = 0;
    gpointer* gKeysArray = g_hash_table_get_keys_as_array (catStat->info,&length);
    char** keysArray = (char**)gKeysArray;
    GPtrArray* array = g_ptr_array_new ();
    GPtrArray*result = g_ptr_array_new_with_free_func (free); 
    charArraytoPtrArray (keysArray,array,length);
    g_ptr_array_sort_with_data (array,compareStars,stats->BusStats);
    for (guint i = length -1,u = 0; i >= 0 && u < num; i--,u++){
        char *bus_id = g_ptr_array_index (array,i);
        Business bus = getBusiness (BCatalog,bus_id);
        float mediaStars = getMediaStars (stats,bus_id);
        if (mediaStars) {
            char *name = Bget_name (bus);
            char *number = malloc (sizeof (char) *4);
            sprintf(number, "%.1f", mediaStars);
            g_ptr_array_add (result, strdup(bus_id));
            g_ptr_array_add (result, name);
            g_ptr_array_add (result,number);
            *size += 3;
        } 
    }
    free (keysArray);
    return result;
}
