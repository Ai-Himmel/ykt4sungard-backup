package com.kingstargroup.form;

public class DeviceSerialLostResult extends AbstractResult {
	/** The value of the simple device_id property. */
	private java.lang.String deviceId;

	/** The value of the simple sum seiral_no property. */
	private long truth;

	/** The value of the simple logic sum seiral_no property. */
	private long logic;

	/** The value of the simple count seiral_no property. */
	private long countserial;

	/** The value of the simple logic count seiral_no property. */
	private long logicserial;

	/** The value of the simple different between count 
	 * and logic count seiral_no property. */
	private long diff;
	

	public long getCountserial() {
		return countserial;
	}

	public void setCountserial(long countserial) {
		this.countserial = countserial;
	}

	public java.lang.String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(java.lang.String deviceId) {
		this.deviceId = deviceId;
	}

	public long getDiff() {
		return diff;
	}

	public void setDiff(long diff) {
		this.diff = diff;
	}

	public long getLogic() {
		return logic;
	}

	public void setLogic(long logic) {
		this.logic = logic;
	}

	public long getLogicserial() {
		return logicserial;
	}

	public void setLogicserial(long logicserial) {
		this.logicserial = logicserial;
	}

	public long getTruth() {
		return truth;
	}

	public void setTruth(long truth) {
		this.truth = truth;
	}

	/**
	 * 
	 */
	public DeviceSerialLostResult() {
		// TODO Auto-generated constructor stub
	}

	/**
	 * @param countserial
	 * @param id
	 * @param diff
	 * @param logic
	 * @param logicserial
	 * @param truth
	 */
	 public DeviceSerialLostResult(String id, long truth, long logic, long countserial, long logicserial, long diff) {
	 // TODO Auto-generated constructor stub
	 this.countserial = countserial;
	 this.deviceId = id;
	 this.diff = diff;
	 this.logic = logic;
	 this.logicserial = logicserial;
	 this.truth = truth;
	 }


}
