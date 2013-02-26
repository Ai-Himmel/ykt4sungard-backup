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
 * .
 * User: Yiming.You
 * Date: 2011-8-3
 */
public class KsCardUtil {
    private static final Logger logger = Logger.getLogger(KsCardUtil.class);

    private static JNative ksCard = null;

    private static final String KS_CARD_DLL = "kscard.dll";

    private static final String SET_MIFARE1_KEY = "ks_setmifare1key";

    private static final String MODIFY_STATUS = "ks_modifystatus";

    private static final String SET_FIELD_WRITE_MODE = "ks_setfieldwritemode";

    private static final String CLEAR_ALL_FILE_WRITE_MODE = "ks_clearallfieldwritemode";

    private static final String SET_FIELD_VAL = "ks_setfieldval";

    private static final String INIT = "ks_init";

    private static final String GET_ERR_MSG = "ks_geterrmsg";

    private static final String OPEN_PORT = "ks_openport";

    private static final String CARD = "ks_card";

    private static final String WRITE_CARD = "ks_writecard";

    private static final String LOAD_CARD_KEYS = "ks_loadcardkeys";

    private static final String BEEP = "ks_beep";

    private static final String BEEP_ERR = "ks_beeperr";

    private static final String RESET = "ks_reset";

    private static final String SET_FIELD_READ_MODE = "ks_setfieldreadmode";

    private static final String READ_CARD = "ks_readcard";

    private static final String GET_FIELD_VAL = "ks_getfieldval";

    public static void loadLibrary() {
        String userDir = System.getProperty("user.dir");
        String dll = userDir + File.separator + KS_CARD_DLL;
        File dllFile = new File(dll);
        if (!dllFile.exists()) {
            throw new RuntimeException("无法加载动态库：" + dll);
        }
        System.load(dll);
//        JNative.setLoggingEnabled(false);
        logger.info("加载动态库成功：" + dll);
    }

