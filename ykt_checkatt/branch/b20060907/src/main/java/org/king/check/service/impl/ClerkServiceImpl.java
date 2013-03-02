/* ============================================================
 * 版权：    king 版权所有 (c) 2006
 * 文件：    org.king.check.service.impl.ClerkServiceImpl.java
 * 创建日期： 2006-6-19 13:31:54
 * 功能：    {具体要实现的功能}
 * 所含类:   {包含的类}
 * 修改记录：
 * 日期                    作者         内容
 * =============================================================
 * 2006-6-19 13:31:54      ljf        创建文件，实现基本功能
 * ============================================================
 */

/**
 * 
 */
package org.king.check.service.impl;

import java.io.Serializable;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.king.check.dao.ClerkDAO;
import org.king.check.domain.Clerk;
import org.king.check.domain.Clerkinfo;
import org.king.check.service.ClerkService;
import org.springframework.jdbc.core.JdbcTemplate;

/**
 * <p> ClerkServiceImpl.java </p>
 * <p> {功能说明} </p>
 *
 * <p><a href="ClerkServiceImpl.java.html"><i>查看源代码</i></a></p>  
 *
 * @author <a href="mailto:m_ljf@msn.com">ljf</a>
 * @version 0.1
 * @since 2006-6-19
 * 
 *
 */
public class ClerkServiceImpl implements ClerkService {
	private static final Log log = LogFactory.getLog(ClerkServiceImpl.class);
	private JdbcTemplate jdbcTemplate;
	
	private ClerkDAO clerkDAO;
	
	
	public void setJdbcTemplate(JdbcTemplate jdbcTemplate) {
		this.jdbcTemplate = jdbcTemplate;
	}

	
	public void setClerkDAO(ClerkDAO clerkDAO) {
		this.clerkDAO = clerkDAO;
	}


