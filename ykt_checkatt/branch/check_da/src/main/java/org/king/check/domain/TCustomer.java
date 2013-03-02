package org.king.check.domain;


/**
 * TCustomer entity. @author MyEclipse Persistence Tools
 */
public class TCustomer extends AbstractTCustomer {

	// Constructors

	/** default constructor */
	public TCustomer() {
	}

	/** minimal constructor */
	public TCustomer(Integer custid,String stuempno) {
		super(custid , stuempno);
	}

	/** full constructor */
	public TCustomer(Integer custid, String stuempno, Integer custtype,
			Integer feetype, String status, String custname,
			String areacode, String deptcode, String deptfullname,
			String specialtycode, String classcode, String idtype, String idno,
			String sex, String country, String nation, String email,
			String tel, String mobile, String addr, String zipcode,
			String custattr, String indate, String outdate, String opendate,
			String closedate, String batchno, Integer openflag,
			Integer holdcardcnt, String useflag, String eaccflag,
			String lastsaved, String classname) {
		super(custid, stuempno, custtype, feetype, status, custname, areacode,
				deptcode, deptfullname, specialtycode, classcode, idtype, idno,
				sex, country, nation, email, tel, mobile, addr, zipcode,
				custattr, indate, outdate, opendate, closedate, batchno,
				openflag, holdcardcnt, useflag, eaccflag, lastsaved, classname);
	}

}
