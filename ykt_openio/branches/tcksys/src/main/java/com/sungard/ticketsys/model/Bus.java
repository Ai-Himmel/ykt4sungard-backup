package com.sungard.ticketsys.model;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "T_TICK_BUS")
public class Bus implements Serializable {

	private static final long serialVersionUID = 1L;
	private String busNo;
	private String busType;
	private Integer seatCount;
	private String busState;

	@Id
	@Column(name = "BUS_NO", unique = true, nullable = false)
	public String getBusNo() {
		return busNo;
	}

	public void setBusNo(String busNo) {
		this.busNo = busNo;
	}

	@Column(name = "BUS_TYPE")
	public String getBusType() {
		return busType;
	}

	public void setBusType(String busType) {
		this.busType = busType;
	}

	@Column(name = "SEAT_COUNT")
	public Integer getSeatCount() {
		return seatCount;
	}

	public void setSeatCount(Integer seatCount) {
		this.seatCount = seatCount;
	}

	@Column(name = "BUS_STATE")
	public String getBusState() {
		return busState;
	}

	public void setBusState(String busState) {
		this.busState = busState;
	}
	
	public static final String STATE_UN_USER = "闲置";
	public static final String STATE_RUN = "运行中";
	public static final String STATE_REPAIRS = "报修";
	
	

}
