package com.kingstargroup.ecard.hibernate.specialty;

/**
 * AbstractTSpecialty entity provides the base persistence definition of the
 * TSpecialty entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTSpecialty implements java.io.Serializable {

	// Fields

	private String specialtycode;
	private String specialtyname;
	private String useflag;
	private String lastsaved;

	// Constructors

	/** default constructor */
	public AbstractTSpecialty() {
	}

	/** minimal constructor */
	public AbstractTSpecialty(String specialtycode) {
		this.specialtycode = specialtycode;
	}

	/** full constructor */
	public AbstractTSpecialty(String specialtycode, String specialtyname,
			String useflag, String lastsaved) {
		this.specialtycode = specialtycode;
		this.specialtyname = specialtyname;
		this.useflag = useflag;
		this.lastsaved = lastsaved;
	}

	// Property accessors

	public String getSpecialtycode() {
		return this.specialtycode;
	}

	public void setSpecialtycode(String specialtycode) {
		this.specialtycode = specialtycode;
	}

	public String getSpecialtyname() {
		return this.specialtyname;
	}

	public void setSpecialtyname(String specialtyname) {
		this.specialtyname = specialtyname;
	}

	public String getUseflag() {
		return this.useflag;
	}

	public void setUseflag(String useflag) {
		this.useflag = useflag;
	}

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

}