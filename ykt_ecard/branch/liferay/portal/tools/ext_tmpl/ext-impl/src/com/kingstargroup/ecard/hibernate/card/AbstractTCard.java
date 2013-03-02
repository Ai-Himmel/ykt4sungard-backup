package com.kingstargroup.ecard.hibernate.card;

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
	private Long custid;
	private String showcardno;
	private String cardphyid;
	private String cardpwd;
	private String expiredate;
	private String status;
	private String lossflag;
	private String lossdate;
	private String lossefttime;
	private String frozeflag;
	private String frozedate;
	private String badflag;
	private String badtype;
	private String baddate;
	private String lockflag;
	private String lockdate;
	private String opendate;
	private String closedate;
	private String lastsaved;

	// Constructors

	/** default constructor */
	public AbstractTCard() {
	}

	/** minimal constructor */
	public AbstractTCard(Long cardno, String status, String lossflag,
			String frozeflag, String badflag) {
		this.cardno = cardno;
		this.status = status;
		this.lossflag = lossflag;
		this.frozeflag = frozeflag;
		this.badflag = badflag;
	}

	/** full constructor */
	public AbstractTCard(Long cardno, Long cardtype, Long feetype, Long custid,
			String showcardno, String cardphyid, String cardpwd,
			String expiredate, String status, String lossflag, String lossdate,
			String lossefttime, String frozeflag, String frozedate,
			String badflag, String badtype, String baddate, String lockflag,
			String lockdate, String opendate, String closedate, String lastsaved) {
		this.cardno = cardno;
		this.cardtype = cardtype;
		this.feetype = feetype;
		this.custid = custid;
		this.showcardno = showcardno;
		this.cardphyid = cardphyid;
		this.cardpwd = cardpwd;
		this.expiredate = expiredate;
		this.status = status;
		this.lossflag = lossflag;
		this.lossdate = lossdate;
		this.lossefttime = lossefttime;
		this.frozeflag = frozeflag;
		this.frozedate = frozedate;
		this.badflag = badflag;
		this.badtype = badtype;
		this.baddate = baddate;
		this.lockflag = lockflag;
		this.lockdate = lockdate;
		this.opendate = opendate;
		this.closedate = closedate;
		this.lastsaved = lastsaved;
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

	public String getExpiredate() {
		return this.expiredate;
	}

	public void setExpiredate(String expiredate) {
		this.expiredate = expiredate;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getLossflag() {
		return this.lossflag;
	}

	public void setLossflag(String lossflag) {
		this.lossflag = lossflag;
	}

	public String getLossdate() {
		return this.lossdate;
	}

	public void setLossdate(String lossdate) {
		this.lossdate = lossdate;
	}

	public String getLossefttime() {
		return this.lossefttime;
	}

	public void setLossefttime(String lossefttime) {
		this.lossefttime = lossefttime;
	}

	public String getFrozeflag() {
		return this.frozeflag;
	}

	public void setFrozeflag(String frozeflag) {
		this.frozeflag = frozeflag;
	}

	public String getFrozedate() {
		return this.frozedate;
	}

	public void setFrozedate(String frozedate) {
		this.frozedate = frozedate;
	}

	public String getBadflag() {
		return this.badflag;
	}

	public void setBadflag(String badflag) {
		this.badflag = badflag;
	}

	public String getBadtype() {
		return this.badtype;
	}

	public void setBadtype(String badtype) {
		this.badtype = badtype;
	}

	public String getBaddate() {
		return this.baddate;
	}

	public void setBaddate(String baddate) {
		this.baddate = baddate;
	}

	public String getLockflag() {
		return this.lockflag;
	}

	public void setLockflag(String lockflag) {
		this.lockflag = lockflag;
	}

	public String getLockdate() {
		return this.lockdate;
	}

	public void setLockdate(String lockdate) {
		this.lockdate = lockdate;
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

}