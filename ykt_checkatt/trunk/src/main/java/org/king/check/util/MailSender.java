package org.king.check.util;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.mail.EmailException;
import org.apache.commons.mail.HtmlEmail;


public class MailSender{
	private static String hostName = "";
	private static String hosteMail = "";
	private static String signature = "";
	private static String userName = ""; //smtp��֤�û���������
	private static String password = "";
	private static HtmlEmail htmlEmail = null;
	
	private MailSender() {
		super();		
	}
	
	public static void sendMail(String subject,String mailto,String hostaddress,String hostemail,String hostuserName,String hostpassword,String hostsignature,String email,String msg){

		try {
			if(!"".equals(subject)&&!"".equals(mailto)&&!"".equals(email)&&!"".equals(msg)){
				PropertiesConfiguration config = GetPropertiesUtil.getInstance();
				subject = StringUtil.encodeString(subject,"GBK");
				msg = StringUtil.encodeString(msg,"GBK");
				if(hostaddress!=null){
					hostName=hostaddress;
				}else{
					hostName=config.getString("Host.Adress");
				}
				if(hostemail!=null){
					hosteMail = hostemail;
				}else{
					hosteMail=config.getString("Host.email");
				}
				if(hostsignature !=null){
					signature = hostsignature;
				}else{
					signature=config.getString("Host.signature");
				}
				if(hostuserName != null){
					userName=hostuserName;
				}else{
					userName=config.getString("Host.userName");
				}
				if(hostpassword != null){
					password=hostpassword;	
				}else{
				   password=config.getString("Host.password");	
				}
				byte[] mypass = SimpleEncoding.hex2byte(password);
				password =new String(SimpleEncoding.decode(mypass,"kingstar".getBytes()));
				htmlEmail= new HtmlEmail();
				htmlEmail.setAuthentication(userName,password);
				htmlEmail.setHostName(hostName);
				//htmlEmail.addTo(email, mailto);
				htmlEmail.addTo(mailto,mailto);
				htmlEmail.setFrom(hosteMail, signature);
				htmlEmail.setSubject(subject);
				htmlEmail.setCharset("GBK");
				htmlEmail.setHtmlMsg(msg);

				System.out.println("mail is sending....");
				htmlEmail.send();
				System.out.println("mail sends successfully--------"+mailto);
			}
			
		} catch (EmailException e) {

			System.out.println("mail sending fails��"+e);
		}catch (Exception e) {
			System.out.println(e+"-------------------");
			e.printStackTrace();
		}	
	}
	public static void mailsSender(String mail,String hostaddress,String hostemail,String hostuserName,String hostpassword,String hostsignature,String leaveInfo){
		sendMail("�������",mail,hostaddress,hostemail,hostuserName,hostpassword,hostsignature,"--",leaveInfo);

}
}
