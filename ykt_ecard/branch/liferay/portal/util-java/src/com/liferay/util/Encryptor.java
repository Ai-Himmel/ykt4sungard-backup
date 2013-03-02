/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.util;

import com.liferay.portal.kernel.util.Base64;
import com.liferay.portal.kernel.util.Digester;
import com.liferay.portal.kernel.util.DigesterUtil;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ServerDetector;

import java.security.Key;
import java.security.Provider;
import java.security.SecureRandom;
import java.security.Security;

import javax.crypto.Cipher;
import javax.crypto.KeyGenerator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="Encryptor.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class Encryptor {

	public static final String ENCODING = Digester.ENCODING;

	public static final String KEY_ALGORITHM = "DES";

	public static final String SUN_PROVIDER_CLASS =
		"com.sun.crypto.provider.SunJCE";

	public static final String IBM_PROVIDER_CLASS =
		"com.ibm.crypto.provider.IBMJCE";

	public static final String PROVIDER_CLASS = GetterUtil.getString(
		SystemProperties.get(Encryptor.class.getName() + ".provider.class"),
		SUN_PROVIDER_CLASS);

	public static Key generateKey() throws EncryptorException {
		return generateKey(KEY_ALGORITHM);
	}

	public static Key generateKey(String algorithm) throws EncryptorException {
		try {
			Security.addProvider(getProvider());

			KeyGenerator generator = KeyGenerator.getInstance(algorithm);
			generator.init(56, new SecureRandom());

			Key key = generator.generateKey();

			return key;
		}
		catch (Exception e) {
			throw new EncryptorException(e);
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
			if ((ServerDetector.isWebSphere()) &&
				(PROVIDER_CLASS.equals(SUN_PROVIDER_CLASS))) {

				if (_log.isWarnEnabled()) {
					_log.warn(
						"WebSphere does not have " + SUN_PROVIDER_CLASS +
							", using " + IBM_PROVIDER_CLASS + " instead");
				}

				providerClass = Class.forName(IBM_PROVIDER_CLASS);
			}
			else if (System.getProperty("java.vm.vendor").equals(
						"IBM Corporation")) {

				if (_log.isWarnEnabled()) {
					_log.warn(
						"IBM JVM does not have " + SUN_PROVIDER_CLASS +
							", using " + IBM_PROVIDER_CLASS + " instead");
				}

				providerClass = Class.forName(IBM_PROVIDER_CLASS);
			}
			else {
				throw cnfe;
			}
		}

		return (Provider)providerClass.newInstance();
	}

	public static String decrypt(Key key, String encryptedString)
		throws EncryptorException {

		byte[] encryptedBytes = Base64.decode(encryptedString);

		return decryptRaw(key, encryptedBytes);
	}

	public static String decryptRaw(Key key, byte[] encryptedBytes)
		throws EncryptorException {

		try {
			Security.addProvider(getProvider());

			Cipher cipher = Cipher.getInstance(key.getAlgorithm());

			cipher.init(Cipher.DECRYPT_MODE, key);

			byte[] decryptedBytes = cipher.doFinal(encryptedBytes);

			String decryptedString = new String(decryptedBytes, ENCODING);

			return decryptedString;
		}
		catch (Exception e) {
			throw new EncryptorException(e);
		}
	}

	public static String digest(String text) {
		return DigesterUtil.digest(text);
	}

	public static String digest(String algorithm, String text) {
		return DigesterUtil.digest(algorithm, text);
	}

	public static String encrypt(Key key, String plainText)
		throws EncryptorException {

		byte[] encryptedBytes = encryptRaw(key, plainText);

		return Base64.encode(encryptedBytes);
	}

	public static byte[] encryptRaw(Key key, String plainText)
		throws EncryptorException {

		try {
			Security.addProvider(getProvider());

			Cipher cipher = Cipher.getInstance(key.getAlgorithm());

			cipher.init(Cipher.ENCRYPT_MODE, key);

			byte[] decryptedBytes = plainText.getBytes(ENCODING);
			byte[] encryptedBytes = cipher.doFinal(decryptedBytes);

			return encryptedBytes;
		}
		catch (Exception e) {
			throw new EncryptorException(e);
		}
	}

	private static Log _log = LogFactory.getLog(Encryptor.class);

}