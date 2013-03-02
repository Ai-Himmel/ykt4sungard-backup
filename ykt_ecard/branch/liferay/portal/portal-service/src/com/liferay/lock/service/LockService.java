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

package com.liferay.lock.service;

import com.liferay.lock.model.Lock;
import com.liferay.portal.PortalException;

import java.rmi.RemoteException;

import java.util.Set;

/**
 * <a href="LockService.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public interface LockService {

	public void clear() throws RemoteException;

	public Lock getLock(String className, Comparable pk)
		throws PortalException, RemoteException;

	public Set getLocksByCompanyId(long companyId)
		throws RemoteException;

	public Set getLocksByUserId(long userId) throws RemoteException;

	public boolean hasLock(String className, Comparable pk, long userId)
		throws RemoteException;

	public boolean isLocked(String className, Comparable pk)
		throws RemoteException;

	public void lock(
			String className, Comparable pk, long companyId, long userId,
			long expirationTime)
		throws PortalException, RemoteException;

	public void unlock(String className, Comparable pk) throws RemoteException;

}