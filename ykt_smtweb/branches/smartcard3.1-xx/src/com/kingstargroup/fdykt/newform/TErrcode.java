package com.kingstargroup.fdykt.newform;

/**
 * TErrcode entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TErrcode extends AbstractTErrcode implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TErrcode() {
	}

	/** minimal constructor */
	public TErrcode(Long errcode) {
		super(errcode);
	}

	/** full constructor */
	public TErrcode(Long errcode, String errmsg) {
		super(errcode, errmsg);
	}

}
