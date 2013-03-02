package org.king.check.domain;

import java.math.BigDecimal;


/**
 * TClassCheckTermRpt entity. @author MyEclipse Persistence Tools
 */
public class TClassCheckTermRpt extends AbstractTClassCheckTermRpt implements java.io.Serializable {

    // Constructors

    /** default constructor */
    public TClassCheckTermRpt() {
    }

	/** minimal constructor */
    public TClassCheckTermRpt(String id) {
        super(id);        
    }

	public TClassCheckTermRpt(String id, TTerm term, TArea area,
			Department deptclass, TCourse course, Integer classPeopleNum,
			Integer checkNum, double checkRate, Integer comeLateNum,
			Integer leaveEarlyNum, double comeLateRate, double leaveEarlyRate,
			String checkDate, String reportDate) {
		super(id, term, area, deptclass, course, classPeopleNum, checkNum, checkRate,
				comeLateNum, leaveEarlyNum, comeLateRate, leaveEarlyRate, checkDate,
				reportDate);
		// TODO Auto-generated constructor stub
	}
    
    /** full constructor */
   
}
