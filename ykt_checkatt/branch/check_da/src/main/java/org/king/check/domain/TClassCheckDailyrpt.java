package org.king.check.domain;



/**
 * TClassCheckDailyrpt entity. @author MyEclipse Persistence Tools
 */
public class TClassCheckDailyrpt extends AbstractTClassCheckDailyrpt implements
		java.io.Serializable {

	// Constructors

	public TClassCheckDailyrpt(String id, Department deptclass, TCourse course,
			Integer classPeopleNum, Integer checkNum, double checkRate,
			Integer comeLateNum, Integer leaveEarlyNum, double comeLateRate,
			double leaveEarlyRate, String checkDate, String reportDate,
			TTerm term, TArea area) {
		super(id, deptclass, course, classPeopleNum, checkNum, checkRate, comeLateNum,
				leaveEarlyNum, comeLateRate, leaveEarlyRate, checkDate, reportDate,
				term, area);
		// TODO Auto-generated constructor stub
	}

	/** default constructor */
	public TClassCheckDailyrpt() {
	}

	/** minimal constructor */
	public TClassCheckDailyrpt(String id) {
		super(id);
	}


	
}
