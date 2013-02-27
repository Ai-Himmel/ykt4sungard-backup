package org.king.topo.domain;

import java.math.BigDecimal;

/**
 * MonitorTopoDeviceDic entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoDeviceDic extends AbstractMonitorTopoDeviceDic
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTopoDeviceDic() {
	}

	/** minimal constructor */
	public MonitorTopoDeviceDic(Integer devphytype, String devtypecode) {
		super(devphytype, devtypecode);
	}

	/** full constructor */
	public MonitorTopoDeviceDic(Integer devphytype, String devtypecode,String devtypename,
			String deviceimage, Integer imagewidth, Integer imageheight) {
		super(devphytype, devtypecode,devtypename, deviceimage, imagewidth, imageheight);
	}

}
