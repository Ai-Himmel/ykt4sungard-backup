package org.king.check.student.web.action;

import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.upload.FormFile;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.domain.TTeacherClass;
import org.king.check.service.DepartmentService;
import org.king.check.service.RoomService;
import org.king.check.service.TeacherClassService;
import org.king.check.util.EmpowerAssistant;
import org.king.check.util.PageLimitUtil;
import org.king.framework.web.action.BaseAction;
import org.king.security.domain.Account;
import org.king.upload.web.form.UpLoadForm;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-12-16
 */
public class TeacherClassAction extends BaseAction {
    private TeacherClassService teacherClassService;

    private RoomService roomService;

    private DepartmentService departmentService;

    public void setTeacherClassService(TeacherClassService teacherClassService) {
        this.teacherClassService = teacherClassService;
    }

    public void setRoomService(RoomService roomService) {
        this.roomService = roomService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public ActionForward teacherClassImplInit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) {
        return mapping.findForward("impl");
    }

    public ActionForward getModel(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String fileName = "teacherClass.xls";

        HSSFWorkbook wb = teacherClassService.getTeacherClassModel();
        response.setContentType("application/x-msdownload");
        response.setHeader("Content-Disposition", "attachment;" + " filename=" + new String(fileName.getBytes(), "ISO-8859-1"));

        OutputStream os = response.getOutputStream();
        wb.write(os);

        return null;
    }

    public ActionForward implTeacherClass(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        //check login
        Object account = session.getAttribute("accountPerson");
        if (account == null || StringUtils.isBlank(account.toString())) {
            return mapping.findForward("faile");
        }
        Integer custid = ((Account) account).getCustId();

        if (form instanceof UpLoadForm) {
            String encoding = request.getCharacterEncoding();
            if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
                response.setContentType("text/html; charset=gb2312");
            }
            StringBuffer msg = new StringBuffer();
            UpLoadForm theForm = (UpLoadForm) form;
            FormFile file = theForm.getTheFile();
            if (file == null) {
                msg.append("The file is not exist,please check!");
            } else {
                InputStream checkis = file.getInputStream();
                try {
                    HSSFWorkbook wb = new HSSFWorkbook(checkis);
                    List tempList = teacherClassService.implTeacherClass(wb, custid, msg);
                    List checkList = null;
                    if (StringUtils.isBlank(msg.toString())) {
                        checkList = teacherClassService.checkTeacherClass(custid, msg);
                    }
                    if (StringUtils.isBlank(msg.toString())) {
                        teacherClassService.saveTeacherClass(tempList, checkList);
                    }
                    new EmpowerAssistant();
                } catch (Exception e) {
                    log.error(e.getMessage());
                    msg.append(e.getMessage());
                } finally {
                    checkis.close();
                    teacherClassService.cleanTeacherClassTemp(custid);
                }
            }
            if (StringUtils.isNotBlank(msg.toString())) {
                request.setAttribute("msg", "导入失败。<br>" + msg.toString());
            } else {
                request.setAttribute("msg", "导入成功。<br>");
            }
        }
        return mapping.findForward("impl");
    }

    public ActionForward teacherClassSearch(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        String pid = (String) dform.get("pid");
        String areaCode = (String) dform.get("areaCode");

        DBPageLimit page = new DBPageLimit();
        PageLimitUtil.pageInfoPopulate("ec", request, page);

        teacherClassService.findTeacherClass(dform, page);
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List deptList = new ArrayList();
        if (StringUtils.isNotBlank(pid)) {
            areaList = departmentService.findAreaFromDepartment(pid);
        }
        if (StringUtils.isNotBlank(areaCode)) {
            deptList = departmentService.findDepartment(areaCode, pid);
        }
        request.setAttribute("areaList", areaList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);

        request.setAttribute("teacherClassList", page.getResult());
        request.setAttribute("totalRows", page.getTotalRows());

        return mapping.findForward("search");
    }

    public ActionForward deleteTeacherClass(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String[] ids = request.getParameterValues("itemlist");
        teacherClassService.deleteTeacherClass(ids);

        return mapping.findForward("success");
    }

    public ActionForward addTeacherClass(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        TTeacherClass teacherClass = new TTeacherClass();
        dform.set("teacherClass", teacherClass);
        List areaList = departmentService.findAreaFromDepartment();
        request.setAttribute("areaList", areaList);

        return mapping.findForward("add");
    }

    public ActionForward saveTeacherClass(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;
        TTeacherClass teacherClass = (TTeacherClass) dform.get("teacherClass");
        String areaCode = (String) dform.get("areaCode");
        String shortName = (String)dform.get("shortName");
        try {
            teacherClassService.saveTeacherClass(teacherClass, areaCode,shortName);
            return mapping.findForward("success");
        } catch (Exception e) {
            request.setAttribute("msg", e.getMessage());
            List areaList = roomService.getAreaList();
            request.setAttribute("areaList", areaList);
            return mapping.findForward("add");
        }
    }

    public ActionForward editTeacherClass(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List areaList = roomService.getAreaList();
        request.setAttribute("areaList", areaList);
        return mapping.findForward("edit");
    }
}
