package com.kingstargroup.fdykt.trade;

import java.io.UnsupportedEncodingException;
import java.sql.SQLException;
import java.util.ArrayList;

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
import com.kingstargroup.fdykt.dao.DB2BrastransDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.BrastransdtlDTO;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.dto.CustomerDTO;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class NetTransAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(NetTransAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = dotrans(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			logger
					.error(
							"execute(ActionMapping, ActionForm, HttpServletRequest, HttpServletResponse)", e); //$NON-NLS-1$

			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward dotrans(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		try {
			request.setCharacterEncoding("GBK");
		} catch (UnsupportedEncodingException e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		DB2CardDAO carddao = new DB2CardDAO();
		DB2CustomerDAO custdao = new DB2CustomerDAO();
		DB2BrastransDAO brasdao = new DB2BrastransDAO();
		String cardId = request.getParameter("cardId");
		String money = request.getParameter("money");
		String serialNo = request.getParameter("serialNo");
		String stuempno = request.getParameter("stuempno");

		String sdate3 = request.getParameter("sdate3");
		String sname2 = request.getParameter("sname2");

		String thirdpartname = request.getParameter("thirdpartname") == null ? ""
				: request.getParameter("thirdpartname").toString();

		if (null == stuempno || null == cardId || null == money
				|| null == serialNo || "".equals(cardId) || "".equals(money)
				|| "".equals(serialNo) || "".equals(stuempno)) {
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1000", "请求数据错误!",
					"", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		String hexcardno = Integer.toHexString(Integer.parseInt(cardId))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		// ActionErrors errors = new ActionErrors();
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
			if(card==null){
				String xmlout = XMLGenerateUtil.ElectXMLGenerate("0001",
						"卡信息异常，请检查是否正常卡!", "", "", "", "", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			System.out.println("卡信息读取失败");
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("0001",
					"卡信息读取失败!", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		
		DB2BrastransDAO brastransdao = new DB2BrastransDAO();
		ArrayList list = null;
		try {
			list = brastransdao
					.getBrasTransLog("select a.*,0 revflag from ykt_cur.T_BRASTRANSDTL a where a.refno='"+sname2+"'");
		} catch (Exception e1) {
			// TODO Auto-generated catch block
			e1.printStackTrace();
		}
		BrastransdtlDTO brastransdtl = null;
		if (list != null && list.size() > 0) {
			brastransdtl = (BrastransdtlDTO) list.get(0);				
		}else{
			//后台没记
			CustomerDTO custdto = custdao.getCustomer(card.getCustid());
			brastransdtl = new BrastransdtlDTO();
			brastransdtl.setRefno(sname2);
			brastransdtl.setCardno(card.getCardno());
			
			brastransdtl.setOppaccname(thirdpartname);
			brastransdtl.setOppaccno(stuempno);
			brastransdtl.setRemark("");
			brastransdtl.setStatus(1);
			brastransdtl.setSummary("网费充值");
			brastransdtl.setTransamt(Double.parseDouble(money));
			brastransdtl.setTransdate(sdate3);
			brastransdtl.setTranstime(DateUtil.getNow().substring(8));
			brastransdtl.setTranstype(1);
			brastransdtl.setChkflag(0);
			if (custdto != null) {
				brastransdtl.setCustname(custdto.getCustname());
				brastransdtl.setStuempno(custdto.getStuempno());

				try {
					brasdao.createBrasTransLog(brastransdtl);
				} catch (ClassNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (SQLException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (Exception e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}

			}
		}

		
		

		long xpackhandle = 0;
		int drtpno = 1;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction2", 9912);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_net_trans_pay", 3002);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
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
						"vsvarstr0".getBytes(), endpoint.getBytes());// 第三方服务地址
				bcc.SetStringFieldByName(xpackhandle, 0, "snote".getBytes(),
						loginName.getBytes());// 第三方登录名
				bcc.SetStringFieldByName(xpackhandle, 0, "snote2".getBytes(),
						loginPwd.getBytes());// 第三方登录密码
				bcc.SetStringFieldByName(xpackhandle, 0, "scard0".getBytes(),
						("YK" + sname2.substring(2)).getBytes());// 流水凭证号
				bcc.SetStringFieldByName(xpackhandle, 0, "saddr".getBytes(),
						stuempno.getBytes());// 第三方账号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt(money));// 转账金额
				boolean bccret = false;
				bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {

							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0000", "网费充值成功", "", "", "", cardId, null);
							try {
								brastransdtl.setStatus(0);
								brastransdtl.setRemark("网费充值成功");
								brasdao.updateBrasTransLog(brastransdtl);
							} catch (Exception e) {
								logger.error(e);
								e.printStackTrace();
							}

							logger.info("卡号=" + cardId + "充值账号stuempno="
									+ stuempno + " 网费充值成功，对应流水号=" + serialNo
									+ "充值金额=" + money);

							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "无数据返回!", "", "", "", "", null);
							try {
								brastransdtl.setStatus(1);
								brastransdtl.setRemark("网费充值失败返回码="
										+ RetCode[0]);
								brasdao.updateBrasTransLog(brastransdtl);
							} catch (Exception e) {
								logger.error(e);
								e.printStackTrace();
							}

							logger.info("卡号=" + cardId + "充值账号stuempno="
									+ stuempno + " 网费充值失败，对应流水号=" + serialNo
									+ "充值金额=" + money + "返回码=" + RetCode[0]);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					} else {
						// 失败
						if (0 < RecordCount[0]) {

							byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);

							String vs_mess = BccUtil.getStringFromByte(vsmess);

							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0002", vs_mess, "", "", "", "", null);
							try {
								brastransdtl.setStatus(1);
								brastransdtl.setRemark("返回码=" + RetCode[0]
										+ "错误信息：" + vs_mess);
								brasdao.updateBrasTransLog(brastransdtl);
							} catch (Exception e) {
								logger.error(e);
								e.printStackTrace();
							}
							logger.info("卡号=" + cardId + "充值账号stuempno="
									+ stuempno + " 网费充值失败，对应流水号=" + serialNo
									+ "充值金额=" + money + "返回码=" + RetCode[0]
									+ "错误信息：" + vs_mess);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.ElectXMLGenerate(
									"0001", "无数据返回!", "", "", "", "", null);
							try {
								brastransdtl.setStatus(1);
								brastransdtl.setRemark("返回码=" + RetCode[0]
										+ "，无错误信息");
								brasdao.updateBrasTransLog(brastransdtl);
							} catch (Exception e) {
								logger.error(e);
								e.printStackTrace();
							}
							logger.info("卡号=" + cardId + "充值账号stuempno="
									+ stuempno + " 网费充值失败，对应流水号=" + serialNo
									+ "充值金额=" + money + "返回码=" + RetCode[0]
									+ "无错误信息");
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}

					}

				} else {
					// 请求失败
					String s = BccUtil.getStringFromByte(errmsg);
					System.out.println("connect:errcode=" + errcode[0] + "msg="
							+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					String xmlout = XMLGenerateUtil.ElectXMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + s, "", "", "", "", null);
					try {
						brastransdtl.setStatus(1);
						brastransdtl.setRemark("第三方请求发送失败");
						brasdao.updateBrasTransLog(brastransdtl);
					} catch (Exception e) {
						logger.error(e);
						e.printStackTrace();
					}
					logger.info("卡号=" + cardId + "充值账号stuempno=" + stuempno
							+ " 网费充值失败，请求发送失败，对应流水号=" + serialNo + "充值金额="
							+ money);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1002",
					"系统出现异常，请稍后重试！", "", "", "", "", null);
			try {
				brastransdtl.setStatus(1);
				brastransdtl.setRemark("系统出现异常");
				brasdao.updateBrasTransLog(brastransdtl);
			} catch (Exception e) {
				logger.error(e);
				e.printStackTrace();
			}
			logger.info("系统出现异常，请稍后重试！");
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1003",
					"系统出现异常，请稍后重试！", "", "", "", "", null);
			logger.info("系统出现异常，请稍后重试！" + e.getMessage());
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.ElectXMLGenerate("1004",
					"系统初始化异常，请稍后重试！", "", "", "", "", null);
			logger.info("系统出现异常，请稍后重试！" + e.getMessage());
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
