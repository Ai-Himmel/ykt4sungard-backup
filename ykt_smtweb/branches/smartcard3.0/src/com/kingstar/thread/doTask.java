package com.kingstar.thread;

import java.util.Date;
import java.util.Timer;
import java.util.TimerTask;

import com.kingstar.basetask.BaseTask;
import com.kingstar.basetask.bean.Task;
import com.kingstar.format.FormatterOutPut;

public class doTask extends TimerTask {

	Timer myTimer = new Timer();

	Task task = null;

	public doTask() {

	 
	}

	public void setTask(Task task) {
		this.task = task;
	}

	public void run() {
		System.out.println("start time dotask..........");

		try {
			
			//处理时间的定时任务
		dealwith();
			
		} catch (Exception e) {
		
			e.printStackTrace();
		}
	}

	public synchronized void dealwith() throws InstantiationException,
			IllegalAccessException, ClassNotFoundException {

		BaseTask bt = (BaseTask) Class.forName(task.getCla()).newInstance();
		bt.init(task);
		bt.run();
		
	
 
		bt.close();
		
		//add to static vector 
		//MainConsole.taskhistorylist.add(task);
		
        FormatterOutPut.writeTaskHistory(task);
        
//      write to data.dat
		try {
			FormatterOutPut.StoreTaskHistorys(task);
		} catch (Exception e) {
			 
			e.printStackTrace();
		}
	 
	}

	public void start(Date d) {

		myTimer.schedule(this, d);
	}

	public void start(int delay, int internal) {

		myTimer.schedule(this, delay * 1000, internal * 1000); //利用timer.schedule方法
	}

	//利用timer.schedule方法

	public void end() {
		myTimer.cancel();
	}

	public static void main(String args[]) {
		doTask myTask1 = new doTask();
		Date d=new Date();
		d.setHours(9);
		myTask1.start(d);
//		doTask myTask2 = new doTask();
//		myTask2.start(0, 1);

		try {
			Thread.sleep(1000);
		} catch (InterruptedException e) {
		}

		myTask1.end();
//		myTask2.end();//程序结束时用cancel()结束Timer

	}

}