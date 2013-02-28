package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TShop entity. @author MyEclipse Persistence Tools
 */

public class TShop implements java.io.Serializable {

	// Fields

	private String shopid;
	private String fshopid;
	private String areacode;
	private String deptcode;
	private String shopname;
	private boolean shoptype;
	private String accflag;
	private String status;
	private String accno;
	private String contactman;
	private String idtype;
	private String idno;
	private String tel;
	private String mobile;
	private String email;
	private String addr;
	private String zipcode;
	private String boardfeeflag;
	private String rakeofftype;
	private double rakeoffrate;
	private double depositagio;
	private BigDecimal depositcnt;
	private double depositamt;
	private double discountamt;
	private String bankcode;
	private String bankaccno;
	private String bankaccname;
	private String opendate;
	private String closedate;
	private String useflag;

	// Constructors

	/** default constructor */
	public TShop() {
	}

	/** full constructor */
	public TShop(String fshopid, String areacode, String deptcode,
			String shopname, boolean shoptype, String accflag, String status,
			String accno, String contactman, String idtype, String idno,
			String tel, String mobile, String email, String addr,
			String zipcode, String boardfeeflag, String rakeofftype,
			double rakeoffrate, double depositagio, BigDecimal depositcnt,
			double depositamt, double discountamt, String bankcode,
			String bankaccno, String bankaccname, String opendate,
			String closedate, String useflag) {
		this.fshopid = fshopid;
		this.areacode = areacode;
		this.deptcode = deptcode;
		this.shopname = shopname;
		this.shoptype = shoptype;
		this.accflag = accflag;
		this.status = status;
		this.accno = accno;
		this.contactman = contactman;
		this.idtype = idtype;
		this.idno = idno;
		this.tel = tel;
		this.mobile = mobile;
		this.email = email;
		this.addr = addr;
		this.zipcode = zipcode;
		this.boardfeeflag = boardfeeflag;
		this.rakeofftype = rakeofftype;
		this.rakeoffrate = rakeoffrate;
		this.depositagio = depositagio;
		this.depositcnt = depositcnt;
		this.depositamt = depositamt;
		this.discountamt = discountamt;
		this.bankcode = bankcode;
		this.bankaccno = bankaccno;
		this.bankaccname = bankaccname;
		this.opendate = opendate;
		this.closedate = closedate;
		this.useflag = useflag;
	}

	// Property accessors

	public String getShopid() {
		return this.shopid;
	}

	public void setShopid(String shopid) {
		this.shopid = shopid;
	}

	public String getFshopid() {
		return this.fshopid;
	}

	public void setFshopid(String fshopid) {
		this.fshopid = fshopid;
	}

	public String getAreacode() {
		return this.areacode;
	}

	public void setAreacode(String areacode) {
		this.areacode = areacode;
	}

	public String getDeptcode() {
		return this.deptcode;
	}

	public void setDeptcode(String deptcode) {
		this.deptcode = deptcode;
	}

	public String getShopname() {
		return this.shopname;
	}

	public void setShopname(String shopname) {
		this.shopname = shopname;
	}

	public boolean getShoptype() {
		return this.shoptype;
	}

	public void setShoptype(boolean shoptype) {
		this.shoptype = shoptype;
	}

	public String getAccflag() {
		return this.accflag;
	}

	public void setAccflag(String accflag) {
		this.accflag = accflag;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public String getContactman() {
		return this.contactman;
	}

	public void setContactman(String contactman) {
		this.contactman = contactman;
	}

	public String getIdtype() {
		return this.idtype;
	}

	public void setIdtype(String idtype) {
		this.idtype = idtype;
	}

	public String getIdno() {
		return this.idno;
	}

	public void setIdno(String idno) {
		this.idno = idno;
	}

	public String getTel() {
		return this.tel;
	}

	public void setTel(String tel) {
		this.tel = tel;
	}

	public String getMobile() {
		return this.mobile;
	}

	public void setMobile(String mobile) {
		this.mobile = mobile;
	}

	public String getEmail() {
		return this.email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getAddr() {
		return this.addr;
	}

	public void setAddr(String addr) {
		this.addr = addr;
	}

	public String getZipcode() {
		return this.zipcode;
	}

	public void setZipcode(String zipcode) {
		this.zipcode = zipcode;
	}

	public String getBoardfeeflag() {
		return this.boardfeeflag;
	}

	public void setBoardfeeflag(String boardfeeflag) {
		this.boardfeeflag = boardfeeflag;
	}

	public String getRakeofftype() {
		return this.rakeofftype;
	}

	public void setRakeofftype(String rakeofftype) {
		this.rakeofftype = rakeofftype;
	}

	public double getRakeoffrate() {
		return this.rakeoffrate;
	}

	public void setRakeoffrate(double rakeoffrate) {
		this.rakeoffrate = rakeoffrate;
	}

	public double getDepositagio() {
		return this.depositagio;
	}

	public void setDepositagio(double depositagio) {
		this.depositagio = depositagio;
	}

	public BigDecimal getDepositcnt() {
		return this.depositcnt;
	}

	public void setDepositcnt(BigDecimal depositcnt) {
		this.depositcnt = depositcnt;
	}

	public double getDepositamt() {
		return this.depositamt;
	}

	public void setDepositamt(double depositamt) {
		this.depositamt = depositamt;
	}

	public double getDiscountamt() {
		return this.discountamt;
	}

	public void setDiscountamt(double discountamt) {
		this.discountamt = discountamt;
	}

	public String getBankcode() {
		return this.bankcode;
	}

	public void setBankcode(String bankcode) {
		this.bankcode = bankcode;
	}

	public String getBankaccno() {
		return this.bankaccno;
	}

	public void setBankaccno(String bankaccno) {
		this.bankaccno = bankaccno;
	}

	public String getBankaccname() {
		return this.bankaccname;
	}

	public void setBankaccname(String bankaccname) {
		this.bankaccname = bankaccname;
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

	public String getUseflag() {
		return this.useflag;
	}

	public void setUseflag(String useflag) {
		this.useflag = useflag;
	}

}