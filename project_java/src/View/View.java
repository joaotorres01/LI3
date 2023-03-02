package View;

import Utils.*;

import java.text.DateFormatSymbols;
import java.util.List;

public class View implements ViewInterface{

    private void options (){
        int page = Paginacao.getPage(), totalPage = Paginacao.getTotalPage();
        ViewInterface.printOpcao("0. Voltar atrás");
        if (page != 0) ViewInterface.printFrase("1. Página Anterior");
        if (page != totalPage) ViewInterface.printFrase("2. Proxima Página");
        if (totalPage != 0) ViewInterface.printFrase("3. Escolher página");
        ViewInterface.printPrompt("Escolha uma opção");
    }


    public void displayQuery1(List<String> list) {
        int page = Paginacao.getPage();
        int totalPage = Paginacao.getTotalPage();
        ViewInterface.clearScreen();
        ViewInterface.printTitulo("Businesses Nunca Avaliados");
        for (int i = page * linhaPorPagina, u = 0; u < linhaPorPagina ; u++,i++) {
            if (i < list.size()) ViewInterface.printFrase(list.get(i));
            else ViewInterface.printFrase("");
        }
        ViewInterface.printFrase("Page:" + page + "/" + totalPage);
        ViewInterface.printOpcao("Total:" + list.size());
        options();
    }

    public void displayQuery2(int ano, int mes, List<Integer> list) {
        ViewInterface.clearScreen();
        ViewInterface.printTitulo("Info mês e ano");
        ViewInterface.printFrase( mes + "/" + ano);
        ViewInterface.printOpcao("Número total de Reviews");
        ViewInterface.printFrase(String.valueOf(list.get(0)));
        ViewInterface.printOpcao("Número total de users distintos");
        ViewInterface.printFrase(String.valueOf(list.get(1)));
        ViewInterface.printFrase("");

    }

    public void displayQuery3(List<Query3Output> list, boolean isUser) {
        int mes = Paginacao.getPage();
        Query3Output output = list.get(mes);
        ViewInterface.clearScreen();
        if (isUser) ViewInterface.printTitulo("Info sobre User");
        else ViewInterface.printTitulo("Info sobre Business");
        ViewInterface.printTitulo(new DateFormatSymbols().getMonths()[mes]);
        ViewInterface.printOpcao("Total Reviews");
        ViewInterface.printFrase(String.valueOf(output.getTotalReviews()));
        if (isUser) ViewInterface.printOpcao("Businesses distintos");
        else ViewInterface.printOpcao("Users distintos");
        ViewInterface.printFrase(String.valueOf(output.getDistintos()));
        ViewInterface.printOpcao("Média da Classificação");
        ViewInterface.printFrase(String.format("%.2f",output.getNotaMedia()));
        ViewInterface.printFrase("\nPage:" + Paginacao.getPage() + "/" + Paginacao.getTotalPage());
        options();
    }

    public void displayQuery5(List<ParIdCount> list) {
        int page = Paginacao.getPage(), totalPage = Paginacao.getTotalPage();
        ViewInterface.clearScreen();
        ViewInterface.printTitulo("Businesses mais avaliados por User");
        System.out.printf(" %25.25s | %s%n","Nome do negócio","Nr de Reviews");
        for (int i = page * linhaPorPagina, u = 0; u < linhaPorPagina ; u++,i++) {
            if (i < list.size()) {
                ParIdCount parIdCount = list.get(i);
                System.out.printf(" %25.25s | %d%n", parIdCount.getId(), parIdCount.getCount());
            }
            else ViewInterface.printFrase("");
        }
        ViewInterface.printFrase("Page:" + page + "/" + totalPage);
        ViewInterface.printOpcao("Total:" + list.size());
        options();
    }

    public void displayQuery6(List<ParIdCount> list) {
        ViewInterface.clearScreen();
        ViewInterface.printTitulo("Businesses mais avaliados por Ano");
        System.out.printf(" %23.23s | %s%n","Id do Business","Nr distintos de users");
        printListIdCount(list);
    }

    public void displayQuery7(List<Query7Ouput> list) {
        int page = Paginacao.getPage(), totalPage = Paginacao.getTotalPage();
        ViewInterface.clearScreen();
        Query7Ouput ouput = list.get(page);
        ViewInterface.printTitulo("Pódio de Negócios Por Cidde");
        ViewInterface.printTitulo(ouput.getCidade());
        System.out.printf("    %23.23s | %s%n","Id do Business","Nr de Reviews");
        List<ParIdCount> parIdCountList = ouput.getParIdCountList();
        for (int i = 0; i < 3 && i < parIdCountList.size();i++){
            ParIdCount parIdCount = parIdCountList.get(i);
            System.out.printf(" " + (i+1) + ". %23.23s | %d%n",parIdCount.getId(),parIdCount.getCount());
        }
        ViewInterface.printFrase("Page:" + page + "/" + totalPage);
        options();
    }

    public void displayQuery8(List<ParIdCount> list) {
        ViewInterface.clearScreen();
        ViewInterface.printTitulo("Users que mais Business Avaliaram");
        System.out.printf(" %23.23s | %s%n","Id do User","Nr distintos de Businesses");
        printListIdCount(list);
    }

