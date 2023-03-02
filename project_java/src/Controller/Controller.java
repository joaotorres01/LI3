package Controller;

import Model.Exceptions.InputInvalidoException;
import Model.GestReviews;
import Model.GestReviewsInterface;
import Utils.*;
import View.ViewInterface;

import java.io.File;
import java.io.IOException;
import java.util.*;

public class Controller implements ControllerInterface{
    private GestReviewsInterface gestReviews;
    private ViewInterface view;
    private int menu;

    public Controller(GestReviewsInterface gestReviews, ViewInterface view) {
        menu = 0;
        this.gestReviews = gestReviews;
        this.view = view;

    }

    public static int getInt(String line) {
        int number;
        try {
            number = Integer.parseInt(line);
        } catch (NumberFormatException e) {
            number = -1;
        }
        return number;
    }

    private static void pressAnyKeyToContinue() {
        ViewInterface.printFrase("Enter para continuar");
        try {
            System.in.read();
        } catch (Exception e) {
        }
    }

    private static void erro(String line) {
        ViewInterface.printFrase(line);
        pressAnyKeyToContinue();
    }

    public void run() {
        boolean out = false;
        Scanner scanner = new Scanner(System.in);
        String[] pieces;
        int number;
        int submenu = 0;
        while (!out) {
            switch ((int) menu) {
                case 0:
                    ViewInterface.clearScreen();
                    ViewInterface.printTitulo("Menu principal");
                    ViewInterface.printOpcao("1. Ler/Carregar Ficheiro ");
                    ViewInterface.printOpcao("2. Queries");
                    ViewInterface.printOpcao("3. Guardar ficheiro");
                    ViewInterface.printOpcao("4. Exit");
                    ViewInterface.printPrompt("Escolha uma opção");
                    pieces = scanner.nextLine().split("\\s+");
                    if (pieces.length == 1) {
                        number = getInt(pieces[0]);
                        if (number >= 1 && number <= 3) menu = number;
                        else if (number == 4) out = true;
                        else erro("Opção inválida");
                    } else erro("Coloque apenas o número");
                    break;
                case 1:
                    switch (submenu) {
                        case 0:
                            ViewInterface.clearScreen();
                            ViewInterface.printOpcao("1. Leitura de um ficheiro de texto");
                            ViewInterface.printOpcao("2. Carregar ficheiro objeto");
                            ViewInterface.printOpcao("0. Voltar atrás");
                            number = askNumero(0, 2);
                            ViewInterface.printPrompt("Escolha uma opção");
                            if (number == 0) menu = 0;
                            if (number == 1 || number == 2) submenu = number;
                            break;
                        case 1:
                            String business = askFile("Business");
                            if (business == null) {
                                submenu = 0;
                                break;
                            }
                            String user = askFile("User");
                            if (user == null) {
                                submenu = 0;
                                break;
                            }
                            String review = askFile("Review");
                            if (review == null) {
                                submenu = 0;
                                break;
                            }
                            Define.changeBusPath(business);
                            Define.changeUsersPath(user);
                            Define.changeReviewPath(review);
                            gestReviews.lerFicheirosToGestReviews();
                            break;
                        case 2:

                            ViewInterface.clearScreen();
                            String fileName = askFile("Filename");
                            if (fileName == null) {
                                submenu = 0;
                                break;
                            }
                            loadFromObject(fileName);
                    }
                    break;
                case 2:
                    switch (submenu) {
                        case 0:
                            ViewInterface.clearScreen();
                            ViewInterface.printTitulo("Queries");
                            ViewInterface.printOpcao("1. Businesses Nunca Avaliados");
                            ViewInterface.printOpcao("2. Info mês e ano");
                            ViewInterface.printOpcao("3. Info sobre User");
                            ViewInterface.printOpcao("4. Info sobre Business");
                            ViewInterface.printOpcao("5. Businesses mais avaliados por User");
                            ViewInterface.printOpcao("6. Businesses mais avaliados por Ano");
                            ViewInterface.printOpcao("7. Pódio por Cidade");
                            ViewInterface.printOpcao("8. Users que mais Business Avaliaram");
                            ViewInterface.printOpcao("9. Users que mais avalariam um dado Business");
                            ViewInterface.printOpcao("10. Média Negócios por Cidade");
                            ViewInterface.printOpcao("11. Stats");
                            ViewInterface.printOpcao("0. Voltar atrás");
                            ViewInterface.printPrompt("Escolha uma opção");
                            pieces = scanner.nextLine().split("\\s+");
                            if (pieces.length == 1) {
                                number = getInt(pieces[0]);
                                if (number >= 1 && number <= 11) submenu = number;
                                else if (number == 0) menu = 0;
                                else erro("Opção inválida");
                            } else erro("Coloque apenas o número");
                            break;
                        case 1:
                            query1();
                            submenu = 0;
                            break;
                        case 2:
                            query2();
                            submenu = 0;
                            break;
                        case 3:
                            if (query3(true)) submenu = 0;
                            break;
                        case 4:
                            if (query3(false)) submenu = 0;
                            break;
                        case 5:
                            if (query5()) submenu = 0;
                            break;
                        case 6:
                            if (query6()) submenu = 0;
                            break;
                        case 7:
                            if (query7()) submenu = 0;
                            break;
                        case 8:
                            if (query8()) submenu = 0;
                            break;
                        case 9:
                            if (query9()) submenu = 0;
                            break;
                        case 10:
                            if (query10()) submenu = 0;
                            break;
                        case 11:
                            showStats();
                            submenu = 0;
                            break;
                    }
                    break;
                case 3:
                    ViewInterface.clearScreen();
                    ViewInterface.printTitulo("Guardar file como Objeto");
                    ViewInterface.printOpcao("0. Voltar atrás");
                    ViewInterface.printPrompt("Nome do ficheiro");
                    String fileName = scanner.nextLine();
                    if (fileName.equals("0")) {
                        menu = 0;
                        break;
                    }
                    ViewInterface.loadingScreen();
                    try {
                        gestReviews.savebject(fileName);
                    } catch (IOException e) {
                        e.printStackTrace();
                        pressAnyKeyToContinue();
                    }
                    menu = 0;
                case 4:
                case 5:

            }
        }
    }


