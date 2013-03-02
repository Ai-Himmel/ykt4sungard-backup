package com.kingstargroup.fdykt.newform;

/**
 * VTrandtlId entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class VTrandtlId extends AbstractVTrandtlId implements
		java.io.Serializable {

	// Constructors

	/** default constructor */
	public VTrandtlId() {
	}

	/** minimal constructor */
	public VTrandtlId(String accdate, Long termid, Long termseqno) {
		super(accdate, termid, termseqno);
	}

	/** full constructor */
	public VTrandtlId(String accdate, String acctime, Long termid,
			Long termseqno, String transdate, String transtime, String coldate,
			String coltime, Long transcode, Long paytype, String voucherno,
			Long custid, String custname, Long cardno, Long purseno,
			Long cardcnt, Double cardbefbal, Double cardaftbal, Double amount,
			Double managefee, String opercode, Long sysid, String devphyid,
			Long devseqno, Long exttype, String extdata, String revflag,
			String status, Long errcode, String remark) {
		super(accdate, acctime, termid, termseqno, transdate, transtime,
				coldate, coltime, transcode, paytype, voucherno, custid,
				custname, cardno, purseno, cardcnt, cardbefbal, cardaftbal,
				amount, managefee, opercode, sysid, devphyid, devseqno,
				exttype, extdata, revflag, status, errcode, remark);
	}

}
