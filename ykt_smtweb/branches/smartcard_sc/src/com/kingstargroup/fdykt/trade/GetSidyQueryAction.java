package com.kingstargroup.fdykt.trade;

import java.math.BigDecimal;
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstar.bcc.bccclt;
import com.kingstargroup.fdykt.BccctlInit;
import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.util.BdUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

/**
 * <p>Title:Test</p>
 * <p>Description: </p>
 * <p>Copyright: Copyright (c) 2004</p>
 * <p>Company: kingstargroup</p>
 * @author
 * @version 1.0
 */

public class GetSidyQueryAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GetSidyQueryAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		KSDaoSessionFactory.createSession();
		ActionForward forward = doGetSidy(mapping, form,request,response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger.error("提交事务失败");
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doGetSidy(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		DB2CardDAO carddao = new DB2CardDAO();
		DB2CustomerDAO custdao = new DB2CustomerDAO();
		String card_id =(String) request.getParameter("cardId");	
		request.setAttribute(card_id, card_id);
		String card_bala = request.getParameter("cardBala");
		String tx_cnt = request.getParameter("txCnt");
	    //String ParamKey = request.getParameter("paramKey");
		//String times = request.getParameter();
		  
		if (card_id == null || null == card_bala || "".equals(card_bala)
				|| "".equals(card_id) 
				 || null == tx_cnt || "".equals(tx_cnt)) {
			
			return mapping.findForward("failure");
		}
		int CardBala =Integer.parseInt(card_bala);
		//CardBala = CardBala / 100;
		String hexcardno = Integer.toHexString(Integer.parseInt(card_id))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;//pad left
		}
		CardDTO card = new CardDTO();
		CustomerDTO cust = new CustomerDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
			cust = custdao.getCustomerById(card.getCosumerId());
			request.setAttribute("stuemp_no", cust.getStuemp_no());
			request.setAttribute("cut_name", cust.getCut_name());
		} catch (Exception e) {
			// TODO: handle exception
			//logger.error("卡信息读取失败"); 
			
			return mapping.findForward("failure");
		}
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt("mainfunction", 7400);
		int func = KSConfiguration.getInstance().getPropertyAsInt("logicfunc_sidy", 847315);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			bcc.XPackInit(1);			
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance().getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetStringFieldByName(xpackhandle, 0, "sclose_emp"
						.getBytes(), "240100".getBytes());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));
				bcc.SetIntFieldByName(xpackhandle, 0, "damt0".getBytes(),
						CardBala);
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(tx_cnt));
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						"web".getBytes());
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 3000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							
							double[] AllsidyAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "lvol6"
									.getBytes(), AllsidyAmount);//补助总金额
							
							double[] getsidyAmount = new double[1];
							bcc.GetDoubleFieldByName(xpackhandle, 0, "lvol3"
									.getBytes(), getsidyAmount);//可领取金额
							
							int[] OutCardAmount = new int[1];
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol5"
									.getBytes(), OutCardAmount);//出卡值，也就是准备向卡里写的值。
							
							
							/*byte[] SerialNo = new byte[26];
							bcc.GetStringFieldByName(xpackhandle, 0, "sserial1"
									.getBytes(), SerialNo, 26);
							int i = 0;
							for (i = 0; i < SerialNo.length; i++) {
								if (0 == SerialNo[i]) {
									break;
								}
							}*/
							/*String cout_card_amount = String
									.valueOf(OutCardAmount[0] * 100);*/
							/*BigDecimal s = new BigDecimal(Integer.toString(OutCardAmount[0]));
							BigDecimal c = new BigDecimal("100");
							BigDecimal one = new BigDecimal("1");
							BigDecimal f = s.divide(one, 2, BigDecimal.ROUND_HALF_UP);
							
							String out_card_amount = String.valueOf(f.multiply(c).doubleValue());*/
							String out_card_amount = BdUtil.round2(OutCardAmount[0],100,2,BigDecimal.ROUND_HALF_UP);
							String all_sidy_amount = BdUtil.round(AllsidyAmount[0],100,2,BigDecimal.ROUND_HALF_UP);
							String get_sidy_amount = BdUtil.round(getsidyAmount[0],100,2,BigDecimal.ROUND_HALF_UP);
							
							//String serial_no = new String(SerialNo, 0, i);
							request.setAttribute("outCardAmount",
									out_card_amount);
							request.setAttribute("allSidyAmount",
									all_sidy_amount);
							request.setAttribute("getSidyAmount",
									get_sidy_amount);
							return mapping.findForward("success");
						} else {
							
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						byte[] vsmess = new byte[300];
						bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
								.getBytes(), vsmess, 300);
						int i;
						for (i = 0; i < vsmess.length; i++) {
							if (vsmess[i] == 0) {
								break;
							}
						}

						String vs_mess = new String(vsmess, 0, i,"GB2312");
					    request.setAttribute("errmsg", vs_mess);
						return mapping.findForward("null");
					}

				} else {
					// 请求失败
					
					return mapping.findForward("failure");
				}
			}
			
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("null");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("null");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！");
			return mapping.findForward("null");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
