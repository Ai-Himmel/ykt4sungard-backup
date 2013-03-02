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

package com.liferay.portal.lar;

import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.lar.UserIdStrategy;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.User;
import com.liferay.portal.service.persistence.UserUtil;

import java.util.Iterator;
import java.util.List;

/**
 * <a href="CurrentUserIdStrategy.java.html"><b><i>View Source</i></b></a>
 *
 * @author Bruno Farache
 *
 */
public class CurrentUserIdStrategy implements UserIdStrategy {

	public CurrentUserIdStrategy(User user) {
		_user = user;
	}

	public long getUserId(String userUuid) throws SystemException {
		if (Validator.isNull(userUuid)) {
			return _user.getUserId();
		}

		List users = UserUtil.findByUuid(userUuid);

		Iterator itr = users.iterator();

		if (itr.hasNext()) {
			User user = (User)itr.next();

			return user.getUserId();
		}
		else {
			return _user.getUserId();
		}
	}

	private User _user;

}