package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import org.datacontract.schemas._2004._07.saff.User;
import org.datacontract.schemas._2004._07.saff.ViewUserOrganizationalUnitRole;

import com.kingstargroup.advquery.hibernate.dao.TradeDAO;

public class TradeUtil extends BasicUtil {
	
	public static List getCardBalance(List userList ,String manIds,boolean isUser,boolean isDept){
		try{
			TradeDAO dao = TradeDAO.getInstance();
			List list  = dao.getCardBalance(manIds);//流水
			List  templist  = new ArrayList();
			double sumfee=0.0;
			for(int i=0 ; i<list.size();i++){
				Object[] obj = (Object[])list.get(i);
				String  manId =obj[2]==null?"":obj[2].toString();
				Map tempMap = new HashMap();
				for(int j=0;j<userList.size();j++){
					//通过用户方式
					if(isUser==true){
						User  user =   (User)(userList.get(j));
						if(manId.equals(user.getIDNo().getValue())){
							tempMap.put("deptName",InterfaceInfoUtil.getDeptByUserId(user.getId()));
							break;
						}else{
							tempMap.put("deptName", "");
						}
					}
					//通过部门方式
					if(isDept==true){
						ViewUserOrganizationalUnitRole user = (ViewUserOrganizationalUnitRole)userList.get(j);
						if(manId.equals(user.getIDNo().getValue())){
							tempMap.put("deptName",user.getOrganizationalUnitName().getValue());
							break;
						}else{
							tempMap.put("deptName", "");
						}
					}
				}
				sumfee = sumfee+ Double.parseDouble(obj[3].toString());
				tempMap.put("cutId", obj[0]);
				tempMap.put("cutName",obj[1]);
				tempMap.put("outBalance",obj[3]);
				tempMap.put("manId", obj[2]);
				templist.add(tempMap);
			}
			    Map tempMap = new HashMap();
				tempMap.put("cutId", "合计");
				tempMap.put("cutName","");
				tempMap.put("outBalance",(Double)sumfee);
				tempMap.put("manId", "");
				templist.add(tempMap);
			
			return templist;
			
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
		 closeSession();
		}
		
	}
	
	
	
	/*public static List getOutBalance(List userList,String manIds ,boolean isUser ,boolean isDept){
		try{
			TradeDAO dao = TradeDAO.getInstance();
			List list  = dao.getOutBalance(manIds);//流水
			List  templist  = new ArrayList();
			for(int i=0 ; i<list.size();i++){
				Object[] obj = (Object[])list.get(i);
				Map tempMap = new HashMap();
				for(int j=0;j<userList.size();j++){
					//通过用户方式
					if(isUser==true){
						User  user =   (User)(userList.get(i));
						if(user.getIDNo().getValue().equals(obj[7])){
							tempMap.put("deptName",InterfaceInfoUtil.getDeptByUserId(user.getId()));
							break;
						}
					}
					//通过部门方式
					if(isDept==true){
						ViewUserOrganizationalUnitRole user = (ViewUserOrganizationalUnitRole)userList.get(i);
						if(user.getIDNo().getValue().equals(obj[7])){
							tempMap.put("deptName",user.getOrganizationalUnitName().getValue());
							break;
						}
					}
				}
				
				tempMap.put("cutName",obj[2]);
				tempMap.put("stuempNo",obj[3]);
				tempMap.put("operateDate",obj[4]);
				tempMap.put("operateTime",obj[5]);
				tempMap.put("outBalance",obj[6]);
				tempMap.put("manId", obj[7]);
				templist.add(tempMap);
			}
			
			return templist;
			
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
		 closeSession();
		}
	}*/
	
	//获取消费统计信息
	public static List  getTradeTotal(List userList,String  manids,String BeginDate,String EndDate,boolean isUser,boolean isDept){
		try{
			 TradeDAO dao = TradeDAO.getInstance();
			 
			 List list  = dao.getTradeTotal(manids,BeginDate,EndDate);
			 List  templist  = new ArrayList();
			 if(list==null){
				 return null;
			 }
			 int sumcount=0;
			 double  sumtrade=0.0;
			
			 for(int i=0 ; i<list.size();i++){
				 Map tempMap = new HashMap();
				 Object[] obj = (Object[])list.get(i);
				 String  manId =obj[3]==null?"":obj[3].toString();
				 for(int j=0;j<userList.size();j++){
						//通过用户方式
					 if(isUser==true){
							User  user =   (User)(userList.get(j));
							if(manId.equals(user.getIDNo().getValue())){
								tempMap.put("deptName",InterfaceInfoUtil.getDeptByUserId(user.getId()));
								break;
							}else{
								tempMap.put("deptName", "");
							}
						}
						//通过部门方式
						if(isDept==true){
							ViewUserOrganizationalUnitRole user = (ViewUserOrganizationalUnitRole)userList.get(j);
							if(manId.equals(user.getIDNo().getValue())){
								tempMap.put("deptName",user.getOrganizationalUnitName().getValue());
								break;
							}else{
								tempMap.put("deptName", "");
							}
						}
					}
				 sumcount = sumcount+Integer.parseInt(obj[1].toString());
				 sumtrade = sumtrade +Double.parseDouble(obj[0].toString());
				
				 tempMap.put("count",String.valueOf(obj[1]));
				 tempMap.put("tradeFee",(Double)obj[0]);
				 tempMap.put("cutId", obj[2]);
				 tempMap.put("manId", obj[3]);
				 tempMap.put("cutName", obj[4]);

				 templist.add(tempMap);
				 
			 }
			 Map tempMap = new HashMap();
			 tempMap.put("count",String.valueOf(sumcount));
			 tempMap.put("tradeFee",(Double)sumtrade);
			 tempMap.put("cutId", "合计");
			 tempMap.put("manId","");
			 tempMap.put("cutName", "");
			 templist.add(tempMap);
			 
			 return templist;
		} catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
		 closeSession();
		}
		
	}
	  public static List getMoreAccountDetail(String manids ,String beginDate,String endDate){
		 try{
		  TradeDAO dao = TradeDAO.getInstance();
		  List list  = dao.getMoreAccountDetail(manids,beginDate,endDate);
          List result = new ArrayList();
          if(list==null ){
				 return null;
			 }
			 for(int i=0 ; i<list.size();i++){
				 Object[] objects = (Object[])list.get(i);
				    HashMap accMap = new HashMap();
					accMap.put("operdate",objects[0]);
					accMap.put("opertime",objects[1]);
					accMap.put("devname",objects[2]);
					accMap.put("operator",objects[3]);
					accMap.put("comments",objects[4]);
					accMap.put("opfee",objects[5]);
					accMap.put("newfee", objects[6]);
					accMap.put("name", objects[7]);
					accMap.put("manId",objects[8]);
					result.add(accMap);
			 }
		   return result;
	   } catch(Exception he) {
			he.printStackTrace();
			return null;		
		} finally {
		 closeSession();
		}
	  }
	
}
