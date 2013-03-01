/*
* @(#)Utility.java
*
* Copyright (c) 2003 DCIVision Ltd
* All rights reserved.
*
* This software is the confidential and proprietary information of DCIVision
* Ltd ("Confidential Information").  You shall not disclose such Confidential
* Information and shall use it only in accordance with the terms of the license
* agreement you entered into with DCIVision Ltd.
 */
package com.kingstargroup.advquery.util;

import java.lang.reflect.InvocationTargetException;
import java.math.BigDecimal;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.Calendar;
import java.util.Collection;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.beanutils.PropertyUtils;


/**
 * Utility.java
 * Common utility functions which used in systems.
 * @author Rollo Chan
 * @version $Revision: 1.2 $
 * @company DCIVision Limited
 * @creation date   24/06/2003
 */

public class Utility {

    public static final String REVISION = "$Revision: 1.2 $";

    private Utility() {
    }

    /**
     * isEmpty
     * Test to see whether input string is empty.
     * @param str A String
     * @return True if it is empty; false if it is not.
     */
    public static boolean isEmpty(String str) {
        return (str == null || str.length() == 0);
    }

    /**
     * isEmpty
     * Test to see whether input string is empty.
     * @param str A String
     * @return True if it is empty; false if it is not.
     */
    public static boolean isEmpty(Object[] array) {
        return (array == null || array.length == 0);
    }

    /**
     * isEmpty
     * Test to see whether input is empty.
     * @param StringArray A array
     * @return True if it is empty; false if it is not.
     */
    public static boolean isEmpty(String[] array) {
        return (array == null || array.length == 0);
    }

    /**
     * isEmpty
     * Test to see whether input is representing a NULL value.
     * @param val An Object
     * @return True if it represents NULL; false if it is not.
     */
    public static boolean isEmpty(Object val) {
        if(val instanceof String)
        {
            String value = (String)val;
            return isEmpty(value);
        }
        return (val == null);
    }

    /**
     * isEmpty
     * Test to see whether input is empty.
     * @param list A List
     * @return True if it is empty; false if it is not.
     */
    public static boolean isEmpty(java.util.List list) {
        return (list == null || list.size() == 0);
    }

    /**
     * getPropertyList
     * Extract a list of properties of javabeans thro. using reflection
     * @param col      the collection of javabeans to be extract
     * @param property the property value of the javabean to be extracted
     * @return A list of extracted properties
     * @throws IllegalAccessException    if error found in PropertyUtil
     * @throws InvocationTargetException if error found in PropertyUtil
     * @throws NoSuchMethodException     if no such property
     */
    public static java.util.List getPropertyList(Collection col, String property) throws IllegalAccessException, InvocationTargetException, NoSuchMethodException {
        List propertyList = new ArrayList();
        if (col == null) return propertyList;
        Iterator itemIter = col.iterator();
        while (itemIter.hasNext()) {
            Object item = itemIter.next();
            if (item != null)
                propertyList.add(PropertyUtils.getProperty(item, property));
        }
        return propertyList;//((Object[]) values.toArray(new Object[values.size()]));
    }

    /**
     * getPropertyArray
     * Retrive an array of object base on the collection thro. reflection
     * e.g groupList is a ArrayList of Group, then getArrayProperty(groupList,"ID") will return an List of ID values.
     * @param col         The collection of javabeans to be extract
     * @param propertyKey The property value key of the javabean to be extracted
     * @return Properties in array format
     * @throws IllegalAccessException    If error found in PropertyUtil
     * @throws InvocationTargetException If error found in PropertyUtil
     * @throws NoSuchMethodException     If no such property
     */
    public static Object[] getPropertyArray(Collection value, String propertyKey, Object[] target) throws IllegalAccessException, InvocationTargetException, NoSuchMethodException {
        return getPropertyList(value, propertyKey).toArray(target);//((Object[]) values.toArray(new Object[values.size()]));
    }

