package Model;

import java.time.LocalDate;

public interface ReviewInterface {

    /**
     * get o id da review
     * @return respetivo id
     */
    String getReview_id();

    /**
     * get o id do user
     * @return respetivo user
     */
    String getUser_id();

    /**
     * get o id do negócio
     * @return respetivo negócio
     */
    String getBusiness_id();

    /**
     * get o número de estrelas
     * @return respetivo número de estrelas
     */
    double getStars();

    /**
     * getter do usefull
     * @return respetiva classificação dada
     */
    int getUseful();

    /**
     * getter do funny
     * @return respetiva classificação dada
     */
    int getFunny();

    /**
     * getter do cool
     * @return respetiva classificação dada
     */
    int getCool();

    /**
     * getter da data
     * @return respetiva data
     */
    LocalDate getDate();

    /**
     * getter do texto da review
     * @return respetiva texto
     */
    String getText();
}
