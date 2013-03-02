package com.kingstargroup.ecard.portlet.bank.service;

import java.io.UnsupportedEncodingException;
import java.util.Arrays;

import org.apache.commons.lang.StringUtils;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.exceptions.BccException;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;
import com.kingstargroup.ecard.util.BccUtil;

public class BankServiceImpl extends BankServiceBase {
	
	/*
	 * ������ѯ���п���
	 */
	public String getLinkBankBindingAcc( String stuempno)throws PortalException {
		String bankcardno = "";
		//String errinfo = "";
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 6000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("bank_account_query", 841603);// ��̨ҵ���ܺ�
		//int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",3);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(), "Q".getBytes());// ��������
				bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(), stuempno.getBytes());// ѧ��
				bcc.SetIntFieldByName(xpackhandle, 0, "lwithdraw_flag".getBytes(), 1);//�ն˱��
				boolean bccret = false;
				try{
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 10000, errcode, errmsg);
				}catch(Exception e){
					System.out.println(e.toString());
				}
				System.out.println(bcc);
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						byte[] byteStrRec = new byte[256];
						Arrays.fill(byteStrRec, (byte) 0);
						bcc.GetStringFieldByName(xpackhandle, 0,"scard0".getBytes(), byteStrRec, 51);
						bankcardno = BccUtil.getStringFromByte(byteStrRec);
						return bankcardno;
					} else {
						// ʧ��
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("δ֪����");
						}
					}
				} else {
					// ����ʧ��
					throw new BccException("����ʧ�ܣ�����������ߺ�̨����Ӧ");
				}
			} else {
				throw new BccException("cpack��ʼ��ʧ��");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		
	}
	
	/*
	 * �����п����� A����ʾ��ӣ���D����ʾ����󶨣���S����ʾͬ��,��R����ʾ������֤��

	 */
	public void linkBindingOper( String stuempno,String bankAcc,String authcode,String operType)throws PortalException {
		//String bankcardno = "";
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 6000);
		int func = KSConfiguration.getInstance().getPropertyAsInt("bank_account_query", 841603);// ��̨ҵ���ܺ�
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(), "B".getBytes());// ��������
				bcc.SetIntFieldByName(xpackhandle, 0, "lwithdraw_flag".getBytes(), 1);//�ն˱��
				
				bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(), stuempno.getBytes());// ѧ��
				bcc.SetStringFieldByName(xpackhandle, 0, "scard0".getBytes(), bankAcc.getBytes());// ���п���
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1".getBytes(), operType.getBytes());// ��������
				if(StringUtils.isNotBlank(authcode)){
					bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd".getBytes(), authcode.getBytes());//���п�У����
				}
				
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						//byte[] byteStrRec = new byte[256];
						//Arrays.fill(byteStrRec, (byte) 0);
						//bcc.GetStringFieldByName(xpackhandle, 0,"scard0".getBytes(), byteStrRec, 51);
						//bankcardno = BccUtil.getStringFromByte(byteStrRec);
						//return bankcardno;
					} else {
						// ʧ��
						if (0 < RecordCount[0]) {
							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("δ֪����");
						}
					}
				} else {
					// ����ʧ��
					throw new BccException("����ʧ�ܣ�����������ߺ�̨����Ӧ");
				}
			} else {
				throw new BccException("cpack��ʼ��ʧ��");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
		
	}
	/*
	 * y
	 */
	public String getBankBindingAccount(TCustomer tcustomer, String stuempno)
			throws PortalException {
		String bankcardno = "";
		String errinfo = "";
		try {
			bankcardno = bankPersistence.getBankAccountFromDB(tcustomer
					.getCustid(), "00");
		} catch (DBSystemException e) {
			// TODO: handle exception
			e.printStackTrace();
		}

		return bankcardno;


	}

	public String updateBankBindingAccount(TCustomer tcustomer,
			String stuempno, String bankcardno) throws PortalException {
		
		if("".equals(bankcardno)){
			throw new BccBgInfoException("���ܸ���Ϊ�����п��ţ�����ʹ��ɾ������ɾ����");
		}

		String bankcardno_db = "";
		try {
			bankcardno_db = bankPersistence.getBankAccountFromDB(tcustomer
					.getCustid(), "00");
		} catch (DBSystemException e) {
			// TODO: handle exception
			e.printStackTrace();
			throw e;

		}
		System.out.println("local card no:"+bankcardno_db+"****");
		if (!bankcardno_db.equals(bankcardno)) {

			if(!"".equals(bankcardno_db)){
				try {
					System.out.println("delete local bank acc:"+bankcardno_db+"****");
					deleteBankBindingAccount(tcustomer, stuempno, false);
				} catch (PortalException e) {
					// TODO: handle exception
					throw e;
				}
			}		

			long xpackhandle = 0;
			int drtpno = 1;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// ��̨drtp���ܺ�
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction1", 5000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"bank_account_query", 270001);// ��̨ҵ���ܺ�
			int tries = KSConfiguration.getInstance().getPropertyAsInt("tries",
					3);// Ĭ�����Դ���
			int[] RetCode = new int[1];
			int[] RecordCount = new int[1];
			bccclt bcc = null;
			try {
				bcc = BccctlInit.getBccctlInstance();
				xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
						.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
				if (0 != xpackhandle) {
					bcc.SetRequestType(xpackhandle, func);
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
							.getBytes(), "A".getBytes());// ��������
					try {
						bcc.SetStringFieldByName(xpackhandle, 0, "sall_name"
								.getBytes(), tcustomer.getCustname().getBytes("GBK"));
					} catch (UnsupportedEncodingException e1) {
						// TODO Auto-generated catch block
						e1.printStackTrace();
					}// ����
					bcc.SetStringFieldByName(xpackhandle, 0, "semail2"
							.getBytes(), tcustomer.getIdno().getBytes());// ���֤��
					bcc.SetStringFieldByName(xpackhandle, 0, "spager"
							.getBytes(), tcustomer.getStuempno().getBytes());// ѧ��
					bcc.SetStringFieldByName(xpackhandle, 0, "scard0"
							.getBytes(), bankcardno.getBytes());
					boolean bccret = false;

					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 20000, errcode, errmsg);

					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {

							int[] intRec = new int[1];
							byte[] byteStrRec = new byte[256];
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lsafe_level"
									.getBytes(), intRec);
							if (0 == intRec[0]) {
								try {
									System.out.println("update local card no:"+bankcardno+"****");
									bankPersistence.updateBankAccountToDB(
											tcustomer.getCustid(), "00",
											bankcardno);
								} catch (DBSystemException e) {
									// TODO: handle exception
									e.printStackTrace();
									throw new DBSystemException(
											"���ж˸��°󶨳ɹ����������ݿ���°�ʧ��");
								}
								return bankcardno;

							} else {
							try{
								System.out.println("remove local card no:"+bankcardno+"****");
								bankPersistence.removeBankAccountFromDB(tcustomer.getCustid(), "00", bankcardno);
							} catch (DBSystemException e) {
								// TODO: handle exception
								e.printStackTrace();
								throw new DBSystemException(
										"���ж˸��°󶨳ɹ����������ݿ���°�ʧ��");
							}
							Arrays.fill(byteStrRec, (byte) 0);
								bcc
										.GetStringFieldByName(xpackhandle, 0,
												"vsvarstr0".getBytes(),
												byteStrRec, 256);
								throw new BccBgInfoException("���з�����Ϣ:"+BccUtil
										.getStringFromByte(byteStrRec));
							}

						} else {
							// ʧ��
							if (0 < RecordCount[0]) {

								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);
								// throw exception plus vmess
								throw new BccBgInfoException(vs_mess);
							} else {
								// throw exception //unknow err
								throw new BccException("δ֪����");
							}

						}

					} else {
						// ����ʧ��
						throw new BccException("����ʧ�ܣ�����������ߺ�̨����Ӧ");
					}
				} else {
					throw new BccException("cpack��ʼ��ʧ��");
				}

			} catch (UnsatisfiedLinkError e) {
				// e.printStackTrace();
				throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}

		}else{
			throw new BccBgInfoException("�����п����Ѿ��󶨣��������");
		}
	}

	public boolean deleteBankBindingAccount(TCustomer tcustomer,
			String stuempno, boolean flag) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 5000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"bank_account_query", 270001);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(),
						"D".getBytes());// ��������
				try {
					bcc.SetStringFieldByName(xpackhandle, 0,
							"sall_name".getBytes(), tcustomer.getCustname()
									.getBytes("GBK"));
				} catch (UnsupportedEncodingException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}// ����
				bcc.SetStringFieldByName(xpackhandle, 0, "semail2".getBytes(),
						tcustomer.getIdno().getBytes());// ���֤��
				bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(),
						tcustomer.getStuempno().getBytes());// ѧ��
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);				
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						int[] intRec = new int[1];
						byte[] byteStrRec = new byte[256];
						Arrays.fill(intRec, 0);
						bcc.GetIntFieldByName(xpackhandle, 0, "lsafe_level"
								.getBytes(), intRec);
						if (0 == intRec[0]) {
							if (flag) {
								try {
									bankPersistence.removeBankAccountFromDB(
											tcustomer.getCustid(), "00", "");
								} catch (Exception e) {
									// TODO: handle exception
									e.printStackTrace();
									throw new DBSystemException(
											"���ж�ɾ���ɹ����������ݿ����ɾ��ʧ��");
								}
							}
							return true;

						} else {
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,
									"vsvarstr0".getBytes(), byteStrRec, 256);
							throw new BccBgInfoException("���з�����Ϣ:"+BccUtil
									.getStringFromByte(byteStrRec));
						}
					} else {
						// ʧ��
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							String vs_mess = BccUtil.getStringFromByte(vsmess);
							// throw exception plus vmess
							throw new BccBgInfoException(vs_mess);
						} else {
							// throw exception //unknow err
							throw new BccException("δ֪����");
						}

					}

				} else {
					// ����ʧ��
					throw new BccException("����ʧ�ܣ�����������ߺ�̨����Ӧ");
				}
			} else {
				throw new BccException("cpack��ʼ��ʧ��");
			}

		} catch (UnsatisfiedLinkError e) {
			// e.printStackTrace();
			throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

}
