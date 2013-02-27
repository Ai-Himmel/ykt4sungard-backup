package com.kingstargroup.form;

/**
 * TCustomer entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TCustomer extends AbstractTCustomer implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCustomer() {
	}

	/** minimal constructor */
	public TCustomer(long custid) {
		super(custid);
	}

	/** full constructor */
	public TCustomer(long custid, long custtype, long feetype, String status,
			String custname, String stuempno, String areacode, String deptcode,
			String deptfullname, String specialtycode, String idtype,
			String idno, String sex, String country, String nation,
			String email, String tel, String mobile, String addr,
			String zipcode, String custattr, String indate, String outdate,
			String opendate, String closedate, String batchno, String useflag,
			String lastsaved, String classcode, long holdcardcnt,
			String eaccflag) {
		super(custid, custtype, feetype, status, custname, stuempno, areacode,
				deptcode, deptfullname, specialtycode, idtype, idno, sex,
				country, nation, email, tel, mobile, addr, zipcode, custattr,
				indate, outdate, opendate, closedate, batchno, useflag,
				lastsaved, classcode, holdcardcnt, eaccflag);
	}

}
