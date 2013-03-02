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

package com.liferay.util.servlet;

import com.liferay.portal.kernel.util.StringPool;

import java.io.Serializable;

import java.security.Principal;

/**
 * <a href="ProtectedPrincipal.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ProtectedPrincipal implements Principal, Serializable {

	public ProtectedPrincipal() {
		this(StringPool.BLANK);
	}

	public ProtectedPrincipal(String name) {
		_name = name;
	}

	public String getName() {
		return _name;
	}

	public boolean equals(Object obj) {
		if (obj == null) {
			return false;
		}

		if (this == obj) {
			return true;
		}

		if (obj instanceof ProtectedPrincipal) {
			ProtectedPrincipal protectedPrincipal = (ProtectedPrincipal)obj;

			if (protectedPrincipal.getName().equals(_name)) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}

	public int hashCode() {
		return _name.hashCode();
	}

	public String toString() {
		return _name;
	}

	private String _name;

}