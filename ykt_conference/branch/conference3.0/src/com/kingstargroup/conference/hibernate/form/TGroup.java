package com.kingstargroup.conference.hibernate.form;

/**
 * TGroup entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TGroup extends AbstractTGroup implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TGroup() {
	}

	/** minimal constructor */
	public TGroup(String operId) {
		super(operId);
	}

	/** full constructor */
	public TGroup(String operId, String groupName, String comments) {
		super(operId, groupName, comments);
	}

}
