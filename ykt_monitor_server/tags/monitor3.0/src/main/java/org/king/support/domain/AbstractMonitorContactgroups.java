package org.king.support.domain;

/**
 * AbstractMonitorContactgroups entity provides the base persistence definition
 * of the MonitorContactgroups entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorContactgroups extends
        org.king.framework.domain.BaseObject implements java.io.Serializable {

    // Fields

    private Integer contactgroupId;
    private String contactgroupName;

    // Constructors

    /**
     * default constructor
     */
    public AbstractMonitorContactgroups() {
    }

    /**
     * full constructor
     */
    public AbstractMonitorContactgroups(String contactgroupName) {
        this.contactgroupName = contactgroupName;
    }

    // Property accessors

    public Integer getContactgroupId() {
        return this.contactgroupId;
    }

    public void setContactgroupId(Integer contactgroupId) {
        this.contactgroupId = contactgroupId;
    }

    public String getContactgroupName() {
        return this.contactgroupName;
    }

    public void setContactgroupName(String contactgroupName) {
        this.contactgroupName = contactgroupName;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 0;
        result = prime * result
                + ((contactgroupId == null) ? 0 : contactgroupId.hashCode());
        result = prime
                * result
                + ((contactgroupName == null) ? 0 : contactgroupName.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (!(obj instanceof AbstractMonitorContactgroups))
            return false;
        AbstractMonitorContactgroups other = (AbstractMonitorContactgroups) obj;
        if (contactgroupId == null) {
            if (other.contactgroupId != null)
                return false;
        } else if (!contactgroupId.equals(other.contactgroupId))
            return false;
        if (contactgroupName == null) {
            if (other.contactgroupName != null)
                return false;
        } else if (!contactgroupName.equals(other.contactgroupName))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "AbstractMonitorContactgroups [contactgroupId=" + contactgroupId
                + ", contactgroupName=" + contactgroupName + "]";
	}

}