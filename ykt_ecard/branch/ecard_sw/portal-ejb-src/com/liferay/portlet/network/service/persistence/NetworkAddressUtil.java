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

package com.liferay.portlet.network.service.persistence;

import com.liferay.portal.model.ModelListener;
import com.liferay.portal.util.PropsUtil;

import com.liferay.util.GetterUtil;
import com.liferay.util.InstancePool;
import com.liferay.util.Validator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="NetworkAddressUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class NetworkAddressUtil {
	public static String PERSISTENCE = GetterUtil.get(PropsUtil.get(
				"value.object.persistence.com.liferay.portlet.network.model.NetworkAddress"),
			"com.liferay.portlet.network.service.persistence.NetworkAddressPersistence");
	public static String LISTENER = GetterUtil.getString(PropsUtil.get(
				"value.object.listener.com.liferay.portlet.network.model.NetworkAddress"));

	public static com.liferay.portlet.network.model.NetworkAddress create(
		java.lang.String addressId) {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.create(addressId);
	}

	public static com.liferay.portlet.network.model.NetworkAddress remove(
		java.lang.String addressId)
		throws com.liferay.portlet.network.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		if (listener != null) {
			listener.onBeforeRemove(findByPrimaryKey(addressId));
		}

		com.liferay.portlet.network.model.NetworkAddress networkAddress = persistence.remove(addressId);

		if (listener != null) {
			listener.onAfterRemove(networkAddress);
		}

		return networkAddress;
	}

	public static com.liferay.portlet.network.model.NetworkAddress update(
		com.liferay.portlet.network.model.NetworkAddress networkAddress)
		throws com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);
		ModelListener listener = null;

		if (Validator.isNotNull(LISTENER)) {
			try {
				listener = (ModelListener)Class.forName(LISTENER).newInstance();
			}
			catch (Exception e) {
				_log.error(e.getMessage());
			}
		}

		boolean isNew = networkAddress.isNew();

		if (listener != null) {
			if (isNew) {
				listener.onBeforeCreate(networkAddress);
			}
			else {
				listener.onBeforeUpdate(networkAddress);
			}
		}

		networkAddress = persistence.update(networkAddress);

		if (listener != null) {
			if (isNew) {
				listener.onAfterCreate(networkAddress);
			}
			else {
				listener.onAfterUpdate(networkAddress);
			}
		}

		return networkAddress;
	}

	public static com.liferay.portlet.network.model.NetworkAddress findByPrimaryKey(
		java.lang.String addressId)
		throws com.liferay.portlet.network.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByPrimaryKey(addressId);
	}

	public static java.util.List findByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end) throws com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end);
	}

	public static java.util.List findByUserId(java.lang.String userId,
		int begin, int end, com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId(userId, begin, end, obc);
	}

	public static com.liferay.portlet.network.model.NetworkAddress findByUserId_First(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.network.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_First(userId, obc);
	}

	public static com.liferay.portlet.network.model.NetworkAddress findByUserId_Last(
		java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.network.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_Last(userId, obc);
	}

	public static com.liferay.portlet.network.model.NetworkAddress[] findByUserId_PrevAndNext(
		java.lang.String addressId, java.lang.String userId,
		com.liferay.util.dao.hibernate.OrderByComparator obc)
		throws com.liferay.portlet.network.NoSuchAddressException, 
			com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findByUserId_PrevAndNext(addressId, userId, obc);
	}

	public static java.util.List findAll()
		throws com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.findAll();
	}

	public static void removeByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);
		persistence.removeByUserId(userId);
	}

	public static int countByUserId(java.lang.String userId)
		throws com.liferay.portal.SystemException {
		NetworkAddressPersistence persistence = (NetworkAddressPersistence)InstancePool.get(PERSISTENCE);

		return persistence.countByUserId(userId);
	}

	private static final Log _log = LogFactory.getLog(NetworkAddressUtil.class);
}