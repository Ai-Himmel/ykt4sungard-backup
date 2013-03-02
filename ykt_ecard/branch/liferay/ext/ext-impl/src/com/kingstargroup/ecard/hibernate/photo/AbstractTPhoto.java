package com.kingstargroup.ecard.hibernate.photo;

import org.hibernate.lob.SerializableBlob;


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
	private org.hibernate.lob.SerializableBlob photo;
	private String photodate;
	private String phototime;
	private String ifcard;
	private String makecarddate;
	private String makecardtime;
	private String res1;
	private String res2;
	private String res3;

	// Constructors

	/** default constructor */
	public AbstractTPhoto() {
	}

	/** minimal constructor */
	public AbstractTPhoto(Long custid) {
		this.custid = custid;
	}

	/** full constructor */
	public AbstractTPhoto(Long custid, String stuempno, SerializableBlob photo,
			String photodate, String phototime, String ifcard,
			String makecarddate, String makecardtime, String res1, String res2,
			String res3) {
		this.custid = custid;
		this.stuempno = stuempno;
		this.photo = photo;
		this.photodate = photodate;
		this.phototime = phototime;
		this.ifcard = ifcard;
		this.makecarddate = makecarddate;
		this.makecardtime = makecardtime;
		this.res1 = res1;
		this.res2 = res2;
		this.res3 = res3;
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

	public SerializableBlob getPhoto() {
		return this.photo;
	}

	public void setPhoto(SerializableBlob photo) {
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

	public String getRes1() {
		return this.res1;
	}

	public void setRes1(String res1) {
		this.res1 = res1;
	}

	public String getRes2() {
		return this.res2;
	}

	public void setRes2(String res2) {
		this.res2 = res2;
	}

	public String getRes3() {
		return this.res3;
	}

	public void setRes3(String res3) {
		this.res3 = res3;
	}

}