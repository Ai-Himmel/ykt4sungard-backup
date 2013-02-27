package org.king.template.domain;

import org.king.support.domain.MonitorContactgroups;

/**
 * MonitorTermdevTemplate entity. @author MyEclipse Persistence Tools
 */
public class MonitorTermdevTemplateAll extends AbstractMonitorTermdevTemplateAll
        implements java.io.Serializable {

    // Constructors

    /**
     * default constructor
     */
    public MonitorTermdevTemplateAll() {
    }

    /**
     * full constructor
     */
    public MonitorTermdevTemplateAll(String templateName,
                                  Integer notificationsEnabled, MonitorTimePeriods notificationPeriod,
                                  MonitorTimePeriods checkPeriod, Double checkInterval, Double retryInterval,
                                  Integer maxCheckAttempts, String checkCommand,
                                  Integer notificationInterval, String notificationOptions,
                                  MonitorContactgroups contactGroups, Integer activeChecksEnable,Integer passiveChecksEnable, Integer notifyOnDown, Integer notifyOnRecovery,Integer checkFlag) {
        super(templateName, notificationsEnabled, notificationPeriod,
                checkPeriod, checkInterval, retryInterval, maxCheckAttempts,
                checkCommand, notificationInterval, notificationOptions,
                contactGroups, activeChecksEnable,passiveChecksEnable, notifyOnDown, notifyOnRecovery,checkFlag);
	}

}
