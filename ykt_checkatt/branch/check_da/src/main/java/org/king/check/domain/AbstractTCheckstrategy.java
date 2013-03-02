package org.king.check.domain;


/**
 * AbstractTCheckstrategy entity provides the base persistence definition of the
 * TCheckstrategy entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckstrategy implements
		java.io.Serializable {

	// Fields

	private String strategytype;
	private Integer strategyvalue;

	// Constructors

	/** default constructor */
	public AbstractTCheckstrategy() {
	}

	/** minimal constructor */
	public AbstractTCheckstrategy(String strategytype) {
		this.strategytype = strategytype;
	}

	/** full constructor */
	public AbstractTCheckstrategy(String strategytype, Integer strategyvalue) {
		this.strategytype = strategytype;
		this.strategyvalue = strategyvalue;
	}

	// Property accessors

	public String getStrategytype() {
		return this.strategytype;
	}

	public void setStrategytype(String strategytype) {
		this.strategytype = strategytype;
	}

	public Integer getStrategyvalue() {
		return this.strategyvalue;
	}

	public void setStrategyvalue(Integer strategyvalue) {
		this.strategyvalue = strategyvalue;
	}

}