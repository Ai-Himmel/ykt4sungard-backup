/**
 * 
 */
package com.kingstargroup.advquery.reportshopbalance;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.lang.ArrayUtils;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;
import com.kingstargroup.advquery.shop.TCifShop;
/**
 * @author Administrator
 *
 */
public class ReportShopBalanceDAO {
	/**
	 * 商户整体账户变动情况，营业额，管理费金额
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getShopAccountChangeStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "ShopAccountChangeStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "ShopAccountChangeStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
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
	 * 消费总体情况统计
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAllConsumeStat(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AllConsumeStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AllConsumeStatMonthSQL";
			}

			Query query = session.getNamedQuery(execSQL);
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
	 * 各校区营业情况对比（笔数）
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAreaSalesNumCompare(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AreaSalesNumCompareSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AreaSalesNumCompareMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
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
	 * 各校区营业情况对比（金额）
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getAreaSalesMoneyCompare(String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "AreaSalesMoneyCompareSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "AreaSalesMoneyCompareMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
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
	 * 各商户营业情况统计
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getOneAccountStat(int shopId,String beginDate,String endDate,String statType){
		String execSQL = "";
		Session session = HibernateSessionFactory.currentSession();
		try {
			if (("bydate".equals(statType))||("byweek".equals(statType))){
				execSQL = "OneShopAccountChangeStatSQL";
			}else if ("bymonth".equals(statType)){
				execSQL = "OneShopAccountChangeStatMonthSQL";
			}
			Query query = session.getNamedQuery(execSQL);
			query.setInteger("shopid",shopId);
			query.setString("begindate",beginDate);
			query.setString("endate",endDate);
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
	 * 各商户营业情况对比
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getShopAccountCompare(String shopId,String beginDate,String endDate,String statType){
		StringBuffer execSQL = new StringBuffer(2000);
		HashMap map = new HashMap();
		if (("bydate".equals(statType))||("byweek".equals(statType))){
			execSQL.append("select new map(rsb.id.shopId as shopid,rsb.shopName as shopname,")
			.append("sum(rsb.tradeNum) as tradenum,sum(rsb.tradeAmt)as tradeamt,")
			.append("sum(rsb.mngAmt)as mngamt,sum(rsb.totalAmt)as totalamt) from TTifReportShopBalance rsb ")
			.append(" where rsb.id.balanceDate>='").append(beginDate).append("' and rsb.id.balanceDate<='").append(endDate)
			.append(" '").append(" and rsb.id.shopId in ").append(shopId)
			.append(" group by rsb.id.shopId,rsb.shopName");
		}else if ("bymonth".equals(statType)){
			execSQL.append("select new map(rsb.id.shopId as shopid,rsb.shopName as shopname,")
			.append("sum(rsb.tradeNum) as tradenum,sum(rsb.tradeAmt)as tradeamt,")
			.append("sum(rsb.mngAmt)as mngamt,sum(rsb.totalAmt)as totalamt)from TTifReportShopBalance as rsb ")
			.append("where substr(rsb.id.balanceDate,1,6)>='").append(beginDate)
			.append("' and substr(rsb.id.balanceDate,1,6)<='").append(endDate)
			.append("'").append(" and rsb.id.shopId in ").append(shopId)
			.append(" group by rsb.id.shopId,rsb.shopName");
		}

		Session session = HibernateSessionFactory.currentSession();
		try {
			Query query = session.createQuery(execSQL.toString());
			List list = query.list();
			return list;
		} catch (HibernateException e) {
			e.printStackTrace();
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 商户结算表
	 * @param shopId
	 * @param beginDate
	 * @param endDate
	 * @return
	 */
	public List getShopAccountReport(String shopidStr,String beginDate,String endDate,String statType){
		Session session = HibernateSessionFactory.currentSession();
		try {
			return analyzeShopAccountReport(shopidStr,beginDate,endDate,statType,session);
		} catch (HibernateException e) {
			e.printStackTrace();
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	private List getShopBalance(String shopidStr,String beginDate,String endDate,String statType,Session session){
		StringBuffer execHQL = new StringBuffer(2000);
		if (("bydate".equals(statType))){
			execHQL.append("select new map(rsb.id.shopId as shopid,rsb.shopName as shopname,")
			.append("sum(rsb.tradeNum) as tradenum,sum(rsb.tradeAmt)as tradeamt,rsb.deptId as deptid)")
			.append(" from TTifReportShopBalance rsb")
			.append(" where rsb.id.balanceDate>='").append(beginDate).append("' and rsb.id.balanceDate<='").append(endDate)
			.append("'").append(" and (rsb.deptId in ").append(shopidStr)
			.append(" or rsb.id.shopId in ").append(shopidStr).append(")")
			.append(" group by rsb.id.shopId,rsb.shopName,rsb.deptId")
			.append(" order by rsb.deptId,rsb.id.shopId");
		}else if ("bymonth".equals(statType)){
			execHQL.append("select new map(rsb.id.shopId as shopid,rsb.shopName as shopname,")
			.append("sum(rsb.tradeNum) as tradenum,sum(rsb.tradeAmt)as tradeamt,rsb.deptId as deptid")
			.append(",substr(rsb.id.balanceDate,1,6) as period) from TTifReportShopBalance as rsb")
			.append(" where substr(rsb.id.balanceDate,1,6)>='").append(beginDate)
			.append("' and substr(rsb.id.balanceDate,1,6)<='").append(endDate)
			.append("'").append(" and (rsb.deptId in ").append(shopidStr)
			.append(" or rsb.id.shopId in ").append(shopidStr).append(")")
			.append(" group by rsb.id.shopId,rsb.shopName,rsb.deptId,substr(rsb.id.balanceDate,1,6)")
			.append(" order by rsb.deptId,rsb.id.shopId,substr(rsb.id.balanceDate,1,6)");
		}else if ("byday".equals(statType)){
			execHQL.append("select new map(rsb.id.shopId as shopid,rsb.shopName as shopname,")
			.append("sum(rsb.tradeNum) as tradenum,sum(rsb.tradeAmt)as tradeamt,rsb.deptId as deptid")
			.append(",rsb.id.balanceDate as period) from TTifReportShopBalance rsb")
			.append(" where rsb.id.balanceDate>='").append(beginDate).append("' and rsb.id.balanceDate<='").append(endDate)
			.append("'").append(" and (rsb.deptId in ").append(shopidStr)
			.append(" or rsb.id.shopId in ").append(shopidStr).append(")")
			.append(" group by rsb.id.shopId,rsb.shopName,rsb.deptId,rsb.id.balanceDate")
			.append(" order by rsb.deptId,rsb.id.shopId,rsb.id.balanceDate");
		}
		Query query = session.createQuery(execHQL.toString());
		return query.list();
	}
	
	/**
	 * 获得商户名称
	 * @param shopidStr
	 * @param session
	 * @return
	 */
	private Map getDeptShop(String shopidStr,Session session){
		String hql = "from TCifShop s where s.shopId in "+shopidStr;
		Query query = session.createQuery(hql);
		List list = query.list();
		Map deptShops = new HashMap();
		if(list!=null && list.size()>0){
			for(int i=0;i<list.size();i++){
				TCifShop shop = (TCifShop) list.get(i);
				deptShops.put(shop.getShopId().toString(), shop);
			}
		}
		return deptShops;
	}
	
	/**
	 * 分析商户结算报表，生成小计，统计等信息
	 * @param queryList
	 * @return
	 */
	private List analyzeShopAccountReport(String shopidStr,String beginDate,String endDate,String statType,Session session){
		Map deptShops = getDeptShop(shopidStr,session);
		List queryList = getShopBalance(shopidStr,beginDate,endDate,statType,session);
		
		String[] shopIds = shopidStr.substring(1, shopidStr.length()-1).split(",");
		
		//商户结合，key为商户shopid，value为下级商户和当前商户结算信息的集合
		Map childrenMap = new HashMap();
		if(queryList!=null && queryList.size()>0){
			for(int i=0;i<queryList.size();i++){
				Map row = (Map) queryList.get(i);
				String currentDeptid = row.get("deptid")==null?"":row.get("deptid").toString();
				String currentShopid = row.get("shopid")==null?"":row.get("shopid").toString();
				
				if(ArrayUtils.contains(shopIds, currentDeptid)){
					//下级商户结算信息
					List children = (List) childrenMap.get(currentDeptid);
					if(children==null){
						children = new ArrayList();
						childrenMap.put(currentDeptid, children);
					}
					children.add(row);
				} else if(ArrayUtils.contains(shopIds, currentShopid)){
					//商户结算信息
					List children = (List) childrenMap.get(currentShopid);
					if(children==null){
						children = new ArrayList();
						childrenMap.put(currentShopid, children);
					}
					children.add(row);
				}
			}
		}
		
		List result = new ArrayList();
		int totalNum = 0;
		double totalAmt = 0.00d;
		//当商户存在下级商户时，则不显示该商户的结算信息，另外计算小计和总计信息
		for(int i=0;i<shopIds.length;i++){
			String shopId = shopIds[i];
			TCifShop shop = (TCifShop) deptShops.get(shopId);
			List children = (List) childrenMap.get(shopId);
			
			int subtotalNum = 0;
			double subtotalAmt = 0.00d;
			int tradenum = 0;
			double tradeamt = 0.00d;
			boolean subtotal = false;
			if(children!=null && children.size()>0){
				for(int j=0;j<children.size();j++){
					Map row = (Map) children.get(j);
					String currentDeptid = row.get("deptid")==null?"":row.get("deptid").toString();
					String currentShopid = row.get("shopid")==null?"":row.get("shopid").toString();
					tradenum = row.get("tradenum")==null?0:Integer.parseInt(row.get("tradenum").toString());
					tradeamt = row.get("tradeamt")==null?0.00d:Double.parseDouble(row.get("tradeamt").toString());
					if("1".equals(shop.getIsLeaf()) && currentShopid.equals(shopId)){
						//叶子节点，没有下级商户，直接查找该商户结算信息
						row.put("deptname", shop.getShopName());
						row.put("shopname", shop.getDeptId());
						row.put("shopname", "");
						row.put("shopid", "");
						result.add(row);
						//计算小计
						subtotalNum = subtotalNum+tradenum;
						subtotalAmt = subtotalAmt+tradeamt;
						//计算总计
						totalNum = totalNum+tradenum;
						totalAmt = totalAmt+tradeamt;
						subtotal = true;
					} else if("2".equals(shop.getIsLeaf()) && currentDeptid.equals(shopId)){
						//非叶子节点，查找下级商户结算信息
						row.put("deptname", shop.getShopName());
						row.put("deptid", shop.getDeptId());
						result.add(row);
						//计算小计
						subtotalNum = subtotalNum+tradenum;
						subtotalAmt = subtotalAmt+tradeamt;
						//计算总计
						totalNum = totalNum+tradenum;
						totalAmt = totalAmt+tradeamt;
						subtotal = true;
					} else {
						//不添加
					}
				}
				//小计
				if(subtotal){
					Map subtotalMap = new HashMap();
					subtotalMap.put("shopname", "小计");
					subtotalMap.put("tradenum", String.valueOf(subtotalNum));
					subtotalMap.put("tradeamt", String.valueOf(subtotalAmt));
					result.add(subtotalMap);
				}
			}
		}
		//生成总计
		if(result.size()>0){
			Map totalMap = new HashMap();
			totalMap.put("deptname", "总计");
			totalMap.put("tradenum",String.valueOf(totalNum));
			totalMap.put("tradeamt",String.valueOf(totalAmt));
			result.add(totalMap);
		}
		return result;
	}
	
	private Log _log = LogFactory.getLog(ReportShopBalanceDAO.class);
}
