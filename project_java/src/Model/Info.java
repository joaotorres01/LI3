package Model;

import Utils.ParReview;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class Info implements InfoInterface,Serializable{
    private static final long serialVersionUID = -2200337020260778264L;
    private int totalReviews;
    private double notaTotal;
    private Map <String, ParReview> ids;

    //              Constructors                //

    public Info(){
        this.totalReviews = 0;
        this.notaTotal = 0;
        this.ids = new HashMap<>();
    }

    public Info (Info info){
        this.totalReviews= info.totalReviews;
        this.notaTotal = info.notaTotal;
        this.ids=info.getIds();
    }
    //              Getters and Setters                //

    public int getTotalReviews() {
        return totalReviews;
    }

    public double getNotaTotal() {
        return notaTotal;
    }

    public Map<String, ParReview> getIds() {
        return this.ids
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, b -> b.getValue().clone()));
    }

    public void updateInfo (String id, double nota){
        totalReviews += 1;
        notaTotal += nota;
        ids.putIfAbsent(id,new ParReview());
        ParReview value = ids.get(id);
        value.update(nota);
    }

    public double getNotaMedia (){
        return notaTotal/totalReviews;
    }

    public int sizeIds (){
        return ids.size();
    }

    public List<Map.Entry<String,ParReview>> ordenadoDecresente (){
        return ids.entrySet().stream().
                sorted((entry, t1) -> {
                    if (t1.getValue().equals(entry.getValue()))
                        return entry.getKey().compareTo(t1.getKey());
                    return t1.getValue().getNrReviews() - entry.getValue().getNrReviews();
                }).
                collect(Collectors.toList());
    }

    public int getNrReviews(String str) {
        return ids.get(str).getNrReviews();
    }


    public Info clone (){
        return new Info(this);
    }
}
