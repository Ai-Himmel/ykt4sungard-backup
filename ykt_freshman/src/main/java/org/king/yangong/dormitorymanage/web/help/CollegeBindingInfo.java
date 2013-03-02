package org.king.yangong.dormitorymanage.web.help;

public class CollegeBindingInfo {
	public String curCollege;

	public String curCollegeStr;

	public String studentType;

	public String studentTypeStr;

	public String sex;

	public String sexStr;

	public int count;

	public CollegeBindingInfo(String curCollege, String curCollegeStr,
			String studentType, String studentTypeStr, String sex, String sexStr,int count) {

		this.curCollege = curCollege;
		this.curCollegeStr = curCollegeStr;
		this.studentType = studentType;
		this.studentTypeStr = studentTypeStr;
		this.sex = sex;
		this.sexStr = sexStr;
		this.count = count;
	}

	public int getCount() {
		return count;
	}

	public void setCount(int count) {
		this.count = count;
	}

	public String getCurCollege() {
		return curCollege;
	}

	public void setCurCollege(String curCollege) {
		this.curCollege = curCollege;
	}

	public String getCurCollegeStr() {
		return curCollegeStr;
	}

	public void setCurCollegeStr(String curCollegeStr) {
		this.curCollegeStr = curCollegeStr;
	}

	public String getSex() {
		return sex;
	}

	public void setSex(String sex) {
		this.sex = sex;
	}

	public String getSexStr() {
		return sexStr;
	}

	public void setSexStr(String sexStr) {
		this.sexStr = sexStr;
	}

	public String getStudentType() {
		return studentType;
	}

	public void setStudentType(String studentType) {
		this.studentType = studentType;
	}

	public String getStudentTypeStr() {
		return studentTypeStr;
	}

	public void setStudentTypeStr(String studentTypeStr) {
		this.studentTypeStr = studentTypeStr;
	}

}
