package org.king.check.config;

public class WorkInfoConfig {

	private static String regularWork="1";
	private static String absence="2";
	private static String lateOnDuty="3";
	private static String earlyOffDuty="4";
	private static String extraWork="5";
	
	public static String getAbsence() {
		return absence;
	}
	public static void setAbsence(String absence) {
		WorkInfoConfig.absence = absence;
	}
	public static String getEarlyOffDuty() {
		return earlyOffDuty;
	}
	public static void setEarlyOffDuty(String earlyOffDuty) {
		WorkInfoConfig.earlyOffDuty = earlyOffDuty;
	}
	public static String getExtraWork() {
		return extraWork;
	}
	public static void setExtraWork(String extraWork) {
		WorkInfoConfig.extraWork = extraWork;
	}
	public static String getLateOnDuty() {
		return lateOnDuty;
	}
	public static void setLateOnDuty(String lateOnDuty) {
		WorkInfoConfig.lateOnDuty = lateOnDuty;
	}
	public static String getRegularWork() {
		return regularWork;
	}
	public static void setRegularWork(String regularWork) {
		WorkInfoConfig.regularWork = regularWork;
	}
	
	
}
