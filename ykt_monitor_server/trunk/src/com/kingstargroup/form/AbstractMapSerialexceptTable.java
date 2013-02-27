package com.kingstargroup.form;

/**
 * AbstractMapSerialexceptTable entity provides the base persistence definition
 * of the MapSerialexceptTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapSerialexceptTable implements
		java.io.Serializable {

	// Fields

	private MapSerialexceptTableId id;
	private String transtime;
	private long cardno;
	private long purseno;
	private long cardcnt;
	private double cardbefbal;
	private double amount;
	private double cardaftbal;
	private double managefee;
	private long transmark;
	private long transcode;
	private long shopid;
	private long subsidyno;
	private String batchno;
	private long sysid;
	private String coldate;
	private String coltime;
	private String accdate;
	private String acctime;
	private String status;
	private long errcode;
	private String errmsg;
	private String delflag;
	private String contactname;
	private long abnormaltype;

	// Constructors

	/** default constructor */
	public AbstractMapSerialexceptTable() {
	}

	/** minimal constructor */
	public AbstractMapSerialexceptTable(MapSerialexceptTableId id, String status) {
		this.id = id;
		this.status = status;
	}

	/** full constructor */
	public AbstractMapSerialexceptTable(MapSerialexceptTableId id,
			String transtime, long cardno, long purseno, long cardcnt,
			double cardbefbal, double amount, double cardaftbal,
			double managefee, long transmark, long transcode, long shopid,
			long subsidyno, String batchno, long sysid, String coldate,
			String coltime, String accdate, String acctime, String status,
			long errcode, String errmsg, String delflag, String contactname,
			long abnormaltype) {
		this.id = id;
		this.transtime = transtime;
		this.cardno = cardno;
		this.purseno = purseno;
		this.cardcnt = cardcnt;
		this.cardbefbal = cardbefbal;
		this.amount = amount;
		this.cardaftbal = cardaftbal;
		this.managefee = managefee;
		this.transmark = transmark;
		this.transcode = transcode;
		this.shopid = shopid;
		this.subsidyno = subsidyno;
		this.batchno = batchno;
		this.sysid = sysid;
		this.coldate = coldate;
		this.coltime = coltime;
		this.accdate = accdate;
		this.acctime = acctime;
		this.status = status;
		this.errcode = errcode;
		this.errmsg = errmsg;
		this.delflag = delflag;
		this.contactname = contactname;
		this.abnormaltype = abnormaltype;
	}

	// Property accessors

	public MapSerialexceptTableId getId() {
		return this.id;
	}

	public void setId(MapSerialexceptTableId id) {
		this.id = id;
	}

	public String getTranstime() {
		return this.transtime;
	}

	public void setTranstime(String transtime) {
		this.transtime = transtime;
	}

	public long getCardno() {
		return this.cardno;
	}

	public void setCardno(long cardno) {
		this.cardno = cardno;
	}

	public long getPurseno() {
		return this.purseno;
	}

	public void setPurseno(long purseno) {
		this.purseno = purseno;
	}

	public long getCardcnt() {
		return this.cardcnt;
	}

	public void setCardcnt(long cardcnt) {
		this.cardcnt = cardcnt;
	}

	public double getCardbefbal() {
		return this.cardbefbal;
	}

	public void setCardbefbal(double cardbefbal) {
		this.cardbefbal = cardbefbal;
	}

	public double getAmount() {
		return this.amount;
	}

	public void setAmount(double amount) {
		this.amount = amount;
	}

	public double getCardaftbal() {
		return this.cardaftbal;
	}

	public void setCardaftbal(double cardaftbal) {
		this.cardaftbal = cardaftbal;
	}

	public double getManagefee() {
		return this.managefee;
	}

	public void setManagefee(double managefee) {
		this.managefee = managefee;
	}

	public long getTransmark() {
		return this.transmark;
	}

	public void setTransmark(long transmark) {
		this.transmark = transmark;
	}

	public long getTranscode() {
		return this.transcode;
	}

	public void setTranscode(long transcode) {
		this.transcode = transcode;
	}


	public long getShopid() {
		return shopid;
	}

	public void setShopid(long shopid) {
		this.shopid = shopid;
	}

	public long getSubsidyno() {
		return this.subsidyno;
	}

	public void setSubsidyno(long subsidyno) {
		this.subsidyno = subsidyno;
	}

	public String getBatchno() {
		return this.batchno;
	}

	public void setBatchno(String batchno) {
		this.batchno = batchno;
	}

	public long getSysid() {
		return this.sysid;
	}

	public void setSysid(long sysid) {
		this.sysid = sysid;
	}

	public String getColdate() {
		return this.coldate;
	}

	public void setColdate(String coldate) {
		this.coldate = coldate;
	}

	public String getColtime() {
		return this.coltime;
	}

	public void setColtime(String coltime) {
		this.coltime = coltime;
	}

	public String getAccdate() {
		return this.accdate;
	}

	public void setAccdate(String accdate) {
		this.accdate = accdate;
	}

	public String getAcctime() {
		return this.acctime;
	}

	public void setAcctime(String acctime) {
		this.acctime = acctime;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public long getErrcode() {
		return this.errcode;
	}

	public void setErrcode(long errcode) {
		this.errcode = errcode;
	}

	public String getErrmsg() {
		return this.errmsg;
	}

	public void setErrmsg(String errmsg) {
		this.errmsg = errmsg;
	}

	public String getDelflag() {
		return this.delflag;
	}

	public void setDelflag(String delflag) {
		this.delflag = delflag;
	}

	public String getContactname() {
		return this.contactname;
	}

	public void setContactname(String contactname) {
		this.contactname = contactname;
	}

	public long getAbnormaltype() {
		return this.abnormaltype;
	}

	public void setAbnormaltype(long abnormaltype) {
		this.abnormaltype = abnormaltype;
	}

}