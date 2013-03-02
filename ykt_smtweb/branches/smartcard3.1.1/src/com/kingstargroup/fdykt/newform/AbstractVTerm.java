package com.kingstargroup.fdykt.newform;

/**
 * AbstractVTerm entity provides the base persistence definition of the VTerm
 * entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractVTerm implements java.io.Serializable {

	// Fields

	private VTermId id;

	// Constructors

	/** default constructor */
	public AbstractVTerm() {
	}

	/** full constructor */
	public AbstractVTerm(VTermId id) {
		this.id = id;
	}

	// Property accessors

	public VTermId getId() {
		return this.id;
	}

	public void setId(VTermId id) {
		this.id = id;
	}

}