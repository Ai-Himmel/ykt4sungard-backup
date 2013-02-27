package org.king.topo.domain;


/**
 * MonitorTopoGroup entity. @author MyEclipse Persistence Tools
 */
public class MonitorTopoGroup extends AbstractMonitorTopoGroup implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MonitorTopoGroup() {
	}

	/** full constructor */
    public MonitorTopoGroup(Integer devicegroupid, String devicegroupname, Integer groupxindex, Integer groupyindex, Integer groupwidth, Integer groupheight, MonitorTopoLocation location) {
        super(devicegroupid, devicegroupname, groupxindex, groupyindex, groupwidth, groupheight, location);
    }
}
