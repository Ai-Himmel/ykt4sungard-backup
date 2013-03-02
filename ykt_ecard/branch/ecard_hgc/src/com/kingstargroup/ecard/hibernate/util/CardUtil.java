/**
 * 
 */
package com.kingstargroup.ecard.hibernate.util;

import java.util.List;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.struts.action.ActionError;
import org.hibernate.Transaction;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.ecard.BccctlInit;
import com.kingstargroup.ecard.KSConfiguration;
import com.kingstargroup.ecard.common.BasicUtil;
import com.kingstargroup.ecard.exceptions.CardAlreadyLostException;
import com.kingstargroup.ecard.exceptions.CardAlreadyOffException;
import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.exceptions.ProcessCardLossException;
import com.kingstargroup.ecard.hibernate.card.CardPersistence;
import com.kingstargroup.ecard.hibernate.card.TCifDept;
import com.kingstargroup.ecard.hibernate.card.TPifCard;
import com.kingstargroup.ecard.hibernate.card.TPifCardlossinfo;
import com.kingstargroup.ecard.hibernate.card.TPifCardlossinfoKey;
import com.kingstargroup.ecard.hibernate.card.TPifSubsystem;
import com.kingstargroup.ecard.hibernate.card.TTifBlackSheet;
import com.kingstargroup.ecard.hibernate.card.TTifMeslist;
import com.kingstargroup.ecard.hibernate.card.TTifTradeserial;
import com.kingstargroup.ecard.hibernate.customer.TCifCustomer;
import com.kingstargroup.ecard.hibernate.sysdate.SysDatePersistence;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.util.lang.FastStringBuffer;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd. File name: CardUtil.java
 * Description: Modify History: �������� ������ ����ʱ�� ��������
 * =================================== ���� Xiao Qi 2005-9-2
 * 
 * @author Xiao Qi
 * @version
 * @since 1.0
 */
