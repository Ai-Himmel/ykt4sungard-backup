package org.king.business.domain;

/**
 * AbstractMonitorUnbalanceAccountHis entity provides the base persistence
 * definition of the MonitorUnbalanceAccountHis entity. @author MyEclipse
 * Persistence Tools
 */

public abstract class AbstractMonitorUnbalanceAccountHis extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private Integer id;
	private String accno;
	private String accname;
	private Integer custid;
	private Integer cardno;
	private Integer purseno;
	private Double availbal;
	private Double cardbal;
	private Integer dpscnt;
	private Integer paycnt;
	private String lasttransdate;
	private String enterdate;
	private String analysedate;
	private Integer lastdate;
	private Double unbalanceamount;
	private Double largestubamount;

	// Constructors

	/** default constructor */
	public AbstractMonitorUnbalanceAccountHis() {
	}

	/** full constructor */
	public AbstractMonitorUnbalanceAccountHis(String accno, String accname,
			Integer custid, Integer cardno, Integer purseno,
			Double availbal, Double cardbal, Integer dpscnt,
			Integer paycnt, String lasttransdate, String enterdate,
			String analysedate, Integer lastdate, Double unbalanceamount,
			Double largestubamount) {
		this.accno = accno;
		this.accname = accname;
		this.custid = custid;
		this.cardno = cardno;
		this.purseno = purseno;
		this.availbal = availbal;
		this.cardbal = cardbal;
		this.dpscnt = dpscnt;
		this.paycnt = paycnt;
		this.lasttransdate = lasttransdate;
		this.enterdate = enterdate;
		this.analysedate = analysedate;
		this.lastdate = lastdate;
		this.unbalanceamount = unbalanceamount;
		this.largestubamount = largestubamount;
	}

	// Property accessors

	public Integer getId() {
		return this.id;
	}

	public void setId(Integer id) {
		this.id = id;
	}

	public String getAccno() {
		return this.accno;
	}

	public void setAccno(String accno) {
		this.accno = accno;
	}

	public String getAccname() {
		return this.accname;
	}

	public void setAccname(String accname) {
		this.accname = accname;
	}

	public Integer getCustid() {
		return this.custid;
	}

	public void setCustid(Integer custid) {
		this.custid = custid;
	}

	public Integer getCardno() {
		return this.cardno;
	}

	public void setCardno(Integer cardno) {
		this.cardno = cardno;
	}

	public Integer getPurseno() {
		return this.purseno;
	}

	public void setPurseno(Integer purseno) {
		this.purseno = purseno;
	}

	public Double getAvailbal() {
		return this.availbal;
	}

	public void setAvailbal(Double availbal) {
		this.availbal = availbal;
	}

	public Double getCardbal() {
		return this.cardbal;
	}

	public void setCardbal(Double cardbal) {
		this.cardbal = cardbal;
	}

	public Integer getDpscnt() {
		return this.dpscnt;
	}

	public void setDpscnt(Integer dpscnt) {
		this.dpscnt = dpscnt;
	}

	public Integer getPaycnt() {
		return this.paycnt;
	}

	public void setPaycnt(Integer paycnt) {
		this.paycnt = paycnt;
	}

	public String getLasttransdate() {
		return this.lasttransdate;
	}

	public void setLasttransdate(String lasttransdate) {
		this.lasttransdate = lasttransdate;
	}

	public String getEnterdate() {
		return this.enterdate;
	}

	public void setEnterdate(String enterdate) {
		this.enterdate = enterdate;
	}

	public String getAnalysedate() {
		return this.analysedate;
	}

	public void setAnalysedate(String analysedate) {
		this.analysedate = analysedate;
	}

	public Integer getLastdate() {
		return this.lastdate;
	}

	public void setLastdate(Integer lastdate) {
		this.lastdate = lastdate;
	}

	public Double getUnbalanceamount() {
		return this.unbalanceamount;
	}

	public void setUnbalanceamount(Double unbalanceamount) {
		this.unbalanceamount = unbalanceamount;
	}

	public Double getLargestubamount() {
		return this.largestubamount;
	}

	public void setLargestubamount(Double largestubamount) {
		this.largestubamount = largestubamount;
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result + ((accname == null) ? 0 : accname.hashCode());
		result = prime * result + ((accno == null) ? 0 : accno.hashCode());
		result = prime * result
				+ ((analysedate == null) ? 0 : analysedate.hashCode());
		result = prime * result
				+ ((availbal == null) ? 0 : availbal.hashCode());
		result = prime * result + ((cardbal == null) ? 0 : cardbal.hashCode());
		result = prime * result + ((cardno == null) ? 0 : cardno.hashCode());
		result = prime * result + ((custid == null) ? 0 : custid.hashCode());
		result = prime * result + ((dpscnt == null) ? 0 : dpscnt.hashCode());
		result = prime * result
				+ ((enterdate == null) ? 0 : enterdate.hashCode());
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		result = prime * result
				+ ((largestubamount == null) ? 0 : largestubamount.hashCode());
		result = prime * result
				+ ((lastdate == null) ? 0 : lastdate.hashCode());
		result = prime * result
				+ ((lasttransdate == null) ? 0 : lasttransdate.hashCode());
		result = prime * result + ((paycnt == null) ? 0 : paycnt.hashCode());
		result = prime * result + ((purseno == null) ? 0 : purseno.hashCode());
		result = prime * result
				+ ((unbalanceamount == null) ? 0 : unbalanceamount.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (getClass() != obj.getClass())
			return false;
		AbstractMonitorUnbalanceAccountHis other = (AbstractMonitorUnbalanceAccountHis) obj;
		if (accname == null) {
			if (other.accname != null)
				return false;
		} else if (!accname.equals(other.accname))
			return false;
		if (accno == null) {
			if (other.accno != null)
				return false;
		} else if (!accno.equals(other.accno))
			return false;
		if (analysedate == null) {
			if (other.analysedate != null)
				return false;
		} else if (!analysedate.equals(other.analysedate))
			return false;
		if (availbal == null) {
			if (other.availbal != null)
				return false;
		} else if (!availbal.equals(other.availbal))
			return false;
		if (cardbal == null) {
			if (other.cardbal != null)
				return false;
		} else if (!cardbal.equals(other.cardbal))
			return false;
		if (cardno == null) {
			if (other.cardno != null)
				return false;
		} else if (!cardno.equals(other.cardno))
			return false;
		if (custid == null) {
			if (other.custid != null)
				return false;
		} else if (!custid.equals(other.custid))
			return false;
		if (dpscnt == null) {
			if (other.dpscnt != null)
				return false;
		} else if (!dpscnt.equals(other.dpscnt))
			return false;
		if (enterdate == null) {
			if (other.enterdate != null)
				return false;
		} else if (!enterdate.equals(other.enterdate))
			return false;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		if (largestubamount == null) {
			if (other.largestubamount != null)
				return false;
		} else if (!largestubamount.equals(other.largestubamount))
			return false;
		if (lastdate == null) {
			if (other.lastdate != null)
				return false;
		} else if (!lastdate.equals(other.lastdate))
			return false;
		if (lasttransdate == null) {
			if (other.lasttransdate != null)
				return false;
		} else if (!lasttransdate.equals(other.lasttransdate))
			return false;
		if (paycnt == null) {
			if (other.paycnt != null)
				return false;
		} else if (!paycnt.equals(other.paycnt))
			return false;
		if (purseno == null) {
			if (other.purseno != null)
				return false;
		} else if (!purseno.equals(other.purseno))
			return false;
		if (unbalanceamount == null) {
			if (other.unbalanceamount != null)
				return false;
		} else if (!unbalanceamount.equals(other.unbalanceamount))
			return false;
		return true;
	}

	@Override
	public String toString() {
		return "AbstractMonitorUnbalanceAccountHis [accname=" + accname
				+ ", accno=" + accno + ", analysedate=" + analysedate
				+ ", availbal=" + availbal + ", cardbal=" + cardbal
				+ ", cardno=" + cardno + ", custid=" + custid + ", dpscnt="
				+ dpscnt + ", enterdate=" + enterdate + ", id=" + id
				+ ", largestubamount=" + largestubamount + ", lastdate="
				+ lastdate + ", lasttransdate=" + lasttransdate + ", paycnt="
				+ paycnt + ", purseno=" + purseno + ", unbalanceamount="
				+ unbalanceamount + "]";
	}
}