package org.king.check.domain;

import java.math.BigDecimal;

/**
 * TCourse entity. @author MyEclipse Persistence Tools
 */
public class TCourse extends AbstractTCourse implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCourse() {
	}

	/** minimal constructor */
	public TCourse(String courseid) {
		super(courseid);
	}

	/** full constructor */
	public TCourse(String courseid, String coursename) {
		super(courseid, coursename);
	}

}
