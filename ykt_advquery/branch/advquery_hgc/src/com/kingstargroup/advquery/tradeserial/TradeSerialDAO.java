/**
 * 
 */
package com.kingstargroup.advquery.tradeserial;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
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
	 * 
	 * @param posId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getConsumeStatByPos(String posId, String beginDate,
			String endDate, String statType) {
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType) || ("byweek".equals(statType)))) {
				execSQL = "ConsumeStatByPosSQL";
			} else if ("bymonth".equals(statType)) {
				execSQL = "ConsumeStatByPosMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("posid", posId);
			query.setString("begindate", beginDate);
			query.setString("enddate", endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}

	/**
	 * 个人帐务情况变动：存款，消费，押金
	 * 
	 * @param custId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAllAccountChangeStatByCustId(String custId,
			String beginDate, String endDate, String statType) {
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType) || ("byweek".equals(statType)))) {
				execSQL = "AllAccountChangeStatByNoSQL";
			} else if ("bymonth".equals(statType)) {
				execSQL = "AllAccountChangeStatByNoMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setString("custid", custId);
			query.setString("begindate", beginDate);
			query.setString("enddate", endDate);
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}

	/*
	 * 查找语句 select cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,
	 * fee.fee_name,cust.cut_name,cust.stuemp_no,cust.classdept_no,
	 * dept.dept_name,cust.s_code,spec.s_name,cust.class_no,
	 * rc.card_no,rc.meal,count(rc.amount)amcount,sum(rc.amount)amsum,
	 * sum(rc.amount)/count(rc.amount) avg from t_rcstatdata rc left join
	 * t_pif_card card on rc.card_no=card.card_id left join t_cif_customer cust
	 * on card.cosumer_id=cust.cut_id left join t_cif_cuttypefee ctype on
	 * cust.cut_type=ctype.cut_type left join t_pif_feetype fee on cust.fee_type =
	 * fee.fee_type left join t_cif_dept dept on cust.classdept_no =
	 * dept.dept_code left join t_cif_speciality spec on cust.s_code =
	 * spec.s_code group by
	 * rc.card_no,cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,fee.fee_name,
	 * cust.cut_name,cust.stuemp_no,cust.classdept_no,dept.dept_name,cust.s_code,
	 * spec.s_name,cust.class_no,rc.meal order by avg,meal desc
	 * 过滤结果集，把消费次数小于规定的消费次数的人员去掉。amcount<次数
	 */
	/*
	 * 贫困生查找，参数： 开始日期，结束日期，院系，专业，班级，客户类别，收费类别，开始学号，结束学号，消费频度
	 */
	public List getSpecialList(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange) {
		StringBuffer strSql = new StringBuffer(1024);
		strSql
				.append(
						" select cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,")
				.append(
						" fee.fee_name,cust.cut_name,cust.stuemp_no,cust.classdept_no,")
				.append(
						" dept.dept_name,cust.s_code,spec.s_name,cust.class_no,")
				.append(
						" rc.card_no,count(rc.amount)amcount,(sum(rc.amount)/100)amsum, ")
				.append(" round(((sum(rc.amount)/count(rc.amount))/100),2) avg ");
				if (!"".equals(meal)) {
			     strSql.append(", rc.meal");
		         }
				strSql.append(" from ykt_cur.t_rcstatdata rc ")
				.append(
						" inner join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
				.append(
						" inner join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
				.append(
						" inner join ykt_cur.t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type")
				.append(
						" inner join ykt_cur.t_pif_feetype fee on cust.fee_type = fee.fee_type")
				.append(
						" inner join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code")
				.append(
						" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code")
				.append(" where rc.tx_date>='").append(bDate).append(
						"' and rc.tx_date<='").append(eDate).append("'");
		// .append(" where rc.meal=:qmeal and rc.tx_date>=:qbDate and
		// rc.tx_date<=:qeDate");
		// 添加分析条件
		if (!"".equals(meal)) {
			strSql.append(" and rc.meal='").append(meal).append("'");
		}
		if (!"".equals(deptNo)) {
			strSql.append(" and cust.classdept_no='").append(deptNo)
					.append("'");
		}
		if (!"".equals(specNo)) {
			strSql.append(" and cust.s_code='").append(specNo).append("'");
		}
		if (!"".equals(classNo)) {
			strSql.append(" and cust.class_no='").append(classNo).append("'");
		}
		if (custType > 0) {
			strSql.append(" and cust.cut_type=").append(custType);
		}
		if (feeType > 0) {
			strSql.append(" and cust.fee_type=").append(feeType);
		}
		if (!"".equals(bStuempNo)) {
			strSql.append(" and cust.stuemp_no>='").append(bStuempNo).append(
					"'");
		}
		if (!"".equals(eStuempNo)) {
			strSql.append(" and cust.stuemp_no<='").append(eStuempNo).append(
					"'");
		}

		strSql
				.append(
						" group by rc.card_no,cust.cut_id,cust.cut_type,ctype.type_name,cust.fee_type,fee.fee_name,")
				.append(
						" cust.cut_name,cust.stuemp_no,cust.classdept_no,dept.dept_name,cust.s_code,")
				.append(" spec.s_name,cust.class_no");
		if (!"".equals(meal)) {
			strSql.append(",rc.meal");
		}
		strSql.append(" order by avg");
		// System.out.println(strSql.toString());
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("cut_id", Hibernate.INTEGER);
			query.addScalar("cut_type", Hibernate.INTEGER);
			query.addScalar("type_name", Hibernate.STRING);
			query.addScalar("fee_type", Hibernate.INTEGER);
			query.addScalar("fee_name", Hibernate.STRING);
			query.addScalar("cut_name", Hibernate.STRING);
			query.addScalar("stuemp_no", Hibernate.STRING);
			query.addScalar("classdept_no", Hibernate.STRING);
			query.addScalar("dept_name", Hibernate.STRING);
			query.addScalar("s_code", Hibernate.STRING);
			query.addScalar("s_name", Hibernate.STRING);
			query.addScalar("class_no", Hibernate.STRING);
			query.addScalar("card_no", Hibernate.INTEGER);
			query.addScalar("amcount", Hibernate.INTEGER);
			query.addScalar("amsum", Hibernate.FLOAT);
			query.addScalar("avg", Hibernate.FLOAT);
			if (!"".equals(meal)) {
				query.addScalar("meal", Hibernate.STRING);
			}else{
				per=per*3;
			}
			List list = query.list();
			float avgValue = 0;
			if (!"".equals(selPer)) {
				Map avgMap = (Map) getSpecStat(meal).get(0);
				avgValue = Float.parseFloat(avgMap.get("totavg").toString());
				/*System.out
						.println("avgValue" + avgMap.get("totavg").toString());*/

			}
		
			List result = new ArrayList();
			for (int i = 0; i < list.size(); i++) {
				Object[] objects = (Object[]) list.get(i);
				
				if (Integer.parseInt(objects[13].toString()) < per) {
					continue;
				}
				//去掉平均均值外的
				if ((Float.parseFloat(objects[15].toString()) < bavgRange)
							|| (Float.parseFloat(objects[15].toString()) > eavgRange)) {
						continue;
				}
				

				if (!"".equals(selPer)) {
					// 比较值
					float compValue = 0;
					if ("up".equals(selPer)) {
						compValue = avgValue * perRange / 100 + avgValue;
						if (compValue > Float
								.parseFloat(objects[15].toString())) {
							continue;
						}
					}
					if ("down".equals(selPer)) {
						compValue = avgValue - avgValue * perRange / 100;
						if (compValue < Float
								.parseFloat(objects[15].toString())) {
							continue;
						}
					}

				}
				HashMap accMap = new HashMap();
				accMap.put("cut_id", objects[0]);
				accMap.put("cut_type", objects[1]);
				accMap.put("type_name", objects[2]);
				accMap.put("fee_type", objects[3]);
				accMap.put("fee_name", objects[4]);
				accMap.put("cut_name", objects[5]);
				accMap.put("stuemp_no", objects[6]);
				accMap.put("classdept_no", objects[7]);
				accMap.put("dept_name", objects[8]);
				accMap.put("s_code", objects[9]);
				accMap.put("s_name", objects[10]);
				accMap.put("class_no", objects[11]);
				accMap.put("card_no", objects[12]);
				accMap.put("amcount", objects[13]);
				accMap.put("amsum", objects[14]);
				accMap.put("avg", objects[15]);
				if (!"".equals(meal)) {
					accMap.put("meal", mealTrans(objects[16].toString()));
				} else {
					accMap.put("meal", "全天");
				}

				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}

	/**
	 * 按年取得总体平均消费金额，男生平均和女士平均
	 * 
	 * @return
	 */
	public List getSpecStat(String meal) {
		StringBuffer strSql = new StringBuffer(1024);
		strSql
				.append(
						"select c.accyear,(a.femaleavg/100)femaleavg,(b.maleavg/100)maleavg,(c.totavg/100)totavg from")
				.append(" (select accyear,sum(amount)/count(*) femaleavg from")
				.append(
						" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
				.append(" from ykt_cur.t_rcstatdata rc")
				.append(
						" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
				.append(
						" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
				.append(" where cust.sex='1'");
		if (!"".equals(meal)) {
			strSql.append("and rc.meal='").append(meal).append("'");
		}
		strSql
				.append(") group by accyear)a,")

				.append(" (select accyear,sum(amount)/count(*) maleavg from")
				.append(
						" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
				.append(" from ykt_cur.t_rcstatdata rc")
				.append(
						" left join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
				.append(
						" left join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
				.append(" where cust.sex='2'");
		if (!"".equals(meal)) {
			strSql.append("and rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)b,")

		.append(" (select accyear,sum(amount)/count(*) totavg from").append(
				" (select rc.meal,substr(rc.tx_date,1,4) accyear,rc.amount")
				.append(" from ykt_cur.t_rcstatdata rc");

		if (!"".equals(meal)) {
			strSql.append(" where rc.meal='").append(meal).append("'");
		}
		strSql.append(") group by accyear)c")

		.append(" where c.accyear=b.accyear(+) and c.accyear=a.accyear(+)")
				.append(" order by c.accyear desc");
		// System.out.println(strSql);
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("accyear", Hibernate.STRING);
			query.addScalar("femaleavg", Hibernate.FLOAT);
			query.addScalar("maleavg", Hibernate.FLOAT);
			query.addScalar("totavg", Hibernate.FLOAT);
			List list = query.list();
			List result = new ArrayList();
			for (int i = 0; i < list.size(); i++) {
				Object[] objects = (Object[]) list.get(i);
				HashMap accMap = new HashMap();
				accMap.put("accyear", objects[0]);
				accMap.put("femaleavg", nullToString(objects[1]));
				accMap.put("maleavg", nullToString(objects[2]));
				accMap.put("totavg", nullToString(objects[3]));
				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}

	/**
	 * 按年取得总体平均消费金额，男生平均和女士平均 gejinfeng 按条件查询 2009-01-04
	 * 
	 * @return
	 */
	public List getSpecStat(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange) {
		StringBuffer strSql = new StringBuffer(1024);
		StringBuffer wheresql2 = new StringBuffer(1024);
		StringBuffer wheresql1 = new StringBuffer(1024);

		if (!"".equals(bDate)) {
			wheresql1.append(" and rc.tx_date >='").append(bDate).append("'");
		}
		if (!"".equals(eDate)) {
			wheresql1.append(" and  rc.tx_date <='").append(eDate).append("'");
		}
		if (!"".equals(meal)) {
			wheresql1.append(" and rc.meal='").append(meal).append("'");
		}

		if (!"".equals(deptNo)) {
			wheresql2.append(" and cust.classdept_no='").append(deptNo).append(
					"'");
		}
		if (!"".equals(specNo)) {
			wheresql2.append(" and cust.s_code='").append(specNo).append("'");
		}
		if (!"".equals(classNo)) {
			wheresql2.append(" and cust.class_no='").append(classNo)
					.append("'");
		}
		if (custType > 0) {
			wheresql2.append(" and cust.cut_type=").append(custType);
		}
		if (feeType > 0) {
			wheresql2.append(" and cust.fee_type=").append(feeType);
		}
		if (!"".equals(bStuempNo)) {
			wheresql2.append(" and cust.stuemp_no>='").append(bStuempNo)
					.append("'");
		}
		if (!"".equals(eStuempNo)) {
			wheresql2.append(" and cust.stuemp_no<='").append(eStuempNo)
					.append("'");
		}
		   wheresql2.append(" ) group by  cut_name  ");
		if (!"".equals(meal)) {
			wheresql2.append( " having count(*) >=").append(per);
		}else{
		    wheresql2.append( " having count(*) >=").append(per*3);
		}

		strSql
				.append(
						" select (a.femaleavg/100)femaleavg,(b.maleavg/100)maleavg,(c.totavg/100)totavg ")
				.append(" from (select NVL(sum(amount)/sum(num),0) femaleavg ")
				.append(" from ( select sum(amount) amount ,count(*) num, cut_name  " )
				.append(" from ( select  rc.meal,rc.amount,cust.cut_name  ")
				.append(
						" from ykt_cur.t_rcstatdata rc inner join ykt_cur.t_pif_card card on rc.card_no=card.card_id  ")

				// and rc.tx_date>='20080101' and rc.tx_date<='20081231'
				// and rc.meal ='lun'
				.append(wheresql1)
				.append(
						" inner join ykt_cur.t_cif_customer cust   on card.cosumer_id=cust.cut_id  ")
				.append(
						" inner join ykt_cur.t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type ")
				.append(
						" inner join ykt_cur.t_pif_feetype fee on cust.fee_type = fee.fee_type ")
				.append(
						" inner join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code ")
				.append(
						" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code  where cust.sex='1' ")
				.append(wheresql2)
				.append(" ))a,  ")
				// and cust.classdept_no='' and cust.s_code='' and
				// cust.class_no=''
				// and cust.cut_type='' and cust.fee_type and cust.stuemp_no>''
				// and cust.stuemp_no<''
				
				.append(" (select NVL(sum(amount)/sum(num),0) maleavg ")
				.append(" from ( select sum(amount) amount ,count(*) num, cut_name  " )
				.append(" from ( select  rc.meal,rc.amount,cust.cut_name  ")
				.append(
						" from ykt_cur.t_rcstatdata rc  inner join ykt_cur.t_pif_card card on rc.card_no=card.card_id  ")
				.append(wheresql1)
				// and rc.tx_date>='20080101' and rc.tx_date<='20081231'
				// and rc.meal ='lun'
				  
				.append(
						" inner join ykt_cur.t_cif_customer cust   on card.cosumer_id=cust.cut_id  ")
				.append(
						" inner join ykt_cur.t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type ")
				.append(
						" inner join ykt_cur.t_pif_feetype fee on cust.fee_type = fee.fee_type ")
				.append(
						" inner join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code ")
				.append(
						" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code  where cust.sex='2' ")
				.append(wheresql2)
				// and cust.classdept_no='' and cust.s_code='' and
				// cust.class_no=''
				// and cust.cut_type='' and cust.fee_type and cust.stuemp_no>''
				// and cust.stuemp_no<''
				.append(" ))b, ")
				
				
				.append(" (select NVL(sum(amount)/sum(num),0) totavg ")
				.append(" from ( select sum(amount) amount ,count(*) num, cut_name  " )
				.append(" from ( select  rc.meal,rc.amount,cust.cut_name  ")
				.append(
						" from ykt_cur.t_rcstatdata rc  inner join ykt_cur.t_pif_card card on rc.card_no=card.card_id ")
				.append(wheresql1)
				// and rc.tx_date>='20080101' and rc.tx_date<='20081231'
				// and rc.meal ='lun'
				.append(
						" inner join ykt_cur.t_cif_customer cust   on card.cosumer_id=cust.cut_id  ")
				.append(
						" inner join ykt_cur.t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type ")
				.append(
						" inner join ykt_cur.t_pif_feetype fee on cust.fee_type = fee.fee_type ")
				.append(
						" inner join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code ")
				.append(
						" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code where cust.sex in ('1','2')")
				.append(wheresql2).append("))c ");
		// and cust.classdept_no='' and cust.s_code='' and cust.class_no=''
		// and cust.cut_type='' and cust.fee_type and cust.stuemp_no>'' and
		// cust.stuemp_no<''
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());

			query.addScalar("femaleavg", Hibernate.FLOAT);
			query.addScalar("maleavg", Hibernate.FLOAT);
			query.addScalar("totavg", Hibernate.FLOAT);
			List list = query.list();
			List result = new ArrayList();
			float avgValue = 0;
			if (!"".equals(selPer)) {
				Map avgMap = (Map) getSpecStat(meal).get(0);
				avgValue = Float.parseFloat(avgMap.get("totavg").toString());

			}
			for (int i = 0; i < list.size(); i++) {
				Object[] objects = (Object[]) list.get(i);

				
				if ((Float.parseFloat(objects[2].toString()) < bavgRange)
							|| (Float.parseFloat(objects[2].toString()) > eavgRange)) {
						continue;
				}
				

				if (!"".equals(selPer)) {
					// 比较值
					float compValue = 0;
					if ("up".equals(selPer)) {
						compValue = avgValue * perRange / 100 + avgValue;
						if (compValue > Float.parseFloat(objects[2].toString())) {
							continue;
						}
					}
					if ("down".equals(selPer)) {
						compValue = avgValue - avgValue * perRange / 100;
						if (compValue < Float.parseFloat(objects[2].toString())) {
							continue;
						}
					}

				}
				HashMap accMap = new HashMap();
				accMap.put("acctime", bDate + "-" + eDate);
				accMap.put("femaleavg", nullToString(objects[0]));
				accMap.put("maleavg", nullToString(objects[1]));
				accMap.put("totavg", nullToString(objects[2]));
				result.add(accMap);
			}

			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}

	// 平均消费金额，人数分布图
	public List getConsemeAvg(String bDate, String eDate, String deptNo,
			String specNo, String classNo, int custType, int feeType,
			String bStuempNo, String eStuempNo, int per, String meal,
			float bavgRange, float eavgRange, String selPer, int perRange) {
 		StringBuffer strSql = new StringBuffer(1024);
		
		strSql .append(" select  count(cut_id) num,round(avg,0)as  amavg from ( ")
				.append(
						" select cust.cut_id  cut_id, count(rc.amount) amcount ," )
	
				.append(" ((sum(rc.amount)/count(rc.amount))/100) avg")
				.append(" from ykt_cur.t_rcstatdata rc ")
				.append(
						" inner join ykt_cur.t_pif_card card on rc.card_no=card.card_id")
				.append(
						" inner join ykt_cur.t_cif_customer cust on card.cosumer_id=cust.cut_id")
				.append(
						" inner join ykt_cur.t_cif_cuttypefee ctype on cust.cut_type=ctype.cut_type")
				.append(
						" inner join ykt_cur.t_pif_feetype fee on cust.fee_type = fee.fee_type")
				.append(
						" inner join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code")
				.append(
						" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code")
				.append(" where rc.tx_date>='").append(bDate).append(
						"' and rc.tx_date<='").append(eDate).append("'");
		// .append(" where rc.meal=:qmeal and rc.tx_date>=:qbDate and
		// rc.tx_date<=:qeDate");
		// 添加分析条件
		if (!"".equals(meal)) {
			strSql.append(" and rc.meal='").append(meal).append("'");
		}
		if (!"".equals(deptNo)) {
			strSql.append(" and cust.classdept_no='").append(deptNo)
					.append("'");
		}
		if (!"".equals(specNo)) {
			strSql.append(" and cust.s_code='").append(specNo).append("'");
		}
		if (!"".equals(classNo)) {
			strSql.append(" and cust.class_no='").append(classNo).append("'");
		}
		if (custType > 0) {
			strSql.append(" and cust.cut_type=").append(custType);
		}
		if (feeType > 0) {
			strSql.append(" and cust.fee_type=").append(feeType);
		}
		if (!"".equals(bStuempNo)) {
			strSql.append(" and cust.stuemp_no>='").append(bStuempNo).append(
					"'");
		}
		if (!"".equals(eStuempNo)) {
			strSql.append(" and cust.stuemp_no<='").append(eStuempNo).append(
					"'");
		}

		strSql
				.append(
						" group by cust.cut_id,")
				.append(
						" cust.cut_name")
				.append(" ");
		if (!"".equals(meal)) {
			strSql.append(",rc.meal");
		}
		if ("".equals(meal)){
			per=per*3;
		}
		strSql.append(" having count(rc.amount) >=").append(per)
		
			.append(" ) w group by round(avg,0) ").append("   order by round(avg,0) " );

		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(strSql.toString());
			query.addScalar("num", Hibernate.INTEGER);
			query.addScalar("amavg", Hibernate.FLOAT);
			List list = query.list();
			List result = new ArrayList();
			float avgValue = 0;
			if (!"".equals(selPer)) {
				Map avgMap = (Map) getSpecStat(meal).get(0);
				avgValue = Float.parseFloat(avgMap.get("totavg").toString());
				

			}
			for (int i = 0; i < list.size(); i++) {
				Object[] objects = (Object[]) list.get(i);
			
				
					if ((Float.parseFloat(objects[1].toString()) < bavgRange)
							|| (Float.parseFloat(objects[1].toString()) > eavgRange)) {
						continue;
					}
				
				if (!"".equals(selPer)) {
					// 比较值
					float compValue = 0;
					if ("up".equals(selPer)) {
						compValue = avgValue * perRange / 100 + avgValue;
						if (compValue > Float
								.parseFloat(objects[1].toString())) {
							continue;
						}
					}
					if ("down".equals(selPer)) {
						compValue = avgValue - avgValue * perRange / 100;
						if (compValue < Float
								.parseFloat(objects[1].toString())) {
							continue;
						}
					}

				}
			

				HashMap accMap = new HashMap();
				accMap.put("num", objects[0]);
				accMap.put("amavg", objects[1]);
				result.add(accMap);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}
	}
	
	/*
	 * 消费信息统计分析
	 */
	public List consuemAnalyse(
			String bDate,String eDate,
			String dept,String spec,
			String classNo,int custType,
			int cardType,String serialType,
			String bStuempNo,String eStuempNo,
			float bConsume,float eConsume,
			String groupedlist,int shopId){
		StringBuffer sqlstr = new StringBuffer(1024);
		//加入select和要分组的内容
		sqlstr.append(consumeSqlSelectAndGroup(groupedlist));
		//加入from和where条件
		sqlstr.append(consumeSqlFromAndWhere(
				bDate,eDate,
				dept,spec,
				classNo,custType,
				cardType,serialType,
				bStuempNo,eStuempNo,
				bConsume,eConsume,shopId,"0","1"));
		
		//加入group by语句
		sqlstr.append(getGroupContext(groupedlist,1));
		
		//加入order by语句
		sqlstr.append(getGroupContext(groupedlist,2));
		
		Session session = HibernateSessionFactory.currentSession();
		try {
			//System.out.println(sqlstr.toString());
			SQLQuery query = session.createSQLQuery(sqlstr.toString());
			
			query.addScalar("num", Hibernate.INTEGER);
			query.addScalar("money", Hibernate.DOUBLE);
			query.addScalar("avg", Hibernate.DOUBLE);
			query.addScalar("serial_type",Hibernate.STRING);
			query.addScalar("trademsg",Hibernate.STRING);
			query.addScalar("classdept_no",Hibernate.STRING);
			query.addScalar("dept_name",Hibernate.STRING);
			query.addScalar("s_code",Hibernate.STRING);
			query.addScalar("s_name",Hibernate.STRING);
			query.addScalar("class_no",Hibernate.STRING);
			query.addScalar("cut_type",Hibernate.INTEGER);
			query.addScalar("type_name",Hibernate.STRING);
			query.addScalar("type_id",Hibernate.INTEGER);
			query.addScalar("shop_id",Hibernate.INTEGER);
			query.addScalar("shop_name",Hibernate.STRING);
			query.addScalar("device_id",Hibernate.INTEGER);
			query.addScalar("device_name",Hibernate.STRING);
			
			List list = query.list();
			List result = new ArrayList();
			int totNum = 0;
			double totMoney = 0;
			Iterator iter = list.iterator();
			while (iter.hasNext()){
				Object[] objs = (Object[])iter.next(); 
				HashMap hm = new HashMap();
				totNum = totNum + Integer.parseInt(nullToString(objs[0]));
				totMoney = totMoney + Double.parseDouble(nullToString(objs[1]));
				hm.put("num",objs[0]);
				hm.put("money",objs[1]);
				hm.put("avg",objs[2]);
				hm.put("serialType",objs[3]);
				hm.put("serialTypeName",objs[4]);
				hm.put("deptNo",objs[5]);
				hm.put("deptName",objs[6]);
				hm.put("specNo",objs[7]);
				hm.put("specName",objs[8]);
				hm.put("classNo",objs[9]);
				hm.put("cutType",objs[10]);
				hm.put("cutTypeName",objs[11]);
				hm.put("cardType",objs[12]);
				hm.put("cardTypeName",getCardTypeName(18,Integer.parseInt(nullToString(objs[12]))));
				hm.put("shopid",objs[13]);
				hm.put("shopname",objs[14]);
				hm.put("deviceid",objs[15]);
				hm.put("devicename",objs[16]);
				
				result.add(hm);
			}
			if (list.size()>0){
				//最后加入合计值和总体平均
				HashMap hm = new HashMap();
				hm.put("num",new Integer(totNum));
				hm.put("money",new Double(totMoney));
				hm.put("avg",new Double(totMoney/totNum));
				hm.put("serialType"," ");
				hm.put("serialTypeName"," ");
				hm.put("deptNo"," ");
				hm.put("deptName"," ");
				hm.put("specNo"," ");
				hm.put("specName"," ");
				hm.put("classNo"," ");
				hm.put("cutType"," ");
				hm.put("cutTypeName"," ");
				hm.put("cardType"," ");
				hm.put("cardTypeName"," ");
				hm.put("shopid"," ");
				hm.put("shopname"," ");
				hm.put("deviceid"," ");
				hm.put("devicename"," ");
				
				String strVal = "----合  计：";
				if (groupedlist.indexOf("tradetype")>=0){
					hm.put("serialTypeName",strVal);
				}else if (groupedlist.indexOf("dept")>=0){
					hm.put("deptName",strVal);
				}else if (groupedlist.indexOf("spec")>=0){
					hm.put("specName",strVal);
				}else if (groupedlist.indexOf("class")>=0){
					hm.put("classNo",strVal);
				}else if (groupedlist.indexOf("custtype")>=0){
					hm.put("cutTypeName",strVal);
				}else if (groupedlist.indexOf("cardtype")>=0){
					hm.put("cardTypeName",strVal);
				}else if (groupedlist.indexOf("busi")>=0){
					hm.put("shopname",strVal);
				}else if (groupedlist.indexOf("device")>=0){
					hm.put("devicename",strVal);
				}			
				result.add(hm);			
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}

	}
	
	/*
	 * 门禁信息统计分析
	 */

	public List entranceAnalyse(
			String bDate,String eDate,
			String dept,String spec,
			String classNo,int custType,
			int cardType,String serialType,
			String bStuempNo,String eStuempNo,
			String groupedlist){		
		StringBuffer sqlstr = new StringBuffer(1024);
		//添加select 和分组条件
		sqlstr.append(entranceSqlSelectAndGroup(groupedlist));
		
		//加入from和where条件
		sqlstr.append(entranceSqlFromAndWhere(
				bDate,eDate,
				dept,spec,
				classNo,custType,
				cardType,serialType,
				bStuempNo,eStuempNo));
		
		//sqlstr.append(" group by dev.dev_usage ");
		sqlstr.append(entranceOrderAndGroup(groupedlist,1));
		
		//sqlstr.append(" order by dev.dev_usage");
		sqlstr.append(entranceOrderAndGroup(groupedlist,2));
		Session session = HibernateSessionFactory.currentSession();
		try {
			//System.out.println(sqlstr.toString());
			SQLQuery query = session.createSQLQuery(sqlstr.toString());
			query.addScalar("num", Hibernate.INTEGER);
			query.addScalar("dev_usage",Hibernate.STRING);
			
			query.addScalar("classdept_no",Hibernate.STRING);
			query.addScalar("dept_name",Hibernate.STRING);
			query.addScalar("s_code",Hibernate.STRING);
			query.addScalar("s_name",Hibernate.STRING);
			query.addScalar("class_no",Hibernate.STRING);
			query.addScalar("cut_type",Hibernate.INTEGER);
			query.addScalar("type_name",Hibernate.STRING);
			query.addScalar("type_id",Hibernate.INTEGER);
			
			
			List list = query.list();
			List result = new ArrayList();
			int totNum = 0;
			Iterator iter = list.iterator();
			while (iter.hasNext()){
				Object[] objs = (Object[])iter.next(); 
				HashMap hm = new HashMap();
				totNum = totNum + Integer.parseInt(nullToString(objs[0]));				
				hm.put("num",objs[0]);
				hm.put("devUse",objs[1]);
				hm.put("devUseName",getCardTypeName(81,Integer.parseInt(nullToString(objs[1]))));
				hm.put("deptNo",objs[2]);
				hm.put("deptName",objs[3]);
				hm.put("specNo",objs[4]);
				hm.put("specName",objs[5]);
				hm.put("classNo",objs[6]);
				hm.put("cutType",objs[7]);
				hm.put("cutTypeName",objs[8]);
				hm.put("cardType",objs[9]);
				hm.put("cardTypeName",getCardTypeName(18,Integer.parseInt(nullToString(objs[9]))));				
				result.add(hm);
			}
			//如果记录不为空，加入合计功能
			if (list.size()>0){
				HashMap hm = new HashMap();
				hm.put("num",new Integer(totNum));
				hm.put("devuse","");
				hm.put("deptNo"," ");
				hm.put("specNo"," ");
				hm.put("cutType"," ");
				hm.put("cardType"," ");
				
				hm.put("devUseName"," ");
				hm.put("deptName"," ");
				hm.put("specName"," ");
				hm.put("classNo"," ");
				hm.put("cutTypeName"," ");
				hm.put("cardTypeName"," ");
				
				String strVal = "----合  计：";
				if (groupedlist.indexOf("dept")>=0){				
					hm.put("deptName",strVal);
				}else if (groupedlist.indexOf("spec")>=0){
					hm.put("deptName",strVal);
				}else if (groupedlist.indexOf("class")>=0){
					hm.put("classNo",strVal);
				}else if (groupedlist.indexOf("custtype")>=0){
					hm.put("cutTypeName",strVal);
				}else if (groupedlist.indexOf("cardtype")>=0){
					hm.put("cardTypeName",strVal);
				}else if (groupedlist.indexOf("devuse")>=0){
					hm.put("devUseName",strVal);
				}			
				result.add(hm);			
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}

	}
	
	
	/*
	 * 消费信息查询
	 */
	public List consuemQuery(
			String bDate,String eDate,
			String dept,String spec,
			String classNo,int custType,
			int cardType,String serialType,
			String bStuempNo,String eStuempNo,
			float bConsume,float eConsume,
			int shopId,String sex){
		StringBuffer sqlstr = new StringBuffer(1024);
		//加入select和要分组的内容
		sqlstr.append("select cust.sex,cust.stuemp_no,cust.cut_name,cust.class_no,")
		.append("dept.dept_name,spec.s_name,cuttype.type_name,count(*) num,sum(trade_fee)money ")
		//加入from和where条件
		.append(consumeSqlFromAndWhere(
				bDate,eDate,
				dept,spec,
				classNo,custType,
				cardType,serialType,
				bStuempNo,eStuempNo,
				bConsume,eConsume,shopId,sex,"0"));
		
		//加入group by语句
		sqlstr.append(" group by cust.sex,cust.stuemp_no,cust.cut_name,cust.class_no,dept.dept_name,spec.s_name,cuttype.type_name");
		
		//加入order by语句
		sqlstr.append(" order by dept.dept_name,spec.s_name");
		
		Session session = HibernateSessionFactory.currentSession();
		try {
			//System.out.println(sqlstr.toString());
			SQLQuery query = session.createSQLQuery(sqlstr.toString());
			
			query.addScalar("sex", Hibernate.STRING);
			query.addScalar("stuemp_no", Hibernate.STRING);
			query.addScalar("cut_name", Hibernate.STRING);
			query.addScalar("class_no",Hibernate.STRING);
			query.addScalar("dept_name",Hibernate.STRING);
			query.addScalar("s_name",Hibernate.STRING);
			query.addScalar("type_name",Hibernate.STRING);
			query.addScalar("num",Hibernate.INTEGER);
			query.addScalar("money",Hibernate.DOUBLE);
			
			List list = query.list();
			List result = new ArrayList();
			Iterator iter = list.iterator();
			while (iter.hasNext()){
				Object[] objs = (Object[])iter.next(); 
				
				if (bConsume>0){
					if (Float.parseFloat(nullToString(objs[8]))<bConsume){
						continue;
					}
				}
				if (eConsume>0){
					if (Float.parseFloat(nullToString(objs[8]))>eConsume){
						continue;
					}
				}
				/*
				if ((Float.parseFloat(nullToString(objs[8]))<bConsume)||
						(Float.parseFloat(nullToString(objs[8]))>eConsume)){
					continue;
				}
				*/
				HashMap hm = new HashMap();
				hm.put("custSex",getSex(objs[0]));
				hm.put("stuempNo",objs[1]);
				hm.put("custName",objs[2]);
				hm.put("classNo",objs[3]);
				hm.put("deptName",objs[4]);
				hm.put("specName",objs[5]);
				hm.put("custType",objs[6]);
				hm.put("consumeNum",objs[7]);
				hm.put("consumeMoney",objs[8]);
				
				result.add(hm);
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		} finally {
			HibernateSessionFactory.closeSession();
		}

	}

	private String getSex(Object o){
		String sex = "";
		if (o==null){
			return sex;
		}else if ("1".equals(o.toString())){
			return "男";
		}else if ("2".equals(o.toString())){
			return "女";
		}else{
			return "";
		}
	}
	private String mealTrans(String in) {
		if ("bk".equals(in.trim())) {
			return "早餐";
		} else if ("lun".equals(in.trim())) {
			return "午餐";
		} else if ("sup".equals(in.trim())) {
			return "晚餐";
		} else {
			return "全天";
		}
	}

	private String nullToString(Object o) {
		if ((o == null)) {
			return "0";
		} else if ("".equals(o.toString())) {
			return "0";
		} else {
			return o.toString();
		}
	}
	
	/**
	 * 返回数据字典类别名称
	 * @param dictvalue
	 * @return
	 */
	public String getCardTypeName(int dictno,int dictvalue){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery("select dict_caption from ykt_cur.t_pif_dictionary where dict_no=:dictno and dict_value=:dictvalue");
			query.setInteger("dictvalue",dictvalue);
			query.setInteger("dictno",dictno);
			query.addScalar("dict_caption",Hibernate.STRING);
			List qryList = query.list();
			if (qryList.size()==0){
				return "";
			}else{
				String caption = qryList.get(0).toString();
				return caption;
			}
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 认证信息类select语句和相关的分组信息
	 * @param groupedlist
	 * @return
	 */
	private String entranceSqlSelectAndGroup(String groupedlist){
		StringBuffer sqlstr = new StringBuffer(512);
		sqlstr.append("select count(*)num");
		//group by 条件开始
		if (groupedlist.indexOf("dept")>=0){
			sqlstr.append(",cust.classdept_no,dept.dept_name");
		}else{
			sqlstr.append(",'' as classdept_no,'' as dept_name");
		}
		if (groupedlist.indexOf("spec")>=0){
			sqlstr.append(",cust.s_code,spec.s_name");
		}else{
			sqlstr.append(",'' as s_code,'' as s_name");
		}
		if (groupedlist.indexOf("class")>=0){
			sqlstr.append(",cust.class_no");
		}else{
			sqlstr.append(",'' as class_no");
		}
		if (groupedlist.indexOf("custtype")>=0){
			sqlstr.append(",cust.cut_type,cuttype.type_name");
		}else{
			sqlstr.append(",'' as cut_type,'' as type_name");
		}
		if (groupedlist.indexOf("cardtype")>=0){
			sqlstr.append(",card.type_id");
		}else{
			sqlstr.append(",'' as type_id");
		}
		if (groupedlist.indexOf("devuse")>=0){
			sqlstr.append(",dev.dev_usage");
		}else{
			sqlstr.append(",'' as dev_usage");
		}
		//group by 条件结束		
		return sqlstr.toString();
		
	}
	
	/**
	 * 认证信息类的from和where查询条件
	 * @param bDate
	 * @param eDate
	 * @param dept
	 * @param spec
	 * @param classNo
	 * @param custType
	 * @param cardType
	 * @param serialType
	 * @param bStuempNo
	 * @param eStuempNo
	 * @return
	 */
	private String entranceSqlFromAndWhere(
			String bDate,String eDate,
			String dept,String spec,
			String classNo,int custType,
			int cardType,String serialType,
			String bStuempNo,String eStuempNo){
		StringBuffer sqlstr = new StringBuffer(512);
		sqlstr.append(" from (")
		.append(" select tx_date,tx_time,device_id,cust_id,card_no")
		.append(" from ykt_cur.t_door_txdtl ")
		.append(" union all")
		.append(" select tx_date,tx_time,device_id,cust_id,card_no")
		.append(" from ykt_his.t_door_txdtl_his) dtl")
		.append(" left join ykt_cur.t_cif_customer cust on dtl.cust_id=cust.cut_id")
		.append(" left join ykt_cur.t_cif_cuttypefee cuttype on cust.cut_type = cuttype.cut_type")
		.append(" left join ykt_cur.t_pif_device dev on dtl.device_id=dev.device_id")
		.append(" left join ykt_cur.t_pif_card card on dtl.card_no = card.card_id")
		.append(" left join ykt_cur.t_cif_dept dept on cust.classdept_no = dept.dept_code")
		.append(" left join ykt_cur.t_cif_speciality spec on cust.s_code = spec.s_code")
		.append(" where 1=1 ");
		//where条件开始---------
		if (bDate.length()>0){
			sqlstr.append(" and dtl.tx_date>='").append(bDate).append("'");
		}
		if (eDate.length()>0){
			sqlstr.append(" and dtl.tx_date<='").append(eDate).append("'");
		}
		if (dept.length()>0){
			sqlstr.append(" and cust.classdept_no in (").append(getDeptByParent(dept)).append(")");
		}
		if (spec.length()>0){
			sqlstr.append(" and cust.s_code='").append(spec).append("'");
		}
		if (classNo.length()>0){
			sqlstr.append(" and cust.class_no='").append(classNo).append("'");
		}
		if (custType!=0){
			sqlstr.append(" and cust.cut_type=").append(custType);
		}
		if (cardType!=0){
			sqlstr.append(" and card.type_id=").append(cardType);
		}
		if (serialType.length()>0){
			sqlstr.append(" and dev.dev_usage='").append(serialType).append("'");
		}
		if (bStuempNo.length()>0){
			sqlstr.append(" and cust.stuemp_no>='").append(bStuempNo).append("'");
		}
		if (eStuempNo.length()>0){
			sqlstr.append(" and cust.stuemp_no<='").append(eStuempNo).append("'");
		}
		//where条件结束-------------
		return sqlstr.toString();
	}
	
	private String entranceOrderAndGroup(String groupedStr,int sign){
		String[] grpList = groupedStr.split(",");
		int grpSize = grpList.length;
		if (grpSize == 0){
			return "";
		}
		StringBuffer grpStr = new StringBuffer(512);
		String currGrp = "";
		if (sign==1){
			grpStr.append(" group by '' ");
		}else{
			grpStr.append(" order by '' ");
		}
		
		for (int i=0;i<grpSize;i++){
			currGrp = grpList[i].toString();
			if ("dept".equals(currGrp)){
				if (sign==1){
					grpStr.append(",cust.classdept_no,dept.dept_name");
				}else{
					grpStr.append(",cust.classdept_no");
				}				
			}else if ("spec".equals(currGrp)){
				if (sign==1){
					grpStr.append(",cust.s_code,spec.s_name");
				}else{
					grpStr.append(",cust.s_code");
				}				
			}else if ("class".equals(currGrp)){
				grpStr.append(",cust.class_no");
			}else if ("custtype".equals(currGrp)){
				if (sign==1){
					grpStr.append(",cust.cut_type,cuttype.type_name");
				}else{
					grpStr.append(",cust.cut_type");
				}				
			}else if ("cardtype".equals(currGrp)){
				grpStr.append(",card.type_id");
			}else if ("devuse".equals(currGrp)){
					grpStr.append(",dev.dev_usage");				
			}
		}
		return grpStr.toString();
	}

	/**
	 * 根据分组信息列表进行分组和排序
	 * @param groupedStr分组信息
	 * @param sign标志，是分组还是排序，1分组，其他为排序
	 * @return
	 */
	private String getGroupContext(String groupedStr,int sign){
		String[] grpList = groupedStr.split(",");
		int grpSize = grpList.length;
		if (grpSize == 0){
			return "";
		}
		StringBuffer grpStr = new StringBuffer(512);
		String currGrp = "";
		if (sign==1){
			grpStr.append(" group by '' ");
		}else{
			grpStr.append(" order by '' ");
		}
		
		for (int i=0;i<grpSize;i++){
			currGrp = grpList[i].toString();
			if ("dept".equals(currGrp)){
				if (sign==1){
					grpStr.append(",cust.classdept_no,dept.dept_name");
				}else{
					grpStr.append(",cust.classdept_no");
				}				
			}else if ("spec".equals(currGrp)){
				if (sign==1){
					grpStr.append(",cust.s_code,spec.s_name");
				}else{
					grpStr.append(",cust.s_code");
				}				
			}else if ("class".equals(currGrp)){
				grpStr.append(",cust.class_no");
			}else if ("custtype".equals(currGrp)){
				if (sign==1){
					grpStr.append(",cust.cut_type,cuttype.type_name");
				}else{
					grpStr.append(",cust.cut_type");
				}				
			}else if ("cardtype".equals(currGrp)){
				grpStr.append(",card.type_id");
			}else if ("tradetype".equals(currGrp)){
				if (sign==1){
					grpStr.append(",ser.serial_type,tc.trademsg");
				}else{
					grpStr.append(",ser.serial_type");
				}				
			}else if ("busi".equals(currGrp)){
				if (sign==1){
					grpStr.append(",shop.shop_id,shop.shop_name");
				}else{
					grpStr.append(",shop.shop_id");
				}				
			}else if ("device".equals(currGrp)){
				if (sign==1){
					grpStr.append(",ser.device_id,dev.device_name");
				}else{
					grpStr.append(",ser.device_id");
				}				
			}
		}
		return grpStr.toString();
	}
	
	private String consumeSqlSelectAndGroup(String groupedlist){
		StringBuffer sqlstr = new StringBuffer(512);
		sqlstr.append("select count(*) num,sum(trade_fee)money,NVL(sum(trade_fee)/count(*),0)avg");
		//.append(",()as totnum");
		//group by 条件开始
		if (groupedlist.indexOf("tradetype")>=0){
			sqlstr.append(",ser.serial_type,tc.trademsg");
		}else{
			sqlstr.append(",'' as serial_type,'' as trademsg");
		}
		if (groupedlist.indexOf("dept")>=0){
			sqlstr.append(",cust.classdept_no,dept.dept_name");
		}else{
			sqlstr.append(",'' as classdept_no,'' as dept_name");
		}
		if (groupedlist.indexOf("spec")>=0){
			sqlstr.append(",cust.s_code,spec.s_name");
		}else{
			sqlstr.append(",'' as s_code,'' as s_name");
		}
		if (groupedlist.indexOf("class")>=0){
			sqlstr.append(",cust.class_no");
		}else{
			sqlstr.append(",'' as class_no");
		}
		if (groupedlist.indexOf("custtype")>=0){
			sqlstr.append(",cust.cut_type,cuttype.type_name");
		}else{
			sqlstr.append(",'' as cut_type,'' as type_name");
		}
		if (groupedlist.indexOf("cardtype")>=0){
			sqlstr.append(",card.type_id");
		}else{
			sqlstr.append(",'' as type_id");
		}
		if (groupedlist.indexOf("busi")>=0){
			sqlstr.append(",shop.shop_id,shop.shop_name");
		}else{
			sqlstr.append(",'' as shop_id,'' as shop_name");
		}
		if (groupedlist.indexOf("device")>=0){
			sqlstr.append(",ser.device_id,dev.device_name");
		}else{
			sqlstr.append(",'' as device_id,'' as device_name");
		}
		//group by 条件结束
		return sqlstr.toString();
	}
	
	/**
	 * 消费信息查询和统计分析条件的from，where语句
	 * @param bDate
	 * @param eDate
	 * @param dept
	 * @param spec
	 * @param classNo
	 * @param custType
	 * @param cardType
	 * @param serialType
	 * @param bStuempNo
	 * @param eStuempNo
	 * @param bConsume
	 * @param eConsume
	 * @return
	 */
	private String consumeSqlFromAndWhere(
			String bDate,String eDate,
			String dept,String spec,
			String classNo,int custType,
			int cardType,String serialType,
			String bStuempNo,String eStuempNo,
			float bConsume,float eConsume,int shopId,String sex,String sign){
		StringBuffer sqlstr = new StringBuffer(512);
		sqlstr.append(" from (")
		.append(" select customer_id,operate_date,operate_time,device_id,card_id,trade_fee,serial_type,oper_code,SERIAL_STATE")
		.append(" from ykt_cur.t_tif_tradeserial ")
		.append(" union all")
		.append(" select customer_id,operate_date,operate_time,device_id,card_id,trade_fee,serial_type,oper_code,SERIAL_STATE")
		.append(" from ykt_his.t_tif_tradeserial_his)ser")
		.append(" left join ykt_cur.t_cif_customer cust on ser.customer_id=cust.cut_id")
		.append(" left join ykt_cur.t_cif_dept dept on cust.classdept_no=dept.dept_code")
		.append(" left join ykt_cur.t_cif_speciality spec on cust.s_code=spec.s_code")
		.append(" left join ykt_cur.t_cif_cuttypefee cuttype on cust.cut_type = cuttype.cut_type")
		.append(" left join ykt_cur.t_pif_device dev on ser.device_id=dev.device_id")
		.append(" left join ykt_cur.t_pif_card card on ser.card_id = card.card_id")
		.append(" left join ykt_cur.t_pif_tradecode tc on ser.serial_type = tc.tradecode")
		.append(" left join ykt_cur.t_cif_shop_pos sp on ser.device_id = sp.device_id")
		.append(" left join ykt_cur.t_cif_shop shop on sp.shop_id = shop.shop_id")
		.append(" where ser.SERIAL_STATE=2 ");
		//where条件开始---------
		if (bDate.length()>0){
			sqlstr.append(" and ser.operate_date>='").append(bDate).append("'");
		}
		if (eDate.length()>0){
			sqlstr.append(" and ser.operate_date<='").append(eDate).append("'");
		}
		if (dept.length()>0){
			sqlstr.append(" and cust.classdept_no in (").append(getDeptByParent(dept)).append(")");
		}
		if (spec.length()>0){
			sqlstr.append(" and cust.s_code='").append(spec).append("'");
		}
		if (classNo.length()>0){
			sqlstr.append(" and cust.class_no='").append(classNo).append("'");
		}
		if (custType!=0){
			sqlstr.append(" and cust.cut_type=").append(custType);
		}
		if (cardType!=0){
			sqlstr.append(" and card.type_id=").append(cardType);
		}
		if (serialType.length()>0){
			sqlstr.append(" and ser.serial_type='").append(serialType).append("'");
		}
		if (bStuempNo.length()>0){
			sqlstr.append(" and cust.stuemp_no>='").append(bStuempNo).append("'");
		}
		if (eStuempNo.length()>0){
			sqlstr.append(" and cust.stuemp_no<='").append(eStuempNo).append("'");
		}
		if ("1".equals(sign)){
			if (bConsume!=0){
				sqlstr.append(" and ser.trade_fee>=").append(bConsume);
			}
			if (eConsume!=0){
				sqlstr.append(" and ser.trade_fee<=").append(eConsume);
			}
			
		}
		if ("0".equals(sign)){
			if (!"0".equals(sex)){
				sqlstr.append(" and cust.sex='").append(sex).append("'");
			}
		}
		if (shopId!=0){
			sqlstr.append(" and shop.shop_id in (").append(getShopByParent(shopId)).append(")");
		}
		//where条件结束-------------
		return sqlstr.toString();
	}
	
	private String getShopByParent(int shopId){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery("select shop_id,shop_name,dept_id from ykt_cur.t_cif_shop start with shop_id=:shopid connect by prior shop_id=dept_id");			
			query.setInteger("shopid",shopId);
			query.addScalar("shop_id",Hibernate.STRING);
			query.addScalar("shop_name",Hibernate.STRING);
			query.addScalar("dept_id",Hibernate.STRING);
			List qryList = query.list();
			int size = qryList.size();
			if (size==0){
				return "";
			}else{
				StringBuffer shopIds = new StringBuffer(512);
				Iterator shopIter = qryList.iterator();
				while (shopIter.hasNext()){
					Object[] row = (Object[])shopIter.next();
					if (shopIter.hasNext()){
						shopIds.append(row[0]).append(",");
					}else{
						shopIds.append(row[0]);
					}
				}
				return shopIds.toString();
			}
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}

	}
	
	private String getDeptByParent(String deptId){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery("select dept_code,dept_name,parentdept_code from ykt_cur.t_cif_dept start with dept_code=:deptid connect by prior dept_code=parentdept_code");			
			query.setString("deptid",deptId);
			query.addScalar("dept_code",Hibernate.STRING);
			query.addScalar("dept_name",Hibernate.STRING);
			query.addScalar("parentdept_code",Hibernate.STRING);
			List qryList = query.list();
			int size = qryList.size();
			if (size==0){
				return "";
			}else{
				StringBuffer deptIds = new StringBuffer(512);
				Iterator deptIter = qryList.iterator();
				while (deptIter.hasNext()){
					Object[] row = (Object[])deptIter.next();
					if (deptIter.hasNext()){
						deptIds.append("'").append(row[0]).append("'").append(",");
					}else{
						deptIds.append("'").append(row[0]).append("'");
					}
				}
				return deptIds.toString();
			}
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}

	}

	private Log _log = LogFactory.getLog(TradeSerialDAO.class);
}
