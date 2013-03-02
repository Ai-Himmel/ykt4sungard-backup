/**
 * 
 */
package com.kingstargroup.ecard.util;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: TypeMappingUtil.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-21  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class TypeMappingUtil {	
	public static String[] getPortletURLInfo(String type) {
		if (type.equals(EcardConstants.INFORMATION_NEWS_TYPE)) {
			return new String[]{"ecardnews", "/ext/ecardhitecardnewsview"};
		} else if (type.equals(EcardConstants.INFORMATION_DISTRIBUTION_TYPE)) {			
			return new String[]{"distributionmap", "/ext/distributionview"};
		} else if (type.equals(EcardConstants.INFORMATION_ABOUT_TYPE)) {
			return new String[]{"ecardabout", "/ext/ecardaboutview"};
		} else if(type.equals(EcardConstants.INFORMATION_SERVICEINFO_TYPE)){
			return new String[]{"ecardservice", "/ext/ecardserviceview"};
		}else if (type.equals(EcardConstants.INFORMATION_RULE_TYPE)) {
			return new String[]{"ecardrule", "/ext/ecardruleview"};
		} else if (type.equals(EcardConstants.INFORMATION_TUTORIAL_TYPE)) {
			return new String[]{"ecardtutorial", "/ext/ecardtutorialview"};
		} else if (type.equals(EcardConstants.INFORMATION_CARDLIST_TYPE)) {
			return new String[]{"ecardlist", "/ext/ecardlistview"};
		} else if (type.equals(EcardConstants.INFORMATION_DOCUMENT_TYPE)) {
			return new String[]{"ecarddoc", "/ext/ecardfiledownload"};
		} else if (type.indexOf(EcardConstants.INFORMATION_FAQ_TYPE + ".") == 0) {
			return new String[]{"ecardfaq", "/ext/ecardfaqview"};
		}
		return new String[]{"", ""};
	}
}
