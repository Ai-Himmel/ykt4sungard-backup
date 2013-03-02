package org.king.check.domain;

public class TodayStuCheckSearchDetail {
	private String areaname;
	private String stuempno;
	private String custname;
	private String courseid;
	private String coursename;
	private String deptcode;
	private String deptname;
	private String checktime;
	public TodayStuCheckSearchDetail(String stuempno, String custname,
			String courseid, String coursename, String deptcode,
			String deptname, String checktime) {
		super();
		this.stuempno = stuempno;
		this.custname = custname;
		this.courseid = courseid;
		this.coursename = coursename;
		this.deptcode = deptcode;
		this.deptname = deptname;
		this.checktime = checktime;
	}
	public String getStuempno() {
		return stuempno;
	}
	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}
	public String getCustname() {
		return custname;
	}
	public void setCustname(String custname) {
		this.custname = custname;
	}
	public String getCourseid() {
		return courseid;
	}
	public void setCourseid(String courseid) {
		this.courseid = courseid;
	}
	public String getCoursename() {
		return coursename;
	}
	public void setCoursename(String coursename) {
		this.coursename = coursename;
	}
	public String getDeptcode() {
		return deptcode;
	}
	public void setDeptcode(String deptcode) {
		this.deptcode = deptcode;
	}
	public String getDeptname() {
		return deptname;
	}
	public void setDeptname(String deptname) {
		this.deptname = deptname;
	}
	public String getChecktime() {
		return checktime;
	}
	public void setChecktime(String checktime) {
		this.checktime = checktime;
	}
	
	
}
