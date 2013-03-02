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

package org.apache.wsrp4j.util;

import javax.xml.namespace.QName;

import oasis.names.tc.wsrp.v1.types.BlockingInteractionResponse;
import oasis.names.tc.wsrp.v1.types.CookieProtocol;
import oasis.names.tc.wsrp.v1.types.DestroyFailed;
import oasis.names.tc.wsrp.v1.types.DestroyPortletsResponse;
import oasis.names.tc.wsrp.v1.types.InteractionParams;
import oasis.names.tc.wsrp.v1.types.MarkupContext;
import oasis.names.tc.wsrp.v1.types.MarkupParams;
import oasis.names.tc.wsrp.v1.types.MarkupResponse;
import oasis.names.tc.wsrp.v1.types.MissingParametersFault;
import oasis.names.tc.wsrp.v1.types.PortletContext;
import oasis.names.tc.wsrp.v1.types.PortletDescription;
import oasis.names.tc.wsrp.v1.types.PortletDescriptionResponse;
import oasis.names.tc.wsrp.v1.types.PortletPropertyDescriptionResponse;
import oasis.names.tc.wsrp.v1.types.PropertyList;
import oasis.names.tc.wsrp.v1.types.RegistrationContext;
import oasis.names.tc.wsrp.v1.types.RegistrationData;
import oasis.names.tc.wsrp.v1.types.Resource;
import oasis.names.tc.wsrp.v1.types.ResourceList;
import oasis.names.tc.wsrp.v1.types.RuntimeContext;
import oasis.names.tc.wsrp.v1.types.ServiceDescription;
import oasis.names.tc.wsrp.v1.types.SessionContext;
import oasis.names.tc.wsrp.v1.types.Templates;
import oasis.names.tc.wsrp.v1.types.UpdateResponse;
import oasis.names.tc.wsrp.v1.types.UserContext;
import oasis.names.tc.wsrp.v1.types.ClonePortlet;
import oasis.names.tc.wsrp.v1.types.DestroyPortlets;
import oasis.names.tc.wsrp.v1.types.GetMarkup;
import oasis.names.tc.wsrp.v1.types.GetPortletDescription;
import oasis.names.tc.wsrp.v1.types.GetPortletProperties;
import oasis.names.tc.wsrp.v1.types.GetPortletPropertyDescription;
import oasis.names.tc.wsrp.v1.types.GetServiceDescription;
import oasis.names.tc.wsrp.v1.types.InitCookie;
import oasis.names.tc.wsrp.v1.types.ModifyRegistration;
import oasis.names.tc.wsrp.v1.types.PerformBlockingInteraction;
import oasis.names.tc.wsrp.v1.types.ReleaseSessions;
import oasis.names.tc.wsrp.v1.types.SetPortletProperties;

import org.apache.wsrp4j.log.LogManager;
import org.apache.wsrp4j.log.Logger;

/**
 * This class validates the objects and their attributes used for the WSRP communication 
 * requests. The object and attribute tree is scanned including the 2nd level. This means, 
 * that the input object, it's attributes and ,if the attribute is itself an object, the 
 * subsequent object and It's attributes are also checked. The checking is done only for 
 * required (R) parameters in the WSRP specification. Optional (O) parameters are ignored. 
 * If a parameter is specified as 'nillable' in the WSRP specification, the check is
 * performed if the value is 'not null'. On null value, no checking is done.  
 */
public class ParameterChecker {

	// for logging and exception support
	private Logger logger = LogManager.getLogManager().getLogger(
			ParameterChecker.class);

	/**
	 * Default Constructor
	 */
	public ParameterChecker() {
	}

	/**
	 * @return true if we check
	 */
	private boolean isCheckEnabled() {
		if (logger.isLogging(Logger.TRACE_HIGH)) {
			return true;
		}
		return false;
	}

	/**
	 * --- THIS IS THE REQUEST SECTION OF THE PARAMETER-CHECKER ---
	 */

