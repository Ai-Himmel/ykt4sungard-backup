package com.kingstargroup.fdykt.util;

import javax.crypto.Cipher;

import java.security.*;

import java.security.spec.RSAPublicKeySpec;

import java.security.spec.RSAPrivateKeySpec;

import java.security.spec.InvalidKeySpecException;

import java.security.interfaces.RSAPrivateKey;

import java.security.interfaces.RSAPublicKey;

import java.io.*;

import java.math.BigInteger;

/**
 * 
 * RSA �����ࡣ�ṩ���ܣ����ܣ�������Կ�Եȷ�����
 * 
 * ��Ҫ��http://www.bouncycastle.org����bcprov-jdk14-123.jar��
 * 
 * 
 * 
 */

public class RSAUtil {

	/**
	 * 
	 * ������Կ��
	 * 
	 * @return KeyPair
	 * 
	 * @throws EncryptException
	 * 
	 */

	public static KeyPair generateKeyPair() throws Exception {

		try {

			KeyPairGenerator keyPairGen = KeyPairGenerator.getInstance("RSA",

			new org.bouncycastle.jce.provider.BouncyCastleProvider());

			final int KEY_SIZE = 1024;// ûʲô��˵���ˣ����ֵ��ϵ������ܵĴ�С�����Ը��ģ����ǲ�Ҫ̫�󣬷���Ч�ʻ��

			keyPairGen.initialize(KEY_SIZE, new SecureRandom());

			KeyPair keyPair = keyPairGen.genKeyPair();

			return keyPair;

		} catch (Exception e) {

			throw new Exception(e.getMessage());

		}

	}

	/**
	 * 
	 * ���ɹ�Կ
	 * 
	 * @param modulus
	 * 
	 * @param publicExponent
	 * 
	 * @return RSAPublicKey
	 * 
	 * @throws Exception
	 * 
	 */

	public static RSAPublicKey generateRSAPublicKey(byte[] modulus,
			byte[] publicExponent) throws Exception {

		KeyFactory keyFac = null;

		try {

			keyFac = KeyFactory.getInstance("RSA",
					new org.bouncycastle.jce.provider.BouncyCastleProvider());

		} catch (NoSuchAlgorithmException ex) {

			throw new Exception(ex.getMessage());

		}

		RSAPublicKeySpec pubKeySpec = new RSAPublicKeySpec(new BigInteger(
				modulus), new BigInteger(publicExponent));

		try {

			return (RSAPublicKey) keyFac.generatePublic(pubKeySpec);

		} catch (InvalidKeySpecException ex) {

			throw new Exception(ex.getMessage());

		}

	}

	/**
	 * 
	 * ����˽Կ
	 * 
	 * @param modulus
	 * 
	 * @param privateExponent
	 * 
	 * @return RSAPrivateKey
	 * 
	 * @throws Exception
	 * 
	 */

	public static RSAPrivateKey generateRSAPrivateKey(byte[] modulus,
			byte[] privateExponent) throws Exception {

		KeyFactory keyFac = null;

		try {

			keyFac = KeyFactory.getInstance("RSA",
					new org.bouncycastle.jce.provider.BouncyCastleProvider());

		} catch (NoSuchAlgorithmException ex) {

			throw new Exception(ex.getMessage());

		}

		RSAPrivateKeySpec priKeySpec = new RSAPrivateKeySpec(new BigInteger(
				modulus), new BigInteger(privateExponent));

		try {

			return (RSAPrivateKey) keyFac.generatePrivate(priKeySpec);

		} catch (InvalidKeySpecException ex) {

			throw new Exception(ex.getMessage());

		}

	}

	/**
	 * 
	 * ����
	 * 
	 * @param key
	 *            ���ܵ���Կ
	 * 
	 * @param data
	 *            �����ܵ���������
	 * 
	 * @return ���ܺ������
	 * 
	 * @throws Exception
	 * 
	 */

