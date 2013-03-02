package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDevice entity provides the base persistence definition of the
 * TDevice entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDevice implements java.io.Serializable {

	// Fields

	private long deviceid;
	private String devicename;
	private String devphyid;
	private long deviceno;
	private long devphytype;
	private String devtypecode;
	private String devverno;
	private String cardphytype;
	private long fdeviceid;
	private long runstatus;
	private String status;
	private long svrportcnt;
	private long svrportno;
	private long commtype;
	private String ip;
	private long portno;
	private long baudrate;
	private String cardset;
	private String cardverno;
	private long lastseqno;
	private String lasttranstime;
	private long purseno;
	private double maxamt;
	private long sysid;
	private String areacode;
	private String doorlstver;
	private long devusage;
	private String opendate;
	private String closedate;
	private String batchno;
	private String lastsaved;
	private String remark;

	// Constructors

	/** default constructor */
	public AbstractTDevice() {
	}

	/** minimal constructor */
	public AbstractTDevice(long deviceid) {
		this.deviceid = deviceid;
	}

	/** full constructor */
	public AbstractTDevice(long deviceid, String devicename, String devphyid,
			long deviceno, long devphytype, String devtypecode,
			String devverno, String cardphytype, long fdeviceid,
			long runstatus, String status, long svrportcnt, long svrportno,
			long commtype, String ip, long portno, long baudrate,
			String cardset, String cardverno, long lastseqno,
			String lasttranstime, long purseno, double maxamt, long sysid,
			String areacode, String doorlstver, long devusage, String opendate,
			String closedate, String batchno, String lastsaved, String remark) {
		this.deviceid = deviceid;
		this.devicename = devicename;
		this.devphyid = devphyid;
		this.deviceno = deviceno;
		this.devphytype = devphytype;
		this.devtypecode = devtypecode;
		this.devverno = devverno;
		this.cardphytype = cardphytype;
		this.fdeviceid = fdeviceid;
		this.runstatus = runstatus;
		this.status = status;
		this.svrportcnt = svrportcnt;
		this.svrportno = svrportno;
		this.commtype = commtype;
		this.ip = ip;
		this.portno = portno;
		this.baudrate = baudrate;
		this.cardset = cardset;
		this.cardverno = cardverno;
		this.lastseqno = lastseqno;
		this.lasttranstime = lasttranstime;
		this.purseno = purseno;
		this.maxamt = maxamt;
		this.sysid = sysid;
		this.areacode = areacode;
		this.doorlstver = doorlstver;
		this.devusage = devusage;
		this.opendate = opendate;
		this.closedate = closedate;
		this.batchno = batchno;
		this.lastsaved = lastsaved;
		this.remark = remark;
	}

	// Property accessors

	public long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
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

	public long getDeviceno() {
		return this.deviceno;
	}

	public void setDeviceno(long deviceno) {
		this.deviceno = deviceno;
	}

	public long getDevphytype() {
		return this.devphytype;
	}

	public void setDevphytype(long devphytype) {
		this.devphytype = devphytype;
	}

	public String getDevtypecode() {
		return this.devtypecode;
	}

	public void setDevtypecode(String devtypecode) {
		this.devtypecode = devtypecode;
	}

	public String getDevverno() {
		return this.devverno;
	}

	public void setDevverno(String devverno) {
		this.devverno = devverno;
	}

	public String getCardphytype() {
		return this.cardphytype;
	}

	public void setCardphytype(String cardphytype) {
		this.cardphytype = cardphytype;
	}

	public long getFdeviceid() {
		return this.fdeviceid;
	}

	public void setFdeviceid(long fdeviceid) {
		this.fdeviceid = fdeviceid;
	}

	public long getRunstatus() {
		return this.runstatus;
	}

	public void setRunstatus(long runstatus) {
		this.runstatus = runstatus;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public long getSvrportcnt() {
		return this.svrportcnt;
	}

	public void setSvrportcnt(long svrportcnt) {
		this.svrportcnt = svrportcnt;
	}

	public long getSvrportno() {
		return this.svrportno;
	}

	public void setSvrportno(long svrportno) {
		this.svrportno = svrportno;
	}

	public long getCommtype() {
		return this.commtype;
	}

	public void setCommtype(long commtype) {
		this.commtype = commtype;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public long getPortno() {
		return this.portno;
	}

	public void setPortno(long portno) {
		this.portno = portno;
	}

	public long getBaudrate() {
		return this.baudrate;
	}

	public void setBaudrate(long baudrate) {
		this.baudrate = baudrate;
	}

	public String getCardset() {
		return this.cardset;
	}

	public void setCardset(String cardset) {
		this.cardset = cardset;
	}

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public long getLastseqno() {
		return this.lastseqno;
	}

	public void setLastseqno(long lastseqno) {
		this.lastseqno = lastseqno;
	}

	public String getLasttranstime() {
		return this.lasttranstime;
	}

	public void setLasttranstime(String lasttranstime) {
		this.lasttranstime = lasttranstime;
	}

	public long getPurseno() {
		return this.purseno;
	}

	public void setPurseno(long purseno) {
		this.purseno = purseno;
	}

	public double getMaxamt() {
		return this.maxamt;
	}

	public void setMaxamt(double maxamt) {
		this.maxamt = maxamt;
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

	public String getDoorlstver() {
		return this.doorlstver;
	}

	public void setDoorlstver(String doorlstver) {
		this.doorlstver = doorlstver;
	}

	public long getDevusage() {
		return this.devusage;
	}

	public void setDevusage(long devusage) {
		this.devusage = devusage;
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

	public String getBatchno() {
		return this.batchno;
	}

	public void setBatchno(String batchno) {
		this.batchno = batchno;
	}

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}