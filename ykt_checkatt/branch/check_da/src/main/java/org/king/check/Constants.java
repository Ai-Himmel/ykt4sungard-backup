/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.Constants.java
 * 创建日期： 2006-6-20 21:26:09
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-20 21:26:09      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.check;

/**
 * <p> Constants.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="Constants.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-20
 * 
 *
 */
public class Constants {

	public static String SELECTED_PERSON = "selectedPerson";
	public static String DBNAME = "ORACLE";//DB2,ORACLE
	public static String LINKADD = "http://www.ecardapp.fudan.edu.cn:8090/check";
	public static String PUBREST = "'1','8','9'";//公事假 
	public static String NOCUSTID="无此老师的学工号:";
	
	public static String EXCEL_IMPSUCCESS="";
	
	public static final String OPRATER_EQUAL = "=";

    public static final String OPRATER_UNEQUAL = "<>";

    public static final String OPRATER_GREATER_AND_EQUAL = ">=";

    public static final String OPRATER_LESS_AND_EQUAL = "<=";

    public static final String OPRATER_GREATER = ">";

    public static final String OPRATER_LESS = "<";

    public static final String OPRATER_CONTAINS = "%|%";

    public static final String OPRATER_NOT_CONTAINS = "%||%";

    public static final String OPRATER_LEFT_CONTAINS = "|%";

    public static final String OPRATER_RIGHT_CONTAINS = "%|";

    public static final String OPRATER_BETWEEN = "between";

    public static final String OPRATER_ISNULL = "is null";

    public static final String OPRATER_ISNOTNULL = "is not null";

    public static final String OPRATER_AND = "and";

    public static final String OPRATER_OR = "or";

    //角色类型--超级管理员
    public static final String ROLE_TYPE_SYS_ADMIN = "0";

    //角色类型--校区管理员
    public static final String ROLE_TYPE_AREA_ADMIN = "1";

    //角色类型--院系管理员
    public static final String ROLE_TYPE_FACULTY_ADMIN = "2";

    //角色类型--辅导员
    public static final String ROLE_TYPE_ASSISTANT = "3";

    //角色类型--任课老师
    public static final String ROLE_TYPE_TEACHER = "4";

    //角色类型--一般角色
    public static final String ROLE_TYPE_NORMAL = "5";

    //系统同步生成的未审核课程计划信息
    public static final String AUTO_COURSEPLAN = "1";

    //人工预览临时生成的未审核课程计划信息
    public static final String MANUAL_COURSEPLAN = "2";

    //未通过审核的历史课程计划信息
    public static final String UNACCEPTED_COURSEPLAN = "0";
	
}
