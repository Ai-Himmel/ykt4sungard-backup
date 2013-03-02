package org.king.dormitorymanage.web.help;

public class DormitoryStatistic {
	
	public String areaId;	
	public String locationId;
	public String dormitoryId;
	public String area;
	public String location;
	public String dormitory;
	public int totalNumber;
	public int studentInCount;
	public int nonCount;
	
	public double areaSort =0.0;	
	public double locationSort =0.0;
	public double dormitorySort =0.0;	
	
	public DormitoryStatistic(String locationId, String dormitoryId,
			String location, String dormitory,
			int totalNumber, int studentInCount, 
			int nonCount, String areaId, String area,
			double areaSort,double locationSort,double dormitorySort) {
		this.locationId = locationId;
		this.dormitoryId = dormitoryId;
		this.location = location;
		this.dormitory = dormitory;
		this.totalNumber = totalNumber;
		this.studentInCount = studentInCount;
		this.nonCount = nonCount;
		this.areaId = areaId;
		this.area = area;
		this.areaSort = areaSort;
		this.locationSort = locationSort;
		this.dormitorySort = dormitorySort;
	}
	/**
	 * @return Returns the dormitory.
	 */
	public String getDormitory() {
		return dormitory;
	}
	/**
	 * @param dormitory The dormitory to set.
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
	 * @param dormitoryId The dormitoryId to set.
	 */
	public void setDormitoryId(String dormitoryId) {
		this.dormitoryId = dormitoryId;
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
	 * @return Returns the locationId.
	 */
	public String getLocationId() {
		return locationId;
	}
	/**
	 * @param locationId The locationId to set.
	 */
	public void setLocationId(String locationId) {
		this.locationId = locationId;
	}
	/**
	 * @return Returns the nonCount.
	 */
	public int getNonCount() {
		return nonCount;
	}
	/**
	 * @param nonCount The nonCount to set.
	 */
	public void setNonCount(int nonCount) {
		this.nonCount = nonCount;
	}
	/**
	 * @return Returns the studentInCount.
	 */
	public int getStudentInCount() {
		return studentInCount;
	}
	/**
	 * @param studentInCount The studentInCount to set.
	 */
	public void setStudentInCount(int studentInCount) {
		this.studentInCount = studentInCount;
	}
	/**
	 * @return Returns the totalNumber.
	 */
	public int getTotalNumber() {
		return totalNumber;
	}
	/**
	 * @param totalNumber The totalNumber to set.
	 */
	public void setTotalNumber(int totalNumber) {
		this.totalNumber = totalNumber;
	}
	public String getArea() {
		return area;
	}
	public void setArea(String area) {
		this.area = area;
	}
	public String getAreaId() {
		return areaId;
	}
	public void setAreaId(String areaId) {
		this.areaId = areaId;
	}
	public double getAreaSort() {
		return areaSort;
	}
	public void setAreaSort(double areaSort) {
		this.areaSort = areaSort;
	}
	public double getDormitorySort() {
		return dormitorySort;
	}
	public void setDormitorySort(double dormitorySort) {
		this.dormitorySort = dormitorySort;
	}
	public double getLocationSort() {
		return locationSort;
	}
	public void setLocationSort(double locationSort) {
		this.locationSort = locationSort;
	}
	
	
	
	
	
}
