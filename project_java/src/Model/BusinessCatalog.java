package Model;

import java.io.Serializable;
import java.util.*;
import java.util.stream.Collectors;

public class BusinessCatalog  implements BusinessCatalogInterface,Serializable {
    private static final long serialVersionUID = 7184865341828421245L;
    private Map<String, BusinessInterface> catalogo;
    //              Constructors                //

    public BusinessCatalog(){
        catalogo = new HashMap<>();
    }


    public boolean updateAvaliado (String businessId){
        BusinessInterface bus = catalogo.get(businessId);
        if (bus.getAvaliado()) return false;
        else bus.setAvaliado(true);
        return true;
    }


    public List<String> naoAvaliados (){
        Set<String> result = new TreeSet<String>();
        for (BusinessInterface bus : catalogo.values()){ ;
            if (!bus.getAvaliado()){
                result.add(bus.getBusiness_id());
            }
        }
        return new ArrayList<>(result);
    }

    public String getNome (String id){
        return catalogo.get(id).getName();
    }

    public void addToCatalogo(Business bus) {
        this.catalogo.put(bus.getBusiness_id(),bus);
    }

    public int size() {
        return catalogo.size();
    }

    public boolean containsId(String business_id) {
        return catalogo.containsKey(business_id);
    }
}
