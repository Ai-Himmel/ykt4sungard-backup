/**
 * 
 */
package com.kingstargroup.conference.common;

import javax.servlet.ServletContext;
import org.apache.struts.Globals;
import org.apache.struts.util.MessageResources;

/**
 * 取得配置参数信息
 * @author Administrator
 *
 */
public class GetProperty {
	public static String getProperties(String property,ServletContext cxt){
		MessageResources msgResources = (MessageResources) cxt.getAttribute(Globals.MESSAGES_KEY);
		return msgResources.getMessage(property);
	}
	public static Boolean getPropertiesB(String property,ServletContext cxt){
		MessageResources msgResources = (MessageResources) cxt.getAttribute(Globals.MESSAGES_KEY);
		return Boolean.valueOf(msgResources.getMessage(property));
	}
}
