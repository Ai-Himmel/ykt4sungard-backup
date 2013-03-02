package org.king.check.domain;

import java.math.BigDecimal;

/**
 * TTime entity. @author MyEclipse Persistence Tools
 */
public class TTime extends AbstractTTime implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TTime() {
	}

	/** minimal constructor */
	public TTime(Integer classNum) {
		super(classNum);
	}

	/** full constructor */
	public TTime(Integer classNum, String beginTime, String endTime) {
		super(classNum, beginTime, endTime);
	}

}
