
#ifndef ___BUS_CATALOG__
#define ___BUS_CATALOG__

#include "business.h"
#include "define.h"

/**
 * @brief Definição da struc BusinessCatalog
 */

typedef struct busCatalog* BusinessCatalog;

/**
 * @brief Insere no Catálogo de Negócios o negócio dado
 * 
 * @param catalog Catálogo de Negócios
 * @param bus negócio
 */

void insertBusiness (BusinessCatalog catalog,Business bus);

/**
 * @brief Inicializa o BusinessCatalog (Construtor)
 * 
 * @return BusinessCatalog Catálogo de Negócios
 */

BusinessCatalog initBCatalog ();

/**
 * @brief Destroi a HashTable que define o catálogo
 * 
 * @param BCatalog Catálogo de Negócios
 */

void destroyBCatalog (BusinessCatalog BCatalog);

/**
 * @brief Função que dada uma letra devolve os ids dos negócios começados por essa letra
 * 
 * @param BCatalog Catálogo de Negócios
 * @param letter letra
 * @param length endereço da length do array
 * @return GPtrArray* array de apontadores dos ids dos negócios
 */

GPtrArray* startedByLetter (BusinessCatalog BCatalog, char letter, int *length);

/**
 * @brief Getter do negócio
 * 
 * @param BCatalog Catálogo de Negócios
 * @param id key do negócio
 * @return Business negócio
 */

Business getBusiness (BusinessCatalog BCatalog,char * id);

/**
 * @brief Verifica se tem no catalogo um dado negócio dado o seu id
 * 
 * @param BCatalog Catálogo de Negócios
 * @param id id do negócio
 * @return gboolean 
 */

/**
 * @brief Verifica se o catálogo contém certo Business
 * 
 * @param BCatalog Catálogo de Business
 * @param id id do Business
 * @return true contem o Business
 */
gboolean containsBusiness (BusinessCatalog BCatalog, char *id);

#endif