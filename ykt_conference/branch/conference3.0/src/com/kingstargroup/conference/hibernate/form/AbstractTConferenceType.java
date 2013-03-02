package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTConferenceType entity provides the base persistence definition of
 * the TConferenceType entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTConferenceType implements java.io.Serializable {

	// Fields

	private long typeId;
	private String typeName;
	private String comments;

	// Constructors

	/** default constructor */
	public AbstractTConferenceType() {
	}

	/** full constructor */
	public AbstractTConferenceType(String typeName, String comments) {
		this.typeName = typeName;
		this.comments = comments;
	}

	// Property accessors

	public long getTypeId() {
		return this.typeId;
	}

	public void setTypeId(long typeId) {
		this.typeId = typeId;
	}

	public String getTypeName() {
		return this.typeName;
	}

	public void setTypeName(String typeName) {
		this.typeName = typeName;
	}

	public String getComments() {
		return this.comments;
	}

	public void setComments(String comments) {
		this.comments = comments;
	}

}