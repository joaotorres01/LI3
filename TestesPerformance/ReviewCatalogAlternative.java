package TestesPerformance;

import Model.Review;

import java.util.HashMap;
import java.util.Map;

public  class ReviewCatalogAlternative {
    private Map<String, Review> catalogo;

    public ReviewCatalogAlternative(){
        catalogo = new HashMap<>();
    }


    public void addToCatalogo (Review review){
        String id = review.getId();
        catalogo.put(id,review);
    }

    public boolean containsData (String id){
        return catalogo.containsKey(id);
    }

    public int size (){
        return  catalogo.size();
    }

    public Review getData (String id){
        return catalogo.get(id);
    }
}
