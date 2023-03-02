#ifndef ___REVIEW__
#define ___REVIEW__


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "define.h"
#include "glib.h"

/**
 * @brief Definição da struct Review
 * 
 */
typedef struct review* Review;

/**
 * @brief Inicialização da review recebendo os seus parametros
 * 
 * @param review_id id da review
 * @param user_id id do user
 * @param business_id id do negócio
 * @param stars estrelas
 * @param useful quão util a review foi
 * @param funny quão engraçada a review foi
 * @param cool quão fixe a review foi
 * @param date data 
 * @param text texto da review
 * @return Review 
 */

Review initReview (char *review_id,char *user_id,char *business_id,float stars,int useful,int funny,int cool,char* date,char*text);

/**
 * @brief Imprime a review
 * 
 * @param review review
 */

void printReview (Review review);

/**
 * @brief Liberta o esapço ocupado pela review em memória
 * 
 * @param data apontador para um tipo de dado
 */

void freeReview (void *data);

/**
 * @brief Getter do id da review
 * 
 * @param review review
 * @return char* id da review
 */

char* Rget_review_id (Review review);

/**
 * @brief Getter do id do user
 * 
 * @param review review
 * @return char* id do user
 */
char* Rget_user_id (Review review);

/**
 * @brief Getter do id do negócio
 * 
 * @param review review
 * @return char* id do negócio
 */

char* Rget_business_id (Review review);

/**
 * @brief Getter das estrelas
 * 
 * @param review review
 * @return char* estrelas
 */

float Rget_stars (Review review);

/**
 * @brief Getter do useful
 * 
 * @param review review
 * @return int useful
 */

int Rget_useful (Review review);

/**
 * @brief Getter do engraçado
 * 
 * @param review review
 * @return int engraçado
 */

int Rget_funny (Review review);

/**
 * @brief Getter do cool
 * 
 * @param review review
 * @return char* cool
 */

int Rget_cool (Review review);

/**
 * @brief Getter da data
 * 
 * @param review review
 * @return char* data da review
 */

char* Rget_date (Review review);

/**
 * @brief Getter do texto da review
 * 
 * @param review review
 * @return char* texto
 */

char* Rget_text (Review review);

/**
 * @brief Transforma uma linha do ficheiro numa review
 * 
 * @param line linha
 * @return Review review
 */

Review strToReview (char *line);


#endif
