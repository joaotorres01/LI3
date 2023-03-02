package TestesPerformance;

import Model.Exceptions.InputInvalidoException;
import Model.Review;
import Utils.ParIdCount;
import Utils.Query3Output;

import java.util.*;
import java.util.stream.Collectors;

public class TimeStruct {
    private static final long serialVersionUID = 6797203395456128870L;
    private Map<Integer, YearStruct> infoAno;
    private InfoTime[] meses;

    //              Constructors                //

    public TimeStruct(){
        this.infoAno = new TreeMap<>();
        this.meses = new InfoTime[12];
    }

    public TimeStruct(Map<Integer, YearStruct> infoAno){
        this.infoAno = infoAno
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, y -> y.getValue().clone()));
    }

    public TimeStruct(TimeStruct ts){
        this.infoAno = ts.getInfoAno();
    }

    //              Getters and Setters                //

    public Map<Integer, YearStruct> getInfoAno() {
        return this.infoAno
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, ys -> ys.getValue().clone()));
    }

    public void setInfoAno(Map<Integer, YearStruct> infoAno) {
        this.infoAno = infoAno
                .entrySet()
                .stream()
                .collect(Collectors.toMap(Map.Entry::getKey, ys -> ys.getValue().clone()));
    }

    //              Clone, Equals               //

    public TimeStruct clone(){
        return new TimeStruct(this);
    }

    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        TimeStruct that = (TimeStruct) o;
        return Objects.equals(getInfoAno(), that.getInfoAno());
    }

    public void updateInfo (Review review){
        int ano = review.getDate().getYear();
        infoAno.putIfAbsent(ano,new YearStruct());
        infoAno.get(ano).updateInfo(review);
        int mes = review.getDate().getMonthValue();
        if (meses[mes-1] == null) meses[mes-1]= new InfoTime();
        meses[mes-1].updateInfo(review);
    }

    public List<Integer> totalReviewsAndUsers(int ano, int mes) throws InputInvalidoException {
        YearStruct yearStruct = infoAno.get(ano);
        if (yearStruct == null) {
            throw new InputInvalidoException("Não há reviews nesse ano");
        }
        return yearStruct.totalReviewsAndUsers(mes);
    }

    public List<Query3Output> reviewsBusinessByMonth(String user_id) {
        List<Query3Output> list = new ArrayList<>();
        for (int i = 0; i < 12; i++) {
            //System.out.println(new DateFormatSymbols().getMonths()[i]);
            InfoTime info = meses[i];
            if (info != null) {
                list.add(new Query3Output(info.nmrTotalReviewsMonth(user_id),info.usersNotaMedia(user_id),info.negociosDistintosUser(user_id)));
            } else System.out.println("Não há reviews nesse mês");
        }
        return list;
    }

    public List<Query3Output> vezesAvaliadoByMonth(String business_id){
        List<Query3Output> list = new ArrayList<>();
        for (int i = 0; i < 12 ; i++){
            //System.out.println(new DateFormatSymbols().getMonths()[i]);
            InfoTime info = meses[i];
            if (info != null) {
                list.add(new Query3Output(info.nmrTotalReviewsMonth(business_id),info.usersNotaMedia(business_id),info.negociosDistintosUser(business_id)));
                //System.out.println("Negócio foi avaliado: "+ info.nmrTotalReviewsMonthBusiness(business_id));
                //System.out.println("Avaliado por: " + info.vezesAvaliado(business_id) + " users");
                //System.out.println("Media = " + info.usersNotaMediaBusiness(business_id));
            }
            else System.out.println("Não foi avaliado");
        }
        return list;
    }

    public Map<Integer,List<ParIdCount>> maisAvaliadosAno(int number) {
        Map<Integer,List<ParIdCount>> map = new TreeMap<>();
        for (Map.Entry<Integer, YearStruct> entry : infoAno.entrySet()){
            map.putIfAbsent(entry.getKey(),new ArrayList<>());
            YearStruct yearStruct = entry.getValue();
            InfoTime infoTime = yearStruct.getInfoAno();
            List<String> list = infoTime.ordenadosDecrescente();
            int i = 0;
            for (String s : list){
                if (i == number)break;;
                ParIdCount par = new ParIdCount(s,infoTime.Usersdistintos(s));
                map.get(entry.getKey()).add(par);
                i++;
            }
        }
        return map;
    }
}