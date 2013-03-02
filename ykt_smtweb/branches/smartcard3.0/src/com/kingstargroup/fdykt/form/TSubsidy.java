package com.kingstargroup.fdykt.form;

/**
 * TSubsidy entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TSubsidy extends AbstractTSubsidy implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TSubsidy() {
	}

	/** minimal constructor */
	public TSubsidy(TSubsidyId id) {
		super(id);
	}

	/** full constructor */
	public TSubsidy(TSubsidyId id, String stuempno, Long custid,
			Long subsidyno, Long cardno, String summary, String brokername,
			String brokeridno, Long paytype, String voucherno, Double amount,
			String subsidytype, String impdate, String imptime, String putdate,
			String puttime, String getdate, String gettime, String status,
			String errmsg, String opercode) {
		super(id, stuempno, custid, subsidyno, cardno, summary, brokername,
				brokeridno, paytype, voucherno, amount, subsidytype, impdate,
				imptime, putdate, puttime, getdate, gettime, status, errmsg,
				opercode);
	}

}
