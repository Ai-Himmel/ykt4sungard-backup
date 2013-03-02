package com.kingstargroup.fdykt.register.fee;

import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

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

public class CheckUserAction extends Action {

	private static final Logger logger = Logger
			.getLogger(CheckUserAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = checkuser(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	public ActionForward checkuser(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		
		//String stuempno = request.getParameter("stuempno");
		String stuempno="";
		String cardNo = request.getParameter("cardno");
		logger.info("==========stuempno==========="+stuempno);
		logger.info("==========cardNo==========="+cardNo);
		DB2CardDAO carddao = new DB2CardDAO();
		String hexcardno = Integer.toHexString(Integer.parseInt(cardNo))
				.toUpperCase();
		for (int i = hexcardno.length(); i < 8; i++) {
			hexcardno = "0" + hexcardno;// pad left
		}
		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(hexcardno);
			
			logger.info("==========cardNo==========="+cardNo);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			request.setAttribute("errmsg", "此卡无法使用");
			return mapping.findForward("failure");
		}
		DB2CustomerDAO  custDao = new DB2CustomerDAO();
		try{
			
    	 stuempno = custDao.getCustomerByCard(card.getCardId());
		}catch(Exception e){
			logger.error("此卡无对应学/工号");
			request.setAttribute("errmsg", "此卡无对应学/工号");
			return mapping.findForward("failure");
		}
	 	
		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_register_update", 847110);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			//logger.info("====");
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			HttpSession session = request.getSession(true);
			
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);

				bcc.SetStringFieldByName(xpackhandle, 0, "sphone".getBytes(),
						stuempno.getBytes());//学工号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(card.getCardId()));//交易卡号
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(),
						Integer.parseInt("1"));//交易标识
                
				boolean bccret = false;
				while (--tries >= 0) {
					bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
							mainfunction, 60000, errcode, errmsg);
					if (bccret) {
						break;
					}
				}
				if (bccret) {
				//	logger.info("==========bccret==is true=========");
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {

							byte[] stuNo = new byte[81];
							byte[] name = new byte[81];
							int[] feeinfo = new int[1];
							byte[] sdate = new byte[81];
							// byte[] stime = new byte[81];
						//	int[]  writeflag = new int[1];
						//	byte[] vsmess = new byte[300];
							byte[] physicsno= new byte[81];
						//	double[] CardMoney = new double[1];
							int[]  custno = new int[1];

							bcc.GetStringFieldByName(xpackhandle, 0, "scust_limit"
									.getBytes(), stuNo, 81);// 学工号
							bcc.GetStringFieldByName(xpackhandle, 0, "sname"
									.getBytes(), name, 81);// 姓名
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol5"
									.getBytes(), feeinfo);// 收费类别
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate0"
									.getBytes(), sdate, 81);// 日期
						/*	bcc.GetIntFieldByName(xpackhandle, 0, "lvol6"
									.getBytes(), writeflag);*///写卡标志
						/*	bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);*///返回信息
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol7"
									.getBytes(), custno);//客户号
							/*bcc.GetDoubleFieldByName(xpackhandle, 0, "damt0"
									.getBytes(), CardMoney);*///库余额
							bcc.GetStringFieldByName(xpackhandle, 0, "sbank_acc".getBytes(), physicsno,81);//物理卡号
            
							/*int i;
							for (i = 0; i < vsmess.length; i++) {
								if (vsmess[i] == 0) {
									break;
								}
							}*/
							int j;
							for (j = 0; j < stuNo.length; j++) {
								if (stuNo[j] == 0) {
									break;
								}
							}
							int k;
							for (k = 0; k < name.length; k++) {
								if (name[k] == 0) {
									break;
								}
							}
							int m;
							for (m = 0; m < sdate.length; m++) {
								if (sdate[m] == 0) {   
									break;
								}
							}
							  //  logger.info("-----stuempno------"+stuNo);
	                         //   logger.info("-----name------"+name);
	                         //   logger.info("-----sdate------"+sdate);
	                         //   logger.info("-----custno------"+custno);
	                         //   logger.info("-----feeinfo------"+String.valueOf(feeinfo[0]));
	                           
							
							/*String vs_mess = new String(vsmess,0,i);
                            if(writeflag[0] == 0){//不写卡
                            //	logger.info("-----vsmess------"+vs_mess); 
                            	request.setAttribute("errmsg",vs_mess);
                            	return mapping.findForward("failure");
                            }*/
                           
                            String d = new String(sdate,0,m);
                            
							request.setAttribute("stuempno", new String(stuNo,0,j));
							request.setAttribute("name", new String(name,0,k));
							request.setAttribute("feeinfo", String.valueOf(feeinfo[0]));
							request.setAttribute("sdate", d.substring(2));
							request.setAttribute("custno", String.valueOf(custno[0]));
							request.setAttribute("cardId", card.getCardId());
							session.setAttribute("cardno", cardNo);
							

							return mapping.findForward("success");
						} else {
							request.setAttribute("errmsg", "后台处理失败");
							return mapping.findForward("failure");
						}

					} else {
						// 失败
						logger.info("-----失败1------");
						if (0 < RecordCount[0]) {
							/*byte[] vsmess = new byte[300];
							bcc.GetStringFieldByName(xpackhandle, 0, "vsmess"
									.getBytes(), vsmess, 300);
							int i;
							for (i = 0; i < vsmess.length; i++) {
								if (vsmess[i] == 0) {
									break;
								}
							}
							String vs_mess = new String(vsmess, 0, i);*/
							request.setAttribute("errmsg", "更新卡信息处理失败");
							return mapping.findForward("failure");
						} else {
							request.setAttribute("errmsg", "更新卡信息处理失败");
							return mapping.findForward("failure");
						}

					}

				} else {
					// 请求失败
					logger.info("-----失败2------");
					int i;
					for (i = 0; i < errmsg.length; i++) {
						if (errmsg[i] == 0) {
							break;
						}
					}
					String s = new String(errmsg, 0, i);
				   //System.out.println("connect:errcode=" + errcode[0] + "msg="
						//	+ s);
					logger.error("connect:errcode=" + errcode[0] + "msg=" + s);
					request.setAttribute("errmsg", "后台通讯暂时不可用，请稍后重试！ " + s);
					return mapping.findForward("failure");
				}
			}

			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("failure");

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统出现异常，请稍后重试！");
			return mapping.findForward("failure");
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			request.setAttribute("errmsg", "系统初始化异常，请稍后重试！");
			return mapping.findForward("failure");
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}

}
