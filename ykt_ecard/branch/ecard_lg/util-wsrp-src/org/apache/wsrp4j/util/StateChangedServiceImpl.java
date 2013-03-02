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

import java.util.ArrayList;
import java.util.Iterator;

/**
 * This class implements the StateChangedService interface and is
 * the parent of all classes with StateChangeService functionality.
 * 
 * @author  <a href="mailto:Ralf.Altrichter@de.ibm.com">Ralf Altrichter</a>
 *
 * @version 1.0
 */

public class StateChangedServiceImpl implements StateChangedService {

	// internal list of StateChangedListeners
	private ArrayList _listeners = new ArrayList();

	/**
	 * Constructor
	 */
	public StateChangedServiceImpl() {

	}

	/**
	 * Adds a StateChangedListener object to the internal
	 * array list. 
	 * 
	 * @param changeListener to be added
	 */
	public void addListener(StateChangedListener changeListener) {

		_listeners.add(changeListener);

	}

	/**
	 * Notifies all registered listeners by calling the 
	 * stateChanged(StateChangedEvent e) method on the 
	 * target object. 
	 */
	public void stateChanged() {
		Iterator iterator = _listeners.iterator();
		while (iterator.hasNext()) {
			StateChangedListener listener = (StateChangedListener) iterator
					.next();
			listener.stateChanged(new StateChangedEvent(this));
		}
	}
}