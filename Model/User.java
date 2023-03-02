package Model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Objects;

public class User implements UserInterface,Serializable {

    private static final long serialVersionUID = 33439123289361492L;
    private String user_id;
    private String name;
    private ArrayList<String> friends;
    private boolean avaliado;

    //              Constructors                //

    public User(){
        this.user_id = "";
        this.name = "";
        this.friends = new ArrayList<>();
        this.avaliado = false;
    }

    public User(String user_id, String name, ArrayList<String> friends, boolean avaliado){
        this.user_id = user_id;
        this.name = name;
        this.friends = new ArrayList<>(friends);
        this.avaliado = avaliado;
    }

    public User(User user){
        this.user_id = user.getUser_id();
        this.name = user.getName();
        this.friends = user.getFriends();
        this.avaliado = user.getAvaliado();
    }

    public User (String linha, boolean friends) {
        String[] campos = linha.split(";");
        this.user_id = campos[0];
        this.name = campos[1];
        if (friends){
            this.friends = new ArrayList<>();
            String[] allFriends = linha.split(",");
            Collections.addAll(this.friends, allFriends);
        }
        this.avaliado = false;
    }


    //              Getters and Setters                //

    public String getUser_id() {
        return user_id;
    }

    public void setUser_id(String user_id) {
        this.user_id = user_id;
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public ArrayList<String> getFriends() {
        return new ArrayList <String> (this.friends);
    }

    public void setFriends(ArrayList<String> friends) {
        this.friends = new ArrayList <String> (this.friends);
    }

    public boolean getAvaliado() {
        return avaliado;
    }

    public void setAvaliado(boolean avaliado) {
        this.avaliado = avaliado;
    }

    //              Clone, Equals               //

    public User clone(){
        return new User(this);
    }


    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        User user = (User) o;
        return getAvaliado() == user.getAvaliado() && Objects.equals(getUser_id(), user.getUser_id()) && Objects.equals(getName(), user.getName()) && Objects.equals(getFriends(), user.getFriends());
    }

    @Override
    public String toString() {
        return "Model.User{" +
                "user_id='" + user_id + '\'' +
                ", name='" + name + '\'' +
                ", friends=" + friends +
                ", avaliado=" + avaliado +
                '}';
    }
}
