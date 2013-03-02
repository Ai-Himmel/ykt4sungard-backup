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

import java.util.Iterator;

/**
 * Defines a registry which can be used to manage users.
 * 
 * @author Stephan Laertz
 **/
public interface UserRegistry {

	/**
	 * Add a user to the registry
	 *
	 * @param user The user to add
	 *
	 * @return The user added or null
	 **/
	public User addUser(User user);

	/**
	 * Get the user with the given id
	 * 
	 * @param userID The ID of the user
	 * 
	 * @return The user object with the given user id
	 **/
	public User getUser(String userID);

	/**
	 * Remove a user from the list of known user
	 * 
	 * @param userID The ID of the user 
	 * @return The user which has been removed or null
	 **/
	public User removeUser(String userID);

	/**
	 * Remove all users from the registry     
	 **/
	public void removeAllUsers();

	/**
	 * Get an iterator with all known users
	 * 
	 * @return All known user objects in an iterator
	 **/
	public Iterator getAllUsers();
}