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
 * 从校舍管理系统同步课程计划数据.
 * User: Yiming.You
 * Date: 2011-3-4
 */
public class SyncUtil {
    private static final Log _log = LogFactory.getLog(SyncUtil.class);

    private static SyncService syncService;

    /**
     * 预览数据，不进入审核流程 *
     */
    public static final String SYNC_PREVIEW = "2";

    /**
     * 待审核的课程计划数据 *
     */
    public static final String SYNC_PENDING = "1";

    /**
     * 未通过审核的课程计划数据 *
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
            throw new RuntimeException("获取远程数据库连接失败：" + e.getMessage());
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
     * 每次预览下周课程计划时，先删除历史预览数据
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
            throw new RuntimeException("删除旧的课程计划预览数据失败" + e.getMessage());
        } finally {
            close(stmt);
        }
    }

    /**
     * 同步课程计划
     *
     * @param status 【1,2】，1表示该次操作为系统自动同步课程计划，2表示该次操作为人工预览课程计划，预览数据仅用于校验数据的合法性，不会被导入到系统课程计划中
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

            //寻找当前学期信息
            TTerm term = getTerm(localConn);
            if (term == null) {
                _log.info("没有找到学期");
                return;
            }
            tSyncLog.setTerm(term.getTermName());
            //计算下周在本学期中对应的周次
            long useWeek = getNextWeek(term.getBeginDate());
            if (useWeek == -1) {
                _log.info("下一周不在学期范围内");
                return;
            }
            tSyncLog.setUseWeek(String.valueOf(useWeek));

            remoteConn = getRemoteConnection();
            remoteStmt = remoteConn.createStatement();

            //查找下周对应课程计划的汇总信息
            Integer recordCount = extractSummary(remoteStmt, term.getTermName(), String.valueOf(useWeek));
            tSyncLog.setRecordCount(recordCount == null ? "" : recordCount.toString());
            if (recordCount == null) {
                throw new RuntimeException("Warning：没有找到课程计划总体信息");
            } else if (recordCount.intValue() == 0) {
            } else {
                //查找下周所有的课程计划
                List result = extractData(remoteStmt);
                if (recordCount.intValue() != result.size()) {
                    throw new RuntimeException("Error：课程计划总体信息中课程计划总数与实际取得课程计划总数不符");
                }
                tSyncLog.setRemark("同步课程计划成功");
                //如果是预览课程计划，那么先删掉历史预览数据
                if (SYNC_PREVIEW.equals(status)) {
                    deletePreviewData(localConn);
                }
                saveData(localConn, result, tSyncLog, status);
//                syncService.saveData(result, tSyncLog, status);
            }
        } catch (Exception e) {
            _log.error("同步课程计划失败：");
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
     * 获取下周一在本学期中对应的周次
     *
     * @param termBeginDate 学期开始日期,yyyyMMdd
     * @return 如果下周一比学期开始日期小，那么返回-1
     */
    private static long getNextWeek(String termBeginDate) {
        Date nextMonday = DateUtilExtend.getNextMonday();
        return DateUtilExtend.getUseWeek(termBeginDate, nextMonday);
    }

    /**
     * 获取当前所处学期信息
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
            throw new RuntimeException("获取学期失败：" + e.getMessage());
        } finally {
            close(rs);
            close(stmt);
        }
    }

    /**
     * 保证result和log的写入在同一个事物中
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
            _log.error("保存同步日志失败：" + e.getMessage());
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
            throw new RuntimeException("提取课程计划总体信息失败：" + e.getMessage());
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
            throw new RuntimeException("提取课程计划详细数据失败：" + e.getMessage());
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
