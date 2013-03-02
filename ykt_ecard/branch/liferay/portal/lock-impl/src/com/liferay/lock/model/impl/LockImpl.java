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

package com.liferay.lock.model.impl;

import com.liferay.lock.model.Lock;

import java.util.Date;

/**
 * <a href="LockImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class LockImpl implements Lock {

	public LockImpl(String className, Comparable pk, long companyId,
					long userId, long expirationTime) {

		_className = className;
		_pk = pk;
		_companyId = companyId;
		_userId = userId;
		_expirationTime = expirationTime;
		_date = new Date();
	}

	public String getClassName() {
		return _className;
	}

	public Comparable getPrimaryKey() {
		return _pk;
	}

	public long getCompanyId() {
		return _companyId;
	}

	public long getUserId() {
		return _userId;
	}

	public long getExpirationTime() {
		return _expirationTime;
	}

	public void setExpirationTime(long expirationTime) {
		_expirationTime = expirationTime;
		_date = new Date();
	}

	public boolean isExpired() {
		Date now = new Date();

		if (now.getTime() > _date.getTime() + _expirationTime) {
			return true;
		}
		else {
			return false;
		}
	}

	public Date getDate() {
		return _date;
	}

	public int compareTo(Object obj) {
		if (obj == null) {
			return -1;
		}

		Lock lock = (Lock)obj;

		int value = 0;
		value = getClassName().compareTo(lock.getClassName());

		if (value != 0) {
			return value;
		}

		value = getPrimaryKey().compareTo(lock.getPrimaryKey());

		if (value != 0) {
			return value;
		}

		value = getDate().compareTo(lock.getDate());

		if (value != 0) {
			return value;
		}

		return 0;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		Lock lock = (Lock)obj;

		if (getClassName().equals(lock.getClassName()) &&
			getPrimaryKey().equals(lock.getPrimaryKey())) {

			return true;
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return getClassName().hashCode() + getPrimaryKey().hashCode();
	}

	private String _className;
	private Comparable _pk;
	private long _companyId;
	private long _userId;
	private long _expirationTime;
	private Date _date;

}