package org.king.check.student.web.action;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.*;
import org.apache.poi.hssf.util.HSSFColor;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.ActionForward;
import org.apache.struts.action.ActionMapping;
import org.apache.struts.action.DynaActionForm;
import org.apache.struts.upload.FormFile;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.domain.TCourseplan;
import org.king.check.domain.TCourseplanclass;
import org.king.check.service.*;
import org.king.check.util.EmpowerTeacher;
import org.king.check.util.InsertDoorList;
import org.king.check.util.PageLimitUtil;
import org.king.framework.web.action.BaseAction;
import org.king.upload.web.form.UpLoadForm;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;
import java.io.InputStream;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;

public class CoursePlanAction extends BaseAction {

    private CourseplanService courseplanService;
    private TermService termService;
    private RoomService roomService;
    private TimeService timeService;
    private DepartmentService departmentService;
    private CourseService courseService;

    public void setTimeService(TimeService timeService) {
        this.timeService = timeService;
    }

    public void setCourseplanService(CourseplanService courseplanService) {
        this.courseplanService = courseplanService;
    }

    public void setTermService(TermService termService) {
        this.termService = termService;
    }

    public void setRoomService(RoomService roomService) {
        this.roomService = roomService;
    }

    public void setCourseService(CourseService courseService) {
        this.courseService = courseService;
    }

    public ActionForward coursePlanInit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        List areaList = departmentService.findAreaFromDepartment();
        List termList = termService.findTerm("");
        request.setAttribute("areaList", areaList);
        request.setAttribute("termList", termList);

