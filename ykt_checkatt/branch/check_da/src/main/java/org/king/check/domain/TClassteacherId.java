package org.king.check.domain;

import java.math.BigDecimal;

/**
 * TClassteacherId entity. @author MyEclipse Persistence Tools
 */
public class TClassteacherId extends AbstractTClassteacherId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TClassteacherId() {
	}

	/** full constructor */
	public TClassteacherId(String classid, BigDecimal custid) {
		super(classid, custid);
	}

}
