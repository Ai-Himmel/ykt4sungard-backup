package com.kingstar.basetask.bean;

import java.io.Serializable;

import com.kingstar.console.sort.Compare;
import com.kingstar.log.Debug;

public class Task implements Serializable,Compare{

	/**
	 * 
	 */
	private static final long serialVersionUID = -6935210175116775891L;
 

	/**
	 * 
	 */
	 

	//time uuid
	Long id ;
	
	String name="";
	String cla = "";
	Integer priority;
	String tasktype="";
	String runtimetype="";
	String runtimedata = "";
	String description = "";
	
	//task状态是在应用层控制
	int status ;

	//using compare task belong date
	String belongdate="";
	
	int belongtype;
	
	public int getBelongtype() {
		return belongtype;
	}

	public void setBelongtype(int belongtype) {
		this.belongtype = belongtype;
	}

	public String getBelongdate() {
		System.out.println(belongdate);
		return belongdate;
	}

	public void setBelongdate(String belongdate) {
		this.belongdate = belongdate;
	}

	public int getStatus() {
		return status;
	}

	public void setStatus(int status) {
		this.status = status;
	}

	public String getDescription() {
		return description;
	}

	public void setDescription(String description) {
		this.description = description;
	}

	// get class
	public String getCla() {
		return cla;
	}

	public void setCla(String cla) {
		this.cla = cla;
	}

	public String getRuntimedata() {
		return runtimedata;
	}

	public void setRuntimedata(String runtimedata) {
		this.runtimedata = runtimedata;
	}



	public Integer getPriority() {
		return priority;
	}

	public void setPriority(Integer priority) {
		this.priority = priority;
	}

	public void debug() {
		Debug.debug("id :" + getId() + "|" + 
				    "name :"+getName()+"|"+
				   "class :" + getCla() + "|"+
				   "tasktype :" + getTasktype() + "|" +
				   "priority :"+ getPriority() + "|" + 
				   "Runtimetype :" + getRuntimetype()+ "|" 
				+"Runtimedata:"+getRuntimedata()+"|"+
				"Description: "+getDescription()+"|"+
				"belongdate :"+getBelongdate()+"|"+
				"belongtype :"+getBelongtype()+"|"+
				"Status :"+getStatus());

	}

	// Using integer compareto interface
	public boolean lessThan(Object l, Object r) {
		return ((Task) l).getPriority().compareTo(((Task) r).getPriority()) < 0;
	}

	public boolean lessThanOrEqual(Object l, Object r) {
		return ((Task) l).getPriority().compareTo(((Task) r).getPriority()) <= 0;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}



	public String getRuntimetype() {
		return runtimetype;
	}

	public void setRuntimetype(String runtimetype) {
		this.runtimetype = runtimetype;
	}

	public String getTasktype() {
		return tasktype;
	}

	public void setTasktype(String tasktype) {
		this.tasktype = tasktype;
	}

	public Long getId() {
		return id;
	}

	public void setId(Long id) {
		this.id = id;
	}




}
