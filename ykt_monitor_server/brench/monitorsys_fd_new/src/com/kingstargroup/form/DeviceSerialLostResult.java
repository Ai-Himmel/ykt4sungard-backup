package com.kingstargroup.form;

public class DeviceSerialLostResult extends AbstractResult {
	/** The value of the simple device_id property. */
	private java.lang.String deviceId;

	/** The value of the simple sum seiral_no property. */
	private Integer truth;

	/** The value of the simple logic sum seiral_no property. */
	private Integer logic;

	/** The value of the simple count seiral_no property. */
	private Integer countserial;

	/** The value of the simple logic count seiral_no property. */
	private Integer logicserial;

	/** The value of the simple different between count 
	 * and logic count seiral_no property. */
	private Integer diff;
	

	public Integer getCountserial() {
		return countserial;
	}

	public void setCountserial(Integer countserial) {
		this.countserial = countserial;
	}

	public java.lang.String getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(java.lang.String deviceId) {
		this.deviceId = deviceId;
	}

	public Integer getDiff() {
		return diff;
	}

	public void setDiff(Integer diff) {
		this.diff = diff;
	}

	public Integer getLogic() {
		return logic;
	}

	public void setLogic(Integer logic) {
		this.logic = logic;
	}

	public Integer getLogicserial() {
		return logicserial;
	}

	public void setLogicserial(Integer logicserial) {
		this.logicserial = logicserial;
	}

	public Integer getTruth() {
		return truth;
	}

	public void setTruth(Integer truth) {
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
	 public DeviceSerialLostResult(String id, Integer truth, Integer logic, Integer countserial, Integer logicserial, Integer diff) {
	 // TODO Auto-generated constructor stub
	 this.countserial = countserial;
	 this.deviceId = id;
	 this.diff = diff;
	 this.logic = logic;
	 this.logicserial = logicserial;
	 this.truth = truth;
	 }


}
