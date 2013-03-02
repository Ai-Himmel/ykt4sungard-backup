/**
 * WSRP_v1_PortletManagement_PortType.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.intf;

public interface WSRP_v1_PortletManagement_PortType extends java.rmi.Remote {
	public oasis.names.tc.wsrp.v1.types.PortletDescriptionResponse getPortletDescription(
			oasis.names.tc.wsrp.v1.types.GetPortletDescription getPortletDescription)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault;

	public oasis.names.tc.wsrp.v1.types.PortletContext clonePortlet(
			oasis.names.tc.wsrp.v1.types.ClonePortlet clonePortlet)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault;

	public oasis.names.tc.wsrp.v1.types.DestroyPortletsResponse destroyPortlets(
			oasis.names.tc.wsrp.v1.types.DestroyPortlets destroyPortlets)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault;

	public oasis.names.tc.wsrp.v1.types.PortletContext setPortletProperties(
			oasis.names.tc.wsrp.v1.types.SetPortletProperties setPortletProperties)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault;

	public oasis.names.tc.wsrp.v1.types.PropertyList getPortletProperties(
			oasis.names.tc.wsrp.v1.types.GetPortletProperties getPortletProperties)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault;

	public oasis.names.tc.wsrp.v1.types.PortletPropertyDescriptionResponse getPortletPropertyDescription(
			oasis.names.tc.wsrp.v1.types.GetPortletPropertyDescription getPortletPropertyDescription)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault;
}