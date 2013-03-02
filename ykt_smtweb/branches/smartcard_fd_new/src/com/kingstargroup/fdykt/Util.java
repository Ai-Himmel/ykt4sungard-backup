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
    
    
    
    public static String DES(String s,String pinKey) throws Exception {
    	byte[] pkey = {-108,-39,-87,-6,-45,-71,-64,-51};
        byte[] key = {pkey[0],pkey[1],pkey[2],pkey[3],pkey[4],pkey[5],pkey[6],pkey[7]};
        byte[] clearText = {'\0', '\0', '\0', '\0', '\0', '\0', '\0', '\0'};
        byte[] bytes = s.getBytes();
        byte[] cipherText;
        SecretKey desKey = new SecretKeySpec(key, "DES");
        Cipher desCipher;
        desCipher = Cipher.getInstance("DES/ECB/NoPadding");
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
        return ciphered ;
    }
    public  static void  main(String[] arg){
    	try{
    	
    	System.out.print(Util.DESEnc("121212"));
       }catch(Exception e){
       }
    }
}
