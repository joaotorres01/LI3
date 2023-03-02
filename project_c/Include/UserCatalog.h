#ifndef __USER__CATALOG__
#define __USER__CATALOG__

#include "user.h"
#include <stdio.h>
#include "define.h"

/**
 * @brief Definição do Catálogo de utilizadores
 */

typedef struct userCatalog* UserCatalog;

/**
 * @brief Inicialização do Catálogo de utilizadores
 * 
 * @return UserCatalog Catálogo de utilizadores
 */

UserCatalog initUCatalog ();

/**
 * @brief Insere um user no Catálogo de utilizadores
 * 
 * @param UCatalog Catálogo de utilizadores
 * @param user user
 */

void insertUser (UserCatalog UCatalog,User user);

/**
 * @brief Destroi a HashTable que difine o Catálogo de utilizadores
 * 
 * @param UCatalog Catálogo de utilizadores
 */

void destroyUCatalog (UserCatalog UCatalog);

/**
 * @brief Getter de um user do Catálogo de utilizadores fornecendo o user id
 * 
 * @param UCatalog Catálogo de utilizadores
 * @param id user id
 * @return User 
 */

User getUser (UserCatalog UCatalog,char * id);

/**
 * @brief Função que verifica se exite um user no Catálogo de utilizadores
 * 
 * @param UCatalog Catálogo de utilizadores
 * @param id user id
 * @return gboolean 
 */

gboolean containsUser (UserCatalog UCatalog,char *id);

void numFriends (UserCatalog UCatalog);

#endif
