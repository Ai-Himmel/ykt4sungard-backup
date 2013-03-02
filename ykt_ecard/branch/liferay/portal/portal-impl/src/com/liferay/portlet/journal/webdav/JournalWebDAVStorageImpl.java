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

package com.liferay.portlet.journal.webdav;

import com.liferay.portal.PortalException;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.webdav.BaseResourceImpl;
import com.liferay.portal.webdav.BaseWebDAVStorageImpl;
import com.liferay.portal.webdav.Resource;
import com.liferay.portal.webdav.Status;
import com.liferay.portal.webdav.WebDAVException;
import com.liferay.portal.webdav.WebDAVRequest;
import com.liferay.portlet.journal.NoSuchStructureException;
import com.liferay.portlet.journal.NoSuchTemplateException;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.model.JournalTemplate;
import com.liferay.portlet.journal.service.JournalStructureLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalStructureServiceUtil;
import com.liferay.portlet.journal.service.JournalTemplateLocalServiceUtil;
import com.liferay.portlet.journal.service.JournalTemplateServiceUtil;

import java.io.File;

import java.util.ArrayList;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpServletResponse;

/**
 * <a href="JournalWebDAVStorageImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author Brian Wing Shun Chan
 *
 */
public class JournalWebDAVStorageImpl extends BaseWebDAVStorageImpl {

	public Status addCollection(WebDAVRequest webDavReq)
		throws WebDAVException {

		return new Status(HttpServletResponse.SC_FORBIDDEN);
	}

