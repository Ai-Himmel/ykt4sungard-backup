package com.kingstargroup.fdykt.newform;

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
	public TBrastransdtl(String refno, Long cardno, String custname,
			String oppaccno, String oppaccname, String transdate,
			String transtime, Long transtype, String summary, Double transamt,
			Long status, String remark) {
		super(refno, cardno, custname, oppaccno, oppaccname, transdate,
				transtime, transtype, summary, transamt, status, remark);
	}

}
