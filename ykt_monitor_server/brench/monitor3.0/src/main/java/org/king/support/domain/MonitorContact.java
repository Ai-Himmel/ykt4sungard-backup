package org.king.support.domain;

import org.king.template.domain.MonitorTimePeriods;

/**
 * MonitorContact entity. @author MyEclipse Persistence Tools
 */
public class MonitorContact extends AbstractMonitorContact implements
        java.io.Serializable {

    // Constructors

    /**
     * default constructor
     */
    public MonitorContact() {
    }

    /**
     * full constructor
     */
    public MonitorContact(Integer contactId, String contactName, String emailAddress, String cellphone, MonitorTimePeriods hostTimeperiod, MonitorTimePeriods serviceTimeperiod, Integer hostNotificationsEnabled, Integer serviceNotificationsEnabled, Integer notifyServiceRecovery, Integer notifyServiceWarning, Integer notifyServiceUnknown, Integer notifyServiceCritical, Integer notifyServiceFlapping, Integer notifyServiceDowntime, Integer notifyHostRecovery, Integer notifyHostDown, Integer notifyHostUnreachable, Integer notifyHostFlapping, Integer notifyHostDowntime, String notifyCommand,MonitorContactgroups contactGroups) {
        super(contactId, contactName, emailAddress, cellphone, hostTimeperiod, serviceTimeperiod, hostNotificationsEnabled, serviceNotificationsEnabled, notifyServiceRecovery, notifyServiceWarning, notifyServiceUnknown, notifyServiceCritical, notifyServiceFlapping, notifyServiceDowntime, notifyHostRecovery, notifyHostDown, notifyHostUnreachable, notifyHostFlapping, notifyHostDowntime, notifyCommand,contactGroups);
    }
}
