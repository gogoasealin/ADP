package producatorConsumatorCuMutex;

import java.util.Queue;
import java.util.concurrent.Semaphore;
import java.util.ArrayList;

public class Main {

	public static ArrayList<Integer> coada = new ArrayList<Integer>();
	public static Semaphore semaphoreFree = new Semaphore(5);
	public static Semaphore semaphoreFull = new Semaphore(0);
	
	public static void main(String[] args) throws InterruptedException {
		
		for(int i = 0; i < 5;i++)
		{
			Producator producator = new Producator(i);
			producator.start();
			Consumator consumator = new Consumator(i);
			consumator.start();
		}
	}
}
