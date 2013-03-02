package org.king.check.service.impl;

import org.apache.commons.lang.StringUtils;
import org.apache.struts.action.DynaActionForm;
import org.king.check.Constants;
import org.king.check.common.ec.DBPageLimit;
import org.king.check.common.query.QueryTranslate;
import org.king.check.dao.CheckrecordDAO;
import org.king.check.dao.CourseplanDAO;
import org.king.check.dao.RoomElecDAO;
import org.king.check.dao.UnplanStudentDAO;
import org.king.check.domain.TCheckstrategy;
import org.king.check.domain.TRoomElec;
import org.king.check.domain.TUnplanstudent;
import org.king.check.domain.TodayStuCheckSearch;
import org.king.check.service.CheckReportService;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.StringUtil;
import org.king.utils.DateUtil;
import org.springframework.jdbc.core.JdbcTemplate;

import java.text.SimpleDateFormat;
import java.util.*;

public class CheckReoprtServiceImpl implements CheckReportService {

    private CourseplanDAO courseplanDAO;

    private JdbcTemplate jdbcTemplate;

    private UnplanStudentDAO unplanstudentDAO;

    private CheckrecordDAO checkrecordDAO;

    private RoomElecDAO roomElecDAO;

    public void setUnplanstudentDAO(UnplanStudentDAO unplanstudentDAO) {
        this.unplanstudentDAO = unplanstudentDAO;
    }

    public void setCourseplanDAO(CourseplanDAO courseplanDAO) {
        this.courseplanDAO = courseplanDAO;
    }

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void setCheckrecordDAO(CheckrecordDAO checkrecordDAO) {
        this.checkrecordDAO = checkrecordDAO;
    }

    public void setRoomElecDAO(RoomElecDAO roomElecDAO) {
        this.roomElecDAO = roomElecDAO;
    }

    // 根据课程计划，查找当日应上课的名单

    public List getAllStudentByPlan(String planId, String classno) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select  t1.id,t4.coursename,t5.short_name as classname,t6.stuempno,t6.custname,t1.usedate, ")
                .append(" t1.begintime,t1.endtime from  ykt_ck.t_courseplan t1  ")
                .append(" inner join ykt_ck.t_courseplanclass t2 on t1.id = t2.planid ")
                .append(" inner join ykt_ck.t_course t4  on t4.courseid = t1.courseid ")
                .append(" inner join ykt_ck.department t5  on t5.dept_id = t2.classno ")
                .append(" inner join ykt_cur.t_customer t6  on t2.classno=t6.classname  ")
                .append(" inner join ykt_ck.t_customer_state t7 on t7.stuempno=t6.stuempno")
                .append(" where t7.stu_state='1' and t1.id='").append(planId).append("'").append(" and t2.classno='").append(classno).append("' ").append(
                " order by t6.stuempno");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 当日实到人员名单查询,开课前30分钟，下课后10分钟有效

