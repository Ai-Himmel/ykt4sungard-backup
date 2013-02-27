package org.king.topo.domain;


/**
 * MonitorTopoDevgroupInfo entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoDevgroupInfo extends AbstractMonitorTopoDevgroupInfo
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTopoDevgroupInfo() {
	}

	/** full constructor */
	public MonitorTopoDevgroupInfo(Integer devicegroupid,
			Integer devphytype, String devtypecode,Integer devtypenum,String lastupdate) {
		super(devicegroupid, devphytype, devtypecode,devtypenum,lastupdate);
	}

}
