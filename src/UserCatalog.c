#include "../Include/UserCatalog.h"


struct userCatalog
{
    GHashTable* AllUsers;
};


UserCatalog initUCatalog (){
    UserCatalog UCatalog = malloc (sizeof (struct userCatalog));
    UCatalog->AllUsers = g_hash_table_new_full (g_str_hash,g_str_equal,free,freeUser);
    return UCatalog;
}


void insertUser (UserCatalog UCatalog,User user){
    g_hash_table_insert (UCatalog->AllUsers,Uget_user_id (user),user);
}

void destroyUCatalog (UserCatalog UCatalog){
    g_hash_table_destroy(UCatalog->AllUsers);
    free (UCatalog);
}


User getUser (UserCatalog UCatalog,char * id){
    return (User) g_hash_table_lookup (UCatalog->AllUsers,id);
}


gboolean containsUser (UserCatalog UCatalog,char *id){
    return g_hash_table_contains (UCatalog->AllUsers,id);
}
