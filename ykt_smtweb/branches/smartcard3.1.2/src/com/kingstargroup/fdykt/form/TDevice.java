package com.kingstargroup.fdykt.form;

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
			String devtypecode, String devverno, String cardphytype,
			Long svrportcnt, Long fdeviceid, String runstatus, String status,
			Long commtype, String ip, Long portno, Long svrportno,
			Long deviceno, Long baudrate, String cardset, String cardverno,
			Long lastseqno, String lasttranstime, Long purseno, Long maxamt,
			Long devphytype, Long sysid, String areacode, String doorlstver,
			Long devusage) {
		super(deviceid, devicename, devphyid, devtypecode, devverno,
				cardphytype, svrportcnt, fdeviceid, runstatus, status,
				commtype, ip, portno, svrportno, deviceno, baudrate, cardset,
				cardverno, lastseqno, lasttranstime, purseno, maxamt,
				devphytype, sysid, areacode, doorlstver, devusage);
	}

}
