package org.king.common;

/**
 * .
 * User: Yiming.You
 * Date: 2011-7-06
 */
public class Constant {
    public static final String PROPERTY_FILE_NAME = "epay.properties";

    public static final String DRTPIP1 = "drtpip1";

    public static final String DRTPIP2 = "drtpip2";

    public static final String DRTPPORT1 = "drtpport1";

    public static final String DRTPPORT2 = "drtpport2";

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

    //登陆账户类型
    public static final String ACCOUT_TYPE_CARD = "1"; //持卡人账户
    public static final String ACCOUT_TYPE_SHOP = "2";//商户账户
    public static final String ACCOUT_TYPE_OPER = "3";//操作员

    //网络账户状态
    public static final String NETACC_STATUS_UNACTIVE = "0"; //未激活
    public static final String NETACC_STATUS_NORMAL = "1"; //正常
    public static final String NETACC_STATUS_LOCKED = "2"; //锁定
    public static final String NETACC_STATUS_CLOSDE = "3"; //销户

    //账户操作日志类型：0-账户登录，1-止付，2-解付，3-修改密码，4-重置密码，5-激活
    public static final String EPAY_ACC_LOG_LOGIN = "0";
    public static final String EPAY_ACC_LOG_STOPPAY = "1";
    public static final String EPAY_ACC_LOG_REGAINPAY = "2";
    public static final String EPAY_ACC_LOG_UPDATEPWD = "3";
    public static final String EPAY_ACC_LOG_SETPWD = "4";
    public static final String EPAY_ACC_LOG_ACTIVE = "5";

    //密码类型:1-卡密码，2-支付密码
    public static final String PWD_TYPE_ACC = "1";
    public static final String PWD_TYPE_PAY = "2";
    
    //操作员状态
    public static final String OPER_STATUS_LOCKED = "0"; //锁定
    public static final String OPER_STATUS_NORMAL = "1"; //正常
    public static final String OPER_STATUS_CLOSDE = "2"; //销户

}
