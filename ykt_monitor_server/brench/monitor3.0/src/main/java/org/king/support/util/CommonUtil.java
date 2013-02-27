package org.king.support.util;

import org.apache.commons.configuration.PropertiesConfiguration;

public class CommonUtil {
	
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
				.append("</th><th>")
				.append(config.getString("com.kingstar.MonitorSys.DEVICE_NAME"))
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
}
