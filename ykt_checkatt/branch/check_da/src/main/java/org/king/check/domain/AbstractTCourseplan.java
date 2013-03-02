package org.king.check.domain;

import java.util.HashSet;
import java.util.Set;



/**
 * AbstractTCourseplan entity provides the base persistence definition of the
 * TCourseplan entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCourseplan  implements java.io.Serializable {

	// Fields

	private String Id;
	private TTerm term;
	private TRoom room;
	private TCourse course;
	private String useDate;
	private Integer useWeek;
	private Integer week;
    private Integer beginClassNum;
    private Integer endClassNum;
	private Integer beginWeek;
	private Integer endWeek;
	private String beginTime;
	private String endTime;
	private TCustomer customer;
	private Integer status;
    private String createTime;
	private String creator;
	private String className;
	private Integer ischeck;
	private Integer isopen;
	private Department dept;
	
	public Department getDept() {
		return dept;
	}

	public void setDept(Department dept) {
		this.dept = dept;
	}

	public Integer getIsopen() {
		return isopen;
	}

	public void setIsopen(Integer isopen) {
		this.isopen = isopen;
	}

	public Integer getIscheck() {
		return ischeck;
	}

	public void setIscheck(Integer ischeck) {
		this.ischeck = ischeck;
	}

	private Set  courseplanClass = new HashSet();
	
	public Integer getUseWeek() {
		return useWeek;
	}

	public void setUseWeek(Integer useWeek) {
		this.useWeek = useWeek;
	}

	// Constructors
	public String getClassName() {
		return className;
	}

	public void setClassName(String className) {
		this.className = className;
	}

	public Integer getWeek() {
		return week;
	}

	public Set getCourseplanClass() {
		return courseplanClass;
	}

	public void setCourseplanClass(Set courseplanClass) {
		this.courseplanClass = courseplanClass;
	}

	public void setWeek(Integer week) {
		this.week = week;
	}

	public Integer getBeginClassNum() {
		return beginClassNum;
	}

	public void setBeginClassNum(Integer beginClassNum) {
		this.beginClassNum = beginClassNum;
	}

	public Integer getEndClassNum() {
		return endClassNum;
	}

	public void setEndClassNum(Integer endClassNum) {
		this.endClassNum = endClassNum;
	}

	public String getCreateTime() {
		return createTime;
	}

	public void setCreateTime(String createTime) {
		this.createTime = createTime;
	}

	public Integer getBeginWeek() {
		return beginWeek;
	}

	public void setBeginWeek(Integer beginWeek) {
		this.beginWeek = beginWeek;
	}

	public Integer getEndWeek() {
		return endWeek;
	}

	public void setEndWeek(Integer endWeek) {
		this.endWeek = endWeek;
	}

	/** default constructor */
	public AbstractTCourseplan() {
	}

	/** mInImal constructor */
	public AbstractTCourseplan(String Id) {
		this.Id = Id;
	}

	

	public AbstractTCourseplan(String id, TTerm term, TRoom room,Department dept ,
			TCourse course, String useDate, Integer useWeek, Integer week,
			Integer beginClassNum, Integer endClassNum, Integer beginWeek,
			Integer endWeek, String beginTime, String endTime,
			TCustomer customer, Integer status, String createTime,
			String creator, String className, Integer ischeck, Integer isopen,
			Set courseplanClass) {
	
		this.Id = id;
		this.term = term;
		this.room = room;
		this.dept = dept;
		this.course = course;
		this.useDate = useDate;
		this.useWeek = useWeek;
		this.week = week;
		this.beginClassNum = beginClassNum;
		this.endClassNum = endClassNum;
		this.beginWeek = beginWeek;
		this.endWeek = endWeek;
		this.beginTime = beginTime;
		this.endTime = endTime;
		this.customer = customer;
		this.status = status;
		this.createTime = createTime;
		this.creator = creator;
		this.className = className;
		this.ischeck = ischeck;
		this.isopen = isopen;
		this.courseplanClass = courseplanClass;
	}

	public void setId(String Id) {
		this.Id = Id;
	}

	// Property accessors

	public String getId() {
		return this.Id;
	}
	public TTerm getTerm() {
		return term;
	}

	public void setTerm(TTerm term) {
		this.term = term;
	}

	public TRoom getRoom() {
		return room;
	}

	public void setRoom(TRoom room) {
		this.room = room;
	}

	public TCourse getCourse() {
		return course;
	}

	public void setCourse(TCourse course) {
		this.course = course;
	}

	public String getUseDate() {
		return useDate;
	}

	public void setUseDate(String useDate) {
		this.useDate = useDate;
	}


	public String getBeginTime() {
		return beginTime;
	}

	public void setBeginTime(String beginTime) {
		this.beginTime = beginTime;
	}


	public String getEndTime() {
		return endTime;
	}

	public void setEndTime(String endTime) {
		this.endTime = endTime;
	}


	public TCustomer getCustomer() {
		return customer;
	}

	public void setCustomer(TCustomer customer) {
		this.customer = customer;
	}

	public String getCreator() {
		return this.creator;
	}

	public void setCreator(String creator) {
		this.creator = creator;
	}

	public Integer getStatus() {
		return status;
	}

	public void setStatus(Integer status) {
		this.status = status;
	}


}