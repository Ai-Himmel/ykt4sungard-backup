package org.king.monitor.domain;

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
	public TCard(long cardno) {
		super(cardno);
	}

	/** full constructor */
	public TCard(long cardno, long cardtype, long feetype, String stuempno,
			long custid, String showcardno, String cardphyid, String cardpwd,
			String status, String cardstatus, String expiredate,
			String lossdate, String opendate, String closedate,
			String lastsaved, String lossflag, String lossefttime,
			String frozedate) {
		super(cardno, cardtype, feetype, stuempno, custid, showcardno,
				cardphyid, cardpwd, status, cardstatus, expiredate, lossdate,
				opendate, closedate, lastsaved, lossflag, lossefttime,
				frozedate);
	}

}
