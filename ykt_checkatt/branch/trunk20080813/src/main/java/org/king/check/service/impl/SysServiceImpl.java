package org.king.check.service.impl;

import java.io.File;
import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.io.OutputStream;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;
import java.util.Map;
import org.apache.log4j.*;
import javax.servlet.ServletException;
import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
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

import org.springframework.jdbc.core.JdbcTemplate;

public class SysServiceImpl implements SysService {
	//private static final Log log = LogFactory.getLog(SysServiceImpl.class);
	
	private JdbcTemplate jdbcTemplate;
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	public List getEmailList(){
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select id,person_code,email from ykt_ck.usr_person")
		.append(" where email is not null or email<>''");
		List mailList=jdbcTemplate.queryForList(sql.toString());
		return mailList;
	}

	/*
	 * 部门数量
	 */
	public int getDeptCount(){
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select count(*)as num from ykt_ck.department");
		Map deptCount=jdbcTemplate.queryForMap(sql.toString());
		if (deptCount.get("num")==null){
			return 0;
		}else{
			return Integer.parseInt(deptCount.get("num").toString());
		}
		
	}
	
	/**
	 * 根据登录名取得该登录人员拥有的部门数量
	 * @param loginCode
	 * @return
	 */
	public int getDeptByLogin(String loginCode){
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select count(*)as num from ykt_ck.t_oper_limit t")
		.append(" where t.oper_id=?");
		Map deptCount=jdbcTemplate.queryForMap(sql.toString(),new Object[]{loginCode});
		if (deptCount.get("num")==null){
			return 0;
		}else{
			return Integer.parseInt(deptCount.get("num").toString());
		}
	}
	
