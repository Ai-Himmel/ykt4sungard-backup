package com.kingstargroup.ecard.hibernate.card;

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
	public TPosdtl(TPosdtlId id, String transtime, Long cardno, Long purseno,
			Long cardcnt, Double cardbefbal, Double amount, Double cardaftbal,
			Double managefee, Long transmark, Long transcode, Long shopid,
			Long subsidyno, String batchno, Long sysid, String coldate,
			String coltime, String accdate, String acctime, Long termid,
			Long termseqno, String status, Long errcode, String errmsg,
			String delflag) {
		super(id, transtime, cardno, purseno, cardcnt, cardbefbal, amount,
				cardaftbal, managefee, transmark, transcode, shopid, subsidyno,
				batchno, sysid, coldate, coltime, accdate, acctime, termid,
				termseqno, status, errcode, errmsg, delflag);
	}

}
