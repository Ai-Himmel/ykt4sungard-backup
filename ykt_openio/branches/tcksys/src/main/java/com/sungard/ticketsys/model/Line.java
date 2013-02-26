package com.sungard.ticketsys.model;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name="T_TICK_LINE")
public class Line implements Serializable {

	private static final long serialVersionUID = 1L;
	private Integer id;
	private String lineName;
	private String startAddr;
	private String endAddr;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	@Column(name="lINE_ID", unique=true, nullable=false)
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	
	@Column(name="LINE_NAME")
	public String getLineName() {
		return lineName;
	}
	public void setLineName(String lineName) {
		this.lineName = lineName;
	}
	
	@Column(name="START_ADDR")
	public String getStartAddr() {
		return startAddr;
	}
	public void setStartAddr(String startAddr) {
		this.startAddr = startAddr;
	}
	
	@Column(name="END_ADDR")
	public String getEndAddr() {
		return endAddr;
	}
	public void setEndAddr(String endAddr) {
		this.endAddr = endAddr;
	}
	
	
	
	
	
}
