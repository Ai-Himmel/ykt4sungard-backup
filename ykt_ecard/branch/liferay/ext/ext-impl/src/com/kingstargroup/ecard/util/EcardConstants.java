/**
 * 
 */
package com.kingstargroup.ecard.util;

import java.util.ArrayList;
import java.util.List;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.util.PropsUtil;


/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.
 * File name: EcardConstants.java
 * Description: һ��ͨ�ۺϲ�ѯ�еĳ���������
 * Modify History: 
 * ��������   ������   ����ʱ��     ��������
 * ===================================
 *  ����    Xiao Qi  2005-9-2  
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */
public class EcardConstants {
	
	/**
	 * һ��ͨ��ͨ�û�����
	 */
	public final static String GENERAL_YKT_GROUP_NAME = "YKT General Group";
	
	/**
	 * һ��ͨ����Ա�û�����
	 */
	public final static String ADMIN_YKT_GROUP_NAME = "YKT Admin Group";
	
	/**
	 * Ĭ�Ͻ������С
	 */
	public final static int DEFAULT_RESULT_SIZE = Integer.parseInt(PropsUtil.get("ecard.result.defaultsize"));
	
	public final static int HOT_INFORMATION_INTERVAL = Integer.parseInt(PropsUtil.get("ecard.hotinfo.interval"));
		
	public final static int LIST_MORE_SIZE = Integer.parseInt(PropsUtil.get("ecard.result.listmoresize"));
	
	public final static int ADMIN_SIZE = Integer.parseInt(PropsUtil.get("ecard.result.adminsize"));
	
	public final static int MAX_RESULT_SIZE = Integer.parseInt(PropsUtil.get("ecard.result.maxsize"));
	
	/**
	 * ������Ϣ��Ӧ����ֵ
	 */
	public final static String INFORMATION_NEWS_TYPE = "0";
	
	public final static String INFORMATION_RULE_TYPE = "1";
	
	/**
	 * �ĵ����ض�Ӧ����ֵ
	 */
	public final static String INFORMATION_DOCUMENT_TYPE = "2";
	
	/**
	 * �Զ��豸�ֲ�ͼ��Ӧ��Ϣ����ֵ
	 */
	public final static String INFORMATION_DISTRIBUTION_TYPE = "3";
	
	/**
	 * FAQ��Ӧ��Ϣ����ֵ
	 */
	public final static String INFORMATION_FAQ_TYPE = "4";
	/**
	 * ��������Ӧ��Ϣ����ֵ
	 */
	public final static String INFORMATION_CARDLIST_TYPE = "5";
	
	/**
	 * ����ָ�϶�Ӧ��Ϣ����ֵ
	 */
	public final static String INFORMATION_TUTORIAL_TYPE = "7";
	
	/**
	 * ϵͳ����Ӧ��Ϣ����ֵ
	 */
	public final static String INFORMATION_ABOUT_TYPE = "8";
	
	/**
	 * ������Ϣ��Ӧ��Ϣ����ֵ
	 */
	public final static String INFORMATION_SERVICEINFO_TYPE = "9";
	/**
	 * �쿨���̶�Ӧ��Ϣ����ֵ
	 */
	
	public final static String INFORMATION_CARDPROCESS_TYPE = "10";
	
	/**
	 * 
	 */
	public final static String INFORMATION_LOSTFOUND_TYPE = "11";
	
	/**
	 * �ĵ��ϴ����߶�
	 */
	public final static int DOC_MAX_SIZE = Integer.parseInt(PropsUtil.get("info.upload.document.maxsize"));
	
	/**
	 * ͼƬ�ϴ����߶�
	 */
	public final static int IMAGE_MAX_SIZE = Integer.parseInt(PropsUtil.get("info.upload.image.maxsize"));
	
	/**
	 * �����ϴ����ļ��б�
	 */
	public final static List DOC_EXTENSION_LIST = new ArrayList();
	
	public final static List IMAGE_EXTENSION_LIST = new ArrayList();
	
	public final static String DELIMITER = ",";
	
	/**
	 * �ϴ��ļ���ŵĸ�Ŀ¼
	 */
	public final static String DOC_ROOT = PropsUtil.get("info.upload.document.dir");
	
	public final static String IMAGE_ROOT = PropsUtil.get("info.upload.image.dir");
	
	public final static String CACHE_DIR = PropsUtil.get("picdealy.cache.dir");
	/**
	 * �ϴ����Ͷ���
	 */
	public final static int IMAGE_TYPE = 1;
	public final static int DOCUMENT_TYPE = 0;
	
	public final static int CARD_STATUS_DIC_NO = 17;
	
	public final static int CARD_TYPE_DIC_NO = 18;
	
	public final static int CONSUME_TYPE_DIC_NO = 21;
	
	public final static String POSTPONE_STATUS_UNACCEPTED = "0";
	
	public final static String POSTPONE_STATUS_ACCEPTED = "1";
	
	public final static String POSTPONE_STATUS_REJECTED = "2";
	/**
	 * ������Ϣ�ַ���
	 */
	public final static String CHOOSE_DEL_CONTENT = "choosedelcontent";
	public final static String DELETE_INFO_SUCCEED = "deleteinfosucceed";
	public final static String DELETE_INFO_FAILED = "deleteinfofailed";
	public final static String RESET_INFO_FAILED = "resetinfofailed";
	public final static String CHOOSE_PROCESS_CONTENT = "chooseprocesscontent";
	public final static String PROCESS_DELAY_SUCCESS = "processdelaysuccess";
	public final static String ADD_INFO_SUCCEED = "addinfosucceed";
	public final static String EDIT_INFO_SUCCESS = "editinfosuccess";
	public final static String EDIT_PASSWORD_SUCCEED = "editpasswordsucced";
	public final static String REPLY_MSG_SUCCESS = "replymsgsuccess";
	
