package org.king.utils;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.king.framework.common.ConfigurableContants;

import java.text.Format;
import java.text.MessageFormat;
import java.util.HashMap;
import java.util.Map;

/**
 * <p> ContantsUtil.java </p>
 * <p> {功能说明} </p>
 * <p/>
 * <p><a href="ContantsUtil.java.html"><i>查看源代码</i></a></p>
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-15
 */
public class Contants extends ConfigurableContants {

	//冲正标志
	public static Map REV_TRANSDTL_FLAG;
	//交易流水状态
    public static Map TRANSDTL_STATUS ;
	// 止付标志
    public static Map STOPPAY_FLAG;
    //网络账户状态
    public static Map NETACC_STATUS;
    //网络账户状态
    public static Map SHOPACC_STATUS;
    
    public static String EPAY_ERROR_ILLEGAL_PARA = "600031";//参数不合法
    public static String EPAY_ERROR_ILLEGAL_AUTH_CODE = "600032";//code认证失败
    public static String EPAY_ERROR_ACCOUNT_STUTS_LOCK = "600033";//账户锁定
    public static String EPAY_ERROR_ACCOUNT_STUTS_STOP = "600034";//账户止付
    public static String EPAY_ERROR_ACCOUNT_STUTS_SLEEP = "600035";//账户未激活
    public static String EPAY_ERROR_ACCOUNT_STUTS_LOGOUT = "600036";//账户已注销
    public static String EPAY_ERROR_ACCOUNT_ERROR = "600037";//账户异常
    public static String EPAY_ERROR_ACCOUNT_AVAILBAL_NOENOUGH = "600038";//账户余额不足
    public static String EPAY_ERROR_SERVER_ERROR = "600039";//后台处理失败
    public static String EPAY_ERROR_FRESHSUBMIT = "600041";//重复提交
    /**
     * 将日期字符串格式化成对应的时间格式
     */
    public static Format DATE_FORMAT = new MessageFormat("{0}-{1}-{2}");
    public static Format DATE_TIME_FORMAT = new MessageFormat("{0}-{1}-{2} {3}:{4}:{5}");
    public static Format TIME_FORMAT= new MessageFormat("{0}:{1}:{2}");

    static {
        init("oneks.properties");
        initStopPayFlag();
        initNetaccStatus();
        initShopaccStatus();
        initTransdtlStatus();
        initRevFlag();
    }



    private static void initStopPayFlag() {
    	STOPPAY_FLAG = new HashMap();
    	STOPPAY_FLAG.put("0", "正常");
    	STOPPAY_FLAG.put("1", "止付");
    }

    private static void initNetaccStatus() {
        NETACC_STATUS = new HashMap();
        NETACC_STATUS.put("0", "未激活");
        NETACC_STATUS.put("1", "正常");
        NETACC_STATUS.put("2", "锁定");
        NETACC_STATUS.put("3", "销户");
    }

    private static void initShopaccStatus() {
        SHOPACC_STATUS = new HashMap();
        SHOPACC_STATUS.put("1", "正常");
        SHOPACC_STATUS.put("2", "销户");
    }
    
    private static void initTransdtlStatus() {
    	TRANSDTL_STATUS = new HashMap();
    	TRANSDTL_STATUS.put("1", "未处理");
    	TRANSDTL_STATUS.put("2", "失败");
    	TRANSDTL_STATUS.put("3", "成功");
    	TRANSDTL_STATUS.put("4", "异常流水");
    	TRANSDTL_STATUS.put("5", "无效流水");
    	TRANSDTL_STATUS.put("6", "重复流水");
    	TRANSDTL_STATUS.put("7", "消费失败流水");
    }
    
    private static void initRevFlag() {
    	REV_TRANSDTL_FLAG = new HashMap();
    	REV_TRANSDTL_FLAG.put("0", "- -");
    	REV_TRANSDTL_FLAG.put("1", "已冲正");
    }
   
}
