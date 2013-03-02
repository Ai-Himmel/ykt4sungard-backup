package com.kingstargroup.ecard.hibernate.shop;

public class ShopDinnerReportResult {
	
	private int shopid;
	private String shopname;
	private int mealtype;
	private String mealname;
	private int deviceid;
	private String transdate;
	private String devicename;
	private int transtype;
	private String summary;
	private int transcnt;
	private double dramt;
	private double cramt;
	private double damt3;
	private int num;
	public int getShopid() {
		return shopid;
	}
	public void setShopid(int shopid) {
		this.shopid = shopid;
	}
	public String getShopname() {
		return shopname;
	}
	public void setShopname(String shopname) {
		this.shopname = shopname;
	}
	public int getMealtype() {
		return mealtype;
	}
	public void setMealtype(int mealtype) {
		this.mealtype = mealtype;
	}
	public String getMealname() {
		return mealname;
	}
	public void setMealname(String mealname) {
		this.mealname = mealname;
	}
	public int getDeviceid() {
		return deviceid;
	}
	public void setDeviceid(int deviceid) {
		this.deviceid = deviceid;
	}
	public String getDevicename() {
		return devicename;
	}
	public void setDevicename(String devicename) {
		this.devicename = devicename;
	}
	public int getTranstype() {
		return transtype;
	}
	public void setTranstype(int transtype) {
		this.transtype = transtype;
	}
	public String getSummary() {
		return summary;
	}
	public void setSummary(String summary) {
		this.summary = summary;
	}
	public int getTranscnt() {
		return transcnt;
	}
	public void setTranscnt(int transcnt) {
		this.transcnt = transcnt;
	}
	public double getDramt() {
		return dramt;
	}
	public void setDramt(double dramt) {
		this.dramt = dramt;
	}
	public double getCramt() {
		return cramt;
	}
	public void setCramt(double cramt) {
		this.cramt = cramt;
	}
	public double getDamt3() {
		return damt3;
	}
	public void setDamt3(double damt3) {
		this.damt3 = damt3;
	}
	public String getTransdate() {
		return transdate;
	}
	public void setTransdate(String transdate) {
		this.transdate = transdate;
	}
	public int getNum() {
		return num;
	}
	public void setNum(int num) {
		this.num = num;
	} 
}
