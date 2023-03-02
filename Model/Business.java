package Model;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.Collections;
import java.util.Objects;

public class Business implements BusinessInterface,Serializable {

    private static final long serialVersionUID = 8807762029911441475L;
    private String business_id;
    private String name;
    private String city;
    private String state;
    private ArrayList<String> categories;
    private boolean avaliado; // true se já foi avaliado

    //              Constructors                //

    public Business(){
        this.business_id = "";
        this.name = "";
        this.city = "";
        this.state = "";
        this.categories = new ArrayList<>();
        this.avaliado = false;
    }
    public Business (String linha){
        String[] campos = linha.split(";",5);
        this.business_id = campos[0];
        this.name = campos[1];
        this.city = campos[2];
        this.state = campos[3];
        this.avaliado = false;
        ArrayList <String> list = new ArrayList<>();
        String[]category = linha.split(campos[4]);
        Collections.addAll(list, category);
        this.categories = list;

    }



    public Business(String business_id, String name, String city, String state,
                    ArrayList<String> categories, boolean avaliado){
        this.business_id = business_id;
        this.name = name;
        this.city = city;
        this.state = state;
        this.categories = new ArrayList<>(categories);
        this.avaliado = avaliado;
    }

    public Business(Business business){
        this.business_id = business.getBusiness_id();
        this.name = business.getName();
        this.city = business.getCity();
        this.state = business.getState();
        this.categories = business.getCategories();
        this.avaliado = business.getAvaliado();
    }

    //              Getters and Setters                //

    public String getBusiness_id() {
        return business_id;
    }


    public String getName() {
        return name;
    }


    public String getCity() {
        return city;
    }


    public String getState() {
        return state;
    }

    public boolean getAvaliado() {
        return avaliado;
    }

    public ArrayList<String> getCategories() {
        return new ArrayList<>(categories);
    }

    public void setCategories(ArrayList<String> categories) {
        this.categories = new ArrayList <String> (this.categories);
    }

    public void setAvaliado(boolean avaliado) {
        this.avaliado = avaliado;
    }

    //              Clone, Equals               //

    public Business clone(){
        return new Business(this);
    }


    public boolean equals(Object o) {
        if (this == o) return true;
        if (o == null || getClass() != o.getClass()) return false;
        Business business = (Business) o;
        return getAvaliado() == business.getAvaliado() && Objects.equals(getBusiness_id(), business.getBusiness_id()) && Objects.equals(getName(), business.getName()) && Objects.equals(getCity(), business.getCity()) && Objects.equals(getState(), business.getState()) && Objects.equals(getCategories(), business.getCategories());
    }

    @Override
    public String toString() {
        return "Model.Model.Business{" +
                "business_id='" + business_id + '\'' +
                ", name='" + name + '\'' +
                ", city='" + city + '\'' +
                ", state='" + state + '\'' +
                ", categories=" + categories +
                ", avaliado=" + avaliado +
                '}';
    }
}
