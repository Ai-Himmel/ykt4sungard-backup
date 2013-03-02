package com.kingstargroup.ecard.hibernate.shop;

/**
 * TShop entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TShop extends AbstractTShop implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TShop() {
	}

	/** minimal constructor */
	public TShop(Long shopid) {
		super(shopid);
	}

	/** full constructor */
	public TShop(Long shopid, Long fshopid, String areacode, String deptcode,
			String shopname, Long shoptype, String accflag,
			String status, String accno, String contactman, String idtype,
			String idno, String tel, String mobile, String email, String addr,
			String zipcode, String boardfeeflag, String rakeofftype,
			Double rakeoffrate, Double depositagio, Long depositcnt,
			Double depositamt, Double discountamt, String bankcode,
			String bankaccno, String bankaccname, String opendate,
			String closedate, String useflag) {
		super(shopid, fshopid, areacode, deptcode, shopname, shoptype, accflag,
				status, accno, contactman, idtype, idno, tel, mobile,
				email, addr, zipcode, boardfeeflag, rakeofftype, rakeoffrate,
				depositagio, depositcnt, depositamt, discountamt, bankcode,
				bankaccno, bankaccname, opendate, closedate, useflag);
	}

}
