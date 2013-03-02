package org.king.check.domain;

import java.math.BigDecimal;


/**
 * TTeacherTermRpt entity. @author MyEclipse Persistence Tools
 */
public class TTeacherTermRpt extends AbstractTTeacherTermRpt implements java.io.Serializable {

    // Constructors

    /** default constructor */
    public TTeacherTermRpt() {
    }

	/** minimal constructor */
    public TTeacherTermRpt(String id) {
        super(id);        
    }

	public TTeacherTermRpt(String id, TTerm term, TArea area, TCourse course,
			String stuempNo, String custName, Integer courseNum,
			Integer checkNum, double checkRate, Integer comeLateNum,
			Integer leaveEarlyNum, double comeLateRate, double leaveEarlyRate,
			String checkDate, String reportDate) {
		super(id, term, area, course, stuempNo, custName, courseNum, checkNum,
				checkRate, comeLateNum, leaveEarlyNum, comeLateRate, leaveEarlyRate,
				checkDate, reportDate);
		// TODO Auto-generated constructor stub
	}
    
    /** full constructor */
  
   
}
