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

package org.apache.wsrp4j.producer.provider;

import oasis.names.tc.wsrp.v1.types.BlockingInteractionResponse;
import oasis.names.tc.wsrp.v1.types.GetMarkup;
import oasis.names.tc.wsrp.v1.types.MarkupResponse;
import oasis.names.tc.wsrp.v1.types.PerformBlockingInteraction;

import org.apache.wsrp4j.exception.WSRPException;

/**
 * Specifies the interface to the markup generating component.
 The methods are called during a WSRP markup request
 */
public interface PortletInvoker {

	/**
	 Generate the WSRP MarkupResponse for a given MarkupRequest
	 @param request _getMarkup WSRP markup request
	 @return MarkupResponse
	 @throw WSRPException
	 */
	public MarkupResponse invokeGetMarkup(GetMarkup request)
			throws WSRPException;

	/**
	 Invoke a portlet action for a given WSRP action request
	 @param request WSRP blocking interaction request
	 @return BlockingInteractionResponse
	 @throw WSRPExceptin
	 */
	public BlockingInteractionResponse invokePerformBlockingInteraction(
			PerformBlockingInteraction request) throws WSRPException;

}