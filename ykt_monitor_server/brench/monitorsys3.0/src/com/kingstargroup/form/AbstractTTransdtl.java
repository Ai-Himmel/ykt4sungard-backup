package com.kingstargroup.form;

/**
 * AbstractTTransdtl entity provides the base persistence definition of the
 * TTransdtl entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTransdtl implements java.io.Serializable {

	// Fields

	private TTransdtlId id;
	private String acctime;
	private String transdate;
	private String transtime;
	private String coldate;
	private String coltime;
	private long transcode;
	private long paytype;
	private String voucherno;
	private long custid;
	private String custname;
	private long cardno;
	private long purseno;
	private long cardcnt;
	private double cardbefbal;
	private double cardaftbal;
	private double amount;
	private double boardfee;
	private String opercode;
	private long sysid;
	private String devphyid;
	private long devseqno;
	private long exttype;
	private String extdata;
	private String revflag;
	private String status;
	private long errcode;
	private String remark;

	// Constructors

	/** default constructor */
	public AbstractTTransdtl() {
	}

	/** minimal constructor */
	public AbstractTTransdtl(TTransdtlId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTTransdtl(TTransdtlId id, String acctime, String transdate,
			String transtime, String coldate, String coltime, long transcode,
			long paytype, String voucherno, long custid, String custname,
			long cardno, long purseno, long cardcnt, double cardbefbal,
			double cardaftbal, double amount, double boardfee, String opercode,
			long sysid, String devphyid, long devseqno, long exttype,
			String extdata, String revflag, String status, long errcode,
			String remark) {
		this.id = id;
		this.acctime = acctime;
		this.transdate = transdate;
		this.transtime = transtime;
		this.coldate = coldate;
		this.coltime = coltime;
		this.transcode = transcode;
		this.paytype = paytype;
		this.voucherno = voucherno;
		this.custid = custid;
		this.custname = custname;
		this.cardno = cardno;
		this.purseno = purseno;
		this.cardcnt = cardcnt;
		this.cardbefbal = cardbefbal;
		this.cardaftbal = cardaftbal;
		this.amount = amount;
		this.boardfee = boardfee;
		this.opercode = opercode;
		this.sysid = sysid;
		this.devphyid = devphyid;
		this.devseqno = devseqno;
		this.exttype = exttype;
		this.extdata = extdata;
		this.revflag = revflag;
		this.status = status;
		this.errcode = errcode;
		this.remark = remark;
	}

	// Property accessors

	public TTransdtlId getId() {
		return this.id;
	}

	public void setId(TTransdtlId id) {
		this.id = id;
	}

	public String getAcctime() {
		return this.acctime;
	}

	public void setAcctime(String acctime) {
		this.acctime = acctime;
	}

	public String getTransdate() {
		return this.transdate;
	}

	public void setTransdate(String transdate) {
		this.transdate = transdate;
	}

	public String getTranstime() {
		return this.transtime;
	}

	public void setTranstime(String transtime) {
		this.transtime = transtime;
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

	public long getTranscode() {
		return this.transcode;
	}

	public void setTranscode(long transcode) {
		this.transcode = transcode;
	}

	public long getPaytype() {
		return this.paytype;
	}

	public void setPaytype(long paytype) {
		this.paytype = paytype;
	}

	public String getVoucherno() {
		return this.voucherno;
	}

	public void setVoucherno(String voucherno) {
		this.voucherno = voucherno;
	}

	public long getCustid() {
		return this.custid;
	}

	public void setCustid(long custid) {
		this.custid = custid;
	}

	public String getCustname() {
		return this.custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
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

	public double getCardaftbal() {
		return this.cardaftbal;
	}

	public void setCardaftbal(double cardaftbal) {
		this.cardaftbal = cardaftbal;
	}

	public double getAmount() {
		return this.amount;
	}

	public void setAmount(double amount) {
		this.amount = amount;
	}

	public double getBoardfee() {
		return this.boardfee;
	}

	public void setBoardfee(double boardfee) {
		this.boardfee = boardfee;
	}

	public String getOpercode() {
		return this.opercode;
	}

	public void setOpercode(String opercode) {
		this.opercode = opercode;
	}

	public long getSysid() {
		return this.sysid;
	}

	public void setSysid(long sysid) {
		this.sysid = sysid;
	}

	public String getDevphyid() {
		return this.devphyid;
	}

	public void setDevphyid(String devphyid) {
		this.devphyid = devphyid;
	}

	public long getDevseqno() {
		return this.devseqno;
	}

	public void setDevseqno(long devseqno) {
		this.devseqno = devseqno;
	}

	public long getExttype() {
		return this.exttype;
	}

	public void setExttype(long exttype) {
		this.exttype = exttype;
	}

	public String getExtdata() {
		return this.extdata;
	}

	public void setExtdata(String extdata) {
		this.extdata = extdata;
	}

	public String getRevflag() {
		return this.revflag;
	}

	public void setRevflag(String revflag) {
		this.revflag = revflag;
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

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}