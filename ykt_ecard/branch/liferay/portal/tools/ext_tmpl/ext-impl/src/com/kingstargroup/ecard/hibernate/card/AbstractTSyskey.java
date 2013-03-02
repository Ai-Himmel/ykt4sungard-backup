package com.kingstargroup.ecard.hibernate.card;

/**
 * AbstractTSyskey entity provides the base persistence definition of the
 * TSyskey entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTSyskey implements java.io.Serializable {

	// Fields

	private String keycode;
	private String keyname;
	private Double keyval;
	private Long maxval;
	private String keytype;

	// Constructors

	/** default constructor */
	public AbstractTSyskey() {
	}

	/** minimal constructor */
	public AbstractTSyskey(String keycode) {
		this.keycode = keycode;
	}

	/** full constructor */
	public AbstractTSyskey(String keycode, String keyname, Double keyval,
			Long maxval, String keytype) {
		this.keycode = keycode;
		this.keyname = keyname;
		this.keyval = keyval;
		this.maxval = maxval;
		this.keytype = keytype;
	}

	// Property accessors

	public String getKeycode() {
		return this.keycode;
	}

	public void setKeycode(String keycode) {
		this.keycode = keycode;
	}

	public String getKeyname() {
		return this.keyname;
	}

	public void setKeyname(String keyname) {
		this.keyname = keyname;
	}

	public Double getKeyval() {
		return this.keyval;
	}

	public void setKeyval(Double keyval) {
		this.keyval = keyval;
	}

	public Long getMaxval() {
		return this.maxval;
	}

	public void setMaxval(Long maxval) {
		this.maxval = maxval;
	}

	public String getKeytype() {
		return this.keytype;
	}

	public void setKeytype(String keytype) {
		this.keytype = keytype;
	}

}