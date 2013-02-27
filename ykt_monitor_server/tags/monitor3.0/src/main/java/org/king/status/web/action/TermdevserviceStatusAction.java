package org.king.status.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.common.displaytag.DBPaginatedList;
import org.king.common.displaytag.decorator.DateDecorator;
import org.king.common.displaytag.decorator.DecoratorFactory;
import org.king.common.displaytag.decorator.StateDecorator;
import org.king.framework.web.action.BaseAction;
import org.king.termdev.domain.MonitorTermdevserviceStatus;
import org.king.termdev.service.TermdevService;
import org.king.utils.PaginationUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * .
 * User: Yiming.You
 * Date: 2010-7-14
 */
public class TermdevserviceStatusAction extends BaseAction {
    private TermdevService termdevService;

    public void setTermdevService(TermdevService termdevService) {
        this.termdevService = termdevService;
    }

    public ActionForward listMonitorTermdevserviceStatus(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        //query condition
        MonitorTermdevserviceStatus monitorTermdevserviceStatus = (MonitorTermdevserviceStatus) ((DynaActionForm) form).get("monitorTermdevserviceStatus");

        DBPaginatedList page = new DBPaginatedList();
        PaginationUtil.pageInfoPopulate("row", request, page);
        termdevService.findMonitorTermdevserviceStatusByPage(page, monitorTermdevserviceStatus);
        String[][] result = termdevService.calculateTermdevserviceStatus();
        StateDecorator termdevserviceStatusDecorator = DecoratorFactory.getTermdevserviceStatusDecorator();
        DateDecorator dateDecorator = DecoratorFactory.getDateDecorator();

        request.setAttribute("termdevserviceStatusDecorator", termdevserviceStatusDecorator);
        request.setAttribute("dateDecorator", dateDecorator);
        request.setAttribute("termdevserviceStatusList", page);
        request.setAttribute("result", result);
        ((DynaActionForm) form).set("monitorTermdevserviceStatus", monitorTermdevserviceStatus);

        return mapping.findForward("listTermdevserviceStatus");
    }
}