package org.king.monitor.domain;

public class DeviceExceptRt extends AbstractResult {
	
	/** The value of the simple device_id property. */
	private java.lang.String deviceId;

	/** The value of the lastNo formerNo property. */
	private long formerNo;

	/** The value of the simple firstNo property. */
	private long nowNo;
	
	/** The value of the simple latterNo property. */
	private long latterNo;
	
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

	public long getFormerNo() {
		return formerNo;
	}

	public void setFormerNo(long formerNo) {
		this.formerNo = formerNo;
	}

	public long getLatterNo() {
		return latterNo;
	}

	public void setLatterNo(long latterNo) {
		this.latterNo = latterNo;
	}

	public long getNowNo() {
		return nowNo;
	}

	public void setNowNo(long nowNo) {
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

	public DeviceExceptRt(String deviceId, long formerNo, long nowNo, long latterNo, String txDate, String txTime) {
		this.deviceId = deviceId;
		this.formerNo = formerNo;
		this.nowNo = nowNo;
		this.latterNo = latterNo;
		this.txDate = txDate;
		this.txTime = txTime;
	}


	
	

}
