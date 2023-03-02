package TestesPerformance;

import Model.Info;
import Model.Review;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Objects;
import java.util.stream.Collectors;

public class InfoTime {
    private int totalReviews;
    private Map<String, Info> users;
    private Map<String, Info> businesses;

    //              Constructors                //

    public InfoTime() {
        this.totalReviews = 0;
        this.users = new HashMap<String, Info>();
        this.businesses = new HashMap<String, Info>();
    }

    public InfoTime(int totalReviews, Map<String, Info> users, Map<String, Info> businesses) {
        this.totalReviews = totalReviews;
        this.users = users
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, i -> i.getValue().clone()));
        this.businesses = businesses
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, i -> i.getValue().clone()));
    }

    public InfoTime(InfoTime im) {
        this.totalReviews = im.getTotalReviews();
        this.users = im.getUsers();
        this.businesses = im.getBusinesses();
    }

    //              Getters and Setters                //

    public int getTotalReviews() {
        return totalReviews;
    }

    public void setTotalReviews(int totalReviews) {
        this.totalReviews = totalReviews;
    }

    public Map<String, Info> getUsers() {
        return this.users
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, i -> i.getValue().clone()));
    }

    public void setUsers(Map<String, Info> users) {
        this.users = users
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, i -> i.getValue().clone()));
    }

    public Map<String, Info> getBusinesses() {
        return this.businesses
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, i -> i.getValue().clone()));
    }

    public void setBusinesses(Map<String, Info> businesses) {
        this.businesses = businesses
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, i -> i.getValue().clone()));
    }

    //              Clone, Equals               //

    public InfoTime clone() {
        return new InfoTime(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        InfoTime infoTime = (InfoTime) o;
        return getTotalReviews() == infoTime.getTotalReviews() && Objects.equals(getUsers(), infoTime.getUsers()) && Objects.equals(getBusinesses(), infoTime.getBusinesses());
    }


    public void updateInfo(Review review) {
        String businessId = review.getBusiness_id();
        String userId = review.getUser_id();
        double nota = review.getStars();
        totalReviews += 1;
        users.putIfAbsent(userId, new Info());
        businesses.putIfAbsent(businessId, new Info());
        users.get(userId).updateInfo(businessId, nota);
        businesses.get(businessId).updateInfo(userId, nota);
    }


    public int sizeUsers() {
        return users.size();
    }

    public int nmrTotalReviewsMonth(String user_id) {
        Info info = users.get(user_id);
        return info == null ? 0 : info.getTotalReviews();
    }

    public int nmrTotalReviewsMonthBusiness(String business_id) {
        Info info = businesses.get(business_id);
        return info == null ? 0 : info.getTotalReviews();
    }

    public double notaTotalMonth(String user_id) {
        Info info = users.get(user_id);
        return info == null ? 0 : info.getNotaTotal();
    }

    public int negociosDistintosUser(String user_id) {
        Info info = users.get(user_id);
        return info == null ? 0 : info.sizeIds();
    }

    public double usersNotaMedia(String user_id) {
        Info info = users.get(user_id);
        return info == null ? 0 : info.getNotaMedia();
    }


    public double usersNotaMediaBusiness(String business_id) {
        Info info = businesses.get(business_id);
        return info == null ? 0 : info.getNotaMedia();
    }

    public int vezesAvaliado(String business_id) {
        Info info = businesses.get(business_id);
        return info == null ? 0 : info.sizeIds();
    }

    public List<String> ordenadosDecrescente (){
        return businesses.entrySet().stream().
                sorted((entry, t1) -> t1.getValue().getTotalReviews() - entry.getValue().getTotalReviews()).
                map(Map.Entry::getKey).
                collect(Collectors.toList());
    }

    public int Usersdistintos (String id){
        return businesses.get(id).sizeIds();
    }

}
