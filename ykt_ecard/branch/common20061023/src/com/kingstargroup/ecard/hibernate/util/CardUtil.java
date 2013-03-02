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
 * Description: Modify History: 操作类型 操作人 操作时间 操作内容
 * =================================== 创建 Xiao Qi 2005-9-2
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
					status = 100559;// 该客户正式卡未挂失,不能办临时卡
				} else {
					status = 100560;// 该客户有一张临时卡可正常使用,不能再办临时卡
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
	 * Description:根据用户的学/工号挂失对应的卡
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
				String customerId = (customer == null ? "" : customer
						.getCutId().toString());
				TPifCard card = cardPst.getCardById(new Integer(cardId));// 先得到对应的主卡对象
				if (card == null) {
					throw new ProcessCardLossException();
				}
				/*
				 * 如果卡已经为被注销状态
				 */
				if (card.getStateId().equals(
						EcardConstants.CARD_WRITE_OFF_STATUS)) {
					throw new CardAlreadyOffException();
				}
				/*
				 * 如果卡已经为挂失状态
				 */
				if (card.getStateId().charAt(1) == EcardConstants.CARD_LOST_FLAG) {
					throw new CardAlreadyLostException();
				}
					long xpackhandle = 0;
					int drtpno = 0;
					int errcode[] = { 1 };
					byte errmsg[] = new byte[300]; 
					int branchno = 0;// 后台drtp功能号
					int mainfunction = KSConfiguration.getInstance()
							.getPropertyAsInt("mainfunction", 9000);
					int func = KSConfiguration.getInstance().getPropertyAsInt(
							"logicfunc_card_loss", 847318);// 后台业务功能号
					int tries = KSConfiguration.getInstance().getPropertyAsInt(
							"tries", 3);// 默认重试次数
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
									.getBytes(), Integer.parseInt(customerId));// 客户号
							bcc.SetIntFieldByName(xpackhandle, 0, "lvol1"
									.getBytes(), Integer.parseInt("0"));// 交易卡号
							bcc.SetIntFieldByName(xpackhandle, 0, "lvol2"
									.getBytes(), Integer.parseInt("0"));// 交易卡号
							/*bcc.SetStringFieldByName(xpackhandle, 0, "semp_pwd"
									.getBytes(), "1".getBytes());// 密码
							bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0"
									.getBytes(), "1".getBytes());// 校验密码
*/							bcc.SetStringFieldByName(xpackhandle, 0,
									"scust_limit".getBytes(), "web".getBytes());// 操作员

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
									// 失败
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
										String vs_mess = new String(vsmess, 0,i);
										
										throw new ProcessCardLossException(vs_mess+RetCode[0]);
									} else {
										throw new ProcessCardLossException("后台处理失败");
									}

								}

							} else {
								// 请求失败
								throw new ProcessCardLossException("请求失败");

							}
						}else{
							throw new ProcessCardLossException("系统出现异常，cpace不存在！");
						}

					} catch (Exception e) {
						// TODO: handle exception
						throw new ProcessCardLossException("系统出现异常，请稍后重试！");
					} catch (UnsatisfiedLinkError e) {
						throw new ProcessCardLossException("动态库加载失败，请稍后重试！");
					} finally {
						if (xpackhandle != 0) {
							bcc.DeleteXpackHandle(xpackhandle);
						}
					}
				}else{
				 throw new ProcessCardLossException("系统可能超时或发生异常，请重新登录后重试！");				
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
