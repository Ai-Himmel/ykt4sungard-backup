package com.kingstargroup.fdykt.newform;

/**
 * AbstractVTrandtlId entity provides the base persistence definition of the
 * VTrandtlId entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractVTrandtlId implements java.io.Serializable {

	// Fields

	private String accdate;
	private String acctime;
	private Long termid;
	private Long termseqno;
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
	public AbstractVTrandtlId() {
	}

	/** minimal constructor */
	public AbstractVTrandtlId(String accdate, Long termid, Long termseqno) {
		this.accdate = accdate;
		this.termid = termid;
		this.termseqno = termseqno;
	}

	/** full constructor */
	public AbstractVTrandtlId(String accdate, String acctime, Long termid,
			Long termseqno, String transdate, String transtime, String coldate,
			String coltime, Long transcode, Long paytype, String voucherno,
			Long custid, String custname, Long cardno, Long purseno,
			Long cardcnt, Double cardbefbal, Double cardaftbal, Double amount,
			Double managefee, String opercode, Long sysid, String devphyid,
			Long devseqno, Long exttype, String extdata, String revflag,
			String status, Long errcode, String remark) {
		this.accdate = accdate;
		this.acctime = acctime;
		this.termid = termid;
		this.termseqno = termseqno;
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

	public boolean equals(Object other) {
		if ((this == other))
			return true;
		if ((other == null))
			return false;
		if (!(other instanceof AbstractVTrandtlId))
			return false;
		AbstractVTrandtlId castOther = (AbstractVTrandtlId) other;

		return ((this.getAccdate() == castOther.getAccdate()) || (this
				.getAccdate() != null
				&& castOther.getAccdate() != null && this.getAccdate().equals(
				castOther.getAccdate())))
				&& ((this.getAcctime() == castOther.getAcctime()) || (this
						.getAcctime() != null
						&& castOther.getAcctime() != null && this.getAcctime()
						.equals(castOther.getAcctime())))
				&& ((this.getTermid() == castOther.getTermid()) || (this
						.getTermid() != null
						&& castOther.getTermid() != null && this.getTermid()
						.equals(castOther.getTermid())))
				&& ((this.getTermseqno() == castOther.getTermseqno()) || (this
						.getTermseqno() != null
						&& castOther.getTermseqno() != null && this
						.getTermseqno().equals(castOther.getTermseqno())))
				&& ((this.getTransdate() == castOther.getTransdate()) || (this
						.getTransdate() != null
						&& castOther.getTransdate() != null && this
						.getTransdate().equals(castOther.getTransdate())))
				&& ((this.getTranstime() == castOther.getTranstime()) || (this
						.getTranstime() != null
						&& castOther.getTranstime() != null && this
						.getTranstime().equals(castOther.getTranstime())))
				&& ((this.getColdate() == castOther.getColdate()) || (this
						.getColdate() != null
						&& castOther.getColdate() != null && this.getColdate()
						.equals(castOther.getColdate())))
				&& ((this.getColtime() == castOther.getColtime()) || (this
						.getColtime() != null
						&& castOther.getColtime() != null && this.getColtime()
						.equals(castOther.getColtime())))
				&& ((this.getTranscode() == castOther.getTranscode()) || (this
						.getTranscode() != null
						&& castOther.getTranscode() != null && this
						.getTranscode().equals(castOther.getTranscode())))
				&& ((this.getPaytype() == castOther.getPaytype()) || (this
						.getPaytype() != null
						&& castOther.getPaytype() != null && this.getPaytype()
						.equals(castOther.getPaytype())))
				&& ((this.getVoucherno() == castOther.getVoucherno()) || (this
						.getVoucherno() != null
						&& castOther.getVoucherno() != null && this
						.getVoucherno().equals(castOther.getVoucherno())))
				&& ((this.getCustid() == castOther.getCustid()) || (this
						.getCustid() != null
						&& castOther.getCustid() != null && this.getCustid()
						.equals(castOther.getCustid())))
				&& ((this.getCustname() == castOther.getCustname()) || (this
						.getCustname() != null
						&& castOther.getCustname() != null && this
						.getCustname().equals(castOther.getCustname())))
				&& ((this.getCardno() == castOther.getCardno()) || (this
						.getCardno() != null
						&& castOther.getCardno() != null && this.getCardno()
						.equals(castOther.getCardno())))
				&& ((this.getPurseno() == castOther.getPurseno()) || (this
						.getPurseno() != null
						&& castOther.getPurseno() != null && this.getPurseno()
						.equals(castOther.getPurseno())))
				&& ((this.getCardcnt() == castOther.getCardcnt()) || (this
						.getCardcnt() != null
						&& castOther.getCardcnt() != null && this.getCardcnt()
						.equals(castOther.getCardcnt())))
				&& ((this.getCardbefbal() == castOther.getCardbefbal()) || (this
						.getCardbefbal() != null
						&& castOther.getCardbefbal() != null && this
						.getCardbefbal().equals(castOther.getCardbefbal())))
				&& ((this.getCardaftbal() == castOther.getCardaftbal()) || (this
						.getCardaftbal() != null
						&& castOther.getCardaftbal() != null && this
						.getCardaftbal().equals(castOther.getCardaftbal())))
				&& ((this.getAmount() == castOther.getAmount()) || (this
						.getAmount() != null
						&& castOther.getAmount() != null && this.getAmount()
						.equals(castOther.getAmount())))
				&& ((this.getManagefee() == castOther.getManagefee()) || (this
						.getManagefee() != null
						&& castOther.getManagefee() != null && this
						.getManagefee().equals(castOther.getManagefee())))
				&& ((this.getOpercode() == castOther.getOpercode()) || (this
						.getOpercode() != null
						&& castOther.getOpercode() != null && this
						.getOpercode().equals(castOther.getOpercode())))
				&& ((this.getSysid() == castOther.getSysid()) || (this
						.getSysid() != null
						&& castOther.getSysid() != null && this.getSysid()
						.equals(castOther.getSysid())))
				&& ((this.getDevphyid() == castOther.getDevphyid()) || (this
						.getDevphyid() != null
						&& castOther.getDevphyid() != null && this
						.getDevphyid().equals(castOther.getDevphyid())))
				&& ((this.getDevseqno() == castOther.getDevseqno()) || (this
						.getDevseqno() != null
						&& castOther.getDevseqno() != null && this
						.getDevseqno().equals(castOther.getDevseqno())))
				&& ((this.getExttype() == castOther.getExttype()) || (this
						.getExttype() != null
						&& castOther.getExttype() != null && this.getExttype()
						.equals(castOther.getExttype())))
				&& ((this.getExtdata() == castOther.getExtdata()) || (this
						.getExtdata() != null
						&& castOther.getExtdata() != null && this.getExtdata()
						.equals(castOther.getExtdata())))
				&& ((this.getRevflag() == castOther.getRevflag()) || (this
						.getRevflag() != null
						&& castOther.getRevflag() != null && this.getRevflag()
						.equals(castOther.getRevflag())))
				&& ((this.getStatus() == castOther.getStatus()) || (this
						.getStatus() != null
						&& castOther.getStatus() != null && this.getStatus()
						.equals(castOther.getStatus())))
				&& ((this.getErrcode() == castOther.getErrcode()) || (this
						.getErrcode() != null
						&& castOther.getErrcode() != null && this.getErrcode()
						.equals(castOther.getErrcode())))
				&& ((this.getRemark() == castOther.getRemark()) || (this
						.getRemark() != null
						&& castOther.getRemark() != null && this.getRemark()
						.equals(castOther.getRemark())));
	}

	public int hashCode() {
		int result = 17;

		result = 37 * result
				+ (getAccdate() == null ? 0 : this.getAccdate().hashCode());
		result = 37 * result
				+ (getAcctime() == null ? 0 : this.getAcctime().hashCode());
		result = 37 * result
				+ (getTermid() == null ? 0 : this.getTermid().hashCode());
		result = 37 * result
				+ (getTermseqno() == null ? 0 : this.getTermseqno().hashCode());
		result = 37 * result
				+ (getTransdate() == null ? 0 : this.getTransdate().hashCode());
		result = 37 * result
				+ (getTranstime() == null ? 0 : this.getTranstime().hashCode());
		result = 37 * result
				+ (getColdate() == null ? 0 : this.getColdate().hashCode());
		result = 37 * result
				+ (getColtime() == null ? 0 : this.getColtime().hashCode());
		result = 37 * result
				+ (getTranscode() == null ? 0 : this.getTranscode().hashCode());
		result = 37 * result
				+ (getPaytype() == null ? 0 : this.getPaytype().hashCode());
		result = 37 * result
				+ (getVoucherno() == null ? 0 : this.getVoucherno().hashCode());
		result = 37 * result
				+ (getCustid() == null ? 0 : this.getCustid().hashCode());
		result = 37 * result
				+ (getCustname() == null ? 0 : this.getCustname().hashCode());
		result = 37 * result
				+ (getCardno() == null ? 0 : this.getCardno().hashCode());
		result = 37 * result
				+ (getPurseno() == null ? 0 : this.getPurseno().hashCode());
		result = 37 * result
				+ (getCardcnt() == null ? 0 : this.getCardcnt().hashCode());
		result = 37
				* result
				+ (getCardbefbal() == null ? 0 : this.getCardbefbal()
						.hashCode());
		result = 37
				* result
				+ (getCardaftbal() == null ? 0 : this.getCardaftbal()
						.hashCode());
		result = 37 * result
				+ (getAmount() == null ? 0 : this.getAmount().hashCode());
		result = 37 * result
				+ (getManagefee() == null ? 0 : this.getManagefee().hashCode());
		result = 37 * result
				+ (getOpercode() == null ? 0 : this.getOpercode().hashCode());
		result = 37 * result
				+ (getSysid() == null ? 0 : this.getSysid().hashCode());
		result = 37 * result
				+ (getDevphyid() == null ? 0 : this.getDevphyid().hashCode());
		result = 37 * result
				+ (getDevseqno() == null ? 0 : this.getDevseqno().hashCode());
		result = 37 * result
				+ (getExttype() == null ? 0 : this.getExttype().hashCode());
		result = 37 * result
				+ (getExtdata() == null ? 0 : this.getExtdata().hashCode());
		result = 37 * result
				+ (getRevflag() == null ? 0 : this.getRevflag().hashCode());
		result = 37 * result
				+ (getStatus() == null ? 0 : this.getStatus().hashCode());
		result = 37 * result
				+ (getErrcode() == null ? 0 : this.getErrcode().hashCode());
		result = 37 * result
				+ (getRemark() == null ? 0 : this.getRemark().hashCode());
		return result;
	}

}