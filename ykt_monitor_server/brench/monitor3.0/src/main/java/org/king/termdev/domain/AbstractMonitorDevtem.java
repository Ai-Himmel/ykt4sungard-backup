package org.king.termdev.domain;

/**
 * .
 * User: Yiming.You
 * Date: 2010-8-2
 */
/**
 * AbstractMonitorDevtem entity provides the base persistence definition of
 * the MonitorDevtem entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorDevtem extends
        org.king.framework.domain.BaseObject implements java.io.Serializable {

    // Fields

    private Integer deviceid;
    private Integer templateid;

    // Constructors

    /**
     * default constructor
     */
    public AbstractMonitorDevtem() {
    }

    /**
     * full constructor
     */
    public AbstractMonitorDevtem(Integer deviceid, Integer templateid) {
        this.deviceid = deviceid;
        this.templateid = templateid;
    }

    // Property accessors

    public Integer getTemplateid() {
        return templateid;
    }

    public void setTemplateid(Integer templateid) {
        this.templateid = templateid;
    }

    public Integer getDeviceid() {
        return deviceid;
    }

    public void setDeviceid(Integer deviceid) {
        this.deviceid = deviceid;
    }

    @Override
    public String toString() {
        return "AbstractMonitorDevtem [deviceid=" + deviceid
                + ", templateid=" + templateid + "]";
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 0;
        result = prime * result
                + ((deviceid == null) ? 0 : deviceid.hashCode());
        result = prime * result
                + ((templateid == null) ? 0 : templateid.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (!(obj instanceof AbstractMonitorDevtem))
            return false;
        AbstractMonitorDevtem other = (AbstractMonitorDevtem) obj;
        if (deviceid == null) {
            if (other.deviceid != null)
                return false;
        } else if (!deviceid.equals(other.deviceid))
            return false;
        if (templateid == null) {
            if (other.templateid != null)
                return false;
        } else if (!templateid.equals(other.templateid))
            return false;
        return true;
	}

}
