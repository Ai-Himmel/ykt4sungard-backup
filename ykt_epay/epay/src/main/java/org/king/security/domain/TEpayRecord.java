package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TEpayRecord entity. @author MyEclipse Persistence Tools
 */

public class TEpayRecord implements java.io.Serializable {

	// Fields

	private String refno;
	private TShop tshop;
	private String oid;
	private TNetacc tnetacc;
	private String accname;
	private double amount;
	private String currency;
	private String epaydate;
	private String epaytime;
	private String status;
	private TTranscode transcode;
	private String checkcnt;
	private String acktime;
	private String updatetime;
	private String errcode;
	private String errmsg;
	private String remark;

	// Constructors

	/** default constructor */
	public TEpayRecord() {
	}

	public String getRefno() {
		return refno;
	}

	public void setRefno(String refno) {
		this.refno = refno;
	}

	public TShop getTshop() {
		return tshop;
	}

	public void setTshop(TShop tshop) {
		this.tshop = tshop;
	}

	public String getOid() {
		return oid;
	}

	public void setOid(String oid) {
		this.oid = oid;
	}

	public TNetacc getTnetacc() {
		return tnetacc;
	}

	public void setTnetacc(TNetacc tnetacc) {
		this.tnetacc = tnetacc;
	}

	public String getAccname() {
		return accname;
	}

	public void setAccname(String accname) {
		this.accname = accname;
	}

	public double getAmount() {
		return amount;
	}

	public void setAmount(double amount) {
		this.amount = amount;
	}

	public String getCurrency() {
		return currency;
	}

	public void setCurrency(String currency) {
		this.currency = currency;
	}


	public String getEpaydate() {
		return epaydate;
	}

	public void setEpaydate(String epaydate) {
		this.epaydate = epaydate;
	}

	public String getEpaytime() {
		return epaytime;
	}

	public void setEpaytime(String epaytime) {
		this.epaytime = epaytime;
	}

	public String getStatus() {
		return status;
	}

	public void setStatus(String status) {
		this.status = status;
	}

	public TTranscode getTranscode() {
		return transcode;
	}

	public void setTranscode(TTranscode transcode) {
		this.transcode = transcode;
	}

	public String getCheckcnt() {
		return checkcnt;
	}

	public void setCheckcnt(String checkcnt) {
		this.checkcnt = checkcnt;
	}

	public String getAcktime() {
		return acktime;
	}

	public void setAcktime(String acktime) {
		this.acktime = acktime;
	}

	public String getUpdatetime() {
		return updatetime;
	}

	public void setUpdatetime(String updatetime) {
		this.updatetime = updatetime;
	}

	public String getErrcode() {
		return errcode;
	}

	public void setErrcode(String errcode) {
		this.errcode = errcode;
	}

	public String getErrmsg() {
		return errmsg;
	}

	public void setErrmsg(String errmsg) {
		this.errmsg = errmsg;
	}

	public String getRemark() {
		return remark;
	}

	public void setRemark(String remark) {
		this.remark = remark;
	}

	

}