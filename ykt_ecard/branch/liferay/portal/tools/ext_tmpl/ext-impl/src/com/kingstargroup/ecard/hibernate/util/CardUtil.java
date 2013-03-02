/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.exceptions.ProcessCardLossException;
import com.kingstargroup.ecard.hibernate.card.CardPersistence;
import com.kingstargroup.ecard.hibernate.card.TCard;
import com.kingstargroup.ecard.hibernate.card.TDept;
import com.kingstargroup.ecard.hibernate.customer.TCustomer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name: CardUtil.java
 * Description: Modify History: �������� ������ ����ʱ�� ��������
 * =================================== ���� Xiao Qi 2005-9-2
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class CardUtil{
	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static List getAvailableCards(String custid)
			throws PortalException {
		return getPersistence().getAvailableCards(custid);
	}

	public static TDept getDept(String deptNo) throws PortalException {
		return getPersistence().getDept(deptNo);
	}

	public static TCard getCardByNo(Long cardno) throws PortalException {
		return getPersistence().getCardByno(cardno);
	}

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static TCard getCurrentCard(String custid)
			throws PortalException {
		return getPersistence().getCurrentValidCard(custid);
	}

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @param state
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static int getCardStatus(String custid, String state)
			throws PortalException {

		int status = 0;

			TCard card = getPersistence().getCardByCustidAndState(custid, state);
			if (card != null) {
				int type = card.getCardtype().intValue();
				if (type == 1) {
					status = 100559;// �ÿͻ���ʽ��δ��ʧ,���ܰ���ʱ��
				} else {
					status = 100560;// �ÿͻ���һ����ʱ��������ʹ��,�����ٰ���ʱ��
				}
			}
		return status;
	}

	/**
	 * Description:�����û���ѧ/���Ź�ʧ��Ӧ�Ŀ�
	 * 
	 * @param customerId
	 *            Modify History:
	 */
	public static void processLostCard(String stuempno, String cardId)
			throws PortalException {
		TCustomer customer = CustomerUtil.getCustomerByStuempno(stuempno);
		try {
			if (customer != null) {
					long xpackhandle = 0;
					int drtpno = 0;
					int errcode[] = { 1 };
					byte errmsg[] = new byte[300];
					int branchno = 0;// ��̨drtp���ܺ�
					int mainfunction = KSConfiguration.getInstance()
							.getPropertyAsInt("mainfunction", 9000);
					int func = KSConfiguration.getInstance().getPropertyAsInt(
							"logicfunc_card_loss", 847318);// ��̨ҵ���ܺ�
					int tries = KSConfiguration.getInstance().getPropertyAsInt(
							"tries", 3);// Ĭ�����Դ���
					int[] RetCode = new int[1];
					int[] RecordCount = new int[1];
					bccclt bcc = null;
					try {
						bcc = BccctlInit.getBccctlInstance();
						xpackhandle = bcc.NewXpackHandle(KSConfiguration
								.getInstance().getProperty("cpackfile",
										"/opt/cpack.dat").getBytes());
						if (0 != xpackhandle) {
							bcc.SetRequestType(xpackhandle, func);
							bcc.SetIntFieldByName(xpackhandle, 0, "lvol0"
									.getBytes(), Integer.parseInt(customer.getCustid().toString()));// �ͻ���
							bcc.SetIntFieldByName(xpackhandle, 0, "lvol1"
									.getBytes(), Integer.parseInt("0"));// ���׿���
							bcc.SetIntFieldByName(xpackhandle, 0, "lvol2"
									.getBytes(), Integer.parseInt("0"));// ���׿���
							bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd"
									.getBytes(), "1".getBytes());// ����
							bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
									.getBytes(), "1".getBytes());// У������
							bcc.SetStringFieldByName(xpackhandle, 0,
									"scust_limit".getBytes(), "web".getBytes());// ����Ա

							boolean bccret = false;
							while (--tries >= 0) {
								bccret = bcc.CallRequest(xpackhandle, drtpno,
										branchno, mainfunction, 2000, errcode,
										errmsg);
								if (bccret) {
									break;
								}
							}
							if (bccret) {
								bcc.GetRetCode(xpackhandle, RetCode);
								bcc.GetRecordCount(xpackhandle, RecordCount);
								if (0 != RetCode[0]) {
									// ʧ��
									if (0 < RecordCount[0]) {
										byte[] vsmess = new byte[300];
										bcc.GetStringFieldByName(xpackhandle,
												0, "vsmess".getBytes(), vsmess,
												300);
										int i;
										for (i = 0; i < vsmess.length; i++) {
											if (vsmess[i] == 0) {
												break;
											}
										}
										String vs_mess = new String(vsmess, 0,
												i);
										throw new ProcessCardLossException(vs_mess);
									} else {
										throw new ProcessCardLossException("��̨����ʧ��");
									}

								}

							} else {
								// ����ʧ��
								throw new ProcessCardLossException("����ʧ��");

							}
						}

					} catch (Exception e) {
						// TODO: handle exception
						throw new ProcessCardLossException("ϵͳ�����쳣�����Ժ����ԣ�");
					} catch (UnsatisfiedLinkError e) {
						throw new ProcessCardLossException("��̬�����ʧ�ܣ����Ժ����ԣ�");
					} finally {
						if (xpackhandle != 0) {
							bcc.DeleteXpackHandle(xpackhandle);
						}
					}
			}else{
				throw new ProcessCardLossException("ϵͳ���ܳ�ʱ�����쳣�������µ�¼�����ԣ�");				
			}
		} catch (PortalException e) {
			e.printStackTrace();
			throw e;
		} catch (Exception he) {
			he.printStackTrace();
			throw new DBSystemException(he);
		}
	}
	
	
	public static CardPersistence getPersistence() {
		return _getUtil()._persistence;
	}

	public void setPersistence(CardPersistence persistence) {
		_persistence = persistence;
	}

	private static CardUtil _getUtil() {
		if (_util == null) {
			_util = (CardUtil)com.liferay.portal.kernel.bean.BeanLocatorUtil.locate(_UTIL);
		}

		return _util;
	}

	private static final String _UTIL = CardUtil.class.getName();
	private static CardUtil _util;
	private CardPersistence _persistence;

}
