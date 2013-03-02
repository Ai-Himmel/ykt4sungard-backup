package com.kingstar.thread;

import java.util.Iterator;

import com.kingstar.basetask.BaseTask;
import com.kingstar.basetask.TaskStateConstants;
import com.kingstar.basetask.bean.Task;
import com.kingstar.console.MainConsole;
import com.kingstar.console.SQL;
import com.kingstar.console.sort.TaskPriorityCompare;
import com.kingstar.format.FormatterOutPut;

public class TaskThread extends KillableThread {

	public TaskThread() {
		super();
	}

	public void run() {
		while (true) {
			//按优先级排序，用TaskPriorityCompare接口
			TaskPriorityCompare tpc = new TaskPriorityCompare();
			MainConsole.tasklist.setCompare(tpc);
			MainConsole.tasklist.sort();

			try {
				//********************************************
				Iterator iter = MainConsole.tasklist.iterator();
				while (iter.hasNext()) {
					Task task = (Task) iter.next();

					//compare is runed
					if (!FormatterOutPut.isruned(task)) {

						if (task.getTasktype().equals("series")
								&& task.getStatus() == TaskStateConstants.START) {
							dealWithTask(task);

						}

					}
				}
				//         		yield();
				System.out.println("crrentthread name:"
						+ Thread.currentThread().getName());
				Thread.sleep(2000);
			} catch (Exception e) {

				System.out.print("error code :" + e.getCause()
						+ "error message:" + e.getMessage());

			}
		}
	}

	//从主tasklist列表中排队取出task执行
	public synchronized void dealWithTask(Task t) throws Exception {

		BaseTask basetask = (BaseTask) Class.forName(t.getCla()).newInstance();
		//为task init and finish方法是为写日志做接口		

		basetask.init(t);
		basetask.run();

		//set task status "run"
		t.setStatus(TaskStateConstants.RUN);

		sleep(1000);

		// set task status "CLOSED"
		basetask.close();

		//add to task_history file 
		FormatterOutPut.writeTaskHistory(t);
	
		//write to data.dat
		FormatterOutPut.StoreTaskHistorys(t);

	}

	

	public void kill() {
		super.kill();

		// running = false;

	}
}
