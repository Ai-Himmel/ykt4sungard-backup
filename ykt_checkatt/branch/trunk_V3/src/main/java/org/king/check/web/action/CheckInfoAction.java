package org.king.check.web.action;

import java.io.PrintWriter;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.CheckInfoService;
import org.king.check.util.CreateCheckInfoThread;
import org.king.check.util.DateUtilExtend;
import org.king.framework.web.action.BaseAction;

public class CheckInfoAction extends BaseAction {
	private static final Log log = LogFactory.getLog(CheckInfoAction.class);
	
	private CheckInfoService checkInfoService;

	public void setCheckInfoService(CheckInfoService checkInfoService) {
		this.checkInfoService = checkInfoService;
	}
	
	/**
	 * �鿴�Ǽ�ʱ������ϸ
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward viewCheckInfoDetail(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		String startDate = dform.getString("startDate");
		String endDate = dform.getString("endDate");
		String stuempNo = dform.getString("stuempNo");
		String locationId = dform.getString("locationId");
		String className = dform.getString("className");
		String custName = dform.getString("custName");
		
		List result = checkInfoService.viewCheckInfoDetail(startDate, endDate,stuempNo, className, locationId,custName);
		List locationList = checkInfoService.findNoneClockLocation();
		
		request.setAttribute("result", result);
		request.setAttribute("locationList", locationList);
		
		return mapping.findForward("checkInfoDetail");
	}
	
	public ActionForward initCheckInfoDetail(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		List locationList = checkInfoService.findNoneClockLocation();
		request.setAttribute("locationList", locationList);
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		dform.set("startDate", yesterday);
		dform.set("endDate", yesterday);
		return mapping.findForward("checkInfoDetail");
	}
	
	/**
	 * �鿴��ʱ������ϸ
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward viewClockCheckInfoDetail(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		String startDate = dform.getString("startDate");
		String endDate = dform.getString("endDate");
		String stuempNo = dform.getString("stuempNo");
		String locationId = dform.getString("locationId");
		String className = dform.getString("className");
		String custName = dform.getString("custName");
		
		List result = checkInfoService.viewClockCheckInfoDetail(startDate, endDate,stuempNo, className, locationId,custName);
		List locationList = checkInfoService.findClockLocation();
		
		request.setAttribute("result", result);
		request.setAttribute("locationList", locationList);
		
		return mapping.findForward("clockCheckInfoDetail");
	}
	
	public ActionForward initClockCheckInfoDetail(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		List locationList = checkInfoService.findClockLocation();
		request.setAttribute("locationList", locationList);
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		dform.set("startDate", yesterday);
		dform.set("endDate", yesterday);
		return mapping.findForward("clockCheckInfoDetail");
	}
	
	/**
	 * �鿴�Ǽ�ʱ����ͳ��
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward viewCheckInfoTotal(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		String startDate = dform.getString("startDate");
		String endDate = dform.getString("endDate");
		String stuempNo = dform.getString("stuempNo");
		String locationId = dform.getString("locationId");
		String className = dform.getString("className");
		String custName = dform.getString("custName");
		
		List result = checkInfoService.viewCheckInfoTotal(startDate, endDate,stuempNo, className, locationId,custName);
		List locationList = checkInfoService.findNoneClockLocation();
		
		request.setAttribute("result", result);
		request.setAttribute("locationList", locationList);
		
		return mapping.findForward("checkInfoTotal");
	}
	
	public ActionForward initCheckInfoTotal(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		List locationList = checkInfoService.findNoneClockLocation();
		request.setAttribute("locationList", locationList);
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		dform.set("startDate", yesterday);
		dform.set("endDate", yesterday);
		return mapping.findForward("checkInfoTotal");
	}
	
	/**
	 * �鿴��ʱ����ͳ��
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward viewClockCheckInfoTotal(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		String startDate = dform.getString("startDate");
		String endDate = dform.getString("endDate");
		String stuempNo = dform.getString("stuempNo");
		String locationId = dform.getString("locationId");
		String className = dform.getString("className");
		String custName = dform.getString("custName");
		
		List result = checkInfoService.viewClockCheckInfoTotal(startDate, endDate,stuempNo, className, locationId,custName);
		List locationList = checkInfoService.findClockLocation();
		
		request.setAttribute("result", result);
		request.setAttribute("locationList", locationList);
		
		return mapping.findForward("clockCheckInfoTotal");
	}
	
	public ActionForward initClockCheckInfoTotal(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		List locationList = checkInfoService.findClockLocation();
		request.setAttribute("locationList", locationList);
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		dform.set("startDate", yesterday);
		dform.set("endDate", yesterday);
		return mapping.findForward("clockCheckInfoTotal");
	}
	
	public ActionForward initRefreshCheckInfo(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		boolean isOpen = CreateCheckInfoThread.isOpen();
		
		request.setAttribute("yesterday", yesterday);
		request.setAttribute("open", isOpen?"disabled":"");
		request.setAttribute("close", isOpen?"":"disabled");
		return mapping.findForward("refreshCheckInfo");
	}
	
	/**
	 * ˢ��ĳ��ʱ��Ŀ���ͳ����Ϣ
	 * 
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward refreshCheckInfo(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		response.setCharacterEncoding("UTF-8");
		PrintWriter writer = response.getWriter();
		String startDate = request.getParameter("startDate");
		String endDate = request.getParameter("endDate");
		String message = "ˢ��[" + startDate + "--" + endDate + "]ʱ����ڿ���";
		try {
			checkInfoService.refreshCheckInfo(startDate, endDate);
			message += "�ɹ�";
		} catch (Exception e) {
			message += "ʧ��";
			log.error(message + "��" + e.getMessage());
		}
		writer.write(message);
		return null;
	}
	
	/**
	 * �����͹ر��Զ����ɿ����߳�
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward autoCreateCheckInfo(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		response.setCharacterEncoding("UTF-8");
		PrintWriter writer = response.getWriter();
		String status = request.getParameter("status");
		
		String message = "";
		try {
			if("open".equals(status)){
				CreateCheckInfoThread.openThread();
			} else if("close".equals(status)) {
				CreateCheckInfoThread.stopThread();
			}
		} catch (Exception e) {
			message =status+"�Զ��������ݹ���ʧ��";
			log.error(message + "��" + e.getMessage());
		}
		writer.write(message);
		return null;
	}
	
	/**
	 * �鿴��ͨ������ˮ��ʵʱ��
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward viewCheckDetail(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		String startDate = dform.getString("startDate");
		String endDate = dform.getString("endDate");
		String stuempNo = dform.getString("stuempNo");
		String locationId = dform.getString("locationId");
		String className = dform.getString("className");
		String custName = dform.getString("custName");
		
		List result = checkInfoService.viewCheckDetail(startDate, endDate,stuempNo, className, locationId,custName);
		List locationList = checkInfoService.findNormalLocation();
		
		request.setAttribute("result", result);
		request.setAttribute("locationList", locationList);
		
		return mapping.findForward("checkDetail");
	}
	
	public ActionForward initCheckDetail(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		List locationList = checkInfoService.findNormalLocation();
		request.setAttribute("locationList", locationList);
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		dform.set("startDate", yesterday);
		dform.set("endDate", yesterday);
		return mapping.findForward("checkDetail");
	}
	
	/**
	 * �鿴��ͨ����ͳ�ƣ�ʵʱ��
	 * @param mapping
	 * @param form
	 * @param request
	 * @param response
	 * @return
	 * @throws Exception
	 */
	public ActionForward viewCheckTotal(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		String startDate = dform.getString("startDate");
		String endDate = dform.getString("endDate");
		String stuempNo = dform.getString("stuempNo");
		String locationId = dform.getString("locationId");
		String className = dform.getString("className");
		String custName = dform.getString("custName");
		
		List result = checkInfoService.viewCheckTotal(startDate, endDate,stuempNo, className, locationId,custName);
		List locationList = checkInfoService.findNormalLocation();
		
		request.setAttribute("result", result);
		request.setAttribute("locationList", locationList);
		
		return mapping.findForward("checkTotal");
	}
	
	public ActionForward initCheckTotal(ActionMapping mapping, ActionForm form,HttpServletRequest request, HttpServletResponse response)throws Exception {
		DynaActionForm dform = ((DynaActionForm) form);
		
		List locationList = checkInfoService.findNormalLocation();
		request.setAttribute("locationList", locationList);
		String yesterday = DateUtilExtend.addDate2(DateUtilExtend.getNowDate2(),-1);
		dform.set("startDate", yesterday);
		dform.set("endDate", yesterday);
		return mapping.findForward("checkTotal");
	}
}
