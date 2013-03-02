package com.kingstargroup.conference.hibernate.form;

/**
 * TConferenceType entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TConferenceType extends AbstractTConferenceType implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TConferenceType() {
	}

	/** full constructor */
	public TConferenceType(String typeName, String comments) {
		super(typeName, comments);
	}

}
