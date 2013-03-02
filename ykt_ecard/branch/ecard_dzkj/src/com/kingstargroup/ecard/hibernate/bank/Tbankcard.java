package com.kingstargroup.ecard.hibernate.bank;

/**
 * Tbankcard entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class Tbankcard extends AbstractTbankcard implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public Tbankcard() {
	}

	/** minimal constructor */
	public Tbankcard(TbankcardId id) {
		super(id);
	}

	/** full constructor */
	public Tbankcard(TbankcardId id, String bankcardno, String batchno,
			String createddate, String lastsaved) {
		super(id, bankcardno, batchno, createddate, lastsaved);
	}

}
