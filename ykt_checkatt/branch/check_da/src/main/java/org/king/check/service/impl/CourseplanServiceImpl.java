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
            StringBuffer hql = new StringBuffer("select cpc.id.planid,replace(wmsys.wm_concat(d.name),',','��<BR>') from TCourseplanclass cpc,Department d where cpc.id.classno=d.id and (");
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

        TCourseplan courseplan = courseplanDAO.getTCourseplan(planId);//ԭ���γ̼ƻ�
        Integer beginWeek = courseplan.getBeginWeek();
        Integer endWeek = courseplan.getEndWeek();

        TArea area = areaService.getArea(dform.get("areaCode").toString());
        TRoom room = roomService.findOneRoom(area.getAreaName(), dform.get("build").toString(), dform.get("roomname").toString());

//        Department dept = departmentService.getDepartment(dform.get("gardno").toString());


        if (room == null) {
            result = result + "У�������ϵ����";

        }
        TCustomer cust = customerService.findCustByStuemp(dform.get("stuempNo").toString());
        if (cust == null || !cust.getCustname().equals(dform.get("custName").toString())) {
            result = result + "���źͽ�ʦ��������Ӧ��";

        }
        //  List  planList = findCourseplan(dform);
        //  if(planList!=null&&planList.size()>0){//��ʱ���������γ�ʹ�ô˽���
        //  	result=result+"��ʱ���������γ�ʹ�ô˽��ҡ�";
        // return mapping.findForward("courseplanedit");
        //  }
        if (!"".equals(result)) {
            return result;
        }


        //PersonsTaskBiz.updateDoorList(courseplan.getCourse().getCourseid(), courseplan.getRoom().getRoomId());


        TTerm term = termService.getTerm(courseplan.getTerm().getTermId());
        String beginDate = term.getBeginDate();//ѧ�ڿ�ʼʱ��
        String useDate = DateUtilExtend.getCourseDate(beginDate, Integer.parseInt(dform.getString("useWeek")), Integer.parseInt(dform.getString("week")), "yyyyMMdd");
        BeanUtils.copyProperties(courseplan, dform);
        courseplan.setUseDate(useDate);
        courseplan.setRoom(room);
