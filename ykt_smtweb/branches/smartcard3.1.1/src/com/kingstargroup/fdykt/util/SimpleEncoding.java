package com.kingstargroup.fdykt.util;

import java.security.Security;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;
import javax.crypto.SecretKey;


public class SimpleEncoding {

	private static String Algorithm = "DES"; // 定义 加密算法,可用
												// DES,DESede,Blowfish

	static boolean debug = false;

	static {
		Security.addProvider(new com.sun.crypto.provider.SunJCE());
	}

	// 生成密钥, 注意此步骤时间比较长
	public static byte[] getKey() throws Exception {
		KeyGenerator keygen = KeyGenerator.getInstance(Algorithm);
		SecretKey deskey = keygen.generateKey();
		if (debug)
			System.out.println("生成密钥:" + byte2hex(deskey.getEncoded()));
		return deskey.getEncoded();
	}

	// 加密
	public static byte[] encode(byte[] input, byte[] key) throws Exception {
		SecretKey deskey = new javax.crypto.spec.SecretKeySpec(key, Algorithm);
		if (debug) {
			System.out.println("加密前的二进串:" + byte2hex(input));
			System.out.println("加密前的字符串:" + new String(input));
		}
		Cipher c1 = Cipher.getInstance(Algorithm);
		c1.init(Cipher.ENCRYPT_MODE, deskey);
		byte[] cipherByte = c1.doFinal(input);
		if (debug)
			System.out.println("加密后的字符串:" + new String(cipherByte));
		System.out.println("加密后的二进串:" + byte2hex(cipherByte));
		return cipherByte;
	}

	// 解密
	public static byte[] decode(byte[] input, byte[] key) throws Exception {
		SecretKey deskey = new javax.crypto.spec.SecretKeySpec(key, Algorithm);
		if (debug)
			System.out.println("解密前的信息:" + byte2hex(input));
		Cipher c1 = Cipher.getInstance(Algorithm);
		c1.init(Cipher.DECRYPT_MODE, deskey);
		byte[] clearByte = c1.doFinal(input);
		if (debug) {
			System.out.println("解密后的二进串:" + byte2hex(clearByte));
			System.out.println("解密后的字符串:" + (new String(clearByte)));
		}
		return clearByte;
	}

	// md5()信息摘要, 不可逆
	public static byte[] md5(byte[] input) throws Exception {
		java.security.MessageDigest alg = java.security.MessageDigest
				.getInstance("MD5"); // or "SHA-1"
		if (debug) {
			System.out.println("摘要前的二进串:" + byte2hex(input));
			System.out.println("摘要前的字符串:" + new String(input));
		}
		alg.update(input);
		byte[] digest = alg.digest();
		if (debug)
			System.out.println("摘要后的二进串:" + byte2hex(digest));
		return digest;
	}

	// 字节码转换成16进制字符串
	public static String byte2hex(byte[] b) {
		String hs = "";
		String stmp = "";
		for (int n = 0; n < b.length; n++) {
			stmp = (java.lang.Integer.toHexString(b[n] & 0XFF));
			if (stmp.length() == 1)
				hs = hs + "0" + stmp;
			else
				hs = hs + stmp;
		}
		return hs.toUpperCase();
	}

	public static byte[] hex2byte(String hexString) {
		int len = hexString.length() >> 1;
		if( hexString.length() % 2 != 0)
			len++;

		byte[] result = new byte [len];
		for (int i = 0; i < hexString.length(); i += 2) {
			int a = Character.digit(hexString.charAt(i), 16);
			if ((i + 1) < hexString.length())
				a = (a << 4) | (Character.digit(hexString.charAt(i + 1), 16));
			result[i >> 1] = (byte)a;
		}
		return result;
	}
	
	public static void main(String[] args) throws Exception {
		//加密过程
		String key = "kingstar";
		String password = "admin";
		String encodedPassword = byte2hex(encode(password.getBytes(), key.getBytes()));
		System.out.println(encodedPassword);
	}

}