	/* (non-Javadoc)
	 * @see org.king.check.service.ClerkService#saveClerk(org.king.check.domain.Clerk)
	 */
	public void saveClerk(Clerk clerk) {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see org.king.check.service.ClerkService#getClerkByStuNumber(java.lang.String)
	 */
	public Clerk getClerkByStuNumber(String stuNumber) {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see org.king.check.service.ClerkService#getClerkBycardNumber(java.lang.String)
	 */
	public Clerk getClerkBycardNumber(String cardNumber) {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see org.king.check.service.ClerkService#getClerkByClerkName(java.lang.String)
	 */
	public Clerk getClerkByClerkName(String clerkName) {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see org.king.check.service.ClerkService#getClerksByDepartId(java.lang.String)
	 */
	public List getClerksByDepartId(String departId) {
		// TODO Auto-generated method stub
		return null;
	}

	/* (non-Javadoc)
	 * @see org.king.check.service.ClerkService#updateClerk(org.king.check.domain.Clerk)
	 */
	public void updateClerk(Clerk clerk) {
		// TODO Auto-generated method stub

	}

	/* (non-Javadoc)
	 * @see org.king.check.service.ClerkService#queryClerk(java.util.Map)
	 */
	public List queryClerk(Map filterMap) {
		/**
		String Sql = "SELECT B.CUT_ID as cut_id,B.STUEMP_NO AS PERSON_CODE,B.CUT_NAME AS PERSON_NAME,C.DEPT_NAME,D.DICT_CAPTION AS IS_SEAT FROM YKT_CK.CLERK A LEFT JOIN YKT_CUR.T_CIF_CUSTOMER B ON A.CLERKID=B.CUT_ID "+
        "LEFT  JOIN (SELECT DICT.DICT_VALUE,DICT.DICT_CAPTION FROM YKT_CK.COM_DICTIONARY DICT WHERE DICT.DICT_NO=1002) D ON A.ISSEAT=D.DICT_VALUE "+
        "LEFT  JOIN YKT_CK.DEPARTMENT C ON A.DEPARTMENTID=C.DEPT_ID";
			
			
		String sCod = " where 1=1 ";
		
		//参数处理
		if(filterMap!=null&&!filterMap.isEmpty()){
			String personCode = (String)filterMap.get("personCode");
			if (StringUtils.isNotEmpty(personCode))
				sCod +=" AND B.STUEMP_NO LIKE "+"'%"+personCode+"%'";
			String personName = (String)filterMap.get("personName");
			if (StringUtils.isNotEmpty(personName))
				sCod +=" AND B.CUT_NAME LIKE "+"'%"+personName+"%'";
			
			String card = (String)filterMap.get("card");
			if (StringUtils.isNotEmpty(card))
				sCod +=" AND B.CARD LIKE "+"'%"+card+"%'";
			
			String personType = (String)filterMap.get("personType");
			if (StringUtils.isNotEmpty(personType)&&!personType.equals("all"))
				sCod +=" AND B.CUT_TYPE = '"+personType+"'";
			
			String department = (String)filterMap.get("department");
			if (StringUtils.isNotEmpty(department)&&!department.equals("all"))
				sCod +=" AND A.DEPARTMENTID = '"+department+"'";
			
		}
		
		if(sCod!=null&&!sCod.equals("")){
			Sql += sCod;
		}
		**/
		StringBuffer sql = new StringBuffer(2048);
		sql.append("SELECT B.CUT_ID as CUT_ID,B.STUEMP_NO AS STUEMPID,B.CUT_NAME AS STUEMPNAME,")
		.append(" C.DEPT_NAME,D.DICT_CAPTION AS IFOFFICE FROM YKT_CK.CLERKINFO A ")
		.append(" LEFT JOIN YKT_CUR.T_CIF_CUSTOMER B ON A.CUST_ID=B.CUT_ID")
		.append(" LEFT JOIN (SELECT DICT.DICT_VALUE,DICT.DICT_CAPTION FROM ")
		.append(" YKT_CK.COM_DICTIONARY DICT WHERE DICT.DICT_NO=1002) D")
		.append(" ON A.IFOFFICE=D.DICT_VALUE LEFT  JOIN YKT_CK.DEPARTMENT C")
		.append(" ON A.DEPT_ID=C.DEPT_ID WHERE 1=1 ");
		//参数处理
		if(filterMap!=null&&!filterMap.isEmpty()){
			String personCode = (String)filterMap.get("personCode");
			if (StringUtils.isNotEmpty(personCode))
				sql.append(" AND B.STUEMP_NO LIKE "+"'%"+personCode+"%'");
			String personName = (String)filterMap.get("personName");
			if (StringUtils.isNotEmpty(personName))
				sql.append(" AND B.CUT_NAME LIKE "+"'%"+personName+"%'");			
			String department = (String)filterMap.get("department");
			if (StringUtils.isNotEmpty(department)&&!department.equals("all"))
				sql.append(" AND A.DEPT_ID = '"+department+"'");
		}
		log.debug("Sql--------------->"+sql.toString());
		List clerkList = jdbcTemplate.queryForList(sql.toString());
		return clerkList;
	}

	/**
	 * 
	 */
	public List queryAvailableClerk(Map filterMap) {
		//查询sql
		String Sql = "SELECT * FROM (SELECT B.CARD,B.PERSON_CODE AS PERSON_CODE,B.PERSON_NAME AS PERSON_NAME,B.PERSON_TYPE,C.DEPT_NAME AS DEPT_NAME,''as is_seat,0 as is_clerk,'否' as is_clerk_title "+
		             "FROM (SELECT * FROM YKT_CK.usr_person A WHERE A.PERSON_CODE NOT IN (SELECT CLERKID FROM YKT_CK.CLERK)) B "+
		             "LEFT JOIN YKT_CK.DEPARTMENT C ON  B.DEPT=C.DEPT_ID) Z";
			 
		String sSqlUnion=" UNION "+
		"SELECT * FROM (SELECT B.CARD,B.PERSON_CODE AS PERSON_CODE,B.PERSON_NAME AS PERSON_NAME,B.PERSON_TYPE,E.DEPT_NAME AS DEPT_NAME,D.DICT_CAPTION AS IS_SEAT,1 as is_clerk,'是' as is_clerk_title "+
		"FROM  (SELECT A.CLERKID AS PERSON_CODE,C.PERSON_NAME,C.DEPT,A.ISSEAT,C.PERSON_TYPE,C.CARD FROM YKT_CK.CLERK A LEFT JOIN YKT_CK.USR_PERSON C ON A.CLERKID=C.PERSON_CODE ) B"+
	      " LEFT JOIN (SELECT DICT.DICT_VALUE,DICT.DICT_CAPTION FROM YKT_CK.COM_DICTIONARY DICT WHERE DICT.DICT_NO=1002) D ON B.ISSEAT=D.DICT_VALUE"+
	      " LEFT JOIN YKT_CK.DEPARTMENT E ON  B.DEPT=E.DEPT_ID) Z"
				;
		String sCod = " WHERE 1=1 ";
		
		//参数处理
		if(filterMap!=null&&!filterMap.isEmpty()){
			String personCode = (String)filterMap.get("personCode");
			if (StringUtils.isNotEmpty(personCode))
				sCod +=" AND Z.PERSON_CODE LIKE "+"'%"+personCode+"%'";
			String personName = (String)filterMap.get("personName");
			if (StringUtils.isNotEmpty(personName))
				sCod +=" AND Z.PERSON_NAME LIKE "+"'%"+personName+"%'";
			String card = (String)filterMap.get("card");
			if (StringUtils.isNotEmpty(card))
				sCod +=" AND Z.CARD LIKE "+"'%"+card+"%'";
			
			String personType = (String)filterMap.get("personType");
			if (StringUtils.isNotEmpty(personType)&&!personType.equals("all"))
				sCod +=" AND Z.PERSON_TYPE = '"+personType+"'";
			
			String department = (String)filterMap.get("department");
			if (StringUtils.isNotEmpty(department)&&!department.equals("all"))
				sCod +=" AND Z.DEPT_NAME = '"+department+"'";
			
		}
	
		Sql = Sql+sCod+sSqlUnion+sCod;
		
		
		List clerkList = jdbcTemplate.queryForList(Sql);
		return clerkList;
	}


	/**
	 * 
	 */
	public int setupClerk(List clerkList) {
		
		int count = 0;
		if(clerkList!=null&&!clerkList.isEmpty()){
			for(int i=0;i<clerkList.size();i++){
				Clerkinfo clerk = (Clerkinfo)clerkList.get(i);
				boolean flag = clerkDAO.isExist(clerk.getCustId());
				
				if(!flag){
					clerkDAO.save(clerk);
				}else{
					clerkDAO.update(clerk);
				}
				count ++;
			}
		}
		return count;
	}

	
	
	public void deleteClerk(String clerkId){
		
		if(clerkId!=null&&clerkId!=""){
			clerkDAO.delete(clerkDAO.get(Integer.valueOf(clerkId)));
		}		
	}
	
	public Clerk get( Serializable id)
	{
		return clerkDAO.get(id);
	}
	public Map getClerkDetailByClerkId(String  clerkId)throws Exception
	{
		Map infoMap=new HashMap();
		
		/*
		 * 得到员工姓名 部门
		 */
        String sql="select cust.CUT_NAME as clerkName, depart.DEPT_NAME as deptName, dict.DICT_CAPTION as caption from " +
				" YKT_CK.CLERK clerk, YKT_CUR.T_CIF_CUSTOMER cust ," +
				" YKT_CK.DEPARTMENT depart, YKT_CK.COM_DICTIONARY dict " +
				" where cust.CUT_ID=clerk.CLERKID and  dict.DICT_NO=1002 and dict.DICT_VALUE=clerk.ISSEAT "+
				" and depart.DEPT_ID=clerk.DEPARTMENTID and clerk.CLERKID="+clerkId;
        log.debug("sql:"+sql);
        List infoList=jdbcTemplate.queryForList(sql);
        
        if(!infoList.isEmpty())
        {
        	Map tempMap=(Map)infoList.get(0);
        	infoMap.put("clerkName",tempMap.get("clerkName"));
        	infoMap.put("deptName",tempMap.get("deptName"));
        	infoMap.put("caption",tempMap.get("caption"));
        }
        /*
         * 得到员工工作制度
         */
        sql="select workconf.CONFNAME as confname, workconf.PERMITLATETIME as latetime,workconf.PREEARLY as earlytime ," +
	  	  "workconf.ONDUTYADVANCEDTIME as ontime,workconf.OFFDUTYLASTTIME as offtime ," +
	  	  "workconf.WORKCONFID as workconfid " +
	  	  " from  YKT_CK.WORKCONFMAP map, YKT_CK.WORKCONF workconf " +
	  	  " where workconf.WORKCONFID=map.WORKCONFID and map.CLERKID="+clerkId;
        
        infoList=jdbcTemplate.queryForList(sql);
        if(!infoList.isEmpty())
        {
        	Map tempMap=(Map)infoList.get(0);
        	infoMap.put("confname",tempMap.get("confname"));
        	infoMap.put("latetime",tempMap.get("latetime"));
        	infoMap.put("earlytime",tempMap.get("earlytime"));
        	infoMap.put("ontime",tempMap.get("ontime"));
        	infoMap.put("offtime",tempMap.get("offtime"));       	
        }
        /*
         * 得到员工 上下班时间制度
         */
        sql=" select timeconf.WORKTIMECONFID as id ," +
  		" timeconf.CONFNAME as timeconfname," +
  		" timeconf.ONDUTYTIME1 as onduty1," +
  		" timeconf.OFFDUTYTIME1 as offduty1," +
  		" timeconf.ONDUTYTIME2 as onduty2," +
  		" timeconf.OFFDUTYTIME2 as offduty2," +
  		" timeconf.ONDUTYTIME3 as onduty3," +
  		" timeconf.OFFDUTYTIME3 as offduty3," +
  		" timeconf.ONDUTYTIME4 as onduty4," +
  		" timeconf.OFFDUTYTIME4 as offduty4 " +
  		" from " +
  		" YKT_CK.CLERK clerk ,YKT_CK.WORKTIMECONF timeconf " +
  		" where timeconf.WORKTIMECONFID=clerk.WORKTIMECONFID and clerk.CLERKID="+clerkId;
        infoList=jdbcTemplate.queryForList(sql);
        if(!infoList.isEmpty())
        {
        	Map tempMap=(Map)infoList.get(0);
        	infoMap.put("timeconfname",tempMap.get("timeconfname"));
        	infoMap.put("onduty1",tempMap.get("onduty1"));
        	infoMap.put("offduty1",tempMap.get("offduty1"));
        	infoMap.put("onduty2",tempMap.get("onduty2"));
        	infoMap.put("offduty2",tempMap.get("offduty2"));
        	infoMap.put("onduty3",tempMap.get("onduty3"));
        	infoMap.put("offduty3",tempMap.get("offduty3"));
        	infoMap.put("onduty4",tempMap.get("onduty4"));
        	infoMap.put("offduty4",tempMap.get("offduty4"));
        }
		
		
		return infoMap;
	}
	

}
