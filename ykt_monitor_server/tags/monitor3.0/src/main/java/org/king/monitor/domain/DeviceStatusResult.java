package org.king.monitor.domain;

public class DeviceStatusResult extends AbstractResult{
	
	
	private String id;
	private long deviceid;
	private String devicename;
	private String devphyid;
	private long fdevceid;
	private String devtypecode;
	private String ip;
	private String errstarttime;
	private String errendtime;
	private long errlasttime;
	private String errlastdate;
	private String contactname;
	private long errreason;
	private long devstatus;
	private String statename;
	private String rcvman;
	
	
	
	public DeviceStatusResult() {
		super();
		// TODO Auto-generated constructor stub
	}
	
	
	
	public DeviceStatusResult(String id, long deviceid, String devicename,
			String devphyid, long fdevceid, String devtypecode, String ip,
			String errstarttime, String errendtime, long errlasttime,
			String errlastdate, String contactname, long errreason,
			long devstatus, String statename, String rcvman) {
		super();
		this.id = id;
		this.deviceid = deviceid;
		this.devicename = devicename;
		this.devphyid = devphyid;
		this.fdevceid = fdevceid;
		this.devtypecode = devtypecode;
		this.ip = ip;
		this.errstarttime = errstarttime;
		this.errendtime = errendtime;
		this.errlasttime = errlasttime;
		this.errlastdate = errlastdate;
		this.contactname = contactname;
		this.errreason = errreason;
		this.devstatus = devstatus;
		this.statename = statename;
		this.rcvman = rcvman;
	}



	public String getErrendtime() {
		return errendtime;
	}



	public void setErrendtime(String errendtime) {
		this.errendtime = errendtime;
	}



	public String getErrlastdate() {
		return errlastdate;
	}
	public void setErrlastdate(String errlastdate) {
		this.errlastdate = errlastdate;
	}
	
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public long getDeviceid() {
		return deviceid;
	}
	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
	}
	public String getDevicename() {
		return devicename;
	}
	public void setDevicename(String devicename) {
		this.devicename = devicename;
	}
	public String getDevphyid() {
		return devphyid;
	}
	public void setDevphyid(String devphyid) {
		this.devphyid = devphyid;
	}
	public long getFdevceid() {
		return fdevceid;
	}
	public void setFdevceid(long fdevceid) {
		this.fdevceid = fdevceid;
	}
	public String getDevtypecode() {
		return devtypecode;
	}
	public void setDevtypecode(String devtypecode) {
		this.devtypecode = devtypecode;
	}
	public String getIp() {
		return ip;
	}
	public void setIp(String ip) {
		this.ip = ip;
	}
	public String getErrstarttime() {
		return errstarttime;
	}
	public void setErrstarttime(String errstarttime) {
		this.errstarttime = errstarttime;
	}
	public long getErrlasttime() {
		return errlasttime;
	}
	public void setErrlasttime(long errlasttime) {
		this.errlasttime = errlasttime;
	}
	public String getContactname() {
		return contactname;
	}
	public void setContactname(String contactname) {
		this.contactname = contactname;
	}
	public long getErrreason() {
		return errreason;
	}
	public void setErrreason(long errreason) {
		this.errreason = errreason;
	}
	public long getDevstatus() {
		return devstatus;
	}
	public void setDevstatus(long devstatus) {
		this.devstatus = devstatus;
	}
	public String getStatename() {
		return statename;
	}
	public void setStatename(String statename) {
		this.statename = statename;
	}
	public String getRcvman() {
		return rcvman;
	}
	public void setRcvman(String rcvman) {
		this.rcvman = rcvman;
	}

	
	
	
}

