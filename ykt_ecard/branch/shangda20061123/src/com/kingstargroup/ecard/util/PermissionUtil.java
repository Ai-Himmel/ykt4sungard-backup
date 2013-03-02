/**
 * 
 */
package com.kingstargroup.ecard.util;

import javax.servlet.http.HttpServletRequest;

import com.liferay.portal.service.spring.RoleServiceUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.util.GetterUtil;
import com.liferay.util.StringPool;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: PermissionUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-10-13  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class PermissionUtil {
	public static boolean hasDelayProcess(HttpServletRequest req) {
		
		return true;
	}
	
	public static boolean hasNewsAdmin(HttpServletRequest req) {
		return process(req, NEWS_ADMIN);
	}
	
	public static boolean hasRuleAdmin(HttpServletRequest req) {
		return process(req, RULE_ADMIN);
	}
	
	public static boolean hasMapAdmin(HttpServletRequest req) {
		return process(req, MAP_ADMIN);
	}
	
	public static boolean hasTutorialAdmin(HttpServletRequest req) {
		return process(req, TUTORIAL_ADMIN);
	}
	
	public static boolean hasFAQAdmin(HttpServletRequest req) {
		return process(req, FAQ_ADMIN);
	}
	
	public static boolean hasMsgboardAdmin(HttpServletRequest req) {
		return process(req, MSGBOARD_ADMIN);
	}
	
	public static boolean hasCardTransactionAdmin(HttpServletRequest req) {
		return process(req, CARDTRANSACTION_ADMIN);
	}
	
	public static boolean hasCardlistAdmin(HttpServletRequest req) {
		return process(req, CARDLIST_ADMIN);
	}
	
	public static boolean hasDocumentAdmin(HttpServletRequest req) {
		return process(req, DOCUMENT_ADMIN);
	}
	
	public static boolean hasAdmin(HttpServletRequest req) {
		return process(req, ADMINISTRATOR);
	}
	
	public static boolean hasAboutAdmin(HttpServletRequest req) {
		return process(req, ABOUT_ADMIN);
	}
	
	public static boolean hasHitinfoAdmin(HttpServletRequest req) {
		return process(req, HITINFO_ADMIN);
	}
	
	public static boolean hasServiceinfoAdmin(HttpServletRequest req) {
		return process(req, SERVICEINFO_ADMIN);
	}
	
	/**
	 * Description:判断当前登录用户是否具有传入的角色权限
	 * @param req
	 * @param roleName
	 * @return
	 * Modify History:
	 */
	static boolean process(HttpServletRequest req, String roleName) {
		String userId = getUserId(req);
		if (userId.equals(StringPool.BLANK)) {
			return false;
		}
		try {
			return RoleServiceUtil.hasRole(userId, roleName);
		} catch (Exception ex) {
			return false;
		}
	}
	static String getUserId(HttpServletRequest req) {
		return GetterUtil.get((String)req.getSession().getAttribute(WebKeys.USER_ID), StringPool.BLANK);
	}
	
	public final static String ADMINISTRATOR = "YKT Administrator";
	public final static String NEWS_ADMIN = "YKT News Administrator";
	public final static String RULE_ADMIN = "YKT Rule Administrator";
	public final static String MAP_ADMIN = "YKT Map Administrator";
	public final static String TUTORIAL_ADMIN = "YKT Tutorial Administrator";
	public final static String FAQ_ADMIN = "YKT FAQ Administrator";
	public final static String MSGBOARD_ADMIN = "YKT Msgboard Administrator";
	public final static String CARDTRANSACTION_ADMIN = "YKT Cardtransaction Administrator";
	public final static String CARDLIST_ADMIN = "YKT Cardlist Administrator";
	public final static String DOCUMENT_ADMIN = "YKT Document Administrator";
	public final static String ABOUT_ADMIN = "YKT About Administrator";
	public final static String HITINFO_ADMIN = "YKT Hitinfo Administrator";
	public final static String SERVICEINFO_ADMIN = "YKT Serviceinfo Administrator";

}
