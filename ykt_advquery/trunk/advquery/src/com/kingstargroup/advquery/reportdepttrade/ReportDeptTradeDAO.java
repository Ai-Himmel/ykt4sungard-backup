/**
 * 
 */
package com.kingstargroup.advquery.reportdepttrade;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;
import com.kingstargroup.advquery.util.WebKeys;

/** 
 * 整个单位卡户帐务变动情况
 * @author Administrator
 *
 */
public class ReportDeptTradeDAO {

	public List getDepAccountStat(String deptCode,String beginDate,String endDate,String statType){
		//String execSQL="";
		StringBuffer execSQL = new StringBuffer(1024);
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			//execSQL = "deptAccountStatSQL";
			execSQL.append("select balance_date,sum(saving)saving,sum(consume)consume,sum(deposit)deposit,")
			.append("sum(managefee)managefee from (Select balance_date,")
			.append(" (case when fee_type in (1,2,3,4) then 1 else 0 end)*opfee saving,")
			.append(" (case when fee_type=15 then 1 else 0 end)*opfee consume,")
			.append(" (case when fee_type=20 then 1 else 0 end)*opfee deposit,")
			.append(" (case when fee_type=10 then 1 else 0 end)*opfee managefee")
			.append(" from YKT_CUR.T_TIF_REPORT_DEPTTRADE where")
			.append(" balance_date>='").append(beginDate).append("' and balance_date<='").append(endDate)
			.append("' and dept_code='").append(deptCode).append("' )t")
			.append(" group by balance_date order by balance_date");
		}else if ("bymonth".equals(statType)){
			//execSQL = "deptAccountStatMonthSQL";
			execSQL.append("select balance_date,sum(saving)saving,sum(consume)consume,sum(deposit)deposit,")
			.append("sum(managefee)managefee from (Select substr(balance_date,1,6)balance_date,")
			.append(" (case when fee_type in (1,2,3,4) then 1 else 0 end)*opfee saving,")
			.append(" (case when fee_type=15 then 1 else 0 end)*opfee consume,")
			.append(" (case when fee_type=20 then 1 else 0 end)*opfee deposit,")
			.append(" (case when fee_type=10 then 1 else 0 end)*opfee managefee")
			.append(" from YKT_CUR.T_TIF_REPORT_DEPTTRADE where")
			.append(" substr(balance_date,1,6)>='").append(beginDate)
			.append("' and substr(balance_date,1,6)<='").append(endDate)
			.append("' and dept_code='").append(deptCode).append("' )t")
			.append(" group by balance_date order by balance_date");
		}
		Session s = HibernateSessionFactory.currentSession();
		try {
			//Query sqlquery = s.getNamedQuery(execSQL);
			//sqlquery.setString("dept_code",deptCode);
			//sqlquery.setString("begindate",beginDate);
			//sqlquery.setString("enddate",endDate);
			//List list = sqlquery.list();
			SQLQuery query = s.createSQLQuery(execSQL.toString());
			query.addScalar("balance_date",Hibernate.STRING);
			query.addScalar("saving",Hibernate.FLOAT);
			query.addScalar("consume",Hibernate.FLOAT);
			query.addScalar("deposit",Hibernate.FLOAT);
			query.addScalar("managefee",Hibernate.FLOAT);
			List list = query.list();
			
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap accMap = new HashMap();
				accMap.put("balance_date",objects[0]);
				accMap.put("saving",objects[1]);
				accMap.put("consume",objects[2]);
				accMap.put("deposit",objects[3]);
				accMap.put("managefee",objects[4]);
				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 单位所有持卡人消费情况总体统计
	 * @return
	 */
/*	public List getDeptConsumeStat(String deptCode,String beginDate,String endDate,String statType){
		String execSQL="";
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			if ("DB2".equals(WebKeys.DATABASE)){
				execSQL = "deptConsumeStatSQL_DB2";
			}else if ("ORACLE".equals(WebKeys.DATABASE)){
				execSQL = "deptConsumeStatSQL_ORACLE";
			}
		}else if ("bymonth".equals(statType)){
			if ("DB2".equals(WebKeys.DATABASE)){
				execSQL = "deptConsumeStatMonthSQL_DB2";
			}else if ("ORACLE".equals(WebKeys.DATABASE)){
				execSQL = "deptConsumeStatMonthSQL_ORACLE";
			}
			
		}
		Session s = HibernateSessionFactory.currentSession();
		try {
			Query sqlquery = s.getNamedQuery(execSQL);
			sqlquery.setString("deptcode",deptCode);
			sqlquery.setString("begindate",beginDate);
			sqlquery.setString("enddate",endDate);
			List list = sqlquery.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}*/
	
	
	public List getDeptConsumeStat(String deptCode,String beginDate,String endDate,String statType){
		StringBuffer execSQL= new StringBuffer(1024);
		if (("bydate".equals(statType))||("byweek".equals(statType))){
		execSQL.append(" select balance_date,  sum(consumenum)consumenum, sum(consumemoney)consumemoney, ")
		       .append("   (case when sum(consumenum)=0 then 0 else to_number(sum(consumemoney))/to_number(sum(consumenum)) end) avgmoney " )
	           .append(" from "	 )
	           .append(" (Select balance_date, ")
	           .append(" (case when fee_type=15 then 1 else 0 end)*opcount consumenum, ")
	           .append(" (case when fee_type=15 then 1 else 0 end)*opfee consumemoney ")
	           .append(" from YKT_CUR.T_TIF_REPORT_DEPTTRADE " )
	           .append(" where  1=1  ");
	            if(deptCode!=null && !deptCode.equals("")){
	     execSQL.append(" and  dept_code= '").append(deptCode).append("'" );
	            }
	     execSQL.append(" and balance_date>='")
	           .append(beginDate).append("' and not (balance_date>'").append(endDate).append("')) t ")
	           .append(" group by balance_date  " )
	           .append(" order by balance_date ");
		}else if ("bymonth".equals(statType)){
			execSQL.append(" select balance_date,sum(consumenum)consumenum, sum(consumemoney)consumemoney," )
				   .append(" (case when sum(consumenum)=0 then 0 else to_number(sum(consumemoney))/to_number(sum(consumenum)) end) avgmoney ")
				   .append(" from " )
			       .append(" (Select balance_date, " )
			       .append("  (case when fee_type=15 then 1 else 0 end)*opcount consumenum, ")
			       .append("  (case when fee_type=15 then 1 else 0 end)*opfee consumemoney ")
		           .append(" from YKT_CUR.T_TIF_REPORT_DEPTTRADE   ")
		           .append(" where 1=1 ");
				   if(deptCode!=null && !deptCode.equals("")){
					  execSQL.append(" and    dept_code='").append(deptCode).append("'");
				   }
				     execSQL.append(" and substr(balance_date,1,6)>='").append(beginDate).append("'")
				     .append(" and not (substr(balance_date,1,6)>'").append(endDate).append("'))t")
				     .append(" group by balance_date ")
				     .append(" order by balance_date " );
		}
		Session s = HibernateSessionFactory.currentSession();
		try {
		  
			SQLQuery query = s.createSQLQuery(execSQL.toString());
			query.addScalar("balance_date",Hibernate.STRING);
			query.addScalar("consumenum",Hibernate.INTEGER);
			query.addScalar("consumemoney",Hibernate.FLOAT);
			query.addScalar("avgmoney",Hibernate.FLOAT);
		
			List list = query.list();
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap conMap = new HashMap();
				conMap.put("balance_date",objects[0]);
				conMap.put("consumenum",objects[1]);
				conMap.put("consumemoney",objects[2]);
				conMap.put("avgmoney",objects[3]);
				result.add(conMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	private Log _log = LogFactory.getLog(ReportDeptTradeDAO.class);
}
