package com.kingstargroup.form;

/**
 * TTransdtl entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TTransdtl extends AbstractTTransdtl implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public TTransdtl() {
	}

	/** minimal constructor */
	public TTransdtl(TTransdtlId id) {
		super(id);
	}

	/** full constructor */
	public TTransdtl(TTransdtlId id, String acctime, String transdate,
			String transtime, String coldate, String coltime, long transcode,
			long paytype, String voucherno, long custid, String custname,
			long cardno, long purseno, long cardcnt, double cardbefbal,
			double cardaftbal, double amount, double boardfee, String opercode,
			long sysid, String devphyid, long devseqno, long exttype,
			String extdata, String revflag, String status, long errcode,
			String remark) {
		super(id, acctime, transdate, transtime, coldate, coltime, transcode,
				paytype, voucherno, custid, custname, cardno, purseno, cardcnt,
				cardbefbal, cardaftbal, amount, boardfee, opercode, sysid,
				devphyid, devseqno, exttype, extdata, revflag, status, errcode,
				remark);
	}

}