	public final static String USER_NOT_SELECTEDE = "user_not_selected";
	public final static String SHOP_BIND_SUCCESS = "shop_bind_success";
	public final static String SHOP_BIND_FAILUE = "shop_bind_failue";
	public final static String ERROR_EXIST = "error_exist";
	public final static String TOTSAVING_ERROR_EXIST = "totsaving_error_exist";
	public final static String SAVINGSORT_ERROR_EXIST = "savingsort_error_exist";
	public final static String CONSUMEBYPOS_ERROR_EXIST = "consumebypos_error_exist";
	public final static String ALLSHOPACCOUNT_ERROR_EXIST = "allshopaccount_error_exist";
	public final static String ONESHOPACCOUNT_ERROR_EXIST = "oneshopaccount_error_exist";
	public final static String SHOPCOMPARE_ERROR_EXIST = "shopcompare_error_exist";
	public final static String ALLACCOUNT_ERROR_EXIST = "allaccount_error_exist";
	public final static String ALLCONSUME_ERROR_EXIST = "allconsume_error_exist";
	public final static String DEPTACCOUNT_ERROR_EXIST = "deptaccount_error_exist";
	public final static String DEPTCONSUME_ERROR_EXIST = "deptconsume_error_exist";
	public final static String PHOTO_ERROR_EXIST = "photo_error_exist";
	public final static String TRANSFER_ERROR_EXIST = "transfer_error_exist";
	public final static String DEVUSERATE_ERROR_EXIST = "devuserate_error_exist";
	public final static String SPECIALLIST_ERROR_EXIST = "speciallist_error_exist";
	public final static String CARDUSE_ERROR_EXIST = "carduse_error_exist";
	public final static String CARDOPENLOSEBACK_ERROR_EXIST = "cardopenloseback_error_exist";
	public final static String QUERYACCOUNTDTL_ERROR_EXIST ="queryaccountdtl_error_exist";
	public final static String CARDUSEBYDEPT_ERROR_EXIST ="cardusebydept_error_exist";
	public final static String SHOPID_NOT_SELECTED = "shopid_not_select"; 
	public final static String DATE_NOT_SELECTED = "date_not_selected";
	public final static String TIME_PERIOD_TOO_LONG = "time_period_too_long";
	
	public final static String INFO_NOT_ENOUGH_CUSTOMER = "info_not_enough_customer";
	public final static String INFO_NOT_ENOUGH_STUEMPNO = "info_not_enough_stuempno";
	public final static String INFO_NOT_ENOUGH_IDCARD = "info_not_enough_idcard";
	
	public final static String NET_TRANS_ERROR_OCCURANCE = "net_trans_error_occurance";
	
	public final static String LOSECARD_NOLOGIN = "losecard_nologin";
	public final static String CARD_DESTORY = "card_destory";
	public final static String LOSECARD_SAVESUCC = "losecard_savesucc";
	public final static String LOSECARD_NOCARD = "losecard_nocard";
	public final static String LOSECARD_RECORDEXIST = "losecard_recordexist";
	public final static String LOSECARD_NOTSAMECARD = "losecard_notsamecard";
	public final static String LOSECARD_INFONOTSAME = "losecard_infonotsame";
	public final static String LOSECARD_CARDSTATUSERROR = "losecard_cardstatuserror";
	public final static String LOSECARD_GETCARDSUCC = "losecard_getcardsucc";
	public final static String LOSECARD_DATAFORMATERROR = "losecard_dateformaterror";
	public final static String LOSECARD_DATACOMERROR = "losecard_datecomderror";
	
	public final static String DETAIL_QUERY_DAYS_NUM = "detail_query_days_num";
	public final static String DETAIL_QUERY_TYPE_SELECT = "detail_query_type_select";


	/**
	 * �õ���ʧ�����²�����ʽ����Ҫ��������ϵͳ����ID
	 */
	public final static int REAPPLY_DAYS_ID = 9;
	
	/**
	 * ��ע����ʶ
	 */
	public final static String CARD_WRITE_OFF_STATUS = "2000";
	
	/**
	 * ����ʧ��ʶ
	 */
	public final static char CARD_LOST_FLAG = '1';
	
	public final static String LINE_SEPARATOR = "\r\n";
	
	/**
	 * ���Իظ�״̬
	 */
	public final static String MSG_NO_REPLY = "0";
	public final static String MSG_REPLIED = "1";
	
	public final static String WEB_COUNTER_NAME = "kingstargroup.webcounter";
	
	/**
	 * POS���׵ļ�¼״̬1:δ����2-����ʧ��3-�ɹ�
	 */
	public final static int POS_STATUS_UNRACODE = 1;
	public final static int POS_STATUS_FAIL = 2;
	public final static int POS_STATUS_SUCCESS = 3;
	
	/*
	 * ������Ϣ����
	 */
	public final static boolean INFO_CACHEABLE = GetterUtil.getBoolean(PropsUtil.get("info.cacheable"));
	public final static int INFO_CACHE_MAXSIZE = GetterUtil.getInteger(PropsUtil.get("info.cache.maxsize"));
	
	public final static int HIT_INFO_SIZE = GetterUtil.getInteger(PropsUtil.get("hitinfo.result.size"));
	
	
}
