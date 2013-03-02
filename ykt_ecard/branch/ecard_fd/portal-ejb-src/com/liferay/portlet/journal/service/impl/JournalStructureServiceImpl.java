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

package com.liferay.portlet.journal.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portlet.journal.DuplicateStructureIdException;
import com.liferay.portlet.journal.NoSuchStructureException;
import com.liferay.portlet.journal.RequiredStructureException;
import com.liferay.portlet.journal.StructureDescriptionException;
import com.liferay.portlet.journal.StructureIdException;
import com.liferay.portlet.journal.StructureNameException;
import com.liferay.portlet.journal.StructureXsdException;
import com.liferay.portlet.journal.model.JournalStructure;
import com.liferay.portlet.journal.service.persistence.JournalArticleUtil;
import com.liferay.portlet.journal.service.persistence.JournalStructureUtil;
import com.liferay.portlet.journal.service.persistence.JournalTemplateUtil;
import com.liferay.portlet.journal.service.spring.JournalArticleServiceUtil;
import com.liferay.portlet.journal.service.spring.JournalStructureService;
import com.liferay.portlet.journal.util.JournalUtil;
import com.liferay.util.StringPool;
import com.liferay.util.Validator;

import java.io.IOException;
import java.io.StringReader;

import java.util.Date;
import java.util.HashSet;
import java.util.Iterator;
import java.util.List;
import java.util.Set;

import org.dom4j.Document;
import org.dom4j.DocumentException;
import org.dom4j.Element;
import org.dom4j.io.SAXReader;

/**
 * <a href="JournalStructureServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.2 $
 *
 */
public class JournalStructureServiceImpl
	extends PrincipalBean implements JournalStructureService {

	// Business methods

	public JournalStructure addStructure(
			String structureId, boolean autoStructureId, String portletId,
			String groupId, String name, String description, String xsd)
		throws PortalException, SystemException {

		structureId = structureId.trim().toUpperCase();

		try {
			xsd = JournalUtil.formatXML(xsd);
		}
		catch (DocumentException de) {
			throw new StructureXsdException();
		}
		catch (IOException ioe) {
			throw new StructureXsdException();
		}

		_validate(structureId, autoStructureId, name, description, xsd);

		User user = getUser();

		if (autoStructureId) {
			structureId = Long.toString(CounterServiceUtil.increment(
				JournalStructure.class.getName()));
		}

		JournalStructure structure = JournalStructureUtil.create(structureId);

		Date now = new Date();

		structure.setPortletId(portletId);
		structure.setGroupId(groupId);
		structure.setCompanyId(user.getCompanyId());
		structure.setUserId(user.getUserId());
		structure.setUserName(user.getFullName());
		structure.setCreateDate(now);
		structure.setModifiedDate(now);
		structure.setName(name);
		structure.setDescription(description);
		structure.setXsd(xsd);

		JournalStructureUtil.update(structure);

		return structure;
	}

	public void deleteStructure(String structureId)
		throws PortalException, SystemException {

		structureId = structureId.trim().toUpperCase();

		if (!JournalArticleServiceUtil.hasAdmin()) {
			throw new PrincipalException();
		}

		if (JournalArticleUtil.countByStructureId(structureId) > 0) {
			throw new RequiredStructureException();
		}

		if (JournalTemplateUtil.countByStructureId(structureId) > 0) {
			throw new RequiredStructureException();
		}

		JournalStructureUtil.remove(structureId);
	}

	public JournalStructure getStructure(String structureId)
		throws PortalException, SystemException {

		structureId = structureId.trim().toUpperCase();

		return JournalStructureUtil.findByPrimaryKey(structureId);
	}

	public List getStructures(
			String portletId, String groupId, String companyId, int begin,
			int end)
		throws SystemException {

		return JournalStructureUtil.findByP_G_C(
			portletId, groupId, companyId, begin, end);
	}

	public int getStructuresSize(
			String portletId, String groupId, String companyId)
		throws SystemException {

		return JournalStructureUtil.countByP_G_C(portletId, groupId, companyId);
	}

	public JournalStructure updateStructure(
			String structureId, String name, String description, String xsd)
		throws PortalException, SystemException {

		structureId = structureId.trim().toUpperCase();

		try {
			xsd = JournalUtil.formatXML(xsd);
		}
		catch (DocumentException de) {
			throw new StructureXsdException();
		}
		catch (IOException ioe) {
			throw new StructureXsdException();
		}

		_validate(name, description, xsd);

		User user = getUser();

		JournalStructure structure =
			JournalStructureUtil.findByPrimaryKey(structureId);

		structure.setModifiedDate(new Date());
		structure.setName(name);
		structure.setDescription(description);
		structure.setXsd(xsd);

		JournalStructureUtil.update(structure);

		return structure;
	}

	// Private methods

	private void _validate(
			String structureId, boolean autoStructureId, String name,
			String description, String xsd)
		throws PortalException, SystemException {

		if (!autoStructureId) {
			if ((Validator.isNull(structureId)) ||
				(Validator.isNumber(structureId)) ||
				(structureId.indexOf(StringPool.SPACE) != -1)) {

				throw new StructureIdException();
			}

			try {
				JournalStructureUtil.findByPrimaryKey(structureId);

				throw new DuplicateStructureIdException();
			}
			catch (NoSuchStructureException nste) {
			}
		}

		_validate(name, description, xsd);
	}

	private void _validate(String name, String description, String xsd)
		throws PortalException {

		if (Validator.isNull(name)) {
			throw new StructureNameException();
		}
		else if (Validator.isNull(description)) {
			throw new StructureDescriptionException();
		}

		if (Validator.isNull(xsd)) {
			throw new StructureXsdException();
		}
		else {
			try {
				SAXReader reader = new SAXReader();

				Document doc = reader.read(new StringReader(xsd));

				Element root = doc.getRootElement();

				List children = root.elements();

				if (children.size() == 0) {
					throw new StructureXsdException();
				}

				Set elNames = new HashSet();

				_validate(children, elNames);
			}
			catch (Exception e) {
				throw new StructureXsdException();
			}
		}
	}

	private void _validate(List children, Set elNames) throws PortalException {
		Iterator itr = children.iterator();

		while (itr.hasNext()) {
			Element el = (Element)itr.next();

			String elName = el.attributeValue("name", StringPool.BLANK);
			String elType = el.attributeValue("type", StringPool.BLANK);

			if (Validator.isNull(elName) ||
				elName.startsWith(JournalStructure.RESERVED)) {

				throw new StructureXsdException();
			}
			else {
				char[] c = elName.toCharArray();

				for (int i = 0; i < c.length; i++) {
					if ((!Validator.isChar(c[i])) &&
						(!Validator.isDigit(c[i])) &&
						(c[i] != '_') && (c[i] != '-')) {

						throw new StructureXsdException();
					}
				}

				String elNameLowerCase = elName.toLowerCase();

				if (elNames.contains(elNameLowerCase)) {
					throw new StructureXsdException();
				}
				else {
					elNames.add(elNameLowerCase);
				}
			}

			if (Validator.isNull(elType)) {
				throw new StructureXsdException();
			}

			_validate(el.elements(), elNames);
		}
	}

}