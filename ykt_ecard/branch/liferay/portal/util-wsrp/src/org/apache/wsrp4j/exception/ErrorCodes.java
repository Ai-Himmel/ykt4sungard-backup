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

public interface ErrorCodes {

	// Persistence
	public static final int STORE_OBJECT_ERROR = 1000;

	public static final int RESTORE_OBJECT_ERROR = 1001;

	public static final int DELETE_OBJECT_ERROR = 1002;

	public static final int UNMARSHAL_ERROR = 1003;

	public static final int MARSHAL_ERROR = 1004;

	// Faults defined by the WSRP Specification
	public static final int ACCESS_DENIED = 1100;

	public static final int INCONSISTENT_PARAMETERS = 1101;

	public static final int INVALID_REGISTRATION = 1102;

	public static final int INVALID_COOKIE = 1103;

	public static final int INVALID_HANDLE = 1104;

	public static final int INVALID_SESSION = 1105;

	public static final int INVALID_USER_CATEGORY = 1106;

	public static final int MISSING_PARAMETERS = 1107;

	public static final int OPERATION_FAILED = 1108;

	public static final int PORTLET_STATE_CHANGE_REQUIRED = 1109;

	public static final int UNSUPPORTED_LOCALE = 1110;

	public static final int UNSUPPORTED_MIME_TYPE = 1111;

	public static final int UNSUPPORTED_MODE = 1112;

	public static final int UNSUPPORTED_WINDOW_STATE = 1113;

	// Error Codes Producer

	// Access to factories
	public static final int PROVIDER_FACTORY_NOT_FOUND = 2001;

	public static final int PROPERTY_FILE_NOT_FOUND = 2002;

	public static final int CONSUMER_REGISTRY_FACTORY_NOT_FOUND = 2003;

	public static final int PERSISTENT_FACTORY_NOT_FOUND = 2004;

	// Description Handler
	public static final int SAVE_SERVICEDESCRIPTION_FAILED = 3000;

	public static final int LOAD_SERVICEDESCRIPTION_FAILED = 3001;

	public static final int MISSING_DEFAULT_LOCALE = 3002;

	public static final int MISSING_DEFAULT_LANGUAGE = 3003;

	public static final int NO_PORTLETDESCRIPTIONS_FOUND = 3004;

	public static final int MISSING_PORTLET_DEFINITION = 3005;

	public static final int PORTLET_PORTLET_NOT_FOUND = 3006;

	// Portlet Pool
	public static final int GET_PORTLET_FAILED = 3020;

	// Portlet Invoker
	public final static int SERVICE_CLASS_NOT_FOUND = 3030;

	public final static int INSTANTIATION_OF_SERVICE_FAILED = 3031;

	// URL Composer
	public static final int UNKNOWN_TOKEN_IN_TEMPLATE = 3040;

	public static final int SYNTAX_ERROR_IN_TEMPLATE = 3041;

	// Error Codes Consumer
	public static final int CONSUMER_PROPERTY_FILE_NOT_FOUND = 6000;

	public static final int INSTANTIATION_OF_CONSUMER_ENV_FAILED = 6001;

	public static final int COULD_NOT_ADD_REQUEST_PARAM = 6002;

	public static final int MISSING_SERVCICE_DESC_PORT = 6003;

	public static final int INIT_OF_SERVICE_DESC_PORT_FAILED = 6004;

	public static final int INVALID_URL_OF_SERVICE_DESC_PORT = 6005;

	public static final int INIT_OF_REGISTRATION_PORT_FAILED = 6006;

	public static final int INVALID_URL_OF_REGISTRATION_PORT = 6007;

	public static final int INVALID_LINK_WITHIN_MARKUP = 6008;

	public static final int NO_VALID_URL_TYPE_PARAM_FOUND = 6009;

	public static final int INVALID_PORTLET_HANDLE = 6010;

	public static final int INVALID_SERVICE_DESCRIPTION = 6011;

	public static final int COULD_NOT_FOLLOW_REDIRECT = 6012;

	public static final int PRODUCER_DOES_NOT_EXIST = 6013;

	public static final int INIT_OF_PORTLET_MGMT_PORT_FAILED = 6014;

	public static final int INVALID_URL_OF_PORTLET_MGMT_PORT = 6015;

	public static final int MISSING_MARKUP_PORT = 6016;

	public static final int INIT_OF_MARKUP_PORT_FAILED = 6017;

	public static final int INVALID_URL_OF_MARKUP_PORT = 6018;

	public static final int PORTLET_DESC_NOT_FOUND = 6019;

	public static final int USER_SESSION_NOT_FOUND = 6020;

	public static final int GROUP_SESSION_NOT_FOUND = 6021;

	public static final int PORTLET_SESSION_NOT_FOUND = 6022;

	public static final int WINDWOS_SESSION_NOT_FOUND = 6023;
}