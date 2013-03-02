package com.kingstargroup.fdykt.form;

/**
 * TMsglist entity.
 * 
 * @author MyEclipse Persistence Tools
 */
public class TMsglist extends AbstractTMsglist implements java.io.Serializable {

	// Constructors

	/** default constructor */
	public TMsglist() {
	}

	/** minimal constructor */
	public TMsglist(Long msgid) {
		super(msgid);
	}

	/** full constructor */
	public TMsglist(Long msgid, Long msgtype, Long msglevel, Long sysid,
			Long deviceid, Long cardno, String transdate, String createdtime,
			String starttime, String endtime, String reqdata, String respdata,
			Long funcno, Long pfuncno, Long maxsendcnt, Long sendcnt,
			Long recvcnt, String status, Long seqno, String opercode,
			Long errcode, String errmsg, String delflag) {
		super(msgid, msgtype, msglevel, sysid, deviceid, cardno, transdate,
				createdtime, starttime, endtime, reqdata, respdata, funcno,
				pfuncno, maxsendcnt, sendcnt, recvcnt, status, seqno, opercode,
				errcode, errmsg, delflag);
	}

}