    private String askFile(String str) {
        while (true) {
            ViewInterface.clearScreen();
            ViewInterface.printOpcao("0. Voltar atrás");
            ViewInterface.printPrompt(str);
            Scanner scanner = new Scanner(System.in);
            String file;
            String[] pieces = scanner.nextLine().split("\\s+");
            if (pieces.length == 1) {
                if (pieces[0].equals("0")) return null;
                file = pieces[0];
                File temp = new File(file);
                if (temp.exists()) return file;
                else erro("Ficheiro não existe");
            } else erro("Coloque apenas o nome do ficheiro");
        }
    }


    private int mudarPagina() {
        int page = Paginacao.getPage();
        int totalPage = Paginacao.getTotalPage();
        Scanner scanner = new Scanner(System.in);
        ViewInterface.printPrompt("Page");
        String[] pieces = scanner.nextLine().split("\\s+");
        int number = -1;
        boolean valid = false;
        if (pieces.length == 1) {
            number = getInt(pieces[0]);
            if (number >= 0 && number <= totalPage) Paginacao.setPage(number);
            else erro("Página inválida");
        } else erro("Escreva apena um número");
        return page;
    }

    private int opcaoPagina() {
        Scanner scanner = new Scanner(System.in);
        int number = 0;
        String[] pieces = scanner.nextLine().split("\\s+");
        if (pieces.length == 1) {
            number = getInt(pieces[0]);
            if (number == 2) Paginacao.incrementPage();
            else if (number == 1) Paginacao.decrementPage();
            else if (number == 0) return 0;
            else if (number == 3) return 3;
            else {
                erro("Opção inválida");
            }
        } else erro("Coloque apenas o número");
        return 1;
    }