public class CardUtil extends BasicUtil {
	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static List getAvailableCards(String customerId)
			throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class
				.getName());
		List cards = null;
		Transaction t = beginTransaction();
		try {
			cards = persistence.getAvailableCards(customerId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return cards;
	}

	public static TCifDept getDept(String deptNo) throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class
				.getName());
		TCifDept dept = null;
		Transaction t = beginTransaction();
		try {
			dept = persistence.getDept(deptNo);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return dept;
	}

	public static TPifCard getCardById(Integer cardId) throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class
				.getName());
		TPifCard card = null;
		Transaction t = beginTransaction();
		try {
			card = persistence.getCardById(cardId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return card;
	}

	/**
	 * Description:
	 * 
	 * @param customerId
	 * @return
	 * @throws PortalException
	 *             Modify History:
	 */
	public static TPifCard getCurrentCard(String customerId)
			throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class
				.getName());
		Transaction t = beginTransaction();
		TPifCard card = null;
		try {
			card = persistence.getCurrentValidCard(customerId);
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return card;
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
	public static int getCardStatus(String customerId, String state)
			throws PortalException {
		CardPersistence persistence = (CardPersistence) getPersistence(CardPersistence.class
				.getName());
		int status = 0;
		Transaction t = beginTransaction();
		try {
			TPifCard card = persistence.getCardByCusIdAndState(customerId,
					state);
			if (card != null) {
				int type = card.getTypeId().intValue();
				if (type == 1) {
					status = 100559;// �ÿͻ���ʽ��δ��ʧ,���ܰ���ʱ��
				} else {
					status = 100560;// �ÿͻ���һ����ʱ��������ʹ��,�����ٰ���ʱ��
				}
			}
			t.commit();
		} catch (DBSystemException e) {
			t.rollback();
			throw e;
		} finally {
			closeSession();
		}
		return status;
	}

	/**
	 * Description:�����û���ѧ/���Ź�ʧ��Ӧ�Ŀ�
	 * 
	 * @param customerId
	 *            Modify History:
	 */
	public static void processLostCard(String stuempNo, String cardId)
			throws PortalException {
		CardPersistence cardPst = (CardPersistence) getPersistence(CardPersistence.class
				.getName());
		SysDatePersistence sysPst = (SysDatePersistence) getPersistence(SysDatePersistence.class
				.getName());
		TCifCustomer customer = CustomerUtil.getCustomerByStuempNo(stuempNo);
		Transaction t = beginTransaction();
		try {
			if (customer != null) {
				if ("direct".equals(KSConfiguration.getInstance().getProperty(
						"constant.bccclt"))) {
					String customerId = (customer == null ? "" : customer
							.getCutId().toString());
					TPifCard card = cardPst.getCardById(new Integer(cardId));// �ȵõ���Ӧ����������
					if (card == null) {
						throw new ProcessCardLossException();
					}
					/*
					 * ������Ѿ�Ϊ��ע��״̬
					 */
					if (card.getStateId().equals(
							EcardConstants.CARD_WRITE_OFF_STATUS)) {
						throw new CardAlreadyOffException();
					}
					/*
					 * ������Ѿ�Ϊ��ʧ״̬
					 */
					if (card.getStateId().charAt(1) == EcardConstants.CARD_LOST_FLAG) {
						throw new CardAlreadyLostException();
					}
					/*
					 * �õ����ݿ�����ʱ��
					 */
					String dateTime = sysPst.getSysDate(0);
					String operateDate = dateTime.substring(0, 8);
					String operateTime = dateTime.substring(8);
					/*
					 * �õ�����������
					 */
					String endDateTime = sysPst.getSysDate(cardPst
							.getReapplyDays());
					/*
					 * ���ù�ʧ��Ϣ����
					 */
					TPifCardlossinfoKey lossKey = new TPifCardlossinfoKey();
					lossKey.setCardId(card.getCardId());
					lossKey.setOperateDate(operateDate);
					lossKey.setOperateTime(operateTime);
					/*
					 * ���ù�ʧ��Ϣ
					 */
					TPifCardlossinfo lossInfo = new TPifCardlossinfo();
					lossInfo.setId(lossKey);
					lossInfo.setBeginDate(operateDate);
					lossInfo.setEndDate(endDateTime.substring(0, 8));
					lossInfo.setStateId(Integer.valueOf(String
							.valueOf(EcardConstants.CARD_LOST_FLAG)));
					cardPst.addCardLossInfo(lossInfo);// ��ӹ�ʧ��Ϣ�����ݿ���
					/*
					 * ����������͹㲥��Ϣ����
					 */
					if (card.getStateId().charAt(2) == '0') {
						/*
						 * ���ú�������Ϣ
						 */
						TTifBlackSheet blackSheet = new TTifBlackSheet();
						blackSheet.setCardId(card.getCardId());
						blackSheet.setIsAd(new Integer(0));
						blackSheet.setOperateDate(operateDate);
						blackSheet.setOperateTime(operateTime);
						blackSheet.setStateId(new Integer(1));
						blackSheet.setVolume(dateTime.substring(2));// ȥ������ʱ���ǰ2λ
						blackSheet.setValiddate("501230121212");
						cardPst.addBlackSheet(blackSheet);
						/*
						 * ���ù㲥������Ϣ
						 */
						TTifMeslist mesList = new TTifMeslist();
						// mesList.setMesid(new
						// Integer(cardPst.getKeyvalueByCode("T_TIF_MESLIST")));
						FastStringBuffer mesContent = new FastStringBuffer();
						mesContent.append("<CARDID>").append(card.getCardId())
								.append("</CARDID>").append("<VERNUM>").append(
										blackSheet.getVolume()).append(
										"</VERNUM>").append("<ADDDELSIGN>")
								.append(blackSheet.getIsAd()).append(
										"</ADDDELSIGN>");
						mesList.setIncontent(mesContent.toString());
						mesList.setFunid(new Integer(930005));
						mesList.setLevel(new Integer(3));
						mesList.setCardNo(card.getCardId());// set card_no
						mesList.setMaxSendCnt(new Integer(10));// magic number
																// 10
						mesList.setDelFlag("0");
						mesList.setEcode(new Integer(9999));
						mesList.setStateid(new Integer(3));
						mesList.setIndt(dateTime);
						mesList.setRecvcount(Integer.valueOf("0"));
						mesList.setSeq(Integer.valueOf("0"));
						mesList.setMsgtype(Integer.valueOf("1"));
						// get subsystem list
						List subsysList = cardPst.getSubSysIdByTypeAndState(12,
								3);
						for (int i = 0; i < subsysList.size(); i++) {
							TTifMeslist cloneMesList = new TTifMeslist();
							BeanUtils.copyProperties(cloneMesList, mesList);
							// cloneMesList.setMesid(new
							// Integer(cardPst.getKeyvalueByCode("T_TIF_MESLIST")));//temporary
							// use
							cloneMesList
									.setDeviceId(((TPifSubsystem) subsysList
											.get(i)).getSystemId());
							cardPst.addMsg(cloneMesList);
						}
					}
					/*
					 * ���¿�״̬Ϊ�ѹ�ʧ  
					 */
					String oldstateId = card.getStateId();
					System.out.println("oldstarted="+oldstateId);
					oldstateId =oldstateId.substring(0,1)+"1"+oldstateId.substring(2,4);
					System.out.println("oldstarted="+oldstateId);
					card.setStateId(oldstateId);
					
					cardPst.update(card);
					/*
					 * ���뿨��ʧ��ˮ
					 */
					TTifTradeserial tradeSerial = new TTifTradeserial();
					tradeSerial.setSerialNo(new Integer(cardPst
							.getKeyvalueByCode("T_TIF_TRADESERIAL")));
					tradeSerial.setOperateDate(operateDate);
					tradeSerial.setOperateTime(operateTime);
					tradeSerial.setCollectDate(operateDate);
					tradeSerial.setCollectTime(operateTime);
					tradeSerial.setEnteractDate(operateDate);
					tradeSerial.setEnteractTime(operateTime);
					tradeSerial.setMaindeviceId(new Integer(0));
					tradeSerial.setDeviceId(new Integer(0));
					tradeSerial.setOperCode("ecardweb");
					tradeSerial.setSerialState(new Integer(9));
					tradeSerial.setSerialType(new Integer(930001));
					tradeSerial.setCustomerId(Integer.valueOf(customerId));
					tradeSerial.setCardId(card.getCardId());
					cardPst.addTradeSerial(tradeSerial);
					t.commit();
				} else {

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
									.getBytes(), Integer.parseInt(customer.getCutId().toString()));// �ͻ���
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
				}
			}else{
				throw new ProcessCardLossException("ϵͳ���ܳ�ʱ�����쳣�������µ�¼�����ԣ�");				
			}
		} catch (PortalException e) {
			t.rollback();
			e.printStackTrace();
			throw e;
		} catch (Exception he) {
			t.rollback();
			he.printStackTrace();
			throw new DBSystemException(he);
		} finally {
			closeSession();
		}
	}

}
