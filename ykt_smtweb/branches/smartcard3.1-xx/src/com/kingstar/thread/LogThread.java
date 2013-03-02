package com.kingstar.thread;
public class LogThread extends KillableThread {

	String name = "LogThread";
     long sleeptime=10000;
	public LogThread() {

		super();
	}

	public LogThread(String n) {
		super();
		name = n;
	}
	public void run()  {
		while (true) {
		try {
			
			System.out.println("start write log");
			System.out.println("log threadname :"+this.name);
			
			//yield();
			
			System.out.println("crrent thread name:"
						+ Thread.currentThread().getName());
			Thread.sleep(3000);
			
		} catch (Exception e) {
			
			e.printStackTrace();
		}
	}
	}
	
	public void kill() {
		super.kill();

	}
	public static void main(String args[]){
		
		
		LogThread t=new LogThread();
	
		t.start();
		
		
	}
}
