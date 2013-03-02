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

package com.liferay.portal.webdav.methods;

import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.Tuple;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.WebDAVProps;
import com.liferay.portal.service.GroupLocalServiceUtil;
import com.liferay.portal.service.WebDAVPropsLocalServiceUtil;
import com.liferay.portal.webdav.BaseResourceImpl;
import com.liferay.portal.webdav.Resource;
import com.liferay.portal.webdav.WebDAVRequest;
import com.liferay.portal.webdav.WebDAVStorage;
import com.liferay.portal.webdav.WebDAVUtil;
import com.liferay.util.xml.DocUtil;
import com.liferay.util.xml.XMLFormatter;

import java.util.Arrays;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

import org.dom4j.Document;
import org.dom4j.DocumentFactory;
import org.dom4j.Element;
import org.dom4j.Namespace;
import org.dom4j.QName;

/**
 * <a href="BasePropMethodImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public abstract class BasePropMethodImpl implements Method {

	protected void addResponse(
			WebDAVStorage storage, WebDAVRequest webDavReq,
			Resource resource, Set props, Element multistatus, long depth)
		throws Exception {

		addResponse(webDavReq, resource, props, multistatus);

		if (resource.isCollection() && (depth != 0)) {
			Iterator itr = storage.getResources(webDavReq).iterator();

			while (itr.hasNext()) {
				resource = (Resource)itr.next();

				addResponse(webDavReq, resource, props, multistatus);
			}
		}
	}

	protected void addResponse(
			WebDAVRequest webDavReq, Resource resource, Set props,
			Element multistatus)
		throws Exception {

		// Make a deep copy of the props

		props = new HashSet(props);

		// Start building multistatus response

		Element response = DocUtil.add(
			multistatus, "response", WebDAVUtil.DAV_URI);

		DocUtil.add(response, "href", WebDAVUtil.DAV_URI, resource.getHREF());

		// Build success and failure propstat elements

		Element successStat = DocUtil.add(
			response, "propstat", WebDAVUtil.DAV_URI);
		Element successProp = DocUtil.add(
			successStat, "prop", WebDAVUtil.DAV_URI);
		Element failureStat = DocUtil.add(
			response, "propstat", WebDAVUtil.DAV_URI);
		Element failureProp = DocUtil.add(
			failureStat, "prop", WebDAVUtil.DAV_URI);

		boolean hasSuccess = false;
		boolean hasFailure = false;

		// Check DAV properties

		if (props.contains(_ALL_PROPS_PAIR)) {
			props.remove(_ALL_PROPS_PAIR);

			if (resource.isCollection()) {
				props.addAll(_ALL_COLLECTION_PROPS);
			}
			else {
				props.addAll(_ALL_SIMPLE_PROPS);
			}
		}

		if (props.contains(_CREATIONDATE_PAIR)) {
			props.remove(_CREATIONDATE_PAIR);

			DocUtil.add(
				successProp, _CREATIONDATE, WebDAVUtil.DAV_URI,
				resource.getCreateDate());

			hasSuccess = true;
		}

		if (props.contains(_DISPLAYNAME_PAIR)) {
			props.remove(_DISPLAYNAME_PAIR);

			DocUtil.add(
				successProp, _DISPLAYNAME, WebDAVUtil.DAV_URI,
				resource.getDisplayName());

			hasSuccess = true;
		}

		if (props.contains(_GETLASTMODIFIED_PAIR)) {
			props.remove(_GETLASTMODIFIED_PAIR);

			DocUtil.add(
				successProp, _GETLASTMODIFIED, WebDAVUtil.DAV_URI,
				resource.getModifiedDate());

			hasSuccess = true;
		}

		if (props.contains(_GETCONTENTTYPE_PAIR)) {
			props.remove(_GETCONTENTTYPE_PAIR);

			DocUtil.add(
				successProp, _GETCONTENTTYPE, WebDAVUtil.DAV_URI,
				resource.getContentType());

			hasSuccess = true;
		}

		if (props.contains(_GETCONTENTLENGTH_PAIR)) {
			props.remove(_GETCONTENTLENGTH_PAIR);

			if (!resource.isCollection()) {
				DocUtil.add(
					successProp, _GETCONTENTLENGTH, WebDAVUtil.DAV_URI,
					resource.getSize());

				hasSuccess = true;
			}
			else {
				DocUtil.add(
					failureProp, _GETCONTENTLENGTH, WebDAVUtil.DAV_URI);

				hasFailure = true;
			}
		}

		if (props.contains(_RESOURCETYPE_PAIR)) {
			props.remove(_RESOURCETYPE_PAIR);

			Element resourceType =
				DocUtil.add(successProp, _RESOURCETYPE, WebDAVUtil.DAV_URI);

			if (resource.isCollection()) {
				DocUtil.add(resourceType, "collection", WebDAVUtil.DAV_URI);
			}

			hasSuccess = true;
		}

		// Check remaining properties against custom properties

		WebDAVProps webDavProps = WebDAVPropsLocalServiceUtil.getWebDAVProps(
			webDavReq.getCompanyId(), resource.getClassName(),
			resource.getPrimaryKey());

		Set customProps = webDavProps.getPropsSet();

		Iterator itr = props.iterator();

		while (itr.hasNext()) {
			Tuple tuple = (Tuple)itr.next();

			String name = (String)tuple.getObject(0);
			Namespace namespace = (Namespace)tuple.getObject(1);

			String prefix = namespace.getPrefix();
			String uri = namespace.getURI();

			if (customProps.contains(tuple)) {
				String text = webDavProps.getText(name, prefix, uri);

				DocUtil.add(successProp, name, namespace, text);

				hasSuccess = true;
			}
			else {
				DocUtil.add(failureProp, name, namespace);

				hasFailure = true;
			}
		}

		// Clean up propstats

		if (hasSuccess) {
			DocUtil.add(
				successStat, "status", WebDAVUtil.DAV_URI, "HTTP/1.1 200 OK");
		}
		else {
			response.remove(successStat);
		}

		if (hasFailure) {
			DocUtil.add(
				failureStat, "status", WebDAVUtil.DAV_URI,
				"HTTP/1.1 404 Not Found");
		}
		else {
			response.remove(failureStat);
		}
	}

	protected void addResponse(String href, Element multistatus)
		throws Exception {

		Element response = DocUtil.add(
			multistatus, "response", WebDAVUtil.DAV_URI);

		DocUtil.add(response, "href", WebDAVUtil.DAV_URI, href);

		Element propstat = DocUtil.add(
			response, "propstat", WebDAVUtil.DAV_URI);

		DocUtil.add(
			propstat, "status", WebDAVUtil.DAV_URI, "HTTP/1.1 404 Not Found");
	}

	protected String getResponseXML(WebDAVRequest webDavReq, Set props)
		throws Exception {

		WebDAVStorage storage = webDavReq.getWebDAVStorage();

		long companyId = webDavReq.getCompanyId();
		long groupId = webDavReq.getGroupId();
		long depth = WebDAVUtil.getDepth(webDavReq.getHttpServletRequest());

		DocumentFactory docFactory = DocumentFactory.getInstance();

		Document doc = docFactory.createDocument();

		Element multistatus = docFactory.createElement(
			new QName("multistatus", WebDAVUtil.DAV_URI));

		doc.setRootElement(multistatus);

		if (companyId <= 0) {
			return getResponseXML(doc);
		}

		if (groupId == 0) {
			addResponse(
				webDavReq,
				new BaseResourceImpl(
					storage.getRootPath(), companyId, companyId),
				props, multistatus);

			if (props.size() > 0) {
				Iterator itr = storage.getCommunities(webDavReq).iterator();

				while (itr.hasNext()) {
					Resource resource = (Resource)itr.next();

					addResponse(webDavReq, resource, props, multistatus);
				}
			}

			return getResponseXML(doc);
		}

		Resource resource = storage.getResource(webDavReq);

		if ((resource == null) && !webDavReq.isGroupPath()) {
			String href = storage.getRootPath() + webDavReq.getPath();

			if (_log.isWarnEnabled()) {
				_log.warn("No resource found for " + webDavReq.getPath());
			}

			addResponse(href, multistatus);

			return getResponseXML(doc);
		}

		try {
			if (resource != null) {
				addResponse(
					storage, webDavReq, resource, props, multistatus, depth);
			}
			else if (webDavReq.isGroupPath()) {
				Group group = GroupLocalServiceUtil.getGroup(groupId);

				resource = new BaseResourceImpl(
					storage.getRootPath() + StringPool.SLASH + companyId,
					groupId, group.getName());

				addResponse(
					storage, webDavReq, resource, props, multistatus, depth);
			}
		}
		catch (NoSuchGroupException nsge) {
			String href = storage.getRootPath() + webDavReq.getPath();

			if (_log.isWarnEnabled()) {
				_log.warn("No group found for " + href);
			}

			addResponse(href, multistatus);
		}

		return getResponseXML(doc);
	}

	protected String getResponseXML(Document doc) throws Exception {
		String xml = XMLFormatter.toString(doc, StringPool.FOUR_SPACES);

		if (_log.isDebugEnabled()) {
			_log.debug("Response XML\n" + xml);
		}

		return xml;
	}

	private static final String _ALLPROPS = "allprops";

	private static final String _CREATIONDATE = "creationdate";

	private static final String _DISPLAYNAME = "displayname";

	private static final String _GETLASTMODIFIED = "getlastmodified";

	private static final String _GETCONTENTTYPE = "getcontenttype";

	private static final String _GETCONTENTLENGTH = "getcontentlength";

	private static final String _RESOURCETYPE = "resourcetype";

	private static final Tuple _ALL_PROPS_PAIR =
		new Tuple(_ALLPROPS, WebDAVUtil.DAV_URI);

	private static final Tuple _CREATIONDATE_PAIR =
		new Tuple(_CREATIONDATE, WebDAVUtil.DAV_URI);

	private static final Tuple _DISPLAYNAME_PAIR =
		new Tuple(_DISPLAYNAME, WebDAVUtil.DAV_URI);

	private static final Tuple _GETLASTMODIFIED_PAIR =
		new Tuple(_GETCONTENTLENGTH, WebDAVUtil.DAV_URI);

	private static final Tuple _GETCONTENTTYPE_PAIR =
		new Tuple(_GETCONTENTTYPE, WebDAVUtil.DAV_URI);

	private static final Tuple _GETCONTENTLENGTH_PAIR =
		new Tuple(_GETLASTMODIFIED, WebDAVUtil.DAV_URI);

	private static final Tuple _RESOURCETYPE_PAIR =
		new Tuple(_RESOURCETYPE, WebDAVUtil.DAV_URI);

	private final List _ALL_COLLECTION_PROPS = Arrays.asList(
		new Object[] {
			_CREATIONDATE_PAIR, _DISPLAYNAME_PAIR, _GETLASTMODIFIED_PAIR,
			_GETCONTENTTYPE_PAIR, _RESOURCETYPE_PAIR
		});

	private final List _ALL_SIMPLE_PROPS = Arrays.asList(
		new Object[] {
			_CREATIONDATE_PAIR, _DISPLAYNAME_PAIR, _GETLASTMODIFIED_PAIR,
			_GETCONTENTTYPE_PAIR, _GETCONTENTLENGTH_PAIR, _RESOURCETYPE_PAIR
		});

	private static Log _log = LogFactory.getLog(BasePropMethodImpl.class);

}