package org.king.check.util;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.mail.EmailAttachment;
import org.apache.commons.mail.EmailException;
import org.apache.commons.mail.HtmlEmail;
import org.apache.commons.mail.MultiPartEmail;


public class MailSender{
	private static String hostName = "";
	private static String hosteMail = "";
	private static String signature = "";
	private static String userName = ""; //smtp认证用户名和密码
	private static String password = "";
	private static MultiPartEmail htmlEmail = null;
	
	private MailSender() {
		super();		
	}
	
	public static void sendMail(String mailto,String msg,String fileAddr,String fileName){

		try {
			if(!"".equals(mailto)&&!"".equals(msg)){
				PropertiesConfiguration config = GetPropertiesUtil.getInstance();
				msg = StringUtil.encodeString(msg,"GBK");
				fileName = StringUtil.encodeString(fileName,"GBK");
				hostName=config.getString("Host.Adress");
				hosteMail=config.getString("Host.email");
				signature=config.getString("Host.signature");
				userName=config.getString("Host.userName");
				password=config.getString("Host.password");	
				//byte[] mypass = SimpleEncoding.hex2byte(password);
				//password =new String(SimpleEncoding.decode(mypass,"kingstar".getBytes()));
				htmlEmail= new HtmlEmail();
				htmlEmail.setAuthentication(userName,password);
				htmlEmail.setHostName(hostName);
				//循环添加发送邮件列表
				String[] mails = StringUtil.split(mailto,";");
				for (int i=0;i<mails.length;i++){
					htmlEmail.addTo(mails[i],mails[i]);
				}
				htmlEmail.setFrom(hosteMail, signature);
				htmlEmail.setSubject(fileName);
				htmlEmail.setMsg(msg);
				
				//添加附件
				EmailAttachment attachment = new EmailAttachment();
				attachment.setPath(fileAddr);
				attachment.setDisposition(EmailAttachment.ATTACHMENT);
				attachment.setDescription("checkReport.xls");
				attachment.setName("checkReport.xls");
				htmlEmail.attach(attachment);
				
				htmlEmail.setCharset("GBK");

				System.out.println("mail is sending....");
				htmlEmail.send();
				System.out.println("mail sends successfully--------"+mailto);
			}
			
		} catch (EmailException e) {

			System.out.println("mail sending fails！"+e);
		}catch (Exception e) {
			System.out.println(e+"-------------------");
			e.printStackTrace();
		}	
	}
	public static void mailsSender(String mail,String fileAddr,String fileName){
			sendMail(mail,fileName,fileAddr,fileName);

	}
}
