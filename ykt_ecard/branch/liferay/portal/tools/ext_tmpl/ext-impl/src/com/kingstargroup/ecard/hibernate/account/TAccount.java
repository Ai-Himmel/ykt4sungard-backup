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
	public TAccount(String accno, Long acctype, String accname, String subjno,
			String accpwd, Long custid, Long cardno, Long purseno,
			Double daycostmaxamt, Double cardmaxbal, String stoppayflag,
			String status, Double ydaybal, Double ydayavailbal,
			Double ydayfrozebal, Double balance, Double availbal,
			Double frozebal, Double subsidybal, Double foregift,
			Long lastcardcnt, Double lastcardbal, Long subsidyno,
			Long lastsubsidyno, Double daycostamt, String lasttransdate,
			String lastaccdate, String opendate, String closedate,
			Double singlemaxamt) {
		super(accno, acctype, accname, subjno, accpwd, custid, cardno, purseno,
				daycostmaxamt, cardmaxbal, stoppayflag, status, ydaybal,
				ydayavailbal, ydayfrozebal, balance, availbal, frozebal,
				subsidybal, foregift, lastcardcnt, lastcardbal, subsidyno,
				lastsubsidyno, daycostamt, lasttransdate, lastaccdate,
				opendate, closedate, singlemaxamt);
	}

}