    public List getRealStudentByPlan(String planId, String classno) throws Exception {
        StringBuffer query = new StringBuffer();

        String today = DateUtil.getNow("yyyyMMdd");
        query.append("select t.id,t.classno,t.coursename,t.classname,t.stuempno,t.custname,t.usedate,min(cr.PUNCHTIME) || '--' || max(cr.PUNCHTIME) as punchtime");
        query.append(" from (select cr1.* from ykt_cur.t_checkrecord cr1 where cr1.PUNCHDATE = '").append(today).append("') cr,");
        query.append(" (select cp.id,d.dept_id as classno,c.coursename,d.short_name as classname,cus.stuempno,cus.custname,cp.usedate,cus.custid,cp.roomid,cp.begintime,cp.endtime,rd.deviceid");
        query.append(" from ykt_ck.t_courseplan cp,ykt_ck.t_course c,ykt_ck.department d,ykt_cur.t_customer cus,ykt_ck.t_customer_state cuss,ykt_ck.t_roomdevice rd");
        query.append(" where cp.id = '").append(planId).append("'");
        query.append(" and c.courseid = cp.courseid");
        query.append(" and d.dept_id = '").append(classno).append("'");
        query.append(" and cus.classname = d.dept_id and cuss.stuempno = cus.stuempno and cuss.stu_state = '1' and rd.roomid = cp.roomid) t");
        query.append(" where cr.CUSTID = t.custid and cr.DEVICEID = t.deviceid and cr.PUNCHDATE = t.usedate");
        query.append(" and cr.punchtime between to_char(to_date(t.usedate || ' ' || t.begintime,'yyyymmdd hh24:mi:ss') - NUMTODSINTERVAL(30, 'minute'),'hh24miss')");
        query.append(" and to_char(to_date(t.usedate || ' ' || t.endtime, 'yyyymmdd hh24:mi:ss') + NUMTODSINTERVAL(10, 'minute'),'hh24miss')");
        query.append(" group by t.id,t.classno,t.coursename,t.classname,t.stuempno,t.custname,t.usedate");
        query.append(" order by t.stuempno");

        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 当日缺勤

    public List getNotComeStudentByPlan(String planId, String classno) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select  t1.id,t2.classno,t4.coursename,t5.short_name as classname , ")
                .append(" t6.stuempno,t6.custid,t6.custname,t1.usedate ,'缺勤'as punchtime ")
                .append(" from  ykt_ck.t_courseplan t1  ")
                .append(" inner join ykt_ck.t_courseplanclass t2 on t1.id = t2.planid ")
                .append(" inner join ykt_ck.t_course t4  on t4.courseid = t1.courseid ")
                .append(" inner join ykt_ck.department t5  on t5.dept_id = t2.classno ")
                .append(" inner join ykt_cur.t_customer t6  on t2.classno=t6.classname ")
                .append(" inner join ykt_ck.t_customer_state cuss on cuss.stuempno=t6.stuempno")
                .append(" left join (").append(" select distinct(t7.CUSTID)   from  t_checkrecord  t7,  ykt_ck.t_courseplan t8 ")
                .append(" where t8.id= '")
                .append(planId)
                .append("' and t7.deviceid in (select rd.deviceid from ykt_ck.t_roomdevice rd where rd.roomid=t8.roomid)")
                .append(" and   t7.PUNCHDATE = t8.usedate ")
                .append(" and t7.punchtime between ")
                .append(" to_char(to_date(t8.usedate || ' ' || t8.begintime, 'yyyymmdd hh24:mi:ss') -NUMTODSINTERVAL(30, 'minute'),'hh24miss') ")
                .append(" and ")
                .append(" to_char(to_date(t8.usedate || ' ' || t8.endtime, 'yyyymmdd hh24:mi:ss') +  NUMTODSINTERVAL(10, 'minute'),'hh24miss')")
                .append(" ) tt on t6.custid=tt.custid ")
                .append(" where cuss.stu_state='1' and t1.id='")
                .append(planId).append("' and t2.classno='").append(classno)
                .append("'")
                .append(" and tt.custid is null ")
                .append(" order by t6.stuempno");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 学生日报实到,迟到,早退

    public List getDailyStudentOther(String courseid, String classid, String begindate, String enddate, String stuempno, String islate, String isleave) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.id,t1.course_id,t2.coursename,t1.class_id,t3.short_name as classname,  ")
                .append(" t1.stuemp_no as stuempno ,t1.cust_name as custname, t1.usedate ,t1.checktime  ")
                .append(" from ykt_ck.t_tea_stu_dailyrpt  t1")
                .append(" inner join  ykt_ck.t_course t2 on  t1.course_id = t2.courseid ")
                .append(" inner join  ykt_ck.department t3 on  t3.dept_id = t1.class_id ")
                .append(" where t1.cust_type=0 and t1.check_num=1  ");
        if ("1".equals(islate)) {
            query.append(" and t1.come_late_num=1 ");
        } else if ("1".equals(isleave)) {
            query.append(" and t1.leave_early_num=1 ");
        }
        query.append(" and t1.course_id = '").append(courseid).append("'")
                .append(" and t1.class_id = '").append(classid).append("'")
                .append(" and t1.usedate between '").append(begindate).append(
                "'").append(" and '").append(enddate).append("'")
                .append(" and t1.stuemp_no='").append(stuempno).append("'")
                .append(" order by t1.usedate desc,t2.coursename ");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 学生日报表应到明细

    public List getDailyStudentShould(String courseid, String classid, String begindate, String enddate, String stuempno) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.id,t1.course_id,t2.coursename,t1.class_id,t3.short_name as classname,  ")
                .append(" t1.stuemp_no as stuempno ,t1.cust_name as custname, t1.usedate   from ykt_ck.t_tea_stu_dailyrpt  t1")
                .append(" inner join  ykt_ck.t_course t2 on  t1.course_id = t2.courseid ")
                .append(" inner join  ykt_ck.department t3 on  t3.dept_id = t1.class_id ")
                .append(" where t1.cust_type=0 and t1.course_num=1  ").append(" and t1.course_id = '").append(courseid).append("'")
                .append(" and t1.class_id = '").append(classid).append("'")
                .append(" and t1.usedate between '").append(begindate).append("'").append(" and '").append(enddate).append("'")
                .append(" and t1.stuemp_no='").append(stuempno).append("'")
                .append(" order by t1.usedate desc,t2.coursename");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 教师日报表应到明细

    public List getDailyTeacherShould(String courseid, String begindate, String enddate, String stuempno) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.id,t1.course_id,t2.coursename,t1.class_id,  ")
                .append(" t1.stuemp_no as stuempno ,t1.cust_name as custname, t1.usedate   from ykt_ck.t_tea_stu_dailyrpt  t1 ")
                .append(" left join  ykt_ck.t_course t2 on  t1.course_id = t2.courseid ")
                .append(" where t1.cust_type=1 and t1.course_num=1 ").append(" and t1.course_id = '").append(courseid).append("'")
                .append(" and t1.usedate between '").append(begindate).append("'").append(" and '").append(enddate).append("'")
                .append(" and t1.stuemp_no='").append(stuempno).append("'")
                .append(" order by t1.usedate desc");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 教师日报实到、迟到、早退、

    public List getDailyTeacherOther(String courseid, String begindate, String enddate, String stuempno, String islate, String isleave) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.id,t1.course_id,t2.coursename,t1.stuemp_no as stuempno ,t1.cust_name as custname, t1.usedate ,t1.checktime  ")
                .append(" from ykt_ck.t_tea_stu_dailyrpt  t1")
                .append(" left join  ykt_ck.t_course t2 on  t1.course_id = t2.courseid ")
                .append(" where t1.cust_type=1 and t1.check_num=1  ");
        if ("1".equals(islate)) {
            query.append(" and t1.come_late_num=1 ");
        } else if ("1".equals(isleave)) {
            query.append(" and t1.leave_early_num=1 ");
        }
        query.append(" and t1.course_id = '").append(courseid).append("'")
                .append(" and t1.usedate between '").append(begindate).append("'").append(" and '").append(enddate).append("'")
                .append(" and t1.stuemp_no='").append(stuempno).append("'")
                .append(" order by t1.usedate desc");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 班级应到人员

    public List getClassShoudStudent(String courseid, String classid, String begindate, String enddate) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.course_id courseid,t2.coursename,t1.class_id ,t3.short_name classname , ")
                .append(" t1.stuemp_no stuempno,t1.cust_name custname,count(cust_name) totalnum , t1.usedate")
                .append(" from ykt_ck.t_tea_stu_dailyrpt  t1 ")
                .append(" inner join  ykt_ck.t_course t2 on  t1.course_id = t2.courseid ")
                .append(" inner join  ykt_ck.department t3 on  t3.dept_id = t1.class_id ")
                .append(" where t1.cust_type=0 and t1.course_num=1 ")
                .append(" and t1.course_id = '").append(courseid).append("'")
                .append(" and  t1.class_id = '").append(classid).append("'")
                .append(" and t1.usedate between '").append(begindate).append("'").append(" and '").append(enddate).append("'")
                .append(" group by t1.course_id,t2.coursename,t1.class_id,t3.short_name, t1.stuemp_no ,t1.cust_name ,t1.usedate ")
                .append(" order by t1.usedate desc,t1.stuemp_no");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    // 班级实到、迟到、早退、

    public List getClassStudentOther(String courseid, String classid, String begindate, String enddate, String islate, String isleave) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.course_id,t2.coursename,t1.class_id ,t3.short_name as classname, ")
                .append(" t1.stuemp_no as stuempno ,t1.cust_name as custname, t1.usedate ,t1.checktime ")
                .append(" from ykt_ck.t_tea_stu_dailyrpt  t1 ")
                .append(" left join  ykt_ck.t_course t2 on  t1.course_id = t2.courseid ")
                .append(" left join  ykt_ck.department t3 on  t3.dept_id = t1.class_id ")
                .append(" where t1.cust_type=0 and t1.check_num=1 ");
        if ("1".equals(islate)) {
            query.append(" and t1.come_late_num=1 ");
        } else if ("1".equals(isleave)) {
            query.append(" and t1.leave_early_num=1 ");
        }
        query.append(" and t1.course_id = '").append(courseid).append("'")
                .append(" and  t1.class_id = '").append(classid).append("'")
                .append(" and t1.usedate between '").append(begindate).append(
                "'").append(" and '").append(enddate).append("'")
                .append(" order by t1.usedate desc,t1.stuemp_no");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    public List getClassStudentNocome(String courseid, String classid, String begindate, String enddate) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.course_id,t2.coursename,t1.class_id ,t3.short_name as classname, ")
                .append(" t1.stuemp_no as stuempno ,t1.cust_name as custname, t1.usedate ,t1.checktime ")
                .append(" from ykt_ck.t_tea_stu_dailyrpt  t1 ")
                .append(" left join  ykt_ck.t_course t2 on  t1.course_id = t2.courseid ")
                .append(" left join  ykt_ck.department t3 on  t3.dept_id = t1.class_id ")
                .append(" where t1.cust_type=0 and t1.check_num=0 and t1.course_num=1");
        query.append(" and t1.course_id = '").append(courseid).append("'")
                .append(" and  t1.class_id = '").append(classid).append("'")
                .append(" and t1.usedate between '").append(begindate).append("'").append(" and '").append(enddate).append("'").append(" order by   t1.usedate desc,t1.stuemp_no");
        List list = jdbcTemplate.queryForList(query.toString());
        return list;
    }

