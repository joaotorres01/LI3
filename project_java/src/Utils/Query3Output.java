package Utils;

public class Query3Output {
    private int totalReviews;
    private double notaMedia;
    private int distintos;

    public Query3Output(int totalReviews, double notaMedia, int distintos) {
        this.totalReviews = totalReviews;
        this.notaMedia = notaMedia;
        this.distintos = distintos;
    }

    public int getTotalReviews() {
        return totalReviews;
    }

    public double getNotaMedia() {
        return notaMedia;
    }

    public int getDistintos() {
        return distintos;
    }
}