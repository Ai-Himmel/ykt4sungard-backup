package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.king.check.door.PersonsTaskBiz;
import org.king.check.service.TermService;
import org.king.framework.web.action.BaseAction;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-10-13
 */
public class RefreshCheckAction extends BaseAction {
    private TermService termService;

    public void setTermService(TermService termService) {
        this.termService = termService;
    }

    public ActionForward init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {
        List terms = termService.findAllTerm();
        request.setAttribute("terms", terms);
        return mapping.findForward("result");
    }

    public ActionForward refreshCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            final String beginDate = request.getParameter("beginDate");
            final String endDate = request.getParameter("endDate");
            if (StringUtils.isNotBlank(beginDate) && StringUtils.isNotBlank(endDate)) {
                PersonsTaskBiz.refreshCheckReport(beginDate, endDate);
                writer.write("刷新考勤成功！");
            } else {
                writer.write("error:请选择日期！");
            }
        } catch (Exception e) {
            writer.write("error:" + e.getMessage());
        }
        return null;
    }

    public ActionForward refreshStudentTermCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        final String termId = request.getParameter("studentTerm");
        try {
            if (!"-1".equals(termId)) {
                PersonsTaskBiz.refreshStudentTermCheck(termId);
                writer.write("刷新考勤成功！");
            } else {
                writer.write("error:请选择学期！");
            }
        } catch (Exception e) {
            writer.write("error:" + e.getMessage());
        }
        return null;
    }

    public ActionForward refreshTeacherTermCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        final String termId = request.getParameter("teacherTerm");
        try {
            if (!"-1".equals(termId)) {
                PersonsTaskBiz.refreshTeacherTermCheck(termId);
                writer.write("刷新考勤成功！");
            } else {
                writer.write("error:请选择学期！");
            }
        } catch (Exception e) {
            writer.write("error:" + e.getMessage());
        }
        return null;
    }

    public ActionForward refreshClassTermCheck(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws IOException {
        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        final String termId = request.getParameter("classTerm");
        try {
            if (!"-1".equals(termId)) {
                PersonsTaskBiz.refreshClassTermCheck(termId);
                writer.write("刷新考勤成功！");
            } else {
                writer.write("error:请选择学期！");
            }
        } catch (Exception e) {
            writer.write("error:" + e.getMessage());
        }
        return null;
    }
}
