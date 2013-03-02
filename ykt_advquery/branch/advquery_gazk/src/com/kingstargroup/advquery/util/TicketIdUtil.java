package com.kingstargroup.advquery.util;

import java.util.ArrayList;
import java.util.List;

import org.datacontract.schemas._2004._07.saff.ArrayOfViewUserOrganizationalUnitRole;
import org.datacontract.schemas._2004._07.saff.ViewUserOrganizationalUnitRole;

import com.kingstargroup.advquery.service.IOrganizationService;
import com.kingstargroup.advquery.service.OrganizationServiceClient;
import com.microsoft.schemas._2003._10.serialization.arrays.ArrayOfguid;

public class TicketIdUtil {
	
    
	//通过选人票据查询选择的人,测试00fe9b82-90f3-45a9-bf27-3112bc3d6aeb
	public static List  getSelectedUsersByTicketID(String ticketid){
	
	 OrganizationServiceClient client = new OrganizationServiceClient();
	 
	 IOrganizationService service = client.getBasicHttpBinding_IOrganizationService();
     
	 List   list = service.getSelectedUsersByTicketID(ticketid).getGuid();
	                 
	 return  list;
	        
  }
	//通过选部门票据,选择部门下的所有人,5a07f8df-b76a-4a7d-9c59-31232c712f3e
	
	public static List     getSelectedUsersByDeptTicketID(String tickedid){
		
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
		/*
		for(int j=0;j<users.size();j++){
			System.out.println(((ViewUserOrganizationalUnitRole)users.get(j)).getUserName().getValue());
			System.out.println(((ViewUserOrganizationalUnitRole)users.get(j)).getOrganizationalUnitName().getValue());
			System.out.println(((ViewUserOrganizationalUnitRole)users.get(j)).getIDNo().getValue());
		}*/
		return users;
	}
	
	public static void main(String[] arg){
		
	//	TicketIdUtil.getSelectedUsersByDeptTicketID("00fe9b82-90f3-45a9-bf27-3112bc3d6aeb");
		TicketIdUtil.getSelectedUsersByDeptTicketID("aa555c18-6c9f-44dd-8f1a-2e27c4b53fe5");
	}
	

}
