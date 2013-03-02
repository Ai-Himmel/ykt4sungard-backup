package org.king.check.domain;

import java.math.BigDecimal;

/**
 * TDevice entity. @author MyEclipse Persistence Tools
 */
public class TDevice extends AbstractTDevice implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TDevice() {
	}

	/** minimal constructor */
	public TDevice(Integer deviceid) {
		super(deviceid);
	}

	/** full constructor */
	public TDevice(Integer deviceid, String devicename, String devphyid,
			Integer deviceno, Integer devphytype, String devtypecode,
			String devverno, String cardphytype, Integer fdeviceid,
			Integer runstatus, String status, Integer svrportcnt,
			Integer svrportno, Integer commtype, String ip,
			Integer portno, Integer baudrate, String cardset,
			String cardverno, Integer lastseqno, String lasttranstime,
			Integer purseno, double maxamt, Integer sysid,
			String areacode, String doorlstver, Integer devusage,
			String opendate, String closedate, String batchno,
			String lastsaved, String remark) {
		super(deviceid, devicename, devphyid, deviceno, devphytype,
				devtypecode, devverno, cardphytype, fdeviceid, runstatus,
				status, svrportcnt, svrportno, commtype, ip, portno, baudrate,
				cardset, cardverno, lastseqno, lasttranstime, purseno, maxamt,
				sysid, areacode, doorlstver, devusage, opendate, closedate,
				batchno, lastsaved, remark);
	}

}
