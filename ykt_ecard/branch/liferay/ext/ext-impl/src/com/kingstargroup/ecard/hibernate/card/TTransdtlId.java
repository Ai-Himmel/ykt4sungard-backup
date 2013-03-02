package com.kingstargroup.ecard.hibernate.card;

/**
 * TTransdtlId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TTransdtlId extends AbstractTTransdtlId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TTransdtlId() {
	}

	/** full constructor */
	public TTransdtlId(String accdate, Long termid, Long termseqno) {
		super(accdate, termid, termseqno);
	}

}
