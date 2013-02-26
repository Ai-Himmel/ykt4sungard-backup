package com.sungard.bcc;

import com.kingstar.bcc.BccUtil;
import com.kingstar.bcc.BccctlInit;
import com.kingstar.bcc.bccclt;
import com.sungard.common.Configuration;
import com.sungard.common.Constant;
import org.apache.log4j.Logger;

import java.util.Arrays;

/**
 * Created by IntelliJ IDEA.
 * User: Haiyu.Peng
 * Date: 11-8-7
 * Time: 上午9:34
 */
public class F846308 {
    private static final Logger _logger = Logger.getLogger(F846308.class);

    public static boolean unfrozeCard(String cardno, String operCode) {
        boolean success = false;

        long xpackhandle = 0;
        int drtpno = 0;
        int errcode[] = {1};
        byte errmsg[] = new byte[300];
        int branchno = 0;
        //后台drtp功能号
        int mainfunction = Configuration.getIntProperty(Constant.MAINfUNCTION1, 9000);
        // 后台业务功能号
        int func = Configuration.getIntProperty(Constant.UNFROZE_CARD, 846308);
        int[] RetCode = new int[1];
        int[] RecordCount = new int[1];
        bccclt bcc = null;
        try {
            bcc = BccctlInit.getBccctlInstance();
            xpackhandle = bcc.NewXpackHandle(Configuration.getProperty(Constant.CPACKFILE, "/opt/cpack.dat").getBytes());
            if (0 != xpackhandle) {
                bcc.SetRequestType(xpackhandle, func);
                //交易卡号
                bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(), Integer.parseInt(cardno));
                //操作员
                bcc.SetStringFieldByName(xpackhandle, 0, "semp".getBytes(), String.valueOf(operCode).getBytes());

                boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno, mainfunction, 10000, errcode, errmsg);
                if (bccret) {
                    bcc.GetRetCode(xpackhandle, RetCode);
                    bcc.GetRecordCount(xpackhandle, RecordCount);
                    _logger.debug("RetCode=" + RetCode[0]);
                    _logger.debug("RecordCount=" + RecordCount[0]);
                    if (0 == RetCode[0]) {
                        if (0 < RecordCount[0]) {
                            byte[] inStr = new byte[300];
                            Arrays.fill(inStr, (byte) 0);
                            bcc.GetStringFieldByName(xpackhandle, 0, "sserial0".getBytes(), inStr, 300);
                            String sserial0 = BccUtil.getStringFromByte(inStr);
                            _logger.debug("sserial0=" + sserial0);
                            success = true;
                        } else {
                            _logger.error("后台处理失败【RecordCount=" + RecordCount[0] + "】");
                        }
                    } else {
                        //失败
                        if (0 < RecordCount[0]) {
                            byte[] vsmess = new byte[300];
                            Arrays.fill(vsmess, (byte) 0);
                            bcc.GetStringFieldByName(xpackhandle, 0, "vsmess".getBytes(), vsmess, 300);
                            String vs_mess = BccUtil.getStringFromByte(vsmess);
                            _logger.error("后台处理失败【vs_mess=" + vs_mess + "】");
                        } else {
                            _logger.error("后台处理失败【RecordCount=" + RecordCount[0] + "】");
                        }
                    }
                } else {
                    // 请求失败
                    int i;
                    for (i = 0; i < errmsg.length; i++) {
                        if (errmsg[i] == 0) {
                            break;
                        }
                    }
                    String s = new String(errmsg, 0, i);
                    _logger.error("CallRequest失败【errcode=" + errcode[0] + ",msg=" + s + "】");
                }
            } else {
                _logger.error("NewXpackHandle失败，xpackhandle=" + xpackhandle);
            }
        } catch (Exception e) {
            _logger.error(e);
        } finally {
            if (xpackhandle != 0) {
                bcc.DeleteXpackHandle(xpackhandle);
            }
        }
        return success;
    }
}
