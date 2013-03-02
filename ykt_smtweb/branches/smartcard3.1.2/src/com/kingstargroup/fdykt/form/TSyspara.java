package com.kingstargroup.fdykt.form;

/**
 * TSyspara entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TSyspara extends AbstractTSyspara implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TSyspara() {
	}

	/** minimal constructor */
	public TSyspara(Long paraid, String paraval) {
		super(paraid, paraval);
	}

	/** full constructor */
	public TSyspara(Long paraid, String paraval, String paraname,
			String paraunit, String displayflag, String remark) {
		super(paraid, paraval, paraname, paraunit, displayflag, remark);
	}

}
