package Model;

import Model.Exceptions.InputInvalidoException;
import Utils.ParIdCount;
import Utils.Query7Ouput;
import Utils.TripleIdMediaCount;

import java.util.*;

public interface StatsStructInterface {
    /**
     * Setter do número total de negócios
     * @param size Número total de negócios
     */
    void setTotalBusiness(int size);

    /**
     * Setter do  número total de users
     * @param size Número total de users
     */
    void setTotalUser(int size);

    /**
     * Método que incrementa o número toal de reviews erradas
     */
    void incrementWrongReviews();

    /**
     * Método que dá update das structs dada um negócio
     * @param business Negócio
     */
    void updateStructs(Business business);

    /**
     * Método que dá update das structs dada uma review
     * @param review Review
     * @param businessAvaliado boolean que diz se foi avaliado ou não
     * @param userAvaliado boolean que diz se fez reviews ou não
     */
    void updateStructs(Review review, boolean businessAvaliado, boolean userAvaliado);

    /**
     * Getter dos Stats
     * @return Stats
     */
    Stats getStats();

    /**
     * Método que calcula os negócios mais avaliados dado um user
     * @param user_id Id do user
     * @return Lista com pares dos ids do negócios e as vezes avaliado
     * @throws InputInvalidoException
     */
    List<ParIdCount> businessMaisAvaliaods(String user_id) throws InputInvalidoException;

    /**
     * Método que retorna uma lista dos users ordenados por mais reviews distintas feitas dado um x
     * @param number Número de reviews dado pelo user
     * @return lista dos users ordenados por mais reviews distintas feitas e o seu respetivo valor
     */
    List<ParIdCount> usersUniqueBusiness(int number);

    /**
     * Método que retorna as n reviews mais avaliadas dado um id do negócio/user
     * @param id Id do negócio/user
     * @param number N reviews
     * @return Lista de TripleIdMediaCount
     * @throws InputInvalidoException
     */
    List<TripleIdMediaCount> businessMaisAvaliaods(String id, int number) throws InputInvalidoException;

    /**
     * Método que determina para cada cidade, estado a estado a média de classificação dos diferentes negócios
     * @return Map que associa a cada estado as cidades e a cada cidade, o id do négocio, média e quantos negócios foram feitos
     */
    Map<String, Map<String,List<TripleIdMediaCount>>> eachBusinessAllCity();

    /**
     * Método que determina para cada cidade os top 3 negócios com mais números de reviews
     * @return Lista com os 3 negócios para cada cidade
     */
    List<Query7Ouput> best3City();
}