    /**
     * getPropertyMap
     * Retrive an map of object base on the collection thro. reflection
     * e.g groupList is a ArrayList of Group, then getArrayProperty(groupList,"ID") will return an List of ID values.
     * @param col         The collection of javabeans to be extract
     * @param propertyKey The property value key of the javabean to be extracted
     * @return Properties in map format
     * @throws IllegalAccessException    If error found in PropertyUtil
     * @throws InvocationTargetException If error found in PropertyUtil
     * @throws NoSuchMethodException     If no such property
     */
    public static java.util.Map getPropertyMap(Collection col, String propertyKey) throws IllegalAccessException, InvocationTargetException, NoSuchMethodException {
        java.util.HashMap values = new java.util.HashMap();
        if (col != null) {
            Iterator itemIter = (col).iterator();
            while (itemIter.hasNext()) {
                Object value = itemIter.next();
                if (value != null) {
                    Object key = PropertyUtils.getProperty(value, propertyKey);
                    if (key != null) values.put(key, value);
                }
            }
        }
        return values;
    }

    /**
     * getPropertyMapList
     * Retrive an map of arraylist base on the collection thro. reflection
     * e.g groupList is a ArrayList of Group, then getPropertyMapList(groupList,"ID") will return an Map of ArrayList where which list contains objects with the same key.
     * @param col         The collection of javabeans to be extract
     * @param propertyKey The property value key of the javabean to be extracted
     * @return Properties in map format with arraylist as item
     * @throws IllegalAccessException    If error found in PropertyUtil
     * @throws InvocationTargetException If error found in PropertyUtil
     * @throws NoSuchMethodException     If no such property
     */
    public static java.util.Map getPropertyMapList(Collection col, String propertyKey) throws IllegalAccessException, InvocationTargetException, NoSuchMethodException {
        java.util.HashMap values = new java.util.HashMap();
        if (col != null) {
            Iterator itemIter = (col).iterator();
            while (itemIter.hasNext()) {
                Object value = itemIter.next();
                if (value != null) {
                    Object key = PropertyUtils.getProperty(value, propertyKey);
                    if (key != null) {
                        List objList = (List) values.get(key);
                        if (objList == null) objList = new ArrayList();
                        objList.add(value);
                        values.put(key, objList);
                    }
                }
            }
        }
        return values;
    }

    /**
     * Convert an Object Array into String Array by calling obj.toString()
     * @param obj The object array.
     * @return The String Array representing that object array
     */
    public static String[] getStringArray(Object[] obj) {
        if (obj == null) return null;

        String[] strArray = new String[obj.length];
        for (int i = 0; i < obj.length; i++) {
            strArray[i] = obj[i].toString();
        }
        return strArray;
    }

    /**
     * @param String: Query
     * @return String[]: Array of logical param
     */
    public static String[] getLogicalString(String query) {
        String andString[] = query.toUpperCase().split("\\s(AND|\\+)\\s");
        String orString[] = query.toUpperCase().split("\\sOR\\s");
        String notString[] = query.toUpperCase().split("\\s(\\-|NOT)\\s");
        String resultString[] = null;
        int count = 0;
        if (andString.length > 1) {
            for (int i = 0; i < andString.length; i++) {
                andString[i] = "AND";
            }
            resultString = andString;
        } else if (orString.length > 1) {
            for (int i = 0; i < orString.length; i++) {
                orString[i] = "OR";
            }
            resultString = orString;
        } else if (notString.length > 1) {
            for (int i = 0; i < notString.length; i++) {
                notString[i] = "NOT";
            }
            resultString = notString;
        }

        return resultString;
    }

    /**
     * splitLogicalString
     * @param query Query
     * @return String[]    result splited array
     */
    public static String[] splitLogicalString(String query) {
        String andString[] = query.toUpperCase().split("\\s(AND|\\+)\\s");
        String orString[] = query.toUpperCase().split("\\sOR\\s");
        String notString[] = query.toUpperCase().split("\\s(\\-|NOT)\\s");
        String resultString[] = null;
        HashMap hm = new HashMap();
        if (andString.length > 1) {
            resultString = andString;
        } else if (orString.length > 1) {
            resultString = orString;
        } else if (notString.length > 1) {
            resultString = notString;
        } else {
            resultString = new String[1];
            resultString[0] = query;
        }
        return resultString;
    }

