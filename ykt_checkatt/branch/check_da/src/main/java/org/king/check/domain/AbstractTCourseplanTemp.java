package org.king.check.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-3
 */
public class AbstractTCourseplanTemp implements java.io.Serializable {
    private Long id;
    private String term;
    private String faculty;
    private String area;
    private String building;
    private String room;
    private String course;
    private String stuempno;
    private String custname;
    private String deptname;
    private String deptcode;
    private String week;
    private String beginWeek;
    private String endWeek;
    private String beginClass;
    private String endClass;
    private String ischeck;
    private String isopen;
    private String remark;
    /**状态分三种，0为未通过审核的历史课程计划信息，1为系统自动同步生成的未审核课程计划信息，2为人工预览生成的未审核课程计划信息**/
    private String status;
    private String checkInfo;
    private String syncDate;

    public AbstractTCourseplanTemp() {
    }

    public AbstractTCourseplanTemp(Long id, String term, String faculty, String area, String building, String room, String course, String stuempno, String custname, String deptname, String deptcode, String week, String beginWeek, String endWeek, String beginClass, String endClass, String ischeck, String isopen, String remark, String status, String checkInfo, String syncDate) {
        this.id = id;
        this.term = term;
        this.faculty = faculty;
        this.area = area;
        this.building = building;
        this.room = room;
        this.course = course;
        this.stuempno = stuempno;
        this.custname = custname;
        this.deptname = deptname;
        this.deptcode = deptcode;
        this.week = week;
        this.beginWeek = beginWeek;
        this.endWeek = endWeek;
        this.beginClass = beginClass;
        this.endClass = endClass;
        this.ischeck = ischeck;
        this.isopen = isopen;
        this.remark = remark;
        this.status = status;
        this.checkInfo = checkInfo;
        this.syncDate = syncDate;
    }

    public Long getId() {
        return id;
    }

    public void setId(Long id) {
        this.id = id;
    }

    public String getTerm() {
        return term;
    }

    public void setTerm(String term) {
        this.term = term;
    }

    public String getFaculty() {
        return faculty;
    }

    public void setFaculty(String faculty) {
        this.faculty = faculty;
    }

    public String getArea() {
        return area;
    }

    public void setArea(String area) {
        this.area = area;
    }

    public String getBuilding() {
        return building;
    }

    public void setBuilding(String building) {
        this.building = building;
    }

    public String getRoom() {
        return room;
    }

    public void setRoom(String room) {
        this.room = room;
    }

    public String getCourse() {
        return course;
    }

    public void setCourse(String course) {
        this.course = course;
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

    public String getDeptname() {
        return deptname;
    }

    public void setDeptname(String deptname) {
        this.deptname = deptname;
    }

    public String getDeptcode() {
        return deptcode;
    }

    public void setDeptcode(String deptcode) {
        this.deptcode = deptcode;
    }

    public String getWeek() {
        return week;
    }

    public void setWeek(String week) {
        this.week = week;
    }

    public String getBeginWeek() {
        return beginWeek;
    }

    public void setBeginWeek(String beginWeek) {
        this.beginWeek = beginWeek;
    }

    public String getEndWeek() {
        return endWeek;
    }

    public void setEndWeek(String endWeek) {
        this.endWeek = endWeek;
    }

    public String getBeginClass() {
        return beginClass;
    }

    public void setBeginClass(String beginClass) {
        this.beginClass = beginClass;
    }

    public String getEndClass() {
        return endClass;
    }

    public void setEndClass(String endClass) {
        this.endClass = endClass;
    }

    public String getIscheck() {
        return ischeck;
    }

    public void setIscheck(String ischeck) {
        this.ischeck = ischeck;
    }

    public String getIsopen() {
        return isopen;
    }

    public void setIsopen(String isopen) {
        this.isopen = isopen;
    }

    public String getRemark() {
        return remark;
    }

    public void setRemark(String remark) {
        this.remark = remark;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public String getCheckInfo() {
        return checkInfo;
    }

    public void setCheckInfo(String checkInfo) {
        this.checkInfo = checkInfo;
    }

    public String getSyncDate() {
        return syncDate;
    }

    public void setSyncDate(String syncDate) {
        this.syncDate = syncDate;
    }
}
