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
	 * �̻������˻��䶯�����Ӫҵ�����ѽ��
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
	 * �����������ͳ��
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
	 * ��У��Ӫҵ����Աȣ�������
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
	 * ��У��Ӫҵ����Աȣ���
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
	 * ���̻�Ӫҵ���ͳ��
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
	 * ���̻�Ӫҵ����Ա�
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
	 * �̻������
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
	 * ����̻�����
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
	 * �����̻����㱨������С�ƣ�ͳ�Ƶ���Ϣ
	 * @param queryList
	 * @return
	 */
	private List analyzeShopAccountReport(String shopidStr,String beginDate,String endDate,String statType,Session session){
		Map deptShops = getDeptShop(shopidStr,session);
		List queryList = getShopBalance(shopidStr,beginDate,endDate,statType,session);
		
		String[] shopIds = shopidStr.substring(1, shopidStr.length()-1).split(",");
		
		//�̻���ϣ�keyΪ�̻�shopid��valueΪ�¼��̻��͵�ǰ�̻�������Ϣ�ļ���
		Map childrenMap = new HashMap();
		if(queryList!=null && queryList.size()>0){
			for(int i=0;i<queryList.size();i++){
				Map row = (Map) queryList.get(i);
				String currentDeptid = row.get("deptid")==null?"":row.get("deptid").toString();
				String currentShopid = row.get("shopid")==null?"":row.get("shopid").toString();
				
				if(ArrayUtils.contains(shopIds, currentDeptid)){
					//�¼��̻�������Ϣ
					List children = (List) childrenMap.get(currentDeptid);
					if(children==null){
						children = new ArrayList();
						childrenMap.put(currentDeptid, children);
					}
					children.add(row);
				} else if(ArrayUtils.contains(shopIds, currentShopid)){
					//�̻�������Ϣ
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
		//���̻������¼��̻�ʱ������ʾ���̻��Ľ�����Ϣ���������С�ƺ��ܼ���Ϣ
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
						//Ҷ�ӽڵ㣬û���¼��̻���ֱ�Ӳ��Ҹ��̻�������Ϣ
						row.put("deptname", shop.getShopName());
						row.put("shopname", shop.getDeptId());
						row.put("shopname", "");
						row.put("shopid", "");
						result.add(row);
						//����С��
						subtotalNum = subtotalNum+tradenum;
						subtotalAmt = subtotalAmt+tradeamt;
						//�����ܼ�
						totalNum = totalNum+tradenum;
						totalAmt = totalAmt+tradeamt;
						subtotal = true;
					} else if("2".equals(shop.getIsLeaf()) && currentDeptid.equals(shopId)){
						//��Ҷ�ӽڵ㣬�����¼��̻�������Ϣ
						row.put("deptname", shop.getShopName());
						row.put("deptid", shop.getDeptId());
						result.add(row);
						//����С��
						subtotalNum = subtotalNum+tradenum;
						subtotalAmt = subtotalAmt+tradeamt;
						//�����ܼ�
						totalNum = totalNum+tradenum;
						totalAmt = totalAmt+tradeamt;
						subtotal = true;
					} else {
						//�����
					}
				}
				//С��
				if(subtotal){
					Map subtotalMap = new HashMap();
					subtotalMap.put("shopname", "С��");
					subtotalMap.put("tradenum", String.valueOf(subtotalNum));
					subtotalMap.put("tradeamt", String.valueOf(subtotalAmt));
					result.add(subtotalMap);
				}
			}
		}
		//�����ܼ�
		if(result.size()>0){
			Map totalMap = new HashMap();
			totalMap.put("deptname", "�ܼ�");
			totalMap.put("tradenum",String.valueOf(totalNum));
			totalMap.put("tradeamt",String.valueOf(totalAmt));
			result.add(totalMap);
		}
		return result;
	}
	
	private Log _log = LogFactory.getLog(ReportShopBalanceDAO.class);
}
