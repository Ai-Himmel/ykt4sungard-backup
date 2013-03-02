package org.king.check.domain;


/**
 * AbstractTCheckInfo entity provides the base persistence definition of the
 * TCheckInfo entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckInfo implements java.io.Serializable {

	// Fields

	private String id;
	private Integer custId;
	private String checkDate;
	private String checkinTime;
	private String checkoutTime;
	private Integer checkDuration;
	private String locationId;
	private Integer checkNum;
	private Integer delayNum;
	private Integer earlyNum;
	private String checkType;

	// Constructors

	/** default constructor */
	public AbstractTCheckInfo() {
	}

	/** minimal constructor */
	public AbstractTCheckInfo(String id, Integer custId, String checkDate) {
		this.id = id;
		this.custId = custId;
		this.checkDate = checkDate;
	}

	/** full constructor */
	public AbstractTCheckInfo(String id, Integer custId, String checkDate,
			String checkinTime, String checkoutTime, Integer checkDuration,
			String locationId, Integer checkNum, Integer delayNum,
			Integer earlyNum, String checkType) {
		this.id = id;
		this.custId = custId;
		this.checkDate = checkDate;
		this.checkinTime = checkinTime;
		this.checkoutTime = checkoutTime;
		this.checkDuration = checkDuration;
		this.locationId = locationId;
		this.checkNum = checkNum;
		this.delayNum = delayNum;
		this.earlyNum = earlyNum;
		this.checkType = checkType;
	}

	// Property accessors

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Integer getCustId() {
		return this.custId;
	}

	public void setCustId(Integer custId) {
		this.custId = custId;
	}

	public String getCheckDate() {
		return this.checkDate;
	}

	public void setCheckDate(String checkDate) {
		this.checkDate = checkDate;
	}

	public String getCheckinTime() {
		return this.checkinTime;
	}

	public void setCheckinTime(String checkinTime) {
		this.checkinTime = checkinTime;
	}

	public String getCheckoutTime() {
		return this.checkoutTime;
	}

	public void setCheckoutTime(String checkoutTime) {
		this.checkoutTime = checkoutTime;
	}

	public Integer getCheckDuration() {
		return this.checkDuration;
	}

	public void setCheckDuration(Integer checkDuration) {
		this.checkDuration = checkDuration;
	}

	public String getLocationId() {
		return this.locationId;
	}

	public void setLocationId(String locationId) {
		this.locationId = locationId;
	}

	public Integer getCheckNum() {
		return this.checkNum;
	}

	public void setCheckNum(Integer checkNum) {
		this.checkNum = checkNum;
	}

	public Integer getDelayNum() {
		return this.delayNum;
	}

	public void setDelayNum(Integer delayNum) {
		this.delayNum = delayNum;
	}

	public Integer getEarlyNum() {
		return this.earlyNum;
	}

	public void setEarlyNum(Integer earlyNum) {
		this.earlyNum = earlyNum;
	}

	public String getCheckType() {
		return this.checkType;
	}

	public void setCheckType(String checkType) {
		this.checkType = checkType;
	}

}