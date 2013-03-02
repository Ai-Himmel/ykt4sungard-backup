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

package com.liferay.portlet;

import com.liferay.portal.model.Layout;
import com.liferay.portal.model.User;

import javax.portlet.PortletMode;
import javax.portlet.WindowState;

import javax.servlet.http.HttpServletResponse;

import org.apache.commons.pool.BasePoolableObjectFactory;
import org.apache.commons.pool.ObjectPool;
import org.apache.commons.pool.impl.StackObjectPool;

/**
 * <a href="ActionResponseFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.38 $
 *
 */
public class ActionResponseFactory {

	public static ActionResponseImpl create(
			ActionRequestImpl req, HttpServletResponse res, String portletName,
			User user, Layout layout, WindowState windowState,
			PortletMode portletMode)
		throws Exception {

		ActionResponseImpl actionResponseImpl =
			(ActionResponseImpl)_instance._pool.borrowObject();

		actionResponseImpl.init(
			req, res, portletName, user, layout, windowState, portletMode);

		return actionResponseImpl;
	}

	public static void recycle(ActionResponseImpl actionResponseImpl)
		throws Exception {

		_instance._pool.returnObject(actionResponseImpl);
	}

	private ActionResponseFactory() {
		_pool = new StackObjectPool(new Factory());
	}

	private static ActionResponseFactory _instance =
		new ActionResponseFactory();

	private ObjectPool _pool;

	private class Factory extends BasePoolableObjectFactory {

		public Object makeObject() {
			return new ActionResponseImpl();
		}

		public void passivateObject(Object obj) {
			ActionResponseImpl actionResponseImpl = (ActionResponseImpl)obj;

			actionResponseImpl.recycle();
		}

	}

}