import Controller.Controller;
import Model.GestReviews;
import Model.GestReviewsInterface;
import Utils.Crono;
import View.ViewInterface;
import View.View;
import Controller.ControllerInterface;
import Controller.Controller;

public class GestReviewApp {
    public static void main(String[] args) {
        GestReviewsInterface gestReviews = new GestReviews();
        ViewInterface view = new View();
        ControllerInterface controller = new Controller(gestReviews,view);

        gestReviews.lerFicheirosToGestReviews();

        Runtime runtime = Runtime.getRuntime();
        // Run the garbage collector
        runtime.gc();
        // Calculate the used memory
        long memory = runtime.totalMemory() - runtime.freeMemory();
        System.out.println("Used memory is bytes: " + memory);

        controller.run();
    }

}
