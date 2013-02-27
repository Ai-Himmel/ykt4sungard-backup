package org.king.host.domain;


/**
 * AbstractMonitorHostgroups entity provides the base persistence definition of
 * the MonitorHostgroups entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorHostgroups extends
        org.king.framework.domain.BaseObject implements java.io.Serializable {

    // Fields

    private Integer hostgroupId;
    private String groupName;

    // Constructors

    /**
     * default constructor
     */
    public AbstractMonitorHostgroups() {
    }

    /**
     * full constructor
     */
    public AbstractMonitorHostgroups(String groupName) {
        this.groupName = groupName;
    }

    // Property accessors

    public Integer getHostgroupId() {
        return this.hostgroupId;
    }

    public void setHostgroupId(Integer hostgroupId) {
        this.hostgroupId = hostgroupId;
    }

    public String getGroupName() {
        return this.groupName;
    }

    public void setGroupName(String groupName) {
        this.groupName = groupName;
    }

    @Override
    public String toString() {
        return "AbstractMonitorHostgroups [groupName=" + groupName
                + ", hostgroupId=" + hostgroupId + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 0;
        result = prime * result
                + ((groupName == null) ? 0 : groupName.hashCode());
        result = prime * result
                + ((hostgroupId == null) ? 0 : hostgroupId.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (!(obj instanceof AbstractMonitorHostgroups))
            return false;
        AbstractMonitorHostgroups other = (AbstractMonitorHostgroups) obj;
        if (groupName == null) {
            if (other.groupName != null)
                return false;
        } else if (!groupName.equals(other.groupName))
            return false;
        if (hostgroupId == null) {
            if (other.hostgroupId != null)
                return false;
        } else if (!hostgroupId.equals(other.hostgroupId))
            return false;
        return true;
	}

}