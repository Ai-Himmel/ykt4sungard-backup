/* ============================================================
 * 版权：    king 版权所有 (c) 2007
 * 文件：    QuartersModel.java
 * 创建日期： 2007-6-18 15:29:52
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 *  2007-6-18 15:29:52     王胜        创建文件，实现基本功能
 * ============================================================
 */
package org.king.quarters.service;

public class QuartersModel {
	private String dormitoryId;
    private Double fee;
    private String location;
    private String dormitory;
    private String roomNumber;
    private Integer accomodation;
    private String classId;
    private String gender;
    private String telphone;
    private String area;
    private String level;
    private String unit;
    private String curDormDept;
    private String ifDistribute;
    private Integer distributeNum;
    private String memo1;
    private String memo2;
    private Integer emptyNum;
    private String direction;
	public Integer getAccomodation() {
		return accomodation;
	}
	public void setAccomodation(Integer accomodation) {
		this.accomodation = accomodation;
	}
	public String getArea() {
		return area;
	}
	public void setArea(String area) {
		this.area = area;
	}
	public String getClassId() {
		return classId;
	}
	public void setClassId(String classId) {
		this.classId = classId;
	}
	public String getCurDormDept() {
		return curDormDept;
	}
	public void setCurDormDept(String curDormDept) {
		this.curDormDept = curDormDept;
	}
	public String getDirection() {
		return direction;
	}
	public void setDirection(String direction) {
		this.direction = direction;
	}
	public Integer getDistributeNum() {
		return distributeNum;
	}
	public void setDistributeNum(Integer distributeNum) {
		this.distributeNum = distributeNum;
	}
	public String getDormitory() {
		return dormitory;
	}
	public void setDormitory(String dormitory) {
		this.dormitory = dormitory;
	}
	public String getDormitoryId() {
		return dormitoryId;
	}
	public void setDormitoryId(String dormitoryId) {
		this.dormitoryId = dormitoryId;
	}
	public Integer getEmptyNum() {
		return emptyNum;
	}
	public void setEmptyNum(Integer emptyNum) {
		this.emptyNum = emptyNum;
	}
	public Double getFee() {
		return fee;
	}
	public void setFee(Double fee) {
		this.fee = fee;
	}
	public String getGender() {
		return gender;
	}
	public void setGender(String gender) {
		this.gender = gender;
	}
	public String getIfDistribute() {
		return ifDistribute;
	}
	public void setIfDistribute(String ifDistribute) {
		this.ifDistribute = ifDistribute;
	}
	public String getLevel() {
		return level;
	}
	public void setLevel(String level) {
		this.level = level;
	}
	public String getLocation() {
		return location;
	}
	public void setLocation(String location) {
		this.location = location;
	}
	public String getMemo1() {
		return memo1;
	}
	public void setMemo1(String memo1) {
		this.memo1 = memo1;
	}
	public String getMemo2() {
		return memo2;
	}
	public void setMemo2(String memo2) {
		this.memo2 = memo2;
	}
	public String getRoomNumber() {
		return roomNumber;
	}
	public void setRoomNumber(String roomNumber) {
		this.roomNumber = roomNumber;
	}
	public String getTelphone() {
		return telphone;
	}
	public void setTelphone(String telphone) {
		this.telphone = telphone;
	}
	public String getUnit() {
		return unit;
	}
	public void setUnit(String unit) {
		this.unit = unit;
	}

}
