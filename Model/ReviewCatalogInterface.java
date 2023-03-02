package Model;

import Model.Exceptions.InputInvalidoException;
import Utils.ParIdCount;

import java.util.*;

public interface ReviewCatalogInterface {

    /**
     * Adiciona uma review ao respetivo catalogo
     * @param review uma review
     */
    void addToCatalogo(Review review);

    /**
     * Verifica se um id de um negócio está inserida no catálogo de reviews
     * @param id business id
     * @return true se o catalogo contem o a review analisada; false caso contrário
     */
    boolean containsBusiness(String id);

    /**
     * Dado um user_id ou um business_id, determinar para os 12 meses independentemente do ano,
     * a informação do numero de reviews  e do numero distinto de Businesses ou Users, respetivamente.
     * @param id id de um User ou de um Business
     * @param isUser true para users; false para business
     * @return informação dos 12 meses
     */
    Info[] byMonth(String id, boolean isUser);

    /**
     * Determina o número total global de reviews realizadas e o número total de users
     * distintos que as realizaram, dado um ano e um mês
     * @param ano ano que queremos analisar
     * @param mes mes que queremos analisar
     * @return lista como o numero total de reviews e os users
     * @throws InputInvalidoException exceção caso não haja reviews nesse mês
     */
    List<Integer> reviewsAnoMes(int ano, int mes)throws InputInvalidoException;

    /**
     * Determina o conjunto dos X negócios mais avaliados (com mais reviews) em cada
     * ano, indicando o número total de distintos utilizadores que o avaliaram (X é um
     * inteiro dado pelo utilizador);
     * @param number X
     * @return Lista com os negocios mais avaliados do ano
     */
    Map<Integer, List<ParIdCount>> maisAvaliadoAno(int number);

    /**
     * Método que organiza a informação de estatísticas relativamente aos 12 meses do ano
     * @return A informação dod 12 meses
     */
    Info[] showStats();
}
