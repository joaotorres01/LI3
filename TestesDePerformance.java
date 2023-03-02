
import Model.Exceptions.InputInvalidoException;
import Model.GestReviews;
import TestesPerformance.GestReviewsAlternative;
import Utils.Crono;
import View.ViewInterface;

import java.util.Scanner;

public class TestesDePerformance {
    public static void main(String[] args) {
        Scanner scanner = new Scanner (System.in);
        ViewInterface.printOpcao("0.Antiga versão (W/TimeStruct)");
        ViewInterface.printOpcao("1.Nova versão");
        ViewInterface.printPrompt("Escolha uma opção");
        int number = scanner.nextInt();
        if (number == 0) {
            for (int i = 0; i < 5; i++) {
                GestReviewsAlternative gestReviews = new GestReviewsAlternative();

                Crono.start();
                gestReviews.lerBusiness("../../../project_c/input_files/business_full.csv");
                Crono.stop();
                System.out.println("Tempo para Leitura Ficheiro Business: " + Crono.getTime() + "s");

                Crono.start();
                gestReviews.lerUsers("../../../project_c/input_files/users_full.csv", false);
                Crono.stop();
                System.out.println("Tempo para Leitura Ficheiro User: " + Crono.getTime() + "s");


                Crono.start();
                gestReviews.lerReviews("../../../project_c/input_files/reviews_1M.csv");
                Crono.stop();
                System.out.println("Tempo para Leitura Ficheiro Reviews: " + Crono.getTime() + "s");
                Runtime runtime = Runtime.getRuntime();
                // Run the garbage collector
                runtime.gc();
                // Calculate the used memory
                long memory = runtime.totalMemory() - runtime.freeMemory();
                System.out.println("Used memory in bytes: " + memory);


                Utils.Crono.start();
                try {
                    gestReviews.query2(2015, 10);
                } catch (Model.Exceptions.InputInvalidoException e) {
                    System.out.println(e.getMessage());
                }
                Utils.Crono.stop();
                System.out.println("Tempo Query 2: " + Utils.Crono.getTime() + "s");

                System.out.println("--------------------------------------------------");

                Utils.Crono.start();


                Utils.Crono.start();
                gestReviews.query3("RtGqdDBvvBCjcu5dUqwfzA");
                Utils.Crono.stop();
                System.out.println("Tempo Query 3: " + Utils.Crono.getTime() + "s");

                System.out.println("--------------------------------------------------");


                Utils.Crono.start();
                gestReviews.query4("6iYb2HFDywm3zjuRg0shjw");
                Utils.Crono.stop();
                System.out.println("Tempo Query 4: " + Utils.Crono.getTime() + "s");

                System.out.println("--------------------------------------------------");


                Utils.Crono.start();
                gestReviews.query6(10);
                Utils.Crono.stop();
                System.out.println("Tempo Query 6: " + Utils.Crono.getTime() + "s");
            }

        }
        else {
            for (int i = 0; i < 5; i++) {
                GestReviews gestReviews = new GestReviews();

                Crono.start();
                gestReviews.lerBusiness("../../../project_c/input_files/business_full.csv");
                Crono.stop();
                System.out.println("Tempo para Leitura Ficheiro Business: " + Crono.getTime() + "s");

                Crono.start();
                gestReviews.lerUsers("../../../project_c/input_files/users_full.csv", false);
                Crono.stop();
                System.out.println("Tempo para Leitura Ficheiro User: " + Crono.getTime() + "s");


                Crono.start();
                gestReviews.lerReviews("../../../project_c/input_files/reviews_1M.csv");
                Crono.stop();
                System.out.println("Tempo para Leitura Ficheiro Reviews: " + Crono.getTime() + "s");
                Runtime runtime = Runtime.getRuntime();
                // Run the garbage collector
                runtime.gc();
                // Calculate the used memory
                long memory = runtime.totalMemory() - runtime.freeMemory();
                System.out.println("Used memory in bytes: " + memory);


                Utils.Crono.start();
                try {
                    gestReviews.query2(2015, 10);
                } catch (Model.Exceptions.InputInvalidoException e) {
                    System.out.println(e.getMessage());
                }
                Utils.Crono.stop();
                System.out.println("Tempo Query 2: " + Utils.Crono.getTime() + "s");

                System.out.println("--------------------------------------------------");

                Utils.Crono.start();


                Utils.Crono.start();
                try {
                    gestReviews.query3("RtGqdDBvvBCjcu5dUqwfzA");
                } catch (InputInvalidoException e) {
                    e.printStackTrace();
                }
                Utils.Crono.stop();
                System.out.println("Tempo Query 3: " + Utils.Crono.getTime() + "s");

                System.out.println("--------------------------------------------------");


                Utils.Crono.start();
                try {
                    gestReviews.query4("6iYb2HFDywm3zjuRg0shjw");
                } catch (InputInvalidoException e) {
                    e.printStackTrace();
                }
                Utils.Crono.stop();
                System.out.println("Tempo Query 4: " + Utils.Crono.getTime() + "s");

                System.out.println("--------------------------------------------------");


                Utils.Crono.start();
                gestReviews.query6(10);
                Utils.Crono.stop();
                System.out.println("Tempo Query 6: " + Utils.Crono.getTime() + "s");
            }
        }
    }
}
