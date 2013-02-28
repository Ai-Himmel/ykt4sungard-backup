package org.king.utils;

import org.apache.log4j.Logger;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Date;

public class DateUtil {
    private static final Logger logger = Logger.getLogger(DateUtil.class);

    private static final DateFormat dateFormat = new SimpleDateFormat("yyyyMMdd");

    private static final DateFormat timeFormat = new SimpleDateFormat("HHmmss");

    public static String getDate(Date date) {
        String result;
        if (date == null) {
            result = dateFormat.format(new Date());
        } else {
            result = dateFormat.format(date);
        }
        return result;
    }

    public static String getTime(Date date) {
        String result;
        if (date == null) {
            result = timeFormat.format(new Date());
        } else {
            result = timeFormat.format(date);
        }
        return result;
    }
}
