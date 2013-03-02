package com.kingstargroup.conference.hibernate.form;

/**
 * TDevConference entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDevConference extends AbstractTDevConference implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDevConference() {
	}

	/** minimal constructor */
	public TDevConference(TDevConferenceId id) {
		super(id);
	}

	/** full constructor */
	public TDevConference(TDevConferenceId id, String conBegindate,
			String conBegintime, String conEndtime, String conSigntime) {
		super(id, conBegindate, conBegintime, conEndtime, conSigntime);
	}

}
