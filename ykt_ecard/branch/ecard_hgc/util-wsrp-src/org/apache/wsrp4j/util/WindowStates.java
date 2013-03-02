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

package org.apache.wsrp4j.util;

import java.util.HashMap;

import javax.portlet.WindowState;

public class WindowStates implements java.io.Serializable {
	private String _value_;

	private static HashMap _table_ = new HashMap();

	// Constructor
	protected WindowStates(String value) {
		_value_ = value;
		_table_.put(_value_, this);
	}

	// define the window states we can currently handle
	public static final String _normal = "wsrp:normal";

	public static final String _minimized = "wsrp:minimized";

	public static final String _maximized = "wsrp:maximized";

	public static final String _solo = "wsrp:solo";

	public static final WindowStates normal = new WindowStates(_normal);

	public static final WindowStates minimized = new WindowStates(_minimized);

	public static final WindowStates maximized = new WindowStates(_maximized);

	public static final WindowStates solo = new WindowStates(_solo);

	public String getValue() {
		return _value_;
	}

	/**
	 * Returns the WSRP window state build from a string representation
	 * If a not supported window state is requested, null is returned
	 * @param value <code>String</string> representation of the WSRP window state
	 * @return The WSRP <code>WindowStates</code> represented by the passed string
	 */
	public static WindowStates fromValue(String value) {
		return (WindowStates) _table_.get(value);
	}

	/**
	 * Returns the WSRP window state build from a string representation
	 * If a not supported window state is requested, null is returned
	 * @param value <code>String</string> representation of the WSRP window state
	 * @return The WSRP <code>WindowStates</code> represented by the passed string
	 */
	public static WindowStates fromString(String value) {
		return fromValue(value);
	}

	public boolean equals(java.lang.Object obj) {
		return (obj == this);
	}

	public int hashCode() {
		return toString().hashCode();
	}

	public String toString() {
		return _value_;
	}

	public java.lang.Object readResolve() throws java.io.ObjectStreamException {
		return fromValue(_value_);
	}

	/**
	 * This helper method maps portlet window states defined in wsrp to portlet 
	 * window states defined in the java portlet standard (JSR-168). 
	 * If the passed wsrp window state is null or can not be mapped 
	 * directly the normal state is returned. 
	 *
	 * @return The <code>javax.portlet.WindowState</code> which corresponds to the given wsrp state.
	 **/
	public static WindowState getJsrPortletStateFromWsrpState(
			WindowStates wsrpState) {
		if (wsrpState == null) {
			return WindowState.NORMAL;
		}
		else if (wsrpState.equals(WindowStates.maximized)) {
			return WindowState.MAXIMIZED;
		}
		else if (wsrpState.equals(WindowStates.minimized)) {
			return WindowState.MINIMIZED;
		}
		else if (wsrpState.equals(WindowStates.normal)) {
			return WindowState.NORMAL;
		}

		return WindowState.NORMAL;
	}

	/**
	 * This helper method maps portlet window states defined in tha java portlet standard (JSR-168)
	 * to window states defined in wsrp. If the passed state can not be resolved wsrp:normal state
	 * is returned.
	 *
	 * @param portletState The <code>javax.portlet.WindowState</code> which should be resolved as
	 *                     as portlet window state defined in wsrp.
	 * @return     
	 **/
	public static WindowStates getWsrpStateFromJsrPortletState(
			WindowState portletState) {
		if (portletState.equals(WindowState.MAXIMIZED)) {
			return WindowStates.maximized;
		}
		else if (portletState.equals(WindowState.MINIMIZED)) {
			return WindowStates.minimized;
		}
		else if (portletState.equals(WindowState.NORMAL)) {
			return WindowStates.normal;
		}

		return WindowStates.normal;
	}

	public static String[] getWindowStatesAsStringArray() {
		return (String[]) _table_.keySet().toArray();
	}
}