package Model;

import Model.Exceptions.InputInvalidoException;
import Utils.ParIdCount;
import Utils.ParReview;
import Utils.Query7Ouput;
import Utils.TripleIdMediaCount;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class StatsStruct implements StatsStructInterface,Serializable {
    private static final long serialVersionUID = -2558362549792084024L;
    private StatsInterface stats;
    private InfoStatsInterface busStats;
    private InfoStatsInterface userStats;
    private Map<String,Map<String, Set <String>>> estadoStats;

    public StatsStruct (){
        this.stats = new Stats();
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
        cityStat.putIfAbsent(city,new TreeSet<>());
        cityStat.get(city).add(business.getBusiness_id());
    }

    public void updateStructs (Review review, boolean businessAvaliado, boolean userAvaliado){
        busStats.updateInfo(review.getBusiness_id(),review.getUser_id(),review.getStars());
        userStats.updateInfo(review.getUser_id(), review.getBusiness_id(), review.getStars());
        if (businessAvaliado) stats.incrementBusinessReviewd();
        if (userAvaliado) stats.incrementUserActive();
        if (review.getFunny() == 0 && review.getCool() == 0 && review.getUseful() == 0) stats.incrementNoImpactReviews();
    }


    public Stats getStats (){
        return stats.clone();
    }


    public List<ParIdCount> businessMaisAvaliaods(String user_id) throws InputInvalidoException {
        List<ParIdCount> result = new ArrayList<>();
        Info info = userStats.getInfo(user_id);
        List<Map.Entry<String, ParReview>> list = info.ordenadoDecresente();
        System.out.printf(" %-22s | Nr de Reviews\n","User_id");
        for (Map.Entry<String,ParReview> entry : list){
            String str = entry.getKey();
            ParIdCount parIdCount = new ParIdCount(str,info.getNrReviews(str));
            result.add(parIdCount);
        }
        return result;
    }

    public List<ParIdCount> usersUniqueBusiness(int number) {
        return userStats.uniqueIds(number);
    }

    public List<TripleIdMediaCount> businessMaisAvaliaods(String id, int number) throws InputInvalidoException {
        return busStats.maisAvaliados (id,number);
    }

    public Map<String, Map<String,List<TripleIdMediaCount>>> eachBusinessAllCity() {
        Map<String,Map<String,List<TripleIdMediaCount>>> outputMap = new TreeMap<>();
        for (Map.Entry<String, Map<String, Set<String>>> entry : estadoStats.entrySet()){
            String estado = entry.getKey();
            for (Map.Entry<String,Set<String>> entry1 : entry.getValue().entrySet()){
                String cidade = entry1.getKey();
                Set<TripleIdMediaCount> set = new TreeSet<>();
                for (String str : entry1.getValue()){
                    try {
                        Info info = busStats.getInfo(str);
                        set.add(new TripleIdMediaCount(str, info.getNotaMedia(),info.getTotalReviews()));
                    }
                    catch (InputInvalidoException e){
                        e.getMessage();
                    }
                }
                if (set.size() > 0) {
                    outputMap.putIfAbsent(estado,new TreeMap<>());
                    List <TripleIdMediaCount> list = new ArrayList<>(set);
                    Map<String,List<TripleIdMediaCount>> estadoMap = outputMap.get(estado);
                    estadoMap.put(cidade,list);
                }
            }
        }
        return outputMap;
    }

    public List<Query7Ouput> best3City (){
        List<Query7Ouput> ouputList = new ArrayList<>();
        for (Map<String, Set<String>> entry : estadoStats.values()){
            for (Map.Entry<String,Set<String>> entry1 : entry.entrySet()){
                Set<String> set = entry1.getValue();
                List<String> list =set.stream().
                        sorted(Comparator.comparingInt(s -> busStats.getTotalReviews(s))).
                        collect(Collectors.toList());
                int size = list.size();
                List<ParIdCount> result = new ArrayList<>();
                for (int i = size-1; i>= 0 && i >= size-3;i--){
                    String str = list.get(i);
                    int nrReviews = busStats.getTotalReviews(str);
                    if (nrReviews > 0) result.add(new ParIdCount(str,nrReviews));
                }
                if (result.size() > 0)ouputList.add(new Query7Ouput(entry1.getKey(),result));
            }
        }
        ouputList = ouputList.stream().
                sorted(Comparator.comparing(Query7Ouput::getCidade))
                .collect(Collectors.toList());
        return ouputList;
    }
}
