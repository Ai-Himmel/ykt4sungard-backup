package org.king.check.domain;

/**
 * AbstractTTeacherTermRpt entity provides the base persistence definition of the TTeacherTermRpt entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTeacherTermRpt  implements java.io.Serializable {


    // Fields    

     private String id;
     private TTerm term;
 	 private TArea area;
     private TCourse course;
     private String stuempNo;
     private String custName;
     private Integer courseNum;
     private Integer checkNum;
     private double checkRate;
     private Integer comeLateNum;
     private Integer leaveEarlyNum;
     private double comeLateRate;
     private double leaveEarlyRate;
     private String checkDate;
     private String reportDate;


    // Constructors

    /** default constructor */
    public AbstractTTeacherTermRpt() {
    }

	/** minimal constructor */
    public AbstractTTeacherTermRpt(String id) {
        this.id = id;
    }
    
    

	public AbstractTTeacherTermRpt(String id, TTerm term, TArea area,
			TCourse course, String stuempNo, String custName,
			java.lang.Integer courseNum, java.lang.Integer checkNum,
			double checkRate, java.lang.Integer comeLateNum,
			java.lang.Integer leaveEarlyNum, double comeLateRate,
			double leaveEarlyRate, String checkDate, String reportDate) {
		super();
		this.id = id;
		this.term = term;
		this.area = area;
		this.course = course;
		this.stuempNo = stuempNo;
		this.custName = custName;
		this.courseNum = courseNum;
		this.checkNum = checkNum;
		this.checkRate = checkRate;
		this.comeLateNum = comeLateNum;
		this.leaveEarlyNum = leaveEarlyNum;
		this.comeLateRate = comeLateRate;
		this.leaveEarlyRate = leaveEarlyRate;
		this.checkDate = checkDate;
		this.reportDate = reportDate;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
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

	public TCourse getCourse() {
		return course;
	}

	public void setCourse(TCourse course) {
		this.course = course;
	}

	public String getStuempNo() {
		return stuempNo;
	}

	public void setStuempNo(String stuempNo) {
		this.stuempNo = stuempNo;
	}

	public String getCustName() {
		return custName;
	}

	public void setCustName(String custName) {
		this.custName = custName;
	}

	public Integer getCourseNum() {
		return courseNum;
	}

	public void setCourseNum(Integer courseNum) {
		this.courseNum = courseNum;
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
    
    







}