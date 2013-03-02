package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTAttendeeList entity provides the base persistence definition of the
 * TAttendeeList entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTAttendeeList implements java.io.Serializable {

	// Fields

	private TAttendeeListId id;
	private long cardNo;
	private String allotDate;
	private String allotTime;
	private String sendSign;
	private String delSign;
	private String attendeeType;
	private String attendSign;
	private String attendDate;
	private String attendTime;
	private String leaveReason;
	private String replacerId;
	private String replacerName;
	private String replacerDept;
	private String replacerDuty;
	private String replacerComments;
	private long delegray;
	private String cutName;
	private String deptName;
	private String stuempNo;
	private String sex;

	// Constructors

	/** default constructor */
	public AbstractTAttendeeList() {
	}

	/** minimal constructor */
	public AbstractTAttendeeList(TAttendeeListId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTAttendeeList(TAttendeeListId id, long cardNo,
			String allotDate, String allotTime, String sendSign,
			String delSign, String attendeeType, String attendSign,
			String attendDate, String attendTime, String leaveReason,
			String replacerId, String replacerName, String replacerDept,
			String replacerDuty, String replacerComments, long delegray,
			String cutName, String deptName, String stuempNo, String sex) {
		this.id = id;
		this.cardNo = cardNo;
		this.allotDate = allotDate;
		this.allotTime = allotTime;
		this.sendSign = sendSign;
		this.delSign = delSign;
		this.attendeeType = attendeeType;
		this.attendSign = attendSign;
		this.attendDate = attendDate;
		this.attendTime = attendTime;
		this.leaveReason = leaveReason;
		this.replacerId = replacerId;
		this.replacerName = replacerName;
		this.replacerDept = replacerDept;
		this.replacerDuty = replacerDuty;
		this.replacerComments = replacerComments;
		this.delegray = delegray;
		this.cutName = cutName;
		this.deptName = deptName;
		this.stuempNo = stuempNo;
		this.sex = sex;
	}

	// Property accessors

	public TAttendeeListId getId() {
		return this.id;
	}

	public void setId(TAttendeeListId id) {
		this.id = id;
	}

	public long getCardNo() {
		return this.cardNo;
	}

	public void setCardNo(long cardNo) {
		this.cardNo = cardNo;
	}

	public String getAllotDate() {
		return this.allotDate;
	}

	public void setAllotDate(String allotDate) {
		this.allotDate = allotDate;
	}

	public String getAllotTime() {
		return this.allotTime;
	}

	public void setAllotTime(String allotTime) {
		this.allotTime = allotTime;
	}

	public String getSendSign() {
		return this.sendSign;
	}

	public void setSendSign(String sendSign) {
		this.sendSign = sendSign;
	}

	public String getDelSign() {
		return this.delSign;
	}

	public void setDelSign(String delSign) {
		this.delSign = delSign;
	}

	public String getAttendeeType() {
		return this.attendeeType;
	}

	public void setAttendeeType(String attendeeType) {
		this.attendeeType = attendeeType;
	}

	public String getAttendSign() {
		return this.attendSign;
	}

	public void setAttendSign(String attendSign) {
		this.attendSign = attendSign;
	}

	public String getAttendDate() {
		return this.attendDate;
	}

	public void setAttendDate(String attendDate) {
		this.attendDate = attendDate;
	}

	public String getAttendTime() {
		return this.attendTime;
	}

	public void setAttendTime(String attendTime) {
		this.attendTime = attendTime;
	}

	public String getLeaveReason() {
		return this.leaveReason;
	}

	public void setLeaveReason(String leaveReason) {
		this.leaveReason = leaveReason;
	}

	public String getReplacerId() {
		return this.replacerId;
	}

	public void setReplacerId(String replacerId) {
		this.replacerId = replacerId;
	}

	public String getReplacerName() {
		return this.replacerName;
	}

	public void setReplacerName(String replacerName) {
		this.replacerName = replacerName;
	}

	public String getReplacerDept() {
		return this.replacerDept;
	}

	public void setReplacerDept(String replacerDept) {
		this.replacerDept = replacerDept;
	}

	public String getReplacerDuty() {
		return this.replacerDuty;
	}

	public void setReplacerDuty(String replacerDuty) {
		this.replacerDuty = replacerDuty;
	}

	public String getReplacerComments() {
		return this.replacerComments;
	}

	public void setReplacerComments(String replacerComments) {
		this.replacerComments = replacerComments;
	}

	public long getDelegray() {
		return this.delegray;
	}

	public void setDelegray(long delegray) {
		this.delegray = delegray;
	}

	public String getCutName() {
		return this.cutName;
	}

	public void setCutName(String cutName) {
		this.cutName = cutName;
	}

	public String getDeptName() {
		return this.deptName;
	}

	public void setDeptName(String deptName) {
		this.deptName = deptName;
	}

	public String getStuempNo() {
		return this.stuempNo;
	}

	public void setStuempNo(String stuempNo) {
		this.stuempNo = stuempNo;
	}

	public String getSex() {
		return this.sex;
	}

	public void setSex(String sex) {
		this.sex = sex;
	}

}