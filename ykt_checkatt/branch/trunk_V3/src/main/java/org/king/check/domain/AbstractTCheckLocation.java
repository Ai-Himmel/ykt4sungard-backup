package org.king.check.domain;

/**
 * AbstractTCheckLocation entity provides the base persistence definition of the
 * TCheckLocation entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckLocation implements java.io.Serializable {

	// Fields

	private String id;
	private String name;

	// Constructors

	/** default constructor */
	public AbstractTCheckLocation() {
	}

	/** minimal constructor */
	public AbstractTCheckLocation(String id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTCheckLocation(String id, String name) {
		this.id = id;
		this.name = name;
	}

	// Property accessors

	public String getId() {
		return this.id;
	}

	public void setId(String id) {
		this.id = id;
	}

	public String getName() {
		return this.name;
	}

	public void setName(String name) {
		this.name = name;
	}

}