
import java.rmi.RemoteException;
import java.rmi.server.UnicastRemoteObject;
import java.util.Scanner;

public class Client extends UnicastRemoteObject implements ClientInterface, Runnable{
    private ServerInterface server;
    private String name;
    protected Client(String name, ServerInterface server) throws RemoteException {
        this.name=name;
        this.server=server;
        server.registerClient(this);
    }

    @Override
    public void retrieveMessage(String message) throws RemoteException {
        System.out.println(message);
    }

    @Override
    public void run() {
        Scanner scanner=new Scanner(System.in);
        String message;
        while (true){
            message = scanner.nextLine();
            try {
                server.broadcastMessage(name+" : "+ message);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
    }
}
