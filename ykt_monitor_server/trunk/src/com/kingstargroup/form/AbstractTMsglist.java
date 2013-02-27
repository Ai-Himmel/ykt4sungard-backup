package com.kingstargroup.form;

/**
 * AbstractTMsglist entity provides the base persistence definition of the
 * TMsglist entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTMsglist implements java.io.Serializable {

	// Fields

	private long msgid;
	private long msgtype;
	private long msglevel;
	private long sysid;
	private long deviceid;
	private long cardno;
	private String transdate;
	private String createdtime;
	private String starttime;
	private String endtime;
	private String reqdata;
	private String respdata;
	private long funcno;
	private long pfuncno;
	private long maxsendcnt;
	private long sendcnt;
	private long recvcnt;
	private String status;
	private long seqno;
	private String opercode;
	private long errcode;
	private String errmsg;
	private String delflag;

	// Constructors

	/** default constructor */
	public AbstractTMsglist() {
	}

	/** minimal constructor */
	public AbstractTMsglist(long msgid) {
		this.msgid = msgid;
	}

	/** full constructor */
	public AbstractTMsglist(long msgid, long msgtype, long msglevel,
			long sysid, long deviceid, long cardno, String transdate,
			String createdtime, String starttime, String endtime,
			String reqdata, String respdata, long funcno, long pfuncno,
			long maxsendcnt, long sendcnt, long recvcnt, String status,
			long seqno, String opercode, long errcode, String errmsg,
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

	public long getMsgid() {
		return this.msgid;
	}

	public void setMsgid(long msgid) {
		this.msgid = msgid;
	}

	public long getMsgtype() {
		return this.msgtype;
	}

	public void setMsgtype(long msgtype) {
		this.msgtype = msgtype;
	}

	public long getMsglevel() {
		return this.msglevel;
	}

	public void setMsglevel(long msglevel) {
		this.msglevel = msglevel;
	}

	public long getSysid() {
		return this.sysid;
	}

	public void setSysid(long sysid) {
		this.sysid = sysid;
	}

	public long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
	}

	public long getCardno() {
		return this.cardno;
	}

	public void setCardno(long cardno) {
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

	public long getFuncno() {
		return this.funcno;
	}

	public void setFuncno(long funcno) {
		this.funcno = funcno;
	}

	public long getPfuncno() {
		return this.pfuncno;
	}

	public void setPfuncno(long pfuncno) {
		this.pfuncno = pfuncno;
	}

	public long getMaxsendcnt() {
		return this.maxsendcnt;
	}

	public void setMaxsendcnt(long maxsendcnt) {
		this.maxsendcnt = maxsendcnt;
	}

	public long getSendcnt() {
		return this.sendcnt;
	}

	public void setSendcnt(long sendcnt) {
		this.sendcnt = sendcnt;
	}

	public long getRecvcnt() {
		return this.recvcnt;
	}

	public void setRecvcnt(long recvcnt) {
		this.recvcnt = recvcnt;
	}

	public String getStatus() {
		return this.status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public long getSeqno() {
		return this.seqno;
	}

	public void setSeqno(long seqno) {
		this.seqno = seqno;
	}

	public String getOpercode() {
		return this.opercode;
	}

	public void setOpercode(String opercode) {
		this.opercode = opercode;
	}

	public long getErrcode() {
		return this.errcode;
	}

	public void setErrcode(long errcode) {
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