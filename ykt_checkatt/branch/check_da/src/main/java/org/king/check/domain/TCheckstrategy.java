package org.king.check.domain;


/**
 * TCheckstrategy entity. @author MyEclipse Persistence Tools
 */
public class TCheckstrategy extends AbstractTCheckstrategy implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TCheckstrategy() {
	}

	/** minimal constructor */
	public TCheckstrategy(String strategytype) {
		super(strategytype);
	}

	/** full constructor */
	public TCheckstrategy(String strategytype, Integer strategyvalue) {
		super(strategytype, strategyvalue);
	}

}
