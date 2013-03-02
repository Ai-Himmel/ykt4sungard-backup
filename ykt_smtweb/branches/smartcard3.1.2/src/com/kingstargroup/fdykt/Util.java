package com.kingstargroup.fdykt;

import javax.crypto.Cipher;
import javax.crypto.SecretKey;
import javax.crypto.spec.SecretKeySpec;

public class Util {
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

    public static String DESEnc(String s) throws Exception {
        byte[] key = {'1', '2', '3', '4', '5', '6', '7', '8'};
        byte[] clearText = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
        byte[] bytes = s.getBytes();
        byte[] cipherText;
        SecretKey desKey = new SecretKeySpec(key, "DES");
        Cipher desCipher;
        //			Create the cipher
        desCipher = Cipher.getInstance("DES/ECB/NoPadding");
        //	   Initialize the cipher for encryption
        desCipher.init(Cipher.ENCRYPT_MODE, desKey);
        for (int i = 0;
             i <
             (bytes.length < clearText.length ? bytes.length : clearText.length);
             i++) {
            clearText[i] = bytes[i];
        }
        cipherText = desCipher.doFinal(clearText);
        String ciphered = "";
        for (int i = 0; i < cipherText.length; i++)
            ciphered += toHEX(cipherText[i]);
        return ciphered;
    }
    
    public static String ZHDesEnc(byte[] pwd) throws Exception{
    	 byte[] key = {'0', '0', '0', '0', '0', '0', '0', '0'};
    	 byte[] clearText = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
    	 byte[] cipherText;
         SecretKey desKey = new SecretKeySpec(key, "DES");
         Cipher desCipher;
         //			Create the cipher
         desCipher = Cipher.getInstance("DES/ECB/NoPadding");
         //	   Initialize the cipher for encryption
         desCipher.init(Cipher.ENCRYPT_MODE, desKey);
         for (int i = 0;
              i <
              (pwd.length < clearText.length ? pwd.length : clearText.length);
              i++) {
             clearText[i] = pwd[i];
         }
         cipherText = desCipher.doFinal(clearText);
         String ciphered = "";
         for (int i = 0; i < cipherText.length; i++)
             ciphered += toHEX(cipherText[i]);
         return ciphered;
    }

}
