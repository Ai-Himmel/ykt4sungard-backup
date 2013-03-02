package com.kingstargroup.ecard.hibernate.losecard;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.ecard.exceptions.DBSystemException;
import com.kingstargroup.ecard.hibernate.information.InformationPersistence;
import com.kingstargroup.ecard.util.DateUtil;
import com.liferay.portal.service.persistence.BasePersistence;

public class LoseCardPersistence extends BasePersistence{

	/**
	 * 登录商户相关信息
	 * @param shopCode
	 * @return
	 * @throws DBSystemException
	 */
	public TLosscardshop getInfoByShopCode(String shopCode) throws DBSystemException {
		TLosscardshop info = null;
		Session s = null;
		try {
			s = openSession();
			info = (TLosscardshop) s.get(TLosscardshop.class,shopCode);
			return info;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}		
	}
	
	public void add(TLosscardshop info) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.saveOrUpdate(info);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}
	
	public boolean update(TLosscardshop info) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.update(info);
			return true;
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/**
	 * 卡相关信息
	 * 
	 */
	public Map getStuempInfo(String cardphyno) {
		Session s = openSession();
		StringBuffer str = new StringBuffer(512);
		str.append("select c.custid,c.stuempno,c.custname,card.cardno,card.cardphyid,card.showcardno,card.status,")
		.append(" (card.status||card.lossflag||card.frozeflag||card.badflag)cardstatus,dict.dictcaption")
		.append(" from ykt_cur.t_customer c left join ykt_cur.t_card card on c.custid=card.custid left join ykt_cur.t_dictionary dict")
		.append(" on (card.status||card.lossflag||card.frozeflag||card.badflag)=dict.dictval where card.cardphyid=:cardphyno");
		//.append(cardphyno).append("'");
		//System.out.println(str.toString());
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			query.setString("cardphyno", cardphyno);
			
			query.addScalar("custid", Hibernate.INTEGER);
			query.addScalar("stuempno",Hibernate.STRING);
			query.addScalar("custname",Hibernate.STRING);
			query.addScalar("cardno",Hibernate.INTEGER);
			query.addScalar("cardphyid",Hibernate.STRING);
			query.addScalar("showcardno",Hibernate.STRING);
			query.addScalar("status",Hibernate.STRING);
			query.addScalar("cardstatus",Hibernate.STRING);
			query.addScalar("dictcaption",Hibernate.STRING);
			List cardInfo = query.list();
			
			Map cardinfoMap = new HashMap();
			if (!cardInfo.isEmpty()){
				Object[] tempObj = (Object[])cardInfo.get(0);
				cardinfoMap.put("custid", tempObj[0]);
				cardinfoMap.put("stuempno", tempObj[1]);
				cardinfoMap.put("custname", tempObj[2]);
				cardinfoMap.put("cardno", tempObj[3]);
				cardinfoMap.put("cardphyid", tempObj[4]);
				cardinfoMap.put("showcardno", tempObj[5]);
				cardinfoMap.put("status", tempObj[6]);
				cardinfoMap.put("cardstatus", tempObj[7]);
				cardinfoMap.put("dictcaption", tempObj[8]);
				//cardinfoMap.put("", tempObj[0]);
				
			}			
			return cardinfoMap;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}
	
	public String cardStatus(String phyid){
		Session s = openSession();
		try{
			StringBuffer   sb = new StringBuffer(256);
			sb.append(" select status from ykt_cur.t_card where cardphyid=:phyid");
			SQLQuery query = s.createSQLQuery(sb.toString());
			query.setString("phyid", phyid);
			query.addScalar("status",Hibernate.STRING);
			List list = query.list();
			if(list!=null && !list.isEmpty()){
				 return list.get(0).toString();
			}else{
				return "";
			}		    
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
		
	}
	
	public void addLossCardInfo(TLosscardinfo info) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.saveOrUpdate(info);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	public List getLossCardBy(String shopCode,Integer cardNo,String endDate)throws DBSystemException {
		
		Session s = openSession();
		StringBuffer str = new StringBuffer(128);
		str.append("select cardno,shopcode,regdate from ykt_cur.t_losscardinfo")
		.append(" where cardno=:cardNo and status=1");
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			//query.setString("shopCode", shopCode);
			query.setInteger("cardNo", cardNo);
			//query.setString("endDate", endDate);
			
			query.addScalar("cardno", Hibernate.INTEGER);
			query.addScalar("shopcode",Hibernate.STRING);
			query.addScalar("regdate",Hibernate.STRING);
			List cardInfo = query.list();
			if (cardInfo.size()==0){
				return null;
			}
			Object[] tempObj = (Object[])cardInfo.get(0);
			if ((tempObj[1].toString()).equals(shopCode)){
				return null;
			}else{
				return cardInfo;
			}
			
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}
	
	public TLosscardinfo getCardInfoBy(String shopCode,Integer cardNo,Integer status) throws DBSystemException {
		String regDate = getRegDate(shopCode,cardNo);
		if ("".equals(regDate)){
			return null;
		}else{			
			TLosscardinfo info = null;
			TLosscardinfoId infoId = new TLosscardinfoId();
			infoId.setCardno(cardNo);
			infoId.setShopcode(shopCode);
			infoId.setRegdate(regDate);
			Session s = null;
			try {
				s = openSession();			
				info = (TLosscardinfo) s.get(TLosscardinfo.class,infoId);
				return info;
			} catch (HibernateException ex) {
				_log.error(ex);
				throw new DBSystemException(ex.getMessage());
			} finally {
				closeSession(s);
			}		
		}
	}

	//取得正常状态的卡日期
	public String getRegDate(String shopCode,Integer cardNo){
		Session s = openSession();
		try{
			StringBuffer   sb = new StringBuffer(128);
			sb.append("select regdate from ykt_cur.t_losscardinfo where cardno=:cardNo and shopcode=:shopCode and status=1");
			SQLQuery query = s.createSQLQuery(sb.toString());
			query.setInteger("cardNo", cardNo);
			query.setString("shopCode", shopCode);
			query.addScalar("regdate",Hibernate.STRING);
			List list = query.list();
			if(list!=null && !list.isEmpty()){
				 return list.get(0).toString();
			}else{
				return "";
			}		    
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
		
	}

	public List getLossCardInfo(String shopCode,String bDate,String eDate,
			Integer cardNo,String showCardNo,String StuempNo,String custName,
			String cardStatus)throws DBSystemException {
		
		Session s = openSession();
		StringBuffer str = new StringBuffer(512);
		str.append("select loss.cardno,loss.cardphyid,loss.shopcode,loss.regdate,loss.regtime,loss.enddate,")
		.append("loss.getcardplace,loss.tel,loss.addr,loss.idno,loss.getdate,loss.remark,dict.dictcaption,")
		.append("card.showcardno,cust.stuempno,cust.custname from ykt_cur.t_losscardinfo loss ")
		.append(" left join ykt_cur.t_dictionary dict on loss.status=dict.dictval")
		.append(" left join ykt_cur.t_card card on loss.cardno=card.cardno")
		.append(" left join ykt_cur.t_customer cust on card.custid=cust.custid")
		.append(" where dict.dicttype=160 and loss.shopcode=:shopCode");
		if (!"".equals(bDate)){
			str.append(" and loss.regdate>=:bDate");
		}
		if (!"".equals(eDate)){
			str.append(" and loss.regdate<=:eDate");
		}
		if (cardNo!=0){
			str.append(" and loss.cardno=:cardNo");
		}
		if (!"".equals(showCardNo)){
			str.append(" and card.showcardno=:showCardNo");
		}
		if (!"".equals(StuempNo)){
			str.append(" and cust.stuempno=:StuempNo");
		}
		if (!"".equals(custName)){
			str.append(" and cust.custname=:custName");
		}
		if (!"".equals(cardStatus)){
			str.append(" and loss.status=:cardStatus");
		}
		//System.out.println(str.toString());
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			query.setString("shopCode", shopCode);
			if (!"".equals(bDate)){
				query.setString("bDate", bDate);
			}
			if (!"".equals(eDate)){
				query.setString("eDate", eDate);
			}
			if (cardNo!=0){
				query.setInteger("cardNo", cardNo);
			}
			if (!"".equals(showCardNo)){
				query.setString("showCardNo", showCardNo);
			}
			if (!"".equals(StuempNo)){
				query.setString("StuempNo", StuempNo);
			}
			if (!"".equals(custName)){
				query.setString("custName", custName);
			}
			if (!"".equals(cardStatus)){
				query.setString("cardStatus", cardStatus);
			}
			
			query.addScalar("cardno", Hibernate.INTEGER);
			query.addScalar("cardphyid",Hibernate.STRING);
			query.addScalar("shopcode",Hibernate.STRING);
			query.addScalar("regdate",Hibernate.STRING);
			query.addScalar("regtime",Hibernate.STRING);
			query.addScalar("enddate",Hibernate.STRING);
			query.addScalar("getcardplace",Hibernate.STRING);
			query.addScalar("tel",Hibernate.STRING);
			query.addScalar("addr",Hibernate.STRING);
			query.addScalar("idno",Hibernate.STRING);
			query.addScalar("getdate",Hibernate.STRING);
			query.addScalar("remark",Hibernate.STRING);
			query.addScalar("dictcaption",Hibernate.STRING);
			query.addScalar("showcardno",Hibernate.STRING);
			query.addScalar("stuempno",Hibernate.STRING);
			query.addScalar("custname",Hibernate.STRING);
			List cardInfo = query.list();
			List result = new ArrayList();
			if (cardInfo!=null){
				for (int i = 0; i < cardInfo.size(); i++) {
					Object[] objects = (Object[]) cardInfo.get(i);
					HashMap cardInfoMap = new HashMap();
					cardInfoMap.put("cardno", objects[0]);
					cardInfoMap.put("cardphyid", objects[1]);
					cardInfoMap.put("shopcode", objects[2]);
					cardInfoMap.put("regdate", objects[3]);
					cardInfoMap.put("regtime", objects[4]);
					cardInfoMap.put("enddate", objects[5]);
					cardInfoMap.put("getcardplace", objects[6]);
					cardInfoMap.put("tel", objects[7]);
					cardInfoMap.put("addr", objects[8]);
					cardInfoMap.put("idno", objects[9]);
					cardInfoMap.put("getdate", objects[10]);
					cardInfoMap.put("remark", objects[11]);
					cardInfoMap.put("dictcaption", objects[12]);
					cardInfoMap.put("showcardno", objects[13]);
					cardInfoMap.put("stuempno", objects[14]);
					cardInfoMap.put("custname", objects[15]);
					//cardInfoMap.put("", objects[5]);					
					result.add(cardInfoMap);
				}
				return result;				
			}else{
				return cardInfo;
			}
			
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}

	/*
	 * 取证件类型列表
	 */
	public List getCardType()throws DBSystemException {
		
		Session s = openSession();
		StringBuffer str = new StringBuffer(128);
		str.append("select t.dictval,t.dictcaption from ykt_cur.t_dictionary t")
		.append(" where t.dicttype=87");
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			query.addScalar("dictval",Hibernate.STRING);
			query.addScalar("dictcaption",Hibernate.STRING);
			List cardInfo = query.list();
			List result = new ArrayList();
			if (cardInfo!=null){
				for (int i = 0; i < cardInfo.size(); i++) {
					Object[] objects = (Object[]) cardInfo.get(i);
					HashMap cardInfoMap = new HashMap();
					cardInfoMap.put("dictval", objects[0]);
					cardInfoMap.put("dictcaption", objects[1]);
					result.add(cardInfoMap);
				}
			}
			return result;				
			
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}

	//根据卡号取得物理卡号
	public String getCardPhyId(Integer cardNo){
		Session s = openSession();
		try{
			StringBuffer   sb = new StringBuffer(128);
			sb.append("select cardphyid from ykt_cur.t_losscardinfo where cardno=:cardNo");
			SQLQuery query = s.createSQLQuery(sb.toString());
			query.setInteger("cardNo", cardNo);
			query.addScalar("cardphyid",Hibernate.STRING);
			List list = query.list();
			if(list!=null && !list.isEmpty()){
				 return list.get(0).toString();
			}else{
				return "";
			}		    
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
		
	}

	//根据卡号取得身份证号,找不到则返回空字符串
	public Map getIdNo(Integer cardNo){
		Session s = openSession();
		try{
			StringBuffer   sb = new StringBuffer(128);
			sb.append("select cust.idno,cust.custid,cust.stuempno,cust.custname,card.cardno")
			.append(" from ykt_cur.t_customer cust")
			.append(" left join ykt_cur.t_card card on cust.custid=card.custid")
			.append(" where card.cardno=:cardNo");
			SQLQuery query = s.createSQLQuery(sb.toString());
			query.setInteger("cardNo", cardNo);
			
			query.addScalar("idno",Hibernate.STRING);
			query.addScalar("custid",Hibernate.INTEGER);
			query.addScalar("stuempno",Hibernate.STRING);
			query.addScalar("custname",Hibernate.STRING);
			query.addScalar("cardno",Hibernate.INTEGER);
			
			List list = query.list();
			HashMap cardInfoMap=null;
			if (list!=null){
				Object[] objects = (Object[]) list.get(0);
				cardInfoMap = new HashMap();
				cardInfoMap.put("idno", objects[0]);
				cardInfoMap.put("custid", objects[1]);
				cardInfoMap.put("stuempno", objects[2]);
				cardInfoMap.put("custname", objects[3]);
				cardInfoMap.put("cardno", objects[4]);
				return cardInfoMap;
			}else{
				return null;
			}
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}		
	}
	
	public void updateLossCardInfo(TLosscardinfo info) throws DBSystemException {
		Session s = null;
		try {
			s = openSession();
			s.update(info);
		} catch (HibernateException ex) {
			_log.error(ex);
			throw new DBSystemException(ex.getMessage());
		} finally {
			closeSession(s);
		}
	}

	/*
	 * 根据数据字典号取数据字典列表
	 */
	public List getDictListBy(Integer dictNo)throws DBSystemException {
		
		Session s = openSession();
		StringBuffer str = new StringBuffer(128);
		str.append("select dictval,dictcaption from ykt_cur.t_dictionary where dicttype=:dictNo");
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			query.setInteger("dictNo", dictNo);
			
			query.addScalar("dictval", Hibernate.STRING);
			query.addScalar("dictcaption",Hibernate.STRING);
			List cardStatus = query.list();
			List result = new ArrayList();
			if (cardStatus!=null){
				for (int i = 0; i < cardStatus.size(); i++) {
					Object[] objects = (Object[]) cardStatus.get(i);
					HashMap cardInfoMap = new HashMap();
					cardInfoMap.put("dictval", objects[0]);
					cardInfoMap.put("dictcaption", objects[1]);
					result.add(cardInfoMap);
				}
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}

	/*
	 * 取得统计信息列表
	 */
	public List getLossStatList(String beginDate,String endDate,String nowDate,String shopCode)
		throws DBSystemException {		
		Session s = openSession();
		StringBuffer str = new StringBuffer(128);
		str.append("select shopcode,sum(totnum)totnum,sum(getnum)getnum,sum(notgetnum)notgetnum,")
		.append(" sum(destorynum)destorynum from(select shopcode, ")
		.append(" (case when status in (1,2,3,4,5,6,9) then 1 else 0 end)totnum,")
		.append(" (case when status=2 then 1 else 0 end)getnum,")
		.append(" (case when status<>2 and enddate>:nowDate then 1 else 0 end)notgetnum,")
		.append(" (case when status<>2 and enddate<:nowDate then 1 else 0 end)destorynum")
		.append(" from ykt_cur.t_losscardinfo where 1=1  ");
		if (!"".equals(beginDate)){
			str.append(" and regdate>=:beginDate");
		}
		if (!"".equals(endDate)){
			str.append(" and regdate<=:endDate");
		}
		if (!"".equals(shopCode)){
			str.append(" and shopcode=:shopCode");
		}
		str.append(" )t group by shopcode");
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			query.setString("nowDate", nowDate);
			query.setString("nowDate", nowDate);
			if (!"".equals(beginDate)){
				query.setString("beginDate", beginDate);
			}
			if (!"".equals(endDate)){
				query.setString("endDate", endDate);
			}
			if (!"".equals(shopCode)){
				query.setString("shopCode", shopCode);
			}
						
			query.addScalar("shopcode", Hibernate.STRING);
			query.addScalar("totnum",Hibernate.INTEGER);
			query.addScalar("getnum",Hibernate.INTEGER);
			query.addScalar("notgetnum",Hibernate.INTEGER);
			query.addScalar("destorynum",Hibernate.INTEGER);
			List cardStatus = query.list();
			List result = new ArrayList();
			if (cardStatus!=null){
				for (int i = 0; i < cardStatus.size(); i++) {
					Object[] objects = (Object[]) cardStatus.get(i);
					HashMap cardInfoMap = new HashMap();
					cardInfoMap.put("shopcode", objects[0]);
					cardInfoMap.put("totnum", objects[1]);
					cardInfoMap.put("getnum", objects[2]);
					cardInfoMap.put("notgetnum", objects[3]);
					cardInfoMap.put("destorynum", objects[4]);
					result.add(cardInfoMap);
				}
			}
			return result;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}
	
	
	public Map getGetCardInfo(String cardNo) {
		Session s = openSession();
		StringBuffer str = new StringBuffer(512);
		str.append("select shopcode,getcardplace,tel,addr from ykt_cur.t_losscardinfo")
		.append(" where status=1 and enddate>=:endDate and cardno=:cardNo");
		//System.out.println(str.toString());
		try {
			SQLQuery query = s.createSQLQuery(str.toString());
			query.setString("endDate", DateUtil.getNow("yyyyMMdd"));
			query.setInteger("cardNo", Integer.parseInt(cardNo));
			
			
			query.addScalar("shopcode",Hibernate.STRING);
			query.addScalar("getcardplace",Hibernate.STRING);
			query.addScalar("tel",Hibernate.STRING);
			query.addScalar("addr",Hibernate.STRING);
			List cardInfo = query.list();
			
			Map cardinfoMap = new HashMap();
			if (!cardInfo.isEmpty()){
				Object[] tempObj = (Object[])cardInfo.get(0);
				cardinfoMap.put("shopcode", tempObj[0]);
				cardinfoMap.put("getcardplace", tempObj[1]);
				cardinfoMap.put("tel", tempObj[2]);
				cardinfoMap.put("addr", tempObj[3]);
				return cardinfoMap;
			}else{
				return null;
			}
			
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}
	}

	private static final Log _log = LogFactory.getLog(InformationPersistence.class);

}
