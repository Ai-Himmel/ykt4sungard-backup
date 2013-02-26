package com.sungard.ticketsys.model;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "T_TICK_SEAT")
public class Seat implements Serializable {

	private static final long serialVersionUID = 1L;
	private Integer id;
	private String serdayId;
	private Integer seatNo;
	private String status;
	private String memo;

	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	@Column(name="SEAT_ID", unique=true, nullable=false)
	public Integer getId() {
		return id;
	}
	public void setId(Integer id) {
		this.id = id;
	}
	
	@Column(name = "SERDAY_ID")
	public String getSerdayId() {
		return serdayId;
	}

	public void setSerdayId(String serdayId) {
		this.serdayId = serdayId;
	}

	@Column(name = "SEAT_NO")
	public Integer getSeatNo() {
		return seatNo;
	}

	public void setSeatNo(Integer seatNo) {
		this.seatNo = seatNo;
	}

	@Column(name = "STATUS")
	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}
	
	@Column(name = "MEMO")	
	public String getMemo() {
		return memo;
	}
	public void setMemo(String memo) {
		this.memo = memo;
	}



	public static final String STATE_WAIT_SALE = "¥˝ €";
	public static final String STATE_SALED = "“— €";
	public static final String STATE_READY_SALE = "‘§¡Ù";

}
