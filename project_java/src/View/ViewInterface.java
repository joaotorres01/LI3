package View;

import Utils.*;

import java.util.List;

public interface ViewInterface {
    /**
     * Método que faz a visualização da query 1
     * @param list Lista ordenada alfabeticamente com os identificadores dos negócios nunca avaliados
     */
    void displayQuery1(List<String> list);

    /**
     * Método que faz a visualização da query 2
     * @param ano Ano
     * @param mes Mês
     * @param list Lista com número total global de reviews realizadas nesse ano e mês
     */
    void displayQuery2(int ano, int mes, List<Integer> list) ;

    /**
     * Método que faz a visualização da query 3/4
     * @param list Lista com reviews, negócios distintos avaliados e a nota média atribuida em cada mês
     * @param isUser true - query 3, false - query 4
     */
    void displayQuery3(List<Query3Output> list, boolean isUser);

    /**
     * Método que faz a visualização da query 5
     * @param list Lista de nomes de negócios mais avaliados eo seu total
     */
    void displayQuery5(List<ParIdCount> list);

    /**
     * Método que faz a visualização da query 6
     * @param list Lista com os X negócios mais avaliados, com o respetivo número total de users que o avaliaram, por ano
     */
    void displayQuery6(List<ParIdCount> list);

    /**
     * Método que faz a visualização da query 7
     * @param list Lista com os 3 negócios com mais número de reviews, por ano
     */
    void displayQuery7(List<Query7Ouput> list);

    /**
     * Método que faz a visualização da query 8
     * @param list Lista com os X users com mais negócios distintos avaliados
     */
    void displayQuery8(List<ParIdCount> list);

    /**
     * Método que faz a visualização da query 9
     * @param id Id do Negócios
     * @param list Lista com os users que mais o avaliaram e para cada um o valor médio de classificação
     */
    void displayQuery9(String id, List<TripleIdMediaCount> list);

    /**
     * Método que faz a visualização da query 10
     * @param list
     * @param cidade
     */
    void displayQuery10(List<TripleIdMediaCount> list, String cidade);

    /**
     * Método da visualização do menu para a query 10
     * @param list Lista com o nome das cidades
     * @param isEstado se quer escolher um estado ou só cidade
     */
    void menuEstados(List<String> list, boolean isEstado);

    /**
     * Método da visualização do menu das Stats
     * @param statsOutput Stats
     */
    void displayStats(StatsOutput statsOutput);

    /**
     * Método da visualização do menu das Stats por mês
     * @param statsOutput Stats
     */
    void displayStats2(StatsOutput statsOutput);

    int linhaPorPagina = 10;
    int largura = 40;


    static String centerString(int width, String s) {
        return String.format("%-" + width  + "s", String.format("%" + (s.length() + (width - s.length()) / 2) + "s", s));
    }


    static void printOpcao(String string){
        System.out.println("\n"+centerString(largura,string));
    }

    static void printTitulo(String str){
        System.out.printf("%s\n\n",centerString(largura,str));
    }

    static void printPrompt(String str){
        System.out.print("\n"+ str + ":");
    }


    static void printFrase(String str){
        System.out.println(centerString(largura,str));
    }

    static void clearScreen() {
        System.out.print("\033[H\033[2J");
        System.out.flush();
    }

    static void loadingScreen (){
        ViewInterface.clearScreen();
        ViewInterface.printFrase("Loading");
    }
}
