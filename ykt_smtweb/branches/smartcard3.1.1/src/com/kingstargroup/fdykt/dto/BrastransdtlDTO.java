package com.kingstargroup.fdykt.dto;

public class BrastransdtlDTO implements java.io.Serializable {
	
	// Fields

	private String refno;
	private long cardno;
	private String stuempno;
	private String custname;
	private String oppaccno;
	private String oppaccname;
	private String transdate;
	private String transtime;
	private long transtype;
	private String summary;
	private double transamt;
	private long status;
	private String remark;
	private String revflag;
	private long chkflag;

	// Property accessors

	public long getChkflag() {
		return chkflag;
	}

	public void setChkflag(long chkflag) {
		this.chkflag = chkflag;
	}

	public String getRefno() {
		return this.refno;
	}

	public void setRefno(String refno) {
		this.refno = refno;
	}

	public long getCardno() {
		return this.cardno;
	}

	public void setCardno(long cardno) {
		this.cardno = cardno;
	}

	public String getCustname() {
		return this.custname;
	}

	public void setCustname(String custname) {
		this.custname = custname;
	}

	public String getOppaccno() {
		return this.oppaccno;
	}

	public void setOppaccno(String oppaccno) {
		this.oppaccno = oppaccno;
	}

	public String getOppaccname() {
		return this.oppaccname;
	}

	public void setOppaccname(String oppaccname) {
		this.oppaccname = oppaccname;
	}

	public String getTransdate() {
		return this.transdate;
	}

	public void setTransdate(String transdate) {
		this.transdate = transdate;
	}

	public String getTranstime() {
		return this.transtime;
	}

	public void setTranstime(String transtime) {
		this.transtime = transtime;
	}

	public long getTranstype() {
		return this.transtype;
	}

	public void setTranstype(long transtype) {
		this.transtype = transtype;
	}

	public String getSummary() {
		return this.summary;
	}

	public void setSummary(String summary) {
		this.summary = summary;
	}

	public double getTransamt() {
		return this.transamt;
	}

	public void setTransamt(double transamt) {
		this.transamt = transamt;
	}

	public long getStatus() {
		return this.status;
	}

	public void setStatus(long status) {
		this.status = status;
	}

	public String getRemark() {
		return this.remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

	public String getRevflag() {
		return revflag;
	}

	public void setRevflag(String revflag) {
		this.revflag = revflag;
	}

	public String getStuempno() {
		return stuempno;
	}

	public void setStuempno(String stuempno) {
		this.stuempno = stuempno;
	}


}
