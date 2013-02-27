package com.kingstargroup.form;

/**
 * AbstractMapSerialostTable entity provides the base persistence definition of
 * the MapSerialostTable entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractMapSerialostTable implements java.io.Serializable {

	// Fields

	private MapSerialostTableId id;
	private String txDate;
	private String txTime;
	private String contactname;
	private long serialReason;
	private long serialStatus;

	// Constructors

	/** default constructor */
	public AbstractMapSerialostTable() {
	}

	/** minimal constructor */
	public AbstractMapSerialostTable(MapSerialostTableId id, String txDate,
			String txTime, long serialReason, long serialStatus) {
		this.id = id;
		this.txDate = txDate;
		this.txTime = txTime;
		this.serialReason = serialReason;
		this.serialStatus = serialStatus;
	}

	/** full constructor */
	public AbstractMapSerialostTable(MapSerialostTableId id, String txDate,
			String txTime, String contactname, long serialReason,
			long serialStatus) {
		this.id = id;
		this.txDate = txDate;
		this.txTime = txTime;
		this.contactname = contactname;
		this.serialReason = serialReason;
		this.serialStatus = serialStatus;
	}

	// Property accessors

	public MapSerialostTableId getId() {
		return this.id;
	}

	public void setId(MapSerialostTableId id) {
		this.id = id;
	}

	public String getTxDate() {
		return this.txDate;
	}

	public void setTxDate(String txDate) {
		this.txDate = txDate;
	}

	public String getTxTime() {
		return this.txTime;
	}

	public void setTxTime(String txTime) {
		this.txTime = txTime;
	}

	public String getContactname() {
		return this.contactname;
	}

	public void setContactname(String contactname) {
		this.contactname = contactname;
	}

	public long getSerialReason() {
		return this.serialReason;
	}

	public void setSerialReason(long serialReason) {
		this.serialReason = serialReason;
	}

	public long getSerialStatus() {
		return this.serialStatus;
	}

	public void setSerialStatus(long serialStatus) {
		this.serialStatus = serialStatus;
	}

}