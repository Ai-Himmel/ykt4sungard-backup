package org.king.monitor.domain;

/**
 * TDevmonitor entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDevmonitor extends AbstractTDevmonitor implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDevmonitor() {
	}

	/** minimal constructor */
	public TDevmonitor(Integer deviceid) {
		super(deviceid);
	}

	/** full constructor */
	public TDevmonitor(Integer deviceid, String optime, String coltime,
			String devtime, Integer beatstatus, String cardverno, Integer hardiskper,
			Integer memoryper, Integer cpuper) {
		super(deviceid, optime, coltime, devtime, beatstatus, cardverno,
				hardiskper, memoryper, cpuper);
	}

}
