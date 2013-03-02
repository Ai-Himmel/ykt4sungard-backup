package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.king.check.service.DepartmentService;
import org.king.check.util.TransferDepartment;
import org.king.framework.web.action.BaseAction;
import org.king.utils.DateUtil;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-18
 */
public class HistoryCheckAction extends BaseAction {

    private static final Log log = LogFactory.getLog(HistoryCheckAction.class);

    private DepartmentService departmentService;

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public ActionForward init(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List yearList = DateUtil.getYearList();

        request.setAttribute("areaList", areaList);
        request.setAttribute("yearList", yearList);
        request.setAttribute("facultyList", facultyList);
        return mapping.findForward("result");
    }

    public ActionForward analyse(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String createYear = (String) dform.get("createYear");
        String areaCode = (String) dform.get("areaCode");
        String pid = (String) dform.get("pid");


        List departments = departmentService.findDepartments(createYear, pid, areaCode);
        List facultyList = departmentService.findFaculty();
        List areaList;
        List yearList = DateUtil.getYearList();

        if (StringUtils.isBlank(pid)) {
            areaList = new ArrayList();
        } else {
            areaList = departmentService.findAreaFromDepartment(pid);
        }


        request.setAttribute("areaList", areaList);
        request.setAttribute("yearList", yearList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("departmentList", departments);
        return mapping.findForward("result");
    }

    public ActionForward process(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String[] ids = request.getParameterValues("itemlist");

        response.setCharacterEncoding("UTF-8");
        PrintWriter writer = response.getWriter();
        try {
            Long deleteTime = departmentService.deleteDepartments(ids);
            if (deleteTime != null) {
                //新线程转移数据
                new TransferDepartment(deleteTime);
            }
            writer.write("操作成功，系统会自动将相关数据移入历史库中！");
        } catch (Exception e) {
            writer.write("error:" + e.getMessage());
        }
        return null;
    }
}
