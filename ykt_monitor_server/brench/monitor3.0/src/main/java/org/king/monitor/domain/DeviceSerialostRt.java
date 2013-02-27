package org.king.monitor.domain;

public class DeviceSerialostRt extends AbstractResult {
	
	/** The value of the simple device_id property. */
	private java.lang.String deviceId;

	/** The value of the lastNo seiral_no property. */
	private long lastNo;

	/** The value of the simple firstNo property. */
	private long firstNo;

	public java.lang.String getDeviceId() {
		return deviceId;
	}
 
	public void setDeviceId(java.lang.String deviceId) {
		this.deviceId = deviceId;
	}

	public long getFirstNo() {
		return firstNo;
	}

	public void setFirstNo(long firstNo) {
		this.firstNo = firstNo;
	}

	public long getLastNo() {
		return lastNo;
	}

	public void setLastNo(long lastNo) {
		this.lastNo = lastNo;
	}
	
	

	public DeviceSerialostRt() {
		super();
	}

	public DeviceSerialostRt(String deviceId, long lastNo, long firstNo) {
		this.deviceId = deviceId;
		this.lastNo = lastNo;
		this.firstNo = firstNo;
	}

	
	
	

}
