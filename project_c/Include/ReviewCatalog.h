#ifndef __REVIEW__CATALOG__
#define __REVIEW__CATALOG__

#include "review.h"
#include <ctype.h>
#include "define.h"

/**
 * @brief Definição da struc ReviewCatalog
 */

typedef struct reviewCatalog* ReviewCatalog;

/**
 * @brief Inicializa o ReviewCatalog
 * 
 * @return ReviewCatalog Catálogo de Reviews
 */

ReviewCatalog initRCatalog ();

/**
 * @brief Insere no Catálogo de Reviews a review dada
 * 
 * @param RCatalog Catálogo de Reviews
 * @param review review
 */

void insertReview (ReviewCatalog RCatalog,Review review);

/**
 * @brief Destroi a HashTable que define o catalogo
 * 
 * @param RCatalog Catálogo de Reviews
 */

void destroyRCatalog (ReviewCatalog RCatalog);

/**
 * @brief Getter do review
 * 
 * @param RCatalog Catálogo de Reviews
 * @param id id do review
 * @return Review review
 */

Review getReview (ReviewCatalog RCatalog,char * id);

/**
 * @brief Verifica se tem no catálogo uma dada review dado o seu id
 * 
 * @param RCatalog Catálogo de Reviews
 * @param id id do review
 * @return gboolean 
 */

gboolean containsReview (ReviewCatalog RCatalog,char *id);



/**
 * @brief Retorna um array de apontadores com as reviews id que contêm uma certa palavra no campo text
 * 
 * @param RCatalog Catálogo de Reviews
 * @param word palavra
 * @param size endereço da length do array que vamos devolver
 * @return GPtrArray* array com apontadores das review id pedidas
 */

GPtrArray* reviewsWithWord (ReviewCatalog RCatalog, char* word, int *size);

#endif
