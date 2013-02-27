package org.king.monitor.domain;

/**
 * TDevice entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TDevice extends AbstractTDevice implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDevice() {
	}

	/** minimal constructor */
	public TDevice(long deviceid) {
		super(deviceid);
	}

	/** full constructor */
	public TDevice(long deviceid, String devicename, String devphyid,
			String devtypecode, String devverno, String cardphytype,
			long svrportcnt, long fdeviceid, String runstatus, String status,
			long commtype, String ip, long portno, long svrportno,
			long deviceno, long baudrate, String cardset, String cardverno,
			long lastseqno, String lasttranstime, long purseno, long maxamt,
			long devphytype, long sysid, String areacode, String doorlstver,
			long devusage) {
		super(deviceid, devicename, devphyid, devtypecode, devverno,
				cardphytype, svrportcnt, fdeviceid, runstatus, status,
				commtype, ip, portno, svrportno, deviceno, baudrate, cardset,
				cardverno, lastseqno, lasttranstime, purseno, maxamt,
				devphytype, sysid, areacode, doorlstver, devusage);
	}

}
