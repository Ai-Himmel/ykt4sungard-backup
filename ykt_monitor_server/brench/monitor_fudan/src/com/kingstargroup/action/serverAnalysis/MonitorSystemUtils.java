package com.kingstargroup.action.serverAnalysis;

import java.net.InetAddress;

import com.kingstargroup.monitorsys.snmp.SNMPObject;
import com.kingstargroup.monitorsys.snmp.SNMPSequence;
import com.kingstargroup.monitorsys.snmp.SNMPVarBindList;
import com.kingstargroup.monitorsys.snmp.SNMPv1CommunicationInterface;

public class MonitorSystemUtils {

	public static String cpuCheck(String ipAddr,String community,int version) {
		String cpuratio = "0";
		try {
			InetAddress hostAddress = InetAddress.getByName(ipAddr);
			// SNMPv1

			SNMPv1CommunicationInterface comInterface = new SNMPv1CommunicationInterface(
					version, hostAddress, community);
			SNMPSequence pair = null;
			SNMPObject snmpValue = null;

			String itemID = "";
			SNMPVarBindList newVars = null;
			comInterface.setSocketTimeout(1500);
			itemID = "1.3.6.1.4.1.9600.1.1.5.1.5.6.95.84.111.116.97.108";
			newVars = comInterface.getMIBEntry(itemID);
			pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));
			snmpValue = pair.getSNMPObjectAt(1);
			cpuratio = snmpValue.toString();
			return cpuratio;
		} catch (Exception ex) {
//			ex.printStackTrace();
			return "down";
		}
	}

	public static String memCheck(String ipAddr,String community,int version) {
		String memratio = "0";
		try {
			InetAddress hostAddress = InetAddress.getByName(ipAddr);
			// SNMPv1

			SNMPv1CommunicationInterface comInterface = new SNMPv1CommunicationInterface(
					version, hostAddress, community);
			SNMPSequence pair = null;
			SNMPObject snmpValue = null;

			String itemID = "";
			SNMPVarBindList newVars = null;
			comInterface.setSocketTimeout(1500);
			itemID = "1.3.6.1.4.1.9600.1.1.2.1.0";
			newVars = comInterface.getMIBEntry(itemID);
			pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));
			snmpValue = pair.getSNMPObjectAt(1);
			float unusedmem = Float.parseFloat(snmpValue.toString());
			
			itemID = "1.3.6.1.2.1.25.2.2.0";
			newVars = comInterface.getMIBEntry(itemID);
			pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));
			snmpValue = pair.getSNMPObjectAt(1);
			
			float totalmem = Float.parseFloat(snmpValue.toString());
			
			float ratio = (totalmem-unusedmem)*100/totalmem;
			
			memratio = String.valueOf(ratio);
			return memratio;
		} catch (Exception ex) {
//			ex.printStackTrace();
			return "down";
		}
	}
	public static String diskCheck(String ipAddr,String community,int version) {
		String diskratio = "0";
		try {
			InetAddress hostAddress = InetAddress.getByName(ipAddr);
			// SNMPv1
			SNMPv1CommunicationInterface comInterface = new SNMPv1CommunicationInterface(
					version, hostAddress, community);
			SNMPSequence pair = null;
			SNMPObject snmpValue = null;

			String itemID = "";
			SNMPVarBindList newVars = null;
			comInterface.setSocketTimeout(1500);
			itemID = "1.3.6.1.4.1.9600.1.1.1.1.5.6.95.84.111.116.97.108";
			newVars = comInterface.getMIBEntry(itemID);
			pair = (SNMPSequence) (newVars.getSNMPObjectAt(0));
			snmpValue = pair.getSNMPObjectAt(1);
			diskratio =  String.valueOf((100-Integer.parseInt(snmpValue.toString())));
			return diskratio;
		} catch (Exception ex) {
//			ex.printStackTrace();
			return "down";
		}
	}


}
