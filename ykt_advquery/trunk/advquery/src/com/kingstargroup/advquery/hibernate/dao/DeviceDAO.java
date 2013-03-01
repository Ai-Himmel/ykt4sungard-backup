/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.common.DateUtilExtend;
public class DeviceDAO extends BasicDAO {
	/**
	 * Description:singleton pattern
	 * @return
	 * Modify History:
	 */
	public static DeviceDAO getInstance() {
		if (_instance == null) {
			_instance = new DeviceDAO();
		}
		return _instance;
	}
	
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: TradeSerialDAO根据日期取得设备的使用数<br>
	 * Return: List<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-10  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public List getDeviceUsed(
			int serialtype,
			String beginDate,
			String endDate,
			String statType)throws HibernateException{
		Session s = getSession();
		String nowDate = DateUtilExtend.getNowDate2();
		StringBuffer sqlStr = new StringBuffer();
		if ("bydate".equals(statType)){
			sqlStr.append("select balance_date,devuse from (")
			.append("select balance_date,count(distinct(device_id)) as devuse from ykt_cur.t_tif_report_oper")
			.append(" where seri_type="+serialtype+" and balance_date>='"+beginDate+"' and balance_date<='"+endDate+"'")
			.append(" group by balance_date")
			.append(" union all")
			.append(" select '"+nowDate+"' as balance_date,count(distinct(device_id)) devuse")
			.append(" from ykt_cur.t_tif_tradeserial where serial_type="+serialtype+")t")
			.append(" where balance_date>='"+beginDate+"' and balance_date<='"+endDate+"'")
			.append(" order by balance_date desc");
		}else if ("bymonth".equals(statType)){
			sqlStr.append("select balance_date,devuse from (")
			.append("select substr(balance_date,1,6) balance_date,count(distinct(device_id)) as devuse ")
			.append(" from ykt_cur.t_tif_report_oper")
			.append(" where seri_type="+serialtype+" and substr(balance_date,1,6)>='"+beginDate)
			.append(" ' and substr(balance_date,1,6)<='"+endDate+"'")
			.append(" group by substr(balance_date,1,6))t")
			.append(" where balance_date>='"+beginDate+"' and balance_date<='"+endDate+"'")
			.append(" order by balance_date desc");
		}
		try {
			System.out.println(sqlStr.toString());
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("balance_date",Hibernate.STRING);
			q.addScalar("devuse",Hibernate.INTEGER);
			return q.list();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}
	}
	/**
	 * Copyright (C), 2000-2006, Kingstar Co., Ltd.<br>
	 * File name: .java<br>
	 * Description: DeviceDAO取得设备总数<br>
	 * Return: String<br>
	 * Modify History: <br>
	 * 操作类型    操作人     操作时间       操作内容<br>
	 * ======================================<br>
	 *  创建      韩纪伟     2006-5-26  <br>
	 * @author   韩纪伟
	 * @version 
	 * @since 1.0
	 */
	public String getDeviceNum(String devType)throws HibernateException{
		Session s = getSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("Select count(*) as devnum from YKT_CUR.T_PIF_DEVICE ")
		.append(" where devtype in "+devType+" and state_id<5");
		try {
			System.out.println("devNum:"+sqlStr.toString());
			SQLQuery q = s.createSQLQuery(sqlStr.toString());
			q.addScalar("devnum",Hibernate.INTEGER);
			return q.list().get(0).toString();
		} catch (HibernateException he) {
			_log.error(he);
			return null;
		}
	}
	private static DeviceDAO _instance;
	private Log _log = LogFactory.getLog(DeviceDAO.class.getClass());
}
