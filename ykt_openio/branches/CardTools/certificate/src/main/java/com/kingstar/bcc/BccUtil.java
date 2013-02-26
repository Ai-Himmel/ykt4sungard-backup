package com.kingstar.bcc;

import java.io.UnsupportedEncodingException;

public class BccUtil {

    public static String getStringFromByte(byte[] inStr) {
        int t = 0;
        for (t = 0; t < inStr.length; t++) {
            if (inStr[t] == 0) {
                break;
            }
        }
        String ret = "";
        try {
            ret = new String(inStr, 0, t, "GBK");
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
            ret = new String(inStr, 0, t);
        }
        return ret;
    }
}

