package com.kingstargroup.form;

public class DeviceSerialostRt extends AbstractResult {
	
	/** The value of the simple device_id property. */
	private java.lang.String deviceId;

	/** The value of the lastNo seiral_no property. */
	private Integer lastNo;

	/** The value of the simple firstNo property. */
	private Integer firstNo;

	public java.lang.String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(java.lang.String deviceId) {
		this.deviceId = deviceId;
	}

	public Integer getFirstNo() {
		return firstNo;
	}

	public void setFirstNo(Integer firstNo) {
		this.firstNo = firstNo;
	}

	public Integer getLastNo() {
		return lastNo;
	}

	public void setLastNo(Integer lastNo) {
		this.lastNo = lastNo;
	}
	
	

	public DeviceSerialostRt() {
		super();
	}

	public DeviceSerialostRt(String deviceId, Integer lastNo, Integer firstNo) {
		super();
		this.deviceId = deviceId;
		this.lastNo = lastNo;
		this.firstNo = firstNo;
	}

	
	
	

}
