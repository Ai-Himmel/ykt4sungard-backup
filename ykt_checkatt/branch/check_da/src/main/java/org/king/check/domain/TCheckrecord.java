package org.king.check.domain;

import java.math.BigDecimal;

/**
 * TCheckrecord entity. @author MyEclipse Persistence Tools
 */
public class TCheckrecord extends AbstractTCheckrecord implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCheckrecord() {
	}

	/** minimal constructor */
	public TCheckrecord(TCheckrecordId id) {
		super(id);
	}

	public TCheckrecord(TCheckrecordId id, Integer custid, Integer cardno,
			String cardphyid, String punchtime, String coldate, Integer status) {
		super(id, custid, cardno, cardphyid, punchtime, coldate, status);
		// TODO Auto-generated constructor stub
	}

	/** full constructor */
	
	

}
