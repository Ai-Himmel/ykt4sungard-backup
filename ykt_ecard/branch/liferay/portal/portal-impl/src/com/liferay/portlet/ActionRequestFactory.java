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

import com.liferay.portal.model.Portlet;
import com.liferay.portal.util.PropsValues;

import javax.portlet.PortletContext;
import javax.portlet.PortletMode;
import javax.portlet.PortletPreferences;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.pool.BasePoolableObjectFactory;
import org.apache.commons.pool.ObjectPool;
import org.apache.commons.pool.impl.StackObjectPool;

/**
 * <a href="ActionRequestFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class ActionRequestFactory {

	public static ActionRequestImpl create(
			HttpServletRequest req, Portlet portlet, CachePortlet cachePortlet,
			PortletContext portletCtx, WindowState windowState,
			PortletMode portletMode, PortletPreferences prefs, long plid)
		throws Exception {

		ActionRequestImpl actionRequestImpl = null;

		if (PropsValues.COMMONS_POOL_ENABLED) {
			actionRequestImpl =
				(ActionRequestImpl)_instance._pool.borrowObject();
		}
		else {
			actionRequestImpl = new ActionRequestImpl();
		}

		actionRequestImpl.init(
			req, portlet, cachePortlet, portletCtx, windowState, portletMode,
			prefs, plid);

		return actionRequestImpl;
	}

	public static void recycle(ActionRequestImpl actionRequestImpl)
		throws Exception {

		if (PropsValues.COMMONS_POOL_ENABLED) {
			_instance._pool.returnObject(actionRequestImpl);
		}
		else if (actionRequestImpl != null) {
			actionRequestImpl.recycle();
		}
	}

	private ActionRequestFactory() {
		_pool = new StackObjectPool(new Factory());
	}

	private static ActionRequestFactory _instance = new ActionRequestFactory();

	private ObjectPool _pool;

	private class Factory extends BasePoolableObjectFactory {

		public Object makeObject() {
			return new ActionRequestImpl();
		}

		public void passivateObject(Object obj) {
			ActionRequestImpl actionRequestImpl = (ActionRequestImpl)obj;

			actionRequestImpl.recycle();
		}

	}

}