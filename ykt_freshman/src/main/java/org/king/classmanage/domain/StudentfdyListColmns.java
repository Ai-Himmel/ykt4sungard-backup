package org.king.classmanage.domain;

public class StudentfdyListColmns implements java.io.Serializable {
	private static final long serialVersionUID = 1L;
	private String studentNo;
	private String enterenceNo;
	private String stuName;
	private String gender;
	private String department;
	private String majorin;
	private String nation;
	private String nationality;
	private String fromProvince;
	private String idType;
	private String idCard;
	private String cultureMode;
	private String studentChar;
	private String checkornot;
	private String schoolornot;
	private String polityBg;
	private String location;
	private String dormitory;
	private String roomnumber;
	private String birthday;
	private String homeTelephone;
	private String tempecardNo;
	private String bathcardNo;
	private String examNo;
	
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
	public String getRoomnumber() {
		return roomnumber;
	}
	public void setRoomnumber(String roomnumber) {
		this.roomnumber = roomnumber;
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
	public StudentfdyListColmns( String studentNo,String enterenceNo,String stuName,
			String gender,String department,String majorin,String nation,String nationality,
			String fromProvince,String idType,String idCard,String cultureMode,String studentChar,
			String checkornot,String schoolornot,String polityBg,String location,String dormitory,String roomnumber,
			String birthday,String homeTelephone,String tempecardNo,String bathcardNo,String examNo
			 ) {
		this.studentNo=studentNo;
		this.enterenceNo=enterenceNo;
		this.stuName=stuName;
		this.gender=gender;
		this.department=department;
		this.majorin=majorin;
		this.nation=nation;
		this.nationality=nationality;
		this.fromProvince=fromProvince;
		this.idType=idType;
		this.idCard=idCard;
		this.cultureMode=cultureMode;
		this.studentChar=studentChar;
		this.checkornot=checkornot;
		this.schoolornot=schoolornot;
		this.polityBg=polityBg;
		this.location=location;
		this.dormitory=dormitory;
		this.roomnumber=roomnumber;
		this.birthday=birthday;
		this.homeTelephone=homeTelephone;
		this.tempecardNo=tempecardNo;
		this.bathcardNo=bathcardNo;
		this.examNo=examNo;
	
	
	}
	public StudentfdyListColmns() {
		super();
		// TODO Auto-generated constructor stub
	}
	public String getFromProvince() {
		return fromProvince;
	}
	public void setFromProvince(String fromProvince) {
		this.fromProvince = fromProvince;
	}


}
