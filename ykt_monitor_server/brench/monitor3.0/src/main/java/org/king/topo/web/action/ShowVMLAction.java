package org.king.topo.web.action;

import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.ajaxanywhere.AAUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.framework.web.action.BaseAction;
import org.king.topo.service.TopoCalculatorService;

public class ShowVMLAction extends BaseAction {
    private TopoCalculatorService topoCalculatorService;



    public void setTopoCalculatorService(TopoCalculatorService topoCalculatorService) {
		this.topoCalculatorService = topoCalculatorService;
	}

	public ActionForward showmvl(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
		List vmlList = topoCalculatorService.getTopoGroupInfoList();
		String headVML = topoCalculatorService.getTopoHeadVMLInfo();
		request.setAttribute("vmlList", vmlList);
		request.setAttribute("headVML", headVML);
		return mapping.findForward("success");

    }
	
	public ActionForward updateVML(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
		if(AAUtils.isAjaxRequest(request)){
			List vmlList = topoCalculatorService.getTopoGroupInfoList();
			String headVML = topoCalculatorService.getTopoHeadVMLInfo();
			request.setAttribute("vmlList", vmlList);
			request.setAttribute("headVML", headVML);
			List groupStatisticList = topoCalculatorService.getTopoGroupStatisticList();
			List serverStatisticList = topoCalculatorService.getServerStatisticList();
			request.setAttribute("scriptzoneGroup", groupStatisticList);
			request.setAttribute("scriptzoneServer", serverStatisticList);
			AAUtils.addZonesToRefresh(request, "scriptzone");
			return mapping.findForward("success");
		}
		List vmlList = topoCalculatorService.getTopoGroupInfoList();
		String headVML = topoCalculatorService.getTopoHeadVMLInfo();
		request.setAttribute("vmlList", vmlList);
		request.setAttribute("headVML", headVML);
		return mapping.findForward("success");
		
	}
	
}
