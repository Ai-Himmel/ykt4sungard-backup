package org.king.check.service.impl;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.CourseplanDAO;
import org.king.check.dao.CourseplanTempDAO;
import org.king.check.dao.SyncLogDAO;
import org.king.check.domain.*;
import org.king.check.service.CourseService;
import org.king.check.service.CustomerService;
import org.king.check.service.DepartmentService;
import org.king.check.service.RoomService;
import org.king.check.service.SyncService;
import org.king.check.service.TimeService;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.StringUtil;
import org.springframework.jdbc.core.JdbcTemplate;

import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class SyncServiceImpl implements SyncService {
    private static final Log _log = LogFactory.getLog(SyncServiceImpl.class);

    private CourseplanTempDAO courseplanTempDAO;

    private SyncLogDAO syncLogDAO;

    private JdbcTemplate jdbcTemplate;

    private RoomService roomService;

    private CustomerService customerService;

    private DepartmentService departmentService;

    private TimeService timeService;

    private CourseService courseService;

    private CourseplanDAO courseplanDAO;

    public void setCourseplanTempDAO(CourseplanTempDAO courseplanTempDAO) {
        this.courseplanTempDAO = courseplanTempDAO;
    }

    public void setSyncLogDAO(SyncLogDAO syncLogDAO) {
        this.syncLogDAO = syncLogDAO;
    }

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    public void setRoomService(RoomService roomService) {
        this.roomService = roomService;
    }

    public void setCustomerService(CustomerService customerService) {
        this.customerService = customerService;
    }

    public void setDepartmentService(DepartmentService departmentService) {
        this.departmentService = departmentService;
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

    public List findCourseplanTemp(String status) throws Exception {
        return findCourseplanTemp(null,null,null,status);
    }

    public List findPendingCourseplanTemp() throws Exception {
        return findCourseplanTemp(null,null,null,"1");
    }

    private List findCourseplanTemp(String termName, String beginDate, String endDate, String status) throws Exception {
        StringBuffer sql = new StringBuffer("select term,faculty,area,building,room,course,stuempno,custname,deptname,deptcode,week,beginweek,endweek,beginclass,endclass,ischeck,isopen,remark,status,checkinfo,id,syncdate from ykt_ck.t_courseplan_temp where 1=1");
        if (StringUtils.isNotBlank(termName)) {
            sql.append(" and term='").append(termName).append("'");
        }
        if (StringUtils.isNotBlank(beginDate)) {
            sql.append(" and syncdate>='").append(beginDate).append("'");
        }
        if (StringUtils.isNotBlank(endDate)) {
            sql.append(" and syncdate<='").append(endDate).append("'");
        }
        if (StringUtils.isNotBlank(status)) {
            sql.append(" and status='").append(status).append("'");
        }
        sql.append(" order by id");
        List list = jdbcTemplate.queryForList(sql.toString());
        List<TCourseplanTemp> result = new ArrayList<TCourseplanTemp>();
        if (list != null) {
            for (int i = 0; i < list.size(); i++) {
                Map row = (Map) list.get(i);

                TCourseplanTemp tCourseplanTemp = new TCourseplanTemp();
                tCourseplanTemp.setTerm((String) row.get("TERM"));
                tCourseplanTemp.setFaculty((String) row.get("FACULTY"));
                tCourseplanTemp.setArea((String) row.get("AREA"));
                tCourseplanTemp.setBuilding((String) row.get("BUILDING"));
                tCourseplanTemp.setRoom((String) row.get("ROOM"));
                tCourseplanTemp.setCourse((String) row.get("COURSE"));
                tCourseplanTemp.setStuempno((String) row.get("STUEMPNO"));
                tCourseplanTemp.setCustname((String) row.get("CUSTNAME"));
                tCourseplanTemp.setDeptname((String) row.get("DEPTNAME"));
                tCourseplanTemp.setDeptcode((String) row.get("DEPTCODE"));
                tCourseplanTemp.setWeek((String) row.get("WEEK"));
                tCourseplanTemp.setBeginWeek((String) row.get("BEGINWEEK"));
                tCourseplanTemp.setEndWeek((String) row.get("ENDWEEK"));
                tCourseplanTemp.setBeginClass((String) row.get("BEGINCLASS"));
                tCourseplanTemp.setEndClass((String) row.get("ENDCLASS"));
                tCourseplanTemp.setIscheck((String) row.get("ISCHECK"));
                tCourseplanTemp.setIsopen((String) row.get("ISOPEN"));
                tCourseplanTemp.setRemark((String) row.get("REMARK"));
                tCourseplanTemp.setStatus((String) row.get("STATUS"));
                tCourseplanTemp.setCheckInfo((String) row.get("CHECKINFO"));
                tCourseplanTemp.setId(Long.valueOf(row.get("ID").toString()));
                tCourseplanTemp.setSyncDate((String) row.get("SYNCDATE"));

                result.add(tCourseplanTemp);
            }
        }
        return result;
    }

    public List findErrorCourseplanTemp(String termName, String beginDate, String endDate) throws Exception {
        return findCourseplanTemp(termName,beginDate,endDate,"0");
    }

    /**
     * @deprecated
     */
    public void deletePreviewData() {
        String hql = "from TCourseplanTemp t where t.status='2' order by t.id";
        List<TCourseplanTemp> list = courseplanTempDAO.find(hql);
        if (list != null) {
            for (TCourseplanTemp tCourseplanTemp : list) {
                courseplanTempDAO.delete(tCourseplanTemp);
            }
        }
    }

    public void saveSyncLog(TSyncLog tSyncLog) {
        syncLogDAO.save(tSyncLog);
    }

    public List findSyncLog(String termName, String useWeek) {
        StringBuffer hql = new StringBuffer("from TSyncLog t where 1=1");
        if (StringUtils.isNotBlank(termName)) {
            hql.append(" and t.term='").append(termName).append("'");
        }
        if (StringUtils.isNotBlank(useWeek)) {
            hql.append(" and t.useWeek='").append(useWeek).append("'");
        }
        hql.append(" order by t.syncTime desc,t.id");
        return syncLogDAO.find(hql.toString());
    }

    private TTerm getTerm() {
        String sql = "select t.termid,t.termname,t.begindate,t.enddate from ykt_ck.t_term t where t.begindate<=to_char(sysdate+10,'yyyyMMdd') and t.enddate>=to_char(sysdate-10,'yyyyMMdd') and t.enable=1";
        List result = jdbcTemplate.queryForList(sql);
        TTerm term = null;
        if (result != null && result.size() > 0) {
            Map row = (Map) result.get(0);
            term = new TTerm();
            term.setTermId((String) row.get("TERMID"));
            term.setTermName((String) row.get("TERMNAME"));
            term.setBeginDate((String) row.get("BEGINDATE"));
            term.setEndDate((String) row.get("ENDDATE"));
        }
        return term;
    }

    public Map getTimeMap() {
        Map timeMap = new HashMap();
        List times = timeService.findAllTimes();
        if (times != null && times.size() > 0) {
            for (int i = 0; i < times.size(); i++) {
                TTime time = (TTime) times.get(i);
                timeMap.put(time.getClassNum(), time);
            }
        }
        return timeMap;
    }

    /**
     * 校验预览课程计划
     */
    public String checkPreviewData() {
        try {
            //寻找当前学期信息
            TTerm term = getTerm();
            if (term == null) {
                _log.info("没有找到学期");
                return "没有找到学期";
            }
            //计算下周在本学期中对应的周次
            Date nextMonday = DateUtilExtend.getNextMonday();
            long useWeek = DateUtilExtend.getUseWeek(term.getBeginDate(), nextMonday);
            if (useWeek == -1) {
                _log.info("下一周不在学期范围内");
                return "下一周不在学期范围内";
            }

            //所有预览课程计划
            List allCourseplan = findPreviewCourseplanTemp();
            if (allCourseplan == null || allCourseplan.isEmpty()) {
                return "没有要校验的课程计划";
            }
            //对预览课程计划进行校验
            Map errorMap = new HashMap();
            Map existMap = findExistCourseplan(term, "2");
            int success = 0;
            for (int i = 0; i < allCourseplan.size(); i++) {
                TCourseplanTemp tCourseplanTemp = (TCourseplanTemp) allCourseplan.get(i);
                Long id = tCourseplanTemp.getId();
                //校验学期
                if (!term.getTermName().equals(tCourseplanTemp.getTerm())) {
                    addError(id, errorMap, "该课程计划对应的学期不存在；");
                }
                //校验字段基本条件
                checkField(tCourseplanTemp, errorMap);

                if (existMap.get(id) != null) {
                    addError(id, errorMap, "该课程计划对应时间段以及教室已被占用；");
                }
                //校验房间是否存在
                TRoom tRoom = roomService.findOneRoom(tCourseplanTemp.getArea(), tCourseplanTemp.getBuilding(), tCourseplanTemp.getRoom());
                if (tRoom == null) {
                    addError(id, errorMap, "该课程计划对应的校区、楼宇、教室在系统中找不到匹配关系；");
                }
                //校验教师信息
                TCustomer tCustomer = customerService.findCustByStuemp(tCourseplanTemp.getStuempno());
                if (tCustomer == null) {
                    addError(id, errorMap, "在系统中找不到该课程计划对应的教师；");
                } else {
                    if (!tCustomer.getCustname().equals(tCourseplanTemp.getCustname())) {
                        addError(id, errorMap, "该课程计划对应的教师工号与姓名不匹配；");
                    }
                }
                //校验上课班级信息
                String[] deptcodes = StringUtil.split(tCourseplanTemp.getDeptcode(), ",");
                for (String deptcode : deptcodes) {
                    if (StringUtils.isNotBlank(deptcode)) {
                        List deptList = departmentService.findDept(deptcode);
                        if (deptList == null || deptList.size() == 0) {
                            addError(id, errorMap, "该课程计划对应的班级代码不存在；");
                        }
                    }
                }
                //如果通过验证，那么将这条预览数据删掉，如果没通过验证，将验证信息写入预览数据中
                StringBuffer error = (StringBuffer) errorMap.get(tCourseplanTemp.getId());
                if (error != null) {
                    tCourseplanTemp.setCheckInfo(error.toString());
                    courseplanTempDAO.update(tCourseplanTemp);
                } else {
                    success++;
                    courseplanTempDAO.delete(tCourseplanTemp);
                }
            }
            return "共[" + allCourseplan.size() + "]条记录，其中[" + success + "]条可以导入。";
        } catch (Exception e) {
            _log.error("校验课程计划失败：");
            _log.error(e);
            return "校验课程计划失败：" + e.getMessage();
        }
    }

    private List findPreviewCourseplanTemp() throws Exception {
        return findCourseplanTemp(null,null,null,"2");
    }

    /**
     * 导入课程计划
     */
    public String importData() {
        String message;
        String now = DateUtilExtend.getNow();
        TSyncLog tSyncLog = new TSyncLog();
        tSyncLog.setSyncTime(now);
        String nowDate = DateUtilExtend.getNowDate2();
        try {
            //寻找当前学期信息
            TTerm term = getTerm();
            if (term == null) {
                _log.info("没有找到学期");
                return "没有找到学期";
            }
            tSyncLog.setTerm(term.getTermName());
            //计算下周在本学期中对应的周次
            Date nextMonday = DateUtilExtend.getNextMonday();
            long useWeek = DateUtilExtend.getUseWeek(term.getBeginDate(), nextMonday);
            if (useWeek == -1) {
                _log.info("下一周不在学期范围内");
                return "下一周不在学期范围内";
            }
            tSyncLog.setUseWeek(String.valueOf(useWeek));

            //所有的待审核课程计划
            List allCourseplan = findPendingCourseplanTemp();
            if (allCourseplan == null || allCourseplan.isEmpty()) {
                throw new RuntimeException("没有要导入的课程计划");
            }
            //对待审核课程计划进行校验
            Map errorMap = new HashMap();
            Map existMap = findExistCourseplan(term, "1");
            Map timeMap = getTimeMap();
            int success = 0;
            for (int i = 0; i < allCourseplan.size(); i++) {
                TCourseplanTemp tCourseplanTemp = (TCourseplanTemp) allCourseplan.get(i);
                Long id = tCourseplanTemp.getId();
                //校验学期
                if (!term.getTermName().equals(tCourseplanTemp.getTerm())) {
                    addError(id, errorMap, "该课程计划对应的学期不存在；");
                }
                //校验字段基本条件
                checkField(tCourseplanTemp, errorMap);

                if (existMap.get(id) != null) {
                    addError(id, errorMap, "该课程计划对应时间段以及教室已被占用；");
                }
                //校验房间是否存在
                TRoom tRoom = roomService.findOneRoom(tCourseplanTemp.getArea(), tCourseplanTemp.getBuilding(), tCourseplanTemp.getRoom());
                if (tRoom == null) {
                    addError(id, errorMap, "该课程计划对应的校区、楼宇、教室在系统中找不到匹配关系；");
                }
                //校验教师信息
                TCustomer tCustomer = customerService.findCustByStuemp(tCourseplanTemp.getStuempno());
                if (tCustomer == null) {
                    addError(id, errorMap, "在系统中找不到该课程计划对应的教师；");
                } else {
                    if (!tCustomer.getCustname().equals(tCourseplanTemp.getCustname())) {
                        addError(id, errorMap, "该课程计划对应的教师工号与姓名不匹配；");
                    }
                }
                //校验上课班级信息
                String[] deptcodes = StringUtil.split(tCourseplanTemp.getDeptcode(), ",");
                for (String deptcode : deptcodes) {
                    if (StringUtils.isNotBlank(deptcode)) {
                        List deptList = departmentService.findDept(deptcode);
                        if (deptList == null || deptList.size() == 0) {
                            addError(id, errorMap, "该课程计划对应的班级代码不存在；");
                        }
                    }
                }
                //导入课程计划
                String nowTime = DateUtilExtend.getTimestamp();
                tCourseplanTemp.setSyncDate(nowDate);
                success = success + saveCourseplan(tCourseplanTemp, term, tRoom, timeMap, tCustomer, nowTime, errorMap);
            }
            message = "共[" + allCourseplan.size() + "]条记录，其中[" + success + "]条已经导入。";
        } catch (Exception e) {
            _log.error("导入课程计划失败：" + e.getMessage());
            message = "导入课程计划失败：" + e.getMessage();
        }
        tSyncLog.setRemark(message);
        syncLogDAO.save(tSyncLog);
        return message;
    }

    private int saveCourseplan(TCourseplanTemp tCourseplanTemp, TTerm term, TRoom room, Map timeMap, TCustomer customer, String nowTime, Map errorMap) {
        int ret = 0;
        try {
            StringBuffer error = (StringBuffer) errorMap.get(tCourseplanTemp.getId());
            if (error != null) {
                tCourseplanTemp.setStatus("0");
                tCourseplanTemp.setCheckInfo(error.toString());
                courseplanTempDAO.update(tCourseplanTemp);
            } else {
                TCourseplan tCourseplan = new TCourseplan();
                tCourseplan.setTerm(term);
                tCourseplan.setRoom(room);
                tCourseplan.setBeginWeek(Integer.valueOf(tCourseplanTemp.getBeginWeek()));
                tCourseplan.setEndWeek(Integer.valueOf(tCourseplanTemp.getEndWeek()));
                tCourseplan.setWeek(Integer.valueOf(tCourseplanTemp.getWeek()));
                tCourseplan.setBeginClassNum(Integer.valueOf(tCourseplanTemp.getBeginClass()));
                tCourseplan.setEndClassNum(Integer.valueOf(tCourseplanTemp.getEndClass()));
                tCourseplan.setCreator("sync");
                if ("是".equals(tCourseplanTemp.getIscheck())) {
                    tCourseplan.setIscheck(Integer.valueOf(1));
                } else {
                    tCourseplan.setIscheck(Integer.valueOf(0));
                }
                if ("是".equals(tCourseplanTemp.getIsopen())) {
                    tCourseplan.setIsopen(Integer.valueOf(1));
                } else {
                    tCourseplan.setIsopen(Integer.valueOf(0));
                }
                tCourseplan.setUseWeek(Integer.valueOf(tCourseplanTemp.getBeginWeek()));
                String useDate = DateUtilExtend.getCourseDate(term.getBeginDate(), tCourseplan.getUseWeek(), tCourseplan.getWeek(), "yyyyMMdd");
                tCourseplan.setUseDate(useDate);
                TTime beginTime = (TTime) timeMap.get(tCourseplan.getBeginClassNum());
                tCourseplan.setBeginTime(beginTime.getBeginTime());
                TTime endTime = (TTime) timeMap.get(tCourseplan.getEndClassNum());
                tCourseplan.setEndTime(endTime.getEndTime());
                tCourseplan.setStatus(Integer.valueOf(1));
                tCourseplan.setCustomer(customer);
                tCourseplan.setCreateTime(nowTime);
                TCourse course = courseService.findOneCourse(tCourseplanTemp.getCourse());
                if (course == null) {
                    course = new TCourse();
                    course.setCoursename(tCourseplanTemp.getCourse());
                    courseService.saveCourse(course);
                }
                tCourseplan.setCourse(course);
                courseplanDAO.save(tCourseplan);
                String[] deptcodes = org.king.utils.StringUtil.split(tCourseplanTemp.getDeptcode(), ",");
                if (deptcodes != null && deptcodes.length > 0) {
                    for (String deptcode : deptcodes) {
                        if (StringUtils.isNotBlank(deptcode)) {
                            TCourseplanclassId id = new TCourseplanclassId(tCourseplan.getId(), deptcode);
                            TCourseplanclass courseplanclass = new TCourseplanclass(id);
                            courseplanDAO.save(courseplanclass);
                        }
                    }
                }
                //将临时课程计划标记为已导入
                tCourseplanTemp.setStatus("3");
                courseplanTempDAO.update(tCourseplanTemp);
                ret = 1;
            }
        } catch (Exception e) {
            tCourseplanTemp.setStatus("0");
            tCourseplanTemp.setCheckInfo("系统异常：" + e.getMessage());
            courseplanTempDAO.update(tCourseplanTemp);
            _log.error("保存课程计划失败：" + e.getMessage());
        }
        return ret;
    }

    /**
     * 检验对应的值是否为空
     *
     * @param value     待检验的值
     * @param errorInfo 检验失败的提示信息
     * @param id        该课程计划的唯一标识，用于存储检验信息
     * @param errorMap  检验信息集合
     */
    private void notNullCheck(String value, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isBlank(value)) {
            addError(id, errorMap, errorInfo + "不能为空；");
        }
    }

    /**
     * 校验两个值是否相等，这里只在两个值都不为空的时候校验
     *
     * @param value1    待校验值1
     * @param value2    待校验值2
     * @param errorInfo 校验失败提示信息
     * @param id        该课程计划的唯一标识，用于存储校验信息
     * @param errorMap  校验信息集合
     */
    private void equalsCheck(String value1, String value2, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isNotBlank(value1) && StringUtils.isNotBlank(value2) && !value1.equals(value2)) {
            addError(id, errorMap, errorInfo + "不相等；");
        }
    }

    /**
     * 校验指定值是否是数字
     *
     * @param value     待校验值
     * @param errorInfo 校验失败提示信息
     * @param id        该课程计划的唯一标识，用于存储校验信息
     * @param errorMap  校验信息集合
     */
    private void numbericCheck(String value, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isNotBlank(value)) {
            for (int i = 0; i < value.length(); i++) {
                if (!Character.isDigit(value.charAt(i))) {
                    addError(id, errorMap, errorInfo + "不是数字；");
                    return;
                }
            }
        }
    }

    /**
     * 主要用于校验是否开门以及是否考勤字段
     *
     * @param value     待校验值
     * @param errorInfo 校验失败提示信息
     * @param id        该课程计划的唯一标识，用于存储校验信息
     * @param errorMap  校验信息集合
     */
    private void yesNoCheck(String value, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isNotBlank(value)) {
            if ("是".equals(value) || "否".equals(value)) {
            } else {
                addError(id, errorMap, errorInfo + "只能为是或者否");
            }
        }
    }

    private void addError(Long id, Map errorMap, String errorInfo) {
        StringBuffer error = (StringBuffer) errorMap.get(id);
        if (error == null) {
            error = new StringBuffer(errorInfo);
            errorMap.put(id, error);
        } else {
            error.append(errorInfo);

        }
    }

    private void checkField(TCourseplanTemp tCourseplanTemp, Map errorMap) {
        Long id = tCourseplanTemp.getId();
        notNullCheck(tCourseplanTemp.getTerm(), "学期", id, errorMap);
        notNullCheck(tCourseplanTemp.getFaculty(), "院系", id, errorMap);
        notNullCheck(tCourseplanTemp.getArea(), "校区", id, errorMap);
        notNullCheck(tCourseplanTemp.getBuilding(), "教学楼", id, errorMap);
        notNullCheck(tCourseplanTemp.getRoom(), "教室", id, errorMap);
        notNullCheck(tCourseplanTemp.getCourse(), "课程", id, errorMap);
        notNullCheck(tCourseplanTemp.getStuempno(), "教师工号", id, errorMap);
        notNullCheck(tCourseplanTemp.getCustname(), "教师姓名", id, errorMap);
        notNullCheck(tCourseplanTemp.getDeptcode(), "上课班级", id, errorMap);
        notNullCheck(tCourseplanTemp.getWeek(), "周几", id, errorMap);
        notNullCheck(tCourseplanTemp.getBeginWeek(), "开始周次", id, errorMap);
        notNullCheck(tCourseplanTemp.getEndWeek(), "结束周次", id, errorMap);
        notNullCheck(tCourseplanTemp.getBeginClass(), "开始课次", id, errorMap);
        notNullCheck(tCourseplanTemp.getEndClass(), "结束课次", id, errorMap);
        notNullCheck(tCourseplanTemp.getIscheck(), "是否考勤", id, errorMap);
        notNullCheck(tCourseplanTemp.getIsopen(), "是否开门", id, errorMap);

        equalsCheck(tCourseplanTemp.getBeginWeek(), tCourseplanTemp.getEndWeek(), "开始周次与结束周次", id, errorMap);
        numbericCheck(tCourseplanTemp.getWeek(), "周几", id, errorMap);
        numbericCheck(tCourseplanTemp.getBeginWeek(), "开始周次", id, errorMap);
        numbericCheck(tCourseplanTemp.getEndWeek(), "结束周次", id, errorMap);
        numbericCheck(tCourseplanTemp.getBeginClass(), "开始课次", id, errorMap);
        numbericCheck(tCourseplanTemp.getEndClass(), "结束课次", id, errorMap);

        yesNoCheck(tCourseplanTemp.getIscheck(), "是否考勤", id, errorMap);
        yesNoCheck(tCourseplanTemp.getIsopen(), "是否开门", id, errorMap);
    }

    /**
     * 判断对应的课程计划是否已经存在于系统中
     * 通过判断具体时间，具体教室是否被占用来判断该课程计划是否已经存在于系统中
     * 如果时间，教室相同，但是其他信息不同，那么此处该记录也将被标记为异常记录，可以通过在系统中修改课程计划的方式来达到更新课程计划的目的
     *
     * @param term   .
     * @param status 用于区别是预览数据还是待审核数据
     * @return .
     */
    private Map findExistCourseplan(TTerm term, String status) {
        StringBuffer sql = new StringBuffer("select t1.id from");
        sql.append(" (select cpt.id,cpt.beginclass,cpt.endclass,cpt.week,cpt.beginweek,r.roomid");
        sql.append(" from ykt_ck.t_courseplan_temp cpt,ykt_cur.t_area a,ykt_ck.t_room r");
        sql.append(" where r.schoolarea = a.areacode and cpt.building = r.build and cpt.room = r.roomname and cpt.area = a.areaname");
        sql.append(" and cpt.status='").append(status).append("' ) t1,");
        sql.append(" (select cp.beginclassnum,cp.endclassnum,cp.week,cp.useweek,cp.roomid");
        sql.append(" from ykt_ck.t_courseplan cp");
        sql.append(" where cp.termid = '").append(term.getTermId()).append("') t2");
        sql.append(" where t1.beginclass = t2.beginclassnum and t1.endclass = t2.endclassnum and t1.week = t2.week");
        sql.append(" and t1.beginweek = t2.useweek and t1.roomid = t2.roomid");
        List result = jdbcTemplate.queryForList(sql.toString());
        Map existMap = new HashMap();
        if (result != null && result.size() > 0) {
            for (int i = 0; i < result.size(); i++) {
                Map row = (Map) result.get(i);
                Long id = Long.valueOf(row.get("ID").toString());
                existMap.put(id, new Object());
            }
        }

        return existMap;
    }
}
