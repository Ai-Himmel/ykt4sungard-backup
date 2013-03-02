package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTInformList entity provides the base persistence definition of the
 * TInformList entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTInformList implements java.io.Serializable {

	// Fields

	private TInformListId id;
	private String informDate;
	private String informTime;
	private String informSign;

	// Constructors

	/** default constructor */
	public AbstractTInformList() {
	}

	/** minimal constructor */
	public AbstractTInformList(TInformListId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTInformList(TInformListId id, String informDate,
			String informTime, String informSign) {
		this.id = id;
		this.informDate = informDate;
		this.informTime = informTime;
		this.informSign = informSign;
	}

	// Property accessors

	public TInformListId getId() {
		return this.id;
	}

	public void setId(TInformListId id) {
		this.id = id;
	}

	public String getInformDate() {
		return this.informDate;
	}

	public void setInformDate(String informDate) {
		this.informDate = informDate;
	}

	public String getInformTime() {
		return this.informTime;
	}

	public void setInformTime(String informTime) {
		this.informTime = informTime;
	}

	public String getInformSign() {
		return this.informSign;
	}

	public void setInformSign(String informSign) {
		this.informSign = informSign;
	}

}