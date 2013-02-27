package org.king.monitor.domain;

/**
 * TAccount entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TAccount extends AbstractTAccount implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TAccount() {
	}

	/** minimal constructor */
	public TAccount(String accno) {
		super(accno);
	}

	/** full constructor */
	public TAccount(String accno, String accname, String subjno, String accpwd,
			long custid, long cardno, long purseno, double singlemaxamt,
			double daycostmaxamt, double cardmaxbal, String status,
			double ydaybal, double balance, double availbal, double frozebal,
			double subsidybal, double foregift, long lastcardcnt,
			double lastcardbal, long subsidyno, double lastsubsidyamt,
			long lastsubsidyno, double daycostamt, String lasttransdate,
			String lastaccdate, String opendate, String closedate) {
		super(accno, accname, subjno, accpwd, custid, cardno, purseno,
				singlemaxamt, daycostmaxamt, cardmaxbal, status, ydaybal,
				balance, availbal, frozebal, subsidybal, foregift, lastcardcnt,
				lastcardbal, subsidyno, lastsubsidyamt, lastsubsidyno,
				daycostamt, lasttransdate, lastaccdate, opendate, closedate);
	}

}
