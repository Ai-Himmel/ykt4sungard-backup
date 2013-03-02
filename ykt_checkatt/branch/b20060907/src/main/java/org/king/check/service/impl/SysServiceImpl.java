package org.king.check.service.impl;

import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.config.CommonConfig;
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
	
	public List search(Map filter)throws Exception
	{
		/**代码比较乱，重写代码hanjiwei20060828
		String sqlTem;
		if(StringUtils.isNotEmpty((String)filter.get("cardStatus"))&&((String)filter.get("cardStatus")).equals("all")&&StringUtils.isNotEmpty((String)filter.get("cardType"))&&!((String)filter.get("cardType")).equals("all"))
		{
			sqlTem=" dict.DICT_CAPTION as type ,";
		}
		else
		{
			sqlTem=" dict.DICT_CAPTION as status ,";
		}
		
		String sql=" select account.CUT_NAME as cut_name , account.ACCOUNT_ID as account_id,dept.DEPT_NAME as dept_name, " +
				" account.STUEMP_NO as stuemp_no,account.CARD_ID as card_id,account.CUSTOMER_ID as customer_id ," +
				sqlTem+
				"(select type_dict.DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY type_dict where  1=1 ";
		if(StringUtils.isNotEmpty((String)filter.get("cardStatus"))&&((String)filter.get("cardStatus")).equals("all")&&StringUtils.isNotEmpty((String)filter.get("cardType"))&&!((String)filter.get("cardType")).equals("all"))
		{
		sql+=" and type_dict.DICT_NO=17 and type_dict.DICT_VALUE =card.STATE_ID )as status ," ;
		}
		else
		{
			sql+=" and type_dict.DICT_NO=18 and type_dict.DICT_VALUE =char(card.TYPE_ID) )as type ," ;
		}
		
		
		sql+="cut.TYPE_NAME as p_type_name" +
				" from " +
				" YKT_CUR.T_AIF_ACCOUNT account, YKT_CUR.T_CIF_CUSTOMER customer , YKT_CUR.T_CIF_DEPT dept ," +
				"YKT_CUR.T_PIF_CARD card,YKT_CUR.T_PIF_DICTIONARY dict ,YKT_CUR.T_CIF_CUTTYPEFEE cut " +
				" where dept.DEPT_CODE=customer.CLASSDEPT_NO and customer.CUT_ID=account.CUSTOMER_ID " +
				" and card.CARD_ID=account.CARD_ID  " +
				" and cut.CUT_TYPE=customer.CUT_TYPE ";
		sql+=StringUtils.isNotEmpty((String)filter.get("personCode"))?" and account.STUEMP_NO='"+(String)filter.get("personCode")+"' ":" ";
		sql+=StringUtils.isNotEmpty((String)filter.get("personName"))?" and account.CUT_NAME='"+(String)filter.get("personName")+"' ":" ";
		sql+=StringUtils.isNotEmpty((String)filter.get("card"))?" and account.CARD_ID="+(String)filter.get("card")+" ":" ";
		
		//卡状态为真，无卡类型条件查询
		if(StringUtils.isNotEmpty((String)filter.get("cardStatus"))&&!((String)filter.get("cardStatus")).equals("all")&&StringUtils.isNotEmpty((String)filter.get("cardType"))&&((String)filter.get("cardType")).equals("all"))
			{
			sql+=" and dict.DICT_VALUE=card.STATE_ID and dict.DICT_NO=17 and dict.DICT_VALUE='"+(String)filter.get("cardStatus")+"'" ;
			}
		else 
		//卡类型为真，无卡状态条件查询
		if(StringUtils.isNotEmpty((String)filter.get("cardStatus"))&&((String)filter.get("cardStatus")).equals("all")&&StringUtils.isNotEmpty((String)filter.get("cardType"))&&!((String)filter.get("cardType")).equals("all"))
		{
		sql+=" and dict.DICT_VALUE=char(card.TYPE_ID) and dict.DICT_NO=18 and dict.DICT_VALUE='"+(String)filter.get("cardType")+"'" ;
		}
		else
		//卡类型为真，卡状态为真查询
		if(StringUtils.isNotEmpty((String)filter.get("cardStatus"))&&!((String)filter.get("cardStatus")).equals("all")&&StringUtils.isNotEmpty((String)filter.get("cardType"))&&!((String)filter.get("cardType")).equals("all"))
		{
		sql+=" and dict.DICT_VALUE=card.STATE_ID and dict.DICT_NO=17 and dict.DICT_VALUE='"+(String)filter.get("cardStatus")+"' and card.TYPE_ID="+(String)filter.get("cardType") ;
		}
		else
		{
			sql+=" and dict.DICT_VALUE=card.STATE_ID and dict.DICT_NO=17 " ;
		}
		
		
		if((String)filter.get("personType")!=null&&!((String)filter.get("personType")).equals("all"))
		{
			sql+=" and customer.CUT_TYPE="+(String)filter.get("personType");
		}
		if((String)filter.get("department")!=null&&!((String)filter.get("department")).equals("all"))
		{
			sql+=" and dept.DEPT_CODE='"+(String)filter.get("department")+"'";
		}
		**/
		StringBuffer sql= new StringBuffer();
		sql.append("select account.CUT_NAME as cut_name,account.ACCOUNT_ID as account_id,")
		.append(" dept.DEPT_NAME as dept_name,account.STUEMP_NO as stuemp_no,")
		.append(" account.CARD_ID as card_id,account.CUSTOMER_ID as customer_id,")
		.append(" (select type_dict.DICT_CAPTION from YKT_CUR.T_PIF_DICTIONARY type_dict where  type_dict.DICT_NO=18 and type_dict.DICT_VALUE =char(card.TYPE_ID) )as type ,")
		.append(" cut.TYPE_NAME as p_type_name from  YKT_CUR.T_AIF_ACCOUNT account, ")
		.append(" YKT_CUR.T_CIF_CUSTOMER customer , YKT_CUR.T_CIF_DEPT dept ,YKT_CUR.T_PIF_CARD card,YKT_CUR.T_CIF_CUTTYPEFEE cut")
		.append(" where dept.DEPT_CODE=customer.CLASSDEPT_NO and customer.CUT_ID=account.CUSTOMER_ID and")
		.append(" cut.CUT_TYPE=customer.CUT_TYPE and card.CARD_ID=account.CARD_ID and card.STATE_ID='1000' ");
		if (StringUtils.isNotEmpty((String)filter.get("personCode"))){
			sql.append(" and account.STUEMP_NO='"+(String)filter.get("personCode")+"' ");
		}
		if (StringUtils.isNotEmpty((String)filter.get("personName"))){
			sql.append(" and account.CUT_NAME='"+(String)filter.get("personName")+"' ");
		}
		if ((String)filter.get("cardType")!=null&&!((String)filter.get("cardType")).equals("all")){
			sql.append(" and card.TYPE_ID="+(String)filter.get("cardType"));
		}
		if((String)filter.get("personType")!=null&&!((String)filter.get("personType")).equals("all"))
		{
			sql.append(" and customer.CUT_TYPE="+(String)filter.get("personType"));
		}
		if((String)filter.get("department")!=null&&!((String)filter.get("department")).equals("all"))
		{
			sql.append(" and dept.DEPT_CODE='"+(String)filter.get("department")+"'");
		}
		log.debug("sql:"+sql.toString());
		
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
		String table=(String)filter.get("table");
		String preSql="select judge.STARTDATE as startdate,judge.ENDDATE as enddate , cut.CUT_NAME as clerkname from ";
		String midSql;
		String whereSql;
		String clerkIdList="";
		String sql;
		//String tokenSql=" union ";
		String []checkValues=(String[])filter.get("checkValues");
		DateFormat dateFormat=DateFormat.getDateInstance();
		
		for(int i=0;i<checkValues.length;i++)
		{
			if(i!=(checkValues.length-1))
			clerkIdList+=checkValues[i]+",";
			else clerkIdList+=checkValues[i];
		}
		log.debug("clerkIdList:"+clerkIdList);
		/*
		 * 将日期格式化
		 */
		String startDate=(String)filter.get("startDate");
	    String endDate=(String)filter.get("endDate");
		  
		startDate=startDate.replace('-','/');
		endDate=endDate.replace('-','/');
		  
		startDate=startDate+" "+(String)filter.get("startHour")+":"+(String)filter.get("startMin")+":00";
		endDate=endDate+" "+(String)filter.get("endHour")+":"+(String)filter.get("endMin")+":00";
		SimpleDateFormat sdf=new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
		
		if(table.equals(CommonConfig.table_LEAVEINFO))
			midSql=CommonConfig.table_LEAVEINFO+" judge ";
		if(table.equals(CommonConfig.table_IRREGULARREST))
			midSql=CommonConfig.table_IRREGULARREST+" judge ";
		if(table.equals(CommonConfig.table_EXTRAWORKINFO))
			midSql=CommonConfig.table_EXTRAWORKINFO+" judge ,YKT_CK.EXTRAWORKINFOMAP extmap ";
		else midSql=CommonConfig.table_LEAVEINFO+" judge ";
		
		midSql+=", YKT_CUR.T_CIF_CUSTOMER cut ";
		
		whereSql=" where judge.STARTDATE<='"+dateFormat.format(sdf.parse(endDate))+" "+(String)filter.get("endHour")+":"+(String)filter.get("endMin")+":00"+"' " +
				" and judge.ENDDATE>='"+dateFormat.format(sdf.parse(startDate))+" "+(String)filter.get("startHour")+":"+(String)filter.get("startMin")+":00"+"' ";
		if(table.equals(CommonConfig.table_EXTRAWORKINFO))
			whereSql+=" and judge.EXTRAINFOID=extmap.EXTRAINFOID and extmap.CLERKID in ("+clerkIdList+") and cut.CUT_ID in ("+clerkIdList+")";
		else
			whereSql+=" and judge.CLERKID in ("+clerkIdList+") and cut.CUT_ID in ("+clerkIdList+")";
		sql=preSql+midSql+whereSql;
		log.debug("sql:"+sql);
		List tempList=jdbcTemplate.queryForList(sql);
	
		return tempList;
	}

	public List getDeptList() throws Exception {
		StringBuffer sql = new StringBuffer(1024);
		sql.append("select dept.DEPT_ID as deptId,dept.DEPT_NAME as deptName from YKT_CK.DEPARTMENT dept ")
		.append("where dept.dept_id not in(select dept_id from ykt_ck.DEPARTMENT where dept_id in (")
		.append("select distinct dept_parentid from ykt_ck.DEPARTMENT))");
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
	

}
