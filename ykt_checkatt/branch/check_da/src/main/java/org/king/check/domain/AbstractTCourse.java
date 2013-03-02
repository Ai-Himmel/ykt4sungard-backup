package org.king.check.domain;

import java.math.BigDecimal;

/**
 * AbstractTCourse entity provides the base persistence definition of the
 * TCourse entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCourse  implements java.io.Serializable {

	// Fields

	private String courseid;
	private String coursename;

	// Constructors

	/** default constructor */
	public AbstractTCourse() {
	}

	/** minimal constructor */
	public AbstractTCourse(String courseid) {
		this.courseid = courseid;
	}

	/** full constructor */
	public AbstractTCourse(String courseid, String coursename) {
		this.courseid = courseid;
		this.coursename = coursename;
	}

	// Property accessors

	public String getCourseid() {
		return this.courseid;
	}

	public void setCourseid(String courseid) {
		this.courseid = courseid;
	}

	public String getCoursename() {
		return this.coursename;
	}

	public void setCoursename(String coursename) {
		this.coursename = coursename;
	}

}