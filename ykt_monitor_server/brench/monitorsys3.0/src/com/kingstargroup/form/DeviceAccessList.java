package com.kingstargroup.form;

/**
 * @author Administrator
 *
 */
public class DeviceAccessList extends AbstractResult{
    /** The composite primary key value. */
    private long deviceId;
    
    /** The value of the simple deviceName property. */
    private java.lang.String deviceName;
    
    /** The value of the simple devphy999Id property. */
    private java.lang.String devphy999Id;
    
    /** The value of the simple devtype property. */
    private java.lang.String devtype;

    /** The value of the simple fdevphyId property. */
    private java.lang.String fdevphyId;
    
    /** The value of the simple stateId property. */
    private java.lang.String  stateId;
    
    /** The value of the simple comadd property. */
    private java.lang.String comadd;
    
    private java.lang.String onmap;

    
	public DeviceAccessList(long deviceId, String deviceName, String devphy999Id, String devtype, String fdevphyId, java.lang.String stateId ,String comadd,String onmap) {
		// TODO Auto-generated constructor stub
		this.comadd = comadd;
		this.deviceId = deviceId;
		this.deviceName = deviceName;
		this.devphy999Id = devphy999Id;
		this.devtype = devtype;
		this.fdevphyId = fdevphyId;
		this.stateId = stateId;
		this.onmap = onmap;
	}

	public java.lang.String getComadd() {
		return comadd;
	}

	public void setComadd(java.lang.String comadd) {
		this.comadd = comadd;
	}

	public long getDeviceId() {
		return deviceId;
	}

	public void setDeviceId(long deviceId) {
		this.deviceId = deviceId;
	}

	public java.lang.String getDeviceName() {
		return deviceName;
	}

	public void setDeviceName(java.lang.String deviceName) {
		this.deviceName = deviceName;
	}

	public java.lang.String getDevphy999Id() {
		return devphy999Id;
	}

	public void setDevphy999Id(java.lang.String devphy999Id) {
		this.devphy999Id = devphy999Id;
	}

	public java.lang.String getDevtype() {
		return devtype;
	}

	public void setDevtype(java.lang.String devtype) {
		this.devtype = devtype;
	}

	public java.lang.String getFdevphyId() {
		return fdevphyId;
	}

	public void setFdevphyId(java.lang.String fdevphyId) {
		this.fdevphyId = fdevphyId;
	}

	public java.lang.String  getStateId() {
		return stateId;
	}

	public void setStateId(java.lang.String  stateId) {
		this.stateId = stateId;
	}

	public java.lang.String getOnmap() {
		return onmap;
	}

	public void setOnmap(java.lang.String onmap) {
		this.onmap = onmap;
	}

	/**
	 * 
	 */
	public DeviceAccessList() {
	}
    
  
    


}
