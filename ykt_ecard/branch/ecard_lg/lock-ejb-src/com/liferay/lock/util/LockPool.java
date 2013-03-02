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

package com.liferay.lock.util;

import com.liferay.lock.DuplicateLockException;
import com.liferay.lock.ExpiredLockException;
import com.liferay.lock.NoSuchLockException;
import com.liferay.lock.model.Lock;
import com.liferay.util.CollectionFactory;

import java.lang.Comparable;

import java.util.Collections;
import java.util.Iterator;
import java.util.Map;
import java.util.Set;
import java.util.TreeSet;

/**
 * <a href="LockPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.11 $
 *
 */
public class LockPool {

	public static void clear() {
		_instance._clear();
	}

	public static Lock getLock(String className, Comparable pk)
		throws ExpiredLockException, NoSuchLockException {

		return _instance._getLock(className, pk);
	}

	public static Set getLocksByCompanyId(String companyId) {
		Set locksByCompanyId = _instance._getLocksByCompanyId(companyId);

		Iterator itr = locksByCompanyId.iterator();

		while (itr.hasNext()) {
			Lock lock = (Lock)itr.next();

			if (lock.isExpired()) {
				itr.remove();

				_instance._getLocks(
					lock.getClassName(), lock.getPrimaryKey()).remove(lock);
				_instance._getLocksByUserId(lock.getUserId()).remove(lock);
			}
		}

		return locksByCompanyId;
	}

	public static Set getLocksByUserId(String userId) {
		Set locksByUserId = _instance._getLocksByUserId(userId);

		Iterator itr = locksByUserId.iterator();

		while (itr.hasNext()) {
			Lock lock = (Lock)itr.next();

			if (lock.isExpired()) {
				itr.remove();

				_instance._getLocks(
					lock.getClassName(), lock.getPrimaryKey()).remove(lock);
				_instance._getLocksByCompanyId(
					lock.getCompanyId()).remove(lock);
			}
		}

		return locksByUserId;
	}

	public static boolean hasLock(
		String className, Comparable pk, String userId) {

		return _instance._hasLock(className, pk, userId);
	}

	public static boolean isLocked(String className, Comparable pk) {
		return _instance._isLocked(className, pk);
	}

	public static void lock(
			String className, Comparable pk, String companyId, String userId,
			long expirationTime)
		throws DuplicateLockException {

		_instance._lock(className, pk, companyId, userId, expirationTime);
	}

	public static void unlock(String className, Comparable pk) {
		_instance._unlock(className, pk);
	}

	private LockPool() {
		_locksByClassName = CollectionFactory.getSyncHashMap();
		_locksByCompanyId = CollectionFactory.getSyncHashMap();
		_locksByUserId = CollectionFactory.getSyncHashMap();
	}

	private void _clear() {
		_locksByClassName.clear();
		_locksByCompanyId.clear();
		_locksByUserId.clear();
	}

	private Lock _getLock(String className, Comparable pk)
		throws ExpiredLockException, NoSuchLockException {

		Map locksByPK = _getLocks(className, pk);

		Lock lock = (Lock)locksByPK.get(pk);

		if (lock == null) {
			throw new NoSuchLockException();
		}
		else if (lock.isExpired()) {
			_unlock(className, pk);

			throw new ExpiredLockException();
		}

		return lock;
	}

	private Map _getLocks(String className, Comparable pk) {
		Map locksByPK = (Map)_locksByClassName.get(className);

		if (locksByPK == null) {
			locksByPK =	CollectionFactory.getSyncHashMap();
			_locksByClassName.put(className, locksByPK);
		}

		return locksByPK;
	}

	private Set _getLocksByCompanyId(String companyId) {
		Set set = (Set)_locksByCompanyId.get(companyId);

		if (set == null) {
			set = Collections.synchronizedSet(new TreeSet());
			_locksByCompanyId.put(companyId, set);
		}

		return set;
	}

	private Set _getLocksByUserId(String userId) {
		Set set = (Set)_locksByUserId.get(userId);

		if (set == null) {
			set = Collections.synchronizedSet(new TreeSet());
			_locksByUserId.put(userId, set);
		}

		return set;
	}

	private boolean _hasLock(String className, Comparable pk, String userId) {
		try {
			Lock lock = _getLock(className, pk);

			if (lock.getUserId().equals(userId)) {
				return true;
			}
		}
		catch (ExpiredLockException ele) {
		}
		catch (NoSuchLockException nsle) {
		}

		return false;
	}

	private boolean _isLocked(String className, Comparable pk) {
		try {
			Lock lock = _getLock(className, pk);

			return true;
		}
		catch (ExpiredLockException ele) {
		}
		catch (NoSuchLockException nsle) {
		}

		return false;
	}

	private void _lock(
			String className, Comparable pk, String companyId, String userId,
			long expirationTime)
		throws DuplicateLockException {

		Map locksByPK = _getLocks(className, pk);

		Lock lock = (Lock)locksByPK.get(pk);

		if (lock != null && lock.isExpired()) {
			_unlock(className, pk);

			lock = null;
		}
		else if (lock != null && !lock.getUserId().equals(userId)) {
			throw new DuplicateLockException(lock);
		}

		if (lock == null) {
			lock = new Lock(className, pk, companyId, userId, expirationTime);

			locksByPK.put(pk, lock);
			_getLocksByCompanyId(companyId).add(lock);
			_getLocksByUserId(userId).add(lock);
		}
		else {
			lock.setExpirationTime(expirationTime);
		}
	}

	private void _unlock(String className, Comparable pk) {
		Map locksByPK = _getLocks(className, pk);

		Lock lock = (Lock)locksByPK.remove(pk);

		if (lock != null) {
			_getLocksByCompanyId(lock.getCompanyId()).remove(lock);
			_getLocksByUserId(lock.getUserId()).remove(lock);
		}
	}

	private static LockPool _instance = new LockPool();

	private Map _locksByClassName;
	private Map _locksByCompanyId;
	private Map _locksByUserId;

}