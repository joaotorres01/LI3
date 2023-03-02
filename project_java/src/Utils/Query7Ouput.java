package Utils;

import java.util.List;

public class Query7Ouput {
    private String cidade;
    private List<ParIdCount> parIdCountList;

    public Query7Ouput (String cidade,List<ParIdCount> parIdCount){
        this.cidade = cidade;
        this.parIdCountList = parIdCount;
    }

    public List<ParIdCount> getParIdCountList() {
        return parIdCountList;
    }

    public String getCidade() {
        return cidade;
    }
}
