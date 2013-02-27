/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.kingstargroup.utils;

import java.io.BufferedReader;
import java.io.ByteArrayOutputStream;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.PrintWriter;
import java.io.StringReader;
import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.List;

import org.apache.commons.configuration.PropertiesConfiguration;

/**
 * <a href="StringUtil.java.html"><b><i>View Source</i></b></a>
 * 
 * @author Brian Wing Shun Chan
 * @version $Revision: 1.24 $
 * 
 */
public class StringUtil {

	public static final String CURRENT_SYS_ENCODING = System
			.getProperty("file.encoding");

	public static String encodeString(String str, String toEncoding)
			throws UnsupportedEncodingException {
		if (CURRENT_SYS_ENCODING.equals(toEncoding)) {
			return str;
		}
		return new String(str.getBytes(toEncoding), toEncoding);
	}

	public static String solidStringGenerate(String id, String name,
			Integer card_no, String cut_name, String serialno, String tx_date,
			String tx_time, String error) {
		String error_cn = GetApplicationResources.getInstance().getString(
				"com.kingstar.MonitorSys.errorReason." + error);
		StringBuffer a = new StringBuffer(100);
		a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
				.append(name).append("</td><td>").append(card_no).append(
						"</td><td>").append(cut_name).append("</td><td>")
				.append(serialno).append("</td><td>").append(tx_date).append(
						"</td><td>").append(tx_time).append("</td><td>")
				.append(error_cn).append("</td></tr>");
		return a.toString();
	}

	// 流水缺失
	public static String seriallostStringGenerate(String id, String name,
			String serialno, String tx_date, String tx_time, String error) {
		String error_cn = GetApplicationResources.getInstance().getString(
				"com.kingstar.MonitorSys.errorReason." + error);
		StringBuffer a = new StringBuffer(100);
		a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
				.append(name).append("</td><td>").append(serialno).append(
						"</td><td>").append(tx_date).append("</td><td>")
				.append(tx_time).append("</td><td>").append(error_cn).append(
						"</td></tr>");
		return a.toString();
	}

	// 设备时钟错误
	public static String devtimeStringGenerate(String id, String name,
			String dev_time, String server_time, String error) {
		String error_cn = GetApplicationResources.getInstance().getString(
				"com.kingstar.MonitorSys.errorReason." + error);
		StringBuffer a = new StringBuffer(100);
		a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
				.append(name).append("</td><td>").append(dev_time).append(
						"</td><td>").append(server_time).append("</td><td>")
				.append(error_cn).append("</td></tr>");
		return a.toString();
	}

	// 异常流水
	// public static String ExpSerialStringGenerate(String id, String name,
	// Integer card_no, String cut_name, String serialno, String tx_date,
	// String tx_time, String error) {
	// String error_cn = GetApplicationResources.getInstance().getString(
	// "com.kingstar.MonitorSys.errorReason." + error);
	// StringBuffer a = new StringBuffer(100);
	// a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
	// .append(name).append("</td><td>").append(card_no).append(
	// "</td><td>").append(cut_name).append("</td><td>")
	// .append(serialno).append("</td><td>").append(tx_date).append(
	// "</td><td>").append(tx_time).append("</td><td>")
	// .append(error_cn).append("</td></tr>");
	// return a.toString();
	// }

	// 中途拔卡
	// public static String MidDragStringGenerate(String id, String name,
	// Integer card_no, String cut_name, String serialno, String tx_date,
	// String tx_time, String error) {
	// String error_cn = GetApplicationResources.getInstance().getString(
	// "com.kingstar.MonitorSys.errorReason." + error);
	// StringBuffer a = new StringBuffer(100);
	// a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
	// .append(name).append("</td><td>").append(card_no).append(
	// "</td><td>").append(cut_name).append("</td><td>")
	// .append(serialno).append("</td><td>").append(tx_date).append(
	// "</td><td>").append(tx_time).append("</td><td>")
	// .append(error_cn).append("</td></tr>");
	// return a.toString();
	// }

