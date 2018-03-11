package producatorConsumatorCuMutex;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;

public class Producator extends Thread {
	
	int id;
	
	Producator (int id)
	{
		this.id = id;
	}
	public int produs = 1;
	private final Lock mutex = new ReentrantLock(true);

	public void run() {
		while(true) {	
			try {
				Thread.sleep(200);
				Main.semaphoreFree.acquire();
				mutex.lock();
				if(Main.coada.size() < 10) {
					Main.coada.add(produs);
				}
				mutex.unlock();
				Main.semaphoreFull.release();
				System.out.println(Main.coada.size());
				
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
		}
	}
	
}	
