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

package com.liferay.portlet.wsrp;

import oasis.names.tc.wsrp.v1.types.StateChange;

import org.apache.wsrp4j.consumer.driver.GenericConsumerEnvironment;
import org.apache.wsrp4j.consumer.driver.PortletDriverRegistryImpl;
import org.apache.wsrp4j.consumer.driver.URLRewriterImpl;
import org.apache.wsrp4j.consumer.util.ConsumerConstants;
import org.apache.wsrp4j.util.Constants;
import org.apache.wsrp4j.util.Modes;
import org.apache.wsrp4j.util.WindowStates;

/**
 * <a href="ConsumerEnvironmentImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Michael Young
 * @version $Revision: 1.6 $
 *
 */
public class ConsumerEnvironmentImpl extends GenericConsumerEnvironment {

	public ConsumerEnvironmentImpl() {

		// set the name of the consumer agent
		setConsumerAgent(CONSUMER_AGENT);

		// define the locales the consumer supports
		String[] supportedLocales = new String[2];
		supportedLocales[0] = Constants.LOCALE_EN_US;
		supportedLocales[1] = Constants.LOCALE_DE_DE;
		setSupportedLocales(supportedLocales);

		// define the modes the consumer supports
		String[] supportedModes = new String[3];
		supportedModes[0] = Modes._view;
		supportedModes[1] = Modes._help;
		supportedModes[2] = Modes._edit;
		setSupportedModes(supportedModes);

		// define the window states the consumer supports
		String[] supportedWindowStates = new String[3];
		supportedWindowStates[0] = WindowStates._normal;
		supportedWindowStates[1] = WindowStates._maximized;
		supportedWindowStates[2] = WindowStates._minimized;
		setSupportedWindowStates(supportedWindowStates);

		// define portlet state change behaviour
		setPortletStateChange(StateChange.readWrite);

		// define the mime types the consumer supports
		setMimeTypes(new String[] { Constants.MIME_TYPE_HTML });

		// define the character sets the consumer supports
		setCharacterEncodingSet(new String[] { Constants.UTF_8 });

		// set the authentication method the consumer uses
		setUserAuthentication(ConsumerConstants.NONE);

		// set consumer components
		setUserRegistry(UserRegistryImpl.getInstance());
		setSessionHandler(SessionHandlerImpl.getInstance(this));

		setPortletRegistry(PortletRegistryImpl.getInstance());
		setTemplateComposer(URLTemplateComposerImpl.getInstance());
		setURLRewriter(URLRewriterImpl.getInstance());
		setPortletDriverRegistry(PortletDriverRegistryImpl.getInstance(this));
		setProducerRegistry(ProducerRegistryImpl.getInstance());
	}

	private static final String CONSUMER_AGENT = "Liferay WSRP Consumer";

}