	// 黑卡消费
	// public static String blkverStringGenerate(String id, String name,
	// Integer card_no, String cut_name, String serialno, String tx_date,
	// String tx_time, String error) {
	// String error_cn = GetApplicationResources.getInstance().getString(
	// "com.kingstar.MonitorSys.errorReason." + error);
	// StringBuffer a = new StringBuffer(100);
	// a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
	// .append(name).append("</td><td>").append(card_no).append(
	// "</td><td>").append(cut_name).append("</td><td>")
	// .append(serialno).append("</td><td>").append(tx_date).append(
	// "</td><td>").append(tx_time).append("</td><td>")
	// .append(error_cn).append("</td></tr>");
	// return a.toString();
	// }

	// 黑名单版本不正确
	public static String blksheetStringGenerate(String id, String name,
			String blksheet_old, String blksheet_new, String error) {
		String error_cn = GetApplicationResources.getInstance().getString(
				"com.kingstar.MonitorSys.errorReason." + error);

		StringBuffer a = new StringBuffer(100);
		a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
				.append(name).append("</td><td>").append(blksheet_old).append(
						"</td><td>").append(blksheet_new).append("</td><td>")
				.append(error_cn).append("</td></tr>");
		return a.toString();
	}

	// 大额消费
	public static String largeExceptStringGenerate(String id, String name,
			Integer card_no, String cut_name, String serialno, float amount,
			String tx_date, String tx_time, String error) {
		String error_cn = GetApplicationResources.getInstance().getString(
				"com.kingstar.MonitorSys.errorReason." + error);
		StringBuffer a = new StringBuffer(100);
		a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
				.append(name).append("</td><td>").append(card_no).append(
						"</td><td>").append(cut_name).append("</td><td>")
				.append(serialno).append("</td><td>").append(amount).append(
						"</td><td>").append(tx_date).append("</td><td>")
				.append(tx_time).append("</td><td>").append(error_cn).append(
						"</td></tr>");
		return a.toString();
	}

	// 压数流水
	public static String suppressExceptStringGenerate(String id, String name,
			String txDate, String txTime, String Date, String serialno,
			String error) {
		String error_cn = GetApplicationResources.getInstance().getString(
				"com.kingstar.MonitorSys.errorReason." + error);
		StringBuffer a = new StringBuffer(100);
		a.append("<tr align=\"center\"><td>").append(id).append("</td><td>")
				.append(name).append("</td><td>").append(txDate).append(
						"</td><td>").append(txTime).append("</td><td>").append(
						Date).append("</td><td>").append(serialno).append(
						"</td><td>").append(error_cn).append("</td></tr>");
		return a.toString();
	}

