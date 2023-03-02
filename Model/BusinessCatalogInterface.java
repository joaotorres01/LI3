package Model;

import java.util.ArrayList;
import java.util.List;
import java.util.Set;
import java.util.TreeSet;

public interface BusinessCatalogInterface {
    boolean updateAvaliado (String businessId);


    /**
     * verifica os businesses que não foram avaliados
     * @return lista desses businesses
     */
    List<String> naoAvaliados ();


    /**
     * determina o nome de um negocio a partir de um user_id
     * @param id business_id
     * @return retorna o respetivo nome do business
     */
    String getNome (String id);


    /**
     * adicona um negocio ao catalogo de negocios
     * @param bus da-se um negocio como argumento
     */
    void addToCatalogo(Business bus);


    /**
     * Determina o tamanho do catalgo
     * @return respetivo tamanho
     */
    int size();


    /**
     * Verifica se o catalogo de negocios contem um determinado negocio
     * @param business_id da-se como argumento um id de um negocio
     * @return retorna true se contem; false caso contrario
     */
    boolean containsId(String business_id);
}
