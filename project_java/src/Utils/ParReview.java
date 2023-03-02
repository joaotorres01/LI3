package Utils;

import java.io.Serializable;

public class ParReview implements Serializable {
    private static final long serialVersionUID = -8548660617102693279L;
    private int nrReviews;
    private double notaTotal;

    public ParReview (){
        nrReviews = 0;
        notaTotal = 0;
    }

    public ParReview (ParReview parReview){
        nrReviews = parReview.nrReviews;
        notaTotal = parReview.notaTotal;
    }

    public void update (double nota){
        nrReviews++;
        notaTotal+= nota;
    }

    public int getNrReviews() {
        return nrReviews;
    }

    public double notaMedia (){
        return (double)notaTotal/nrReviews;
    }

    public ParReview clone (){
        return new ParReview(this);
    }
}
