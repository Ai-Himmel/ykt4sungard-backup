package com.kingstargroup.fdykt.dto;

public class UpdateInfoDTO implements java.io.Serializable {
	private String cardphyid;
	private long feetype;
	private String feename;
	private String accname;
	private long custid;
	private long cardno;
	private long cardtype;		
	private double balance;
	private double availbal;
	private double frozebal;
	private String opendate;
	private String expiredate;
	private String stuempno;
	public String getCardphyid() {
		return cardphyid;
	}
	public void setCardphyid(String cardphyid) {
		this.cardphyid = cardphyid;
	}
	public long getFeetype() {
		return feetype;
	}
	public void setFeetype(long feetype) {
		this.feetype = feetype;
	}
	public String getFeename() {
		return feename;
	}
	public void setFeename(String feename) {
		this.feename = feename;
	}
	public String getAccname() {
		return accname;
	}
	public void setAccname(String accname) {
		this.accname = accname;
	}
	public long getCustid() {
		return custid;
	}
	public void setCustid(long custid) {
		this.custid = custid;
	}
	public long getCardno() {
		return cardno;
	}
	public void setCardno(long cardno) {
		this.cardno = cardno;
	}
	public long getCardtype() {
		return cardtype;
	}
	public void setCardtype(long cardtype) {
		this.cardtype = cardtype;
	}
	public double getBalance() {
		return balance;
	}
	public void setBalance(double balance) {
		this.balance = balance;
	}
	public double getAvailbal() {
		return availbal;
	}
	public void setAvailbal(double availbal) {
		this.availbal = availbal;
	}
	public double getFrozebal() {
		return frozebal;
	}
	public void setFrozebal(double frozebal) {
		this.frozebal = frozebal;
	}
	
	public String getOpendate() {
		return opendate;
	}
	public void setOpendate(String opendate) {
		this.opendate = opendate;
	}
	public String getExpiredate() {
		return expiredate;
	}
	public void setExpiredate(String expiredate) {
		this.expiredate = expiredate;
	}
	
	public String getStuempno() {
		return stuempno;
	}
	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}
	
	
	
}
