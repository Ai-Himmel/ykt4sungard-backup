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
 * RSA 工具类。提供加密，解密，生成密钥对等方法。
 * 
 * 需要到http://www.bouncycastle.org下载bcprov-jdk14-123.jar。
 * 
 * 
 * 
 */

public class RSAUtil {

	/**
	 * 
	 * 生成密钥对
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

			final int KEY_SIZE = 1024;// 没什么好说的了，这个值关系到块加密的大小，可以更改，但是不要太大，否则效率会低

			keyPairGen.initialize(KEY_SIZE, new SecureRandom());

			KeyPair keyPair = keyPairGen.genKeyPair();

			return keyPair;

		} catch (Exception e) {

			throw new Exception(e.getMessage());

		}

	}

	/**
	 * 
	 * 生成公钥
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
	 * 生成私钥
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
	 * 加密
	 * 
	 * @param key
	 *            加密的密钥
	 * 
	 * @param data
	 *            待加密的明文数据
	 * 
	 * @return 加密后的数据
	 * 
	 * @throws Exception
	 * 
	 */

	public static byte[] encrypt(Key key, byte[] data) throws Exception {

		try {

			Cipher cipher = Cipher.getInstance("RSA",
					new org.bouncycastle.jce.provider.BouncyCastleProvider());

			cipher.init(Cipher.ENCRYPT_MODE, key);

			int blockSize = cipher.getBlockSize();// 获得加密块大小，如:加密前数据为128个byte，而key_size=1024
													// 加密块大小为127
													// byte,加密后为128个byte;因此共有2个加密块，第一个127
													// byte第二个为1个byte

			int outputSize = cipher.getOutputSize(data.length);// 获得加密块加密后块大小

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

				// 这里面doUpdate方法不可用，查看源代码后发现每次doUpdate后并没有什么实际动作除了把byte[]放到ByteArrayOutputStream中，而最后doFinal的时候才将所有的byte[]进行加密，可是到了此时加密块大小很可能已经超出了OutputSize所以只好用dofinal方法。

				i++;

			}

			return raw;

		} catch (Exception e) {

			throw new Exception(e.getMessage());

		}

	}

	/**
	 * 
	 * 解密
	 * 
	 * @param key
	 *            解密的密钥
	 * 
	 * @param raw
	 *            已经加密的数据
	 * 
	 * @return 解密后的明文
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
