package Model;

import Model.Exceptions.InputInvalidoException;
import Utils.ParIdCount;
import Utils.ParReview;

import java.io.Serializable;
import java.util.*;

public class ReviewCatalog implements ReviewCatalogInterface,Serializable {
    private static final long serialVersionUID = 3235854202539408600L;
    private Map<Integer,Map<Integer,List<ReviewInterface>>> catalogo;

    //              Contructors               //


    public ReviewCatalog(){
        catalogo = new TreeMap<>();
    }

    public void addToCatalogo (Review review){
        int ano = review.getDate().getYear();
        catalogo.putIfAbsent(ano,new TreeMap<>());
        int mes = review.getDate().getMonthValue();
        catalogo.get(ano).putIfAbsent(mes,new ArrayList<>());
        catalogo.get(ano).get(mes).add(review);
    }

    public boolean containsBusiness (String id){
        return catalogo.containsKey(id);
    }

    public Info[] byMonth (String id, boolean isUser) {
        Info[] array = new Info[12];
        int mes;
        for (Map<Integer, List<ReviewInterface>> map : catalogo.values()) {
            for (Map.Entry<Integer, List<ReviewInterface>> entry : map.entrySet()) {
                mes = entry.getKey();
                for (ReviewInterface review : entry.getValue()){
                    if (isUser) {
                        if (id.equals(review.getUser_id())) {
                            if (array[mes - 1] == null) array[mes - 1] = new Info();
                            array[mes - 1].updateInfo(review.getBusiness_id(), review.getStars());
                        }
                    }
                    else{
                        if (id.equals(review.getBusiness_id())){
                            if (array[mes -1] == null) array[mes -1] = new Info();
                            array[mes -1].updateInfo(review.getUser_id(),review.getStars());
                        }
                    }
                }
            }
        }
        return array;
    }


    public List<Integer> reviewsAnoMes (int ano,int mes)throws InputInvalidoException {
        Set<String> set = new HashSet<>();
        if (!catalogo.containsKey(ano) || !catalogo.get(ano).containsKey(mes)) throw new InputInvalidoException("Input inválido");
        List<ReviewInterface> list = catalogo.get(ano).get(mes);
        for (ReviewInterface review : list){
            set.add(review.getUser_id());
        }
        List<Integer> result = new ArrayList<>(2);
        result.add(list.size());
        result.add(set.size());
        return result;
    }


    public Map<Integer, List<ParIdCount>> maisAvaliadoAno (int number){
        Map <Integer,List<ParIdCount>> result = new TreeMap<>();
        for (Map.Entry<Integer, Map<Integer, List<ReviewInterface>>> entry: catalogo.entrySet()){
            Map <String, Set<String>> map = new HashMap<>();
            Info info = new Info();
            for (List<ReviewInterface> list : entry.getValue().values()){
                for (ReviewInterface review : list){
                    String busId = review.getBusiness_id();
                    info.updateInfo(busId,review.getStars());
                    map.putIfAbsent(busId,new HashSet<>());
                    map.get(busId).add(review.getUser_id());
                }
            }
            List<Map.Entry<String, ParReview>> ordenadoDecresente = info.ordenadoDecresente();
            List<ParIdCount> list = new ArrayList<>();
            for (int i = 0; i < number && i < ordenadoDecresente.size();i++){
                Map.Entry<String,ParReview> parReviewEntry = ordenadoDecresente.get(i);
                String key = parReviewEntry.getKey();
                int size = map.get(key).size();
                list.add(new ParIdCount(key,size));
            }
            result.put(entry.getKey(),list);
        }
        return result;
    }


    public Info[] showStats (){
        Info[] array = new Info[12];
        int mes;
        for (Map<Integer, List<ReviewInterface>> entry : catalogo.values()) {
            for (Map.Entry<Integer, List<ReviewInterface>> entry1 : entry.entrySet()){
                mes = entry1.getKey();
                for (ReviewInterface review : entry1.getValue()){
                    if (array[mes - 1] == null) array[mes - 1] = new Info();
                    array[mes - 1].updateInfo(review.getUser_id(), review.getStars());
                }
            }
        }
        return array;
    }

}
