package org.king.check.domain;

/**
 * TCheckLocation entity. @author MyEclipse Persistence Tools
 */
public class TCheckLocation extends AbstractTCheckLocation implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCheckLocation() {
	}

	/** minimal constructor */
	public TCheckLocation(String id) {
		super(id);
	}

	/** full constructor */
	public TCheckLocation(String id, String name) {
		super(id, name);
	}

}
