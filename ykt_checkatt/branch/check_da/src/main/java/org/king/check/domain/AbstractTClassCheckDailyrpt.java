package org.king.check.domain;


/**
 * AbstractTClassCheckDailyrpt entity provides the base persistence definition
 * of the TClassCheckDailyrpt entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTClassCheckDailyrpt 
		implements java.io.Serializable {

	// Fields

	private String id;
	private Department deptclass;
	private TCourse course;
	private Integer classPeopleNum;
	private Integer checkNum;
	private double checkRate;
	private Integer comeLateNum;
	private Integer leaveEarlyNum;
	private double comeLateRate;
	private double leaveEarlyRate;
	private String checkDate;
	private String reportDate;
	private TTerm term;
	private TArea area;

	// Constructors

	/** default constructor */
	public AbstractTClassCheckDailyrpt() {
	}

	/** minimal constructor */
	public AbstractTClassCheckDailyrpt(String id) {
		this.id = id;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public Department getDeptclass() {
		return deptclass;
	}

	public void setDeptclass(Department deptclass) {
		this.deptclass = deptclass;
	}

	public TCourse getCourse() {
		return course;
	}

	public void setCourse(TCourse course) {
		this.course = course;
	}

	public Integer getClassPeopleNum() {
		return classPeopleNum;
	}

	public void setClassPeopleNum(Integer classPeopleNum) {
		this.classPeopleNum = classPeopleNum;
	}

	public Integer getCheckNum() {
		return checkNum;
	}

	public void setCheckNum(Integer checkNum) {
		this.checkNum = checkNum;
	}

	public double getCheckRate() {
		return checkRate;
	}

	public void setCheckRate(double checkRate) {
		this.checkRate = checkRate;
	}

	public Integer getComeLateNum() {
		return comeLateNum;
	}

	public void setComeLateNum(Integer comeLateNum) {
		this.comeLateNum = comeLateNum;
	}

	public Integer getLeaveEarlyNum() {
		return leaveEarlyNum;
	}

	public void setLeaveEarlyNum(Integer leaveEarlyNum) {
		this.leaveEarlyNum = leaveEarlyNum;
	}

	public double getComeLateRate() {
		return comeLateRate;
	}

	public void setComeLateRate(double comeLateRate) {
		this.comeLateRate = comeLateRate;
	}

	public double getLeaveEarlyRate() {
		return leaveEarlyRate;
	}

	public void setLeaveEarlyRate(double leaveEarlyRate) {
		this.leaveEarlyRate = leaveEarlyRate;
	}

	public String getCheckDate() {
		return checkDate;
	}

	public void setCheckDate(String checkDate) {
		this.checkDate = checkDate;
	}

	public String getReportDate() {
		return reportDate;
	}

	public void setReportDate(String reportDate) {
		this.reportDate = reportDate;
	}

	public TTerm getTerm() {
		return term;
	}

	public void setTerm(TTerm term) {
		this.term = term;
	}

	public TArea getArea() {
		return area;
	}

	public void setArea(TArea area) {
		this.area = area;
	}

	public AbstractTClassCheckDailyrpt(String id, Department deptclass,
			TCourse course, Integer classPeopleNum, Integer checkNum,
			double checkRate, Integer comeLateNum, Integer leaveEarlyNum,
			double comeLateRate, double leaveEarlyRate, String checkDate,
			String reportDate, TTerm term, TArea area) {
		this.id = id;
		this.deptclass = deptclass;
		this.course = course;
		this.classPeopleNum = classPeopleNum;
		this.checkNum = checkNum;
		this.checkRate = checkRate;
		this.comeLateNum = comeLateNum;
		this.leaveEarlyNum = leaveEarlyNum;
		this.comeLateRate = comeLateRate;
		this.leaveEarlyRate = leaveEarlyRate;
		this.checkDate = checkDate;
		this.reportDate = reportDate;
		this.term = term;
		this.area = area;
	}

}