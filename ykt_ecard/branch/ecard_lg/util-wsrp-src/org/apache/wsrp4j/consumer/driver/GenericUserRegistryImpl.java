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

import java.util.Hashtable;
import java.util.Iterator;

import org.apache.wsrp4j.consumer.User;
import org.apache.wsrp4j.consumer.UserRegistry;

public class GenericUserRegistryImpl implements UserRegistry {

	private Hashtable users;

	public GenericUserRegistryImpl() {
		this.users = new Hashtable();
	}

	/**
	 * Get the user with the given id
	 *
	 * @param userID The ID of the user
	 *
	 * @return The user
	 **/
	public User getUser(String userID) {
		if (userID != null) {
			return (User) users.get(userID);
		}

		return null;
	}

	/**
	 * Remove a user from the list of known user
	 *
	 * @param userID The ID of the user
	 * @return The user which has been removed or null
	 **/
	public User removeUser(String userID) {
		if (userID == null)
			return null;

		return (User) users.remove(userID);
	}

	/**
	 * Add a user. If a record with the given userid already exists, 
	 * the input UserContext object is returned, otherwise a null value.
	 *
	 * @param user The user object to add     
	 * 
	 * @return Null on success or the input user object 
	 * in case a user with the same user id already exists. 
	 **/
	public User addUser(User user) {

		if (user != null) {

			String userID = user.getUserID();
			if (userID != null) {
				if (!users.containsKey(userID)) {
					users.put(userID, user);

					return null;
				}
			}
		}

		return user;
	}

	/**
	 * Get an iterator with all known users
	 *
	 * @return All known user contexts in an iterator
	 **/
	public Iterator getAllUsers() {
		return users.values().iterator();
	}

	public void removeAllUsers() {
		users.clear();
	}
}