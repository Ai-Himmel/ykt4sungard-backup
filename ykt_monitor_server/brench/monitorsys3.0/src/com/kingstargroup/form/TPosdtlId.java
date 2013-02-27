package com.kingstargroup.form;

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
	public TPosdtlId(String transdate, String devphyid, long devseqno) {
		super(transdate, devphyid, devseqno);
	}

}
