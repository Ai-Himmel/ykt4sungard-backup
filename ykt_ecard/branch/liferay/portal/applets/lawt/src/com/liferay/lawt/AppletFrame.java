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

package com.liferay.lawt;

import java.applet.Applet;
import java.applet.AppletContext;
import java.applet.AppletStub;
import java.applet.AudioClip;

import java.awt.Frame;
import java.awt.Image;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

import java.io.InputStream;

import java.net.URL;

import java.util.Enumeration;
import java.util.HashMap;
import java.util.Iterator;
import java.util.Map;

/**
 * <a href="AppletFrame.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class AppletFrame extends Frame implements AppletStub, AppletContext {

	public AppletFrame(Applet applet, int x, int y) {
		this(applet, new HashMap(), x, y);
	}

	public AppletFrame(Applet applet, Map params, int x, int y) {
		setTitle(applet.getClass().getName());
		setSize(x, y);

		_params = params;

		addWindowListener(
			new WindowAdapter() {
				public void windowClosing(WindowEvent e) {
					System.exit(0);
				}
			}
		);

		add(applet);
		applet.setStub(this);
		applet.init();
		show();
		applet.start();
	}

	// AppletStub methods

	public void appletResize(int width, int height) {
	}

	public AppletContext getAppletContext() {
		return this;
	}

	public URL getCodeBase() {
		return null;
	}

	public URL getDocumentBase() {
		return null;
	}

	public String getParameter(String name) {
		return (String)_params.get(name);
	}

	public boolean isActive() {
		return true;
	}

	// AppletContext methods

	public Applet getApplet(String name) {
		return null;
	}

	public Enumeration getApplets() {
		return null;
	}

	public AudioClip getAudioClip(URL url) {
		return null;
	}

	public Image getImage(URL url) {
		return null;
	}

	public InputStream getStream(String key) {
		return null;
	}

	public Iterator getStreamKeys() {
		return null;
	}

	public void setStream(String key, InputStream stream) {
	}

	public void showDocument(URL url) {
	}

	public void showDocument(URL url, String target) {
	}

	public void showStatus(String status) {
	}

	private Map _params;

}