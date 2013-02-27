package org.king.business.domain;


/**
 * MonitorDevCardverHis entity. @author MyEclipse Persistence Tools
 */
public class MonitorDevCardverHis extends AbstractMonitorDevCardverHis
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorDevCardverHis() {
	}

	/** full constructor */
	public MonitorDevCardverHis(Integer deviceid, String cardvarno,
			String entertime, String lastupdate, Integer lasttime,
			String lattestverno) {
		super(deviceid, cardvarno, entertime, lastupdate, lasttime,
				lattestverno);
	}

}
