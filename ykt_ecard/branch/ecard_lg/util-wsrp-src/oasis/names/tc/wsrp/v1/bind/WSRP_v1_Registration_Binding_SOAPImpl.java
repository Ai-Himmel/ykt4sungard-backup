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
 * WSRP_v1_Registration_Binding_SOAPImpl.java
 *
 * This file was auto-generated from WSDL
 * by the Apache Axis WSDL2Java emitter.
 */

package oasis.names.tc.wsrp.v1.bind;

import org.apache.wsrp4j.producer.driver.WSRPEngine;

public class WSRP_v1_Registration_Binding_SOAPImpl implements
		oasis.names.tc.wsrp.v1.intf.WSRP_v1_Registration_PortType {
	public oasis.names.tc.wsrp.v1.types.RegistrationContext register(
			oasis.names.tc.wsrp.v1.types.RegistrationData register)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault {
		return WSRPEngine.getInstance().register(register);
	}

	public oasis.names.tc.wsrp.v1.types.ReturnAny deregister(
			oasis.names.tc.wsrp.v1.types.RegistrationContext deregister)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault {
		return WSRPEngine.getInstance().deregister(deregister);
	}

	public oasis.names.tc.wsrp.v1.types.RegistrationState modifyRegistration(
			oasis.names.tc.wsrp.v1.types.ModifyRegistration modifyRegistration)
			throws java.rmi.RemoteException,
			oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault,
			oasis.names.tc.wsrp.v1.types.OperationFailedFault,
			oasis.names.tc.wsrp.v1.types.MissingParametersFault {
		return WSRPEngine.getInstance().modifyRegistration(modifyRegistration);
	}

}