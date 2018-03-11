package producatorConsumatorCuMutex;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Consumator extends Thread{

	private final Lock mutex = new ReentrantLock(true);
	
	public void run() {
		while(true) {
			mutex.lock();
			if(!Main.coada.isEmpty()) {
				Main.coada.remove();			
			}
			mutex.unlock();
			System.out.println("Produs scos " + Main.coada.size());
			try {
				Thread.sleep(3000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
}
