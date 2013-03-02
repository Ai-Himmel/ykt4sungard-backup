package com.kingstargroup.ecard.hibernate.device;

/**
 * AbstractTDevice entity provides the base persistence definition of the
 * TDevice entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDevice implements java.io.Serializable {

	// Fields

	private Long deviceid;
	private String devicename;
	private String devphyid;
	private Long deviceno;
	private Long devphytype;
	private String devtypecode;
	private String devverno;
	private String cardphytype;
	private Long fdeviceid;
	private String runstatus;
	private String status;
	private Long svrportcnt;
	private Long svrportno;
	private Long commtype;
	private String ip;
	private Long portno;
	private Long baudrate;
	private String cardset;
	private String cardverno;
	private Long lastseqno;
	private String lasttranstime;
	private Long purseno;
	private Double maxamt;
	private Long sysid;
	private String areacode;
	private String doorlstver;
	private Long devusage;
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
	public AbstractTDevice(Long deviceid) {
		this.deviceid = deviceid;
	}

	/** full constructor */
	public AbstractTDevice(Long deviceid, String devicename, String devphyid,
			Long deviceno, Long devphytype, String devtypecode,
			String devverno, String cardphytype, Long fdeviceid,
			String runstatus, String status, Long svrportcnt, Long svrportno,
			Long commtype, String ip, Long portno, Long baudrate,
			String cardset, String cardverno, Long lastseqno,
			String lasttranstime, Long purseno, Double maxamt, Long sysid,
			String areacode, String doorlstver, Long devusage, String opendate,
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

	public Long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Long deviceid) {
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

	public Long getDeviceno() {
		return this.deviceno;
	}

	public void setDeviceno(Long deviceno) {
		this.deviceno = deviceno;
	}

	public Long getDevphytype() {
		return this.devphytype;
	}

	public void setDevphytype(Long devphytype) {
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

	public Long getFdeviceid() {
		return this.fdeviceid;
	}

	public void setFdeviceid(Long fdeviceid) {
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

	public Long getSvrportcnt() {
		return this.svrportcnt;
	}

	public void setSvrportcnt(Long svrportcnt) {
		this.svrportcnt = svrportcnt;
	}

	public Long getSvrportno() {
		return this.svrportno;
	}

	public void setSvrportno(Long svrportno) {
		this.svrportno = svrportno;
	}

	public Long getCommtype() {
		return this.commtype;
	}

	public void setCommtype(Long commtype) {
		this.commtype = commtype;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public Long getPortno() {
		return this.portno;
	}

	public void setPortno(Long portno) {
		this.portno = portno;
	}

	public Long getBaudrate() {
		return this.baudrate;
	}

	public void setBaudrate(Long baudrate) {
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

	public Long getLastseqno() {
		return this.lastseqno;
	}

	public void setLastseqno(Long lastseqno) {
		this.lastseqno = lastseqno;
	}

	public String getLasttranstime() {
		return this.lasttranstime;
	}

	public void setLasttranstime(String lasttranstime) {
		this.lasttranstime = lasttranstime;
	}

	public Long getPurseno() {
		return this.purseno;
	}

	public void setPurseno(Long purseno) {
		this.purseno = purseno;
	}

	public Double getMaxamt() {
		return this.maxamt;
	}

	public void setMaxamt(Double maxamt) {
		this.maxamt = maxamt;
	}

	public Long getSysid() {
		return this.sysid;
	}

	public void setSysid(Long sysid) {
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

	public Long getDevusage() {
		return this.devusage;
	}

	public void setDevusage(Long devusage) {
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