package com.kingstargroup.ecard.hibernate.losecard;
// default package

/**
 * AbstractTLosscardinfo entity provides the base persistence definition of the
 * TLosscardinfo entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTLosscardinfo implements java.io.Serializable {

	// Fields

	private TLosscardinfoId id;
	private String cardphyid;
	private String regtime;
	private long status;
	private String enddate;
	private String getcardplace;
	private String tel;
	private String addr;
	private long idtype;
	private String idno;
	private String getdate;
	private String gettime;
	private String remark;

	// Constructors

	/** default constructor */
	public AbstractTLosscardinfo() {
	}

	/** minimal constructor */
	public AbstractTLosscardinfo(TLosscardinfoId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTLosscardinfo(TLosscardinfoId id, String cardphyid,
			String regtime, long status, String enddate, String getcardplace,
			String tel, String addr, long idtype, String idno, String getdate,
			String gettime, String remark) {
		this.id = id;
		this.cardphyid = cardphyid;
		this.regtime = regtime;
		this.status = status;
		this.enddate = enddate;
		this.getcardplace = getcardplace;
		this.tel = tel;
		this.addr = addr;
		this.idtype = idtype;
		this.idno = idno;
		this.getdate = getdate;
		this.gettime = gettime;
		this.remark = remark;
	}

	// Property accessors

	public TLosscardinfoId getId() {
		return this.id;
	}

	public void setId(TLosscardinfoId id) {
		this.id = id;
	}

	public String getCardphyid() {
		return this.cardphyid;
	}

	public void setCardphyid(String cardphyid) {
		this.cardphyid = cardphyid;
	}

	public String getRegtime() {
		return this.regtime;
	}

	public void setRegtime(String regtime) {
		this.regtime = regtime;
	}

	public long getStatus() {
		return this.status;
	}

	public void setStatus(long status) {
		this.status = status;
	}

	public String getEnddate() {
		return this.enddate;
	}

	public void setEnddate(String enddate) {
		this.enddate = enddate;
	}

	public String getGetcardplace() {
		return this.getcardplace;
	}

	public void setGetcardplace(String getcardplace) {
		this.getcardplace = getcardplace;
	}

	public String getTel() {
		return this.tel;
	}

	public void setTel(String tel) {
		this.tel = tel;
	}

	public String getAddr() {
		return this.addr;
	}

	public void setAddr(String addr) {
		this.addr = addr;
	}

	public long getIdtype() {
		return this.idtype;
	}

	public void setIdtype(long idtype) {
		this.idtype = idtype;
	}

	public String getIdno() {
		return this.idno;
	}

	public void setIdno(String idno) {
		this.idno = idno;
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

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

}