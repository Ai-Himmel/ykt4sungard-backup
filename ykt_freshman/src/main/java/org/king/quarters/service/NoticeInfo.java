/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    NoticeInfo.java
 * 创建日期： 2007-6-14 10:32:59
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-14 10:32:59     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.service;


public class NoticeInfo {
	
	private String id;
	private String stuNo;
	private String name;
	private String dormitory;
	private String unit;
	private String roomNumber;
	private Double fee;
	
	private Double grade;
	private String college;
	private String majors ;
	private String location;
	private String area;
	private String endyear;
	public String getCollege() {
		return college;
	}
	public NoticeInfo(){
		
		
	}
	public NoticeInfo(String id, String stuNo, String name, String dormitory, String unit, String roomNuber, Double fee, Double grade, String college, String majors, String location, String area,String endyear) {
		super();
		// TODO Auto-generated constructor stub
		this.id = id;
		this.stuNo = stuNo;
		this.name = name;
		this.dormitory = dormitory;
		this.unit = unit;
		this.roomNumber = roomNuber;
		this.fee = fee;
		
		this.grade = grade;
		this.college = college;
		this.majors = majors;
		this.location = location;
		this.area = area;
		this.endyear=endyear;
	}
	public void setCollege(String college) {
		this.college = college;
	}
	public String getDormitory() {
		return dormitory;
	}
	public void setDormitory(String dormitory) {
		this.dormitory = dormitory;
	}
	public Double getFee() {
		return fee;
	}
	public void setFee(Double fee) {
		this.fee = fee;
	}
	public Double getGrade() {
		return grade;
	}
	public void setGrade(Double grade) {
		this.grade = grade;
	}
	public String getId() {
		return id;
	}
	public void setId(String id) {
		this.id = id;
	}
	public String getMajors() {
		return majors;
	}
	public void setMajors(String majors) {
		this.majors = majors;
	}
	public String getName() {
		return name;
	}
	public void setName(String name) {
		this.name = name;
	}
	
	
	public String getRoomNumber() {
		return roomNumber;
	}
	public void setRoomNumber(String roomNumber) {
		this.roomNumber = roomNumber;
	}
	public String getStuNo() {
		return stuNo;
	}
	public void setStuNo(String stuNo) {
		this.stuNo = stuNo;
	}
	public String getUnit() {
		return unit;
	}
	public void setUnit(String unit) {
		this.unit = unit;
	}
	
	public String getArea() {
		return area;
	}
	public void setArea(String area) {
		this.area = area;
	}
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
	public String getEndyear() {
		return endyear;
	}
	public void setEndyear(String endyear) {
		this.endyear = endyear;
	}

}
