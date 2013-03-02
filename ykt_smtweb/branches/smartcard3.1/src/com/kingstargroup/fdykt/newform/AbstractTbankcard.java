package com.kingstargroup.fdykt.newform;

/**
 * AbstractTbankcard entity provides the base persistence definition of the
 * Tbankcard entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTbankcard implements java.io.Serializable {

	// Fields

	private TbankcardId id;
	private String bankcardno;
	private String batchno;
	private String createddate;
	private String lastsaved;

	// Constructors

	/** default constructor */
	public AbstractTbankcard() {
	}

	/** minimal constructor */
	public AbstractTbankcard(TbankcardId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTbankcard(TbankcardId id, String bankcardno, String batchno,
			String createddate, String lastsaved) {
		this.id = id;
		this.bankcardno = bankcardno;
		this.batchno = batchno;
		this.createddate = createddate;
		this.lastsaved = lastsaved;
	}

	// Property accessors

	public TbankcardId getId() {
		return this.id;
	}

	public void setId(TbankcardId id) {
		this.id = id;
	}

	public String getBankcardno() {
		return this.bankcardno;
	}

	public void setBankcardno(String bankcardno) {
		this.bankcardno = bankcardno;
	}

	public String getBatchno() {
		return this.batchno;
	}

	public void setBatchno(String batchno) {
		this.batchno = batchno;
	}

	public String getCreateddate() {
		return this.createddate;
	}

	public void setCreateddate(String createddate) {
		this.createddate = createddate;
	}

	public String getLastsaved() {
		return this.lastsaved;
	}

	public void setLastsaved(String lastsaved) {
		this.lastsaved = lastsaved;
	}

}