package org.king.check.service.impl;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.service.SysService;
import org.springframework.jdbc.core.JdbcTemplate;

public class SysServiceImpl implements SysService {
	 private static final Log log = LogFactory.getLog(SysServiceImpl.class);
	
	private JdbcTemplate jdbcTemplate;
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}
	
     public List getCardStatus()throws Exception
     {
    	 String sql="select dict.DICT_VALUE as value , dict.DICT_CAPTION as caption from " +
    	 		"YKT_CUR.T_PIF_DICTIONARY dict " +
    	 		"where dict.DICT_NO=17";
    	 
    	 List cardStatusList=jdbcTemplate.queryForList(sql);
    	 return cardStatusList;
     }
	
	public List getPersonType()throws Exception
	 {
		String sql="select cut.CUT_TYPE as  type , cut.TYPE_NAME as name from " +
 		"YKT_CUR.T_CIF_CUTTYPEFEE cut ";
		
		List personTypeList=jdbcTemplate.queryForList(sql);
		return personTypeList;
    }
	public List getCardType()throws Exception
	{
		String sql="select dict.DICT_VALUE as value , dict.DICT_CAPTION as caption from " +
 		"YKT_CUR.T_PIF_DICTIONARY dict " +
 		"where dict.DICT_NO=18";
 
        List cardTypeList=jdbcTemplate.queryForList(sql);
        return cardTypeList;
	}
	
	public List getDepartList()throws Exception
	{
		String sql="select dept.DEPT_CODE as dept_code , dept.DEPT_NAME as dept_name from YKT_CUR.T_CIF_DEPT dept" +
				" where dept.PARENTDEPT_CODE!='NA' AND dept.PARENTDEPT_CODE is not null order by DEPT_NAME asc";
		
		List departmentList=jdbcTemplate.queryForList(sql);
		
		return departmentList;
	}
	
	/**
	 * hanjiwei modify it 20061030
	 */
	public List search(Map filter)throws Exception
	{
		StringBuffer sql= new StringBuffer();
		sql.append("select cust.CUT_NAME as cust_name,cust.CUT_ID as cust_id,")
		.append(" cust.STUEMP_NO as stuemp_no,ctype.TYPE_NAME as type_name ")
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
		log.debug("sql查询:"+sql.toString());
		
		List searchRes=jdbcTemplate.queryForList(sql.toString());
		return searchRes;
	}
	
	public String getCustomerNameByCustomerId(Integer customerId)throws Exception
	{
		String sql="select customer.CUT_NAME  as name from YKT_CUR.T_CIF_CUSTOMER customer where customer.CUT_ID="+customerId;
		
		log.debug(sql);
		
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
		sql.append("select dept.DEPT_ID as deptId,dept.DEPT_NAME as deptName from YKT_CK.DEPARTMENT dept ")
		.append("where dept.dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
		.append("select distinct dept_parentid from ykt_ck.DEPARTMENT))");
		List deptList=jdbcTemplate.queryForList(sql.toString());
		return deptList;
	}
	
	public List getDeptList(String operId)throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select DEPT_ID as deptId, DEPT_NAME as deptName from YKT_CK.DEPARTMENT")
		.append(" where dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
		.append(" select distinct dept_parentid from ykt_ck.DEPARTMENT))")
		.append(" and  dept_id in (select distinct DEPT_ID from YKT_CK.T_OPER_LIMIT")
		.append(" where oper_id='"+operId+"')");
		List deptList=jdbcTemplate.queryForList(sql.toString());
		return deptList;
	}

	public Integer getCardNo(Integer custId) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		Integer cardNo = null;
		sql.append("select CARD_ID as cardNo from YKT_CUR.T_PIF_CARD")
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
		sql.append("select DICT_VALUE, DICT_CAPTION")
		.append(" from YKT_CUR.T_PIF_DICTIONARY")
		.append(" where dict_no=1210 order by int(dict_value)");
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
		Map custInfo=jdbcTemplate.queryForMap(sql.toString());
		return custInfo;
	}

	public String getAccountIdByStuempNo(String stuempNo) throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select ID,ACCOUNT_NAME from YKT_CK.USR_ACCOUNT")
		.append(" where ACCOUNT_NAME='"+stuempNo+"'");
		Map custInfo=jdbcTemplate.queryForMap(sql.toString());
		return custInfo.get("ID").toString();
	}
	
	
}
