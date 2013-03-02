package com.kingstargroup.ecard.util;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.log4j.Logger;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: DateUtil.java<br>
 * Description: <br>
 * Modify History����Change Log��: <br>
 * �������ͣ��������޸ĵȣ� �������� ������ �������ݼ���<br>
 * ���� 2005-10-16 ������ ����һ�����ڸ�ʽyyyyMMddHHmmss���ַ�������ǰʱ�䣩
 * <p>
 * 
 * @author ������
 * @version 1.0
 * @since 1.0
 */
public class StringRegUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(StringRegUtil.class);

	/**
     * ���ַ�����ͷ�����пո��滻��ָ�����ַ�
     * ��JSP�о����õ����ַ�����ͷ��n���ո��滻��n��&nbsp;�ַ�
     * �Ϳ���ʹ�ô˺�������ʾ��
     * replaceStartsWithSpace("    �й�    ����    ��ɳ","&nbsp;");���Ϊ��&nbsp;&nbsp;�й�    ����    ��ɳ��
     * @param str String
     * @param sub String
     * @return String
     */
    public static String replaceStartsWithSpace(String str, String sub) {
        String returnStr = "";
        String regEx = "\\S"; //�ǿո��ַ�
        java.util.regex.Pattern pattern = Pattern.compile(regEx);
        Matcher matcher = pattern.matcher(str);
        matcher.find();
        int start = matcher.start(); //�ǿո�ʼ��λ��
        for (int i = 0; i < start; i++) {
            returnStr = returnStr + sub;
        }
        returnStr = returnStr + str.substring(start);
        return returnStr;
    }


	
}
