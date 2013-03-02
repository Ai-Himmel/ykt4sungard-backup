package com.kingstargroup.fdykt.newform;

/**
 * AbstractVDeviceId entity provides the base persistence definition of the
 * VDeviceId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractVDeviceId implements java.io.Serializable {

	// Fields

	private String nu;
	private Long deviceid;
	private String devicename;
	private String devphyid;
	private String devtypecode;
	private String devverno;
	private String cardphytype;
	private Long svrportcnt;
	private Long fdeviceid;
	private String runstatus;
	private String status;
	private Long commtype;
	private String ip;
	private Long portno;
	private Long svrportno;
	private Long deviceno;
	private Long baudrate;
	private String cardset;
	private String cardverno;
	private Long lastseqno;
	private String lasttranstime;
	private Long purseno;
	private Double maxamt;
	private Long devphytype;
	private Long sysid;
	private String areacode;
	private String doorlstver;
	private Long devusage;

	// Constructors

	/** default constructor */
	public AbstractVDeviceId() {
	}

	/** minimal constructor */
	public AbstractVDeviceId(Long deviceid) {
		this.deviceid = deviceid;
	}

	/** full constructor */
	public AbstractVDeviceId(String nu, Long deviceid, String devicename,
			String devphyid, String devtypecode, String devverno,
			String cardphytype, Long svrportcnt, Long fdeviceid,
			String runstatus, String status, Long commtype, String ip,
			Long portno, Long svrportno, Long deviceno, Long baudrate,
			String cardset, String cardverno, Long lastseqno,
			String lasttranstime, Long purseno, Double maxamt, Long devphytype,
			Long sysid, String areacode, String doorlstver, Long devusage) {
		this.nu = nu;
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

	public String getNu() {
		return this.nu;
	}

	public void setNu(String nu) {
		this.nu = nu;
	}

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

	public Long getSvrportcnt() {
		return this.svrportcnt;
	}

	public void setSvrportcnt(Long svrportcnt) {
		this.svrportcnt = svrportcnt;
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

	public Long getSvrportno() {
		return this.svrportno;
	}

	public void setSvrportno(Long svrportno) {
		this.svrportno = svrportno;
	}

	public Long getDeviceno() {
		return this.deviceno;
	}

	public void setDeviceno(Long deviceno) {
		this.deviceno = deviceno;
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

	public Long getDevphytype() {
		return this.devphytype;
	}

	public void setDevphytype(Long devphytype) {
		this.devphytype = devphytype;
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

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractVDeviceId))
			return false;
		AbstractVDeviceId castOther = (AbstractVDeviceId) other;

		return ((this.getNu() == castOther.getNu()) || (this.getNu() != null
				&& castOther.getNu() != null && this.getNu().equals(
				castOther.getNu())))
				&& ((this.getDeviceid() == castOther.getDeviceid()) || (this
						.getDeviceid() != null
						&& castOther.getDeviceid() != null && this
						.getDeviceid().equals(castOther.getDeviceid())))
				&& ((this.getDevicename() == castOther.getDevicename()) || (this
						.getDevicename() != null
						&& castOther.getDevicename() != null && this
						.getDevicename().equals(castOther.getDevicename())))
				&& ((this.getDevphyid() == castOther.getDevphyid()) || (this
						.getDevphyid() != null
						&& castOther.getDevphyid() != null && this
						.getDevphyid().equals(castOther.getDevphyid())))
				&& ((this.getDevtypecode() == castOther.getDevtypecode()) || (this
						.getDevtypecode() != null
						&& castOther.getDevtypecode() != null && this
						.getDevtypecode().equals(castOther.getDevtypecode())))
				&& ((this.getDevverno() == castOther.getDevverno()) || (this
						.getDevverno() != null
						&& castOther.getDevverno() != null && this
						.getDevverno().equals(castOther.getDevverno())))
				&& ((this.getCardphytype() == castOther.getCardphytype()) || (this
						.getCardphytype() != null
						&& castOther.getCardphytype() != null && this
						.getCardphytype().equals(castOther.getCardphytype())))
				&& ((this.getSvrportcnt() == castOther.getSvrportcnt()) || (this
						.getSvrportcnt() != null
						&& castOther.getSvrportcnt() != null && this
						.getSvrportcnt().equals(castOther.getSvrportcnt())))
				&& ((this.getFdeviceid() == castOther.getFdeviceid()) || (this
						.getFdeviceid() != null
						&& castOther.getFdeviceid() != null && this
						.getFdeviceid().equals(castOther.getFdeviceid())))
				&& ((this.getRunstatus() == castOther.getRunstatus()) || (this
						.getRunstatus() != null
						&& castOther.getRunstatus() != null && this
						.getRunstatus().equals(castOther.getRunstatus())))
				&& ((this.getStatus() == castOther.getStatus()) || (this
						.getStatus() != null
						&& castOther.getStatus() != null && this.getStatus()
						.equals(castOther.getStatus())))
				&& ((this.getCommtype() == castOther.getCommtype()) || (this
						.getCommtype() != null
						&& castOther.getCommtype() != null && this
						.getCommtype().equals(castOther.getCommtype())))
				&& ((this.getIp() == castOther.getIp()) || (this.getIp() != null
						&& castOther.getIp() != null && this.getIp().equals(
						castOther.getIp())))
				&& ((this.getPortno() == castOther.getPortno()) || (this
						.getPortno() != null
						&& castOther.getPortno() != null && this.getPortno()
						.equals(castOther.getPortno())))
				&& ((this.getSvrportno() == castOther.getSvrportno()) || (this
						.getSvrportno() != null
						&& castOther.getSvrportno() != null && this
						.getSvrportno().equals(castOther.getSvrportno())))
				&& ((this.getDeviceno() == castOther.getDeviceno()) || (this
						.getDeviceno() != null
						&& castOther.getDeviceno() != null && this
						.getDeviceno().equals(castOther.getDeviceno())))
				&& ((this.getBaudrate() == castOther.getBaudrate()) || (this
						.getBaudrate() != null
						&& castOther.getBaudrate() != null && this
						.getBaudrate().equals(castOther.getBaudrate())))
				&& ((this.getCardset() == castOther.getCardset()) || (this
						.getCardset() != null
						&& castOther.getCardset() != null && this.getCardset()
						.equals(castOther.getCardset())))
				&& ((this.getCardverno() == castOther.getCardverno()) || (this
						.getCardverno() != null
						&& castOther.getCardverno() != null && this
						.getCardverno().equals(castOther.getCardverno())))
				&& ((this.getLastseqno() == castOther.getLastseqno()) || (this
						.getLastseqno() != null
						&& castOther.getLastseqno() != null && this
						.getLastseqno().equals(castOther.getLastseqno())))
				&& ((this.getLasttranstime() == castOther.getLasttranstime()) || (this
						.getLasttranstime() != null
						&& castOther.getLasttranstime() != null && this
						.getLasttranstime()
						.equals(castOther.getLasttranstime())))
				&& ((this.getPurseno() == castOther.getPurseno()) || (this
						.getPurseno() != null
						&& castOther.getPurseno() != null && this.getPurseno()
						.equals(castOther.getPurseno())))
				&& ((this.getMaxamt() == castOther.getMaxamt()) || (this
						.getMaxamt() != null
						&& castOther.getMaxamt() != null && this.getMaxamt()
						.equals(castOther.getMaxamt())))
				&& ((this.getDevphytype() == castOther.getDevphytype()) || (this
						.getDevphytype() != null
						&& castOther.getDevphytype() != null && this
						.getDevphytype().equals(castOther.getDevphytype())))
				&& ((this.getSysid() == castOther.getSysid()) || (this
						.getSysid() != null
						&& castOther.getSysid() != null && this.getSysid()
						.equals(castOther.getSysid())))
				&& ((this.getAreacode() == castOther.getAreacode()) || (this
						.getAreacode() != null
						&& castOther.getAreacode() != null && this
						.getAreacode().equals(castOther.getAreacode())))
				&& ((this.getDoorlstver() == castOther.getDoorlstver()) || (this
						.getDoorlstver() != null
						&& castOther.getDoorlstver() != null && this
						.getDoorlstver().equals(castOther.getDoorlstver())))
				&& ((this.getDevusage() == castOther.getDevusage()) || (this
						.getDevusage() != null
						&& castOther.getDevusage() != null && this
						.getDevusage().equals(castOther.getDevusage())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result + (getNu() == null ? 0 : this.getNu().hashCode());
		result = 37 * result
				+ (getDeviceid() == null ? 0 : this.getDeviceid().hashCode());
		result = 37
				* result
				+ (getDevicename() == null ? 0 : this.getDevicename()
						.hashCode());
		result = 37 * result
				+ (getDevphyid() == null ? 0 : this.getDevphyid().hashCode());
		result = 37
				* result
				+ (getDevtypecode() == null ? 0 : this.getDevtypecode()
						.hashCode());
		result = 37 * result
				+ (getDevverno() == null ? 0 : this.getDevverno().hashCode());
		result = 37
				* result
				+ (getCardphytype() == null ? 0 : this.getCardphytype()
						.hashCode());
		result = 37
				* result
				+ (getSvrportcnt() == null ? 0 : this.getSvrportcnt()
						.hashCode());
		result = 37 * result
				+ (getFdeviceid() == null ? 0 : this.getFdeviceid().hashCode());
		result = 37 * result
				+ (getRunstatus() == null ? 0 : this.getRunstatus().hashCode());
		result = 37 * result
				+ (getStatus() == null ? 0 : this.getStatus().hashCode());
		result = 37 * result
				+ (getCommtype() == null ? 0 : this.getCommtype().hashCode());
		result = 37 * result + (getIp() == null ? 0 : this.getIp().hashCode());
		result = 37 * result
				+ (getPortno() == null ? 0 : this.getPortno().hashCode());
		result = 37 * result
				+ (getSvrportno() == null ? 0 : this.getSvrportno().hashCode());
		result = 37 * result
				+ (getDeviceno() == null ? 0 : this.getDeviceno().hashCode());
		result = 37 * result
				+ (getBaudrate() == null ? 0 : this.getBaudrate().hashCode());
		result = 37 * result
				+ (getCardset() == null ? 0 : this.getCardset().hashCode());
		result = 37 * result
				+ (getCardverno() == null ? 0 : this.getCardverno().hashCode());
		result = 37 * result
				+ (getLastseqno() == null ? 0 : this.getLastseqno().hashCode());
		result = 37
				* result
				+ (getLasttranstime() == null ? 0 : this.getLasttranstime()
						.hashCode());
		result = 37 * result
				+ (getPurseno() == null ? 0 : this.getPurseno().hashCode());
		result = 37 * result
				+ (getMaxamt() == null ? 0 : this.getMaxamt().hashCode());
		result = 37
				* result
				+ (getDevphytype() == null ? 0 : this.getDevphytype()
						.hashCode());
		result = 37 * result
				+ (getSysid() == null ? 0 : this.getSysid().hashCode());
		result = 37 * result
				+ (getAreacode() == null ? 0 : this.getAreacode().hashCode());
		result = 37
				* result
				+ (getDoorlstver() == null ? 0 : this.getDoorlstver()
						.hashCode());
		result = 37 * result
				+ (getDevusage() == null ? 0 : this.getDevusage().hashCode());
		return result;
	}

}