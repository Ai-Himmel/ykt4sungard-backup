package com.kingstargroup.ecard.hibernate.card;

/**
 * TPosdtlId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TPosdtlId extends AbstractTPosdtlId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TPosdtlId() {
	}

	/** full constructor */
	public TPosdtlId(String transdate, String devphyid, Long devseqno) {
		super(transdate, devphyid, devseqno);
	}

}
