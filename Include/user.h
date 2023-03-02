#ifndef ___USER___
#define ___USER___

#include <glib.h>
#include "define.h"

/**
 * @brief Definição da struct user
 * 
 */

typedef struct user* User;

/**
 * @brief Liberta espaço ocupado pelo user
 * 
 * @param data apontador para um tipo de data
 */

void freeUser (void * data);

/**
 * @brief Inicializa o user recebndo os seus parametros
 * 
 * @param User_id id do user
 * @param name nome
 * @param friends amigos
 * @param numFriends número de amigos
 * @return User user
 */

User initUser (char * User_id, char * name, GPtrArray * friends,int numFriends);
/**
 * @brief Getter do id do user 
 * 
 * @param user user
 * @return char* id do user
 */
char* Uget_user_id (User user);
/**
 * @brief Getter do nome do user
 * 
 * @param user user
 * @return char* nome
 */

char* Uget_name (User user);

/**
 * @brief Getter dos amigos do user
 * 
 * @param user user
 * @return GPtrArray* array com os apontadores dos ids dos amigos
 */

GPtrArray* Uget_friends (User user);

/**
 * @brief Transforma uma linha do ficheiro num user com ou sem amigos
 * 
 * @param line linha
 * @param with_friends representa se quer ler os amigos do user
 * @return User user
 */

User strToUser (char * line,int with_friends);
/**
 * @brief Getter do número de amigos
 * 
 * @param user user
 * @return int número de amigos
 */
int Uget_numFriends (User user);

#endif