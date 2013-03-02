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
		// ���ð�ʱ������
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
				
			// ��������TIME����
			if (task.getTasktype().equals("time")
					&& task.getStatus() == TaskStateConstants.START) {

				// ��������
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

	// �� dotask ���Tastimertaskִ��
	public void dealWithTask(Task t) throws Exception {

		// ȡ��task����־������������ִ��

		Task task = t;
		doTask dt = new doTask();
		dt.setTask(task);

		// ����ִ��ʱ��********************8
		// �鿴ʱ���Ƿ����
		SimpleDateFormat format = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");
		Date runtime = format.parse(task.getRuntimedata());
		
		// Date r = new Date(task.getRuntimedata());
		// ��һ����ͷ�ڵ�ʱ������
		// if (runtime.compareTo(now) >= 0) {
		
		dt.start(runtime);
		 
		//task.setStatus(TaskStateConstants.RUN);

				

	}

	// �ص���ʽʵ�֣��˷������ǳ���ģ�������ʵ�֣�ȥ�����Ѽ�ִ�е�������Ϣ
	public void kill() {
		super.kill();

	}

}
