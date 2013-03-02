package org.king.check.service.impl;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
//import org.apache.commons.logging.Log;
//import org.apache.commons.logging.LogFactory;
import org.king.check.Constants;
import org.king.check.config.CommonConfig;
import org.king.check.service.SysService;
import org.springframework.jdbc.core.JdbcTemplate;

public class SysServiceImpl implements SysService {
	//private static final Log log = LogFactory.getLog(SysServiceImpl.class);
	
	private JdbcTemplate jdbcTemplate;
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	
     public List getCardStatus()throws Exception
     {
    	 String sql="select dict.DICT_VALUE  value , dict.DICT_CAPTION caption from " +
    	 		"YKT_CUR.T_PIF_DICTIONARY dict " +
    	 		"where dict.DICT_NO=17";
    	 
    	 List cardStatusList=jdbcTemplate.queryForList(sql);
    	 return cardStatusList;
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
		.append(" where cust.CUT_ID not in (select CUST_ID from YKT_CK.T_CLERKINFO)");
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
		//log.debug("sql查询:"+sql.toString());
		
		List searchRes=jdbcTemplate.queryForList(sql.toString());
		return searchRes;
	}
	
	public String getCustomerNameByCustomerId(Integer customerId)throws Exception
	{
		String sql="select customer.CUT_NAME  name from YKT_CUR.T_CIF_CUSTOMER customer where customer.CUT_ID="+customerId;
				
		List tempList;
		String customerName=null;
		
		tempList=jdbcTemplate.queryForList(sql);
		if(!tempList.isEmpty())
		{
			Map tmpMap=(Map)tempList.get(0);
			customerName=(String)tmpMap.get("name");
		}
		
			
		return customerName;
	}
	
	
	public String getIfOffice(int custId) throws Exception {
		String sql="select CUST_ID, IFOFFICE from YKT_CK.T_CLERKINFO where CUST_ID="+custId;
		
		List tempList=jdbcTemplate.queryForList(sql);
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
	
	public String getDeptName(String deptId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DEPT_ID,DEPT_NAME from YKT_CK.DEPARTMENT ")
		.append("where DEPT_ID='").append(deptId).append("'");
		List deptList=jdbcTemplate.queryForList(sql.toString());
		if (deptList.size()!=0){
			Map deptMap = (Map)deptList.get(0);
			return deptMap.get("DEPT_NAME").toString();
		}else{
			return "无部门名称信息";
		}
	}
	
	public List getDeptList(String operId)throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
		.append(" where dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
		.append(" select distinct dept_parentid from ykt_ck.DEPARTMENT))")
		.append(" and  dept_id in (select distinct DEPT_ID from YKT_CK.T_OPER_LIMIT")
		.append(" where oper_id='"+operId+"')");
		System.out.println(sql);
		List deptList=jdbcTemplate.queryForList(sql.toString());
		return deptList;
	}
	

	public List getDeptInfo(String deptId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DEPT_ID deptId, DEPT_NAME deptName from YKT_CK.DEPARTMENT")
		.append(" where dept_id ='"+deptId+"'");
		List deptInfo=jdbcTemplate.queryForList(sql.toString());
		return deptInfo;
	}

	public Integer getCardNo(Integer custId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		Integer cardNo = null;
		sql.append("select CARD_ID cardNo from YKT_CUR.T_PIF_CARD")
		.append(" where COSUMER_ID="+custId+" and STATE_ID='1000'");
		List cardList=jdbcTemplate.queryForList(sql.toString());
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

	public String getOperName(String operId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select person_name from ykt_ck.usr_person")
		.append(" where id='"+operId+"'");
		List operList=jdbcTemplate.queryForList(sql.toString());
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
		.append(" where dict_no=1210 and DICT_VALUE='"+leaveTypeId+"'");
		List operList=jdbcTemplate.queryForList(sql.toString());
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
		.append(" where STUEMP_NO='"+stuempNo+"'");
		List operList=jdbcTemplate.queryForList(sql.toString());
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
		.append(" where CUT_ID="+custId);
		List custInfo=jdbcTemplate.queryForList(sql.toString());
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
		.append(" where cust.STUEMP_NO='").append(filter.get("stuempNo").toString()).append("'");
		List custList=jdbcTemplate.queryForList(sql.toString());
		return custList;
	}

	public String getAccountIdByStuempNo(String stuempNo) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select ID,ACCOUNT_NAME from YKT_CK.USR_ACCOUNT")
		.append(" where ACCOUNT_NAME='"+stuempNo+"'");
		Map custInfo=jdbcTemplate.queryForMap(sql.toString());
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
	
	
}
