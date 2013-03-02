/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: ClassAlertHistory.java
 * Description: TODO
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期       操作者             操作内容简述
 * 创建  				 2006-5-10     何林青             
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */
package org.king.classmanage.web.help;

public class ClassAlertHistory {
	
	public String studentId;
	public String studentNo;
	public String stuName;
	public String classO;
	public String assistantO;
	public String collegeO;
	public String classN;
	public String assistantN;
	public String collegeN;
	public String operator;
	public String operatorTime;
	
	public ClassAlertHistory(String studentId, String studentNo, String stuName, String classO, String assistantO, String collegeO, String classN, String assistantN, String collegeN, String operator, String operatorTime) {
		this.studentId = studentId;
		this.studentNo = studentNo;
		this.stuName = stuName;
		this.classO = classO;
		this.assistantO = assistantO;
		this.collegeO = collegeO;
		this.classN = classN;
		this.assistantN = assistantN;
		this.collegeN = collegeN;
		this.operator = operator;
		this.operatorTime = operatorTime;
	}
	/**
	 * @return Returns the assistantN.
	 */
	public String getAssistantN() {
		return assistantN;
	}
	/**
	 * @param assistantN The assistantN to set.
	 */
	public void setAssistantN(String assistantN) {
		this.assistantN = assistantN;
	}
	/**
	 * @return Returns the assistantO.
	 */
	public String getAssistantO() {
		return assistantO;
	}
	/**
	 * @param assistantO The assistantO to set.
	 */
	public void setAssistantO(String assistantO) {
		this.assistantO = assistantO;
	}
	/**
	 * @return Returns the classN.
	 */
	public String getClassN() {
		return classN;
	}
	/**
	 * @param classN The classN to set.
	 */
	public void setClassN(String classN) {
		this.classN = classN;
	}
	/**
	 * @return Returns the classO.
	 */
	public String getClassO() {
		return classO;
	}
	/**
	 * @param classO The classO to set.
	 */
	public void setClassO(String classO) {
		this.classO = classO;
	}
	/**
	 * @return Returns the collegeN.
	 */
	public String getCollegeN() {
		return collegeN;
	}
	/**
	 * @param collegeN The collegeN to set.
	 */
	public void setCollegeN(String collegeN) {
		this.collegeN = collegeN;
	}
	/**
	 * @return Returns the collegeO.
	 */
	public String getCollegeO() {
		return collegeO;
	}
	/**
	 * @param collegeO The collegeO to set.
	 */
	public void setCollegeO(String collegeO) {
		this.collegeO = collegeO;
	}
	/**
	 * @return Returns the operator.
	 */
	public String getOperator() {
		return operator;
	}
	/**
	 * @param operator The operator to set.
	 */
	public void setOperator(String operator) {
		this.operator = operator;
	}
	/**
	 * @return Returns the operatorTime.
	 */
	public String getOperatorTime() {
		return operatorTime;
	}
	/**
	 * @param operatorTime The operatorTime to set.
	 */
	public void setOperatorTime(String operatorTime) {
		this.operatorTime = operatorTime;
	}
	/**
	 * @return Returns the studentId.
	 */
	public String getStudentId() {
		return studentId;
	}
	/**
	 * @param studentId The studentId to set.
	 */
	public void setStudentId(String studentId) {
		this.studentId = studentId;
	}
	/**
	 * @return Returns the studentNo.
	 */
	public String getStudentNo() {
		return studentNo;
	}
	/**
	 * @param studentNo The studentNo to set.
	 */
	public void setStudentNo(String studentNo) {
		this.studentNo = studentNo;
	}
	/**
	 * @return Returns the stuName.
	 */
	public String getStuName() {
		return stuName;
	}
	/**
	 * @param stuName The stuName to set.
	 */
	public void setStuName(String stuName) {
		this.stuName = stuName;
	}
	
	

}
