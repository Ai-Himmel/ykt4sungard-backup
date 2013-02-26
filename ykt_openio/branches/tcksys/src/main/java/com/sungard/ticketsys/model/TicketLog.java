package com.sungard.ticketsys.model;

import java.io.Serializable;
import java.util.Date;

import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.Table;

@Entity
@Table(name = "T_TICK_TICKET_LOG")
public class TicketLog implements Serializable {

	private static final long serialVersionUID = 1L;
	private Integer ticketId;
	private String payType;
	private String busSerno;
	private String serdayId;
	private Integer seatNo;
	private String startAddr;
	private String endAddr;
	private String price;
	private String departTime;
	private String departDate;
	private Date printTime;
	private String opter;
	private String ticketType;
	private Boolean isReserve;
	private Boolean isback;
	private String memo;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	@Column(name="TICKET_ID", unique=true, nullable=false)
	public Integer getTicketId() {
		return ticketId;
	}
	public void setTicketId(Integer ticketId) {
		this.ticketId = ticketId;
	}
	
	@Column(name = "PAY_TYPE")
	public String getPayType() {
		return payType;
	}
	public void setPayType(String payType) {
		this.payType = payType;
	}
	
	@Column(name = "BUS_SERNO")
	public String getBusSerno() {
		return busSerno;
	}
	public void setBusSerno(String busSerno) {
		this.busSerno = busSerno;
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
	
	@Column(name = "START_ADDR")
	public String getStartAddr() {
		return startAddr;
	}
	public void setStartAddr(String startAddr) {
		this.startAddr = startAddr;
	}
	
	@Column(name = "END_ADDR")
	public String getEndAddr() {
		return endAddr;
	}
	public void setEndAddr(String endAddr) {
		this.endAddr = endAddr;
	}
	
	@Column(name = "PRICE")
	public String getPrice() {
		return price;
	}
	public void setPrice(String price) {
		this.price = price;
	}
	
	@Column(name = "DEPART_TIME")
	public String getDepartTime() {
		return departTime;
	}
	public void setDepartTime(String departTime) {
		this.departTime = departTime;
	}
	
	@Column(name = "DEPART_DATE")
	public String getDepartDate() {
		return departDate;
	}
	public void setDepartDate(String departDate) {
		this.departDate = departDate;
	}
	
	@Column(name = "PRINT_TIME")
	public Date getPrintTime() {
		return printTime;
	}
	public void setPrintTime(Date printTime) {
		this.printTime = printTime;
	}
	
	@Column(name = "OPTER")
	public String getOpter() {
		return opter;
	}
	public void setOpter(String opter) {
		this.opter = opter;
	}
	
	@Column(name = "TICKET_TYPE")
	public String getTicketType() {
		return ticketType;
	}
	public void setTicketType(String ticketType) {
		this.ticketType = ticketType;
	}
	
	@Column(name = "IS_RESERVE")
	public Boolean getIsReserve() {
		return isReserve;
	}
	public void setIsReserve(Boolean isReserve) {
		this.isReserve = isReserve;
	}
	
	@Column(name = "ISBACK")
	public Boolean getIsback() {
		return isback;
	}
	public void setIsback(Boolean isback) {
		this.isback = isback;
	}
	
	@Column(name = "MEMO")
	public String getMemo() {
		return memo;
	}
	public void setMemo(String memo) {
		this.memo = memo;
	}
 
	public static final String PAY_TYPE_CASH = "现金";
	public static final String PAY_TYPE_CARD = "校园卡";
	
	public static final String TICKET_TYPE_MORM = "普通";
	public static final String TICKET_TYPE_PER = "内部";
	
	public static final String PRINT_YES = "已打印";
	public static final String PRINT_NO = "未打印";
}

