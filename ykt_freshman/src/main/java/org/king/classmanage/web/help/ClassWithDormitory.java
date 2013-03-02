/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassWithDormitory.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-30     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

import org.king.classmanage.domain.Classmodel;

public class ClassWithDormitory extends Classmodel {

	public String collegeName;

	public String assistantName;
	
	public String area;
	
	public String location;

	public String dormitory;

	public String roomNumber;
	
	public String direction; 
	
	public String gender;
	
	public String telphone;
	
	public int accomodation;
	
	
	
	

	/**
	 * @return Returns the telphone.
	 */
	public String getTelphone() {
		return telphone;
	}

	/**
	 * @param telphone The telphone to set.
	 */
	public void setTelphone(String telphone) {
		this.telphone = telphone;
	}

	/**
	 * @return Returns the accomodation.
	 */
	public int getAccomodation() {
		return accomodation;
	}

	/**
	 * @param accomodation The accomodation to set.
	 */
	public void setAccomodation(int accomodation) {
		this.accomodation = accomodation;
	}

	/**
	 * @return Returns the gender.
	 */
	public String getGender() {
		return gender;
	}

	/**
	 * @param gender The gender to set.
	 */
	public void setGender(String gender) {
		this.gender = gender;
	}

	/**
	 * @return Returns the location.
	 */
	public String getLocation() {
		return location;
	}

	/**
	 * @param location The location to set.
	 */
	public void setLocation(String location) {
		this.location = location;
	}

	/**
	 * @return Returns the collegeName.
	 */
	public String getCollegeName() {
		return collegeName;
	}

	/**
	 * @param collegeName
	 *            The collegeName to set.
	 */
	public void setCollegeName(String collegeName) {
		this.collegeName = collegeName;
	}

	/**
	 * @return Returns the dormitory.
	 */
	public String getDormitory() {
		return dormitory;
	}

	/**
	 * @param dormitory
	 *            The dormitory to set.
	 */
	public void setDormitory(String dormitory) {
		this.dormitory = dormitory;
	}

	/**
	 * @return Returns the managerName.
	 */
	public String getAssistantName() {
		return assistantName;
	}

	/**
	 * @param managerName
	 *            The managerName to set.
	 */
	public void setAssistantName(String assistantName) {
		this.assistantName = assistantName;
	}

	/**
	 * @return Returns the roomNumber.
	 */
	public String getRoomNumber() {
		return roomNumber;
	}

	/**
	 * @param roomNumber
	 *            The roomNumber to set.
	 */
	public void setRoomNumber(String roomNumber) {
		this.roomNumber = roomNumber;
	}


	public String getArea() {
		return area;
	}

	public void setArea(String area) {
		this.area = area;
	}

	public String getDirection() {
		return direction;
	}

	public void setDirection(String direction) {
		this.direction = direction;
	}

	/**
	 * @param classId
	 * @param classNo
	 * @param className
	 * @param collegeName
	 * @param managerName
	 * @param dormitory
	 * @param roomNumber
	 */
	public ClassWithDormitory(String classId, String classNo, String className,
			String collegeName, String assistantName,String location, String dormitory,
			String roomNumber,String gender,String telphone,int accomodation,String area,String direction) {
		this.setClassId(classId);
		this.setClassNo(classNo);
		this.setClassName(className);
		this.assistantName = assistantName;
		this.collegeName = collegeName;
		this.location = location;
		this.dormitory = dormitory;
		this.roomNumber = roomNumber;
		this.direction = direction;
		this.telphone = telphone;
		this.setGender(gender);
		this.setAccomodation(accomodation);
		this.setArea(area);
	}

}
