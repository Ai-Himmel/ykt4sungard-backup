package org.king.check.domain;



/**
 * TTeaStuDailyrpt entity. @author MyEclipse Persistence Tools
 */
public class TTeaStuDailyRpt extends AbstractTTeaStuDailyRpt implements
		java.io.Serializable {


	/** default constructor */
	public TTeaStuDailyRpt() {
	}

	
	/** minimal constructor */
	public TTeaStuDailyRpt(String id) {
		super(id);
	}


	public TTeaStuDailyRpt(String id, Department deptclass, TCourse course,
			String stuempNo, String custName, Integer courseNum,
			Integer checkNum, double checkRate, Integer comeLateNum,
			Integer leaveEarlyNum, double comeLateRate, double leaveEarlyRate,
			String checkDate, String reportDate, TTerm term, TArea area,
			Integer custType,String useDate,String checkTime) {
		super(id, deptclass, course, stuempNo, custName, courseNum, checkNum,
				checkRate, comeLateNum, leaveEarlyNum, comeLateRate, leaveEarlyRate,
				checkDate, reportDate, term, area, custType,useDate,checkTime);
	}

}
