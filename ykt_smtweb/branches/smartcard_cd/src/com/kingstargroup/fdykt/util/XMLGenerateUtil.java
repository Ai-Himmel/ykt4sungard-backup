package com.kingstargroup.fdykt.util;

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
import java.lang.reflect.Field;
import java.lang.reflect.Method;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;


public class XMLGenerateUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(XMLGenerateUtil.class);

	public static String XMLGenerate(String errorCode,
			String errorMessage, String SidyAmount,String OutCardAmount,String SerialNo,String ParamKey,String CardId,List listDate) {
		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - start");
		}

		String XMLTemp = "<?xml version=\"1.0\" encoding=\"GBK\"?><table></table>";
		try {
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element head = root.addElement("head");
			// head.addElement("ErrorCode",errorCode);
			head.addElement("ErrorCode").addText(errorCode);
			// head.addElement("ErrorMessage",errorMessage);
			head.addElement("ErrorMessage").addText(errorMessage);
			head.addElement("SidyAmount").addText(SidyAmount);
			head.addElement("OutCardAmount").addText(OutCardAmount);
			head.addElement("SerialNo").addText(SerialNo);
			head.addElement("ParamKey").addText(ParamKey);
			head.addElement("CardId").addText(CardId);
			Element content = root.addElement("content").addText("");
			Element record = null;
			if (listDate != null) {
				for (int i = 0; i < listDate.size(); i++) {
					Object tmp = listDate.get(i);
					Class a = null;
					a = tmp.getClass().getSuperclass();
					Field[] fields = a.getDeclaredFields();
					record = content.addElement("record");
					for (int j = 0; j < fields.length; j++) {
						String name = fields[j].getName();
						if ("hashValue".equals(name) || "password".equals(name)) {
							continue;
						}
						StringBuffer getterMethodName = new StringBuffer();
						char firstChar = Character.toUpperCase(name.charAt(0));
						getterMethodName.append("get").append(firstChar)
								.append(name.substring(1));
						Method m = a.getMethod(getterMethodName.toString(),
								null);
						Object objectValue = m.invoke(tmp, null);
						String value = "";
						if (objectValue != null) {
							if ("getId".equals(getterMethodName.toString())
									&& !"java.lang.Integer".equals(objectValue
											.getClass().getName())) {
								Field[] keyFields = objectValue.getClass()
										.getDeclaredFields();
								Class c = objectValue.getClass();
								for (int k = 0; k < keyFields.length; k++) {
									String keyName = keyFields[k].getName();
									if ("hashValue".equals(keyName)) {
										continue;
									}
									StringBuffer getterKeyMethodName = new StringBuffer();
									char firstKeyChar = Character
											.toUpperCase(keyName.charAt(0));
									getterKeyMethodName.append("get").append(
											firstKeyChar).append(
											keyName.substring(1));
									Method mKey = c.getMethod(
											getterKeyMethodName.toString(),
											null);
									Object objectKeyValue = mKey.invoke(
											objectValue, null);
									String KeyValue = "";
									if (objectKeyValue != null) {
										KeyValue = objectKeyValue.toString();
									}
									// record.addElement(name,value);
									record.addElement(keyName)
											.addText(KeyValue);
								}
							} else {
								value = objectValue.toString();
							}

						}
						// record.addElement(name,value);
						record.addElement(name).addText(value);
					}
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
	
	public static String MoblileXMLGenerate(String errorCode,
			String errorMessage, String MobileAmount,String OutCardAmount,String SerialNo,String ParamKey,String CardId,List listDate) {
		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - start");
		}

		String XMLTemp = "<?xml version=\"1.0\" encoding=\"GBK\"?><table></table>";
		try {
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element head = root.addElement("head");
			// head.addElement("ErrorCode",errorCode);
			head.addElement("ErrorCode").addText(errorCode);
			// head.addElement("ErrorMessage",errorMessage);
			head.addElement("ErrorMessage").addText(errorMessage);
			head.addElement("MobileAmount").addText(MobileAmount);
			head.addElement("OutCardAmount").addText(OutCardAmount);
			head.addElement("SerialNo").addText(SerialNo);
			head.addElement("ParamKey").addText(ParamKey);
			head.addElement("CardId").addText(CardId);
			Element content = root.addElement("content").addText("");
			Element record = null;
			if (listDate != null) {
				for (int i = 0; i < listDate.size(); i++) {
					Object tmp = listDate.get(i);
					Class a = null;
					a = tmp.getClass().getSuperclass();
					Field[] fields = a.getDeclaredFields();
					record = content.addElement("record");
					for (int j = 0; j < fields.length; j++) {
						String name = fields[j].getName();
						if ("hashValue".equals(name) || "password".equals(name)) {
							continue;
						}
						StringBuffer getterMethodName = new StringBuffer();
						char firstChar = Character.toUpperCase(name.charAt(0));
						getterMethodName.append("get").append(firstChar)
								.append(name.substring(1));
						Method m = a.getMethod(getterMethodName.toString(),
								null);
						Object objectValue = m.invoke(tmp, null);
						String value = "";
						if (objectValue != null) {
							if ("getId".equals(getterMethodName.toString())
									&& !"java.lang.Integer".equals(objectValue
											.getClass().getName())) {
								Field[] keyFields = objectValue.getClass()
										.getDeclaredFields();
								Class c = objectValue.getClass();
								for (int k = 0; k < keyFields.length; k++) {
									String keyName = keyFields[k].getName();
									if ("hashValue".equals(keyName)) {
										continue;
									}
									StringBuffer getterKeyMethodName = new StringBuffer();
									char firstKeyChar = Character
											.toUpperCase(keyName.charAt(0));
									getterKeyMethodName.append("get").append(
											firstKeyChar).append(
											keyName.substring(1));
									Method mKey = c.getMethod(
											getterKeyMethodName.toString(),
											null);
									Object objectKeyValue = mKey.invoke(
											objectValue, null);
									String KeyValue = "";
									if (objectKeyValue != null) {
										KeyValue = objectKeyValue.toString();
									}
									// record.addElement(name,value);
									record.addElement(keyName)
											.addText(KeyValue);
								}
							} else {
								value = objectValue.toString();
							}

						}
						// record.addElement(name,value);
						record.addElement(name).addText(value);
					}
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
	
	public static String WaterXMLGenerate(String errorCode,
			String errorMessage, String WaterAmount,String OutCardAmount,String OutCardAmount1,String SerialNo,String SerialNo1,String CardId,List listDate) {
		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - start");
		}

		String XMLTemp = "<?xml version=\"1.0\" encoding=\"GBK\"?><table></table>";
		try {
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element head = root.addElement("head");
			// head.addElement("ErrorCode",errorCode);
			head.addElement("ErrorCode").addText(errorCode);
			// head.addElement("ErrorMessage",errorMessage);
			head.addElement("ErrorMessage").addText(errorMessage);
			head.addElement("WaterAmount").addText(WaterAmount);
			head.addElement("OutCardAmount").addText(OutCardAmount);
			head.addElement("OutCardAmount1").addText(OutCardAmount1);
			head.addElement("SerialNo").addText(SerialNo);
			head.addElement("SerialNo1").addText(SerialNo1);
			head.addElement("CardId").addText(CardId);
			Element content = root.addElement("content").addText("");
			Element record = null;
			if (listDate != null) {
				for (int i = 0; i < listDate.size(); i++) {
					Object tmp = listDate.get(i);
					Class a = null;
					a = tmp.getClass().getSuperclass();
					Field[] fields = a.getDeclaredFields();
					record = content.addElement("record");
					for (int j = 0; j < fields.length; j++) {
						String name = fields[j].getName();
						if ("hashValue".equals(name) || "password".equals(name)) {
							continue;
						}
						StringBuffer getterMethodName = new StringBuffer();
						char firstChar = Character.toUpperCase(name.charAt(0));
						getterMethodName.append("get").append(firstChar)
								.append(name.substring(1));
						Method m = a.getMethod(getterMethodName.toString(),
								null);
						Object objectValue = m.invoke(tmp, null);
						String value = "";
						if (objectValue != null) {
							if ("getId".equals(getterMethodName.toString())
									&& !"java.lang.Integer".equals(objectValue
											.getClass().getName())) {
								Field[] keyFields = objectValue.getClass()
										.getDeclaredFields();
								Class c = objectValue.getClass();
								for (int k = 0; k < keyFields.length; k++) {
									String keyName = keyFields[k].getName();
									if ("hashValue".equals(keyName)) {
										continue;
									}
									StringBuffer getterKeyMethodName = new StringBuffer();
									char firstKeyChar = Character
											.toUpperCase(keyName.charAt(0));
									getterKeyMethodName.append("get").append(
											firstKeyChar).append(
											keyName.substring(1));
									Method mKey = c.getMethod(
											getterKeyMethodName.toString(),
											null);
									Object objectKeyValue = mKey.invoke(
											objectValue, null);
									String KeyValue = "";
									if (objectKeyValue != null) {
										KeyValue = objectKeyValue.toString();
									}
									// record.addElement(name,value);
									record.addElement(keyName)
											.addText(KeyValue);
								}
							} else {
								value = objectValue.toString();
							}

						}
						// record.addElement(name,value);
						record.addElement(name).addText(value);
					}
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
