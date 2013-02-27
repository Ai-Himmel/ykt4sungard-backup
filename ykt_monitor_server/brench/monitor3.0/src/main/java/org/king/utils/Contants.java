/* ============================================================
 * ��Ȩ��    king ��Ȩ���� (c) 2006
 * �ļ���    org.king.utils.ContantsUtil.java
 * �������ڣ� 2006-6-15 16:45:14
 * ���ܣ�    {����Ҫʵ�ֵĹ���}
 * ������:   {��������}
 * �޸ļ�¼��
 * ����                    ����         ����
 * =============================================================
 * 2006-6-15 16:45:14      ljf        �����ļ���ʵ�ֻ�������
 * ============================================================
 */

/**
 *
 */
package org.king.utils;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.king.support.util.GetPropertiesUtil;

import java.text.Format;
import java.text.MessageFormat;
import java.util.HashMap;
import java.util.Map;

/**
 * <p> ContantsUtil.java </p>
 * <p> {����˵��} </p>
 * <p/>
 * <p><a href="ContantsUtil.java.html"><i>�鿴Դ����</i></a></p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 */
public class Contants extends ConfigurableContants {

    /**
     * ����״̬
     */
    public static Map HOST_STATUS;

    /**
     * ����״̬
     */
    public static Map SERVICE_STATUS;

    /**
     * �豸״̬
     */
    public static Map TERMDEVICE_STATUS;

    /**
     * �豸����״̬
     */
    public static Map TERMDEVSERVICE_STATUS;

    public static Map YES_NO_STATUS;

    public static Map HOST_TYPE;
    
    public static Map HOST_DIV;

    /**
     * �������ַ�����ʽ���ɶ�Ӧ��ʱ���ʽ
     */
    public static Format DATE_FORMAT = new MessageFormat("{0}-{1}-{2} {3}:{4}:{5}");

    static {
        init("oneks.properties");
        initHostStatus();
        initServiceStatus();
        initTermdeviceStatus();
        initTermdevserviceStatus();
        initYesNoStatus();
        initHostType();
        initHostDiv();
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
        YES_NO_STATUS.put("1", "��");
        YES_NO_STATUS.put("0", "��");
    }

    private static void initHostType() {
        HOST_TYPE = new HashMap();
        HOST_TYPE.put("00", "���ݿ������");
        HOST_TYPE.put("01", "�洢�豸(��)");
        HOST_TYPE.put("02", "�洢�豸(��)");
        HOST_TYPE.put("03", "Ӧ�÷�����(��)");
        HOST_TYPE.put("04", "Ӧ�÷�����(��)");
        HOST_TYPE.put("05", "����������(��)");
        HOST_TYPE.put("06", "����������(��)");
        HOST_TYPE.put("07", "WEB������");
        HOST_TYPE.put("08", "ǰ�÷�����");
        HOST_TYPE.put("09", "Ȧ�������");
        HOST_TYPE.put("10", "����������");
        HOST_TYPE.put("11", "��ý��");
        HOST_TYPE.put("12", "Ȧ���");
        HOST_TYPE.put("13", "LANPORT");
        HOST_TYPE.put("14", "����������");
    }
    
    private static void initHostDiv(){
    	HOST_DIV = new HashMap();
    	 HOST_DIV.put("00", "dataserver_1");
         HOST_DIV.put("01", "datastore_1");
         HOST_DIV.put("02", "datastore_2");
         HOST_DIV.put("03", "server_1");
         HOST_DIV.put("04", "server_2");
         HOST_DIV.put("05", "server_3");
         HOST_DIV.put("06", "server_4");
         HOST_DIV.put("07", "pc_server_1");
         HOST_DIV.put("08", "pc_server_2");
         HOST_DIV.put("09", "pc_server_3");
         HOST_DIV.put("10", "pc_server_4");
         HOST_DIV.put("14", "pc_server_7");
    }

    /**
     * ����ܽ����豸���豸����
     */
    public static String getFormatDevtypeCode() {
        PropertiesConfiguration config = GetPropertiesUtil.getInstance();
        String[] array = config.getStringArray("countable.devtypecode");
        StringBuffer result = new StringBuffer();
        if (array != null && array.length > 0) {
            for (int i = 0; i < array.length; i++) {
                result.append("'").append(array[i]).append("',");
            }
            result = result.deleteCharAt(result.length() - 1);
        } else {
            result.append("' '");
        }
        return result.toString();
    }
}
