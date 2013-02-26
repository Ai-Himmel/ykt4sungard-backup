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
@Table(name = "T_TICK_REFUND_LOG")
public class RefundLog implements Serializable {

	private static final long serialVersionUID = 1L;
	private Integer refuntId;
	private Integer ticketId;
	private String handFee;
	private Date refuntTime; 
	private String serdayId;
	
	@Id
	@GeneratedValue(strategy=GenerationType.AUTO)
	@Column(name="REFUNT_ID", unique=true, nullable=false)
	public Integer getRefuntId() {
		return refuntId;
	}
	public void setRefuntId(Integer refuntId) {
		this.refuntId = refuntId;
	}
	
	@Column(name = "TICKET_ID")
	public Integer getTicketId() {
		return ticketId;
	}
	public void setTicketId(Integer ticketId) {
		this.ticketId = ticketId;
	}
	
	@Column(name = "HAND_FEE")
	public String getHandFee() {
		return handFee;
	}
	public void setHandFee(String handFee) {
		this.handFee = handFee;
	}
	
	@Column(name = "REFUNT_TIME")
	public Date getRefuntTime() {
		return refuntTime;
	}
	public void setRefuntTime(Date refuntTime) {
		this.refuntTime = refuntTime;
	}
	
	@Column(name = "SERDAY_ID")
	public String getSerdayId() {
		return serdayId;
	}
	public void setSerdayId(String serdayId) {
		this.serdayId = serdayId;
	}
	

}
