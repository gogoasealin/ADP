package producatorConsumatorCuMutex;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Producator extends Thread {
	

	public int produs = 1;
	private final Lock mutex = new ReentrantLock(true);
	
	public void run() {
		while(true) {
			mutex.lock();
			if(Main.coada.size() < 10) {
				Main.coada.add(produs);
			}
			mutex.unlock();
			System.out.println("Produs adaugat " + Main.coada.size());
			try {
				Thread.sleep(1000);
			} catch (InterruptedException e) {
				// TODO Auto-generated catch block
				e.printStackTrace();
			}
		}
	}
	
}	
