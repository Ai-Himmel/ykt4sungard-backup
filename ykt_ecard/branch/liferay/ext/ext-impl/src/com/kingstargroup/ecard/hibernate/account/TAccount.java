package com.kingstargroup.ecard.hibernate.account;

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
			Long custid, Long cardno, Long purseno, Double singlemaxamt,
			Double daycostmaxamt, Double cardmaxbal, String status,
			Double ydaybal, Double balance, Double availbal, Double frozebal,
			Double subsidybal, Double foregift, Long lastcardcnt,
			Double lastcardbal, Long subsidyno, Double lastsubsidyamt,
			Long lastsubsidyno, Double daycostamt, String lasttransdate,
			String lastaccdate, String opendate, String closedate) {
		super(accno, accname, subjno, accpwd, custid, cardno, purseno,
				singlemaxamt, daycostmaxamt, cardmaxbal, status, ydaybal,
				balance, availbal, frozebal, subsidybal, foregift, lastcardcnt,
				lastcardbal, subsidyno, lastsubsidyamt, lastsubsidyno,
				daycostamt, lasttransdate, lastaccdate, opendate, closedate);
	}

}
