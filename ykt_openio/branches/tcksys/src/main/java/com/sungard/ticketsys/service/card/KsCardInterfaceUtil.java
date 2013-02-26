package com.sungard.ticketsys.service.card;

import org.apache.log4j.Logger;
import org.xvolks.jnative.JNative;
import org.xvolks.jnative.Type;
import org.xvolks.jnative.exceptions.NativeException;
import org.xvolks.jnative.pointers.Pointer;
import org.xvolks.jnative.pointers.memory.MemoryBlockFactory;

import java.io.File;
import java.util.Properties;

/**
 * 读写卡
 */
public class KsCardInterfaceUtil {
    private static final Logger logger = Logger.getLogger(KsCardInterfaceUtil.class);

    private static JNative cardInterface = null;

    private static final String CARD_INTERFACE_DLL = "KsCardInterFace.dll";
    
    private static final String INIT = "KS_Init";

    private static final String OPEN_PORT = "KS_OpenPort";

    private static final String SIGN_IN = "KS_SignIn";

    private static final String CLOSE_PORT = "KS_ClosePort";

    private static final String BEEP = "KS_Beep";

    private static final String BEEP_ERR = "KS_BeepErr";

    private static final String REQUEST_CARD = "KS_RequestCard";

    private static final String RESET = "KS_Reset";

    private static final String SET_READ_FIELD_NAME = "KS_SetReadFieldName";

    private static final String READ_CARD = "KS_ReadCard";

    private static final String GET_FIELD_VAL = "KS_GetFieldVal";

    private static final String GET_ERR_MSG = "KS_GetErrMsg";

    private static final String GET_CARD_STATUS = "KS_GetCardStatus";

    private static final String PAY_PREPARE = "KS_PayPrepare";

    private static final String CARD_BALANCE_DEC = "KS_CardBalanceDec";

    private static final String PAY_PROCESS = "KS_PayProcess";

    private static final String GET_PROVE = "KS_GetProve";

    private static final String UN_PROVE_PROCESS = "KS_UnProveProcess";

    private static final String PAY_CANCEL_PROCESS = "KS_PayCancelProcess";

    /**
     * 加载KsCardInterFace动态库
     */
    public static void loadLibrary() {
    	  String userDir = System.getProperty("user.dir");
          String dll = userDir + File.separator + CARD_INTERFACE_DLL;
          File dllFile = new File(dll);
          if (!dllFile.exists()) {
        	  logger.error("无法加载动态库：" + dll);
//              throw new RuntimeException("无法加载动态库：" + dll);
          }else {
        	  System.load(dll);
              JNative.setLoggingEnabled(false);
              logger.info("加载动态库成功：" + dll);
		}
         
    }

