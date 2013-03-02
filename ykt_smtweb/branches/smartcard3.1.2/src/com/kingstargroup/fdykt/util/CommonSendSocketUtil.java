/**
 * 
 */
package com.kingstargroup.fdykt.util;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.net.Socket;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.log4j.Logger;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: CommonSendSMGUtil.java<br>
 * Description: <br>
 * Modify History（或Change Log）: <br>
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述<br>
 * 创建 2005-11-7 何林青 <br>
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class CommonSendSocketUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(CommonSendSocketUtil.class);

	private static String IP = "";

	private static String PORT = "";

	private static String PASSWORD = "";

	private static Socket socket;

	private static PrintWriter out;

	/**
	 * 
	 */
	public CommonSendSocketUtil() {
		super();
		// TODO Auto-generated constructor stub
	}
/*
 * send SMG method 
 * @param  phoneNum   format 139*******;131********  use delimeter ";" to split them
 * @param  content    smg's message
 */
	public static void sendSocketInfo(String cellphone, String money,String serialno,String ecardno) {
		

		PropertiesConfiguration config = GetPropertiesUtil.getInstance();
		IP = config.getString("MOBILETRANS.IP");
		PORT = config.getString("MOBILETRANS.Port");
		String contents ="";
		
		try {
			contents=SocketInfoGenerateUtil.InfoGenerate(cellphone, money, serialno, ecardno);
			if (logger.isInfoEnabled()) {
				logger.info("信息发送中...");
			}
			socket = new Socket(IP, Integer.parseInt(PORT));
			out = new PrintWriter(socket.getOutputStream(), true);
			out.println(contents);
			BufferedReader bufferedReader = new BufferedReader(new InputStreamReader(socket.getInputStream()));
			String line = null;
			while ((line = bufferedReader.readLine()) != null) {
				String encycode = line.substring(line.length()-130, line.length());
				String decodeStr = SocketInfoGenerateUtil.InfoDecode(encycode);
//				String tempStr = line.substring(beginIndex)
//				if(decodeStr)
			}
			out.close();
			socket.close();
			if (logger.isInfoEnabled()) {
				logger.info("短信发送成功！");
			}

		} catch (IOException e) {
			logger.error("短信发送失败！", e);

		}		
		if (logger.isDebugEnabled()) {
			logger.debug("sendSMG(String, String) - end");
		}
	}

}
