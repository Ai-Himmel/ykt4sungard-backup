/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.utils.ContantsUtil.java
 * 创建日期： 2006-6-15 16:45:14
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-15 16:45:14      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.utils;

import java.text.Format;
import java.text.MessageFormat;
import java.util.HashMap;
import java.util.Map;
import java.util.Properties;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.king.support.util.GetPropertiesUtil;

/**
 * <p> ContantsUtil.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ContantsUtil.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 * 
 *
 */
public class Contants extends ConfigurableContants{

    /**
     * 主机状态
     */
    public static Map HOST_STATUS;

    /**
     * 服务状态
     */
    public static Map SERVICE_STATUS;

    /**
     * 设备状态
     */
    public static Map TERMDEVICE_STATUS;

    /**
     * 设备服务状态
     */
    public static Map TERMDEVSERVICE_STATUS;

    public static Map YES_NO_STATUS;

    /**
     * 将日期字符串格式化成对应的时间格式
     */
    public static Format DATE_FORMAT = new MessageFormat("{0}-{1}-{2} {3}:{4}:{5}");
	
    static {
        init("oneks.properties");
        initHostStatus();
        initServiceStatus();
        initTermdeviceStatus();
        initTermdevserviceStatus();
        initYesNoStatus();
    }

    public final static String LDAP_PATH = getProperty("constant.ldap.path", "/");
	
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

    public static final String NOTIFY_HOST_BY_EMAIL = "notify-host-by-email";

    public static final String NOTIFY_HOST_BY_SMS = "notify-host-by-sms";

    public static final String NOTIFY_SERVICE_BY_EMAIL = "notify-service-by-email";

    public static final String NOTIFY_SERVICE_BY_SMS = "notify-service-by-sms";

    private static void initHostStatus() {
        HOST_STATUS = new HashMap();
        HOST_STATUS.put("0", "up");
        HOST_STATUS.put("1", "down");
        HOST_STATUS.put("2", "unreachable");
        HOST_STATUS.put("3", "pending");
    }

    private static void initServiceStatus() {
        SERVICE_STATUS = new HashMap();
        SERVICE_STATUS.put("0", "ok");
        SERVICE_STATUS.put("1", "warning");
        SERVICE_STATUS.put("2", "critical");
        SERVICE_STATUS.put("3", "unknow");
        SERVICE_STATUS.put("4", "pending");
    }

    private static void initTermdeviceStatus() {
        TERMDEVICE_STATUS = new HashMap();
        TERMDEVICE_STATUS.put("0", "up");
        TERMDEVICE_STATUS.put("1", "down");
        TERMDEVICE_STATUS.put("2", "unreachable");
    }

    private static void initTermdevserviceStatus() {
        TERMDEVSERVICE_STATUS = new HashMap();
        TERMDEVSERVICE_STATUS.put("0", "ok");
        TERMDEVSERVICE_STATUS.put("1", "warning");
        TERMDEVSERVICE_STATUS.put("2", "critical");
    }

    private static void initYesNoStatus() {
        YES_NO_STATUS = new HashMap();
        YES_NO_STATUS.put("1", "是");
        YES_NO_STATUS.put("0", "否");
    }

    /**
     * 获得能接子设备的设备代码
     */
    public static String getFormatDevtypeCode(){
        PropertiesConfiguration config = GetPropertiesUtil.getInstance();
        String[] array = config.getStringArray("countable.devtypecode");
        StringBuffer result = new StringBuffer();
        if(array!=null && array.length>0){
            for(int i=0;i<array.length;i++){
                result.append("'").append(array[i]).append("',");
            }
            result = result.deleteCharAt(result.length()-1);
        } else {
            result.append("' '");
        }
        return result.toString();
    }
}
