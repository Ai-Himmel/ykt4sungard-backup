package org.king.business.domain;


/**
 * MonitorUnbalanceAccountHis entity. @author MyEclipse Persistence Tools
 */
public class MonitorUnbalanceAccountHis extends
		AbstractMonitorUnbalanceAccountHis implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorUnbalanceAccountHis() {
	}

	/** full constructor */
	public MonitorUnbalanceAccountHis(String accno, String accname,
			Integer custid, Integer cardno, Integer purseno,
			Double availbal, Double cardbal, Integer dpscnt,
			Integer paycnt, String lasttransdate, String enterdate,
			String analysedate, Integer lastdate, Double unbalanceamount,
			Double largestubamount) {
		super(accno, accname, custid, cardno, purseno, availbal, cardbal,
				dpscnt, paycnt, lasttransdate, enterdate, analysedate,
				lastdate, unbalanceamount, largestubamount);
	}

}
