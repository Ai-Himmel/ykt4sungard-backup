package org.king.check.student.web.action;

import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.SyncService;
import org.king.check.service.TermService;
import org.king.check.util.SyncUtil;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class SyncAction extends BaseAction {

    private SyncService syncService;

    private TermService termService;

    public void setSyncService(SyncService syncService) {
        this.syncService = syncService;
    }

    public void setTermService(TermService termService) {
        this.termService = termService;
    }

    public ActionForward init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List terms = termService.findAllTerm();
        request.setAttribute("terms", terms);
        return mapping.findForward("list");
    }

    public ActionForward findCourseplanTemp(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String termName = (String) dform.get("termName");
        String useWeek = (String) dform.get("useWeek");
        String beginDate = (String) dform.get("beginDate");
        String endDate = (String) dform.get("endDate");
        String status = request.getParameter("status");
        List result;
        if ("0".equals(status)) {
            //查找错误课程计划
            result = syncService.findErrorCourseplanTemp(termName, beginDate, endDate);
        } else {
            result = syncService.findCourseplanTemp(status);
        }
        List terms = termService.findAllTerm();

        request.setAttribute("result", result);
        request.setAttribute("totalRows", result.size());
        request.setAttribute("terms", terms);
        return mapping.findForward("list");
    }

    public ActionForward checkPreviewData(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String info = syncService.checkPreviewData();
        request.setAttribute("previewInfo", info);
        return new ActionForward("/syncCourseplan.do?method=findCourseplanTemp&status=2");
    }

    public ActionForward previewData(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
//        syncService.deletePreviewData();
        SyncUtil.previewData();
        return new ActionForward("/syncCourseplan.do?method=findCourseplanTemp&status=2");
    }

    public ActionForward importData(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String info = syncService.importData();
        request.setAttribute("importInfo", info);
        return new ActionForward("/syncCourseplan.do?method=findCourseplanTemp&status=0");
    }

    public ActionForward findSyncLog(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String termName = (String) dform.get("termName");
        String useWeek = (String) dform.get("useWeek");
        List result = syncService.findSyncLog(termName, useWeek);
        List terms = termService.findAllTerm();

        request.setAttribute("result", result);
        request.setAttribute("totalRows", result.size());
        request.setAttribute("terms", terms);
        return mapping.findForward("syncLog");
    }
}
