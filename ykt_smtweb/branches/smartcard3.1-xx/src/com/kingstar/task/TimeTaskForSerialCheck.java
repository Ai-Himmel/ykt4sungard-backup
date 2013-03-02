package com.kingstar.task;

import java.util.ArrayList;
import java.util.Arrays;

import org.apache.log4j.Logger;

import com.kingstar.basetask.BaseTask;
import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2BrastransDAO;
import com.kingstargroup.fdykt.dto.BrastransdtlDTO;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;

public class TimeTaskForSerialCheck extends BaseTask {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(TimeTaskForSerialCheck.class);

	public boolean run() {
		if (logger.isDebugEnabled()) {
			logger.debug("run() - start"); //$NON-NLS-1$
		}

		/**
		 * 1�������в�ѯ������������ˮ������������ɹ���������ˮ�� 2�������������������� 3���������� ������ˮ�š����
		 * 4�����벻�Ե���ˮ�����±�� 5�����²��貹�����ˮ���
		 * 
		 */

		String serialno = DateUtil
				.getOtherDate(DateUtil.getNow("yyyyMMdd"), 0);
		
		String serialnoStr = getLikeStrFromServer(serialno);
		
		

		DB2BrastransDAO brastransdao = new DB2BrastransDAO();
		ArrayList list = null;
		try {
			list = brastransdao
					.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.t_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1 and a.REFNO like '"
							+ serialno + "%' ");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		if (list != null && list.size() > 0) {
			for (int i = 0; i < list.size(); i++) {
				BrastransdtlDTO brasdto = (BrastransdtlDTO) list.get(i);
				
				if("1".equals(brasdto.getRevflag())){
					//�ѳ���
					brasdto.setStatus(0);
					brasdto.setRemark("��ˮ�Ѿ�����");
					try {
						brastransdao.updateBrasTransLog(brasdto);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
				}else{
					if (serialnoStr.indexOf(brasdto.getRefno()) == -1) {
						// send
						sendreq(brasdto);
					} else {
						// update
						brasdto.setStatus(0);
						brasdto.setRemark("���ѳ�ֵ�ɹ�");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						}  catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}
				

			}

		}
		
		ArrayList unchecklist = null;
		try {
			unchecklist = brastransdao
					.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.t_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		
		if (unchecklist != null && unchecklist.size() > 0) {
			for (int j = 0; j < unchecklist.size(); j++) {
				BrastransdtlDTO brasdto = (BrastransdtlDTO) unchecklist.get(j);
				
				if("1".equals(brasdto.getRevflag())){
					//�ѳ���
					brasdto.setStatus(0);
					brasdto.setRemark("��ˮ�Ѿ�����");
					try {
						brastransdao.updateBrasTransLog(brasdto);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
					
				}else{
					String retStr = getLikeStrFromServer(brasdto.getRefno());					
					if (retStr.indexOf(brasdto.getRefno()) == -1) {
						// send
						sendreq(brasdto);
					} else {
						// update
						brasdto.setStatus(0);
						brasdto.setRemark("���ѳ�ֵ�ɹ�");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						}  catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}				

			}

		}	
		
		
		return true;

	}
	
	private String getLikeStrFromServer(String serialno){
		
		String serialnoStr ="";
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_check", 3003);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		String loginName = KSConfiguration.getInstance().getProperty(
				"loginName", "");
		String loginPwd = KSConfiguration.getInstance().getProperty("loginPwd",
				"");
		String endpoint = KSConfiguration.getInstance().getProperty("endpoint",
				"http://localhost/csi/services/CamsWebService");

		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0,
						"vsvarstr0".getBytes(), endpoint.getBytes());// �����������ַ
				bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),
						loginName.getBytes());// ��������¼��
				bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(),
						loginPwd.getBytes());// ��������¼����
				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation0".getBytes(),
						("YK" + serialno.substring(2) + "%").getBytes());// ��ѯflowid
				boolean bccret = false;

				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String refno = "";
							String oppaccno = "";
							String transamt = "";

							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							double[] doubleRec = new double[1];

							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, i, "scard0"
									.getBytes(), byteStrRec, 256);
							refno = BccUtil.getStringFromByte(byteStrRec);

							serialnoStr += refno + ",";

						}
						while (bcc.HaveNextPack(xpackhandle)) {
							bccret = false;

							bccret = bcc.CallNext(xpackhandle, 10000, errcode,
									errmsg);

							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 == RetCode[0]) {
									for (int i = 0; i < RecordCount[0]; i++) {
										String refno = "";
										String oppaccno = "";
										String transamt = "";

										byte[] byteStrRec = new byte[256];
										int[] intRec = new int[1];
										double[] doubleRec = new double[1];

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "scard0".getBytes(),
												byteStrRec, 9);
										refno = BccUtil
												.getStringFromByte(byteStrRec);

										serialnoStr += refno + ",";
									}

								}

							}
						}

					} else {
						// ʧ��
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							logger.info(vs_mess);
						} else {
							// throw exception //unknow err
							logger.info("���˷���δ֪����"+RetCode[0]);
						}

					}

				} else {
					// ����ʧ��
					logger.info("���˷�����������ʧ�ܣ�����������ߺ�̨����Ӧ");

				}
			} else {
				logger.info("���˷�������cpack��ʼ��ʧ��");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			logger.info("���˷������󣺶�̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		
		return serialnoStr;
	}

	private void sendreq(BrastransdtlDTO brasdto) {
		DB2BrastransDAO db2brastransdao = new DB2BrastransDAO();
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_pay", 3002);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		String loginName = KSConfiguration.getInstance().getProperty(
				"loginName", "");
		String loginPwd = KSConfiguration.getInstance().getProperty("loginPwd",
				"");
		String endpoint = KSConfiguration.getInstance().getProperty("endpoint",
				"http://localhost/csi/services/CamsWebService");

		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0,
						"vsvarstr0".getBytes(), endpoint.getBytes());// �����������ַ
				bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),
						loginName.getBytes());// ��������¼��
				bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(),
						loginPwd.getBytes());// ��������¼����
				bcc.SetStringFieldByName(xpackhandle, 0, "scard0".getBytes(),
						brasdto.getRefno().getBytes());// ��ˮƾ֤��
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						brasdto.getOppaccno().getBytes());// �������˺�
				bcc
						.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
								Integer.parseInt(String.valueOf(brasdto
										.getTransamt())));// ת�˽��
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 5000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
							brasdto.setStatus(0);
							brasdto.setRemark("���ѳ�ֵ����ɹ�");
							db2brastransdao.updateBrasTransLog(brasdto);
					} else {
						// ʧ��
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);

							String vs_mess = BccUtil.getStringFromByte(vsmess);

							brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ�" + vs_mess);
							db2brastransdao.updateBrasTransLog(brasdto);
						} else {

							brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ�������=" + RetCode[0]);
							db2brastransdao.updateBrasTransLog(brasdto);
						}

					}

				} else {
					// ����ʧ��

					brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ���̨ͨѶ��ʱ������");
					db2brastransdao.updateBrasTransLog(brasdto);

				}
			}

			brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ�ϵͳ�����쳣");
			db2brastransdao.updateBrasTransLog(brasdto);

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());

		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());

		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

}
