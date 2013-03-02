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

package org.apache.wsrp4j.util;

/**
 * 
 * @author  <a href="mailto:Ralf.Altrichter@de.ibm.com">Ralf Altrichter</a>
 *
 * @version 1.0
 */
public interface StateChangedService {

	/**
	 * Adds a new StateChangedListener to the internal list. All registered
	 * Listeners will receive a notification, if the stateChanged() method 
	 * is called. 
	 * 
	 * @param changeListener StateChangedListener
	 */
	public abstract void addListener(StateChangedListener changeListener);

	/**
	 * Must be called, if stateChanged occoured
	 */
	public abstract void stateChanged();

}