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
import org.apache.wsrp4j.producer.ConsumerRegistry;
import org.apache.wsrp4j.producer.ConsumerRegistryFactory;
import org.apache.wsrp4j.producer.provider.Provider;

/**
 * <a href="ConsumerRegistryFactoryImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Michael Young
 * @version $Revision: 1.3 $
 *
 */
public class ConsumerRegistryFactoryImpl implements ConsumerRegistryFactory {

	/**
	 * Returns an instance of the ConsumerRegistryImpl-class.
	 *
	 * @param provider
	 *            A provider interface.
	 *
	 * @return ConsumerRegistry An instance of ConsumerRegistryImpl.
	 */
	public ConsumerRegistry getConsumerRegistry(Provider provider)
			throws WSRPException {

		if (_consumerReg == null) {
			_consumerReg = new ConsumerRegistryImpl(provider);
		}

		return _consumerReg;
	}

	// holds an instance of a consumer registry
	private ConsumerRegistryImpl _consumerReg = null;

}