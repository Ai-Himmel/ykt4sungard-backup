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

import javax.portlet.PortletMode;

public class Modes implements java.io.Serializable {
	private java.lang.String _value_;

	private static java.util.HashMap _table_ = new java.util.HashMap();

	// Constructor
	protected Modes(java.lang.String value) {
		_value_ = value;
		_table_.put(_value_, this);
	}

	// define the modes we can currently handle
	public static final java.lang.String _view = "wsrp:view";

	public static final java.lang.String _edit = "wsrp:edit";

	public static final java.lang.String _help = "wsrp:help";

	public static final java.lang.String _preview = "wsrp:preview";

	public static final Modes view = new Modes(_view);

	public static final Modes edit = new Modes(_edit);

	public static final Modes help = new Modes(_help);

	public static final Modes preview = new Modes(_preview);

	public java.lang.String getValue() {
		return _value_;
	}

	/**
	 * Returns the WSRP mode build from a string representation
	 * If a not supported Mode is requested, null is returned
	 * @param value <code>String</string> representation of the WSRP mode
	 * @return The WSRP <code>Mode</code> represented by the passed string
	 */
	public static Modes fromValue(java.lang.String value) {
		return (Modes) _table_.get(value);
	}

	/**
	 * Returns the WSRP mode build from a string representation
	 * If a not supported Mode is requested, null is returned
	 * @param value <code>String</string> representation of the WSRP mode
	 * @return The WSRP <code>Mode</code> represented by the passed string
	 */
	public static Modes fromString(java.lang.String value) {
		return fromValue(value);
	}

	public boolean equals(java.lang.Object obj) {
		return (obj == this);
	}

	public int hashCode() {
		return toString().hashCode();
	}

	public java.lang.String toString() {
		return _value_;
	}

	public java.lang.Object readResolve() throws java.io.ObjectStreamException {
		return fromValue(_value_);
	}

	/**
	 * This helper method maps portlet modes defined in wsrp to portlet modes
	 * defined in the java portlet standard (JSR-168). If the passed wsrp mode
	 * is null or can not be mapped the view mode is returned. 
	 *
	 * @return The <code>javax.portlet.PortletMode</code> which corresponds to the given wsrp mode.
	 **/
	public static PortletMode getJsrPortletModeFromWsrpMode(Modes wsrpMode) {
		if (wsrpMode == null) {
			return PortletMode.VIEW;
		}
		else if (wsrpMode.equals(Modes.edit)) {
			return PortletMode.EDIT;
		}
		else if (wsrpMode.equals(Modes.help)) {
			return PortletMode.HELP;
		}
		else if (wsrpMode.equals(Modes.view)) {
			return PortletMode.VIEW;
		}

		return PortletMode.VIEW;
	}

	/**
	 * This helper method maps portlet modes defined in tha java portlet standard (JSR-168)
	 * to modes defined in wsrp. If the passed portlet mode can not be resolved wsrp:view mode
	 * is returned.
	 *
	 * @param portletMode The <code>javax.portlet.PortletMode</code> which should be resolved as
	 *                     as portlet mode defined in wsrp.
	 * @return     
	 **/
	public static Modes getWsrpModeFromJsrPortletMode(PortletMode portletMode) {
		if (portletMode == null) {
			throw new IllegalArgumentException("Portlet mode must not be null.");
		}

		if (portletMode.equals(PortletMode.EDIT)) {
			return Modes.edit;
		}
		else if (portletMode.equals(PortletMode.HELP)) {
			return Modes.help;
		}
		else if (portletMode.equals(PortletMode.VIEW)) {
			return Modes.view;
		}

		return Modes.view;
	}
}