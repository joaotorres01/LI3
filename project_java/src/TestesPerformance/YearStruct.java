package TestesPerformance;

import Model.Exceptions.InputInvalidoException;
import Model.Review;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class YearStruct implements Serializable {
    private static final long serialVersionUID = -4789666443031730940L;
    private Map<Integer, InfoTime> infoMes;
    private InfoTime infoAno;

    //              Constructors                //

    public YearStruct(){
        this.infoMes = new TreeMap<>();
        infoAno = new InfoTime();
    }

    public YearStruct(YearStruct ys){
        this.infoMes = ys.getInfoMes();
    }

    //              Getters and Setters                //

    public Map<Integer, InfoTime> getInfoMes() {
        return this.infoMes
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, im -> im.getValue().clone()));
    }

    public void setInfoMes(Map<Integer, InfoTime> infoMes) {
        this.infoMes = infoMes
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, im -> im.getValue().clone()));
    }

    //              Clone, Equals               //

    public YearStruct clone(){
        return new YearStruct(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        YearStruct that = (YearStruct) o;
        return Objects.equals(getInfoMes(), that.getInfoMes());
    }

    public void updateInfo (Review review){
        int month = review.getDate().getMonthValue();
        infoMes.putIfAbsent(month,new InfoTime());
        infoMes.get(month).updateInfo(review);
        infoAno.updateInfo(review);
    }

    public List<Integer> totalReviewsAndUsers(int mes)throws InputInvalidoException {
        InfoTime month = infoMes.get(mes);
        if (month == null)throw new InputInvalidoException("Não há revies para o mês dado");
        List<Integer> array = new ArrayList<>();
        array.add(month.getTotalReviews());
        array.add(month.sizeUsers());
        return array;
    }

    public InfoTime getInfoAno() {
        return infoAno;
    }
}