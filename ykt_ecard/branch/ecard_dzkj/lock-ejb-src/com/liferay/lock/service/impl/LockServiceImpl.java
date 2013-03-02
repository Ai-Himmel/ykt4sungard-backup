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

package com.liferay.lock.service.impl;

import com.liferay.lock.model.Lock;
import com.liferay.lock.service.spring.LockService;
import com.liferay.lock.util.LockPool;
import com.liferay.portal.PortalException;

import java.lang.Comparable;

import java.util.Set;

/**
 * <a href="LockServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class LockServiceImpl implements LockService {

	public void clear() {
		LockPool.clear();
	}

	public Lock getLock(String className, Comparable pk)
		throws PortalException {

		return LockPool.getLock(className, pk);
	}

	public Set getLocksByCompanyId(String companyId) {
		return LockPool.getLocksByCompanyId(companyId);
	}

	public Set getLocksByUserId(String userId) {
		return LockPool.getLocksByUserId(userId);
	}

	public boolean hasLock(String className, Comparable pk, String userId) {
		return LockPool.hasLock(className, pk, userId);
	}

	public boolean isLocked(String className, Comparable pk) {
		return LockPool.isLocked(className, pk);
	}

	public void lock(
			String className, Comparable pk, String companyId, String userId,
			long expirationTime)
		throws PortalException {

		LockPool.lock(className, pk, companyId, userId, expirationTime);
	}

	public void unlock(String className, Comparable pk) {
		LockPool.unlock(className, pk);
	}

}