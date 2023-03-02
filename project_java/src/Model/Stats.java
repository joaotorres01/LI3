package Model;

import java.io.Serializable;

public class Stats implements StatsInterface,Serializable {
    private static final long serialVersionUID = -4141706953901057388L;
    private int wrongReviews;
    private int totalBusiness;
    private int totalBusinessReviewed;
    private int totalUser;
    private int totalUserActive;
    private int noImpactReviews;

    //              Constructors                //

    public Stats(){
        this.wrongReviews = 0;
        this.totalBusiness = 0;
        this.totalBusinessReviewed = 0;
        this.totalUser = 0;
        this.totalUserActive = 0;
        this.noImpactReviews = 0;
    }

    public Stats(int wrongReviews, int totalBusiness, int totalBusinessReviewed, int totalUser,
                 int totalUserActive, int noImpactReviews){
        this.wrongReviews = wrongReviews;
        this.totalBusiness = totalBusiness;
        this.totalBusinessReviewed = totalBusinessReviewed;
        this.totalUser = totalUser;
        this.totalUserActive = totalUserActive;
        this.noImpactReviews = noImpactReviews;
    }

    public Stats(Stats stats){
        this.wrongReviews = stats.getWrongReviews();
        this.totalBusiness = stats.getTotalBusiness();
        this.totalBusinessReviewed = stats.getTotalBusinessReviewed();
        this.totalUser = stats.getTotalUser();
        this.totalUserActive = stats.getTotalUserActive();
        this.noImpactReviews = stats.getNoImpactReviews();
    }

    //              Getters and Setters                //

    public void setTotalUser(int totalUser) {
        this.totalUser = totalUser;
    }

    public void setTotalBusiness(int totalBusiness) {
        this.totalBusiness = totalBusiness;
    }

    public int getWrongReviews() {
        return wrongReviews;
    }

    public int getTotalBusiness() {
        return totalBusiness;
    }

    public int getTotalBusinessReviewed() {
        return totalBusinessReviewed;
    }

    public int getTotalUser() {
        return totalUser;
    }

    public int getTotalUserActive() {
        return totalUserActive;
    }

    public int getNoImpactReviews() {
        return noImpactReviews;
    }


    //              Clone, Equals               //

    public Stats clone(){
        return new Stats(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Stats stats = (Stats) o;
        return getWrongReviews() == stats.getWrongReviews() && getTotalBusiness() == stats.getTotalBusiness() && getTotalBusinessReviewed() == stats.getTotalBusinessReviewed() && getTotalUser() == stats.getTotalUser() && getTotalUserActive() == stats.getTotalUserActive() && getNoImpactReviews() == stats.getNoImpactReviews();
    }

    public void incrementBusinessReviewd (){
        totalBusinessReviewed += 1;
    }

    public void incrementUserActive (){
        totalUserActive += 1;
    }

    public void incrementWrongReviews (){
        wrongReviews += 1;
    }

    public void incrementNoImpactReviews(){
        noImpactReviews += 1;
    }

}
