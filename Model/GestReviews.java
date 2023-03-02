package Model;

import Model.Exceptions.InputInvalidoException;
import Model.Exceptions.InputInvalidoException;
import Utils.*;

import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

public class GestReviews implements GestReviewsInterface,Serializable{
    private static final long serialVersionUID = -5916248299300248942L;
    private BusinessCatalogInterface BCatalog;
    private UserCatalogInterface UCatalog;
    private ReviewCatalogInterface RCatalog;
    private StatsStructInterface statsStruct;


    public GestReviews (){
        this.BCatalog = new BusinessCatalog();
        this.UCatalog = new UserCatalog();
        this.RCatalog = new ReviewCatalog();
        this.statsStruct = new StatsStruct();

    }

    public void lerFicheirosToGestReviews (){
        this.statsStruct = new StatsStruct();
        this.BCatalog = new BusinessCatalog();
        Crono.start();
        lerBusiness(Define.getBusinessPath());
        Crono.stop();
        System.out.println("Tempo para a leitura do ficheiro Business:" + Crono.getTime());


        this.UCatalog = new UserCatalog();
        Crono.start();
        lerUsers(Define.getUsersPath(), false);
        Crono.stop();
        System.out.println("Tempo para a leitura do ficheiro Users:" + Crono.getTime());


        this.RCatalog = new ReviewCatalog();
        Crono.start();
        lerReviews(Define.getReviewsPath());
        Crono.stop();
        System.out.println("Tempo para a leitura du ficheiro Reviews:" + Crono.getTime());

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
                    UserInterface user = new User(linha,friends);
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


    private static String correctUser (String linha){
        String[] campos = linha.split(";");
        return new StringBuilder().append(campos[0]).append(";").append(campos[1]).toString();
    }

    public StatsOutput showStats (){
        Stats stats = statsStruct.getStats();
        StatsOutput output = new StatsOutput(stats);
        Info[]array = RCatalog.showStats();
        for (int i = 0; i < 12;i++){
            Info info = array[i];
            output.AddToList(info);
        }
        return output;
    }


    public List<String> query1 (){
        return BCatalog.naoAvaliados();
    }

    public List<Integer> query2(int ano, int mes)throws InputInvalidoException {
        //statsStruct.totalReviewsAndUsers(ano,mes); W/timeStruct
        return RCatalog.reviewsAnoMes(ano, mes);
    }


    public void savebject(String objectPath) throws IOException{
        FileOutputStream fos = new FileOutputStream(objectPath);
        BufferedOutputStream bos = new BufferedOutputStream(fos);
        ObjectOutputStream oos = new ObjectOutputStream(bos);
        oos.writeObject(this);
        oos.flush();
        oos.close();
    }



    public List<Query3Output> query3(String user_id)throws InputInvalidoException {
        if (!UCatalog.containsUser(user_id)) throw new InputInvalidoException("Model.User inexistente");
        List<Query3Output> result = new ArrayList<>();
        //statsStruct.reviewsBusinessByMonth(user_id); W/timeStruct
        Info[] array = RCatalog.byMonth(user_id,true);
        return getQuery3Outputs(result, array);
    }

    private List<Query3Output> getQuery3Outputs(List<Query3Output> result, Info[] array) {
        for (int i= 0;i <12;i++){
            Info info = array[i];
            Query3Output query3Output;
            if (info != null) {
                query3Output = new Query3Output(info.getTotalReviews(),info.getNotaMedia(),info.sizeIds());
            }
            else query3Output = new Query3Output(0,0,0);
            result.add(query3Output);
        }
        return result;
    }


    public List<Query3Output> query4(String business_id)throws InputInvalidoException {
        if (!BCatalog.containsId(business_id)) throw new InputInvalidoException("Negócio inexistente");
        //statsStruct.vezesAvaliadoByMonth(business_id); //  W/timeStruct
        Info[] array = RCatalog.byMonth(business_id,false);
        List<Query3Output> result = new ArrayList<>();
        return getQuery3Outputs(result, array);
    }


    public List<ParIdCount> query5 (String user_id) throws InputInvalidoException {
        List<ParIdCount> result = statsStruct.businessMaisAvaliaods (user_id);
        for (ParIdCount par : result){
            String id = par.getId();
            par.setId(BCatalog.getNome(id));
        }
        result = result.stream().
                sorted((parIdCount, t1) -> {
                    if (parIdCount.getCount() == t1.getCount())
                        return parIdCount.getId().compareTo(t1.getId());
                    return t1.getCount() - parIdCount.getCount();
                }).collect(Collectors.toList());
        return result;
    }

    public Map<Integer, List<ParIdCount>> query6 (int number){
        return RCatalog.maisAvaliadoAno(number);
    }

    public List<Query7Ouput> query7(){
        return statsStruct.best3City();
    }

    public List<ParIdCount> query8 (int number){
        return statsStruct.usersUniqueBusiness(number);
    }

    public List<TripleIdMediaCount> query9 (String id, int number) throws InputInvalidoException {
        if (!BCatalog.containsId(id)) throw new InputInvalidoException("Id do Model.Business não existe");
        return statsStruct.businessMaisAvaliaods(id,number);
    }

    public Map<String, Map<String, List<TripleIdMediaCount>>> query10 () {
        return statsStruct.eachBusinessAllCity();
    }
}