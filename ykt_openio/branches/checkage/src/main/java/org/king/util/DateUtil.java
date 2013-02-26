package org.king.util;

import org.apache.log4j.Logger;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class DateUtil {
    private static final Logger logger = Logger.getLogger(DateUtil.class);

    private static final DateFormat dateFormat = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

    public static String getNowTime() {
        Date now = new Date();
        return dateFormat.format(now);
    }
}
