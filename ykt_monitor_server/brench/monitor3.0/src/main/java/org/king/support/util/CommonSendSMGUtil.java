package org.king.support.util;

import java.io.IOException;
import java.io.PrintWriter;
import java.net.Socket;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.log4j.Logger;
import org.king.utils.StringUtil;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: CommonSendSMGUtil.java<br>
 * Description: <br>
 * Modify History����Change Log��: <br>
 * �������ͣ��������޸ĵȣ� �������� ������ �������ݼ���<br>
 * ���� 2005-11-7 ������ <br>
 * <p>
 * 
 * @author ������
 * @version 1.0
 * @since 1.0
 */
public class CommonSendSMGUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CommonSendSMGUtil.class);

	private static String IP = "";

	private static String PORT = "";

	private static String PASSWORD = "";

	private static Socket socket;

	private static PrintWriter out;

	/**
	 * 
	 */
	public CommonSendSMGUtil() {
		super();
		// TODO Auto-generated constructor stub
	}
/*
 * send SMG method 
 * @param  phoneNum   format 139*******;131********  use delimeter ";" to split them
 * @param  content    smg's message
 */
	public static void sendSMG(String phoneNum, String content) {
		

		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		IP = config.getString("SMG.IP");
		PORT = config.getString("SMG.Port");
		PASSWORD = config.getString("SMG.password");
		String contents ="";
		
		try {
			contents=PASSWORD+"$"+phoneNum+"$"+content;
			contents = StringUtil.encodeString(contents,"GBK");
			if (logger.isInfoEnabled()) {
				logger.info("���ŷ�����...");
			}
			socket = new Socket(IP, Integer.parseInt(PORT));
			out = new PrintWriter(socket.getOutputStream(), true);
			out.println(contents);
			out.close();
			socket.close();
			if (logger.isInfoEnabled()) {
				logger.info("���ŷ��ͳɹ���");
			}			

		} catch (IOException e) {
			logger.error("���ŷ���ʧ�ܣ�", e);

		}		
		if (logger.isDebugEnabled()) {
			logger.debug("sendSMG(String, String) - end");
		}
	}

}
