package org.king.check.service.impl;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.Date;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;
import javax.servlet.http.HttpSession;

import org.apache.commons.lang.StringUtils;
import org.apache.poi.hssf.usermodel.HSSFCell;
import org.apache.poi.hssf.usermodel.HSSFCellStyle;
import org.apache.poi.hssf.usermodel.HSSFHeader;
import org.apache.poi.hssf.usermodel.HSSFRichTextString;
import org.apache.poi.hssf.usermodel.HSSFRow;
import org.apache.poi.hssf.usermodel.HSSFSheet;
import org.apache.poi.hssf.usermodel.HSSFWorkbook;
import org.apache.poi.hssf.util.Region;
import org.king.check.Constants;
import org.king.check.config.CommonConfig;
import org.king.check.service.SysService;
import org.king.check.util.DateUtilExtend;
import org.king.check.util.StringUtil;
import org.king.framework.util.MyUtils;
import org.springframework.jdbc.core.JdbcTemplate;

public class SysServiceImpl implements SysService {
    //private static final Log log = LogFactory.getLog(SysServiceImpl.class);

    private JdbcTemplate jdbcTemplate;

    public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
        this.jdbcTemplate = jdbcTemplate;
    }

    /*
     * 取得部门名称
     */

    public String getDeptname(String deptId) throws Exception {
        String deptname = "";
        if (deptId == null || "".equals(deptId)) {
            return deptname;
        }
        StringBuffer sql = new StringBuffer(1024);
        sql.append(" select  dept_name  from    ykt_ck.department where dept_Id='" + deptId + "'");
        List deptList = jdbcTemplate.queryForList(sql.toString());
        if (deptList != null && deptList.size() > 0) {
            Map deptMap = (Map) deptList.get(0);
            deptname = deptMap.get("dept_name").toString();
        }
        return deptname;
    }

    /*
      * 取得所有的部门数量
      */

    public int getDeptCount() throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select count(*)num from ykt_ck.department t");
        List deptList = jdbcTemplate.queryForList(sql.toString());
        if (deptList.isEmpty()) {
            return 0;
        } else {
            Map deptCount = (Map) deptList.get(0);
            return Integer.parseInt(deptCount.get("num").toString());
        }

    }

    /**
     * 根据登录帐号取得该帐号说拥有的部门操作权限数量
     *
     * @param Account
     * @return
     * @throws Exception
     */
    public int getDeptCountByAccount(String Account) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select count(*)num from ykt_ck.t_oper_limit t where oper_id=?");
        List deptList = jdbcTemplate.queryForList(sql.toString(), new Object[]{Account});
        if (deptList.isEmpty()) {
            return 0;
        } else {
            Map deptCount = (Map) deptList.get(0);
            return Integer.parseInt(deptCount.get("num").toString());
        }

    }


    public List getCheckTypeInfo() throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select type_id typeId,type_name typeName from YKT_CK.T_CHECKTYPE");
        List checkTypeInfo = jdbcTemplate.queryForList(sql.toString());
        return checkTypeInfo;
    }

    public List getCardStatus() throws Exception {
        String sql = "select dict.DICT_VALUE  value , dict.DICT_CAPTION caption from " +
                "YKT_CUR.T_PIF_DICTIONARY dict " +
                "where dict.DICT_NO=17";

        List cardStatusList = jdbcTemplate.queryForList(sql);
        return cardStatusList;
    }

    public List getCheckattType() throws Exception {
        String sql = "select dict.DICT_VALUE  value , dict.DICT_CAPTION caption from " +
                "YKT_CUR.T_PIF_DICTIONARY dict " +
                "where dict.DICT_NO=1200";

        List checkattList = jdbcTemplate.queryForList(sql);
        return checkattList;
    }

    public List getPersonType() throws Exception {
        String sql = "select cut.CUT_TYPE type , cut.TYPE_NAME name from " +
                "YKT_CUR.T_CIF_CUTTYPEFEE cut ";

        List personTypeList = jdbcTemplate.queryForList(sql);
        return personTypeList;
    }

    public List getCardType() throws Exception {
        String sql = "select dict.DICT_VALUE value , dict.DICT_CAPTION caption from " +
                "YKT_CUR.T_PIF_DICTIONARY dict " +
                "where dict.DICT_NO=18";

        List cardTypeList = jdbcTemplate.queryForList(sql);
        return cardTypeList;
    }

    public List getDepartList() throws Exception {
        String sql = "select dept.DEPT_CODE dept_code , dept.DEPT_NAME dept_name from YKT_CUR.T_CIF_DEPT dept" +
                " where dept.PARENTDEPT_CODE!='NA' and DEPT_LEVEL=1 AND dept.PARENTDEPT_CODE is not null";

        List departmentList = jdbcTemplate.queryForList(sql);

        return departmentList;
    }

    /**
     * hanjiwei modify it 20061030
     */
    public List search(Map filter) throws Exception {
        StringBuffer sql = new StringBuffer();
        sql.append("select cust.CUT_NAME cust_name,cust.CUT_ID cust_id,")
                .append(" cust.STUEMP_NO stuemp_no,ctype.TYPE_NAME type_name ")
                .append(" from  YKT_CUR.T_CIF_CUSTOMER cust ")
                .append(" left join YKT_CUR.T_CIF_DEPT dept on dept.DEPT_CODE=cust.CLASSDEPT_NO")
                .append(" left join YKT_CUR.T_CIF_CUTTYPEFEE ctype on  ctype.CUT_TYPE=cust.CUT_TYPE")
                .append(" where (cust.STUEMP_NO is not null or cust.STUEMP_NO<>'')")
                .append(" and cust.CUT_ID not in (select CUST_ID from YKT_CK.T_CLERKINFO)");
        if (StringUtils.isNotEmpty((String) filter.get("personCode"))) {
            sql.append(" and cust.STUEMP_NO like '%" + (String) filter.get("personCode") + "%' ");
        }
        if ((String) filter.get("cutType") != null && !((String) filter.get("cutType")).equals("all")) {
            sql.append(" and cust.cut_Type=" + (String) filter.get("cutType"));
        }
        if (StringUtils.isNotEmpty((String) filter.get("personName"))) {
            sql.append(" and cust.CUT_NAME like '%" + (String) filter.get("personName") + "%' ");
        }
        if ((String) filter.get("department") != null && !((String) filter.get("department")).equals("all")) {
            sql.append(" and dept.DEPT_CODE='" + (String) filter.get("department") + "'");
        }
        System.out.println(sql.toString());

        List searchRes = jdbcTemplate.queryForList(sql.toString());
        return searchRes;
    }

    public String getCustomerNameByCustomerId(Integer customerId) throws Exception {
        String sql = "select customer.CUT_NAME  name from YKT_CUR.T_CIF_CUSTOMER customer where customer.CUT_ID=?";

        List tempList;
        String customerName = null;

        tempList = jdbcTemplate.queryForList(sql, new Object[]{customerId});
        if (!tempList.isEmpty()) {
            Map tmpMap = (Map) tempList.get(0);
            customerName = (String) tmpMap.get("name");
        }
        return customerName;
    }

    public String getIfOffice(int custId) throws Exception {
        String sql = "select CUST_ID, IFOFFICE from YKT_CK.T_CLERKINFO where CUST_ID=" + custId;

        List tempList = jdbcTemplate.queryForList(sql);
        String ifOffice = null;

        if (!tempList.isEmpty()) {
            Map tmpMap = (Map) tempList.get(0);
            ifOffice = (String) tmpMap.get("IFOFFICE");
        }
        return ifOffice;
    }

    /*
      *  (non-Javadoc)
      * @see org.king.check.service.SysService#isExistDate(java.util.Map)
      * 检查查询的表中时间段是否已经存在
      */

    public List isExistDate(Map filter) throws Exception {
        return null;
    }

    public List getDeptList() throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select dept.DEPT_ID deptId,dept.DEPT_NAME deptName from YKT_CK.DEPARTMENT dept ")
                .append("where dept.dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
                .append("select distinct dept_parentid from ykt_ck.DEPARTMENT))");
        List deptList = jdbcTemplate.queryForList(sql.toString());
        return deptList;
    }

    public String getCheckTypeName(String typeId) {
        if ("".equals(typeId)) {
            return "";
        }
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select TYPE_ID,TYPE_NAME from YKT_CK.T_CHECKTYPE ")
                .append("where TYPE_ID=?");
        List deptList = jdbcTemplate.queryForList(sql.toString(), new Object[]{typeId});
        if (deptList.size() != 0) {
            Map deptMap = (Map) deptList.get(0);
            return deptMap.get("TYPE_NAME").toString();
        } else {
            return "";
        }
    }
    /*
      * 取得部门名称 (non-Javadoc)
      * @see org.king.check.service.SysService#getDeptName(java.lang.String)
      */

    public String getDeptName(String deptId) {
        if ("".equals(deptId)) {
            return "";
        }
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select DEPT_ID,DEPT_NAME from YKT_CK.DEPARTMENT ")
                .append("where DEPT_ID='").append(deptId).append("'");
        List deptList = jdbcTemplate.queryForList(sql.toString());
        if (deptList.size() != 0) {
            Map deptMap = (Map) deptList.get(0);
            return deptMap.get("DEPT_NAME").toString();
        } else {
            return "";
        }
    }

    public List getDeptList(String operId) {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
                .append(" where dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
                .append(" select distinct dept_parentid from ykt_ck.DEPARTMENT))")
                .append(" and  dept_id in (select distinct DEPT_ID from YKT_CK.T_OPER_LIMIT")
                .append(" where oper_id=?)");
        //System.out.println(sql);
        List deptList = jdbcTemplate.queryForList(sql.toString(), new Object[]{StringUtil.getStringIfNull(operId)});
        return deptList;
    }

    public String getDeptNameStr(List deptList) throws Exception {
        Iterator iter = deptList.iterator();
        StringBuffer deptStr = new StringBuffer(512);
        while (iter.hasNext()) {
            Map deptMap = (Map) iter.next();
            if (iter.hasNext()) {
                deptStr.append(deptMap.get("deptName").toString()).append(",");
            } else {
                deptStr.append(deptMap.get("deptName").toString());
            }
        }
        return null;

    }


    public String getDeptStr(List deptList) throws Exception {
        Iterator iter = deptList.iterator();
        StringBuffer deptStr = new StringBuffer(512);
        while (iter.hasNext()) {
            Map deptMap = (Map) iter.next();
            if (iter.hasNext()) {
                deptStr.append(deptMap.get("deptId").toString()).append(",");
            } else {
                deptStr.append(deptMap.get("deptId").toString());
            }
        }
        return null;

    }

    public List getDeptInfo(String deptId) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
                .append(" where dept_id =?");
        List deptInfo = jdbcTemplate.queryForList(sql.toString(), new Object[]{deptId});
        return deptInfo;
    }

    public Integer getCardNo(Integer custId) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        Integer cardNo = null;
        sql.append("select CARD_ID cardNo from YKT_CUR.T_PIF_CARD")
                .append(" where COSUMER_ID=" + custId + " and STATE_ID='1000'");
        List cardList = jdbcTemplate.queryForList(sql.toString());
        if (!cardList.isEmpty()) {
            Map tmpMap = (Map) cardList.get(0);
            cardNo = (Integer) tmpMap.get("cardNo");
        }
        return cardNo;
    }

    public List getLeaveList() throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        if ("ORACLE".equals(Constants.DBNAME)) {
            sql.append("select DICT_VALUE, DICT_CAPTION")
                    .append(" from YKT_CUR.T_PIF_DICTIONARY")
                    .append(" where dict_no=1210 order by to_number(dict_value)");
        } else if ("DB2".equals(Constants.DBNAME)) {
            sql.append("select DICT_VALUE, DICT_CAPTION")
                    .append(" from YKT_CUR.T_PIF_DICTIONARY")
                    .append(" where dict_no=1210 order by int(dict_value)");
        }
        List leaveTypeList = jdbcTemplate.queryForList(sql.toString());
        return leaveTypeList;
    }

    public String getOperName(String operId) {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select person_name from ykt_ck.usr_person")
                .append(" where id='" + operId + "'");
        List operList = jdbcTemplate.queryForList(sql.toString());
        String operName = "";
        if (!operList.isEmpty()) {
            Map tmpMap = (Map) operList.get(0);
            operName = (String) tmpMap.get("person_name");
        }
        return operName;
    }

    public String getLeaveTypeName(String leaveTypeId) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY")
                .append(" where dict_no=1210 and DICT_VALUE='" + leaveTypeId + "'");
        List operList = jdbcTemplate.queryForList(sql.toString());
        String leaveTypeName = "";
        if (!operList.isEmpty()) {
            Map tmpMap = (Map) operList.get(0);
            leaveTypeName = (String) tmpMap.get("DICT_CAPTION");
        }
        return leaveTypeName;
    }

    public int getCustIdByStuempNo(String stuempNo) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select CUT_ID from YKT_CUR.T_CIF_CUSTOMER")
                .append(" where STUEMP_NO='" + stuempNo + "'");
        List operList = jdbcTemplate.queryForList(sql.toString());
        int custId = 0;
        if (!operList.isEmpty()) {
            Map tmpMap = (Map) operList.get(0);
            custId = Integer.parseInt(tmpMap.get("CUT_ID").toString());
        }
        return custId;
    }

    public Map getCustInfoByCustId(int custId) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select CUT_NAME,STUEMP_NO from YKT_CUR.T_CIF_CUSTOMER")
                .append(" where CUT_ID=" + custId);
        System.out.println(sql.toString());
        List custInfo = jdbcTemplate.queryForList(sql.toString());
        System.out.println("查询人员信息表YKT_CUR.T_CIF_CUSTOMER记录--" + new Integer(custInfo.size()));
        Map custMap = new HashMap();
        if (custInfo.size() > 0) {
            Map tempMap = (Map) custInfo.get(0);
            custMap.put("CUT_NAME", tempMap.get("CUT_NAME"));
            custMap.put("STUEMP_NO", tempMap.get("STUEMP_NO"));
            return custMap;
        } else {
            custMap.put("CUT_NAME", "");
            custMap.put("STUEMP_NO", "");
            return custMap;
        }
    }

    public List getCustInfo(Map filter) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select cust.CUT_ID, cust.CUT_NAME,  cust.STUEMP_NO,dept.DEPT_ID,dept.DEPT_NAME")
                .append(" from YKT_CUR.T_CIF_CUSTOMER cust")
                .append(" left join YKT_CK.T_CLERKINFO clerk on cust.CUT_ID=clerk.CUST_ID")
                .append(" left join YKT_CK.DEPARTMENT dept on clerk.DEPT_ID=dept.DEPT_ID")
                .append(" where cust.STUEMP_NO='").append(filter.get("stuempNo").toString()).append("'");
        List custList = jdbcTemplate.queryForList(sql.toString());
        return custList;
    }

    public String getAccountIdByStuempNo(String stuempNo) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select ID,ACCOUNT_NAME from YKT_CK.USR_ACCOUNT")
                .append(" where ACCOUNT_NAME='" + stuempNo + "'");
        Map custInfo = jdbcTemplate.queryForMap(sql.toString());
        return custInfo.get("ID").toString();
    }

    public String ifAgree(String agreeId) {
        if ("0".equals(agreeId)) {
            return CommonConfig.NOTAGREE;
        } else if ("1".equals(agreeId)) {
            return CommonConfig.AGREE;
        } else {
            return "";
        }
    }

    public String ifCheck(String checkId) {
        if ("0".equals(checkId)) {
            return CommonConfig.NOTCHECK;
        } else if ("1".equals(checkId)) {
            return CommonConfig.CHECK;
        } else {
            return "";
        }
    }

    /**
     * 根据考勤人员编号取得部门编号
     * hanjiwei add it 20071030
     *
     * @param deptId
     * @return
     * @throws Exception
     */
    public Map getDeptInfoBySeriId(int seriId) {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select t.serial_id,t.cust_id,info.dept_id from")
                .append(" ykt_ck.t_attserial_record t,ykt_ck.t_clerkinfo info")
                .append(" where info.cust_id=t.cust_id and t.serial_id=?");
        //.append(seriId);
        Map custList = jdbcTemplate.queryForMap(sql.toString(), new Object[]{new Integer(seriId)});
        return custList;
    }

    /**
     * 根据手工考勤流水号取得考勤人员的客户号和客户所在的部门
     * hanjiwei add it 20071030
     *
     * @param deptId
     * @return
     * @throws Exception
     */
    public Map getDeptInfo(int custId) {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select cust_id,dept_id from ykt_ck.t_clerkinfo")
                .append(" where cust_id=?");
        //.append(custId);
        Map custList = jdbcTemplate.queryForMap(sql.toString(), new Object[]{new Integer(custId)});
        return custList;
    }


    /**
     * 根据部门编号取得考勤人员名单详细信息
     * hanjiwei add it 20071030
     *
     * @param deptId
     * @return
     * @throws Exception
     */
    public List getClerkInfo(String deptId) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select t.cust_id, cust.stuemp_no,cust.cut_name,dept.dept_name,cap.dict_caption,")
                .append(" cap.dict_value from ykt_ck.t_clerkinfo t,ykt_cur.t_cif_customer cust,")
                .append(" ykt_ck.department dept,ykt_cur.t_pif_dictionary cap")
                .append(" where t.cust_id=cust.cut_id and t.dept_id=dept.dept_id and")
                //.append(" where t.cust_id=cust.cut_id and t.dept_id=dept.dept_id and cust.stuemp_no='003356' and")
                .append(" t.ifoffice=cap.dict_value and cap.dict_no=1200");
        if (!"".equals(deptId)) {
            sql.append(" and t.dept_id in ('").append(deptId).append("')");
        }
        sql.append(" order by dept.dept_name,t.dept_id");

        List custList = jdbcTemplate.queryForList(sql.toString());
        /*
          if (!"".equals(deptId)){
              custList=jdbcTemplate.queryForList(sql.toString(),new Object[]{deptId});
          }else{
              custList=jdbcTemplate.queryForList(sql.toString());
          }*/
        return custList;
    }

    /**
     * 取得手工考勤记录
     */
    public int getManCheck(String custId, String checkDate) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select count(*)as num from ykt_ck.t_attserial_record t")
                .append(" where cust_id=?")
                        //.append(Integer.parseInt(custId))
                .append(" and att_date=?")
                .append(" and serial_id >0 ")
                .append(" and  cust_id not in ")
                .append(" (select cust_id from ykt_ck.t_attserial ")
                .append("  where cust_id=? and  att_date =?)");

        //.append(checkDate).append("'");
        int custList = jdbcTemplate.queryForInt(sql.toString(), new Object[]{Integer.valueOf(custId), checkDate, Integer.valueOf(custId), checkDate});
        return custList;
    }

    public int getManCheckWeb(String custId, String checkDate) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select count(*)as num from ykt_ck.t_attserial_record t")
                .append(" where cust_id=?")
                        //.append(Integer.parseInt(custId))
                .append(" and att_date=?")
                .append(" and serial_id < 0 ")
                .append(" and  cust_id not in ")
                .append(" (select cust_id from ykt_ck.t_attserial_record ")
                .append(" where cust_id=? and  att_date =? and serial_id>0) ")
                .append(" and cust_id not in  ")
                .append(" ( select cust_id from ykt_ck.t_attserial ")
                .append(" where  cust_id=? and  att_date =?) ");
        //.append(checkDate).append("'");
        int custList = jdbcTemplate.queryForInt(sql.toString(), new Object[]{Integer.valueOf(custId), checkDate, Integer.valueOf(custId), checkDate, Integer.valueOf(custId), checkDate});
        return custList;
    }

    /**
     * 取得打卡考勤记录
     */
    public int getCardCheck(String custId, String checkDate) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select count(*)as num from ykt_ck.t_attserial t")
                .append(" where status='1' and cust_id=?")
                        //.append(Integer.parseInt(custId))
                .append(" and att_date=?");
        //.append(checkDate).append("'");
        int custList = jdbcTemplate.queryForInt(sql.toString(), new Object[]{Integer.valueOf(custId), checkDate});
        return custList;
    }

    /**
     * 取得打卡后，被取消的考勤记录
     */
    public int getCardCheckCancel(String custId, String checkDate) throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select count(*)as num from ykt_ck.t_attserial t")
                .append(" where status='0' and cust_id=?")
                        //.append(Integer.parseInt(custId))
                .append(" and att_date=?");
        //.append(checkDate).append("'");
        int custList = jdbcTemplate.queryForInt(sql.toString(), new Object[]{Integer.valueOf(custId), checkDate});
        return custList;
    }


    public String getReportRecord(String deptId, String statMonth) {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select report_month,dept_id,status from ykt_ck.t_makereportrecord t")
                .append(" where dept_Id=?")
                .append(" and report_month=?");
        List custList = jdbcTemplate.queryForList(sql.toString(), new Object[]{deptId, statMonth});
        String status = "0";
        if (custList.size() > 0) {
            Map custMap = (Map) custList.get(0);
            status = custMap.get("status").toString();
        }
        return status;
    }


    /*
      * 根据月份取得每天所对应的周 (non-Javadoc)
      * @see org.king.check.service.SysService#getWeekByDate(java.lang.String)
      */

    public List getWeekByDate(String statMonth) {
        if ((statMonth == null) || ("".endsWith(statMonth))) {
            return null;
        } else {
            List returnList = new ArrayList();

            for (int i = 1; i < DateUtilExtend.getDaysByMonth(statMonth) + 1; i++) {
                Map workTime = new HashMap();
                StringBuffer statDate = new StringBuffer(8);
                statDate.append(statMonth.substring(0, 4))
                        .append(statMonth.substring(5, 7))
                        .append(formatString(String.valueOf(i)));
                workTime.put("date", formatString(String.valueOf(i)));
                workTime.put("week", DateUtilExtend.getWeekByDate(statDate.toString()));
                returnList.add(workTime);
            }
            return returnList;
        }
    }

    /**
     * 取得一个月份的开始日期和结束日期
     *
     * @param statMonth
     * @return
     */
    public Map getBeginAndEndDate(String statMonth) {
        Map dateMap = new HashMap();
        StringBuffer beginDate = new StringBuffer(8);
        beginDate.append(statMonth.substring(0, 4))
                .append(statMonth.substring(5, 7))
                .append(formatString(String.valueOf(1)));
        dateMap.put("beginDate", beginDate.toString());

        int dateNum = DateUtilExtend.getDaysByMonth(statMonth);
        StringBuffer endDate = new StringBuffer(8);
        endDate.append(statMonth.substring(0, 4))
                .append(statMonth.substring(5, 7))
                .append(formatString(String.valueOf(dateNum)));
        dateMap.put("endDate", endDate.toString());
        return dateMap;
    }
    /*
      *  (non-Javadoc)
      * @see org.king.check.service.SysService#getWeekByDate(java.lang.String)
      */

    public List getWeekByDate(String startDate, String endDate) {
        if ((startDate == null) || (endDate == null)) {
            return null;
        } else {
            List returnList = new ArrayList();
            String checkDate = startDate;
            while (DateUtilExtend.diffDate(endDate, checkDate) <= 0) {
                Map workTime = new HashMap();
                workTime.put("date", checkDate);
                workTime.put("week", "星期" + DateUtilExtend.getWeekByDate(checkDate));
                returnList.add(workTime);
                checkDate = DateUtilExtend.addDate2(checkDate, 1);
            }
            return returnList;
        }
    }

    public Map initCheckMap(String statMonth) {
        if ((statMonth == null) || ("".endsWith(statMonth))) {
            return null;
        } else {
            Map checkMap = new HashMap();
            checkMap.put("deptName", "");
            checkMap.put("stuempNo", "");
            checkMap.put("custName", "");
            checkMap.put("custType", "");
            for (int i = 1; i < DateUtilExtend.getDaysByMonth(statMonth) + 1; i++) {
                checkMap.put(formatString(String.valueOf(i)), formatString(String.valueOf(i)));
            }
            return checkMap;
        }
    }

    public Map getPatchDate(String statMonth) {
        Map dateMap = getBeginAndEndDate(statMonth);
        String beginDate = dateMap.get("beginDate").toString();
        String endDate = dateMap.get("endDate").toString();
        String patchBDate = "";//补助开始日期
        String patchEDate = "";//补助结束日期
        String week = DateUtilExtend.getWeekByDate(beginDate);
        String endWeek = DateUtilExtend.getWeekByDate(endDate);
        //boolean tempBool = false;
        //实际发补助的开始日期和结束日期
        if ("一".equals(week)) {
            patchBDate = beginDate;

        } else {
            int year = Integer.parseInt(statMonth.substring(0, 4));
            int weekNum = DateUtilExtend.getWeekNumOfYearDay(beginDate);
            Date[] ss = DateUtilExtend.getStartEnd(year, weekNum);
            patchBDate = DateUtilExtend.addDate2(DateUtilExtend.formatDate3(ss[0]), 1);
            //tempBool = true;
        }
        if ("日".equals(endWeek)) {
            patchEDate = endDate;
        } else {
            int year = Integer.parseInt(statMonth.substring(0, 4));
            int weekNum = DateUtilExtend.getWeekNumOfYearDay(endDate);//取得结束日期是当年的那个星期
            Date[] ss = DateUtilExtend.getStartEnd(year, weekNum);
            if (weekNum == 52) {//当年的最后一个星期
                patchEDate = DateUtilExtend.addDate2(DateUtilExtend.formatDate3(ss[1]), 1);
            } else {
                patchEDate = DateUtilExtend.formatDate3(ss[0]);
            }
        }
        Map patchDateMap = new HashMap();
        patchDateMap.put("beginDate", patchBDate);
        patchDateMap.put("endDate", patchEDate);
        return patchDateMap;
    }


    private int deleterow = 0;
    /*
      * 把生成的考勤记录导入到Excel
      * @see org.king.check.service.SysService#importReportToExcel(java.lang.String, java.lang.String, java.util.List)
      */
    /*public void importReportToExcel(
             String realPath,
             String deptId,
             String statMonth,
             List reportList,
             String operId,
             String finance) throws Exception{
         HSSFWorkbook wb = new HSSFWorkbook();
         HSSFSheet recordReport = wb.createSheet("recordReportSheet");

         HSSFHeader header = recordReport.getHeader();

         if ("1".equals(finance)){
             header.setCenter(HSSFHeader.font("Stencil-Normal", "Bold") +
                     HSSFHeader.fontSize((short) 12) + "考勤补贴计算报表");
         }else{
             header.setCenter(HSSFHeader.font("Stencil-Normal", "Bold") +
                     HSSFHeader.fontSize((short) 12) + "考勤签到记录明细");
         }


         HSSFCellStyle style = normalStl(wb);

         makeExcelTitle(statMonth,recordReport,style,deptId,finance);
         HSSFRow row = null;
         deleterow = 0;
         int rowId = 3;
         int cellRow = reportList.size()+3;
         Iterator reportIter = reportList.iterator();
         while (reportIter.hasNext()){
             Map reportMap = (Map)reportIter.next();

             //如果没有考勤记录，则把这行跳过去，不再显示
             if ("0".equals(reportMap.get("totMoney").toString())&&
                     "0".equals(reportMap.get("totNum").toString())){
                 deleterow++;
                 continue;
             }
             String deptName = reportMap.get("deptName").toString();
             String stuempNo = reportMap.get("stuempNo").toString();
             String custName = reportMap.get("custName").toString();
             String custType = reportMap.get("custType").toString();
             row = recordReport.createRow((short)rowId);
             rowId = rowId + 1;
             HSSFCell cell0 = row.createCell((short)0);
             HSSFCell cell1 = row.createCell((short)1);
             HSSFCell cell2 = row.createCell((short)2);
             HSSFCell cell3 = row.createCell((short)3);
             cell0.setCellType(HSSFCell.CELL_TYPE_STRING);
             cell1.setCellType(HSSFCell.CELL_TYPE_STRING);
             cell2.setCellType(HSSFCell.CELL_TYPE_STRING);
             cell3.setCellType(HSSFCell.CELL_TYPE_STRING);

             cell0.setCellValue(new HSSFRichTextString(deptName));
             cell1.setCellValue(new HSSFRichTextString(stuempNo));
             cell2.setCellValue(new HSSFRichTextString(custName));
             cell3.setCellValue(new HSSFRichTextString(custType));
             cell0.setCellStyle(style);
             cell1.setCellStyle(style);
             cell2.setCellStyle(style);
             cell3.setCellStyle(style);

             List dayList = getWeekByDate(statMonth);
             Iterator dayIter = dayList.iterator();
             while (dayIter.hasNext()){
                 Map dayMap = (Map)dayIter.next();
                 int dayId = Integer.parseInt(dayMap.get("date").toString())+3;
                 recordReport.setColumnWidth((short)dayId,(short)700);
                 HSSFCell cell = row.createCell((short)dayId);
                 cell.setCellType(HSSFCell.CELL_TYPE_STRING);

                 cell.setCellValue(new HSSFRichTextString(reportMap.get(dayMap.get("date").toString()).toString()));
                 cell.setCellStyle(style);
             }
             recordReport.setColumnWidth((short)(short)(dayList.size()+4),(short)1200);
             HSSFCell cell4 = row.createCell((short)(dayList.size()+4));
             cell4.setCellType(HSSFCell.CELL_TYPE_STRING);

             cell4.setCellValue(new HSSFRichTextString(reportMap.get("totNum").toString()));
             cell4.setCellStyle(style);

             recordReport.setColumnWidth((short)(short)(dayList.size()+5),(short)1200);
             HSSFCell cell5 = row.createCell((short)(dayList.size()+5));
             cell4.setCellType(HSSFCell.CELL_TYPE_STRING);
             if ("1".equals(finance)){
                 cell5.setCellValue(new HSSFRichTextString(reportMap.get("totMoney").toString()));
             }else{
                 cell5.setCellValue(new HSSFRichTextString(" "));
             }
             cell5.setCellStyle(style);
         }

         //生成Excel制表信息
         makeExcelBottom(recordReport,operId,cellRow,statMonth);

         String statDate = statMonth.substring(0,4)+statMonth.substring(5,7);
         String loadFile = "";
         String excelName = "";

         if ("1".equals(finance)){
             excelName = "checkRecordReportFinance.xls";
         }else{
             excelName = "checkRecordReport.xls";
         }

         if ("".equals(deptId)){
             loadFile = realPath+"/downloadfile/"+"0"+statDate+excelName;
         }else{
             loadFile = realPath+"/downloadfile/"+deptId+statDate+excelName;
         }
         FileOutputStream fileOut = new FileOutputStream(loadFile);
         wb.write(fileOut);
         fileOut.close();
     }*/

    public void importReportToExcel(
            String realPath,
            String deptId,
            String statMonth,
            List reportList,
            String operId,
            String finance) throws Exception {
        HSSFWorkbook wb = new HSSFWorkbook();
        HSSFSheet recordReport = wb.createSheet("recordReportSheet");

        HSSFHeader header = recordReport.getHeader();

        if ("1".equals(finance)) {
            header.setCenter(HSSFHeader.font("Stencil-Normal", "Bold") +
                    HSSFHeader.fontSize((short) 12) + "考勤补贴计算报表");
        } else {
            header.setCenter(HSSFHeader.font("Stencil-Normal", "Bold") +
                    HSSFHeader.fontSize((short) 12) + "考勤签到记录明细");
        }
        try {

            HSSFCellStyle style = normalStl(wb);

            makeExcelTitle(statMonth, recordReport, style, deptId, finance);
            HSSFRow row = null;
            deleterow = 0;
            int rowId = 3;
            int cellRow = reportList.size() + 3;
            Iterator reportIter = reportList.iterator();
            while (reportIter.hasNext()) {
                Map reportMap = (Map) reportIter.next();

                //如果没有考勤记录，则把这行跳过去，不再显示
                if ("0".equals(reportMap.get("bt").toString()) &&
                        "0".equals(reportMap.get("cs").toString())) {
                    deleterow++;
                    continue;
                }
                String deptName = reportMap.get("bm").toString();

                String stuempNo = reportMap.get("gh").toString();
                String custName = reportMap.get("xm").toString();
                String custType = reportMap.get("kqlb").toString();
                //System.out.println("===="+custName+"==");
                row = recordReport.createRow((short) rowId);
                rowId = rowId + 1;
                HSSFCell cell0 = row.createCell((short) 0);
                HSSFCell cell1 = row.createCell((short) 1);
                HSSFCell cell2 = row.createCell((short) 2);
                HSSFCell cell3 = row.createCell((short) 3);
                cell0.setCellType(HSSFCell.CELL_TYPE_STRING);
                cell1.setCellType(HSSFCell.CELL_TYPE_STRING);
                cell2.setCellType(HSSFCell.CELL_TYPE_STRING);
                cell3.setCellType(HSSFCell.CELL_TYPE_STRING);

                cell0.setCellValue(new HSSFRichTextString(deptName));
                cell1.setCellValue(new HSSFRichTextString(stuempNo));
                cell2.setCellValue(new HSSFRichTextString(custName));
                cell3.setCellValue(new HSSFRichTextString(custType));
                cell0.setCellStyle(style);
                cell1.setCellStyle(style);
                cell2.setCellStyle(style);
                cell3.setCellStyle(style);

                List dayList = getWeekByDate(statMonth);
                Iterator dayIter = dayList.iterator();
                while (dayIter.hasNext()) {
                    Map dayMap = (Map) dayIter.next();
                    int dayId = Integer.parseInt(dayMap.get("date").toString()) + 3;

                    recordReport.setColumnWidth((short) dayId, (short) 700);
                    HSSFCell cell = row.createCell((short) dayId);
                    cell.setCellType(HSSFCell.CELL_TYPE_STRING);


                    String dayValue = reportMap.get("day" + dayMap.get("date")) == null ? " " : reportMap.get("day" + dayMap.get("date").toString()).toString();

                    //	System.out.println("====="+dayValue+"===");
                    cell.setCellValue(new HSSFRichTextString(dayValue));
                    //System.out.println("===="+style+"==");
                    cell.setCellStyle(style);
                }
                recordReport.setColumnWidth((short) (short) (dayList.size() + 4), (short) 1200);
                HSSFCell cell4 = row.createCell((short) (dayList.size() + 4));
                cell4.setCellType(HSSFCell.CELL_TYPE_STRING);
                //System.out.println("====="+reportMap.get("cs").toString()+"次===");
                cell4.setCellValue(new HSSFRichTextString(reportMap.get("cs").toString()));
                cell4.setCellStyle(style);

                recordReport.setColumnWidth((short) (short) (dayList.size() + 5), (short) 1200);
                HSSFCell cell5 = row.createCell((short) (dayList.size() + 5));
                cell4.setCellType(HSSFCell.CELL_TYPE_STRING);
                if ("1".equals(finance)) {

                    cell5.setCellValue(new HSSFRichTextString(reportMap.get("bt").toString()));
                } else {
                    cell5.setCellValue(new HSSFRichTextString(" "));
                }
                cell5.setCellStyle(style);
            }

            //生成Excel制表信息
            makeExcelBottom(recordReport, operId, cellRow, statMonth);

            String statDate = statMonth.substring(0, 4) + statMonth.substring(5, 7);
            String loadFile = "";
            String excelName = "";

            if ("1".equals(finance)) {
                excelName = "checkRecordReportFinance.xls";
            } else {
                excelName = "checkRecordReport.xls";
            }

            if ("".equals(deptId)) {
                loadFile = realPath + "/downloadfile/" + 0 + statDate + excelName;
            } else {
                loadFile = realPath + "/downloadfile/" + deptId + statDate + excelName;
            }

            FileOutputStream fileOut = new FileOutputStream(loadFile);
            wb.write(fileOut);
            fileOut.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }


    /*
      * Excel表头设置
      */

    private void makeExcelTitle(
            String statMonth,
            HSSFSheet recordReport,
            HSSFCellStyle style,
            String deptname,
            String finance) {
        recordReport.setColumnWidth((short) 0, (short) 7000);
        recordReport.setColumnWidth((short) 1, (short) 2800);
        recordReport.setColumnWidth((short) 2, (short) 2800);
        recordReport.setColumnWidth((short) 3, (short) 2800);

        //HSSFRow row0 = recordReport.createRow((short)0);
        HSSFRow row1 = recordReport.createRow((short) 1);
        HSSFRow row2 = recordReport.createRow((short) 2);

        List dayList = getWeekByDate(statMonth);
        int dayNum = dayList.size();
        Iterator dayIter = dayList.iterator();
        while (dayIter.hasNext()) {
            Map dayMap = (Map) dayIter.next();
            int dayId = Integer.parseInt(dayMap.get("date").toString()) + 3;
            recordReport.setColumnWidth((short) dayId, (short) 700);
            HSSFCell cell22 = row1.createCell((short) dayId);
            cell22.setCellType(HSSFCell.CELL_TYPE_STRING);

            cell22.setCellValue(new HSSFRichTextString(dayMap.get("week").toString()));
            cell22.setCellStyle(style);
            HSSFCell cell33 = row2.createCell((short) dayId);
            cell33.setCellType(HSSFCell.CELL_TYPE_STRING);

            cell33.setCellValue(new HSSFRichTextString(dayMap.get("date").toString()));
            cell33.setCellStyle(style);
        }
        //设置表格宽度
        recordReport.setColumnWidth((short) (short) (dayNum + 4), (short) 1200);
        recordReport.setColumnWidth((short) (short) (dayNum + 5), (short) 1200);

        //合并表格
        recordReport.addMergedRegion(new Region(0, (short) 0, 2, (short) 0));
        recordReport.addMergedRegion(new Region(0, (short) 1, 2, (short) 1));
        recordReport.addMergedRegion(new Region(0, (short) 2, 2, (short) 2));
        recordReport.addMergedRegion(new Region(0, (short) 3, 2, (short) 3));
        recordReport.addMergedRegion(new Region(0, (short) 4, 0, (short) (dayNum + 3)));
        recordReport.addMergedRegion(new Region(0, (short) (dayNum + 4), 2, (short) 0));
        recordReport.addMergedRegion(new Region(0, (short) (dayNum + 5), 2, (short) 0));

        for (int i = 0; i < 4; i++) {
            HSSFRow row00 = recordReport.createRow(0);
            HSSFCell cell00 = row00.createCell((short) i);
            cell00.setCellType(HSSFCell.CELL_TYPE_STRING);

            cell00.setCellValue(new HSSFRichTextString(getText(i)));
            cell00.setCellStyle(style);
            recordReport.createRow(1).createCell((short) i).setCellStyle(style);
            recordReport.createRow(2).createCell((short) i).setCellStyle(style);
        }

        HSSFRow row66 = recordReport.createRow(0);

        HSSFCell cell66 = row66.createCell((short) 4);
        cell66.setCellType(HSSFCell.CELL_TYPE_STRING);
        if ("1".equals(finance)) {
            cell66.setCellValue(new HSSFRichTextString(deptname + statMonth + "考勤补贴计算报表"));
        } else {
            cell66.setCellValue(new HSSFRichTextString(deptname + statMonth + "月份明细考勤记录"));
        }
        cell66.setCellStyle(style);
        for (int i = 5; i < dayNum + 4; i++) {
            row66.createCell((short) i).setCellStyle(style);
        }

        HSSFRow row77 = recordReport.createRow(0);
        HSSFCell cell77 = row77.createCell((short) (dayNum + 4));
        cell77.setCellValue(new HSSFRichTextString("次数"));
        cell77.setCellStyle(style);
        recordReport.createRow(1).createCell((short) (dayNum + 4)).setCellStyle(style);
        recordReport.createRow(2).createCell((short) (dayNum + 4)).setCellStyle(style);

        HSSFRow row88 = recordReport.createRow(0);
        HSSFCell cell88 = row88.createCell((short) (dayNum + 5));
        cell88.setCellValue(new HSSFRichTextString("补贴(元)"));
        cell88.setCellStyle(style);
        recordReport.createRow(1).createCell((short) (dayNum + 5)).setCellStyle(style);
        recordReport.createRow(2).createCell((short) (dayNum + 5)).setCellStyle(style);

    }

    private void makeExcelBottom(HSSFSheet recordReport, String operId, int cellRow, String statDate) {
        HSSFRow rowM = recordReport.createRow(cellRow - deleterow + 1);

        Map patchDate = getPatchDate(statDate);
        String beginDate = patchDate.get("beginDate").toString();
        String endDate = patchDate.get("endDate").toString();
        StringBuffer memo = new StringBuffer(256);
        memo.append("说明：专职教师出勤补贴开始日期-").append(beginDate).append("  结束日期-").append(endDate);
        HSSFCell cellM = rowM.createCell((short) 0);
        cellM.setCellType(HSSFCell.CELL_TYPE_STRING);
        cellM.setCellValue(new HSSFRichTextString(memo.toString()));


        HSSFRow row = recordReport.createRow(cellRow - deleterow + 3);

        HSSFCell cell0 = row.createCell((short) 0);
        cell0.setCellType(HSSFCell.CELL_TYPE_STRING);
        cell0.setCellValue(new HSSFRichTextString("制表日期：" + DateUtilExtend.getNowDate()));

        HSSFCell cell1 = row.createCell((short) 1);
        cell1.setCellType(HSSFCell.CELL_TYPE_STRING);
        cell1.setCellValue(new HSSFRichTextString("制表人："));

        HSSFCell cell2 = row.createCell((short) 2);
        cell2.setCellType(HSSFCell.CELL_TYPE_STRING);
        cell2.setCellValue(new HSSFRichTextString(getOperName(operId)));

        HSSFCell cell3 = row.createCell((short) 3);
        cell3.setCellType(HSSFCell.CELL_TYPE_STRING);
        cell3.setCellValue(new HSSFRichTextString("部门负责人核实："));

        HSSFRow rowF = recordReport.createRow(cellRow - deleterow + 5);
        HSSFCell cellF = rowF.createCell((short) 0);
        cellF.setCellType(HSSFCell.CELL_TYPE_STRING);
        cellF.setCellValue(new HSSFRichTextString(" √ 表示打卡考勤，* 表示手工考勤 ，#表示无卡考勤 ，○ 表示无效打卡 "));


    }
    /*
      * 设置Excel边框
      */

    private HSSFCellStyle normalStl(HSSFWorkbook wb) {
        HSSFCellStyle normalStyle = wb.createCellStyle();
        normalStyle.setBorderLeft(HSSFCellStyle.BORDER_THIN);
        normalStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
        normalStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);
        normalStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
        normalStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
        return normalStyle;
    }

    private String getText(int i) {
        String text = "";
        if (i == 0) {
            text = "部 门";
        }
        if (i == 1) {
            text = "工 号";
        }
        if (i == 2) {
            text = "姓 名";
        }
        if (i == 3) {
            text = "考勤类别";
        }
        return text;
    }

    private String formatString(String inStr) {
        if ((inStr == null) || ("".equals(inStr))) {
            return "";
        } else {
            if (inStr.length() == 2) {
                return inStr;
            } else {
                return "0" + inStr;
            }
        }
    }

    public void downLoadFile(HttpServletRequest request, HttpServletResponse response)
            throws IOException, ServletException {
        String realPath = request.getRealPath("");

        String startDate = request.getParameter("statDate");
        String deptId = request.getParameter("deptId");

        String finance = request.getParameter("finance");
        String downDeptId = "";
        String statMonth = startDate.substring(0, 4) + startDate.substring(5, 7);

        if ("".equals(deptId)) {
            downDeptId = "0";
        } else {
            downDeptId = deptId;
        }
        HttpSession session = request.getSession();
        String accountId = (String) session.getAttribute("account");
        List deptList = getDeptList(accountId);
        StringBuffer deptStr = new StringBuffer(512);
        /*if ("".equals(deptId)){
                  //Iterator deptIter = deptList.iterator();
                  //while (deptIter.hasNext()){
                  for (int i=0;i<deptList.size();i++){
                      Map deptMap = (Map)deptList.get(i);
                      String dep = deptMap.get("deptId").toString();
                      if (i==0){
                          deptStr.append(dep).append("',");
                      }else if (i==deptList.size()-1){
                          deptStr.append("'").append(dep);
                      }else{
                          deptStr.append("'").append(dep).append("',");
                      }

                  }
              }else{
                  deptStr.append(deptId);
              }
              if ("".equals(deptId)){
                  downDeptId = MyUtils.toMD5(deptStr.toString());
              }else{
                  downDeptId = deptId;
              }*/

        String excelName = "";
        if ("1".equals(finance)) {
            excelName = "checkRecordReportFinance.xls";
        } else {
            excelName = "checkRecordReport.xls";
        }
        OutputStream o = response.getOutputStream();
        byte b[] = new byte[1024];

        String downLoadFileName = downDeptId + statMonth + excelName;
        // the file to download.
        File fileLoad = new File(realPath + "/downloadfile", downLoadFileName);
        // the dialogbox of download file.
        response.setHeader("Content-disposition", "attachment;filename=" + downLoadFileName);
        // set the MIME type.
        response.setContentType("application/xls");
        // get the file length.
        long fileLength = fileLoad.length();
        String length = String.valueOf(fileLength);
        response.setHeader("Content_Length", length);
        // download the file.
        FileInputStream in = new FileInputStream(fileLoad);
        int n = 0;
        while ((n = in.read(b)) != -1) {
            o.write(b, 0, n);
        }
    }

    public List getDeptListForKQService() throws Exception {
        StringBuffer sql = new StringBuffer(1024);
        sql.append("select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
                .append(" where dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
                .append(" select distinct dept_parentid from ykt_ck.DEPARTMENT))")
                .append(" and  dept_id in (select distinct DEPT_ID from YKT_CK.T_OPER_LIMIT)")
                .append(" where 1=?)");
        //System.out.println(sql);
        List deptList=jdbcTemplate.queryForList(sql.toString(),new Object[]{"1"});
		
		return deptList;
	}
	
	
}
