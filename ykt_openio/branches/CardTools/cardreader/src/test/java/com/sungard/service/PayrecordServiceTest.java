package com.sungard.service;

import com.sungard.bean.Payrecord;
import com.sungard.common.Configuration;
import junit.framework.TestCase;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-22
 */
public class PayrecordServiceTest extends TestCase {
    @Override
    protected void setUp() throws Exception {
        super.setUp();
        Configuration.load();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    public void testSavePayrecord() {
        Payrecord payrecord = new Payrecord();
        payrecord.setCardno(110);
        payrecord.setStuempno("2013");
        payrecord.setCustname("Shirely");
        payrecord.setMedicineFee(1.0);
        payrecord.setDressingFee(2.0);
        payrecord.setInjectionFee(3.0);
        payrecord.setVaccineFee(4.0);
        payrecord.setOtherFee(5.0);
        payrecord.setTotalFee(6.0);
        payrecord.setOperator("youyiming");
        payrecord.setTransDate("20110923");
        payrecord.setTransTime("031911");
        payrecord.setRefno("20110311");
        payrecord.setMac("--");
        payrecord.setTransType("1");
        PayrecordService.savePayrecord(payrecord);
        PayrecordService.findPayrecordDetail(null, null, null, null);
    }
}
