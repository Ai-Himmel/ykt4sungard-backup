package org.king.topo.domain;

import java.math.BigDecimal;
import java.sql.Clob;

/**
 * monitorTopoGroupInfo entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoGroupInfo extends AbstractMonitorTopoGroupInfo
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTopoGroupInfo() {
	}

	/** minimal constructor */
	public MonitorTopoGroupInfo(Integer devicegroupid) {
		super(devicegroupid);
	}

	/** full constructor */
	public MonitorTopoGroupInfo(Integer devicegroupid,
			Integer groupwidth, Integer groupheight, String groupvml,
			String lastupdate) {
		super(devicegroupid, groupwidth, groupheight, groupvml, lastupdate);
	}

}
