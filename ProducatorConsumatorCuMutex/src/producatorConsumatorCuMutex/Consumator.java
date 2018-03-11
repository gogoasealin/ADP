package producatorConsumatorCuMutex;

import java.util.concurrent.locks.Lock;
import java.util.concurrent.locks.ReentrantLock;


public class Consumator extends Thread{

	private final Lock mutex = new ReentrantLock(true);
	private int id;
	
	Consumator(int id)
	{
		this.id = id;
	}
	
	public void run() {
		while(true) {
			
			try {
				Main.semaphoreFull.acquire();
				mutex.lock();
				if(!Main.coada.isEmpty()) {	
					Main.coada.remove(0);	
				}
				mutex.unlock();
				Main.semaphoreFree.release();
				System.out.println(Main.coada.size());
				Thread.sleep(3000);
			} catch (InterruptedException e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}

		}
	}
	
}
