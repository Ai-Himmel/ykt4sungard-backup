package com.kingstargroup.ecard.hibernate.losecard;
// default package

/**
 * TLosscardinfo entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TLosscardinfo extends AbstractTLosscardinfo implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TLosscardinfo() {
	}

	/** minimal constructor */
	public TLosscardinfo(TLosscardinfoId id) {
		super(id);
	}

	/** full constructor */
	public TLosscardinfo(TLosscardinfoId id, String cardphyid, String regtime,
			long status, String enddate, String getcardplace, String tel,
			String addr, long idtype, String idno, String getdate,
			String gettime, String remark) {
		super(id, cardphyid, regtime, status, enddate, getcardplace, tel, addr,
				idtype, idno, getdate, gettime, remark);
	}

}
