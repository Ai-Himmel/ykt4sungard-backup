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
	
	public static final String CHECK = "已审核";
	public static final String NOTCHECK = "未审核";
	public static final String AGREE = "同意";
	public static final String NOTAGREE = "不同意";
	
	//hanjiwei add it 20071227
	public static final String leaveManual = "4";//请假和手工签到两者都有
	public static final String leave = "3";//请假
	public static final String manual = "2";//手工考勤
	public static final String normal = "1";//正常签到
	
	public static final String leaveDetail = "searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId=";//请假详细信息链接
	public static final String manualDetail = "searchNoSeatWorkInfo.do?method=goManualDetailInfo&custId=";//手工签到详细信息链接
	public static final String leaveManualDetail = "searchNoSeatWorkInfo.do?method=goLeaveDetailInfo&leaveReportId=";//手工考勤和请假详细信息链接
	public static final String isNotSeat = "2";//不坐班考勤
	
	
}
