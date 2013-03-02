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

package com.liferay.portlet.polls.service.persistence;

import com.liferay.portal.service.persistence.GlobalPool;

import com.liferay.portlet.polls.model.PollsQuestion;

import com.liferay.util.SystemProperties;
import com.liferay.util.Validator;

import com.opensymphony.oscache.base.NeedsRefreshException;
import com.opensymphony.oscache.general.GeneralCacheAdministrator;

/**
 * <a href="PollsQuestionPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class PollsQuestionPool {
	public static void clear() {
		_instance._clear();
	}

	public static PollsQuestion get(String questionId) {
		return _instance._get(questionId);
	}

	public static PollsQuestion put(String questionId, PollsQuestion obj) {
		return _instance._put(questionId, obj);
	}

	public static PollsQuestion remove(String questionId) {
		return _instance._remove(questionId);
	}

	private PollsQuestionPool() {
		_cacheable = PollsQuestion.CACHEABLE;

		int maxSize = PollsQuestion.MAX_SIZE;
		_cache = new GeneralCacheAdministrator(SystemProperties.getProperties());
		_cache.getCache().setCapacity(maxSize);
		GlobalPool.registerPool(PollsQuestionPool.class.getName());
	}

	private void _clear() {
		_cache.flushAll();
	}

	private PollsQuestion _get(String questionId) {
		if (!_cacheable) {
			return null;
		}
		else if (questionId == null) {
			return null;
		}
		else {
			PollsQuestion obj = null;
			String key = questionId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (PollsQuestion)_cache.getFromCache(key);
			}
			catch (NeedsRefreshException nfe) {
			}
			finally {
				if (obj == null) {
					_cache.cancelUpdate(key);
				}
			}

			return obj;
		}
	}

	private PollsQuestion _put(String questionId, PollsQuestion obj) {
		if (!_cacheable) {
			return obj;
		}
		else if (questionId == null) {
			return obj;
		}
		else {
			String key = questionId.toString();

			if (Validator.isNotNull(key)) {
				_cache.flushEntry(key);
				_cache.putInCache(key, obj);
			}

			return obj;
		}
	}

	private PollsQuestion _remove(String questionId) {
		if (!_cacheable) {
			return null;
		}
		else if (questionId == null) {
			return null;
		}
		else {
			PollsQuestion obj = null;
			String key = questionId.toString();

			if (Validator.isNull(key)) {
				return null;
			}

			try {
				obj = (PollsQuestion)_cache.getFromCache(key);
				_cache.flushEntry(key);
			}
			catch (NeedsRefreshException nfe) {
			}
			finally {
				if (obj == null) {
					_cache.cancelUpdate(key);
				}
			}

			return obj;
		}
	}

	private static PollsQuestionPool _instance = new PollsQuestionPool();
	private GeneralCacheAdministrator _cache;
	private boolean _cacheable;
}