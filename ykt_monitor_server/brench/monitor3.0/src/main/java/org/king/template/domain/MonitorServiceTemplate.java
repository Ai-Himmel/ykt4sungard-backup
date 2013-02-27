package org.king.template.domain;

import org.king.support.domain.MonitorCommands;
import org.king.support.domain.MonitorContactgroups;

/**
 * MonitorServiceTemplate entity. @author MyEclipse Persistence Tools
 */
public class MonitorServiceTemplate extends AbstractMonitorServiceTemplate
        implements java.io.Serializable {

    // Constructors

    /**
     * default constructor
     */
    public MonitorServiceTemplate() {
    }

    /**
     * full constructor
     */
    public MonitorServiceTemplate(Integer templateId, String templateName, MonitorCommands checkCommand, String checkCommandArgs, MonitorTimePeriods notificationTimeperiod, MonitorTimePeriods checkTimeperiod, Double checkInterval, Double retryInterval, Integer maxCheckAttempts, Double notificationInterval, Integer notifyOnWarning, Integer notifyOnUnknown, Integer notifyOnCritical, Integer notifyOnRecovery, Integer notifyOnFlapping, Integer notifyOnDowntime, Integer flapDetectionEnabled, Integer flapDetectionOnOk, Integer flapDetectionOnWarning, Integer flapDetectionOnUnknown, Integer flapDetectionOnCritical, Double lowFlapThreshold, Double highFlapThreshold, Integer freshnessChecksEnabled, Integer freshnessThreshold, Integer passiveChecksEnabled, Integer eventHandlerEnabled, Integer activeChecksEnabled, Integer retainStatusInformation, Integer retainNonstatusInformation, Integer notificationsEnabled, String notificationOptions, MonitorContactgroups contactGroups) {
        super(templateId, templateName, checkCommand, checkCommandArgs, notificationTimeperiod, checkTimeperiod, checkInterval, retryInterval, maxCheckAttempts, notificationInterval, notifyOnWarning, notifyOnUnknown, notifyOnCritical, notifyOnRecovery, notifyOnFlapping, notifyOnDowntime, flapDetectionEnabled, flapDetectionOnOk, flapDetectionOnWarning, flapDetectionOnUnknown, flapDetectionOnCritical, lowFlapThreshold, highFlapThreshold, freshnessChecksEnabled, freshnessThreshold, passiveChecksEnabled, eventHandlerEnabled, activeChecksEnabled, retainStatusInformation, retainNonstatusInformation, notificationsEnabled, notificationOptions, contactGroups);
    }
}
