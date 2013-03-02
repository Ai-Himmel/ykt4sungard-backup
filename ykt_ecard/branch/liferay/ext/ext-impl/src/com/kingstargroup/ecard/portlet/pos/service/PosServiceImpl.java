package com.kingstargroup.ecard.portlet.pos.service;

import java.io.UnsupportedEncodingException;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.BccBgInfoException;
import com.kingstargroup.ecard.exceptions.BccException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.pos.PosPersistence;
import com.kingstargroup.ecard.util.BccUtil;

/**
 * pos��ˢ����ѯ
 * @author Yiming.You
 *
 */
public class PosServiceImpl extends PosServiceBase {
	/**
	 * @param lvol0			�豸���
	 * @param snote			�豸����
	 * @param sdate0		��ʼ����
	 * @param sdate1		��������
	 * @param stime0		��ʼʱ��
	 * @param stime1		����ʱ��
	 * 
	 * @return
	 */
	public List getPosDetail(String lvol0, String snote, String sdate0,String sdate1, String stime0, String stime1) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 600);
		int func = KSConfiguration.getInstance().getPropertyAsInt("pos_detail",846725);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List result = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				if(StringUtils.isNotBlank(lvol0)){
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),Integer.parseInt(lvol0));
				}
				if(StringUtils.isNotBlank(snote)){
					bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),snote.getBytes());				
				}
				if(StringUtils.isNotBlank(sdate0)){
					sdate0 = sdate0.replaceAll("-", "");
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate0".getBytes(),sdate0.getBytes());
				}
				if(StringUtils.isNotBlank(sdate1)){
					sdate1 = sdate1.replaceAll("-", "");
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),sdate1.getBytes());
				}
				if(StringUtils.isNotBlank(stime0)){
					bcc.SetStringFieldByName(xpackhandle, 0, "stime0".getBytes(),stime0.getBytes());
				}
				if(StringUtils.isNotBlank(stime1)){
					bcc.SetStringFieldByName(xpackhandle, 0, "stime1".getBytes(),stime1.getBytes());
				}

				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 30000, errcode, errmsg);

				while (true) {
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							for (int i = 0; i < RecordCount[0]; i++) {
								byte[] byteStrRec = new byte[256];
								int[] intRec = new int[1];
								double[] doubleRec = new double[1];
								
								Map row = new HashMap();
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lvol0".getBytes(), intRec);
								row.put("deviceId", intRec[0]);
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"snote".getBytes(),byteStrRec, 256);
								row.put("deviceName", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"sdate0".getBytes(),byteStrRec, 256);
								row.put("date", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"stime0".getBytes(),byteStrRec, 256);
								row.put("time", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"sall_name".getBytes(),byteStrRec, 256);
								row.put("custName", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"spager".getBytes(),byteStrRec, 256);
								row.put("custNo", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(doubleRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle,i, "damt0".getBytes(),doubleRec);
								row.put("money", doubleRec[0]);
							

								result.add(row);
							}
							
							if(!bcc.HaveNextPack(xpackhandle)){
								break;
							} else {
								bccret = bcc.CallNext(xpackhandle, 30000, errcode,errmsg);
							}
						} else {
							// ʧ��
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);
								// throw exception plus vmess
								throw new BccBgInfoException(vs_mess);
							} else {
								throw new BccException("δ֪����");
							}
						}
					} else {
						throw new BccException("����ʧ��");
					}
				}

				return result;
			} else {
				throw new BccException("cpack��ʼ��ʧ��");
			}
		} catch (UnsatisfiedLinkError e) {
			throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

	/**
	 * @param lvol0			�豸���
	 * @param snote			�豸����
	 * @param sdate0		��ʼ����
	 * @param sdate1		��������
	 * @param stime0		��ʼʱ��
	 * @param stime1		����ʱ��
	 * 
	 * @return
	 */
	public List getPostReport(String lvol0, String snote, String sdate0,String sdate1, String stime0, String stime1) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 600);
		int func = KSConfiguration.getInstance().getPropertyAsInt("pos_report",846726);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List result = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				if(StringUtils.isNotBlank(lvol0)){
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),Integer.parseInt(lvol0));
				}
				if(StringUtils.isNotBlank(snote)){
					bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),snote.getBytes());
				}
				if(StringUtils.isNotBlank(sdate0)){
					sdate0 = sdate0.replaceAll("-", "");
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate0".getBytes(),sdate0.getBytes());
				}
				if(StringUtils.isNotBlank(sdate1)){
					sdate1 = sdate1.replaceAll("-", "");
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),sdate1.getBytes());
				}
				if(StringUtils.isNotBlank(stime0)){
					bcc.SetStringFieldByName(xpackhandle, 0, "stime0".getBytes(),stime0.getBytes());
				}
				if(StringUtils.isNotBlank(stime1)){
					bcc.SetStringFieldByName(xpackhandle, 0, "stime1".getBytes(),stime1.getBytes());
				}

				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 30000, errcode, errmsg);

				while (true) {
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							for (int i = 0; i < RecordCount[0]; i++) {
								byte[] byteStrRec = new byte[256];
								int[] intRec = new int[1];
								double[] doubleRec = new double[1];
								
								Map row = new HashMap();
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lvol0".getBytes(), intRec);
								row.put("deviceId", intRec[0]);
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"snote".getBytes(),byteStrRec, 256);
								row.put("deviceName", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"sdate0".getBytes(),byteStrRec, 256);
								row.put("date", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"stime0".getBytes(),byteStrRec, 256);
								row.put("time", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lvol1".getBytes(), intRec);
								row.put("pegCount", intRec[0]);
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lvol2".getBytes(), intRec);
								row.put("chargeCount", intRec[0]);
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lvol3".getBytes(), intRec);
								row.put("totalCount", intRec[0]);								

								result.add(row);
							}
							
							if(!bcc.HaveNextPack(xpackhandle)){
								break;
							} else {
								bccret = bcc.CallNext(xpackhandle, 30000, errcode,errmsg);
							}
						} else {
							// ʧ��
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);
								// throw exception plus vmess
								throw new BccBgInfoException(vs_mess);
							} else {
								throw new BccException("δ֪����");
							}
						}
					} else {
						throw new BccException("����ʧ��");
					}
				}

				return result;
			} else {
				throw new BccException("cpack��ʼ��ʧ��");
			}
		} catch (UnsatisfiedLinkError e) {
			throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

	/**
	 * @param spager		ѧ����
	 * @param sall_name		����
	 * @param scert_no		����
	 * @param sdate0		��ʼ����
	 * @param sdate1		��������
	 * @param stime0		��ʼʱ��
	 * @param stime1		����ʱ��
	 * 
	 * @return
	 */
	public List getPosSwipeDetail(String spager, String sall_name,String scert_no, String sdate0, String sdate1, String stime0,String stime1) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 600);
		int func = KSConfiguration.getInstance().getPropertyAsInt("pos_swipedetail",846723);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List result = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				if(StringUtils.isNotBlank(spager)){
					bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(),spager.getBytes());
				}
				if(StringUtils.isNotBlank(sall_name)){
					try {
						bcc.SetStringFieldByName(xpackhandle, 0, "sall_name".getBytes(),sall_name.getBytes("GBK"));
					} catch (UnsupportedEncodingException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				if(StringUtils.isNotBlank(scert_no)){
					bcc.SetStringFieldByName(xpackhandle, 0, "scert_no".getBytes(),scert_no.getBytes());
				}
				if(StringUtils.isNotBlank(sdate0)){
					sdate0 = sdate0.replaceAll("-", "");
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate0".getBytes(),sdate0.getBytes());
				}
				if(StringUtils.isNotBlank(sdate1)){
					sdate1 = sdate1.replaceAll("-", "");
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),sdate1.getBytes());
				}
				if(StringUtils.isNotBlank(stime0)){
					bcc.SetStringFieldByName(xpackhandle, 0, "stime0".getBytes(),stime0.getBytes());
				}
				if(StringUtils.isNotBlank(stime1)){
					bcc.SetStringFieldByName(xpackhandle, 0, "stime1".getBytes(),stime1.getBytes());
				}

				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 30000, errcode, errmsg);

				while (true) {
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							for (int i = 0; i < RecordCount[0]; i++) {
								byte[] byteStrRec = new byte[256];
								int[] intRec = new int[1];
								double[] doubleRec = new double[1];
								
								Map row = new HashMap();
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"vsvarstr0".getBytes(),byteStrRec, 256);
								row.put("departmentName", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"sall_name".getBytes(),byteStrRec, 256);
								row.put("custName", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"spager".getBytes(),byteStrRec, 256);
								row.put("custNo", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"sdate0".getBytes(),byteStrRec, 256);
								row.put("date", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"stime0".getBytes(),byteStrRec, 256);
								row.put("time", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"snote".getBytes(),byteStrRec, 256);
								row.put("device", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(doubleRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle,i, "damt0".getBytes(),doubleRec);
								row.put("money", doubleRec[0]);								

								result.add(row);
							}
							
							if(!bcc.HaveNextPack(xpackhandle)){
								break;
							} else {
								bccret = bcc.CallNext(xpackhandle, 30000, errcode,errmsg);
							}
						} else {
							// ʧ��
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);
								// throw exception plus vmess
								throw new BccBgInfoException(vs_mess);
							} else {
								throw new BccException("δ֪����");
							}
						}
					} else {
						throw new BccException("����ʧ��");
					}
				}

				return result;
			} else {
				throw new BccException("cpack��ʼ��ʧ��");
			}
		} catch (UnsatisfiedLinkError e) {
			throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

	/**
	 * @param lvol0			���1����ְ��-��ʽ��3�������շ��ࣻ2������
	 * @param spager		ѧ����
	 * @param sall_name		����
	 * @param scert_no		����
	 * @param sdate0		��ʼ�·�
	 * @param sdate1		�����·�
	 * 
	 * @return
	 */
	public List getPosSwipeReport(String lvol0, String spager, String sall_name,String scert_no, String sdate0, String sdate1) throws PortalException {
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// ��̨drtp���ܺ�
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 600);
		int func = KSConfiguration.getInstance().getPropertyAsInt("pos_swipereport",846724);// ��̨ҵ���ܺ�
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// Ĭ�����Դ���
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		List result = new ArrayList();
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				if(StringUtils.isNotBlank(lvol0)){
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),Integer.parseInt(lvol0));
				}
				if(StringUtils.isNotBlank(spager)){
					bcc.SetStringFieldByName(xpackhandle, 0, "spager".getBytes(),spager.getBytes());
				}
				if(StringUtils.isNotBlank(sall_name)){
					try {
						bcc.SetStringFieldByName(xpackhandle, 0, "sall_name".getBytes(),sall_name.getBytes("GBK"));
					} catch (UnsupportedEncodingException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					}
				}
				if(StringUtils.isNotBlank(scert_no)){
					bcc.SetStringFieldByName(xpackhandle, 0, "scert_no".getBytes(),scert_no.getBytes());
				}
				if(StringUtils.isNotBlank(sdate0)){
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate0".getBytes(),sdate0.getBytes());
				}
				if(StringUtils.isNotBlank(sdate1)){
					bcc.SetStringFieldByName(xpackhandle, 0, "sdate1".getBytes(),sdate1.getBytes());
				}

				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,mainfunction, 30000, errcode, errmsg);

				while (true) {
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {
							for (int i = 0; i < RecordCount[0]; i++) {
								byte[] byteStrRec = new byte[256];
								int[] intRec = new int[1];
								double[] doubleRec = new double[1];
								
								Map row = new HashMap();
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lserial1".getBytes(), intRec);
								row.put("lserial1", intRec[0]);
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"sdate0".getBytes(),byteStrRec, 256);
								row.put("sdate0", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"vsvarstr0".getBytes(),byteStrRec, 256);
								row.put("departmentName", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"sall_name".getBytes(),byteStrRec, 256);
								row.put("custName", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"spager".getBytes(),byteStrRec, 256);
								row.put("custNo", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(byteStrRec, (byte) 0);
								bcc.GetStringFieldByName(xpackhandle, i,"scard0".getBytes(),byteStrRec, 256);
								row.put("chargeType", BccUtil.getStringFromByte(byteStrRec));
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lvol0".getBytes(), intRec);
								row.put("totalCount", intRec[0]);
								
								Arrays.fill(intRec, 0);
								bcc.GetIntFieldByName(xpackhandle, i, "lvol1".getBytes(), intRec);
								row.put("dayCount", intRec[0]);
								
								Arrays.fill(doubleRec, 0);
								bcc.GetDoubleFieldByName(xpackhandle,i, "damt0".getBytes(),doubleRec);
								row.put("money", doubleRec[0]);
								

								result.add(row);
							}
							
							if(!bcc.HaveNextPack(xpackhandle)){
								break;
							} else {
								bccret = bcc.CallNext(xpackhandle, 30000, errcode,errmsg);
							}
						} else {
							// ʧ��
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,"vsmess".getBytes(), vsmess, 300);
								String vs_mess = BccUtil.getStringFromByte(vsmess);
								// throw exception plus vmess
								throw new BccBgInfoException(vs_mess);
							} else {
								throw new BccException("δ֪����");
							}
						}
					} else {
						throw new BccException("����ʧ��");
					}
				}

				return result;
			} else {
				throw new BccException("cpack��ʼ��ʧ��");
			}
		} catch (UnsatisfiedLinkError e) {
			throw new BccException("��̬�����ʧ�ܣ����Ժ����ԣ�");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

	/**
	 * ������еĲ���
	 */
	public List getDepartments() {
		return posPersistence.getDepartments();
	}
}
