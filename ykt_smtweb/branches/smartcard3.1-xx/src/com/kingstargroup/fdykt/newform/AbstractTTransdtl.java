package com.kingstargroup.fdykt.newform;

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
	private Long transcode;
	private Long paytype;
	private String voucherno;
	private Long custid;
	private String custname;
	private Long cardno;
	private Long purseno;
	private Long cardcnt;
	private Double cardbefbal;
	private Double cardaftbal;
	private Double amount;
	private Double managefee;
	private String opercode;
	private String chkoper;
	private String chkdate;
	private Long sysid;
	private String devphyid;
	private Long devseqno;
	private Long exttype;
	private String extdata;
	private String revflag;
	private String status;
	private Long errcode;
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
			String transtime, String coldate, String coltime, Long transcode,
			Long paytype, String voucherno, Long custid, String custname,
			Long cardno, Long purseno, Long cardcnt, Double cardbefbal,
			Double cardaftbal, Double amount, Double managefee,
			String opercode, String chkoper, String chkdate, Long sysid,
			String devphyid, Long devseqno, Long exttype, String extdata,
			String revflag, String status, Long errcode, String remark) {
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
		this.managefee = managefee;
		this.opercode = opercode;
		this.chkoper = chkoper;
		this.chkdate = chkdate;
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

	public Long getTranscode() {
		return this.transcode;
	}

	public void setTranscode(Long transcode) {
		this.transcode = transcode;
	}

	public Long getPaytype() {
		return this.paytype;
	}

	public void setPaytype(Long paytype) {
		this.paytype = paytype;
	}

	public String getVoucherno() {
		return this.voucherno;
	}

	public void setVoucherno(String voucherno) {
		this.voucherno = voucherno;
	}

	public Long getCustid() {
		return this.custid;
	}

	public void setCustid(Long custid) {
		this.custid = custid;
	}

	public String getCustname() {
		return this.custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
	}

	public Long getCardno() {
		return this.cardno;
	}

	public void setCardno(Long cardno) {
		this.cardno = cardno;
	}

	public Long getPurseno() {
		return this.purseno;
	}

	public void setPurseno(Long purseno) {
		this.purseno = purseno;
	}

	public Long getCardcnt() {
		return this.cardcnt;
	}

	public void setCardcnt(Long cardcnt) {
		this.cardcnt = cardcnt;
	}

	public Double getCardbefbal() {
		return this.cardbefbal;
	}

	public void setCardbefbal(Double cardbefbal) {
		this.cardbefbal = cardbefbal;
	}

	public Double getCardaftbal() {
		return this.cardaftbal;
	}

	public void setCardaftbal(Double cardaftbal) {
		this.cardaftbal = cardaftbal;
	}

	public Double getAmount() {
		return this.amount;
	}

	public void setAmount(Double amount) {
		this.amount = amount;
	}

	public Double getManagefee() {
		return this.managefee;
	}

	public void setManagefee(Double managefee) {
		this.managefee = managefee;
	}

	public String getOpercode() {
		return this.opercode;
	}

	public void setOpercode(String opercode) {
		this.opercode = opercode;
	}

	public String getChkoper() {
		return this.chkoper;
	}

	public void setChkoper(String chkoper) {
		this.chkoper = chkoper;
	}

	public String getChkdate() {
		return this.chkdate;
	}

	public void setChkdate(String chkdate) {
		this.chkdate = chkdate;
	}

	public Long getSysid() {
		return this.sysid;
	}

	public void setSysid(Long sysid) {
		this.sysid = sysid;
	}

	public String getDevphyid() {
		return this.devphyid;
	}

	public void setDevphyid(String devphyid) {
		this.devphyid = devphyid;
	}

	public Long getDevseqno() {
		return this.devseqno;
	}

	public void setDevseqno(Long devseqno) {
		this.devseqno = devseqno;
	}

	public Long getExttype() {
		return this.exttype;
	}

	public void setExttype(Long exttype) {
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

	public Long getErrcode() {
		return this.errcode;
	}

	public void setErrcode(Long errcode) {
		this.errcode = errcode;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}