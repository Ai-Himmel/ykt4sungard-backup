package com.kingstar.task;

import java.util.ArrayList;
import java.util.Arrays;

import org.apache.log4j.Logger;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2BrastransDAO;
import com.kingstargroup.fdykt.dto.BrastransdtlDTO;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;

public class TimeTaskForSerialCheckThread extends Thread {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(TimeTaskForSerialCheckThread.class);

	private static boolean requestStop = false;
	private int restartcheck = 0;
	private String checktime = "032000";

	public void run() {
		while (!requestStop) {
			
			restartcheck = KSConfiguration.getInstance().getPropertyAsInt(
					"restartcheck", 0);
			checktime = KSConfiguration.getInstance().getProperty("checktime",
					"032000");
			
			if (restartcheck == 1) {// ��ʱ������������ֱ������
				try {

					long sleepTime = DateUtil.getIntervalTime(DateUtil
							.getNewDateTime(DateUtil.getNow("yyyyMMdd"), 1,
									"yyyyMMdd")
							+ checktime, DateUtil.getNow());
					if (logger.isInfoEnabled()) {
						logger
								.info("bras�����߳̽�������״̬!"
										+ " ���߿�ʼʱ��:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss") + ", ����ʱ��:" + sleepTime + " ����"); //$NON-NLS-1$
					}
					if (sleepTime <= 0) {
						sleep(24 * 3600 * 1000);
					} else {
						sleep(sleepTime);
					}
				} catch (InterruptedException e) {
					logger.error("bras�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
				} catch (Exception e) {
					logger.error("bras�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
				}
			}

			
			DB2BrastransDAO brastransdao = new DB2BrastransDAO();
			String uncheckdate = DateUtil.getNow("yyyyMMdd");
			try {
				uncheckdate = brastransdao.getMinUncheckBrasTransLogDate();
			} catch (Exception e2) {
				// TODO Auto-generated catch block
				e2.printStackTrace();
			}

			String nowdate = DateUtil.getNow("yyyyMMdd");

			checkLogic(brastransdao,uncheckdate, nowdate);
			try {

				long sleepTime = DateUtil.getIntervalTime(DateUtil
						.getNewDateTime(DateUtil.getNow("yyyyMMdd"), 1,
								"yyyyMMdd")
						+ checktime, DateUtil.getNow());
				if (logger.isInfoEnabled()) {
					logger
							.info("bras�����߳̽�������״̬!"
									+ " ���߿�ʼʱ��:" + DateUtil.getNow("yyyy/MM/dd/HH:mm:ss") + ", ����ʱ��:" + sleepTime + " ����"); //$NON-NLS-1$
				}
				if (sleepTime <= 0) {
					sleep(24 * 3600 * 1000);
				} else {
					sleep(sleepTime);
				}
			} catch (InterruptedException e) {
				logger.error("bras�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
			} catch (Exception e) {
				logger.error("bras�����̳߳��������쳣�����ܱ�ǿ��ֹͣ�� ", e); //$NON-NLS-1$
			}
		}

	}

	private void checkLogic(DB2BrastransDAO brastransdao,String uncheckdate,
			String nowdate) {
		/**
		 * 1�������в�ѯ������������ˮ������������ɹ���������ˮ�� 2�������������������� 3���������� ������ˮ�š����
		 * 4�����벻�Ե���ˮ�����±�� 5�����²��貹�����ˮ���
		 * 
		 */

		while (DateUtil.checkSpecialTimeSequence(uncheckdate, nowdate,
				"yyyyMMdd") <0) {

			String serialnoStr = "";
			ArrayList list = null;
			try {
				list = brastransdao
						.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.v_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1 and a.REFNO like '"
								+ uncheckdate + "%' ");
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			if (list != null && list.size() > 0) {
				try {
					serialnoStr = getLikeStrFromServer(uncheckdate);
				} catch (Exception e2) {
					// TODO Auto-generated catch block
					e2.printStackTrace();
					logger.info("�������������ݲ����ã�����ʧ��");
					break;
				}
				
				for (int i = 0; i < list.size(); i++) {
					BrastransdtlDTO brasdto = (BrastransdtlDTO) list.get(i);
					if ("1".equals(brasdto.getRevflag())) {
						// �ѳ���
						brasdto.setStatus(0);
						brasdto.setRemark("��ˮ�Ѿ�����");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						} catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}

					} else {
						String sendrefno = "YK"
								+ brasdto.getRefno().substring(2);
						if (serialnoStr.indexOf(sendrefno) == -1) {
							// send
							sendreq(brastransdao,brasdto);
						} else {
							// update
							brasdto.setStatus(0);
							brasdto.setRemark("���ѳ�ֵ�ɹ�");
							try {
								brastransdao.updateBrasTransLog(brasdto);
							} catch (Exception e) {
								// TODO Auto-generated catch block
								e.printStackTrace();
							}
						}
					}

				}

			}

			try {
				brastransdao.updateBrasTransLogCHKFLAG(uncheckdate);
			} catch (Exception e) {
				// TODO Auto-generated catch block

				e.printStackTrace();
			}

			
			
			//log brastransdtl����û�е�����
			
			ArrayList lostlist = null;
			try {
				lostlist = brastransdao
						.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.v_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1 and a.REFNO like '"
								+ uncheckdate + "%' ");
			} catch (Exception e1) {
				// TODO Auto-generated catch block
				e1.printStackTrace();
			}
			
			
			
			
			uncheckdate = DateUtil.getNewDateTime(uncheckdate, 1, "yyyyMMdd");

		}


