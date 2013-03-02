package com.kingstargroup.fdykt.newform;

/**
 * VDeviceId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class VDeviceId extends AbstractVDeviceId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public VDeviceId() {
	}

	/** minimal constructor */
	public VDeviceId(Long deviceid) {
		super(deviceid);
	}

	/** full constructor */
	public VDeviceId(String nu, Long deviceid, String devicename,
			String devphyid, String devtypecode, String devverno,
			String cardphytype, Long svrportcnt, Long fdeviceid,
			String runstatus, String status, Long commtype, String ip,
			Long portno, Long svrportno, Long deviceno, Long baudrate,
			String cardset, String cardverno, Long lastseqno,
			String lasttranstime, Long purseno, Double maxamt, Long devphytype,
			Long sysid, String areacode, String doorlstver, Long devusage) {
		super(nu, deviceid, devicename, devphyid, devtypecode, devverno,
				cardphytype, svrportcnt, fdeviceid, runstatus, status,
				commtype, ip, portno, svrportno, deviceno, baudrate, cardset,
				cardverno, lastseqno, lasttranstime, purseno, maxamt,
				devphytype, sysid, areacode, doorlstver, devusage);
	}

}
