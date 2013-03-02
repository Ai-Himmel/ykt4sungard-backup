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
 * WSRP_v1_PortletManagement_Binding_SOAPImpl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.bind;

import org.apache.wsrp4j.producer.driver.WSRPEngine;

public class WSRP_v1_PortletManagement_Binding_SOAPImpl implements
		oasis.names.tc.wsrp.v1.intf.WSRP_v1_PortletManagement_PortType {
	public oasis.names.tc.wsrp.v1.types.PortletDescriptionResponse getPortletDescription(
			oasis.names.tc.wsrp.v1.types.GetPortletDescription getPortletDescription)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault {
		return WSRPEngine.getInstance().getPortletDescription(
				getPortletDescription);
	}

	public oasis.names.tc.wsrp.v1.types.PortletContext clonePortlet(
			oasis.names.tc.wsrp.v1.types.ClonePortlet clonePortlet)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault {
		return WSRPEngine.getInstance().clonePortlet(clonePortlet);
	}

	public oasis.names.tc.wsrp.v1.types.DestroyPortletsResponse destroyPortlets(
			oasis.names.tc.wsrp.v1.types.DestroyPortlets destroyPortlets)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault {
		return WSRPEngine.getInstance().destroyPortlets(destroyPortlets);
	}

	public oasis.names.tc.wsrp.v1.types.PortletContext setPortletProperties(
			oasis.names.tc.wsrp.v1.types.SetPortletProperties setPortletProperties)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault {
		return WSRPEngine.getInstance().setPortletProperties(
				setPortletProperties);
	}

	public oasis.names.tc.wsrp.v1.types.PropertyList getPortletProperties(
			oasis.names.tc.wsrp.v1.types.GetPortletProperties getPortletProperties)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault {
		return WSRPEngine.getInstance().getPortletProperties(
				getPortletProperties);
	}

	public oasis.names.tc.wsrp.v1.types.PortletPropertyDescriptionResponse getPortletPropertyDescription(
			oasis.names.tc.wsrp.v1.types.GetPortletPropertyDescription getPortletPropertyDescription)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault,
			oasis.names.tc.wsrp.v1.types.InconsistentParametersFault,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault,
			oasis.names.tc.wsrp.v1.types.AccessDeniedFault,
			oasis.names.tc.wsrp.v1.types.InvalidHandleFault {
		return WSRPEngine.getInstance().getPortletPropertyDescription(
				getPortletPropertyDescription);
	}

}