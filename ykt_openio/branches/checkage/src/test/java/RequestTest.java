import junit.framework.TestCase;
import org.apache.log4j.Logger;
import org.king.common.Configuration;
import org.king.common.Constant;
import org.king.http.HttpRequester;
import org.king.http.HttpResponser;
import org.king.http.HttpsRequester;
import org.quartz.Scheduler;
import org.quartz.SchedulerException;
import org.quartz.impl.StdSchedulerFactory;

import java.io.IOException;


/**
 * .
 * User: Yiming.You
 * Date: 2011-4-26
 */
public class RequestTest extends TestCase {
    private static final Logger logger = Logger.getLogger(RequestTest.class);

    @Override
    protected void setUp() throws Exception {
        super.setUp();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    public void testGet() throws IOException {
        HttpRequester request = new HttpRequester("http://www.google.com.hk");
        request.setMethod(HttpRequester.GET);
        request.addParameter("q", "youyiming");
        assertEquals(request.getFullUrl(), "http://www.google.com.hk?q=youyiming");
        HttpResponser response = request.send();
        logger.info(response.getContent());
    }

    public void testPost() throws IOException {
        HttpRequester request = new HttpRequester("http://www.dict.cn");
        request.setMethod(HttpRequester.POST);
        request.addParameter("q", "card");
        assertEquals(request.getFullUrl(), "http://www.dict.cn");
        HttpResponser response = request.send();
        logger.info(response.getContent());
    }

    public void testProperties() {
        Configuration.load();
        String driverClass = Configuration.getProperty(Constant.DRIVER_CLASS);
        String jdbcUrl = Configuration.getProperty(Constant.JDBC_URL);
        String user = Configuration.getProperty(Constant.USERNAME);
        String password = Configuration.getProperty(Constant.PASSWORD);
        String checkUrl = Configuration.getProperty(Constant.CHECK_URL);
        String checkSql = Configuration.getProperty(Constant.CHECK_SQL);
        assertEquals(driverClass, "oracle.jdbc.driver.OracleDriver");
        assertEquals(jdbcUrl, "jdbc:oracle:thin:@10.49.118.250:1521:yktv3db");
        assertEquals(user, "ykt_cur");
        assertEquals(password, "kingstar");
        assertEquals(checkUrl, "http://localhost/getPost.php");
        assertEquals(checkSql, "select t.TERMSEQNO as ecardid,t.TRANSDATE,t.TRANSTIME,t.STUEMPNO from v_transdtl t where t.STATUS=3 and rownum<=10");
    }

    public void testJob() throws SchedulerException, InterruptedException {
        Scheduler scheduler = StdSchedulerFactory.getDefaultScheduler();
        scheduler.start();
        Thread.sleep(100000);
        scheduler.shutdown();
    }

    public void testPhpPost() throws IOException {
        String[][] data = new String[1][11];
        for (int i = 0; i < data.length; i++) {
            data[i] = new String[11];
            data[i][0] = "20110428001000";
            data[i][1] = "2011-04-29 19:50:11";
            data[i][2] = "22096";
            data[i][3] = "109999996";
            data[i][4] = "xuxin";
            data[i][5] = "1";
            data[i][6] = "1397";
            data[i][7] = "222.195.40.37";
            data[i][8] = "13040782961567";
            data[i][9] = "2011-04-29 19:58:16";
            data[i][10] = "2011-04-29 19:52:11";
        }

        HttpRequester request = new HttpRequester("http://localhost/getPost.php");
        request.setMethod(HttpRequester.POST);
        assertEquals(request.getFullUrl(), "http://localhost/getPost.php");

        for (int i = 0; i < data.length; i++) {
            request.addParameter("data[0][ecard_id]", data[i][0]);
            request.addParameter("data[0][request_time]", data[i][1]);
            request.addParameter("data[0][ecard_num]", data[i][2]);
            request.addParameter("data[0][username]", data[i][3]);
            request.addParameter("data[0][fullname]", data[i][4]);
            request.addParameter("data[0][amount]", data[i][5]);
            request.addParameter("data[0][ecard_machine_id]", data[i][6]);
            request.addParameter("data[0][ecard_ip]", data[i][7]);
            request.addParameter("data[0][inpayamount_id]", data[i][8]);
            request.addParameter("data[0][reply_time]", data[i][9]);
            request.addParameter("data[0][ack_time]", data[i][10]);

            request.addParameter("data[1][ecard_id]", data[i][0]);
            request.addParameter("data[1][request_time]", data[i][1]);
            request.addParameter("data[1][ecard_num]", data[i][2]);
            request.addParameter("data[1][username]", data[i][3]);
            request.addParameter("data[1][fullname]", data[i][4]);
            request.addParameter("data[1][amount]", data[i][5]);
            request.addParameter("data[1][ecard_machine_id]", data[i][6]);
            request.addParameter("data[1][ecard_ip]", data[i][7]);
            request.addParameter("data[1][inpayamount_id]", data[i][8]);
            request.addParameter("data[1][reply_time]", data[i][9]);
            request.addParameter("data[1][ack_time]", data[i][10]);
        }

        HttpResponser response = request.send();
        String content = response.getContent();
        assertNotNull(content);
        content = content.replaceAll("<br>", "\r\n");
        logger.info(content);
    }

    public void testHttps() throws Exception {
        HttpsRequester request = new HttpsRequester("https://10.49.255.74/info.html");
        request.addParameter("q", "card");
        HttpResponser response = request.send();
        logger.info(response.getContent());
    }
}
