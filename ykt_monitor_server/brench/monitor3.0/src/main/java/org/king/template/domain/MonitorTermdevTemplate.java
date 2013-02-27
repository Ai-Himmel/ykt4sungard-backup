package org.king.template.domain;

import org.king.support.domain.MonitorContactgroups;

/**
 * MonitorTermdevTemplate entity. @author MyEclipse Persistence Tools
 */
public class MonitorTermdevTemplate extends AbstractMonitorTermdevTemplate
        implements java.io.Serializable {

    // Constructors

    /**
     * default constructor
     */
    public MonitorTermdevTemplate() {
    }

    /**
     * full constructor
     */
    public MonitorTermdevTemplate(String templateName,
                                  Integer notificationsEnabled, MonitorTimePeriods notificationPeriod,
                                  MonitorTimePeriods checkPeriod, Double checkInterval, Double retryInterval,
                                  Integer maxCheckAttempts, String checkCommand,
                                  Integer notificationInterval, String notificationOptions,
                                  MonitorContactgroups contactGroups, Integer activeChecksEnable,Integer passiveChecksEnable, Integer notifyOnDown, Integer notifyOnRecovery) {
        super(templateName, notificationsEnabled, notificationPeriod,
                checkPeriod, checkInterval, retryInterval, maxCheckAttempts,
                checkCommand, notificationInterval, notificationOptions,
                contactGroups, activeChecksEnable,passiveChecksEnable, notifyOnDown, notifyOnRecovery);
	}

}
