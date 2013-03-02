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

package com.liferay.lock.service.spring;

import com.liferay.lock.model.Lock;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;

import java.lang.Comparable;

import java.util.Set;

/**
 * <a href="LockServiceUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.8 $
 *
 */
public class LockServiceUtil {

	public static void clear() throws SystemException {
		try {
			LockService lockService = LockServiceFactory.getService();

			lockService.clear();
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static Lock getLock(String className, Comparable pk)
		throws PortalException, SystemException {

		try {
			LockService lockService = LockServiceFactory.getService();

			return lockService.getLock(className, pk);
		}
		catch (PortalException pe) {
			throw pe;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static Set getLocksByCompanyId(String companyId)
		throws SystemException {

		try {
			LockService lockService = LockServiceFactory.getService();

			return lockService.getLocksByCompanyId(companyId);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static Set getLocksByUserId(String userId) throws SystemException {
		try {
			LockService lockService = LockServiceFactory.getService();

			return lockService.getLocksByUserId(userId);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static boolean hasLock(
			String className, Comparable pk, String userId)
		throws SystemException {

		try {
			LockService lockService = LockServiceFactory.getService();

			return lockService.hasLock(className, pk, userId);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static boolean isLocked(String className, Comparable pk)
		throws SystemException {

		try {
			LockService lockService = LockServiceFactory.getService();

			return lockService.isLocked(className, pk);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void lock(
			String className, Comparable pk, String companyId, String userId,
			long expirationTime)
		throws PortalException, SystemException {

		try {
			LockService lockService = LockServiceFactory.getService();

			lockService.lock(
				className, pk, companyId, userId, expirationTime);
		}
		catch (PortalException pe) {
			throw pe;
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

	public static void unlock(String className, Comparable pk)
		throws SystemException {

		try {
			LockService lockService = LockServiceFactory.getService();

			lockService.unlock(className, pk);
		}
		catch (Exception e) {
			throw new SystemException(e);
		}
	}

}