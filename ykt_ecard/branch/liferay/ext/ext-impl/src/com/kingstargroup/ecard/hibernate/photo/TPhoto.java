package com.kingstargroup.ecard.hibernate.photo;

import org.hibernate.lob.SerializableBlob;

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
	public TPhoto(Long custid) {
		super(custid);
	}

	/** full constructor */
	public TPhoto(Long custid, String stuempno, SerializableBlob photo, String photodate,
			String phototime, String ifcard, String makecarddate,
			String makecardtime, String res1, String res2, String res3) {
		super(custid, stuempno, photo, photodate, phototime, ifcard,
				makecarddate, makecardtime, res1, res2, res3);
	}

}
