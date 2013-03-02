package org.king.check.domain;

import java.util.Set;


/**
 * TCourseplan entity. @author MyEclipse Persistence Tools
 */
public class TCourseplan extends AbstractTCourseplan {

	// Constructors

	/** default constructor */
	public TCourseplan() {
	}

	/** minimal constructor */
	public TCourseplan(String id) {
		super(id);
	}

	public TCourseplan(String id, TTerm term,Department dept,  TRoom room, TCourse course,
			String useDate, Integer useWeek, Integer week,
			Integer beginClassNum, Integer endClassNum, Integer beginWeek,
			Integer endWeek, String beginTime, String endTime,
			TCustomer customer, Integer status, String createTime,
			String creator, String className, Integer ischeck, Integer isopen,
			Set courseplanClass) {
		super(id, term,room, dept,course, useDate, useWeek, week, beginClassNum,
				endClassNum, beginWeek, endWeek, beginTime, endTime, customer, status,
				createTime, creator, className, ischeck, isopen, courseplanClass);
		// TODO Auto-generated constructor stub
	}

	
	/** full constructor */


}
