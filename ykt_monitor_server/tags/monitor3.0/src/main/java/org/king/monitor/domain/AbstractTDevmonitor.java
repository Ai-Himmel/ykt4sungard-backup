package org.king.monitor.domain;

import java.math.BigDecimal;

/**
 * AbstractTDevmonitor entity provides the base persistence definition of the
 * TDevmonitor entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractTDevmonitor extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer deviceid;
	private String optime;
	private String coltime;
	private String devtime;
	private Integer beatstatus;
	private String cardverno;
	private Integer hardiskper;
	private Integer memoryper;
	private Integer cpuper;

	// Constructors

	/** default constructor */
	public AbstractTDevmonitor() {
	}

	/** minimal constructor */
	public AbstractTDevmonitor(Integer deviceid) {
		this.deviceid = deviceid;
	}

	/** full constructor */
	public AbstractTDevmonitor(Integer deviceid, String optime,
			String coltime, String devtime, Integer beatstatus,
			String cardverno, Integer hardiskper, Integer memoryper,
			Integer cpuper) {
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

	public Integer getDeviceid() {
		return this.deviceid;
	}

	public void setDeviceid(Integer deviceid) {
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

	public Integer getBeatstatus() {
		return this.beatstatus;
	}

	public void setBeatstatus(Integer beatstatus) {
		this.beatstatus = beatstatus;
	}

	public String getCardverno() {
		return this.cardverno;
	}

	public void setCardverno(String cardverno) {
		this.cardverno = cardverno;
	}

	public Integer getHardiskper() {
		return this.hardiskper;
	}

	public void setHardiskper(Integer hardiskper) {
		this.hardiskper = hardiskper;
	}

	public Integer getMemoryper() {
		return this.memoryper;
	}

	public void setMemoryper(Integer memoryper) {
		this.memoryper = memoryper;
	}

	public Integer getCpuper() {
		return this.cpuper;
	}

	public void setCpuper(Integer cpuper) {
		this.cpuper = cpuper;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((beatstatus == null) ? 0 : beatstatus.hashCode());
		result = prime * result
				+ ((cardverno == null) ? 0 : cardverno.hashCode());
		result = prime * result + ((coltime == null) ? 0 : coltime.hashCode());
		result = prime * result + ((cpuper == null) ? 0 : cpuper.hashCode());
		result = prime * result
				+ ((deviceid == null) ? 0 : deviceid.hashCode());
		result = prime * result + ((devtime == null) ? 0 : devtime.hashCode());
		result = prime * result
				+ ((hardiskper == null) ? 0 : hardiskper.hashCode());
		result = prime * result
				+ ((memoryper == null) ? 0 : memoryper.hashCode());
		result = prime * result + ((optime == null) ? 0 : optime.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractTDevmonitor))
			return false;
		AbstractTDevmonitor other = (AbstractTDevmonitor) obj;
		if (beatstatus == null) {
			if (other.beatstatus != null)
				return false;
		} else if (!beatstatus.equals(other.beatstatus))
			return false;
		if (cardverno == null) {
			if (other.cardverno != null)
				return false;
		} else if (!cardverno.equals(other.cardverno))
			return false;
		if (coltime == null) {
			if (other.coltime != null)
				return false;
		} else if (!coltime.equals(other.coltime))
			return false;
		if (cpuper == null) {
			if (other.cpuper != null)
				return false;
		} else if (!cpuper.equals(other.cpuper))
			return false;
		if (deviceid == null) {
			if (other.deviceid != null)
				return false;
		} else if (!deviceid.equals(other.deviceid))
			return false;
		if (devtime == null) {
			if (other.devtime != null)
				return false;
		} else if (!devtime.equals(other.devtime))
			return false;
		if (hardiskper == null) {
			if (other.hardiskper != null)
				return false;
		} else if (!hardiskper.equals(other.hardiskper))
			return false;
		if (memoryper == null) {
			if (other.memoryper != null)
				return false;
		} else if (!memoryper.equals(other.memoryper))
			return false;
		if (optime == null) {
			if (other.optime != null)
				return false;
		} else if (!optime.equals(other.optime))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractTDevmonitor [beatstatus=" + beatstatus + ", cardverno="
				+ cardverno + ", coltime=" + coltime + ", cpuper=" + cpuper
				+ ", deviceid=" + deviceid + ", devtime=" + devtime
				+ ", hardiskper=" + hardiskper + ", memoryper=" + memoryper
				+ ", optime=" + optime + "]";
	}

}