	public static String blksheetMailGenerate(String contact,
			String analysisTime, int record, String content, String errType) {
		PropertiesConfiguration config = GetApplicationResources.getInstance();
		StringBuffer returnStr = new StringBuffer();

		returnStr
				.append("<html><head><meta http-equiv=\"Content-Type\"")
				.append("content=\"text/html; charset=gb2312\"></head><body>")
				.append(
						"<table width=\"900\" align=\"center\"><tr><td width=\"293\">")
				// .append(contact)
				.append(contact + " ")
				.append(config.getString("com.kingstar.MonitorSys.NAME"))
				.append(":")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_HEAD"))
				.append("</td></tr><tr><td>")
				.append(config.getString("com.kingstar.MonitorSys.SYSTEM_INFO"))
				.append("</td></tr><tr><td>")
				.append(analysisTime)
				.append("&nbsp;&nbsp;&nbsp;&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_INFO"))
				.append("&nbsp;<b>")
				.append(record)
				.append("</b>&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.STRIP"))
				.append("&nbsp;<b>")
				.append(
						config.getString("com.kingstar.MonitorSys.errorReason."
								+ errType))
				.append("</b>&nbsp;")
				.append("</td></tr><tr><td></td></tr></table>")

				.append("<table width=\"900\" align=\"center\">")
				.append("<tr><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_ID"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_NAME"))
				.append("</th><th>")
				.append(
						config
								.getString("com.kingstar.MonitorSys.BLKSHEET_OLD"))
				.append("</th><th>")
				.append(
						config
								.getString("com.kingstar.MonitorSys.BLKSHEET_NEW"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.ERROR"))
				.append("</th></tr>")
				.append(content)
				.append(
						"</table><table width=\"900\" border=\"0\" align=\"center\">")
				.append("<tr align=center><td>&nbsp;").append(
						config.getString("com.kingstar.MonitorSys.COPYRIGHT"))
				.append("</td></tr></table></body></html>");
		return returnStr.toString();
	}

	public static String largeExceptMailGenerate(String contact,
			String analysisTime, int record, String content, String errType) {
		PropertiesConfiguration config = GetApplicationResources.getInstance();
		StringBuffer returnStr = new StringBuffer();

		returnStr
				.append("<html><head><meta http-equiv=\"Content-Type\"")
				.append("content=\"text/html; charset=gb2312\"></head><body>")
				.append(
						"<table width=\"1100\" align=\"center\"><tr><td width=\"293\">")
				// .append(contact)
				.append(contact + " ")
				.append(config.getString("com.kingstar.MonitorSys.NAME"))
				.append(":")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_HEAD"))
				.append("</td></tr><tr><td>")
				.append(config.getString("com.kingstar.MonitorSys.SYSTEM_INFO"))
				.append("</td></tr><tr><td>")
				.append(analysisTime)
				.append("&nbsp;&nbsp;&nbsp;&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_INFO"))
				.append("&nbsp;<b>")
				.append(record)
				.append("</b>&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.STRIP"))
				.append("&nbsp;<b>")
				.append(
						config.getString("com.kingstar.MonitorSys.errorReason."
								+ errType))
				.append("</b>&nbsp;")
				.append("</td></tr><tr><td></td></tr></table>")

				.append("<table width=\"1100\" align=\"center\">")
				.append("<tr><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_ID"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_NAME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.CARD_NO"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.CUT_NAME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.SERIAL_NO"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.AMOUNT"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.TX_DATE"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.TX_TIME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.ERROR"))
				.append("</th></tr>")
				.append(content)
				.append(
						"</table><table width=\"1100\" border=\"0\" align=\"center\">")
				.append("<tr align=center><td>&nbsp;").append(
						config.getString("com.kingstar.MonitorSys.COPYRIGHT"))
				.append("</td></tr></table></body></html>");
		return returnStr.toString();
	}

	public static String suppressExceptMailGenerate(String contact,
			String analysisTime, int record, String content, String errType) {
		PropertiesConfiguration config = GetApplicationResources.getInstance();
		StringBuffer returnStr = new StringBuffer();

		returnStr
				.append("<html><head><meta http-equiv=\"Content-Type\"")
				.append("content=\"text/html; charset=gb2312\"></head><body>")
				.append(
						"<table width=\"900\" align=\"center\"><tr><td width=\"293\">")
				// .append(contact)
				.append(contact + " ")
				.append(config.getString("com.kingstar.MonitorSys.NAME"))
				.append(":")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_HEAD"))
				.append("</td></tr><tr><td>")
				.append(config.getString("com.kingstar.MonitorSys.SYSTEM_INFO"))
				.append("</td></tr><tr><td>")
				.append(analysisTime)
				.append("&nbsp;&nbsp;&nbsp;&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_INFO"))
				.append("&nbsp;<b>")
				.append(record)
				.append("</b>&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.STRIP"))
				.append("&nbsp;<b>")
				.append(
						config.getString("com.kingstar.MonitorSys.errorReason."
								+ errType))
				.append("</b>&nbsp;")
				.append("</td></tr><tr><td></td></tr></table>")

				.append("<table width=\"900\" align=\"center\">")
				.append("<tr><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_ID"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_NAME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.LAST_DATE"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.LAST_TIME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DATE"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.SERIAL_NO"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.ERROR"))
				.append("</th></tr>")
				.append(content)
				.append(
						"</table><table width=\"900\" border=\"0\" align=\"center\">")
				.append("<tr align=center><td>&nbsp;").append(
						config.getString("com.kingstar.MonitorSys.COPYRIGHT"))
				.append("</td></tr></table></body></html>");
		return returnStr.toString();
	}
	
	public static String devTimeMailGenerate(String contact, String analysisTime,
			int record, String content, String errType) {
		PropertiesConfiguration config = GetApplicationResources.getInstance();
		StringBuffer returnStr = new StringBuffer();

		returnStr
				.append("<html><head><meta http-equiv=\"Content-Type\"")
				.append("content=\"text/html; charset=gb2312\"></head><body>")
				.append(
						"<table width=\"900\" align=\"center\"><tr><td width=\"293\">")
				// .append(contact)
				.append(contact + " ")
				.append(config.getString("com.kingstar.MonitorSys.NAME"))
				.append(":")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_HEAD"))
				.append("</td></tr><tr><td>")
				.append(config.getString("com.kingstar.MonitorSys.SYSTEM_INFO"))
				.append("</td></tr><tr><td>")
				.append(analysisTime)
				.append("&nbsp;&nbsp;&nbsp;&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_INFO"))
				.append("&nbsp;<b>")
				.append(record)
				.append("</b>&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.STRIP"))
				.append("&nbsp;<b>")
				.append(
						config.getString("com.kingstar.MonitorSys.errorReason."
								+ errType))
				.append("</b>&nbsp;")
				.append("</td></tr><tr><td></td></tr></table>")

				.append("<table width=\"900\" align=\"center\">")
				.append("<tr><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_ID"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_NAME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEV_TIME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.SERVER_TIME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.ERROR"))
				.append("</th></tr>")
				.append(content)
				.append(
						"</table><table width=\"900\" border=\"0\" align=\"center\">")
				.append("<tr align=center><td>&nbsp;").append(
						config.getString("com.kingstar.MonitorSys.COPYRIGHT"))
				.append("</td></tr></table></body></html>");
		return returnStr.toString();
	}

	public static String wholeSMGGenerate(String contact, String analysisTime,
			int record, String errType) {
		PropertiesConfiguration config = GetApplicationResources.getInstance();
		StringBuffer returnStr = new StringBuffer();
		returnStr.append(contact).append(" ").append(
				config.getString("com.kingstar.MonitorSys.SMG.HEAD")).append(
				" ").append(analysisTime).append(" ").append(
				config.getString("com.kingstar.MonitorSys.SMG.INFO")).append(
				record).append(
				config.getString("com.kingstar.MonitorSys.STRIP")).append(
				config.getString("com.kingstar.MonitorSys.errorReason."
						+ errType));
		return returnStr.toString();

	}

	public static String wholeMailGenerate(String contact, String analysisTime,
			int record, String content, String errType) {
		PropertiesConfiguration config = GetApplicationResources.getInstance();
		StringBuffer returnStr = new StringBuffer();

		returnStr
				.append("<html><head><meta http-equiv=\"Content-Type\"")
				.append("content=\"text/html; charset=gb2312\"></head><body>")
				.append(
						"<table width=\"900\" align=\"center\"><tr><td width=\"293\">")
				// .append(contact)
				.append(contact + " ")
				.append(config.getString("com.kingstar.MonitorSys.NAME"))
				.append(":")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_HEAD"))
				.append("</td></tr><tr><td>")
				.append(config.getString("com.kingstar.MonitorSys.SYSTEM_INFO"))
				.append("</td></tr><tr><td>")
				.append(analysisTime)
				.append("&nbsp;&nbsp;&nbsp;&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_INFO"))
				.append("&nbsp;<b>")
				.append(record)
				.append("</b>&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.STRIP"))
				.append("&nbsp;<b>")
				.append(
						config.getString("com.kingstar.MonitorSys.errorReason."
								+ errType))
				.append("</b>&nbsp;")
				.append("</td></tr><tr><td></td></tr></table>")

				.append("<table width=\"900\" align=\"center\">")
				.append("<tr><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_ID"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_NAME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.CARD_NO"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.CUT_NAME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.SERIAL_NO"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.TX_DATE"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.TX_TIME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.ERROR"))
				.append("</th></tr>")
				.append(content)
				.append(
						"</table><table width=\"900\" border=\"0\" align=\"center\">")
				.append("<tr align=center><td>&nbsp;").append(
						config.getString("com.kingstar.MonitorSys.COPYRIGHT"))
				.append("</td></tr></table></body></html>");
		return returnStr.toString();
	}
	
	public static String serialostMailGenerate(String contact, String analysisTime,
			int record, String content, String errType) {
		PropertiesConfiguration config = GetApplicationResources.getInstance();
		StringBuffer returnStr = new StringBuffer();

		returnStr
				.append("<html><head><meta http-equiv=\"Content-Type\"")
				.append("content=\"text/html; charset=gb2312\"></head><body>")
				.append(
						"<table width=\"900\" align=\"center\"><tr><td width=\"293\">")
				// .append(contact)
				.append(contact + " ")
				.append(config.getString("com.kingstar.MonitorSys.NAME"))
				.append(":")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_HEAD"))
				.append("</td></tr><tr><td>")
				.append(config.getString("com.kingstar.MonitorSys.SYSTEM_INFO"))
				.append("</td></tr><tr><td>")
				.append(analysisTime)
				.append("&nbsp;&nbsp;&nbsp;&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.MAIL_INFO"))
				.append("&nbsp;<b>")
				.append(record)
				.append("</b>&nbsp;")
				.append(config.getString("com.kingstar.MonitorSys.STRIP"))
				.append("&nbsp;<b>")
				.append(
						config.getString("com.kingstar.MonitorSys.errorReason."
								+ errType))
				.append("</b>&nbsp;")
				.append("</td></tr><tr><td></td></tr></table>")

				.append("<table width=\"900\" align=\"center\">")
				.append("<tr><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_ID"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_NAME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.SERIAL_NO"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.TX_DATE"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.TX_TIME"))
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.ERROR"))
				.append("</th></tr>")
				.append(content)
				.append(
						"</table><table width=\"900\" border=\"0\" align=\"center\">")
				.append("<tr align=center><td>&nbsp;").append(
						config.getString("com.kingstar.MonitorSys.COPYRIGHT"))
				.append("</td></tr></table></body></html>");
		return returnStr.toString();
	}

	public static String add(String s, String add) {
		return add(s, add, ",");
	}

	public static String add(String s, String add, String delimiter) {
		return add(s, add, delimiter, false);
	}

	public static String add(String s, String add, String delimiter,
			boolean allowDuplicates) {

		if ((add == null) || (delimiter == null)) {
			return null;
		}

		if (s == null) {
			s = "";
		}

		if (allowDuplicates || !contains(s, add, delimiter)) {
			if (null == s || s.endsWith(delimiter)) {
				s += add + delimiter;
			} else {
				s += delimiter + add + delimiter;
			}
		}

		return s;
	}

	public static boolean contains(String s, String text) {
		return contains(s, text, ",");
	}

	public static boolean contains(String s, String text, String delimiter) {
		if ((s == null) || (text == null) || (delimiter == null)) {
			return false;
		}

		if (!s.endsWith(delimiter)) {
			s += delimiter;
		}

		int pos = s.indexOf(delimiter + text + delimiter);

		if (pos == -1) {
			if (s.startsWith(text + delimiter)) {
				return true;
			}

			return false;
		}

		return true;
	}

	public static int count(String s, String text) {
		if ((s == null) || (text == null)) {
			return 0;
		}

		int count = 0;

		int pos = s.indexOf(text);

		while (pos != -1) {
			pos = s.indexOf(text, pos + text.length());
			count++;
		}

		return count;
	}

	public static boolean endsWith(String s, char end) {
		return startsWith(s, (new Character(end)).toString());
	}

	public static boolean endsWith(String s, String end) {
		if ((s == null) || (end == null)) {
			return false;
		}

		if (end.length() > s.length()) {
			return false;
		}

		String temp = s.substring(s.length() - end.length(), s.length());

		if (temp.equalsIgnoreCase(end)) {
			return true;
		} else {
			return false;
		}
	}

	public static String merge(List list) {
		return merge(list, ",");
	}

	public static String merge(List list, String delimiter) {
		return merge((String[]) list.toArray(new String[0]), delimiter);
	}

	public static String merge(String array[]) {
		return merge(array, ",");
	}

	public static String merge(String array[], String delimiter) {
		if (array == null) {
			return null;
		}

		StringBuffer sb = new StringBuffer();

		for (int i = 0; i < array.length; i++) {
			sb.append(array[i].trim());

			if ((i + 1) != array.length) {
				sb.append(delimiter);
			}
		}

		return sb.toString();
	}

	public static String read(ClassLoader classLoader, String name)
			throws IOException {

		return read(classLoader.getResourceAsStream(name));
	}

	public static String read(InputStream is) throws IOException {
		BufferedReader br = new BufferedReader(new InputStreamReader(is));

		StringBuffer sb = new StringBuffer();
		String line = null;

		while ((line = br.readLine()) != null) {
			sb.append(line).append('\n');
		}

		br.close();

		return sb.toString().trim();
	}

	public static String remove(String s, String remove) {
		return remove(s, remove, ",");
	}

	public static String remove(String s, String remove, String delimiter) {
		if ((s == null) || (remove == null) || (delimiter == null)) {
			return null;
		}

		if (null == s && !s.endsWith(delimiter)) {
			s += delimiter;
		}

		while (contains(s, remove, delimiter)) {
			int pos = s.indexOf(delimiter + remove + delimiter);

			if (pos == -1) {
				if (s.startsWith(remove + delimiter)) {
					s = s.substring(remove.length() + delimiter.length(), s
							.length());
				}
			} else {
				s = s.substring(0, pos)
						+ s.substring(pos + remove.length()
								+ delimiter.length(), s.length());
			}
		}

		return s;
	}

	public static String replace(String s, char oldSub, char newSub) {
		return replace(s, oldSub, new Character(newSub).toString());
	}

	public static String replace(String s, char oldSub, String newSub) {
		if ((s == null) || (newSub == null)) {
			return null;
		}

		char[] c = s.toCharArray();

		StringBuffer sb = new StringBuffer();

		for (int i = 0; i < c.length; i++) {
			if (c[i] == oldSub) {
				sb.append(newSub);
			} else {
				sb.append(c[i]);
			}
		}

		return sb.toString();
	}

	public static String replace(String s, String oldSub, String newSub) {
		if ((s == null) || (oldSub == null) || (newSub == null)) {
			return null;
		}

		int y = s.indexOf(oldSub);

		if (y >= 0) {
			StringBuffer sb = new StringBuffer();

			int length = oldSub.length();
			int x = 0;

			while (x <= y) {
				sb.append(s.substring(x, y));
				sb.append(newSub);
				x = y + length;
				y = s.indexOf(oldSub, x);
			}

			sb.append(s.substring(x));

			return sb.toString();
		} else {
			return s;
		}
	}

	public static String replace(String s, String[] oldSubs, String[] newSubs) {
		if ((s == null) || (oldSubs == null) || (newSubs == null)) {
			return null;
		}

		if (oldSubs.length != newSubs.length) {
			return s;
		}

		for (int i = 0; i < oldSubs.length; i++) {
			s = replace(s, oldSubs[i], newSubs[i]);
		}

		return s;
	}

	public static String reverse(String s) {
		if (s == null) {
			return null;
		}

		char[] c = s.toCharArray();
		char[] reverse = new char[c.length];

		for (int i = 0; i < c.length; i++) {
			reverse[i] = c[c.length - i - 1];
		}

		return new String(reverse);
	}

	public static String shorten(String s) {
		return shorten(s, 20);
	}

	public static String shorten(String s, int length) {
		return shorten(s, length, "..");
	}

	public static String shorten(String s, String suffix) {
		return shorten(s, 20, suffix);
	}

	public static String shorten(String s, int length, String suffix) {
		if (s == null || suffix == null) {
			return null;
		}

		if (s.length() > length) {
			s = s.substring(0, length) + suffix;
		}

		return s;
	}

	public static String[] split(String s) {
		return split(s, ",");
	}

	public static String[] split(String s, String delimiter) {
		if (s == null || delimiter == null) {
			return new String[0];
		}

		s = s.trim();

		if (!s.endsWith(delimiter)) {
			s += delimiter;
		}

		if (s.equals(delimiter)) {
			return new String[0];
		}

		List nodeValues = new ArrayList();

		if (delimiter.equals("\n") || delimiter.equals("\r")) {
			try {
				BufferedReader br = new BufferedReader(new StringReader(s));

				String line = null;

				while ((line = br.readLine()) != null) {
					nodeValues.add(line);
				}

				br.close();
			} catch (IOException ioe) {
				ioe.printStackTrace();
			}
		} else {
			int offset = 0;
			int pos = s.indexOf(delimiter, offset);

			while (pos != -1) {
				nodeValues.add(s.substring(offset, pos));

				offset = pos + delimiter.length();
				pos = s.indexOf(delimiter, offset);
			}
		}

		return (String[]) nodeValues.toArray(new String[0]);
	}

	public static boolean[] split(String s, String delimiter, boolean x) {
		String[] array = split(s, delimiter);
		boolean[] newArray = new boolean[array.length];

		for (int i = 0; i < array.length; i++) {
			boolean value = x;

			try {
				value = Boolean.valueOf(array[i]).booleanValue();
			} catch (Exception e) {
			}

			newArray[i] = value;
		}

		return newArray;
	}

	public static double[] split(String s, String delimiter, double x) {
		String[] array = split(s, delimiter);
		double[] newArray = new double[array.length];

		for (int i = 0; i < array.length; i++) {
			double value = x;

			try {
				value = Double.parseDouble(array[i]);
			} catch (Exception e) {
			}

			newArray[i] = value;
		}

		return newArray;
	}

	public static float[] split(String s, String delimiter, float x) {
		String[] array = split(s, delimiter);
		float[] newArray = new float[array.length];

		for (int i = 0; i < array.length; i++) {
			float value = x;

			try {
				value = Float.parseFloat(array[i]);
			} catch (Exception e) {
			}

			newArray[i] = value;
		}

		return newArray;
	}

	public static int[] split(String s, String delimiter, int x) {
		String[] array = split(s, delimiter);
		int[] newArray = new int[array.length];

		for (int i = 0; i < array.length; i++) {
			int value = x;

			try {
				value = Integer.parseInt(array[i]);
			} catch (Exception e) {
			}

			newArray[i] = value;
		}

		return newArray;
	}

	public static long[] split(String s, String delimiter, long x) {
		String[] array = split(s, delimiter);
		long[] newArray = new long[array.length];

		for (int i = 0; i < array.length; i++) {
			long value = x;

			try {
				value = Long.parseLong(array[i]);
			} catch (Exception e) {
			}

			newArray[i] = value;
		}

		return newArray;
	}

	public static short[] split(String s, String delimiter, short x) {
		String[] array = split(s, delimiter);
		short[] newArray = new short[array.length];

		for (int i = 0; i < array.length; i++) {
			short value = x;

			try {
				value = Short.parseShort(array[i]);
			} catch (Exception e) {
			}

			newArray[i] = value;
		}

		return newArray;
	}

	public static final String stackTrace(Throwable t) {
		String s = null;

		try {
			ByteArrayOutputStream baos = new ByteArrayOutputStream();
			t.printStackTrace(new PrintWriter(baos, true));
			s = baos.toString();
		} catch (Exception e) {
		}

		return s;
	}

	public static boolean startsWith(String s, char begin) {
		return startsWith(s, (new Character(begin)).toString());
	}

	public static boolean startsWith(String s, String start) {
		if ((s == null) || (start == null)) {
			return false;
		}

		if (start.length() > s.length()) {
			return false;
		}

		String temp = s.substring(0, start.length());

		if (temp.equalsIgnoreCase(start)) {
			return true;
		} else {
			return false;
		}
	}

	public static String trimLeading(String s) {
		for (int i = 0; i < s.length(); i++) {
			if (!Character.isWhitespace(s.charAt(i))) {
				return s.substring(i, s.length());
			}
		}

		return "";
	}

	public static String trimTrailing(String s) {
		for (int i = s.length() - 1; i >= 0; i--) {
			if (!Character.isWhitespace(s.charAt(i))) {
				return s.substring(0, i + 1);
			}
		}

		return "";
	}

	public static String wrap(String text) {
		return wrap(text, 80, "\n");
	}

	public static String wrap(String text, int width, String lineSeparator) {
		if (text == null) {
			return null;
		}

		StringBuffer sb = new StringBuffer();

		try {
			BufferedReader br = new BufferedReader(new StringReader(text));

			String s = "";

			while ((s = br.readLine()) != null) {
				if (s.length() == 0) {
					sb.append(lineSeparator);
				} else {
					String[] tokens = s.split(" ");
					boolean firstWord = true;
					int curLineLength = 0;

					for (int i = 0; i < tokens.length; i++) {
						if (!firstWord) {
							sb.append(" ");
							curLineLength++;
						}

						if (firstWord) {
							sb.append(lineSeparator);
						}

						sb.append(tokens[i]);

						curLineLength += tokens[i].length();

						if (curLineLength >= width) {
							firstWord = true;
							curLineLength = 0;
						} else {
							firstWord = false;
						}
					}
				}
			}
		} catch (IOException ioe) {
			ioe.printStackTrace();
		}

		return sb.toString();
	}

}