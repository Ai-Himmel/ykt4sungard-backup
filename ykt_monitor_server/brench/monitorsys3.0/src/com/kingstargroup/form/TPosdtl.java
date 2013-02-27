package com.kingstargroup.form;

/**
 * TPosdtl entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TPosdtl extends AbstractTPosdtl implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TPosdtl() {
	}

	/** minimal constructor */
	public TPosdtl(TPosdtlId id, String status) {
		super(id, status);
	}

	/** full constructor */
	public TPosdtl(TPosdtlId id, String transtime, long cardno, long purseno,
			long cardcnt, double cardbefbal, double amount, double cardaftbal,
			double managefee, long transmark, long transcode, long shopid,
			long subsidyno, String batchno, long sysid, String coldate,
			String coltime, String accdate, String acctime, long termid,
			long termseqno, String status, long errcode, String errmsg,
			String delflag) {
		super(id, transtime, cardno, purseno, cardcnt, cardbefbal, amount,
				cardaftbal, managefee, transmark, transcode, shopid,
				subsidyno, batchno, sysid, coldate, coltime, accdate, acctime,
				termid, termseqno, status, errcode, errmsg, delflag);
	}

}
