package com.sungard.card;

import junit.framework.TestCase;

import java.util.Properties;

/**
 * .
 * User: Yiming.You
 * Date: 2011-7-24
 */
public class KsCardInterfaceUtilTest extends TestCase {

    private int port = 100;

    private int baud = 115200;

    private Properties result;

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        KsCardInterfaceUtil.loadLibrary();
        result = new Properties();
        assertTrue(KsCardInterfaceUtil.ksInit());
        assertTrue(KsCardInterfaceUtil.ksOpenPort(port, baud));
    }

    /**
     * 测试读卡器签到函数
     */
    public void testSignIn() {
        assertTrue(KsCardInterfaceUtil.ksSignIn(result));
    }

    /**
     * 测试寻卡函数
     */
    public void testRequestCard() {
        assertTrue(KsCardInterfaceUtil.ksSignIn(result));
        assertTrue(KsCardInterfaceUtil.ksRequestCard(result));
    }

    /**
     * 测试读取卡中字段函数，读取CARDNO
     */
    public void testReadCardField() {
        assertTrue(KsCardInterfaceUtil.ksSignIn(result));
        assertTrue(KsCardInterfaceUtil.ksRequestCard(result));
        KsCardInterfaceUtil.ksReset();
        assertTrue(KsCardInterfaceUtil.ksSetReadFieldName("CARDNO"));
        assertTrue(KsCardInterfaceUtil.ksReadCard());
        assertTrue(KsCardInterfaceUtil.ksGetFieldVal("CARDNO", result));
    }

    /**
     * 测试读取卡状态函数
     */
    public void testGetCardStatus() {
        assertTrue(KsCardInterfaceUtil.ksSignIn(result));
        assertTrue(KsCardInterfaceUtil.ksRequestCard(result));
        KsCardInterfaceUtil.ksReset();
        assertTrue(KsCardInterfaceUtil.ksSetReadFieldName("CARDNO"));
        assertTrue(KsCardInterfaceUtil.ksReadCard());
        assertTrue(KsCardInterfaceUtil.ksGetFieldVal("CARDNO", result));
        int cardno = Integer.parseInt(result.getProperty("CARDNO"));
        assertTrue(KsCardInterfaceUtil.ksGetCardStatus(cardno, result));
    }

    /**
     * 测试消费函数
     */
    public void testPay() {
        assertTrue(KsCardInterfaceUtil.ksSignIn(result));
        assertTrue(KsCardInterfaceUtil.ksRequestCard(result));
        String cardPhyId = result.getProperty("cardPhyId");

        KsCardInterfaceUtil.ksReset();
        assertTrue(KsCardInterfaceUtil.ksSetReadFieldName("CARDNO"));
        assertTrue(KsCardInterfaceUtil.ksReadCard());
        assertTrue(KsCardInterfaceUtil.ksGetFieldVal("CARDNO", result));
        int cardno = Integer.parseInt(result.getProperty("CARDNO"));

        assertTrue(KsCardInterfaceUtil.ksSetReadFieldName("CARDBAL"));
        assertTrue(KsCardInterfaceUtil.ksReadCard());
        assertTrue(KsCardInterfaceUtil.ksGetFieldVal("CARDBAL", result));
        int cardBal = Integer.parseInt(result.getProperty("CARDBAL"));

        assertTrue(KsCardInterfaceUtil.ksSetReadFieldName("PAYCNT"));
        assertTrue(KsCardInterfaceUtil.ksReadCard());
        assertTrue(KsCardInterfaceUtil.ksGetFieldVal("PAYCNT", result));
        int payCnt = Integer.parseInt(result.getProperty("PAYCNT"));

        assertTrue(KsCardInterfaceUtil.ksGetCardStatus(cardno, result));

        int transAmt = 100;
        assertTrue(KsCardInterfaceUtil.ksPayPrepare(cardPhyId, cardno, cardBal, payCnt, transAmt, result));
        assertTrue(KsCardInterfaceUtil.ksCardBalanceDec(result));
        assertTrue(KsCardInterfaceUtil.ksPayProcess(result));
    }

    @Override
    protected void tearDown() throws Exception {
        assertTrue(KsCardInterfaceUtil.ksClosePort());
        super.tearDown();
    }
}
