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

package org.apache.wsrp4j.consumer.driver;

import oasis.names.tc.wsrp.v1.types.UserContext;

import org.apache.wsrp4j.consumer.User;
import org.apache.wsrp4j.util.StateChangedServiceImpl;

/**
 * This class contains the userid and the UserContext together for 
 * Castor persistence support. 
 * 
 * @author  <a href="mailto:Ralf.Altrichter@de.ibm.com">Ralf Altrichter</a>
 */
public class UserImpl extends StateChangedServiceImpl implements User {

	// The users ID
	private String _userID = null;

	// The UserContext for this user
	private UserContext _userContext = null;

	/**
	 * Creates a user without a user id. 
	 **/
	public UserImpl() {
	}

	/**
	 * Creates a user with the given user id. 
	 **/
	public UserImpl(String userID) {
		_userID = userID;
	}

	/**
	 * Returns the userID
	 * 
	 * @return _userID
	 */
	public String getUserID() {

		return _userID;

	}

	/**
	 * Sets the userID
	 * 
	 * @param userID as String
	 */
	public void setUserID(String userID) {

		_userID = userID;

	}

	/**
	 * Returns the UserContext for this userid
	 * 
	 * @return _userContext 
	 */
	public UserContext getUserContext() {

		return _userContext;

	}

	/**
	 * Sets the UserContext for this userID
	 *
	 * @param userContext 
	 */
	public void setUserContext(UserContext userContext) {

		_userContext = userContext;

	}

}