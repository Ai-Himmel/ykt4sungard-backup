package org.king.monitor.domain;

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
	public TCardver(String cardverno, String accdate, long termid,
			long termseqno, long cardno, String cardphyid, long cardvertype,
			String adddelflag, String status) {
		super(cardverno, accdate, termid, termseqno, cardno, cardphyid,
				cardvertype, adddelflag, status);
	}

}
