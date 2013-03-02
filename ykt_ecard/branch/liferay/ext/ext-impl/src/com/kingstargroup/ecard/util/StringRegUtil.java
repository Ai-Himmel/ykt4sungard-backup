package com.kingstargroup.ecard.util;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

import org.apache.log4j.Logger;

/**
 * <br>
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. <br>
 * File name: DateUtil.java<br>
 * Description: <br>
 * Modify History（或Change Log）: <br>
 * 操作类型（创建、修改等） 操作日期 操作者 操作内容简述<br>
 * 创建 2005-10-16 何林青 返回一个日期格式yyyyMMddHHmmss的字符串（当前时间）
 * <p>
 * 
 * @author 何林青
 * @version 1.0
 * @since 1.0
 */
public class StringRegUtil {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(StringRegUtil.class);

	/**
     * 将字符串开头的所有空格替换成指定的字符
     * 在JSP中经常用到把字符串开头的n个空格替换成n个&nbsp;字符
     * 就可以使用此函数调用示例
     * replaceStartsWithSpace("    中国    湖南    长沙","&nbsp;");结果为“&nbsp;&nbsp;中国    湖南    长沙”
     * @param str String
     * @param sub String
     * @return String
     */
    public static String replaceStartsWithSpace(String str, String sub) {
        String returnStr = "";
        String regEx = "\\S"; //非空格字符
        java.util.regex.Pattern pattern = Pattern.compile(regEx);
        Matcher matcher = pattern.matcher(str);
        matcher.find();
        int start = matcher.start(); //非空格开始的位置
        for (int i = 0; i < start; i++) {
            returnStr = returnStr + sub;
        }
        returnStr = returnStr + str.substring(start);
        return returnStr;
    }


	
}
