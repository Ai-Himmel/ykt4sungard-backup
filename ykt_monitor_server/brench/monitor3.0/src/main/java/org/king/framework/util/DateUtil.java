package org.king.framework.util;

import java.text.ParseException;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Date;
import java.util.Locale;
import java.util.MissingResourceException;
import java.util.ResourceBundle;
import org.king.framework.Constants;
import org.springframework.context.i18n.LocaleContextHolder;

public class DateUtil
{
  private static String defaultDatePattern = "yyyy-MM-dd";

  public static String getDatePattern()
  {
    return defaultDatePattern;
  }

  public static String getToday()
  {
    Date today = new Date();
    return format(today);
  }

  public static String format(Date date)
  {
    return format(date, getDatePattern());
  }

  public static String format(Date date, String pattern)
  {
    String returnValue = "";

    if (date != null) {
      SimpleDateFormat df = new SimpleDateFormat(pattern);
      returnValue = df.format(date);
    }

    return returnValue;
  }

  public static Date parse(String strDate)
  {
    return parse(strDate, getDatePattern());
  }

  public static Date parse(String strDate, String pattern)
  {
    try
    {
      SimpleDateFormat df = new SimpleDateFormat(pattern);
      return df.parse(strDate);
    } catch (ParseException e) {
      e.printStackTrace();
    }return null;
  }

  public static Date addMonth(Date date, int n)
  {
    Calendar cal = Calendar.getInstance();
    cal.setTime(date);
    cal.add(2, n);
    return cal.getTime();
  }

  static
  {
    try
    {
      Locale locale = LocaleContextHolder.getLocale();
      defaultDatePattern = ResourceBundle.getBundle(Constants.MESSAGE_BUNDLE_KEY, locale).getString("date.default_format");
    }
    catch (MissingResourceException mse)
    {
    }
  }
}