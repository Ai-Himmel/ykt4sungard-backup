/**
 * 
 */
package com.kingstargroup.advquery.hibernate.dao;

import java.util.Collections;
import java.util.Comparator;
import java.util.Iterator;
import java.util.List;
import java.util.Locale;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.HibernateException;
import org.hibernate.Query;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.ibm.icu.text.CollationKey;
import com.ibm.icu.text.Collator;
import com.kingstargroup.advquery.common.SortListColl;
import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;
import com.kingstargroup.advquery.hibernate.util.UserUtil;
import com.kingstargroup.advquery.util.WebKeys;

/**
 * @author Administrator
 * 
 */
public class GetQueryConListDAO {

	/**
	 * 根据不同的权限得到商户列表
	 * @return
	 */
	public List getShopList(String operCode) {
		if(null == operCode)
			return null;
		StringBuffer sqlStr = new StringBuffer(2048);
		if (isShopOwner(operCode)){
			sqlStr.append("Select shop_id,shop_name,dept_id,'' dept_name from YKT_CUR.T_CIF_SHOP where shop_state=1");
		}else{
			if ("DB2".equals(WebKeys.DATABASE)){
				sqlStr.append("with shoplog(shop_id,shop_name,dept_id,dept_name)as(")
				.append(" select a.shop_id,a.shop_name,a.dept_id,'' from YKT_CUR.T_CIF_SHOP a")
				.append(" where shop_state=1 and shop_id in (select int(store_code) ")
				.append(" from YKT_QUERY.T_LEADQUERY_STORELIMIT where oper_code='")
				.append(operCode).append("')")
				//加上union all后会有重复记录
				//.append(" union all")
				//.append(" select a.shop_id,a.shop_name,a.dept_id,b.shop_name from ")
				//.append(" YKT_CUR.T_CIF_SHOP a,shoplog b")
				//.append(" where b.shop_id=a.dept_id and a.shop_state=1")
				.append(" ) select shop_id ,shop_name,dept_id,dept_name from shoplog");
			}else if ("ORACLE".equals(WebKeys.DATABASE)){
				sqlStr.append("select shop_id,dept_id,shop_name,'' dept_name from YKT_CUR.T_CIF_SHOP")
				.append(" where shop_state=1")
				.append(" start with shop_id in ")
				.append(" (select to_number(store_code) from YKT_QUERY.T_LEADQUERY_STORELIMIT where oper_code='")
				.append(operCode).append("')")
				.append(" connect by prior shop_id = dept_id");
			}
		}
		Session session = HibernateSessionFactory.currentSession();
		try {
			//Query query = session.createQuery(" from TCifShop");
			SQLQuery sqlquery = session.createSQLQuery(sqlStr.toString());
			sqlquery.addScalar("shop_id",Hibernate.INTEGER);
			sqlquery.addScalar("shop_name",Hibernate.STRING);
			sqlquery.addScalar("dept_id",Hibernate.INTEGER);
			sqlquery.addScalar("dept_name",Hibernate.STRING);
			List list = sqlquery.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	public String getShopIds(String operCode){
		List shopList = getShopList(operCode);
		Iterator shopIter = shopList.iterator();
		StringBuffer ids = new StringBuffer(256);
		while (shopIter.hasNext()){
			Object[] row = (Object[])shopIter.next();
			if (shopIter.hasNext()){
				ids.append(row[0]).append(",");
			}else{
				ids.append(row[0]);
			}
		}
		return ids.toString();
	}
	/**
	 * 返回根据商户编号返回商户名称
	 * @return
	 */
	public List getShopName(int shopId){
		Session session = HibernateSessionFactory.currentSession();
		try {
			Query query = session.createQuery(" from TCifShop where shop_id=:shopid ");
			query.setInteger("shopid",shopId);
			return query.list();
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	
	/**
	 * 返回收费机的名称设备编号
	 * @return
	 */
	public List getPosDeviceListByLimit(String operCode){
		if (null==operCode){
			return null;
		}
		StringBuffer sqlStr = new StringBuffer(2048);
		if (isShopOwner(operCode)){
			sqlStr.append("Select dev999_id,device_name from YKT_CUR.T_PIF_DEVICE")
			.append(" where state_id<>5 and devtype in ('1005','0226','0232')");
		}else{
			if ("DB2".equals(WebKeys.DATABASE)){
				sqlStr.append("with shoplog(shop_id,shop_name,dept_id,dept_name)as(")
				.append(" select a.shop_id,a.shop_name,a.dept_id,'' from YKT_CUR.T_CIF_SHOP a")
				.append(" where shop_state=1 and shop_id in (select int(store_code) ")
				.append(" from YKT_QUERY.T_LEADQUERY_STORELIMIT where oper_code='")
				.append(operCode).append("')")
				//加上union all后会有重复记录
				//.append(" union all")
				//.append(" select a.shop_id,a.shop_name,a.dept_id,b.shop_name from ")
				//.append(" YKT_CUR.T_CIF_SHOP a,shoplog b")
				//.append(" where b.shop_id=a.dept_id and a.shop_state=1")
				.append(" )select dev.dev999_id,dev.device_name")
				.append(" from shoplog shop,YKT_CUR.T_CIF_SHOP_POS pos,YKT_CUR.T_PIF_DEVICE dev")
				.append(" where shop.shop_id=pos.shop_id and dev.device_id=pos.device_id and dev.state_id<>5");			
			}else if ("ORACLE".equals(WebKeys.DATABASE)){
				sqlStr.append("select distinct dev.dev999_id,dev.device_name from(")
				.append(" select shop_id,dept_id,shop_name,'' dept_name from YKT_CUR.T_CIF_SHOP where shop_state=1")
				.append(" start with shop_id in (select to_number(store_code) from YKT_QUERY.T_LEADQUERY_STORELIMIT where oper_code='")
				.append(operCode).append("')")
				.append(" connect by prior shop_id = dept_id)shop,YKT_CUR.T_CIF_SHOP_POS pos,YKT_CUR.T_PIF_DEVICE dev")
				.append(" where shop.shop_id=pos.shop_id and dev.device_id=pos.device_id and dev.state_id<>5");
			}
		}
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery(sqlStr.toString());
			query.addScalar("dev999_id",Hibernate.STRING);
			query.addScalar("device_name",Hibernate.STRING);
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
	 * 判断登录者是否为商户
	 * @param operCode
	 * @return
	 */
	public boolean isShopOwner(String operCode){
		return UserUtil.getUser(operCode).getIsShopOwner().equals("0") ? true : false;
	}
	
	/**
	 * 返回收费机的名称
	 * @return
	 */
	public List getPosDeviceList(String posId){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery query = session.createSQLQuery("select DEVICE_NAME  from ykt_cur.T_PIF_DEVICE where DEVTYPE in('1055','0226','0232') and DEV999_ID=:posid");
			query.setString("posid",posId);
			query.addScalar("DEVICE_NAME",Hibernate.STRING);
			return query.list();
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 得到专业信息
	 * @return
	 */
	public List getSpecialityList(){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery sqlquery = session.createSQLQuery("Select s_code,s_name from YKT_CUR.T_CIF_SPECIALITY ");
			sqlquery.addScalar("s_code",Hibernate.STRING);
			sqlquery.addScalar("s_name",Hibernate.STRING);
			List list = sqlquery.list();
			Collections.sort(list,new SortListColl());
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 得到班级信息
	 * @return
	 */
	public List getClassNoList(){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery sqlquery = session.createSQLQuery("select distinct(class_no)classNo,'11' as ss from ykt_cur.t_cif_customer ");
			sqlquery.addScalar("classNo",Hibernate.STRING);
			sqlquery.addScalar("ss",Hibernate.STRING);
			List list = sqlquery.list();
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}


	/**
	 * 得到部门信息
	 */
	public List getDeptList(){
		Session session = HibernateSessionFactory.currentSession();
		StringBuffer sqlStr = new StringBuffer();
		sqlStr.append("Select dept_code,dept_name from YKT_CUR.T_CIF_DEPT");
		try {
			SQLQuery sqlquery = session.createSQLQuery(sqlStr.toString());
			sqlquery.addScalar("dept_code",Hibernate.STRING);
			sqlquery.addScalar("dept_name",Hibernate.STRING);
			List list = sqlquery.list();
			Comparator comp1 = new Comparator() {
				public int compare(Object o1, Object o2) {
					Object[] m1 = (Object[]) o1;
					Object[] m2 = (Object[]) o2;
					Collator col = Collator.getInstance(Locale.CHINA);
					String deptName1 = (String)m1[1];
					String deptName2 = (String) m2[1];
					CollationKey c1 = col.getCollationKey(deptName1);
					CollationKey c2 = col.getCollationKey(deptName2);
					return c1.compareTo(c2);
				}
			};
			Collections.sort(list, comp1);
			return list;
		} catch (Exception e) {
			e.printStackTrace();
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	
	/**
	 * 根据部门编号得到部门名称
	 * @param deptCode
	 * @return
	 */
	public List getDeptName(String deptCode){
		Session session = HibernateSessionFactory.currentSession();
		try {
			Query query = session.createQuery(" from TCifDept where dept_code=:deptcode order by DEPT_NAME");
			query.setString("deptcode",deptCode);
			return query.list();
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	

	/**
	 * 得到照片信息人员类别列表
	 */
	public List getEmpType(){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery sqlquery = session.createSQLQuery("Select distinct cut_type,type_name from ykt_cur.t_cif_cuttypefee order by cut_type");
			sqlquery.addScalar("cut_type",Hibernate.STRING);
			sqlquery.addScalar("type_name",Hibernate.STRING);
			List list = sqlquery.list();
			return list; 
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}

	/**
	 * 根据人员学工号得到人员名称
	 */
	public List getCustNameByID(String custID){
		Session session = HibernateSessionFactory.currentSession();
		try { 
			Query query = session.createQuery(" from TCifCustomer where cut_id = :custID");
			query.setString("custID",custID);
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
	 * 根据选择的商户编号查找该商户编号是否在该商户操作范围内，若在则返回要对比的商户编号
	 */
	public String getCompareShopList(String selectedShop,String operCode){
		String selectedShopId[] = selectedShop.split(","); 
		StringBuffer inShopIdList = new StringBuffer(200); 
		StringBuffer outShopId = new StringBuffer(200);
		int m = 0;
		List inShop = getShopList(operCode);
		Iterator iter = inShop.iterator();
		
		while (iter.hasNext()){
			Object[] row = (Object[])iter.next();
			inShopIdList.append(row[0].toString()).append(",");
		}
		String [] inShopId = inShopIdList.toString().substring(0,inShopIdList.toString().length()-1).split(",");
		for (int j=0;j<selectedShopId.length;j++){
			for (int k=0;k<inShopId.length;k++){
				if (selectedShopId[j].equals(inShopId[k])){
					outShopId.append(selectedShopId[j])
					.append(",");
					m++;
				}
			}
		}
		return outShopId.toString().substring(0,outShopId.toString().length()-1);
	}
	
	/**
	 * 得到收费类别信息
	 * @return
	 */
	public List getFeeTypeList(){
		Session session = HibernateSessionFactory.currentSession();
		try {
			SQLQuery sqlquery = session.createSQLQuery("select fee_type,fee_name from ykt_cur.t_pif_feetype ");
			sqlquery.addScalar("fee_type",Hibernate.STRING);
			sqlquery.addScalar("fee_name",Hibernate.STRING);
			List list = sqlquery.list();
			Collections.sort(list,new SortListColl());
			return list;
		} catch (HibernateException e) {
			_log.error(e);
			return null;
		}finally{
			HibernateSessionFactory.closeSession();
		}
	}
	

	private Log _log = LogFactory.getLog(UserDAO.class.getClass());

}
