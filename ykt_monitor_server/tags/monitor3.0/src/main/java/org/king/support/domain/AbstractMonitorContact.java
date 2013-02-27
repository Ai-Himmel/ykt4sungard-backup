package org.king.support.domain;

import org.king.template.domain.MonitorTimePeriods;

/**
 * AbstractMonitorContact entity provides the base persistence definition of the
 * MonitorContact entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorContact extends
        org.king.framework.domain.BaseObject implements java.io.Serializable {

    // Fields

    private Integer contactId;
    private String contactName;
    private String emailAddress;
    private String cellphone;
    private MonitorTimePeriods hostTimeperiod = new MonitorTimePeriods();
    private MonitorTimePeriods serviceTimeperiod = new MonitorTimePeriods();
    private Integer hostNotificationsEnabled;
    private Integer serviceNotificationsEnabled;
    private Integer notifyServiceRecovery;
    private Integer notifyServiceWarning;
    private Integer notifyServiceUnknown;
    private Integer notifyServiceCritical;
    private Integer notifyServiceFlapping;
    private Integer notifyServiceDowntime;
    private Integer notifyHostRecovery;
    private Integer notifyHostDown;
    private Integer notifyHostUnreachable;
    private Integer notifyHostFlapping;
    private Integer notifyHostDowntime;
    private String notifyCommand;
    private MonitorContactgroups contactGroups = new MonitorContactgroups();

    // Constructors

    /**
     * default constructor
     */
    public AbstractMonitorContact() {
    }

    protected AbstractMonitorContact(Integer contactId, String contactName, String emailAddress, String cellphone, MonitorTimePeriods hostTimeperiod, MonitorTimePeriods serviceTimeperiod, Integer hostNotificationsEnabled, Integer serviceNotificationsEnabled, Integer notifyServiceRecovery, Integer notifyServiceWarning, Integer notifyServiceUnknown, Integer notifyServiceCritical, Integer notifyServiceFlapping, Integer notifyServiceDowntime, Integer notifyHostRecovery, Integer notifyHostDown, Integer notifyHostUnreachable, Integer notifyHostFlapping, Integer notifyHostDowntime, String notifyCommand,MonitorContactgroups contactGroups) {
        this.contactId = contactId;
        this.contactName = contactName;
        this.emailAddress = emailAddress;
        this.cellphone = cellphone;
        this.hostTimeperiod = hostTimeperiod;
        this.serviceTimeperiod = serviceTimeperiod;
        this.hostNotificationsEnabled = hostNotificationsEnabled;
        this.serviceNotificationsEnabled = serviceNotificationsEnabled;
        this.notifyServiceRecovery = notifyServiceRecovery;
        this.notifyServiceWarning = notifyServiceWarning;
        this.notifyServiceUnknown = notifyServiceUnknown;
        this.notifyServiceCritical = notifyServiceCritical;
        this.notifyServiceFlapping = notifyServiceFlapping;
        this.notifyServiceDowntime = notifyServiceDowntime;
        this.notifyHostRecovery = notifyHostRecovery;
        this.notifyHostDown = notifyHostDown;
        this.notifyHostUnreachable = notifyHostUnreachable;
        this.notifyHostFlapping = notifyHostFlapping;
        this.notifyHostDowntime = notifyHostDowntime;
        this.notifyCommand = notifyCommand;
        this.contactGroups = contactGroups;
    }

    /**
     * full constructor
     */


    // Property accessors
    public Integer getContactId() {
        return this.contactId;
    }

    public void setContactId(Integer contactId) {
        this.contactId = contactId;
    }

    public String getContactName() {
        return this.contactName;
    }

    public void setContactName(String contactName) {
        this.contactName = contactName;
    }

    public String getEmailAddress() {
        return this.emailAddress;
    }

    public void setEmailAddress(String emailAddress) {
        this.emailAddress = emailAddress;
    }

    public String getCellphone() {
        return this.cellphone;
    }

    public void setCellphone(String cellphone) {
        this.cellphone = cellphone;
    }

    public MonitorTimePeriods getHostTimeperiod() {
        return hostTimeperiod;
    }

    public void setHostTimeperiod(MonitorTimePeriods hostTimeperiod) {
        this.hostTimeperiod = hostTimeperiod;
    }

    public MonitorTimePeriods getServiceTimeperiod() {
        return serviceTimeperiod;
    }

    public void setServiceTimeperiod(MonitorTimePeriods serviceTimeperiod) {
        this.serviceTimeperiod = serviceTimeperiod;
    }

    public Integer getHostNotificationsEnabled() {
        return this.hostNotificationsEnabled;
    }

    public void setHostNotificationsEnabled(Integer hostNotificationsEnabled) {
        this.hostNotificationsEnabled = hostNotificationsEnabled;
    }

    public Integer getServiceNotificationsEnabled() {
        return this.serviceNotificationsEnabled;
    }

    public void setServiceNotificationsEnabled(
            Integer serviceNotificationsEnabled) {
        this.serviceNotificationsEnabled = serviceNotificationsEnabled;
    }

    public Integer getNotifyServiceRecovery() {
        return this.notifyServiceRecovery;
    }

    public void setNotifyServiceRecovery(Integer notifyServiceRecovery) {
        this.notifyServiceRecovery = notifyServiceRecovery;
    }

    public Integer getNotifyServiceWarning() {
        return this.notifyServiceWarning;
    }

    public void setNotifyServiceWarning(Integer notifyServiceWarning) {
        this.notifyServiceWarning = notifyServiceWarning;
    }

    public Integer getNotifyServiceUnknown() {
        return this.notifyServiceUnknown;
    }

    public void setNotifyServiceUnknown(Integer notifyServiceUnknown) {
        this.notifyServiceUnknown = notifyServiceUnknown;
    }

    public Integer getNotifyServiceCritical() {
        return this.notifyServiceCritical;
    }

    public void setNotifyServiceCritical(Integer notifyServiceCritical) {
        this.notifyServiceCritical = notifyServiceCritical;
    }

    public Integer getNotifyServiceFlapping() {
        return this.notifyServiceFlapping;
    }

    public void setNotifyServiceFlapping(Integer notifyServiceFlapping) {
        this.notifyServiceFlapping = notifyServiceFlapping;
    }

    public Integer getNotifyServiceDowntime() {
        return this.notifyServiceDowntime;
    }

    public void setNotifyServiceDowntime(Integer notifyServiceDowntime) {
        this.notifyServiceDowntime = notifyServiceDowntime;
    }

    public Integer getNotifyHostRecovery() {
        return this.notifyHostRecovery;
    }

    public void setNotifyHostRecovery(Integer notifyHostRecovery) {
        this.notifyHostRecovery = notifyHostRecovery;
    }

    public Integer getNotifyHostDown() {
        return this.notifyHostDown;
    }

    public void setNotifyHostDown(Integer notifyHostDown) {
        this.notifyHostDown = notifyHostDown;
    }

    public Integer getNotifyHostUnreachable() {
        return this.notifyHostUnreachable;
    }

    public void setNotifyHostUnreachable(Integer notifyHostUnreachable) {
        this.notifyHostUnreachable = notifyHostUnreachable;
    }

    public Integer getNotifyHostFlapping() {
        return this.notifyHostFlapping;
    }

    public void setNotifyHostFlapping(Integer notifyHostFlapping) {
        this.notifyHostFlapping = notifyHostFlapping;
    }

    public Integer getNotifyHostDowntime() {
        return this.notifyHostDowntime;
    }

    public void setNotifyHostDowntime(Integer notifyHostDowntime) {
        this.notifyHostDowntime = notifyHostDowntime;
    }

    public String getNotifyCommand() {
        return notifyCommand;
    }

    public void setNotifyCommand(String notifyCommand) {
        this.notifyCommand = notifyCommand;
    }

    public MonitorContactgroups getContactGroups() {
        return contactGroups;
    }

    public void setContactGroups(MonitorContactgroups contactGroups) {
        this.contactGroups = contactGroups;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 0;
        result = prime * result
                + ((cellphone == null) ? 0 : cellphone.hashCode());
        result = prime * result
                + ((contactId == null) ? 0 : contactId.hashCode());
        result = prime * result
                + ((contactName == null) ? 0 : contactName.hashCode());
        result = prime * result
                + ((emailAddress == null) ? 0 : emailAddress.hashCode());
        result = prime
                * result
                + ((hostNotificationsEnabled == null) ? 0
                : hostNotificationsEnabled.hashCode());
        result = prime
                * result
                + ((hostTimeperiod == null) ? 0 : hostTimeperiod.hashCode());
        result = prime * result
                + ((notifyHostDown == null) ? 0 : notifyHostDown.hashCode());
        result = prime
                * result
                + ((notifyHostDowntime == null) ? 0 : notifyHostDowntime
                .hashCode());
        result = prime
                * result
                + ((notifyHostFlapping == null) ? 0 : notifyHostFlapping
                .hashCode());
        result = prime
                * result
                + ((notifyHostRecovery == null) ? 0 : notifyHostRecovery
                .hashCode());
        result = prime
                * result
                + ((notifyHostUnreachable == null) ? 0 : notifyHostUnreachable
                .hashCode());
        result = prime
                * result
                + ((notifyServiceCritical == null) ? 0 : notifyServiceCritical
                .hashCode());
        result = prime
                * result
                + ((notifyServiceDowntime == null) ? 0 : notifyServiceDowntime
                .hashCode());
        result = prime
                * result
                + ((notifyServiceFlapping == null) ? 0 : notifyServiceFlapping
                .hashCode());
        result = prime
                * result
                + ((notifyServiceRecovery == null) ? 0 : notifyServiceRecovery
                .hashCode());
        result = prime
                * result
                + ((notifyServiceUnknown == null) ? 0 : notifyServiceUnknown
                .hashCode());
        result = prime
                * result
                + ((notifyServiceWarning == null) ? 0 : notifyServiceWarning
                .hashCode());
        result = prime
                * result
                + ((serviceNotificationsEnabled == null) ? 0
                : serviceNotificationsEnabled.hashCode());
        result = prime
                * result
                + ((serviceTimeperiod == null) ? 0 : serviceTimeperiod
                .hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (!(obj instanceof AbstractMonitorContact))
            return false;
        AbstractMonitorContact other = (AbstractMonitorContact) obj;
        if (cellphone == null) {
            if (other.cellphone != null)
                return false;
        } else if (!cellphone.equals(other.cellphone))
            return false;
        if (contactId == null) {
            if (other.contactId != null)
                return false;
        } else if (!contactId.equals(other.contactId))
            return false;
        if (contactName == null) {
            if (other.contactName != null)
                return false;
        } else if (!contactName.equals(other.contactName))
            return false;
        if (emailAddress == null) {
            if (other.emailAddress != null)
                return false;
        } else if (!emailAddress.equals(other.emailAddress))
            return false;
        if (hostNotificationsEnabled == null) {
            if (other.hostNotificationsEnabled != null)
                return false;
        } else if (!hostNotificationsEnabled
                .equals(other.hostNotificationsEnabled))
            return false;
        if (hostTimeperiod == null) {
            if (other.hostTimeperiod != null)
                return false;
        } else if (!hostTimeperiod.equals(other.hostTimeperiod))
            return false;
        if (notifyHostDown == null) {
            if (other.notifyHostDown != null)
                return false;
        } else if (!notifyHostDown.equals(other.notifyHostDown))
            return false;
        if (notifyHostDowntime == null) {
            if (other.notifyHostDowntime != null)
                return false;
        } else if (!notifyHostDowntime.equals(other.notifyHostDowntime))
            return false;
        if (notifyHostFlapping == null) {
            if (other.notifyHostFlapping != null)
                return false;
        } else if (!notifyHostFlapping.equals(other.notifyHostFlapping))
            return false;
        if (notifyHostRecovery == null) {
            if (other.notifyHostRecovery != null)
                return false;
        } else if (!notifyHostRecovery.equals(other.notifyHostRecovery))
            return false;
        if (notifyHostUnreachable == null) {
            if (other.notifyHostUnreachable != null)
                return false;
        } else if (!notifyHostUnreachable.equals(other.notifyHostUnreachable))
            return false;
        if (notifyServiceCritical == null) {
            if (other.notifyServiceCritical != null)
                return false;
        } else if (!notifyServiceCritical.equals(other.notifyServiceCritical))
            return false;
        if (notifyServiceDowntime == null) {
            if (other.notifyServiceDowntime != null)
                return false;
        } else if (!notifyServiceDowntime.equals(other.notifyServiceDowntime))
            return false;
        if (notifyServiceFlapping == null) {
            if (other.notifyServiceFlapping != null)
                return false;
        } else if (!notifyServiceFlapping.equals(other.notifyServiceFlapping))
            return false;
        if (notifyServiceRecovery == null) {
            if (other.notifyServiceRecovery != null)
                return false;
        } else if (!notifyServiceRecovery.equals(other.notifyServiceRecovery))
            return false;
        if (notifyServiceUnknown == null) {
            if (other.notifyServiceUnknown != null)
                return false;
        } else if (!notifyServiceUnknown.equals(other.notifyServiceUnknown))
            return false;
        if (notifyServiceWarning == null) {
            if (other.notifyServiceWarning != null)
                return false;
        } else if (!notifyServiceWarning.equals(other.notifyServiceWarning))
            return false;
        if (serviceNotificationsEnabled == null) {
            if (other.serviceNotificationsEnabled != null)
                return false;
        } else if (!serviceNotificationsEnabled
                .equals(other.serviceNotificationsEnabled))
            return false;
        if (serviceTimeperiod == null) {
            if (other.serviceTimeperiod != null)
                return false;
        } else if (!serviceTimeperiod.equals(other.serviceTimeperiod))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "AbstractMonitorContact [cellphone=" + cellphone
                + ", contactId=" + contactId + ", contactName=" + contactName
                + ", emailAddress=" + emailAddress
                + ", hostNotificationsEnabled=" + hostNotificationsEnabled
                + ", hostTimeperiodId=" + hostTimeperiod
                + ", notifyHostDown=" + notifyHostDown
                + ", notifyHostDowntime=" + notifyHostDowntime
                + ", notifyHostFlapping=" + notifyHostFlapping
                + ", notifyHostRecovery=" + notifyHostRecovery
                + ", notifyHostUnreachable=" + notifyHostUnreachable
                + ", notifyServiceCritical=" + notifyServiceCritical
                + ", notifyServiceDowntime=" + notifyServiceDowntime
                + ", notifyServiceFlapping=" + notifyServiceFlapping
                + ", notifyServiceRecovery=" + notifyServiceRecovery
                + ", notifyServiceUnknown=" + notifyServiceUnknown
                + ", notifyServiceWarning=" + notifyServiceWarning
                + ", serviceNotificationsEnabled="
                + serviceNotificationsEnabled + ", serviceTimeperiodId="
                + serviceTimeperiod + "]";
	}

}