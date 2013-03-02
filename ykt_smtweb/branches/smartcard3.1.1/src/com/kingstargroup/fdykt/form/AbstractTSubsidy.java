package com.kingstargroup.fdykt.form;

/**
 * AbstractTSubsidy entity provides the base persistence definition of the
 * TSubsidy entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTSubsidy implements java.io.Serializable {

	// Fields

	private TSubsidyId id;
	private String stuempno;
	private Long custid;
	private Long subsidyno;
	private Long cardno;
	private String summary;
	private String brokername;
	private String brokeridno;
	private Long paytype;
	private String voucherno;
	private Double amount;
	private String subsidytype;
	private String impdate;
	private String imptime;
	private String putdate;
	private String puttime;
	private String getdate;
	private String gettime;
	private String status;
	private String errmsg;
	private String opercode;

	// Constructors

	/** default constructor */
	public AbstractTSubsidy() {
	}

	/** minimal constructor */
	public AbstractTSubsidy(TSubsidyId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTSubsidy(TSubsidyId id, String stuempno, Long custid,
			Long subsidyno, Long cardno, String summary, String brokername,
			String brokeridno, Long paytype, String voucherno, Double amount,
			String subsidytype, String impdate, String imptime, String putdate,
			String puttime, String getdate, String gettime, String status,
			String errmsg, String opercode) {
		this.id = id;
		this.stuempno = stuempno;
		this.custid = custid;
		this.subsidyno = subsidyno;
		this.cardno = cardno;
		this.summary = summary;
		this.brokername = brokername;
		this.brokeridno = brokeridno;
		this.paytype = paytype;
		this.voucherno = voucherno;
		this.amount = amount;
		this.subsidytype = subsidytype;
		this.impdate = impdate;
		this.imptime = imptime;
		this.putdate = putdate;
		this.puttime = puttime;
		this.getdate = getdate;
		this.gettime = gettime;
		this.status = status;
		this.errmsg = errmsg;
		this.opercode = opercode;
	}

	// Property accessors

	public TSubsidyId getId() {
		return this.id;
	}

	public void setId(TSubsidyId id) {
		this.id = id;
	}

	public String getStuempno() {
		return this.stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}

	public Long getCustid() {
		return this.custid;
	}

	public void setCustid(Long custid) {
		this.custid = custid;
	}

	public Long getSubsidyno() {
		return this.subsidyno;
	}

	public void setSubsidyno(Long subsidyno) {
		this.subsidyno = subsidyno;
	}

	public Long getCardno() {
		return this.cardno;
	}

	public void setCardno(Long cardno) {
		this.cardno = cardno;
	}

	public String getSummary() {
		return this.summary;
	}

	public void setSummary(String summary) {
		this.summary = summary;
	}

	public String getBrokername() {
		return this.brokername;
	}

	public void setBrokername(String brokername) {
		this.brokername = brokername;
	}

	public String getBrokeridno() {
		return this.brokeridno;
	}

	public void setBrokeridno(String brokeridno) {
		this.brokeridno = brokeridno;
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

	public Double getAmount() {
		return this.amount;
	}

	public void setAmount(Double amount) {
		this.amount = amount;
	}

	public String getSubsidytype() {
		return this.subsidytype;
	}

	public void setSubsidytype(String subsidytype) {
		this.subsidytype = subsidytype;
	}

	public String getImpdate() {
		return this.impdate;
	}

	public void setImpdate(String impdate) {
		this.impdate = impdate;
	}

	public String getImptime() {
		return this.imptime;
	}

	public void setImptime(String imptime) {
		this.imptime = imptime;
	}

	public String getPutdate() {
		return this.putdate;
	}

	public void setPutdate(String putdate) {
		this.putdate = putdate;
	}

	public String getPuttime() {
		return this.puttime;
	}

	public void setPuttime(String puttime) {
		this.puttime = puttime;
	}

	public String getGetdate() {
		return this.getdate;
	}

	public void setGetdate(String getdate) {
		this.getdate = getdate;
	}

	public String getGettime() {
		return this.gettime;
	}

	public void setGettime(String gettime) {
		this.gettime = gettime;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getErrmsg() {
		return this.errmsg;
	}

	public void setErrmsg(String errmsg) {
		this.errmsg = errmsg;
	}

	public String getOpercode() {
		return this.opercode;
	}

	public void setOpercode(String opercode) {
		this.opercode = opercode;
	}

}