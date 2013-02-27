/**
 * 
 */
package org.king.support.util;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.mail.EmailException;
import org.apache.commons.mail.HtmlEmail;
import org.apache.log4j.Logger;
import org.king.utils.StringUtil;

/**<br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: CommonSendMailUtil.java<br>
 * Description: <br>
 * Modify History����Change Log��:  <br>
 * �������ͣ��������޸ĵȣ�   ��������     ������    �������ݼ���<br>
 * ����  				 2005-11-7  ������    <br>
 * <p>
 *
 * @author      ������
 * @version     1.0
 * @since       1.0
 */
public class CommonSendMailUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CommonSendMailUtil.class);

	private static String hostName = "";
	private static String hosteMail = "";
	private static String signature = "";
	private static String userName = ""; //smtp��֤�û���������
	private static String password = "";
	private static HtmlEmail htmlEmail = null;
	
	private CommonSendMailUtil() {
		super();		
	}
	
	public static boolean sendMail(String subject,String mailto,String email,String msg){

		try {
			if(!"".equals(subject)&&!"".equals(mailto)&&!"".equals(email)&&!"".equals(msg)){
				PropertiesConfiguration config = GetPropertiesUtil.getInstance();
				subject = StringUtil.encodeString(subject,"GBK");
				msg = StringUtil.encodeString(msg,"GBK");
				mailto = StringUtil.encodeString(mailto, "GBK");
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
				if (logger.isInfoEnabled()) {
					logger.info("�ʼ�����...");
				}
				htmlEmail.send();
				if (logger.isInfoEnabled()) {
					logger.info("�ʼ����ͳɹ�...");
				}
				return true;
			}
			
		} catch (EmailException e) {
			logger.error("�ʼ�����ʧ�ܣ�", e);
			e.printStackTrace();
		}catch (Exception e) {
			logger.error("�ʼ�����ʧ�ܣ�", e);

		}	
		if (logger.isDebugEnabled()) {
			logger.debug("sendMail(String, String, String, String) - end");
		}
		return false;
	}

}
