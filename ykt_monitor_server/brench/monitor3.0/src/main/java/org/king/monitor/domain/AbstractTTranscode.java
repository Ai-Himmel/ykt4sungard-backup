package org.king.monitor.domain;

/**
 * AbstractTTranscode entity provides the base persistence definition of the
 * TTranscode entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTTranscode implements java.io.Serializable {

	// Fields

	private long transcode;
	private String transname;
	private long logflag;
	private long limitflag;

	// Constructors

	/** default constructor */
	public AbstractTTranscode() {
	}

	/** minimal constructor */
	public AbstractTTranscode(long transcode) {
		this.transcode = transcode;
	}

	/** full constructor */
	public AbstractTTranscode(long transcode, String transname, long logflag,
			long limitflag) {
		this.transcode = transcode;
		this.transname = transname;
		this.logflag = logflag;
		this.limitflag = limitflag;
	}

	// Property accessors

	public long getTranscode() {
		return this.transcode;
	}

	public void setTranscode(long transcode) {
		this.transcode = transcode;
	}

	public String getTransname() {
		return this.transname;
	}

	public void setTransname(String transname) {
		this.transname = transname;
	}

	public long getLogflag() {
		return this.logflag;
	}

	public void setLogflag(long logflag) {
		this.logflag = logflag;
	}

	public long getLimitflag() {
		return this.limitflag;
	}

	public void setLimitflag(long limitflag) {
		this.limitflag = limitflag;
	}

}