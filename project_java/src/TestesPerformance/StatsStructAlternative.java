package TestesPerformance;
import Model.Business;
import Model.Exceptions.InputInvalidoException;
import Model.InfoStats;
import Model.Review;
import Model.Stats;
import Utils.ParIdCount;
import Utils.Query3Output;

import java.util.*;

public class StatsStructAlternative {

    private static final long serialVersionUID = -2558362549792084024L;
    private Stats stats;
    private TimeStruct timeStruct;
    private InfoStats busStats;
    private InfoStats userStats;
    private Map<String,Map<String, Set <String>>> estadoStats;

    public StatsStructAlternative(){
        this.stats = new Stats();
        this.timeStruct = new TimeStruct();
        this.busStats = new InfoStats();
        this.userStats = new InfoStats();
        this.estadoStats = new HashMap<>();
    }

    public void setTotalBusiness (int size){
        stats.setTotalBusiness(size);
    }

    public void setTotalUser (int size){
        stats.setTotalUser(size);
    }

    public void incrementWrongReviews (){
        stats.incrementWrongReviews();
    }

    public void updateStructs (Business business){
        String state = business.getState();;
        estadoStats.putIfAbsent(state,new HashMap<>());
        String city = business.getCity();
        Map<String, Set <String>> cityStat = estadoStats.get(state);
        cityStat.putIfAbsent(city,new HashSet<>());
        cityStat.get(city).add(business.getBusiness_id());
    }

    public void updateStructs (Review review, boolean businessAvaliado, boolean userAvaliado){
        busStats.updateInfo(review.getBusiness_id(),review.getUser_id(),review.getStars());
        userStats.updateInfo(review.getUser_id(), review.getBusiness_id(), review.getStars());
        timeStruct.updateInfo(review);
        if (businessAvaliado) stats.incrementBusinessReviewd();
        if (userAvaliado) stats.incrementUserActive();
        if (review.getFunny() == 0 && review.getCool() == 0 && review.getUseful() == 0) stats.incrementNoImpactReviews();
    }



    public void updateInfo (Review review){
        timeStruct.updateInfo(review);
    }


    public List<Integer> totalReviewsAndUsers(int ano, int mes) throws InputInvalidoException {
        return timeStruct.totalReviewsAndUsers(ano,mes);
    }

    public List<Query3Output> reviewsBusinessByMonth(String user_id){
        return timeStruct.reviewsBusinessByMonth(user_id);
    }

    public List<Query3Output> vezesAvaliadoByMonth(String business_id){
        return timeStruct.vezesAvaliadoByMonth(business_id);
    }


    public Map<Integer, List<ParIdCount>> maisAvaliadosAno(int number) {
        return timeStruct.maisAvaliadosAno (number);
    }
}
