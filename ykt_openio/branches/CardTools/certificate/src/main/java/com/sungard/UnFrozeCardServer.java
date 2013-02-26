package com.sungard;

import com.sungard.bcc.F846308;
import com.sungard.card.KsCardUtil;
import com.sungard.common.Configuration;
import com.sungard.common.Constant;
import com.sungard.util.DateUtil;
import com.sungard.util.FileUtil;
import com.sungard.util.StringUtil;
import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import java.util.Properties;

/**
 * 该程序用于解冻卡，将卡状态和系统卡状态恢复为正常
 * User: Yiming.You
 * Date: 2011-8-1
 */
public class UnFrozeCardServer {
    private static final Logger logger = Logger.getLogger(UnFrozeCardServer.class);

    public static void main(String[] args) {
        logger.debug(StringUtil.getDebugString("java.library.path", System.getProperty("java.library.path")));
        Configuration.load();
        String operCode = Configuration.getProperty(Constant.OPER_CODE);
        if (StringUtils.isBlank(operCode)) {
            logger.error("操作员未配置，请检查" + Constant.PROPERTY_FILE_NAME + "文件中的operCode属性");
            System.exit(1);
        }

        int statusIndex = Configuration.getIntProperty(Constant.CF_CARDSTATUS, 7);
        String frozeStatus = Configuration.getProperty(Constant.FROZE_STATUS, "3");
        int timeout = Configuration.getIntProperty(Constant.UNFROZE_TIMEOUT, 0);
        int port = Configuration.getIntProperty(Constant.PORT, 100);
        int baud = Configuration.getIntProperty(Constant.BAUD, 115200);
        Properties result = new Properties();

        KsCardUtil.loadLibrary();
        KsCardUtil.ksInit();
        KsCardUtil.ksOpenPort(port, baud);
        logger.debug("start unfroze card server successfully");

        String cardPhyId = null;
        String currentCardPhyId;
        String cardno;
        long currentTime = System.currentTimeMillis();
        String cardStatus;
        boolean success = false;
        String info = "";
        while (true) {
            if (KsCardUtil.ksCard(result, false)) {
                //判断是否超过间隔时间
                if (currentTime + timeout <= System.currentTimeMillis()) {
                    cardPhyId = null;
                }

                currentCardPhyId = result.getProperty("cardPhyId");
                if (StringUtils.isBlank(currentCardPhyId)) {
                    //error
                    logger.error("读取cardphyid失败");
                    KsCardUtil.ksBeepErr();
                } else if (currentCardPhyId.equals(cardPhyId)) {
                    //found the same card,do nothing
                } else {
                    logger.info("********" + "发现卡[cardphyid=" + currentCardPhyId + "]" + "********");
                    //UnFroze Card
                    KsCardUtil.ksReset();
                    KsCardUtil.ksSetFieldReadMode(2);
                    KsCardUtil.ksSetFieldReadMode(7);
                    KsCardUtil.ksReadCard();
                    if (KsCardUtil.ksGetFieldVal(2, "CARDNO", result) && KsCardUtil.ksGetFieldVal(7, "CARDSTATUS", result)) {
                        cardno = result.getProperty("CARDNO");
                        if (!F846308.unfrozeCard(cardno, operCode)) {
                            logger.error("解冻卡失败[cardno=" + cardno + "]");
                            KsCardUtil.ksBeepErr();
                        } else {
                            success = true;
                            logger.info("解冻卡成功[cardno=" + cardno + "]");
                            KsCardUtil.ksBeep();
                        }
                        //修改卡状态
                        cardStatus = result.getProperty("CARDSTATUS");
                        logger.info("卡状态:" + cardStatus);
                        if ("0".equals(cardStatus)) {
                            //do nothing
                        } else if (frozeStatus.equals(cardStatus)) {
                            if (KsCardUtil.ksModifystatus(currentCardPhyId, statusIndex, "0")) {
                                cardStatus = "0";
                                logger.info("修改卡状态成功[cardstatus=0]");
                                KsCardUtil.ksBeep();
                                success = success && true;
                            } else {
                                success = false;
                                logger.error("修改卡状态失败[cardstatus=" + cardStatus + "]");
                                KsCardUtil.ksBeepErr();
                            }
                        }
                        info = "\"" + DateUtil.getCurDateStrALL() + "\"," + "\"cardno:" + cardno + "\"," + "\"cardphyid:" + currentCardPhyId + "\"," + "\"card status:" + cardStatus + "\"";
                        if (success) {
                            FileUtil.logToFile(info, DateUtil.getCurDateStrYYYYMMDD() + "-success.log");
                        } else {
                            FileUtil.logToFile(info, DateUtil.getCurDateStrYYYYMMDD() + "-failure.log");
                        }
                    } else {
                        logger.error("读取cardno或者cardstatus失败");
                        KsCardUtil.ksBeepErr();
                    }
                    logger.info("*****************************************");
                }
                //只要寻卡成功就记住物理卡号
                cardPhyId = currentCardPhyId;
                currentTime = System.currentTimeMillis();
            }
        }
    }
}
