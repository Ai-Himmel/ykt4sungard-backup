package com.kingstargroup.fdykt.newform;

/**
 * AbstractTPhoto entity provides the base persistence definition of the TPhoto
 * entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTPhoto implements java.io.Serializable {

	// Fields

	private Long custid;
	private String stuempno;
	private String photo;
	private String photodate;
	private String phototime;
	private String ifcard;
	private String makecarddate;
	private String makecardtime;
	private String photoexacttime;

	// Constructors

	/** default constructor */
	public AbstractTPhoto() {
	}

	/** minimal constructor */
	public AbstractTPhoto(Long custid) {
		this.custid = custid;
	}

	/** full constructor */
	public AbstractTPhoto(Long custid, String stuempno, String photo,
			String photodate, String phototime, String ifcard,
			String makecarddate, String makecardtime, String photoexacttime) {
		this.custid = custid;
		this.stuempno = stuempno;
		this.photo = photo;
		this.photodate = photodate;
		this.phototime = phototime;
		this.ifcard = ifcard;
		this.makecarddate = makecarddate;
		this.makecardtime = makecardtime;
		this.photoexacttime = photoexacttime;
	}

	// Property accessors

	public Long getCustid() {
		return this.custid;
	}

	public void setCustid(Long custid) {
		this.custid = custid;
	}

	public String getStuempno() {
		return this.stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}

	public String getPhoto() {
		return this.photo;
	}

	public void setPhoto(String photo) {
		this.photo = photo;
	}

	public String getPhotodate() {
		return this.photodate;
	}

	public void setPhotodate(String photodate) {
		this.photodate = photodate;
	}

	public String getPhototime() {
		return this.phototime;
	}

	public void setPhototime(String phototime) {
		this.phototime = phototime;
	}

	public String getIfcard() {
		return this.ifcard;
	}

	public void setIfcard(String ifcard) {
		this.ifcard = ifcard;
	}

	public String getMakecarddate() {
		return this.makecarddate;
	}

	public void setMakecarddate(String makecarddate) {
		this.makecarddate = makecarddate;
	}

	public String getMakecardtime() {
		return this.makecardtime;
	}

	public void setMakecardtime(String makecardtime) {
		this.makecardtime = makecardtime;
	}

	public String getPhotoexacttime() {
		return this.photoexacttime;
	}

	public void setPhotoexacttime(String photoexacttime) {
		this.photoexacttime = photoexacttime;
	}

}