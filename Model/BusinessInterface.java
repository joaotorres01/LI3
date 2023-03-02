package Model;

import java.util.ArrayList;

public interface BusinessInterface {

    /**
     * get o id do negocio
     * @return respetivo id
     */
    String getBusiness_id();

    /**
     * get o nome do negocio
     * @return respetivo nome
     */
    String getName();

    /**
     * get a cidade do negocio
     * @return respetiva cidade
     */
    String getCity();

    /**
     * get o estado do negocio
     * @return respetivo estado
     */
    String getState();

    /**funçao que determina se um negocio ja foi avaliado
     *
     * @return true se já foi avaliado; false caso contrário
     */
    boolean getAvaliado();

    /**
     * Muda o estado de avaliado do negócio
     * @param avaliado true (avalidado) or false (não avaliado)
     */
    void setAvaliado(boolean avaliado);

    /**
     * get a lista de categorias
     * @return lista de categorias
     */
    ArrayList<String> getCategories();
}