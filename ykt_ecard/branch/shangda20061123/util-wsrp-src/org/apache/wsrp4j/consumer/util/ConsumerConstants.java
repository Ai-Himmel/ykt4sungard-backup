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

package org.apache.wsrp4j.consumer.util;

public interface ConsumerConstants {

	/**
	 * Key in the property file which is used to set the implementation 
	 * of the consumer environment.
	 **/
	public final String CONSUMER_ENV_CLASS = "consumer.enviroment.class";

	// some constants used within the proxy portlet
	public static final String WSRP_INSTANCE_KEY = "wsrp_portlet_instance_key";

	public static final String WSRP_SESSION_ID = "wsrp_session_id";

	public static final String WSRP_MARKUP_CACHE = "wsrp_markup_cache";

	public static final String WSRP_GROUPSESSIONS = "wsrp_group_sessions";

	public static final String WSRP_PORTLET_MAN_PORT = "wsrp_portlet_manag_port";

	public static final String WSRP_MARKUP_PORT = "wsrp_markup_port";

	public static final String WSRP_INIT_COOKIE_DONE = "wsrp_init_cookie_done";

	public static final String WSRP_INIT_COOKIE_REQ = "wsrp_init_cookie_required";

	// consumer to end-user authentication methods
	public static final String NONE = "wsrp:none";

	public static final String PASSWORD = "wsrp:password";

	public static final String CERTIFICATE = "wsrp:certificate";

	// keys for proxy portlet preferences
	public static final String WSRP_PORTLET_HANDLE = "wsrp_portlet_handle";

	public static final String WSRP_PARENT_HANDLE = "wsrp_parent_handle";

	public static final String WSRP_PRODUCER_ID = "wsrp_producer_id";

	public static final String WSRP_REGISTRATION_URL = "wsrp_reg_url";

	public static final String WSRP_SERVICE_DESC_URL = "wsrp_service_desc_url";

	public static final String WSRP_PORTLET_SERV_URL = "wsrp_portlet_serv_url";

	public static final String WSRP_PORTLET_MGMT_URL = "wsrp_portlet_mgmt_url";

	public static final String WSRP_MARKUP_URL = "wsrp_markup_url";
}