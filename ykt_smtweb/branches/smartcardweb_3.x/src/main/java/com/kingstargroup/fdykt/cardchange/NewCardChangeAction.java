package com.kingstargroup.fdykt.cardchange;

import java.sql.SQLException;
import java.util.Arrays;
import java.util.HashMap;

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
import com.kingstargroup.fdykt.dao.DB2AccountDAO;
import com.kingstargroup.fdykt.dao.DB2CardDAO;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.dto.CardDTO;
import com.kingstargroup.fdykt.trade.MobileCheckAction;
import com.kingstargroup.fdykt.util.BccUtil;
import com.kingstargroup.fdykt.util.DateUtil;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class NewCardChangeAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger
			.getLogger(MobileCheckAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = saveinfo(mapping, form, request, response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward saveinfo(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {

		saveToken(request);

		DB2CardDAO carddao = new DB2CardDAO();
		DB2AccountDAO accdao = new DB2AccountDAO();
		String cardphyid = request.getParameter("cardphyid");
		String card_bala = request.getParameter("cardBala");
		String dpt_card_cnt = request.getParameter("dpt_card_cnt");
		String pay_card_cnt = request.getParameter("pay_card_cnt");
		String showcardno = request.getParameter("showcardno");
		String newcardphyid = request.getParameter("newcardphyid");
		
		String water_money1 = request.getParameter("water_money1");
		String water_price11 = request.getParameter("water_price11");
		String water_price21 = request.getParameter("water_price21");
		String water_price31 = request.getParameter("water_price31");

		String water_money2 = request.getParameter("water_money2");
		String water_price12 = request.getParameter("water_price12");
		String water_price22 = request.getParameter("water_price22");
		String water_price32 = request.getParameter("water_price32");
		
		String water_money3 = request.getParameter("water_money3");
		String water_price13 = request.getParameter("water_price13");
		String water_price23 = request.getParameter("water_price23");
		String water_price33 = request.getParameter("water_price33");
		String pursetype1 = request.getParameter("pursetype1");
		String pursetype2 = request.getParameter("pursetype2");
		String pursetype3 = request.getParameter("pursetype3");


//		request.setAttribute("cardphyid", cardphyid);
//		request.setAttribute("cardsubsidyno", cardsubsidyno);
//		request.setAttribute("txCnt", txCnt);
//		request.setAttribute("cardBala", card_bala);
//		request.setAttribute("showcardno", showcardno);
//		request.setAttribute("newcardphyid", newcardphyid);


		CardDTO card = new CardDTO();
		try {
			card = carddao.getCardInfoById(cardphyid);
		} catch (Exception e) {
			// TODO: handle exception
			logger.error("卡信息读取失败");
			String xmlout = XMLGenerateUtil.XMLGenerate("8888", "卡信息读取错误",
					"", "", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}
		
		if(card==null){
			//request.setAttribute("errmsg", "找不到这张卡的相关信息，<br><br>请核对卡片是否被挂失<br><br>如果仍不行，请到校园卡管理中心");
			String xmlout = XMLGenerateUtil.XMLGenerate("5555", "卡片信息未找到，可能已经被注销",
					"", "", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		String reqip = request.getRemoteAddr();
		// reqip = "10.49.188.50";
		int deviceid = -2;
		try {
			deviceid = accdao.getdevidFromip(reqip);
			if (deviceid < 0) {
				String xmlout = XMLGenerateUtil.XMLGenerate("9999", "设备未注册，不能使用此功能！",
						"", "", "", "", "", "", "", "","", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			}
		} catch (Exception e1) {
			e1.printStackTrace();
			String xmlout = XMLGenerateUtil.XMLGenerate("9999", "设备未注册，不能使用此功能！",
					"", "", "", "", "", "", "", "","", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		}

		long xpackhandle = 0;
		int drtpno = 0;
		int errcode[] = { 1 };
		byte errmsg[] = new byte[300];
		int branchno = 0;// 后台drtp功能号
		int mainfunction = KSConfiguration.getInstance().getPropertyAsInt(
				"mainfunction1", 9000);
		int func = KSConfiguration.getInstance().getPropertyAsInt(
				"logicfunc_changecard_oldcard", 846327);// 后台业务功能号
		int tries = KSConfiguration.getInstance().getPropertyAsInt("tries", 3);// 默认重试次数
		int[] RetCode = new int[1];
		int[] RecordCount = new int[1];
		bccclt bcc = null;
		try {
			bcc = BccctlInit.getBccctlInstance();
			xpackhandle = bcc.NewXpackHandle(KSConfiguration.getInstance()
					.getProperty("cpackfile", "/opt/cpack.dat").getBytes());
			if (0 != xpackhandle) {
				bcc.SetRequestType(xpackhandle, func);
				bcc.SetIntFieldByName(xpackhandle, 0, "lcert_code".getBytes(),
						deviceid);// 客户端id
				// bcc.SetStringFieldByName(xpackhandle, 0, "semp".getBytes(),
				// "2000".getBytes());
				bcc.SetStringFieldByName(xpackhandle, 0, "sstatus0".getBytes(),
						"C".getBytes());
				bcc.SetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(),
						Integer.parseInt(String.valueOf(card.getCardno())));// 卡号


				bcc.SetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(),
						Integer.parseInt(dpt_card_cnt));// 交易次数(充值

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(),
						Integer.parseInt(pay_card_cnt));// 交易次数(消费

				bcc.SetIntFieldByName(xpackhandle, 0, "lvol7".getBytes(),
						Integer.parseInt(card_bala));// 卡余额

				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no".getBytes(),
						cardphyid.getBytes());// 物理卡号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "scust_no2".getBytes(),
						newcardphyid.getBytes());//新卡物理卡号
				
				bcc.SetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(),
						showcardno.getBytes());//显示卡号

				boolean bccret = bcc.CallRequest(xpackhandle, drtpno, branchno,
						mainfunction, 10000, errcode, errmsg);

				if (bccret) {
					bcc.GetRetCode(xpackhandle, RetCode);
					bcc.GetRecordCount(xpackhandle, RecordCount);
					if (0 == RetCode[0]) {
						if (0 < RecordCount[0]) {
							byte[] byteStrRec = new byte[256];
							int[] intRec = new int[1];
							// double[] doubleRec = new double[1];
//							outPack->lvol1=tCard.custid;
//							outPack->lsafe_level2=customer.custtype;
//							outPack->lvol5=tCard.feetype;
//							des2src(outPack->sall_name,customer.custname);
//							des2src(outPack->spager,customer.stuempno);
//							des2src(outPack->scert_no,customer.deptcode);
//							des2src(outPack->semail2,customer.idno);
//							des2src(outPack->smarket_code,customer.sex);
//							des2src(outPack->sdate0,tCard.expiredate);
//							sprintf(outPack->sholder_ac_no,"%d",10);				//发行方标识
//							des2src(outPack->smarket_code2,customer.idtype);
//							outPack->lsafe_level=tCard.cardtype;
//							outPack->lvol0=tCard.cardno;
//							outPack->lvol4=cardinsteaddtl.oldsubsidyno;
//							outPack->lvol8=(int)(cardinsteaddtl.oldcardbal*100);
//							outPack->lvol11=D4U5(tCardAccount.singlemaxamt*100,0);
//							outPack->lvol12=D4U5(tCardAccount.daycostmaxamt*100,0);
//							outPack->lvol6=cardinsteaddtl.oldcardcnt;
//							des2src(outPack->sorder0,tCard.showcardno);
//							des2src(outPack->stx_pwd,cardpwd);			
//							des2src(outPack->sdate3,pAccTrans->trans.accdate);
//							des2src(outPack->stime3,pAccTrans->trans.acctime);
//							des2src(outPack->semp,trans.opercode);
//							outPack->lwithdraw_flag=trans.termid;
//							outPack->lserial1=trans.termseqno;
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol1".getBytes(), intRec);
							int lvol1 = intRec[0];//custid
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0,"lsafe_level2".getBytes(), intRec);
							int lsafe_level2 = intRec[0];//custtype
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol5".getBytes(), intRec);
							int lvol5 = intRec[0];//feetype
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,"sall_name".getBytes(), byteStrRec, 256);
							String sall_name = BccUtil.getStringFromByte(byteStrRec);//custname
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "spager".getBytes(), byteStrRec, 256);
							String spager = BccUtil.getStringFromByte(byteStrRec);//stuempno
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "scert_no".getBytes(), byteStrRec, 256);
							String scert_no = BccUtil.getStringFromByte(byteStrRec);//deptcode
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "semail2".getBytes(), byteStrRec, 256);
							String semail2 = BccUtil.getStringFromByte(byteStrRec);//idno		
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,"smarket_code".getBytes(), byteStrRec, 256);
							String smarket_code = BccUtil.getStringFromByte(byteStrRec);//sex
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate0".getBytes(), byteStrRec, 256);
							String sdate0 = BccUtil.getStringFromByte(byteStrRec);//expiredate							
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sholder_ac_no".getBytes(), byteStrRec, 256);
							String sholder_ac_no = BccUtil.getStringFromByte(byteStrRec);//发行方标识							
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0,"smarket_code2".getBytes(), byteStrRec, 256);
							String smarket_code2 = BccUtil.getStringFromByte(byteStrRec);//idtype
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0,"lsafe_level".getBytes(), intRec);
							int lsafe_level = intRec[0];//cardtype
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol0".getBytes(), intRec);
							int lvol0 = intRec[0];//cardno
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol4".getBytes(), intRec);
							int lvol4 = intRec[0];//oldsubsidyno
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol8".getBytes(), intRec);
							int lvol8 = intRec[0];//oldcardbal
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol11".getBytes(), intRec);
							int lvol11 = intRec[0];//singlemaxamt
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol12".getBytes(), intRec);
							int lvol12 = intRec[0];//daycostmaxamt
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lvol6".getBytes(), intRec);
							int lvol6 = intRec[0];//oldcardcnt
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sorder0".getBytes(), byteStrRec, 256);
							String sorder0 = BccUtil.getStringFromByte(byteStrRec);//showcardno
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "stx_pwd".getBytes(), byteStrRec, 256);
							String stx_pwd = BccUtil.getStringFromByte(byteStrRec);//cardpwd
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "sdate3".getBytes(), byteStrRec, 256);
							String sdate3 = BccUtil.getStringFromByte(byteStrRec);//accdate
							Arrays.fill(byteStrRec, (byte) 0);
							bcc.GetStringFieldByName(xpackhandle, 0, "stime3".getBytes(), byteStrRec, 256);
							String stime3 = BccUtil.getStringFromByte(byteStrRec);//accdate
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0, "lserial1".getBytes(), intRec);
							int lserial1 = intRec[0];//termseqno	
							Arrays.fill(intRec, 0);
							bcc.GetIntFieldByName(xpackhandle, 0,"lwithdraw_flag".getBytes(), intRec);
							int lwithdraw_flag = intRec[0];//termid		

							HashMap result = new HashMap();
							result.put("lserial1", String.valueOf(lserial1));
							result.put("lwithdraw_flag", String
									.valueOf(lwithdraw_flag));
							result.put("sdate3", String.valueOf(sdate3));
							result.put("lvol0", String.valueOf(lvol0));
							result.put("sorder0", String.valueOf(sorder0));
							result.put("lvol1", String.valueOf(lvol1));
							result.put("lsafe_level2", String
									.valueOf(lsafe_level2));
							result.put("lvol5", String.valueOf(lvol5));

							result.put("sall_name", String.valueOf(sall_name));
							result.put("spager", String.valueOf(spager));
							result.put("scert_no", String.valueOf(scert_no));
							result.put("semail2", String.valueOf(semail2));
							result.put("smarket_code", String
									.valueOf(smarket_code));
							result.put("sdate0", String.valueOf(sdate0));
							result.put("lvol8", String.valueOf(lvol8));
							result.put("lvol6", String.valueOf(lvol6));
							result.put("lvol4", String.valueOf(lvol4));
							result.put("stx_pwd", String.valueOf(stx_pwd));
							result.put("lvol11", String.valueOf(lvol11));
							result.put("lvol12", String.valueOf(lvol12));
							result.put("sholder_ac_no", String.valueOf(sholder_ac_no));
							result.put("smarket_code2", String.valueOf(smarket_code2));
							result.put("lsafe_level", String.valueOf(lsafe_level));
							result.put("stime3", String.valueOf(stime3));	
							String validatedate = DateUtil.getNewDateTime(sdate3, 90, "yyyyMMdd");
							result.put("validatedate", validatedate);
							if(pursetype1!=null&&!"0".equals(pursetype1)){								
								result.put("pursetype1", String.valueOf(pursetype1));	
								result.put("water_money1", String.valueOf(water_money1));	
								result.put("water_price11", String.valueOf(water_price11));	
								result.put("water_price21", String.valueOf(water_price21));	
								result.put("water_price31", String.valueOf(water_price31));	
							}
							if(pursetype2!=null&&!"0".equals(pursetype2)){								
								result.put("pursetype2", String.valueOf(pursetype2));	
								result.put("water_money2", String.valueOf(water_money2));	
								result.put("water_price12", String.valueOf(water_price12));	
								result.put("water_price22", String.valueOf(water_price22));	
								result.put("water_price32", String.valueOf(water_price32));	
							}
							if(pursetype3!=null&&!"0".equals(pursetype3)){								
								result.put("pursetype3", String.valueOf(pursetype1));	
								result.put("water_money3", String.valueOf(water_money3));	
								result.put("water_price13", String.valueOf(water_price13));	
								result.put("water_price23", String.valueOf(water_price23));	
								result.put("water_price33", String.valueOf(water_price33));	
							}
							
							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0000", "新生换卡成功", result);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							System.out.println(xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0001", "无数据返回!", null);
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

							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0002", vs_mess, null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.MapXMLGenerate(
									"0001", "无数据返回!", null);
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
					String xmlout = XMLGenerateUtil.MapXMLGenerate("1001",
							"后台通讯暂时不可用，请稍后重试！ " + s, null);
					XMLGenerateUtil.XMLSendOut(request, response, xmlout);
					return null;
				}
			}
			String xmlout = XMLGenerateUtil.MapXMLGenerate("1002",
					"系统出现异常，请稍后重试！", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;

		} catch (Exception e) {
			// TODO: handle exception
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.MapXMLGenerate("1003",
					"系统出现异常，请稍后重试！", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} catch (UnsatisfiedLinkError e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.MapXMLGenerate("1004",
					"系统初始化异常，请稍后重试！", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			if (xpackhandle != 0) {
				bcc.DeleteXpackHandle(xpackhandle);
			}
		}
	}
}