    public List findDeviceUnplanned() throws Exception {
        String sql = "select d.deviceid as deviceid,d.devicename as devicename from ykt_ck.t_device_unplanned t,ykt_cur.t_device d where d.deviceid=t.deviceid";
        return jdbcTemplate.queryForList(sql);
    }

    public void findCheckDetail(DynaActionForm dform, DBPageLimit page) {
        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString("select d.devicename as devicename,c.stuempno as stuempno,c.custname as custname,cr.id.punchdate as punchdate,cr.punchtime as punchtime from TCheckrecord cr,TDevice d,TCustomer c where d.deviceid=cr.id.deviceid and cr.custid=c.custid");
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNo() - 1) * page.getPageSize());
        queryTranslate.setPageSize(page.getPageSize());

        String deviceid = dform.get("deviceid").toString();
        if (StringUtils.isNotBlank(deviceid)) {
            queryTranslate.addEqualCondition("cr.id.deviceid", deviceid);
        }
        String beginDate = dform.get("beginDate").toString();
        if (StringUtils.isBlank(beginDate)) {
            beginDate = DateUtil.getFirstDayOfWeek("yyyyMMdd");
            dform.set("beginDate", beginDate);
        }
        queryTranslate.addCondition("cr.id.punchdate", Constants.OPRATER_GREATER_AND_EQUAL, beginDate);

        String endDate = dform.get("endDate").toString();
        if (StringUtils.isBlank(endDate)) {
            endDate = DateUtil.getNow("yyyyMMdd");
            dform.set("endDate", endDate);
        }
        queryTranslate.addCondition("cr.id.punchdate", Constants.OPRATER_LESS_AND_EQUAL, endDate);

        queryTranslate.setOrderby(" order by cr.id.punchdate desc,c.stuempno");

        page.setMap(true);
        checkrecordDAO.findCheckDetailByPage(page, queryTranslate);
    }

    public List findDeviceCheckList(DynaActionForm dform) throws Exception {
        String beginDate = dform.get("beginDate").toString();
        if (StringUtils.isBlank(beginDate)) {
            beginDate = DateUtilExtend.getYesterday();
            dform.set("beginDate", beginDate);
        }
        String endDate = dform.get("endDate").toString();
        if (StringUtils.isBlank(endDate)) {
            endDate = DateUtilExtend.getYesterday();
            dform.set("endDate", endDate);
        }
        String deviceid = dform.get("deviceid").toString();

        StringBuffer sql = new StringBuffer("select du.deviceid as deviceid, d.devicename as devicename, count(cr.DEVICEID) as checknum from ykt_cur.t_device d, ykt_ck.t_device_unplanned du left outer join (select cr1.* from ykt_cur.t_checkrecord cr1,ykt_cur.t_customer cus where cus.custid=cr1.CUSTID) cr on du.deviceid = cr.DEVICEID");
        sql.append(" and cr.PUNCHDATE >='").append(beginDate).append("'");
        sql.append(" and cr.PUNCHDATE <='").append(endDate).append("'");
        sql.append(" where d.deviceid = du.deviceid ");
        if (StringUtils.isNotBlank(deviceid)) {
            sql.append(" and du.deviceid=").append(deviceid);
        }
        sql.append(" group by du.deviceid, d.devicename order by d.devicename");
        List list = jdbcTemplate.queryForList(sql.toString());
        return list;
    }

    public List getStuCheckRpt(DynaActionForm dform) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select  t3.class_id classno ,t3.course_id courseid ,t6.short_name  classname,t4.coursename, t5.stuempno stuempno,  t5.custname, t3.coursenum, ");
        query.append(" t3.coursenum, t3.checknum, t3.comelatenum,  t3.leaveearlynum ,t.areaname ");
        query.append(" from (select t1.class_id , t1.course_id,t1.stuemp_no, t1.cust_name,  ");
        query.append(" sum(t1.course_num) coursenum,sum(t1.check_num) checknum,");
        query.append(" sum(t1.come_late_num) comelatenum, sum(t1.leave_early_num) leaveearlynum ");
        query.append(" from ykt_ck.t_tea_stu_dailyrpt t1, ykt_ck.t_term t2 ,ykt_ck.t_oper_limit ol,ykt_ck.t_courseplan cp ");
        query.append("  where t2.enable = '1'  and t1.term_id = t2.termid  and t1.cust_type = 0 and t1.id=cp.id||'-'||t1.stuemp_no and cp.usedate=t1.usedate and ((ol.resource_id=t1.class_id and ol.type is null) or (ol.resource_id=cp.custid and ol.type='4'))");
        query.append(" and ol.oper_id='").append(dform.get("custid")).append("'");

        if (StringUtils.isNotBlank((String) dform.get("beginDate"))) {
            query.append(" and  t1.usedate >='").append(dform.get("beginDate").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("endDate"))) {
            query.append(" and  t1.usedate <='").append(dform.get("endDate").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("courseId"))) {
            query.append(" and t1.course_id ='").append(dform.get("courseId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("classno"))) {
            query.append(" and t1.class_id = '").append(dform.get("classno").toString()).append("'");
        }

        query.append("  group by t1.class_id, t1.course_id, t1.stuemp_no, t1.cust_name) t3,")
                .append("	ykt_ck.t_course t4,ykt_cur.t_customer t5,ykt_ck.department t6,ykt_ck.t_faculty f,ykt_cur.t_area t ")
                .append(" where t3.course_id = t4.courseid and t.areacode = t6.area_code and t3.stuemp_no = t5.stuempno and t6.dept_id = t3.class_id and f.value=t6.faculty");
        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and   t6.area_code='").append(dform.get("schoolarea").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("stuempNo"))) {
            query.append(" and t5.stuempno like '%").append(dform.get("stuempNo")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("custName"))) {
            query.append(" and t5.custname like '%").append(dform.get("custName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("departmentName"))) {
            query.append(" and t6.short_name like '%").append(dform.get("departmentName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("pid"))) {
            query.append(" and f.pid= '").append(dform.get("pid")).append("'");
        }
        query.append("  order by t.areaname , t6.short_name ,t4.coursename ");
        List list = jdbcTemplate.queryForList(query.toString());
        return calculateRate(list);
    }

    // 当日流水统计

    public List getTodayStuCheckList(DynaActionForm dform) throws Exception {
        List resultList = new ArrayList();
        Integer beforeclassallowed = 30;
        Integer afterclassallowed = 10;
        List timeList = courseplanDAO.find("from TCheckstrategy");
        for (int k = 0; k < timeList.size(); k++) {
            TCheckstrategy tcheckstrategy = (TCheckstrategy) timeList.get(k);
            if ("beforeclassallowed".equals(tcheckstrategy.getStrategytype())) {
                beforeclassallowed = tcheckstrategy.getStrategyvalue();
            }
            if ("afterclassallowed".equals(tcheckstrategy.getStrategytype())) {
                afterclassallowed = tcheckstrategy.getStrategyvalue();
            }
        }
        List list;
        StringBuffer query = new StringBuffer();
        query.append(" select t1.id, t3.stuempno, t7.short_name deptname,t7.dept_id, t3.custname, t5.areaname, t6.coursename,");
        query.append(" t2.classno  ,count(t8.custid) sharr ,t4.roomid ,t1.begintime ,t1.endtime ");
        query.append(" from YKT_CK.T_COURSEPLAN  t1 ");
        query.append(" inner join YKT_CK.T_COURSEPLANCLASS  t2  on t1.id = t2.planid ");
        query.append(" inner join ykt_cur.t_customer t3 on t3.custid = t1.custid ");
        query.append(" inner join ykt_ck.t_room  t4  on  t4.roomid = t1.roomid  ");
        query.append(" inner join ykt_ck.t_course t6 on t1.courseid = t6.courseid ");
        query.append(" inner join ykt_ck.department t7  on t7.dept_id = t2.classno ");
        query.append(" inner join ykt_cur.t_area t5  on  t5.areacode = t7.area_code ");
        query.append(" inner join ykt_ck.t_faculty f on f.value=t7.faculty");
        query.append(" inner join ykt_cur.t_customer t8 on t8.classname = t2.classno ");
        query.append(" inner join ykt_ck.t_customer_state t10 on t10.stuempno = t8.stuempno ");
        query.append(" inner join ykt_ck.t_oper_limit t9 on ((t9.resource_id=t2.classno and t9.type is null) or (t9.resource_id=t1.custid and t9.type='4'))");
        query.append(" where t10.stu_state='1' and t1.ischeck=1 ").append(" and t1.usedate='");
        query.append(DateUtil.getNow("yyyyMMdd")).append("' and t9.oper_id='").append(dform.get("custid")).append("'");
        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append("  and t7.area_code='").append((String) dform.get("schoolarea")).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("stuempNo"))) {
            query.append(" and t3.stuempno like '%").append(dform.get("stuempNo")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("custName"))) {
            query.append(" and t3.custname like '%").append(dform.get("custName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("departmentName"))) {
            query.append(" and t7.short_name like '%").append(dform.get("departmentName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("classno"))) {
            query.append("  and t2.classno ='").append((String) dform.get("classno")).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("pid"))) {
            query.append("  and f.pid ='").append((String) dform.get("pid")).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("courseId"))) {
            query.append("  and t6.courseid='").append((String) dform.get("courseId")).append("'");
        }
        query.append(" group by t1.id,t3.stuempno, t7.short_name, t3.custname,").append("  t5.areaname, t6.coursename, t2.classno,t7.dept_id,t4.roomid ,t1.begintime ,t1.endtime ");
        query.append(" order by t5.areaname,t7.short_name,t6.coursename");
        list = jdbcTemplate.queryForList(query.toString());
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Map m = (Map) list.get(i);

                TodayStuCheckSearch check = new TodayStuCheckSearch();
                check.setId((String) m.get("id"));
                check.setAreaname((String) m.get("areaname"));
                check.setStuempno((String) m.get("stuempno"));
                check.setCustname((String) m.get("custname"));
                check.setCoursename((String) m.get("coursename"));
                check.setDeptcode((String) m.get("classno"));
                check.setDeptname((String) m.get("deptname"));
                check.setBegintime((String) m.get("begintime"));
                check.setEndtime((String) m.get("endtime"));
                check.setSharr(Integer.parseInt(m.get("sharr").toString()));
                check.setRealarr(0);
                check.setReallate(0);
                StringBuffer str = new StringBuffer();
                str.append(" select count(distinct t1.custid) as realcount from t_checkrecord t1 ");
                str.append(" where  t1.custid in (select custid from ykt_cur.t_customer where classname= '");
                str.append((String) m.get("classno")).append("')");
                str.append(" and t1.deviceid in (select  deviceid from ykt_ck.t_roomdevice where roomid='");
                str.append((String) m.get("roomid")).append("')");
                str.append(" and t1.punchdate ='").append(DateUtil.getNow("yyyyMMdd")).append("'");
                str.append(" and t1.punchtime between to_char(to_date('").append(DateUtil.getNow("yyyyMMdd")).append("'||' '||'").append((String) m.get("begintime")).append("' , 'yyyymmdd hh24:mi:ss') - NUMTODSINTERVAL( ").append(beforeclassallowed).append(", 'minute'),'hh24miss')");
                str.append(" and to_char(to_date('").append(DateUtil.getNow("yyyyMMdd")).append("'||' '||'").append((String) m.get("endtime")).append("', 'yyyymmdd hh24:mi:ss') + NUMTODSINTERVAL( ").append(afterclassallowed).append(",'minute'),'hh24miss')");
                List realList = jdbcTemplate.queryForList(str.toString());
                if (realList != null && realList.size() > 0) {
                    String realcount = ((Map) realList.get(0)).get("realcount").toString();
                    check.setRealarr(Integer.parseInt(realcount));
                    check.setReallate(check.getSharr() - Integer.parseInt(realcount));
                }
                resultList.add(check);
            }
        }
        return resultList;
    }

    public List getRoomState(DynaActionForm dform) throws Exception {
        String useDate = DateUtilExtend.getNowDate2();
        StringBuffer query = new StringBuffer("select t1.*, t2.transtime from");
        query.append(" (select a.areaname,r.build,r.roomname,cp.usedate,cp.begintime,cp.endtime,d.deviceid,a.areacode");
        query.append(" from ykt_ck.t_courseplan cp,ykt_ck.t_room r,ykt_cur.t_area a,ykt_ck.t_roomdevice rd,ykt_cur.t_device d");
        query.append(" where cp.usedate = '").append(useDate).append("' and cp.roomid = r.roomid and r.schoolarea = a.areacode and r.roomid = rd.roomid and rd.deviceid = d.deviceid and d.devtypecode = '0121') t1");
        query.append(" left join (select dtl.transdate, dtl.transtime, dtl.deviceid from ykt_cur.t_doordtl dtl where transmark = '1026' and transdate = '").append(useDate).append("') t2");
        query.append(" on t1.deviceid = t2.deviceid and to_date(t2.transdate || t2.transtime, 'yyyymmddhh24miss') between to_date(t1.usedate || t1.begintime, 'yyyymmddhh24:mi') and to_date(t1.usedate || t1.endtime, 'yyyymmddhh24:mi') + 1 / 144");

        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" where t1.areacode='").append(dform.get("schoolarea").toString()).append("'");
        }

        List list = jdbcTemplate.queryForList(query.toString());
        SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");

        long now = sdf.parse(sdf.format(new Date())).getTime();
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Map m = (Map) list.get(i);
                long beginTime = sdf.parse(DateUtilExtend.formattime(m.get("begintime").toString())).getTime();
                long endTime = sdf.parse(DateUtilExtend.formattime(m.get("endtime").toString())).getTime();
                Object transtime = m.get("transtime");
                //有效断电流水的时间范围为从上课开始到下课之后的十分钟
                if (now < beginTime) {
                    //空闲
                    m.put("state", "1");
                } else if (now < endTime + 10 * 60 * 1000) {
                    //从开始上课到下课后的十分钟内，如果有断电流水，那么状态为刷卡断电，否则为在用
                    if (transtime != null && StringUtils.isNotBlank(transtime.toString())) {
                        m.put("state", "3");
                    } else {
                        m.put("state", "2");
                    }
                } else if (now < endTime + 20 * 60 * 1000) {
                    //从下课后十分钟到下课后二十分钟内，如果有断电流水，那么状态为空闲，否则为超时未断电
                    if (transtime != null && StringUtils.isNotBlank(transtime.toString())) {
                        m.put("state", "1");
                    } else {
                        m.put("state", "4");
                    }
                } else {
                    m.put("state", "1");
                }
                m.put("statename", getStateName(m.get("state").toString()));
            }
        }
        ContentComparator con = new ContentComparator();
        Collections.sort(list, con);
        return list;
    }

    // 取得待处理的房间

    public List getTRoomTRans(DynaActionForm dform) throws Exception {
        String useDate = DateUtilExtend.getNowDate2();
        StringBuffer query = new StringBuffer("");
        query.append("select re.serialno,a.areaname,r.build,r.roomname,cp.usedate,cp.begintime,cp.endtime,re.state");
        query.append(" from ykt_ck.t_courseplan cp,ykt_ck.t_room r,ykt_cur.t_area a,ykt_ck.t_roomdevice rd,ykt_cur.t_device d,ykt_ck.t_room_elec re");
        query.append(" where cp.usedate = '").append(useDate).append("' and cp.roomid = r.roomid and r.schoolarea = a.areacode and r.roomid = rd.roomid and rd.deviceid = d.deviceid and d.devtypecode = '0121' and re.serialno = cp.id and re.isdeal=0");

        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and a.areacode='").append(dform.get("schoolarea").toString()).append("'");
        }

        List list = jdbcTemplate.queryForList(query.toString());

        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Map m = (Map) list.get(i);
                if ("3".equals(m.get("state").toString())) {
                    m.put("statename", getStateName("3"));
                } else {
                    m.put("statename", getStateName("4"));
                }
            }
        }
        ContentComparator con = new ContentComparator();
        Collections.sort(list, con);
        return list;
    }

    private class ContentComparator implements Comparator {
        public int compare(Object o1, Object o2) {
            int i = 0;
            int stat1 = Integer.parseInt(((Map) o1).get("state").toString());
            int stat2 = Integer.parseInt(((Map) o2).get("state").toString());
            if (stat1 < stat2) {
                i = 1;
            }
            if (stat1 > stat2) {
                i = -1;
            }
            return i;
        }
    }

    private String getStateName(String state) {

        if ("1".equals(state)) {
            return "空闲";
        }
        if ("2".equals(state)) {
            return "在用";
        }
        if ("3".equals(state)) {
            return "刷卡断电";
        }
        if ("4".equals(state)) {
            return "超时未断电";
        }
        return "";
    }

    public boolean roomTrans(String[] serialno, String personname, String personcode) throws Exception {
        if (serialno != null && serialno.length > 0) {
            for (int i = 0; i < serialno.length; i++) {
                if (!"".equals(serialno[i])) {
                    String query = "from TRoomElec t where t.serialno='" + serialno[i] + "'";
                    List list = roomElecDAO.findRoomElec(query);
                    TRoomElec roomElec = (TRoomElec) list.get(0);
                    roomElec.setUpdatedate(DateUtilExtend.getNowDate2());
                    roomElec.setUpdatetime(DateUtilExtend.getNowTime());
                    roomElec.setPersonname(personname);
                    roomElec.setPersoncode(personcode);
                    roomElec.setIsdeal(Integer.valueOf(1));
                    roomElecDAO.updateRoomElec(roomElec);
                }
            }
        }
        return true;
    }

    private String stopElec(String deviceId, String beginTime, String endTime) {
        StringBuffer query = new StringBuffer();
        query
                .append(
                        " select serialno from ( select transdate||'-'||devseqno||'-'||deviceid as serialno from t_doordtl ")
                .append(" where transmark='1026'").append(" and deviceid =")
                .append(deviceId).append(" and transtime between '").append(
                beginTime).append("' and '").append(endTime)
                .append("'")
                        // .append(" and transdate ='20100625'")
                .append(" and transdate ='").append(
                DateUtilExtend.getNowDate2()).append("'").append(
                " order by transtime ) where  rownum=1 ");
        List list = jdbcTemplate.queryForList(query.toString());
        if (list != null && list.size() > 0) {
            return ((Map) list.get(0)).get("serialno").toString();
        }
        return "";
    }

    private boolean isTrans(String serialno) {
        StringBuffer query = new StringBuffer();
        query.append(" select t from TRoomElec t where t.serialno='").append(
                serialno).append("'");
        List list = courseplanDAO.find(query.toString());
        if (list != null && list.size() > 0) {
            return true;
        }
        return false;
    }

    public List getClassCheckRpt(DynaActionForm dform) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append("select  new Map(t.deptclass.name as classname ,t.deptclass.id as classno,t.course.courseid as courseid ,t.course.coursename as coursename, sum(t.classPeopleNum) as coursenum , ");
        query.append(" sum(t.checkNum) as checknum ,").append(" sum(t.comeLateNum) as comelatenum , ").append(" sum(t.leaveEarlyNum) as leaveearlynum ");
        query.append(" ,count(t.id) as ishave ").append(" ) from  TClassCheckDailyrpt t,Toperlimit ol,TFaculty f where f.value=t.deptclass.faculty and t.deptclass.id=ol.id.resourceId and ol.type is null");
        query.append(" and ol.id.operId='").append(dform.get("custid")).append("'");

        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and   t.deptclass.areaCode='").append(dform.get("schoolarea").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("classno"))) {
            query.append(" and   t.deptclass.id='").append(dform.get("classno").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("courseId"))) {
            query.append(" and  t.course.courseid='").append(dform.get("courseId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("beginDate"))) {
            query.append(" and  t.checkDate >='").append(dform.get("beginDate").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("endDate"))) {
            query.append(" and  t.checkDate <='").append(dform.get("endDate").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("departmentName"))) {
            query.append(" and t.deptclass.name like '%").append(dform.get("departmentName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("pid"))) {
            query.append(" and f.pid='").append(dform.get("pid")).append("'");
        }
        query.append(" group by t.deptclass.name ,t.deptclass.id, t.course.courseid , t.course.coursename ");
        query.append(" order by t.deptclass.name desc,t.course.coursename");

        List list = courseplanDAO.find(query.toString());

        return calculateRate(list);
    }

    private boolean ishaveOtherStudent(String courseid, String classid,
                                       String begindate, String enddate) throws Exception {
        StringBuffer query = new StringBuffer();
        query
                .append(
                        " select t1.id  from ykt_ck.t_courseplan t1 ,ykt_ck.t_courseplanclass t2 ")
                .append(" where t1.id = t2.planid  ")
                .append(" and  courseid='").append(courseid).append("'")
                .append(" and usedate between '").append(begindate).append(
                "' and '").append(enddate).append("'").append(
                " and t2.classno= '").append(classid).append("'");
        List list = jdbcTemplate.queryForList(query.toString());
        String planid = "";
        if (list != null && list.size() > 0) {
            Map m = (Map) list.get(0);
            planid = planid + "'" + m.get("id") + "',";
        }
        planid = planid.substring(0, planid.length() - 1);

        StringBuffer str = new StringBuffer();
        str
                .append(
                        " select t1.id ,t1.stuempno,t1.custname   ")
                .append(
                        " from  ykt_ck.t_unplanstudent t1  ")
                .append(
                        " where 1=1 ");

        str.append(" and subStr(t1.id,1,32)in ( ").append(planid).append(")");
        List otherlist = jdbcTemplate.queryForList(str.toString());
        if (otherlist != null && otherlist.size() > 0) {
            return true;
        }
        return false;
    }

    // 教师考勤报表

    public List getTeaCheckRpt(DynaActionForm dform) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select t1.course_id courseid, stuemp_no as stuempno,cust_name as custname ,t2.coursename,sum(course_num) as coursenum , ")
                .append(" sum(check_num) as checknum ,sum(come_late_num) as comelatenum ,sum(leave_early_num) as leaveearlynum")
                .append(" from ykt_ck.t_tea_stu_dailyrpt t1 ")
                .append(" left join ykt_ck.t_course  t2 on t1.course_id = t2.courseid ")
                .append(" where cust_type=1 ");
        /*if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and   t1.area_id ='").append(dform.get("schoolarea").toString()).append("'");
        }*/
        if (StringUtils.isNotBlank((String) dform.get("courseId"))) {
            query.append(" and  t1.course_id='").append(dform.get("courseId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("beginDate"))) {
            query.append(" and  t1.usedate >='").append(dform.get("beginDate").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("endDate"))) {
            query.append(" and  t1.usedate <='").append(dform.get("endDate").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("stuempNo"))) {
            query.append(" and  t1.stuemp_No like '%").append(dform.get("stuempNo").toString()).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("custName"))) {
            query.append(" and  t1.cust_Name like '%").append(dform.get("custName").toString()).append("%'");
        }
        query.append(" group by t1.course_id,stuemp_no,cust_name,t2.coursename order by stuemp_no,t2.coursename");
        List list = jdbcTemplate.queryForList(query.toString());
        return calculateRate(list);
    }

    /**
     * 学生按学期进行考勤统计
     */
    public void getStudentTermCheckRpt(DynaActionForm dform, DBPageLimit page) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select  t.deptclass.name as classname , t.course.coursename as coursename ,t.course.courseid as courseid,t.deptclass.id as classid,")
                .append(" t.stuempNo as stuempno, t.custName as custname , sum(t.courseNum) as coursenum ,  sum(t.checkNum) as checknum , ")
                .append(" sum(t.comeLateNum) as comelatenum ,").append(" sum(t.leaveEarlyNum) as leaveearlynum").append("  from TStudentTermRpt  t,Toperlimit ol,TFaculty f where  f.value=t.deptclass.faculty and ol.id.resourceId=t.deptclass.id and ol.type is null");
        query.append(" and ol.id.operId='").append(dform.get("custid")).append("' ");
        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and   t.deptclass.areaCode='").append(dform.get("schoolarea").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("classno"))) {
            query.append(" and   t.deptclass.id='").append(dform.get("classno").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("courseId"))) {
            query.append(" and  t.course.courseid='").append(dform.get("courseId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("termId"))) {
            query.append(" and  t.term.termId='").append(dform.get("termId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("stuempNo"))) {
            query.append(" and t.stuempNo like '%").append(dform.get("stuempNo")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("custName"))) {
            query.append(" and t.custName like '%").append(dform.get("custName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("departmentName"))) {
            query.append(" and t.deptclass.name like '%").append(dform.get("departmentName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("pid"))) {
            query.append(" and f.pid='").append(dform.get("pid")).append("'");
        }

        query.append(" group by t.deptclass.areaCode,t.deptclass.name ,t.deptclass.id, t.course.coursename ,t.course.courseid, t.term.termId , t.stuempNo , t.custName");
        query.append(" order by t.deptclass.areaCode,t.deptclass.name desc,t.course.coursename,t.stuempNo");

        QueryTranslate queryTranslate = new QueryTranslate();
        queryTranslate.setQueryString(query.toString());
        queryTranslate.setOffset(true);
        queryTranslate.setPageStartNo((page.getPageNo() - 1) * page.getPageSize());
        queryTranslate.setPageSize(page.getPageSize());
        page.setMap(true);
        checkrecordDAO.findCheckDetailByPage(page, queryTranslate);

        calculateRate(page.getResult());
    }

    /**
     * 教师按学期进行考勤统计
     */
    public List getTeacherTermCheckRpt(DynaActionForm dform) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select  new Map(t.course.coursename as coursename ,t.course.courseid as courseid, ")
                .append(" t.stuempNo as stuempno, t.custName as custname , sum(t.courseNum) as coursenum ,  sum(t.checkNum) as checknum , ")
                .append(" sum(t.comeLateNum) as comelatenum ,").append(" sum(leaveEarlyNum) as leaveearlynum").append(" ) from TTeacherTermRpt  t where 1=1 ");
        /*if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and   t.area.areaCode='").append(dform.get("schoolarea").toString()).append("'");
        }*/
        if (StringUtils.isNotBlank((String) dform.get("courseId"))) {
            query.append(" and  t.course.courseid='").append(dform.get("courseId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("termId"))) {
            query.append(" and  t.term.termId='").append(dform.get("termId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("stuempNo"))) {
            query.append(" and t.stuempNo like '%").append(dform.get("stuempNo")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("custName"))) {
            query.append(" and t.custName like '%").append(dform.get("custName")).append("%'");
        }

        query.append(" group by t.course.coursename ,t.course.courseid, t.term.termId , t.stuempNo , t.custName");
        query.append(" order by t.stuempNo,t.course.coursename");

        return calculateRate(courseplanDAO.find(query.toString()));
    }

    /**
     * 班级按学期进行考勤统计
     */
    public List getClassTermCheckRpt(DynaActionForm dform) throws Exception {
        StringBuffer query = new StringBuffer("");
        query.append(" select  new Map(t.deptclass.name as classname , t.course.coursename as coursename , t.course.courseid as courseid,t.deptclass.id as classid,")
                .append(" sum(t.classPeopleNum) as coursenum ,  sum(t.checkNum) as checknum , ")
                .append(" sum(t.comeLateNum) as comelatenum ,").append(" sum(t.leaveEarlyNum) as leaveearlynum").append(" ) from TClassCheckTermRpt  t,Toperlimit ol,TFaculty f where f.value=t.deptclass.faculty and ol.id.resourceId=t.deptclass.id and ol.type is null");
        query.append(" and ol.id.operId='").append(dform.get("custid")).append("' ");
        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and   t.deptclass.areaCode='").append(dform.get("schoolarea").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("classno"))) {
            query.append(" and   t.deptclass.id='").append(dform.get("classno").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("courseId"))) {
            query.append(" and  t.course.courseid='").append(dform.get("courseId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("termId"))) {
            query.append(" and  t.term.termId='").append(dform.get("termId").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("departmentName"))) {
            query.append(" and t.deptclass.name like '%").append(dform.get("departmentName")).append("%'");
        }
        if (StringUtils.isNotBlank((String) dform.get("pid"))) {
            query.append(" and f.pid='").append(dform.get("pid")).append("'");
        }

        query.append(" group by t.deptclass.areaCode,t.deptclass.name ,t.deptclass.id, t.course.coursename ,t.course.courseid, t.term.termId");
        query.append(" order by t.deptclass.areaCode,t.deptclass.name desc,t.course.coursename");

        return calculateRate(courseplanDAO.find(query.toString()));
    }

    /**
     * 计算出勤率，迟到率，早退率 该方法的使用有局限性，请确定key值匹配在使用
     *
     * @param list
     * @return
     */
    private List calculateRate(List list) {
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Map map = (Map) list.get(i);
                // 应到人次
                Integer coursenum = Integer.parseInt(map.get("coursenum").toString());
                // 实到人次
                Integer checknum = Integer.parseInt(map.get("checknum").toString());
                // 迟到人次
                Integer comelatenum = Integer.parseInt(map.get("comelatenum").toString());
                // 早退人次
                Integer leaveearlynum = Integer.parseInt(map.get("leaveearlynum").toString());

                if (coursenum == null || coursenum == 0) {
                    map.put("checkrate", "0");
                    map.put("comelaterate", "0");
                    map.put("leaveearlyrate", "0");
                    map.put("absenceNum", 0);
                } else {
                    // 出勤率
                    map.put("checkrate", StringUtil.getPercentage(checknum, coursenum, 2));
                    // 迟到率
                    map.put("comelaterate", StringUtil.getPercentage(comelatenum, coursenum, 2));
                    // 早退率
                    map.put("leaveearlyrate", StringUtil.getPercentage(leaveearlynum, coursenum, 2));
                    map.put("absenceNum", coursenum - checknum);
                }
            }
        }
        return list;
    }

    // 教室处理日志查询

    public List getTransPerson(DynaActionForm dform) throws Exception {
        StringBuffer query = new StringBuffer();
        query.append(" select  new Map(t.updatedate as updatedate ,t.updatetime as updatetime,t.personcode as personcode,")
                .append(" t.personname as personname,t.room.build  as build ,t.room.roomName as roomname ,t.room.schoolArea.areaName  as areaname) ")
                .append(" from  TRoomElec t  where t.isdeal=1 and t.state='4'  ");
        if (StringUtils.isNotBlank((String) dform.get("schoolarea"))) {
            query.append(" and t.room.schoolArea.areaCode='").append(dform.get("schoolarea").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("beginDate"))) {
            query.append(" and  t.updatedate>='").append(dform.get("beginDate").toString()).append("'");
        }
        if (StringUtils.isNotBlank((String) dform.get("endDate"))) {
            query.append(" and  t.updatedate <='").append(dform.get("endDate").toString()).append("'");
        }
        query.append(" order by t.updatedate desc,t.updatetime desc");
        return courseplanDAO.find(query.toString());
    }

    public List getTodayStuCheckDetailList(String planId) throws Exception {
        // TODO Auto-generated method stub
        return null;
    }

    public List getUnplanStudent(String courseid, String classid, String begindate, String enddate, String isactivate, String islate, String isleave, String stuempNo) throws Exception {
        StringBuffer query = new StringBuffer();
        query.append(" select t1.id  from ykt_ck.t_courseplan t1 ,ykt_ck.t_courseplanclass t2 ")
                .append(" where t1.id = t2.planid  ")
                .append(" and  courseid='").append(courseid).append("'")
                .append(" and usedate between '").append(begindate).append("' and '").append(enddate).append("'").append(" and t2.classno= '").append(classid).append("'");
        List list = jdbcTemplate.queryForList(query.toString());
        String planid = "";
        if (list != null && list.size() > 0) {
            for (int i = 0; i < list.size(); i++) {
                Map m = (Map) list.get(i);
                planid = planid + "'" + m.get("id") + "',";
            }
        }
        planid = planid.substring(0, planid.length() - 1);

        StringBuffer str = new StringBuffer();
        str.append(" select t1.id ,t1.stuempno,t1.custname,t2.short_name classname,t3.coursename,t1.checkdate,t1.checktime ,decode(t1.isactivate,0,'无效',1,'有效') isactivate  ")
                .append(" from  ykt_ck.t_unplanstudent t1 ,ykt_ck.department t2 ,ykt_ck.t_course t3 ")
                .append(" where t1.classno = t2.dept_id  and t1.courseid = t3.courseid ")
                .append(" and t1.isactivate = ").append(isactivate);
        if ("1".equals(islate)) {
            str.append(" and t1.come_late_num=1");
        }
        if ("1".equals(isleave)) {
            str.append(" and t1.leave_early_num=1");
        }
        if (StringUtils.isNotBlank(stuempNo)) {
            str.append(" and t1.stuempno='").append(stuempNo).append("'");
        }

        str.append(" and subStr(t1.id,1,32)in ( ").append(planid).append(") order by t1.checkdate desc,t2.short_name,t1.stuempno");
        List otherlist = jdbcTemplate.queryForList(str.toString());
        return otherlist;
    }

    public void updateUnplanStudent(String student, String type) throws Exception {
        String[] stus = student.split(",");
        for (int i = 0; i < stus.length; i++) {
            StringBuffer query = new StringBuffer();
            query.append(" from TUnplanstudent t where t.id='").append(stus[i]).append("'");
            List list = courseplanDAO.find(query.toString());
            TUnplanstudent unplan = (TUnplanstudent) list.get(0);
            if ("confirm".equals(type)) {
                unplan.setIsactivate(new Integer(1));
            }
            if ("cancel".endsWith(type)) {
                unplan.setIsactivate(new Integer(0));
            }
            unplanstudentDAO.update(unplan);
        }
    }

    /**
     * 查找考勤明细
     *
     * @param termId        学期
     * @param classId       班级
     * @param courseId      课程
     * @param stuempNo      学号
     * @param custType      类型（教师：1，学生：0）
     * @param courseNum     应到课次
     * @param checkNum      实到课次
     * @param comeLateNum   迟到课次
     * @param leaveEarlyNum 早退课次
     * @return .
     */
    public List getCheckDetail(String termId, String classId, String courseId, String stuempNo, Integer custType, Integer courseNum, Integer checkNum, Integer comeLateNum, Integer leaveEarlyNum) throws Exception {
        StringBuffer query = new StringBuffer("select new Map(t.course.coursename as courseName,t.stuempNo as stuempNo,t.deptclass.name as deptName,t.custName as custName,t.useDate as useDate,t.checkTime as checkTime) from TTeaStuDailyRpt t where 1=1");
        if (StringUtils.isNotBlank(termId)) {
            query.append(" and   t.term.termId='").append(termId).append("'");
        }
        if (StringUtils.isNotBlank(classId)) {
            query.append(" and   t.deptclass.id='").append(classId).append("'");
        }
        if (StringUtils.isNotBlank(courseId)) {
            query.append(" and   t.course.courseid='").append(courseId).append("'");
        }
        if (StringUtils.isNotBlank(stuempNo)) {
            query.append(" and   t.stuempNo='").append(stuempNo).append("'");
        }
        if (custType != null) {
            query.append(" and   t.custType=").append(custType.intValue());
        }
        if (courseNum != null) {
            query.append(" and   t.courseNum=").append(courseNum.intValue());
        }
        if (checkNum != null) {
            query.append(" and   t.checkNum=").append(checkNum.intValue());
        }
        if (comeLateNum != null) {
            query.append(" and   t.comeLateNum=").append(comeLateNum.intValue());
        }
        if (leaveEarlyNum != null) {
            query.append(" and   t.leaveEarlyNum=").append(leaveEarlyNum.intValue());
        }
        query.append(" order by t.useDate desc,t.stuempNo,t.course.courseid");

        return checkrecordDAO.findCheckDetail(query.toString());
    }

    /**
     * 查找教师考勤明细
     *
     * @param termId        学期
     * @param courseId      课程
     * @param stuempNo      学号
     * @param courseNum     应到课次
     * @param checkNum      实到课次
     * @param comeLateNum   迟到课次
     * @param leaveEarlyNum 早退课次
     * @return .
     */
    public List getTeacherCheckDetail(String termId, String courseId, String stuempNo, Integer courseNum, Integer checkNum, Integer comeLateNum, Integer leaveEarlyNum) throws Exception {
        StringBuffer query = new StringBuffer("select new Map(t.course.coursename as courseName,t.stuempNo as stuempNo,t.custName as custName,t.useDate as useDate,t.checkTime as checkTime) from TTeaStuDailyRpt t where t.custType=1");
        if (StringUtils.isNotBlank(termId)) {
            query.append(" and   t.term.termId='").append(termId).append("'");
        }
        if (StringUtils.isNotBlank(courseId)) {
            query.append(" and   t.course.courseid='").append(courseId).append("'");
        }
        if (StringUtils.isNotBlank(stuempNo)) {
            query.append(" and   t.stuempNo='").append(stuempNo).append("'");
        }
        if (courseNum != null) {
            query.append(" and   t.courseNum=").append(courseNum.intValue());
        }
        if (checkNum != null) {
            query.append(" and   t.checkNum=").append(checkNum.intValue());
        }
        if (comeLateNum != null) {
            query.append(" and   t.comeLateNum=").append(comeLateNum.intValue());
        }
        if (leaveEarlyNum != null) {
            query.append(" and   t.leaveEarlyNum=").append(leaveEarlyNum.intValue());
        }
        query.append(" order by t.useDate desc");

        return checkrecordDAO.findCheckDetail(query.toString());
    }

    /**
     * 查找班级考勤明细
     *
     * @param termId        学期
     * @param classId       班级
     * @param courseId      课程
     * @param stuempNo      学号
     * @param courseNum     应到课次
     * @param checkNum      实到课次
     * @param comeLateNum   迟到课次
     * @param leaveEarlyNum 早退课次
     * @return .
     */
    public List getClassCheckDetail(String termId, String classId, String courseId, String stuempNo, Integer courseNum, Integer checkNum, Integer comeLateNum, Integer leaveEarlyNum, String beginDate, String endDate) throws Exception {
        StringBuffer query = new StringBuffer("select new Map(t.course.coursename as courseName,t.stuempNo as stuempNo,t.deptclass.name as deptName,t.custName as custName,t.useDate as useDate,t.checkTime as checkTime) from TTeaStuDailyRpt t where t.custType=0");
        if (StringUtils.isNotBlank(termId)) {
            query.append(" and   t.term.termId='").append(termId).append("'");
        }
        if (StringUtils.isNotBlank(classId)) {
            query.append(" and   t.deptclass.id='").append(classId).append("'");
        }
        if (StringUtils.isNotBlank(courseId)) {
            query.append(" and   t.course.courseid='").append(courseId).append("'");
        }
        if (StringUtils.isNotBlank(stuempNo)) {
            query.append(" and   t.stuempNo='").append(stuempNo).append("'");
        }
        if (courseNum != null) {
            query.append(" and   t.courseNum=").append(courseNum.intValue());
        }
        if (checkNum != null) {
            query.append(" and   t.checkNum=").append(checkNum.intValue());
        }
        if (comeLateNum != null) {
            query.append(" and   t.comeLateNum=").append(comeLateNum.intValue());
        }
        if (leaveEarlyNum != null) {
            query.append(" and   t.leaveEarlyNum=").append(leaveEarlyNum.intValue());
        }
        if (StringUtils.isNotBlank(beginDate)) {
            query.append(" and   t.useDate>='").append(beginDate).append("'");
        }
        if (StringUtils.isNotBlank(endDate)) {
            query.append(" and   t.useDate<='").append(endDate).append("'");
        }
        query.append(" order by t.useDate desc,t.stuempNo,t.course.courseid");

        return checkrecordDAO.findCheckDetail(query.toString());
    }
}
