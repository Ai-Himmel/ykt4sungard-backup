package org.king.template.domain;

import org.king.host.domain.MonitorHostgroups;
import org.king.support.domain.MonitorCommands;
import org.king.support.domain.MonitorContactgroups;

/**
 * MonitorHostTemplate entity. @author MyEclipse Persistence Tools
 */
public class MonitorHostTemplate extends AbstractMonitorHostTemplate implements
        java.io.Serializable {

    // Constructors

    /**
     * default constructor
     */
    public MonitorHostTemplate() {
    }

    /**
     * full constructor
     */
    public MonitorHostTemplate(Integer templateId, String templateName, MonitorCommands checkCommand, String checkCommandArgs, MonitorCommands eventhandlerCommand, String eventhandlerCommandArgs, MonitorTimePeriods notificationTimeperiod, MonitorTimePeriods checkTimeperiod, Double checkInterval, Double retryInterval, Integer maxCheckAttempts, Double notificationInterval, Integer notifyOnDown, Integer notifyOnUnreachable, Integer notifyOnRecovery, Integer notifyOnFlapping, Integer notifyOnDowntime, Integer flapDetectionEnabled, Integer flapDetectionOnUp, Integer flapDetectionOnDown, Integer flapDetectionOnUnreachable, Double lowFlapThreshold, Double highFlapThreshold, Integer freshnessChecksEnabled, Integer freshnessThreshold, Integer passiveChecksEnabled, Integer eventHandlerEnabled, Integer activeChecksEnabled, Integer retainStatusInformation, Integer retainNonstatusInformation, Integer notificationsEnabled, String notificationOptions, MonitorContactgroups contactGroups, MonitorHostgroups hostgroups) {
        super(templateId, templateName, checkCommand, checkCommandArgs, eventhandlerCommand, eventhandlerCommandArgs, notificationTimeperiod, checkTimeperiod, checkInterval, retryInterval, maxCheckAttempts, notificationInterval, notifyOnDown, notifyOnUnreachable, notifyOnRecovery, notifyOnFlapping, notifyOnDowntime, flapDetectionEnabled, flapDetectionOnUp, flapDetectionOnDown, flapDetectionOnUnreachable, lowFlapThreshold, highFlapThreshold, freshnessChecksEnabled, freshnessThreshold, passiveChecksEnabled, eventHandlerEnabled, activeChecksEnabled, retainStatusInformation, retainNonstatusInformation, notificationsEnabled, notificationOptions, contactGroups, hostgroups);
    }
}
