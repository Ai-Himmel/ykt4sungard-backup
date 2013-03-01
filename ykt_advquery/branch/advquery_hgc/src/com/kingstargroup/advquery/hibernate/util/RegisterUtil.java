package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import com.kingstargroup.advquery.hibernate.dao.GetQueryConListDAO;
import com.kingstargroup.advquery.hibernate.dao.RegisterDAO;

import com.kingstargroup.advquery.register.dto.Register;

public class RegisterUtil extends BasicUtil {  
	
	
     public static Map	getResisterInfo (String regId,String custId){
    	 try{
    	 RegisterDAO dao= RegisterDAO.getInstance();
    	 List list = dao.getResisterInfo(regId,custId);
    	 
         return (Map)(list.get(0));
    	 }catch(Exception he) {
 			he.printStackTrace();
 			return new HashMap();
 		} finally {
 			closeSession();
 		}	
     }
    public static boolean    updateResisterInfo(String regId,String cutId,String comments){
    	try{
    		RegisterDAO dao= RegisterDAO.getInstance();
    		return dao.updateResisterInfo(regId,cutId,comments);
    	}catch(Exception he) {
			he.printStackTrace();
			return false;
		} finally {
			closeSession();
		}	
    }
	
	 
	
	public static  boolean  updateReserverByStuempNo(String stuempNo,String optDate,String optTime,String Comments){
		try{
		RegisterDAO dao= RegisterDAO.getInstance();
		return  dao.updateReserverByStuempNo(stuempNo,optDate,optTime,Comments);
		}catch(Exception he) {
			he.printStackTrace();
			return false;
		} finally {
			closeSession();
		}	
	}
	
	
	//学生付费备注
	
	public static Map getReserverByStuempNo(String stuempNo,String optDate ,String optTime){
		
		
		try{
			   RegisterDAO dao= RegisterDAO.getInstance();
			   List list = dao.getReserverByStuempNo(stuempNo,optDate,optTime);
        		Map temp = new HashMap();
        		Object[] obj = (Object[])list.get(0);
        		temp.put("stuempNo",obj[0]);
        		temp.put("cutName",obj[1]);
        		temp.put("registerInfo",obj[2]);
        		temp.put("optDate",obj[3]);
        		temp.put("optTime",obj[4]);
        		temp.put("comments",obj[5]);
        		
            return temp; 		
		}catch(Exception he) {
			he.printStackTrace();
			return new HashMap();		
		} finally {
			closeSession();
		}	
        		   
	}
	
	
	
	//学生付费报表
	public static List  getFeeReport(Register reg){
		 try{
			 RegisterDAO dao= RegisterDAO.getInstance();
		     List list = dao.getFeeReport(reg);
		     List result = new ArrayList();
	      
	        	for(int i=0;i<list.size();i++){
	        		Map temp = new HashMap();
	        		   Object[] obj = (Object[])list.get(i);
	        		     temp.put("term",obj[0]);
	        		     if(i==(list.size()-1)){
	        		    	 temp.put("deptName","");	
	        		    	 temp.put("classNo","");
	        		     }else{
	        		       temp.put("deptName",obj[1]);
	        		       temp.put("classNo",obj[2]);
	        		     }
	        	        
	        	         temp.put("flag1",obj[3]);
	        	         temp.put("flag2",obj[4]);
	        	         temp.put("flag3",obj[5]);
	        	         temp.put("flag4",obj[6]);
	        	         temp.put("classtotal",obj[7]);
	        	         result.add(temp);
	        	}
	        	  return result;
		    }catch(Exception he) {
				he.printStackTrace();
				return new ArrayList();		
			} finally {
				closeSession();
			}
	}

	
	
	//学生缴费信息查询
	
      public static List getFeeQueryResult(Register reg){
    	  try{
		    RegisterDAO dao= RegisterDAO.getInstance();
		    List list  = dao.getFeeQueryResult(reg);
			List result = new ArrayList();
	  
	    	for(int i=0;i<list.size();i++){
	    		Map temp = new HashMap();
	    		   Object[] obj = (Object[])list.get(i);
	    		      temp.put("regId",obj[0]);
	    		      temp.put("term",obj[1]);
	    		      temp.put("stuempNo",obj[2]);
	    	          temp.put("cutName",obj[3]);
	    	          temp.put("optDate",obj[4]);
	    	          temp.put("regInfo",obj[5]);
	    	          temp.put("deptName",obj[6]);
	    	          temp.put("Sname",obj[7]);
	    	          temp.put("typeName",obj[8]);
	    	          temp.put("feeName",obj[9]);
	    	          temp.put("classNo",obj[10]);
	    	          temp.put("optTime",obj[11]);
	    	          temp.put("reserver","备注");
	    	          result.add(temp);
	    	}
	    	  return result;
	    }catch(Exception he) {
			he.printStackTrace();
			return new ArrayList();		
		} finally {
			closeSession();
		}
	 }
	
	
	
	
	
