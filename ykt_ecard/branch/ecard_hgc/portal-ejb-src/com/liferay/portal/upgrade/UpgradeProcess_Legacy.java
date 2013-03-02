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

package com.liferay.portal.upgrade;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.portal.NoSuchGroupException;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.Group;
import com.liferay.portal.model.Image;
import com.liferay.portal.service.spring.CompanyLocalServiceUtil;
import com.liferay.portal.service.spring.GroupLocalServiceUtil;
import com.liferay.portal.service.spring.ImageServiceUtil;
import com.liferay.util.StringUtil;

import java.util.Iterator;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="UpgradeProcess_Legacy.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.5 $
 *
 */
public class UpgradeProcess_Legacy implements UpgradeProcess {

	public void upgrade(int buildNumber) throws UpgradeException {

		// Version 3.1.0 has build number 1712

		if (buildNumber > 1712) {
			return;
		}

		_log.info("Upgrading");

		try {

			// Counter names renamed from *com.liferay.ejb.* to
			// *com.liferay.model.* as of 1.9.0

			_updateCounter();

			// Default users depend on General Guest's group pages as of 2.1.0

			_updateDefaultUser();

			// Image names lengthened as of 2.2.0

			_updateImage();
		}
		catch (PortalException pe) {
			throw new UpgradeException(pe.getCause());
		}
		catch (SystemException se) {
			throw new UpgradeException(se.getCause());
		}
	}

	private void _updateCounter() throws SystemException {
		Iterator itr = CounterServiceUtil.getNames().iterator();

		while (itr.hasNext()) {
			String name = (String)itr.next();

			int pos = name.indexOf(".ejb.");

			if (name.startsWith("com.liferay.") && pos != -1) {
				CounterServiceUtil.rename(
					name,
					StringUtil.replace(name, ".ejb.", ".model."));
			}
		}
	}

	private void _updateDefaultUser() throws PortalException, SystemException {
		Iterator itr = CompanyLocalServiceUtil.getCompanies().iterator();

		while (itr.hasNext()) {
			Company company = (Company)itr.next();

			try {
				Group generalGroup = GroupLocalServiceUtil.getGroupByName(
					company.getCompanyId(), "General");

				GroupLocalServiceUtil.deleteGroup(generalGroup.getGroupId());
			}
			catch (NoSuchGroupException nsge) {
			}
		}
	}

	private void _updateImage() throws PortalException, SystemException {

		// Image Gallery

		Iterator itr = ImageServiceUtil.getImageById("%.ig.%").iterator();

		while (itr.hasNext()) {
			Image image = (Image)itr.next();

			String oldImageId = image.getImageId();

			String newImageId = StringUtil.replace(
				oldImageId, ".ig.", ".image_gallery.");

			if (newImageId.endsWith(".tn")) {
				newImageId = newImageId.substring(
					0, newImageId.length() - 2) + "small";
			}
			else {
				newImageId = newImageId + ".large";
			}

			ImageServiceUtil.updateImage(newImageId, image.getTextObj());
			ImageServiceUtil.deleteImage(oldImageId);
		}

		// Shopping Item

		itr = ImageServiceUtil.getImageById("%.s.%").iterator();

		while (itr.hasNext()) {
			Image image = (Image)itr.next();

			String oldImageId = image.getImageId();

			String newImageId = StringUtil.replace(
				oldImageId, ".s.", ".shopping.item.");

			ImageServiceUtil.updateImage(newImageId, image.getTextObj());
			ImageServiceUtil.deleteImage(oldImageId);
		}
	}

	private static final Log _log =
		LogFactory.getLog(UpgradeProcess_Legacy.class);

}