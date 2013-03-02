package com.kingstargroup.ecard.hibernate.card;

/**
 * AbstractTSubsystem entity provides the base persistence definition of the
 * TSubsystem entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTSubsystem implements java.io.Serializable {

	// Fields

	private Long sysid;
	private String sysname;
	private Long systype;
	private String areacode;
	private Long serverid;
	private String macaddr;
	private String ip;
	private Long port;
	private String cardverno;
	private String initkey;
	private String dynakey;
	private String synctime;
	private String runstatus;
	private String status;
	private String opendate;
	private String closedate;
	private String remark;

	// Constructors

	/** default constructor */
	public AbstractTSubsystem() {
	}

	/** minimal constructor */
	public AbstractTSubsystem(Long sysid) {
		this.sysid = sysid;
	}

	/** full constructor */
	public AbstractTSubsystem(Long sysid, String sysname, Long systype,
			String areacode, Long serverid, String macaddr, String ip,
			Long port, String cardverno, String initkey, String dynakey,
			String synctime, String runstatus, String status, String opendate,
			String closedate, String remark) {
		this.sysid = sysid;
		this.sysname = sysname;
		this.systype = systype;
		this.areacode = areacode;
		this.serverid = serverid;
		this.macaddr = macaddr;
		this.ip = ip;
		this.port = port;
		this.cardverno = cardverno;
		this.initkey = initkey;
		this.dynakey = dynakey;
		this.synctime = synctime;
		this.runstatus = runstatus;
		this.status = status;
		this.opendate = opendate;
		this.closedate = closedate;
		this.remark = remark;
	}

	// Property accessors

	public Long getSysid() {
		return this.sysid;
	}

	public void setSysid(Long sysid) {
		this.sysid = sysid;
	}

	public String getSysname() {
		return this.sysname;
	}

	public void setSysname(String sysname) {
		this.sysname = sysname;
	}

	public Long getSystype() {
		return this.systype;
	}

	public void setSystype(Long systype) {
		this.systype = systype;
	}

	public String getAreacode() {
		return this.areacode;
	}

	public void setAreacode(String areacode) {
		this.areacode = areacode;
	}

	public Long getServerid() {
		return this.serverid;
	}

	public void setServerid(Long serverid) {
		this.serverid = serverid;
	}

	public String getMacaddr() {
		return this.macaddr;
	}

	public void setMacaddr(String macaddr) {
		this.macaddr = macaddr;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public Long getPort() {
		return this.port;
	}

	public void setPort(Long port) {
		this.port = port;
	}

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public String getInitkey() {
		return this.initkey;
	}

	public void setInitkey(String initkey) {
		this.initkey = initkey;
	}

	public String getDynakey() {
		return this.dynakey;
	}

	public void setDynakey(String dynakey) {
		this.dynakey = dynakey;
	}

	public String getSynctime() {
		return this.synctime;
	}

	public void setSynctime(String synctime) {
		this.synctime = synctime;
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

	public String getOpendate() {
		return this.opendate;
	}

	public void setOpendate(String opendate) {
		this.opendate = opendate;
	}

	public String getClosedate() {
		return this.closedate;
	}

	public void setClosedate(String closedate) {
		this.closedate = closedate;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}