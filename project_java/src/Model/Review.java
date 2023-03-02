package Model;

import java.io.Serializable;
import java.time.LocalDate;
import java.time.format.DateTimeFormatter;

public class Review implements ReviewInterface, Serializable {

    private static final long serialVersionUID = -6674310253926035903L;
    private String review_id;
    private String user_id;
    private String business_id;
    private double stars;
    private int useful;
    private int funny;
    private int cool;
    private LocalDate date;
    private String text;


    //          Constructors        //

    public Review(){
        this.review_id="";
        this.user_id="";
        this.business_id="";
        this.stars=0;
        this.useful=0;
        this.funny=0;
        this.cool=0;
        this.date=LocalDate.now();
        this.text= "";
    }


    public Review (String linha){
        String[] campos = linha.split(";",9);
        this.review_id = campos[0];
        this.user_id = campos[1];
        this.business_id =campos[2];
        this.stars = Double.parseDouble(campos[3]);
        this.useful = Integer.parseInt(campos[4]);
        this.funny = Integer.parseInt(campos[5]);
        this.cool = Integer.parseInt(campos[6]);
        int index = campos[7].indexOf(" ");
        this.date = LocalDate.parse(campos[7].substring(0,index), DateTimeFormatter.ofPattern("yyyy-MM-dd"));
        this.text = campos[8];

    }

    //              Getters and Setters                //

    public String getReview_id() {
        return review_id;
    }


    public String getUser_id() {
        return user_id;
    }

    public String getBusiness_id() {
        return business_id;
    }

    public double getStars() {
        return stars;
    }


    public int getUseful() {
        return useful;
    }

    public int getFunny() {
        return funny;
    }


    public int getCool() {
        return cool;
    }

    public LocalDate getDate() {
        return date;
    }

    public String getText() {
        return text;
    }



    public String getId() {
        return review_id;
    }
}