    private void printListIdCount(List<ParIdCount> list) {
        int page = Paginacao.getPage(), totalPage = Paginacao.getTotalPage();
        for (int i = page * linhaPorPagina, u = 0; u < linhaPorPagina ; u++,i++) {
            if (i < list.size()) {
                ParIdCount parIdCount = list.get(i);
                System.out.printf(" %23.23s | %d%n", parIdCount.getId(), parIdCount.getCount());
            }
            else ViewInterface.printFrase("");
        }
        ViewInterface.printFrase("Page:" + page + "/" + totalPage);
        ViewInterface.printOpcao("Total:" + list.size());
        options();
    }

    public void displayQuery9(String id, List<TripleIdMediaCount> list) {
        int page = Paginacao.getPage(), totalPage = Paginacao.getTotalPage();
        ViewInterface.clearScreen();
        ViewInterface.printTitulo("Users que mais avalariam um dado Business");
        ViewInterface.printTitulo("Business ID: " + id);
        printListTriple(list, page, totalPage);
        options();
    }

    private void printListTriple(List<TripleIdMediaCount> list, int page, int totalPage) {
        System.out.printf(" %23.23s | %5s | %5s%n","Id do User","Total","Media");
        for (int i = page * linhaPorPagina, u = 0; u < linhaPorPagina ; u++,i++) {
            if (i < list.size()) {
                TripleIdMediaCount parIdMedia = list.get(i);
                System.out.printf(" %23.23s | %5d | %5.2f %n", parIdMedia.getId(),parIdMedia.getCount(),parIdMedia.getMedia());
            }
            else ViewInterface.printFrase("");
        }
        ViewInterface.printFrase("Page:" + page + "/" + totalPage);
    }


    public void menuEstados (List<String> list, boolean isEstado){
        int page = Paginacao.getPage(), totalPage = Paginacao.getTotalPage();
        ViewInterface.clearScreen();
        if (isEstado) ViewInterface.printTitulo("Escolha um Estado");
        else ViewInterface.printTitulo("Escolha uma Cidade");
        for (int i = page * linhaPorPagina, u = 0; u < linhaPorPagina; u++,i++){
            if (i < list.size())
                ViewInterface.printFrase((u+1) + ". " + list.get(i));
        }
        ViewInterface.printFrase("Page:" + page + "/" + totalPage);
        ViewInterface.printOpcao("0. Voltar atrás");
        if (page != 0) ViewInterface.printOpcao((linhaPorPagina + 1) + ". Página Anterior");
        if (page != totalPage) ViewInterface.printOpcao((linhaPorPagina + 2) + ". Proxima Página");
        ViewInterface.printPrompt("Escolha uma opção");
    }

    public void displayQuery10(List<TripleIdMediaCount> list, String cidade) {
        ViewInterface.clearScreen();
        int page = Paginacao.getPage();
        int totalPage = Paginacao.getTotalPage();
        ViewInterface.printTitulo("Classificações do Negócio na Cidade");
        ViewInterface.printTitulo(cidade);
        printListTriple(list, page, totalPage);
        ViewInterface.printOpcao("Total:" + list.size());
        options();
    }

    public void displayStats(StatsOutput statsOutput) {
        ViewInterface.printTitulo("Stats");
        ViewInterface.printOpcao("Reviews Erradas: " + statsOutput.getWrongReviews());
        ViewInterface.printOpcao("Total de Businesses: " + statsOutput.getTotalBusiness());
        ViewInterface.printOpcao("Businesses Avaliados: " + statsOutput.getTotalBusinessReviewed());
        ViewInterface.printOpcao("Businesses Não Avaliados: " + statsOutput.getTotalBusinessNotReviewed());
        ViewInterface.printOpcao("Total de Users: " + statsOutput.getTotalUser());
        ViewInterface.printOpcao("Total Users Ativos: " + statsOutput.getTotalUserActive());
        ViewInterface.printOpcao("Total Users Inativos: " + statsOutput.getTotalUserNotActive());
        ViewInterface.printOpcao("Reviews com 0 Impacto: " +statsOutput.getNoImpactReviews());

        ViewInterface.printOpcao("0. Voltar Atrás");
        ViewInterface.printOpcao("1. Stats Mês");
        ViewInterface.printPrompt("Escolha uma opção");

    }

    public void displayStats2(StatsOutput statsOutput) {
        ViewInterface.clearScreen();
        ViewInterface.printTitulo("Stats Mes");
        int mes = Paginacao.getPage();
        ViewInterface.printTitulo(new DateFormatSymbols().getMonths()[mes]);
        ViewInterface.printOpcao("Número total de reviews : " + statsOutput.getTotalReviews(mes));
        ViewInterface.printOpcao(String.format("Média de classificação de reviews: %.2f",statsOutput.getMedia(mes) ));
        ViewInterface.printOpcao("Númeor distintos de Active Users: " +statsOutput.getDistintos(mes));
        ViewInterface.printOpcao(String.format("Média Globlal: %.2f", statsOutput.notaMediaGlobal()));
        ViewInterface.printFrase("Page:" + Paginacao.getPage() + "/" + Paginacao.getTotalPage());
        options();
    }
}
