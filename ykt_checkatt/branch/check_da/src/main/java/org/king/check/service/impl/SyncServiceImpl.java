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
     * У��Ԥ���γ̼ƻ�
     */
    public String checkPreviewData() {
        try {
            //Ѱ�ҵ�ǰѧ����Ϣ
            TTerm term = getTerm();
            if (term == null) {
                _log.info("û���ҵ�ѧ��");
                return "û���ҵ�ѧ��";
            }
            //���������ڱ�ѧ���ж�Ӧ���ܴ�
            Date nextMonday = DateUtilExtend.getNextMonday();
            long useWeek = DateUtilExtend.getUseWeek(term.getBeginDate(), nextMonday);
            if (useWeek == -1) {
                _log.info("��һ�ܲ���ѧ�ڷ�Χ��");
                return "��һ�ܲ���ѧ�ڷ�Χ��";
            }

            //����Ԥ���γ̼ƻ�
            List allCourseplan = findPreviewCourseplanTemp();
            if (allCourseplan == null || allCourseplan.isEmpty()) {
                return "û��ҪУ��Ŀγ̼ƻ�";
            }
            //��Ԥ���γ̼ƻ�����У��
            Map errorMap = new HashMap();
            Map existMap = findExistCourseplan(term, "2");
            int success = 0;
            for (int i = 0; i < allCourseplan.size(); i++) {
                TCourseplanTemp tCourseplanTemp = (TCourseplanTemp) allCourseplan.get(i);
                Long id = tCourseplanTemp.getId();
                //У��ѧ��
                if (!term.getTermName().equals(tCourseplanTemp.getTerm())) {
                    addError(id, errorMap, "�ÿγ̼ƻ���Ӧ��ѧ�ڲ����ڣ�");
                }
                //У���ֶλ�������
                checkField(tCourseplanTemp, errorMap);

                if (existMap.get(id) != null) {
                    addError(id, errorMap, "�ÿγ̼ƻ���Ӧʱ����Լ������ѱ�ռ�ã�");
                }
                //У�鷿���Ƿ����
                TRoom tRoom = roomService.findOneRoom(tCourseplanTemp.getArea(), tCourseplanTemp.getBuilding(), tCourseplanTemp.getRoom());
                if (tRoom == null) {
                    addError(id, errorMap, "�ÿγ̼ƻ���Ӧ��У����¥�������ϵͳ���Ҳ���ƥ���ϵ��");
                }
                //У���ʦ��Ϣ
                TCustomer tCustomer = customerService.findCustByStuemp(tCourseplanTemp.getStuempno());
                if (tCustomer == null) {
                    addError(id, errorMap, "��ϵͳ���Ҳ����ÿγ̼ƻ���Ӧ�Ľ�ʦ��");
                } else {
                    if (!tCustomer.getCustname().equals(tCourseplanTemp.getCustname())) {
                        addError(id, errorMap, "�ÿγ̼ƻ���Ӧ�Ľ�ʦ������������ƥ�䣻");
                    }
                }
                //У���Ͽΰ༶��Ϣ
                String[] deptcodes = StringUtil.split(tCourseplanTemp.getDeptcode(), ",");
                for (String deptcode : deptcodes) {
                    if (StringUtils.isNotBlank(deptcode)) {
                        List deptList = departmentService.findDept(deptcode);
                        if (deptList == null || deptList.size() == 0) {
                            addError(id, errorMap, "�ÿγ̼ƻ���Ӧ�İ༶���벻���ڣ�");
                        }
                    }
                }
                //���ͨ����֤����ô������Ԥ������ɾ�������ûͨ����֤������֤��Ϣд��Ԥ��������
                StringBuffer error = (StringBuffer) errorMap.get(tCourseplanTemp.getId());
                if (error != null) {
                    tCourseplanTemp.setCheckInfo(error.toString());
                    courseplanTempDAO.update(tCourseplanTemp);
                } else {
                    success++;
                    courseplanTempDAO.delete(tCourseplanTemp);
                }
            }
            return "��[" + allCourseplan.size() + "]����¼������[" + success + "]�����Ե��롣";
        } catch (Exception e) {
            _log.error("У��γ̼ƻ�ʧ�ܣ�");
            _log.error(e);
            return "У��γ̼ƻ�ʧ�ܣ�" + e.getMessage();
        }
    }

    private List findPreviewCourseplanTemp() throws Exception {
        return findCourseplanTemp(null,null,null,"2");
    }

    /**
     * ����γ̼ƻ�
     */
    public String importData() {
        String message;
        String now = DateUtilExtend.getNow();
        TSyncLog tSyncLog = new TSyncLog();
        tSyncLog.setSyncTime(now);
        String nowDate = DateUtilExtend.getNowDate2();
        try {
            //Ѱ�ҵ�ǰѧ����Ϣ
            TTerm term = getTerm();
            if (term == null) {
                _log.info("û���ҵ�ѧ��");
                return "û���ҵ�ѧ��";
            }
            tSyncLog.setTerm(term.getTermName());
            //���������ڱ�ѧ���ж�Ӧ���ܴ�
            Date nextMonday = DateUtilExtend.getNextMonday();
            long useWeek = DateUtilExtend.getUseWeek(term.getBeginDate(), nextMonday);
            if (useWeek == -1) {
                _log.info("��һ�ܲ���ѧ�ڷ�Χ��");
                return "��һ�ܲ���ѧ�ڷ�Χ��";
            }
            tSyncLog.setUseWeek(String.valueOf(useWeek));

            //���еĴ���˿γ̼ƻ�
            List allCourseplan = findPendingCourseplanTemp();
            if (allCourseplan == null || allCourseplan.isEmpty()) {
                throw new RuntimeException("û��Ҫ����Ŀγ̼ƻ�");
            }
            //�Դ���˿γ̼ƻ�����У��
            Map errorMap = new HashMap();
            Map existMap = findExistCourseplan(term, "1");
            Map timeMap = getTimeMap();
            int success = 0;
            for (int i = 0; i < allCourseplan.size(); i++) {
                TCourseplanTemp tCourseplanTemp = (TCourseplanTemp) allCourseplan.get(i);
                Long id = tCourseplanTemp.getId();
                //У��ѧ��
                if (!term.getTermName().equals(tCourseplanTemp.getTerm())) {
                    addError(id, errorMap, "�ÿγ̼ƻ���Ӧ��ѧ�ڲ����ڣ�");
                }
                //У���ֶλ�������
                checkField(tCourseplanTemp, errorMap);

                if (existMap.get(id) != null) {
                    addError(id, errorMap, "�ÿγ̼ƻ���Ӧʱ����Լ������ѱ�ռ�ã�");
                }
                //У�鷿���Ƿ����
                TRoom tRoom = roomService.findOneRoom(tCourseplanTemp.getArea(), tCourseplanTemp.getBuilding(), tCourseplanTemp.getRoom());
                if (tRoom == null) {
                    addError(id, errorMap, "�ÿγ̼ƻ���Ӧ��У����¥�������ϵͳ���Ҳ���ƥ���ϵ��");
                }
                //У���ʦ��Ϣ
                TCustomer tCustomer = customerService.findCustByStuemp(tCourseplanTemp.getStuempno());
                if (tCustomer == null) {
                    addError(id, errorMap, "��ϵͳ���Ҳ����ÿγ̼ƻ���Ӧ�Ľ�ʦ��");
                } else {
                    if (!tCustomer.getCustname().equals(tCourseplanTemp.getCustname())) {
                        addError(id, errorMap, "�ÿγ̼ƻ���Ӧ�Ľ�ʦ������������ƥ�䣻");
                    }
                }
                //У���Ͽΰ༶��Ϣ
                String[] deptcodes = StringUtil.split(tCourseplanTemp.getDeptcode(), ",");
                for (String deptcode : deptcodes) {
                    if (StringUtils.isNotBlank(deptcode)) {
                        List deptList = departmentService.findDept(deptcode);
                        if (deptList == null || deptList.size() == 0) {
                            addError(id, errorMap, "�ÿγ̼ƻ���Ӧ�İ༶���벻���ڣ�");
                        }
                    }
                }
                //����γ̼ƻ�
                String nowTime = DateUtilExtend.getTimestamp();
                tCourseplanTemp.setSyncDate(nowDate);
                success = success + saveCourseplan(tCourseplanTemp, term, tRoom, timeMap, tCustomer, nowTime, errorMap);
            }
            message = "��[" + allCourseplan.size() + "]����¼������[" + success + "]���Ѿ����롣";
        } catch (Exception e) {
            _log.error("����γ̼ƻ�ʧ�ܣ�" + e.getMessage());
            message = "����γ̼ƻ�ʧ�ܣ�" + e.getMessage();
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
                if ("��".equals(tCourseplanTemp.getIscheck())) {
                    tCourseplan.setIscheck(Integer.valueOf(1));
                } else {
                    tCourseplan.setIscheck(Integer.valueOf(0));
                }
                if ("��".equals(tCourseplanTemp.getIsopen())) {
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
                //����ʱ�γ̼ƻ����Ϊ�ѵ���
                tCourseplanTemp.setStatus("3");
                courseplanTempDAO.update(tCourseplanTemp);
                ret = 1;
            }
        } catch (Exception e) {
            tCourseplanTemp.setStatus("0");
            tCourseplanTemp.setCheckInfo("ϵͳ�쳣��" + e.getMessage());
            courseplanTempDAO.update(tCourseplanTemp);
            _log.error("����γ̼ƻ�ʧ�ܣ�" + e.getMessage());
        }
        return ret;
    }

    /**
     * �����Ӧ��ֵ�Ƿ�Ϊ��
     *
     * @param value     �������ֵ
     * @param errorInfo ����ʧ�ܵ���ʾ��Ϣ
     * @param id        �ÿγ̼ƻ���Ψһ��ʶ�����ڴ洢������Ϣ
     * @param errorMap  ������Ϣ����
     */
    private void notNullCheck(String value, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isBlank(value)) {
            addError(id, errorMap, errorInfo + "����Ϊ�գ�");
        }
    }

    /**
     * У������ֵ�Ƿ���ȣ�����ֻ������ֵ����Ϊ�յ�ʱ��У��
     *
     * @param value1    ��У��ֵ1
     * @param value2    ��У��ֵ2
     * @param errorInfo У��ʧ����ʾ��Ϣ
     * @param id        �ÿγ̼ƻ���Ψһ��ʶ�����ڴ洢У����Ϣ
     * @param errorMap  У����Ϣ����
     */
    private void equalsCheck(String value1, String value2, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isNotBlank(value1) && StringUtils.isNotBlank(value2) && !value1.equals(value2)) {
            addError(id, errorMap, errorInfo + "����ȣ�");
        }
    }

    /**
     * У��ָ��ֵ�Ƿ�������
     *
     * @param value     ��У��ֵ
     * @param errorInfo У��ʧ����ʾ��Ϣ
     * @param id        �ÿγ̼ƻ���Ψһ��ʶ�����ڴ洢У����Ϣ
     * @param errorMap  У����Ϣ����
     */
    private void numbericCheck(String value, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isNotBlank(value)) {
            for (int i = 0; i < value.length(); i++) {
                if (!Character.isDigit(value.charAt(i))) {
                    addError(id, errorMap, errorInfo + "�������֣�");
                    return;
                }
            }
        }
    }

    /**
     * ��Ҫ����У���Ƿ����Լ��Ƿ����ֶ�
     *
     * @param value     ��У��ֵ
     * @param errorInfo У��ʧ����ʾ��Ϣ
     * @param id        �ÿγ̼ƻ���Ψһ��ʶ�����ڴ洢У����Ϣ
     * @param errorMap  У����Ϣ����
     */
    private void yesNoCheck(String value, String errorInfo, Long id, Map errorMap) {
        if (StringUtils.isNotBlank(value)) {
            if ("��".equals(value) || "��".equals(value)) {
            } else {
                addError(id, errorMap, errorInfo + "ֻ��Ϊ�ǻ��߷�");
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
        notNullCheck(tCourseplanTemp.getTerm(), "ѧ��", id, errorMap);
        notNullCheck(tCourseplanTemp.getFaculty(), "Ժϵ", id, errorMap);
        notNullCheck(tCourseplanTemp.getArea(), "У��", id, errorMap);
        notNullCheck(tCourseplanTemp.getBuilding(), "��ѧ¥", id, errorMap);
        notNullCheck(tCourseplanTemp.getRoom(), "����", id, errorMap);
        notNullCheck(tCourseplanTemp.getCourse(), "�γ�", id, errorMap);
        notNullCheck(tCourseplanTemp.getStuempno(), "��ʦ����", id, errorMap);
        notNullCheck(tCourseplanTemp.getCustname(), "��ʦ����", id, errorMap);
        notNullCheck(tCourseplanTemp.getDeptcode(), "�Ͽΰ༶", id, errorMap);
        notNullCheck(tCourseplanTemp.getWeek(), "�ܼ�", id, errorMap);
        notNullCheck(tCourseplanTemp.getBeginWeek(), "��ʼ�ܴ�", id, errorMap);
        notNullCheck(tCourseplanTemp.getEndWeek(), "�����ܴ�", id, errorMap);
        notNullCheck(tCourseplanTemp.getBeginClass(), "��ʼ�δ�", id, errorMap);
        notNullCheck(tCourseplanTemp.getEndClass(), "�����δ�", id, errorMap);
        notNullCheck(tCourseplanTemp.getIscheck(), "�Ƿ���", id, errorMap);
        notNullCheck(tCourseplanTemp.getIsopen(), "�Ƿ���", id, errorMap);

        equalsCheck(tCourseplanTemp.getBeginWeek(), tCourseplanTemp.getEndWeek(), "��ʼ�ܴ�������ܴ�", id, errorMap);
        numbericCheck(tCourseplanTemp.getWeek(), "�ܼ�", id, errorMap);
        numbericCheck(tCourseplanTemp.getBeginWeek(), "��ʼ�ܴ�", id, errorMap);
        numbericCheck(tCourseplanTemp.getEndWeek(), "�����ܴ�", id, errorMap);
        numbericCheck(tCourseplanTemp.getBeginClass(), "��ʼ�δ�", id, errorMap);
        numbericCheck(tCourseplanTemp.getEndClass(), "�����δ�", id, errorMap);

        yesNoCheck(tCourseplanTemp.getIscheck(), "�Ƿ���", id, errorMap);
        yesNoCheck(tCourseplanTemp.getIsopen(), "�Ƿ���", id, errorMap);
    }

    /**
     * �ж϶�Ӧ�Ŀγ̼ƻ��Ƿ��Ѿ�������ϵͳ��
     * ͨ���жϾ���ʱ�䣬��������Ƿ�ռ�����жϸÿγ̼ƻ��Ƿ��Ѿ�������ϵͳ��
     * ���ʱ�䣬������ͬ������������Ϣ��ͬ����ô�˴��ü�¼Ҳ�������Ϊ�쳣��¼������ͨ����ϵͳ���޸Ŀγ̼ƻ��ķ�ʽ���ﵽ���¿γ̼ƻ���Ŀ��
     *
     * @param term   .
     * @param status ����������Ԥ�����ݻ��Ǵ��������
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