    /**
     * 签  名：int __stdcall ks_init();
     * 功  能：读卡库环境初始化
     * 参  数：无
     * 返回值：成功则返回0，失败非0
     *
     * @return .
     */
    public static boolean ksInit() {
        boolean success = false;
        try {
            ksCard = new JNative(KS_CARD_DLL, INIT);
            //指定返回参数的类型
            ksCard.setRetVal(Type.INT);
            logger.debug("invoke method " + INIT);
            //调用方法
            ksCard.invoke();
            //获取返回值
            int returnValue = ksCard.getRetValAsInt();
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
     * 签  名：int __stdcall ks_openport(int port,int band);
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
            ksCard = new JNative(KS_CARD_DLL, OPEN_PORT);

            int i = 0;
            ksCard.setParameter(i++, Type.INT, String.valueOf(port));
            ksCard.setParameter(i++, Type.INT, String.valueOf(baud));
            ksCard.setRetVal(Type.INT);

            logger.debug("invoke method " + OPEN_PORT);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
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
     * 签  名：int __stdcall ks_card(char *sCardPhyID);
     * 功  能：寻卡
     * 参  数: char *sCardPhyID 输出参数，返回卡的物理序列号,长度17字节。
     * 返回值: 返回0为成功，其他为错误
     *
     * @param result .
     * @return .
     */
    public static boolean ksCard(Properties result) {
        boolean success = false;
        Pointer pCardPhyId = null;
        try {
            ksCard = new JNative(KS_CARD_DLL, CARD);
            ksCard.setRetVal(Type.INT);
            pCardPhyId = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            ksCard.setParameter(i++, pCardPhyId);

            logger.debug("invoke method " + CARD);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
            logger.debug(CARD + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
                String cardPhyId = pCardPhyId.getAsString();
                result.setProperty("cardPhyId", cardPhyId);
            } else {
                //logger.error(ksGetErrMsg());
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        } finally {
            dispose(pCardPhyId);
        }
        return success;
    }

    /**
     * 签  名：char* __stdcall ks_geterrmsg(char *errmsg);
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
            ksCard = new JNative(KS_CARD_DLL, GET_ERR_MSG);
            ksCard.setRetVal(Type.STRING);
            pMsg = new Pointer(MemoryBlockFactory.createMemoryBlock(500));
            int i = 0;
            ksCard.setParameter(i++, pMsg);

            logger.debug("invoke method " + GET_ERR_MSG);
            ksCard.invoke();
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
     * 设置MF1卡工作密钥
     * 签  名：int __stdcall ks_setmifare1key(const char sWorkKey[17]);
     *
     * @return .
     */
    public static boolean ksSetmifare1key(String key) {
        boolean success = false;
        try {
            ksCard = new JNative(KS_CARD_DLL, SET_MIFARE1_KEY);
            ksCard.setRetVal(Type.INT);
            int i = 0;
            logger.debug("mifare1key:" + key);
            ksCard.setParameter(i++, Type.STRING, key);

            logger.debug("invoke method " + SET_MIFARE1_KEY);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
            logger.debug(SET_MIFARE1_KEY + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                //error
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 装载密钥
     * 签  名：int __stdcall ks_loadcardkeys(const char *sKeyCardPwd);
     *
     * @return .
     */
    public static boolean ksLoadCardKeys(String key) {
        boolean success = false;
        try {
            ksCard = new JNative(KS_CARD_DLL, LOAD_CARD_KEYS);
            ksCard.setRetVal(Type.INT);
            int i = 0;
            logger.debug("key:" + key);
            ksCard.setParameter(i++, Type.STRING, key);

            logger.debug("invoke method " + LOAD_CARD_KEYS);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
            logger.debug(LOAD_CARD_KEYS + "[returnValue=" + returnValue + "]");

            if (returnValue == 0) {
                success = true;
            } else {
                //error
            }
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
        return success;
    }

    /**
     * 修改卡状态
     *
     * @return .
     */
    public static boolean ksModifystatus(String cardPhyId, int fieldID, String fieldVal) {
        boolean success = false;
        ksClearAllFieldWriteMode();
        ksSetFieldWriteMode(fieldID);
        if (ksSetFieldVal(fieldID, fieldVal)) {
            success = ksWriteCard(cardPhyId);
        }
        return success;
    }

    /**
     * 设置该字段写模式
     * 签  名：void __stdcall ks_setfieldwritemode(int fieldID);
     *
     * @return .
     */
    public static void ksSetFieldWriteMode(int fieldID) {
        try {
            ksCard = new JNative(KS_CARD_DLL, SET_FIELD_WRITE_MODE);
            int i = 0;
            ksCard.setParameter(i++, Type.INT, String.valueOf(fieldID));

            logger.debug("invoke method " + SET_FIELD_WRITE_MODE);
            ksCard.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 清除所有字段的写模式
     * 签  名：void __stdcall ks_clearallfieldwritemode();
     *
     * @return .
     */
    public static void ksClearAllFieldWriteMode() {
        try {
            ksCard = new JNative(KS_CARD_DLL, CLEAR_ALL_FILE_WRITE_MODE);

            logger.debug("invoke method " + CLEAR_ALL_FILE_WRITE_MODE);
            ksCard.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 设置写字段数据
     * 签  名：int __stdcall ks_setfieldval(int fieldID,const char *fieldval);
     *
     * @return .
     */
    public static boolean ksSetFieldVal(int fieldID, String fieldVal) {
        boolean success = false;
        Pointer pFieldVal = null;
        try {
            ksCard = new JNative(KS_CARD_DLL, SET_FIELD_VAL);
            ksCard.setRetVal(Type.INT);
            pFieldVal = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pFieldVal.setMemory(fieldVal);
            int i = 0;
            ksCard.setParameter(i++, Type.INT, String.valueOf(fieldID));
            ksCard.setParameter(i++, pFieldVal);

            logger.debug("invoke method " + SET_FIELD_VAL);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
            logger.debug(SET_FIELD_VAL + "[returnValue=" + returnValue + "]");

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
            dispose(pFieldVal);
        }

        return success;
    }

    /**
     * 写卡
     * 签  名：int __stdcall ks_writecard (const char *sCardPhyID=NULL);
     *
     * @return .
     */
    public static boolean ksWriteCard(String cardPhyId) {
        boolean success = false;
        Pointer pCardPhyId = null;
        try {
            ksCard = new JNative(KS_CARD_DLL, WRITE_CARD);
            ksCard.setRetVal(Type.INT);
            pCardPhyId = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            pCardPhyId.setMemory(cardPhyId);
            int i = 0;
            ksCard.setParameter(i++, pCardPhyId);

            logger.debug("invoke method " + WRITE_CARD);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
            logger.debug(WRITE_CARD + "[returnValue=" + returnValue + "]");

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
            dispose(pCardPhyId);
        }

        return success;
    }

    /**
     * 签  名：void __stdcall ks_beep();
     * 功  能: 读卡器蜂鸣
     * 参  数: 无
     * 返回值: 返回0为成功，其他为错误
     */
    public static void ksBeep() {
        try {
            ksCard = new JNative(KS_CARD_DLL, BEEP);
            logger.debug("invoke method " + BEEP);
            ksCard.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 签  名：void __stdcall ks_beeperr();
     * 功  能: 读卡器蜂鸣
     * 参  数: 无
     * 返回值: 返回0为成功，其他为错误
     */
    public static void ksBeepErr() {
        try {
            ksCard = new JNative(KS_CARD_DLL, BEEP_ERR);
            logger.debug("invoke method " + BEEP_ERR);
            ksCard.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 签  名：int __stdcall ks_reset(int msec);
     * 功  能：重置读写字段标志，同时清空缓存数据。
     * 参  数: 无
     * 返回值: 无
     *
     * @return .
     */
    public static void ksReset() {
        try {
            ksCard = new JNative(KS_CARD_DLL, RESET);
            logger.debug("invoke method " + RESET);
            ksCard.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 签  名：void __stdcall ks_setfieldreadmode(int fieldID);
     * 功  能: 设置要读取的字段
     * 返回值: 返回0为成功，其他为错误
     *
     * @param fieldID .
     */
    public static void ksSetFieldReadMode(int fieldID) {
        try {
            ksCard = new JNative(KS_CARD_DLL, SET_FIELD_READ_MODE);

            int i = 0;
            ksCard.setParameter(i++, Type.INT, String.valueOf(fieldID));

            logger.debug("invoke method " + SET_FIELD_READ_MODE);
            ksCard.invoke();
        } catch (NativeException e) {
            logger.error(e.getMessage());
        } catch (IllegalAccessException e) {
            logger.error(e.getMessage());
        }
    }

    /**
     * 签  名：int __stdcall ks_readcard();
     * 功  能: 从卡中读取信息
     * 参  数: 无
     * 返回值: 返回0表示成功, 非0表示失败(不对应错误码)
     *
     * @return .
     */
    public static boolean ksReadCard() {
        boolean success = false;
        try {
            ksCard = new JNative(KS_CARD_DLL, READ_CARD);
            ksCard.setRetVal(Type.INT);

            logger.debug("invoke method " + READ_CARD);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
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
     * 签  名：int __stdcall ks_getfieldval(int fieldID,char *fieldval);
     * 功  能:读取卡中指定字段的值
     * 参  数: fieldID 字段索引
     * Fieldval：输出值，为对应字段的值
     * 返回值: 返回0为成功
     *
     * @param fieldID .
     * @param result  .
     * @return .
     */
    public static boolean ksGetFieldVal(int fieldID, String fieldName, Properties result) {
        boolean success = false;
        Pointer pFieldVal = null;
        try {
            ksCard = new JNative(KS_CARD_DLL, GET_FIELD_VAL);
            ksCard.setRetVal(Type.INT);
            pFieldVal = new Pointer(MemoryBlockFactory.createMemoryBlock(100));
            int i = 0;
            ksCard.setParameter(i++, Type.INT, String.valueOf(fieldID));
            ksCard.setParameter(i++, pFieldVal);

            logger.debug("invoke method " + GET_FIELD_VAL);
            ksCard.invoke();
            int returnValue = ksCard.getRetValAsInt();
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
            dispose(pFieldVal);
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
