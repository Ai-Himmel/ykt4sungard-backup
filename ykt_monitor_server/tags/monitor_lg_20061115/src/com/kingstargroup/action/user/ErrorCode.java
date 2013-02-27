package com.kingstargroup.action.user;
/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name:ErrorCode.java
 * Description: xml返回错误码表
 * Modify History（或Change Log）: 
 * 操作类型（创建、修改等） 操作日期     操作者    操作内容简述
 * 创建                2005-09-28   何林青    发送给前台的错误码对照表
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */

public class ErrorCode {
	// ~ Static fields/initializers
	// =============================================

	/**
	 * The application scoped attribute for persistence engine and class that
	 * implements it
	 */
	/**
	 * server url
	 */
	public static final String SERVER_URL = "http://10.49.188.52:8080/MonitorSys/";
	/**
	 * every success action return this code
	 */
	public static final String SUCCESS = "0000";

	/**
	 * when user login but user not exist return this code
	 */
	public static final String NO_USER = "0001";

	/**
	 * when user login but user password error retrun this code
	 */
	public static final String PWD_ERROR = "0002";
	/**
	 * when user login but this user is stoped by manager retrun this code
	 */
	public static final String USER_STOPED= "0003";
	/**
	 * default password
	 */
	public static final String DEFAULT_PASSWORD = "123456";
	
	/**
	 * default super_user
	 */
	public static final String SUPER_USER = "admin";
	/**
	 * default manager's code
	 */
	public static final String MANAGER_USER_ROLE = "9999";
	/**
	 * default user status
	 */
	public static final String USER_STATUS_OK = "0";

	/**
	 * when user change password but the old password error retrun this code
	 */
	public static final String OLD_PASSWORD_ERROR = "0010";

	/**
	 * when user change password but the two new password dismatch return this code
	 */
	public static final String NEW_PASSWORD_ERROR = "0011";

	/**
	 * when manager add a user but this user exist in database retrun this code
	 */
	public static final String USER_EXIST = "0004";

	/**
	 * when manager add a contact but this contact exist in database retrun this code
	 */
	public static final String CONTACT_EXIST = "0005";
	
	/**
	 * when manager add a system reference but this reference exist in database retrun this code
	 */
	public static final String REFERENCE_EXIST = "0006";

	/**
	 * when user session is timeout or user haven't login retrun this code
	 */
	public static final String LOGIN_AGAIN_NEED = "4444";

	/**
	 * when some error or exception happen in server  retrun this code
	 */
	public static final String SERVER_IS_BUSY = "7777";
	
	/**
	 * when user can not be delete return this code
	 */
	public static final String CAN_NOT_DELETE = "3333";
	
	/**
	 * when user info can not be reset return this code
	 */
	public static final String CAN_NOT_RESET = "3334";

}
