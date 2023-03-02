package Model;

import Model.Exceptions.InputInvalidoException;
import Utils.ParIdCount;
import Utils.ParReview;
import Utils.TripleIdMediaCount;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class InfoStats implements InfoStatsInterface,Serializable {

    private static final long serialVersionUID = -5997971723914341407L;
    private Map<String, InfoInterface> stats;

    //              Constructors                //

    public InfoStats(){
        this.stats = new HashMap<>();
    }


    public void updateInfo (String id, String id_info, Double nota){
        stats.putIfAbsent(id,new Info());
        stats.get(id).updateInfo(id_info,nota);
    }

    public Info getInfo (String id) throws InputInvalidoException {
        if (!stats.containsKey(id)) throw new InputInvalidoException();
        return stats.get(id).clone();
    }


    public List<ParIdCount> uniqueIds(int number) {
        List<String> list;
        list = stats.entrySet().stream().
                sorted(Comparator.comparingInt(entry -> entry.getValue().sizeIds())).
                map(Map.Entry::getKey).
                collect(Collectors.toList());
        List<ParIdCount> result = new ArrayList<>();
        int size = list.size();
        for (int i = size-1; i >= 0 && i >= size- number;i--){
            String str = list.get(i);
            result.add(new ParIdCount(str,stats.get(str).sizeIds()));
        }
        return result;
    }

    public List<TripleIdMediaCount> maisAvaliados(String id, int number) throws InputInvalidoException {
        if (!stats.containsKey(id)) throw new InputInvalidoException("Este Negócio não tem reviews associadas");
        InfoInterface info = stats.get(id);
        List <TripleIdMediaCount> array = new ArrayList<>();
        List<Map.Entry<String, ParReview>> list = info.ordenadoDecresente();
        for (int i = 0; i < number;i++){
            Map.Entry<String, ParReview> entry = list.get(i);
            ParReview parReview = entry.getValue();
            array.add(new TripleIdMediaCount(entry.getKey(),parReview.notaMedia(), parReview.getNrReviews()));
        }
        return array;
    }

    public int getTotalReviews (String id){
        if (stats.containsKey(id)) return stats.get(id).getTotalReviews();
        return 0;
    }

    public double notaMedia (String id){
        return stats.get(id).getNotaMedia();
    }

    public boolean containsId (String id){
        return stats.containsKey(id);
    }
}
