package com.kingstargroup.ecard.hibernate.card;

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
	public TSyspara(Long paraid) {
		super(paraid);
	}

	/** full constructor */
	public TSyspara(Long paraid, String paraval, String paraname,
			String paraunit, String displayflag, String remark, String lastsaved) {
		super(paraid, paraval, paraname, paraunit, displayflag, remark,
				lastsaved);
	}

}
