package com.kingstar.thread;

import java.util.Iterator;

import com.kingstar.basetask.bean.Task;
import com.kingstar.console.MainConsole;

public class MonitorThread extends KillableThread {

	String name = "monitor";
	long sleeptime = 10000;

	public MonitorThread() {

		super();
	}

	public MonitorThread(String n) {
		super();
		name = n;
	}

	public void run() {
		while (true) {
			try {
		
			System.out.println("monitor thread starting .....");
			Iterator i = MainConsole.tasklist.iterator();

			while (i.hasNext()) {
				Task temp = (Task) i.next();
				temp.debug();

			}
			
			System.out.println( "crrentthread name:"
						+ Thread.currentThread().getName());
			Thread.sleep(4000);
		 //   yield();
	
		

		
		} catch (Exception e) {

			e.printStackTrace();
		}
	}
	}

	public void kill() {
		super.kill();

	}

	public static void main(String args[]) {

		MonitorThread t = new MonitorThread();

		t.start();

	}
}
