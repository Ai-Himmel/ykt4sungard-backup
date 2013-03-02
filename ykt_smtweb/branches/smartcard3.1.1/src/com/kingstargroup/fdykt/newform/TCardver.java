package com.kingstargroup.fdykt.newform;

/**
 * TCardver entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TCardver extends AbstractTCardver implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCardver() {
	}

	/** minimal constructor */
	public TCardver(String cardverno) {
		super(cardverno);
	}

	/** full constructor */
	public TCardver(String cardverno, String accdate, Long termid,
			Long termseqno, Long cardno, String cardphyid, String stuempno,
			Long cardvertype, String adddelflag, String status) {
		super(cardverno, accdate, termid, termseqno, cardno, cardphyid,
				stuempno, cardvertype, adddelflag, status);
	}

}
