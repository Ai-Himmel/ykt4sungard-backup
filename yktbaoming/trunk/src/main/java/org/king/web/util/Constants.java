package org.king.web.util;

public class Constants {
	public static final String CURENTDEPT="currentDept";	 //当前部门  (DeptInfo)
	public static final String ACCOUNTID="account";		 //当前登录Id
	public static final String MANAGERDEPTS="managerDepts";//当前所管理的部门 (List)
	public static final String CURENTROLES="rolesByAccountIdAndDeptId";//当前部门和登录号所得的角色
	public static final String LOGIN_NAME="userName";//当前登录名
	public static final String PERSON_NAME="personName";//当前用户名
	
	public static final String DICTIONUSE="1"; // 使用
	public static final String DICTIONNOTUSE="0"; //废弃
		
    //开关标识名称
	public final static String noName = "否";
	public final static String yesName = "是";
	
    //开关标识代码
	public final static String noCode = "0";
	public final static String yesCode = "1";
	
    //物料名称、厂商名称等的状态值
	public final static String notCheckName = "未审";
	public final static String isUsingName = "使用";
	public final static String notUsingName = "废弃";
    //物料名称、厂商名称等的状态代码
	public final static String notCheckCode = "n";
	public final static String isUsingCode = "1";
	public final static String notUsingCode = "0";
		
	//物料名称、厂商名称等的状态数组
	public final static String[][] mczt = new String[][]{
		{notCheckCode,notCheckName},{isUsingCode,isUsingName},{notUsingCode,notUsingName}
	};
	
    //开关标识数组
	public final static String[][] onoff_flag = new String[][]{
		{noCode,noName},{yesCode,yesName}
	};
}
