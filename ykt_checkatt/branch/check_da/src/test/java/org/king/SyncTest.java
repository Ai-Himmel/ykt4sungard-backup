package org.king;

import junit.framework.TestCase;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.MailSender;
import org.king.check.util.SyncUtil;

import java.text.ParseException;
import java.util.Date;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-3
 */
public class SyncTest extends TestCase {
    public void testMailSender() {
        MailSender.sendMail("«ÎºŸ…Í«Î", "Yiming.You@sungard.com", "--", "just for test");
    }

    public void testSyncData() {
        SyncUtil.syncData();
    }

    public void testWeek() throws ParseException {
        Date nextMonday = DateUtilExtend.getNextMonday();
        System.out.println("nextMonday = " + nextMonday);

        long useWeek = DateUtilExtend.getUseWeek("20110221", nextMonday);
        System.out.println("useWeek = " + useWeek);
    }
}
