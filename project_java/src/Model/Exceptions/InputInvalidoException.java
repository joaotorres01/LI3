package Model.Exceptions;

public class InputInvalidoException extends Exception{
    public InputInvalidoException(){
        super();
    }

    public InputInvalidoException(String msg){
        super(msg);
    }
}
