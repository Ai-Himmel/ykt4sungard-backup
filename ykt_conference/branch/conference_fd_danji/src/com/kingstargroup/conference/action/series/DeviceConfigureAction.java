package com.kingstargroup.conference.action.series;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.NumberUtils;
import org.apache.struts.action.Action;
import org.apache.struts.action.ActionError;
import org.apache.struts.action.ActionErrors;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;

import com.kingstargroup.conference.action.cardread.ReadCardUtil;
import com.kingstargroup.conference.common.Threadpool;

public class DeviceConfigureAction extends Action {

	public ActionForward execute(ActionMapping mapping, ActionForm form,
			HttpServletRequest request, HttpServletResponse response)
			throws Exception {
		String port = request.getParameter("port");
		String frequency = request.getParameter("frequency");
		String flag = request.getParameter("flag");
		ActionErrors messages = new ActionErrors();
		try {
			if ("open".equals(flag)) {
				if (null == port || "".equals(port)) {
					messages.add("port",
							new ActionError("readcard.portnoempty"));
					saveErrors(request, messages);
					return mapping.findForward("deviceconf");
				}
				if (null == frequency || "".equals(frequency)) {
					messages.add("frequency", new ActionError(
							"readcard.frequencynoempty"));
					saveErrors(request, messages);
					return mapping.findForward("deviceconf");
				}

				int intport = 0;
				if (NumberUtils.isDigits(port)) {
					intport = Integer.parseInt(port);
				} else {
					messages
							.add("port", new ActionError("readcard.numberonly"));
					saveErrors(request, messages);
					return mapping.findForward("deviceconf");
				}

				int intfrequency = 0;
				if (NumberUtils.isDigits(frequency)) {
					intfrequency = Integer.parseInt(frequency);
				} else {
					messages
							.add("frequency", new ActionError("readcard.numberonly"));
					saveErrors(request, messages);
					return mapping.findForward("deviceconf");
				}
				
				
				if (0 == ReadCardUtil.PortStat) {
					if (0 == ReadCardUtil.OpenSeriesPort(intport, intfrequency)) {
						ReadCardUtil.PortStat = 1;
						Threadpool.getIntance().startThread();
//						messages.add("errorinfo", new ActionError(
//								"readcard.opensuccess"));
//						saveErrors(request, messages);
//						return mapping.findForward("deviceconf");
						request.setAttribute("tipinfo", "串口打开成功，读卡程序自动启动！");
						return mapping.findForward("success");
					} else {
						messages.add("errorinfo", new ActionError(
								"readcard.openfailue"));
						saveErrors(request, messages);
						return mapping.findForward("deviceconf");
					}
				} else {
					messages.add("errorinfo", new ActionError(
							"readcard.portisopened"));
					saveErrors(request, messages);
					return mapping.findForward("deviceconf");
				}
			} else if ("close".equals(flag)) {
				if (1 == ReadCardUtil.PortStat) {
					if (0 == ReadCardUtil.CloseSeriesPort()) {
						ReadCardUtil.PortStat = 0;
						Threadpool.getIntance().stopThread();
//						messages.add("errorinfo", new ActionError(
//								"readcard.closesuccess"));
//						saveErrors(request, messages);
//						return mapping.findForward("deviceconf");
						request.setAttribute("tipinfo", "串口关闭成功，读卡程序自动关闭！");
						return mapping.findForward("success");
					} else {
						messages.add("errorinfo", new ActionError(
								"readcard.closefailue"));
						saveErrors(request, messages);
						return mapping.findForward("deviceconf");
					}
				} else {
					messages.add("errorinfo", new ActionError(
							"readcard.noporttoclose"));
					saveErrors(request, messages);
					return mapping.findForward("deviceconf");
				}
			} else {
				return mapping.findForward("deviceconf");
			}
		} catch (Exception e) {
			e.printStackTrace();
		}
		messages.add("errorinfo", new ActionError("readcard.error"));
		saveErrors(request, messages);
		return mapping.findForward("deviceconf");
	}

}
