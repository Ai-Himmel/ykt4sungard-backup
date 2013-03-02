package com.kingstargroup.fdykt.form;

/**
 * AbstractTCard entity provides the base persistence definition of the TCard
 * entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCard implements java.io.Serializable {

	// Fields

	private Long cardno;
	private Long cardtype;
	private Long feetype;
	private String stuempno;
	private Long custid;
	private String showcardno;
	private String cardphyid;
	private String cardpwd;
	private String status;
	private String cardstatus;
	private String expiredate;
	private String lossdate;
	private String opendate;
	private String closedate;
	private String lastsaved;
	private String lossflag;
	private String lossefttime;
	private String frozedate;

	// Constructors

	/** default constructor */
	public AbstractTCard() {
	}

	/** minimal constructor */
	public AbstractTCard(Long cardno) {
		this.cardno = cardno;
	}

	/** full constructor */
	public AbstractTCard(Long cardno, Long cardtype, Long feetype,
			String stuempno, Long custid, String showcardno, String cardphyid,
			String cardpwd, String status, String cardstatus,
			String expiredate, String lossdate, String opendate,
			String closedate, String lastsaved, String lossflag,
			String lossefttime, String frozedate) {
		this.cardno = cardno;
		this.cardtype = cardtype;
		this.feetype = feetype;
		this.stuempno = stuempno;
		this.custid = custid;
		this.showcardno = showcardno;
		this.cardphyid = cardphyid;
		this.cardpwd = cardpwd;
		this.status = status;
		this.cardstatus = cardstatus;
		this.expiredate = expiredate;
		this.lossdate = lossdate;
		this.opendate = opendate;
		this.closedate = closedate;
		this.lastsaved = lastsaved;
		this.lossflag = lossflag;
		this.lossefttime = lossefttime;
		this.frozedate = frozedate;
	}

	// Property accessors

	public Long getCardno() {
		return this.cardno;
	}

	public void setCardno(Long cardno) {
		this.cardno = cardno;
	}

	public Long getCardtype() {
		return this.cardtype;
	}

	public void setCardtype(Long cardtype) {
		this.cardtype = cardtype;
	}

	public Long getFeetype() {
		return this.feetype;
	}

	public void setFeetype(Long feetype) {
		this.feetype = feetype;
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

	public String getShowcardno() {
		return this.showcardno;
	}

	public void setShowcardno(String showcardno) {
		this.showcardno = showcardno;
	}

	public String getCardphyid() {
		return this.cardphyid;
	}

	public void setCardphyid(String cardphyid) {
		this.cardphyid = cardphyid;
	}

	public String getCardpwd() {
		return this.cardpwd;
	}

	public void setCardpwd(String cardpwd) {
		this.cardpwd = cardpwd;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getCardstatus() {
		return this.cardstatus;
	}

	public void setCardstatus(String cardstatus) {
		this.cardstatus = cardstatus;
	}

	public String getExpiredate() {
		return this.expiredate;
	}

	public void setExpiredate(String expiredate) {
		this.expiredate = expiredate;
	}

	public String getLossdate() {
		return this.lossdate;
	}

	public void setLossdate(String lossdate) {
		this.lossdate = lossdate;
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

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

	public String getLossflag() {
		return this.lossflag;
	}

	public void setLossflag(String lossflag) {
		this.lossflag = lossflag;
	}

	public String getLossefttime() {
		return this.lossefttime;
	}

	public void setLossefttime(String lossefttime) {
		this.lossefttime = lossefttime;
	}

	public String getFrozedate() {
		return this.frozedate;
	}

	public void setFrozedate(String frozedate) {
		this.frozedate = frozedate;
	}

}