package com.kingstargroup.form;

public class UnusualDeviceResult extends AbstractResult {
	private long id ;
    /** The value of the simple devphy999Id property. */
    private java.lang.String devphy999Id;

	/** The value of the simple deviceName property. */
	private java.lang.String deviceName;

	/** The value of the simple deviceType property. */
	private java.lang.String deviceType;

	/** The value of the simple contactName property. */
	private java.lang.String contactName;

	/** The value of the simple errorReason property. */
	private long errorReason;

	/**
	 * @param id
	 * @param devphy999Id
	 * @param deviceName
	 * @param deviceType
	 * @param contactName
	 * @param errorReason
	 */
	public UnusualDeviceResult(long id, String devphy999Id, String deviceName,
			String deviceType, String contactName, long errorReason) {
		super();
		// TODO Auto-generated constructor stub
		this.id = id;
		this.devphy999Id = devphy999Id;
		this.deviceName = deviceName;
		this.deviceType = deviceType;
		this.contactName = contactName;
		this.errorReason = errorReason;
	}

    /**
     * Return the value of the DEVPHY999_ID column.
     * @return java.lang.String
     */
    public java.lang.String getDevphy999Id()
    {
        return this.devphy999Id;
    }

    /**
     * Set the value of the DEVPHY999_ID column.
     * @param devphy999Id
     */
    public void setDevphy999Id(java.lang.String devphy999Id)
    {
        this.devphy999Id = devphy999Id;
    }


	/**
	 * Return the value of the DEVICE_NAME column.
	 * 
	 * @return java.lang.String
	 */
	public java.lang.String getDeviceName() {
		return this.deviceName;
	}

	/**
	 * Set the value of the DEVICE_NAME column.
	 * 
	 * @param deviceName
	 */
	public void setDeviceName(java.lang.String deviceName) {
		this.deviceName = deviceName;
	}

	/**
	 * Return the value of the DEVICE_TYPE column.
	 * 
	 * @return java.lang.String
	 */
	public java.lang.String getDeviceType() {
		return this.deviceType;
	}

	/**
	 * Set the value of the DEVICE_TYPE column.
	 * 
	 * @param deviceType
	 */
	public void setDeviceType(java.lang.String deviceType) {
		this.deviceType = deviceType;
	}

	/**
	 * Return the value of the CONTACT_NAME column.
	 * 
	 * @return java.lang.String
	 */
	public java.lang.String getContactName() {
		return this.contactName;
	}

	/**
	 * Set the value of the CONTACT_NAME column.
	 * 
	 * @param contactName
	 */
	public void setContactName(java.lang.String contactName) {
		this.contactName = contactName;
	}

	/**
	 * Return the value of the ERROR_REASON column.
	 * 
	 * @return java.lang.long
	 */

	public long getErrorReason() {
		return errorReason;
	}
	/**
	 * Set the value of the ERROR_REASON column.
	 * 
	 * @param errorReason
	 */
	public void setErrorReason(long errorReason) {
		this.errorReason = errorReason;
	}

	public long getId() {
		return id;
	}

	public void setId(long id) {
		this.id = id;
	}

}