	/**
	 * Check the GetServiceDescritpion. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) String[] DesiredLocales, only if SendAllLocales == false
	 * 
	 * @param request _getServiceDescription
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see GetServiceDescription
	 */
	public void check(GetServiceDescription request)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check ClonePortlet request object pointer
			if (request instanceof GetServiceDescription) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);

			}
			else {
				throwMissingParametersFault("Input object is not from type GetServiceDescription or is null");
			}
		}
	}

	/**
	 * Check the ModifyRegistration. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) RegistrationData
	 * 
	 * @param request _modifyRegistration
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see ModifyRegistration
	 */
	public void check(ModifyRegistration request)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check ClonePortlet request object pointer
			if (request instanceof ModifyRegistration) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getRegistrationData(), Constants.NILLABLE_FALSE);

			}
			else {
				throwMissingParametersFault("Input object is not from type ModifyRegistration or is null");
			}
		}
	}

	/**
	 * Check the GetMarkup. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletContext
	 * 3) RuntimeContext
	 * 4) UserContext, only if available
	 * 5) MarkupParams
	 * 
	 * @param request getMarkup
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see GetMarkup
	 */
	public void check(GetMarkup request) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check ClonePortlet request object pointer
			if (request instanceof GetMarkup) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletContext(), Constants.NILLABLE_FALSE);
				check(request.getRuntimeContext(), Constants.NILLABLE_FALSE);
				check(request.getUserContext(), Constants.NILLABLE_TRUE);
				check(request.getMarkupParams(), Constants.NILLABLE_FALSE);

			}
			else {
				throwMissingParametersFault("Input object is not from type GetMarkup or is null");
			}
		}
	}

	/**
	 * Check the PerformBlockingInteraction. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletContext
	 * 3) RuntimeContext
	 * 4) UserContext, only if available
	 * 5) MarkupParams
	 * 6) InteractionParams
	 * 
	 * @param request _performBlockingInteraction
	 *  
	 * @throws MissingParametersFault     
	 * 
	 * @see PerformBlockingInteraction
	 */
	public void check(PerformBlockingInteraction request)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check PerformBlockingInteraction request object pointer
			if (request instanceof PerformBlockingInteraction) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletContext(), Constants.NILLABLE_FALSE);
				check(request.getRuntimeContext(), Constants.NILLABLE_FALSE);
				check(request.getUserContext(), Constants.NILLABLE_TRUE);
				check(request.getMarkupParams(), Constants.NILLABLE_FALSE);
				check(request.getInteractionParams(), Constants.NILLABLE_FALSE);

			}
			else {
				throwMissingParametersFault("Input object is not from type PerformBlockingInteraction or is null");
			}
		}
	}

	/**
	 * Check the InitCookie. The following attributes are mandatory: 
	 * 
	 * 1) RegistrationContext, only if available
	 *
	 * @param  request _initCookie
	 *  
	 * @throws MissingParametersFault         
	 * 
	 * @see InitCookie
	 */
	public void check(InitCookie request) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check InitCookie request object pointer
			if (request instanceof InitCookie) {

				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);

			}
			else {

				throwMissingParametersFault("Input object is not from type InitCookie or is null");
			}
		}
	}

	/**
	 * Parameter check for the GetPortletDescription object. The following attributes are mandatory
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletContext
	 * 3) UserContext, only if available
	 *
	 * @param request _getPortletDescription 
	 *
	 * @throws MissingParametersFault
	 * 
	 * @see GetPortletDescription
	 */
	public void check(GetPortletDescription request)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check GetPortletDescription request object pointer
			if (request instanceof GetPortletDescription) {
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletContext(), Constants.NILLABLE_FALSE);
				check(request.getUserContext(), Constants.NILLABLE_TRUE);

			}
			else {
				throwMissingParametersFault("Input object is not from type GetPortletDescription or is null");
			}
		}
	}

	/**
	 * Parameter check for the ClonePortlet object. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletContext
	 * 3) UserContext, only if available
	 * 
	 * @param request _clonePortlet 
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see ClonePortlet
	 */
	public void check(ClonePortlet request) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check ClonePortlet request object pointer
			if (request instanceof ClonePortlet) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletContext(), Constants.NILLABLE_FALSE);
				check(request.getUserContext(), Constants.NILLABLE_TRUE);

			}
			else {

				throwMissingParametersFault("Input object is not a ClonePortlet or is null");
			}
		}
	}

	/**
	 * Parameter check for the DestroyEntites object. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletHandle
	 * 
	 * @param request _destroyPortlets
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see DestroyPortlets
	 */
	public void check(DestroyPortlets request) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check DestroyPortlet request object pointer
			if (request instanceof DestroyPortlets) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletHandles(), Constants.NILLABLE_FALSE);

			}
			else {

				throwMissingParametersFault("Input object is not a DestroyPortlets or is null");
			}
		}
	}

	/**
	 * Parameter check for the SetPortletProperties object. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletContext
	 * 3) UserContext, only if available
	 * 4) PropertyList
	 *
	 * @param request _setPortletProperties
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see SetPortletProperties
	 */
	public void check(SetPortletProperties request)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check SetPortletProperties request object pointer
			if (request instanceof SetPortletProperties) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletContext(), Constants.NILLABLE_FALSE);
				check(request.getUserContext(), Constants.NILLABLE_TRUE);
				check(request.getPropertyList(), Constants.NILLABLE_FALSE);

			}
			else {

				throwMissingParametersFault("Input object is not a SetPortletProperties or is null");
			}
		}
	}

	/**
	 * Parameter check for the SetPortletProperties object. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletContext
	 * 3) UserContext, only if available
	 * 4) Names, only if available
	 *
	 * @param request _getPortletProperties
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see GetPortletPorperties
	 */
	public void check(GetPortletProperties request)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check GetPortletProperties request object pointer
			if (request instanceof GetPortletProperties) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletContext(), Constants.NILLABLE_FALSE);
				check(request.getUserContext(), Constants.NILLABLE_TRUE);
				check(request.getNames(), Constants.NILLABLE_TRUE);

			}
			else {
				throwMissingParametersFault("Input object is not a GetPortletProperties or is null");
			}
		}
	}

	/**
	 * Parameter check for the SetPortletProperties object. The following attributes are mandatory: 
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) PortletContext
	 * 3) UserContext, only if available
	 *
	 * @param request _getPortletPropertyDescription
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see GetPortletPropertyDescription
	 */
	public void check(GetPortletPropertyDescription request)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check GetPortletPropertyDescription request object pointer
			if (request instanceof GetPortletPropertyDescription) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);
				check(request.getPortletContext(), Constants.NILLABLE_FALSE);
				check(request.getUserContext(), Constants.NILLABLE_TRUE);

			}
			else {

				throwMissingParametersFault("Input object is not a GetPortletPropertyDescription or is null");
			}
		}
	}

	/**
	 * Parameter check for the ReleaseSession object. The following attributes are mandatory:
	 * 
	 * 1) RegistrationContext, only if available
	 * 2) String[] SessionHandles
	 *
	 * @param request _releaseSession
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see ReleaseSession
	 */
	public void check(ReleaseSessions request) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check ReleaseSession request object pointer
			if (request instanceof ReleaseSessions) {

				// check for registration context
				check(request.getRegistrationContext(), Constants.NILLABLE_TRUE);

				// check sessionhandles array
				check(request.getSessionIDs(), Constants.NILLABLE_FALSE);

			}
			else {

				throwMissingParametersFault("Input object is not a ReleaseSession or is null");
			}
		}
	}

	/**
	 * --- THIS IS THE RESPONSE SECTION OF THE PARAMETER-CHECKER ---
	 */

	/**
	 * Parameter check for the ServiceDescription object. The following attribute needs to be set:
	 *  
	 * - requiresRegistration
	 *
	 * @param response ServiceDescription
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see ServiceDescription
	 */
	public void check(ServiceDescription response)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check ServiceDescription  object pointer
			if (response instanceof ServiceDescription) {

				if (response != null) {

				}
				else if (response.getOfferedPortlets() != null) {

					PortletDescription[] portletDesc = response
							.getOfferedPortlets();

					for (int i = 0; i < portletDesc.length; i++) {

						check(portletDesc[i]);
					}

				}
				else if (response.getRequiresInitCookie() != null) {

					check(response.getRequiresInitCookie(), true);

				}
				else if (response.getResourceList() != null) {

					check(response.getResourceList(), true);

				}
				else {

					throwMissingParametersFault("No valid service description.");
				}
			}
			else {

				throwMissingParametersFault("No valid service description response found.");
			}
		}
	}

	/**
	 * Parameter check for the BlockingInteractionResponse object. The following attribute needs to be set:
	 *  
	 * either
	 *  - updateResponse
	 * or
	 *  - redirectURL
	 *
	 * @param response BlockingInteractionResponse
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see BlockingInteractionResponse
	 */
	public void check(BlockingInteractionResponse response)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check BlockingInteractionResponse  object pointer
			if (response instanceof BlockingInteractionResponse) {

				if (response.getUpdateResponse() != null
						&& response.getRedirectURL() == null) {

					check(response.getUpdateResponse());

				}
				else if (response.getRedirectURL() != null
						&& response.getUpdateResponse() == null) {

					// everything is fine

				}
				else {

					throwMissingParametersFault("No valid blocking interaction response. UpdateResponse"
							+ "and redirect url are mutually exclusive");
				}
			}
			else {

				throwMissingParametersFault("No valid blocking interaction response found.");
			}
		}
	}

	/**
	 * Parameter check for the UpdateResponse object. The following attribute needs to be set:
	 *  
	 * 1) SessionContext, only if available
	 * 2) PortletContext, only if available
	 * 3) MarkupContext, only if available
	 * 4) NavigationalState
	 * 
	 * @param response UpdateResponse
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see UpdateResponse
	 */
	private void check(UpdateResponse response) throws MissingParametersFault {

		// check UpdateResponse  object pointer
		if (response instanceof UpdateResponse) {

			check(response.getSessionContext(), Constants.NILLABLE_TRUE);
			check(response.getPortletContext(), Constants.NILLABLE_TRUE);
			check(response.getMarkupContext(), Constants.NILLABLE_TRUE);

			// TODO: check for valid window states and portlet modes

		}
		else {

			throwMissingParametersFault("No valid update response found.");
		}
	}

	/**
	 * Parameter check for the MarkupResponse object. The following attribute needs to be set:
	 * 
	 * 1) MarkupContext
	 * 2) SessionContext, only if available
	 * 
	 * @param response MarkupResponse
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see MarkupResponse
	 */
	public void check(MarkupResponse response) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check MarkupResponse  object pointer
			if (response instanceof MarkupResponse) {

				check(response.getMarkupContext(), Constants.NILLABLE_FALSE);
				check(response.getSessionContext(), Constants.NILLABLE_TRUE);

			}
			else {

				throwMissingParametersFault("No valid markup response found.");
			}
		}
	}

	/**
	 * Validates the PortletDescriptionResponse object
	 * 
	 * 1) PortletDescription
	 * 2) ResourceList, only if available
	 * 
	 * @param response PortletDescriptionResponse
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see PortletDescriptionResponse
	 */
	public void check(PortletDescriptionResponse response)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check MarkupResponse  object pointer
			if (response instanceof PortletDescriptionResponse) {

				check(response.getPortletDescription());
				check(response.getResourceList(), Constants.NILLABLE_TRUE);

			}
			else {

				throwMissingParametersFault("No valid PortletDescriptionResponse response found.");
			}
		}
	}

	/**
	 * Validates the PortletPropertyDescriptionResponse object
	 * 
	 * 1) ResourceList
	 * 
	 * @param response PortletPropertyDescriptionResponse
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see PortletPropertyDescriptionResponse
	 */
	public void check(PortletPropertyDescriptionResponse response)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check MarkupResponse  object pointer
			if (response instanceof PortletPropertyDescriptionResponse) {

				// TODO: check ModelDescription

				check(response.getResourceList(), Constants.NILLABLE_TRUE);

			}
			else {

				throwMissingParametersFault("No valid PortletPropertyDescriptionResponse response found.");
			}
		}
	}

	/**
	 * Validates the DestroyPortletsResponse object
	 * 
	 * 1) DestroyFailed[], only if available
	 *
	 * @param response DestroyPortletResponse
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see DestroyPortletsResponse
	 */
	public void check(DestroyPortletsResponse response)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check MarkupResponse  object pointer
			if (response instanceof DestroyPortletsResponse) {

				check(response.getDestroyFailed(), Constants.NILLABLE_TRUE);

			}
			else {

				throwMissingParametersFault("No valid PortletDescriptionResponse response found.");
			}
		}
	}

	/**
	 * --- THIS IS THE AUXILLARY SECTION OF THE PARAMETER-CHECKER ---
	 */

	/**
	 * Parameter check for the PortletDescription object. The following parameter needs to be set:
	 * 
	 * 1) portletHandle
	 * 2) markupType[] 
	 *
	 * @param element PortletDescription
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see PortletDescription
	 */
	public void check(PortletDescription element) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check PortletDescription  object pointer
			if (element instanceof PortletDescription) {

				if (element.getPortletHandle() == null) {
					throwMissingParametersFault("A portlet handle has to be set in the portlet description.");
				}

				if (element.getMarkupTypes() == null) {
					throwMissingParametersFault("Markup types have to be defined in the portlet description.");
				}

			}
			else {

				throwMissingParametersFault("No valid portlet description found.");
			}
		}
	}

	/**
	 * Parameter check for the PortletDescription object. The following parameter needs to be set:
	 * 
	 * all templates...
	 *
	 * @param element Templates
	 *  
	 * @throws MissingParametersFault
	 * 
	 * @see PortletDescription
	 */
	public void check(Templates element) throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check PortletDescription  object pointer
			if (element instanceof Templates) {
				if (element.getDefaultTemplate() == null) {
					throwMissingParametersFault("DefaultTemplate has not been set!");
				}

				if (element.getSecureDefaultTemplate() == null) {
					throwMissingParametersFault("SecureDefaultTemplate Template has not been set!");
				}
			}
			else {
				throwMissingParametersFault("Consumer has to provide templates!");
			}
		}
	}

	/**
	 * Parameter check for the SessionContext object. The following parameter needs to be set:
	 * 
	 * 1) sessionID
	 * 2) expire
	 * 
	 * @param context SessionContext
	 * @param nillable boolean true, if the SessionContext can be nill
	 *                false, if the SessionContext is not nillable
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see SessionContext
	 */
	private void check(SessionContext context, boolean nillable)
			throws MissingParametersFault {
		if (context != null) {
			if (context.getSessionID() == null) {
				throwMissingParametersFault("No valid session context found. No session handle set.");
			}
			else {
				// check, if the ID is valid, instance and length
				//TODO: activate this, if ID is no longer as string declared!
				//check(context.getSessionID());
			}
			if (context.getExpires() == 0) {
				throwMissingParametersFault("No valid session context found. No session expire set.");
			}
		}
		else {
			if (!nillable) {
				throwMissingParametersFault("No valid session context found.");
			}
		}
	}

	/**
	 * Parameter check for the MarkupContext object. The following parameter needs to be set:
	 * 
	 * 1) markupBinary and markupString mutually exclusive, if markupType is available
	 * 2) locale, if markupType is available
	 * 
	 * @param context MarkupContext
	 * @param nillable boolean true, if the MarkupContext can be nill
	 *                false, if the MarkupContext is not nillable
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see MarkupContext
	 */
	private void check(MarkupContext context, boolean nillable)
			throws MissingParametersFault {
		if (context != null) {
			boolean bMarkupBinary = false, bMarkupString = false;
			if (context.getMarkupBinary() != null) {
				bMarkupBinary = true;
			}
			if (context.getMarkupString() != null) {
				bMarkupString = true;
			}

			// XOR of markupBinary and markupString
			if (bMarkupBinary ^ bMarkupString) {
				if (context.getMimeType() == null) {
					throwMissingParametersFault("MimeType not set in MarkupContext.");
				}
				else {
					if (context.getLocale() == null) {
						throwMissingParametersFault("Locale not set in MarkupContext.");
					}
				}
			}
		}
		else {
			if (!nillable) {
				throwMissingParametersFault("No valid markup context found.");
			}
		}
	}

	/**
	 * Check the PropertyList. The following attributes are mandatory:
	 * 
	 * 1) Property[]
	 * 
	 * @param propertyList PropertyList
	 * @param nillable boolean true, if the PropertyList can be nill
	 *                false, if the PropertyList is not nillable
	 *
	 * @throws MissingParametersFault      
	 * 
	 * @see PropertyList
	 */
	public void check(PropertyList propertyList, boolean nillable)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check only, if object not null, otherwise ignore. Object is defined as nillable
			if (propertyList != null) {
				// property is mandatory
				if (propertyList.getProperties() == null) {
					throwMissingParametersFault("PropertyList[] in PropertyList is null");
				}

			}
			else {
				// check if nillable is allowed
				if (nillable == false) {
					throwMissingParametersFault("PropertyList object is null");
				}
			}
		}
	}

	/**
	 * Check the RegistrationData. The following attributes are mandatory:
	 * 
	 *  1) ConsumerName
	 *  2) ConsumerAgent
	 * 
	 * @param registrationData RegistrationData
	 * @param nillable boolean true, if the RegistrationData can be nill
	 *                false, if the RegistrationData is not nillable
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see RegistrationData
	 */
	public void check(RegistrationData registrationData, boolean nillable)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check only, if object not null, otherwise ignore. Object is defined as nillable
			if (registrationData != null) {
				// check the consumer name, is mandatory
				if (registrationData.getConsumerName() == null) {
					throwMissingParametersFault("ConsumerName in RegistrationData is null");
				}
				// check the consumer agent, is mandatory
				if (registrationData.getConsumerAgent() == null) {
					throwMissingParametersFault("ConsumerAgent in RegistrationData is null");
				}

			}
			else {
				// if registrationcontext is null, check if nillable is allowed
				if (nillable == false) {
					throwMissingParametersFault("RegistrationData object is null");
				}
			}
		}
	}

	/**
	 * Check a string array. The following attributes are mandatory:
	 * 
	 *  1) must be a string array
	 *  2) must have a array.length > 0
	 * 
	 * @param array String[]
	 * 
	 * @param nillable boolean true, if the String[] can be nill
	 *                false, if the String[] is not nillable
	 * 
	 * 
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see String
	 */
	private void check(String[] array, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null, otherwise ignore. Object is defined as nillable
		if (array != null) {
			// check the array
			if (array.length == 0) {
				throwMissingParametersFault("String[] array length is zero (0)");
			}
		}
		else {
			// if array is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("String array[] object is null");
			}
		}
	}

	/**
	 * Check the InteractionParams. The following attributes are mandatory:
	 * 
	 *  1) PortletStateChange 
	 * 
	 * @param interactionParams InteractionParams
	 * @param nillable boolean true, if the InteractionParams can be nill
	 *                false, if the InteractionParams is not nillable
	 * 
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see InteractionParams
	 */
	private void check(InteractionParams interactionParams, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null, otherwise ignore. Object is defined as nillable
		if (interactionParams != null) {
			// check the portletHandle, is mandatory
			if (interactionParams.getPortletStateChange() == null) {
				throwMissingParametersFault("PortletStateChange in InteractionParams is null");
			}
		}
		else {
			// if registrationcontext is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("InteractionParams object is null");
			}
		}
	}

	/**
	 * Check the RegistrationContext. The following attributes are mandatory:
	 * 
	 *  1) RegistrationHandle
	 * 
	 * @param registrationContext RegistrationContext
	 * 
	 * @param nillable boolean true, if the RegistrationContext can be nill
	 *                false, if the RegistrationContext is not nillable
	 * 
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see RegistrationContext
	 */
	public void check(RegistrationContext registrationContext, boolean nillable)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check only, if object not null, otherwise ignore. Object is defined as nillable
			if (registrationContext != null) {
				// check the registrationHandle, is mandatory
				if (registrationContext.getRegistrationHandle() == null) {
					throwMissingParametersFault("RegistrationHandle in RegistrationContext is null");
				}
			}
			else {
				// if registrationcontext is null, check if nillable is allowed
				if (nillable == false) {
					throwMissingParametersFault("RegistrationContext object is null");
				}
			}
		}
	}

	/**
	 * Check the PortletContext. The following attributes are mandatory:
	 * 
	 *  1) PortletHandle
	 * 
	 * @param portletContext PortletContext
	 * 
	 * @param nillable boolean true, if the PortletContext can be nill
	 *                false, if the PortletContext is not nillable
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see PortletContext
	 */
	public void check(PortletContext portletContext, boolean nillable)
			throws MissingParametersFault {
		if (isCheckEnabled()) {
			// check only, if object not null, otherwise ignore. Object is defined as nillable
			if (portletContext != null) {
				// check the portletHandle, is mandatory
				if (portletContext.getPortletHandle() == null) {
					throwMissingParametersFault("PortletHandle in PortletContext is null");
				}
			}
			else {
				// if registrationcontext is null, check if nillable is allowed
				if (nillable == false) {
					throwMissingParametersFault("PortletContext object is null");
				}
			}
		}
	}

	/**
	 * Check the RuntimeContext. The following attributes are mandatory:
	 * 
	 *  1) UserAuthentication
	 *  2) PortletInstanceKey
	 * 
	 * @param runtimeContext RuntimeContext
	 * 
	 * @param nillable boolean true, if the RuntimeContext can be nill
	 *                false, if the RuntimeContext is not nillable
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see RuntimeContext
	 */
	private void check(RuntimeContext runtimeContext, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null, otherwise ignore. Object is defined as nillable
		if (runtimeContext != null) {
			// check the userAuthentication, is mandatory
			if (runtimeContext.getUserAuthentication() == null) {
				throwMissingParametersFault("UserAuthentication in RuntimeContext is null");
			}

			// check the portletHandle, is mandatory
			if (runtimeContext.getPortletInstanceKey() != null) {
				//TODO: activate this, if the string is changed to key type
				//check(runtimeContext.getPortletInstanceKey()); 
			}
		}
		else {
			// if registrationcontext is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("RuntimeContext object is null");
			}
		}
	}

	/**
	 * Validates the DestroyFailed Array. If DestroyFailed objects are available, 
	 * they are checked for their content. 
	 * 
	 * @param destroyFailedArray DestroyFailed[]
	 * 
	 * @param nillable boolean true, if the DestroyFailed[] can be nill
	 *                false, if the DestroyFailed[] is not nillable
	 * 
	 */
	private void check(DestroyFailed[] destroyFailedArray, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null, otherwise ignore. Object is defined as nillable
		if (destroyFailedArray != null) {
			if (destroyFailedArray.length > 0) {
				for (int x = 0; x < destroyFailedArray.length; x++) {
					// mandatory
					if (destroyFailedArray[x].getPortletHandle() == null) {
						throwMissingParametersFault("Missing Portlet handle in DestroyFailed object.");
					}

					// mandatory
					if (destroyFailedArray[x].getReason() == null) {
						throwMissingParametersFault("Missing Reason in DestroyFailed object.");
					}
				}
			}
			else {
				throwMissingParametersFault("DestroyFailedArray length is zero (0).");
			}
		}
		else {
			// if destroyFailedArray is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("DestroyFailed[] object is null");
			}
		}
	}

	/**
	 * Check the UserContext. The following attributes are mandatory:
	 * 
	 *  1) UserContextKey
	 * 
	 * @param userContext UserContext
	 * @param nillable boolean true, if the UserContext can be nill
	 *                false, if the UserContext is not nillable
	 * 
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see UserContext
	 */
	private void check(UserContext userContext, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null, otherwise ignore. Object is defined as nillable
		if (userContext != null) {
			// check the UserContextKey, is mandatory
			if (userContext.getUserContextKey() == null) {
				throwMissingParametersFault("UserContextKey in UserContext is null");
			}
		}
		else {
			// if registrationcontext is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("UserContext object is null");
			}
		}
	}

	/**
	 * Validates the ResourceList object for available resources. 
	 * 
	 * @param resourceList
	 * @param nillable, true if null is allowed
	 * 
	 * @throws MissingParametersFault
	 */
	private void check(ResourceList resourceList, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null.
		if (resourceList != null) {
			// check for Resources, it's mandatory
			if (resourceList.getResources() == null) {
				throwMissingParametersFault("Resource[] is null");
			}
			else {
				Resource[] resourceArray = resourceList.getResources();
				if (resourceArray.length < 1) {
					throwMissingParametersFault("ResourceArray length is zero (0).");
				}
			}
		}
		else {
			// if registrationcontext is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("ResourceList object is null");
			}
		}
	}

	/**
	 * Validates the CookieProtocol object
	 * 
	 * @param requiresInit
	 * @param nillable, true if null is allowed
	 * 
	 * @throws MissingParametersFault
	 */
	private void check(CookieProtocol requiresInit, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null.
		if (requiresInit != null) {
			if (requiresInit.toString().equals(CookieProtocol._none)) {
			}
			else if (requiresInit.toString().equals(CookieProtocol._perGroup)) {
			}
			else if (requiresInit.toString().equals(CookieProtocol._perUser)) {
			}
			else {
				throwMissingParametersFault("Invalid value ("
						+ requiresInit.toString()
						+ ") of CookieProtocol object.");
			}
		}
		else {
			// if requiresInit is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("RequiresInitCookie object is null");
			}
		}
	}

	/**
	 * Check the MarkupParams. The following attributes are mandatory:
	 * 
	 * 1) ClientData
	 * 2) Locale
	 * 3) MimeType
	 * 4) Mode
	 * 5) WindowState
	 * 
	 * @param markupParams MarkupParams
	 * 
	 * @param nillable boolean true, if the MarkupParams can be nill
	 *                false, if the MarkupParams is not nillable
	 * 
	 * 
	 * @throws MissingParametersFault     
	 * 
	 * @see MarkupParams
	 */
	private void check(MarkupParams markupParams, boolean nillable)
			throws MissingParametersFault {
		// check only, if object not null, otherwise ignore. Object is defined as nillable
		if (markupParams != null) {
			// check ClientData, is mandatory
			if (markupParams.getClientData() == null) {
				throwMissingParametersFault("ClientData in MarkupParams is null");
			}
			if (markupParams.getLocales() == null) {
				throwMissingParametersFault("Locales in MarkupParams is null");
			}
			if (markupParams.getMimeTypes() == null) {
				throwMissingParametersFault("MimeTypes in MarkupParams is null");
			}
			if (markupParams.getMode() == null) {
				throwMissingParametersFault("Mode in MarkupParams is null");
			}
			if (markupParams.getWindowState() == null) {
				throwMissingParametersFault("WindowState in MarkupParams is null");
			}
		}
		else {
			// if registrationcontext is null, check if nillable is allowed
			if (nillable == false) {
				throwMissingParametersFault("MarkupParams object is null");
			}
		}
	}

	/**
	 * Creates and throws a MissingParametersFault exception
	 * 
	 * @param msg String error message
	 * 
	 * @throws MissingParametersFault
	 * 
	 * @see MissingParameterFault
	 */
	private void throwMissingParametersFault(String msg)
			throws MissingParametersFault {
		MissingParametersFault e = new MissingParametersFault();
		e.setFaultCode(new QName("urn:oasis:names:tc:wsrp:v1:types",
				"Interface.MissingParameters"));
		e.setFaultString(msg);
		throw e;
	}
}