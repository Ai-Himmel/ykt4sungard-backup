package com.kingstargroup.conference.hibernate.form;

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

	/** full constructor */
	public TMsglist(long msgtype, long msglevel, long sysid, long deviceid,
			long cardno, String transdate, String createdtime,
			String starttime, String endtime, String reqdata, String respdata,
			long funcno, long pfuncno, long maxsendcnt, long sendcnt,
			long recvcnt, String status, long seqno, String opercode,
			long errcode, String errmsg, String delflag) {
		super(msgtype, msglevel, sysid, deviceid, cardno, transdate,
				createdtime, starttime, endtime, reqdata, respdata, funcno,
				pfuncno, maxsendcnt, sendcnt, recvcnt, status, seqno, opercode,
				errcode, errmsg, delflag);
	}

}