    /**
     * getList
     * @param ary The object array.
     * @return The list contains all the object array elements.
     */
    public static List getList(Object[] ary) {
        if (ary == null) {
            return (null);
        }
        List result = new ArrayList();
        for (int i = 0; i < ary.length; i++) {
            result.add(ary[i]);
        }
        return (result);
    }

    /**
     * getStringArray
     * @param ary The object array.
     * @return The list contains all the object array elements.
     */
    public static String[] getStringArray(List list) {
        if (list == null) {
            return (null);
        }
        String[] result = new String[list.size()];
        for (int i = 0; i < list.size(); i++) {
            try {
                result[i] = (String) list.get(i);
            } catch (ClassCastException ce) {
                result[i] = ((Integer) list.get(i)).toString();
            }
        }
        return (result);
    }

    /**
     * Returns Calendar converted from Timestamp.
     * @param inTime Source timestamp which to be converted.
     * @return Calendar object which converted from input.
     */
    public static java.util.Calendar timestampToCalendar(java.sql.Timestamp inTime) {
        if (inTime == null) {
            return (null);
        }
        java.util.Calendar cal = java.util.Calendar.getInstance();
        cal.setTime(inTime);
        return (cal);
    }

    /**
     * Returns Timestamp converted from Calendar.
     * @param inCal Source calendar which to be converted.
     * @return Timestamp object which converted from input.
     */
    public static java.sql.Timestamp calendarToTimestamp(java.util.Calendar inCal) {
        if (inCal == null) {
            return (null);
        }
        java.sql.Timestamp time = new java.sql.Timestamp(inCal.getTime().getTime());
        return (time);
    }

    /**
     * addYear - Returns the timestamp after adding certain amount of Year.
     * @param src Source timestamp.
     * @param val Number of hours going to add, can be negative number.
     * @return Timestamp after adding certain amount of hours.
     */
    public static java.sql.Timestamp addYear(java.sql.Timestamp src, int val) {
        java.util.Calendar tmpCal = timestampToCalendar(src);
        if (tmpCal == null) {
            return (null);
        }
        tmpCal.add(java.util.Calendar.YEAR, val);
        return (calendarToTimestamp(tmpCal));
    }

    /**
     * addMonth - Returns the timestamp after adding certain amount of Month.
     * @param src Source timestamp.
     * @param val Number of hours going to add, can be negative number.
     * @return Timestamp after adding certain amount of hours.
     */
    public static java.sql.Timestamp addMonth(java.sql.Timestamp src, int val) {
        java.util.Calendar tmpCal = timestampToCalendar(src);
        if (tmpCal == null) {
            return (null);
        }
        tmpCal.add(java.util.Calendar.MONTH, val);
        return (calendarToTimestamp(tmpCal));
    }

    /**
     * addDay - Returns the timestamp after adding certain amount of day.
     * @param src Source timestamp.
     * @param val Number of hours going to add, can be negative number.
     * @return Timestamp after adding certain amount of hours.
     */
    public static java.sql.Timestamp addDay(java.sql.Timestamp src, int val) {
        java.util.Calendar tmpCal = timestampToCalendar(src);
        if (tmpCal == null) {
            return (null);
        }
        tmpCal.add(java.util.Calendar.DAY_OF_MONTH, val);
        return (calendarToTimestamp(tmpCal));
    }

    /**
     * addHour - Returns the timestamp after adding certain amount of hours.
     * @param src Source timestamp.
     * @param val Number of hours going to add, can be negative number.
     * @return Timestamp after adding certain amount of hours.
     */
    public static java.sql.Timestamp addHour(java.sql.Timestamp src, int val) {
        java.util.Calendar tmpCal = timestampToCalendar(src);
        if (tmpCal == null) {
            return (null);
        }
        tmpCal.add(java.util.Calendar.HOUR_OF_DAY, val);
        return (calendarToTimestamp(tmpCal));
    }