		ArrayList unchecklist = null;
		try {
			unchecklist = brastransdao
					.getBrasTransLog("select a.*,b.revflag from ykt_cur.T_BRASTRANSDTL a,ykt_cur.v_transdtl b where a.refno=b.refno and b.transcode='3180' and a.status=1 and a.refno<'"
							+ nowdate + "'");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}

		if (unchecklist != null && unchecklist.size() > 0) {
			for (int j = 0; j < unchecklist.size(); j++) {
				BrastransdtlDTO brasdto = (BrastransdtlDTO) unchecklist.get(j);

				if ("1".equals(brasdto.getRevflag())) {
					// �ѳ���
					brasdto.setStatus(0);
					brasdto.setRemark("��ˮ�Ѿ�����");
					try {
						brastransdao.updateBrasTransLog(brasdto);
					} catch (Exception e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}

				} else {
					String retStr = "";
					try {
						retStr = getLikeStrFromServer(brasdto.getRefno());
					} catch (Exception e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
						logger.info("�������������������,��������ʧ��");
						continue;
					}
					String sendrefno = "YK" + brasdto.getRefno().substring(2);
					if (retStr.indexOf(sendrefno) == -1) {
						// send
						sendreq(brastransdao,brasdto);
					} else {
						// update
						brasdto.setStatus(0);
						brasdto.setRemark("���ѳ�ֵ�ɹ�");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						} catch (Exception e) {
							// TODO Auto-generated catch block
							e.printStackTrace();
						}
					}
				}

			}

		}

	}

	private String getLikeStrFromServer(String serialno) throws Exception {

		String serialnoStr = "";
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_check", 3003);// ��̨ҵ���ܺ�
		// int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
		// 3);// Ĭ�����Դ���
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
				String reqrefno = "YK" + serialno.substring(2) + "%";
				bcc.SetStringFieldByName(xpackhandle, 0,
						"sstation0".getBytes(), reqrefno.getBytes());// ��ѯflowid

				logger.info("��ѯ��������ˮ����ѯ������" + reqrefno);
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 60000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						for (int i = 0; i < RecordCount[0]; i++) {
							String refno = "";
							// String oppaccno = "";
							// String transamt = "";

							byte[] byteStrRec = new byte[256];
							// int[] intRec = new int[1];
							// double[] doubleRec = new double[1];

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
										// String oppaccno = "";
										// String transamt = "";

										byte[] byteStrRec = new byte[256];
										// int[] intRec = new int[1];
										// double[] doubleRec = new double[1];

										Arrays.fill(byteStrRec, (byte) 0);
										bcc.GetStringFieldByName(xpackhandle,
												i, "scard0".getBytes(),
												byteStrRec, 256);
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
							logger.info("���˷������� ����ԭ��" + vs_mess);
							throw new Exception("���˷������� ����ԭ��" + vs_mess);

						} else {
							// throw exception //unknow err
							logger.info("���˷���δ֪���� �����룺" + RetCode[0]);
							throw new Exception("���˷���δ֪���� �����룺" + RetCode[0]);
						}

					}

				} else {
					// ����ʧ��
					logger.info("���˷�����������ʧ�ܣ�����������ߺ�̨����Ӧ");

					throw new Exception("���˷�����������ʧ�ܣ�����������ߺ�̨����Ӧ");
				}
			} else {
				logger.info("���˷�������cpack��ʼ��ʧ��");
				throw new Exception("���˷�������cpack��ʼ��ʧ��");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			logger.info("���˷������󣺶�̬�����ʧ�ܣ����Ժ����ԣ�");
			throw new Exception(e);
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		logger.info("���ؽ����" + serialnoStr);
		return serialnoStr;
	}

	private void sendreq(DB2BrastransDAO brastransdao,BrastransdtlDTO brasdto) {
		if (logger.isDebugEnabled()) {
			logger.debug("sendreq(BrastransdtlDTO) - start"); //$NON-NLS-1$
		}

		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_pay", 3002);// ��̨ҵ���ܺ�
		// int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
		// 3);// Ĭ�����Դ���
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
				String reqrefno = "YK" + brasdto.getRefno().substring(2);
				bcc.SetStringFieldByName(xpackhandle, 0, "scard0".getBytes(),
						reqrefno.getBytes());// ��ˮƾ֤��
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						brasdto.getOppaccno().getBytes());// �������˺�
				String tsamt = String.valueOf(brasdto.getTransamt());
				tsamt = tsamt.substring(0, tsamt.indexOf("."));
				bcc
						.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
								Integer.parseInt(tsamt));// ת�˽��
				logger.info("����������������ˮ" + brasdto.getRefno() + "��"
						+ brasdto.getTransamt());
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 30000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						brasdto.setStatus(0);
						brasdto.setRemark("���ѳ�ֵ����ɹ�");
						try {
							brastransdao.updateBrasTransLog(brasdto);
						} catch (Exception e) {
							// TODO: handle exception
							logger.error("�������ѳ�ֵ��ʧ��,��ˮ�ţ�" + brasdto.getRefno()
									+ "״̬��[" + brasdto.getStatus() + "],��ע��"
									+ brasdto.getRemark());
							e.printStackTrace();
						}

					} else {
						// ʧ��
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);

							String vs_mess = BccUtil.getStringFromByte(vsmess);

							brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ�" + vs_mess);
							try {
								brastransdao.updateBrasTransLog(brasdto);
							} catch (Exception e) {
								// TODO: handle exception
								logger.error("�������ѳ�ֵ��ʧ��,��ˮ�ţ�"
										+ brasdto.getRefno() + "״̬��["
										+ brasdto.getStatus() + "],��ע��"
										+ brasdto.getRemark());
								e.printStackTrace();
							}
						} else {

							brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ�������=" + RetCode[0]);
							try {
								brastransdao.updateBrasTransLog(brasdto);
							} catch (Exception e) {
								// TODO: handle exception
								logger.error("�������ѳ�ֵ��ʧ��,��ˮ�ţ�"
										+ brasdto.getRefno() + "״̬��["
										+ brasdto.getStatus() + "],��ע��"
										+ brasdto.getRemark());
								e.printStackTrace();
							}
						}

					}

				} else {
					// ����ʧ��

					brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ���̨ͨѶ��ʱ������");
					try {
						brastransdao.updateBrasTransLog(brasdto);
					} catch (Exception e) {
						// TODO: handle exception
						logger.error("�������ѳ�ֵ��ʧ��,��ˮ�ţ�" + brasdto.getRefno()
								+ "״̬��[" + brasdto.getStatus() + "],��ע��"
								+ brasdto.getRemark());
						e.printStackTrace();
					}
				}
			}else{
				brasdto.setRemark("���ѳ�ֵ����ʧ�ܣ�cpack��ʼ��ʧ��");
				try {
					brastransdao.updateBrasTransLog(brasdto);
				} catch (Exception e) {
					// TODO: handle exception
					logger.error("�������ѳ�ֵ��ʧ��,��ˮ�ţ�" + brasdto.getRefno() + "״̬��["
							+ brasdto.getStatus() + "],��ע��" + brasdto.getRemark());
					e.printStackTrace();
				}
			}

			

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

		if (logger.isDebugEnabled()) {
			logger.debug("sendreq(BrastransdtlDTO) - end"); //$NON-NLS-1$
		}
	}
}
