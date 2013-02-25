package com.sungard.smartcard.util;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * .
 *
 * @author Yiming.You
 * @version v1.00
 * @since 12-2-22
 */
public class DateUtil {

    /**
     * 获得当前时间格式为yyyymmddhh24miss
     *
     * @return 形如：20120222164012
     */
    public static String getCurrentTime() {
        DateFormat dateFormat = new SimpleDateFormat("yyyyMMddHHmmss");
        return dateFormat.format(new Date());
    }
}
