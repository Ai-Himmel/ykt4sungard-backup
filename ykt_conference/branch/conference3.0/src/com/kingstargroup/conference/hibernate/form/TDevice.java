package com.kingstargroup.conference.hibernate.form;

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
			long deviceno, long devphytype, String devtypecode,
			String devverno, String cardphytype, long fdeviceid,
			long runstatus, String status, long svrportcnt, long svrportno,
			long commtype, String ip, long portno, long baudrate,
			String cardset, String cardverno, long lastseqno,
			String lasttranstime, long purseno, double maxamt, long sysid,
			String areacode, String doorlstver, long devusage, String opendate,
			String closedate, String batchno, String lastsaved, String remark) {
		super(deviceid, devicename, devphyid, deviceno, devphytype,
				devtypecode, devverno, cardphytype, fdeviceid, runstatus,
				status, svrportcnt, svrportno, commtype, ip, portno, baudrate,
				cardset, cardverno, lastseqno, lasttranstime, purseno, maxamt,
				sysid, areacode, doorlstver, devusage, opendate, closedate,
				batchno, lastsaved, remark);
	}

}
