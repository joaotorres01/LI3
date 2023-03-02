package Utils;

public class Define {

    private static String BusinessPath = "../../../project_c/input_files/business_full.csv";
    private static String UsersPath = "../../../project_c/input_files/users_full.csv";
    private static String ReviewsPath = "../../../project_c/input_files/reviews_1M.csv";

    public static String getBusinessPath() {
        return BusinessPath;
    }

    public static String getReviewsPath() {
        return ReviewsPath;
    }

    public static String getUsersPath() {
        return UsersPath;
    }

    public static void changeBusPath (String path){
        BusinessPath = path;
    }

    public static void changeUsersPath (String path){
        UsersPath = path;
    }
    public static void changeReviewPath (String path){
        ReviewsPath = path;
    }

}
