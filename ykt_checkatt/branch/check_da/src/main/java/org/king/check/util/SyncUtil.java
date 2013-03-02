package org.king.check.util;

import org.apache.commons.configuration.PropertiesConfiguration;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.domain.TCourseplanTemp;
import org.king.check.domain.TSyncLog;
import org.king.check.domain.TTerm;
import org.king.check.service.SyncService;

import javax.naming.Context;
import javax.naming.InitialContext;
import javax.sql.DataSource;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.Date;
import java.util.List;

/**
 * ��У�����ϵͳͬ���γ̼ƻ�����.
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class SyncUtil {
    private static final Log _log = LogFactory.getLog(SyncUtil.class);

    private static SyncService syncService;

    /**
     * Ԥ�����ݣ�������������� *
     */
    public static final String SYNC_PREVIEW = "2";

    /**
     * ����˵Ŀγ̼ƻ����� *
     */
    public static final String SYNC_PENDING = "1";

    /**
     * δͨ����˵Ŀγ̼ƻ����� *
     */
    public static final String SYNC_FAILURE = "0";

    public static final String SYNC_SUCCESS = "3";

    public void setSyncService(SyncService syncService) {
        SyncUtil.syncService = syncService;
    }

    private static Connection getRemoteConnection() {
        Connection remoteConn;
        try {
            PropertiesConfiguration config = GetPropertiesUtil.getInstance();
            String url = config.getString("sync.url");
            String user = config.getString("sync.user");
            String password = config.getString("sync.password");
            Class.forName("com.microsoft.sqlserver.jdbc.SQLServerDriver");
            remoteConn = DriverManager.getConnection(url, user, password);
            return remoteConn;
        } catch (Exception e) {
            throw new RuntimeException("��ȡԶ�����ݿ�����ʧ�ܣ�" + e.getMessage());
        }
    }

    public static void previewData() {
        syncData(SYNC_PREVIEW);
    }

    public static void syncData() {
        syncData(SYNC_PENDING);
    }

    public static void importData() {
        syncService.importData();
    }

    /**
     * ÿ��Ԥ�����ܿγ̼ƻ�ʱ����ɾ����ʷԤ������
     *
     * @param conn .
     * @return .
     */
    public static int deletePreviewData(Connection conn) {
        Statement stmt = null;
        try {
            String sql = "delete from ykt_ck.t_courseplan_temp t where t.status='2'";
            stmt = conn.createStatement();
            return stmt.executeUpdate(sql);
        } catch (SQLException e) {
            throw new RuntimeException("ɾ���ɵĿγ̼ƻ�Ԥ������ʧ��" + e.getMessage());
        } finally {
            close(stmt);
        }
    }

    /**
     * ͬ���γ̼ƻ�
     *
     * @param status ��1,2����1��ʾ�ôβ���Ϊϵͳ�Զ�ͬ���γ̼ƻ���2��ʾ�ôβ���Ϊ�˹�Ԥ���γ̼ƻ���Ԥ�����ݽ�����У�����ݵĺϷ��ԣ����ᱻ���뵽ϵͳ�γ̼ƻ���
     */
    private static void syncData(String status) {
        Context context = null;
        Connection localConn = null;

        Connection remoteConn = null;
        Statement remoteStmt = null;

        String nowTime = DateUtilExtend.getNow();
        TSyncLog tSyncLog = new TSyncLog();
        tSyncLog.setSyncTime(nowTime);
        try {
            context = new InitialContext();
            DataSource ds = (DataSource) context.lookup("java:comp/env/jdbc/check");
            localConn = ds.getConnection();

            //Ѱ�ҵ�ǰѧ����Ϣ
            TTerm term = getTerm(localConn);
            if (term == null) {
                _log.info("û���ҵ�ѧ��");
                return;
            }
            tSyncLog.setTerm(term.getTermName());
            //���������ڱ�ѧ���ж�Ӧ���ܴ�
            long useWeek = getNextWeek(term.getBeginDate());
            if (useWeek == -1) {
                _log.info("��һ�ܲ���ѧ�ڷ�Χ��");
                return;
            }
            tSyncLog.setUseWeek(String.valueOf(useWeek));

            remoteConn = getRemoteConnection();
            remoteStmt = remoteConn.createStatement();

            //�������ܶ�Ӧ�γ̼ƻ��Ļ�����Ϣ
            Integer recordCount = extractSummary(remoteStmt, term.getTermName(), String.valueOf(useWeek));
            tSyncLog.setRecordCount(recordCount == null ? "" : recordCount.toString());
            if (recordCount == null) {
                throw new RuntimeException("Warning��û���ҵ��γ̼ƻ�������Ϣ");
            } else if (recordCount.intValue() == 0) {
            } else {
                //�����������еĿγ̼ƻ�
                List result = extractData(remoteStmt);
                if (recordCount.intValue() != result.size()) {
                    throw new RuntimeException("Error���γ̼ƻ�������Ϣ�пγ̼ƻ�������ʵ��ȡ�ÿγ̼ƻ���������");
                }
                tSyncLog.setRemark("ͬ���γ̼ƻ��ɹ�");
                //�����Ԥ���γ̼ƻ�����ô��ɾ����ʷԤ������
                if (SYNC_PREVIEW.equals(status)) {
                    deletePreviewData(localConn);
                }
                saveData(localConn, result, tSyncLog, status);
//                syncService.saveData(result, tSyncLog, status);
            }
        } catch (Exception e) {
            _log.error("ͬ���γ̼ƻ�ʧ�ܣ�");
            _log.error(e);
            tSyncLog.setRemark(e.getMessage());
            saveData(localConn,null, tSyncLog, status);
        } finally {
            close(remoteStmt);
            close(remoteConn);
            close(localConn);
            close(context);
        }
    }

    /**
     * ��ȡ����һ�ڱ�ѧ���ж�Ӧ���ܴ�
     *
     * @param termBeginDate ѧ�ڿ�ʼ����,yyyyMMdd
     * @return �������һ��ѧ�ڿ�ʼ����С����ô����-1
     */
    private static long getNextWeek(String termBeginDate) {
        Date nextMonday = DateUtilExtend.getNextMonday();
        return DateUtilExtend.getUseWeek(termBeginDate, nextMonday);
    }

    /**
     * ��ȡ��ǰ����ѧ����Ϣ
     *
     * @param conn
     * @return .
     */
    public static TTerm getTerm(Connection conn) {
        Statement stmt = null;
        ResultSet rs = null;
        try {
            TTerm term = null;
            String sql = "select t.termname,t.begindate,t.enddate from ykt_ck.t_term t where t.begindate<=to_char(sysdate+10,'yyyyMMdd') and t.enddate>=to_char(sysdate-10,'yyyyMMdd') and t.enable=1";
            stmt = conn.createStatement();
            rs = stmt.executeQuery(sql);
            if (rs.next()) {
                term = new TTerm();
                term.setTermName(rs.getString("TERMNAME"));
                term.setBeginDate(rs.getString("BEGINDATE"));
                term.setEndDate(rs.getString("ENDDATE"));
            }
            return term;
        } catch (SQLException e) {
            throw new RuntimeException("��ȡѧ��ʧ�ܣ�" + e.getMessage());
        } finally {
            close(rs);
            close(stmt);
        }
    }

    /**
     * ��֤result��log��д����ͬһ��������
     *
     * @param conn     .
     * @param result   .
     * @param tSyncLog .
     * @param status   .
     */
    private static void saveData(Connection conn, List result, TSyncLog tSyncLog, String status) {
        PreparedStatement logStatement = null;
        PreparedStatement dataStatement = null;
        try {
            boolean autoCommit = conn.getAutoCommit();
            conn.setAutoCommit(false);
            if (tSyncLog != null) {
                syncService.saveSyncLog(tSyncLog);
            }
            if (result != null && result.size() > 0) {
                String sql = "INSERT INTO YKT_CK.T_COURSEPLAN_TEMP(ID,TERM,FACULTY,AREA,BUILDING,ROOM,COURSE,STUEMPNO,CUSTNAME,DEPTNAME,DEPTCODE,WEEK,BEGINWEEK,ENDWEEK,BEGINCLASS,ENDCLASS,ISCHECK,ISOPEN,STATUS)" +
                        " VALUES(YKT_CK.SEQ_SYNC.NEXTVAL,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
                dataStatement = conn.prepareStatement(sql);

                for (int i = 0; i < result.size(); i++) {
                    TCourseplanTemp tCourseplanTemp = (TCourseplanTemp) result.get(i);
                    dataStatement.setString(1, tCourseplanTemp.getTerm());
                    dataStatement.setString(2, tCourseplanTemp.getFaculty());
                    dataStatement.setString(3, tCourseplanTemp.getArea());
                    dataStatement.setString(4, tCourseplanTemp.getBuilding());
                    dataStatement.setString(5, tCourseplanTemp.getRoom());
                    dataStatement.setString(6, tCourseplanTemp.getCourse());
                    dataStatement.setString(7, tCourseplanTemp.getStuempno());
                    dataStatement.setString(8, tCourseplanTemp.getCustname());
                    dataStatement.setString(9, tCourseplanTemp.getDeptname());
                    dataStatement.setString(10, tCourseplanTemp.getDeptcode());
                    dataStatement.setString(11, tCourseplanTemp.getWeek());
                    dataStatement.setString(12, tCourseplanTemp.getBeginWeek());
                    dataStatement.setString(13, tCourseplanTemp.getEndWeek());
                    dataStatement.setString(14, tCourseplanTemp.getBeginClass());
                    dataStatement.setString(15, tCourseplanTemp.getEndClass());
                    dataStatement.setString(16, tCourseplanTemp.getIscheck());
                    dataStatement.setString(17, tCourseplanTemp.getIsopen());
                    dataStatement.setString(18, status);
                    dataStatement.addBatch();
                }
                dataStatement.executeBatch();
            }
            conn.commit();
            conn.setAutoCommit(autoCommit);
        } catch (Exception e) {
            try {
                conn.rollback();
            } catch (SQLException e1) {
                _log.error(e1.getMessage());
            }
            _log.error("����ͬ����־ʧ�ܣ�" + e.getMessage());
        } finally {
            close(logStatement);
            close(dataStatement);
        }
    }

    private static Integer extractSummary(Statement stmt, String termname, String useWeek) {
        Integer recordCount = null;
        ResultSet rs = null;
        try {
            String sql = "select s.Term,s.Week,s.recordCount,s.createDate from iExportToCardSummary s where s.Term='" + termname + "' and s.Week=" + useWeek;
            rs = stmt.executeQuery(sql);
            if (rs.next()) {
                recordCount = Integer.valueOf(rs.getString("recordCount"));
            }
            return recordCount;
        } catch (SQLException e) {
            throw new RuntimeException("��ȡ�γ̼ƻ�������Ϣʧ�ܣ�" + e.getMessage());
        } finally {
            close(rs);
        }
    }

    private static List extractData(Statement stmt) {
        List result = new ArrayList();
        ResultSet rs = null;
        try {
            String sql = "select d.Term,d.Department,d.Area,d.Building,d.ClassRoom,d.Course,d.TeacherCardNo,d.TeacherName,d.ClassName,d.Classes," +
                    "d.Week,d.StartWeek,d.EndWeek,d.StartClass,d.EndClass,d.IsCheck,d.IsOpendoor,d.Memo from iExportToCardData d " +
                    "order by d.Department,d.Area,d.Building";
            rs = stmt.executeQuery(sql);

            while (rs.next()) {
                TCourseplanTemp tCourseplanTemp = new TCourseplanTemp();
                tCourseplanTemp.setTerm(rs.getString("Term"));
                tCourseplanTemp.setFaculty(rs.getString("Department"));
                tCourseplanTemp.setArea(rs.getString("Area"));
                tCourseplanTemp.setBuilding(rs.getString("Building"));
                tCourseplanTemp.setRoom(rs.getString("ClassRoom"));
                tCourseplanTemp.setCourse(rs.getString("Course"));
                tCourseplanTemp.setStuempno(rs.getString("TeacherCardNo"));
                tCourseplanTemp.setCustname(rs.getString("TeacherName"));
                tCourseplanTemp.setDeptname(rs.getString("ClassName"));
                tCourseplanTemp.setDeptcode(rs.getString("Classes"));
                tCourseplanTemp.setWeek(rs.getString("Week"));
                tCourseplanTemp.setBeginWeek(rs.getString("StartWeek"));
                tCourseplanTemp.setEndWeek(rs.getString("EndWeek"));
                tCourseplanTemp.setBeginClass(rs.getString("StartClass"));
                tCourseplanTemp.setEndClass(rs.getString("EndClass"));
                tCourseplanTemp.setIscheck(rs.getString("IsCheck"));
                tCourseplanTemp.setIsopen(rs.getString("IsOpendoor"));
                tCourseplanTemp.setRemark(rs.getString("Memo"));
                result.add(tCourseplanTemp);
            }
            return result;
        } catch (SQLException e) {
            throw new RuntimeException("��ȡ�γ̼ƻ���ϸ����ʧ�ܣ�" + e.getMessage());
        } finally {
            close(rs);
        }
    }

    public static void close(ResultSet rs) {
        try {
            if (rs != null) {
                rs.close();
            }
        } catch (Exception e) {
        }
    }

    public static void close(Statement stmt) {
        try {
            if (stmt != null) {
                stmt.close();
            }
        } catch (Exception e) {
        }
    }

    public static void close(Connection conn) {
        try {
            if (conn != null) {
                conn.close();
            }
        } catch (Exception e) {
        }
    }

    public static void close(Context contex) {
        try {
            if (contex != null) {
                contex.close();
            }
        } catch (Exception e) {
        }
    }
}
