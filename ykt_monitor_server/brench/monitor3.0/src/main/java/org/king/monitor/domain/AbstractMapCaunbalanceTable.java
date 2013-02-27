package org.king.monitor.domain;

/**
 * AbstractMapCaunbalanceTable entity provides the base persistence definition
 * of the MapCaunbalanceTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapCaunbalanceTable implements
		java.io.Serializable {

	// Fields

	private MapCaunbalanceTableId id;
	private String accname;
	private String subjno;
	private String accpwd;
	private long custid;
	private long cardno;
	private long purseno;
	private double daycostmaxamt;
	private double cardmaxbal;
	private String stoppayflag;
	private String status;
	private double ydaybal;
	private double ydayavailbal;
	private double ydayfrozebal;
	private double balance;
	private double availbal;
	private double frozebal;
	private double subsidybal;
	private double foregift;
	private long lastcardcnt;
	private double lastcardbal;
	private double daycostamt;
	private String lasttransdate;
	private String lastaccdate;
	private long lastsubsidyno;
	private String opendate;
	private String closedate;

	// Constructors

	/** default constructor */
	public AbstractMapCaunbalanceTable() {
	}

	/** minimal constructor */
	public AbstractMapCaunbalanceTable(MapCaunbalanceTableId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractMapCaunbalanceTable(MapCaunbalanceTableId id,
			String accname, String subjno, String accpwd, long custid,
			long cardno, long purseno, double daycostmaxamt, double cardmaxbal,
			String stoppayflag, String status, double ydaybal,
			double ydayavailbal, double ydayfrozebal, double balance,
			double availbal, double frozebal, double subsidybal,
			double foregift, long lastcardcnt, double lastcardbal,
			double daycostamt, String lasttransdate, String lastaccdate,
			long lastsubsidyno, String opendate, String closedate) {
		this.id = id;
		this.accname = accname;
		this.subjno = subjno;
		this.accpwd = accpwd;
		this.custid = custid;
		this.cardno = cardno;
		this.purseno = purseno;
		this.daycostmaxamt = daycostmaxamt;
		this.cardmaxbal = cardmaxbal;
		this.stoppayflag = stoppayflag;
		this.status = status;
		this.ydaybal = ydaybal;
		this.ydayavailbal = ydayavailbal;
		this.ydayfrozebal = ydayfrozebal;
		this.balance = balance;
		this.availbal = availbal;
		this.frozebal = frozebal;
		this.subsidybal = subsidybal;
		this.foregift = foregift;
		this.lastcardcnt = lastcardcnt;
		this.lastcardbal = lastcardbal;
		this.daycostamt = daycostamt;
		this.lasttransdate = lasttransdate;
		this.lastaccdate = lastaccdate;
		this.lastsubsidyno = lastsubsidyno;
		this.opendate = opendate;
		this.closedate = closedate;
	}

	// Property accessors

	public MapCaunbalanceTableId getId() {
		return this.id;
	}

	public void setId(MapCaunbalanceTableId id) {
		this.id = id;
	}

	public String getAccname() {
		return this.accname;
	}

	public void setAccname(String accname) {
		this.accname = accname;
	}

	public String getSubjno() {
		return this.subjno;
	}

	public void setSubjno(String subjno) {
		this.subjno = subjno;
	}

	public String getAccpwd() {
		return this.accpwd;
	}

	public void setAccpwd(String accpwd) {
		this.accpwd = accpwd;
	}

	public long getCustid() {
		return this.custid;
	}

	public void setCustid(long custid) {
		this.custid = custid;
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

	public double getDaycostmaxamt() {
		return this.daycostmaxamt;
	}

	public void setDaycostmaxamt(double daycostmaxamt) {
		this.daycostmaxamt = daycostmaxamt;
	}

	public double getCardmaxbal() {
		return this.cardmaxbal;
	}

	public void setCardmaxbal(double cardmaxbal) {
		this.cardmaxbal = cardmaxbal;
	}

	public String getStoppayflag() {
		return this.stoppayflag;
	}

	public void setStoppayflag(String stoppayflag) {
		this.stoppayflag = stoppayflag;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public double getYdaybal() {
		return this.ydaybal;
	}

	public void setYdaybal(double ydaybal) {
		this.ydaybal = ydaybal;
	}

	public double getYdayavailbal() {
		return this.ydayavailbal;
	}

	public void setYdayavailbal(double ydayavailbal) {
		this.ydayavailbal = ydayavailbal;
	}

	public double getYdayfrozebal() {
		return this.ydayfrozebal;
	}

	public void setYdayfrozebal(double ydayfrozebal) {
		this.ydayfrozebal = ydayfrozebal;
	}

	public double getBalance() {
		return this.balance;
	}

	public void setBalance(double balance) {
		this.balance = balance;
	}

	public double getAvailbal() {
		return this.availbal;
	}

	public void setAvailbal(double availbal) {
		this.availbal = availbal;
	}

	public double getFrozebal() {
		return this.frozebal;
	}

	public void setFrozebal(double frozebal) {
		this.frozebal = frozebal;
	}

	public double getSubsidybal() {
		return this.subsidybal;
	}

	public void setSubsidybal(double subsidybal) {
		this.subsidybal = subsidybal;
	}

	public double getForegift() {
		return this.foregift;
	}

	public void setForegift(double foregift) {
		this.foregift = foregift;
	}

	public long getLastcardcnt() {
		return this.lastcardcnt;
	}

	public void setLastcardcnt(long lastcardcnt) {
		this.lastcardcnt = lastcardcnt;
	}

	public double getLastcardbal() {
		return this.lastcardbal;
	}

	public void setLastcardbal(double lastcardbal) {
		this.lastcardbal = lastcardbal;
	}

	public double getDaycostamt() {
		return this.daycostamt;
	}

	public void setDaycostamt(double daycostamt) {
		this.daycostamt = daycostamt;
	}

	public String getLasttransdate() {
		return this.lasttransdate;
	}

	public void setLasttransdate(String lasttransdate) {
		this.lasttransdate = lasttransdate;
	}

	public String getLastaccdate() {
		return this.lastaccdate;
	}

	public void setLastaccdate(String lastaccdate) {
		this.lastaccdate = lastaccdate;
	}


	public long getLastsubsidyno() {
		return lastsubsidyno;
	}

	public void setLastsubsidyno(long lastsubsidyno) {
		this.lastsubsidyno = lastsubsidyno;
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


}