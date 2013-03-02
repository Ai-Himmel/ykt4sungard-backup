/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassStatistic.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-5-12     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

public class ClassStatistic {
	
	public String collegeName;
	public String className;
	public int stuNumber;
	public int stuMale;
	public int stuFemale;
	

	/**
	 * @return Returns the stuFemale.
	 */
	public int getStuFemale() {
		return stuFemale;
	}


	/**
	 * @param stuFemale The stuFemale to set.
	 */
	public void setStuFemale(int stuFemale) {
		this.stuFemale = stuFemale;
	}


	/**
	 * @return Returns the stuMale.
	 */
	public int getStuMale() {
		return stuMale;
	}


	/**
	 * @param stuMale The stuMale to set.
	 */
	public void setStuMale(int stuMale) {
		this.stuMale = stuMale;
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
	 * @return Returns the stuNumber.
	 */
	public int getStuNumber() {
		return stuNumber;
	}


	/**
	 * @param stuNumber The stuNumber to set.
	 */
	public void setStuNumber(int stuNumber) {
		this.stuNumber = stuNumber;
	}


	public ClassStatistic(String collegeName, String className, int stuNumber, int stuMale, int stuFemale) {
		this.collegeName = collegeName;
		this.className = className;
		this.stuNumber = stuNumber;
		this.stuMale = stuMale;
		this.stuFemale = stuFemale;
	}


	
	

}