    private int askNumero(int menor, int maior) {
        Scanner scanner = new Scanner(System.in);
        int number;
        String[] pieces = scanner.nextLine().split("\\s+");
        if (pieces.length == 1) {
            number = getInt(pieces[0]);
            if (number >= menor && number <= maior) return number;
        } else erro("Coloque apenas o número");
        return -1;
    }

    private int askQuestionNumber(boolean isUser) {
        Scanner scanner = new Scanner(System.in);
        boolean valid = false;
        int number = 0;
        while (true) {
            ViewInterface.clearScreen();
            ViewInterface.printOpcao("0. Voltar atrás");
            if (isUser) ViewInterface.printPrompt("Numero de Users");
            else ViewInterface.printPrompt("Numero de negócios");
            String[] pieces = scanner.nextLine().split("\\s+");
            if (pieces.length == 1) {
                number = getInt(pieces[0]);
                if (number != -1) return number;
                else erro("Inválido");
            } else erro("Coloque apenas um número");
        }
    }

    private String askId(boolean isUser) {
        Scanner scanner = new Scanner(System.in);
        boolean valid = false;
        String id = null;
        while (!valid) {
            ViewInterface.clearScreen();
            ViewInterface.printOpcao("0. Voltar Atrás");
            if (!isUser) ViewInterface.printPrompt("ID do Business");
            else ViewInterface.printPrompt("ID do User");
            String[] pieces = scanner.nextLine().split("\\s+");
            if (pieces.length == 1) {
                int number = getInt(pieces[0]);
                if (number == 0) return null;
                valid = true;
                id = pieces[0];
            } else erro("Escreva apenas o id");
        }
        return id;
    }

    private void sayTime(String str) {
        ViewInterface.clearScreen();
        ViewInterface.printFrase("Tempo para completar a query: " + str + "s");
        pressAnyKeyToContinue();
    }

    private void query1() {
        ViewInterface.loadingScreen();
        Crono.start();
        List<String> list = gestReviews.query1();
        Crono.stop();
        sayTime(Crono.getTime());
        Paginacao.start(list.size());
        int number = 0;
        boolean out = false;
        while (!out) {
            view.displayQuery1(list);
            number = opcaoPagina();
            if (number == 0) out = true;
            else if (number == 3) {
                ViewInterface.clearScreen();
                view.displayQuery1(list);
                mudarPagina();
            }
        }
    }


    private void query2() {
        boolean valid = false;
        int ano = 0, mes = 0;
        while (!valid) {
            ViewInterface.clearScreen();
            ViewInterface.printOpcao("0. Voltar atrás");
            ViewInterface.printPrompt("Ano");
            ano = askNumero(0, 2021);
            if (ano == 0) return;
            if (ano != -1) {
                ViewInterface.printPrompt("Mes");
                mes = askNumero(0, 12);
                if (mes != -1) valid = true;
                if (mes == 0) return;
            }
        }
        valid = false;
        ViewInterface.clearScreen();
        ViewInterface.loadingScreen();
        Crono.start();
        List<Integer> list = null;
        try {
            list = gestReviews.query2(ano, mes);
            valid = true;
        } catch (InputInvalidoException e) {
            e.getMessage();
        }
        Crono.stop();
        if (valid) {
            sayTime(Crono.getTime());
            view.displayQuery2(ano, mes, list);
            pressAnyKeyToContinue();
        }
    }

