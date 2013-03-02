package com.kingstargroup.fdykt.dto;

public class ParklogDTO implements java.io.Serializable {
	private String checkintime;
	private String checkouttime;
	private String checkinplace;
	private String checkoutplace;
	private String custid;
	private String custname;
	private String carnumber;

	public String getCheckintime() {
		return checkintime;
	}

	public void setCheckintime(String checkintime) {
		this.checkintime = checkintime;
	}

	public String getCheckouttime() {
		return checkouttime;
	}

	public void setCheckouttime(String checkouttime) {
		this.checkouttime = checkouttime;
	}

	public String getCheckinplace() {
		return checkinplace;
	}

	public void setCheckinplace(String checkinplace) {
		this.checkinplace = checkinplace;
	}

	public String getCheckoutplace() {
		return checkoutplace;
	}

	public void setCheckoutplace(String checkoutplace) {
		this.checkoutplace = checkoutplace;
	}

	public String getCustid() {
		return custid;
	}

	public void setCustid(String custid) {
		this.custid = custid;
	}

	public String getCustname() {
		return custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
	}

	public String getCarnumber() {
		return carnumber;
	}

	public void setCarnumber(String carnumber) {
		this.carnumber = carnumber;
	}

}
