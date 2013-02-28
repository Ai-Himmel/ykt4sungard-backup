package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TEpayAccLog entity. @author MyEclipse Persistence Tools
 */

public class TEpayAccLog implements java.io.Serializable {

	// Fields

	private Long id;
	private String accno;
	private String opertime;
	private String ip;
	private String action;
	private String message;

	// Constructors

	/** default constructor */
	public TEpayAccLog() {
	}

	/** minimal constructor */
	public TEpayAccLog(String accno) {
		this.accno = accno;
	}

	/** full constructor */
	public TEpayAccLog(String accno, String opertime, String ip,
			String action, String message) {
		this.accno = accno;
		this.opertime = opertime;
		this.ip = ip;
		this.action = action;
		this.message = message;
	}

	// Property accessors

	public Long getId() {
		return this.id;
	}

	public void setId(Long id) {
		this.id = id;
	}

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public String getOpertime() {
		return this.opertime;
	}

	public void setOpertime(String opertime) {
		this.opertime = opertime;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public String getAction() {
		return this.action;
	}

	public void setAction(String action) {
		this.action = action;
	}

	public String getMessage() {
		return this.message;
	}

	public void setMessage(String message) {
		this.message = message;
	}

}