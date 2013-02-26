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
 * ��д��
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
     * ����KsCardInterFace��̬��
     */
    public static void loadLibrary() {
    	  String userDir = System.getProperty("user.dir");
          String dll = userDir + File.separator + CARD_INTERFACE_DLL;
          File dllFile = new File(dll);
          if (!dllFile.exists()) {
        	  logger.error("�޷����ض�̬�⣺" + dll);
//              throw new RuntimeException("�޷����ض�̬�⣺" + dll);
          }else {
        	  System.load(dll);
              JNative.setLoggingEnabled(false);
              logger.info("���ض�̬��ɹ���" + dll);
		}
         
    }

    /**
     * ǩ  ����int __stdcall KS_Init()
     * ��  �ܣ������⻷����ʼ��
     * ��  ������
     * ����ֵ���ɹ��򷵻�0��ʧ�ܷ�0
     *
     * @return .
     */
    public static boolean ksInit() {
        boolean success = false;
        try {
            cardInterface = new JNative(CARD_INTERFACE_DLL, INIT);
            //ָ�����ز���������
            cardInterface.setRetVal(Type.INT);
            logger.debug("invoke method " + INIT);
            //���÷���
            cardInterface.invoke();
            //��ȡ����ֵ
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
     * ǩ  ����int __stdcall KS_OpenPort(int port, int baud)
     * ��  �ܣ���ʼ��ͨѶ��
     * ��  ����port��ȡֵΪ0��19ʱ����ʾ����1��20��Ϊ100ʱ����ʾUSB��ͨѶ����ʱ��������Ч��
     * baud��ΪͨѶ������9600��115200
     * ����ֵ: ����0Ϊ�ɹ�������Ϊ����
     *
     * @param port ȡֵΪ0��19ʱ����ʾ����1��20��Ϊ100ʱ����ʾUSB��ͨѶ����ʱ��������Ч��
     * @param baud ΪͨѶ������9600��115200
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
     * ǩ  ����int __stdcall KS_SignIn(int* nShopID,char* sShopName)
     * ��  ��: ������ǩ��
     * ��  ��: nShopID��������������ض�����������̻���
     * sShopName��������������ض�����������̻��Ŷ�Ӧ���̻���������61�ֽ�
     * ����ֵ: ����0��ʾ�ɹ�, ������ʾʧ��
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
     * ǩ  ����int __stdcall KS_ClosePort()
     * ��  ��: �ر��Ѵ򿪵Ķ˿�
     * ��  ��: ��
     * ����ֵ: ����0Ϊ�ɹ�������Ϊ����
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
     * ǩ  ����void __stdcall KS_Beep()
     * ��  ��: ����������
     * ��  ��: ��
     * ����ֵ: ����0Ϊ�ɹ�������Ϊ����
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
     * ǩ  ����void __stdcall KS_BeepErr()
     * ��  ��: ����������
     * ��  ��: ��
     * ����ֵ: ����0Ϊ�ɹ�������Ϊ����
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
     * ǩ  ����int __stdcall KS_RequestCard(char *sCardPhyID)
     * ��  �ܣ�Ѱ��
     * ��  ��: char *sCardPhyID ������������ؿ����������к�,����17�ֽڡ�
     * ����ֵ: ����0Ϊ�ɹ�������Ϊ����
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
     * ǩ  ����void __stdcall KS_Reset();
     * ��  �ܣ����ö�д�ֶα�־��ͬʱ��ջ������ݡ�
     * ��  ��: ��
     * ����ֵ: ��
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
     * ǩ  ����int __stdcall KS_SetReadFieldName(char *fieldname)
     * ��  ��: ����Ҫ��ȡ���ֶ�(FieldName)
     * ��  ��: char *fieldname�ֶ�������д��Ӣ����ĸ��FileName��Χ���ĵ�
     * ����ֵ: ����0Ϊ�ɹ�������Ϊ����
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
     * ǩ  ����int __stdcall KS_ReadCard ()
     * ��  ��: �ӿ��ж�ȡ��Ϣ
     * ��  ��: ��
     * ����ֵ: ����0��ʾ�ɹ�, ��0��ʾʧ��(����Ӧ������)
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
     * ǩ  ����int __stdcall KS_GetFieldVal(char *fieldname,char *fieldval)
     * ��  ��:��ȡ����ָ���ֶ�����ֵ
     * ��  ��: fieldname�ֶ���,��CARDNO��CUSTID��
     * Fieldval�����ֵ��Ϊ��Ӧ�ֶε�ֵ
     * ����ֵ: ����0Ϊ�ɹ�
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
     * ��ȡ����ĳһ�ֶ�ֵ
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
     * ǩ  ����char* __stdcall KS_GetErrMsg(char *msg);
     * ��  ��:�����ú���ʧ��ʱ���������ú�����ȡ������Ϣ��
     * ��  ��:char* msg :�������������ΪNULL
     * ����ֵ��char* ���ش�����Ϣ
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
     * ǩ  ����int __stdcall KS_GetCardStatus(int cardno,char *statuscode,char *statusinfo);
     * ��  ��:���ݽ��׿������������������ݿ��鿨״̬��
     * ��  ��:int cardno ���׿��ţ��������
     * Char* Statuscode ������� ״̬�� ��1�ֽ�
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
     * �ۿ�Ԥ������
     * ǩ  ����int __stdcall KS_PayPrepare(const char *sCardPhyID,int nCardNo,int nCardBal,int nPayCnt,int nTransAmt,char *sRefNo,char *sMac)
     * ��  ��: ������鿨�Ƿ�Ϸ��������н��׳�ʼ������
     * ��  ��:
     * ����ֵ��
     * sCardPhyID:��Ƭ���к�,8�ֽ�ʮ�������ַ���
     * nCardNo��  ���׿���
     * nCardBal�� ��������ǰ������λΪ��
     * nPayCnt ��  ���Ѵ���
     * nTransAmt�� ���ѽ���λΪ��
     * ���ֵ��
     * sRefNo��	 ���ײο��� ����14λ��������������ظý��׵Ľ��ײο��š�
     * sMac ��	 �ý��ײο��ŵ�MACֵ
     * ����ֵ: ����0��ʾ�ɹ�, ������ʾʧ��
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
     * �ۿ�����
     * ǩ  ����int __stdcall KS_CardBalanceDec(char* cGetProveFlag);
     * ��  �ܣ��ۿ�Ǯ�����
     * ��  ����char* cGetProveFlag  Ϊ0x00��ʾ�ۿ�ʧ�ܣ�Ϊ0x01��ʾд��δ��ɣ���;�ο���
     * ����ֵ��0��ʾ�������óɹ���������ʾ��������ʧ�ܣ�����ʹ��KS_GetErrMsg���õ�������Ϣ��
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
     * ���Ѵ�����
     * ǩ  ����int __stdcall  KS_PayProcess()
     * ��  ��: �ۿ�ɹ����ύ����̨������ˮ���˴���
     * ��  ��: ��
     * ����ֵ: ����0��ʾ�ɹ�, ������ʾʧ��
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
     * ȡ������֤����
     * ǩ  ����int __stdcall KS_GetProve(char* cReWriteCardFlag);
     * ��  �ܣ����ۿ��������ó�����;�ο�ʱ����Ҫ���ñ��������ж��Ƿ���Ҫ����д����
     * ��  ����char* cReWriteCardFlag   ������� ��0x00��ʾд���ѳɹ�������Ҫ����д�� 0x01��ʾд��ʧ�ܣ���Ҫ����д��
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
     * ȡ������֤ʧ�ܴ�����
     * ǩ  ����int __stdcall KS_UnProveProcess();
     * ��  �ܣ���������;�ο������ֿ���û������ˢ�����쳣����£����ñ�������ֹ���ס�
     * ��  �����ޡ�
     * ����ֵ: ����0��ʾ�ɹ�, ������ʾʧ��
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
     * �۷ѳ�������
     * ǩ  ����int __stdcall KS_PayCancelProcess(const char *sRefNo,const char *sMac,const char *sCardPhyID,int nCardNo,int nCardBal,int nDpsCnt);
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
     * �ͷ���Դ
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
