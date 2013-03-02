package org.king.check.domain;

import java.math.BigDecimal;

/**
 * AbstractTTime entity provides the base persistence definition of the TTime
 * entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTime  implements
		java.io.Serializable {

	// Fields

	private Integer classNum;
	private String beginTime;
	private String endTime;

	// Constructors

	/** default constructor */
	public AbstractTTime() {
	}

	/** minimal constructor */
	public AbstractTTime(Integer classNum) {
		this.classNum = classNum;
	}

	/** full constructor */
	public AbstractTTime(Integer classNum, String beginTime, String endTime) {
		this.classNum = classNum;
		this.beginTime = beginTime;
		this.endTime = endTime;
	}

	// Property accessors

	public Integer getClassNum() {
		return this.classNum;
	}

	public void setClassNum(Integer classNum) {
		this.classNum = classNum;
	}

	public String getBeginTime() {
		return this.beginTime;
	}

	public void setBeginTime(String beginTime) {
		this.beginTime = beginTime;
	}

	public String getEndTime() {
		return this.endTime;
	}

	public void setEndTime(String endTime) {
		this.endTime = endTime;
	}

}