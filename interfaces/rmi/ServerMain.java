
import java.net.MalformedURLException;
import java.rmi.Naming;
import java.rmi.RemoteException;

public class ServerMain {
    public static void main(String args[]) throws RemoteException, MalformedURLException {
        Naming.rebind("Server",new Server());
    }
}
