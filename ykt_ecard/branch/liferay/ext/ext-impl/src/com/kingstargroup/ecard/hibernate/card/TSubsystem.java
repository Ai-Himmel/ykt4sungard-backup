package com.kingstargroup.ecard.hibernate.card;

/**
 * TSubsystem entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TSubsystem extends AbstractTSubsystem implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TSubsystem() {
	}

	/** minimal constructor */
	public TSubsystem(Long sysid) {
		super(sysid);
	}

	/** full constructor */
	public TSubsystem(Long sysid, String sysname, Long systype,
			String areacode, Long serverid, String macaddr, String ip,
			Long port, String cardverno, String initkey, String dynakey,
			String synctime, String runstatus, String status, String opendate,
			String closedate, String remark) {
		super(sysid, sysname, systype, areacode, serverid, macaddr, ip, port,
				cardverno, initkey, dynakey, synctime, runstatus, status,
				opendate, closedate, remark);
	}

}
