package com.kingstar.console.sort;

import com.kingstar.basetask.bean.Task;


public class TaskPriorityCompare extends Task {
 
 
	private static final long serialVersionUID = 4763919676732237181L;

	public boolean lessThan(Object lhs, Object rhs) {
	
		return ((Task) lhs).getPriority().compareTo(((Task) rhs).getPriority()) < 0;
	}

	public boolean lessThanOrEqual(Object lhs, Object rhs) {
		// TODO Auto-generated method stub
		return ((Task) lhs).getPriority().compareTo(((Task) rhs).getPriority()) <= 0;
	}

}
