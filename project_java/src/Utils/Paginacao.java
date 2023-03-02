package Utils;

import View.View;

public class Paginacao {
    private static int page;
    private static int totalPage;

    public static void start (int size){
        page = 0;
        totalPage = size/ View.linhaPorPagina;
        if (size%View.linhaPorPagina == 0) totalPage--;
    }

    public static int getPage() {
        return page;
    }

    public static int getTotalPage() {
        return totalPage;
    }

    public static void incrementPage (){
        if (page != totalPage) page++;
    }

    public static void decrementPage (){
        if (page != 0) page--;
    }

    public static void setPage(int page) {
        Paginacao.page = page;
    }
}