	public static byte[] encrypt(Key key, byte[] data) throws Exception {

		try {

			Cipher cipher = Cipher.getInstance("RSA",
					new org.bouncycastle.jce.provider.BouncyCastleProvider());

			cipher.init(Cipher.ENCRYPT_MODE, key);

			int blockSize = cipher.getBlockSize();// ��ü��ܿ��С����:����ǰ����Ϊ128��byte����key_size=1024
													// ���ܿ��СΪ127
													// byte,���ܺ�Ϊ128��byte;��˹���2�����ܿ飬��һ��127
													// byte�ڶ���Ϊ1��byte

			int outputSize = cipher.getOutputSize(data.length);// ��ü��ܿ���ܺ���С

			int leavedSize = data.length % blockSize;

			int blocksSize = leavedSize != 0 ? data.length / blockSize + 1
					: data.length / blockSize;

			byte[] raw = new byte[outputSize * blocksSize];

			int i = 0;

			while (data.length - i * blockSize > 0) {

				if (data.length - i * blockSize > blockSize)

					cipher.doFinal(data, i * blockSize, blockSize, raw, i
							* outputSize);

				else

					cipher.doFinal(data, i * blockSize, data.length - i
							* blockSize, raw, i * outputSize);

				// ������doUpdate���������ã��鿴Դ�������ÿ��doUpdate��û��ʲôʵ�ʶ������˰�byte[]�ŵ�ByteArrayOutputStream�У������doFinal��ʱ��Ž����е�byte[]���м��ܣ����ǵ��˴�ʱ���ܿ��С�ܿ����Ѿ�������OutputSize����ֻ����dofinal������

				i++;

			}

			return raw;

		} catch (Exception e) {

			throw new Exception(e.getMessage());

		}

	}

	/**
	 * 
	 * ����
	 * 
	 * @param key
	 *            ���ܵ���Կ
	 * 
	 * @param raw
	 *            �Ѿ����ܵ�����
	 * 
	 * @return ���ܺ������
	 * 
	 * @throws Exception
	 * 
	 */

	public static byte[] decrypt(Key key, byte[] raw) throws Exception {

		try {

			Cipher cipher = Cipher.getInstance("RSA",
					new org.bouncycastle.jce.provider.BouncyCastleProvider());

			cipher.init(cipher.DECRYPT_MODE, key);

			int blockSize = cipher.getBlockSize();

			ByteArrayOutputStream bout = new ByteArrayOutputStream(64);

			int j = 0;

			while (raw.length - j * blockSize > 0) {

				bout.write(cipher.doFinal(raw, j * blockSize, blockSize));

				j++;

			}

			return bout.toByteArray();

		} catch (Exception e) {

			throw new Exception(e.getMessage());

		}

	}

	/**
	 * 
	 * 
	 * 
	 * @param args
	 * 
	 * @throws Exception
	 * 
	 */

	public static void main(String[] args) throws Exception {


		KeyPair keyPair = RSAUtil.generateKeyPair();
		

		RSAPublicKey pubKey = (RSAPublicKey) keyPair.getPublic();

		RSAPrivateKey priKey = (RSAPrivateKey) keyPair.getPrivate();

		byte[] pubModBytes = pubKey.getModulus().toByteArray();
		
		
		System.out.println(byte2hex(pubModBytes));

		byte[] pubPubExpBytes = pubKey.getPublicExponent().toByteArray();
		System.out.println(byte2hex(pubPubExpBytes));

		byte[] priModBytes = priKey.getModulus().toByteArray();
		System.out.println(byte2hex(priModBytes));

		byte[] priPriExpBytes = priKey.getPrivateExponent().toByteArray();
		System.out.println(byte2hex(priPriExpBytes));

		RSAPublicKey recoveryPubKey = RSAUtil.generateRSAPublicKey(pubModBytes,
				pubPubExpBytes);

		RSAPrivateKey recoveryPriKey = RSAUtil.generateRSAPrivateKey(
				priModBytes, priPriExpBytes);
		byte[] eee = RSAUtil.encrypt(recoveryPriKey, "12".getBytes());
		System.out.println(byte2hex(eee));
		
	}
	
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

}
