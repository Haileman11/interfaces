import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.NotBoundException;
import java.rmi.RemoteException;

public class ClientMain {
    public static void main(String[] args) throws RemoteException, NotBoundException, MalformedURLException {
        String serverURL="rmi://localhost/Server";
        ServerInterface server= (ServerInterface) Naming.lookup(serverURL);
        new Thread(new Client(args[0], server)).start();
    }
}
