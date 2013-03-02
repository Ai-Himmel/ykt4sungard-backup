package com.kingstargroup.conference.hibernate.form;

import java.sql.Blob;

/**
 * TPhoto entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TPhoto extends AbstractTPhoto implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TPhoto() {
	}

	/** minimal constructor */
	public TPhoto(long custid) {
		super(custid);
	}

	/** full constructor */
	public TPhoto(long custid, String stuempno, Blob photo, String photodate,
			String phototime, String ifcard, String makecarddate,
			String makecardtime, String photoexacttime) {
		super(custid, stuempno, photo, photodate, phototime, ifcard,
				makecarddate, makecardtime, photoexacttime);
	}

}
