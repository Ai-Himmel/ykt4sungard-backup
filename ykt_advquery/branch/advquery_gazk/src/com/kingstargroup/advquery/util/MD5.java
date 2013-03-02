package com.kingstargroup.advquery.util;
import java.security.MessageDigest;

public class MD5 {
    private String inStr;

    private MessageDigest md5;

    /**
     * Constructs the MD5 object and sets the string whose MD5 is to be
     * computed.
     * 
     * @param inStr
     *            the <code>String</code> whose MD5 is to be computed
     */
    public MD5(String inStr) {
        this.inStr = inStr;
        try {
            this.md5 = MessageDigest.getInstance("MD5");
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    /**
     * Computes the MD5 fingerprint of a string.
     * 
     * @return the MD5 digest of the input <code>String</code>
     */
    public String compute() {

        char[] charArray = this.inStr.toCharArray();

        byte[] byteArray = new byte[charArray.length];

        for (int i = 0; i < charArray.length; i++)
            byteArray[i] = (byte) charArray[i];

        byte[] md5Bytes = this.md5.digest(byteArray);

        StringBuffer hexValue = new StringBuffer();

        for (int i = 0; i < md5Bytes.length; i++) {
            int val = ((int) md5Bytes[i]) & 0xff;
            if (val < 16)
                hexValue.append("0");
            hexValue.append(Integer.toHexString(val));
        }
        return hexValue.toString();
    }
    public static void main(String[] arg){
    	MD5 m = new MD5("310102198301231214");
    	
    	System.out.println(m.compute().toUpperCase());
    	
    }
    
}