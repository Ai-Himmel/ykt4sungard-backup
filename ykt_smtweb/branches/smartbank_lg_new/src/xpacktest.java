

import com.cn.kingstar.drtp.drtpjlib;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class xpacktest {

	/**
	 * File name: xpacktest.java<br>
	 * Description: <br>
	 * Return: @param args<br>
	 * Modify History: <br>
	 * ��������    ������     ����ʱ��       ��������<br>
	 * ======================================<br>
	 *  ����      ������    2007-4-24  <br>
	 * @author   ������
	 * @version 
	 * @since 1.0
	 */
	public static void main(String[] args) {
		// TODO Auto-generated method stub

			drtpjlib obj = null;
			xpacklib xpack = null;
			long xpackhandle = 0;
			try {
				// TODO: Add initialization code here
				obj = new drtpjlib();
				int errcode[] = { 1 };
				byte errmsg[] = new byte[300];
				byte ip[] = new byte[300];
				byte message[] = new byte[8000];
				byte drtphandle[] = new byte[64];
				int port = 4000;
				int handle;
				boolean ret;
				int len[] = { 1 };
				int branch = 7000;//��̨drtp���ܺ�
				int func = 960001;//��̨ҵ���ܺ�
				int tries = 3;// Ĭ�����Դ���

				String sip = "10.49.188.243";//drtp ip
				ip = sip.getBytes();

				ret = obj.DrtpInit(errcode, errmsg);
				System.out.println("init=" + ret);
				handle = obj.DrtpConnect(ip, port, errcode, errmsg);
				if (handle < 0) {
					String s = new String(errmsg, 0, 300);
					System.out
							.println("connect:errcode=" + errcode[0] + "msg=" + s);
				} else {
					xpack = new xpacklib();
					byte[] name = "c:/cpack.dat".getBytes();
					xpackhandle = xpack.NewXpackHandle(name);
					System.out.println("***************************seruusldjfi************88");
					if (0 != xpackhandle) {
						// �ɹ�
						/*
						 * drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
						 * drtp->AddField(F_SCLOSE_EMP,"240104"); // ������
						 * drtp->AddField(F_LVOL0,cardinfo.cardid); // ���׿���
						 * drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd); // ����
						 * drtp->AddField(F_DAMT0,cardinfo.balance); //�뿨ֵ
						 * drtp->AddField(F_LVOL1,cardinfo.tx_cnt); //�ۼƽ��״���
						 * drtp->AddField(F_SNAME,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);//
						 * ϵͳ��� //�豸�ɣ� drtp->AddField(F_SCUST_NO,"system"); //����Ա
						 */
						xpack.SetRequestType(xpackhandle, func);
						xpack.SetStringFieldByName(xpackhandle, 0, "SCLOSE_EMP"
								.getBytes(), "240104".getBytes());
						xpack.SetIntFieldByName(xpackhandle, 0, "LVOL0".getBytes(),
								Integer.parseInt("000000"));
						xpack.SetDoubleFieldByName(xpackhandle, 0, "DAMT0"
								.getBytes(), Double.parseDouble("2000"));
						xpack.SetIntFieldByName(xpackhandle, 0,
								"LVOL1".getBytes(), Integer.parseInt("2"));
						xpack.SetStringFieldByName(xpackhandle, 0, "SNAME"
								.getBytes(), "550".getBytes());
						xpack.SetStringFieldByName(xpackhandle, 0, "SCUST_NO"
								.getBytes(), "web".getBytes());
						byte[] PackBuffer = new byte[1024];
						int[] PackDataLength = new int[1];
						xpack.EnCodeXpackForRequest(xpackhandle, PackBuffer, 1024,
								PackDataLength);
						while (--tries >= 0) {
							ret = obj.DrtpPostMessage(1, 0, branch, PackBuffer,
									PackDataLength[0], errcode, errmsg, handle);
							if (ret == true) {
								break;
							}
						}
						if (ret == false) {
							// drtp����ʧ��
							String xmlout = XMLGenerateUtil.XMLGenerate("1001",
									"����������ʧ�ܣ����Ժ����ԣ�" + errmsg.toString(), "", "",
									"", "", "", null);
							
						}
						tries = 3;
						while (--tries >= 0) {
							ret = obj.DrtpReadMessage(message, 7000, len, handle,
									drtphandle, errcode, errmsg);
							if (ret == true) {
								break;
							}
						}
						if (ret == false) {
							String xmlout = XMLGenerateUtil.XMLGenerate("1002",
									errmsg.toString(), "", "", "", "", "", null);
						} else {
							xpack.DeCodeXpack(xpackhandle, message, message.length);
							int[] RetCode = new int[1];
							xpack.GetRetCode(xpackhandle, RetCode);
							if (0 == RetCode[0]) {
								int[] SidyAmount = new int[1];
								xpack.GetIntFieldByName(xpackhandle, 0, "damt1"
										.getBytes(), SidyAmount);
								int[] OutCardAmount = new int[1];
								xpack.GetIntFieldByName(xpackhandle, 0, "damt2"
										.getBytes(), OutCardAmount);
								byte[] SerialNo = new byte[26];
								xpack.GetStringFieldByName(xpackhandle, 0,
										"sserial1".getBytes(), SerialNo, 26);

							} else {
								String xmlout = XMLGenerateUtil.XMLGenerate("0001",
										message.toString(), "", "", "", "", "",
										null);

							}
						}
					}

				}
			} catch (Exception e) {

				String xmlout = XMLGenerateUtil.XMLGenerate("1003",
						"ϵͳ�����쳣�����Ժ����ԣ�", "", "", "", "", "", null);
				e.printStackTrace();
			} finally {
				System.out.println("***************************909987************88");
				if (xpackhandle != 0) {
					xpack.DeleteXpackHandle(xpackhandle);
				}
				if (null != obj) {
					obj.DrtpClose();
					obj.DrtpExit();
				}

			}

		}
	}
