package org.king.check.door;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.DepartmentUtil;
import org.king.check.util.SyncUtil;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.sql.DataSource;
import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.Statement;
import java.sql.Types;
import java.text.SimpleDateFormat;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * Created by IntelliJ IDEA.
 * User: Administrator
 * Date: 2010-4-15
 * Time: 0:24:59
 * To change this template use File | Settings | File Templates.
 */
public class PersonsTaskBiz {
    private static final Log _log = LogFactory.getLog(PersonsTaskBiz.class);

    /**
     * �·�ȡ���Լ��Ž�����
     */
    public static void execute() {
        try {
            _log.debug("---------start to insert door list-----------");
            insertDoorList();
            _log.debug("---------success to insert door list-----------");
        } catch (Exception e) {
            _log.debug("---------fail to insert door list-----------");
            e.printStackTrace();
        }
    }

    /**
     * �����Чȡ���Լ��Ž���������
     */
    public static void cleanDoorData() {
        _log.debug("---------start to clean door list-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String procedure = "{call ykt_cur.proc_clean_door_data}";
            cstmt = conn.prepareCall(procedure);
            cstmt.execute();
            _log.debug("---------success to clean door list-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to clean door list-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * ���ɿ��ڱ���
     */
    public static void checkReport() {
        _log.debug("---------start to generate check report-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String procedure = "{call ykt_ck.check_report.proc_check_report}";
            cstmt = conn.prepareCall(procedure);
            cstmt.execute();
            _log.debug("---------success to generate check report-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to generate check report-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * ˢ��ָ��ʱ��ο���
     *
     * @param beginDate .
     * @param endDate   .
     */
    public static void refreshCheckReport(String beginDate, String endDate) {
        _log.debug("---------start to refresh check report-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String procedure = "{call ykt_ck.check_report.proc_refresh_check_report(?,?)}";
            cstmt = conn.prepareCall(procedure);
            cstmt.setString(1, beginDate);
            cstmt.setString(2, endDate);
            cstmt.execute();
            _log.debug("---------success to refresh check report-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to refresh check report-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * ˢ��ָ��ѧ��ѧ��ѧ�ڿ��ڱ���
     *
     * @param termId .
     */
    public static void refreshStudentTermCheck(String termId) {
        _log.debug("---------start to refresh student term check report-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        int result = 0;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String function = "{?=call ykt_ck.check_report.refresh_student_term_report(?)}";
            cstmt = conn.prepareCall(function);
            cstmt.registerOutParameter(1, Types.INTEGER);
            cstmt.setString(2, termId);
            cstmt.execute();
            result = cstmt.getInt(1);
            _log.debug("---------success to refresh student term check report-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to refresh student term check report-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * ˢ��ָ��ѧ�ڽ�ʦѧ�ڿ��ڱ���
     *
     * @param termId .
     */
    public static void refreshTeacherTermCheck(String termId) {
        _log.debug("---------start to refresh teacher term check report-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        int result = 0;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String function = "{?=call ykt_ck.check_report.refresh_teacher_term_report(?)}";
            cstmt = conn.prepareCall(function);
            cstmt.registerOutParameter(1, Types.INTEGER);
            cstmt.setString(2, termId);
            cstmt.execute();
            result = cstmt.getInt(1);
            _log.debug("---------success to refresh teacher term check report-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to refresh teacher term check report-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * ˢ��ָ��ѧ�ڰ༶ѧ�ڿ��ڱ���
     *
     * @param termId .
     */
    public static void refreshClassTermCheck(String termId) {
        _log.debug("---------start to refresh class term check report-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        int result = 0;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String function = "{?=call ykt_ck.check_report.refresh_class_term_report(?)}";
            cstmt = conn.prepareCall(function);
            cstmt.registerOutParameter(1, Types.INTEGER);
            cstmt.setString(2, termId);

            cstmt.execute();
            result = cstmt.getInt(1);
            _log.debug("---------success to refresh class term check report-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to refresh class term check report-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    public static void insertDoorList() throws Exception {
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String procedure = "{call ANALYSIZE_DOORDATA2(?,?,?)}";
            cstmt = conn.prepareCall(procedure);
            cstmt.setString(1, "");
            cstmt.setString(2, "");
            cstmt.setString(3, "1");
            cstmt.execute();
        }
        finally {
            if (cstmt != null)
                cstmt.close();
            if (conn != null)
                conn.close();
            if (ctx != null)
                ctx.close();
        }
    }

    /**
     * ɾ���ѷ�����Ž���Ա����
     *
     * @param courseId  ԭ�γ�ID
     * @param oldRoomId ԭ�γ̶�Ӧ�Ľ���ID
     * @throws Exception
     */
    public static void updateDoorList(String courseId, String oldRoomId) {
        try {
            Context ctx = null;
            Connection conn = null;
            CallableStatement cstmt = null;
            try {
                ctx = new InitialContext();
                DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
                conn = ds.getConnection();
                String procedure = "{call ANALYSIZE_DOORDATA2(?,?,?)}";
                cstmt = conn.prepareCall(procedure);
                cstmt.setString(1, courseId);
                cstmt.setString(2, oldRoomId);
                cstmt.setString(3, "2");
                cstmt.execute();
            }
            finally {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            }
        } catch (Exception e) {
            _log.error("ɾ������Ա����ʧ��.");
            e.printStackTrace();
        }
    }

    /**
     * ɨ�赱���ʦ�ϵ���ˮ
     */
    public static void scanRoomState() {
        try {
            _log.info("start scanning room state");
            Context ctx = null;
            Connection conn = null;
            Statement stmt = null;
            PreparedStatement pstmt = null;
            try {
                ctx = new InitialContext();
                DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
                conn = ds.getConnection();
                stmt = conn.createStatement();
                String useDate = DateUtilExtend.getNowDate2();
                StringBuffer query = new StringBuffer("select t1.*, t2.transtime from");
                query.append(" (select cp.id, cp.usedate, d.deviceid, cp.begintime, cp.endtime,cp.roomid");
                query.append(" from ykt_ck.t_courseplan cp,ykt_ck.t_room r,ykt_ck.t_roomdevice rd,ykt_cur.t_device d");
                query.append(" where cp.usedate = '").append(useDate).append("' and cp.roomid = r.roomid and r.roomid = rd.roomid and rd.deviceid = d.deviceid and d.devtypecode = '0121') t1");
                query.append(" left join (select dtl.transdate, dtl.transtime, dtl.deviceid from ykt_cur.t_doordtl dtl where transmark = '1026' and transdate = '").append(useDate).append("') t2");
                query.append(" on t1.deviceid = t2.deviceid and to_date(t2.transdate || t2.transtime, 'yyyymmddhh24miss') between to_date(t1.usedate || t1.begintime, 'yyyymmddhh24:mi') and to_date(t1.usedate || t1.endtime, 'yyyymmddhh24:mi') + 1 / 144");
                query.append(" left join ykt_ck.t_room_elec re on re.serialno=t1.id where re.serialno is null");

                ResultSet resultSet = stmt.executeQuery(query.toString());

                SimpleDateFormat sdf = new SimpleDateFormat("HHmmss");

                long now = sdf.parse(sdf.format(new java.util.Date())).getTime();
                List result = new ArrayList();
                while (resultSet.next()) {
                    Map row = new HashMap();
                    row.put("id", resultSet.getString("id"));
                    row.put("usedate", resultSet.getString("usedate"));
                    row.put("transtime", resultSet.getString("transtime"));
                    row.put("roomid", resultSet.getString("roomid"));

                    long beginTime = sdf.parse(DateUtilExtend.formattime(resultSet.getString("begintime"))).getTime();
                    long endTime = sdf.parse(DateUtilExtend.formattime(resultSet.getString("endtime"))).getTime();
                    String transtime = resultSet.getString("transtime");
                    //��Ч�ϵ���ˮ��ʱ�䷶ΧΪ���Ͽο�ʼ���¿�֮���ʮ����
                    if (now < beginTime) {
                        //����
                        row.put("state", "1");
                    } else if (now < endTime + 10 * 60 * 1000) {
                        //�ӿ�ʼ�Ͽε��¿κ��ʮ�����ڣ�����жϵ���ˮ����ô״̬Ϊˢ���ϵ磬����Ϊ����
                        if (StringUtils.isNotBlank(transtime)) {
                            row.put("state", "3");
                        } else {
                            row.put("state", "2");
                        }
                    } else {
                        //����жϵ���ˮ����ô״̬Ϊˢ���ϵ磬����Ϊ��ʱδ�ϵ�
                        if (StringUtils.isNotBlank(transtime)) {
                            row.put("state", "3");
                        } else {
                            row.put("state", "4");
                        }
                    }
                    result.add(row);
                }

                boolean autoCommit = conn.getAutoCommit();
                conn.setAutoCommit(false);
                pstmt = conn.prepareStatement("insert into ykt_ck.t_room_elec(serialno,updatedate,updatetime,transtime,state,roomid,isdeal) values(?,to_char(sysdate,'yyyymmdd'),to_char(sysdate,'hh24miss'),?,?,?,0)");
                for (int i = 0; i < result.size(); i++) {
                    Map row = (Map) result.get(i);
                    if ("4".equals(row.get("state"))) {
                        //��ʱδ�ϵ�
                        pstmt.setString(1, row.get("id").toString());
                        pstmt.setString(2, "");
                        pstmt.setInt(3, 4);
                        pstmt.setString(4, row.get("roomid").toString());
                        pstmt.addBatch();
                    } else if ("3".equals(row.get("state"))) {
                        //ˢ���ϵ�
                        pstmt.setString(1, row.get("id").toString());
                        pstmt.setString(2, row.get("transtime").toString());
                        pstmt.setInt(3, 3);
                        pstmt.setString(4, row.get("roomid").toString());
                        pstmt.addBatch();
                    }
                }
                pstmt.executeBatch();
                conn.commit();
                conn.setAutoCommit(autoCommit);
                _log.info("finish scanning room state");
            }
            finally {
                if (stmt != null)
                    stmt.close();
                if (pstmt != null)
                    pstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            }
        } catch (Exception e) {
            _log.error("��ȡ�����õ�״̬ʧ��.");
            e.printStackTrace();
        }
    }

    /**
     * ���༶�������ת������ʷ����
     *
     * @param deleteTime ɾ��ʱ��
     */
    public static void transferDepartment(Long deleteTime) {
        _log.debug("---------start to transfer department-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String procedure = "{call ykt_ck.check_report.proc_transfer_department(?)}";
            cstmt = conn.prepareCall(procedure);
            cstmt.setLong(1, deleteTime.longValue());
            cstmt.execute();
            _log.debug("---------success to transfer department-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to transfer department-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * ɨ���ת�ư༶�������ڷ����쳣��û��ת�ƽ���ʷ��İ༶����ת�ƽ���ʷ��
     * ���¹���༶ƴ����
     */
    public static void refreshDepartment() {
        try {
            _log.info("start refresh department");
            Context ctx = null;
            Connection conn = null;
            Statement stmt = null;
            PreparedStatement pstmt = null;
            try {
                ctx = new InitialContext();
                DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
                conn = ds.getConnection();
                stmt = conn.createStatement();
                String query = "select distinct dt.delete_time as deleteTime from ykt_ck.department_temp dt";

                ResultSet resultSet = stmt.executeQuery(query);
                while (resultSet.next()) {
                    Long deleteTime = Long.valueOf(resultSet.getString("deleteTime"));
                    transferDepartment(deleteTime);
                }
                //���¹���༶ƴ����
                DepartmentUtil.departmentTreeService.initDepartmentTree();
                _log.info("finish refresh department");
            }
            finally {
                if (stmt != null)
                    stmt.close();
                if (pstmt != null)
                    pstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            }
        } catch (Exception e) {
            _log.error("fail to refresh department.");
            e.printStackTrace();
        }
    }

    /**
     * Ϊ�ο���ʦ�����ο���ʦ��ɫ
     */
    public static void empowerTeacher() {
        _log.debug("---------start to empower teacher-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String procedure = "{call ykt_ck.check_report.proc_empower_teacher}";
            cstmt = conn.prepareCall(procedure);
            cstmt.execute();
            _log.debug("---------success to empower teacher-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to empower teacher-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * Ϊ����Ա���踨��Ա��ɫ
     */
    public static void empowerAssistant() {
        _log.debug("---------start to empower assistant-----------");
        Context ctx = null;
        Connection conn = null;
        CallableStatement cstmt = null;
        try {
            ctx = new InitialContext();
            DataSource ds = (DataSource) ctx.lookup("java:comp/env/jdbc/check");
            conn = ds.getConnection();
            String procedure = "{call ykt_ck.check_report.proc_empower_assistant}";
            cstmt = conn.prepareCall(procedure);
            cstmt.execute();
            _log.debug("---------success to empower assistant-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to empower assistant-----------");
        } finally {
            try {
                if (cstmt != null)
                    cstmt.close();
                if (conn != null)
                    conn.close();
                if (ctx != null)
                    ctx.close();
            } catch (Exception e1) {
            }
        }
    }

    /**
     * ͬ���γ̼ƻ�����
     */
    public static void syncData() {
        _log.debug("---------start to sync courseplan-----------");
        try {
            SyncUtil.syncData();
            _log.debug("---------success to sync courseplan-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to sync courseplan-----------");
        }
    }

    /**
     * ����γ̼ƻ�����
     */
    public static void importData() {
        _log.debug("---------start to import courseplan-----------");
        try {
            SyncUtil.importData();
            _log.debug("---------success to import courseplan-----------");
        } catch (Exception e) {
            e.printStackTrace();
            _log.debug("---------fail to import courseplan-----------");
        }
    }
}
