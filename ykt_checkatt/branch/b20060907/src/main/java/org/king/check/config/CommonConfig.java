package org.king.check.config;

public class CommonConfig {

	/*对考勤信息的查询条件*/
	public static final String startDate="startDate" ;
	
	public static final String endDate="endDate";
	
	public static final String deptId="deptId";
	
	public static final String page="page";
	
	public static final String titleStr="titleStr";
	
	public static final String dutyStrs="dutyStrs";
	
	public static final String trueName="trueName";
	
	/*
	 * 以下与字典表对应一致
	 */
	
	/*
	 * 考勤细节信息标志位描述字典
	 */
	public static final String late="1";//迟到
	
	public static final String earlyQuit="2";//早退 
	
	public static final String earlycheckin="3";//超过允许提前打卡时间 
	
	public static final String latecheckout="4";//超过允许滞后打卡时间
	
	public static final String onDutyOk="5";//上班正常 
	
	public static final String offDutyOk="6";//下班正常 
	
	/*
	 * 考勤信息标志位描述字典
	 */
	
	public static final String workInfoException="2";//考勤信息异常
	
	public static final String workInfoOk="5";//考勤信息正常
	
	public static final String absent="4";//旷工
	
	/*
	 * 请假标志位
	 */
	public static final String isGlobe="1";
	/*
	 * 需要检索的表名
	 */
	public static final String table_LEAVEINFO="YKT_CK.LEAVEINFO";
	public static final String table_EXTRAWORKINFO="YKT_CK.EXTRAWORKINFO";
	public static final String table_IRREGULARREST="YKT_CK.IRREGULARREST";
	/*
	 * 部门考勤制度标识描述
	 */
	public static final String restInWKD="1";//周末休息标识
	public static final String workInWKD="2";//周末上班标识
}
