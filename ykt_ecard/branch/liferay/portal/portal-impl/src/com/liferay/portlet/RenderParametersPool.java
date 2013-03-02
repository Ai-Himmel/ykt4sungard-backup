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

package com.liferay.portlet;

import com.liferay.portal.util.WebKeys;
import com.liferay.util.CollectionFactory;

import java.util.HashMap;
import java.util.Map;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

/**
 * <a href="RenderParametersPool.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class RenderParametersPool {

	public static void clear(HttpServletRequest req, long plid) {
		Map plidPool = get(req, plid);

		plidPool.clear();
	}

	public static void clear(
		HttpServletRequest req, long plid, String portletId) {

		Map params = get(req, plid, portletId);

		params.clear();
	}

	public static Map get(HttpServletRequest req, long plid) {
		HttpSession ses = req.getSession();

		if (plid <= 0) {
			return CollectionFactory.getHashMap();
		}

		String key = RenderParametersPool.class.getName() + plid;

		Map pool = (Map)_getRenderParametersPool(ses);

		Map plidPool = (Map)pool.get(key);

		if (plidPool == null) {
			plidPool = CollectionFactory.getHashMap();

			pool.put(key, plidPool);
		}

		return plidPool;
	}

	public static Map get(HttpServletRequest req, long plid, String portletId) {
		Map plidPool = get(req, plid);

		Map params = (Map)plidPool.get(portletId);

		if (params == null) {
			params = new HashMap();

			plidPool.put(portletId, params);
		}

		return params;
	}

	public static void put(
		HttpServletRequest req, long plid, String portletId, Map params) {

		Map plidPool = get(req, plid);

		plidPool.put(portletId, params);
	}

	private static Map _getRenderParametersPool(HttpSession ses) {
		Map renderParametersPool =
			(Map)ses.getAttribute(WebKeys.PORTLET_RENDER_PARAMETERS);

		if (renderParametersPool == null) {
			renderParametersPool = CollectionFactory.getHashMap();

			ses.setAttribute(
				WebKeys.PORTLET_RENDER_PARAMETERS, renderParametersPool);
		}

		return renderParametersPool;
	}

}