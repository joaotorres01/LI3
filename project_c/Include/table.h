#ifndef __TABLE__
#define __TABLE__

#include <glib.h>
#include "define.h"

/**
 * @brief Defenição da TABLE
 * 
 */
typedef struct table* TABLE;

/**
 * @brief Getter da Info da Table 
 * 
 * @param table table
 * @return GPtrArray* array de apontador
 */
GPtrArray* getInfo (TABLE table);

/**
 * @brief Inicializa uma TABLE recebendo os seus parametros
 * 
 * @param array array com a info
 * @param length tamanho da table
 * @param numColunas numero de colunas
 * @return TABLE table
 */

TABLE initTable (GPtrArray *array,int length,int numColunas);

/**
 * @brief Getter do tamanho da Table
 * 
 * @param table table
 * @return int tamanho da table
 */

int tableGetLength (TABLE table);
/**
 * @brief Liberta o espaço ocupado pela Table
 * 
 * @param table table
 */

void clearTable (TABLE table);

/**
 * @brief Getter do nr de colunas
 * 
 * @param table table
 * @return int nr de colunas da table
 */

int tableGetNrCol (TABLE table);
#endif