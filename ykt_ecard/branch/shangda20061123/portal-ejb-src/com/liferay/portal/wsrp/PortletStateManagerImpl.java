/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */

package com.liferay.portal.wsrp;

import oasis.names.tc.wsrp.v1.types.ModelDescription;
import oasis.names.tc.wsrp.v1.types.PropertyList;

import org.apache.wsrp4j.producer.provider.PortletState;
import org.apache.wsrp4j.producer.provider.PortletStateManager;

/**
 * <a href="PortletStateManagerImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @version $Revision: 1.6 $
 *
 */
public class PortletStateManagerImpl implements PortletStateManager {

	public void setAsPropertyList(String portletHandle, PropertyList state) {
	}

	public PropertyList getAsPropertyList(String portletHandle) {
		return null;
	}

	public PropertyList getAsPropertyList(PortletState state) {
		return null;
	}

	public PropertyList getAsPropertyList(
		String portletHandle, String[] names) {

		return null;
	}

	public void setAsString(String portletHandle, String state) {
	}

	public String getAsString(String portletHandle) {
		return "";
	}

	public String getAsString(PortletState state) {
		return "";
	}

	public String getAsString(String portletHandle, String[] names) {
		return "";
	}

	public ModelDescription getModelDescription(
		String portletHandle, String[] desiredLocales, boolean sendAllLocales) {

		return null;
	}

	public void destroy(String portletHandle) {
	}

	public PortletState get(String portletHandle) {
		return null;
	}

	public void set(String portletHandle, PortletState state) {
	}

}