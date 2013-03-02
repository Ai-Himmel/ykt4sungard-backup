package org.king.classmanage.domain;

public class StudentListColumns implements java.io.Serializable {
	/**
	 * 
	 */
	private static final long serialVersionUID = 1L;

	private String college;

	private String name;

	private String assistant;

	private String studentNo;

	private String enterenceNo;

	private String stuName;

	private String gender;

	private String department;

	private String majorin;

	private String nation;

	private String nationality;

	private String province;

	private String idType;

	private String idCard;

	private String cultureMode;

	private String studentChar;

	private String checkornot;

	private String schoolornot;

	private String polityBg;

	private String location;

	private String dormitory;

	private String roomNumber;

	private String birthday;

	private String homeTelephone;

	private String tempecardNo;

	private String bathcardNo;

	private String examNo;

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

	public String getBirthday() {
		return birthday;
	}

	public void setBirthday(String birthday) {
		this.birthday = birthday;
	}

	public String getCheckornot() {
		return checkornot;
	}

	public void setCheckornot(String checkornot) {
		this.checkornot = checkornot;
	}

	public String getCollege() {
		return college;
	}

	public void setCollege(String college) {
		this.college = college;
	}

	public String getCultureMode() {
		return cultureMode;
	}

	public void setCultureMode(String cultureMode) {
		this.cultureMode = cultureMode;
	}

	public String getDepartment() {
		return department;
	}

	public void setDepartment(String department) {
		this.department = department;
	}

	public String getDormitory() {
		return dormitory;
	}

	public void setDormitory(String dormitory) {
		this.dormitory = dormitory;
	}

	public String getEnterenceNo() {
		return enterenceNo;
	}

	public void setEnterenceNo(String enterenceNo) {
		this.enterenceNo = enterenceNo;
	}

	public String getExamNo() {
		return examNo;
	}

	public void setExamNo(String examNo) {
		this.examNo = examNo;
	}

	public String getGender() {
		return gender;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}

	public String getHomeTelephone() {
		return homeTelephone;
	}

	public void setHomeTelephone(String homeTelephone) {
		this.homeTelephone = homeTelephone;
	}

	public String getIdCard() {
		return idCard;
	}

	public void setIdCard(String idCard) {
		this.idCard = idCard;
	}

	public String getIdType() {
		return idType;
	}

	public void setIdType(String idType) {
		this.idType = idType;
	}

	public String getLocation() {
		return location;
	}

	public void setLocation(String location) {
		this.location = location;
	}

	public String getMajorin() {
		return majorin;
	}

	public void setMajorin(String majorin) {
		this.majorin = majorin;
	}

	public String getName() {
		return name;
	}

	public void setName(String name) {
		this.name = name;
	}

	public String getNation() {
		return nation;
	}

	public void setNation(String nation) {
		this.nation = nation;
	}

	public String getNationality() {
		return nationality;
	}

	public void setNationality(String nationality) {
		this.nationality = nationality;
	}

	public String getPolityBg() {
		return polityBg;
	}

	public void setPolityBg(String polityBg) {
		this.polityBg = polityBg;
	}

	public String getProvince() {
		return province;
	}

	public void setProvince(String province) {
		this.province = province;
	}

	public String getRoomNumber() {
		return roomNumber;
	}

	public void setRoomNumber(String roomNumber) {
		this.roomNumber = roomNumber;
	}

	public String getSchoolornot() {
		return schoolornot;
	}

	public void setSchoolornot(String schoolornot) {
		this.schoolornot = schoolornot;
	}

	public String getStudentChar() {
		return studentChar;
	}

	public void setStudentChar(String studentChar) {
		this.studentChar = studentChar;
	}

	public String getStudentNo() {
		return studentNo;
	}

	public void setStudentNo(String studentNo) {
		this.studentNo = studentNo;
	}

	public String getStuName() {
		return stuName;
	}

	public void setStuName(String stuName) {
		this.stuName = stuName;
	}

	public String getTempecardNo() {
		return tempecardNo;
	}

	public void setTempecardNo(String tempecardNo) {
		this.tempecardNo = tempecardNo;
	}

	public StudentListColumns(String college, String name, String assistant,
			String studentNo, String enterenceNo, String stuName,
			String gender, String department, String majorin, String nation,
			String nationality, String province, String idType, String idCard,
			String cultureMode, String studentChar, String checkornot,
			String schoolornot, String polityBg, String location,
			String dormitory, String roomNumber, String birthday,
			String homeTelephone, String tempecardNo, String bathcardNo,
			String examNo) {
		super();
		this.college = college;
		this.name = name;
		this.assistant = assistant;
		this.studentNo = studentNo;
		this.enterenceNo = enterenceNo;
		this.stuName = stuName;
		this.gender = gender;
		this.department = department;
		this.majorin = majorin;
		this.nation = nation;
		this.nationality = nationality;
		this.province = province;
		this.idType = idType;
		this.idCard = idCard;
		this.cultureMode = cultureMode;
		this.studentChar = studentChar;
		this.checkornot = checkornot;
		this.schoolornot = schoolornot;
		this.polityBg = polityBg;
		this.location = location;
		this.dormitory = dormitory;
		this.roomNumber = roomNumber;
		this.birthday = birthday;
		this.homeTelephone = homeTelephone;
		this.tempecardNo = tempecardNo;
		this.bathcardNo = bathcardNo;
		this.examNo = examNo;
	}

	public StudentListColumns() {
		super();
		// TODO Auto-generated constructor stub
	}

}
