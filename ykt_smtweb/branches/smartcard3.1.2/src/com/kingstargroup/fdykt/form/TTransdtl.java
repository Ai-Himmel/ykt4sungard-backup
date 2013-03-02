package com.kingstargroup.fdykt.form;

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
			String transtime, String coldate, String coltime, Long transcode,
			Long paytype, String voucherno, Long custid, String custname,
			Long cardno, Long purseno, Long cardcnt, Double cardbefbal,
			Double cardaftbal, Double amount, Double boardfee, String opercode,
			Long sysid, String devphyid, Long devseqno, Long exttype,
			String extdata, String revflag, String status, Long errcode,
			String remark) {
		super(id, acctime, transdate, transtime, coldate, coltime, transcode,
				paytype, voucherno, custid, custname, cardno, purseno, cardcnt,
				cardbefbal, cardaftbal, amount, boardfee, opercode, sysid,
				devphyid, devseqno, exttype, extdata, revflag, status, errcode,
				remark);
	}

}
