package com.kingstargroup.ecard.hibernate.card;

/**
 * TSyskey entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TSyskey extends AbstractTSyskey implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TSyskey() {
	}

	/** minimal constructor */
	public TSyskey(String keycode) {
		super(keycode);
	}

	/** full constructor */
	public TSyskey(String keycode, String keyname, Double keyval, Long maxval,
			String keytype) {
		super(keycode, keyname, keyval, maxval, keytype);
	}

}