        return mapping.findForward("self");
    }

    // 课程计划修改1
    public ActionForward updateCourseplan_step1(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String planId = request.getParameter("planId");
        DynaActionForm dform = (DynaActionForm) form;
        String schoolarea = "";
        String build = "";
        Map courseplanMap = courseplanService.getTCourseplanMap(planId);

        schoolarea = courseplanMap.get("areaCode").toString();
        build = courseplanMap.get("build").toString();
        BeanUtils.copyProperties(dform, courseplanMap);

        // 校区列表
        List areaList = departmentService.findAreaFromDepartment();
        // 楼宇列表
        List buildList = roomService.getBuildList(schoolarea);
        // 教室列表
        List roomnameList = roomService.getRoomNameList(build);
        // 上课时段列表
        List timeList = timeService.findClassTimes();

        List departments = departmentService.getDepartmentsByPlanId(planId);

        request.setAttribute("planId", planId);
        request.setAttribute("timeList", timeList);
        request.setAttribute("areaList", areaList);
        request.setAttribute("buildList", buildList);
        request.setAttribute("roomnameList", roomnameList);
        request.setAttribute("courseplanMap", courseplanMap);
        request.setAttribute("departments", departments);
        return mapping.findForward("courseplanedit");
    }

    // 课程计划修改
    public ActionForward updateCourseplan(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String planId = request.getParameter("planId");
        DynaActionForm dform = (DynaActionForm) form;
        String[] bindclasses = request.getParameterValues("bindclasses");

        String result = courseplanService.updateCourseplan(form, planId, bindclasses);

        String schoolarea = "";
        String build = "";
        Map courseplanMap = courseplanService.getTCourseplanMap(planId);

//		schoolarea = courseplanMap.get("areaCode").toString();
//		build = courseplanMap.get("build").toString();
        schoolarea = dform.get("areaCode").toString();
        build = dform.get("build").toString();
//		BeanUtils.copyProperties(dform, courseplanMap);

        // 校区列表
        List areaList = roomService.getAreaList();
        // 楼宇列表
        List buildList = roomService.getBuildList(schoolarea);
        // 教室列表
        List roomnameList = roomService.getRoomNameList(build);
        // 上课时段列表
        List timeList = timeService.findClassTimes();

//        List gard = departmentService.findallGard();
        List gard = new ArrayList();

        request.setAttribute("gard", gard);
        request.setAttribute("result", result);
        request.setAttribute("timeList", timeList);
        request.setAttribute("areaList", areaList);
        request.setAttribute("buildList", buildList);
        request.setAttribute("roomnameList", roomnameList);
        request.setAttribute("courseplanMap", courseplanMap);
//		return mapping.findForward("courseplanUpdate");
        return null;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public ActionForward courseplanSearchInit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;

        DBPageLimit page = new DBPageLimit();
        PageLimitUtil.pageInfoPopulate("ec", request, page);

        courseplanService.findCourseplan(dform, page);
        request.setAttribute("courseplanList", page.getResult());
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List buildList = new ArrayList();
        List roomnameList = new ArrayList();
        List deptList = new ArrayList();
//        List courseList = departmentService.findCourse("", "", "");
        List courseList = new ArrayList();


        request.setAttribute("areaList", areaList);
        request.setAttribute("buildList", buildList);
        request.setAttribute("roomnameList", roomnameList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        request.setAttribute("totalRows", page.getTotalRows());

        return mapping.findForward("courseplanlist");
    }

    public ActionForward courseplanSearch(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;

        DBPageLimit page = new DBPageLimit();
        PageLimitUtil.pageInfoPopulate("ec", request, page);

        courseplanService.findCourseplan(dform, page);
        String areaCode = dform.getString("schoolArea");
        String build = dform.getString("build");
        String pid = dform.getString("pid");
        String classno = dform.getString("classno");

        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List buildList = new ArrayList();
        List roomnameList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse(areaCode, pid, classno);

        // 楼宇列表
        if (StringUtils.isNotBlank(pid)) {
            areaList = departmentService.findAreaFromDepartment(pid);
        }
        if (StringUtils.isNotBlank(build)) {
            // 教室列表
            roomnameList = roomService.getRoomNameList(build);
        }
        if (StringUtils.isNotBlank(areaCode)) {
            buildList = roomService.getBuildList(areaCode);
            deptList = departmentService.findDepartment(areaCode, pid);
        }

        request.setAttribute("areaList", areaList);
        request.setAttribute("buildList", buildList);
        request.setAttribute("roomnameList", roomnameList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        request.setAttribute("courseplanList", page.getResult());
        request.setAttribute("totalRows", page.getTotalRows());

        return mapping.findForward("courseplanlist");
    }

    public ActionForward deleCourseplan(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String[] planId = request.getParameterValues("itemlist");
        for (int i = 0; i < planId.length; i++) {
            if (StringUtils.isNotBlank(planId[i])) {
                TCourseplan courseplan = courseplanService.getTCourseplan(planId[i]);
                List classList = courseplanService.findCourseplanclass(planId[i]);
                for (int j = 0; j < classList.size(); j++) {
                    TCourseplanclass planclass = (TCourseplanclass) classList.get(j);
                    courseplanService.deleteCourseplanClass(planclass);
                }
                courseplanService.deleteCourseplan(courseplan);
                // 更新
                //PersonsTaskBiz.updateDoorList(courseplan.getCourse().getCourseid(), courseplan.getRoom().getRoomId());
            }
        }
        request.setAttribute("deleflag", "true");
        return courseplanSearch(mapping, form, request, response);
    }

    public ActionForward impCoursePlan(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        HttpSession session = request.getSession(false);
        if (session == null) {
            session = request.getSession(true);
        }
        List areaList = departmentService.findAreaFromDepartment();
        List termList = termService.findTerm("");
        request.setAttribute("areaList", areaList);
        request.setAttribute("termList", termList);
        String userId = "";

        if (session.getAttribute("personCode") != null)
            userId = (String) session.getAttribute("personCode");

        if (userId.equals("")) {
            return mapping.findForward("faile");
        }
        String termId = request.getParameter("termId");
        String areaCode = request.getParameter("areaCode");

        if (form instanceof UpLoadForm) {// 如果form是UpLoadsForm

            String encoding = request.getCharacterEncoding();

            if ((encoding != null) && (encoding.equalsIgnoreCase("utf-8"))) {
                response.setContentType("text/html; charset=gb2312");
            }
            UpLoadForm theForm = (UpLoadForm) form;
            FormFile file = theForm.getTheFile();// 取得上传的文件
            if (file == null) {
                return mapping.findForward("importfail");
            }

            String contentType = file.getContentType();
            String size = (file.getFileSize() + " bytes");// 文件大小

            String fileName = file.getFileName();// 文件名
            fileName = request.getParameter("filepath");
            InputStream checkis = file.getInputStream();// 把文件读入,用于检查格式
            // InputStream is=file.getInputStream();//把文件读入,用于导入数据

            String resultstring = "";

            String importMode = request.getParameter("importmode");
            try {

                HSSFWorkbook wb = new HSSFWorkbook(checkis);
                String tableName = wb.getSheetName(0);
                HSSFSheet sheet = wb.getSheet(tableName);
                resultstring = courseplanService.ifCourseCanImp(sheet, termId,
                        areaCode);

                if (!"".equals(resultstring)) {// 检查不能导入
                    request.setAttribute("resultstring", resultstring);
                    return mapping.findForward("self");
                }
                resultstring = courseplanService.saveCourseplanImp(sheet,
                        termId, userId);

                // PersonsTaskBiz.insertDoorList();//保存完计划后插入
                new InsertDoorList();
                //为任课老师赋予任课老师角色
                new EmpowerTeacher();

                request.setAttribute("resultstring", resultstring);
                return mapping.findForward("self");

            } catch (Exception e) {
                e.printStackTrace();
                request.setAttribute("resultstring", resultstring
                        + "系统出现未知错误无法导入，请联系管理员");
                return mapping.findForward("self");
            } finally {
                checkis.close();
                // is.close();
            }
        }
        return mapping.findForward("self");
    }

    public ActionForward getModel(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        String fileName = "coursePlanModel.xls";

        // Create the Sheet with the name of the Table
        HSSFWorkbook wb = new HSSFWorkbook();

        // 设置显示的字体以及相关的样式
        HSSFFont font = wb.createFont();
        font.setFontHeightInPoints((short) 8);
        font.setItalic(false);
        font.setStrikeout(false);

        // 设置标题栏单元格的样式
        HSSFCellStyle cellHeadStyle = wb.createCellStyle();
        cellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellHeadStyle.setBorderBottom((short) 1);
        cellHeadStyle.setBorderLeft((short) 1);
        cellHeadStyle.setBorderRight((short) 1);
        cellHeadStyle.setBorderTop((short) 1);
        cellHeadStyle.setFillForegroundColor(HSSFColor.GREY_25_PERCENT.index);
        cellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

        // 设置数据行的字体以及以及相关的对齐方式
        HSSFCellStyle cellDataStyle = wb.createCellStyle();
        cellDataStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        cellDataStyle.setFont(font);

        HSSFSheet sheet1 = wb.createSheet("Sheet1");

        // Grab & populate the Column Names
        HSSFRow row = sheet1.createRow((short) 0);

        // Populate the first row of the spreadsheet with the column names
        List columnNames = new ArrayList();

        columnNames.add(0, "学期");
        columnNames.add(1, "院系");
        columnNames.add(2, "校区	");
        columnNames.add(3, "教学楼");
        columnNames.add(4, "教室");
        columnNames.add(5, "课程	");
        columnNames.add(6, "教师学工号");
        columnNames.add(7, "教师姓名");
        columnNames.add(8, "上课班级");
        columnNames.add(9, "周几");
        columnNames.add(10, "开始周次");
        columnNames.add(11, "结束周次");
        columnNames.add(12, "开始课数");
        columnNames.add(13, "结束课数");
        columnNames.add(14, "是否考勤");
        columnNames.add(15, "是否开门");

        HSSFCellStyle keycellHeadStyle = wb.createCellStyle();// 必填字段的标题栏格式
        keycellHeadStyle.setAlignment(HSSFCellStyle.ALIGN_LEFT);
        keycellHeadStyle.setBorderBottom((short) 1);
        keycellHeadStyle.setBorderLeft((short) 1);
        keycellHeadStyle.setBorderRight((short) 1);
        keycellHeadStyle.setBorderTop((short) 1);
        keycellHeadStyle.setFillForegroundColor(HSSFColor.LIGHT_ORANGE.index);
        keycellHeadStyle.setFillPattern(HSSFCellStyle.SOLID_FOREGROUND);

        for (int i = 0; i < columnNames.size(); i++) {
            HSSFCell cname = row.createCell((short) i);
            if (i == 0 || i == 1)
                cname.setCellStyle(keycellHeadStyle);
            else
                cname.setCellStyle(cellHeadStyle);
            cname.setEncoding(HSSFCell.ENCODING_UTF_16);
            cname.setCellValue((String) columnNames.get(i));
        }

        // create row in spreadsheet
        row = sheet1.createRow((short) 1);

        // populate the spreadsheet with the cell
        HSSFCell ctitle = row.createCell((short) 0);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("09春");

        ctitle = row.createCell((short) 1);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("开放学院");

        ctitle = row.createCell((short) 2);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("国顺");

        ctitle = row.createCell((short) 3);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("新大楼");

        ctitle = row.createCell((short) 4);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("120");

        ctitle = row.createCell((short) 5);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("多媒体技术基础");

        ctitle = row.createCell((short) 6);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("3209");

        ctitle = row.createCell((short) 7);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("郑任儿");

        ctitle = row.createCell((short) 8);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("09春工商专,09春货代");

        ctitle = row.createCell((short) 9);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("2");

        ctitle = row.createCell((short) 10);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("1");

        ctitle = row.createCell((short) 11);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("1");

        ctitle = row.createCell((short) 12);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("1");

        ctitle = row.createCell((short) 13);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("2");

        ctitle = row.createCell((short) 14);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("是");

        ctitle = row.createCell((short) 15);
        ctitle.setCellStyle(cellDataStyle);
        ctitle.setEncoding(HSSFCell.ENCODING_UTF_16);
        ctitle.setCellValue("是");

        response.setContentType("application/x-msdownload");
        response.setHeader("Content-Disposition", "attachment;" + " filename="
                + new String(fileName.getBytes(), "ISO-8859-1"));

        OutputStream os = response.getOutputStream();
        wb.write(os);
        /*-----------------------------------------------------------------------*/
        return null;
    }

    public ActionForward courseplanQueryInit(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;

        DBPageLimit page = new DBPageLimit();
        PageLimitUtil.pageInfoPopulate("ec", request, page);

        courseplanService.findCourseplan(dform, page);
        request.setAttribute("courseplanList", page.getResult());
        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List buildList = new ArrayList();
        List roomnameList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse("", "", "");

        request.setAttribute("areaList", areaList);
        request.setAttribute("buildList", buildList);
        request.setAttribute("roomnameList", roomnameList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        request.setAttribute("totalRows", page.getTotalRows());
        return mapping.findForward("courseplanquery");
    }

    public ActionForward courseplanQuery(ActionMapping mapping, ActionForm form, HttpServletRequest request, HttpServletResponse response) throws Exception {
        DynaActionForm dform = (DynaActionForm) form;

        DBPageLimit page = new DBPageLimit();
        PageLimitUtil.pageInfoPopulate("ec", request, page);

        courseplanService.findCourseplan(dform, page);
        String areaCode = dform.getString("schoolArea");
        String build = dform.getString("build");
        String pid = dform.getString("pid");
        String classno = dform.getString("classno");

        List facultyList = departmentService.findFaculty();
        List areaList = new ArrayList();
        List buildList = new ArrayList();
        List roomnameList = new ArrayList();
        List deptList = new ArrayList();
        List courseList = departmentService.findCourse(areaCode, pid, classno);

        // 楼宇列表
        if (StringUtils.isNotBlank(pid)) {
            areaList = departmentService.findAreaFromDepartment(pid);
        }
        if (StringUtils.isNotBlank(build)) {
            // 教室列表
            roomnameList = roomService.getRoomNameList(build);
        }
        if (StringUtils.isNotBlank(areaCode)) {
            buildList = roomService.getBuildList(areaCode);
            deptList = departmentService.findDepartment(areaCode, pid);
        }

        request.setAttribute("areaList", areaList);
        request.setAttribute("buildList", buildList);
        request.setAttribute("roomnameList", roomnameList);
        request.setAttribute("facultyList", facultyList);
        request.setAttribute("deptList", deptList);
        request.setAttribute("courseList", courseList);

        request.setAttribute("courseplanList", page.getResult());
        request.setAttribute("totalRows", page.getTotalRows());

        return mapping.findForward("courseplanquery");
    }
}
