package producatorConsumatorCuMutex;

import java.util.Queue;
import java.util.LinkedList;

public class Main {

	public static Queue<Integer> coada = new LinkedList<Integer>();
	
	public static void main(String[] args) throws InterruptedException {
		Producator producator = new Producator();
		Consumator consumator = new Consumator();
		
		producator.start();
		consumator.start();	
		
	}

}
