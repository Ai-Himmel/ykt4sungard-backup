package com.sungard.service;

import com.sungard.bean.Payrecord;
import com.sungard.util.DBUtil;
import org.apache.commons.lang.StringUtils;
import org.apache.log4j.Logger;

import java.sql.Connection;
import java.sql.PreparedStatement;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-22
 */
public class PayrecordService {
    private static final Logger logger = Logger.getLogger(PayrecordService.class);

    /**
     * 保存办证大厅收费记录
     *
     * @param payrecord .
     */
    public static boolean savePayrecord(Payrecord payrecord) {
        boolean success = false;
        Connection conn = null;
        PreparedStatement pstmt = null;
        try {
            conn = DBUtil.getConnection();
            if (conn == null) {
                throw new RuntimeException("can't get connection");
            }
            String sql = "insert into ykt_cur.T_CERTIFICATERECORD(cardno,stuempno,custname,medicine_fee,dressing_fee,injection_fee,vaccine_fee,other_fee,total_fee,operator,trans_date,trans_time,refno,mac,trans_type,classname) values (?,?,?,?,?,?,?,?,?,?,?,?,?,?,?,?)";
            pstmt = conn.prepareStatement(sql);
            pstmt.setInt(1, payrecord.getCardno().intValue());
            pstmt.setString(2, payrecord.getStuempno());
            pstmt.setString(3, payrecord.getCustname());
            pstmt.setDouble(4, payrecord.getMedicineFee());
            pstmt.setDouble(5, payrecord.getDressingFee());
            pstmt.setDouble(6, payrecord.getInjectionFee());
            pstmt.setDouble(7, payrecord.getVaccineFee());
            pstmt.setDouble(8, payrecord.getOtherFee());
            pstmt.setDouble(9, payrecord.getTotalFee());
            pstmt.setString(10, payrecord.getOperator());
            pstmt.setString(11, payrecord.getTransDate());
            pstmt.setString(12, payrecord.getTransTime());
            pstmt.setString(13, payrecord.getRefno());
            pstmt.setString(14, payrecord.getMac());
            pstmt.setString(15, payrecord.getTransType());
            pstmt.setString(16, payrecord.getClassName());
            pstmt.execute();
            success = true;
        } catch (SQLException e) {
            logger.error(e);
        } finally {
            DBUtil.closeStatement(pstmt);
            DBUtil.closeConnection(conn);
        }
        return success;
    }

    /**
     * 查找办证大厅收费记录明细
     *
     * @param stuempno  学工号
     * @param custname  姓名
     * @param startDate 开始日期
     * @param endDate   结束日期
     * @return .
     */
    public static List<Payrecord> findPayrecordDetail(String stuempno, String custname, String startDate, String endDate) {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        List<Payrecord> result = new ArrayList<Payrecord>();
        try {
            conn = DBUtil.getConnection();
            stmt = conn.createStatement();
            String sql = "select * from ykt_cur.T_CERTIFICATERECORD";
            sql += " where trans_date>='" + startDate + "' and trans_date<='" + endDate + "'";
            if (StringUtils.isNotBlank(stuempno)) {
                sql += " and stuempno like '%" + stuempno + "%'";
            }
            if (StringUtils.isNotBlank(custname)) {
                sql += " and custname like '%" + custname + "%'";
            }
            sql += " order by trans_date desc,refno desc";
            logger.debug("find T_CERTIFICATERECORD:" + sql);
            rs = stmt.executeQuery(sql);
            while (rs.next()) {
                Payrecord payrecord = new Payrecord();
                payrecord.setCardno(rs.getInt("cardno"));
                payrecord.setStuempno(rs.getString("stuempno"));
                payrecord.setCustname(rs.getString("custname"));
                payrecord.setMedicineFee(Double.valueOf(rs.getString("medicine_fee")));
                payrecord.setDressingFee(Double.valueOf(rs.getString("dressing_fee")));
                payrecord.setInjectionFee(Double.valueOf(rs.getString("injection_fee")));
                payrecord.setVaccineFee(Double.valueOf(rs.getString("vaccine_fee")));
                payrecord.setOtherFee(Double.valueOf(rs.getString("other_fee")));
                payrecord.setTotalFee(Double.valueOf(rs.getString("total_fee")));
                payrecord.setOperator(rs.getString("operator"));
                payrecord.setTransDate(rs.getString("trans_date"));
                payrecord.setTransTime(rs.getString("trans_time"));
                payrecord.setRefno(rs.getString("refno"));
                payrecord.setMac(rs.getString("mac"));
                payrecord.setTransType(rs.getString("trans_type"));
                payrecord.setClassName(rs.getString("classname"));
                result.add(payrecord);
            }
        } catch (Exception e) {
            logger.error(e);
            throw new RuntimeException(e.getMessage());
        } finally {
            DBUtil.closeResultSet(rs);
            DBUtil.closeStatement(stmt);
            DBUtil.closeConnection(conn);
        }
        return result;
    }

