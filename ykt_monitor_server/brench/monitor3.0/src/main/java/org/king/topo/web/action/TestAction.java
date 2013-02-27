package org.king.topo.web.action;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.framework.web.action.BaseAction;
import org.king.topo.service.TopoCalculatorService;

public class TestAction extends BaseAction {
    private TopoCalculatorService topoCalculatorService;



    public void setTopoCalculatorService(TopoCalculatorService topoCalculatorService) {
		this.topoCalculatorService = topoCalculatorService;
	}

	public ActionForward test(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
		topoCalculatorService.calculateDivHtml();
		topoCalculatorService.calculateDevgroupInfo();
		topoCalculatorService.calculateTopoServerStatistic(0);
        return null;
    }
}
