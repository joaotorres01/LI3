#include "../Include/BusinessCatalog.h"

struct busCatalog
{
    GHashTable* AllBusiness;
};

BusinessCatalog initBCatalog (){
    BusinessCatalog Bcatalog = malloc (sizeof (struct busCatalog));
    Bcatalog->AllBusiness = g_hash_table_new_full (g_str_hash,g_str_equal,free,freeBusiness);
    return Bcatalog;
}


void insertBusiness (BusinessCatalog BCatalog,Business bus){
    char *id = Bget_business_id (bus);
    g_hash_table_insert (BCatalog->AllBusiness,id,bus);
}

void destroyBCatalog (BusinessCatalog BCatalog){
    g_hash_table_destroy(BCatalog->AllBusiness);
    free (BCatalog);
}


//TABLE
GPtrArray*  startedByLetter (BusinessCatalog BCatalog, char letter, int *length){
    GHashTableIter iter;
    gpointer key, value;
    g_hash_table_iter_init (&iter,BCatalog->AllBusiness);
    GPtrArray *array = g_ptr_array_new_with_free_func(free);
    while (g_hash_table_iter_next(&iter, &key, &value)){
        Business bus = (Business) value;
        char*name = Bget_name (bus);
        if (letter > 96) letter -= 32;
        if (name[0] == letter || name[0] == letter + 32){
            *length += 1;
            g_ptr_array_add (array,name);
        }
    }
    return array;
}



Business getBusiness (BusinessCatalog BCatalog,char * id){
    return (Business) g_hash_table_lookup (BCatalog->AllBusiness,id);
}

gboolean containsBusiness (BusinessCatalog BCatalog, char *id){
    return g_hash_table_contains (BCatalog->AllBusiness,id);
}


