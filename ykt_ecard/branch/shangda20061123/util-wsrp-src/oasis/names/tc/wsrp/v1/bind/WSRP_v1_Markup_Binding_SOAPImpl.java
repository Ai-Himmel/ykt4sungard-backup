/*
 * Copyright 2000-2001,2004 The Apache Software Foundation.
 * 
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 * 
 *      http://www.apache.org/licenses/LICENSE-2.0
 * 
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/* 

 */

/**
 * WSRP_v1_Markup_Binding_SOAPImpl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.bind;

import org.apache.wsrp4j.producer.driver.WSRPEngine;

public class WSRP_v1_Markup_Binding_SOAPImpl implements
		oasis.names.tc.wsrp.v1.intf.WSRP_v1_Markup_PortType {
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
			oasis.names.tc.wsrp.v1.types.UnsupportedWindowStateFault {
		return WSRPEngine.getInstance().getMarkup(getMarkup);
	}

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
			oasis.names.tc.wsrp.v1.types.UnsupportedWindowStateFault {
		return WSRPEngine.getInstance().performBlockingInteraction(
				performBlockingInteraction);
	}

	public oasis.names.tc.wsrp.v1.types.ReturnAny releaseSessions(
			oasis.names.tc.wsrp.v1.types.ReleaseSessions releaseSessions)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault {
		return WSRPEngine.getInstance().releaseSessions(releaseSessions);
	}

	public oasis.names.tc.wsrp.v1.types.ReturnAny initCookie(
			oasis.names.tc.wsrp.v1.types.InitCookie initCookie)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault {
		return WSRPEngine.getInstance().initCookie(initCookie);
	}

}