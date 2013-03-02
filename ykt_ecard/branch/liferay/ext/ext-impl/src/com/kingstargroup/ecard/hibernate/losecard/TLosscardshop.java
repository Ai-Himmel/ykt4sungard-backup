package com.kingstargroup.ecard.hibernate.losecard;
// default package

/**
 * TLosscardshop entity. @author MyEclipse Persistence Tools
 */
public class TLosscardshop extends AbstractTLosscardshop implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TLosscardshop() {
	}

	/** minimal constructor */
	public TLosscardshop(String shopcode) {
		super(shopcode);
	}

	/** full constructor */
	public TLosscardshop(String shopcode, String shopname, String addr,
			String tel, String getcardplace, String lastsaved) {
		super(shopcode, shopname, addr, tel, getcardplace, lastsaved);
	}

}
