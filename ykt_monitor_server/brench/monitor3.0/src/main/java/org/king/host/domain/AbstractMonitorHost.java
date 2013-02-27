package org.king.host.domain;

import org.king.support.domain.MonitorCommands;
import org.king.support.domain.MonitorContactgroups;
import org.king.template.domain.MonitorTimePeriods;


/**
 * AbstractMonitorHost entity provides the base persistence definition of the
 * MonitorHost entity. @author MyEclipse Persistence Tools
 */

public abstract class AbstractMonitorHost extends
        org.king.framework.domain.BaseObject implements java.io.Serializable {

    // Fields

    private Integer hostId;
    private String alias;
    private String displayName;
    private String hostAddress;
    private MonitorCommands checkCommand = new MonitorCommands();
    private String checkCommandArgs;
    private MonitorCommands eventhandlerCommand = new MonitorCommands();
    private String eventhandlerCommandArgs;
    private MonitorTimePeriods notificationTimeperiod = new MonitorTimePeriods();
    private MonitorTimePeriods checkTimeperiod = new MonitorTimePeriods();
    private Double checkInterval;
    private Double retryInterval;
    private Integer maxCheckAttempts;
    private Double notificationInterval;
    private Integer notifyOnDown;
    private Integer notifyOnUnreachable;
    private Integer notifyOnRecovery;
    private Integer notifyOnFlapping;
    private Integer notifyOnDowntime;
    private Integer flapDetectionEnabled;
    private Integer flapDetectionOnUp;
    private Integer flapDetectionOnDown;
    private Integer flapDetectionOnUnreachable;
    private Double lowFlapThreshold = Double.valueOf(0);
    private Double highFlapThreshold = Double.valueOf(0);
    private Integer freshnessChecksEnabled;
    private Integer freshnessThreshold;
    private Integer passiveChecksEnabled;
    private Integer eventHandlerEnabled;
    private Integer activeChecksEnabled;
    private Integer retainStatusInformation;
    private Integer retainNonstatusInformation;
    private Integer notificationsEnabled;
    private String notes;
    private String notesUrl;
    private String actionurl;
    private String notificationOptions;
    private MonitorContactgroups contactGroups = new MonitorContactgroups();
    private MonitorHostgroups hostgroups = new MonitorHostgroups();
    private String hostType;

    // Constructors

    /**
     * default constructor
     */
    public AbstractMonitorHost() {
    }

    /**
     * minimal constructor
     */
    public AbstractMonitorHost(Integer hostId) {
        this.hostId = hostId;
    }

    protected AbstractMonitorHost(Integer hostId, String alias, String displayName, String hostAddress, MonitorCommands checkCommand, String checkCommandArgs, MonitorCommands eventhandlerCommand, String eventhandlerCommandArgs, MonitorTimePeriods notificationTimeperiod, MonitorTimePeriods checkTimeperiod, Double checkInterval, Double retryInterval, Integer maxCheckAttempts, Double notificationInterval, Integer notifyOnDown, Integer notifyOnUnreachable, Integer notifyOnRecovery, Integer notifyOnFlapping, Integer notifyOnDowntime, Integer flapDetectionEnabled, Integer flapDetectionOnUp, Integer flapDetectionOnDown, Integer flapDetectionOnUnreachable, Double lowFlapThreshold, Double highFlapThreshold, Integer freshnessChecksEnabled, Integer freshnessThreshold, Integer passiveChecksEnabled, Integer eventHandlerEnabled, Integer activeChecksEnabled, Integer retainStatusInformation, Integer retainNonstatusInformation, Integer notificationsEnabled, String notes, String notesUrl, String actionurl, String notificationOptions, MonitorContactgroups contactGroups, MonitorHostgroups hostgroups) {
        this.hostId = hostId;
        this.alias = alias;
        this.displayName = displayName;
        this.hostAddress = hostAddress;
        this.checkCommand = checkCommand;
        this.checkCommandArgs = checkCommandArgs;
        this.eventhandlerCommand = eventhandlerCommand;
        this.eventhandlerCommandArgs = eventhandlerCommandArgs;
        this.notificationTimeperiod = notificationTimeperiod;
        this.checkTimeperiod = checkTimeperiod;
        this.checkInterval = checkInterval;
        this.retryInterval = retryInterval;
        this.maxCheckAttempts = maxCheckAttempts;
        this.notificationInterval = notificationInterval;
        this.notifyOnDown = notifyOnDown;
        this.notifyOnUnreachable = notifyOnUnreachable;
        this.notifyOnRecovery = notifyOnRecovery;
        this.notifyOnFlapping = notifyOnFlapping;
        this.notifyOnDowntime = notifyOnDowntime;
        this.flapDetectionEnabled = flapDetectionEnabled;
        this.flapDetectionOnUp = flapDetectionOnUp;
        this.flapDetectionOnDown = flapDetectionOnDown;
        this.flapDetectionOnUnreachable = flapDetectionOnUnreachable;
        this.lowFlapThreshold = lowFlapThreshold;
        this.highFlapThreshold = highFlapThreshold;
        this.freshnessChecksEnabled = freshnessChecksEnabled;
        this.freshnessThreshold = freshnessThreshold;
        this.passiveChecksEnabled = passiveChecksEnabled;
        this.eventHandlerEnabled = eventHandlerEnabled;
        this.activeChecksEnabled = activeChecksEnabled;
        this.retainStatusInformation = retainStatusInformation;
        this.retainNonstatusInformation = retainNonstatusInformation;
        this.notificationsEnabled = notificationsEnabled;
        this.notes = notes;
        this.notesUrl = notesUrl;
        this.actionurl = actionurl;
        this.notificationOptions = notificationOptions;
        this.contactGroups = contactGroups;
        this.hostgroups = hostgroups;
    }

    // Property accessors

    public Integer getHostId() {
        return this.hostId;
    }


	public void setHostId(Integer hostId) {
        this.hostId = hostId;
    }

    public String getAlias() {
        return this.alias;
    }

    public void setAlias(String alias) {
        this.alias = alias;
    }

    public String getDisplayName() {
        return this.displayName;
    }

    public void setDisplayName(String displayName) {
        this.displayName = displayName;
    }

    public String getHostAddress() {
        return hostAddress;
    }

    public void setHostAddress(String hostAddress) {
        this.hostAddress = hostAddress;
    }

    public MonitorCommands getCheckCommand() {
        return checkCommand;
    }

    public void setCheckCommand(MonitorCommands checkCommand) {
        this.checkCommand = checkCommand;
    }

    public String getCheckCommandArgs() {
        return this.checkCommandArgs;
    }

    public void setCheckCommandArgs(String checkCommandArgs) {
        this.checkCommandArgs = checkCommandArgs;
    }

    public MonitorCommands getEventhandlerCommand() {
        return eventhandlerCommand;
    }

    public void setEventhandlerCommand(MonitorCommands eventhandlerCommand) {
        this.eventhandlerCommand = eventhandlerCommand;
    }

    public String getEventhandlerCommandArgs() {
        return this.eventhandlerCommandArgs;
    }

    public void setEventhandlerCommandArgs(String eventhandlerCommandArgs) {
        this.eventhandlerCommandArgs = eventhandlerCommandArgs;
    }

    public MonitorTimePeriods getNotificationTimeperiod() {
        return this.notificationTimeperiod;
    }

    public void setNotificationTimeperiod(MonitorTimePeriods notificationTimeperiod) {
        this.notificationTimeperiod = notificationTimeperiod;
    }

    public MonitorTimePeriods getCheckTimeperiod() {
        return this.checkTimeperiod;
    }

    public void setCheckTimeperiod(MonitorTimePeriods checkTimeperiod) {
        this.checkTimeperiod = checkTimeperiod;
    }

    public Double getCheckInterval() {
        return this.checkInterval;
    }

    public void setCheckInterval(Double checkInterval) {
        this.checkInterval = checkInterval;
    }

    public Double getRetryInterval() {
        return this.retryInterval;
    }

    public void setRetryInterval(Double retryInterval) {
        this.retryInterval = retryInterval;
    }

    public Integer getMaxCheckAttempts() {
        return this.maxCheckAttempts;
    }

    public void setMaxCheckAttempts(Integer maxCheckAttempts) {
        this.maxCheckAttempts = maxCheckAttempts;
    }

    public Double getNotificationInterval() {
        return notificationInterval;
    }

    public void setNotificationInterval(Double notificationInterval) {
        this.notificationInterval = notificationInterval;
    }

    public Integer getNotifyOnDown() {
        return this.notifyOnDown;
    }

    public void setNotifyOnDown(Integer notifyOnDown) {
        this.notifyOnDown = notifyOnDown;
    }

    public Integer getNotifyOnUnreachable() {
        return this.notifyOnUnreachable;
    }

    public void setNotifyOnUnreachable(Integer notifyOnUnreachable) {
        this.notifyOnUnreachable = notifyOnUnreachable;
    }

    public Integer getNotifyOnRecovery() {
        return this.notifyOnRecovery;
    }

    public void setNotifyOnRecovery(Integer notifyOnRecovery) {
        this.notifyOnRecovery = notifyOnRecovery;
    }

    public Integer getNotifyOnFlapping() {
        return this.notifyOnFlapping;
    }

    public void setNotifyOnFlapping(Integer notifyOnFlapping) {
        this.notifyOnFlapping = notifyOnFlapping;
    }

    public Integer getNotifyOnDowntime() {
        return this.notifyOnDowntime;
    }

    public void setNotifyOnDowntime(Integer notifyOnDowntime) {
        this.notifyOnDowntime = notifyOnDowntime;
    }

    public Integer getFlapDetectionEnabled() {
        return this.flapDetectionEnabled;
    }

    public void setFlapDetectionEnabled(Integer flapDetectionEnabled) {
        this.flapDetectionEnabled = flapDetectionEnabled;
    }

    public Integer getFlapDetectionOnUp() {
        return this.flapDetectionOnUp;
    }

    public void setFlapDetectionOnUp(Integer flapDetectionOnUp) {
        this.flapDetectionOnUp = flapDetectionOnUp;
    }

    public Integer getFlapDetectionOnDown() {
        return this.flapDetectionOnDown;
    }

    public void setFlapDetectionOnDown(Integer flapDetectionOnDown) {
        this.flapDetectionOnDown = flapDetectionOnDown;
    }

    public Integer getFlapDetectionOnUnreachable() {
        return this.flapDetectionOnUnreachable;
    }

    public void setFlapDetectionOnUnreachable(
            Integer flapDetectionOnUnreachable) {
        this.flapDetectionOnUnreachable = flapDetectionOnUnreachable;
    }

    public Double getLowFlapThreshold() {
        return this.lowFlapThreshold;
    }

    public void setLowFlapThreshold(Double lowFlapThreshold) {
        this.lowFlapThreshold = lowFlapThreshold;
    }

    public Double getHighFlapThreshold() {
        return this.highFlapThreshold;
    }

    public void setHighFlapThreshold(Double highFlapThreshold) {
        this.highFlapThreshold = highFlapThreshold;
    }

    public Integer getFreshnessChecksEnabled() {
        return this.freshnessChecksEnabled;
    }

    public void setFreshnessChecksEnabled(Integer freshnessChecksEnabled) {
        this.freshnessChecksEnabled = freshnessChecksEnabled;
    }

    public Integer getFreshnessThreshold() {
        return this.freshnessThreshold;
    }

    public void setFreshnessThreshold(Integer freshnessThreshold) {
        this.freshnessThreshold = freshnessThreshold;
    }

    public Integer getPassiveChecksEnabled() {
        return this.passiveChecksEnabled;
    }

    public void setPassiveChecksEnabled(Integer passiveChecksEnabled) {
        this.passiveChecksEnabled = passiveChecksEnabled;
    }

    public Integer getEventHandlerEnabled() {
        return this.eventHandlerEnabled;
    }

    public void setEventHandlerEnabled(Integer eventHandlerEnabled) {
        this.eventHandlerEnabled = eventHandlerEnabled;
    }

    public Integer getActiveChecksEnabled() {
        return this.activeChecksEnabled;
    }

    public void setActiveChecksEnabled(Integer activeChecksEnabled) {
        this.activeChecksEnabled = activeChecksEnabled;
    }

    public Integer getRetainStatusInformation() {
        return this.retainStatusInformation;
    }

    public void setRetainStatusInformation(Integer retainStatusInformation) {
        this.retainStatusInformation = retainStatusInformation;
    }

    public Integer getRetainNonstatusInformation() {
        return this.retainNonstatusInformation;
    }

    public void setRetainNonstatusInformation(
            Integer retainNonstatusInformation) {
        this.retainNonstatusInformation = retainNonstatusInformation;
    }

    public Integer getNotificationsEnabled() {
        return this.notificationsEnabled;
    }

    public void setNotificationsEnabled(Integer notificationsEnabled) {
        this.notificationsEnabled = notificationsEnabled;
    }

    public String getNotes() {
        return this.notes;
    }

    public void setNotes(String notes) {
        this.notes = notes;
    }

    public String getNotesUrl() {
        return this.notesUrl;
    }

    public void setNotesUrl(String notesUrl) {
        this.notesUrl = notesUrl;
    }

    public String getActionurl() {
        return this.actionurl;
    }

    public void setActionurl(String actionurl) {
        this.actionurl = actionurl;
    }

    public String getNotificationOptions() {
        return notificationOptions;
    }

    public void setNotificationOptions(String notificationOptions) {
        this.notificationOptions = notificationOptions;
    }

    public MonitorContactgroups getContactGroups() {
        return contactGroups;
    }

    public void setContactGroups(MonitorContactgroups contactGroups) {
        this.contactGroups = contactGroups;
    }

    public MonitorHostgroups getHostgroups() {
        return hostgroups;
    }

    public void setHostgroups(MonitorHostgroups hostgroups) {
        this.hostgroups = hostgroups;
    }

    public String getHostType() {
        return hostType;
    }

    public void setHostType(String hostType) {
        this.hostType = hostType;
    }

    @Override
    public int hashCode() {
        final int prime = 31;
        int result = 0;
        result = prime * result
                + ((actionurl == null) ? 0 : actionurl.hashCode());
        result = prime
                * result
                + ((activeChecksEnabled == null) ? 0 : activeChecksEnabled
                .hashCode());
        result = prime * result + ((alias == null) ? 0 : alias.hashCode());
        result = prime * result
                + ((checkCommand == null) ? 0 : checkCommand.hashCode());
        result = prime
                * result
                + ((checkCommandArgs == null) ? 0 : checkCommandArgs.hashCode());
        result = prime * result
                + ((checkInterval == null) ? 0 : checkInterval.hashCode());
        result = prime
                * result
                + ((checkTimeperiod == null) ? 0 : checkTimeperiod
                .hashCode());
        result = prime * result
                + ((displayName == null) ? 0 : displayName.hashCode());
        result = prime
                * result
                + ((eventHandlerEnabled == null) ? 0 : eventHandlerEnabled
                .hashCode());
        result = prime
                * result
                + ((eventhandlerCommandArgs == null) ? 0
                : eventhandlerCommandArgs.hashCode());
        result = prime
                * result
                + ((eventhandlerCommand == null) ? 0 : eventhandlerCommand
                .hashCode());
        result = prime
                * result
                + ((flapDetectionEnabled == null) ? 0 : flapDetectionEnabled
                .hashCode());
        result = prime
                * result
                + ((flapDetectionOnDown == null) ? 0 : flapDetectionOnDown
                .hashCode());
        result = prime
                * result
                + ((flapDetectionOnUnreachable == null) ? 0
                : flapDetectionOnUnreachable.hashCode());
        result = prime
                * result
                + ((flapDetectionOnUp == null) ? 0 : flapDetectionOnUp
                .hashCode());
        result = prime
                * result
                + ((freshnessChecksEnabled == null) ? 0
                : freshnessChecksEnabled.hashCode());
        result = prime
                * result
                + ((freshnessThreshold == null) ? 0 : freshnessThreshold
                .hashCode());
        result = prime
                * result
                + ((highFlapThreshold == null) ? 0 : highFlapThreshold
                .hashCode());
        result = prime * result
                + ((hostAddress == null) ? 0 : hostAddress.hashCode());
        result = prime * result + ((hostId == null) ? 0 : hostId.hashCode());
        result = prime
                * result
                + ((lowFlapThreshold == null) ? 0 : lowFlapThreshold.hashCode());
        result = prime
                * result
                + ((maxCheckAttempts == null) ? 0 : maxCheckAttempts.hashCode());
        result = prime * result + ((notes == null) ? 0 : notes.hashCode());
        result = prime * result
                + ((notesUrl == null) ? 0 : notesUrl.hashCode());
        result = prime
                * result
                + ((notificationTimeperiod == null) ? 0
                : notificationTimeperiod.hashCode());
        result = prime
                * result
                + ((notificationsEnabled == null) ? 0 : notificationsEnabled
                .hashCode());
        result = prime * result
                + ((notifyOnDown == null) ? 0 : notifyOnDown.hashCode());
        result = prime
                * result
                + ((notifyOnDowntime == null) ? 0 : notifyOnDowntime.hashCode());
        result = prime
                * result
                + ((notifyOnFlapping == null) ? 0 : notifyOnFlapping.hashCode());
        result = prime
                * result
                + ((notifyOnRecovery == null) ? 0 : notifyOnRecovery.hashCode());
        result = prime
                * result
                + ((notifyOnUnreachable == null) ? 0 : notifyOnUnreachable
                .hashCode());
        result = prime
                * result
                + ((passiveChecksEnabled == null) ? 0 : passiveChecksEnabled
                .hashCode());
        result = prime
                * result
                + ((retainNonstatusInformation == null) ? 0
                : retainNonstatusInformation.hashCode());
        result = prime
                * result
                + ((retainStatusInformation == null) ? 0
                : retainStatusInformation.hashCode());
        result = prime * result
                + ((retryInterval == null) ? 0 : retryInterval.hashCode());
        return result;
    }

    @Override
    public boolean equals(Object obj) {
        if (this == obj)
            return true;
        if (!(obj instanceof AbstractMonitorHost))
            return false;
        AbstractMonitorHost other = (AbstractMonitorHost) obj;
        if (actionurl == null) {
            if (other.actionurl != null)
                return false;
        } else if (!actionurl.equals(other.actionurl))
            return false;
        if (activeChecksEnabled == null) {
            if (other.activeChecksEnabled != null)
                return false;
        } else if (!activeChecksEnabled.equals(other.activeChecksEnabled))
            return false;
        if (alias == null) {
            if (other.alias != null)
                return false;
        } else if (!alias.equals(other.alias))
            return false;
        if (checkCommand == null) {
            if (other.checkCommand != null)
                return false;
        } else if (!checkCommand.equals(other.checkCommand))
            return false;
        if (checkCommandArgs == null) {
            if (other.checkCommandArgs != null)
                return false;
        } else if (!checkCommandArgs.equals(other.checkCommandArgs))
            return false;
        if (checkInterval == null) {
            if (other.checkInterval != null)
                return false;
        } else if (!checkInterval.equals(other.checkInterval))
            return false;
        if (checkTimeperiod == null) {
            if (other.checkTimeperiod != null)
                return false;
        } else if (!checkTimeperiod.equals(other.checkTimeperiod))
            return false;
        if (displayName == null) {
            if (other.displayName != null)
                return false;
        } else if (!displayName.equals(other.displayName))
            return false;
        if (eventHandlerEnabled == null) {
            if (other.eventHandlerEnabled != null)
                return false;
        } else if (!eventHandlerEnabled.equals(other.eventHandlerEnabled))
            return false;
        if (eventhandlerCommandArgs == null) {
            if (other.eventhandlerCommandArgs != null)
                return false;
        } else if (!eventhandlerCommandArgs
                .equals(other.eventhandlerCommandArgs))
            return false;
        if (eventhandlerCommand == null) {
            if (other.eventhandlerCommand != null)
                return false;
        } else if (!eventhandlerCommand.equals(other.eventhandlerCommand))
            return false;
        if (flapDetectionEnabled == null) {
            if (other.flapDetectionEnabled != null)
                return false;
        } else if (!flapDetectionEnabled.equals(other.flapDetectionEnabled))
            return false;
        if (flapDetectionOnDown == null) {
            if (other.flapDetectionOnDown != null)
                return false;
        } else if (!flapDetectionOnDown.equals(other.flapDetectionOnDown))
            return false;
        if (flapDetectionOnUnreachable == null) {
            if (other.flapDetectionOnUnreachable != null)
                return false;
        } else if (!flapDetectionOnUnreachable
                .equals(other.flapDetectionOnUnreachable))
            return false;
        if (flapDetectionOnUp == null) {
            if (other.flapDetectionOnUp != null)
                return false;
        } else if (!flapDetectionOnUp.equals(other.flapDetectionOnUp))
            return false;
        if (freshnessChecksEnabled == null) {
            if (other.freshnessChecksEnabled != null)
                return false;
        } else if (!freshnessChecksEnabled.equals(other.freshnessChecksEnabled))
            return false;
        if (freshnessThreshold == null) {
            if (other.freshnessThreshold != null)
                return false;
        } else if (!freshnessThreshold.equals(other.freshnessThreshold))
            return false;
        if (highFlapThreshold == null) {
            if (other.highFlapThreshold != null)
                return false;
        } else if (!highFlapThreshold.equals(other.highFlapThreshold))
            return false;
        if (hostAddress == null) {
            if (other.hostAddress != null)
                return false;
        } else if (!hostAddress.equals(other.hostAddress))
            return false;
        if (hostId == null) {
            if (other.hostId != null)
                return false;
        } else if (!hostId.equals(other.hostId))
            return false;
        if (lowFlapThreshold == null) {
            if (other.lowFlapThreshold != null)
                return false;
        } else if (!lowFlapThreshold.equals(other.lowFlapThreshold))
            return false;
        if (maxCheckAttempts == null) {
            if (other.maxCheckAttempts != null)
                return false;
        } else if (!maxCheckAttempts.equals(other.maxCheckAttempts))
            return false;
        if (notes == null) {
            if (other.notes != null)
                return false;
        } else if (!notes.equals(other.notes))
            return false;
        if (notesUrl == null) {
            if (other.notesUrl != null)
                return false;
        } else if (!notesUrl.equals(other.notesUrl))
            return false;
        if (notificationTimeperiod == null) {
            if (other.notificationTimeperiod != null)
                return false;
        } else if (!notificationTimeperiod
                .equals(other.notificationTimeperiod))
            return false;
        if (notificationsEnabled == null) {
            if (other.notificationsEnabled != null)
                return false;
        } else if (!notificationsEnabled.equals(other.notificationsEnabled))
            return false;
        if (notifyOnDown == null) {
            if (other.notifyOnDown != null)
                return false;
        } else if (!notifyOnDown.equals(other.notifyOnDown))
            return false;
        if (notifyOnDowntime == null) {
            if (other.notifyOnDowntime != null)
                return false;
        } else if (!notifyOnDowntime.equals(other.notifyOnDowntime))
            return false;
        if (notifyOnFlapping == null) {
            if (other.notifyOnFlapping != null)
                return false;
        } else if (!notifyOnFlapping.equals(other.notifyOnFlapping))
            return false;
        if (notifyOnRecovery == null) {
            if (other.notifyOnRecovery != null)
                return false;
        } else if (!notifyOnRecovery.equals(other.notifyOnRecovery))
            return false;
        if (notifyOnUnreachable == null) {
            if (other.notifyOnUnreachable != null)
                return false;
        } else if (!notifyOnUnreachable.equals(other.notifyOnUnreachable))
            return false;
        if (passiveChecksEnabled == null) {
            if (other.passiveChecksEnabled != null)
                return false;
        } else if (!passiveChecksEnabled.equals(other.passiveChecksEnabled))
            return false;
        if (retainNonstatusInformation == null) {
            if (other.retainNonstatusInformation != null)
                return false;
        } else if (!retainNonstatusInformation
                .equals(other.retainNonstatusInformation))
            return false;
        if (retainStatusInformation == null) {
            if (other.retainStatusInformation != null)
                return false;
        } else if (!retainStatusInformation
                .equals(other.retainStatusInformation))
            return false;
        if (retryInterval == null) {
            if (other.retryInterval != null)
                return false;
        } else if (!retryInterval.equals(other.retryInterval))
            return false;
        return true;
    }

    @Override
    public String toString() {
        return "AbstractMonitorHost [actionurl=" + actionurl
                + ", activeChecksEnabled=" + activeChecksEnabled + ", alias="
                + alias + ", checkCommand=" + checkCommand
                + ", checkCommandArgs=" + checkCommandArgs + ", checkInterval="
                + checkInterval + ", checkTimeperiod=" + checkTimeperiod
                + ", displayName=" + displayName + ", eventHandlerEnabled="
                + eventHandlerEnabled + ", eventhandlerCommandArgs="
                + eventhandlerCommandArgs + ", eventhandlerCommand="
                + eventhandlerCommand + ", flapDetectionEnabled="
                + flapDetectionEnabled + ", flapDetectionOnDown="
                + flapDetectionOnDown + ", flapDetectionOnUnreachable="
                + flapDetectionOnUnreachable + ", flapDetectionOnUp="
                + flapDetectionOnUp + ", freshnessChecksEnabled="
                + freshnessChecksEnabled + ", freshnessThreshold="
                + freshnessThreshold + ", highFlapThreshold="
                + highFlapThreshold + ", hostAddress=" + hostAddress
                + ", hostId=" + hostId + ", lowFlapThreshold="
                + lowFlapThreshold + ", maxCheckAttempts=" + maxCheckAttempts
                + ", notes=" + notes + ", notesUrl=" + notesUrl
                + ", notificationTimeperiod=" + notificationTimeperiod
                + ", notificationsEnabled=" + notificationsEnabled
                + ", notifyOnDown=" + notifyOnDown + ", notifyOnDowntime="
                + notifyOnDowntime + ", notifyOnFlapping=" + notifyOnFlapping
                + ", notifyOnRecovery=" + notifyOnRecovery
                + ", notifyOnUnreachable=" + notifyOnUnreachable
                + ", passiveChecksEnabled=" + passiveChecksEnabled
                + ", retainNonstatusInformation=" + retainNonstatusInformation
                + ", retainStatusInformation=" + retainStatusInformation
                + ", retryInterval=" + retryInterval + "]";
    }
}