//        courseplan.setDept(dept);
        String beginTime = "";
        String endTime = "";
        //���ݿδλ������ʱ��
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

        result = result + "�޸ĳɹ�";
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
     * �ж϶�Ӧ�γ̼ƻ��Ƿ��Ѿ������ݿ���
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
            String beginDate = term.getBeginDate();//ѧ�ڿ�ʼʱ��
            int rowCount = sheet.getPhysicalNumberOfRows();
            String nowTime = DateUtilExtend.getTimestamp();
            if (rowCount > 0) {
                int savenum = 0;
                //���ڴ洢�����ϴ��Ŀγ̼ƻ�
                Set courseplans = new HashSet();
                for (int i = 1; i < rowCount; i++) {
                    try {
                        HSSFRow row = sheet.getRow(i);
                        String termName = getTrimedStr(row.getCell((short) 0).getStringCellValue()).trim();//ѧ��
                        String deptName = getTrimedStr(row.getCell((short) 1).getStringCellValue()).trim();//Ժϵ
                        String schoolArea = getTrimedStr(row.getCell((short) 2).getStringCellValue()).trim();//У��
                        String build = getTrimedStr(row.getCell((short) 3).getStringCellValue()).trim();//¥��
                        String roomName = getTrimedStr(row.getCell((short) 4).getStringCellValue()).trim();//����
                        String courseName = getTrimedStr(row.getCell((short) 5).getStringCellValue()).trim();//�γ�
                        String stuempNo = getTrimedStr(row.getCell((short) 6).getStringCellValue()).trim();//��ʦѧ����
                        String custname = getTrimedStr(row.getCell((short) 7).getStringCellValue()).trim();//��ʦ��
                        String classIds = getTrimedStr(row.getCell((short) 8).getStringCellValue()).trim();//�༶����
                        String week = getTrimedStr(row.getCell((short) 9).getStringCellValue()).trim();//�ܼ��Ͽ�
                        String begWeekNum = getTrimedStr(row.getCell((short) 10).getStringCellValue()).trim();//��ʼ�ܴ�
                        String endWeekNum = getTrimedStr(row.getCell((short) 11).getStringCellValue()).trim();//�����ܴ�
                        String beginClassNum = getTrimedStr(row.getCell((short) 12).getStringCellValue()).trim();//��ʼ�δ�
                        String endClassNum = getTrimedStr(row.getCell((short) 13).getStringCellValue()).trim();//�����δ�
                        String ischeck = getTrimedStr(row.getCell((short) 14).getStringCellValue()).trim();//�Ƿ���
                        String isopen = getTrimedStr(row.getCell((short) 15).getStringCellValue()).trim();//�Ƿ���

                        //�жϵ�ǰ�γ̼ƻ��Ƿ��Ѿ�����
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


                        if (isopen.equals("��")) {
                            isopen = "1";
                        } else if (isopen.equals("��")) {
                            isopen = "0";
                        }

                        if (ischeck.equals("��")) {
                            ischeck = "1";
                        } else if (ischeck.equals("��")) {
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

                            //ʹ�õĵ�ǰ��
                            courseplan.setUseWeek(new Integer(j));

                            //���ݵڼ����ܼ������ʱ��
                            String useDate = DateUtilExtend.getCourseDate(beginDate, j, Integer.parseInt(week), "yyyyMMdd");
                            courseplan.setUseDate(useDate);

                            //���ݿδλ������ʱ��
                            Map begMap = timeService.getTimeByClass(beginClassNum);
                            Map endMap = timeService.getTimeByClass(endClassNum);
                            if (begMap != null) {
                                beginTime = begMap.get("beginTime").toString();
                            } else {
                                result = result + "��" + rowCount + "��ʼ�δδ���<br>";
                                return result;
                            }
                            if (endMap != null) {
                                endTime = endMap.get("endTime").toString();
                            } else {
                                result = result + "��" + rowCount + "�����δδ���<br>";
                                return result;
                            }
                            courseplan.setBeginTime(beginTime);
                            courseplan.setEndTime(endTime);


                            courseplan.setStatus(1);
                            TCustomer cust = customerService.findCustByStuemp(stuempNo);
                            courseplan.setCustomer(cust);

                            courseplan.setCreateTime(nowTime);

                            //���ҿγ���Ϣ�����û�������γ̡�
                            TCourse course = courseService.findOneCourse(courseName);
                            if (course == null) {
                                course = new TCourse();
                                course.setCoursename(courseName);
                                courseService.saveCourse(course);
                            }

                            courseplan.setCourse(course);

                            //todo ��ʱ���洢Ժϵ�ֶ�
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
                        result = result + "��" + rowCount + "���ݵ���ʧ�ܡ�<br>";
                    }
                }
                result = "�ɹ�����" + savenum + "����¼��<br>";
            } else {
                result = "û���ҵ���Ч�ļ�¼";
            }
        } catch (Exception e) {

            return result;
        }
        return result;
    }

    //�ж������Ƿ���Ե���
    public String ifCourseCanImp(HSSFSheet sheet, String termId, String areaCode) {
        String result = "";

        int rowCount = sheet.getPhysicalNumberOfRows();
        if (rowCount > 0) {
            for (int i = 1; i < rowCount; i++) {
                try {
                    String termName = "";//ѧ��
                    String schoolArea = "";//У��
                    String build = "";//¥��
                    String roomName = "";//����
                    String courseName = "";//�γ�
                    String stuempNo = "";//��ʦѧ����
                    String custname = "";//��ʦ��
                    String classIds = "";//�༶��
                    String week = "";//�ܼ��Ͽ�
                    String begWeekNum = "";//��ʼ�ܴ�
                    String endWeekNum = "";//�����ܴ�
                    String beginClassNum = "";//��ʼ�δ�
                    String endClassNum = "";//�����δ�
                    String ischeck = "";//�Ƿ���
                    String isopen = "";//�Ƿ���
                    String deptName = "";//Ժϵ
                    try {
                        HSSFRow row = sheet.getRow(i);
                        termName = getTrimedStr(row.getCell((short) 0).getStringCellValue()).trim();//ѧ��
                        deptName = getTrimedStr(row.getCell((short) 1).getStringCellValue()).trim();//У��
                        schoolArea = getTrimedStr(row.getCell((short) 2).getStringCellValue()).trim();//У��
                        build = getTrimedStr(row.getCell((short) 3).getStringCellValue()).trim();//¥��
                        roomName = getTrimedStr(row.getCell((short) 4).getStringCellValue()).trim();//����
                        courseName = getTrimedStr(row.getCell((short) 5).getStringCellValue()).trim();//�γ�
                        stuempNo = getTrimedStr(row.getCell((short) 6).getStringCellValue()).trim();//��ʦѧ����
                        custname = getTrimedStr(row.getCell((short) 7).getStringCellValue()).trim();//��ʦ��
                        classIds = getTrimedStr(row.getCell((short) 8).getStringCellValue()).trim();//�༶����
                        week = getTrimedStr(row.getCell((short) 9).getStringCellValue()).trim();//�ܼ��Ͽ�
                        begWeekNum = getTrimedStr(row.getCell((short) 10).getStringCellValue()).trim();//��ʼ�ܴ�
                        endWeekNum = getTrimedStr(row.getCell((short) 11).getStringCellValue()).trim();//�����ܴ�
                        beginClassNum = getTrimedStr(row.getCell((short) 12).getStringCellValue()).trim();//��ʼ�δ�
                        endClassNum = getTrimedStr(row.getCell((short) 13).getStringCellValue()).trim();//�����δ�
                        ischeck = getTrimedStr(row.getCell((short) 14).getStringCellValue()).trim();//�����δ�
                        isopen = getTrimedStr(row.getCell((short) 15).getStringCellValue()).trim();//�����δ�
                    } catch (NumberFormatException ne) {
                        result = result + "��" + i + "���������ݷ��ı����ͣ��޸��ı����ͺ��ٵ��롣<br>";
                    } catch (NullPointerException n) {
                        result = result + "��" + i + "���п����ݣ��������ٵ��롣<br>";
                    }

                    TTerm term = termService.getTerm(termId);

                    if (!term.getTermName().equals(termName)) {
                        result = result + "��" + i + "��ѧ����" + termName + "��ϵͳѧ������ƥ�䣬���޸���ȷ���ٵ��롣<br>";
                        break;
                    }

                    //todo ��ʱ���ж�Ժϵ�Ƿ�ƥ��
                    /*Department dept = departmentService.getDepartmentByName(deptName);
                    if (dept == null) {
                        result = result + "��" + i + "��Ժϵ��" + deptName + "����ϵͳû��ƥ��Ĺ�ϵ��������󣬺��ٵ��롣<br>";
                    }*/


                    TRoom r = roomService.findOneRoom(schoolArea, build, roomName);
                    if (r == null) {
                        result = result + "��" + i + "��У��:" + schoolArea + ",¥��:" + build + ",����:" + roomName + ":����ϵͳû��ƥ��Ĺ�ϵ��������󣬻��������Һ��ٵ��롣<br>";
                    }

                    TCustomer cust = customerService.findCustByStuemp(stuempNo);
                    if (cust == null || !cust.getCustname().equals(custname)) {
                        result = result + "��" + i + "�й���" + stuempNo + "�ͽ�ʦ����" + custname + "����Ӧ�����޸ĺ��ٵ��롣<br>";
                    }

                    String[] classId = StringUtil.split(classIds, ",");
                    if (classId.length == 0) {
                        result = result + "��" + i + "�а༶���벻��Ϊ�ա�<br>";
                    }

                    for (int j = 0; j < classId.length; j++) {
                        java.util.List classList = departmentService.findDept(classId[j].toUpperCase());
                        if (classList == null || classList.isEmpty()) {
                            result = result + "��" + i + "�а༶���룬��ϵͳ�༶���벻ƥ��,���޸���ȷ�������Ӱ༶���ٵ��롣<br>";
                        }
                    }
                    if (!ischeck.equals("��") && !ischeck.equals("��")) {
                        result = result + "��" + i + "���Ƿ��ڣ�Ӧ��д�ǻ��<br>";
                    }
                    if (!isopen.equals("��") && !isopen.equals("��")) {
                        result = result + "��" + i + "���Ƿ��ţ�Ӧ��д�ǻ��<br>";
                    }
                    try {
                        if (!(Integer.parseInt(week) >= 1 && Integer.parseInt(week) <= 7)) {
                            result = result + "��" + i + "���ܼ���ȡֵ��ΧӦ1��7��<br>";
                        }
                        if (!(Integer.parseInt(begWeekNum) >= 1 && Integer.parseInt(begWeekNum) <= Integer.parseInt(endWeekNum))) {
                            result = result + "��" + i + "�п�ʼ�ܴε�ȡֵ��ΧӦ1��ѧ�ڽ����ܴΡ�<br>";
                        }
                        if (!(Integer.parseInt(endWeekNum) >= (Integer.parseInt(begWeekNum)))) {//todo ѧ�ڽ�����
                            result = result + "��" + i + "�н����ܴε�ȡֵ��ΧӦ���ڵ��ڿ�ʼ�ܣ�С�ڵ���ѧ���ܴΡ�<br>";
                        }
                        if (Integer.parseInt(endWeekNum) > 52) {
                            result = result + "��" + i + "�н����ܴ�,����ѧ�ڷ�Χ��<br>";
                        }
                        if (!(Integer.parseInt(endClassNum) >= 1 && Integer.parseInt(endClassNum) <= 13
                                && Integer.parseInt(endClassNum) >= Integer.parseInt(beginClassNum))) {
                            result = result + "��" + i + "�н����δε�ȡֵ��ΧӦ���ڵ��ڿ�ʼ�δΣ�С�ڵ���13��<br>";
                        }

                        if (!(Integer.parseInt(beginClassNum) >= 1 && Integer.parseInt(beginClassNum) <= 13
                                && Integer.parseInt(beginClassNum) <= Integer.parseInt(endClassNum))) {
                            result = result + "��" + i + "�п�ʼ�δε�ȡֵ��ΧӦ���ڵ���1��С�ڵ��ڽ����ܴΡ�<br>";
                        }

                        if (Integer.parseInt(beginClassNum) <= 4 && Integer.parseInt(endClassNum) > 4) {
                            result = result + "��" + i + "�пδε�ȡֵ��Χ���ܿ������硣<br>";
                        }
                        if (Integer.parseInt(beginClassNum) <= 8 && Integer.parseInt(endClassNum) > 8) {
                            result = result + "��" + i + "�пδε�ȡֵ��Χ���ܿ����磬���ϡ�<br>";
                        }

                    } catch (NumberFormatException e) {
                        result = result + "��" + i + "�������зǷ����������ͣ������޸ĺ��ٵ��롣<br>";
                    }
                } catch (Exception e) {
                    result = result + "��" + i + "�������쳣�������޸ĺ��ٵ��롣<br>";
                    return result;
                }
            }
        } else {
            result = "û���ҵ���Ч�ļ�¼";
        }
        if (!"".equals(result)) {
            result = result + "����ʧ�ܡ�";
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
