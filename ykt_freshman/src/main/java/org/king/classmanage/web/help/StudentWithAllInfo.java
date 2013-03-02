/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: StudentWithAllInfo.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-5-9     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

import org.king.classmanage.domain.Studentmodel;

public class StudentWithAllInfo extends Studentmodel {

	public String college;

	public String classId;
	
	public String bathcardNo;

	public String assistant;
	
	public String area;	
	
	public String location;

	public String dormitory;

	public String roomnumber;

	/**
	 * @return Returns the bathcardNo.
	 */
	public String getBathcardNo() {
		return bathcardNo;
	}

	/**
	 * @param bathcardNo The bathcardNo to set.
	 */
	public void setBathcardNo(String bathcardNo) {
		this.bathcardNo = bathcardNo;
	}

	/**
	 * @return Returns the assistant.
	 */
	public String getAssistant() {
		return assistant;
	}

	/**
	 * @param assistant
	 *            The assistant to set.
	 */
	public void setAssistant(String assistant) {
		this.assistant = assistant;
	}


	/**
	 * @return Returns the classId.
	 */
	public String getClassId() {
		return classId;
	}

	/**
	 * @param classId The classId to set.
	 */
	public void setClassId(String classId) {
		this.classId = classId;
	}

	/**
	 * @return Returns the college.
	 */
	public String getCollege() {
		return college;
	}

	/**
	 * @param college
	 *            The college to set.
	 */
	public void setCollege(String college) {
		this.college = college;
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
	 * @return Returns the roomnumber.
	 */
	public String getRoomnumber() {
		return roomnumber;
	}	

	public String getArea() {
		return area;
	}

	public void setArea(String area) {
		this.area = area;
	}

	/**
	 * @param roomnumber
	 *            The roomnumber to set.
	 */
	public void setRoomnumber(String roomnumber) {
		this.roomnumber = roomnumber;
	}

	public StudentWithAllInfo(String college, String classId, String assistant,String location,
			String dormitory, String roomnumber, String studentId,
			String studentNo, String enterenceNo, String examNo,String tempecardNo,String idCard,String bathcardNo,
			String stuName, String gender, String birthday,
			String homeTelephone, String nation, String nationality,
			String fromProvince, String midSchCode, String midSchName,
			String polityBg, String majorin,String department, String specIntrst,
			String studentType, String enrollYear, String curGrade,
			String dormId,String area,String idType,String cultureMode,String studentChar,Integer checkornot,Integer schoolornot) {
//        <!-- 证件类型 -->
//        <property name="idType" type="string">
//        <!-- 培养层次 -->
//        <property name="cultureMode" type="string">
//        <!-- 学生性质 -->
//        <property name="studentChar" type="string">
//        <!-- 是否在籍 -->
//        <property name="checkornot" type="integer">
//        <!-- 是否在校 -->
//        <property name="schoolornot" type="integer">
		this.setBirthday(birthday);
		this.setAssistant(assistant);
		this.setClassId(classId);
		this.setCollege(college);
		this.setCurGrade(curGrade);
		this.setDormId(dormId);
		this.setDormitory(dormitory);
		this.setEnrollYear(enrollYear);
		this.setEnterenceNo(enterenceNo);
		this.setExamNo(examNo);
		this.setTempecardNo(tempecardNo);
		this.setIdCard(idCard);
		this.setBathcardNo(bathcardNo);
		this.setFromProvince(fromProvince);
		this.setGender(gender);
		this.setHomeTelephone(homeTelephone);
		this.setMajorin(majorin);
		this.setDepartment(department);
		this.setMidSchCode(midSchCode);
		this.setMidSchName(midSchName);
		this.setNation(nation);
		this.setNationality(nationality);
		this.setPolityBg(polityBg);
		this.setRoomnumber(roomnumber);
		this.setSpecIntrst(specIntrst);
		this.setStudentId(studentId);
		this.setStudentNo(studentNo);
		this.setStudentType(studentType);
		this.setStuName(stuName);
		this.setLocation(location);
		this.setArea(area);
		this.setIdType(idType);
		this.setCultureMode(cultureMode);
		this.setStudentChar(studentChar);
		this.setCheckornot(checkornot);
		this.setSchoolornot(schoolornot);
		

	}

}