    /**
     * 签  名：int __stdcall KS_Init()
     * 功  能：读卡库环境初始化
     * 参  数：无
     * 返回值：成功则返回0，失败非0
     *
     * @return .
     */
    public static boolean ksInit() {
        boolean success = false;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, INIT);
            //指定返回参数的类型
            cardInterface.setRetVal(Type.INT);
            logger.debug("invoke method " + INIT);
            //调用方法
            cardInterface.invoke();
            //获取返回值
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(INIT + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 签  名：int __stdcall KS_OpenPort(int port, int baud)
     * 功  能：初始化通讯口
     * 参  数：port：取值为0～19时，表示串口1～20；为100时，表示USB口通讯，此时波特率无效。
     * baud：为通讯波特率9600～115200
     * 返回值: 返回0为成功，其他为错误
     *
     * @param port 取值为0～19时，表示串口1～20；为100时，表示USB口通讯，此时波特率无效。
     * @param baud 为通讯波特率9600～115200
     * @return .
     */
    public static boolean ksOpenPort(int port, int baud) {
        boolean success = false;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, OPEN_PORT);

            int i = 0;
            cardInterface.setParameter(i++, Type.INT, String.valueOf(port));
            cardInterface.setParameter(i++, Type.INT, String.valueOf(baud));
            cardInterface.setRetVal(Type.INT);

            logger.debug("invoke method " + OPEN_PORT);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(OPEN_PORT + "[returnValue=" + returnValue + "]");
            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 签  名：int __stdcall KS_SignIn(int* nShopID,char* sShopName)
     * 功  能: 读卡器签到
     * 参  数: nShopID：输出参数，返回读卡器分配的商户号
     * sShopName：输出参数，返回读卡器分配的商户号对应的商户名，长度61字节
     * 返回值: 返回0表示成功, 其他表示失败
     *
     * @param result .
     * @return .
     */
    public static boolean ksSignIn(Properties result) {
        boolean success = false;
        Pointer pShopId = null;
        Pointer pShopName = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, SIGN_IN);
            cardInterface.setRetVal(Type.INT);

            pShopId = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pShopName = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            cardInterface.setParameter(i++, pShopId);
            cardInterface.setParameter(i++, pShopName);

            logger.debug("invoke method " + SIGN_IN);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(SIGN_IN + "[returnValue=" + returnValue + "]");
            if (returnValue == 0) {
                success = true;
                int shopId = pShopId.getAsInt(0);
                String shopName = pShopName.getAsString();
                result.setProperty("shopId", String.valueOf(shopId));
                result.setProperty("shopName", shopName);
                logger.debug(SIGN_IN + "[shopID=" + shopId + ";shopName=" + shopName + "]");
            } else {
                String errMsg = ksGetErrMsg();
                result.setProperty("errMsg", errMsg);
                logger.error(errMsg);
            }
        } catch (NativeException e) {
        	result.setProperty("errMsg", e.getMessage());
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
        	result.setProperty("errMsg", e.getMessage());
            logger.error(e.getMessage());
        } finally {
            dispose(pShopId);
            dispose(pShopName);
        }
        return success;
    }

    /**
     * 签  名：int __stdcall KS_ClosePort()
     * 功  能: 关闭已打开的端口
     * 参  数: 无
     * 返回值: 返回0为成功，其他为错误
     *
     * @return .
     */
    public static boolean ksClosePort() {
        boolean success = false;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, CLOSE_PORT);
            cardInterface.setRetVal(Type.INT);
            logger.debug("invoke method " + CLOSE_PORT);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(CLOSE_PORT + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 签  名：void __stdcall KS_Beep()
     * 功  能: 读卡器蜂鸣
     * 参  数: 无
     * 返回值: 返回0为成功，其他为错误
     *
     * @return .
     */
    public static void ksBeep() {
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, BEEP);
            logger.debug("invoke method " + BEEP);
            cardInterface.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 签  名：void __stdcall KS_BeepErr()
     * 功  能: 读卡器蜂鸣
     * 参  数: 无
     * 返回值: 返回0为成功，其他为错误
     *
     * @return .
     */
    public static void ksBeepErr() {
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, BEEP_ERR);
            logger.debug("invoke method " + BEEP_ERR);
            cardInterface.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 签  名：int __stdcall KS_RequestCard(char *sCardPhyID)
     * 功  能：寻卡
     * 参  数: char *sCardPhyID 输出参数，返回卡的物理序列号,长度17字节。
     * 返回值: 返回0为成功，其他为错误
     *
     * @param result .
     * @return .
     */
    public static boolean ksRequestCard(Properties result) {
        boolean success = false;
        Pointer pCardPhyId = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, REQUEST_CARD);
            cardInterface.setRetVal(Type.INT);
            pCardPhyId = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            cardInterface.setParameter(i++, pCardPhyId);

            logger.debug("invoke method " + REQUEST_CARD);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(REQUEST_CARD + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
                String cardPhyId = pCardPhyId.getAsString();
                result.setProperty("cardPhyId", cardPhyId);
            } else {
            	result.setProperty("errMsg", ksGetErrMsg());
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
            result.setProperty("errMsg", e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
            result.setProperty("errMsg", e.getMessage());
        } finally {
            dispose(pCardPhyId);
        }
        return success;
    }

    /**
     * 签  名：void __stdcall KS_Reset();
     * 功  能：重置读写字段标志，同时清空缓存数据。
     * 参  数: 无
     * 返回值: 无
     *
     * @return .
     */
    public static void ksReset() {
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, RESET);
            logger.debug("invoke method " + RESET);
            cardInterface.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 签  名：int __stdcall KS_SetReadFieldName(char *fieldname)
     * 功  能: 设置要读取的字段(FieldName)
     * 参  数: char *fieldname字段名，大写的英文字母，FileName范围见文档
     * 返回值: 返回0为成功，其他为错误
     *
     * @param fieldName .
     * @return .
     */
    public static boolean ksSetReadFieldName(String fieldName) {
        boolean success = false;
        Pointer pFieldName = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, SET_READ_FIELD_NAME);
            cardInterface.setRetVal(Type.INT);
            pFieldName = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pFieldName.setMemory(fieldName);
            int i = 0;
            cardInterface.setParameter(i++, pFieldName);

            logger.debug("invoke method " + SET_READ_FIELD_NAME);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(SET_READ_FIELD_NAME + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        } finally {
            dispose(pFieldName);
        }
        return success;
    }

    /**
     * 签  名：int __stdcall KS_ReadCard ()
     * 功  能: 从卡中读取信息
     * 参  数: 无
     * 返回值: 返回0表示成功, 非0表示失败(不对应错误码)
     *
     * @return .
     */
    public static boolean ksReadCard() {
        boolean success = false;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, READ_CARD);
            cardInterface.setRetVal(Type.INT);

            logger.debug("invoke method " + READ_CARD);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(READ_CARD + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 签  名：int __stdcall KS_GetFieldVal(char *fieldname,char *fieldval)
     * 功  能:读取卡中指定字段名的值
     * 参  数: fieldname字段名,如CARDNO、CUSTID等
     * Fieldval：输出值，为对应字段的值
     * 返回值: 返回0为成功
     *
     * @param fieldName .
     * @param result    .
     * @return .
     */
    public static boolean ksGetFieldVal(String fieldName, Properties result) {
        boolean success = false;
        Pointer pFieldName = null;
        Pointer pFieldVal = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, GET_FIELD_VAL);
            cardInterface.setRetVal(Type.INT);
            pFieldName = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pFieldVal = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pFieldName.setMemory(fieldName);
            int i = 0;
            cardInterface.setParameter(i++, pFieldName);
            cardInterface.setParameter(i++, pFieldVal);

            logger.debug("invoke method " + GET_FIELD_VAL);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(GET_FIELD_VAL + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
                String fieldValue = pFieldVal.getAsString();
                result.setProperty(fieldName, fieldValue);
                logger.debug(GET_FIELD_VAL + "[fieldName=" + fieldName + ";fieldValue=" + fieldValue + "]");
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        } finally {
            dispose(pFieldName);
            dispose(pFieldVal);
        }
        return success;
    }

    /**
     * 读取卡中某一字段值
     *
     * @param fieldName .
     * @param result    .
     */
    public static boolean getFieldValue(String fieldName, Properties result) {
        if (!ksSetReadFieldName(fieldName)) {
            ksGetErrMsg();
            result.setProperty("errMsg", ksGetErrMsg());
            return false;
        }
        if (!ksReadCard()) {
            ksGetErrMsg();
            result.setProperty("errMsg", ksGetErrMsg());
            return false;
        }
        if (!ksGetFieldVal(fieldName, result)) {
            ksGetErrMsg();
            result.setProperty("errMsg", ksGetErrMsg());
            return false;
        }
        return true;
    }

    /**
     * 签  名：char* __stdcall KS_GetErrMsg(char *msg);
     * 功  能:当调用函数失败时，立即调用函数获取错误信息。
     * 参  数:char* msg :输出参数，可以为NULL
     * 返回值：char* 返回错误信息
     *
     * @return .
     */
    public static String ksGetErrMsg() {
        String msg = "";
        Pointer pMsg = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, GET_ERR_MSG);
            cardInterface.setRetVal(Type.STRING);
            pMsg = new Pointer(MemoryBlockFactory.createMemoryBlock(500));
            int i = 0;
            cardInterface.setParameter(i++, pMsg);

            logger.debug("invoke method " + GET_ERR_MSG);
            cardInterface.invoke();
            msg = pMsg.getAsString();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        } finally {
            dispose(pMsg);
        }
        return msg;
    }

    /**
     * 签  名：int __stdcall KS_GetCardStatus(int cardno,char *statuscode,char *statusinfo);
     * 功  能:根据交易卡号联机到服务器数据库检查卡状态。
     * 参  数:int cardno 交易卡号，输入参数
     * Char* Statuscode 输出参数 状态码 ，1字节
     *
     * @param cardno .
     * @param result .
     * @return .
     */
    public static boolean ksGetCardStatus(int cardno, Properties result) {
        boolean success = false;
        Pointer pStatusCode = null;
        Pointer pStatusInfo = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, GET_CARD_STATUS);
            cardInterface.setRetVal(Type.INT);
            pStatusCode = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pStatusInfo = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            cardInterface.setParameter(i++, Type.INT, String.valueOf(cardno));
            cardInterface.setParameter(i++, pStatusCode);
            cardInterface.setParameter(i++, pStatusInfo);

            logger.debug("invoke method " + GET_CARD_STATUS);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(GET_CARD_STATUS + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
                String statusCode = pStatusCode.getAsString();
                String statusInfo = pStatusInfo.getAsString();
                result.setProperty("statusCode", statusCode);
                result.setProperty("statusInfo", statusInfo);
                logger.debug(GET_CARD_STATUS + "[statusCode=" + statusCode + ";statusInfo=" + statusInfo + "]");
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        } finally {
            dispose(pStatusCode);
            dispose(pStatusInfo);
        }
        return success;
    }

    /**
     * 扣款预处理函数
     * 签  名：int __stdcall KS_PayPrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefNo,char *sMac)
     * 功  能: 联机检查卡是否合法，并进行交易初始化处理。
     * 参  数:
     * 输入值：
     * sCardPhyID:卡片序列号,8字节十六进制字符串
     * nCardNo：  交易卡号
     * nCardBal： 卡余额（交易前余额），单位为分
     * nPayCnt ：  消费次数
     * nTransAmt： 消费金额，单位为分
     * 输出值：
     * sRefNo：	 交易参考号 长度14位，输出参数，返回该交易的交易参考号。
     * sMac ：	 该交易参考号的MAC值
     * 返回值: 返回0表示成功, 其他表示失败
     *
     * @param cardPhyId .
     * @param cardno    .
     * @param cardBal   .
     * @param payCnt    .
     * @param transAmt  .
     * @param result    .
     * @return .
     */
    public static boolean ksPayPrepare(String cardPhyId, int cardno, int cardBal, int payCnt, int transAmt, Properties result) {
        boolean success = false;
        Pointer pRefNo = null;
        Pointer pMac = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, PAY_PREPARE);
            cardInterface.setRetVal(Type.INT);
            pRefNo = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pMac = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            cardInterface.setParameter(i++, Type.STRING, cardPhyId);
            cardInterface.setParameter(i++, Type.INT, String.valueOf(cardno));
            cardInterface.setParameter(i++, Type.INT, String.valueOf(cardBal));
            cardInterface.setParameter(i++, Type.INT, String.valueOf(payCnt));
            cardInterface.setParameter(i++, Type.INT, String.valueOf(transAmt));
            cardInterface.setParameter(i++, pRefNo);
            cardInterface.setParameter(i++, pMac);

            logger.debug("invoke method " + PAY_PREPARE);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(PAY_PREPARE + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
                String refNo = pRefNo.getAsString();
                String mac = pMac.getAsString();
                result.setProperty("refNo", refNo);
                result.setProperty("mac", mac);
                logger.debug(PAY_PREPARE + "[refNo=" + refNo + ";mac=" + mac + "]");
            } else {
            	 result.setProperty("errMsg",ksGetErrMsg());
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
            result.setProperty("errMsg", e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
            result.setProperty("errMsg", e.getMessage());
        } finally {
            dispose(pRefNo);
            dispose(pMac);
        }
        return success;
    }

    /**
     * 扣卡余额函数
     * 签  名：int __stdcall KS_CardBalanceDec(char* cGetProveFlag);
     * 功  能：扣卡钱包余额
     * 参  数：char* cGetProveFlag  为0x00表示扣款失败，为0x01表示写卡未完成，中途拔卡。
     * 返回值：0表示函数调用成功，其他表示函数调用失败，可以使用KS_GetErrMsg来得到错误信息。
     *
     * @param result .
     * @return .
     */
    public static boolean ksCardBalanceDec(Properties result) {
        boolean success = false;
        Pointer pGetProveFlag = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, CARD_BALANCE_DEC);
            cardInterface.setRetVal(Type.INT);
            logger.debug("invoke method " + CARD_BALANCE_DEC);
            pGetProveFlag = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            cardInterface.setParameter(i++, pGetProveFlag);

            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(CARD_BALANCE_DEC + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
                String getProveFlag = pGetProveFlag.getAsString();
                result.setProperty("getProveFlag", getProveFlag);
                logger.debug(CARD_BALANCE_DEC + "[getProveFlag=" + getProveFlag + "]");
            } else {
            	result.setProperty("errMsg", ksGetErrMsg());
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
        	result.setProperty("errMsg", e.getMessage());
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
        	result.setProperty("errMsg", e.getMessage());
            logger.error(e.getMessage());
        } finally {
            dispose(pGetProveFlag);
        }
        return success;
    }

    /**
     * 消费处理函数
     * 签  名：int __stdcall  KS_PayProcess()
     * 功  能: 扣款成功后，提交到后台进行流水记账处理。
     * 参  数: 无
     * 返回值: 返回0表示成功, 其他表示失败
     *
     * @return
     */
    public static boolean ksPayProcess(Properties result) {
        boolean success = false;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, PAY_PROCESS);
            cardInterface.setRetVal(Type.INT);
            logger.debug("invoke method " + PAY_PROCESS);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(PAY_PROCESS + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
            	result.setProperty("errMsg", ksGetErrMsg());
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
        	result.setProperty("errMsg", e.getMessage());
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
        	result.setProperty("errMsg", e.getMessage());
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 取交易认证函数
     * 签  名：int __stdcall KS_GetProve(char* cReWriteCardFlag);
     * 功  能：当扣卡余额函数调用出现中途拔卡时，需要调用本函数，判断是否需要重新写卡。
     * 参  数：char* cReWriteCardFlag   输出参数 ，0x00表示写卡已成功，不需要重新写卡 0x01表示写卡失败，需要重新写卡
     *
     * @return .
     */
    public static boolean ksGetProve() {
        boolean success = false;
        Pointer pRewriteCardFlag = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, GET_PROVE);
            cardInterface.setRetVal(Type.INT);
            pRewriteCardFlag = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            cardInterface.setParameter(i++, pRewriteCardFlag);

            logger.debug("invoke method " + GET_PROVE);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(GET_PROVE + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        } finally {
            dispose(pRewriteCardFlag);
        }
        return success;
    }

    /**
     * 取交易认证失败处理函数
     * 签  名：int __stdcall KS_UnProveProcess();
     * 功  能：当出现中途拔卡，而持卡人没有重新刷卡的异常情况下，调用本函数中止交易。
     * 参  数：无。
     * 返回值: 返回0表示成功, 其他表示失败
     *
     * @return .
     */
    public static boolean ksUnProveProcess() {
        boolean success = false;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, UN_PROVE_PROCESS);
            cardInterface.setRetVal(Type.INT);
            logger.debug("invoke method " + UN_PROVE_PROCESS);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(UN_PROVE_PROCESS + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 扣费冲正函数
     * 签  名：int __stdcall KS_PayCancelProcess(const char *sRefNo,const char *sMac,const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt);
     *
     * @return .
     */
    public static boolean ksPayCancelProcess(String refNo, String mac, String cardPhyId, int cardno, int cardBal, int dpsCnt) {
        boolean success = false;
        Pointer pRefNo = null;
        Pointer pMac = null;
        Pointer pCardPhyId = null;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, PAY_CANCEL_PROCESS);
            cardInterface.setRetVal(Type.INT);
            pRefNo = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pMac = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pCardPhyId = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pRefNo.setMemory(refNo);
            pMac.setMemory(mac);
            pCardPhyId.setMemory(cardPhyId);
            int i = 0;
            cardInterface.setParameter(i++, pRefNo);
            cardInterface.setParameter(i++, pMac);
            cardInterface.setParameter(i++, pCardPhyId);
            cardInterface.setParameter(i++, Type.INT, String.valueOf(cardno));
            cardInterface.setParameter(i++, Type.INT, String.valueOf(cardBal));
            cardInterface.setParameter(i++, Type.INT, String.valueOf(dpsCnt));

            logger.debug("invoke method " + PAY_CANCEL_PROCESS);
            cardInterface.invoke();
            int returnValue = cardInterface.getRetValAsInt();
            logger.debug(PAY_CANCEL_PROCESS + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        } finally {
            dispose(pRefNo);
            dispose(pMac);
            dispose(pCardPhyId);
        }
        return success;
    }

    /**
     * 释放资源
     *
     * @param pointer .
     */
    public static void dispose(Pointer pointer) {
        try {
            if (pointer != null) {
                pointer.dispose();
            }
        } catch (NativeException e) {
        }
    }
}
