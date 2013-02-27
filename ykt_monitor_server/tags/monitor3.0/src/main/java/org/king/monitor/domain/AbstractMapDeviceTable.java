package org.king.monitor.domain;

/**
 * AbstractMapDeviceTable entity provides the base persistence definition of the
 * MapDeviceTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapDeviceTable implements java.io.Serializable {

	// Fields

	private MapDeviceTableId id;
	private String devicename;
	private String devphyid;
	private String devtypecode;
	private String fdevphyid;
	private String runstatus;
	private String status;
	private String ip;
	private long deviceno;
	private String cardverno;
	private long sysid;
	private String areacode;
	private long devusage;
	private String devicetime;
	private String servertime;
	private String contactName;
	private double cpu;
	private double memory;
	private double harddisk;
	private long errorReason;

	// Constructors

	/** default constructor */
	public AbstractMapDeviceTable() {
	}

	/** minimal constructor */
	public AbstractMapDeviceTable(MapDeviceTableId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapDeviceTable(MapDeviceTableId id, String devicename,
			String devphyid, String devtypecode, String fdevphyid,
			String runstatus, String status, String ip, long deviceno,
			String cardverno, long sysid, String areacode, long devusage,
			String devicetime, String servertime, String contactName,
			double cpu, double memory, double harddisk, long errorReason) {
		this.id = id;
		this.devicename = devicename;
		this.devphyid = devphyid;
		this.devtypecode = devtypecode;
		this.fdevphyid = fdevphyid;
		this.runstatus = runstatus;
		this.status = status;
		this.ip = ip;
		this.deviceno = deviceno;
		this.cardverno = cardverno;
		this.sysid = sysid;
		this.areacode = areacode;
		this.devusage = devusage;
		this.devicetime = devicetime;
		this.servertime = servertime;
		this.contactName = contactName;
		this.cpu = cpu;
		this.memory = memory;
		this.harddisk = harddisk;
		this.errorReason = errorReason;
	}

	// Property accessors

	public String getFdevphyid() {
		return fdevphyid;
	}

	public void setFdevphyid(String fdevphyid) {
		this.fdevphyid = fdevphyid;
	}

	public MapDeviceTableId getId() {
		return this.id;
	}

	public void setId(MapDeviceTableId id) {
		this.id = id;
	}

	public String getDevicename() {
		return this.devicename;
	}

	public void setDevicename(String devicename) {
		this.devicename = devicename;
	}

	public String getDevphyid() {
		return this.devphyid;
	}

	public void setDevphyid(String devphyid) {
		this.devphyid = devphyid;
	}

	public String getDevtypecode() {
		return this.devtypecode;
	}

	public void setDevtypecode(String devtypecode) {
		this.devtypecode = devtypecode;
	}

	public String getRunstatus() {
		return this.runstatus;
	}

	public void setRunstatus(String runstatus) {
		this.runstatus = runstatus;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public long getDeviceno() {
		return this.deviceno;
	}

	public void setDeviceno(long deviceno) {
		this.deviceno = deviceno;
	}

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public long getSysid() {
		return this.sysid;
	}

	public void setSysid(long sysid) {
		this.sysid = sysid;
	}

	public String getAreacode() {
		return this.areacode;
	}

	public void setAreacode(String areacode) {
		this.areacode = areacode;
	}

	public long getDevusage() {
		return this.devusage;
	}

	public void setDevusage(long devusage) {
		this.devusage = devusage;
	}

	public String getDevicetime() {
		return this.devicetime;
	}

	public void setDevicetime(String devicetime) {
		this.devicetime = devicetime;
	}

	public String getServertime() {
		return this.servertime;
	}

	public void setServertime(String servertime) {
		this.servertime = servertime;
	}

	public String getContactName() {
		return this.contactName;
	}

	public void setContactName(String contactName) {
		this.contactName = contactName;
	}

	public double getCpu() {
		return this.cpu;
	}

	public void setCpu(double cpu) {
		this.cpu = cpu;
	}

	public double getMemory() {
		return this.memory;
	}

	public void setMemory(double memory) {
		this.memory = memory;
	}

	public double getHarddisk() {
		return this.harddisk;
	}

	public void setHarddisk(double harddisk) {
		this.harddisk = harddisk;
	}

	public long getErrorReason() {
		return this.errorReason;
	}

	public void setErrorReason(long errorReason) {
		this.errorReason = errorReason;
	}

}