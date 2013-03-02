package com.kingstargroup.conference.hibernate.form;

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
	public TCustomer(long custid, String stuempno, long custtype, long feetype,
			String status, String custname, String areacode, String deptcode,
			String deptfullname, String specialtycode, String classcode,
			String idtype, String idno, String sex, String country,
			String nation, String email, String tel, String mobile,
			String addr, String zipcode, String custattr, String indate,
			String outdate, String opendate, String closedate, String batchno,
			long holdcardcnt, String useflag, String eaccflag, String lastsaved) {
		super(custid, stuempno, custtype, feetype, status, custname, areacode,
				deptcode, deptfullname, specialtycode, classcode, idtype, idno,
				sex, country, nation, email, tel, mobile, addr, zipcode,
				custattr, indate, outdate, opendate, closedate, batchno,
				holdcardcnt, useflag, eaccflag, lastsaved);
	}

}
