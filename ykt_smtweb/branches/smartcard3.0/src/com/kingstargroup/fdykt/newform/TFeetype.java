package com.kingstargroup.fdykt.newform;

/**
 * TFeetype entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TFeetype extends AbstractTFeetype implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TFeetype() {
	}

	/** minimal constructor */
	public TFeetype(Long feetype) {
		super(feetype);
	}

	/** full constructor */
	public TFeetype(Long feetype, String feename, String boardfeeflag,
			String useflag, String remark) {
		super(feetype, feename, boardfeeflag, useflag, remark);
	}

}
