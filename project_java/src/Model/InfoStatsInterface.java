package Model;

import Model.Exceptions.InputInvalidoException;
import Utils.ParIdCount;
import Utils.TripleIdMediaCount;

import java.util.*;

public interface InfoStatsInterface {


    /**
     * Método que atualiza a info, dado um id de um user e de um business (ou vice-versa) e a sua nota
     * @param id Id do negócio/user
     * @param id_info Id do user/negócio
     * @param nota Nota
     */
    void updateInfo(String id, String id_info, Double nota);

    /**
     * Getter da info de um determinado id
     * @param id Id do negócio/user
     * @return Info do id
     * @throws InputInvalidoException Caso não exista o id dado
     */
    Info getInfo(String id) throws InputInvalidoException;

    /**
     * Método que retorna uma lista dos users ordenados por mais reviews distintas feitas dado um x
     * @param number Tamanho para a lista
     * @return Lista com o id e as reviews distintas feitas
     */
    List<ParIdCount> uniqueIds(int number);

    /**
     * Método que retorna as n reviews mais avaliadas dado um id do negócio/user
     * @param id Id do negócio/user
     * @param number N reviews
     * @return Lista de TripleIdMediaCount
     * @throws InputInvalidoException Caso não exista o id dado
     */
    List<TripleIdMediaCount> maisAvaliados(String id, int number) throws InputInvalidoException;

    /**
     * Getter do número total de Reviews
     * @param id
     * @return
     */
    int getTotalReviews(String id);

    /**
     * Getter da nota média dado um id
     * @param id Id do negócio/user
     * @return Nota média
     */
    double notaMedia(String id);

    /**
     * Verifica se contém um dado id
     * @param id Id do negócio/user
     * @return true ou false
     */
    boolean containsId(String id);
}
