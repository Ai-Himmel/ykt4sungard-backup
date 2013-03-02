package com.kingstargroup.fdykt.newform;

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
	public TDevice(Long deviceid) {
		super(deviceid);
	}

	/** full constructor */
	public TDevice(Long deviceid, String devicename, String devphyid,
			Long deviceno, Long devphytype, String devtypecode,
			String devverno, String cardphytype, Long fdeviceid,
			String runstatus, String status, Long svrportcnt, Long svrportno,
			Long commtype, String ip, Long portno, Long baudrate,
			String cardset, String cardverno, Long lastseqno,
			String lasttranstime, Long purseno, Double maxamt, Long sysid,
			String areacode, String doorlstver, Long devusage, String opendate,
			String closedate, String batchno, String lastsaved, String remark) {
		super(deviceid, devicename, devphyid, deviceno, devphytype,
				devtypecode, devverno, cardphytype, fdeviceid, runstatus,
				status, svrportcnt, svrportno, commtype, ip, portno, baudrate,
				cardset, cardverno, lastseqno, lasttranstime, purseno, maxamt,
				sysid, areacode, doorlstver, devusage, opendate, closedate,
				batchno, lastsaved, remark);
	}

}
