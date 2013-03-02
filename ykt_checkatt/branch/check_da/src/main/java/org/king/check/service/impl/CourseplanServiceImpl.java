package org.king.check.service.impl;

import org.apache.commons.beanutils.BeanUtils;
import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.struts.action.ActionForm;
import org.apache.struts.action.DynaActionForm;
import org.king.check.Constants;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.common.query.QueryTranslate;
import org.king.check.dao.CourseplanDAO;
import org.king.check.domain.*;
import org.king.check.door.PersonsTaskBiz;
import org.king.check.service.*;
import org.king.check.util.DateUtilExtend;
import org.king.utils.DateUtil;
import org.king.utils.StringUtil;

import java.util.*;

public class CourseplanServiceImpl implements CourseplanService {

    private CourseplanDAO courseplanDAO;

    private RoomService roomService;

    private CustomerService customerService;

    private TermService termService;

    private CourseService courseService;

    private TimeService timeService;

    private AreaService areaService;

    private DepartmentService departmentService;

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
    }

    public List findCourseplanclass(String planId) {
        StringBuffer query = new StringBuffer(" ");
        query.append("  from TCourseplanclass c where c.id.planid='").append(planId).append("'");
        return courseplanDAO.findplanclass(query.toString());
    }


    public void setAreaService(AreaService areaService) {
        this.areaService = areaService;
    }

    public void deleteCourseplanClass(TCourseplanclass planclass) {
        courseplanDAO.delete(planclass);
    }


    public void findCourseplan(DynaActionForm dform, DBPageLimit page) throws Exception {
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString("select distinct t.id as Id, t.room.schoolArea.areaName as areaName,t.room.build as build,t.room.roomName as roomName,t.customer.stuempno as stuempNo, t.customer.custname as custName, t.course.coursename as courseName,'' as className,t.week as week,t.useWeek as useWeek,t.useDate as useDate,t.beginClassNum as beginClassNum,t.endClassNum as endClassNum from TCourseplan t");
        String classno = dform.get("classno").toString();
        String departmentName = dform.get("departmentName").toString();
        String pid = dform.get("pid").toString();
        //change hql
        if(StringUtils.isNotBlank(classno) || StringUtils.isNotBlank(departmentName) || StringUtils.isNotBlank(pid)){
            queryTranslate.setQueryString("select distinct t.id as Id, t.room.schoolArea.areaName as areaName,t.room.build as build,t.room.roomName as roomName,t.customer.stuempno as stuempNo, t.customer.custname as custName, t.course.coursename as courseName,'' as className,t.week as week,t.useWeek as useWeek,t.useDate as useDate,t.beginClassNum as beginClassNum,t.endClassNum as endClassNum from TCourseplan t,TCourseplanclass cpc,Department d,TFaculty f where cpc.id.classno=d.id and t.id=cpc.id.planid and f.value=d.faculty");
        }

        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNo() - 1) * page.getPageSize());
        queryTranslate.setPageSize(page.getPageSize());
        queryTranslate.setOrderby(" order by t.useDate desc,t.id");

        if (StringUtils.isNotBlank(classno)) {
            queryTranslate.addEqualCondition("cpc.id.classno", classno);
        }
        if (StringUtils.isNotBlank(departmentName)) {
            queryTranslate.addLikeCondition("d.name", departmentName);
        }
        if (StringUtils.isNotBlank(pid)) {
            queryTranslate.addLikeCondition("f.pid", pid);
        }

        String stuempNo = dform.get("stuempNo").toString();
        if (StringUtils.isNotBlank(stuempNo)) {
            queryTranslate.addLikeCondition("t.customer.stuempno", stuempNo);
        }
        String custName = dform.get("custName").toString();
        if (StringUtils.isNotBlank(custName)) {
            queryTranslate.addLikeCondition("t.customer.custname", custName);
        }
        String beginDate = dform.get("beginDate").toString();
        if (StringUtils.isBlank(beginDate)) {
            beginDate = DateUtil.getFirstDayOfWeek("yyyyMMdd");
            dform.set("beginDate", beginDate);
        }
        queryTranslate.addCondition("t.useDate", Constants.OPRATER_GREATER_AND_EQUAL, beginDate);

        String endDate = dform.get("endDate").toString();
        if (StringUtils.isBlank(endDate)) {
            endDate = DateUtil.getNow("yyyyMMdd");
            dform.set("endDate", endDate);
        }
        queryTranslate.addCondition("t.useDate", Constants.OPRATER_LESS_AND_EQUAL, endDate);

        String useWeek = dform.get("useWeek").toString();
        if (StringUtils.isNotBlank(useWeek)) {
            queryTranslate.addEqualCondition("t.useWeek", useWeek);
        }
        String beginWeek = dform.get("beginWeek").toString();
        if (StringUtils.isNotBlank(beginWeek)) {
            queryTranslate.addEqualCondition("t.beginWeek", Integer.valueOf(beginWeek));
        }
        String endWeek = dform.get("endWeek").toString();
        if (StringUtils.isNotBlank(endWeek)) {
            queryTranslate.addEqualCondition("t.endWeek", Integer.valueOf(endWeek));
        }
        String courseId = dform.get("courseId").toString();
        if (StringUtils.isNotBlank(courseId)) {
            queryTranslate.addEqualCondition("t.course.courseid", courseId);
        }

        String week = dform.get("week").toString();
        if (StringUtils.isNotBlank(week)) {
            queryTranslate.addEqualCondition("t.week", week);
        }
        String beginClassNum = dform.get("beginClassNum").toString();
        if (StringUtils.isNotBlank(beginClassNum)) {
            queryTranslate.addEqualCondition("t.beginClassNum", Integer.valueOf(beginClassNum));
        }
        String endClassNum = dform.get("endClassNum").toString();
        if (StringUtils.isNotBlank(endClassNum)) {
            queryTranslate.addEqualCondition("t.endClassNum", Integer.valueOf(endClassNum));
        }
        String schoolArea = dform.get("schoolArea").toString();
        if (StringUtils.isNotBlank(schoolArea)) {
            queryTranslate.addEqualCondition("t.room.schoolArea.areaCode", schoolArea);
        }
        String build = dform.get("build").toString();
        if (StringUtils.isNotBlank(build)) {
            queryTranslate.addEqualCondition("t.room.build", build);
        }
        String roomname = dform.get("roomname").toString();
        if (StringUtils.isNotBlank(roomname)) {
            queryTranslate.addEqualCondition("t.room.roomName", roomname);
        }
        String classname = dform.get("classname").toString();
        if (StringUtils.isNotBlank(classname)) {
            queryTranslate.addLikeCondition("d.name", classname);
        }

        page.setMap(true);
        courseplanDAO.findCourseplanByPage(page, queryTranslate);

        //find the class name according to plan id
        if (page.getResult() != null && page.getResult().size() > 0) {
            StringBuffer hql = new StringBuffer("select cpc.id.planid,replace(wmsys.wm_concat(d.name),',','；<BR>') from TCourseplanclass cpc,Department d where cpc.id.classno=d.id and (");
            for (int i = 0; i < page.getResult().size(); i++) {
                Map row = (Map) page.getResult().get(i);
                hql.append("cpc.id.planid='").append(row.get("Id")).append("' or ");
            }
            hql = hql.delete(hql.length()-3,hql.length()-1);
            hql.append(") group by cpc.id.planid");
            Map deptMap = new HashMap();
            List list = courseplanDAO.find(hql.toString());
            if (list != null && list.size() > 0) {
                for (int i = 0; i < list.size(); i++) {
                    Object[] cpc = (Object[]) list.get(i);
                    deptMap.put(cpc[0], cpc[1]);
                }
                for (int i = 0; i < page.getResult().size(); i++) {
                    Map row = (Map) page.getResult().get(i);
                    row.put("className", deptMap.get(row.get("Id")));
                }
            }
        }
    }

    public void deleteCourseplan(TCourseplan courseplan) throws Exception {
        courseplanDAO.delete(courseplan);

    }


    public void updateCourseplan(TCourseplan courseplan) throws Exception {
        courseplanDAO.update(courseplan);
    }

    private void updateCourseplan(TCourseplan courseplan, String[] classes) {
        //delete the exist classes
        Set<TCourseplanclass> courseplanclasses = courseplan.getCourseplanClass();
        for (TCourseplanclass courseplanclass : courseplanclasses) {
            courseplanDAO.delete(courseplanclass);
        }
        courseplanclasses.clear();

        if (classes != null) {
            for (String departmentId : classes) {
                TCourseplanclass courseplanclass = new TCourseplanclass();
                TCourseplanclassId courseplanclassId = new TCourseplanclassId();
                courseplanclassId.setClassno(departmentId);
                courseplanclassId.setPlanid(courseplan.getId());
                courseplanclass.setId(courseplanclassId);

                courseplanclasses.add(courseplanclass);
                courseplanDAO.save(courseplanclass);

            }
        }
    }

    public String updateCourseplan(ActionForm form, String planId, String[] classes)
            throws Exception {
        String result = "";
        DynaActionForm dform = (DynaActionForm) form;

        TCourseplan courseplan = courseplanDAO.getTCourseplan(planId);//原来课程计划
        Integer beginWeek = courseplan.getBeginWeek();
        Integer endWeek = courseplan.getEndWeek();

        TArea area = areaService.getArea(dform.get("areaCode").toString());
        TRoom room = roomService.findOneRoom(area.getAreaName(), dform.get("build").toString(), dform.get("roomname").toString());

//        Department dept = departmentService.getDepartment(dform.get("gardno").toString());


        if (room == null) {
            result = result + "校区房间关系错误。";

        }
        TCustomer cust = customerService.findCustByStuemp(dform.get("stuempNo").toString());
        if (cust == null || !cust.getCustname().equals(dform.get("custName").toString())) {
            result = result + "工号和教师姓名不对应。";

        }
        //  List  planList = findCourseplan(dform);
        //  if(planList!=null&&planList.size()>0){//此时段有其他课程使用此教室
        //  	result=result+"此时段有其他课程使用此教室。";
        // return mapping.findForward("courseplanedit");
        //  }
        if (!"".equals(result)) {
            return result;
        }


        //PersonsTaskBiz.updateDoorList(courseplan.getCourse().getCourseid(), courseplan.getRoom().getRoomId());


        TTerm term = termService.getTerm(courseplan.getTerm().getTermId());
        String beginDate = term.getBeginDate();//学期开始时间
        String useDate = DateUtilExtend.getCourseDate(beginDate, Integer.parseInt(dform.getString("useWeek")), Integer.parseInt(dform.getString("week")), "yyyyMMdd");
        BeanUtils.copyProperties(courseplan, dform);
        courseplan.setUseDate(useDate);
        courseplan.setRoom(room);
//        courseplan.setDept(dept);
        String beginTime = "";
        String endTime = "";
        //根据课次换算具体时间
        Map begMap = timeService.getTimeByClass(dform.getString("beginClassNum"));
        Map endMap = timeService.getTimeByClass(dform.getString("endClassNum"));
        if (begMap != null) {
            beginTime = begMap.get("beginTime").toString();
        }
        if (endMap != null) {
            endTime = endMap.get("endTime").toString();
        }
        courseplan.setBeginTime(beginTime);
        courseplan.setEndTime(endTime);
        courseplan.setBeginWeek(beginWeek);
        courseplan.setEndWeek(endWeek);
        courseplan.setCustomer(cust);
        courseplanDAO.update(courseplan);
        //update the relationship first
        updateCourseplan(courseplan, classes);

//        PersonsTaskBiz.insertDoorList();

        result = result + "修改成功";
        return result;
    }

    public TCourseplan getTCourseplan(String id) throws Exception {
        return (TCourseplan) courseplanDAO.getTCourseplan(id);
    }

    public List getClassByPlanId(String id) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select new Map(c.id.planid as planid ,c.id.classno as classno  )")
                .append(" from TCourseplanclass c  where c.id.planid ='").append(id).append("'");
        List list = courseplanDAO.find(query.toString());
        return list;
    }


    public Map getTCourseplanMap(String id) throws Exception {
        StringBuffer query = new StringBuffer(" ");
        query.append("select new Map ( t.dept.id as gardno ,t.id as Id ,t.room.schoolArea.areaCode as areaCode , ")
                .append(" t.room.schoolArea.areaName as areaName ,")
                .append(" t.room.build as build ,")
                .append(" t.room.roomName as roomname ,")
                .append(" t.customer.stuempno  as stuempNo ,")
                .append(" t.customer.custname as custName , ")
                .append(" t.week as week ,")
                .append(" t.useWeek as useWeek ,")
                .append(" t.useDate as useDate ,")
                .append(" t.beginClassNum as beginClassNum ,")
                .append(" t.endClassNum as endClassNum ,")
                .append(" t.beginWeek as beginWeek ,")
                .append(" t.endWeek as endWeek ,")
                .append(" t.ischeck as ischeck ,")
                .append(" t.isopen as isopen")
                .append(" ) from ")
                .append(" TCourseplan t where 1 = 1 ")
                .append(" and t.id ='").append(id).append("'");
        List list = courseplanDAO.find(query.toString());
        return (Map) list.get(0);
    }

    /**
     * 判断对应课程计划是否已经在数据库中
     *
     * @param tCourseplan  .
     * @return             .
     */
    public boolean isExistCourplan(TCourseplan tCourseplan){
        StringBuffer hql = new StringBuffer("from TCourseplan t where");
        hql.append(" t.term.termId='").append(tCourseplan.getTerm().getTermId()).append("'");
        hql.append(" and t.room.roomId='").append(tCourseplan.getRoom().getRoomId()).append("'");
        hql.append(" and t.week=").append(tCourseplan.getWeek());
        hql.append(" and t.beginClassNum=").append(tCourseplan.getBeginClassNum());
        hql.append(" and t.endClassNum=").append(tCourseplan.getEndClassNum());
        hql.append(" and t.useWeek=").append(tCourseplan.getUseWeek());
        List result = courseplanDAO.find(hql.toString());
        return result != null && result.size() > 0;
    }

    public String saveCourseplanImp(HSSFSheet sheet, String termId, String userId) {
        String result = "";

        try {
            TTerm term = termService.getTerm(termId);
            String beginDate = term.getBeginDate();//学期开始时间
            int rowCount = sheet.getPhysicalNumberOfRows();
            String nowTime = DateUtilExtend.getTimestamp();
            if (rowCount > 0) {
                int savenum = 0;
                //用于存储本次上传的课程计划
                Set courseplans = new HashSet();
                for (int i = 1; i < rowCount; i++) {
                    try {
                        HSSFRow row = sheet.getRow(i);
                        String termName = getTrimedStr(row.getCell((short) 0).getStringCellValue()).trim();//学期
                        String deptName = getTrimedStr(row.getCell((short) 1).getStringCellValue()).trim();//院系
                        String schoolArea = getTrimedStr(row.getCell((short) 2).getStringCellValue()).trim();//校区
                        String build = getTrimedStr(row.getCell((short) 3).getStringCellValue()).trim();//楼宇
                        String roomName = getTrimedStr(row.getCell((short) 4).getStringCellValue()).trim();//教室
                        String courseName = getTrimedStr(row.getCell((short) 5).getStringCellValue()).trim();//课程
                        String stuempNo = getTrimedStr(row.getCell((short) 6).getStringCellValue()).trim();//教师学工号
                        String custname = getTrimedStr(row.getCell((short) 7).getStringCellValue()).trim();//教师名
                        String classIds = getTrimedStr(row.getCell((short) 8).getStringCellValue()).trim();//班级编码
                        String week = getTrimedStr(row.getCell((short) 9).getStringCellValue()).trim();//周几上课
                        String begWeekNum = getTrimedStr(row.getCell((short) 10).getStringCellValue()).trim();//开始周次
                        String endWeekNum = getTrimedStr(row.getCell((short) 11).getStringCellValue()).trim();//结束周次
                        String beginClassNum = getTrimedStr(row.getCell((short) 12).getStringCellValue()).trim();//开始课次
                        String endClassNum = getTrimedStr(row.getCell((short) 13).getStringCellValue()).trim();//结束课次
                        String ischeck = getTrimedStr(row.getCell((short) 14).getStringCellValue()).trim();//是否考勤
                        String isopen = getTrimedStr(row.getCell((short) 15).getStringCellValue()).trim();//是否开门

                        //判断当前课程计划是否已经导入
                        StringBuffer key = new StringBuffer();
                        key.append(termName).append(",").append(deptName).append(",").append(schoolArea).append(",").append(build).append(",")
                                .append(roomName).append(",").append(courseName).append(",").append(stuempNo).append(",")
                                .append(week).append(",").append(begWeekNum).append(",").append(endWeekNum).append(",")
                                .append(beginClassNum).append(",").append(endClassNum);
                        if(courseplans.contains(key.toString())){
                            continue;
                        } else{
                            courseplans.add(key.toString());
                        }


                        if (isopen.equals("是")) {
                            isopen = "1";
                        } else if (isopen.equals("否")) {
                            isopen = "0";
                        }

                        if (ischeck.equals("是")) {
                            ischeck = "1";
                        } else if (ischeck.equals("否")) {
                            ischeck = "0";
                        }
                        String beginTime = "";
                        String endTime = "";
                        for (int j = Integer.parseInt(begWeekNum); j <= Integer.parseInt(endWeekNum); j++) {

                            TCourseplan courseplan = new TCourseplan();
                            TRoom room = roomService.findOneRoom(schoolArea, build, roomName);
                            courseplan.setTerm(new TTerm(termId));
                            courseplan.setRoom(room);
                            courseplan.setBeginWeek(Integer.valueOf(begWeekNum));
                            courseplan.setEndWeek(Integer.valueOf(endWeekNum));
                            courseplan.setWeek(Integer.valueOf(week));
                            courseplan.setBeginClassNum(Integer.valueOf(beginClassNum));
                            courseplan.setEndClassNum(Integer.valueOf(endClassNum));
                            courseplan.setCreator(userId);
                            courseplan.setIscheck(Integer.parseInt(ischeck));
                            courseplan.setIsopen(Integer.parseInt(isopen));

                            //使用的当前周
                            courseplan.setUseWeek(new Integer(j));

                            //根据第几周周几查具体时间
                            String useDate = DateUtilExtend.getCourseDate(beginDate, j, Integer.parseInt(week), "yyyyMMdd");
                            courseplan.setUseDate(useDate);

                            //根据课次换算具体时间
                            Map begMap = timeService.getTimeByClass(beginClassNum);
                            Map endMap = timeService.getTimeByClass(endClassNum);
                            if (begMap != null) {
                                beginTime = begMap.get("beginTime").toString();
                            } else {
                                result = result + "第" + rowCount + "开始课次错误。<br>";
                                return result;
                            }
                            if (endMap != null) {
                                endTime = endMap.get("endTime").toString();
                            } else {
                                result = result + "第" + rowCount + "结束课次错误。<br>";
                                return result;
                            }
                            courseplan.setBeginTime(beginTime);
                            courseplan.setEndTime(endTime);


                            courseplan.setStatus(1);
                            TCustomer cust = customerService.findCustByStuemp(stuempNo);
                            courseplan.setCustomer(cust);

                            courseplan.setCreateTime(nowTime);

                            //查找课程信息，如果没有新增课程。
                            TCourse course = courseService.findOneCourse(courseName);
                            if (course == null) {
                                course = new TCourse();
                                course.setCoursename(courseName);
                                courseService.saveCourse(course);
                            }

                            courseplan.setCourse(course);

                            //todo 暂时不存储院系字段
//                            Department dept = departmentService.getDepartmentByName(deptName);

//                            courseplan.setDept(dept);

                            if (!isExistCourplan(courseplan)) {
                                courseplanDAO.save(courseplan);

                                String[] classId = StringUtil.split(classIds, ",");
                                if (classId != null && classId.length > 0) {
                                    for (int k = 0; k < classId.length; k++) {
                                        TCourseplanclassId id = new TCourseplanclassId(courseplan.getId(), classId[k].toUpperCase());
                                        TCourseplanclass courseplanclass = new TCourseplanclass(id);
                                        courseplanDAO.save(courseplanclass);
                                    }
                                }
                            }
                        }
                        savenum++;
                    } catch (Exception e) {
                        result = result + "第" + rowCount + "数据导入失败。<br>";
                    }
                }
                result = "成功导入" + savenum + "条记录。<br>";
            } else {
                result = "没有找到有效的记录";
            }
        } catch (Exception e) {

            return result;
        }
        return result;
    }

    //判断数据是否可以导入
    public String ifCourseCanImp(HSSFSheet sheet, String termId, String areaCode) {
        String result = "";

        int rowCount = sheet.getPhysicalNumberOfRows();
        if (rowCount > 0) {
            for (int i = 1; i < rowCount; i++) {
                try {
                    String termName = "";//学期
                    String schoolArea = "";//校区
                    String build = "";//楼宇
                    String roomName = "";//教室
                    String courseName = "";//课程
                    String stuempNo = "";//教师学工号
                    String custname = "";//教师名
                    String classIds = "";//班级名
                    String week = "";//周几上课
                    String begWeekNum = "";//开始周次
                    String endWeekNum = "";//结束周次
                    String beginClassNum = "";//开始课次
                    String endClassNum = "";//结束课次
                    String ischeck = "";//是否考勤
                    String isopen = "";//是否开门
                    String deptName = "";//院系
                    try {
                        HSSFRow row = sheet.getRow(i);
                        termName = getTrimedStr(row.getCell((short) 0).getStringCellValue()).trim();//学期
                        deptName = getTrimedStr(row.getCell((short) 1).getStringCellValue()).trim();//校区
                        schoolArea = getTrimedStr(row.getCell((short) 2).getStringCellValue()).trim();//校区
                        build = getTrimedStr(row.getCell((short) 3).getStringCellValue()).trim();//楼宇
                        roomName = getTrimedStr(row.getCell((short) 4).getStringCellValue()).trim();//教室
                        courseName = getTrimedStr(row.getCell((short) 5).getStringCellValue()).trim();//课程
                        stuempNo = getTrimedStr(row.getCell((short) 6).getStringCellValue()).trim();//教师学工号
                        custname = getTrimedStr(row.getCell((short) 7).getStringCellValue()).trim();//教师名
                        classIds = getTrimedStr(row.getCell((short) 8).getStringCellValue()).trim();//班级编码
                        week = getTrimedStr(row.getCell((short) 9).getStringCellValue()).trim();//周几上课
                        begWeekNum = getTrimedStr(row.getCell((short) 10).getStringCellValue()).trim();//开始周次
                        endWeekNum = getTrimedStr(row.getCell((short) 11).getStringCellValue()).trim();//结束周次
                        beginClassNum = getTrimedStr(row.getCell((short) 12).getStringCellValue()).trim();//开始课次
                        endClassNum = getTrimedStr(row.getCell((short) 13).getStringCellValue()).trim();//结束课次
                        ischeck = getTrimedStr(row.getCell((short) 14).getStringCellValue()).trim();//结束课次
                        isopen = getTrimedStr(row.getCell((short) 15).getStringCellValue()).trim();//结束课次
                    } catch (NumberFormatException ne) {
                        result = result + "第" + i + "行数字数据非文本类型，修改文本类型后再导入。<br>";
                    } catch (NullPointerException n) {
                        result = result + "第" + i + "行有空数据，请填充后再导入。<br>";
                    }

                    TTerm term = termService.getTerm(termId);

                    if (!term.getTermName().equals(termName)) {
                        result = result + "第" + i + "行学期名" + termName + "与系统学期名不匹配，请修改正确后再导入。<br>";
                        break;
                    }

                    //todo 暂时不判断院系是否匹配
                    /*Department dept = departmentService.getDepartmentByName(deptName);
                    if (dept == null) {
                        result = result + "第" + i + "行院系：" + deptName + "，在系统没有匹配的关系，请检查错误，后再导入。<br>";
                    }*/


                    TRoom r = roomService.findOneRoom(schoolArea, build, roomName);
                    if (r == null) {
                        result = result + "第" + i + "行校区:" + schoolArea + ",楼宇:" + build + ",房间:" + roomName + ":，在系统没有匹配的关系，请检查错误，或新增教室后再导入。<br>";
                    }

                    TCustomer cust = customerService.findCustByStuemp(stuempNo);
                    if (cust == null || !cust.getCustname().equals(custname)) {
                        result = result + "第" + i + "行工号" + stuempNo + "和教师姓名" + custname + "不对应，请修改后再导入。<br>";
                    }

                    String[] classId = StringUtil.split(classIds, ",");
                    if (classId.length == 0) {
                        result = result + "第" + i + "行班级编码不能为空。<br>";
                    }

                    for (int j = 0; j < classId.length; j++) {
                        java.util.List classList = departmentService.findDept(classId[j].toUpperCase());
                        if (classList == null || classList.isEmpty()) {
                            result = result + "第" + i + "行班级编码，与系统班级编码不匹配,请修改正确，或增加班级后再导入。<br>";
                        }
                    }
                    if (!ischeck.equals("是") && !ischeck.equals("否")) {
                        result = result + "第" + i + "行是否考勤，应填写是或否。<br>";
                    }
                    if (!isopen.equals("是") && !isopen.equals("否")) {
                        result = result + "第" + i + "行是否开门，应填写是或否。<br>";
                    }
                    try {
                        if (!(Integer.parseInt(week) >= 1 && Integer.parseInt(week) <= 7)) {
                            result = result + "第" + i + "行周几的取值范围应1至7。<br>";
                        }
                        if (!(Integer.parseInt(begWeekNum) >= 1 && Integer.parseInt(begWeekNum) <= Integer.parseInt(endWeekNum))) {
                            result = result + "第" + i + "行开始周次的取值范围应1至学期结束周次。<br>";
                        }
                        if (!(Integer.parseInt(endWeekNum) >= (Integer.parseInt(begWeekNum)))) {//todo 学期结束周
                            result = result + "第" + i + "行结束周次的取值范围应大于等于开始周，小于等于学期周次。<br>";
                        }
                        if (Integer.parseInt(endWeekNum) > 52) {
                            result = result + "第" + i + "行结束周次,超出学期范围。<br>";
                        }
                        if (!(Integer.parseInt(endClassNum) >= 1 && Integer.parseInt(endClassNum) <= 13
                                && Integer.parseInt(endClassNum) >= Integer.parseInt(beginClassNum))) {
                            result = result + "第" + i + "行结束课次的取值范围应大于等于开始课次，小于等于13。<br>";
                        }

                        if (!(Integer.parseInt(beginClassNum) >= 1 && Integer.parseInt(beginClassNum) <= 13
                                && Integer.parseInt(beginClassNum) <= Integer.parseInt(endClassNum))) {
                            result = result + "第" + i + "行开始课次的取值范围应大于等于1，小于等于结束周次。<br>";
                        }

                        if (Integer.parseInt(beginClassNum) <= 4 && Integer.parseInt(endClassNum) > 4) {
                            result = result + "第" + i + "行课次的取值范围不能跨上下午。<br>";
                        }
                        if (Integer.parseInt(beginClassNum) <= 8 && Integer.parseInt(endClassNum) > 8) {
                            result = result + "第" + i + "行课次的取值范围不能跨下午，晚上。<br>";
                        }

                    } catch (NumberFormatException e) {
                        result = result + "第" + i + "行数据有非法的整数类型，请检查修改后，再导入。<br>";
                    }
                } catch (Exception e) {
                    result = result + "第" + i + "行数据异常，请检查修改后，再导入。<br>";
                    return result;
                }
            }
        } else {
            result = "没有找到有效的记录";
        }
        if (!"".equals(result)) {
            result = result + "导入失败。";
        }
        return result;
    }

    private String getTrimedStr(String input) {
        if (input.startsWith("sz")) {
            return input.substring(2);
        } else {
            return input;
        }
    }


    public void setTimeService(TimeService timeService) {
        this.timeService = timeService;
    }


    public void setCourseService(CourseService courseService) {
        this.courseService = courseService;
    }


    public void setCourseplanDAO(CourseplanDAO courseplanDAO) {
        this.courseplanDAO = courseplanDAO;
    }


    public void setRoomService(RoomService roomService) {
        this.roomService = roomService;
    }


    public void setCustomerService(CustomerService customerService) {
        this.customerService = customerService;
    }


    public void setTermService(TermService termService) {
        this.termService = termService;
    }


    public void saveCourseplan(TCourseplan courseplan)
            throws Exception {
        courseplanDAO.save(courseplan);

    }

    private static String getCourseDate(String beginDate, int weekNum, int week, String format) {
        String ret = "";
        try {
            java.text.SimpleDateFormat sdf = new java.text.SimpleDateFormat(format);
            Calendar c = Calendar.getInstance(Locale.CHINESE);
            c.setFirstDayOfWeek(Calendar.MONDAY);
            //System.out.println(c.getFirstDayOfWeek());
            Date d = sdf.parse(beginDate);
            // System.out.println(Calendar.MONDAY);
            c.setTime(d);
            c.add(Calendar.WEEK_OF_YEAR, weekNum - 1);
            //System.out.println(sdf.format(c.getTime()));
            c.set(Calendar.DAY_OF_WEEK, week + 1);
            ret = sdf.format(c.getTime());
        }
        catch (Exception e) {

        }
        return ret;
    }


}
