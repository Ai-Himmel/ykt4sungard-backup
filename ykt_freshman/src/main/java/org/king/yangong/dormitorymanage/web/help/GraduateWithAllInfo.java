package org.king.yangong.dormitorymanage.web.help;

import org.king.yangong.dormitorymanage.domain.YxGraduate;

public class GraduateWithAllInfo extends YxGraduate {
	public String college;

	public String classId;
	
	public String bathcardNo;

	public String assistant;
	
	public String area;
	
	public String location;

	public String dormitory;

	public String unit;
	
	public String roomnumber;

	public String getAssistant() {
		return assistant;
	}

	public void setAssistant(String assistant) {
		this.assistant = assistant;
	}

	public String getBathcardNo() {
		return bathcardNo;
	}

	public void setBathcardNo(String bathcardNo) {
		this.bathcardNo = bathcardNo;
	}

	public String getClassId() {
		return classId;
	}

	public void setClassId(String classId) {
		this.classId = classId;
	}

	public String getCollege() {
		return college;
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

	public String getLocation() {
		return location;
	}

	public void setLocation(String location) {
		this.location = location;
	}

	public String getRoomnumber() {
		return roomnumber;
	}
	
	
    public GraduateWithAllInfo(
    		String college,String classId,String area,String location,String dormitory,String unit,String roomnumber, 
    		String id,String graduateNo, String graduateName, String sex,
    		String nation, String nationality,String speciality,String studentType,
    		String enrollYear,String enrollMonth ,String birthday,String curGrade,
    		String curCollegeDepartment,String IFPAYDORMFEE ,String cultureMode, String matriculateType,
    		String curDepartment,String curCollege,String adminCollege, 
    		String graduateType,String distriction,String requestAvailable,String residentNeed,
    		String dormitoryId,String updateTime,String updateDate) {
    	
    	
    	this.setArea(area);
    	this.setCollege(college);
    	this.setClassId(classId);
    	this.setLocation(location);
    	this.setDormitory(dormitory);
    	this.setUnit(unit);
    	this.setRoomnumber(roomnumber);
    	this.setId(id);
		this.setGraduateNo(graduateNo);
		this.setGraduateName(graduateName);
		this.setSex(sex);
		this.setNation(nation);
		this.setNationality(nationality);
		this.setStudentType(studentType);
		this.setEnrollYear(enrollYear);
		this.setEnrollMonth(enrollMonth) ;
		this.setBirthday(birthday);
		this.setCurGrade(curGrade);
		this.setCurCollegeDepartment(curCollegeDepartment);
		this.setIFPAYDORMFEE(IFPAYDORMFEE);
		this.setSpeciality(speciality);
		this.setCultureMode(cultureMode);
		this.setMatriculateType(matriculateType);
		this.setCurDepartment(curDepartment);
		this.setCurCollege(curCollege);
		this.setAdminCollege(adminCollege);
//		this.setLengthofschool(lengthofschool);
		this.setGraduateType(graduateType);
		this.setDistriction(distriction);
		this.setRequestAvailable(requestAvailable);
		this.setResidentNeed(residentNeed);
		this.setDormitoryId(dormitoryId);
		this.setUpdateTime(updateTime);
		this.setUpdateDate(updateDate);
	}

	public String getArea() {
		return area;
	}

	public void setArea(String area) {
		this.area = area;
	}

	public String getUnit() {
		return unit;
	}

	public void setUnit(String unit) {
		this.unit = unit;
	}

	public void setRoomnumber(String roomnumber) {
		this.roomnumber = roomnumber;
	}
	
}
