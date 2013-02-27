package com.kingstargroup.form;

/**
 * AbstractTDevmonitor entity provides the base persistence definition of the
 * TDevmonitor entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDevmonitor implements java.io.Serializable {

	// Fields

	private long deviceid;
	private String optime;
	private String coltime;
	private String devtime;
	private long beatstatus;
	private String cardverno;
	private long hardiskper;
	private long memoryper;
	private long cpuper;

	// Constructors

	/** default constructor */
	public AbstractTDevmonitor() {
	}

	/** minimal constructor */
	public AbstractTDevmonitor(long deviceid) {
		this.deviceid = deviceid;
	}

	/** full constructor */
	public AbstractTDevmonitor(long deviceid, String optime, String coltime,
			String devtime, long beatstatus, String cardverno, long hardiskper,
			long memoryper, long cpuper) {
		this.deviceid = deviceid;
		this.optime = optime;
		this.coltime = coltime;
		this.devtime = devtime;
		this.beatstatus = beatstatus;
		this.cardverno = cardverno;
		this.hardiskper = hardiskper;
		this.memoryper = memoryper;
		this.cpuper = cpuper;
	}

	// Property accessors

	public long getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(long deviceid) {
		this.deviceid = deviceid;
	}

	public String getOptime() {
		return this.optime;
	}

	public void setOptime(String optime) {
		this.optime = optime;
	}

	public String getColtime() {
		return this.coltime;
	}

	public void setColtime(String coltime) {
		this.coltime = coltime;
	}

	public String getDevtime() {
		return this.devtime;
	}

	public void setDevtime(String devtime) {
		this.devtime = devtime;
	}

	public long getBeatstatus() {
		return this.beatstatus;
	}

	public void setBeatstatus(long beatstatus) {
		this.beatstatus = beatstatus;
	}

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public long getHardiskper() {
		return this.hardiskper;
	}

	public void setHardiskper(long hardiskper) {
		this.hardiskper = hardiskper;
	}

	public long getMemoryper() {
		return this.memoryper;
	}

	public void setMemoryper(long memoryper) {
		this.memoryper = memoryper;
	}

	public long getCpuper() {
		return this.cpuper;
	}

	public void setCpuper(long cpuper) {
		this.cpuper = cpuper;
	}

}