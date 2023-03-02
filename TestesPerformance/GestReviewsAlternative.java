package TestesPerformance;

import Model.*;
import Model.Exceptions.InputInvalidoException;
import Utils.ParIdCount;
import Utils.Query3Output;

import java.io.*;
import java.util.List;
import java.util.Map;

public class GestReviewsAlternative {
    private static final long serialVersionUID = -5916248299300248942L;
    private BusinessCatalog BCatalog;
    private UserCatalog UCatalog;
    private ReviewCatalogAlternative RCatalog;
    private StatsStructAlternative statsStruct;


    public GestReviewsAlternative(){
        this.BCatalog = new BusinessCatalog();
        this.UCatalog = new UserCatalog();
        this.RCatalog = new ReviewCatalogAlternative();
        this.statsStruct = new StatsStructAlternative();

    }

    public void lerBusiness (String nomeFich){
        BufferedReader inFile;
        String linha;
        boolean first = true;
        try {
            inFile = new BufferedReader(new FileReader(nomeFich));
            while ((linha = inFile.readLine()) != null) {
                if (!first) {
                    Business bus = new Business(linha);
                    this.BCatalog.addToCatalogo(bus);
                    statsStruct.updateStructs(bus);
                }
                else first = false;
            }
        } catch (IOException exc) {
            System.out.println(exc);
        }
        statsStruct.setTotalBusiness(BCatalog.size());
    }


    public void lerUsers (String nomeFich,boolean friends){
        BufferedReader inFile;
        String linha;
        boolean first = true;
        try {
            inFile = new BufferedReader(new FileReader(nomeFich));
            while ((linha = inFile.readLine()) != null) {
                //linha = correctUser(linha);
                if (!first) {
                    User user = new User(linha,friends);
                    UCatalog.addToCatalogo(user);
                }
                else first = false;
            }
        } catch (IOException exc) {
            System.out.println(exc);
        }
        statsStruct.setTotalUser(UCatalog.size());
    }

    public void lerReviews (String nomeFich){
        BufferedReader inFile;
        String linha;
        boolean first = true;
        try {
            inFile = new BufferedReader(new FileReader(nomeFich));
            while ((linha = inFile.readLine()) != null) {
                if (!first) {
                    Review review = new Review(linha);
                    if (BCatalog.containsId(review.getBusiness_id()) && UCatalog.containsUser(review.getUser_id())){
                        RCatalog.addToCatalogo(review);
                        updateStructs(review);
                    }
                    else statsStruct.incrementWrongReviews();
                }
                else first = false;
            }
        } catch (IOException exc) {
            System.out.println(exc);
        }
    }

    private void updateStructs (Review review){
        boolean businessAvaliado = BCatalog.updateAvaliado(review.getBusiness_id());
        boolean userAvaliado = UCatalog.updateAvaliado(review.getUser_id());
        statsStruct.updateStructs(review,businessAvaliado,userAvaliado);
    }

    public List<Integer> query2 (int ano, int mes)throws InputInvalidoException{
        return statsStruct.totalReviewsAndUsers(ano,mes);
    }

    public List<Query3Output> query3(String user_id){
        return statsStruct.reviewsBusinessByMonth(user_id);
    }

    public List<Query3Output> query4(String business_id){
        return statsStruct.vezesAvaliadoByMonth(business_id);
    }

    public Map<Integer, List<ParIdCount>> query6 (int number){
        return statsStruct.maisAvaliadosAno (number);
    }

}
