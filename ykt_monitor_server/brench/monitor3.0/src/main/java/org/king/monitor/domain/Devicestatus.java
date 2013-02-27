package org.king.monitor.domain;


/**
 * Devicestatus entity. @author MyEclipse Persistence Tools
 */
public class Devicestatus extends AbstractDevicestatus implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public Devicestatus() {
	}

	/** full constructor */
	public Devicestatus(long deviceid, String devicename, String devphyid,
			long fdevceid, String devtypecode, long sysid, String areacode,
			String cardverno, long devusage, String ip, String errstarttime,
			long errlasttime, String errendtime, String contactname,
			long errreason, long devstatus,String lastupdate) {
		super(deviceid, devicename, devphyid, fdevceid, devtypecode, sysid,
				areacode, cardverno, devusage, ip, errstarttime, errlasttime,
				errendtime, contactname, errreason, devstatus,lastupdate);
	}

}
