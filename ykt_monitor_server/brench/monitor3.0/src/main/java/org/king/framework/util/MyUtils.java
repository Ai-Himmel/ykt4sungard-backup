package org.king.framework.util;

import java.io.Serializable;
import java.util.Collection;
import java.util.Map;
import java.util.Set;

import org.apache.commons.lang.StringUtils;

public class MyUtils extends StringUtils
{
  public static boolean isBlank(String str)
  {
    return (str == null) || (str.trim().length() <= 0);
  }

  public static boolean isBlank(Object[] objs) {
    return (objs == null) || (objs.length <= 0);
  }

  public static boolean isBlank(Collection obj) {
    return (obj == null) || (obj.size() <= 0);
  }

  public static boolean isBlank(Set obj) {
    return (obj == null) || (obj.size() <= 0);
  }

  public static boolean isBlank(Serializable obj) {
    return obj == null;
  }

  public static boolean isBlank(Map obj) {
    return (obj == null) || (obj.size() <= 0);
  }


  public static String toMD5(String str) {
    return MD5.toMD5(str);
  }
}