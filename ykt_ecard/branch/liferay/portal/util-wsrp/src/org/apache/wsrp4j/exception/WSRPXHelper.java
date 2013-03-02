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

package org.apache.wsrp4j.exception;

import java.io.InputStream;
import java.util.Enumeration;
import java.util.HashMap;
import java.util.Properties;
import java.util.StringTokenizer;

import javax.xml.namespace.QName;

import oasis.names.tc.wsrp.v1.types.AccessDeniedFault;
import oasis.names.tc.wsrp.v1.types.Fault;
import oasis.names.tc.wsrp.v1.types.InconsistentParametersFault;
import oasis.names.tc.wsrp.v1.types.InvalidCookieFault;
import oasis.names.tc.wsrp.v1.types.InvalidHandleFault;
import oasis.names.tc.wsrp.v1.types.InvalidRegistrationFault;
import oasis.names.tc.wsrp.v1.types.InvalidSessionFault;
import oasis.names.tc.wsrp.v1.types.InvalidUserCategoryFault;
import oasis.names.tc.wsrp.v1.types.MissingParametersFault;
import oasis.names.tc.wsrp.v1.types.OperationFailedFault;
import oasis.names.tc.wsrp.v1.types.PortletStateChangeRequiredFault;
import oasis.names.tc.wsrp.v1.types.UnsupportedLocaleFault;
import oasis.names.tc.wsrp.v1.types.UnsupportedMimeTypeFault;
import oasis.names.tc.wsrp.v1.types.UnsupportedModeFault;
import oasis.names.tc.wsrp.v1.types.UnsupportedWindowStateFault;

import org.apache.axis.AxisFault;
import org.apache.axis.utils.XMLUtils;
import org.apache.wsrp4j.log.Logger;
import org.apache.wsrp4j.util.Constants;
import org.w3c.dom.Document;
import org.w3c.dom.Element;

/**
 * Handles the throwing of exceptions. 
 * Instead of calling <code> throw(new WSRPException("exception text")) </code>
 * simply type <code>ExceptionHelper throwX(1234)</code>
 * So the appropriate messages can be handled in a central place.
 * Also the Exceptions will be logged
 */
public class WSRPXHelper {

	private static final String EMPTY_STRING = "";

	// the name of the .properties file
	private static String EXCEPTION_MAPPING_FILE = "wsrp-exception-mapping.properties";

	// the content of the .properties file
	private static HashMap exceptionMapping = null;

	/**
	 * Throws a new exception with a specific message 
	 * identified by an error code without logging
	 * 
	 * @param errorCode integer specifying an error message
	 * @exception WSRPException
	 */
	public static void throwX(int errorCode) throws WSRPException {
		WSRPException e = getException(errorCode, null);
		throw e;
	}

	/**
	 * Throws a new exception with a specific message 
	 * identified by an error code without logging
	 * 
	 * @param errorCode integer specifying an error message
	 * @param t         the nested exception
	 * @exception WSRPException
	 */
	public static void throwX(int errorCode, Throwable t) throws WSRPException {
		WSRPException e = getException(errorCode, t);
		throw e;
	}

	/**
	 * Throws a new exception with a specific message
	 * identified by an error code and logs the exception
	 * to a logger.
	 * 
	 * @param logger    an appropriate logger
	 * @param logLevel  requested logging level (ERROR,WARN,INFO,
	 *                  TRACE_LOW,
	 *                  TRACE_MEDIUM,
	 *                  TRACE_HIGH)
	 * @param method    the method in that an Exception is thrown
	 * @param errorCode integer specifying an error message
	 * @exception WSRPException
	 */
	public static void throwX(Logger logger, int logLevel, String method,
			int errorCode) throws WSRPException {
		WSRPException e = getException(errorCode, null);
		//log stack trace
		if (logger != null) {
			logger.text(logLevel, method, e, EMPTY_STRING);
		}
		throw e;
	}

	/**
	 * Throws a new exception with a specific message
	 * identified by an error code and logs the exception
	 * to a logger.
	 * 
	 * @param logger    an appropriate logger
	 * @param logLevel  requested logging level (ERROR,WARN,INFO,
	 *                  TRACE_LOW,
	 *                  TRACE_MEDIUM,
	 *                  TRACE_HIGH)
	 * @param method    the method in that an Exception is thrown
	 * @param errorCode integer specifying an error message
	 * @param t         the nested exception
	 * @exception WSRPException
	 */
	public static void throwX(Logger logger, int logLevel, String method,
			int errorCode, Throwable t) throws WSRPException {
		WSRPException e = getException(errorCode, t);
		//log exception
		if (logger != null) {
			if (t instanceof WSRPException) {
				//log NO trace
				logger.text(logLevel, method, e.getMessage());
			}
			else {
				//log stack trace
				logger.text(logLevel, method, e, EMPTY_STRING);
			}
		}
		throw e;
	}

