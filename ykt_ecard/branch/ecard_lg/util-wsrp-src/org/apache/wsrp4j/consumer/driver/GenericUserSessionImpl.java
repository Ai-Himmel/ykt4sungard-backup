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

package org.apache.wsrp4j.consumer.driver;

import java.util.Hashtable;
import java.util.Iterator;

import org.apache.wsrp4j.consumer.GroupSession;
import org.apache.wsrp4j.consumer.GroupSessionMgr;
import org.apache.wsrp4j.consumer.UserSessionMgr;
import org.apache.wsrp4j.exception.WSRPException;

public abstract class GenericUserSessionImpl extends InitCookieInfoImpl
		implements UserSessionMgr {

	// ID of the user this session belongs to
	private String userID = null;

	// ID of the producer this user session is bind to
	private String producerID = null;

	// mapping access points to hashtable of group sessions
	protected Hashtable groupSessions = null;

	public GenericUserSessionImpl(String producerID, String userID,
			String markupURL) throws WSRPException {
		super(markupURL);
		this.producerID = producerID;
		this.userID = userID;
	}

	/**
	 * Get ID of the user this session is bind to
	 * 
	 * @return User ID
	 **/
	public String getUserID() {
		return this.userID;
	}

	/**
	 * Set the ID of the user this session is bind to 
	 * 
	 * @param userID ID of the user
	 **/
	public void setUserID(String userID) {
		if (userID != null) {
			this.userID = userID;
		}
	}

	/**
	 * Get ID of the producer this session is bind to
	 * 
	 * @return ID of the producer
	 **/
	public String getProducerID() {
		return this.producerID;
	}

	/**
	 * Set the ID of the producer this session is bind to.
	 * 
	 * @param producerID ID of the producer
	 **/
	public void setProducerID(String producerID) {
		this.producerID = producerID;
	}

	/**
	 * Get the group session for this group ID
	 *     
	 * @param groupID ID of the portlet application
	 * @return The a group session for the provided group ID or a new groupSession
	 **/
	public abstract GroupSessionMgr getGroupSession(String groupID)
			throws WSRPException;

	/**
	 * Add a group session to the user session
	 * 
	 * @param groupSession A group session
	 **/
	public void addGroupSession(GroupSession groupSession) {
		if (groupSession != null) {
			this.groupSessions.put(groupSession.getGroupID(), groupSession);
		}
	}

	/**
	 * Get all group session 
	 *      
	 * @return Iterator with all group sessions for the given producer access point
	 **/
	public Iterator getAllGroupSessions() {
		return this.groupSessions.values().iterator();
	}

	/**
	 * Remove a group session from the user session
	 *      
	 * @param groupID ID of the portlet application
	 **/
	public void removeGroupSession(String groupID) {
		if (groupID != null) {
			this.groupSessions.remove(groupID);
		}
	}

	/**
	 * Remove all group sessions
	 *      
	 **/
	public void removeAllGroupSessions() {
		this.groupSessions.clear();
	}

	/**
	 * Check if a group session exists for the given group ID
	 *      
	 * @param groupID ID of the portlet group
	 * @return True if a group session exists for the provided group ID
	 **/
	public boolean existsGroupSession(String groupID) {
		if (groupID == null)
			return false;

		return this.groupSessions.containsKey(groupID);
	}

	protected void setGroupSessionTable(Hashtable groupSessions) {
		this.groupSessions = groupSessions;
	}
}