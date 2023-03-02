package Model;

import java.util.ArrayList;

public interface UserInterface {
    /**
     * Getter do id do user
     * @return Id do user
     */
    String getUser_id();

    /**
     * Getter do nome do user
     * @return Nome do user
     */
    String getName();

    /**
     * Getter dos friends
     * @return Lista com os id dos friends
     */
    ArrayList<String> getFriends();

    /**
     * Verfica se um user já foi avaliado
     * @return true ou false
     */
    boolean getAvaliado();

    /**
     * Setter do avaliado dado um booleano
     * @param avaliado true ou false
     */
    void setAvaliado(boolean avaliado);

}