	/**
	 * This method translates a WSRP exception into an
	 * apropriate WSRP fault according to the error code
	 * 
	 * @param exception the WSRPException to be translated
	 * @exception java.rmi.RemoteException the translated fault
	 */
	public static void handleWSRPException(WSRPException exception)
			throws java.rmi.RemoteException {

		if (exceptionMapping == null) {
			loadExceptionMapping();
		}

		AxisFault fault = null;
		int errorCode = ((Integer) exceptionMapping.get(String
				.valueOf(exception.getErrorCode()))).intValue();

		if (errorCode == ErrorCodes.ACCESS_DENIED) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.ACCESS_DENIED_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(AccessDeniedFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.ACCESS_DENIED_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.INCONSISTENT_PARAMETERS) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.INCONSISTENT_PARAMETERS_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(
						InconsistentParametersFault.getTypeDesc().getXmlType()
								.getNamespaceURI(),
						Constants.INCONSISTENT_PARAMETERS_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.INVALID_REGISTRATION) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.INVALID_REGISTRATION_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(InvalidRegistrationFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.INVALID_REGISTRATION_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.INVALID_COOKIE) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.INVALID_COOKIE_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(InvalidCookieFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.INVALID_COOKIE_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.INVALID_HANDLE) {
			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.INVALID_HANDLE_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(InvalidHandleFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.INVALID_HANDLE_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.INVALID_SESSION) {
			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.INVALID_SESSION_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(InvalidSessionFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.INVALID_SESSION_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.INVALID_USER_CATEGORY) {
			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.INVALID_USER_CATEGORY_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(InvalidUserCategoryFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.INVALID_USER_CATEGORY_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.MISSING_PARAMETERS) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.MISSING_PARAMETERS_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(MissingParametersFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.MISSING_PARAMETERS_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.OPERATION_FAILED) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.OPERATION_FAILED_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(OperationFailedFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.OPERATION_FAILED_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.PORTLET_STATE_CHANGE_REQUIRED) {
			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(),
					Constants.PORTLET_STATE_CHANGE_REQUIRED_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(
						PortletStateChangeRequiredFault.getTypeDesc()
								.getXmlType().getNamespaceURI(),
						Constants.PORTLET_STATE_CHANGE_REQUIRED_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.UNSUPPORTED_LOCALE) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.UNSUPPORTED_LOCALE_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(UnsupportedLocaleFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.UNSUPPORTED_LOCALE_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.UNSUPPORTED_MIME_TYPE) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.UNSUPPORTED_MIME_TYPE_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(UnsupportedMimeTypeFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.UNSUPPORTED_MIME_TYPE_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.UNSUPPORTED_MODE) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(), Constants.UNSUPPORTED_MODE_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(UnsupportedModeFault
						.getTypeDesc().getXmlType().getNamespaceURI(),
						Constants.UNSUPPORTED_MODE_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else if (errorCode == ErrorCodes.UNSUPPORTED_WINDOW_STATE) {

			fault = new AxisFault();
			QName qname = new QName(Fault.getTypeDesc().getXmlType()
					.getNamespaceURI(),
					Constants.UNSUPPORTED_WINDOW_STATE_FAULT);
			fault.setFaultCode(qname);
			fault.setFaultString(exception.getMessage());

			try {

				Document doc = XMLUtils.newDocument();
				Element element = doc.createElementNS(
						UnsupportedWindowStateFault.getTypeDesc().getXmlType()
								.getNamespaceURI(),
						Constants.UNSUPPORTED_WINDOW_STATE_FAULT);
				fault.clearFaultDetails();
				fault.setFaultDetail(new Element[] { element });

			}
			catch (Exception e) {

				// do nothing and keep the fault details as serialized by axis 
			}

		}
		else {

			throw new java.rmi.RemoteException();

		}

		throw fault;

	}

	private static void loadExceptionMapping() {
		try {
			exceptionMapping = new HashMap();

			// read in .properties-file
			InputStream in = WSRPXHelper.class.getClassLoader()
					.getResourceAsStream(EXCEPTION_MAPPING_FILE);
			Properties props = new Properties();
			props.load(in);

			// convert read Properties to a more useful representation
			Enumeration keys = props.propertyNames();
			StringTokenizer tokenizer = null;

			while (keys.hasMoreElements()) {

				String value = null;
				String currentKey = (String) keys.nextElement();
				exceptionMapping.put(currentKey, new Integer(currentKey));

				value = props.getProperty(currentKey);
				if (value != null && value.length() > 0) {
					tokenizer = new StringTokenizer(value, ",");
					String token = null;

					while (tokenizer.hasMoreTokens()) {
						token = tokenizer.nextToken();

						if (token != null) {
							exceptionMapping
									.put(token, new Integer(currentKey));
						}

					}

				}
			}

		}
		catch (Exception e) {

			// TODO
			e.printStackTrace();

		}

	}

	/**
	 * This method translates a WSRP fault into a WSRP 
	 * exception containing a corresponding error code
	 * and logs the occurence of the exception
	 * 
	 * @param logger the logger to be used
	 * @param wsrpFault the fault to be translated
	 * @exception WSRPException this is the translated exception
	 */
	public static void handleWSRPFault(Logger logger,
			java.rmi.RemoteException wsrpFault) throws WSRPException {

		if (wsrpFault instanceof AccessDeniedFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1100,
					wsrpFault);

		}
		else if (wsrpFault instanceof InconsistentParametersFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1101,
					wsrpFault);

		}
		else if (wsrpFault instanceof InvalidRegistrationFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1102,
					wsrpFault);

		}
		else if (wsrpFault instanceof InvalidCookieFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1103,
					wsrpFault);

		}
		else if (wsrpFault instanceof InvalidHandleFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1104,
					wsrpFault);

		}
		else if (wsrpFault instanceof InvalidSessionFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1105,
					wsrpFault);

		}
		else if (wsrpFault instanceof InvalidUserCategoryFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1106,
					wsrpFault);

		}
		else if (wsrpFault instanceof MissingParametersFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1107,
					wsrpFault);

		}
		else if (wsrpFault instanceof OperationFailedFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1108,
					wsrpFault);

		}
		else if (wsrpFault instanceof PortletStateChangeRequiredFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1109,
					wsrpFault);

		}
		else if (wsrpFault instanceof UnsupportedLocaleFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1110,
					wsrpFault);

		}
		else if (wsrpFault instanceof UnsupportedMimeTypeFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1111,
					wsrpFault);

		}
		else if (wsrpFault instanceof UnsupportedModeFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1112,
					wsrpFault);

		}
		else if (wsrpFault instanceof UnsupportedWindowStateFault) {

			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1113,
					wsrpFault);

		}
		else {

			// its any other java.rmi.RemoteException
			WSRPXHelper.throwX(logger, Logger.ERROR, EMPTY_STRING, 1116,
					wsrpFault);

		}

	}

	/**
	 Returns an Exception. The type of the Exception depends on the error code that is passed to the method.
	 @param errorCode integer specifying an error message
	 @return Exception. The type depends on the error code
	 */
	protected static WSRPException getException(int errorCode, Throwable t) {
		WSRPException e = null;
		if (errorCode >= Messages.PRODUCER_LOWER_BOUND
				&& errorCode <= Messages.PRODUCER_UPPER_BOUND) {
			if (t == null) {

				e = new WSRPException(errorCode);
			}
			else {
				e = new WSRPException(errorCode, t);
			}
			e.setProducerExceptionRange();
		}
		else if (errorCode >= Messages.PROVIDER_LOWER_BOUND
				&& errorCode <= Messages.PROVIDER_UPPER_BOUND) {
			if (t == null) {

				e = new WSRPException(errorCode);
			}
			else {
				e = new WSRPException(errorCode, t);
			}
			e.setProviderExceptionRange();
		}
		else if (errorCode >= Messages.CONSUMER_LOWER_BOUND
				&& errorCode <= Messages.CONSUMER_UPPER_BOUND) {
			if (t == null) {

				e = new WSRPException(errorCode);
			}
			else {
				e = new WSRPException(errorCode, t);
			}
			e.setConsumerExceptionRange();
		}
		else if (errorCode >= Messages.COMMON_LOWER_BOUND
				&& errorCode <= Messages.COMMON_UPPER_BOUND) {
			if (t == null) {

				e = new WSRPException(errorCode);
			}
			else {
				e = new WSRPException(errorCode, t);
			}
			e.setCommonExceptionRange();
		}
		else {
			if (t == null) {

				e = new WSRPException(errorCode);
			}
			else {
				e = new WSRPException(errorCode, t);
			}
		}
		return e;
	}
}