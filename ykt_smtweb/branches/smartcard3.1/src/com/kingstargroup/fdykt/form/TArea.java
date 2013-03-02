package com.kingstargroup.fdykt.form;

/**
 * TArea entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TArea extends AbstractTArea implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TArea() {
	}

	/** minimal constructor */
	public TArea(String areacode) {
		super(areacode);
	}

	/** full constructor */
	public TArea(String areacode, String areaname, String fareacode,
			Long arealevel, String addr, String remark) {
		super(areacode, areaname, fareacode, arealevel, addr, remark);
	}

}