    private boolean query3(boolean isUser) {
        String id;
        boolean valid = false;
        id = askId(isUser);
        if (id == null) return true;
        ViewInterface.clearScreen();
        ViewInterface.loadingScreen();
        Crono.start();
        List<Query3Output> list = null;
        try {
            if (isUser) list = gestReviews.query3(id);
            else list = gestReviews.query4(id);
            valid = true;
        } catch (InputInvalidoException e) {
            ViewInterface.printFrase(e.getMessage());
            pressAnyKeyToContinue();
        }
        Crono.stop();
        if (valid) {
            sayTime(Crono.getTime());
            Paginacao.start(ViewInterface.linhaPorPagina * 12);
            int number = 1;
            while (number != 0) {
                ViewInterface.clearScreen();
                view.displayQuery3(list, isUser);
                number = opcaoPagina();
                if (number == 3) {
                    ViewInterface.clearScreen();
                    view.displayQuery3(list, isUser);
                    mudarPagina();
                }
            }
        }
        return valid;
    }

    private boolean query5() {
        String id;
        boolean valid = false;
        id = askId(true);
        if (id == null) return true;
        Crono.start();
        ViewInterface.loadingScreen();
        List<ParIdCount> list = null;
        try {
            list = gestReviews.query5(id);
            valid = true;
        } catch (InputInvalidoException e) {
            e.getMessage();
        }
        Crono.stop();
        if (valid) {
            sayTime(Crono.getTime());
            boolean out = false;
            Paginacao.start(list.size());
            while (true) {
                view.displayQuery5(list);
                int number = opcaoPagina();
                if (number == 0) return true;
                if (number == 3) {
                    ViewInterface.clearScreen();
                    view.displayQuery5(list);
                    mudarPagina();
                }
            }
        }
        return false;

    }

    private boolean query6() {
        int number;
        boolean valid = false;
        number = askQuestionNumber(false);
        ViewInterface.loadingScreen();
        Crono.start();
        Map<Integer, List<ParIdCount>> map = gestReviews.query6(number);
        Crono.stop();
        sayTime(Crono.getTime());
        while (true) {
            ViewInterface.clearScreen();
            int i = 1;
            Set<Integer> anos = map.keySet();
            List<Integer> anosList = new ArrayList<>(anos);
            ViewInterface.printTitulo("Escolha o ano");
            for (Integer ano : anosList) {
                ViewInterface.printFrase(i + "." + ano);
                i++;
            }
            ViewInterface.printOpcao("0. Voltar atrás");
            ViewInterface.printPrompt("Escolha uma opçao");
            number = askNumero(0, anos.size());
            if (number == 0) return true;
            if (number != -1) valid = true;
            if (valid) {
                valid = false;
                boolean sair = false;
                List<ParIdCount> list = map.get(anosList.get(number - 1));
                Paginacao.start(list.size());
                while (!sair) {
                    view.displayQuery6(list);
                    number = opcaoPagina();
                    if (number == 0) sair = true;
                    if (number == 3) {
                        ViewInterface.clearScreen();
                        view.displayQuery6(list);
                        mudarPagina();
                    }
                }
            }
        }
    }


    private boolean query7() {
        ViewInterface.clearScreen();
        ViewInterface.loadingScreen();
        Crono.start();
        List<Query7Ouput> list = gestReviews.query7();
        Crono.stop();
        sayTime(Crono.getTime());
        int number = 0;
        Paginacao.start(list.size() * ViewInterface.linhaPorPagina);
        while (true) {
            view.displayQuery7(list);
            number = opcaoPagina();
            if (number == 0) break;
            if (number == 3) {
                ViewInterface.clearScreen();
                view.displayQuery7(list);
                mudarPagina();
            }
        }
        return true;
    }


    private boolean query8() {
        boolean valid = false;
        int number = askQuestionNumber(true);
        ViewInterface.clearScreen();
        ViewInterface.loadingScreen();
        Crono.start();
        List<ParIdCount> list = gestReviews.query8(number);
        Crono.stop();
        sayTime(Crono.getTime());
        Paginacao.start(list.size());
        while (!valid) {
            view.displayQuery8(list);
            number = opcaoPagina();
            if (number == 0) valid = true;
            if (number == 3) {
                ViewInterface.clearScreen();
                view.displayQuery8(list);
                mudarPagina();
            }
        }
        return true;
    }

