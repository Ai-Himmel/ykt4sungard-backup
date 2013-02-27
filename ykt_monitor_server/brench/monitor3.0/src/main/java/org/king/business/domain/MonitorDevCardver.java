package org.king.business.domain;


/**
 * MonitorDevCardver entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevCardver extends AbstractMonitorDevCardver implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDevCardver() {
	}

	/** full constructor */
	public MonitorDevCardver(String cardvarno, String entertime,
			String lastupdate, Integer lasttime, String lattestverno) {
		super(cardvarno, entertime, lastupdate, lasttime, lattestverno);
	}

}
