package com.kingstargroup.form;

import java.util.Date;

/**
 * Monitors entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class Monitors extends AbstractMonitors implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public Monitors() {
	}

	/** minimal constructor */
	public Monitors(MonitorsId id, Date modified) {
		super(id, modified);
	}

	/** full constructor */
	public Monitors(MonitorsId id, String valuestr, Date modified) {
		super(id, valuestr, modified);
	}

}
