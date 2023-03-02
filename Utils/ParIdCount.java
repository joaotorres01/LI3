package Utils;

public class ParIdCount {
    private String id;
    private int count;

    public ParIdCount (){
        count = 0;
        id = "";
    }

    public ParIdCount(String id,int count) {
        this.count = count;
        this.id = id;
    }

    public ParIdCount (ParIdCount par){
        this.id = par.id;
        this.count = par.count;
    }

    public String getId() {
        return id;
    }

    public int getCount() {
        return count;
    }

    public void setId(String id) {
        this.id = id;
    }
}
