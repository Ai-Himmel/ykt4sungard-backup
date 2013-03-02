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

import com.liferay.portal.service.spring.PortletServiceUtil;
import com.liferay.portal.wsrp.util.WSRPUtil;
import com.liferay.util.CollectionFactory;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;
import java.util.Map;

import org.apache.wsrp4j.exception.WSRPException;
import org.apache.wsrp4j.producer.provider.ConsumerConfiguredPortlet;
import org.apache.wsrp4j.producer.provider.Portlet;
import org.apache.wsrp4j.producer.provider.PortletPool;
import org.apache.wsrp4j.producer.provider.ProducerOfferedPortlet;
import org.apache.wsrp4j.producer.provider.driver.ConsumerConfiguredPortletImpl;
import org.apache.wsrp4j.producer.provider.driver.ProducerOfferedPortletImpl;

/**
 * <a href="PortletPoolImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.8 $
 *
 */
public class PortletPoolImpl implements PortletPool {

	public Iterator getAllConsumerConfiguredPortlets() {
		return _consumerConfiguredPortlets.values().iterator();
	}

	public Iterator getAllProducerOfferedPortlets() {
		String companyId = WSRPUtil.getCompanyId();
		Iterator wsrpPortletsIt = null;
		List wsrpPortlets = new ArrayList();

		try {
			List liferayPortlets = PortletServiceUtil.getPortlets(companyId);

			for (int i = 0; i < liferayPortlets.size(); i++) {
				com.liferay.portal.model.Portlet liferayPortlet = (com.liferay.portal.model.Portlet) liferayPortlets
						.get(i);

				Portlet producerPortlet = _createProducerPortlet(liferayPortlet);

				wsrpPortlets.add(producerPortlet);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}

		return wsrpPortlets.iterator();
	}

	public Portlet clone(String portletHandle) throws WSRPException {
		Portlet portlet = (Portlet) _consumerConfiguredPortlets
				.get(portletHandle);

		// we don't really support cloning right now
		// this is done be compliant with the wsrp4j implementation
		if (portlet != null) {
			return null;
		}
		else {
			portlet = _createConsumerPortlet(portletHandle);
			_consumerConfiguredPortlets.put(portletHandle, portlet);
		}

		return portlet;
	}

	public boolean destroy(String portletHandle) throws WSRPException {
		// we do not support cloning yet
		return false;
	}

	public Iterator destroySeveral(Iterator portletHandles) {
		// we do not support cloning yet
		return null;
	}

	public Portlet get(String portletHandle) throws WSRPException {
		Portlet wsrpPortlet = null;

		try {
			wsrpPortlet = (Portlet) _consumerConfiguredPortlets
					.get(portletHandle);

			if (wsrpPortlet == null) {
				String companyId = WSRPUtil.getCompanyId();

				com.liferay.portal.model.Portlet liferayPortlet = PortletServiceUtil
						.getPortletById(companyId, portletHandle);

				if (liferayPortlet != null) {
					wsrpPortlet = _createProducerPortlet(liferayPortlet);
				}
			}
		}
		catch (Exception e) {
		}

		return wsrpPortlet;
	}

	private Portlet _createProducerPortlet(String portletHandle) {
		ProducerOfferedPortlet producerPortlet = new ProducerOfferedPortletImpl();

		producerPortlet.setPortletHandle(portletHandle);
		producerPortlet.setRegistrationRequired(false);

		return producerPortlet;
	}

	private Portlet _createConsumerPortlet(String portletHandle) {
		ConsumerConfiguredPortlet consumerPortlet = new ConsumerConfiguredPortletImpl();

		consumerPortlet.setPortletHandle(portletHandle);
		consumerPortlet.setParentHandle(portletHandle);

		return consumerPortlet;
	}

	private Portlet _createProducerPortlet(
			com.liferay.portal.model.Portlet liferayPortlet) {
		return _createProducerPortlet(liferayPortlet.getPortletId());
	}

	private Map _consumerConfiguredPortlets = CollectionFactory.getHashMap();

}