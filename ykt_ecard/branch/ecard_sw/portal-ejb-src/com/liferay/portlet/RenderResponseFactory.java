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

import javax.servlet.http.HttpServletResponse;

import org.apache.commons.pool.BasePoolableObjectFactory;
import org.apache.commons.pool.ObjectPool;
import org.apache.commons.pool.impl.StackObjectPool;

/**
 * <a href="RenderResponseFactory.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.38 $
 *
 */
public class RenderResponseFactory {

	public static RenderResponseImpl create(
			RenderRequestImpl req, HttpServletResponse res, String portletName,
			String companyId)
		throws Exception {

		return create(req, res, portletName, companyId, null);
	}

	public static RenderResponseImpl create(
			RenderRequestImpl req, HttpServletResponse res, String portletName,
			String companyId, String layoutId)
		throws Exception {

		RenderResponseImpl renderResponseImpl =
			(RenderResponseImpl)_instance._pool.borrowObject();

		renderResponseImpl.init(req, res, portletName, companyId, layoutId);

		return renderResponseImpl;
	}

	public static void recycle(RenderResponseImpl renderResponseImpl)
		throws Exception {

		_instance._pool.returnObject(renderResponseImpl);
	}

	private RenderResponseFactory() {
		_pool = new StackObjectPool(new Factory());
	}

	private static RenderResponseFactory _instance =
		new RenderResponseFactory();

	private ObjectPool _pool;

	private class Factory extends BasePoolableObjectFactory {

		public Object makeObject() {
			return new RenderResponseImpl();
		}

		public void passivateObject(Object obj) {
			RenderResponseImpl renderResponseImpl = (RenderResponseImpl)obj;

			renderResponseImpl.recycle();
		}

	}

}