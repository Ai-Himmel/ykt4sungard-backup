package com.kingstargroup.utils;

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

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.log4j.Logger;
import org.dom4j.Document;
import org.dom4j.DocumentHelper;
import org.dom4j.Element;

import com.kingstargroup.form.AbstractResult;

public class XMLGenerateUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(XMLGenerateUtil.class);

	public static String XMLGenerateWithFlag(String errorCode,
			String errorMessage, List listDate, String flag) {
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
			head.addElement("Flag").addText(flag);
			Element content = root.addElement("content");
			Element record = null;
			if (listDate != null) {
				for (int i = 0; i < listDate.size(); i++) {
					Object tmp = listDate.get(i);
					Class a = null;
					if (tmp instanceof AbstractResult) {
						a = tmp.getClass();
					} else {
						a = tmp.getClass().getSuperclass();
					}
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

	public static String XMLGenerate(String errorCode, String errorMessage,
			List listDate) {
		return XMLGenerateWithFlag(errorCode, errorMessage, listDate, "0");
	}

	public static String DeXMLGenerate(String xmlOut, List listDate) {
		if (logger.isDebugEnabled()) {
			logger.debug("DeXMLGenerate(String, List) - start"); //$NON-NLS-1$
		}

		String XMLTemp = xmlOut;
		try {
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element errorMessage = root.element("head").element("ErrorMessage");
			String errMsg = String.valueOf(Integer.parseInt(errorMessage
					.getText())
					+ listDate.size());
			errorMessage.clearContent();
			errorMessage.addText(errMsg);
			Element content = root.element("content");
			Element record = null;
			if (listDate != null) {
				for (int i = 0; i < listDate.size(); i++) {
					Object tmp = listDate.get(i);
					Class a = null;
					if (tmp instanceof AbstractResult) {
						a = tmp.getClass();
					} else {
						a = tmp.getClass().getSuperclass();
					}
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
			logger.error("DeXMLGenerate(String, List)", e); //$NON-NLS-1$

			System.err.println(e + "error");
		}

		if (logger.isDebugEnabled()) {
			logger.debug("XMLGenerate(String, String, List) - end");
		}
		return XMLTemp;

	}

	public static String serialXMLGenerate(String xmlOut, String xmlOutMonitor,
			int flag) {
		if (logger.isDebugEnabled()) {
			logger.debug("serialXMLGenerate(String, List) - start"); //$NON-NLS-1$
		}
		String XMLTemp = xmlOut;
		try {
			PropertiesConfiguration config = GetApplicationResources
					.getInstance();
			int cont = 0;
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element errorMessage = root.element("head").element("ErrorMessage");
			Element content = root.element("content");
			Element record = null;
			String[] serials = config.getStringArray("SERIAL_HEAD");
			for (int i = 0; i < serials.length; i++) {
				if (xmlOutMonitor.indexOf(serials[i]) == -1) {

					String tempStr = config
							.getString("com.kingstar.MonitorSys." + serials[i]);
					if (1 == flag) {
						// 返回数字
						if (!"BSHEETVER_ERROR".equals(serials[i])
								&& !"SETTIME_ERROR".equals(serials[i])
								&& !"UNBALANCE_ERROR".equals(serials[i])
								&& !"SERI_LOSS".equals(serials[i])
								&& !"SUPRESS_EXCEPTION".equals(serials[i])) {
							record = content.addElement("record");
							record.addElement("itemNo").addText(
									String.valueOf(i + 2));
							record.addElement("itemName").addText(tempStr);
							cont++;
						}

					} else {
						record = content.addElement("record");
						record.addElement("itemNo").addText(serials[i]);
						record.addElement("itemName").addText(tempStr);
						cont++;
					}

				}
			}
			String errMsg = String.valueOf(Integer.parseInt(errorMessage
					.getText())
					+ cont);
			errorMessage.clearContent();
			errorMessage.addText(errMsg);
			XMLTemp = document.asXML();
		} catch (Exception e) {
			logger.error("serialXMLGenerate(String)", e); //$NON-NLS-1$

			System.err.println(e + "error");
		}

		if (logger.isDebugEnabled()) {
			logger.debug("serialXMLGenerate(String, String, List) - end");
		}
		return XMLTemp;

	}

	public static String deviceXMLGenerate(String xmlOut) {
		if (logger.isDebugEnabled()) {
			logger.debug("serialXMLGenerate(String, List) - start"); //$NON-NLS-1$
		}
		String XMLTemp = xmlOut;
		try {
			PropertiesConfiguration config = GetApplicationResources
					.getInstance();
			int cont = 0;
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element errorMessage = root.element("head").element("ErrorMessage");
			Element content = root.element("content");
			Element record = null;
			String[] devices = config.getStringArray("DEVICE_HEAD");
			for (int i = 0; i < devices.length; i++) {
				String tempStr = config.getString("com.kingstar.MonitorSys."
						+ devices[i]);
				// 返回数字
				record = content.addElement("record");
				if (devices[i].equals("SET_DISCONNECT")) {
					record.addElement("itemNo").addText("101");
				} else if (devices[i].equals("SET_ALARM")) {
					record.addElement("itemNo").addText("102");
				} else if (devices[i].equals("SET_BSHEETVER_ERROR")) {
					record.addElement("itemNo").addText("11");
				} else if (devices[i].equals("SET_SETTIME_ERROR")) {
					record.addElement("itemNo").addText("12");
				} else {
					record.addElement("itemNo").addText("0");
				}
				record.addElement("itemName").addText(tempStr);
				cont++;

			}
			String errMsg = String.valueOf(Integer.parseInt(errorMessage
					.getText())
					+ cont);
			errorMessage.clearContent();
			errorMessage.addText(errMsg);
			XMLTemp = document.asXML();
		} catch (Exception e) {
			logger.error("deviceXMLGenerate(String)", e); //$NON-NLS-1$

			System.err.println(e + "error");
		}

		if (logger.isDebugEnabled()) {
			logger.debug("deviceXMLGenerate(String, String, List) - end");
		}
		return XMLTemp;

	}

	public static String SpecialXmlGenerate(int a, int b, int c, int d) {
		if (logger.isDebugEnabled()) {
			logger.debug("SpecialXmlGenerate(int, int, int, int) - start"); //$NON-NLS-1$
		}

		String XMLTemp = "<?xml version=\"1.0\" encoding=\"GBK\"?><table></table>";
		try {
			Document document = DocumentHelper.parseText(XMLTemp);
			Element root = document.getRootElement();
			Element head = root.addElement("head");
			// head.addElement("ErrorCode",errorCode);
			head.addElement("ErrorCode").addText("0000");
			// head.addElement("ErrorMessage",errorMessage);
			head.addElement("ErrorMessage").addText("5");
			Element content = root.addElement("content");
			Element record = content.addElement("record");
			// record.addElement(name,value);
			record.addElement("tag1000").addText(String.valueOf(a+b+c+d));
			record.addElement("tag1001").addText(String.valueOf(a));
			record.addElement("tag1002").addText(String.valueOf(b));
			record.addElement("tag1003").addText(String.valueOf(c));
			record.addElement("tag1004").addText(String.valueOf(d));

			XMLTemp = document.asXML();
		} catch (Exception e) {
			logger.error("SpecialXmlGenerate(int, int, int, int)", e); //$NON-NLS-1$			
			System.err.println(e + "error");
			return "";
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
