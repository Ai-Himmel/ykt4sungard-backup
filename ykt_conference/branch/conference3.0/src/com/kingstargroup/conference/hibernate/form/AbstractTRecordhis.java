package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTRecordhis entity provides the base persistence definition of the
 * TRecordhis entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTRecordhis implements java.io.Serializable {

	// Fields

	private long id;
	private long confid;
	private String physicalNo;
	private String checktime;
	private String attendSign;
	private String dealornot;

	// Constructors

	/** default constructor */
	public AbstractTRecordhis() {
	}

	/** full constructor */
	public AbstractTRecordhis(long confid, String physicalNo, String checktime,
			String attendSign, String dealornot) {
		this.confid = confid;
		this.physicalNo = physicalNo;
		this.checktime = checktime;
		this.attendSign = attendSign;
		this.dealornot = dealornot;
	}

	// Property accessors

	public long getId() {
		return this.id;
	}

	public void setId(long id) {
		this.id = id;
	}

	public long getConfid() {
		return this.confid;
	}

	public void setConfid(long confid) {
		this.confid = confid;
	}

	public String getPhysicalNo() {
		return this.physicalNo;
	}

	public void setPhysicalNo(String physicalNo) {
		this.physicalNo = physicalNo;
	}

	public String getChecktime() {
		return this.checktime;
	}

	public void setChecktime(String checktime) {
		this.checktime = checktime;
	}

	public String getAttendSign() {
		return this.attendSign;
	}

	public void setAttendSign(String attendSign) {
		this.attendSign = attendSign;
	}

	public String getDealornot() {
		return this.dealornot;
	}

	public void setDealornot(String dealornot) {
		this.dealornot = dealornot;
	}

}