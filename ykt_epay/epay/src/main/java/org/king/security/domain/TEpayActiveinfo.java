package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TEpayActiveinfo entity. @author MyEclipse Persistence Tools
 */

public class TEpayActiveinfo implements java.io.Serializable {

	// Fields

	private BigDecimal id;
	private String accno;
	private String activecode;
	private String status;
	private String activetime;
	private String ip;
	private String remark;

	// Constructors

	/** default constructor */
	public TEpayActiveinfo() {
	}

	/** minimal constructor */
	public TEpayActiveinfo(String accno) {
		this.accno = accno;
	}

	/** full constructor */
	public TEpayActiveinfo(String accno, String activecode, String status,
			String activetime, String ip, String remark) {
		this.accno = accno;
		this.activecode = activecode;
		this.status = status;
		this.activetime = activetime;
		this.ip = ip;
		this.remark = remark;
	}

	// Property accessors

	public BigDecimal getId() {
		return this.id;
	}

	public void setId(BigDecimal id) {
		this.id = id;
	}

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public String getActivecode() {
		return this.activecode;
	}

	public void setActivecode(String activecode) {
		this.activecode = activecode;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getActivetime() {
		return this.activetime;
	}

	public void setActivetime(String activetime) {
		this.activetime = activetime;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}