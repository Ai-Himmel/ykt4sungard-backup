package org.king.util;

import org.apache.commons.codec.digest.DigestUtils;
import org.king.common.Constant;

import java.io.UnsupportedEncodingException;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class EncryptUtil {
    public static String encrypt(String inputText) {
        String encryptText = null;
        try {
            MessageDigest m = MessageDigest.getInstance(Constant.ENCRYPT_TYPE);
            m.update(inputText.getBytes("UTF8"));
            byte s[] = m.digest();
            return hex(s);
        } catch (NoSuchAlgorithmException e) {
            e.printStackTrace();
        } catch (UnsupportedEncodingException e) {
            e.printStackTrace();
        }
        return encryptText;
    }

    /**
     * 返回十六进制字符串
     *
     * @param arr .
     * @return .
     */
    private static String hex(byte[] arr) {
        StringBuffer sb = new StringBuffer();
        for (int i = 0; i < arr.length; ++i) {
            sb.append(Integer.toHexString((arr[i] & 0xFF) | 0x100).substring(1, 3));
        }
        return sb.toString();
    }

    public static String getJJLinkMD5String(String clientIp, long time) {
        String returnValue = "";
        String inputStr = DigestUtils.md5Hex((new StringBuilder()).append(clientIp).append(time).toString());
        int inputLength = inputStr.length();
        if (inputLength > 0) {
            StringBuilder sb = new StringBuilder(inputLength);
            for (int index = inputLength - 1; index >= 0; index--)
                sb.append(inputStr.charAt(index));

            returnValue = sb.toString();
        }
        return returnValue;
    }
}
