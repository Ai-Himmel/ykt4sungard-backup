package com.kingstargroup.fdykt.util;

import java.security.*;
import javax.crypto.*;

public class Crypt {

	private static String Algorithm = "DES"; // ���� �����㷨,����
	// DES,DESede,Blowfish

	static boolean debug = false;

	static {
		Security.addProvider(new com.sun.crypto.provider.SunJCE());
	}

	// ������Կ, ע��˲���ʱ��Ƚϳ�
	public static byte[] getKey() throws Exception {
		KeyGenerator keygen = KeyGenerator.getInstance(Algorithm);
		SecretKey deskey = keygen.generateKey();
		if (debug)
			System.out.println("������Կ:" + byte2hex(deskey.getEncoded()));
		return deskey.getEncoded();
	}

	// ����
	public static byte[] encode(byte[] input, byte[] key) throws Exception {
		SecretKey deskey = new javax.crypto.spec.SecretKeySpec(key, Algorithm);
		if (debug) {
			System.out.println("����ǰ�Ķ�����:" + byte2hex(input));
			System.out.println("����ǰ���ַ���:" + new String(input));
		}
		Cipher c1 = Cipher.getInstance(Algorithm);
		c1.init(Cipher.ENCRYPT_MODE, deskey);
		byte[] cipherByte = c1.doFinal(input);
		if (debug)
			System.out.println("���ܺ�Ķ�����:" + byte2hex(cipherByte));
		return cipherByte;
	}

	// ����
	public static byte[] decode(byte[] input, byte[] key) throws Exception {
		SecretKey deskey = new javax.crypto.spec.SecretKeySpec(key, Algorithm);
		if (debug)
			System.out.println("����ǰ����Ϣ:" + byte2hex(input));
		Cipher c1 = Cipher.getInstance(Algorithm);
		c1.init(Cipher.DECRYPT_MODE, deskey);
		byte[] clearByte = c1.doFinal(input);
		if (debug) {
			System.out.println("���ܺ�Ķ�����:" + byte2hex(clearByte));
			System.out.println("���ܺ���ַ���:" + (new String(clearByte)));
		}
		return clearByte;
	}

	// md5()��ϢժҪ, ������
	public static byte[] md5(byte[] input) throws Exception {
		java.security.MessageDigest alg = java.security.MessageDigest
				.getInstance("MD5"); // or "SHA-1"
		if (debug) {
			System.out.println("ժҪǰ�Ķ�����:" + byte2hex(input));
			System.out.println("ժҪǰ���ַ���:" + new String(input));
		}
		alg.update(input);
		byte[] digest = alg.digest();
		if (debug)
			System.out.println("ժҪ��Ķ�����:" + byte2hex(digest));
		return digest;
	}

	// �ֽ���ת����16�����ַ���
	public static String byte2hex(byte[] b) {
		String hs = "";
		String stmp = "";
		for (int n = 0; n < b.length; n++) {
			stmp = (java.lang.Integer.toHexString(b[n] & 0XFF));
			if (stmp.length() == 1)
				hs = hs + "0" + stmp;
			else
				hs = hs + stmp;
			if (n < b.length - 1)
				hs = hs + ":";
		}
		return hs.toUpperCase();
	}

	public String encode(String pwd) throws Exception {
		byte[] key = "�ú�ѧϰ".getBytes();
		byte[] newpwd = encode(pwd.getBytes(), key);
		String securityPwd = new String(newpwd);
		return securityPwd;
	}

	public static void main(String[] args) throws Exception {
		debug = true;
		// byte[] key = getKey();
		byte[] key = "�ú�ѧϰ".getBytes();
		decode(encode("���Լ���".getBytes(), key), key);
		md5("���Լ���".getBytes());
	}
}
