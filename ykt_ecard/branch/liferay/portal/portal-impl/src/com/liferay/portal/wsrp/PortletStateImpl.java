/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
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

import java.util.HashMap;

import oasis.names.tc.wsrp.v1.types.ModelDescription;
import oasis.names.tc.wsrp.v1.types.PropertyList;

import org.apache.wsrp4j.producer.provider.PortletState;

import org.w3c.dom.Element;

/**
 * <a href="PortletStateImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 *
 */
public class PortletStateImpl implements PortletState {

	public void setAsElement(Element props) {
	}

	public Element getAsElement() {
		return null;
	}

	public Element getAsElement(String[] names) {
		return null;
	}

	public void setAsPropertyList(PropertyList props) {
	}

	public PropertyList getAsPropertyList() {
		return null;
	}

	public PropertyList getAsPropertylist(String[] names) {
		return null;
	}

	public void setAsString(String state) {
	}

	public String getAsString() {
		return null;
	}

	public String getAsString(String[] names) {
		return null;
	}

	public void setModelDescription(ModelDescription modelDescription) {
	}

	public ModelDescription getModelDescription() {
		return null;
	}

	public void setPortletHandle(String portletHandle) {
	}

	public String getPortletHandle() {
		return null;
	}

	public void setPropertyMap(HashMap propertyMap) {
	}

	public HashMap getPropertyMap() {
		return null;
	}

}