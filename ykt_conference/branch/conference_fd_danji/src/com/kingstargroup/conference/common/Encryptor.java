/**
 * 
 */
package com.kingstargroup.conference.common;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: Encryptor.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型   操作人   操作时间     操作内容<br>
 * ===================================<br>
 *  创建    Xiao Qi  2005-11-10  <br>
 * @author Xiao Qi
 * @version 
 * @since 1.0
 */


import java.io.UnsupportedEncodingException;

import java.security.Key;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.security.Provider;
import java.security.SecureRandom;
import java.security.Security;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;

import org.apache.xerces.impl.dv.util.Base64;

import sun.misc.BASE64Encoder;

/**
 * <a href="Encryptor.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.15 $
 *
 */
public class Encryptor {

	public static final String ENCODING = "UTF-8";

	public static final String DIGEST_ALGORITHM = "SHA";

	public static final String KEY_ALGORITHM = "DES";

	public static final String SUN_PROVIDER_CLASS =
		"com.sun.crypto.provider.SunJCE";

	public static final String IBM_PROVIDER_CLASS =
		"com.ibm.crypto.provider.IBMJCE";

	public static final String PROVIDER_CLASS = SUN_PROVIDER_CLASS;

	public static Key generateKey() {
		return generateKey(KEY_ALGORITHM);
	}

	public static Key generateKey(String algorithm) {
		try {
			Security.addProvider(getProvider());

			KeyGenerator generator = KeyGenerator.getInstance(algorithm);
			generator.init(56, new SecureRandom());

			Key key = generator.generateKey();

			return key;
		}
		catch (Exception e) {
			return null;
		}
	}

	public static Provider getProvider()
		throws ClassNotFoundException, IllegalAccessException,
			   InstantiationException {

		Class providerClass = null;

		try {
			providerClass = Class.forName(PROVIDER_CLASS);
		}
		catch (ClassNotFoundException cnfe) {
			providerClass = Class.forName(IBM_PROVIDER_CLASS);
		}

		return (Provider)providerClass.newInstance();
	}

	public static String decrypt(Key key, String encryptedString) {

		try {
			Security.addProvider(getProvider());

			Cipher cipher = Cipher.getInstance(key.getAlgorithm());
			cipher.init(Cipher.DECRYPT_MODE, key);

			byte[] encryptedBytes = Base64.decode(encryptedString);
			byte[] decryptedBytes = cipher.doFinal(encryptedBytes);

			String decryptedString = new String(decryptedBytes, ENCODING);

			return decryptedString;
		}
		catch (Exception e) {
			return "";
		}
	}

	public static String digest(String text) {
		return digest(DIGEST_ALGORITHM, text);
	}

	public static String digest(String algorithm, String text) {
		MessageDigest mDigest = null;

		try{
			mDigest = MessageDigest.getInstance(algorithm);

			mDigest.update(text.getBytes(ENCODING));
		}
		catch(NoSuchAlgorithmException nsae) {
			nsae.printStackTrace();
		}
		catch(UnsupportedEncodingException uee) {
			uee.printStackTrace();
		}

		byte raw[] = mDigest.digest();

		return (new BASE64Encoder()).encode(raw);
	}

	public static String encrypt(Key key, String plainText) {

		try {
			Security.addProvider(getProvider());

			Cipher cipher = Cipher.getInstance(key.getAlgorithm());
			cipher.init(Cipher.ENCRYPT_MODE, key);

			byte[] decryptedBytes = plainText.getBytes(ENCODING);
			byte[] encryptedBytes = cipher.doFinal(decryptedBytes);

			String encryptedString = Base64.encode(encryptedBytes);

			return encryptedString;
		}
		catch (Exception e) {
			return "";
		}
	}
	
	public static void main(String[] args) {
		System.out.println(digest("3333"));
	}

}
