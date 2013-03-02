/**
 * 
 */
package com.kingstargroup.ecard.hibernate.shop;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.Iterator;
import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.exceptions.PortalException;
import com.kingstargroup.ecard.hibernate.bras.TBrastransdtl;
import com.kingstargroup.ecard.portlet.shop.service.ShopService;
import com.kingstargroup.ecard.portlet.shop.service.ShopServiceFactory;
import com.kingstargroup.ecard.util.EcardConstants;
import com.liferay.portal.service.persistence.BasePersistence;

/**
 * Copyright (C), 2000-2005, Kingstar Co., Ltd.<br>
 * File name: ShopPersistence.java<br>
 * Description: <br>
 * Modify History: <br>
 * 操作类型 操作人 操作时间 操作内容<br>
 * ===================================<br>
 * 创建 Xiao Qi 2005-10-19 <br>
 * 
 * @author HLQ
 * @version
 * @since 1.0
 */
public class ShopPersistence extends BasePersistence {

	public synchronized List createShopJSList(String rootId)
			throws PortalException {
		List shopJSList = new ArrayList();
		nodeId = 1;
		shopJSList = _createShopJSList(rootId, "");
		return shopJSList;
	}

	private List getChildList(String fshopid) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Query q = s
					.createQuery(" from TShop where fshopid = :fshopid and status='1' order by shopid asc");
			q.setInteger("fshopid", Integer.parseInt(fshopid));
			q.setCacheable(true);
			return q.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}

	private List _createShopJSList(String parentId, String nodeParentId)
			throws DBSystemException {
		ShopService shopService = ShopServiceFactory.getService();

		List shopJSList = new ArrayList();
		try {
			List childList = getChildList(parentId);
			for (int i = 0; i < childList.size(); i++) {
				TShop shop = (TShop) childList.get(i);
				StringBuffer nodeBuff = new StringBuffer();
				nodeBuff.append(nodeId)// nodeId
						.append("|").append(nodeParentId).append("|");// parentId
				if (i == childList.size() - 1) {// ls
					nodeBuff.append("1|");
				} else {
					nodeBuff.append("0|");
				}
				nodeBuff.append("|");// path
				nodeBuff.append(shop.getShopname()).append("|");// name
				nodeBuff.append("|");// image
				nodeBuff.append(shop.getShopid());// href
				shopJSList.add(nodeBuff.toString());// add to list
				int parentNode = nodeId;
				nodeId++;
				/*
				 * process child list
				 */
				shopJSList
						.addAll(_createShopJSList(shop.getShopid().toString(),
								String.valueOf(parentNode)));
			}
		} catch (DBSystemException he) {
			throw he;
		} catch (Exception e) {
			e.printStackTrace();
		}
		return shopJSList;
	}

	public List getStoreList(String userid) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Query query = s
					.createQuery(" select sl.id.storeCode from StoreLimit sl where sl.id.operCode = :userid");
			query.setString("userid", userid);
			return query.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}

	}

	public void deleteStoreList(String userid) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Query query = s
					.createQuery(" from StoreLimit a where a.id.operCode = :userid");

			query.setString("userid", userid);
			Iterator it = query.iterate();
			while (it.hasNext()) {
				s.delete(it.next());
			}
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}

	public void saveStoreLimit(StoreLimit storelimit) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.save(storelimit);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}
	}

	public List getShopList(String userid) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			Query query = null;
				query = s.createQuery(" select a from TShop a,StoreLimit b where a.shopid=b.id.storeCode and b.id.operCode = :userid and a.status=1");
				query.setString("userid", userid);		
			return query.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}

	}
	
	
	public List getShopPosList(int shopid, String begindate, String enddate,
			String devphyId) throws DBSystemException {
		Session s = openSession();
		StringBuffer str = new StringBuffer(512);
		str.append("select posl.amount,posl.transdate,posl.transtime,posl.termid,posl.devphyId,posl.cardbefbal,posl.cardaftbal,")
		.append("cust.custName,cust.stuempno,cust.classname from ykt_cur.t_transdtl posl ")
		.append(" left join ykt_cur.t_card card on posl.cardno=card.cardno")
		.append(" left join ykt_cur.t_customer cust on card.custid=cust.custid")
		.append(" where posl.status = " + EcardConstants.POS_STATUS_SUCCESS)//POS交易的记录状态为：3-成功
     	.append(" and posl.transcode<>3290")
		.append(" and exists(select 1 from ykt_cur.t_shoppos shoppos where shoppos.devphyid=posl.devphyId and shoppos.shopid= :shopid)");
		
		if (!"".equals(begindate)){
			str.append(" and posl.transdate>=:begindate");
		}
		if (!"".equals(enddate)){
			str.append(" and posl.transdate<=:enddate");
		}
		if (!"".equals(devphyId)){
			str.append(" and posl.devphyId=:devphyId");
		}
		
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			query.setInteger("shopid", shopid);
			if (!"".equals(begindate)){
				query.setString("begindate", begindate);
			}
			if (!"".equals(enddate)){
				query.setString("enddate", enddate);
			}
			if (!"".equals(devphyId)){
				query.setString("devphyId", devphyId);
			}
			
			query.addScalar("amount", Hibernate.DOUBLE);
			query.addScalar("transdate",Hibernate.STRING);
			query.addScalar("transtime",Hibernate.STRING);
			query.addScalar("termid",Hibernate.INTEGER);
			query.addScalar("devphyId",Hibernate.STRING);
			query.addScalar("cardbefbal",Hibernate.DOUBLE);
			query.addScalar("cardaftbal",Hibernate.DOUBLE);
			query.addScalar("custName",Hibernate.STRING);
			query.addScalar("stuempno",Hibernate.STRING);
			query.addScalar("classname",Hibernate.STRING);
			
			List posLogInfo = query.list();
			List result = new ArrayList();
			Double totalAmount = 0.00 ;
			Double amount;
			
			if (posLogInfo!=null){
				for (int i = 0; i < posLogInfo.size(); i++) {
					Object[] objects = (Object[]) posLogInfo.get(i);
					HashMap cardInfoMap = new HashMap();
					cardInfoMap.put("amount", objects[0]);
					amount = Double.parseDouble(objects[0]+"");
					totalAmount += amount;
					cardInfoMap.put("transdate", objects[1]);
					cardInfoMap.put("transtime", objects[2]);
					cardInfoMap.put("termid", objects[3]);
					cardInfoMap.put("devphyId", objects[4]);
					cardInfoMap.put("cardbefbal", objects[5]);
					cardInfoMap.put("cardaftbal", objects[6]);
					cardInfoMap.put("custName", objects[7]);
					cardInfoMap.put("stuempno", objects[8]);
					cardInfoMap.put("classname", objects[9]);
					result.add(cardInfoMap);
				}
				
				if(posLogInfo.size()>0){
					//合计行
					HashMap cardInfoMap = new HashMap();
					cardInfoMap.put("custName", "合计");
					cardInfoMap.put("classname", "发生额总计：");
					cardInfoMap.put("amount", totalAmount);
					cardInfoMap.put("transdate", "交易次数 ");
					cardInfoMap.put("transtime", posLogInfo.size()+"次" );
					result.add(cardInfoMap);
				}
			
				return result;				
			}else{
				return posLogInfo;
			}
			
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}

	public List getBrasTransLogList(String begindate, String enddate,
			String refno,String stuempno, String custname, String oppaccno, String oppaccname,
			String status,String brastype) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			String sql = " from TBrastransdtl where transdate<=:enddate and transdate>=:begindate ";
			if (!"".equals(oppaccno)) {
				sql += "and oppaccno like :oppaccno ";
			}

			if (!"".equals(refno)) {
				sql += "and refno like :refno ";
			}
			
			if (!"".equals(stuempno)) {
				sql += "and stuempno like :stuempno ";
			}


			if (!"".equals(custname)) {
				sql += "and custname like :custname ";
			}

			if (!"".equals(oppaccname)) {
				sql += "and oppaccname like :oppaccname ";
			}
			if (!"-".equals(status)) {
				sql += "and status = :status ";
			}
			if (!"-".equals(brastype)) {
				sql += "and chkflag = :chkflag ";
			}
			sql += " order by refno desc";
			Query query = s.createQuery(sql);
			query.setString("enddate", enddate);
			query.setString("begindate", begindate);
			if (!"".equals(oppaccno)) {
				query.setString("oppaccno", "%" + oppaccno + "%");
			}

			if (!"".equals(refno)) {
				query.setString("refno", "%" + refno + "%");
			}
			
			if (!"".equals(stuempno)) {
				query.setString("stuempno", "%" + stuempno + "%");
			}

			if (!"".equals(custname)) {
				query.setString("custname", "%" + custname + "%");
			}

			if (!"".equals(oppaccname)) {
				query.setString("oppaccname", "%" + oppaccname + "%");
			}
			if (!"-".equals(status)) {
				query.setLong("status", Long.parseLong(status));
			}
			if (!"-".equals(brastype)) {
				query.setLong("chkflag", Long.parseLong(brastype));
			}

			return query.list();
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		}

	}

	private static final Log _log = LogFactory.getLog(ShopPersistence.class);
	private static int nodeId = 1;
	
}
