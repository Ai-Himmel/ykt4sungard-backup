/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: DormitoryWithAllInfo.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-6-7     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.dormitorymanage.web.help;

import org.king.dormitorymanage.domain.Dormitorymodel;

public class DormitoryWithAllInfo extends Dormitorymodel {

	public String fromProvince;

	public String collegeName;

	public String classNo;

	public String managerName;

	public String studentNo;

	public String stuName;

	public String majorin;

	public String nation;
	
	public String birthday;

	public DormitoryWithAllInfo(double fee,String area, String location, String dormitory,String unit,
			String roomNumber, int accomodation, String classId, String gender,
			String fromProvince, String collegeName, String classNo,
			String managerName, String studentNo, String stuName,
			String majorin, String nation,String birthday) {
		this.setFee(fee);
		this.setArea(area);
		this.setLocation(location);
		this.setDormitory(dormitory);
		this.setUnit(unit);
		this.setRoomNumber(roomNumber);
		this.setAccomodation(accomodation);
		this.setClassId(classId);
		this.setGender(gender);
		this.setFromProvince(fromProvince);
		this.setCollegeName(collegeName);
		this.setClassNo(classNo);
		this.setManagerName(managerName);
		this.setStudentNo(studentNo);
		this.setStuName(stuName);
		this.setMajorin(majorin);
		this.setNation(nation);
		this.setBirthday(birthday);
	}

	/**
	 * @return Returns the classNo.
	 */
	public String getClassNo() {
		return classNo;
	}

	/**
	 * @param classNo
	 *            The classNo to set.
	 */
	public void setClassNo(String classNo) {
		this.classNo = classNo;
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
	 * @return Returns the fromProvince.
	 */
	public String getFromProvince() {
		return fromProvince;
	}

	/**
	 * @param fromProvince
	 *            The fromProvince to set.
	 */
	public void setFromProvince(String fromProvince) {
		this.fromProvince = fromProvince;
	}

	/**
	 * @return Returns the majorin.
	 */
	public String getMajorin() {
		return majorin;
	}

	/**
	 * @param majorin
	 *            The majorin to set.
	 */
	public void setMajorin(String majorin) {
		this.majorin = majorin;
	}

	/**
	 * @return Returns the managerName.
	 */
	public String getManagerName() {
		return managerName;
	}

	/**
	 * @param managerName
	 *            The managerName to set.
	 */
	public void setManagerName(String managerName) {
		this.managerName = managerName;
	}

	/**
	 * @return Returns the nation.
	 */
	public String getNation() {
		return nation;
	}

	/**
	 * @param nation
	 *            The nation to set.
	 */
	public void setNation(String nation) {
		this.nation = nation;
	}

	/**
	 * @return Returns the studentNo.
	 */
	public String getStudentNo() {
		return studentNo;
	}

	/**
	 * @param studentNo
	 *            The studentNo to set.
	 */
	public void setStudentNo(String studentNo) {
		this.studentNo = studentNo;
	}

	/**
	 * @return Returns the stuName.
	 */
	public String getStuName() {
		return stuName;
	}

	/**
	 * @param stuName
	 *            The stuName to set.
	 */
	public void setStuName(String stuName) {
		this.stuName = stuName;
	}

	public String getBirthday() {
		return birthday;
	}

	public void setBirthday(String birthday) {
		this.birthday = birthday;
	}

}
