package Model;

public interface StatsInterface {
    /**
     * Getter do número total de reviews erradas
     * @return Número de Reviews erradas
     */
    int getWrongReviews();

    /**
     * Getter do número total de Negócios
     * @return Número total de Negócios
     */
    int getTotalBusiness();

    /**
     * Getter do número total de negócios revisados
     * @return Número total de negócios revisados
     */
    int getTotalBusinessReviewed();

    /**
     * Getter do número total de users
     * @return Número total de users
     */
    int getTotalUser();

    /**
     * Getter do número total de users ativos
     * @return Número total de users ativos
     */
    int getTotalUserActive();

    /**
     * Getter do número total de reviews com 0 impacto
     * @return Número total de reviews
     */
    int getNoImpactReviews();

    /**
     *  Método que incrementa o número total de negócios revisados
     */
    void incrementBusinessReviewd();

    /**
     * Método que incrementa o número total de users ativos
     */
    void incrementUserActive();

    /**
     * Método que incrementa o número total de reviews erradas
     */
    void incrementWrongReviews();

    /**
     * Método que incrementa o número total de reviews com 0 impacto
     */
    void incrementNoImpactReviews();

    /**
     * Setter do número total de users
     * @param totalUser Número total de users
     */
    void setTotalUser(int totalUser);

    /**
     * Setter do número total de negócios
     * @param totalBusiness
     */
    void setTotalBusiness(int totalBusiness);

    /**
     * Clone do Stats
     * @return Stats
     */
    Stats clone();
}
