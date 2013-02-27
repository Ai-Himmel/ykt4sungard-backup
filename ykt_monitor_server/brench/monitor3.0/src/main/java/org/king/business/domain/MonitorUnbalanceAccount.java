package org.king.business.domain;


/**
 * MonitorUnbalanceAccount entity. @author MyEclipse Persistence Tools
 */
public class MonitorUnbalanceAccount extends AbstractMonitorUnbalanceAccount
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorUnbalanceAccount() {
	}

	/** full constructor */
	public MonitorUnbalanceAccount(String accname, Integer custid,
			Integer cardno, Integer purseno, Double availbal,
			Double cardbal, Integer dpscnt, Integer paycnt,
			String lasttransdate, String enterdate, String analysedate,
			Integer lastdate, Double unbalanceamount, Double largestubamount) {
		super(accname, custid, cardno, purseno, availbal, cardbal, dpscnt,
				paycnt, lasttransdate, enterdate, analysedate, lastdate,
				unbalanceamount, largestubamount);
	}

}
