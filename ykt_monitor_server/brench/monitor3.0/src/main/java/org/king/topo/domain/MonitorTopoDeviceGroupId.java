package org.king.topo.domain;


/**
 * MonitorTopoDeviceGroupId entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoDeviceGroupId extends AbstractMonitorTopoDeviceGroupId
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTopoDeviceGroupId() {
	}

	/** full constructor */
	public MonitorTopoDeviceGroupId(Integer deviceid,
			Integer devicegroupid) {
		super(deviceid, devicegroupid);
	}
}
