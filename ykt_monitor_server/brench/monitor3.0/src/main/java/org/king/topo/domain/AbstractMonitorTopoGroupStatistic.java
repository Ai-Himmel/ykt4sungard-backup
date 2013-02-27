package org.king.topo.domain;



/**
 * AbstractMonitorTopoGroupStatistic entity provides the base persistence definition of the MonitorTopoGroupStatistic entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorTopoGroupStatistic extends org.king.framework.domain.BaseObject implements java.io.Serializable {


    // Fields    

     private Integer id;
     private String wordinfo;
     private String hintinfo;
     private Integer status;
     private String lastupdate;
     
     private MonitorTopoDevgroupInfo monitorTopoDevgroupInfo = new MonitorTopoDevgroupInfo();


    // Constructors

    /** default constructor */
    public AbstractMonitorTopoGroupStatistic() {
    }

	/** minimal constructor */
    public AbstractMonitorTopoGroupStatistic(Integer id) {
        this.id = id;
    }
    
    /** full constructor */
    public AbstractMonitorTopoGroupStatistic(Integer id, String wordinfo, String hintinfo, Integer status, String lastupdate) {
        this.id = id;
        this.wordinfo = wordinfo;
        this.hintinfo = hintinfo;
        this.status = status;
        this.lastupdate = lastupdate;
    }

   


	public MonitorTopoDevgroupInfo getMonitorTopoDevgroupInfo() {
		return monitorTopoDevgroupInfo;
	}

	public void setMonitorTopoDevgroupInfo(
			MonitorTopoDevgroupInfo monitorTopoDevgroupInfo) {
		this.monitorTopoDevgroupInfo = monitorTopoDevgroupInfo;
	}

	public Integer getId() {
        return this.id;
    }
    
    public void setId(Integer id) {
        this.id = id;
    }

    public String getWordinfo() {
        return this.wordinfo;
    }
    
    public void setWordinfo(String wordinfo) {
        this.wordinfo = wordinfo;
    }

    public String getHintinfo() {
        return this.hintinfo;
    }
    
    public void setHintinfo(String hintinfo) {
        this.hintinfo = hintinfo;
    }

    public Integer getStatus() {
        return this.status;
    }
    
    public void setStatus(Integer status) {
        this.status = status;
    }

    public String getLastupdate() {
        return this.lastupdate;
    }
    
    public void setLastupdate(String lastupdate) {
        this.lastupdate = lastupdate;
    }

	@Override
	public String toString() {
		return "AbstractMonitorTopoGroupStatistic [hintinfo=" + hintinfo
				+ ", id=" + id + ", lastupdate=" + lastupdate + ", status="
				+ status + ", wordinfo=" + wordinfo + "]";
	}

	@Override
	public int hashCode() {
		final int prime = 31;
		int result = 0;
		result = prime * result
				+ ((hintinfo == null) ? 0 : hintinfo.hashCode());
		result = prime * result + ((id == null) ? 0 : id.hashCode());
		result = prime * result
				+ ((lastupdate == null) ? 0 : lastupdate.hashCode());
		result = prime * result + ((status == null) ? 0 : status.hashCode());
		result = prime * result
				+ ((wordinfo == null) ? 0 : wordinfo.hashCode());
		return result;
	}

	@Override
	public boolean equals(Object obj) {
		if (this == obj)
			return true;
		if (!(obj instanceof AbstractMonitorTopoGroupStatistic))
			return false;
		AbstractMonitorTopoGroupStatistic other = (AbstractMonitorTopoGroupStatistic) obj;
		if (hintinfo == null) {
			if (other.hintinfo != null)
				return false;
		} else if (!hintinfo.equals(other.hintinfo))
			return false;
		if (id == null) {
			if (other.id != null)
				return false;
		} else if (!id.equals(other.id))
			return false;
		if (lastupdate == null) {
			if (other.lastupdate != null)
				return false;
		} else if (!lastupdate.equals(other.lastupdate))
			return false;
		if (status == null) {
			if (other.status != null)
				return false;
		} else if (!status.equals(other.status))
			return false;
		if (wordinfo == null) {
			if (other.wordinfo != null)
				return false;
		} else if (!wordinfo.equals(other.wordinfo))
			return false;
		return true;
	}
   








}