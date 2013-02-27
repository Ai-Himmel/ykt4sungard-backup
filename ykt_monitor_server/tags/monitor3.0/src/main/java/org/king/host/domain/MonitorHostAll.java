package org.king.host.domain;

import org.king.support.domain.MonitorCommands;
import org.king.support.domain.MonitorContactgroups;
import org.king.template.domain.MonitorTimePeriods;


/**
 * MonitorHost entity. @author MyEclipse Persistence Tools
 */
public class MonitorHostAll extends AbstractMonitorHostAll implements
        java.io.Serializable {

    // Constructors

    /**
     * default constructor
     */
    public MonitorHostAll() {
    }

    /**
     * minimal constructor
     */
    public MonitorHostAll(Integer hostId) {
        super(hostId);
    }

    /**
     * full constructor
     */
    public MonitorHostAll(Integer hostId, String alias, String displayName, String hostAddress, MonitorCommands checkCommand, String checkCommandArgs, MonitorCommands eventhandlerCommand, String eventhandlerCommandArgs, MonitorTimePeriods notificationTimeperiod, MonitorTimePeriods checkTimeperiod, Double checkInterval, Double retryInterval, Integer maxCheckAttempts, Double notificationInterval, Integer notifyOnDown, Integer notifyOnUnreachable, Integer notifyOnRecovery, Integer notifyOnFlapping, Integer notifyOnDowntime, Integer flapDetectionEnabled, Integer flapDetectionOnUp, Integer flapDetectionOnDown, Integer flapDetectionOnUnreachable, Double lowFlapThreshold, Double highFlapThreshold, Integer freshnessChecksEnabled, Integer freshnessThreshold, Integer passiveChecksEnabled, Integer eventHandlerEnabled, Integer activeChecksEnabled, Integer retainStatusInformation, Integer retainNonstatusInformation, Integer notificationsEnabled, String notes, String notesUrl, String actionurl, String notificationOptions, MonitorContactgroups contactGroups, MonitorHostgroups hostgroups,Integer checkFlag) {
        super(hostId, alias, displayName, hostAddress, checkCommand, checkCommandArgs, eventhandlerCommand, eventhandlerCommandArgs, notificationTimeperiod, checkTimeperiod, checkInterval, retryInterval, maxCheckAttempts, notificationInterval, notifyOnDown, notifyOnUnreachable, notifyOnRecovery, notifyOnFlapping, notifyOnDowntime, flapDetectionEnabled, flapDetectionOnUp, flapDetectionOnDown, flapDetectionOnUnreachable, lowFlapThreshold, highFlapThreshold, freshnessChecksEnabled, freshnessThreshold, passiveChecksEnabled, eventHandlerEnabled, activeChecksEnabled, retainStatusInformation, retainNonstatusInformation, notificationsEnabled, notes, notesUrl, actionurl, notificationOptions, contactGroups, hostgroups,checkFlag);
    }
}
