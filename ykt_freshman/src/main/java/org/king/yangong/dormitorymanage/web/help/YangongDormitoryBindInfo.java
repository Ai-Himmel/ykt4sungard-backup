package org.king.yangong.dormitorymanage.web.help;

public class YangongDormitoryBindInfo {
	public String dormitoryId;

	public String area;

	public String areaStr;

	public String location;

	public String locationStr;

	public String dormitory;

	public String dormitoryStr;

	public String level;

	public String levelStr;

	public String unit;

	public String unitStr;
	
	public String direction;
	
	public String directionStr;

	public String roomNumber;

	public String gender;
	
	public String genderStr;

	public int emptyNum;
	
	public String stuType;

	public String collegeId;

	public YangongDormitoryBindInfo(String dormitoryId, String area,
			String areaStr, String location, String locationStr,
			String dormitory, String dormitoryStr, String level,
			String levelStr, String unit, String unitStr,String direction,String directionStr, String roomNumber,
			String gender, String genderStr,int emptyNum, String stuType,String collegeId) {
		this.dormitoryId = dormitoryId;
		this.area = area;
		this.areaStr = areaStr;
		this.location = location;
		this.locationStr = locationStr;
		this.dormitory = dormitory;
		this.dormitoryStr = dormitoryStr;
		this.level = level;
		this.levelStr = levelStr;
		this.unit = unit;
		this.unitStr = unitStr;
		this.direction = direction;
		this.directionStr = directionStr;
		this.roomNumber = roomNumber;
		this.gender = gender;
		this.genderStr = genderStr;
		this.emptyNum = emptyNum;
		this.stuType = stuType;
		this.collegeId = collegeId;
	}

	public String getStuType() {
		return stuType;
	}

	public void setStuType(String stuType) {
		this.stuType = stuType;
	}

	public String getArea() {
		return area;
	}

	public void setArea(String area) {
		this.area = area;
	}

	public String getAreaStr() {
		return areaStr;
	}

	public void setAreaStr(String areaStr) {
		this.areaStr = areaStr;
	}

	public String getCollegeId() {
		return collegeId;
	}

	public void setCollegeId(String collegeId) {
		this.collegeId = collegeId;
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

	public String getDormitoryStr() {
		return dormitoryStr;
	}

	public void setDormitoryStr(String dormitoryStr) {
		this.dormitoryStr = dormitoryStr;
	}

	public int getEmptyNum() {
		return emptyNum;
	}

	public void setEmptyNum(int emptyNum) {
		this.emptyNum = emptyNum;
	}

	public String getGender() {
		return gender;
	}

	public void setGender(String gender) {
		this.gender = gender;
	}

	public String getLevel() {
		return level;
	}

	public void setLevel(String level) {
		this.level = level;
	}

	public String getLevelStr() {
		return levelStr;
	}

	public void setLevelStr(String levelStr) {
		this.levelStr = levelStr;
	}

	public String getLocation() {
		return location;
	}

	public void setLocation(String location) {
		this.location = location;
	}

	public String getLocationStr() {
		return locationStr;
	}

	public void setLocationStr(String locationStr) {
		this.locationStr = locationStr;
	}

	public String getRoomNumber() {
		return roomNumber;
	}

	public void setRoomNumber(String roomNumber) {
		this.roomNumber = roomNumber;
	}

	public String getUnit() {
		return unit;
	}

	public void setUnit(String unit) {
		this.unit = unit;
	}

	public String getUnitStr() {
		return unitStr;
	}

	public void setUnitStr(String unitStr) {
		this.unitStr = unitStr;
	}

	public String getDirection() {
		return direction;
	}

	public void setDirection(String direction) {
		this.direction = direction;
	}

	public String getDirectionStr() {
		return directionStr;
	}

	public void setDirectionStr(String directionStr) {
		this.directionStr = directionStr;
	}

	public String getGenderStr() {
		return genderStr;
	}

	public void setGenderStr(String genderStr) {
		this.genderStr = genderStr;
	}

}
