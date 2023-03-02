package Model;

import Utils.ParReview;

import java.util.List;
import java.util.Map;

public interface InfoInterface {
    /**
     * Método que calcula o tamanho do map que contém os ids
     * @return Tamanho do mapa
     */
    int sizeIds();

    /**
     * Getter do número total de Reviews
     * @return Número total de Reviews
     */
    int getTotalReviews();

    /**
     * Getter da nota média das reviews
     * @return Nota média das reviews
     */
    double getNotaMedia();

    /**
     * Getter a nota total
     * @return Nota total
     */
    double getNotaTotal();

    /**
     * Método que atualiza a entrada de uma review na Info
     * @param id Id do user/business
     * @param nota Nota da review
     */
    void updateInfo(String id, double nota);

    /**
     * Clone da Info
     * @return Nova Info
     */
    Info clone();

    /**
     * Método que ordena por ordem descrescente o map com os ids conforme o número de reviews, caso seja igual por orden alfabética
     * @return Lista com um par String e ParReview
     */
    List<Map.Entry<String,ParReview>> ordenadoDecresente();
}
