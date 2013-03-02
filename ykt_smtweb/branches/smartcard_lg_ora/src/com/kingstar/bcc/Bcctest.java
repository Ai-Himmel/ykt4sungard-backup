package com.kingstar.bcc;

import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class Bcctest {

	/**
	 * File name: Bcctest.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      何林青    2007-4-25  <br>
	 * @author   何林青
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = 9700;
		int func = 847316;// 后台业务功能号
		int tries = 3;// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		bcc = BccctlInit.getBccctlInstance();
		xpackhandle = bcc.NewXpackHandle("c:\\cpack.dat".getBytes());
		for(int k=0;k<1000;k++){
			tries=3;
			try {				
				if (0 != xpackhandle) {
					bcc.SetRequestType(xpackhandle, func);
					bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
							Integer.parseInt("240200"));//请求号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
							Integer.parseInt("14"));//卡号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
							Integer.parseInt("123456"));//模拟流水号
					bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(),
							50.1);//入卡值
					bcc.SetDoubleFieldByName(xpackhandle, 0, "damt1".getBytes(),
							Double.parseDouble("20"));//交易金额
					bcc.SetStringFieldByName(xpackhandle, 0, "sphone".getBytes(),
							"11111111111".getBytes());//手机号码
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
							Integer.parseInt("10"));//交易次数
					bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
							"web".getBytes());//操作员
					
					boolean bccret = false;
					while (--tries >= 0) {
						bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 1000, errcode, errmsg);
						if (bccret) {
							break;
						}
					}
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							if (0 < RecordCount[0]) {
								double[] OutCardAmount = new double[1];
								bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
										.getBytes(), OutCardAmount);
								double[] TransAmount = new double[1];
								bcc.GetDoubleFieldByName(xpackhandle, 0, "damt1"
										.getBytes(), TransAmount);							
								int[] SerialNo = new int[1];
								bcc.GetIntFieldByName(xpackhandle, 0, "lvol0"
										.getBytes(), SerialNo);
								String out_card_amount = String
										.valueOf(OutCardAmount[0] * 100);
								String serial_no = String.valueOf(SerialNo[0]);
								
								
								System.out.println("aaaaaaaaaa");
							} else {
								System.out.println("bbbbbbbbbbb");
							}

						} else {
							// 失败
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
										.getBytes(), vsmess, 300);
								int i;
								for (i = 0; i < vsmess.length; i++) {
									if (vsmess[i] == 0) {
										break;
									}
								}
								String vs_mess = new String(vsmess, 0, i);
								System.out.println(vs_mess);
							} else {
								System.out.println("cccccccccccc");
							}

						}

					} else {
						// 请求失败

						int i;
						for (i = 0; i < errmsg.length; i++) {
							if (errmsg[i] == 0) {
								break;
							}
						}
						String s = new String(errmsg, 0, i);
						System.out.println("connect:errcode=" + errcode[0] + "msg="
								+ s);
						System.out.println("connect:errcode=" + errcode[0] + "msg=" + s);
					}
				}
				System.out.println("ddddddddddd");

			} catch (Exception e) {
				System.out.println(e.getMessage());
			} catch (UnsatisfiedLinkError e) {
				System.out.println(e.getMessage());
			}
		}
		

	}
}