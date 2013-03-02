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

package com.liferay.portal.service.impl;

import com.liferay.portal.NoSuchPortletPreferencesException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Portlet;
import com.liferay.portal.model.PortletPreferences;
import com.liferay.portal.model.PortletPreferencesIds;
import com.liferay.portal.model.impl.PortletImpl;
import com.liferay.portal.service.base.PortletPreferencesLocalServiceBaseImpl;
import com.liferay.portlet.PortletPreferencesImpl;
import com.liferay.portlet.PortletPreferencesSerializer;

import java.util.List;
import java.util.Map;

/**
 * <a href="PortletPreferencesLocalServiceImpl.java.html"><b><i>View Source</i>
 * </b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class PortletPreferencesLocalServiceImpl
	extends PortletPreferencesLocalServiceBaseImpl {

	public void deletePortletPreferences(long portletPreferencesId)
		throws PortalException, SystemException {

		PortletPreferences portletPreferences =
			portletPreferencesPersistence.findByPrimaryKey(
				portletPreferencesId);

		long ownerId = portletPreferences.getOwnerId();
		int ownerType = portletPreferences.getOwnerType();

		portletPreferencesPersistence.remove(portletPreferences);

		PortletPreferencesLocalUtil.clearPreferencesPool(ownerId, ownerType);
	}

	public void deletePortletPreferences(long ownerId, int ownerType, long plid)
		throws PortalException, SystemException {

		portletPreferencesPersistence.removeByO_O_P(ownerId, ownerType, plid);

		PortletPreferencesLocalUtil.clearPreferencesPool(ownerId, ownerType);
	}

	public void deletePortletPreferences(
			long ownerId, int ownerType, long plid, String portletId)
		throws PortalException, SystemException {

		portletPreferencesPersistence.removeByO_O_P_P(
			ownerId, ownerType, plid, portletId);

		PortletPreferencesLocalUtil.clearPreferencesPool(ownerId, ownerType);
	}

	public javax.portlet.PortletPreferences getDefaultPreferences(
			long companyId, String portletId)
		throws PortalException, SystemException {

		Portlet portlet = portletLocalService.getPortletById(
			companyId, portletId);

		return PortletPreferencesSerializer.fromDefaultXML(
			portlet.getDefaultPreferences());
	}

	public List getPortletPreferences() throws SystemException {
		return portletPreferencesPersistence.findAll();
	}

	public List getPortletPreferences(long plid) throws SystemException {
		return portletPreferencesPersistence.findByPlid(plid);
	}

	public List getPortletPreferences(long plid, String portletId)
		throws SystemException {

		return portletPreferencesPersistence.findByP_P(plid, portletId);
	}

	public List getPortletPreferences(long ownerId, int ownerType, long plid)
		throws PortalException, SystemException {

		return portletPreferencesPersistence.findByO_O_P(
			ownerId, ownerType, plid);
	}

	public PortletPreferences getPortletPreferences(
			long ownerId, int ownerType, long plid, String portletId)
		throws PortalException, SystemException {

		return portletPreferencesPersistence.findByO_O_P_P(
			ownerId, ownerType, plid, portletId);
	}

	public javax.portlet.PortletPreferences getPreferences(
			PortletPreferencesIds portletPreferencesIds)
		throws PortalException, SystemException {

		return getPreferences(
			portletPreferencesIds.getCompanyId(),
			portletPreferencesIds.getOwnerId(),
			portletPreferencesIds.getOwnerType(),
			portletPreferencesIds.getPlid(),
			portletPreferencesIds.getPortletId());
	}

	public javax.portlet.PortletPreferences getPreferences(
			long companyId, long ownerId, int ownerType, long plid,
			String portletId)
		throws PortalException, SystemException {

		return getPreferences(
			companyId, ownerId, ownerType, plid, portletId, null);
	}

	public javax.portlet.PortletPreferences getPreferences(
			long companyId, long ownerId, int ownerType, long plid,
			String portletId, String defaultPreferences)
		throws PortalException, SystemException {

		Map prefsPool = PortletPreferencesLocalUtil.getPreferencesPool(
			ownerId, ownerType);

		String key = encodeKey(plid, portletId);

		PortletPreferencesImpl prefs =
			(PortletPreferencesImpl)prefsPool.get(key);

		if (prefs == null) {
			PortletPreferences portletPreferences = null;

			Portlet portlet = portletLocalService.getPortletById(
				companyId, portletId);

			try {
				portletPreferences =
					portletPreferencesPersistence.findByO_O_P_P(
						ownerId, ownerType, plid, portletId);
			}
			catch (NoSuchPortletPreferencesException nsppe) {
				long portletPreferencesId = counterLocalService.increment();

				portletPreferences = portletPreferencesPersistence.create(
					portletPreferencesId);

				portletPreferences.setOwnerId(ownerId);
				portletPreferences.setOwnerType(ownerType);
				portletPreferences.setPlid(plid);
				portletPreferences.setPortletId(portletId);

				if (Validator.isNull(defaultPreferences)) {
					if (portlet == null) {
						defaultPreferences = PortletImpl.DEFAULT_PREFERENCES;
					}
					else {
						defaultPreferences = portlet.getDefaultPreferences();
					}
				}

				portletPreferences.setPreferences(defaultPreferences);

				portletPreferencesPersistence.update(portletPreferences);
			}

			prefs = PortletPreferencesSerializer.fromXML(
				companyId, ownerId, ownerType, plid, portletId,
				portletPreferences.getPreferences());

			prefsPool.put(key, prefs);
		}

		return (PortletPreferencesImpl)prefs.clone();
	}

	public PortletPreferences updatePreferences(
			long ownerId, int ownerType, long plid, String portletId,
			javax.portlet.PortletPreferences prefs)
		throws PortalException, SystemException {

		PortletPreferences portletPreferences = null;

		try {
			portletPreferences = portletPreferencesPersistence.findByO_O_P_P(
				ownerId, ownerType, plid, portletId);
		}
		catch (NoSuchPortletPreferencesException nsppe) {
			long portletPreferencesId = counterLocalService.increment();

			portletPreferences = portletPreferencesPersistence.create(
				portletPreferencesId);

			portletPreferences.setOwnerId(ownerId);
			portletPreferences.setOwnerType(ownerType);
			portletPreferences.setPlid(plid);
			portletPreferences.setPortletId(portletId);
		}

		PortletPreferencesImpl prefsImpl = (PortletPreferencesImpl)prefs;

		String xml = PortletPreferencesSerializer.toXML(prefsImpl);

		portletPreferences.setPreferences(xml);

		portletPreferencesPersistence.update(portletPreferences);

		PortletPreferencesLocalUtil.clearPreferencesPool(ownerId, ownerType);

		return portletPreferences;
	}

	protected String encodeKey(long plid, String portletId) {
		StringMaker sm = new StringMaker();

		sm.append(plid);
		sm.append(StringPool.POUND);
		sm.append(portletId);

		return sm.toString();
	}

}