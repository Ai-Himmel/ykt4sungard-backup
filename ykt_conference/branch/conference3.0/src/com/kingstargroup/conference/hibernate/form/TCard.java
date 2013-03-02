package com.kingstargroup.conference.hibernate.form;

/**
 * TCard entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TCard extends AbstractTCard implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCard() {
	}

	/** minimal constructor */
	public TCard(long cardno, String status, String lossflag, String frozeflag,
			String badflag) {
		super(cardno, status, lossflag, frozeflag, badflag);
	}

	/** full constructor */
	public TCard(long cardno, String accno, long cardtype, long feetype,
			long custid, String showcardno, String cardphyid, String cardpwd,
			String expiredate, String status, String lossflag, String lossdate,
			String lossefttime, String frozeflag, String frozedate,
			String badflag, String badtype, String baddate, String lockflag,
			String lockdate, String opendate, String closedate,
			String cardverno, String lastsaved) {
		super(cardno, accno, cardtype, feetype, custid, showcardno, cardphyid,
				cardpwd, expiredate, status, lossflag, lossdate, lossefttime,
				frozeflag, frozedate, badflag, badtype, baddate, lockflag,
				lockdate, opendate, closedate, cardverno, lastsaved);
	}

}
