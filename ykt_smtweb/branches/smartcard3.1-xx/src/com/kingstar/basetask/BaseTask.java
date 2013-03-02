package com.kingstar.basetask;

import com.kingstar.basetask.bean.Task;

public abstract class BaseTask implements TaskKillable {

    Task task=null;

  //task parameter for delete task and print info
	public void setTask(Task task) {
	this.task = task;
	}
	public void init(Task t) {
		setTask(t);
	}

	public abstract boolean run();
	public void close() {
		// 回调方式实现
		TaskKillablesList.close(task);
	}


}
