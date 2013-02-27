package com.kingstargroup.form;

public class ServiceExceptionResult extends AbstractResult {

	/** The value of the simple analysistime property. */
	private java.lang.String analysistime;

	/** The value of the simple serverName property. */
	private java.lang.String serverName;

	/** The value of the simple serviceType property. */
	private java.lang.String serviceType;

	/** The value of the simple serviceName property. */
	private java.lang.String serviceName;

	/** The value of the simple contactname property. */
	private java.lang.String contactname;

	/** The value of the simple status property. */
	private java.lang.String status;

	/** The value of the simple errorcode property. */
	private java.lang.Short errorcode;

	public ServiceExceptionResult(String analysistime, String serverName,
			String serviceType, String serviceName, String contactname,
			String status, Short errorcode) {
		this.analysistime = analysistime;
		this.serverName = serverName;
		this.serviceType = serviceType;
		this.serviceName = serviceName;
		this.contactname = contactname;
		this.status = status;
		this.errorcode = errorcode;
	}

	public java.lang.String getAnalysistime() {
		return analysistime;
	}

	public void setAnalysistime(java.lang.String analysistime) {
		this.analysistime = analysistime;
	}

	public java.lang.String getContactname() {
		return contactname;
	}

	public void setContactname(java.lang.String contactname) {
		this.contactname = contactname;
	}

	public java.lang.Short getErrorcode() {
		return errorcode;
	}

	public void setErrorcode(java.lang.Short errorcode) {
		this.errorcode = errorcode;
	}

	public java.lang.String getServerName() {
		return serverName;
	}

	public void setServerName(java.lang.String serverName) {
		this.serverName = serverName;
	}

	public java.lang.String getServiceName() {
		return serviceName;
	}

	public void setServiceName(java.lang.String serviceName) {
		this.serviceName = serviceName;
	}

	public java.lang.String getServiceType() {
		return serviceType;
	}

	public void setServiceType(java.lang.String serviceType) {
		this.serviceType = serviceType;
	}

	public java.lang.String getStatus() {
		return status;
	}

	public void setStatus(java.lang.String status) {
		this.status = status;
	}
	
	

}
