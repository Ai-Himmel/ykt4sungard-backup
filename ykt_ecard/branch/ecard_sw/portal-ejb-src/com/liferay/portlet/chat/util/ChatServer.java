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

package com.liferay.portlet.chat.util;

import com.liferay.util.StringPool;

import com.lyrisoft.chat.Translator;
import com.lyrisoft.util.io.ResourceException;
import com.lyrisoft.util.properties.PropertyException;

import java.io.IOException;

import java.util.Properties;

import javax.servlet.ServletContext;

/**
 * <a href="ChatServer.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class ChatServer extends com.lyrisoft.chat.server.remote.ChatServer {

	public ChatServer(String conf, ServletContext ctx) throws Exception {
		super(conf, ctx);
	}

	public void initTranslator(Properties props) {
		try {
			Translator.getMessage("none");
		}
		catch (Exception e) {

			// Ensure that the translator is only initialized once

			Translator.init(props);
		}
	}

	protected int getAvailablePort(Properties props) throws PropertyException {
		return ChatUtil.getNextPort();
	}

	protected void readMotd() throws ResourceException, IOException {
		_motd = StringPool.BLANK;
	}

	protected void createLoggers(String logFile, String errorLogFile) {
		logger = new Logger(Logger.LOG_LEVEL_INFO);
		errorLogger = new Logger(Logger.LOG_LEVEL_ERROR);
	}

}