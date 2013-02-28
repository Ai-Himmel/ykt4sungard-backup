package org.king.security.domain;

import java.math.BigDecimal;

/**
 * VTransdtl entity. @author MyEclipse Persistence Tools
 */

public class VTransdtl implements java.io.Serializable {

	// Fields

	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;
	private VTransdtlId id;
	private String acctime;
	private String transdate;
	private String transtime;
	private TRefno refno;
	private BigDecimal transcode;
	private BigDecimal custid;
	private String custname;
	private String stuempno;
	private Long showcardno;
	private BigDecimal cardno;
	private BigDecimal purseno;
	private Boolean transflag;
	private BigDecimal cardcnt;
	private Double cardbefbal;
	private Double cardaftbal;
	private Double amount;
	private Double addamt;
	private Double managefee;
	private BigDecimal paytype;
	private String voucherno;
	private String opercode;
	private BigDecimal sysid;
	private String devphyid;
	private BigDecimal devseqno;
	private BigDecimal exttype;
	private String extdata;
	private String coldate;
	private String coltime;
	private Boolean offlineflag;
	private String revflag;
	private String status;
	private BigDecimal errcode;
	private String remark;

	// Constructors

	/** default constructor */
	public VTransdtl() {
	}

	/** full constructor */
	public VTransdtl(VTransdtlId id) {
		this.id = id;
	}

	// Property accessors

	public VTransdtlId getId() {
		return this.id;
	}

	public void setId(VTransdtlId id) {
		this.id = id;
	}

	public String getAcctime() {
		return acctime;
	}

	public void setAcctime(String acctime) {
		this.acctime = acctime;
	}

	public String getTransdate() {
		return transdate;
	}

	public void setTransdate(String transdate) {
		this.transdate = transdate;
	}

	public String getTranstime() {
		return transtime;
	}

	public void setTranstime(String transtime) {
		this.transtime = transtime;
	}

	public TRefno getRefno() {
		return refno;
	}

	public void setRefno(TRefno refno) {
		this.refno = refno;
	}

	public BigDecimal getTranscode() {
		return transcode;
	}

	public void setTranscode(BigDecimal transcode) {
		this.transcode = transcode;
	}

	public BigDecimal getCustid() {
		return custid;
	}

	public void setCustid(BigDecimal custid) {
		this.custid = custid;
	}

	public String getCustname() {
		return custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
	}

	public String getStuempno() {
		return stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}

	public Long getShowcardno() {
		return showcardno;
	}

	public void setShowcardno(Long showcardno) {
		this.showcardno = showcardno;
	}

	public BigDecimal getCardno() {
		return cardno;
	}

	public void setCardno(BigDecimal cardno) {
		this.cardno = cardno;
	}

	public BigDecimal getPurseno() {
		return purseno;
	}

	public void setPurseno(BigDecimal purseno) {
		this.purseno = purseno;
	}

	public Boolean getTransflag() {
		return transflag;
	}

	public void setTransflag(Boolean transflag) {
		this.transflag = transflag;
	}

	public BigDecimal getCardcnt() {
		return cardcnt;
	}

	public void setCardcnt(BigDecimal cardcnt) {
		this.cardcnt = cardcnt;
	}

	public Double getCardbefbal() {
		return cardbefbal;
	}

	public void setCardbefbal(Double cardbefbal) {
		this.cardbefbal = cardbefbal;
	}

	public Double getCardaftbal() {
		return cardaftbal;
	}

	public void setCardaftbal(Double cardaftbal) {
		this.cardaftbal = cardaftbal;
	}

	public Double getAmount() {
		return amount;
	}

	public void setAmount(Double amount) {
		this.amount = amount;
	}

	public Double getAddamt() {
		return addamt;
	}

	public void setAddamt(Double addamt) {
		this.addamt = addamt;
	}

	public Double getManagefee() {
		return managefee;
	}

	public void setManagefee(Double managefee) {
		this.managefee = managefee;
	}

	public BigDecimal getPaytype() {
		return paytype;
	}

	public void setPaytype(BigDecimal paytype) {
		this.paytype = paytype;
	}

	public String getVoucherno() {
		return voucherno;
	}

	public void setVoucherno(String voucherno) {
		this.voucherno = voucherno;
	}

	public String getOpercode() {
		return opercode;
	}

	public void setOpercode(String opercode) {
		this.opercode = opercode;
	}

	public BigDecimal getSysid() {
		return sysid;
	}

	public void setSysid(BigDecimal sysid) {
		this.sysid = sysid;
	}

	public String getDevphyid() {
		return devphyid;
	}

	public void setDevphyid(String devphyid) {
		this.devphyid = devphyid;
	}

	public BigDecimal getDevseqno() {
		return devseqno;
	}

	public void setDevseqno(BigDecimal devseqno) {
		this.devseqno = devseqno;
	}

	public BigDecimal getExttype() {
		return exttype;
	}

	public void setExttype(BigDecimal exttype) {
		this.exttype = exttype;
	}

	public String getExtdata() {
		return extdata;
	}

	public void setExtdata(String extdata) {
		this.extdata = extdata;
	}

	public String getColdate() {
		return coldate;
	}

	public void setColdate(String coldate) {
		this.coldate = coldate;
	}

	public String getColtime() {
		return coltime;
	}

	public void setColtime(String coltime) {
		this.coltime = coltime;
	}

	public Boolean getOfflineflag() {
		return offlineflag;
	}

	public void setOfflineflag(Boolean offlineflag) {
		this.offlineflag = offlineflag;
	}

	public String getRevflag() {
		return revflag;
	}

	public void setRevflag(String revflag) {
		this.revflag = revflag;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public BigDecimal getErrcode() {
		return errcode;
	}

	public void setErrcode(BigDecimal errcode) {
		this.errcode = errcode;
	}

	public String getRemark() {
		return remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}
	
}