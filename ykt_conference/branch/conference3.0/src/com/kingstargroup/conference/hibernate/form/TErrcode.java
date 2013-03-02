package com.kingstargroup.conference.hibernate.form;

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
	public TErrcode(long errcode) {
		super(errcode);
	}

	/** full constructor */
	public TErrcode(long errcode, String errmsg) {
		super(errcode, errmsg);
	}

}
