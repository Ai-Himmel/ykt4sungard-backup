package org.king.monitor.domain;

/**
 * MonitorsId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MonitorsId extends AbstractMonitorsId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorsId() {
	}

	/** full constructor */
	public MonitorsId(String host, String category, String entry) {
		super(host, category, entry);
	}

}
