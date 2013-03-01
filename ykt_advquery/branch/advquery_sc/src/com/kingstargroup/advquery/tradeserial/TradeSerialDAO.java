/**
 * 
 */
package com.kingstargroup.advquery.tradeserial;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;

/**
 * @author Administrator
 *
 */
public class TradeSerialDAO {

	/**
	 * 得到某一台Pos机在一段时间内的消费情况
	 * @param posId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getConsumeStatByPos(String posId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				execSQL = "ConsumeStatByPosSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "ConsumeStatByPosMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("posid",posId);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 个人帐务情况变动：存款，消费，押金
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAllAccountChangeStatByCustId(String custId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType)||("byweek".equals(statType)))){
				execSQL = "AllAccountChangeStatByNoSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AllAccountChangeStatByNoMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("custid",custId);
			query.setString("begindate",beginDate);
			query.setString("enddate",endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	/*查找语句
		select cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,
		fee.fee_name,cust.cut_name,cust.stuemp_no,cust.classdept_no,
		dept.dept_name,cust.s_code,spec.s_name,cust.class_no,
		rc.card_no,rc.meal,count(rc.amount)amcount,sum(rc.amount)amsum,
		sum(rc.amount)/count(rc.amount) avg
		from t_rcstatdata rc 
		left join t_pif_card card on rc.card_no=card.card_id
		left join t_cif_customer cust on card.cosumer_id=cust.cut_id
		left join t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type
		left join t_pif_feetype fee on cust.fee_type = fee.fee_type
		left join t_cif_dept dept on cust.classdept_no = dept.dept_code
		left join t_cif_speciality spec on cust.s_code = spec.s_code
		group by rc.card_no,cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,fee.fee_name,
		cust.cut_name,cust.stuemp_no,cust.classdept_no,dept.dept_name,cust.s_code,
		spec.s_name,cust.class_no,rc.meal
		order by avg,meal desc	 
		过滤结果集，把消费次数小于规定的消费次数的人员去掉。amcount<次数
		*/
	/*
	 * 贫困生查找，参数：
	 * 开始日期，结束日期，院系，专业，班级，客户类别，收费类别，开始学号，结束学号，消费频度
	 */
	public List getSpecialList(String bDate,String eDate,
			String deptNo,String specNo,
			String classNo,int custType,
			int feeType,String bStuempNo,
			String eStuempNo,int per,String meal,
			float bavgRange,float eavgRange,
			String selPer,int perRange){
		StringBuffer strSql = new StringBuffer(1024);
		strSql.append("select cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,")
		.append(" fee.fee_name,cust.cut_name,cust.stuemp_no,cust.classdept_no,")
		.append(" dept.dept_name,cust.s_code,spec.s_name,cust.class_no,");
		if (!"".equals(meal)){
			strSql.append(" rc.meal,");
		}
		strSql.append(" rc.card_no,count(rc.amount)amcount,(sum(rc.amount)/100)amsum,")
		.append(" ((sum(rc.amount)/count(rc.amount))/100) avg")
		.append(" from ykt_cur.t_rcstatdata rc ")
		.append(" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
		.append(" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
		.append(" left join ykt_cur.t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type")
		.append(" left join ykt_cur.t_pif_feetype fee on cust.fee_type = fee.fee_type")
		.append(" left join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code")
		.append(" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code")
		.append(" where rc.tx_date>='")
		.append(bDate).append("' and rc.tx_date<='").append(eDate).append("'");
		//.append(" where rc.meal=:qmeal and rc.tx_date>=:qbDate and rc.tx_date<=:qeDate");
		//添加分析条件
		if (!"".equals(meal)){
			strSql.append(" and rc.meal='").append(meal).append("'");
		}
		if (!"".equals(deptNo)){
			strSql.append(" and cust.classdept_no='").append(deptNo).append("'");
		}
		if (!"".equals(specNo)){
			strSql.append(" and cust.s_code='").append(specNo).append("'");
		}
		if (!"".equals(classNo)){
			strSql.append(" and cust.class_no='").append(classNo).append("'");
		}
		if (custType>0){
			strSql.append(" and cust.cut_type=").append(custType);
		}
		if (feeType>0){
			strSql.append(" and cust.fee_type=").append(feeType);
		}
		if (!"".equals(bStuempNo)){
			strSql.append(" and cust.stuemp_no>='").append(bStuempNo).append("'");
		}
		if (!"".equals(eStuempNo)){
			strSql.append(" and cust.stuemp_no<='").append(eStuempNo).append("'");
		}
		

		strSql.append(" group by rc.card_no,cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,fee.fee_name,")
		.append(" cust.cut_name,cust.stuemp_no,cust.classdept_no,dept.dept_name,cust.s_code,")
		.append(" spec.s_name,cust.class_no");
		if (!"".equals(meal)){
			strSql.append(",rc.meal");
		}
		strSql.append(" order by avg");
		//System.out.println(strSql.toString());
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("cut_id",Hibernate.INTEGER);
			query.addScalar("cut_type",Hibernate.INTEGER);
			query.addScalar("type_name",Hibernate.STRING);
			query.addScalar("fee_type",Hibernate.INTEGER);
			query.addScalar("fee_name",Hibernate.STRING);
			query.addScalar("cut_name",Hibernate.STRING);
			query.addScalar("stuemp_no",Hibernate.STRING);
			query.addScalar("classdept_no",Hibernate.STRING);
			query.addScalar("dept_name",Hibernate.STRING);
			query.addScalar("s_code",Hibernate.STRING);
			query.addScalar("s_name",Hibernate.STRING);
			query.addScalar("class_no",Hibernate.STRING);
			query.addScalar("card_no",Hibernate.INTEGER);
			query.addScalar("amcount",Hibernate.INTEGER);
			query.addScalar("amsum",Hibernate.INTEGER);
			query.addScalar("avg",Hibernate.FLOAT);
			if (!"".equals(meal)){
				query.addScalar("meal",Hibernate.STRING);
			}
			List list = query.list();			
			float avgValue = 0;
			if (!"".equals(selPer)){
				Map avgMap= (Map)getSpecStat(meal).get(0);
				avgValue = Float.parseFloat(avgMap.get("totavg").toString());
				System.out.println("avgValue"+avgMap.get("totavg").toString());
				
			}
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				if (Integer.parseInt(objects[13].toString())<per){
					continue;
				}
				if ((bavgRange>0)){
					if ((Float.parseFloat(objects[15].toString())<bavgRange)||
							(Float.parseFloat(objects[15].toString())>eavgRange)){
						continue;
					}
				}
				
				if (!"".equals(selPer)){
					//比较值
					float compValue = 0;
					if ("up".equals(selPer)){
						compValue = avgValue*perRange/100 + avgValue;
						if (compValue>Float.parseFloat(objects[15].toString())){
							continue;
						}
					}
					if ("down".equals(selPer)){
						compValue = avgValue - avgValue*perRange/100 ;
						if (compValue<Float.parseFloat(objects[15].toString())){
							continue;
						}
					}
					
				}
				HashMap accMap = new HashMap();
				accMap.put("cut_id",objects[0]);
				accMap.put("cut_type",objects[1]);
				accMap.put("type_name",objects[2]);
				accMap.put("fee_type",objects[3]);
				accMap.put("fee_name",objects[4]);
				accMap.put("cut_name",objects[5]);
				accMap.put("stuemp_no",objects[6]);
				accMap.put("classdept_no",objects[7]);
				accMap.put("dept_name",objects[8]);
				accMap.put("s_code",objects[9]);
				accMap.put("s_name",objects[10]);
				accMap.put("class_no",objects[11]);
				accMap.put("card_no",objects[12]);
				accMap.put("amcount",objects[13]);
				accMap.put("amsum",objects[14]);
				accMap.put("avg",objects[15]);
				if (!"".equals(meal)){
					accMap.put("meal",mealTrans(objects[16].toString()));
				}else{
					accMap.put("meal","全天");
				}

				
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
	 * 按年取得总体平均消费金额，男生平均和女士平均
	 * @return
	 */
	public List getSpecStat(String meal){
		StringBuffer strSql = new StringBuffer(1024);
		strSql.append("select c.accyear,(a.femaleavg/100)femaleavg,(b.maleavg/100)maleavg,(c.totavg/100)totavg from")
		.append(" (select accyear,sum(amount)/count(*) femaleavg from")
		.append(" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
		.append(" from ykt_cur.t_rcstatdata rc")
		.append(" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
		.append(" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
		.append(" where cust.sex='1'");
		if (!"".equals(meal)){
			strSql.append("and rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)a,")

		.append(" (select accyear,sum(amount)/count(*) maleavg from")
		.append(" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
		.append(" from ykt_cur.t_rcstatdata rc")
		.append(" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
		.append(" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
		.append(" where cust.sex='2'");
		if (!"".equals(meal)){
			strSql.append("and rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)b,")

		.append(" (select accyear,sum(amount)/count(*) totavg from")
		.append(" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
		.append(" from ykt_cur.t_rcstatdata rc");
		
		if (!"".equals(meal)){
			strSql.append(" where rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)c")

		.append(" where c.accyear=b.accyear(+) and c.accyear=a.accyear(+)")
		.append(" order by c.accyear desc");
		//System.out.println(strSql);
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("accyear",Hibernate.STRING);
			query.addScalar("femaleavg",Hibernate.FLOAT);
			query.addScalar("maleavg",Hibernate.FLOAT);
			query.addScalar("totavg",Hibernate.FLOAT);
			List list = query.list();
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap accMap = new HashMap();
				accMap.put("accyear",objects[0]);
				accMap.put("femaleavg",nullToString(objects[1]));
				accMap.put("maleavg",nullToString(objects[2]));
				accMap.put("totavg",nullToString(objects[3]));
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
	
	//平均消费金额，人数分布图
	public List getConsemeAvg(String meal,String bDate,String eDate){
		StringBuffer strSql = new StringBuffer(1024);
		strSql.append("select count(card_no)num,(amount/100)amavg from ykt_cur.t_rcstatdata")
		.append(" where tx_date>='").append(bDate).append("' and tx_date<='").append(eDate).append("'");
		if (!"".equals(meal)){
			strSql.append(" and meal='").append(meal).append("'");
		}		
		strSql.append(" group by amount/100")
		.append(" order by amount/100");
		//System.out.println(strSql);
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("num",Hibernate.INTEGER);
			query.addScalar("amavg",Hibernate.FLOAT);
			List list = query.list();
			List result = new ArrayList();
			for (int i=0 ;i<list.size();i++){
				Object[] objects = (Object[])list.get(i);
				HashMap accMap = new HashMap();
				accMap.put("num",objects[0]);
				accMap.put("amavg",objects[1]);
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

	private String mealTrans(String in){
		if ("bk".equals(in.trim())){
			return "早餐";
		}else if ("lun".equals(in.trim())){
			return "午餐";
		}else if ("sup".equals(in.trim())){
			return "晚餐";
		}else{
			return "全天";
		}
	}
	private String nullToString(Object o){
		if ((o==null)){
			return "0";
		}else if ("".equals(o.toString())){
			return "0";
		}else{
			return o.toString();
		}
	}

	private Log _log = LogFactory.getLog(TradeSerialDAO.class);
}
