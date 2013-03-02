package com.kingstargroup.fdykt.newform;

/**
 * AbstractTMsglist entity provides the base persistence definition of the
 * TMsglist entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTMsglist implements java.io.Serializable {

	// Fields

	private Long msgid;
	private Long msgtype;
	private Long msglevel;
	private Long sysid;
	private Long deviceid;
	private Long cardno;
	private String transdate;
	private String createdtime;
	private String starttime;
	private String endtime;
	private String reqdata;
	private String respdata;
	private Long funcno;
	private Long pfuncno;
	private Long maxsendcnt;
	private Long sendcnt;
	private Long recvcnt;
	private String status;
	private Long seqno;
	private String opercode;
	private Long errcode;
	private String errmsg;
	private String delflag;

	// Constructors

	/** default constructor */
	public AbstractTMsglist() {
	}

	/** minimal constructor */
	public AbstractTMsglist(Long msgid) {
		this.msgid = msgid;
	}

	/** full constructor */
	public AbstractTMsglist(Long msgid, Long msgtype, Long msglevel,
			Long sysid, Long deviceid, Long cardno, String transdate,
			String createdtime, String starttime, String endtime,
			String reqdata, String respdata, Long funcno, Long pfuncno,
			Long maxsendcnt, Long sendcnt, Long recvcnt, String status,
			Long seqno, String opercode, Long errcode, String errmsg,
			String delflag) {
		this.msgid = msgid;
		this.msgtype = msgtype;
		this.msglevel = msglevel;
		this.sysid = sysid;
		this.deviceid = deviceid;
		this.cardno = cardno;
		this.transdate = transdate;
		this.createdtime = createdtime;
		this.starttime = starttime;
		this.endtime = endtime;
		this.reqdata = reqdata;
		this.respdata = respdata;
		this.funcno = funcno;
		this.pfuncno = pfuncno;
		this.maxsendcnt = maxsendcnt;
		this.sendcnt = sendcnt;
		this.recvcnt = recvcnt;
		this.status = status;
		this.seqno = seqno;
		this.opercode = opercode;
		this.errcode = errcode;
		this.errmsg = errmsg;
		this.delflag = delflag;
	}

	// Property accessors

	public Long getMsgid() {
		return this.msgid;
	}

	public void setMsgid(Long msgid) {
		this.msgid = msgid;
	}

	public Long getMsgtype() {
		return this.msgtype;
	}

	public void setMsgtype(Long msgtype) {
		this.msgtype = msgtype;
	}

	public Long getMsglevel() {
		return this.msglevel;
	}

	public void setMsglevel(Long msglevel) {
		this.msglevel = msglevel;
	}

	public Long getSysid() {
		return this.sysid;
	}

	public void setSysid(Long sysid) {
		this.sysid = sysid;
	}

	public Long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Long deviceid) {
		this.deviceid = deviceid;
	}

	public Long getCardno() {
		return this.cardno;
	}

	public void setCardno(Long cardno) {
		this.cardno = cardno;
	}

	public String getTransdate() {
		return this.transdate;
	}

	public void setTransdate(String transdate) {
		this.transdate = transdate;
	}

	public String getCreatedtime() {
		return this.createdtime;
	}

	public void setCreatedtime(String createdtime) {
		this.createdtime = createdtime;
	}

	public String getStarttime() {
		return this.starttime;
	}

	public void setStarttime(String starttime) {
		this.starttime = starttime;
	}

	public String getEndtime() {
		return this.endtime;
	}

	public void setEndtime(String endtime) {
		this.endtime = endtime;
	}

	public String getReqdata() {
		return this.reqdata;
	}

	public void setReqdata(String reqdata) {
		this.reqdata = reqdata;
	}

	public String getRespdata() {
		return this.respdata;
	}

	public void setRespdata(String respdata) {
		this.respdata = respdata;
	}

	public Long getFuncno() {
		return this.funcno;
	}

	public void setFuncno(Long funcno) {
		this.funcno = funcno;
	}

	public Long getPfuncno() {
		return this.pfuncno;
	}

	public void setPfuncno(Long pfuncno) {
		this.pfuncno = pfuncno;
	}

	public Long getMaxsendcnt() {
		return this.maxsendcnt;
	}

	public void setMaxsendcnt(Long maxsendcnt) {
		this.maxsendcnt = maxsendcnt;
	}

	public Long getSendcnt() {
		return this.sendcnt;
	}

	public void setSendcnt(Long sendcnt) {
		this.sendcnt = sendcnt;
	}

	public Long getRecvcnt() {
		return this.recvcnt;
	}

	public void setRecvcnt(Long recvcnt) {
		this.recvcnt = recvcnt;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public Long getSeqno() {
		return this.seqno;
	}

	public void setSeqno(Long seqno) {
		this.seqno = seqno;
	}

	public String getOpercode() {
		return this.opercode;
	}

	public void setOpercode(String opercode) {
		this.opercode = opercode;
	}

	public Long getErrcode() {
		return this.errcode;
	}

	public void setErrcode(Long errcode) {
		this.errcode = errcode;
	}

	public String getErrmsg() {
		return this.errmsg;
	}

	public void setErrmsg(String errmsg) {
		this.errmsg = errmsg;
	}

	public String getDelflag() {
		return this.delflag;
	}

	public void setDelflag(String delflag) {
		this.delflag = delflag;
	}

}