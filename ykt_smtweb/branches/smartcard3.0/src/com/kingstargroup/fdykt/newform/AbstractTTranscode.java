package com.kingstargroup.fdykt.newform;

/**
 * AbstractTTranscode entity provides the base persistence definition of the
 * TTranscode entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTranscode implements java.io.Serializable {

	// Fields

	private Long transcode;
	private String transname;
	private Long logflag;
	private Long limitflag;
	private Long feeflag;
	private Long transflag;
	private Long disableflag;

	// Constructors

	/** default constructor */
	public AbstractTTranscode() {
	}

	/** minimal constructor */
	public AbstractTTranscode(Long transcode) {
		this.transcode = transcode;
	}

	/** full constructor */
	public AbstractTTranscode(Long transcode, String transname, Long logflag,
			Long limitflag, Long feeflag, Long transflag, Long disableflag) {
		this.transcode = transcode;
		this.transname = transname;
		this.logflag = logflag;
		this.limitflag = limitflag;
		this.feeflag = feeflag;
		this.transflag = transflag;
		this.disableflag = disableflag;
	}

	// Property accessors

	public Long getTranscode() {
		return this.transcode;
	}

	public void setTranscode(Long transcode) {
		this.transcode = transcode;
	}

	public String getTransname() {
		return this.transname;
	}

	public void setTransname(String transname) {
		this.transname = transname;
	}

	public Long getLogflag() {
		return this.logflag;
	}

	public void setLogflag(Long logflag) {
		this.logflag = logflag;
	}

	public Long getLimitflag() {
		return this.limitflag;
	}

	public void setLimitflag(Long limitflag) {
		this.limitflag = limitflag;
	}

	public Long getFeeflag() {
		return this.feeflag;
	}

	public void setFeeflag(Long feeflag) {
		this.feeflag = feeflag;
	}

	public Long getTransflag() {
		return this.transflag;
	}

	public void setTransflag(Long transflag) {
		this.transflag = transflag;
	}

	public Long getDisableflag() {
		return this.disableflag;
	}

	public void setDisableflag(Long disableflag) {
		this.disableflag = disableflag;
	}

}