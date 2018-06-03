
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.ArrayList;

public class Server extends UnicastRemoteObject implements ServerInterface {
    private static final long serialVersion=1L;
    private ArrayList<ClientInterface> clients;
    protected Server() throws RemoteException{
        clients=new ArrayList<>();

    }

    @Override
    public synchronized void broadcastMessage(String message) throws RemoteException {
        int i=0;
        while (i<clients.size()){
            clients.get(i++).retrieveMessage(message);
        }
    }

    @Override
    public synchronized void registerClient(ClientInterface client)  {
        this.clients.add((ClientInterface) client);
    }
}
