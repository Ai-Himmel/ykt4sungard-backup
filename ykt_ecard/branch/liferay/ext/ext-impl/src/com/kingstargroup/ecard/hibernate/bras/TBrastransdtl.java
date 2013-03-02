package com.kingstargroup.ecard.hibernate.bras;

/**
 * TBrastransdtl entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TBrastransdtl extends AbstractTBrastransdtl implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TBrastransdtl() {
	}

	/** minimal constructor */
	public TBrastransdtl(String refno) {
		super(refno);
	}

	/** full constructor */
	public TBrastransdtl(String refno, Long cardno, String stuempno,
			String custname, String oppaccno, String oppaccname,
			String transdate, String transtime, Long transtype, String summary,
			Double transamt, Long status, String remark, Long chkflag) {
		super(refno, cardno, stuempno, custname, oppaccno, oppaccname,
				transdate, transtime, transtype, summary, transamt, status,
				remark, chkflag);
	}

}