    /**
     * 统计办证大厅收费记录
     *
     * @param startDate 开始日期
     * @param endDate   结束日期
     * @return .
     */
    public static List<Map> findPayrecordReport(String startDate, String endDate) {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        List<Map> result = new ArrayList<Map>();
        try {
            conn = DBUtil.getConnection();
            stmt = conn.createStatement();
            String sql = "select trans_date,count(distinct stuempno) as person_number,count(stuempno) as pay_number,sum(medicine_fee) as medicine_fee,sum(dressing_fee) as dressing_fee,sum(injection_fee) as injection_fee,sum(vaccine_fee) as vaccine_fee,sum(other_fee) as other_fee,sum(total_fee) as total_fee from ykt_cur.T_CERTIFICATERECORD";
            sql += " where trans_date>='" + startDate + "' and trans_date<='" + endDate + "'";
            sql += " group by trans_date order by trans_date asc";
            logger.debug("find T_CERTIFICATERECORD:" + sql);
            rs = stmt.executeQuery(sql);
            while (rs.next()) {
                Map row = new HashMap();
                row.put("transDate", rs.getString("trans_date"));
                row.put("personNumber", rs.getInt("person_number"));
                row.put("payNumber", rs.getInt("pay_number"));
                row.put("medicineFee", Double.valueOf(rs.getString("medicine_fee")));
                row.put("dressingFee", Double.valueOf(rs.getString("dressing_fee")));
                row.put("injectionFee", Double.valueOf(rs.getString("injection_fee")));
                row.put("vaccineFee", Double.valueOf(rs.getString("vaccine_fee")));
                row.put("otherFee", Double.valueOf(rs.getString("other_fee")));
                row.put("totalFee", Double.valueOf(rs.getString("total_fee")));
                result.add(row);
            }
        } catch (Exception e) {
            logger.error(e);
            throw new RuntimeException(e.getMessage());
        } finally {
            DBUtil.closeResultSet(rs);
            DBUtil.closeStatement(stmt);
            DBUtil.closeConnection(conn);
        }
        return result;
    }

    /**
     * 查找班级名称
     *
     * @param stuempno 学工号
     * @return .
     */
    public static String findClassName(String stuempno) {
        Connection conn = null;
        Statement stmt = null;
        ResultSet rs = null;
        String classname = "";
        try {
            conn = DBUtil.getConnection();
            stmt = conn.createStatement();
            String sql = "select classname from ykt_cur.T_CUSTOMER where stuempno='" + stuempno + "'";
            logger.debug("find CLASSNAME:" + sql);
            rs = stmt.executeQuery(sql);
            if (rs.next()) {
                classname = rs.getString("classname");
                if (classname == null) {
                    classname = "";
                }
            }
        } catch (Exception e) {
            logger.error(e);
        } finally {
            DBUtil.closeResultSet(rs);
            DBUtil.closeStatement(stmt);
            DBUtil.closeConnection(conn);
        }
        return classname;
    }
}
