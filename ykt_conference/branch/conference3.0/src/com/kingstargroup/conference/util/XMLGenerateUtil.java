package com.kingstargroup.conference.util;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. 
 * File name: XMLGenerateUtil.java
 * Description: util类，主要处理一些有关于xml相关的操作。
 * Modify History（或Change Log）:  
 * 操作类型（创建、修改等）   操作日期     操作者    操作内容简述
 * 创建  				2005-9-28    何林青    设计XML产生类
 * 修订					2005-10-08   何林青    增加XML输出类 XMLSendOut
 * <p>
 *
 * @author      何林青
 * @version     1.0
 * @since       1.0
 */

import java.io.PrintWriter;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

import com.kingstargroup.conference.hibernate.form.TConference;

public class XMLGenerateUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(XMLGenerateUtil.class);

	public static String XMLGenerate(String errorCode,
			String errorMessage, List listDate) {
		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - start");
		}

		String XMLTemp = "<?xml version=\"1.0\" encoding=\"GBK\"?><table></table>";
		try {
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element head = root.addElement("head");
			head.addElement("ErrorCode").addText(errorCode);
			head.addElement("ErrorMessage").addText(errorMessage);
			Element content = root.addElement("content");
			Element record = null;
			if (listDate != null) {
				for (int i = 0; i < listDate.size(); i++) {
					TConference tmp = (TConference)listDate.get(i);
					record = content.addElement("record");
					record.addElement("conId").addText(String.valueOf(tmp.getConId()));
					record.addElement("conName").addText(tmp.getConName());
					}
				}
			XMLTemp = document.asXML();
		} catch (Exception e) {
			logger.error("XMLGenerate(String, String, List)", e);

			System.err.println(e + "error");
		}

		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - end");
		}
		return XMLTemp;

	}
	
	public static String XMLGenerateJD(String errorCode,
			String errorMessage, List listDate) {
		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - start");
		}

		StringBuffer XMLTemp = new StringBuffer();
		
		XMLTemp.append(errorCode)
		.append("$")
		.append(errorMessage);
		
		if (listDate != null) {
			XMLTemp.append("$");
			for (int i = 0; i < listDate.size(); i++) {
				TConference tmp = (TConference)listDate.get(i);				
				XMLTemp.append(tmp.getConId())
				.append("$");
				if(i==listDate.size()-1){
					XMLTemp.append(tmp.getConName());
				}else{
					XMLTemp.append(tmp.getConName())
					.append("$");
				}
				
			}
		}

		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - end");
		}
		return XMLTemp.toString();

	}



	public static boolean XMLSendOut(HttpServletRequest request,
			HttpServletResponse response, String XMLStr) {
		if (logger.isDebugEnabled()) {
			logger
					.debug("XMLSendOut(HttpServletRequest, HttpServletResponse, String) - start"); //$NON-NLS-1$
		}

		try {
			response.setContentType("text/html;charset=GBK");
			PrintWriter out = response.getWriter();
			out.println(XMLStr);
			out.flush();
			out.close();
			if (logger.isDebugEnabled()) {
				logger
						.debug("XMLSendOut(HttpServletRequest, HttpServletResponse, String) - end"); //$NON-NLS-1$
			}

		} catch (Exception e) {
			logger
					.warn(
							"XMLSendOut(HttpServletRequest, HttpServletResponse, String) - exception ignored", e); //$NON-NLS-1$
			System.err.println(e + "error");
			return false;
		}
		return true;
	}
}