	//报道学生信息汇总
	  public static List getRegisterReport(Register reg){
		 
		  try{
		        RegisterDAO dao= RegisterDAO.getInstance();
	        	List list = dao.getRegisterReport(reg);
	        	List result = new ArrayList();
	            for(int i=0 ;i<list.size();i++){
	            	Map temp = new HashMap();
	        		   Object[] obj = (Object[])list.get(i);
	        		   temp.put("term",obj[0]);
	        		   if(i==list.size()-1){
	        			   temp.put("deptName","");
	        			   temp.put("classname","");
	        		   }else{
	        		   temp.put("deptName",obj[1]);
	        		   temp.put("classname",obj[2]);
	        		   }
	        		  
	        		   temp.put("classtotal",obj[3]);
	        		   temp.put("regtotal",obj[4]);
	        		   result.add(temp);
	            }
	            return result;
		  }catch(Exception he) {
				he.printStackTrace();
				return new ArrayList();		
			} finally {
				closeSession();
			}
	    }
	        		
	
	//查询报到学生信息
	
	   public static   List     getRegisterResult(Register reg){
		   try{
		        RegisterDAO dao= RegisterDAO.getInstance();
	        	List list = dao.getRegisterQueryResult(reg);
	        	List result = new ArrayList();
	        	for(int i=0;i<list.size();i++){
	        		Map temp = new HashMap();
	        		   Object[] obj = (Object[])list.get(i);
	        		      temp.put("regId",obj[0]);
	        		      temp.put("custId",obj[1]);
			              temp.put("txDate",obj[2]);
			              temp.put("stuempNo",obj[3]);
			              temp.put("cutName",obj[4]);
			              temp.put("Sname",obj[5]);
			              temp.put("typeName",obj[6]);
			              temp.put("deptName",obj[7]);
			              temp.put("classNo",obj[8]);
			              temp.put("feeName",obj[9]);
			              temp.put("regId" ,obj[10]); 
			  			  temp.put("termName",obj[11]);
			  			  temp.put("comments",obj[12]);
			            result.add(temp); 
	        	}
	        	return result; 
	        	
		   }catch(Exception he) {
				he.printStackTrace();
				return new ArrayList();		
			} finally {
				closeSession();
			}
	    }
	 //
	   
      //学生注册查询功能,学生已报（不管是不是超期），同时缴费状态为已缴，缓缴或特殊缓缴均可视作已注册
		
	   public static   List     getRegisterComeResult(Register reg){
		   try{
		        RegisterDAO dao= RegisterDAO.getInstance();
	        	List list = dao.getRegisterComeQueryResult(reg);
	        	List result = new ArrayList();
	        	for(int i=0;i<list.size();i++){
	        		Map temp = new HashMap();
	        		   Object[] obj = (Object[])list.get(i);
	        		      temp.put("regId",obj[0]);
	        		      temp.put("custId",obj[1]);
			              temp.put("stuempNo",obj[3]);
			              temp.put("cutName",obj[4]);
			              temp.put("deptName",obj[6]);			      
			              temp.put("Sname",obj[8]);
			              temp.put("typeName",obj[9]);
			              temp.put("classNo",obj[10]);
			              temp.put("termName",obj[11]);
			              temp.put("register" ,Integer.parseInt(obj[12].toString())==0?"未注册":"已注册"); 
			              temp.put("cutType" ,obj[13]); 
			            result.add(temp); 
	        	}
	        	return result; 
	        	
		   }catch(Exception he) {
				he.printStackTrace();
				return new ArrayList();		
			} finally {
				closeSession();
			}
	    }
	   
	   
	   
	 public static  boolean ImpNoRegStudent(String termName) throws Exception {
		 try{
		  RegisterDAO dao= RegisterDAO.getInstance();
		  if (termName ==null ||"".equals(termName)){
			  return false;
		  }
		  return dao.ImpNoRegisterStudent(termName);
		
	     }catch(Exception he) {
			he.printStackTrace();
			return false;	
		} finally {
			closeSession();
		}
     }
}
