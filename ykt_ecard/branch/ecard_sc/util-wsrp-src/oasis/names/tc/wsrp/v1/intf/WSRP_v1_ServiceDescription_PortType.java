/**
 * WSRP_v1_ServiceDescription_PortType.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.intf;

public interface WSRP_v1_ServiceDescription_PortType extends java.rmi.Remote {
	public oasis.names.tc.wsrp.v1.types.ServiceDescription getServiceDescription(
			oasis.names.tc.wsrp.v1.types.GetServiceDescription getServiceDescription)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault;
}