package com.kingstargroup.fdykt.newform;

/**
 * AbstractTPosdtl entity provides the base persistence definition of the
 * TPosdtl entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTPosdtl implements java.io.Serializable {

	// Fields

	private TPosdtlId id;
	private String transtime;
	private Long cardno;
	private Long purseno;
	private Long cardcnt;
	private Double cardbefbal;
	private Double amount;
	private Double cardaftbal;
	private Double managefee;
	private Long transmark;
	private Long transcode;
	private Long shopid;
	private Long subsidyno;
	private String batchno;
	private Long sysid;
	private String coldate;
	private String coltime;
	private String accdate;
	private String acctime;
	private Long termid;
	private Long termseqno;
	private String status;
	private Long errcode;
	private String errmsg;
	private String delflag;

	// Constructors

	/** default constructor */
	public AbstractTPosdtl() {
	}

	/** minimal constructor */
	public AbstractTPosdtl(TPosdtlId id, String status) {
		this.id = id;
		this.status = status;
	}

	/** full constructor */
	public AbstractTPosdtl(TPosdtlId id, String transtime, Long cardno,
			Long purseno, Long cardcnt, Double cardbefbal, Double amount,
			Double cardaftbal, Double managefee, Long transmark,
			Long transcode, Long shopid, Long subsidyno, String batchno,
			Long sysid, String coldate, String coltime, String accdate,
			String acctime, Long termid, Long termseqno, String status,
			Long errcode, String errmsg, String delflag) {
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
		this.termid = termid;
		this.termseqno = termseqno;
		this.status = status;
		this.errcode = errcode;
		this.errmsg = errmsg;
		this.delflag = delflag;
	}

	// Property accessors

	public TPosdtlId getId() {
		return this.id;
	}

	public void setId(TPosdtlId id) {
		this.id = id;
	}

	public String getTranstime() {
		return this.transtime;
	}

	public void setTranstime(String transtime) {
		this.transtime = transtime;
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

	public Double getAmount() {
		return this.amount;
	}

	public void setAmount(Double amount) {
		this.amount = amount;
	}

	public Double getCardaftbal() {
		return this.cardaftbal;
	}

	public void setCardaftbal(Double cardaftbal) {
		this.cardaftbal = cardaftbal;
	}

	public Double getManagefee() {
		return this.managefee;
	}

	public void setManagefee(Double managefee) {
		this.managefee = managefee;
	}

	public Long getTransmark() {
		return this.transmark;
	}

	public void setTransmark(Long transmark) {
		this.transmark = transmark;
	}

	public Long getTranscode() {
		return this.transcode;
	}

	public void setTranscode(Long transcode) {
		this.transcode = transcode;
	}

	public Long getShopid() {
		return this.shopid;
	}

	public void setShopid(Long shopid) {
		this.shopid = shopid;
	}

	public Long getSubsidyno() {
		return this.subsidyno;
	}

	public void setSubsidyno(Long subsidyno) {
		this.subsidyno = subsidyno;
	}

	public String getBatchno() {
		return this.batchno;
	}

	public void setBatchno(String batchno) {
		this.batchno = batchno;
	}

	public Long getSysid() {
		return this.sysid;
	}

	public void setSysid(Long sysid) {
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

	public Long getTermid() {
		return this.termid;
	}

	public void setTermid(Long termid) {
		this.termid = termid;
	}

	public Long getTermseqno() {
		return this.termseqno;
	}

	public void setTermseqno(Long termseqno) {
		this.termseqno = termseqno;
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

}