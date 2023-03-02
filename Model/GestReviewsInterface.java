package Model;

import Model.Exceptions.InputInvalidoException;
import Utils.*;

import java.io.*;
import java.util.List;
import java.util.Map;

public interface GestReviewsInterface {

    /**
     * Método que faz a leituras dos 3 tipos de ficheiros com o respetivo tempo de leitura
     */
    void lerFicheirosToGestReviews ();

    /**
     * Leitura do ficheiro dos negócios
     * @param nomeFich Nome do ficheiro
     */
    void lerBusiness(String nomeFich);

    /**
     * Leitura do ficheiro dos users
     * @param nomeFich nome do ficheiro
     * @param friends com ou sem amigos
     */
    void lerUsers(String nomeFich, boolean friends);

    /**
     * Leitura do ficheiro das reviews
     * @param nomeFich nome do ficheiro
     */
    void lerReviews(String nomeFich);

    /**
     * Guardar a gestReviews como objeto num ficheiro
     * @param objectPath
     * @throws IOException
     */
    void savebject(String objectPath) throws IOException;

    static GestReviewsInterface loadObject(String objectPath) throws IOException, ClassNotFoundException {
        FileInputStream fis = new FileInputStream(objectPath);
        BufferedInputStream bif = new BufferedInputStream(fis);
        ObjectInputStream ois = new ObjectInputStream(bif);
        GestReviews gestReviews = (GestReviews) ois.readObject();
        ois.close();
        return gestReviews;
    }

    /**
     * Método que realiza a query 1
     * @return Lista ordenada alfabeticamente com os identificadores dos negócios nunca avaliados
     */
    List<String> query1();

    /**
     * Método que realiza a query 2
     * @param ano Ano
     * @param mes Mês
     * @return Lista com número total global de reviews realizadas nesse ano e mês
     * @throws InputInvalidoException
     */
    List<Integer> query2(int ano, int mes)throws InputInvalidoException;

    /**
     * Método que realiza a query 3
     * @param user_id Id do user
     * @return Lista com reviews, negócios distintos avaliados e a nota média atribuida em cada mês
     * @throws InputInvalidoException
     */
    List<Query3Output> query3(String user_id)throws InputInvalidoException;

    /**
     * Método que realiza a query 4
     * @param business_id Id do negócio
     * @return Lista com reviews, negócios distintos avaliados e a nota média atribuida em cada mês
     * @throws InputInvalidoException
     */
    List<Query3Output> query4(String business_id)throws InputInvalidoException;

    /**
     * Método que realiza a query 5
     * @param user_id Id do user
     * @return Lista de nomes de negócios mais avaliados eo seu total
     * @throws InputInvalidoException
     */
    List<ParIdCount> query5(String user_id) throws InputInvalidoException;

    /**
     * Método que realiza a query 6
     * @param number Número de negócios
     * @return Lista com os X negócios mais avaliados, com o respetivo número total de users que o avaliaram, por ano
     */
    Map<Integer, List<ParIdCount>> query6(int number);

    /**
     * Método que realiza a query 7
     * @return Lista com os 3 negócios com mais número de reviews, por ano
     */
    List<Query7Ouput> query7();

    /**
     * Método que realiza a query 8
     * @param number Número de users
     * @return Lista com os X users com mais negócios distintos avaliados
     */
    List<ParIdCount> query8(int number);

    /**
     * Método que realiza a query 9
     * @param id Id
     * @param number Número de users
     * @return Lista com os users que mais o avaliaram e para cada um o valor médio de classificação
     * @throws InputInvalidoException
     */
    List<TripleIdMediaCount> query9(String id, int number) throws InputInvalidoException;

    /**
     * Método que realiza a query 10
     * @return
     */
    Map<String, Map<String, List<TripleIdMediaCount>>> query10();

    /**
     * Método responsável por reunir a informação necessária para as Estatísticas
     * @return O Output para a visualização
     */
    StatsOutput showStats ();
}
