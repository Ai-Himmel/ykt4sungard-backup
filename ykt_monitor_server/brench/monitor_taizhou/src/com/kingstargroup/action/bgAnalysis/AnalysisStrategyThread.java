package com.kingstargroup.action.bgAnalysis;
import java.net.InetAddress;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.httpclient.HttpClient;
import org.apache.commons.httpclient.HttpMethod;
import org.apache.commons.httpclient.methods.GetMethod;

import sun.rmi.transport.proxy.HttpReceiveSocket;

import com.kingstargroup.monitorsys.snmp.SNMPObject;
import com.kingstargroup.monitorsys.snmp.SNMPObjectIdentifier;
import com.kingstargroup.monitorsys.snmp.SNMPSequence;
import com.kingstargroup.monitorsys.snmp.SNMPVarBindList;
import com.kingstargroup.monitorsys.snmp.SNMPv1CommunicationInterface;

public class AnalysisStrategyThread extends Thread {

	public AnalysisStrategyThread() {
		super();
		// TODO Auto-generated constructor stub
	}

	/*
	 * (non-Javadoc)
	 * 
	 * @see java.lang.Runnable#run()
	 */
	public void run() {
		while (true) {
			try {
				
				 // create a communications interface to a remote SNMP-capable device;
	            // need to provide the remote host's InetAddress and the community
	            // name for the device; in addition, need to  supply the version number
	            // for the SNMP messages to be sent (the value 0 corresponding to SNMP
	            // version 1)
				/**
				 * 从数据库中取出所有子系统的信息
				 * while(iter.hasnext()){
				 * iter.next
				 * 拿到ip
				 * 拿到community
				 * 拿到system type （window,linux,solias）
				 * 
				 *
				 *   http://www-304.ibm.com/jct09002c/isv/tech/faq/individual.jsp?oid=1:24672
				 * }	
				 */
				HttpClient client = new HttpClient();
				HttpMethod method = new GetMethod("Http://10.9.188.50:8080/Monitorys");
				
	            InetAddress hostAddress = InetAddress.getByName("10.49.188.211");
	            String community = "public";
	            int version = 1;    // SNMPv1
	            
	            SNMPv1CommunicationInterface comInterface = new SNMPv1CommunicationInterface(version, hostAddress, community);

	            
	            
	            SNMPSequence pair = null;
	            SNMPObjectIdentifier snmpOID = null;
	            SNMPObject snmpValue = null;
	            double value = 0;
	            double value1 = 0;
	            double value2 = 0;
	            double value3 = 0;
	            
	            double memo =0;
	            
	            SNMPSequence pair1 = null;
	            SNMPObjectIdentifier snmpOID1 = null;
	            SNMPObject snmpValue1 = null;
	            String appName ="";
	            
	            String itemID="";
	            SNMPVarBindList newVars = null;
	            SNMPVarBindList newVars1 = null;
	            
	            itemID = "1.3.6.1.2.1.25.2.2.0";
	            newVars = comInterface.getMIBEntry(itemID);  
	            pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
	            snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
	            snmpValue= pair.getSNMPObjectAt(1);
	            memo = Float.parseFloat(snmpValue.toString());
	            
	            itemID = "1.3.6.1.2.1.25.5.1.1.2";
	            newVars = comInterface.getNextMIBEntry(itemID);
            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
        		snmpValue= pair.getSNMPObjectAt(1);		            	
            	value+= Float.parseFloat(snmpValue.toString());
            	
            	//linux special way
            	
//            	itemID = "1.3.6.1.2.1.25.4.2.1.2";
//            	newVars1 = comInterface.getNextMIBEntry(itemID);
//            	pair1= (SNMPSequence)(newVars1.getSNMPObjectAt(0));
//            	snmpOID1 = (SNMPObjectIdentifier)pair1.getSNMPObjectAt(0);
//        		snmpValue1= pair1.getSNMPObjectAt(1);		            	
//        		appName += snmpValue1.toString()+",";
//            	
//            	while(snmpOID.toString().startsWith("1.3.6.1.2.1.25.5.1.1.2")){
//	            	newVars = comInterface.getNextMIBEntry(snmpOID.toString());
//	            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
//	            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
//            		snmpValue= pair.getSNMPObjectAt(1);		
//            		newVars1 = comInterface.getNextMIBEntry(snmpOID1.toString());
//                	pair1= (SNMPSequence)(newVars1.getSNMPObjectAt(0));
//                	snmpOID1 = (SNMPObjectIdentifier)pair1.getSNMPObjectAt(0);
//            		snmpValue1= pair1.getSNMPObjectAt(1);
//            		if(appName.indexOf(snmpValue1.toString())==-1){
//            			appName += snmpValue1.toString()+",";
//                		if(snmpOID.toString().startsWith("1.3.6.1.2.1.25.5.1.1.2")){
//                			value+= Float.parseFloat(snmpValue.toString());
//                			System.out.println(snmpOID.toString());
//                		}
//            		}           			            	
//	            	
//	            };
	            
	            //for windows	             
            	
            	while(snmpOID.toString().startsWith("1.3.6.1.2.1.25.5.1.1.2")){
	            	newVars = comInterface.getNextMIBEntry(snmpOID.toString());
	            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
	            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
            		snmpValue= pair.getSNMPObjectAt(1);		
                	if(snmpOID.toString().startsWith("1.3.6.1.2.1.25.5.1.1.2")){
            			value+= Float.parseFloat(snmpValue.toString());
           // 			System.out.println(snmpOID.toString());
                	}       			            	
	            	
	            };
//	            for(int i=0; i< newVars.size();i++){
//	            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(i));
//	            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
//	            	if(snmpOID.toString().startsWith("1.3.6.1.2.1.25.5.1.1.2")){
//	            		snmpValue= pair.getSNMPObjectAt(1);
//		            	
//		            	value+= Float.parseFloat(snmpValue.toString());
//	            	}  
//	            }
	            System.out.println("内存使用率："+String.valueOf((value+180000)/memo*100).substring(0,5)+"%");
	           

	            double idle =0;
	            
	            itemID = "1.3.6.1.2.1.25.1.1.0";
	            	            
	            newVars = comInterface.getMIBEntry(itemID);
	            pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
	            snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
	            snmpValue= pair.getSNMPObjectAt(1);
	            idle+= Float.parseFloat(snmpValue.toString());
	            
	            itemID = "1.3.6.1.2.1.25.5.1.1.1";

            	newVars1 = comInterface.getNextMIBEntry(itemID);
            	pair1= (SNMPSequence)(newVars1.getSNMPObjectAt(0));
            	snmpOID1 = (SNMPObjectIdentifier)pair1.getSNMPObjectAt(0);
        		snmpValue1= pair1.getSNMPObjectAt(1);	
        		idle = Float.parseFloat(snmpValue1.toString());
 //           	value1+= Float.parseFloat(snmpValue1.toString());
            	while(snmpOID1.toString().startsWith("1.3.6.1.2.1.25.5.1.1.1")){	
            		newVars1 = comInterface.getNextMIBEntry(snmpOID1.toString());
                	pair1= (SNMPSequence)(newVars1.getSNMPObjectAt(0));
                	snmpOID1 = (SNMPObjectIdentifier)pair1.getSNMPObjectAt(0);
            		snmpValue1= pair1.getSNMPObjectAt(1);
                		if(snmpOID1.toString().startsWith("1.3.6.1.2.1.25.5.1.1.1")){
                			value1+= Float.parseFloat(snmpValue1.toString());
          //      			System.out.println(snmpOID1.toString());
                		}			            	
	            	
	            };	
	            idle += value1;
	            
	            	            
//	            newVars = comInterface.retrieveAllMIBInfo(itemID);
//	            
//	      
//	            for(int i=0; i< newVars.size();i++){
//	            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(i));
//	            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
//	            	if(snmpOID.toString().startsWith("1.3.6.1.2.1.25.5.1.1.1")){
//	            		snmpValue= pair.getSNMPObjectAt(1);		            	
//		            	value1+= Float.parseFloat(snmpValue.toString());
//	            	}	           
//	            }
	            System.out.println("cpu使用率："+String.valueOf((value1/idle)*100).substring(0,5)+"%");
	                        
	            itemID = "1.3.6.1.2.1.25.2.3.1.5";
	            
	            
	            newVars = comInterface.getNextMIBEntry(itemID);
            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
        		snmpValue= pair.getSNMPObjectAt(1);
        		value2+= Float.parseFloat(snmpValue.toString());
	            while(snmpOID.toString().startsWith("1.3.6.1.2.1.25.2.3.1.5")){
	            	newVars = comInterface.getNextMIBEntry(snmpOID.toString());
	            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
	            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
	            	if(snmpOID.toString().startsWith("1.3.6.1.2.1.25.2.3.1.5")){
	            		snmpValue= pair.getSNMPObjectAt(1);		            	
		            	value2+= Float.parseFloat(snmpValue.toString());
	            	}
	           
	            }
	            
	            itemID = "1.3.6.1.2.1.25.2.3.1.6";          
	            newVars = comInterface.getNextMIBEntry(itemID);
	            pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
        		snmpValue= pair.getSNMPObjectAt(1);
        		value3+= Float.parseFloat(snmpValue.toString());
	            while(snmpOID.toString().startsWith("1.3.6.1.2.1.25.2.3.1.6")){
	            	newVars = comInterface.getNextMIBEntry(snmpOID.toString());
	            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
	            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
	            	if(snmpOID.toString().startsWith("1.3.6.1.2.1.25.2.3.1.6")){
	            		snmpValue= pair.getSNMPObjectAt(1);	
		            	value3+= Float.parseFloat(snmpValue.toString());
	            	}
	            
	            }
	            System.out.println("硬盘使用率："+String.valueOf((value3/value2)*100).substring(0,5)+"%");
	            
	            
	
	            sleep(1000);
	            
	                
	        }
	        catch(Exception e)
	        {
	            System.out.println("Exception during SNMP operation:  " + e + "\n");
	        }
	        
	    }  
				   
	}

}