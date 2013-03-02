
import java.sql.SQLException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;


import com.cn.kingstar.drtp.drtpjlib;
import com.kingstargroup.fdykt.dao.KSDaoSessionFactory;
import com.kingstargroup.fdykt.util.XMLGenerateUtil;

public class GetSidyAction extends Action {
	/**
	 * Logger for this class
	 */
	private static final Logger logger = Logger.getLogger(GetSidyAction.class);

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		KSDaoSessionFactory.createSession();
		ActionForward forward = doGetSidy(mapping, form, request,response);
		try {
			KSDaoSessionFactory.commit();
		} catch (SQLException e) {
			e.printStackTrace();
		}
		return forward;
	}

	private ActionForward doGetSidy(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		// DB2TradeSerialDAO tradeserialdao = new DB2TradeSerialDAO();
		HttpSession session = request.getSession();
		String card_id = request.getParameter("cardId");
		String card_bala = request.getParameter("cardBala");
		String tx_cnt = request.getParameter("txCnt");
		String ParamKey = request.getParameter("paramKey");
	//	String ParamKey = (String) session.getAttribute("paramKey");
		if (card_id == null || null == card_bala || "".equals(card_bala)
				|| "".equals(card_id) || null == ParamKey
				|| "".equals(ParamKey) || null == tx_cnt || "".equals(tx_cnt))
			return mapping.findForward("error");
		drtpjlib obj = null;
		xpacklib xpack = null;
		long xpackhandle = 0;
		try {
			// TODO: Add initialization code here
			obj = new drtpjlib();
			int errcode[] = { 1 };
			byte errmsg[] = new byte[300];
			byte ip[] = new byte[300];
			byte message[] = new byte[8000];
			byte drtphandle[] = new byte[64];
			int port = 4000;
			int handle;
			boolean ret;
			int len[] = { 1 };
			int branch = 7000;//后台drtp功能号
			int func = 960001;//后台业务功能号
			int tries = 3;// 默认重试次数

			String sip = "10.49.188.243";//drtp ip
			ip = sip.getBytes();

			ret = obj.DrtpInit(errcode, errmsg);
			//System.out.println("init=" + ret);
			handle = obj.DrtpConnect(ip, port, errcode, errmsg);
			if (handle < 0) {
				String s = new String(errmsg, 0, 300);
				/*System.out
						.println("connect:errcode=" + errcode[0] + "msg=" + s);
				logger.error("connect:errcode=" + errcode[0] + "msg=" + s);*/
				String xmlout = XMLGenerateUtil.XMLGenerate("1000",
						"后台通讯暂时不可用，请稍后重试！" + errmsg.toString(), "", "", "", "",
						"", null);
				XMLGenerateUtil.XMLSendOut(request, response, xmlout);
				return null;
			} else {
				xpack = new xpacklib();
				xpackhandle = xpack.NewXpackHandle("/xpack.dat".getBytes());
				System.out.println("***************************seruusldjfi************88");
				if (0 != xpackhandle) {
					// 成功
					/*
					 * drtp->SetRequestHeader(KS_BANK_TX_CODE,1);
					 * drtp->AddField(F_SCLOSE_EMP,"240104"); // 交易码
					 * drtp->AddField(F_LVOL0,cardinfo.cardid); // 交易卡号
					 * drtp->AddField(F_SEMP_PWD,(LPSTR)(LPCTSTR)passwd); // 密码
					 * drtp->AddField(F_DAMT0,cardinfo.balance); //入卡值
					 * drtp->AddField(F_LVOL1,cardinfo.tx_cnt); //累计交易次数
					 * drtp->AddField(F_SNAME,(LPSTR)(LPCTSTR)dlg->GetConfig()->m_systemNo);//
					 * 系统编号 //设备ＩＤ drtp->AddField(F_SCUST_NO,"system"); //操作员
					 */
					xpack.SetRequestType(xpackhandle, func);
					xpack.SetStringFieldByName(xpackhandle, 0, "SCLOSE_EMP"
							.getBytes(), "240104".getBytes());
					xpack.SetIntFieldByName(xpackhandle, 0, "LVOL0".getBytes(),
							Integer.parseInt(card_id));
					xpack.SetDoubleFieldByName(xpackhandle, 0, "DAMT0"
							.getBytes(), Double.parseDouble(card_bala));
					xpack.SetIntFieldByName(xpackhandle, 0,
							"LVOL1".getBytes(), Integer.parseInt(tx_cnt));
					xpack.SetStringFieldByName(xpackhandle, 0, "SNAME"
							.getBytes(), "550".getBytes());
					xpack.SetStringFieldByName(xpackhandle, 0, "SCUST_NO"
							.getBytes(), "web".getBytes());
					byte[] PackBuffer = new byte[1024];
					int[] PackDataLength = new int[1];
					xpack.EnCodeXpackForRequest(xpackhandle, PackBuffer, 1024,
							PackDataLength);
					while (--tries >= 0) {
						ret = obj.DrtpPostMessage(1, 0, branch, PackBuffer,
								PackDataLength[0], errcode, errmsg, handle);
						if (ret == true) {
							break;
						}
					}
					if (ret == false) {
						// drtp发送失败
						String xmlout = XMLGenerateUtil.XMLGenerate("1001",
								"交易请求发送失败，请稍后重试！" + errmsg.toString(), "", "",
								"", "", "", null);
						XMLGenerateUtil.XMLSendOut(request, response, xmlout);
						return null;

					}
					tries = 3;
					while (--tries >= 0) {
						ret = obj.DrtpReadMessage(message, 7000, len, handle,
								drtphandle, errcode, errmsg);
						if (ret == true) {
							break;
						}
					}
					if (ret == false) {
						String xmlout = XMLGenerateUtil.XMLGenerate("1002",
								errmsg.toString(), "", "", "", "", "", null);
						XMLGenerateUtil.XMLSendOut(request, response, xmlout);
						xpack.DeleteXpackHandle(xpackhandle);
						return null;
					} else {
						xpack.DeCodeXpack(xpackhandle, message, message.length);
						int[] RetCode = new int[1];
						xpack.GetRetCode(xpackhandle, RetCode);
						if (0 == RetCode[0]) {
							int[] SidyAmount = new int[1];
							xpack.GetIntFieldByName(xpackhandle, 0, "damt1"
									.getBytes(), SidyAmount);
							int[] OutCardAmount = new int[1];
							xpack.GetIntFieldByName(xpackhandle, 0, "damt2"
									.getBytes(), OutCardAmount);
							byte[] SerialNo = new byte[26];
							xpack.GetStringFieldByName(xpackhandle, 0,
									"sserial1".getBytes(), SerialNo, 26);
							String xmlout = XMLGenerateUtil.XMLGenerate("0000",
									"补助领取成功", String.valueOf(SidyAmount[0]),
									String.valueOf(OutCardAmount[0]), SerialNo
											.toString(), ParamKey, card_id,
									null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						} else {
							String xmlout = XMLGenerateUtil.XMLGenerate("0001",
									message.toString(), "", "", "", "", "",
									null);
							XMLGenerateUtil.XMLSendOut(request, response,
									xmlout);
							return null;
						}
					}
				}
				return null;
			}
		} catch (Exception e) {
			logger.error(e.getMessage());
			String xmlout = XMLGenerateUtil.XMLGenerate("1003",
					"系统出现异常，请稍后重试！", "", "", "", "", "", null);
			XMLGenerateUtil.XMLSendOut(request, response, xmlout);
			return null;
		} finally {
			System.out.println("***************************909987************88");
			if (xpackhandle != 0) {
				xpack.DeleteXpackHandle(xpackhandle);
			}
			if (null != obj) {
				obj.DrtpClose();
				obj.DrtpExit();
			}

		}
	}
}
