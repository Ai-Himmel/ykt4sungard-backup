package org.king.monitor.domain;

/**
 * MapSerialexceptTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class MapSerialexceptTable extends AbstractMapSerialexceptTable
		implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public MapSerialexceptTable() {
	}

	/** minimal constructor */
	public MapSerialexceptTable(MapSerialexceptTableId id, String status) {
		super(id, status);
	}

	/** full constructor */
	public MapSerialexceptTable(MapSerialexceptTableId id, String transtime,
			long cardno, long purseno, long cardcnt, double cardbefbal,
			double amount, double cardaftbal, double managefee, long transmark,
			long transcode, long shopid, long subsidyno, String batchno,
			long sysid, String coldate, String coltime, String accdate,
			String acctime, String status, long errcode, String errmsg,
			String delflag, String contactname, long abnormaltype) {
		super(id, transtime, cardno, purseno, cardcnt, cardbefbal, amount,
				cardaftbal, managefee, transmark, transcode, shopid,
				subsidyno, batchno, sysid, coldate, coltime, accdate, acctime,
				status, errcode, errmsg, delflag, contactname, abnormaltype);
	}

}
