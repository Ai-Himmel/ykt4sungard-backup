package com.sungard.smartcard;

/**
 * 请求处理结果的返回码，客户端可通过返回码判断后台处理是否成功
 * 系统管理模块的返回码从100001开始
 * 设备管理模块的返回码从200001开始
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-20
 */
public interface RetCode {
    //正常返回
    public int OK = 0;

    //系统异常，"System Error:{}"
    public int SYSTEM_EXCEPTION = 100001;

    //未实现的功能，"Unrealized method"
    public int UNREALIZED_METHOD = 100002;

    //操作员不存在，"OPERATOR [{}] does not exist"
    public int OPERATOR_NOT_EXIST = 100003;

    //参数不存在"param is null:{}"
    public int SYSTEM_PARAM_NULL = 100004;

    //记录不存在 "record [{}] does not exist"
    public int RECORD_NOT_EXIST = 100005;

    //参数错误"param is error:{}"
    public int SYSTEM_PARAM_ERROR = 100006;

    //操作员编号不能为空
    public int OPERCODE_NULL = 100007;

    //设备不存在，"Device [{}] does not exist"
    public int DEVICE_NOT_EXIST = 200001;

    //卡号[{}]已绑定
    public int CARD_BOUND = 1000110401;

    //没有充值操作员授权权限
    public int OPERATOR_NO_BURSARRIGHT=1000110301;


    //卡号不能为空
    public int CARD_NULL = 1000110402;

    //操作员被锁定，"Operator [{}] be locked"
    public int OPERATOR_LOCK = 1000110701;

    //操作员被注销，"Operator [{}] be canceled"
    public int OPERATOR_CANCEL = 1000110702;

    //操作员密码错误，"Operator [{}] inputted the wrong password"
    public int OPERATOR_WRONG_PASSWORD = 1000110703;

    //操作员站点ip不合法，"the ip of site is forbidden"
    public int OPERATOR_WRONG_SITEIP = 1000110704;

    //操作员无法利用ip访问站点，"the operator [{}] has not permission to this site through [{}]"
    public int OPERATOR_WRONG_OPERSITEIP = 1000110705;

    //新增站点名称为空，"name of the site can not be null"
    public int ADDSITE_WRONG_NULLSITENAME = 1000110101;

    //新增站点ip不能为空,"ip must be set"
    public int ADDSITE_WRONG_NULLSITEIP = 1000110102;

    //新增站点名称重复,"the input sitename have exist in database"
    public int ADDSITE_WRONG_DUPLICATESITENAME = 1000110103;

    //新增站点ip重复,"the input ip have exist in database"
    public int ADDSITE_WRONG_DUPLICATESITEIP = 1000110104;

    //新增站点名称超过50字符,"the input sitename have exist in database"
    public int ADDSITE_WRONG_LONGSITENAME = 1000110105;

    //新增站点ip格式错误,"the input ip is not in correct style"
    public int ADDSITE_WRONG_IPSTYLE = 1000110106;

    //删除站点存在关联操作员,"there are some operator rely on this site"
    public int DELSITE_EXISTOPERATOR = 1000110107;

    //网点名称为空,"the name of branch must be set"
    public int ADDBRANCH_WRONG_NULLBRANCHNAME = 1000110001;

    //网点类型为空,"the type of branch must be set"
    public int ADDBRANCH_WRONG_NULLBRANCHTYPE = 1000110002;

    //网点区域号为空
    public int ADDBRANCH_WRONG_NULLAREACODE = 1000110003;

    //网点名称超过50
    public int ADDBRANCH_WRONG_TOOLONGBRANCHNAME = 1000110004;

    //网点名称重复
    public int ADDBRANCH_WRONG_DUPLICATEBRANCHNAME = 1000110005;

    //网点存在关联操作员
    public int DELBRANCH_WRONG_EXISTOPERATOR = 1000110006;

    //网点不存在
    public int DELBRANCH_WRONG_NOTEXISTBRANCH = 1000110007;

    //操作员号不能为空
    public int ADDOPSITE_WRONG_NULLOPERCODE = 1000110501;

    //站点号不能为空
    public int ADDOPSITE_WRONG_NULLOPSITENO = 1000110502;

    //站点号操作员关系已经存在
    public int ADDOPSITE_WRONG_EXISTSOPSITENUM = 1000110503;

    //站点号操作员关系不存在
    public int ADDOPSITE_WRONG_NOTEXISTSOPSITENUM = 1000110504;

    //操作员输入密码错误
    public int OPERATOR_WRONG_NOPRIORITY = 1000110601;

    //操作员号为空
    public int OPERATOR_NULLOPERCODE = 1000110201;

    //操作员名称为空
    public int OPERATOR_NULLOPERNAME = 1000110202;

    //操作员类型为空
    public int OPERATOR_NULLOPERTYPE = 1000110203;

    //是否是限制站点为空
    public int OPERATOR_NULLSITELIMIT = 1000110204;

    //网点号为空
    public int OPERATOR_NULLBRANCHNO = 1000110205;
    
    
    
    
    
    
    //收费类型别已存在
    public int E_EXIST_FEETYPE = 1000410201;
    //收费名称已存在
    public int E_EXIST_FEETYPENAME = 1000410202;
    //该[{收费类别|卡类型|交易码}]已设置为不收费
    public int E_CFGFEE_EXIST_FREEFEE = 1000410401;
    //[{收费类别|卡类型|交易码}]交易收费信息已经存在
    public int E_CFGFEE_EXIST_FEEITEM = 1000410402;
    //免费条目不允许修改
    public int E_CFGFEE_FREEITEM_UPD = 1000410403;

    //卡类型名称[{}]已经存在
    public int E_EXIST_CARDTYPENAME = 1000410601;
    //匿名卡消费类型已存在
    public int E_EXIST_ANONYMCARDTYPE = 1000410602;
    //匿名卡收费类型不能为空
    public int E_NULL_ANONYMCARD_FEETYPE = 1000410603;
    //该卡类型不能删除
    public int E_CARDTYPE_SYSRESERVED = 1000410604;
    //该卡已使用
    public int E_CARDTYPE_USED = 1000410605;
    //该卡类型不存在
    public int E_NOTEXIST_CARDTYPE = 1000410606;
    //过度临时卡参数禁止修改
    public int E_TMPCARDPARA_FORBID_UPDATED = 1000410607;
    //过度临时卡需要设置有效天数
    public int E_TMPCARD_NEED_FIXDAYCNT = 1000410608;


    //在系统中不存在
    public int IS_NOT_EXISTS = 1100110001;
    //在系统中已存在
    public int IS_EXISTS = 1100110002;
    //在系统中不能为空
    public int IS_NOT_NULL = 1100110003;
    //设备已经注销
    public int DEVICE_CANCELLED = 1100110004;
    //设备已经和商户关联
    public int DEVICE_CONNECTWITH_SHOP = 1100110005;
    //长度不等于14
    public int LENGTH_NOT_14 = 1100110006;
    //ip地址不正确
    public int IP_NO_CORRENT = 1100110007;
    //不是整数
    public int IS_NOT_NUMBERIC = 1100110008;


    //根节点不能[{}],如删除，修改
    public int NO_DELORUPD_FARTHERNODE = 1000710001;
    //请先删除下级[{}]，如部门记录、区域记录等
    public int FIRST_DELETE_SONNODE = 1000710002;

    //不匹配
    public int IS_NOT_MATCH = 1400210501;


}
