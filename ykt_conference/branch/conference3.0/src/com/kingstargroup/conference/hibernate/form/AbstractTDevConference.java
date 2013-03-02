package com.kingstargroup.conference.hibernate.form;

/**
 * AbstractTDevConference entity provides the base persistence definition of the
 * TDevConference entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDevConference implements java.io.Serializable {

	// Fields

	private TDevConferenceId id;
	private String conBegindate;
	private String conBegintime;
	private String conEndtime;
	private String conSigntime;

	// Constructors

	/** default constructor */
	public AbstractTDevConference() {
	}

	/** minimal constructor */
	public AbstractTDevConference(TDevConferenceId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTDevConference(TDevConferenceId id, String conBegindate,
			String conBegintime, String conEndtime, String conSigntime) {
		this.id = id;
		this.conBegindate = conBegindate;
		this.conBegintime = conBegintime;
		this.conEndtime = conEndtime;
		this.conSigntime = conSigntime;
	}

	// Property accessors

	public TDevConferenceId getId() {
		return this.id;
	}

	public void setId(TDevConferenceId id) {
		this.id = id;
	}

	public String getConBegindate() {
		return this.conBegindate;
	}

	public void setConBegindate(String conBegindate) {
		this.conBegindate = conBegindate;
	}

	public String getConBegintime() {
		return this.conBegintime;
	}

	public void setConBegintime(String conBegintime) {
		this.conBegintime = conBegintime;
	}

	public String getConEndtime() {
		return this.conEndtime;
	}

	public void setConEndtime(String conEndtime) {
		this.conEndtime = conEndtime;
	}

	public String getConSigntime() {
		return this.conSigntime;
	}

	public void setConSigntime(String conSigntime) {
		this.conSigntime = conSigntime;
	}

}