    private boolean query9() {
        String id;
        id = askId(false);
        if (id == null) return true;
        int number = 0;
        number = askQuestionNumber(true);
        ViewInterface.clearScreen();
        ViewInterface.loadingScreen();
        List<TripleIdMediaCount> list;
        Crono.start();
        try {
            list = gestReviews.query9(id, number);
        } catch (InputInvalidoException e) {
            erro(e.getMessage());
            return false;
        }
        Crono.stop();
        sayTime(Crono.getTime());
        Paginacao.start(list.size());
        while (true) {
            view.displayQuery9(id, list);
            number = opcaoPagina();
            if (number == 0) return true;
            if (number == 3) {
                ViewInterface.clearScreen();
                view.displayQuery9(id, list);
                mudarPagina();
            }
        }
    }

    private boolean query10() {
        ViewInterface.loadingScreen();
        Crono.start();
        Map<String, Map<String, List<TripleIdMediaCount>>> map = gestReviews.query10();
        Crono.stop();
        sayTime(Crono.getTime());
        List<String> listEstado = new ArrayList<>(map.keySet());
        int number = 0;
        while (true) {
            Paginacao.start(listEstado.size());
            if ((number = listMenu(listEstado, true)) == 0) return true;
            String estado = listEstado.get(number - 1);
            Map<String, List<TripleIdMediaCount>> estadoMap = map.get(estado);
            List<String> cidadesList = new ArrayList<>(estadoMap.keySet());
            boolean sair = false;
            while (!sair) {
                if (number == 0) sair = true;
                else {
                    Paginacao.start(cidadesList.size());
                    number = listMenu(cidadesList, false);
                    if (number != 0) {
                        String cidade = cidadesList.get(number - 1);
                        List<TripleIdMediaCount> businessList = estadoMap.get(cidade);
                        Paginacao.start(businessList.size());
                        while (true) {
                            view.displayQuery10(businessList, cidade);
                            number = opcaoPagina();
                            if (number == 0) break;
                            if (number == 3) {
                                ViewInterface.clearScreen();
                                view.displayQuery10(businessList, cidade);
                                mudarPagina();
                            }
                        }
                    }
                }
            }
        }
    }

    private int listMenu(List<String> list, boolean isEstado) {
        Scanner scanner = new Scanner(System.in);
        int number = 0;
        while (true) {
            view.menuEstados(list, isEstado);
            String[] pieces = scanner.nextLine().split("\\s+");
            if (pieces.length == 1) {
                number = getInt(pieces[0]);
                if (number == ViewInterface.linhaPorPagina + 2) Paginacao.incrementPage();
                else if (number == ViewInterface.linhaPorPagina + 1) Paginacao.decrementPage();
                else if (number == 0) return 0;
                else if (number >= 1 && number < 1 + ViewInterface.linhaPorPagina) {
                    return number + ViewInterface.linhaPorPagina * Paginacao.getPage();
                } else {
                    erro("Opção inválida");
                }
            } else erro("Coloque apenas o número");
        }
    }

    private void showStats() {
        ViewInterface.loadingScreen();
        Crono.start();
        StatsOutput statsOutput = gestReviews.showStats();
        Crono.stop();
        sayTime(Crono.getTime());
        int number;
        do {
            ViewInterface.clearScreen();
            view.displayStats(statsOutput);
            number = askNumero(0, 1);
            if (number == 0) return;
        } while (number != 1);
        Paginacao.start(ViewInterface.linhaPorPagina * 12);
        while (true) {
            view.displayStats2(statsOutput);
            number = opcaoPagina();
            if (number == 0) break;
            if (number == 3) {
                ViewInterface.clearScreen();
                view.displayStats2(statsOutput);
                mudarPagina();
            }
        }
    }


    private void loadFromObject(String input) {
        this.gestReviews = new GestReviews();
        try {
            this.gestReviews = GestReviewsInterface.loadObject(input);
        } catch (IOException | ClassNotFoundException e) {
            erro("erro ao carregar ficheiro");
        }
    }

}
