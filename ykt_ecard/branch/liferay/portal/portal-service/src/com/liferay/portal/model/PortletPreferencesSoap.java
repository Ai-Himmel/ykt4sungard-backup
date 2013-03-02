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

package com.liferay.portal.model;

import java.io.Serializable;

import java.util.ArrayList;
import java.util.List;

/**
 * <a href="PortletPreferencesSoap.java.html"><b><i>View Source</i></b></a>
 *
 * <p>
 * ServiceBuilder generated this class. Modifications in this class will be
 * overwritten the next time is generated.
 * </p>
 *
 * <p>
 * This class is used by
 * <code>com.liferay.portal.service.http.PortletPreferencesServiceSoap</code>.
 * </p>
 *
 * @author Brian Wing Shun Chan
 *
 * @see com.liferay.portal.service.http.PortletPreferencesServiceSoap
 *
 */
public class PortletPreferencesSoap implements Serializable {
	public static PortletPreferencesSoap toSoapModel(PortletPreferences model) {
		PortletPreferencesSoap soapModel = new PortletPreferencesSoap();

		soapModel.setPortletPreferencesId(model.getPortletPreferencesId());
		soapModel.setOwnerId(model.getOwnerId());
		soapModel.setOwnerType(model.getOwnerType());
		soapModel.setPlid(model.getPlid());
		soapModel.setPortletId(model.getPortletId());
		soapModel.setPreferences(model.getPreferences());

		return soapModel;
	}

	public static PortletPreferencesSoap[] toSoapModels(List models) {
		List soapModels = new ArrayList(models.size());

		for (int i = 0; i < models.size(); i++) {
			PortletPreferences model = (PortletPreferences)models.get(i);

			soapModels.add(toSoapModel(model));
		}

		return (PortletPreferencesSoap[])soapModels.toArray(new PortletPreferencesSoap[0]);
	}

	public PortletPreferencesSoap() {
	}

	public long getPrimaryKey() {
		return _portletPreferencesId;
	}

	public void setPrimaryKey(long pk) {
		setPortletPreferencesId(pk);
	}

	public long getPortletPreferencesId() {
		return _portletPreferencesId;
	}

	public void setPortletPreferencesId(long portletPreferencesId) {
		_portletPreferencesId = portletPreferencesId;
	}

	public long getOwnerId() {
		return _ownerId;
	}

	public void setOwnerId(long ownerId) {
		_ownerId = ownerId;
	}

	public int getOwnerType() {
		return _ownerType;
	}

	public void setOwnerType(int ownerType) {
		_ownerType = ownerType;
	}

	public long getPlid() {
		return _plid;
	}

	public void setPlid(long plid) {
		_plid = plid;
	}

	public String getPortletId() {
		return _portletId;
	}

	public void setPortletId(String portletId) {
		_portletId = portletId;
	}

	public String getPreferences() {
		return _preferences;
	}

	public void setPreferences(String preferences) {
		_preferences = preferences;
	}

	private long _portletPreferencesId;
	private long _ownerId;
	private int _ownerType;
	private long _plid;
	private String _portletId;
	private String _preferences;
}