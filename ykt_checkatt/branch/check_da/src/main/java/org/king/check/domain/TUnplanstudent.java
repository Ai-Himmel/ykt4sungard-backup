package org.king.check.domain;

/**
 * TUnplanstudent entity. @author MyEclipse Persistence Tools
 */

public class TUnplanstudent  implements
		java.io.Serializable {

	// Fields

	private String id;
	private String stuempno;
	private String custname;
	private String classno;
	private String courseid;
	private String checkdate;
	private String checktime;
	private String usedate;
	private String reportdate;
	private Integer isactivate;
	private Integer comeLateNum;
	private Integer leaveEarlyNum;

	// Constructors

	/** default constructor */
	public TUnplanstudent() {
	}

	/** minimal constructor */
	public TUnplanstudent(String id) {
		this.id = id;
	}

	/** full constructor */
	public TUnplanstudent(String id, String stuempno, String custname,
			String classno, String courseid, String checkdate,
			String checktime, String usedate, String reportdate,
			Integer isactivate, Integer comeLateNum, Integer leaveEarlyNum) {
		this.id = id;
		this.stuempno = stuempno;
		this.custname = custname;
		this.classno = classno;
		this.courseid = courseid;
		this.checkdate = checkdate;
		this.checktime = checktime;
		this.usedate = usedate;
		this.reportdate = reportdate;
		this.isactivate = isactivate;
		this.comeLateNum = comeLateNum;
		this.leaveEarlyNum = leaveEarlyNum;
	}

	// Property accessors

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getStuempno() {
		return this.stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}

	public String getCustname() {
		return this.custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
	}

	public String getClassno() {
		return this.classno;
	}

	public void setClassno(String classno) {
		this.classno = classno;
	}

	public String getCourseid() {
		return this.courseid;
	}

	public void setCourseid(String courseid) {
		this.courseid = courseid;
	}

	public String getCheckdate() {
		return this.checkdate;
	}

	public void setCheckdate(String checkdate) {
		this.checkdate = checkdate;
	}

	public String getChecktime() {
		return this.checktime;
	}

	public void setChecktime(String checktime) {
		this.checktime = checktime;
	}

	public String getUsedate() {
		return this.usedate;
	}

	public void setUsedate(String usedate) {
		this.usedate = usedate;
	}

	public String getReportdate() {
		return this.reportdate;
	}

	public void setReportdate(String reportdate) {
		this.reportdate = reportdate;
	}

	public Integer getIsactivate() {
		return this.isactivate;
	}

	public void setIsactivate(Integer isactivate) {
		this.isactivate = isactivate;
	}

	public Integer getComeLateNum() {
		return this.comeLateNum;
	}

	public void setComeLateNum(Integer comeLateNum) {
		this.comeLateNum = comeLateNum;
	}

	public Integer getLeaveEarlyNum() {
		return this.leaveEarlyNum;
	}

	public void setLeaveEarlyNum(Integer leaveEarlyNum) {
		this.leaveEarlyNum = leaveEarlyNum;
	}

}