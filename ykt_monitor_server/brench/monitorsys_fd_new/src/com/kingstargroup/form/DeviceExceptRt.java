package com.kingstargroup.form;

public class DeviceExceptRt extends AbstractResult {
	
	/** The value of the simple device_id property. */
	private java.lang.String deviceId;

	/** The value of the lastNo formerNo property. */
	private Integer formerNo;

	/** The value of the simple firstNo property. */
	private Integer nowNo;
	
	/** The value of the simple latterNo property. */
	private Integer latterNo;
	
	/** The value of the lastNo seiral_no property. */
	private String	txDate;

	/** The value of the simple firstNo property. */
	private String txTime;

	public java.lang.String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(java.lang.String deviceId) {
		this.deviceId = deviceId;
	}

	public Integer getFormerNo() {
		return formerNo;
	}

	public void setFormerNo(Integer formerNo) {
		this.formerNo = formerNo;
	}

	public Integer getLatterNo() {
		return latterNo;
	}

	public void setLatterNo(Integer latterNo) {
		this.latterNo = latterNo;
	}

	public Integer getNowNo() {
		return nowNo;
	}

	public void setNowNo(Integer nowNo) {
		this.nowNo = nowNo;
	}

	public String getTxDate() {
		return txDate;
	}

	public void setTxDate(String txDate) {
		this.txDate = txDate;
	}

	public String getTxTime() {
		return txTime;
	}

	public void setTxTime(String txTime) {
		this.txTime = txTime;
	}

	
	
	public DeviceExceptRt() {
	}

	public DeviceExceptRt(String deviceId, Integer formerNo, Integer nowNo, Integer latterNo, String txDate, String txTime) {
		this.deviceId = deviceId;
		this.formerNo = formerNo;
		this.nowNo = nowNo;
		this.latterNo = latterNo;
		this.txDate = txDate;
		this.txTime = txTime;
	}


	
	

}
