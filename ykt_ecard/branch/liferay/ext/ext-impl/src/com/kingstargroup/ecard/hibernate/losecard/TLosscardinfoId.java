package com.kingstargroup.ecard.hibernate.losecard;
// default package

/**
 * TLosscardinfoId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TLosscardinfoId extends AbstractTLosscardinfoId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TLosscardinfoId() {
	}

	/** full constructor */
	public TLosscardinfoId(long cardno, String shopcode, String regdate) {
		super(cardno, shopcode, regdate);
	}

}
