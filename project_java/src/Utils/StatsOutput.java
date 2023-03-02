package Utils;

import Model.Info;
import Model.Stats;

import java.util.ArrayList;
import java.util.List;

public class StatsOutput {
    private final Stats stats;
    private final List<TripleStat> list;
    private double notaTotal;
    private int totalReviews;


    public StatsOutput (Stats stats){
        this.stats = stats;
        this.list = new ArrayList<>();
        notaTotal = 0;
        totalReviews = 0;
    }

    public void AddToList (Info info){
        TripleStat tripleStat = new TripleStat(info.getTotalReviews(), info.getNotaMedia(), info.sizeIds());
        notaTotal += info.getNotaTotal();
        totalReviews +=  info.getTotalReviews();
        list.add(tripleStat);
    }

    public double notaMediaGlobal (){
        return notaTotal/totalReviews;
    }

    public int getWrongReviews() {
        return stats.getWrongReviews();
    }

    public int getTotalBusiness() {
        return stats.getTotalBusiness();
    }

    public int getTotalBusinessReviewed() {
        return stats.getTotalBusinessReviewed();
    }

    public int getTotalBusinessNotReviewed() {
        return getTotalBusiness() - getTotalBusinessReviewed();
    }

    public int getTotalUser() {
        return stats.getTotalUser();
    }

    public int getTotalUserActive() {
        return stats.getTotalUserActive();
    }

    public int getTotalUserNotActive() {
        return getTotalUser() - getTotalUserActive();
    }

    public int getNoImpactReviews() {
        return stats.getNoImpactReviews();
    }

    public int getTotalReviews(int mes) {
        return list.get(mes).getTotalReviews();
    }

    public double getMedia(int mes) {
        return list.get(mes).getMedia();
    }

    public int getDistintos(int mes) {
        return list.get(mes).getDistintos();
    }

    private static class TripleStat {
        private final int totalReviews;
        private final double media;
        private final int distintos;

        public TripleStat(int totalReviews, double media, int distintos) {
            this.totalReviews = totalReviews;
            this.media = media;
            this.distintos = distintos;
        }

        public int getTotalReviews() {
            return totalReviews;
        }

        public double getMedia() {
            return media;
        }

        public int getDistintos() {
            return distintos;
        }
    }
}
