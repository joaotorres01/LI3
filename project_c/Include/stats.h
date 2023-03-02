#ifndef ___STATS___
#define ___STATS___


#include "BusinessCatalog.h"
#include "ReviewCatalog.h"
#include "UserCatalog.h"
#include "define.h"

/**
 * @brief Definição da struct stats
 */
typedef struct stats* Stats;

/**
 * @brief Definição da struct Display da Query 6
 */

typedef struct displayQ6* DisplayQ6;

/**
 * @brief Getter da cidade a através do display
 * 
 * @param display display
 * @return char* cidade
 */

char *Q6getCidade (DisplayQ6 display);

/**
 * @brief Getter da info a através do display
 * 
 * @param display display
 * @return GPtrArray* array de apontadores
 */

GPtrArray* Q6getInfo (DisplayQ6 display);

/**
 * @brief Getter da length do array de apontadores atarvés do display
 * 
 * @param display display
 * @return int tamanho do array
 */

int Q6getlength (DisplayQ6 display);

/**
 * @brief Inicialização do tipo stats (Construtores)
 * 
 * @return Stats 
 */

Stats initStats ();
/**
 * @brief Função que detroi as hashtables que definem o tipo stats
 * 
 * @param stats stats
 */

void destroyStats (Stats stats);

/**
 * @brief Função que adiciona ao BusStats e ao UserStats o id da review dada
 * 
 * @param st stats
 * @param review review
 */

void updateStats (Stats st, Review review);

/**
 * @brief Função que adiciona ao CityStat e ao CategoryStat o id do negócio dado
 * 
 * @param st stats
 * @param bus negócio
 */

void updateCityStat (Stats st,Business bus);

/**
 * @brief Getter que calcula a media das estrelas a partir de um stats e dado o id do negócio
 * 
 * @param stats stats
 * @param bus_id id do negócio
 * @return float média de estrelas
 */

float getMediaStars (Stats stats, char *bus_id);

/**
 * @brief Getter que retorna o número total de reviews dado um stats e um id do negócio
 * 
 * @param stats stats
 * @param bus_id id do negócio
 * @return int numero total de reviews
 */

int getTotalReviews (Stats stats,char *bus_id);

/**
 * @brief 
 * 
 * @param review 
 * @param BCatalog 
 * @param UCatalog 
 * @return int   
 */

int validateReview (Review review, BusinessCatalog BCatalog, UserCatalog UCatalog);

GPtrArray* userReviews (char *id,Stats stats,BusinessCatalog BCatalog,int *size);

GPtrArray* businessWithStartCity (Stats stats,BusinessCatalog BCatalog, char *cidade, float stars, int *size);

GPtrArray* topBusinessEveryCity (Stats stats,int num,BusinessCatalog BCatalog,int *size);

GPtrArray* internationalUsers (Stats stats,BusinessCatalog BCatalog,int *size);

GPtrArray* topBusinessWithCategory(Stats stats,BusinessCatalog BCatalog, int num, char *category,int *size);

int validateReview (Review review, BusinessCatalog BCatalog, UserCatalog UCatalog);

#endif