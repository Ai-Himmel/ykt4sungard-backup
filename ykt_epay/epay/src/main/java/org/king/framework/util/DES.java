package org.king.framework.util;


import org.apache.commons.lang.StringUtils;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.SecretKeyFactory;
import javax.crypto.spec.DESKeySpec;
import javax.crypto.spec.SecretKeySpec;
import java.text.MessageFormat;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

public class DES {
    private static byte[] key = {'1', '2', '3', '4', '5', '6', '7', '8'};

    public static String toHEX(byte b) {
        int i = b & 0X00FF;
        char hi, low;
        if (i / 16 < 10)
            hi = (char) ('0' + i / 16);
        else
            hi = (char) ('A' + i / 16 - 10);
        if (i % 16 < 10)
            low = (char) ('0' + i % 16);
        else
            low = (char) ('A' + i % 16 - 10);
        return hi + "" + low;

    }

    public static byte[] hexStr2ByteArr(String strIn) throws Exception {
        byte[] arrB = strIn.getBytes();
        int iLen = arrB.length;
        // 两个字符表示一个字节，所以字节数组长度是字符串长度除以2
        byte[] arrOut = new byte[iLen / 2];
        for (int i = 0; i < iLen; i = i + 2) {
            String strTmp = new String(arrB, i, 2);
            arrOut[i / 2] = (byte) Integer.parseInt(strTmp, 16);
        }
        return arrOut;
    }

    public static String DESEnc(String s) throws Exception {
        byte[] clearText = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
        byte[] bytes = s.getBytes();
        byte[] cipherText;
        SecretKey desKey = new SecretKeySpec(key, "DES");
        Cipher desCipher;
        //			Create the cipher
        desCipher = Cipher.getInstance("DES/ECB/NoPadding");
        //desCipher = Cipher.getInstance("DES/ECB/PKCS5Padding");
        //	   Initialize the cipher for encryption
        desCipher.init(Cipher.ENCRYPT_MODE, desKey);
        for (int i = 0; i < (bytes.length < clearText.length ? bytes.length : clearText.length); i++) {
            clearText[i] = bytes[i];
        }
        cipherText = desCipher.doFinal(clearText);

        String ciphered = "";
        for (int i = 0; i < cipherText.length; i++)
            ciphered += toHEX(cipherText[i]);
        return ciphered;
    }

    public static String DESDec(String pwd) throws Exception {
        DESKeySpec dks = new DESKeySpec(key);
        SecretKeyFactory keyFactory = SecretKeyFactory.getInstance("DES");
        SecretKey secretKey = keyFactory.generateSecret(dks);
        Cipher cipher = Cipher.getInstance("DES/ECB/NoPadding");
        cipher.init(Cipher.DECRYPT_MODE, secretKey);
        byte[] cipherText = cipher.doFinal(hexStr2ByteArr(pwd));
        int i = 0;
        for (; i < cipherText.length; i++) {
            if (cipherText[i] == 0) {
                break;
            }
        }
        return new String(cipherText, 0, i);
    }

    public static String format(String src) {
        String dist = "######";
        try {
            MessageFormat format = new MessageFormat("{0,number,#.##}");
            if (StringUtils.isNotBlank(src)) {
                src = src.trim();
                Object[] objs = {Double.valueOf(src)};
                dist = format.format(objs);
            }
        } catch (Exception e) {
            e.printStackTrace();
        }
        return dist;
    }

    public static String[] getJJLinkStatus(String tag, String responseString) {
        String returnValue[] = new String[2];
        String regex = "<" + tag + ">(.*)</" + tag + ">";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(responseString);
        while (matcher.find()) {
            returnValue[0] = matcher.group(1);
        }

        return returnValue;
    }

    /**
     * A algorithm base on DES, you can use your own key to encrypt the password
     * the length of the key and password should not be greater than 8
     *
     * @param key      secret key which is used to encrypt password
     * @param password original password
     * @return encrypted password
     * @throws Exception .
     */
    public static String DESEnc(String key, String password) throws Exception {
        byte[] clearText = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
        byte[] bytes = password.getBytes();
        byte[] cipherText;
        byte[] keyText = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
        byte[] temp = key.getBytes();
        for (int i = 0; i < (keyText.length < temp.length ? keyText.length : temp.length); i++) {
            keyText[i] = temp[i];
        }
        SecretKey desKey = new SecretKeySpec(keyText, "DES");
        Cipher desCipher;
        //Create the cipher
        desCipher = Cipher.getInstance("DES/ECB/NoPadding");
        //Initialize the cipher for encryption
        desCipher.init(Cipher.ENCRYPT_MODE, desKey);
        for (int i = 0; i < (bytes.length < clearText.length ? bytes.length : clearText.length); i++) {
            clearText[i] = bytes[i];
        }
        cipherText = desCipher.doFinal(clearText);

        String ciphered = "";
        for (int i = 0; i < cipherText.length; i++)
            ciphered += toHEX(cipherText[i]);
        return ciphered;
    }

    public static void main(String[] args) throws Exception {
        System.out.println(DESEnc("666666"));
        System.out.println(DESDec("BED3FB28576F2BB0"));
        System.out.println(DESDec("642D7C8EB2C8E658"));
        System.out.println(DESEnc("system", "111111"));
    }
}
