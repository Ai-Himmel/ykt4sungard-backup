package com.kingstar.basetask.bean;

import com.kingstar.console.sort.Compare;
import com.kingstar.log.Debug;

public class ThreadTask implements Compare {


 	String id="";
	String name="";
	String cla="";
	String description="";
	int priority =5 ;
	boolean isdaemon=false;
	String threadtype="fame";
	int threadcount=1;
	String threadGroup ="";
	
	//task状态是在应用层控制
	int status ;
	
	public int getStatus() {
		return status;
	}
	public void setStatus(int status) {
		this.status = status;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	public String getCla() {
		return cla;
	}
	public void setCla(String cla) {
		this.cla = cla;
	}
	public String getDescription() {
		return description;
	}
	public void setDescription(String description) {
		this.description = description;
	}
	public int getPriority() {
		return priority;
	}
	public void setPriority(int priority) {
		this.priority = priority;
	}
	public boolean isIsdaemon() {
		return isdaemon;
	}
	public void setIsdaemon(boolean isdaemon) {
		this.isdaemon = isdaemon;
	}

	public int getThreadcount() {
		return threadcount;
	}
	public void setThreadcount(int threadcount) {
		this.threadcount = threadcount;
	}
	public String getThreadGroup() {
		return threadGroup;
	}
	public void setThreadGroup(String threadGroup) {
		this.threadGroup = threadGroup;
	}
	
	
	public void debug() {
		Debug.debug("id :"+getId()+"||"+
				"calss :"+getCla()+"||"+
				"comment :"+getDescription()+"||"+
				"priority :"+getPriority()+"||"+
				"description :"+getDescription()+"||"+
				"threadcount :"+getThreadcount()+"|"+
				"Status :"+getStatus());
				
			
	}
	public String getThreadtype() {
		return threadtype;
	}
	public void setThreadtype(String threadtype) {
		this.threadtype = threadtype;
	}
	
	//Using integer compareto interface
	public boolean lessThan(Object l, Object r) {
		//1.4jdk
		return new Integer(((ThreadTask)l).getPriority()).compareTo(new Integer(((ThreadTask)r).getPriority()))< 0;
		
		
	//1.5jdk
		//return ((Integer)((ThreadTask)l).getPriority()).compareTo((Integer)(((ThreadTask) r).getPriority()))< 0;
//		return ((ThreadTask) l).getPriority().compareTo(((ThreadTask) r).getPriority()) < 0;
	}

	public boolean lessThanOrEqual(Object l, Object r) {
		
	//1.4jdk
		return new Integer(((ThreadTask)l).getPriority()).compareTo(new Integer(((ThreadTask)r).getPriority()))<=0;
	
		
		//1.5jdk
//		return ((Integer)((ThreadTask)l).getPriority()).compareTo((Integer)(((ThreadTask) r).getPriority()))<= 0;
	}
}
