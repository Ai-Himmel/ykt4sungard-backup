/**
 * 
 */
package com.kingstargroup.ecard.util;

import java.util.ArrayList;
import java.util.List;

import com.liferay.portal.util.PropsUtil;
import com.liferay.util.GetterUtil;

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
	 * һ��ͨ�̹�������
	 */
	public final static String  TEACHER_WORK_NAME="YKT Teacher Worker";
	
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
	public final static String CHOOSE_PROCESS_CONTENT = "chooseprocesscontent";
	public final static String PROCESS_DELAY_SUCCESS = "processdelaysuccess";
	public final static String ADD_INFO_SUCCEED = "addinfosucceed";
	public final static String EDIT_INFO_SUCCESS = "editinfosuccess";
	public final static String EDIT_PASSWORD_SUCCEED = "editpasswordsucced";
	public final static String REPLY_MSG_SUCCESS = "replymsgsuccess";
	public final static String CHOOSE_MAINTAIN_TYPE ="choosemaintaintype";
	public final static String UPDATE_INFO_SUCCESS="������Ϣ�ɹ�";
	public final static String UPDATE_INFO_FAIL="������Ϣʧ��";
	public final static String MAINTAIN_EMAIL_SERVICE="�ʼ�������";
	public final static String MAINTAIN_EMAIL_SENDADDRESS="������";
	public final static String MAINTAIN_EMAIL_RECEIVEADDRESS="�ռ���";
	public final static String MAINTAIN_SMTP_USER="SMTP�û���"; 
	public final static String MAINTAIN_SMTP_PWD="SMTP����";
	public final static String MAINTAIN_SMTP_TITLE="�ʼ�����";
    public final static String MAINTAIN="�豸����";
	public final static String ADMIN_NO_ANSWER="����Ա�ظ���Ϣ�󣬲ſ��Է�����Ϣ";
	public final static String ISSENDREPORT ="�Ƿ��ڷ��ͱ���";
	public final static String SENDBEGINDATE="���Ϳ�ʼ����";
	public final static String DAYS = "�������";
	public final static String REPORTTITLE="ά��ͳ�Ʊ���";
	
	//public final static String 

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
	
	/*
	 * ������Ϣ����
	 */
	public final static boolean INFO_CACHEABLE = GetterUtil.getBoolean(PropsUtil.get("info.cacheable"));
	public final static int INFO_CACHE_MAXSIZE = GetterUtil.getInteger(PropsUtil.get("info.cache.maxsize"));
	
	public final static int HIT_INFO_SIZE = GetterUtil.getInteger(PropsUtil.get("hitinfo.result.size"));
	/*
	 * �����豸ά����Ϣ
	 */
	public final static String   MAINTAIN_NO="001";
	
}