	public int copyCollectionResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite, long depth)
		throws WebDAVException {

		return HttpServletResponse.SC_FORBIDDEN;
	}

	public int copySimpleResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException {

		return HttpServletResponse.SC_FORBIDDEN;
	}

	public int deleteResource(WebDAVRequest webDavReq) throws WebDAVException {
		try {
			Resource resource = getResource(webDavReq);

			if (resource == null) {
				return HttpServletResponse.SC_NOT_FOUND;
			}

			Object model = resource.getModel();

			if (model instanceof JournalStructure) {
				JournalStructure structure = (JournalStructure)model;

				JournalStructureServiceUtil.deleteStructure(
					structure.getGroupId(), structure.getStructureId());

				return HttpServletResponse.SC_NO_CONTENT;
			}
			else if (model instanceof JournalTemplate) {
				JournalTemplate template = (JournalTemplate)model;

				JournalTemplateServiceUtil.deleteTemplate(
					template.getGroupId(), template.getTemplateId());

				return HttpServletResponse.SC_NO_CONTENT;
			}
			else {
				return HttpServletResponse.SC_FORBIDDEN;
			}
		}
		catch (PortalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public Resource getResource(WebDAVRequest webDavReq)
		throws WebDAVException {

		try {
			String[] pathArray = webDavReq.getPathArray();

			if (pathArray.length == 3) {
				//String companyId = pathArray[0];
				//String groupId = pathArray[1];
				String type = pathArray[2];

				return toResource(webDavReq, type, false);
			}
			else if (pathArray.length == 4) {
				//String companyId = pathArray[0];
				//String groupId = pathArray[1];
				String type = pathArray[2];
				String journalTypeId = pathArray[3];

				if (type.equals(_TYPE_STRUCTURES)) {
					try {
						JournalStructure journalStructure =
							JournalStructureLocalServiceUtil.getStructure(
								webDavReq.getGroupId(), journalTypeId);

						return toResource(webDavReq, journalStructure, false);
					}
					catch (NoSuchStructureException nsse) {
						return null;
					}
				}
				else if (type.equals(_TYPE_TEMPLATES)) {
					try {
						JournalTemplate journalTemplate =
							JournalTemplateLocalServiceUtil.getTemplate(
								webDavReq.getGroupId(), journalTypeId);

						return toResource(webDavReq, journalTemplate, false);
					}
					catch (NoSuchTemplateException nste) {
						return null;
					}
				}
			}

			return null;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public List getResources(WebDAVRequest webDavReq)
		throws WebDAVException {

		try {
			String[] pathArray = webDavReq.getPathArray();

			if (pathArray.length == 2) {
				return getFolders(webDavReq);
			}
			else if (pathArray.length == 3) {
				String type = pathArray[2];

				if (type.equals(_TYPE_STRUCTURES)) {
					return getStructures(webDavReq);
				}
				else if (type.equals(_TYPE_TEMPLATES)) {
					return getTemplates(webDavReq);
				}
			}

			return new ArrayList();
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	public int moveCollectionResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException {

		return HttpServletResponse.SC_FORBIDDEN;
	}

	public int moveSimpleResource(
			WebDAVRequest webDavReq, Resource resource, String destination,
			boolean overwrite)
		throws WebDAVException {

		return HttpServletResponse.SC_FORBIDDEN;
	}

	public int putResource(WebDAVRequest webDavReq) throws WebDAVException {
		try {
			Resource resource = getResource(webDavReq);

			if (resource == null) {
				return HttpServletResponse.SC_NOT_FOUND;
			}

			Object model = resource.getModel();

			if (model instanceof JournalStructure) {
				JournalStructure structure = (JournalStructure)model;

				HttpServletRequest req = webDavReq.getHttpServletRequest();

				String xsd = StringUtil.read(req.getInputStream());

				JournalStructureServiceUtil.updateStructure(
					structure.getGroupId(), structure.getStructureId(),
					structure.getName(), structure.getDescription(), xsd);

				return HttpServletResponse.SC_CREATED;
			}
			else if (model instanceof JournalTemplate) {
				JournalTemplate template = (JournalTemplate)model;

				HttpServletRequest req = webDavReq.getHttpServletRequest();

				String xsl = StringUtil.read(req.getInputStream());
				boolean formatXsl = true;
				File smallFile = null;

				JournalTemplateServiceUtil.updateTemplate(
					template.getGroupId(), template.getTemplateId(),
					template.getStructureId(), template.getName(),
					template.getDescription(), xsl, formatXsl,
					template.getLangType(), template.isCacheable(),
					template.isSmallImage(), template.getSmallImageURL(),
					smallFile);

				return HttpServletResponse.SC_CREATED;
			}
			else {
				return HttpServletResponse.SC_FORBIDDEN;
			}
		}
		catch (PortalException pe) {
			return HttpServletResponse.SC_FORBIDDEN;
		}
		catch (Exception e) {
			throw new WebDAVException(e);
		}
	}

	protected List getFolders(WebDAVRequest webDavReq) throws Exception {
		List folders = new ArrayList();

		//folders.add(toResource(webDavReq, _TYPE_ARTICLES, true));
		folders.add(toResource(webDavReq, _TYPE_STRUCTURES, true));
		folders.add(toResource(webDavReq, _TYPE_TEMPLATES, true));

		return folders;
	}

	protected List getStructures(WebDAVRequest webDavReq) throws Exception {
		List templates = new ArrayList();

		Iterator itr = JournalStructureLocalServiceUtil.getStructures(
			webDavReq.getGroupId()).iterator();

		while (itr.hasNext()) {
			JournalStructure structure = (JournalStructure)itr.next();

			Resource resource = toResource(webDavReq, structure, true);

			templates.add(resource);
		}

		return templates;
	}

	protected List getTemplates(WebDAVRequest webDavReq) throws Exception {
		List templates = new ArrayList();

		Iterator itr = JournalTemplateLocalServiceUtil.getTemplates(
			webDavReq.getGroupId()).iterator();

		while (itr.hasNext()) {
			JournalTemplate template = (JournalTemplate)itr.next();

			Resource resource = toResource(webDavReq, template, true);

			templates.add(resource);
		}

		return templates;
	}

	protected Resource toResource(
		WebDAVRequest webDavReq, String type, boolean appendPath) {

		String parentPath = getRootPath() + webDavReq.getPath();
		String name = StringPool.BLANK;

		if (appendPath) {
			name = type;
		}

		Resource resource = new BaseResourceImpl(parentPath, name, type);

		resource.setModel(type);

		return resource;
	}

	protected Resource toResource(
		WebDAVRequest webDavReq, JournalStructure structure,
		boolean appendPath) {

		String parentPath = getRootPath() + webDavReq.getPath();
		String name = StringPool.BLANK;

		if (appendPath) {
			name = structure.getStructureId();
		}

		return new JournalStructureResourceImpl(structure, parentPath, name);
	}

	protected Resource toResource(
		WebDAVRequest webDavReq, JournalTemplate template, boolean appendPath) {

		String parentPath = getRootPath() + webDavReq.getPath();
		String name = StringPool.BLANK;

		if (appendPath) {
			name = template.getTemplateId();
		}

		return new JournalTemplateResourceImpl(template, parentPath, name);
	}

	//private static final String _TYPE_ARTICLES = "Articles";

	private static final String _TYPE_STRUCTURES = "Structures";

	private static final String _TYPE_TEMPLATES = "Templates";

}