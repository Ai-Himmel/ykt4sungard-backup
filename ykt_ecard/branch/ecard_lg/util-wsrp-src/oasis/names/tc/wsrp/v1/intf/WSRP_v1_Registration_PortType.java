/**
 * WSRP_v1_Registration_PortType.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.intf;

public interface WSRP_v1_Registration_PortType extends java.rmi.Remote {
	public oasis.names.tc.wsrp.v1.types.RegistrationContext register(
			oasis.names.tc.wsrp.v1.types.RegistrationData register)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault;

	public oasis.names.tc.wsrp.v1.types.ReturnAny deregister(
			oasis.names.tc.wsrp.v1.types.RegistrationContext deregister)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault;

	public oasis.names.tc.wsrp.v1.types.RegistrationState modifyRegistration(
			oasis.names.tc.wsrp.v1.types.ModifyRegistration modifyRegistration)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault;
}