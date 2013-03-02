package com.kingstargroup.conference.hibernate.form;

/**
 * TDelegate entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDelegate extends AbstractTDelegate implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDelegate() {
	}

	/** minimal constructor */
	public TDelegate(String operId) {
		super(operId);
	}

	/** full constructor */
	public TDelegate(String dlgtName, String deptId, String open,
			String operId, String comment) {
		super(dlgtName, deptId, open, operId, comment);
	}

}
