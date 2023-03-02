package Utils;

public class TripleIdMediaCount implements Comparable<TripleIdMediaCount>{
    private String id;
    private int count;
    private double media;

    public TripleIdMediaCount(){
        count = 0;
        media = 0;
        id = "";
    }

    public TripleIdMediaCount(String id, double media, int count) {
        this.media = media;
        this.id = id;
        this.count = count;
    }

    public TripleIdMediaCount(TripleIdMediaCount par){
        this.id = par.id;
        this.media = par.media;
    }

    public String getId() {
        return id;
    }

    public double getMedia() {
        return media;
    }

    public int getCount() {
        return count;
    }

    @Override
    public int compareTo(TripleIdMediaCount tripleIdMediaCount) {
        if (this.count == tripleIdMediaCount.count){
            if (this.media == tripleIdMediaCount.media) return this.id.compareTo(tripleIdMediaCount.id);
            return Double.compare(tripleIdMediaCount.media,this.media);
        }
        return tripleIdMediaCount.count - this.count;
    }
}