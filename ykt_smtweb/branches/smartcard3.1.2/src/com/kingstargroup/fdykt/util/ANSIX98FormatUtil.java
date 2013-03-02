package com.kingstargroup.fdykt.util;

public class ANSIX98FormatUtil {
	/**
	   * getPinBlock
	   * 标准ANSI X9.8 Format（带主帐号信息）的PIN BLOCK计算
	   * PIN BLOCK 格式等于 PIN 按位异或 主帐号;
	   * @param pin String
	   * @param accno String
	   * @return byte[]
	   */
	public static byte[] process(String pin, String accno) {
	    byte arrAccno[] = getHAccno(accno);
	    byte arrPin[] = getHPin(pin);
	    byte arrRet[] = new byte[8];
	    //PIN BLOCK 格式等于 PIN 按位异或 主帐号;
	    for (int i = 0; i < 8; i++) {
	      arrRet[i] = (byte) (arrPin[i] ^ arrAccno[i]);
	    }
	    return arrRet;
	}

	/**
	   * getHPin
	   * 对密码进行转换
	   * PIN格式
	   * BYTE 1 PIN的长度
	   * BYTE 2 – BYTE 3/4/5/6/7   4--12个PIN(每个PIN占4个BIT)
	   * BYTE 4/5/6/7/8 – BYTE 8   FILLER "F" (每个"F"占4个BIT)
	   * @param pin String
	   * @return byte[]
	   */
	private static byte[] getHPin(String pin) {
	    byte arrPin[] = pin.getBytes();
	    byte encode[] = new byte[8];
	    encode[0] = (byte) 0x06;
	    encode[1] = (byte) uniteBytes(arrPin[0], arrPin[1]);
	    encode[2] = (byte) uniteBytes(arrPin[2], arrPin[3]);
	    encode[3] = (byte) uniteBytes(arrPin[4], arrPin[5]);
	    encode[4] = (byte) 0xFF;
	    encode[5] = (byte) 0xFF;
	    encode[6] = (byte) 0xFF;
	    encode[7] = (byte) 0xFF;
	    return encode;
	}

	/**
	   * getHAccno
	   * 对帐号进行转换
	   * BYTE 1 — BYTE 2 0X0000
	   * BYTE 3 — BYTE 8 12个主帐号
	   * 取主帐号的右12位（不包括最右边的校验位），不足12位左补"0X00"。
	   * @param accno String
	   * @return byte[]
	   */
	private static byte[] getHAccno(String accno) {
	    //取出主帐号；
	    int len = accno.length();
	    byte arrTemp[] = accno.substring(len < 13 ? 0 : len - 13, len - 1).getBytes();
	    byte arrAccno[] = new byte[12];
	    for (int i = 0; i < 12; i++) {
	      arrAccno[i] = (i <= arrTemp.length ? arrTemp[i] : (byte) 0x00);
	    }
	    byte encode[] = new byte[8];
	    encode[0] = (byte) 0x00;
	    encode[1] = (byte) 0x00;
	    encode[2] = (byte) uniteBytes(arrAccno[0], arrAccno[1]);
	    encode[3] = (byte) uniteBytes(arrAccno[2], arrAccno[3]);
	    encode[4] = (byte) uniteBytes(arrAccno[4], arrAccno[5]);
	    encode[5] = (byte) uniteBytes(arrAccno[6], arrAccno[7]);
	    encode[6] = (byte) uniteBytes(arrAccno[8], arrAccno[9]);
	    encode[7] = (byte) uniteBytes(arrAccno[10], arrAccno[11]);
	    return encode;
	}
	
	
	private static byte uniteBytes(byte src0, byte src1) {
	     byte _b0 = Byte.decode("0x" + new String(new byte[] {src0})).byteValue();
	     _b0 = (byte) (_b0 << 4);
	     byte _b1 = Byte.decode("0x" + new String(new byte[] {src1})).byteValue();
	     byte result = (byte) (_b0 | _b1);
	     return result;
	} 

}
