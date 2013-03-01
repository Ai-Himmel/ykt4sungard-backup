package com.kingstargroup.advquery.hibernate.dao;

import java.util.List;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;
import org.hibernate.Hibernate;
import org.hibernate.SQLQuery;
import org.hibernate.Session;

import com.kingstargroup.advquery.hibernate.HibernateSessionFactory;

public class InterfaceInfoDAO {
	
	public   String   getManIdsByGuIds(List guids){
		try{
			
			Session session = HibernateSessionFactory.currentSession();
			String guidStr ="";
			if(guids != null){
			for(int i=0;i<guids.size();i++){
				guidStr = guidStr +"'"+ guids.get(i)+"',";
			}
			guidStr = guidStr.substring(0,guidStr.lastIndexOf(","));
			}else{
				return "";
			}
			
			String sql =" select   man_Id  from  ykt_cur.t_tif_interfaceinfo where guid in ("+guidStr+")";
			
			SQLQuery  query= session.createSQLQuery(sql);
			
			query.addScalar("man_Id",Hibernate.STRING);
			
			List list  = query.list();
			
			String manids="";
			if(list != null){
			for(int i=0 ; i<list.size();i++){
				
				manids = manids + "'"+ list.get(i)+"',";
				
			}
			}else{
				return "";
			}
			return manids;
		}catch(Exception e){
			_log.error("通过guid获取manid，失败");
			 
			return "";
		}
	
	}
	
	public static InterfaceInfoDAO  getInstance(){
		if(_instance ==null){
			_instance = new InterfaceInfoDAO();
		}
		return _instance;
		
	}
	
	private static InterfaceInfoDAO _instance;
	
	private Log _log = LogFactory.getLog(InterfaceInfoDAO.class.getClass());

}
