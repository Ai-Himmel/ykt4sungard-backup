package com.kingstargroup.fdykt.netcompute;

import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.io.OutputStreamWriter;
import java.net.URL;
import java.net.URLConnection;
import java.net.URLEncoder;
import java.util.ArrayList;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.fdykt.KSConfiguration;
import com.kingstargroup.fdykt.Util;
import com.kingstargroup.fdykt.dao.DB2CustomerDAO;
import com.kingstargroup.fdykt.dto.CustomerDTO;

public class NetComputePutinAction extends Action {
	private static final Logger logger = Logger.getLogger(NetComputePutinAction.class);
	/**
	 * Logger for this class
	 */

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response) {
		String cardphyid = request.getParameter("cardphyid");//物理卡号long
		String money = request.getParameter("money");
		String cardBala = request.getParameter("cardBala");
		String txCnt = request.getParameter("txCnt");
		String stuempno = request.getParameter("stuempno");
		String authType = KSConfiguration.getInstance().getProperty("netcomputertrans.auth.type", "0");
		String netIndex = request.getParameter("netIndex");
		if ("0".equals(authType)) {
			DB2CustomerDAO customerdao = new DB2CustomerDAO();
			String sql = "select * from T_CUSTOMER t where stuempno='" + stuempno+"'";
			ArrayList customers;
			try {
				customers = customerdao.RetriveCustomer(sql);
				if (customers.size() == 0) {			
					request.setAttribute("errmsg", "学工号对应的信息不存在，请确认输入的正确性!");
					return mapping.findForward("failure");
				}
				CustomerDTO temp = (CustomerDTO)customers.get(0);
				String stuempname = temp.getCustname();
				request.setAttribute("stuempname", stuempname);
			} catch (Exception e) {
				request.setAttribute("errmsg", "学工号对应的信息查询失败，请稍后重试!");
				return mapping.findForward("failure");
			}
		} else if ("1".equals(authType)) {
			try {
				// Construct data
				String data = URLEncoder.encode("action", "UTF-8") + "=" + URLEncoder.encode("userinfo", "UTF-8");
				data += "&" + URLEncoder.encode("username", "UTF-8") + "=" + URLEncoder.encode(stuempno, "UTF-8");

				String server = KSConfiguration.getInstance().getProperty("netcomputertrans.auth.url", "");
				if (StringUtils.isBlank(server)) {
					request.setAttribute("errmsg","第三方服务器地址未配置，请检查参数netcomputertrans.auth.url[ksconfig.properties]");
					return mapping.findForward("failure");
				}
				// Send data
				URL url = new URL(server);
				URLConnection conn = url.openConnection();
				conn.setConnectTimeout(10000);
				conn.setDoOutput(true);
				OutputStreamWriter wr = new OutputStreamWriter(conn.getOutputStream());
				wr.write(data);
				wr.flush();

				// Get the response
				BufferedReader rd = new BufferedReader(new InputStreamReader(conn.getInputStream(),"UTF-8"));
				StringBuffer result = new StringBuffer();
				String line;
				while ((line = rd.readLine()) != null) {
					result.append(line);
				}
				wr.close();
				rd.close();

				// process return xml
				logger.info("return xml:"+result.toString());
				String status = Util.getJJLinkStatus("status", result.toString())[0];
				if ("成功".equals(status)) {
					String fullname = Util.getJJLinkStatus("fullname", result.toString())[0];
					String amount = Util.format(Util.getJJLinkStatus("amount", result.toString())[0]);
				} else {
					String msg = Util.getJJLinkStatus("msg", result.toString())[0];
					request.setAttribute("errmsg", msg);
					return mapping.findForward("failure");
				}
			} catch (Exception e) {
				logger.error(e);
				request.setAttribute("errmsg", "第三方服务器通讯故障，请稍后重试！");
				return mapping.findForward("failure");
			}
		} else if ("9".equals(authType)) {
			
		} else {
			request.setAttribute("errmsg", "netcomputertrans.auth.type参数配置不正确！");
			return mapping.findForward("failure");
		}
		
		request.setAttribute("cardphyid", cardphyid);
		request.setAttribute("money", money);
		request.setAttribute("cardBala", cardBala);
		request.setAttribute("txCnt", txCnt);
		request.setAttribute("stuempno", stuempno);
		request.setAttribute("netIndex", netIndex);
		return mapping.findForward("success");
	}

}
