package org.king.check.domain;

/**
 * AbstractTCheckattReport entity provides the base persistence definition of
 * the TCheckattReport entity.
 * 
 * @author MyEclipse Persistence Tools
 */

public abstract class AbstractTCheckattReport extends
		org.king.framework.domain.BaseObject implements java.io.Serializable {

	// Fields

	private TCheckattReportId id;
	private String ifoffice;
	private int worktimeValue;
	private int factValue;
	private int handTimes;
	private int overtimeValue;
	private int tworestValue;
	private int holidayValue;
	private int delayValue;
	private int leaveEarly;
	private int leaveValue;
	private String leaveType;
	private int leaveTime;
	private int ext1;
	private int ext2;
	private int ext3;
	private int ext4;
	private int ext5;
	private int checkNum;
	private int delayNum;
	private int earlyNum;
	private int leaveNum;
	private int extcheckNum;
	private int worktimeNum;

	// Constructors

	/** default constructor */
	public AbstractTCheckattReport() {
	}

	/** minimal constructor */
	public AbstractTCheckattReport(TCheckattReportId id) {
		this.id = id;
	}

	/** full constructor */
	public AbstractTCheckattReport(TCheckattReportId id, String ifoffice,
			int worktimeValue, int factValue, int handTimes,
			int overtimeValue, int tworestValue, int holidayValue,
			int delayValue, int leaveEarly, int leaveValue,
			String leaveType, int leaveTime, int ext1, int ext2, int ext3,
			int ext4, int ext5, int checkNum, int delayNum, int earlyNum,
			int leaveNum, int extcheckNum, int worktimeNum) {
		this.id = id;
		this.ifoffice = ifoffice;
		this.worktimeValue = worktimeValue;
		this.factValue = factValue;
		this.handTimes = handTimes;
		this.overtimeValue = overtimeValue;
		this.tworestValue = tworestValue;
		this.holidayValue = holidayValue;
		this.delayValue = delayValue;
		this.leaveEarly = leaveEarly;
		this.leaveValue = leaveValue;
		this.leaveType = leaveType;
		this.leaveTime = leaveTime;
		this.ext1 = ext1;
		this.ext2 = ext2;
		this.ext3 = ext3;
		this.ext4 = ext4;
		this.ext5 = ext5;
		this.checkNum = checkNum;
		this.delayNum = delayNum;
		this.earlyNum = earlyNum;
		this.leaveNum = leaveNum;
		this.extcheckNum = extcheckNum;
		this.worktimeNum = worktimeNum;
	}

	// Property accessors

	public TCheckattReportId getId() {
		return this.id;
	}

	public void setId(TCheckattReportId id) {
		this.id = id;
	}

	public String getIfoffice() {
		return this.ifoffice;
	}

	public void setIfoffice(String ifoffice) {
		this.ifoffice = ifoffice;
	}

	public int getWorktimeValue() {
		return this.worktimeValue;
	}

	public void setWorktimeValue(int worktimeValue) {
		this.worktimeValue = worktimeValue;
	}

	public int getFactValue() {
		return this.factValue;
	}

	public void setFactValue(int factValue) {
		this.factValue = factValue;
	}

	public int getHandTimes() {
		return this.handTimes;
	}

	public void setHandTimes(int handTimes) {
		this.handTimes = handTimes;
	}

	public int getOvertimeValue() {
		return this.overtimeValue;
	}

	public void setOvertimeValue(int overtimeValue) {
		this.overtimeValue = overtimeValue;
	}

	public int getTworestValue() {
		return this.tworestValue;
	}

	public void setTworestValue(int tworestValue) {
		this.tworestValue = tworestValue;
	}

	public int getHolidayValue() {
		return this.holidayValue;
	}

	public void setHolidayValue(int holidayValue) {
		this.holidayValue = holidayValue;
	}

	public int getDelayValue() {
		return this.delayValue;
	}

	public void setDelayValue(int delayValue) {
		this.delayValue = delayValue;
	}

	public int getLeaveEarly() {
		return this.leaveEarly;
	}

	public void setLeaveEarly(int leaveEarly) {
		this.leaveEarly = leaveEarly;
	}

	public int getLeaveValue() {
		return this.leaveValue;
	}

	public void setLeaveValue(int leaveValue) {
		this.leaveValue = leaveValue;
	}

	public String getLeaveType() {
		return this.leaveType;
	}

	public void setLeaveType(String leaveType) {
		this.leaveType = leaveType;
	}

	public int getLeaveTime() {
		return this.leaveTime;
	}

	public void setLeaveTime(int leaveTime) {
		this.leaveTime = leaveTime;
	}

	public int getExt1() {
		return this.ext1;
	}

	public void setExt1(int ext1) {
		this.ext1 = ext1;
	}

	public int getExt2() {
		return this.ext2;
	}

	public void setExt2(int ext2) {
		this.ext2 = ext2;
	}

	public int getExt3() {
		return this.ext3;
	}

	public void setExt3(int ext3) {
		this.ext3 = ext3;
	}

	public int getExt4() {
		return this.ext4;
	}

	public void setExt4(int ext4) {
		this.ext4 = ext4;
	}

	public int getExt5() {
		return this.ext5;
	}

	public void setExt5(int ext5) {
		this.ext5 = ext5;
	}

	public int getCheckNum() {
		return this.checkNum;
	}

	public void setCheckNum(int checkNum) {
		this.checkNum = checkNum;
	}

	public int getDelayNum() {
		return this.delayNum;
	}

	public void setDelayNum(int delayNum) {
		this.delayNum = delayNum;
	}

	public int getEarlyNum() {
		return this.earlyNum;
	}

	public void setEarlyNum(int earlyNum) {
		this.earlyNum = earlyNum;
	}

	public int getLeaveNum() {
		return this.leaveNum;
	}

	public void setLeaveNum(int leaveNum) {
		this.leaveNum = leaveNum;
	}

	public int getExtcheckNum() {
		return this.extcheckNum;
	}

	public void setExtcheckNum(int extcheckNum) {
		this.extcheckNum = extcheckNum;
	}

	public int getWorktimeNum() {
		return this.worktimeNum;
	}

	public void setWorktimeNum(int worktimeNum) {
		this.worktimeNum = worktimeNum;
	}

}