	public List getCheckTypeInfo() throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select type_id typeId,type_name typeName from YKT_CK.T_CHECKTYPE");
		List checkTypeInfo=jdbcTemplate.queryForList(sql.toString());
		return checkTypeInfo;
	}

     public List getCardStatus()throws Exception
     {
    	 String sql="select dict.DICT_VALUE  value , dict.DICT_CAPTION caption from " +
    	 		"YKT_CUR.T_PIF_DICTIONARY dict " +
    	 		"where dict.DICT_NO=17";
    	 
    	 List cardStatusList=jdbcTemplate.queryForList(sql);
    	 return cardStatusList;
     }

     public List getCheckattType()throws Exception{
    	 String sql="select dict.DICT_VALUE  value , dict.DICT_CAPTION caption from " +
    	 		"YKT_CUR.T_PIF_DICTIONARY dict " +
    	 		"where dict.DICT_NO=1200";
    	 
    	 List checkattList=jdbcTemplate.queryForList(sql);
    	 return checkattList;
     }

	public List getPersonType()throws Exception
	 {
		String sql="select cut.CUT_TYPE type , cut.TYPE_NAME name from " +
 		"YKT_CUR.T_CIF_CUTTYPEFEE cut ";
		
		List personTypeList=jdbcTemplate.queryForList(sql);
		return personTypeList;
    }
	public List getCardType()throws Exception
	{
		String sql="select dict.DICT_VALUE value , dict.DICT_CAPTION caption from " +
 		"YKT_CUR.T_PIF_DICTIONARY dict " +
 		"where dict.DICT_NO=18";
 
        List cardTypeList=jdbcTemplate.queryForList(sql);
        return cardTypeList;
	}
	
	public List getDepartList()throws Exception
	{
		String sql="select dept.DEPT_CODE dept_code , dept.DEPT_NAME dept_name from YKT_CUR.T_CIF_DEPT dept" +
				" where dept.PARENTDEPT_CODE!='NA' and DEPT_LEVEL=1 AND dept.PARENTDEPT_CODE is not null";
		
		List departmentList=jdbcTemplate.queryForList(sql);
		
		return departmentList;
	}
	
	public List getSpecList()throws Exception{
		String sql="select s_code,s_name from t_cif_speciality";
		
		List specList=jdbcTemplate.queryForList(sql);
		
		return specList;
	}
	
	/**
	 * hanjiwei modify it 20061030
	 */
	public List search(Map filter)throws Exception
	{
		StringBuffer sql= new StringBuffer();
		sql.append("select cust.CUT_NAME cust_name,cust.CUT_ID cust_id,")
		.append(" cust.STUEMP_NO stuemp_no,ctype.TYPE_NAME type_name ")
		.append(" from  YKT_CUR.T_CIF_CUSTOMER cust ")
		.append(" left join YKT_CUR.T_CIF_DEPT dept on dept.DEPT_CODE=cust.CLASSDEPT_NO")
		.append(" left join YKT_CUR.T_CIF_CUTTYPEFEE ctype on  ctype.CUT_TYPE=cust.CUT_TYPE")
		.append(" left join YKT_CUR.t_cif_speciality spec on spec.s_code=cust.s_code")
		.append(" where (cust.STUEMP_NO is not null or cust.STUEMP_NO<>'')")
		.append(" and cust.CUT_ID not in (select CUST_ID from YKT_CK.T_CLERKINFO)");
		if (StringUtils.isNotEmpty((String)filter.get("personCode"))){
			sql.append(" and cust.STUEMP_NO like '%"+(String)filter.get("personCode")+"%' ");
		}
		if (StringUtils.isNotEmpty((String)filter.get("personName"))){
			sql.append(" and cust.CUT_NAME like '%"+(String)filter.get("personName")+"%' ");
		}
		if((String)filter.get("department")!=null&&!((String)filter.get("department")).equals("all"))
		{
			sql.append(" and dept.DEPT_CODE='"+(String)filter.get("department")+"'");
		}
		if((String)filter.get("spec")!=null&&!((String)filter.get("spec")).equals("all"))
		{
			sql.append(" and spec.s_code='"+(String)filter.get("spec")+"'");
		}
		//log.debug("sql查询:"+sql.toString());
		
		List searchRes=jdbcTemplate.queryForList(sql.toString());
		return searchRes;
	}
	
	public String getCustomerNameByCustomerId(Integer customerId)throws Exception
	{
		String sql="select customer.CUT_NAME  name from YKT_CUR.T_CIF_CUSTOMER customer where customer.CUT_ID=?";
				
		List tempList;
		String customerName=null;
		
		tempList=jdbcTemplate.queryForList(sql,new Object[]{customerId});
		if(!tempList.isEmpty())
		{
			Map tmpMap=(Map)tempList.get(0);
			customerName=(String)tmpMap.get("name");
		}			
		return customerName;
	}
		
	public String getIfOffice(int custId) throws Exception {
		String sql="select CUST_ID, IFOFFICE from YKT_CK.T_CLERKINFO where CUST_ID=?";
		
		List tempList=jdbcTemplate.queryForList(sql,new Object[]{new Integer(custId)});
		String ifOffice=null;
		
		if(!tempList.isEmpty())
		{
			Map tmpMap=(Map)tempList.get(0);
			ifOffice=(String)tmpMap.get("IFOFFICE");
		}
		return ifOffice;
	}

	/*
	 *  (non-Javadoc)
	 * @see org.king.check.service.SysService#isExistDate(java.util.Map)
	 * 检查查询的表中时间段是否已经存在
	 */
	public List isExistDate(Map filter)throws Exception
	{
		return null;
	}

	public List getDeptList() throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select dept.DEPT_ID deptId,dept.DEPT_NAME deptName from YKT_CK.DEPARTMENT dept ")
		.append("where dept.dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
		.append("select distinct dept_parentid from ykt_ck.DEPARTMENT))");
		List deptList=jdbcTemplate.queryForList(sql.toString());
		return deptList;
	}
	
	public String getCheckTypeName(String typeId){
		if ("".equals(typeId)){
			return "";
		}
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select TYPE_ID,TYPE_NAME from YKT_CK.T_CHECKTYPE ")
		.append("where TYPE_ID=?");
		List deptList=jdbcTemplate.queryForList(sql.toString(),new Object[]{typeId});
		if (deptList.size()!=0){
			Map deptMap = (Map)deptList.get(0);
			return deptMap.get("TYPE_NAME").toString();
		}else{
			return "";
		}
	}
	/*
	 * 取得部门名称 (non-Javadoc)
	 * @see org.king.check.service.SysService#getDeptName(java.lang.String)
	 */
	public String getDeptName(String deptId){
		if ("".equals(deptId)){
			return "";
		}
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DEPT_ID,DEPT_NAME from YKT_CK.DEPARTMENT ")
		.append("where DEPT_ID=?");
		List deptList=jdbcTemplate.queryForList(sql.toString(),new Object[]{deptId});
		if (deptList.size()!=0){
			Map deptMap = (Map)deptList.get(0);
			return deptMap.get("DEPT_NAME").toString();
		}else{
			return "";
		}
	}
	
	public List getDeptList(String operId)throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
		.append(" where dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
		.append(" select distinct dept_parentid from ykt_ck.DEPARTMENT))")
		.append(" and  dept_id in (select distinct DEPT_ID from YKT_CK.T_OPER_LIMIT")
		.append(" where oper_id=?)");
		//System.out.println(sql);
		List deptList=jdbcTemplate.queryForList(sql.toString(),new Object[]{operId});
		return deptList;
	}
	

	public List getDeptInfo(String deptId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
		.append(" where dept_id =?");
		List deptInfo=jdbcTemplate.queryForList(sql.toString(),new Object[]{deptId});
		return deptInfo;
	}

	public Integer getCardNo(Integer custId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		Integer cardNo = null;
		sql.append("select CARD_ID cardNo from YKT_CUR.T_PIF_CARD")
		.append(" where COSUMER_ID=? and STATE_ID='1000'");
		List cardList=jdbcTemplate.queryForList(sql.toString(),new Object[]{custId});
		if(!cardList.isEmpty())
		{
			Map tmpMap=(Map)cardList.get(0);
			cardNo=(Integer)tmpMap.get("cardNo");
		}
		return cardNo;
	}

	public List getLeaveList() throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		if ("ORACLE".equals(Constants.DBNAME)){
			sql.append("select DICT_VALUE, DICT_CAPTION")
			.append(" from YKT_CUR.T_PIF_DICTIONARY")
			.append(" where dict_no=1210 order by to_number(dict_value)");
		}else if ("DB2".equals(Constants.DBNAME)){
			sql.append("select DICT_VALUE, DICT_CAPTION")
			.append(" from YKT_CUR.T_PIF_DICTIONARY")
			.append(" where dict_no=1210 order by int(dict_value)");
		}
		List leaveTypeList=jdbcTemplate.queryForList(sql.toString());
		return leaveTypeList;
	}

	public String getOperName(String operId) {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select person_name from ykt_ck.usr_person")
		.append(" where id=?");
		List operList=jdbcTemplate.queryForList(sql.toString(),new Object[]{operId});
		String operName = "";
		if (!operList.isEmpty()){
			Map tmpMap = (Map)operList.get(0);
			operName = (String)tmpMap.get("person_name");
		}
		return operName;
	}

	public String getLeaveTypeName(String leaveTypeId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY")
		.append(" where dict_no=1210 and DICT_VALUE=?");
		List operList=jdbcTemplate.queryForList(sql.toString(),new Object[]{leaveTypeId.trim()});
		String leaveTypeName = "";
		if (!operList.isEmpty()){
			Map tmpMap = (Map)operList.get(0);
			leaveTypeName = (String)tmpMap.get("DICT_CAPTION");
		}
		return leaveTypeName;
	}
	
	public int getCustIdByStuempNo(String stuempNo)throws Exception{
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select CUT_ID from YKT_CUR.T_CIF_CUSTOMER")
		.append(" where STUEMP_NO=?");
		List operList=jdbcTemplate.queryForList(sql.toString(),new Object[]{stuempNo});
		int custId = 0;
		if (!operList.isEmpty()){
			Map tmpMap = (Map)operList.get(0);
			custId = Integer.parseInt(tmpMap.get("CUT_ID").toString());
		}
		return custId;
	}

	public Map getCustInfoByCustId(int custId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select CUT_NAME,STUEMP_NO from YKT_CUR.T_CIF_CUSTOMER")
		.append(" where CUT_ID=?");
		List custInfo=jdbcTemplate.queryForList(sql.toString(),new Object[]{new Integer(custId)});
		Map custMap = new HashMap();
		if (!custInfo.isEmpty()){
			Map tempMap = (Map)custInfo.get(0);
			custMap.put("CUT_NAME",tempMap.get("CUT_NAME"));
			custMap.put("STUEMP_NO",tempMap.get("STUEMP_NO"));
			return custMap;
		}else{
			return null;
		}
	}

	public List getCustInfo(Map filter) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select cust.CUT_ID, cust.CUT_NAME,  cust.STUEMP_NO,dept.DEPT_ID,dept.DEPT_NAME")
		.append(" from YKT_CUR.T_CIF_CUSTOMER cust")
		.append(" left join YKT_CK.T_CLERKINFO clerk on cust.CUT_ID=clerk.CUST_ID")
		.append(" left join YKT_CK.DEPARTMENT dept on clerk.DEPT_ID=dept.DEPT_ID")
		.append(" where cust.STUEMP_NO=?");
		List custList=jdbcTemplate.queryForList(sql.toString(),new Object[]{filter.get("stuempNo").toString()});
		return custList;
	}

	public String getAccountIdByStuempNo(String stuempNo) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select ID,ACCOUNT_NAME from YKT_CK.USR_ACCOUNT")
		.append(" where ACCOUNT_NAME=?");
		Map custInfo=jdbcTemplate.queryForMap(sql.toString(),new Object[]{stuempNo});
		return custInfo.get("ID").toString();
	}

	public String ifAgree(String agreeId) {
		if ("0".equals(agreeId)){
			return CommonConfig.NOTAGREE;
		}else if ("1".equals(agreeId)){
			return CommonConfig.AGREE;
		}else{
			return "";
		}
	}

	public String ifCheck(String checkId) {
		if ("0".equals(checkId)){
			return CommonConfig.NOTCHECK;
		}else if ("1".equals(checkId)){
			return CommonConfig.CHECK;
		}else{
			return "";
		}
	}
	/**
	 * 根据考勤人员编号取得部门编号
	 * hanjiwei add it 20071030
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
		Map custList=jdbcTemplate.queryForMap(sql.toString(),new Object[]{new Integer(seriId)});
		return custList;
	}
	
	/**
	 * 根据手工考勤流水号取得考勤人员的客户号和客户所在的部门
	 * hanjiwei add it 20071030
	 * @param deptId
	 * @return
	 * @throws Exception
	 */
	public Map getDeptInfo(int custId) {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select cust_id,dept_id from ykt_ck.t_clerkinfo")
		.append(" where cust_id=?");
		//.append(custId);
		Map custList=jdbcTemplate.queryForMap(sql.toString(),new Object[]{new Integer(custId)});
		return custList;
	}
	
	
	/**
	 * 根据部门编号取得考勤人员名单详细信息
	 * hanjiwei add it 20071030
	 * @param deptId
	 * @return
	 * @throws Exception
	 */
	public List getClerkInfo(String deptId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select t.cust_id, cust.stuemp_no,cust.cut_name,dept.dept_name,cap.dict_caption")
		.append(" from ykt_ck.t_clerkinfo t,ykt_cur.t_cif_customer cust,")
		.append(" ykt_ck.department dept,ykt_cur.t_pif_dictionary cap")
		.append(" where t.cust_id=cust.cut_id and t.dept_id=dept.dept_id and")
		.append(" t.ifoffice=cap.dict_value and cap.dict_no=1200");
		if (!"".equals(deptId)){
			sql.append(" and t.dept_id=?");//.append(deptId).append("'");
		}
		sql.append(" order by t.dept_id");
	    log.info("---------sql.toString()---------");
		List custList= null;
		if (!"".equals(deptId)){
			custList=jdbcTemplate.queryForList(sql.toString(),new Object[]{deptId});
		}else{
			custList=jdbcTemplate.queryForList(sql.toString());
		}
		return custList;
	}
	
	/**
	 * 坐班人员列表
	 * @param deptId
	 * @return
	 * @throws Exception
	 */
	public List getCheckClerkInfo(String deptId,String ifoffice) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select t.cust_id, cust.stuemp_no,cust.cut_name,dept.dept_name,cap.DICT_VALUE,cap.dict_caption")
		.append(" from ykt_ck.t_clerkinfo t,ykt_cur.t_cif_customer cust,")
		.append(" ykt_ck.department dept,ykt_cur.t_pif_dictionary cap")
		.append(" where t.cust_id=cust.cut_id and t.dept_id=dept.dept_id and")
		.append(" t.ifoffice=cap.dict_value and cap.dict_no=1200");
		if (!"".equals(ifoffice)){
			sql.append(" and t.ifoffice in(").append(ifoffice).append(")");
		}
		if (!"".equals(deptId)){
			sql.append(" and t.dept_id=?");//.append(deptId).append("'");
		}
		sql.append(" order by t.dept_id");
		
		List custList= null;
		if (!"".equals(deptId)){
			custList=jdbcTemplate.queryForList(sql.toString(),new Object[]{deptId});
		}else{
			custList=jdbcTemplate.queryForList(sql.toString());
		}
		return custList;
	}
	
	/**
	 * 取得手工考勤记录
	 */
	public int getManCheck(String custId,String checkDate) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select count(*)as num from ykt_ck.t_attserial_record t")
		.append(" where cust_id=?")
		//.append(Integer.parseInt(custId))
		.append(" and att_date=?");
		//.append(checkDate).append("'");
		int custList=jdbcTemplate.queryForInt(sql.toString(),new Object[]{Integer.valueOf(custId),checkDate});
		return custList;
	}
	
	/**
	 * 取得打卡考勤记录
	 */
	public int getCardCheck(String custId,String checkDate) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select count(*)as num from ykt_ck.t_attserial t")
		.append(" where cust_id=?")
		//.append(Integer.parseInt(custId))
		.append(" and att_date=?");
		//.append(checkDate).append("'");
		int custList=jdbcTemplate.queryForInt(sql.toString(),new Object[]{Integer.valueOf(custId),checkDate});
		return custList;
	}
	
	public int getReportRecord(String deptId,String statMonth) {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select count(*)as num from ykt_ck.t_makereportrecord t")
		.append(" where dept_Id=?")
		//.append(deptId)
		.append(" and report_month=?");
		//.append(statMonth).append("'");
		int custList=jdbcTemplate.queryForInt(sql.toString(),new Object[]{deptId,statMonth});
		return custList;
	}

	/**
	 * 考勤列表
	 * @param custId
	 * @param checkDate
	 * @return
	 */
	public List getCheckReportList(String custId,String checkDate){
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select cust_id,check_date,check_num,worktime_num from ykt_ck.t_checkatt_report t")
		.append(" where cust_id=?")
		.append(" and check_date=? and ifoffice=1");
		List custList=jdbcTemplate.queryForList(sql.toString(),new Object[]{Integer.valueOf(custId),checkDate});
		return custList;
	}
	/*
	 * 根据月份取得每天所对应的周 (non-Javadoc)
	 * @see org.king.check.service.SysService#getWeekByDate(java.lang.String)
	 */
	public List getWeekByDate(String statMonth){
		if ((statMonth==null)||("".endsWith(statMonth))){
			return null;
		}else{
			List returnList = new ArrayList();
			
			for (int i=1;i<DateUtilExtend.getDaysByMonth(statMonth)+1;i++){
				Map workTime = new HashMap();
				StringBuffer statDate = new StringBuffer(8);
				statDate.append(statMonth.substring(0,4))
				.append(statMonth.substring(5,7))
				.append(formatString(String.valueOf(i)));
				workTime.put("date",formatString(String.valueOf(i)));
				workTime.put("week",DateUtilExtend.getWeekByDate(statDate.toString()));
				returnList.add(workTime);
			}
			return returnList;
		}
	}
	/*
	 *  (non-Javadoc)
	 * @see org.king.check.service.SysService#getWeekByDate(java.lang.String)
	 */
	public List getWeekByDate(String startDate,String endDate){
		if ((startDate==null)||(endDate==null)){
			return null;
		}else{
			List returnList = new ArrayList();
			String checkDate = startDate;
			while (DateUtilExtend.diffDate(endDate, checkDate) <= 0){
				Map workTime = new HashMap();
				workTime.put("date",checkDate);
				workTime.put("week","星期"+DateUtilExtend.getWeekByDate(checkDate));
				returnList.add(workTime);
				checkDate = DateUtilExtend.addDate2(checkDate,1);
			}
			return returnList;
		}
	}
	
	public Map initCheckMap(String statMonth){
		if ((statMonth==null)||("".endsWith(statMonth))){
			return null;
		}else{
			Map checkMap = new HashMap();
			checkMap.put("deptName","");
			checkMap.put("stuempNo","");
			checkMap.put("custName","");
			checkMap.put("custType","");
			for (int i=1;i<DateUtilExtend.getDaysByMonth(statMonth)+1;i++){
				checkMap.put(formatString(String.valueOf(i)),formatString(String.valueOf(i)));
			}
			return checkMap;
		}
	}
	
	/**
	 * 生成人员名单信息表格
	 * @param reportMap
	 * @param row
	 * @param style
	 * @return
	 */
	private HSSFRow setCheckInfo(Map reportMap,HSSFRow row,HSSFCellStyle style){
		String deptName = reportMap.get("deptName").toString();
		String stuempNo = reportMap.get("stuempNo").toString();
		String custName = reportMap.get("custName").toString();
		String custType = reportMap.get("custType").toString();
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
		return row;
	}
	
	/*
	 * 把生成的考勤记录导入到Excel
	 * @see org.king.check.service.SysService#importReportToExcel(java.lang.String, java.lang.String, java.util.List)
	 */
	public void importReportToExcel(String realPath,String deptId,String statMonth,List reportList,String operId) throws Exception{
	    HSSFWorkbook wb = new HSSFWorkbook();
	    HSSFSheet recordReport = wb.createSheet("recordReportSheet");
	    
	    HSSFHeader header = recordReport.getHeader();
	    header.setCenter(HSSFHeader.font("Stencil-Normal", "Bold") +
	                    HSSFHeader.fontSize((short) 12) + "考勤签到记录明细");
	    
	    HSSFCellStyle style = normalStl(wb);
	    
	    makeExcelTitle(statMonth,recordReport,style,deptId);
	   // makeExcelTitleNoToken(statMonth,recordReport,style,deptId,true);
	    HSSFRow row = null;
	    
	    int rowId = 3;
	    int cellRow = reportList.size()+3;
	    Iterator reportIter = reportList.iterator();
	    while (reportIter.hasNext()){
	    	Map reportMap = (Map)reportIter.next();
			row = recordReport.createRow((short)rowId);
			rowId = rowId + 1;
			setCheckInfo(reportMap,row,style);
			
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
		/*	recordReport.setColumnWidth((short)(short)(4),(short)1200);
			HSSFCell cell4 = row.createCell((short)(4));
			cell4.setCellType(HSSFCell.CELL_TYPE_STRING);
			cell4.setCellValue(new HSSFRichTextString(reportMap.get("totNum").toString()));
			cell4.setCellStyle(style);*/
			
			recordReport.setColumnWidth((short)(short)(dayList.size()+4),(short)1200);
			HSSFCell cell4 = row.createCell((short)(dayList.size()+4));
			cell4.setCellType(HSSFCell.CELL_TYPE_STRING);
			cell4.setCellValue(new HSSFRichTextString(reportMap.get("totNum").toString()));
			cell4.setCellStyle(style);
			
		/*	recordReport.setColumnWidth((short)(short)(dayList.size()+5),(short)1200);
			HSSFCell cell5 = row.createCell((short)(dayList.size()+5));
			cell5.setCellType(HSSFCell.CELL_TYPE_STRING);
			cell5.setCellValue(new HSSFRichTextString(reportMap.get("halfNum").toString()));
			cell5.setCellStyle(style);
			
			recordReport.setColumnWidth((short)(short)(dayList.size()+6),(short)1200);
			HSSFCell cell6 = row.createCell((short)(dayList.size()+6));
			cell6.setCellType(HSSFCell.CELL_TYPE_STRING);			
			cell6.setCellValue(new HSSFRichTextString(reportMap.get("patchMoney").toString()));
			cell6.setCellStyle(style);
			
			recordReport.setColumnWidth((short)(short)(dayList.size()+7),(short)1200);
			HSSFCell cell7 = row.createCell((short)(dayList.size()+7));
			cell7.setCellType(HSSFCell.CELL_TYPE_STRING);			
			cell7.setCellValue(new HSSFRichTextString(reportMap.get("holidayNum").toString()));
			cell7.setCellStyle(style);
			
			recordReport.setColumnWidth((short)(short)(dayList.size()+8),(short)1200);
			HSSFCell cell8 = row.createCell((short)(dayList.size()+8));
			cell8.setCellType(HSSFCell.CELL_TYPE_STRING);			
			cell8.setCellValue(new HSSFRichTextString(reportMap.get("linkNum").toString()));
			cell8.setCellStyle(style);*/
	    }
	    
	    //生成Excel制表信息
	    makeExcelBottom(recordReport,operId,cellRow);
	    
	    String statDate = statMonth.substring(0,4)+statMonth.substring(5,7);
	    String loadFile = "";
	    if ("".equals(deptId)){
	    	loadFile = realPath+"/downloadfile/"+"0"+statDate+"checkRecordReport.xls";
	    }else{
	    	loadFile = realPath+"/downloadfile/"+deptId+statDate+"checkRecordReport.xls";
	    	//loadFile = realPath+"\\downloadfile\\"+deptId+statDate+"checkRecordReport.xls";
	    }
	    FileOutputStream fileOut = new FileOutputStream(loadFile);
	    wb.write(fileOut);
	    fileOut.close();
	}
	
	private void makeExcelTitleNoToken(String statMonth,HSSFSheet recordReport,HSSFCellStyle style,String deptId,boolean noToken){
		recordReport.setColumnWidth((short)0,(short)7000);
		recordReport.setColumnWidth((short)1,(short)2800);
		recordReport.setColumnWidth((short)2,(short)2800);
		recordReport.setColumnWidth((short)3,(short)2800);
		
		//HSSFRow row0 = recordReport.createRow((short)0);
		HSSFRow row1 = recordReport.createRow((short)1);
		HSSFRow row2 = recordReport.createRow((short)2);
		
		List dayList = getWeekByDate(statMonth);
		//int dayNum = dayList.size();
		int dayNum = 1;
		//Iterator dayIter = dayList.iterator();
	/*	while (dayIter.hasNext()){
			Map dayMap = (Map)dayIter.next();
			int dayId = Integer.parseInt(dayMap.get("date").toString())+3;
			recordReport.setColumnWidth((short)dayId,(short)700);
			HSSFCell cell22 = row1.createCell((short)dayId);
			cell22.setCellType(HSSFCell.CELL_TYPE_STRING);

			cell22.setCellValue(new HSSFRichTextString(dayMap.get("week").toString()));
			cell22.setCellStyle(style);
			HSSFCell cell33 = row2.createCell((short)dayId);
			cell33.setCellType(HSSFCell.CELL_TYPE_STRING);

			cell33.setCellValue(new HSSFRichTextString(dayMap.get("date").toString()));
			cell33.setCellStyle(style);
		}*/
		//设置表格宽度
		recordReport.setColumnWidth((short)(short)(dayNum+4),(short)1200);	
		recordReport.setColumnWidth((short)(short)(dayNum+5),(short)1200);
		
		//合并表格
		recordReport.addMergedRegion(new Region(0,(short)0,2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)1,2,(short)1));
		recordReport.addMergedRegion(new Region(0,(short)2,2,(short)2));
		recordReport.addMergedRegion(new Region(0,(short)3,2,(short)3));
		recordReport.addMergedRegion(new Region(0,(short)4,0,(short)(dayNum+3)));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+4),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+5),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+6),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+7),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+8),2,(short)0));
		
		for (int i=0;i<4;i++){
			HSSFRow row00 = recordReport.createRow(1);
			HSSFCell cell00 = row00.createCell((short) i);
			cell00.setCellType(HSSFCell.CELL_TYPE_STRING);

			cell00.setCellValue(new HSSFRichTextString(getText(i)));
			cell00.setCellStyle(style);
			recordReport.createRow(2).createCell((short) i).setCellStyle(style);
			recordReport.createRow(3).createCell((short) i).setCellStyle(style);
		}
		
		HSSFRow row66 = recordReport.createRow(0);

		HSSFCell cell66 = row66.createCell((short)2);
		cell66.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell66.setCellValue(new HSSFRichTextString(getDeptName(deptId)+statMonth+"月份明细考勤记录"));
		
		HSSFRow row77 = recordReport.createRow(1);
		HSSFCell cell77 = row77.createCell((short) (dayNum+3));		 
		cell77.setCellValue(new HSSFRichTextString("当月总考勤天数"));
		cell77.setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+3)).setCellStyle(style);
		recordReport.createRow(3).createCell((short) (dayNum+3)).setCellStyle(style);
		
		/*HSSFRow row771 = recordReport.createRow(0);
		HSSFCell cell771 = row771.createCell((short) (dayNum+5));		 
		cell771.setCellValue(new HSSFRichTextString("半勤次数"));
		cell771.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+5)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+5)).setCellStyle(style);

		HSSFRow row772 = recordReport.createRow(0);
		HSSFCell cell772 = row772.createCell((short) (dayNum+6));		 
		cell772.setCellValue(new HSSFRichTextString("补贴金额"));
		cell772.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+6)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+6)).setCellStyle(style);
		
		HSSFRow row773 = recordReport.createRow(0);
		HSSFCell cell773 = row773.createCell((short) (dayNum+7));		 
		cell773.setCellValue(new HSSFRichTextString("双休日次数"));
		cell773.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+7)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+7)).setCellStyle(style);
		
		HSSFRow row88 = recordReport.createRow(0);
		HSSFCell cell88 = row88.createCell((short) (dayNum+8));		 
		cell88.setCellValue(new HSSFRichTextString("连班次数"));
		cell88.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+8)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+8)).setCellStyle(style);*/

		
	
	}
	
	/*
	 * Excel表头设置
	 */
	private void makeExcelTitle(String statMonth,HSSFSheet recordReport,HSSFCellStyle style,String deptId){
		recordReport.setColumnWidth((short)0,(short)7000);
		recordReport.setColumnWidth((short)1,(short)2800);
		recordReport.setColumnWidth((short)2,(short)2800);
		recordReport.setColumnWidth((short)3,(short)2800);
		
		//HSSFRow row0 = recordReport.createRow((short)0);
		HSSFRow row1 = recordReport.createRow((short)1);
		HSSFRow row2 = recordReport.createRow((short)2);
		
		List dayList = getWeekByDate(statMonth);
		int dayNum = dayList.size();
		Iterator dayIter = dayList.iterator();
		while (dayIter.hasNext()){
			Map dayMap = (Map)dayIter.next();
			int dayId = Integer.parseInt(dayMap.get("date").toString())+3;
			recordReport.setColumnWidth((short)dayId,(short)700);
			HSSFCell cell22 = row1.createCell((short)dayId);
			cell22.setCellType(HSSFCell.CELL_TYPE_STRING);

			cell22.setCellValue(new HSSFRichTextString(dayMap.get("week").toString()));
			cell22.setCellStyle(style);
			HSSFCell cell33 = row2.createCell((short)dayId);
			cell33.setCellType(HSSFCell.CELL_TYPE_STRING);

			cell33.setCellValue(new HSSFRichTextString(dayMap.get("date").toString()));
			cell33.setCellStyle(style);
		}
		//设置表格宽度
		recordReport.setColumnWidth((short)(short)(dayNum+4),(short)1200);	
		recordReport.setColumnWidth((short)(short)(dayNum+5),(short)1200);
		
		//合并表格
		recordReport.addMergedRegion(new Region(0,(short)0,2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)1,2,(short)1));
		recordReport.addMergedRegion(new Region(0,(short)2,2,(short)2));
		recordReport.addMergedRegion(new Region(0,(short)3,2,(short)3));
		recordReport.addMergedRegion(new Region(0,(short)4,0,(short)(dayNum+3)));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+4),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+5),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+6),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+7),2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)(dayNum+8),2,(short)0));
		
		for (int i=0;i<4;i++){
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
		cell66.setCellValue(new HSSFRichTextString(getDeptName(deptId)+statMonth+"月份明细考勤记录"));
		cell66.setCellStyle(style);
		for (int i=5;i<dayNum+4;i++){
			row66.createCell((short) i).setCellStyle(style);
		}
		
		HSSFRow row77 = recordReport.createRow(0);
		HSSFCell cell77 = row77.createCell((short) (dayNum+4));		 
		cell77.setCellValue(new HSSFRichTextString("有效考勤天数"));
		cell77.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+4)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+4)).setCellStyle(style);

		/*HSSFRow row771 = recordReport.createRow(0);
		HSSFCell cell771 = row771.createCell((short) (dayNum+5));		 
		cell771.setCellValue(new HSSFRichTextString("半勤次数"));
		cell771.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+5)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+5)).setCellStyle(style);

		HSSFRow row772 = recordReport.createRow(0);
		HSSFCell cell772 = row772.createCell((short) (dayNum+6));		 
		cell772.setCellValue(new HSSFRichTextString("补贴金额"));
		cell772.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+6)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+6)).setCellStyle(style);
		
		HSSFRow row773 = recordReport.createRow(0);
		HSSFCell cell773 = row773.createCell((short) (dayNum+7));		 
		cell773.setCellValue(new HSSFRichTextString("双休日次数"));
		cell773.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+7)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+7)).setCellStyle(style);
		
		HSSFRow row88 = recordReport.createRow(0);
		HSSFCell cell88 = row88.createCell((short) (dayNum+8));		 
		cell88.setCellValue(new HSSFRichTextString("连班次数"));
		cell88.setCellStyle(style);
		recordReport.createRow(1).createCell((short) (dayNum+8)).setCellStyle(style);
		recordReport.createRow(2).createCell((short) (dayNum+8)).setCellStyle(style);*/

	}
	
	private void makeExcelBottom(HSSFSheet recordReport,String operId,int cellRow){
		HSSFRow row0 = recordReport.createRow(cellRow+2);
		HSSFCell cell00 = row0.createCell((short) 0);
		cell00.setCellType(HSSFCell.CELL_TYPE_STRING);
		//cell00.setCellValue(new HSSFRichTextString("符号：√全勤，O半勤，X缺勤，//连班全勤，#连班半勤"));
		cell00.setCellValue(new HSSFRichTextString("符号：√全勤，X缺勤 "));
		
		HSSFRow row = recordReport.createRow(cellRow+3);
		HSSFCell cell0 = row.createCell((short) 0);
		cell0.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell0.setCellValue(new HSSFRichTextString("报表日期："+DateUtilExtend.getNowDate()));
		
		HSSFCell cell1 = row.createCell((short) 1);
		cell1.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell1.setCellValue(new HSSFRichTextString("制表人："));
		
		HSSFCell cell2 = row.createCell((short) 2);
		cell2.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell2.setCellValue(new HSSFRichTextString(getOperName(operId)));
		
		HSSFCell cell3 = row.createCell((short) 3);
		cell3.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell3.setCellValue(new HSSFRichTextString("审核人："));
		

	}
	/*
	 * 设置Excel边框
	 */
	private HSSFCellStyle normalStl(HSSFWorkbook wb){
		HSSFCellStyle normalStyle = wb.createCellStyle();
		normalStyle.setBorderLeft(HSSFCellStyle.BORDER_THIN);
		normalStyle.setBorderTop(HSSFCellStyle.BORDER_THIN);
		normalStyle.setBorderRight(HSSFCellStyle.BORDER_THIN);
		normalStyle.setBorderBottom(HSSFCellStyle.BORDER_THIN);
		normalStyle.setAlignment(HSSFCellStyle.ALIGN_CENTER);
		return normalStyle;
	}
	
	private String getText(int i){
		String text = "";
		if (i==0){
			text = "部门/院系";
		}
		if (i==1){
			text = "学/工号";
		}
		if (i==2){
			text = "姓 名";
		}
		if (i==3){
			text = "考勤类别";
		}
		return text;
	}
	 
	private String formatString(String inStr){
		if ((inStr==null)||("".equals(inStr))){
			return "";
		}else{
			if (inStr.length()==2){
				return inStr;
			}else{
				return "0"+inStr;
			}
		}
	}
	
	/**
	 * 生成学生考勤信息
	 * @param realPath
	 * @param deptId
	 * @param statMonth
	 * @param reportList
	 * @param operId
	 * @throws Exception
	 */
	public void importReportToExcelStu(String realPath,String deptId,String beginDate,String endDate,List reportList,String operId) throws Exception{
	    HSSFWorkbook wb = new HSSFWorkbook();
	    HSSFSheet recordReport = wb.createSheet("recordReportSheet");
	    
	    HSSFHeader header = recordReport.getHeader();
	    header.setCenter(HSSFHeader.font("Stencil-Normal", "Bold") +
	                    HSSFHeader.fontSize((short) 12) + "学生考勤签到记录明细");
	    
	    HSSFCellStyle style = normalStl(wb);
	    
	    makeExcelTitleStu(beginDate,endDate,recordReport,style,deptId);
	    
	    HSSFRow row = null;
	    
	    int rowId = 3;
	    int cellRow = reportList.size()+3;
	    Iterator reportIter = reportList.iterator();
	    while (reportIter.hasNext()){
	    	Map reportMap = (Map)reportIter.next();
			row = recordReport.createRow((short)rowId);
			rowId = rowId + 1;
			setCheckInfo(reportMap,row,style);
			
			String tempDate = beginDate;
			int dayNum = 28;
			int dayId = 0;
			for (int i=0;i<28;i++){
				dayId = i+4;
				recordReport.setColumnWidth((short)dayId,(short)700);
				HSSFCell cell = row.createCell((short)(dayId));
				cell.setCellType(HSSFCell.CELL_TYPE_STRING);
				cell.setCellValue(new HSSFRichTextString(reportMap.get(getCheckSign2(i%4)+tempDate).toString()));
				cell.setCellStyle(style);
				if ((i%4==3)&&(i>0)){
					tempDate = DateUtilExtend.addDate2(tempDate.toString(),1);	
				}
			}
			recordReport.setColumnWidth((short)(short)(dayNum+4),(short)1200);
			HSSFCell cell4 = row.createCell((short)(dayNum+4));
			cell4.setCellType(HSSFCell.CELL_TYPE_STRING);
			cell4.setCellValue(new HSSFRichTextString(reportMap.get("checkNum").toString()));
			cell4.setCellStyle(style);
			
			recordReport.setColumnWidth((short)(short)(dayNum+5),(short)1200);
			HSSFCell cell5 = row.createCell((short)(dayNum+5));
			cell5.setCellType(HSSFCell.CELL_TYPE_STRING);
			cell5.setCellValue(new HSSFRichTextString(reportMap.get("lateNum").toString()));
			cell5.setCellStyle(style);
			
			recordReport.setColumnWidth((short)(short)(dayNum+6),(short)1200);
			HSSFCell cell6 = row.createCell((short)(dayNum+6));
			cell6.setCellType(HSSFCell.CELL_TYPE_STRING);			
			cell6.setCellValue(new HSSFRichTextString(reportMap.get("leaveNum").toString()));
			cell6.setCellStyle(style);

			/*
			recordReport.setColumnWidth((short)(short)(dayNum+7),(short)1200);
			HSSFCell cell7 = row.createCell((short)(dayNum+7));
			cell7.setCellType(HSSFCell.CELL_TYPE_STRING);			
			cell7.setCellValue(new HSSFRichTextString(reportMap.get("earlyNum").toString()));
			cell7.setCellStyle(style);
			*/
	    }
	    
	    //生成Excel制表信息
	    makeExcelBottomStu(recordReport,operId,cellRow);
	    
	    //String beginDate = beginDate;
	    String loadFile = "";
	    if ("".equals(deptId)){
	    	loadFile = realPath+"/downloadfile/"+"0"+beginDate+"checkRecordReport.xls";
	    }else{
	    	loadFile = realPath+"/downloadfile/"+deptId+beginDate+"checkRecordReport.xls";
	    }
	    FileOutputStream fileOut = new FileOutputStream(loadFile);
	    wb.write(fileOut);
	    fileOut.close();
	}
	
	private String getCheckSign(int i){
		String sign = "";
		switch (i) {
		case 0:
			sign = "早";
			break;
		case 1:
			sign = "上";
			break;
		case 2:
			sign = "下";
			break;
		case 3:
			sign = "晚";
			break;
		default:
			break;
		}
		return sign;
	}

	private String getCheckSign2(int i){
		String sign = "";
		switch (i) {
		case 0:
			sign = "mo-";
			break;
		case 1:
			sign = "am-";
			break;
		case 2:
			sign = "pm-";
			break;
		case 3:
			sign = "ni-";
			break;
		default:
			break;
		}
		return sign;
	}
	

	/*
	 * Excel表头设置
	 */
	private void makeExcelTitleStu(String beginDate,String endDate,HSSFSheet recordReport,HSSFCellStyle style,String deptId){
		recordReport.setColumnWidth((short)0,(short)7000);
		recordReport.setColumnWidth((short)1,(short)2800);
		recordReport.setColumnWidth((short)2,(short)2800);
		recordReport.setColumnWidth((short)3,(short)2800);
		
		//HSSFRow row0 = recordReport.createRow((short)0);
		HSSFRow row1 = recordReport.createRow((short)1);
		HSSFRow row2 = recordReport.createRow((short)2);
		
		String tempDate = beginDate;
		
		int dayNum = 28;
		int dayId = 0;
		for (int i=0;i<28;i++){
			dayId = i+4;
			recordReport.setColumnWidth((short)dayId,(short)700);
			HSSFCell cell22 = row1.createCell((short)dayId);
			cell22.setCellType(HSSFCell.CELL_TYPE_STRING);
			cell22.setCellValue(new HSSFRichTextString(tempDate));
			cell22.setCellStyle(style);
			
			HSSFCell cell33 = row2.createCell((short)dayId);
			cell33.setCellType(HSSFCell.CELL_TYPE_STRING);
			cell33.setCellValue(new HSSFRichTextString(getCheckSign(i%4)));
			cell33.setCellStyle(style);
			if (i%4==0){
				tempDate = DateUtilExtend.addDate2(tempDate.toString(),1);
			}
		}
		
		//设置最后几列表格宽度
		recordReport.setColumnWidth((short)(short)(dayNum+4),(short)1200);	
		recordReport.setColumnWidth((short)(short)(dayNum+5),(short)1200);
		recordReport.setColumnWidth((short)(short)(dayNum+6),(short)1200);
		
		//合并表格
		recordReport.addMergedRegion(new Region(0,(short)0,2,(short)0));
		recordReport.addMergedRegion(new Region(0,(short)1,2,(short)1));
		recordReport.addMergedRegion(new Region(0,(short)2,2,(short)2));
		recordReport.addMergedRegion(new Region(0,(short)3,2,(short)3));
		//主题头表格合并
		recordReport.addMergedRegion(new Region(0,(short)4,0,(short)(dayNum+6)));
		//日期表格合并
		int step = 0;
		for (int j=0;j<7;j++){
			recordReport.addMergedRegion(new Region(1,(short)(4+step),1,(short)(7+step)));
			step = step + 4;
		}
		//次数表格合并
		recordReport.addMergedRegion(new Region(1,(short)32,1,(short)34));
		
		for (int i=0;i<4;i++){
			HSSFRow row00 = recordReport.createRow(0);
			HSSFCell cell00 = row00.createCell((short) i);
			cell00.setCellType(HSSFCell.CELL_TYPE_STRING);

			cell00.setCellValue(new HSSFRichTextString(getText(i)));
			cell00.setCellStyle(style);
			recordReport.createRow(1).createCell((short) i).setCellStyle(style);
			recordReport.createRow(2).createCell((short) i).setCellStyle(style);
		}
		
		//设置题头
		HSSFRow row66 = recordReport.createRow(0);
		HSSFCell cell66 = row66.createCell((short) 4);
		cell66.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell66.setCellValue(new HSSFRichTextString(getDeptName(deptId)+beginDate+"--"+endDate+"学生考勤记录"));
		cell66.setCellStyle(style);
		
		for (int i=5;i<dayNum+5;i++){
			row66.createCell((short) i).setCellStyle(style);
		}

		//设置次数题头
		HSSFRow row666 = recordReport.createRow(1);
		HSSFCell cell666 = row666.createCell((short)(dayNum+4));
		cell666.setCellValue(new HSSFRichTextString("次数"));
		cell666.setCellStyle(style);
		
		for (int i=dayNum+5;i<dayNum+7;i++){
			row666.createCell((short) i).setCellStyle(style);
		}

		HSSFRow row77 = recordReport.createRow(2);
		HSSFCell cell77 = row77.createCell((short) (dayNum+4));		 
		cell77.setCellValue(new HSSFRichTextString("正常"));
		cell77.setCellStyle(style);

		HSSFRow row771 = recordReport.createRow(2);
		HSSFCell cell771 = row771.createCell((short) (dayNum+5));		 
		cell771.setCellValue(new HSSFRichTextString("迟到"));
		cell771.setCellStyle(style);

		HSSFRow row88 = recordReport.createRow(2);
		HSSFCell cell88 = row88.createCell((short) (dayNum+6));		 
		cell88.setCellValue(new HSSFRichTextString("缺席"));
		cell88.setCellStyle(style);
		
		/*
		HSSFRow row99 = recordReport.createRow(2);
		HSSFCell cell99 = row99.createCell((short) (dayNum+7));		 
		cell99.setCellValue(new HSSFRichTextString("早退"));
		cell99.setCellStyle(style);
		*/
	}
	
	
	private void makeExcelBottomStu(HSSFSheet recordReport,String operId,int cellRow){
		HSSFRow row0 = recordReport.createRow(cellRow+2);
		HSSFCell cell00 = row0.createCell((short) 0);
		cell00.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell00.setCellValue(new HSSFRichTextString("符号说明：√正常签到，⊙迟到，X缺勤"));
		
		
		HSSFRow row = recordReport.createRow(cellRow+3);
		HSSFCell cell0 = row.createCell((short) 0);
		cell0.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell0.setCellValue(new HSSFRichTextString("报表日期："+DateUtilExtend.getNowDate()));
		
		HSSFCell cell1 = row.createCell((short) 1);
		cell1.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell1.setCellValue(new HSSFRichTextString("制表人："));
		
		HSSFCell cell2 = row.createCell((short) 2);
		cell2.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell2.setCellValue(new HSSFRichTextString(getOperName(operId)));
		
		HSSFCell cell3 = row.createCell((short) 3);
		cell3.setCellType(HSSFCell.CELL_TYPE_STRING);
		cell3.setCellValue(new HSSFRichTextString("审核人："));
		

	}

	
	public void downLoadFile(HttpServletRequest request, HttpServletResponse response)
												throws IOException, ServletException {
		String realPath = request.getRealPath("");
		String startDate = request.getParameter("statDate");
		String beginDate = request.getParameter("beginDate");
		String deptId = request.getParameter("deptId");
		String downDeptId = "";
		String statMonth = "";
		if (null==startDate){
			statMonth = DateUtilExtend.formatDate2(beginDate);
		}else if (null==beginDate){
			statMonth= startDate.substring(0,4)+startDate.substring(5,7);
		}
		
		if ("".equals(deptId)){
			downDeptId = "0";
		}else{
			downDeptId = deptId;
		}
		OutputStream o = response.getOutputStream();
		byte b[] = new byte[1024];
		String downLoadFileName = downDeptId+statMonth+"checkRecordReport.xls";
		// the file to download.
		File fileLoad = new File(realPath+"/downloadfile", downLoadFileName);
		// the dialogbox of download file.
		response.setHeader("Content-disposition", "attachment;filename="+downLoadFileName);
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
	
	private static final Log log = LogFactory.getLog(SysServiceImpl.class);
}
