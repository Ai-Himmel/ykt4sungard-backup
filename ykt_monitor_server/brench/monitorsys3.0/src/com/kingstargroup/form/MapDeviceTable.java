package com.kingstargroup.form;

/**
 * MapDeviceTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapDeviceTable extends AbstractMapDeviceTable implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapDeviceTable() {
	}

	/** minimal constructor */
	public MapDeviceTable(MapDeviceTableId id) {
		super(id);
	}

	/** full constructor */
	public MapDeviceTable(MapDeviceTableId id, String devicename,
			String devphyid, String devtypecode, String fdevphyid,
			String runstatus, String status, String ip, long deviceno,
			String cardverno, long sysid, String areacode, long devusage,
			String devicetime, String servertime, String contactName,
			double cpu, double memory, double harddisk, long errorReason) {
		super(id, devicename, devphyid, devtypecode, fdevphyid, runstatus,
				status, ip, deviceno, cardverno, sysid, areacode, devusage,
				devicetime, servertime, contactName, cpu, memory, harddisk,
				errorReason);
	}

}
