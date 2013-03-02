package org.king.check.domain;

/**
 * AbstractTClassteacher entity provides the base persistence definition of the
 * TClassteacher entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTClassteacher implements java.io.Serializable {

	// Fields

	private TClassteacherId id;

	// Constructors

	/** default constructor */
	public AbstractTClassteacher() {
	}

	/** full constructor */
	public AbstractTClassteacher(TClassteacherId id) {
		this.id = id;
	}

	// Property accessors

	public TClassteacherId getId() {
		return this.id;
	}

	public void setId(TClassteacherId id) {
		this.id = id;
	}

}