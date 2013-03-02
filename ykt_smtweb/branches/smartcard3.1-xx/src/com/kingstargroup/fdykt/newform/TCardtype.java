package com.kingstargroup.fdykt.newform;

/**
 * TCardtype entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TCardtype extends AbstractTCardtype implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCardtype() {
	}

	/** minimal constructor */
	public TCardtype(Long cardtype) {
		super(cardtype);
	}

	/** full constructor */
	public TCardtype(Long cardtype, String cardtypename, String anonymflag,
			Long feetype, Double cardcostfee, String reuseable,
			String renewable, String multipurse, String fixdayflag,
			Long fixdaycnt, String useflag, String purpose) {
		super(cardtype, cardtypename, anonymflag, feetype, cardcostfee,
				reuseable, renewable, multipurse, fixdayflag, fixdaycnt,
				useflag, purpose);
	}

}
