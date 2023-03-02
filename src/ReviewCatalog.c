

#include "../Include/ReviewCatalog.h"

struct reviewCatalog
{
    GHashTable* AllReviews;
};


ReviewCatalog initRCatalog (){
    ReviewCatalog RCatalog = malloc (sizeof (struct reviewCatalog));
    RCatalog->AllReviews = g_hash_table_new_full (g_str_hash,g_str_equal,free,freeReview);
    return RCatalog;
}


void insertReview (ReviewCatalog RCatalog,Review review){
    g_hash_table_insert (RCatalog->AllReviews,Rget_review_id (review),review);
}

void destroyRCatalog (ReviewCatalog RCatalog){
    g_hash_table_destroy(RCatalog->AllReviews);
    free (RCatalog);
}


Review getReview (ReviewCatalog RCatalog,char * id){
    return (Review) g_hash_table_lookup (RCatalog->AllReviews,id);
}


gboolean containsReview (ReviewCatalog RCatalog,char *id){
    return g_hash_table_contains (RCatalog->AllReviews,id);
}

GPtrArray* reviewsWithWord (ReviewCatalog RCatalog, char* word, int *size){
    GPtrArray *array = g_ptr_array_new_with_free_func (free);
    guint length = 0;
    char **keys_array = (char **) g_hash_table_get_keys_as_array (RCatalog->AllReviews,&length);
    for (guint i = 0; i < length;i++){
        char *review_id = keys_array[i];
        Review review = getReview (RCatalog,review_id);
        char *text = Rget_text (review), *ret;
        int len = strlen (word);
        while ((ret = strstr (text,word))){
            char prev = ret[-1];
            char next = ret[len];
            if (ret == text || ispunct(prev) || isspace (prev))
                if (!next ||ispunct (next) || isspace (next)){
                    g_ptr_array_add (array,strdup (review_id));
                    *size += 1;
                    break;
                }
            if (text == ret) text++;
            else text = ret; 
        }
    }
    return array;
}
