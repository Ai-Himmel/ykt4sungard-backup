/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: AbroadClasses.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-6-2     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

public class AbroadClasses {

	public String classId;	
	public String classNo;
	public String className;
	public String collegeName;	
	public String managerName;
	/**
	 * @return Returns the classId.
	 */
	public String getClassId() {
		return classId;
	}
	/**
	 * @param classId The classId to set.
	 */
	public void setClassId(String classId) {
		this.classId = classId;
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
	 * @return Returns the classNo.
	 */
	public String getClassNo() {
		return classNo;
	}
	/**
	 * @param classNo The classNo to set.
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
	 * @param collegeName The collegeName to set.
	 */
	public void setCollegeName(String collegeName) {
		this.collegeName = collegeName;
	}
	/**
	 * @return Returns the managerName.
	 */
	public String getManagerName() {
		return managerName;
	}
	/**
	 * @param managerName The managerName to set.
	 */
	public void setManagerName(String managerName) {
		this.managerName = managerName;
	}
	public AbroadClasses(String classId, String classNo, String className, String collegeName, String managerName) {
		super();
		// TODO Auto-generated constructor stub
		this.classId = classId;
		this.classNo = classNo;
		this.className = className;
		this.collegeName = collegeName;
		this.managerName = managerName;
	}
	
	
	
}
