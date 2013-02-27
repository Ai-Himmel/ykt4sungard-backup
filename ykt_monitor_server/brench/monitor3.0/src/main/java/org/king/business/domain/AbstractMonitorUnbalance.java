package org.king.business.domain;

/**
 * AbstractMonitorUnbalance entity provides the base persistence definition of
 * the MonitorUnbalance entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorUnbalance extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private String recdate;
	private Integer stm100acc;
	private Double stm100amt;
	private Integer stm100accchange;
	private Double stm100amtchange;
	private Integer stm50acc;
	private Double stm50amt;
	private Integer stm50accchange;
	private Double stm50amtchange;
	private Integer stm10acc;
	private Double stm10amt;
	private Integer stm10accchange;
	private Double stm10amtchange;
	private Integer stm1acc;
	private Double stm1amt;
	private Integer stm1accchange;
	private Double stm1amtchange;
	private Integer stm0acc;
	private Double stm0amt;
	private Integer stm0accchange;
	private Double stm0amtchange;
	private Integer st1acc;
	private Double st1amt;
	private Integer st1accchange;
	private Double st1amtchange;
	private Integer st10acc;
	private Double st10amt;
	private Integer st10accchange;
	private Double st10amtchange;
	private Integer st50acc;
	private Double st50amt;
	private Integer st50accchange;
	private Double st50amtchange;
	private Integer st100acc;
	private Double st100amt;
	private Integer st100accchange;
	private Double st100amtchange;
	private Integer lt100acc;
	private Double lt100amt;
	private Integer lt100accchange;
	private Double lt100amtchange;
	private Integer totalacc;
	private Double totalamt;
	private Double totalabsamt;

	// Constructors

	/** default constructor */
	public AbstractMonitorUnbalance() {
	}

	/** full constructor */
	public AbstractMonitorUnbalance(Integer stm100acc, Double stm100amt,
			Integer stm100accchange, Double stm100amtchange,
			Integer stm50acc, Double stm50amt, Integer stm50accchange,
			Double stm50amtchange, Integer stm10acc, Double stm10amt,
			Integer stm10accchange, Double stm10amtchange,
			Integer stm1acc, Double stm1amt, Integer stm1accchange,
			Double stm1amtchange, Integer stm0acc, Double stm0amt,
			Integer stm0accchange, Double stm0amtchange, Integer st1acc,
			Double st1amt, Integer st1accchange, Double st1amtchange,
			Integer st10acc, Double st10amt, Integer st10accchange,
			Double st10amtchange, Integer st50acc, Double st50amt,
			Integer st50accchange, Double st50amtchange,
			Integer st100acc, Double st100amt, Integer st100accchange,
			Double st100amtchange, Integer lt100acc, Double lt100amt,
			Integer lt100accchange, Double lt100amtchange,
			Integer totalacc, Double totalamt, Double totalabsamt) {
		this.stm100acc = stm100acc;
		this.stm100amt = stm100amt;
		this.stm100accchange = stm100accchange;
		this.stm100amtchange = stm100amtchange;
		this.stm50acc = stm50acc;
		this.stm50amt = stm50amt;
		this.stm50accchange = stm50accchange;
		this.stm50amtchange = stm50amtchange;
		this.stm10acc = stm10acc;
		this.stm10amt = stm10amt;
		this.stm10accchange = stm10accchange;
		this.stm10amtchange = stm10amtchange;
		this.stm1acc = stm1acc;
		this.stm1amt = stm1amt;
		this.stm1accchange = stm1accchange;
		this.stm1amtchange = stm1amtchange;
		this.stm0acc = stm0acc;
		this.stm0amt = stm0amt;
		this.stm0accchange = stm0accchange;
		this.stm0amtchange = stm0amtchange;
		this.st1acc = st1acc;
		this.st1amt = st1amt;
		this.st1accchange = st1accchange;
		this.st1amtchange = st1amtchange;
		this.st10acc = st10acc;
		this.st10amt = st10amt;
		this.st10accchange = st10accchange;
		this.st10amtchange = st10amtchange;
		this.st50acc = st50acc;
		this.st50amt = st50amt;
		this.st50accchange = st50accchange;
		this.st50amtchange = st50amtchange;
		this.st100acc = st100acc;
		this.st100amt = st100amt;
		this.st100accchange = st100accchange;
		this.st100amtchange = st100amtchange;
		this.lt100acc = lt100acc;
		this.lt100amt = lt100amt;
		this.lt100accchange = lt100accchange;
		this.lt100amtchange = lt100amtchange;
		this.totalacc = totalacc;
		this.totalamt = totalamt;
		this.totalabsamt = totalabsamt;
	}

	// Property accessors

	public String getRecdate() {
		return this.recdate;
	}

	public void setRecdate(String recdate) {
		this.recdate = recdate;
	}

	public Integer getStm100acc() {
		return this.stm100acc;
	}

	public void setStm100acc(Integer stm100acc) {
		this.stm100acc = stm100acc;
	}

	public Double getStm100amt() {
		return this.stm100amt;
	}

	public void setStm100amt(Double stm100amt) {
		this.stm100amt = stm100amt;
	}

	public Integer getStm100accchange() {
		return this.stm100accchange;
	}

	public void setStm100accchange(Integer stm100accchange) {
		this.stm100accchange = stm100accchange;
	}

	public Double getStm100amtchange() {
		return this.stm100amtchange;
	}

	public void setStm100amtchange(Double stm100amtchange) {
		this.stm100amtchange = stm100amtchange;
	}

	public Integer getStm50acc() {
		return this.stm50acc;
	}

	public void setStm50acc(Integer stm50acc) {
		this.stm50acc = stm50acc;
	}

	public Double getStm50amt() {
		return this.stm50amt;
	}

	public void setStm50amt(Double stm50amt) {
		this.stm50amt = stm50amt;
	}

	public Integer getStm50accchange() {
		return this.stm50accchange;
	}

	public void setStm50accchange(Integer stm50accchange) {
		this.stm50accchange = stm50accchange;
	}

	public Double getStm50amtchange() {
		return this.stm50amtchange;
	}

	public void setStm50amtchange(Double stm50amtchange) {
		this.stm50amtchange = stm50amtchange;
	}

	public Integer getStm10acc() {
		return this.stm10acc;
	}

	public void setStm10acc(Integer stm10acc) {
		this.stm10acc = stm10acc;
	}

	public Double getStm10amt() {
		return this.stm10amt;
	}

	public void setStm10amt(Double stm10amt) {
		this.stm10amt = stm10amt;
	}

	public Integer getStm10accchange() {
		return this.stm10accchange;
	}

	public void setStm10accchange(Integer stm10accchange) {
		this.stm10accchange = stm10accchange;
	}

	public Double getStm10amtchange() {
		return this.stm10amtchange;
	}

	public void setStm10amtchange(Double stm10amtchange) {
		this.stm10amtchange = stm10amtchange;
	}

	public Integer getStm1acc() {
		return this.stm1acc;
	}

	public void setStm1acc(Integer stm1acc) {
		this.stm1acc = stm1acc;
	}

	public Double getStm1amt() {
		return this.stm1amt;
	}

	public void setStm1amt(Double stm1amt) {
		this.stm1amt = stm1amt;
	}

	public Integer getStm1accchange() {
		return this.stm1accchange;
	}

	public void setStm1accchange(Integer stm1accchange) {
		this.stm1accchange = stm1accchange;
	}

	public Double getStm1amtchange() {
		return this.stm1amtchange;
	}

	public void setStm1amtchange(Double stm1amtchange) {
		this.stm1amtchange = stm1amtchange;
	}

	public Integer getStm0acc() {
		return this.stm0acc;
	}

	public void setStm0acc(Integer stm0acc) {
		this.stm0acc = stm0acc;
	}

	public Double getStm0amt() {
		return this.stm0amt;
	}

	public void setStm0amt(Double stm0amt) {
		this.stm0amt = stm0amt;
	}

	public Integer getStm0accchange() {
		return this.stm0accchange;
	}

	public void setStm0accchange(Integer stm0accchange) {
		this.stm0accchange = stm0accchange;
	}

	public Double getStm0amtchange() {
		return this.stm0amtchange;
	}

	public void setStm0amtchange(Double stm0amtchange) {
		this.stm0amtchange = stm0amtchange;
	}

	public Integer getSt1acc() {
		return this.st1acc;
	}

	public void setSt1acc(Integer st1acc) {
		this.st1acc = st1acc;
	}

	public Double getSt1amt() {
		return this.st1amt;
	}

	public void setSt1amt(Double st1amt) {
		this.st1amt = st1amt;
	}

	public Integer getSt1accchange() {
		return this.st1accchange;
	}

	public void setSt1accchange(Integer st1accchange) {
		this.st1accchange = st1accchange;
	}

	public Double getSt1amtchange() {
		return this.st1amtchange;
	}

	public void setSt1amtchange(Double st1amtchange) {
		this.st1amtchange = st1amtchange;
	}

	public Integer getSt10acc() {
		return this.st10acc;
	}

	public void setSt10acc(Integer st10acc) {
		this.st10acc = st10acc;
	}

	public Double getSt10amt() {
		return this.st10amt;
	}

	public void setSt10amt(Double st10amt) {
		this.st10amt = st10amt;
	}

	public Integer getSt10accchange() {
		return this.st10accchange;
	}

	public void setSt10accchange(Integer st10accchange) {
		this.st10accchange = st10accchange;
	}

	public Double getSt10amtchange() {
		return this.st10amtchange;
	}

	public void setSt10amtchange(Double st10amtchange) {
		this.st10amtchange = st10amtchange;
	}

	public Integer getSt50acc() {
		return this.st50acc;
	}

	public void setSt50acc(Integer st50acc) {
		this.st50acc = st50acc;
	}

	public Double getSt50amt() {
		return this.st50amt;
	}

	public void setSt50amt(Double st50amt) {
		this.st50amt = st50amt;
	}

	public Integer getSt50accchange() {
		return this.st50accchange;
	}

	public void setSt50accchange(Integer st50accchange) {
		this.st50accchange = st50accchange;
	}

	public Double getSt50amtchange() {
		return this.st50amtchange;
	}

	public void setSt50amtchange(Double st50amtchange) {
		this.st50amtchange = st50amtchange;
	}

	public Integer getSt100acc() {
		return this.st100acc;
	}

	public void setSt100acc(Integer st100acc) {
		this.st100acc = st100acc;
	}

	public Double getSt100amt() {
		return this.st100amt;
	}

	public void setSt100amt(Double st100amt) {
		this.st100amt = st100amt;
	}

	public Integer getSt100accchange() {
		return this.st100accchange;
	}

	public void setSt100accchange(Integer st100accchange) {
		this.st100accchange = st100accchange;
	}

	public Double getSt100amtchange() {
		return this.st100amtchange;
	}

	public void setSt100amtchange(Double st100amtchange) {
		this.st100amtchange = st100amtchange;
	}

	public Integer getLt100acc() {
		return this.lt100acc;
	}

	public void setLt100acc(Integer lt100acc) {
		this.lt100acc = lt100acc;
	}

	public Double getLt100amt() {
		return this.lt100amt;
	}

	public void setLt100amt(Double lt100amt) {
		this.lt100amt = lt100amt;
	}

	public Integer getLt100accchange() {
		return this.lt100accchange;
	}

	public void setLt100accchange(Integer lt100accchange) {
		this.lt100accchange = lt100accchange;
	}

	public Double getLt100amtchange() {
		return this.lt100amtchange;
	}

	public void setLt100amtchange(Double lt100amtchange) {
		this.lt100amtchange = lt100amtchange;
	}

	public Integer getTotalacc() {
		return this.totalacc;
	}

	public void setTotalacc(Integer totalacc) {
		this.totalacc = totalacc;
	}

	public Double getTotalamt() {
		return this.totalamt;
	}

	public void setTotalamt(Double totalamt) {
		this.totalamt = totalamt;
	}

	public Double getTotalabsamt() {
		return this.totalabsamt;
	}

	public void setTotalabsamt(Double totalabsamt) {
		this.totalabsamt = totalabsamt;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((lt100acc == null) ? 0 : lt100acc.hashCode());
		result = prime * result
				+ ((lt100accchange == null) ? 0 : lt100accchange.hashCode());
		result = prime * result
				+ ((lt100amt == null) ? 0 : lt100amt.hashCode());
		result = prime * result
				+ ((lt100amtchange == null) ? 0 : lt100amtchange.hashCode());
		result = prime * result + ((recdate == null) ? 0 : recdate.hashCode());
		result = prime * result
				+ ((st100acc == null) ? 0 : st100acc.hashCode());
		result = prime * result
				+ ((st100accchange == null) ? 0 : st100accchange.hashCode());
		result = prime * result
				+ ((st100amt == null) ? 0 : st100amt.hashCode());
		result = prime * result
				+ ((st100amtchange == null) ? 0 : st100amtchange.hashCode());
		result = prime * result + ((st10acc == null) ? 0 : st10acc.hashCode());
		result = prime * result
				+ ((st10accchange == null) ? 0 : st10accchange.hashCode());
		result = prime * result + ((st10amt == null) ? 0 : st10amt.hashCode());
		result = prime * result
				+ ((st10amtchange == null) ? 0 : st10amtchange.hashCode());
		result = prime * result + ((st1acc == null) ? 0 : st1acc.hashCode());
		result = prime * result
				+ ((st1accchange == null) ? 0 : st1accchange.hashCode());
		result = prime * result + ((st1amt == null) ? 0 : st1amt.hashCode());
		result = prime * result
				+ ((st1amtchange == null) ? 0 : st1amtchange.hashCode());
		result = prime * result + ((st50acc == null) ? 0 : st50acc.hashCode());
		result = prime * result
				+ ((st50accchange == null) ? 0 : st50accchange.hashCode());
		result = prime * result + ((st50amt == null) ? 0 : st50amt.hashCode());
		result = prime * result
				+ ((st50amtchange == null) ? 0 : st50amtchange.hashCode());
		result = prime * result + ((stm0acc == null) ? 0 : stm0acc.hashCode());
		result = prime * result
				+ ((stm0accchange == null) ? 0 : stm0accchange.hashCode());
		result = prime * result + ((stm0amt == null) ? 0 : stm0amt.hashCode());
		result = prime * result
				+ ((stm0amtchange == null) ? 0 : stm0amtchange.hashCode());
		result = prime * result
				+ ((stm100acc == null) ? 0 : stm100acc.hashCode());
		result = prime * result
				+ ((stm100accchange == null) ? 0 : stm100accchange.hashCode());
		result = prime * result
				+ ((stm100amt == null) ? 0 : stm100amt.hashCode());
		result = prime * result
				+ ((stm100amtchange == null) ? 0 : stm100amtchange.hashCode());
		result = prime * result
				+ ((stm10acc == null) ? 0 : stm10acc.hashCode());
		result = prime * result
				+ ((stm10accchange == null) ? 0 : stm10accchange.hashCode());
		result = prime * result
				+ ((stm10amt == null) ? 0 : stm10amt.hashCode());
		result = prime * result
				+ ((stm10amtchange == null) ? 0 : stm10amtchange.hashCode());
		result = prime * result + ((stm1acc == null) ? 0 : stm1acc.hashCode());
		result = prime * result
				+ ((stm1accchange == null) ? 0 : stm1accchange.hashCode());
		result = prime * result + ((stm1amt == null) ? 0 : stm1amt.hashCode());
		result = prime * result
				+ ((stm1amtchange == null) ? 0 : stm1amtchange.hashCode());
		result = prime * result
				+ ((stm50acc == null) ? 0 : stm50acc.hashCode());
		result = prime * result
				+ ((stm50accchange == null) ? 0 : stm50accchange.hashCode());
		result = prime * result
				+ ((stm50amt == null) ? 0 : stm50amt.hashCode());
		result = prime * result
				+ ((stm50amtchange == null) ? 0 : stm50amtchange.hashCode());
		result = prime * result
				+ ((totalabsamt == null) ? 0 : totalabsamt.hashCode());
		result = prime * result
				+ ((totalacc == null) ? 0 : totalacc.hashCode());
		result = prime * result
				+ ((totalamt == null) ? 0 : totalamt.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (getClass() != obj.getClass())
			return false;
		AbstractMonitorUnbalance other = (AbstractMonitorUnbalance) obj;
		if (lt100acc == null) {
			if (other.lt100acc != null)
				return false;
		} else if (!lt100acc.equals(other.lt100acc))
			return false;
		if (lt100accchange == null) {
			if (other.lt100accchange != null)
				return false;
		} else if (!lt100accchange.equals(other.lt100accchange))
			return false;
		if (lt100amt == null) {
			if (other.lt100amt != null)
				return false;
		} else if (!lt100amt.equals(other.lt100amt))
			return false;
		if (lt100amtchange == null) {
			if (other.lt100amtchange != null)
				return false;
		} else if (!lt100amtchange.equals(other.lt100amtchange))
			return false;
		if (recdate == null) {
			if (other.recdate != null)
				return false;
		} else if (!recdate.equals(other.recdate))
			return false;
		if (st100acc == null) {
			if (other.st100acc != null)
				return false;
		} else if (!st100acc.equals(other.st100acc))
			return false;
		if (st100accchange == null) {
			if (other.st100accchange != null)
				return false;
		} else if (!st100accchange.equals(other.st100accchange))
			return false;
		if (st100amt == null) {
			if (other.st100amt != null)
				return false;
		} else if (!st100amt.equals(other.st100amt))
			return false;
		if (st100amtchange == null) {
			if (other.st100amtchange != null)
				return false;
		} else if (!st100amtchange.equals(other.st100amtchange))
			return false;
		if (st10acc == null) {
			if (other.st10acc != null)
				return false;
		} else if (!st10acc.equals(other.st10acc))
			return false;
		if (st10accchange == null) {
			if (other.st10accchange != null)
				return false;
		} else if (!st10accchange.equals(other.st10accchange))
			return false;
		if (st10amt == null) {
			if (other.st10amt != null)
				return false;
		} else if (!st10amt.equals(other.st10amt))
			return false;
		if (st10amtchange == null) {
			if (other.st10amtchange != null)
				return false;
		} else if (!st10amtchange.equals(other.st10amtchange))
			return false;
		if (st1acc == null) {
			if (other.st1acc != null)
				return false;
		} else if (!st1acc.equals(other.st1acc))
			return false;
		if (st1accchange == null) {
			if (other.st1accchange != null)
				return false;
		} else if (!st1accchange.equals(other.st1accchange))
			return false;
		if (st1amt == null) {
			if (other.st1amt != null)
				return false;
		} else if (!st1amt.equals(other.st1amt))
			return false;
		if (st1amtchange == null) {
			if (other.st1amtchange != null)
				return false;
		} else if (!st1amtchange.equals(other.st1amtchange))
			return false;
		if (st50acc == null) {
			if (other.st50acc != null)
				return false;
		} else if (!st50acc.equals(other.st50acc))
			return false;
		if (st50accchange == null) {
			if (other.st50accchange != null)
				return false;
		} else if (!st50accchange.equals(other.st50accchange))
			return false;
		if (st50amt == null) {
			if (other.st50amt != null)
				return false;
		} else if (!st50amt.equals(other.st50amt))
			return false;
		if (st50amtchange == null) {
			if (other.st50amtchange != null)
				return false;
		} else if (!st50amtchange.equals(other.st50amtchange))
			return false;
		if (stm0acc == null) {
			if (other.stm0acc != null)
				return false;
		} else if (!stm0acc.equals(other.stm0acc))
			return false;
		if (stm0accchange == null) {
			if (other.stm0accchange != null)
				return false;
		} else if (!stm0accchange.equals(other.stm0accchange))
			return false;
		if (stm0amt == null) {
			if (other.stm0amt != null)
				return false;
		} else if (!stm0amt.equals(other.stm0amt))
			return false;
		if (stm0amtchange == null) {
			if (other.stm0amtchange != null)
				return false;
		} else if (!stm0amtchange.equals(other.stm0amtchange))
			return false;
		if (stm100acc == null) {
			if (other.stm100acc != null)
				return false;
		} else if (!stm100acc.equals(other.stm100acc))
			return false;
		if (stm100accchange == null) {
			if (other.stm100accchange != null)
				return false;
		} else if (!stm100accchange.equals(other.stm100accchange))
			return false;
		if (stm100amt == null) {
			if (other.stm100amt != null)
				return false;
		} else if (!stm100amt.equals(other.stm100amt))
			return false;
		if (stm100amtchange == null) {
			if (other.stm100amtchange != null)
				return false;
		} else if (!stm100amtchange.equals(other.stm100amtchange))
			return false;
		if (stm10acc == null) {
			if (other.stm10acc != null)
				return false;
		} else if (!stm10acc.equals(other.stm10acc))
			return false;
		if (stm10accchange == null) {
			if (other.stm10accchange != null)
				return false;
		} else if (!stm10accchange.equals(other.stm10accchange))
			return false;
		if (stm10amt == null) {
			if (other.stm10amt != null)
				return false;
		} else if (!stm10amt.equals(other.stm10amt))
			return false;
		if (stm10amtchange == null) {
			if (other.stm10amtchange != null)
				return false;
		} else if (!stm10amtchange.equals(other.stm10amtchange))
			return false;
		if (stm1acc == null) {
			if (other.stm1acc != null)
				return false;
		} else if (!stm1acc.equals(other.stm1acc))
			return false;
		if (stm1accchange == null) {
			if (other.stm1accchange != null)
				return false;
		} else if (!stm1accchange.equals(other.stm1accchange))
			return false;
		if (stm1amt == null) {
			if (other.stm1amt != null)
				return false;
		} else if (!stm1amt.equals(other.stm1amt))
			return false;
		if (stm1amtchange == null) {
			if (other.stm1amtchange != null)
				return false;
		} else if (!stm1amtchange.equals(other.stm1amtchange))
			return false;
		if (stm50acc == null) {
			if (other.stm50acc != null)
				return false;
		} else if (!stm50acc.equals(other.stm50acc))
			return false;
		if (stm50accchange == null) {
			if (other.stm50accchange != null)
				return false;
		} else if (!stm50accchange.equals(other.stm50accchange))
			return false;
		if (stm50amt == null) {
			if (other.stm50amt != null)
				return false;
		} else if (!stm50amt.equals(other.stm50amt))
			return false;
		if (stm50amtchange == null) {
			if (other.stm50amtchange != null)
				return false;
		} else if (!stm50amtchange.equals(other.stm50amtchange))
			return false;
		if (totalabsamt == null) {
			if (other.totalabsamt != null)
				return false;
		} else if (!totalabsamt.equals(other.totalabsamt))
			return false;
		if (totalacc == null) {
			if (other.totalacc != null)
				return false;
		} else if (!totalacc.equals(other.totalacc))
			return false;
		if (totalamt == null) {
			if (other.totalamt != null)
				return false;
		} else if (!totalamt.equals(other.totalamt))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorUnbalance [lt100acc=" + lt100acc
				+ ", lt100accchange=" + lt100accchange + ", lt100amt="
				+ lt100amt + ", lt100amtchange=" + lt100amtchange
				+ ", recdate=" + recdate + ", st100acc=" + st100acc
				+ ", st100accchange=" + st100accchange + ", st100amt="
				+ st100amt + ", st100amtchange=" + st100amtchange
				+ ", st10acc=" + st10acc + ", st10accchange=" + st10accchange
				+ ", st10amt=" + st10amt + ", st10amtchange=" + st10amtchange
				+ ", st1acc=" + st1acc + ", st1accchange=" + st1accchange
				+ ", st1amt=" + st1amt + ", st1amtchange=" + st1amtchange
				+ ", st50acc=" + st50acc + ", st50accchange=" + st50accchange
				+ ", st50amt=" + st50amt + ", st50amtchange=" + st50amtchange
				+ ", stm0acc=" + stm0acc + ", stm0accchange=" + stm0accchange
				+ ", stm0amt=" + stm0amt + ", stm0amtchange=" + stm0amtchange
				+ ", stm100acc=" + stm100acc + ", stm100accchange="
				+ stm100accchange + ", stm100amt=" + stm100amt
				+ ", stm100amtchange=" + stm100amtchange + ", stm10acc="
				+ stm10acc + ", stm10accchange=" + stm10accchange
				+ ", stm10amt=" + stm10amt + ", stm10amtchange="
				+ stm10amtchange + ", stm1acc=" + stm1acc + ", stm1accchange="
				+ stm1accchange + ", stm1amt=" + stm1amt + ", stm1amtchange="
				+ stm1amtchange + ", stm50acc=" + stm50acc
				+ ", stm50accchange=" + stm50accchange + ", stm50amt="
				+ stm50amt + ", stm50amtchange=" + stm50amtchange
				+ ", totalabsamt=" + totalabsamt + ", totalacc=" + totalacc
				+ ", totalamt=" + totalamt + "]";
	}
}