/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: NationDistributionInfo.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-5-15     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

public class NationDistributionInfo {
	
	public String collegeName;
	public String className;
	public int studentCount;
	public String nation;
	
	public NationDistributionInfo(String collegeName, String className, int studentCount, String nation) {
		this.collegeName = collegeName;
		this.className = className;
		this.studentCount = studentCount;
		this.nation = nation;
	}
	/**
	 * @return Returns the className.
	 */
	public String getClassName() {
		return className;
	}
	/**
	 * @param className The className to set.
	 */
	public void setClassName(String className) {
		this.className = className;
	}
	/**
	 * @return Returns the collegeName.
	 */
	public String getCollegeName() {
		return collegeName;
	}
	/**
	 * @param collegeName The collegeName to set.
	 */
	public void setCollegeName(String collegeName) {
		this.collegeName = collegeName;
	}
	/**
	 * @return Returns the nation.
	 */
	public String getNation() {
		return nation;
	}
	/**
	 * @param nation The nation to set.
	 */
	public void setNation(String nation) {
		this.nation = nation;
	}
	/**
	 * @return Returns the studentCount.
	 */
	public int getStudentCount() {
		return studentCount;
	}
	/**
	 * @param studentCount The studentCount to set.
	 */
	public void setStudentCount(int studentCount) {
		this.studentCount = studentCount;
	}
	
	

}
