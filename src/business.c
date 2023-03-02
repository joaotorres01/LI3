#include "../Include/business.h"

struct business
{
    char *business_id;
    char *name;
    char *city;
    char *state;
    GPtrArray *categories;
    int numCategories;
};

static gint compareStringsGPtrArray(gconstpointer a, gconstpointer b) {
    char* s1 = *((char**)a);
    char* s2 = *((char**)b);
    return strcmp(s1, s2);
}

void renameCity (char *city){
    for (int i = 1; city[i];i++){
        if (isalnum(city[i])&& city[i] < 91 && isalpha(city[i-1]))city[i] += 32;
    }
}

void renameName (char *name){
    for (int i = 0;name[i];i++)
        if (!isalnum(name[i]) && !ispunct(name[i]) && !isspace(name[i]))name[i] = '*';
}

Business strToBusiness (char *line){
    char *businessId = strtok (line,";");
    char *name = strtok (NULL,";");
    renameName (name);
    char *city = strtok (NULL,";");
    renameCity (city);
    char *state = strtok (NULL,";");
    GPtrArray *array = g_ptr_array_new();
    char *category;
    int num = 0;
    while ((category = strtok (NULL,","))){
        g_ptr_array_add(array,strdup(category));
        num++;
    }
    Business business = initBusiness (businessId,name,city,state,array,num);
    return business;
}


Business initBusiness (char* businessId,char *name,char *city,char *state,GPtrArray *array,int num){
    Business newBusiness = malloc (sizeof (struct business));
    newBusiness->business_id= strdup(businessId);
    newBusiness->name = strdup(name);
    newBusiness->city = strdup (city);
    newBusiness->state = strdup (state);
    g_ptr_array_sort (array,compareStringsGPtrArray);
    newBusiness->categories = array;
    newBusiness->numCategories = num;
    return newBusiness;
}


void freeBusiness (void *data){
    Business bus = (Business)data;
    free (bus->business_id);
    free (bus->name);
    free (bus->city);
    free (bus->state);
    g_ptr_array_set_free_func(bus->categories,free);
    g_ptr_array_free (bus->categories,TRUE);
    free (bus);
}


//GETTER

char *Bget_business_id (Business bus){
    return strdup(bus->business_id);
}

char *Bget_name (Business bus){
    return strdup(bus->name);
}

char *Bget_city (Business bus){
    return strdup(bus->city);
}

char *Bget_state (Business bus){
    return strdup(bus->state);
}

GPtrArray* Bget_categories (Business bus){
    return bus->categories;
}

int Bget_numCategories (Business bus){
    return bus->numCategories;
}
