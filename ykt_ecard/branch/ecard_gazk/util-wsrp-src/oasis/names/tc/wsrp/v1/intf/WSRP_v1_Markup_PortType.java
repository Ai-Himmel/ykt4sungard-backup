/**
 * WSRP_v1_Markup_PortType.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis 1.2RC3 Feb 28, 2005 (10:15:14 EST) WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.intf;

public interface WSRP_v1_Markup_PortType extends java.rmi.Remote {
	public oasis.names.tc.wsrp.v1.types.MarkupResponse getMarkup(
			oasis.names.tc.wsrp.v1.types.GetMarkup getMarkup)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedMimeTypeFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedModeFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedLocaleFault,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InvalidSessionFault,
			oasis.names.tc.wsrp.v1.types.InvalidCookieFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedWindowStateFault;

	public oasis.names.tc.wsrp.v1.types.BlockingInteractionResponse performBlockingInteraction(
			oasis.names.tc.wsrp.v1.types.PerformBlockingInteraction performBlockingInteraction)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedMimeTypeFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedModeFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedLocaleFault,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InvalidSessionFault,
			oasis.names.tc.wsrp.v1.types.InvalidCookieFault,
			oasis.names.tc.wsrp.v1.types.PortletStateChangeRequiredFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault,
			oasis.names.tc.wsrp.v1.types.UnsupportedWindowStateFault;

	public oasis.names.tc.wsrp.v1.types.ReturnAny releaseSessions(
			oasis.names.tc.wsrp.v1.types.ReleaseSessions releaseSessions)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault;

	public oasis.names.tc.wsrp.v1.types.ReturnAny initCookie(
			oasis.names.tc.wsrp.v1.types.InitCookie initCookie)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault;
}