package org.king.classmanage.web.help;

public class AbroadStuInfo {
	public String StudentId;
	public String studentNo;
	public String stuName;
	public String gender;
	public String nationality;
	public String majorin;
	public AbroadStuInfo(String studentId, String studentNo, String stuName, String gender, String nationality, String majorin) {
		StudentId = studentId;
		this.studentNo = studentNo;
		this.stuName = stuName;
		this.gender = gender;
		this.nationality = nationality;
		this.majorin = majorin;
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
	 * @return Returns the majorin.
	 */
	public String getMajorin() {
		return majorin;
	}
	/**
	 * @param majorin The majorin to set.
	 */
	public void setMajorin(String majorin) {
		this.majorin = majorin;
	}
	/**
	 * @return Returns the nationality.
	 */
	public String getNationality() {
		return nationality;
	}
	/**
	 * @param nationality The nationality to set.
	 */
	public void setNationality(String nationality) {
		this.nationality = nationality;
	}
	/**
	 * @return Returns the studentId.
	 */
	public String getStudentId() {
		return StudentId;
	}
	/**
	 * @param studentId The studentId to set.
	 */
	public void setStudentId(String studentId) {
		StudentId = studentId;
	}
	/**
	 * @return Returns the studentNo.
	 */
	public String getStudentNo() {
		return studentNo;
	}
	/**
	 * @param studentNo The studentNo to set.
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
	 * @param stuName The stuName to set.
	 */
	public void setStuName(String stuName) {
		this.stuName = stuName;
	}
	
	
	
	
	
}
