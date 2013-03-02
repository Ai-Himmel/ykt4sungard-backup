package com.kingstargroup.fdykt.newform;

/**
 * AbstractVTrandtl entity provides the base persistence definition of the
 * VTrandtl entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractVTrandtl implements java.io.Serializable {

	// Fields

	private VTrandtlId id;

	// Constructors

	/** default constructor */
	public AbstractVTrandtl() {
	}

	/** full constructor */
	public AbstractVTrandtl(VTrandtlId id) {
		this.id = id;
	}

	// Property accessors

	public VTrandtlId getId() {
		return this.id;
	}

	public void setId(VTrandtlId id) {
		this.id = id;
	}

}