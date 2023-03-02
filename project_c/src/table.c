
#include "../Include/table.h"


struct table
{
    GPtrArray* info;
    int length; 
    int numColunas;
};



TABLE initTable (GPtrArray *array,int length,int numColunas){
    TABLE table = malloc (sizeof (struct table)); 
    table->length = length;
    table->info = array;
    table->numColunas = numColunas;
    return table;
}


GPtrArray* getInfo (TABLE table){
    return table->info;
}

int tableGetLength (TABLE table){
    return table->length;
}

int tableGetNrCol (TABLE table){
    return table->numColunas; 
}

void clearTable (TABLE table){
    if (table){
        g_ptr_array_free (table->info,TRUE);
        free (table);
        table = NULL;
    }
}