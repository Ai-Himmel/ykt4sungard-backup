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

package com.liferay.portal.webdav.methods;

import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.InstancePool;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.webdav.WebDAVException;
import com.liferay.util.CollectionFactory;

import java.util.Map;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MethodFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class MethodFactory {

	public static Method create(HttpServletRequest req)
		throws WebDAVException {

		return _instance._create(req);
	}

	private MethodFactory() {
		_methods = CollectionFactory.getHashMap();

		if (_log.isDebugEnabled()) {
			_log.debug("Delete method implementation " + _DELETE_METHOD_IMPL);
		}

		_methods.put("COPY", InstancePool.get(_COPY_METHOD_IMPL));
		_methods.put("DELETE", InstancePool.get(_DELETE_METHOD_IMPL));
		_methods.put("GET", InstancePool.get(_GET_METHOD_IMPL));
		_methods.put("HEAD", InstancePool.get(_HEAD_METHOD_IMPL));
		_methods.put("MKCOL", InstancePool.get(_MKCOL_METHOD_IMPL));
		_methods.put("MOVE", InstancePool.get(_MOVE_METHOD_IMPL));
		_methods.put("OPTIONS", InstancePool.get(_OPTIONS_METHOD_IMPL));
		_methods.put("PROPFIND", InstancePool.get(_PROPFIND_METHOD_IMPL));
		_methods.put("PROPPATCH", InstancePool.get(_PROPPATCH_METHOD_IMPL));
		_methods.put("PUT", InstancePool.get(_PUT_METHOD_IMPL));
	}

	private Method _create(HttpServletRequest req) throws WebDAVException {
		String method = req.getMethod();

		if (_log.isDebugEnabled()) {
			_log.debug("Get method " + method);
		}

		Method methodImpl = (Method)_methods.get(method.toUpperCase());

		if (methodImpl == null) {
			throw new WebDAVException(
				"Method " + method + " is not implemented");
		}
		else {
			if (_log.isDebugEnabled()) {
				_log.debug(
					"Method " + method + " is mapped to " +
						methodImpl.getClass().getName());
			}
		}

		return methodImpl;
	}

	private static final String _COPY_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".COPY"),
		CopyMethodImpl.class.getName());

	private static final String _DELETE_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".DELETE"),
		DeleteMethodImpl.class.getName());

	private static final String _GET_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".GET"),
		GetMethodImpl.class.getName());

	private static final String _HEAD_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".HEAD"),
		HeadMethodImpl.class.getName());

	private static final String _MKCOL_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".MKCOL"),
		MkcolMethodImpl.class.getName());

	private static final String _MOVE_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".MOVE"),
		MoveMethodImpl.class.getName());

	private static final String _OPTIONS_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".OPTIONS"),
		OptionsMethodImpl.class.getName());

	private static final String _PROPFIND_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".PROPFIND"),
		PropfindMethodImpl.class.getName());

	private static final String _PROPPATCH_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".PROPPATCH"),
		ProppatchMethodImpl.class.getName());

	private static final String _PUT_METHOD_IMPL = GetterUtil.getString(
		PropsUtil.get(MethodFactory.class.getName() + ".PUT"),
		PutMethodImpl.class.getName());

	private static Log _log = LogFactory.getLog(MethodFactory.class);

	private static MethodFactory _instance = new MethodFactory();

	private Map _methods;

}