package org.king.check.domain;

import java.math.BigDecimal;


/**
 * TStudentTermRpt entity. @author MyEclipse Persistence Tools
 */
public class TStudentTermRpt extends AbstractTStudentTermRpt implements java.io.Serializable {

    // Constructors

    /** default constructor */
    public TStudentTermRpt() {
    }

	/** minimal constructor */
    public TStudentTermRpt(String id) {
        super(id);        
    }

	public TStudentTermRpt(String id, TTerm term, TArea area,
			Department deptclass, TCourse course, String stuempNo,
			String custName, Integer courseNum, Integer checkNum,
			double checkRate, Integer comeLateNum, Integer leaveEarlyNum,
			double comeLateRate, double leaveEarlyRate, String checkDate,
			String reportDate) {
		super(id, term, area, deptclass, course, stuempNo, custName, courseNum,
				checkNum, checkRate, comeLateNum, leaveEarlyNum, comeLateRate,
				leaveEarlyRate, checkDate, reportDate);
		// TODO Auto-generated constructor stub
	}
    
    /** full constructor */
    
}
