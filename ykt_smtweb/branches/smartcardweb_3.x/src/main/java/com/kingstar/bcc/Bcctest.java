package com.kingstar.bcc;

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
		// TODO Auto-generated method stub
		String sip = "10.49.188.243";// drtp ip
		int port = 4000;
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		byte ip[] = new byte[300];
		byte message[] = new byte[8000];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = 9000;
		int func = 847315;// 后台业务功能号
		int tries = 3;// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		ip = sip.getBytes();
		bccclt bcc = null;
		try {
			bcc = new bccclt();
			bcc.SetDebugSwitch(true);

			bcc.BCCCLTInit(1);
			drtpno = bcc.AddDrtpNode(ip, port);

			bcc.XPackInit(1);
			xpackhandle = bcc.NewXpackHandle("c:\\cpack.dat".getBytes());

			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240104".getBytes());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt("20516"));
				bcc.SetDoubleFieldByName(xpackhandle, 0, "damt0".getBytes(),
						Double.parseDouble("56.2"));
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt("104"));
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());
				boolean bccret = bcc.CallRequest(xpackhandle, drtpno,
						branchno, mainfunction, 3000, errcode, errmsg);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {						
						if (0 < RecordCount[0]) {
							int[] SidyAmount = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "damt1"
									.getBytes(), SidyAmount);
							int[] OutCardAmount = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "damt2"
									.getBytes(), OutCardAmount);
							// int[] SerialNo = new int[1];
							// bcc.GetIntFieldByName(xpackhandle, 0, "lserial0"
							// .getBytes(), SerialNo);
							byte[] SerialNo = new byte[26];
							bcc.GetStringFieldByName(xpackhandle, 0, "sserial1"
									.getBytes(), SerialNo, 26);
							int i = 0;
							for (i = 0; i < SerialNo.length; i++) {
								if (0 == SerialNo[i]) {
									break;
								}
							}
							String serial_no = new String(SerialNo, 0, i);
							String xmlout = XMLGenerateUtil.XMLGenerate("0000",
									"补助领取成功", String.valueOf(SidyAmount[0]),
									String.valueOf(OutCardAmount[0]),
									serial_no, "", "","", "","","",null);
							System.out.println(xmlout);

						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!", "", "","", "", "","","","", "", null);
							System.out.println(xmlout);
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

							String xmlout = XMLGenerateUtil.XMLGenerate("0002",
									vs_mess, "", "", "", "", "","","","","", null);
							System.out.println(xmlout);
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									"无数据返回!", "", "", "", "","", "","","","", null);
							System.out.println(xmlout);
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
					String s = new String(errmsg, 0,i);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					String xmlout = XMLGenerateUtil.XMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + s, "","","","", "","", "",
							"", "", null);
					System.out.println(xmlout);
				}
			}
			String xmlout = XMLGenerateUtil.XMLGenerate("1002",
					"系统出现异常，请稍后重试！", "", "", "", "","", "","","","", null);
			System.out.println(xmlout);


		} catch (Exception e) {

			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"系统出现异常，请稍后重试！", "", "", "", "","","", "","","", null);
			System.out.println(xmlout);

		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}

	}
}