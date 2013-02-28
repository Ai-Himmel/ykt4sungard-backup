package org.king.security.domain;

import java.math.BigDecimal;

/**
 * TTranscode entity. @author MyEclipse Persistence Tools
 */

public class TTranscode implements java.io.Serializable {

	// Fields

	private String transcode;
	private String transname;
	private String logflag;
	private String limitflag;
	private String feeflag;
	private String transflag;
	private String disableflag;

	// Constructors

	/** default constructor */
	public TTranscode() {
	}

	/** full constructor */
	public TTranscode(String transname, String logflag,
			String limitflag, String feeflag, String transflag,
			String disableflag) {
		this.transname = transname;
		this.logflag = logflag;
		this.limitflag = limitflag;
		this.feeflag = feeflag;
		this.transflag = transflag;
		this.disableflag = disableflag;
	}

	// Property accessors

	public String getTranscode() {
		return this.transcode;
	}

	public void setTranscode(String transcode) {
		this.transcode = transcode;
	}

	public String getTransname() {
		return this.transname;
	}

	public void setTransname(String transname) {
		this.transname = transname;
	}

	public String getLogflag() {
		return this.logflag;
	}

	public void setLogflag(String logflag) {
		this.logflag = logflag;
	}

	public String getLimitflag() {
		return this.limitflag;
	}

	public void setLimitflag(String limitflag) {
		this.limitflag = limitflag;
	}

	public String getFeeflag() {
		return this.feeflag;
	}

	public void setFeeflag(String feeflag) {
		this.feeflag = feeflag;
	}

	public String getTransflag() {
		return this.transflag;
	}

	public void setTransflag(String transflag) {
		this.transflag = transflag;
	}

	public String getDisableflag() {
		return this.disableflag;
	}

	public void setDisableflag(String disableflag) {
		this.disableflag = disableflag;
	}

}