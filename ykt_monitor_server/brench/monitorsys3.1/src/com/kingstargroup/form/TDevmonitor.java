package com.kingstargroup.form;

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
	public TDevmonitor(long deviceid) {
		super(deviceid);
	}

	/** full constructor */
	public TDevmonitor(long deviceid, String optime, String coltime,
			String devtime, long beatstatus, String cardverno, long hardiskper,
			long memoryper, long cpuper) {
		super(deviceid, optime, coltime, devtime, beatstatus, cardverno,
				hardiskper, memoryper, cpuper);
	}

}
