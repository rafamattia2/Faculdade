
public class SistemaBanco {
    public static void main(String[]args){
        Conta minhaConta;
        minhaConta = new Conta();
        minhaConta.dono="Maria";
        minhaConta.deposita(500.0);
        System.out.println("Saldo atual: "+minhaConta.saldo);
        minhaConta.saca(200.0);
        System.out.println("Saldo atual: "+minhaConta.saldo);   
    }
    
}
