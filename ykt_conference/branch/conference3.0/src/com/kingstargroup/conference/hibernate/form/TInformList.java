package com.kingstargroup.conference.hibernate.form;

/**
 * TInformList entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TInformList extends AbstractTInformList implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TInformList() {
	}

	/** minimal constructor */
	public TInformList(TInformListId id) {
		super(id);
	}

	/** full constructor */
	public TInformList(TInformListId id, String informDate, String informTime,
			String informSign) {
		super(id, informDate, informTime, informSign);
	}

}
