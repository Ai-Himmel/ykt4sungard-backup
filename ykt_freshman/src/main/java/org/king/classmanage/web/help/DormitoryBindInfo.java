package org.king.classmanage.web.help;

public class DormitoryBindInfo {
	public String dormitoryId;

	public String location;

	public String locationStr;

	public String dormitory;

	public String dormitoryStr;

	public String roomNumber;
	
	public String direction;

	public String gender;

	public int accomodation;

	public String classId;

	public DormitoryBindInfo(String dormitoryId, String location,
			String locationStr, String dormitory, String dormitoryStr,
			String roomNumber, String gender, int accomodation,
			String classId,String direction) {
		this.dormitoryId = dormitoryId;
		this.location = location;
		this.locationStr = locationStr;
		this.dormitory = dormitory;
		this.dormitoryStr = dormitoryStr;
		this.roomNumber = roomNumber;
		this.direction = direction;		
		this.gender = gender;
		this.accomodation = accomodation;
		this.classId = classId;
	}

	/**
	 * @return Returns the accomodation.
	 */
	public int getAccomodation() {
		return accomodation;
	}

	/**
	 * @param accomodation
	 *            The accomodation to set.
	 */
	public void setAccomodation(int accomodation) {
		this.accomodation = accomodation;
	}

	/**
	 * @return Returns the classId.
	 */
	public String getClassId() {
		return classId;
	}

	/**
	 * @param classId
	 *            The classId to set.
	 */
	public void setClassId(String classId) {
		this.classId = classId;
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
	 * @return Returns the dormitoryId.
	 */
	public String getDormitoryId() {
		return dormitoryId;
	}

	/**
	 * @param dormitoryId
	 *            The dormitoryId to set.
	 */
	public void setDormitoryId(String dormitoryId) {
		this.dormitoryId = dormitoryId;
	}

	/**
	 * @return Returns the dormitoryStr.
	 */
	public String getDormitoryStr() {
		return dormitoryStr;
	}

	/**
	 * @param dormitoryStr
	 *            The dormitoryStr to set.
	 */
	public void setDormitoryStr(String dormitoryStr) {
		this.dormitoryStr = dormitoryStr;
	}

	/**
	 * @return Returns the gender.
	 */
	public String getGender() {
		return gender;
	}

	/**
	 * @param gender
	 *            The gender to set.
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
	 * @param location
	 *            The location to set.
	 */
	public void setLocation(String location) {
		this.location = location;
	}

	/**
	 * @return Returns the locationStr.
	 */
	public String getLocationStr() {
		return locationStr;
	}

	/**
	 * @param locationStr
	 *            The locationStr to set.
	 */
	public void setLocationStr(String locationStr) {
		this.locationStr = locationStr;
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

	public String getDirection() {
		return direction;
	}

	public void setDirection(String direction) {
		this.direction = direction;
	}
	
	

}
