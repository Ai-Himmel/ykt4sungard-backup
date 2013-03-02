package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTCustomer entity provides the base persistence definition of the
 * TCustomer entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCustomer implements java.io.Serializable {

	// Fields

	private long custid;
	private String stuempno;
	private long custtype;
	private long feetype;
	private String status;
	private String custname;
	private String areacode;
	private String deptcode;
	private String deptfullname;
	private String specialtycode;
	private String classcode;
	private String idtype;
	private String idno;
	private String sex;
	private String country;
	private String nation;
	private String email;
	private String tel;
	private String mobile;
	private String addr;
	private String zipcode;
	private String custattr;
	private String indate;
	private String outdate;
	private String opendate;
	private String closedate;
	private String batchno;
	private long holdcardcnt;
	private String useflag;
	private String eaccflag;
	private String lastsaved;

	// Constructors

	/** default constructor */
	public AbstractTCustomer() {
	}

	/** minimal constructor */
	public AbstractTCustomer(long custid) {
		this.custid = custid;
	}

	/** full constructor */
	public AbstractTCustomer(long custid, String stuempno, long custtype,
			long feetype, String status, String custname, String areacode,
			String deptcode, String deptfullname, String specialtycode,
			String classcode, String idtype, String idno, String sex,
			String country, String nation, String email, String tel,
			String mobile, String addr, String zipcode, String custattr,
			String indate, String outdate, String opendate, String closedate,
			String batchno, long holdcardcnt, String useflag, String eaccflag,
			String lastsaved) {
		this.custid = custid;
		this.stuempno = stuempno;
		this.custtype = custtype;
		this.feetype = feetype;
		this.status = status;
		this.custname = custname;
		this.areacode = areacode;
		this.deptcode = deptcode;
		this.deptfullname = deptfullname;
		this.specialtycode = specialtycode;
		this.classcode = classcode;
		this.idtype = idtype;
		this.idno = idno;
		this.sex = sex;
		this.country = country;
		this.nation = nation;
		this.email = email;
		this.tel = tel;
		this.mobile = mobile;
		this.addr = addr;
		this.zipcode = zipcode;
		this.custattr = custattr;
		this.indate = indate;
		this.outdate = outdate;
		this.opendate = opendate;
		this.closedate = closedate;
		this.batchno = batchno;
		this.holdcardcnt = holdcardcnt;
		this.useflag = useflag;
		this.eaccflag = eaccflag;
		this.lastsaved = lastsaved;
	}

	// Property accessors

	public long getCustid() {
		return this.custid;
	}

	public void setCustid(long custid) {
		this.custid = custid;
	}

	public String getStuempno() {
		return this.stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}

	public long getCusttype() {
		return this.custtype;
	}

	public void setCusttype(long custtype) {
		this.custtype = custtype;
	}

	public long getFeetype() {
		return this.feetype;
	}

	public void setFeetype(long feetype) {
		this.feetype = feetype;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public String getCustname() {
		return this.custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
	}

	public String getAreacode() {
		return this.areacode;
	}

	public void setAreacode(String areacode) {
		this.areacode = areacode;
	}

	public String getDeptcode() {
		return this.deptcode;
	}

	public void setDeptcode(String deptcode) {
		this.deptcode = deptcode;
	}

	public String getDeptfullname() {
		return this.deptfullname;
	}

	public void setDeptfullname(String deptfullname) {
		this.deptfullname = deptfullname;
	}

	public String getSpecialtycode() {
		return this.specialtycode;
	}

	public void setSpecialtycode(String specialtycode) {
		this.specialtycode = specialtycode;
	}

	public String getClasscode() {
		return this.classcode;
	}

	public void setClasscode(String classcode) {
		this.classcode = classcode;
	}

	public String getIdtype() {
		return this.idtype;
	}

	public void setIdtype(String idtype) {
		this.idtype = idtype;
	}

	public String getIdno() {
		return this.idno;
	}

	public void setIdno(String idno) {
		this.idno = idno;
	}

	public String getSex() {
		return this.sex;
	}

	public void setSex(String sex) {
		this.sex = sex;
	}

	public String getCountry() {
		return this.country;
	}

	public void setCountry(String country) {
		this.country = country;
	}

	public String getNation() {
		return this.nation;
	}

	public void setNation(String nation) {
		this.nation = nation;
	}

	public String getEmail() {
		return this.email;
	}

	public void setEmail(String email) {
		this.email = email;
	}

	public String getTel() {
		return this.tel;
	}

	public void setTel(String tel) {
		this.tel = tel;
	}

	public String getMobile() {
		return this.mobile;
	}

	public void setMobile(String mobile) {
		this.mobile = mobile;
	}

	public String getAddr() {
		return this.addr;
	}

	public void setAddr(String addr) {
		this.addr = addr;
	}

	public String getZipcode() {
		return this.zipcode;
	}

	public void setZipcode(String zipcode) {
		this.zipcode = zipcode;
	}

	public String getCustattr() {
		return this.custattr;
	}

	public void setCustattr(String custattr) {
		this.custattr = custattr;
	}

	public String getIndate() {
		return this.indate;
	}

	public void setIndate(String indate) {
		this.indate = indate;
	}

	public String getOutdate() {
		return this.outdate;
	}

	public void setOutdate(String outdate) {
		this.outdate = outdate;
	}

	public String getOpendate() {
		return this.opendate;
	}

	public void setOpendate(String opendate) {
		this.opendate = opendate;
	}

	public String getClosedate() {
		return this.closedate;
	}

	public void setClosedate(String closedate) {
		this.closedate = closedate;
	}

	public String getBatchno() {
		return this.batchno;
	}

	public void setBatchno(String batchno) {
		this.batchno = batchno;
	}

	public long getHoldcardcnt() {
		return this.holdcardcnt;
	}

	public void setHoldcardcnt(long holdcardcnt) {
		this.holdcardcnt = holdcardcnt;
	}

	public String getUseflag() {
		return this.useflag;
	}

	public void setUseflag(String useflag) {
		this.useflag = useflag;
	}

	public String getEaccflag() {
		return this.eaccflag;
	}

	public void setEaccflag(String eaccflag) {
		this.eaccflag = eaccflag;
	}

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

}