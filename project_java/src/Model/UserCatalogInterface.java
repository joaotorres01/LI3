package Model;

public interface UserCatalogInterface {
    /**
     * Método que adiciona um user ao catálogo
     * @param user User
     */
    void addToCatalogo(UserInterface user);

    /**
     * Verifica se já contem o user no catálogo
     * @param id id do user
     * @return true ou false
     */
    boolean containsUser(String id);

    /**
     * Método que calcula o tamanho do catálogo
     * @return Tamanho do catálogo
     */
    int size();

    /**
     * Getter do User
     * @param id Id do user
     * @return User
     */
    UserInterface getUser(String id);

    /**
     * Método que verifica se um user já foi avaliado e se já retorna falso (ou vice-versa)
     * @param id Id do user
     * @return true ou false
     */
    boolean updateAvaliado(String id);
}
