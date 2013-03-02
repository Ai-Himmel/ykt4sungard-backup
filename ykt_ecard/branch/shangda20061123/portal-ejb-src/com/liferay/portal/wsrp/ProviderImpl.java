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

package com.liferay.portal.wsrp;

import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.producer.provider.DescriptionHandler;
import org.apache.wsrp4j.producer.provider.PortletInvoker;
import org.apache.wsrp4j.producer.provider.PortletPool;
import org.apache.wsrp4j.producer.provider.PortletRegistrationFilter;
import org.apache.wsrp4j.producer.provider.PortletRegistrationFilterWriter;
import org.apache.wsrp4j.producer.provider.PortletStateManager;
import org.apache.wsrp4j.producer.provider.Provider;
import org.apache.wsrp4j.producer.provider.URLComposer;
import org.apache.wsrp4j.producer.provider.driver.PortletRegistrationFilterImpl;
import org.apache.wsrp4j.producer.provider.driver.URLComposerImpl;

/**
 * <a href="ProviderImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.8 $
 *
 */
public class ProviderImpl implements Provider {

	public DescriptionHandler getDescriptionHandler() {
		if (_descriptionHandler == null) {
			_descriptionHandler = new DescriptionHandlerImpl();
		}

		return _descriptionHandler;
	}

	public PortletInvoker getPortletInvoker() {
		if (_portletInvoker == null) {
			_portletInvoker = new PortletInvokerImpl(this);
		}

		return _portletInvoker;
	}

	public PortletPool getPortletPool() {
		if (_portletPool == null) {
			_portletPool = new PortletPoolImpl();
		}

		return _portletPool;
	}

	public PortletRegistrationFilter getPortletRegistrationFilter() {
		if (_portletRegistrationFilter == null) {
			_portletRegistrationFilter =
				PortletRegistrationFilterImpl.createReader();
		}

		return _portletRegistrationFilter;
	}

	public PortletRegistrationFilterWriter getPortletRegistrationFilterWriter() {
		if (_portletRegistrationFilterWriter == null) {
			_portletRegistrationFilterWriter =
				PortletRegistrationFilterImpl.createWriter();
		}

		return _portletRegistrationFilterWriter;
	}

	public PortletStateManager getPortletStateManager()
		throws WSRPException {
		if (_portletStateManager == null) {
			_portletStateManager = new PortletStateManagerImpl();
		}

		return _portletStateManager;
	}

	public URLComposer getURLComposer() {
		if (_urlComposer == null) {
			_urlComposer = URLComposerImpl.getInstance(this);
		}

		return _urlComposer;
	}

	private DescriptionHandler _descriptionHandler;
	private PortletInvoker _portletInvoker;
	private PortletPool _portletPool;
	private PortletRegistrationFilter _portletRegistrationFilter;
	private PortletRegistrationFilterWriter _portletRegistrationFilterWriter;
	private PortletStateManager _portletStateManager;
	private URLComposer _urlComposer;

}