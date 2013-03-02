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

import com.liferay.portal.util.Constants;
import com.liferay.util.velocity.ServletResourceLoader;

import java.io.IOException;
import java.io.PrintWriter;

import javax.portlet.ActionRequest;
import javax.portlet.ActionResponse;
import javax.portlet.GenericPortlet;
import javax.portlet.PortletConfig;
import javax.portlet.PortletContext;
import javax.portlet.PortletException;
import javax.portlet.PortletRequest;
import javax.portlet.PortletResponse;
import javax.portlet.RenderRequest;
import javax.portlet.RenderResponse;

import org.apache.velocity.Template;
import org.apache.velocity.VelocityContext;
import org.apache.velocity.context.Context;
import org.apache.velocity.io.VelocityWriter;
import org.apache.velocity.runtime.RuntimeSingleton;
import org.apache.velocity.util.SimplePool;

/**
 * <a href="VelocityPortlet.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Steven P. Goldsmith
 * @version $Revision: 1.11 $
 *
 */
public class VelocityPortlet extends GenericPortlet {

	/**
	 * The context key for the portlet request.
	 */
	public static final String REQUEST = "VelocityPortlet.portletRequest";

	/**
	 * The context key for the portlet response.
	 */
	public static final String RESPONSE = "VelocityPortlet.portletResponse";

	/**
	 * Cache of writers.
	 */
	private static SimplePool writerPool = new SimplePool(40);

	public void init(PortletConfig config) throws PortletException {
		super.init(config);

		PortletContext portletCtx = config.getPortletContext();

		_portletContextName = portletCtx.getPortletContextName();

		_editTemplate = getInitParameter("edit-template");
		_helpTemplate = getInitParameter("help-template");
		_viewTemplate = getInitParameter("view-template");
	}

	public void doEdit(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		if (req.getPreferences() == null) {
			super.doEdit(req, res);
		}
		else {
			try {
				mergeTemplate(getTemplate(_editTemplate), req, res);
			}
			catch (Exception e) {
				throw new PortletException(e);
			}
		}
	}

	public void doHelp(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		try {
			mergeTemplate(getTemplate(_helpTemplate), req, res);
		}
		catch (Exception e) {
			throw new PortletException(e);
		}
	}

	public void doView(RenderRequest req, RenderResponse res)
		throws IOException, PortletException {

		try {
			mergeTemplate(getTemplate(_viewTemplate), req, res);
		}
		catch (Exception e) {
			throw new PortletException(e);
		}
	}

	public void processAction(ActionRequest req, ActionResponse res)
		throws IOException, PortletException {
	}

	protected Context getContext(PortletRequest req, PortletResponse res) {
		Context context = new VelocityContext();

		context.put(REQUEST, req);
		context.put(RESPONSE, res);

		return context;
	}

	protected Template getTemplate(String name) throws Exception {
		return RuntimeSingleton.getTemplate(
			_portletContextName + ServletResourceLoader.CONTEXT_SEPARATOR +
			Constants.TEXT_HTML_DIR + name);
	}

	protected Template getTemplate(String name, String encoding)
		throws Exception {

		return RuntimeSingleton.getTemplate(
			Constants.TEXT_HTML_DIR + name, encoding);
	}

	protected void mergeTemplate(
			Template template, RenderRequest req, RenderResponse res)
		throws Exception {

		mergeTemplate(template, getContext(req, res), req, res);
	}

	protected void mergeTemplate(
			Template template, Context context, RenderRequest req,
			RenderResponse res)
		throws Exception {

		res.setContentType(req.getResponseContentType());

		VelocityWriter velocityWriter = null;

		try {
			velocityWriter = (VelocityWriter)writerPool.get();

			PrintWriter output = res.getWriter();

			if (velocityWriter == null) {
				velocityWriter = new VelocityWriter(output, 4 * 1024, true);
			}
			else {
				velocityWriter.recycle(output);
			}

			template.merge(context, velocityWriter);
		}
		finally {
			try {
				if (velocityWriter != null) {
					velocityWriter.flush();
					velocityWriter.recycle(null);

					writerPool.put(velocityWriter);
				}
			}
			catch (Exception e) {
			}
		}
	}

	private String _portletContextName;
	private String _editTemplate;
	private String _helpTemplate;
	private String _viewTemplate;

}