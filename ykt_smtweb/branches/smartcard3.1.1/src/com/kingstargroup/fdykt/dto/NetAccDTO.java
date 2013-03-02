package com.kingstargroup.fdykt.dto;

/**
 * ÍøÂçÇ®°üÕË»§
 * @author Xuan.Zhou
 *
 */
public class NetAccDTO implements java.io.Serializable{

	private static final long serialVersionUID = 1L;
	private String accno;
	private String accname;
	private String accPwd;
	private String status;
	private long custid;
	private double availbal;
	private double frozebal;
	private double balance;
	private String lastTransDate;
	private String lastaccdate;
	private String opendate;
	private String closedate;
	
	public String getAccno() {
		return accno;
	}
	public void setAccno(String accno) {
		this.accno = accno;
	}
	public String getAccname() {
		return accname;
	}
	public void setAccname(String accname) {
		this.accname = accname;
	}
	public String getAccPwd() {
		return accPwd;
	}
	public void setAccPwd(String accPwd) {
		this.accPwd = accPwd;
	}
	public String getStatus() {
		return status;
	}
	public void setStatus(String status) {
		this.status = status;
	}
	public long getCustid() {
		return custid;
	}
	public void setCustid(long custid) {
		this.custid = custid;
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
	public double getBalance() {
		return balance;
	}
	public void setBalance(double balance) {
		this.balance = balance;
	}
	public String getLastTransDate() {
		return lastTransDate;
	}
	public void setLastTransDate(String lastTransDate) {
		this.lastTransDate = lastTransDate;
	}
	public String getLastaccdate() {
		return lastaccdate;
	}
	public void setLastaccdate(String lastaccdate) {
		this.lastaccdate = lastaccdate;
	}
	public String getOpendate() {
		return opendate;
	}
	public void setOpendate(String opendate) {
		this.opendate = opendate;
	}
	public String getClosedate() {
		return closedate;
	}
	public void setClosedate(String closedate) {
		this.closedate = closedate;
	}
	

}
