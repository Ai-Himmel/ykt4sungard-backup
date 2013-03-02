package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;
import java.util.Map;

import org.apache.commons.lang.StringUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;


public class LunchDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static LunchDAO getInstance() {
		if (_instance == null) {
			_instance = new LunchDAO();
		}
		return _instance;
	}
	
	/**
	 * 根据收费类别对就餐人员进行分类查找
	 * @param params
	 * @return
	 * @throws HibernateException
	 */
	public List getLunchDetail(Map params)throws HibernateException{
		String feeType = params.get("feeType")==null?"":params.get("feeType").toString();
		String cutType = params.get("cutType")==null?"":params.get("cutType").toString();
		String stuempNo = params.get("stuempNo")==null?"":params.get("stuempNo").toString();
		String custName = params.get("custName")==null?"":params.get("custName").toString();
		String beginDate = params.get("beginDate")==null?"":params.get("beginDate").toString();
		String endDate = params.get("endDate")==null?"":params.get("endDate").toString();
		
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select t.stuemp_no,t.cut_name,fee.fee_type,fee.fee_name,cuttype.type_name,t.totalMeal as meal,t.totalAmount as amount,t.period");
		sqlStr.append(" from (select cus.stuemp_no,cus.cut_name,cus.fee_type,cus.cut_type,count(rcs.meal) as totalMeal,sum(rcs.amount) as totalAmount,substr(rcs.tx_date, 1, 6) as period");
		sqlStr.append(" from ykt_cur.t_rcstatdata rcs,ykt_cur.t_pif_card card,ykt_cur.t_cif_customer cus");
		sqlStr.append(" where substr(rcs.tx_date, 1, 6) >=:begindate and substr(rcs.tx_date, 1, 6) <=:enddate and rcs.card_no = card.card_id and card.cosumer_id = cus.cut_id");
		sqlStr.append(" group by cus.stuemp_no,cus.cut_name,substr(rcs.tx_date, 1, 6),cus.fee_type,cus.cut_type) t,");
		sqlStr.append(" ykt_cur.t_pif_feetype fee,ykt_cur.t_cif_cuttypefee cuttype");
		sqlStr.append(" where t.fee_type = fee.fee_type and t.cut_type = cuttype.cut_type");
		if(StringUtils.isNotBlank(feeType)){
			sqlStr.append(" and t.fee_type=").append(feeType);
		}
		if(StringUtils.isNotBlank(cutType)){
			sqlStr.append(" and t.cut_type=").append(cutType);
		}
		if(StringUtils.isNotBlank(stuempNo)){
			sqlStr.append(" and t.stuemp_no like '%").append(stuempNo).append("%'");
		}
		if(StringUtils.isNotBlank(custName)){
			sqlStr.append(" and t.cut_name like '%").append(custName).append("%'");
		}
		sqlStr.append(" order by fee.fee_type, t.stuemp_no, t.period with ur");
		
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("stuemp_no",Hibernate.STRING);
			q.addScalar("cut_name",Hibernate.STRING);
			q.addScalar("fee_type",Hibernate.STRING);
			q.addScalar("fee_name",Hibernate.STRING);
			q.addScalar("type_name",Hibernate.STRING);
			q.addScalar("meal",Hibernate.STRING);
			q.addScalar("amount",Hibernate.STRING);
			q.addScalar("period",Hibernate.STRING);
			
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}	
	}
	
	/**
	 * 查找贫困生
	 * 就餐条件可灵活配置，可以配置符号如>,<,=,>=,<=；
	 * @param params
	 * @return
	 * @throws HibernateException
	 */
	public List getLunchPerson(Map params)throws HibernateException{
		String statType = params.get("statType")==null?"":params.get("statType").toString();
		
		String dayLimit = params.get("dayLimit").toString();
		String day = params.get("day")==null?"":params.get("day").toString();
		String mealLimit = params.get("mealLimit").toString();
		String meal = params.get("meal")==null?"":params.get("meal").toString();
		String moneyLimit = params.get("moneyLimit").toString();
		String money = params.get("money")==null?"":params.get("money").toString();
		String feeType = params.get("feeType")==null?"":params.get("feeType").toString();
		String cutType = params.get("cutType")==null?"":params.get("cutType").toString();
		String stuempNo = params.get("stuempNo")==null?"":params.get("stuempNo").toString();
		String custName = params.get("custName")==null?"":params.get("custName").toString();
		String beginDate = params.get("beginDate")==null?"":params.get("beginDate").toString();
		String endDate = params.get("endDate")==null?"":params.get("endDate").toString();
		
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		
		if("bydate".equals(statType)){
			sqlStr.append("select t.stuemp_no,t.cut_name,fee.fee_type,fee.fee_name,cuttype.type_name,t.totalMeal,t.totalAmount,t.totalDay,'' as period");
			sqlStr.append(" from (select sub.stuemp_no,sub.cut_name,sub.fee_type,sub.cut_type,sum(sub.meal) as totalMeal,sum(sub.amount) as totalAmount,count(sub.tx_date) as totalDay");
			sqlStr.append(" from (select cus.stuemp_no,cus.cut_name,cus.fee_type,cus.cut_type,count(rcs.meal) meal,sum(rcs.amount) amount,rcs.tx_date");
			sqlStr.append(" from ykt_cur.t_rcstatdata rcs,ykt_cur.t_pif_card card,ykt_cur.t_cif_customer cus");
			sqlStr.append(" where rcs.tx_date >=:begindate and rcs.tx_date <=:enddate");
			sqlStr.append(" and rcs.card_no = card.card_id and card.cosumer_id = cus.cut_id");
			sqlStr.append(" group by cus.stuemp_no,cus.cut_name,rcs.tx_date,cus.fee_type,cus.cut_type");
			if(StringUtils.isNotBlank(meal) && StringUtils.isNotBlank(money)){
				sqlStr.append(" having count(rcs.meal)").append(mealLimit).append(meal).append(" and sum(rcs.amount)").append(moneyLimit).append(money);
			} else if(StringUtils.isNotBlank(meal) && StringUtils.isBlank(money)){
				sqlStr.append(" having count(rcs.meal)").append(mealLimit).append(meal);
			} else if(StringUtils.isBlank(meal) && StringUtils.isNotBlank(money)){
				sqlStr.append(" having sum(rcs.amount)").append(moneyLimit).append(money);
			}
			sqlStr.append(") sub");
			sqlStr.append(" group by sub.stuemp_no, sub.cut_name, sub.fee_type, sub.cut_type");
			if(StringUtils.isNotBlank(day)){
				sqlStr.append(" having count(sub.tx_date)").append(dayLimit).append(day);
			}
			sqlStr.append(") t,ykt_cur.t_pif_feetype fee,ykt_cur.t_cif_cuttypefee cuttype");
			sqlStr.append(" where t.fee_type = fee.fee_type and t.cut_type = cuttype.cut_type");
			if(StringUtils.isNotBlank(feeType)){
				sqlStr.append(" and t.fee_type=").append(feeType);
			}
			if(StringUtils.isNotBlank(cutType)){
				sqlStr.append(" and t.cut_type=").append(cutType);
			}
			if(StringUtils.isNotBlank(stuempNo)){
				sqlStr.append(" and t.stuemp_no like '%").append(stuempNo).append("%'");
			}
			if(StringUtils.isNotBlank(custName)){
				sqlStr.append(" and t.cut_name like '%").append(custName).append("%'");
			}
			sqlStr.append(" order by fee.fee_type, t.stuemp_no with ur");
		}else if ("bymonth".equals(statType)){
			sqlStr.append("select t.stuemp_no,t.cut_name,fee.fee_type,fee.fee_name,cuttype.type_name,t.totalMeal,t.totalAmount,t.totalDay,t.peroid as period");
			sqlStr.append(" from (select sub.stuemp_no,sub.cut_name,sub.fee_type,sub.cut_type,sum(sub.meal) as totalMeal,sum(sub.amount) as totalAmount,count(sub.tx_date) as totalDay,substr(sub.tx_date, 1, 6) as peroid");
			sqlStr.append(" from (select cus.stuemp_no,cus.cut_name,cus.fee_type,cus.cut_type,count(rcs.meal) meal,sum(rcs.amount) amount,rcs.tx_date");
			sqlStr.append(" from ykt_cur.t_rcstatdata rcs,ykt_cur.t_pif_card card,ykt_cur.t_cif_customer cus");
			sqlStr.append(" where substr(rcs.tx_date, 1, 6) >=:begindate and substr(rcs.tx_date, 1, 6) <=:enddate");
			sqlStr.append(" and rcs.card_no = card.card_id and card.cosumer_id = cus.cut_id");
			sqlStr.append(" group by cus.stuemp_no,cus.cut_name,rcs.tx_date,cus.fee_type,cus.cut_type");
			if(StringUtils.isNotBlank(meal) && StringUtils.isNotBlank(money)){
				sqlStr.append(" having count(rcs.meal)").append(mealLimit).append(meal).append(" and sum(rcs.amount)").append(moneyLimit).append(money);
			} else if(StringUtils.isNotBlank(meal) && StringUtils.isBlank(money)){
				sqlStr.append(" having count(rcs.meal)").append(mealLimit).append(meal);
			} else if(StringUtils.isBlank(meal) && StringUtils.isNotBlank(money)){
				sqlStr.append(" having sum(rcs.amount)").append(moneyLimit).append(money);
			}
			sqlStr.append(") sub");
			sqlStr.append(" group by sub.stuemp_no, sub.cut_name, sub.fee_type, sub.cut_type,substr(sub.tx_date, 1, 6)");
			if(StringUtils.isNotBlank(day)){
				sqlStr.append(" having count(sub.tx_date)").append(dayLimit).append(day);
			}
			sqlStr.append(") t,ykt_cur.t_pif_feetype fee,ykt_cur.t_cif_cuttypefee cuttype");
			sqlStr.append(" where t.fee_type = fee.fee_type and t.cut_type = cuttype.cut_type");
			if(StringUtils.isNotBlank(feeType)){
				sqlStr.append(" and t.fee_type=").append(feeType);
			}
			if(StringUtils.isNotBlank(cutType)){
				sqlStr.append(" and t.cut_type=").append(cutType);
			}
			if(StringUtils.isNotBlank(stuempNo)){
				sqlStr.append(" and t.stuemp_no like '%").append(stuempNo).append("%'");
			}
			if(StringUtils.isNotBlank(custName)){
				sqlStr.append(" and t.cut_name like '%").append(custName).append("%'");
			}
			sqlStr.append(" order by fee.fee_type, t.stuemp_no,t.peroid with ur");
			
		}
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("stuemp_no",Hibernate.STRING);
			q.addScalar("cut_name",Hibernate.STRING);
			q.addScalar("fee_type",Hibernate.STRING);
			q.addScalar("fee_name",Hibernate.STRING);
			q.addScalar("type_name",Hibernate.STRING);
			q.addScalar("totalMeal",Hibernate.STRING);
			q.addScalar("totalAmount",Hibernate.STRING);
			q.addScalar("totalDay",Hibernate.STRING);
			q.addScalar("period",Hibernate.STRING);
			
			q.setString("begindate",beginDate);
			q.setString("enddate",endDate);
			
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}	
	}
	
	/**
	 * 查找客户收费类别
	 * @return
	 * @throws HibernateException
	 */
	public List getFeeType()throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("select t.fee_type as feeType,t.fee_name as feeName from ykt_cur.t_pif_feetype t  order by t.fee_type");
		try {
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("feeType",Hibernate.STRING);
			q.addScalar("feeName",Hibernate.STRING);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}	
	}
	
	private static LunchDAO _instance;
	private Log _log = LogFactory.getLog(LunchDAO.class.getClass());
}