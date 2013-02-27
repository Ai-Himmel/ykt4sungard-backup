package com.kingstargroup.form;

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
	private String devtypecode;
	private String devverno;
	private String cardphytype;
	private long svrportcnt;
	private long fdeviceid;
	private String runstatus;
	private String status;
	private long commtype;
	private String ip;
	private long portno;
	private long svrportno;
	private long deviceno;
	private long baudrate;
	private String cardset;
	private String cardverno;
	private long lastseqno;
	private String lasttranstime;
	private long purseno;
	private long maxamt;
	private long devphytype;
	private long sysid;
	private String areacode;
	private String doorlstver;
	private long devusage;

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
			String devtypecode, String devverno, String cardphytype,
			long svrportcnt, long fdeviceid, String runstatus, String status,
			long commtype, String ip, long portno, long svrportno,
			long deviceno, long baudrate, String cardset, String cardverno,
			long lastseqno, String lasttranstime, long purseno, long maxamt,
			long devphytype, long sysid, String areacode, String doorlstver,
			long devusage) {
		this.deviceid = deviceid;
		this.devicename = devicename;
		this.devphyid = devphyid;
		this.devtypecode = devtypecode;
		this.devverno = devverno;
		this.cardphytype = cardphytype;
		this.svrportcnt = svrportcnt;
		this.fdeviceid = fdeviceid;
		this.runstatus = runstatus;
		this.status = status;
		this.commtype = commtype;
		this.ip = ip;
		this.portno = portno;
		this.svrportno = svrportno;
		this.deviceno = deviceno;
		this.baudrate = baudrate;
		this.cardset = cardset;
		this.cardverno = cardverno;
		this.lastseqno = lastseqno;
		this.lasttranstime = lasttranstime;
		this.purseno = purseno;
		this.maxamt = maxamt;
		this.devphytype = devphytype;
		this.sysid = sysid;
		this.areacode = areacode;
		this.doorlstver = doorlstver;
		this.devusage = devusage;
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

	public long getSvrportcnt() {
		return this.svrportcnt;
	}

	public void setSvrportcnt(long svrportcnt) {
		this.svrportcnt = svrportcnt;
	}

	public long getFdeviceid() {
		return this.fdeviceid;
	}

	public void setFdeviceid(long fdeviceid) {
		this.fdeviceid = fdeviceid;
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

	public long getSvrportno() {
		return this.svrportno;
	}

	public void setSvrportno(long svrportno) {
		this.svrportno = svrportno;
	}

	public long getDeviceno() {
		return this.deviceno;
	}

	public void setDeviceno(long deviceno) {
		this.deviceno = deviceno;
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

	public long getMaxamt() {
		return this.maxamt;
	}

	public void setMaxamt(long maxamt) {
		this.maxamt = maxamt;
	}

	public long getDevphytype() {
		return this.devphytype;
	}

	public void setDevphytype(long devphytype) {
		this.devphytype = devphytype;
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

}