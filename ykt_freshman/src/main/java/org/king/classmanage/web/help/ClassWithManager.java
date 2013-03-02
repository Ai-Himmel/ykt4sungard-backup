/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassWithManager.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-4-30     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

import org.king.classmanage.domain.Classmodel;

public class ClassWithManager extends Classmodel {
	public String collegeName;
	public String assistantName;
	public String tutor1Name;
	public String tutor1org;
	public String tutor2Name;
	public String tutor2org;

	
	/**
	 * @param yxCollege
	 * @param classNo
	 * @param className
	 * @param introduction
	 * @param yxStudents
	 */
	public ClassWithManager(String classId, String classNo, String className, String introduction,String collegeName) {
		this.setClassId(classId);
		this.setClassNo(classNo);
		this.setClassName(className);
		this.setIntroduction(introduction);
		this.collegeName= collegeName;
	}
	/**
	 * @return Returns the assistantName.
	 */
	public String getAssistantName() {
		return assistantName;
	}
	/**
	 * @param assistantName The assistantName to set.
	 */
	public void setAssistantName(String assistantName) {
		this.assistantName = assistantName;
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
	 * @return Returns the tutor1Name.
	 */
	public String getTutor1Name() {
		return tutor1Name;
	}
	/**
	 * @param tutor1Name The tutor1Name to set.
	 */
	public void setTutor1Name(String tutor1Name) {
		this.tutor1Name = tutor1Name;
	}
	/**
	 * @return Returns the tutor2Name.
	 */
	public String getTutor2Name() {
		return tutor2Name;
	}
	/**
	 * @param tutor2Name The tutor2Name to set.
	 */
	public void setTutor2Name(String tutor2Name) {
		this.tutor2Name = tutor2Name;
	}
	/**
	 * @return Returns the tutor1org.
	 */
	public String getTutor1org() {
		return tutor1org;
	}
	/**
	 * @param tutor1org The tutor1org to set.
	 */
	public void setTutor1org(String tutor1org) {
		this.tutor1org = tutor1org;
	}
	/**
	 * @return Returns the tutor2org.
	 */
	public String getTutor2org() {
		return tutor2org;
	}
	/**
	 * @param tutor2org The tutor2org to set.
	 */
	public void setTutor2org(String tutor2org) {
		this.tutor2org = tutor2org;
	}
	
	
	
}
