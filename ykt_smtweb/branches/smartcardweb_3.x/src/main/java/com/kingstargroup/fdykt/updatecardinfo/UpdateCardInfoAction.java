package com.kingstargroup.fdykt.updatecardinfo;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.ActionMessages;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.UpdateInfoDTO;
import com.kingstargroup.fdykt.util.BccUtil;

public class UpdateCardInfoAction extends Action{
	
	private static final Logger logger = Logger
	.getLogger(UpdateCardInfoAction.class);
	
	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = updateCard(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}
	
	private ActionForward updateCard(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String CardPhyId = request.getParameter("CardPhyId"); // 物理卡号
		String cardbal = request.getParameter("cardbal");
		String payCardCnt = request.getParameter("payCardCnt");
		String dptCardCnt = request.getParameter("dptCardCnt");
		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		ActionErrors errors = new ActionErrors();

		int deviceid = -2;
		try {
			String reqip = request.getRemoteAddr();
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"deviceid.notregister"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"deviceid.notregister"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		
		
		//
		UpdateInfoDTO updateinfo = null;
		try {
			DB2AccountDAO accountdao = new DB2AccountDAO();
			updateinfo = accountdao.getUpdateInfoByCardphyid(CardPhyId);
			if (updateinfo == null) {
				return (mapping.findForward("isnull"));
			}
		} catch (Exception e) {
			logger.error("查询客户信息失败");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError("查询客户信息失败"));
			saveErrors(request, errors);
			return (mapping.findForward("failure"));
		}
		
		request.setAttribute("CardPhyId", CardPhyId);
		request.setAttribute("UpdateInfoDTO", updateinfo);
		
		
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(CardPhyId);
		} catch (Exception e) {
			System.out.println("卡信息读取失败");
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"cardinfo.geterror"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}

		try {
			long xpackhandle = 0;
			int drtpno = 0;
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			int branchno = 0;// 后台drtp功能号
			int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
					"mainfunction1", 9000);
			int func = KSConfiguration.getInstance().getPropertyAsInt(
					"logicfunc_consumerlimit_reset", 846320);// 后台业务功能号
			int[] RetCode = new int[1];
			int[] RecordCount = new int[1];
			bccclt bcc = null;
			try {
				bcc = BccctlInit.getBccctlInstance();
				xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
						.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
				if (0 != xpackhandle) {
					bcc.SetRequestType(xpackhandle, func);

					bcc.SetStringFieldByName(xpackhandle, 0, "lwithdraw_flag"
							.getBytes(), String.valueOf(deviceid).getBytes());// 终端号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
							Integer.parseInt(String.valueOf(card.getCardno())));// 卡号
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
							Integer.parseInt(dptCardCnt));// 充值次数
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
							Integer.parseInt(payCardCnt));// 交易次数
					bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
							Integer.parseInt(cardbal));// 卡余额
					bcc.SetStringFieldByName(xpackhandle, 0, "sstation1"
							.getBytes(), CardPhyId.getBytes());// 物理卡号
					bcc.SetStringFieldByName(xpackhandle, 0, "sstatus1"
							.getBytes(), "1".getBytes());

					boolean bccret = false;
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
								mainfunction, 5000, errcode, errmsg);
					if (bccret) {
						bcc.GetRetCode(xpackhandle, RetCode);
						bcc.GetRecordCount(xpackhandle, RecordCount);
						if (0 == RetCode[0]) {						
							return mapping.findForward("success");
						} else {
							// 失败
							if (0 < RecordCount[0]) {
								byte[] vsmess = new byte[300];
								bcc.GetStringFieldByName(xpackhandle, 0,
										"vsmess".getBytes(), vsmess, 300);
								String vs_mess =BccUtil.getStringFromByte(vsmess);
								errors.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionError("back.error",vs_mess));
								saveErrors(request, errors);
								return mapping.findForward("failure");
							} else {
								errors.add(ActionMessages.GLOBAL_MESSAGE,
										new ActionError("back.error","后台处理失败"));
								saveErrors(request, errors);
								return mapping.findForward("failure");
							}

						}

					} else {
						// 请求失败

						errors.add(ActionMessages.GLOBAL_MESSAGE,
								new ActionError("errors.request"));
						saveErrors(request, errors);
						return mapping.findForward("failure");

					}
				}
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"system.error"));
				saveErrors(request, errors);
				return mapping.findForward("failure");

			} catch (Exception e) {
				// TODO: handle exception
				logger.error(e.getMessage());
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"system.error"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			} catch (UnsatisfiedLinkError e) {
				logger.error(e.getMessage());
				errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
						"system.error"));
				saveErrors(request, errors);
				return mapping.findForward("failure");
			} finally {
				if (xpackhandle != 0) {
					bcc.DeleteXpackHandle(xpackhandle);
				}
			}
		} catch (Exception e) {
			errors.add(ActionMessages.GLOBAL_MESSAGE, new ActionError(
					"cardinfo.fresherror"));
			saveErrors(request, errors);
			return mapping.findForward("failure");
		}
	}
}
