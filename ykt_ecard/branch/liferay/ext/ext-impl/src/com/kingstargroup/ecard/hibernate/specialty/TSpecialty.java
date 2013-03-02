package com.kingstargroup.ecard.hibernate.specialty;

/**
 * TSpecialty entity. @author MyEclipse Persistence Tools
 */
public class TSpecialty extends AbstractTSpecialty implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TSpecialty() {
	}

	/** minimal constructor */
	public TSpecialty(String specialtycode) {
		super(specialtycode);
	}

	/** full constructor */
	public TSpecialty(String specialtycode, String specialtyname,
			String useflag, String lastsaved) {
		super(specialtycode, specialtyname, useflag, lastsaved);
	}

}
