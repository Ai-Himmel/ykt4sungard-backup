package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTCard entity provides the base persistence definition of the TCard
 * entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCard implements java.io.Serializable {

	// Fields

	private long cardno;
	private String accno;
	private long cardtype;
	private long feetype;
	private long custid;
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
	private String cardverno;
	private String lastsaved;

	// Constructors

	/** default constructor */
	public AbstractTCard() {
	}

	/** minimal constructor */
	public AbstractTCard(long cardno, String status, String lossflag,
			String frozeflag, String badflag) {
		this.cardno = cardno;
		this.status = status;
		this.lossflag = lossflag;
		this.frozeflag = frozeflag;
		this.badflag = badflag;
	}

	/** full constructor */
	public AbstractTCard(long cardno, String accno, long cardtype,
			long feetype, long custid, String showcardno, String cardphyid,
			String cardpwd, String expiredate, String status, String lossflag,
			String lossdate, String lossefttime, String frozeflag,
			String frozedate, String badflag, String badtype, String baddate,
			String lockflag, String lockdate, String opendate,
			String closedate, String cardverno, String lastsaved) {
		this.cardno = cardno;
		this.accno = accno;
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
		this.cardverno = cardverno;
		this.lastsaved = lastsaved;
	}

	// Property accessors

	public long getCardno() {
		return this.cardno;
	}

	public void setCardno(long cardno) {
		this.cardno = cardno;
	}

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public long getCardtype() {
		return this.cardtype;
	}

	public void setCardtype(long cardtype) {
		this.cardtype = cardtype;
	}

	public long getFeetype() {
		return this.feetype;
	}

	public void setFeetype(long feetype) {
		this.feetype = feetype;
	}

	public long getCustid() {
		return this.custid;
	}

	public void setCustid(long custid) {
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

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

}