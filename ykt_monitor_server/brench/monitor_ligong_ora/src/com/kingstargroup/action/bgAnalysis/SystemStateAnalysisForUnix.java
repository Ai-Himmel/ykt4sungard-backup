package com.kingstargroup.action.bgAnalysis;
import java.net.InetAddress;

import com.kingstargroup.monitorsys.snmp.SNMPObject;
import com.kingstargroup.monitorsys.snmp.SNMPObjectIdentifier;
import com.kingstargroup.monitorsys.snmp.SNMPSequence;
import com.kingstargroup.monitorsys.snmp.SNMPVarBindList;
import com.kingstargroup.monitorsys.snmp.SNMPv1CommunicationInterface;

public class SystemStateAnalysisForUnix extends Thread {

	public SystemStateAnalysisForUnix() {
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
	            InetAddress hostAddress = InetAddress.getByName("172.18.109.20");
	            String community = "kingstar";
	            int version = 0;    // SNMPv1
	            
	            SNMPv1CommunicationInterface comInterface = new SNMPv1CommunicationInterface(version, hostAddress, community);

	            
	            
	            SNMPSequence pair = null;
	            SNMPObjectIdentifier snmpOID = null;
	            SNMPObject snmpValue = null;
	            double idlecpu = 0;
	            double usedcpu = 0;
	            double totmem = 0;
	            double availablemem = 0;
	            double value2 =0;
	            double value3 =0;
	            
	            
	            String itemID="";
	            SNMPVarBindList newVars = null;
	            
//   http://netman.cit.buffalo.edu/index.html
//	            http://www.snmplink.org/
//	                http://wwwsnmp.cs.utwente.nl/

//	            itemID = "1.3.6.1.4.1.2021.4.5.0";
	            itemID = "1.3.6.1.4.1.2021.4.5.0";
            	newVars = comInterface.getMIBEntry(itemID);
            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
        		snmpValue= pair.getSNMPObjectAt(1);		            	
        		totmem = Float.parseFloat(snmpValue.toString());
        		
        		itemID = "1.3.6.1.4.1.2021.4.6.0";
            	newVars = comInterface.getMIBEntry(itemID);
            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
        		snmpValue= pair.getSNMPObjectAt(1);		            	
        		availablemem = Float.parseFloat(snmpValue.toString());

        		
	            
	            System.out.println("内存使用率："+String.valueOf((totmem-availablemem)/totmem*100).substring(0,5)+"%");
	           
            	itemID = "1.3.6.1.4.1.2021.11.53.0";
            	newVars = comInterface.getMIBEntry(itemID);
            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
        		snmpValue= pair.getSNMPObjectAt(1);		            	
        		idlecpu = Float.parseFloat(snmpValue.toString());
        		
        		itemID = "1.3.6.1.4.1.2021.11.52.0";
            	newVars = comInterface.getMIBEntry(itemID);
            	pair= (SNMPSequence)(newVars.getSNMPObjectAt(0));
            	snmpOID = (SNMPObjectIdentifier)pair.getSNMPObjectAt(0);
        		snmpValue= pair.getSNMPObjectAt(1);		            	
        		usedcpu = Float.parseFloat(snmpValue.toString());
        		
	            System.out.println("cpu使用率："+String.valueOf((usedcpu/(idlecpu+usedcpu))*100).substring(0,5)+"%");
	                        
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