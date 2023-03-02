#ifndef __BUSINESS___
#define __BUSINESS___

#include <glib.h>
#include <stdio.h>
#include <ctype.h>
#include "define.h"

/**
 * @brief Definição da struct business
 * 
 */
typedef struct business* Business;

/**
 * @brief Inicializa um negócio
 * 
 * @param businessId id do negócio
 * @param name nome
 * @param city cidade
 * @param state estado
 * @param array array com apontadores das categorias
 * @param num número de categorias
 * @return Business negócio
 */

Business initBusiness (char* businessId,char *name,char *city,char *state,GPtrArray *array, int num);

/**
 * @brief Liberta o espaço ocupado por um negócio
 * 
 * @param data apontador para um tipo de dado
 */

void freeBusiness (void *data);

/**
 * @brief Getter do id do negócio
 * 
 * @param bus negócio
 * @return char* id do negócio
 */

char *Bget_business_id (Business bus);

/**
 * @brief Getter do nome de um negócio
 * 
 * @param bus negócio
 * @return char* nome
 */

char *Bget_name (Business bus);

/**
 * @brief Getter da cidade de um negócio
 * 
 * @param bus negócio
 * @return char* cidade
 */

char *Bget_city (Business bus);

/**
 * @brief Getter do estado de um negócio
 * 
 * @param bus negócio
 * @return char* estado
 */

char *Bget_state (Business bus);
/**
 * @brief Getter do array das categorias de um negócio
 * 
 * @param bus negócio
 * @return GPtrArray* array de apontadores das categorias
 */

GPtrArray* Bget_categories (Business bus);
/**
 * @brief Getter do número de categorias de um negócio
 * 
 * @param bus negócio
 * @return int número de categorias
 */

int Bget_numCategories (Business bus);

/**
 * @brief Transforma uma linha do ficheiro num negócio
 * 
 * @param line linha
 * @return Business negócio
 */
Business strToBusiness (char *line);

#endif