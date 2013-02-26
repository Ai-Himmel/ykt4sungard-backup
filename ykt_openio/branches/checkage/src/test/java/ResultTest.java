import junit.framework.TestCase;
import org.apache.log4j.Logger;
import org.king.bean.ReceiveBean;
import org.king.bean.ReceiveItem;
import org.king.util.EncryptUtil;
import org.king.util.NodeUtil;
import org.king.util.Transformer;
import org.xml.sax.SAXException;

import javax.xml.parsers.ParserConfigurationException;
import java.io.IOException;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class ResultTest extends TestCase {
    private static final Logger logger = Logger.getLogger(RequestTest.class);

    Transformer transformer;

    @Override
    protected void setUp() throws Exception {
        super.setUp();
        transformer = new Transformer();
    }

    @Override
    protected void tearDown() throws Exception {
        super.tearDown();
    }

    public void testInit() {
        String initContent = "<ecard><action>会话初始化</action><status>成功</status><msg>初始化成功!</msg><ecard_ip>222.195.40.37</ecard_ip><time>1303998715</time><code>0aca3de6ecade616a13529d1d03bab67</code></ecard>";
        String action = NodeUtil.getNodeValue("action", initContent)[0];
        String status = NodeUtil.getNodeValue("status", initContent)[0];
        String msg = NodeUtil.getNodeValue("msg", initContent)[0];
        String ecard_ip = NodeUtil.getNodeValue("ecard_ip", initContent)[0];
        String time = NodeUtil.getNodeValue("time", initContent)[0];
        String code = NodeUtil.getNodeValue("code", initContent)[0];

        assertEquals(action, "会话初始化");
        assertEquals(status, "成功");
        assertEquals(msg, "初始化成功!");
        assertEquals(ecard_ip, "222.195.40.37");
        assertEquals(time, "1303998715");
        assertEquals(code, "0aca3de6ecade616a13529d1d03bab67");
    }


    public void testSuccessfulData() throws IOException, SAXException, ParserConfigurationException {
        String content = "<ecard>\r\n <action>对帐请求</action>\r\n <status>成功 </status>\r\n <msg>  所有数据更新成功!</msg>\r\n ";
        content = content + "<data>\r\n <check>\r\n <ecard_id>12345679</ecard_id>\r\n <check_result> 对帐成功!无错误!\r\n</check_result>\r\n </check>\r\n ";
        content = content + "<check>\r\n <ecard_id>12345680</ecard_id>\r\n <check_result> 对帐补充值成功! </check_result>\r\n </check>\r\n ";
        content = content + "<check>\r\n <ecard_id>12345681</ecard_id>\r\n <check_result>对帐成功!无错误!  </check_result>\r\n </check>\r\n </data>\r\n";
        content = content + "<time>1279746471</time>\r\n<code>d7e6f440919fe5df240da3bd68369403</code>\r\n</ecard>\r\n";
        ReceiveBean receiveBean = transformer.parseCheckResult(content);
        assertEquals(receiveBean.getAction(), "对帐请求");
        assertEquals(receiveBean.getStatus(), "成功");
        assertEquals(receiveBean.getMsg(), "所有数据更新成功!");
        assertEquals(receiveBean.getTime(), "1279746471");
        assertEquals(receiveBean.getCode(), "d7e6f440919fe5df240da3bd68369403");

        List<ReceiveItem> items = receiveBean.getData();
        ReceiveItem item0 = items.get(0);
        assertEquals(item0.getEcardId(), "12345679");
        assertEquals(item0.getCheckResult(), "对帐成功!无错误!");

        ReceiveItem item1 = items.get(1);
        assertEquals(item1.getEcardId(), "12345680");
        assertEquals(item1.getCheckResult(), "对帐补充值成功!");

        ReceiveItem item2 = items.get(2);
        assertEquals(item2.getEcardId(), "12345681");
        assertEquals(item2.getCheckResult(), "对帐成功!无错误!");
        logger.info(content);
    }

    public void testUnsuccessfulData() throws IOException, SAXException, ParserConfigurationException {
        String content = "<ecard>\r\n<action>对帐请求</action>\r\n<status>失败</status>\r\n<msg>无详细对帐请求数据!</msg>\r\n<time>1279746471</time>\r\n<code>d7e6f440919fe5df240da3bd68369403</code>\r\n</ecard>";
        ReceiveBean receiveBean = transformer.parseCheckResult(content);
        assertEquals(receiveBean.getAction(), "对帐请求");
        assertEquals(receiveBean.getStatus(), "失败");
        assertEquals(receiveBean.getMsg(), "无详细对帐请求数据!");
        assertEquals(receiveBean.getTime(), "1279746471");
        assertEquals(receiveBean.getCode(), "d7e6f440919fe5df240da3bd68369403");
    }

    public void testApply() {
        //init
        String ip = "222.195.40.37";
        long initTime = System.currentTimeMillis() / 1000;
        String initCode = EncryptUtil.getJJLinkMD5String(ip, initTime);
        //curl -d "action=init&time=1303998715&code=0aca3de6ecade616a13529d1d03bab67" -D cookie.txt -k https://10.255.200.193/ecard/
        String initCmd = "curl -d \"action=init&time=" + initTime + "&code=" + initCode + "\" -D cookie.txt -k https://10.255.200.193/ecard/";
        System.out.println(initCmd);

        String applyCmd = "curl -b cookie.txt -d \"action=recharge_request&time=" + initTime + "&code=" + initCode + "&ecard_id=20110428001000&request_time=2011-04-29 19:50:11&ecard_num=22096&username=109999996&fullname=xuxin&amount=1.00&ecard_machine_id=1397" + "\" -k https://10.255.200.193/ecard/";
        System.out.println(applyCmd);

        String ackCmd = "curl -b cookie.txt -d \"action=recharge_ack&time=" + initTime + "&code=" + initCode + "&ecard_id=20110428001000&inpayamount_id=&ack_time=2011-04-29 19:52:11" + "\" -k https://10.255.200.193/ecard/";
        System.out.println(ackCmd);
    }

    public void testAA(){
        String s1 = "curl –d \"&action=init&time=1304240357&code=538706aea0d1cdbfb0e00eebb2b9e923\" –D cookie.txt –k https://10.255.200.193/ecard/";
        String s2 = "curl -b cookie.txt -d \"&action=check_request&time=1304240359&code=2a54a58eb20ea06082f50629246fb352&request_time=2011-05-01 16:59:19&data[][ecard_id]=20110428001000&data[][request_time]=2011-04-29 19:50:11&data[][ecard_num]=22096&data[][username]=109999996&data[][fullname]=xuxin&data[][amount]=1&data[][ecard_machine_id]=1397&data[][ecard_ip]=222.195.40.37&data[][inpayamount_id]=13040782961567&data[][reply_time]=2011-04-29 19:58:16&data[][ack_time]=2011-04-29 19:52:11\" -k https://10.255.200.193/ecard/";
        String s3 = "curl -b cookie.txt -d \"&action=destroy&time=1304240361&code=51511c60b718b6f93f308891dcaa63e5\" -k https://10.255.200.193/ecard/";

        System.out.println("s1 = " + s1);
        System.out.println("s2 = " + s2);
        System.out.println("s3 = " + s3);
    }
}
