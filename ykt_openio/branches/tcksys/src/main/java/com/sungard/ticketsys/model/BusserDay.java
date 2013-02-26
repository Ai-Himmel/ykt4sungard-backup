package com.sungard.ticketsys.model;

import java.io.Serializable;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "T_TICK_BUSSER_DAY")
public class BusserDay implements Serializable {

	private static final long serialVersionUID = 1L;
	private String serdayId;
	private String busSerNo;
	private String departDate;
	private Integer ticketCount;
	private Integer remainCount;
	private Integer reserveCount;
	private String busNo;
	private String status;

	@Id
	@Column(name = "SERDAY_ID", unique = true, nullable = false)
	public String getSerdayId() {
		return serdayId;
	}

	public void setSerdayId(String serdayId) {
		this.serdayId = serdayId;
	}

	@Column(name = "BUS_SERNO")
	public String getBusSerNo() {
		return busSerNo;
	}

	public void setBusSerNo(String busSerNo) {
		this.busSerNo = busSerNo;
	}

	@Column(name = "DEPART_DATE")
	public String getDepartDate() {
		return departDate;
	}

	public void setDepartDate(String departDate) {
		this.departDate = departDate;
	}

	@Column(name = "TICKET_COUNT")
	public Integer getTicketCount() {
		return ticketCount;
	}

	public void setTicketCount(Integer ticketCount) {
		this.ticketCount = ticketCount;
	}

	@Column(name = "REMAIN_COUNT")
	public Integer getRemainCount() {
		return remainCount;
	}

	public void setRemainCount(Integer remainCount) {
		this.remainCount = remainCount;
	}
	
	
   @Column(name = "RESERVE_COUNT")
	public Integer getReserveCount() {
		return reserveCount;
	}

	public void setReserveCount(Integer reserveCount) {
		this.reserveCount = reserveCount;
	}

	@Column(name = "BUS_NO")
	public String getBusNo() {
		return busNo;
	}

	public void setBusNo(String busNo) {
		this.busNo = busNo;
	}

	@Column(name = "STATUS")
	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public static final String STATE_WAIT_SALE = "可售票";
	public static final String STATE_STOP_SALE = "停止售票";
	public static final String STATE_IS_RUN = "已发车";
	public static final String STATE_FAIL = "作废";
}
