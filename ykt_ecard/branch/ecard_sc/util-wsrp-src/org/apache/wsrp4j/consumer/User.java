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

package org.apache.wsrp4j.consumer;

import oasis.names.tc.wsrp.v1.types.UserContext;

/**
 * This interface defines a user with a certain
 * user id and a user context.
 * 
 * @author Stephan Laertz
 **/
public interface User {

	/**
	 * Returns the userID
	 * 
	 * @return _userID
	 */
	public String getUserID();

	/**
	 * Sets the userID
	 * 
	 * @param userID as String
	 */
	public void setUserID(String userID);

	/**
	 * Returns the UserContext for this userid
	 * 
	 * @return _userContext 
	 */
	public UserContext getUserContext();

	/**
	 * Sets the UserContext for this userID
	 *
	 * @param userContext 
	 */
	public void setUserContext(UserContext userContext);
}