package com.kingstar.thread;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Iterator;

import com.kingstar.basetask.TaskStateConstants;
import com.kingstar.basetask.bean.Task;
import com.kingstar.console.MainConsole;
import com.kingstar.console.sort.TaskTimeCompare;
import com.kingstar.format.FormatterOutPut;

public class TimeTaskThread extends KillableThread {

	public TimeTaskThread() {
		super();
	}

	public void run() {
		while (true) {
		// 设置按时间排序
		TaskTimeCompare ttp = new TaskTimeCompare();
		MainConsole.tasklist.setCompare(ttp);
		MainConsole.tasklist.sort();

		// println tasklist
		System.out.println("start timetask ");
		MainConsole.printtasklist();

		Iterator iter = MainConsole.tasklist.iterator();
 
		while (iter.hasNext()) {
			Task task = (Task) iter.next();
			
       // compare is runed
			if(!FormatterOutPut.isruned(task)){
				
			// 是任务是TIME类型
			if (task.getTasktype().equals("time")
					&& task.getStatus() == TaskStateConstants.START) {

				// 处理任务
				try {
					dealWithTask(task);	
					task.setStatus(TaskStateConstants.RUN);
 

				} catch (Exception e) {

					System.out.print("error code :" + e.getCause()
							+ "error message:" + e.getMessage());
				}
			}

		}
		}
 	
			System.out.println("crrentthread name:"
						+ Thread.currentThread().getName());	 
			break;
		}

	
	}

	// 用 dotask 类对Tastimertask执行
	public void dealWithTask(Task t) throws Exception {

		// 取出task中日志放在任务器上执行

		Task task = t;
		doTask dt = new doTask();
		dt.setTask(task);

		// 设置执行时间********************8
		// 查看时间是否过期
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date runtime = format.parse(task.getRuntimedata());
		
		// Date r = new Date(task.getRuntimedata());
		// 起一个钟头内的时间任务
		// if (runtime.compareTo(now) >= 0) {
		
		dt.start(runtime);
		 
		//task.setStatus(TaskStateConstants.RUN);

				

	}

	// 回调方式实现，此方法不是抽象的，但必须实现，去清险已级执行的任务信息
	public void kill() {
		super.kill();

	}

}
