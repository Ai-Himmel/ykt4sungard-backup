package com.kingstargroup.advquery.util;

import org.apache.axis.client.Service;
import org.apache.axis.client.Call;
import org.apache.axis.client.Service;
import javax.xml.namespace.QName;
public class caClinet {
	
	public static void main(String[] args) {
		
    try{

    String endpoint  =
    	"http://222.66.165.27:8097/saff.organization.web/service/organizationservice.svc?wsdl";
    Service service = new Service();
    Call call = (Call) service.createCall();
    call.setTargetEndpointAddress(new   java.net.URL(endpoint));   
    call.setOperationName(new   QName("http://222.66.165.27:8097/saff.organization.web/service/organizationservice.svc","GetSelectedObjectNamesByTicketID"));   
    String   day   =   (String)call.invoke(new   Object[]   {"ADF3C8F3-661B-40ED-906D-D632F157E941"});   
    System.out.println(day); 

    
    }catch(Exception e){
    	
    }


	}
}
