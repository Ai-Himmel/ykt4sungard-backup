package com.kingstargroup.conference.mail;

import java.util.Iterator;
import java.util.List;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.mail.EmailException;
import org.apache.commons.mail.HtmlEmail;

import com.kingstargroup.conference.common.GetPropertiesUtil;
import com.kingstargroup.conference.common.SimpleEncoding;
import com.kingstargroup.conference.common.StringUtil;
import com.kingstargroup.conference.hibernate.form.TConference;
import com.kingstargroup.conference.hibernate.form.TCustomer;
import com.kingstargroup.conference.util.AttendeeUtil;
import com.kingstargroup.conference.util.ConferenceUtil;

public class MailSender{
	private static String hostName = "";
	private static String hosteMail = "";
	private static String signature = "";
	private static String userName = ""; //smtp认证用户名和密码
	private static String password = "";
	private static HtmlEmail htmlEmail = null;
	
	private MailSender() {
		super();		
	}
	
	public static void sendMail(String subject,String mailto,String email,String msg){

		try {
			if(!"".equals(subject)&&!"".equals(mailto)&&!"".equals(email)&&!"".equals(msg)){
				PropertiesConfiguration config = GetPropertiesUtil.getInstance();
				subject = StringUtil.encodeString(subject,"GBK");
				msg = StringUtil.encodeString(msg,"GBK");
				hostName=config.getString("Host.Adress");
				hosteMail=config.getString("Host.email");
				signature=config.getString("Host.signature");
				userName=config.getString("Host.userName");
				password=config.getString("Host.password");	
				byte[] mypass = SimpleEncoding.hex2byte(password);
				password =new String(SimpleEncoding.decode(mypass,"kingstar".getBytes()));
				htmlEmail= new HtmlEmail();
				htmlEmail.setAuthentication(userName,password);
				htmlEmail.setHostName(hostName);
				htmlEmail.addTo(email, mailto);
				htmlEmail.setFrom(hosteMail, signature);
				htmlEmail.setSubject(subject);
				htmlEmail.setCharset("GBK");
				htmlEmail.setHtmlMsg(msg);
				System.out.println("mail is sending....");
				htmlEmail.send();
				System.out.println("mail sends successfully！");
			}
			
		} catch (EmailException e) {

			System.out.println("mail sending fails！"+e);
		}catch (Exception e) {

			e.printStackTrace();
		}	
	}

	public static void mailsSender(int confid){
		String mail = "";
		String name = "";
		String confName = "";
		String confContent = "";
		TConference conf = ConferenceUtil.getConfById(new Long(confid));
		confName = conf.getConName();
		confContent = conf.getContent();
		List custList = AttendeeUtil.getCustListByConfId(confid);
		Iterator iter = custList.iterator();
		while (iter.hasNext()){
			TCustomer cust = (TCustomer)iter.next();
			if (null==cust.getEmail()){
				mail = "";
				name = "";
			}else{
				mail = cust.getEmail().toString();
				name = cust.getCustname().toString();
			}
			sendMail(confName+"会议通知",name,mail,confContent);
		}

	}
}
