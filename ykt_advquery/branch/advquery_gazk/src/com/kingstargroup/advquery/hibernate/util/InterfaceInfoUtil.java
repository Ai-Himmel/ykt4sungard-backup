package com.kingstargroup.advquery.hibernate.util;

import java.util.ArrayList;
import java.util.List;
import org.datacontract.schemas._2004._07.saff.ArrayOfUser;
import org.datacontract.schemas._2004._07.saff.ArrayOfUserOrganizationalUnitRoleRelation;
import org.datacontract.schemas._2004._07.saff.ArrayOfViewUserOrganizationalUnitRole;
import org.datacontract.schemas._2004._07.saff.User;
import org.datacontract.schemas._2004._07.saff.UserOrganizationalUnitRoleRelation;
import org.datacontract.schemas._2004._07.saff.ViewUserOrganizationalUnitRole;
import com.kingstargroup.advquery.service.IOrganizationService;
import com.kingstargroup.advquery.service.OrganizationServiceClient;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfguid;

public class InterfaceInfoUtil {
	
    
	//通过选人票据查询选择的人,测试00fe9b82-90f3-45a9-bf27-3112bc3d6aeb
	public static List<User>  getSelectedUsersByTicketID(String ticketid){
	 // System.out.println("-------------"+ticketid);
	 OrganizationServiceClient client = new OrganizationServiceClient();
	// System.out.println("-------------"+client);
	 IOrganizationService service = client.getBasicHttpBinding_IOrganizationService();
	// System.out.println("-------------"+service);
	 ArrayOfguid   guids = service.getSelectedUsersByTicketID(ticketid);
	// System.out.println("-------------"+guids);
	
                   
	 ArrayOfUser   users =   service.getUsersByIds(guids);
	// System.out.println("--users-----------"+users.getUser());                   
	 List<User>  userList  =   users.getUser();  
	// System.out.println("--userList.size()-----------"+userList.size());    
	 return  userList;
	
	 
	/* if(userList != null){
		 
		 for(int i=0;i<userList.size();i++){
			User  user =   userList.get(i);
			//System.out.print(user.getName().getValue());
			//System.out.print(user.getIDNo().getValue());
			//System.out.println(getDeptByUserId(user.getId()));
			
		 }
	 }
	 */
	 
	 
	        
  }
	//通过人取得所属部门
	public  static String  getDeptByUserId(String  userId){
		
		 String deptName = "";
		 try{
		 OrganizationServiceClient client = new OrganizationServiceClient();
		 
		 IOrganizationService service = client.getBasicHttpBinding_IOrganizationService();
		 
		 ViewUserOrganizationalUnitRole u = service.getDefaultOrganizationalUnitRoleByUserId(userId);
		  
		 deptName = u.getOrganizationalUnitName().getValue();
		 
		 //System.out.println(deptName);
		
		 }catch(Exception e){
			 return "";
		 }
		return deptName;
		
	} 
	
	
	
	//通过选部门票据,选择部门下的所有人,5a07f8df-b76a-4a7d-9c59-31232c712f3e
	
	public static List<ViewUserOrganizationalUnitRole>     getSelectedUsersByDeptTicketID(String tickedid){
		
		OrganizationServiceClient client = new OrganizationServiceClient();
		 
		IOrganizationService service = client.getBasicHttpBinding_IOrganizationService();
		
		ArrayOfguid guids = service.getSelectedOrganizationalUnitsByTicketID(tickedid);
		
		List  guidList = guids.getGuid();
		String guid ="";
		List<ViewUserOrganizationalUnitRole>   users = new ArrayList();
		if(guidList != null){
			
			for(int i=0;i<guidList.size();i++){
				guid =	guidList.get(i).toString();
				ArrayOfViewUserOrganizationalUnitRole  user =  service.getUsersByOrganizationalUnit(guid, true, true);
				List<ViewUserOrganizationalUnitRole>   u = (List<ViewUserOrganizationalUnitRole>) user.getViewUserOrganizationalUnitRole();
			    users.addAll(u);
			}
			
		}
		
		/*for(int j=0;j<users.size();j++){
			System.out.println(((ViewUserOrganizationalUnitRole)users.get(j)).getUserName().getValue());
			System.out.println(((ViewUserOrganizationalUnitRole)users.get(j)).getOrganizationalUnitName().getValue());
			System.out.println(((ViewUserOrganizationalUnitRole)users.get(j)).getIDNo().getValue());
		}*/
		return users;
	}
	
	public static String    getManIdsByGuIds(List<ViewUserOrganizationalUnitRole> users){
		String manids ="";  
		if(users==null){
			 return manids;
		}
		 for(int i=0;i<users.size();i++){
		    String manid  =  ((ViewUserOrganizationalUnitRole)users.get(i)).getIDNo().getValue();
		    if(manid == null)
		    	continue;
		    manids = manids +"'"+ manid+"',";
		 }
		 manids = manids.substring(0, manids.length()-1);
		return manids;
	}
	
	public static String  getManIdByUsers(List users){
		String manids ="";
		if(users==null){
			return manids;
		}
		for(int i=0;i<users.size();i++){
			String manid =   ((User)users.get(i)).getIDNo().getValue();
			if(manid == null)
				continue;
			manids =manids +"'"+manid+"',";
		}
		manids = manids.substring(0,manids.length()-1);
		return manids;
	}
	
	public static void main(String[] arg){
		
		List user1 = InterfaceInfoUtil.getSelectedUsersByTicketID("00fe9b82-90f3-45a9-bf27-3112bc3d6aeb");
		
		System.out.println(InterfaceInfoUtil.getManIdByUsers(user1));
		
		//List users = InterfaceInfoUtil.getSelectedUsersByDeptTicketID("aa555c18-6c9f-44dd-8f1a-2e27c4b53fe5");
		/*String manids = InterfaceInfoUtil.getManIdsByGuIds(users);
	    System.out.println(manids);
	*/
		
		}
	

}
