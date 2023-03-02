package Model;

import Model.User;

import java.io.Serializable;
import java.util.HashMap;
import java.util.Map;
import java.util.stream.Collectors;

public class UserCatalog implements UserCatalogInterface,Serializable {
    private static final long serialVersionUID = 4125645806643726204L;
    private Map<String, UserInterface> catalogo;

    public UserCatalog(){
        catalogo = new HashMap<>();
    }


    public void addToCatalogo (UserInterface user){
        String id = user.getUser_id();
        catalogo.put(id,user);
    }

    public boolean containsUser (String id){
        return catalogo.containsKey(id);
    }

    public int size (){
        return  catalogo.size();
    }

    public UserInterface getUser (String id){
        return catalogo.get(id);
    }

    public boolean updateAvaliado (String id){
        UserInterface user = catalogo.get(id);
        if (user.getAvaliado()) return false;
        else user.setAvaliado(true);
        return true;
    }

}
