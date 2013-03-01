package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.kingstargroup.advquery.hibernate.dao.DictionaryDAO;

public class DictionaryUtil extends BasicUtil {
	
	
	public static List  getFeeState(){
		try{
			DictionaryDAO dao = DictionaryDAO.getInstance();
			List result = dao.getFeeState();
			List mapList = new ArrayList();
			for(int i=0 ;i<result.size();i++){
				 Object[] obj =(Object[])result.get(i);
				 Map temp = new HashMap();  
				 temp.put("flag",obj[0]);
				 temp.put("info",obj[1]);
				 mapList.add(temp);
			}
			return mapList;
		}catch(Exception e){
			e.printStackTrace();
			return new ArrayList();	
		}finally{
			closeSession();
		}
		
	}
	
	
	public static List  getTermList(){
		try{
			DictionaryDAO dao = DictionaryDAO.getInstance();
			List result = dao.getTermList();
			/*List mapList = new ArrayList();
			for(int i=0 ;i<result.size();i++){
				 Object[] obj =(Object[])result.get(i);
				 Map temp = new HashMap();
				 temp.put("code",obj[0]);
				 temp.put("name",obj[1]);
				 mapList.add(temp);
			}*/
			return result;
		}catch(Exception e){
			e.printStackTrace();
			return new ArrayList();	
		}finally{
			closeSession();
		}
	}
	
	//取得院系信息 
	public static  List  getDeptList(){
		try{
		DictionaryDAO dao = DictionaryDAO.getInstance();
		List result = dao.getDeptList();
		
		return result;
		}catch(Exception e){
			e.printStackTrace();
			return new ArrayList();	
		}finally{
			closeSession();
		}
	}
	
	//取得专业信息
	public static  List getSpeciality(){
		try{
			List mapList = new ArrayList();
			DictionaryDAO dao = DictionaryDAO.getInstance();
			List result = dao.getSpeciality();
			for(int i=0 ;i<result.size();i++){
				 Object[] obj =(Object[])result.get(i);
				 Map temp = new HashMap();
				 temp.put("code",obj[0]);
				 temp.put("name",obj[1]);
				 mapList.add(temp);
			}
			return mapList;
		}catch(Exception e){
			e.printStackTrace();
			return new ArrayList();	
		}finally{
			closeSession();
		}
	}
	//取得身份类别
	public static  List getCuttype(){
		try{
			List mapList = new ArrayList();
			DictionaryDAO dao = DictionaryDAO.getInstance();
			List result = dao.getCuttype();
			for(int i=0 ;i<result.size();i++){
				 Object[] obj =(Object[])result.get(i);
				 Map temp = new HashMap();
				 temp.put("degree",obj[0]);
				 temp.put("name",obj[1]);
				 mapList.add(temp);
			}
			return mapList;
		}catch(Exception e){
			e.printStackTrace();
			return new ArrayList();	
		}finally{
			closeSession();
		}
	}
	//取得收费类别
	
	public static  List getFeetype(){
		try{
			List mapList = new ArrayList();
			DictionaryDAO dao = DictionaryDAO.getInstance();
			List result = dao.getFeetype();
			for(int i=0 ;i<result.size();i++){
				 Object[] obj =(Object[])result.get(i);
				 Map temp = new HashMap();
				 temp.put("type",obj[0]);
				 temp.put("name",obj[1]);
				 mapList.add(temp);
			}
			return mapList;
		}catch(Exception e){
			e.printStackTrace();
			return new ArrayList();	
		}finally{
			closeSession();
		}
	}

}