    /**
     * addMinute - Returns the timestamp after adding certain amount of minutes.
     * @param src Source timestamp.
     * @param val Number of hours going to add, can be negative number.
     * @return Timestamp after adding certain amount of hours.
     */
    public static java.sql.Timestamp addMinute(java.sql.Timestamp src, int val) {
        java.util.Calendar tmpCal = timestampToCalendar(src);
        if (tmpCal == null) {
            return (null);
        }
        tmpCal.add(java.util.Calendar.MINUTE, val);
        return (calendarToTimestamp(tmpCal));
    }

    /**
     * Call this function to set the time section of a calendar
     * @param inCalendar
     * @param hr
     * @param min
     * @param sec
     * @param milliSec
     */
    public static void setCalendarTime(Calendar inCalendar, int hr, int min, int sec, int milliSec) {
        if (inCalendar != null) {
            if (hr != -1) {
                inCalendar.set(Calendar.HOUR_OF_DAY, hr);
            }
            if (min != -1) {
                inCalendar.set(Calendar.MINUTE, min);
            }
            if (sec != -1) {
                inCalendar.set(Calendar.SECOND, sec);
            }
            if (milliSec != -1) {
                inCalendar.set(Calendar.MILLISECOND, milliSec);
            }
        }
    }

    /**
     * Call this function to parse the dateString into System Date format
     * @param dateString The date value string
     * @param dateFormat
     * @param min
     * @param sec
     * @param milliSec
     */
    public static java.sql.Timestamp parseDateStringToSystemDate(String dateString, String dateFormat) {
        java.sql.Timestamp tmp = null;
        ;
        // Initial system date parameter
        SimpleDateFormat df = new SimpleDateFormat(dateFormat);
        try {
            Date inDate = df.parse(dateString);
            Calendar calendar = Calendar.getInstance();
            calendar.setTime(inDate);

            tmp = calendarToTimestamp(calendar);
        } catch (Exception e) {
            e.printStackTrace();
        }
        return tmp;
    }

    /**
     * Call this function to round off the second and millisecond of time.
     * @param timestamp The timestamp value to be strip to minutes
     * @return
     */

    public static java.sql.Timestamp stripToMinutes(java.sql.Timestamp timestamp) {
        Calendar cal = Calendar.getInstance();
        cal.setTimeInMillis(timestamp.getTime());
        int day = cal.get(Calendar.DATE);
        int month = cal.get(Calendar.MONTH);
        int year = cal.get(Calendar.YEAR);
        int hour = cal.get(Calendar.HOUR_OF_DAY);
        int time = cal.get(Calendar.MINUTE);

        cal.clear();
        cal.set(year, month, day, hour, time);
        timestamp = new java.sql.Timestamp(cal.getTimeInMillis());
        //System.out.println("the update time stamp:"+timestamp);
        return timestamp;
    }

    static SimpleDateFormat formatter = new SimpleDateFormat("yyyy-MM-dd");

    public static String parseDateToString(Date date) {
        String str = "";
        if (!Utility.isEmpty(date)) {
            str = formatter.format(date);
        }
        return str;
    }

    public static String parseNumberToString(BigDecimal bigDecimal) {
        String str = "";
        if (!Utility.isEmpty(bigDecimal)) {
            str = bigDecimal.toString();
        }
        return str;
    }

    public static String parseNumberToFloat(Float f) {
        String str = "";
        if (!Utility.isEmpty(f)) {
            str = f.toString();
        }
        return str;
    }


    public static String parseIntToString(Integer integer) {
        String str = "";
        if (!Utility.isEmpty(integer)) {
            str = integer.toString();
        }
        return str;
    }

    public static String parseFloatToString(Float loat) {
        String str = "";
        if (!Utility.isEmpty(loat)) {
            str = loat.toString();
        }
        return str;
    }

    public static Date getCurDate() {
        Date date = new Date();
        return date;
    }

    public static String getCurDateStr() {
        Calendar ca = Calendar.getInstance();
        String dateStr = formatter.format(ca.getTime());
        return dateStr;
    }

    public static String parseIntegerToString(Integer integer) {
        String str = "";
        if (!Utility.isEmpty(integer)) {
            str = integer.toString();
        }
        return str;
    }

}