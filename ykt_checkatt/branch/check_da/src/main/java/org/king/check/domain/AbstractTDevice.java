package org.king.check.domain;

import java.math.BigDecimal;

/**
 * AbstractTDevice entity provides the base persistence definition of the
 * TDevice entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDevice extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer deviceid;
	private String devicename;
	private String devphyid;
	private Integer deviceno;
	private Integer devphytype;
	private String devtypecode;
	private String devverno;
	private String cardphytype;
	private Integer fdeviceid;
	private Integer runstatus;
	private String status;
	private Integer svrportcnt;
	private Integer svrportno;
	private Integer commtype;
	private String ip;
	private Integer portno;
	private Integer baudrate;
	private String cardset;
	private String cardverno;
	private Integer lastseqno;
	private String lasttranstime;
	private Integer purseno;
	private double maxamt;
	private Integer sysid;
	private String areacode;
	private String doorlstver;
	private Integer devusage;
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
	public AbstractTDevice(Integer deviceid) {
		this.deviceid = deviceid;
	}

	/** full constructor */
	public AbstractTDevice(Integer deviceid, String devicename,
			String devphyid, Integer deviceno, Integer devphytype,
			String devtypecode, String devverno, String cardphytype,
			Integer fdeviceid, Integer runstatus, String status,
			Integer svrportcnt, Integer svrportno, Integer commtype,
			String ip, Integer portno, Integer baudrate, String cardset,
			String cardverno, Integer lastseqno, String lasttranstime,
			Integer purseno, double maxamt, Integer sysid,
			String areacode, String doorlstver, Integer devusage,
			String opendate, String closedate, String batchno,
			String lastsaved, String remark) {
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

	public Integer getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Integer deviceid) {
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

	public Integer getDeviceno() {
		return this.deviceno;
	}

	public void setDeviceno(Integer deviceno) {
		this.deviceno = deviceno;
	}

	public Integer getDevphytype() {
		return this.devphytype;
	}

	public void setDevphytype(Integer devphytype) {
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

	public Integer getFdeviceid() {
		return this.fdeviceid;
	}

	public void setFdeviceid(Integer fdeviceid) {
		this.fdeviceid = fdeviceid;
	}

	public Integer getRunstatus() {
		return this.runstatus;
	}

	public void setRunstatus(Integer runstatus) {
		this.runstatus = runstatus;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public Integer getSvrportcnt() {
		return this.svrportcnt;
	}

	public void setSvrportcnt(Integer svrportcnt) {
		this.svrportcnt = svrportcnt;
	}

	public Integer getSvrportno() {
		return this.svrportno;
	}

	public void setSvrportno(Integer svrportno) {
		this.svrportno = svrportno;
	}

	public Integer getCommtype() {
		return this.commtype;
	}

	public void setCommtype(Integer commtype) {
		this.commtype = commtype;
	}

	public String getIp() {
		return this.ip;
	}

	public void setIp(String ip) {
		this.ip = ip;
	}

	public Integer getPortno() {
		return this.portno;
	}

	public void setPortno(Integer portno) {
		this.portno = portno;
	}

	public Integer getBaudrate() {
		return this.baudrate;
	}

	public void setBaudrate(Integer baudrate) {
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

	public Integer getLastseqno() {
		return this.lastseqno;
	}

	public void setLastseqno(Integer lastseqno) {
		this.lastseqno = lastseqno;
	}

	public String getLasttranstime() {
		return this.lasttranstime;
	}

	public void setLasttranstime(String lasttranstime) {
		this.lasttranstime = lasttranstime;
	}

	public Integer getPurseno() {
		return this.purseno;
	}

	public void setPurseno(Integer purseno) {
		this.purseno = purseno;
	}

	public double getMaxamt() {
		return this.maxamt;
	}

	public void setMaxamt(double maxamt) {
		this.maxamt = maxamt;
	}

	public Integer getSysid() {
		return this.sysid;
	}

	public void setSysid(Integer sysid) {
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

	public Integer getDevusage() {
		return this.devusage;
	}

	public void setDevusage(Integer devusage) {
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

	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((areacode == null) ? 0 : areacode.hashCode());
		result = prime * result + ((batchno == null) ? 0 : batchno.hashCode());
		result = prime * result
				+ ((baudrate == null) ? 0 : baudrate.hashCode());
		result = prime * result
				+ ((cardphytype == null) ? 0 : cardphytype.hashCode());
		result = prime * result + ((cardset == null) ? 0 : cardset.hashCode());
		result = prime * result
				+ ((cardverno == null) ? 0 : cardverno.hashCode());
		result = prime * result
				+ ((closedate == null) ? 0 : closedate.hashCode());
		result = prime * result
				+ ((commtype == null) ? 0 : commtype.hashCode());
		result = prime * result
				+ ((deviceid == null) ? 0 : deviceid.hashCode());
		result = prime * result
				+ ((devicename == null) ? 0 : devicename.hashCode());
		result = prime * result
				+ ((deviceno == null) ? 0 : deviceno.hashCode());
		result = prime * result
				+ ((devphyid == null) ? 0 : devphyid.hashCode());
		result = prime * result
				+ ((devphytype == null) ? 0 : devphytype.hashCode());
		result = prime * result
				+ ((devtypecode == null) ? 0 : devtypecode.hashCode());
		result = prime * result
				+ ((devusage == null) ? 0 : devusage.hashCode());
		result = prime * result
				+ ((devverno == null) ? 0 : devverno.hashCode());
		result = prime * result
				+ ((doorlstver == null) ? 0 : doorlstver.hashCode());
		result = prime * result
				+ ((fdeviceid == null) ? 0 : fdeviceid.hashCode());
		result = prime * result + ((ip == null) ? 0 : ip.hashCode());
		result = prime * result
				+ ((lastsaved == null) ? 0 : lastsaved.hashCode());
		result = prime * result
				+ ((lastseqno == null) ? 0 : lastseqno.hashCode());
		result = prime * result
				+ ((lasttranstime == null) ? 0 : lasttranstime.hashCode());
		long temp;
		temp = Double.doubleToLongBits(maxamt);
		result = prime * result + (int) (temp ^ (temp >>> 32));
		result = prime * result
				+ ((opendate == null) ? 0 : opendate.hashCode());
		result = prime * result + ((portno == null) ? 0 : portno.hashCode());
		result = prime * result + ((purseno == null) ? 0 : purseno.hashCode());
		result = prime * result + ((remark == null) ? 0 : remark.hashCode());
		result = prime * result
				+ ((runstatus == null) ? 0 : runstatus.hashCode());
		result = prime * result + ((status == null) ? 0 : status.hashCode());
		result = prime * result
				+ ((svrportcnt == null) ? 0 : svrportcnt.hashCode());
		result = prime * result
				+ ((svrportno == null) ? 0 : svrportno.hashCode());
		result = prime * result + ((sysid == null) ? 0 : sysid.hashCode());
		return result;
	}

	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractTDevice))
			return false;
		AbstractTDevice other = (AbstractTDevice) obj;
		if (areacode == null) {
			if (other.areacode != null)
				return false;
		} else if (!areacode.equals(other.areacode))
			return false;
		if (batchno == null) {
			if (other.batchno != null)
				return false;
		} else if (!batchno.equals(other.batchno))
			return false;
		if (baudrate == null) {
			if (other.baudrate != null)
				return false;
		} else if (!baudrate.equals(other.baudrate))
			return false;
		if (cardphytype == null) {
			if (other.cardphytype != null)
				return false;
		} else if (!cardphytype.equals(other.cardphytype))
			return false;
		if (cardset == null) {
			if (other.cardset != null)
				return false;
		} else if (!cardset.equals(other.cardset))
			return false;
		if (cardverno == null) {
			if (other.cardverno != null)
				return false;
		} else if (!cardverno.equals(other.cardverno))
			return false;
		if (closedate == null) {
			if (other.closedate != null)
				return false;
		} else if (!closedate.equals(other.closedate))
			return false;
		if (commtype == null) {
			if (other.commtype != null)
				return false;
		} else if (!commtype.equals(other.commtype))
			return false;
		if (deviceid == null) {
			if (other.deviceid != null)
				return false;
		} else if (!deviceid.equals(other.deviceid))
			return false;
		if (devicename == null) {
			if (other.devicename != null)
				return false;
		} else if (!devicename.equals(other.devicename))
			return false;
		if (deviceno == null) {
			if (other.deviceno != null)
				return false;
		} else if (!deviceno.equals(other.deviceno))
			return false;
		if (devphyid == null) {
			if (other.devphyid != null)
				return false;
		} else if (!devphyid.equals(other.devphyid))
			return false;
		if (devphytype == null) {
			if (other.devphytype != null)
				return false;
		} else if (!devphytype.equals(other.devphytype))
			return false;
		if (devtypecode == null) {
			if (other.devtypecode != null)
				return false;
		} else if (!devtypecode.equals(other.devtypecode))
			return false;
		if (devusage == null) {
			if (other.devusage != null)
				return false;
		} else if (!devusage.equals(other.devusage))
			return false;
		if (devverno == null) {
			if (other.devverno != null)
				return false;
		} else if (!devverno.equals(other.devverno))
			return false;
		if (doorlstver == null) {
			if (other.doorlstver != null)
				return false;
		} else if (!doorlstver.equals(other.doorlstver))
			return false;
		if (fdeviceid == null) {
			if (other.fdeviceid != null)
				return false;
		} else if (!fdeviceid.equals(other.fdeviceid))
			return false;
		if (ip == null) {
			if (other.ip != null)
				return false;
		} else if (!ip.equals(other.ip))
			return false;
		if (lastsaved == null) {
			if (other.lastsaved != null)
				return false;
		} else if (!lastsaved.equals(other.lastsaved))
			return false;
		if (lastseqno == null) {
			if (other.lastseqno != null)
				return false;
		} else if (!lastseqno.equals(other.lastseqno))
			return false;
		if (lasttranstime == null) {
			if (other.lasttranstime != null)
				return false;
		} else if (!lasttranstime.equals(other.lasttranstime))
			return false;
		if (Double.doubleToLongBits(maxamt) != Double
				.doubleToLongBits(other.maxamt))
			return false;
		if (opendate == null) {
			if (other.opendate != null)
				return false;
		} else if (!opendate.equals(other.opendate))
			return false;
		if (portno == null) {
			if (other.portno != null)
				return false;
		} else if (!portno.equals(other.portno))
			return false;
		if (purseno == null) {
			if (other.purseno != null)
				return false;
		} else if (!purseno.equals(other.purseno))
			return false;
		if (remark == null) {
			if (other.remark != null)
				return false;
		} else if (!remark.equals(other.remark))
			return false;
		if (runstatus == null) {
			if (other.runstatus != null)
				return false;
		} else if (!runstatus.equals(other.runstatus))
			return false;
		if (status == null) {
			if (other.status != null)
				return false;
		} else if (!status.equals(other.status))
			return false;
		if (svrportcnt == null) {
			if (other.svrportcnt != null)
				return false;
		} else if (!svrportcnt.equals(other.svrportcnt))
			return false;
		if (svrportno == null) {
			if (other.svrportno != null)
				return false;
		} else if (!svrportno.equals(other.svrportno))
			return false;
		if (sysid == null) {
			if (other.sysid != null)
				return false;
		} else if (!sysid.equals(other.sysid))
			return false;
		return true;
	}

	public String toString() {
		return "AbstractTDevice [areacode=" + areacode + ", batchno=" + batchno
				+ ", baudrate=" + baudrate + ", cardphytype=" + cardphytype
				+ ", cardset=" + cardset + ", cardverno=" + cardverno
				+ ", closedate=" + closedate + ", commtype=" + commtype
				+ ", deviceid=" + deviceid + ", devicename=" + devicename
				+ ", deviceno=" + deviceno + ", devphyid=" + devphyid
				+ ", devphytype=" + devphytype + ", devtypecode=" + devtypecode
				+ ", devusage=" + devusage + ", devverno=" + devverno
				+ ", doorlstver=" + doorlstver + ", fdeviceid=" + fdeviceid
				+ ", ip=" + ip + ", lastsaved=" + lastsaved + ", lastseqno="
				+ lastseqno + ", lasttranstime=" + lasttranstime + ", maxamt="
				+ maxamt + ", opendate=" + opendate + ", portno=" + portno
				+ ", purseno=" + purseno + ", remark=" + remark
				+ ", runstatus=" + runstatus + ", status=" + status
				+ ", svrportcnt=" + svrportcnt + ", svrportno=" + svrportno
				+ ", sysid=" + sysid + "]";
	}

}