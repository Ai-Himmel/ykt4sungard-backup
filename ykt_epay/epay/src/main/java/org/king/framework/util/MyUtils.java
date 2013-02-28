package org.king.framework.util;

import org.apache.commons.lang.StringUtils;

import java.io.Serializable;
import java.util.Collection;
import java.util.Map;
import java.util.Set;

public class MyUtils extends StringUtils {
    public static boolean isBlank(String str) {
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
    
    public static String toDes(String str){
		try {
			return DES.DESEnc(str);
		} catch (Exception e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
			return null;
		}
    }
}