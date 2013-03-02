package org.king.check.domain;

public class TodayStuCheckSearch {
	private String id;
	private String areaname;
	private String stuempno;
	private String custname;
	private String courseid;
	private String coursename;
	private String deptcode;
	private String deptname;
	private String gardname;
	private String begintime;
	private String endtime;
	private Integer sharr;
	private Integer realarr;
	private Integer reallate;
	
	
	public String getGardname() {
		return gardname;
	}

	public void setGardname(String gardname) {
		this.gardname = gardname;
	}

    public TodayStuCheckSearch() {
    }

    public TodayStuCheckSearch(String id, String areaname, String stuempno,
			String custname, String courseid, String coursename,
			String deptcode, String deptname, String gardname, 
			String  begintime,String endtime,
			Integer sharr,
			Integer realarr, Integer reallate) {
		this.id = id;
		this.areaname = areaname;
		this.stuempno = stuempno;
		this.custname = custname;
		this.courseid = courseid;
		this.coursename = coursename;
		this.deptcode = deptcode;
		this.deptname = deptname;
		this.gardname = gardname;
		this.sharr = sharr;
		this.begintime = begintime;
		this.endtime = endtime;
		this.realarr = realarr;
		this.reallate = reallate;
	}

	public String getId() {
		return id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getBegintime() {
		return begintime;
	}

	public void setBegintime(String begintime) {
		this.begintime = begintime;
	}

	public String getEndtime() {
		return endtime;
	}

	public void setEndtime(String endtime) {
		this.endtime = endtime;
	}

	public String getAreaname() {
		return areaname;
	}

	public void setAreaname(String areaname) {
		this.areaname = areaname;
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
	public Integer getSharr() {
		return sharr;
	}
	public void setSharr(Integer sharr) {
		this.sharr = sharr;
	}
	public Integer getRealarr() {
		return realarr;
	}
	public void setRealarr(Integer realarr) {
		this.realarr = realarr;
	}
	public Integer getReallate() {
		return reallate;
	}
	public void setReallate(Integer reallate) {
		this.reallate = reallate;
	}
	
	
	
}
