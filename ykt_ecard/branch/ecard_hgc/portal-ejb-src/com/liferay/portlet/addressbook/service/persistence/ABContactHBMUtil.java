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

package com.liferay.portlet.addressbook.service.persistence;

/**
 * <a href="ABContactHBMUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.183 $
 *
 */
public class ABContactHBMUtil {
	public static com.liferay.portlet.addressbook.model.ABContact model(
		ABContactHBM abContactHBM) {
		com.liferay.portlet.addressbook.model.ABContact abContact = ABContactPool.get(abContactHBM.getPrimaryKey());

		if (abContact == null) {
			abContact = new com.liferay.portlet.addressbook.model.ABContact(abContactHBM.getContactId(),
					abContactHBM.getUserId(), abContactHBM.getFirstName(),
					abContactHBM.getMiddleName(), abContactHBM.getLastName(),
					abContactHBM.getNickName(), abContactHBM.getEmailAddress(),
					abContactHBM.getHomeStreet(), abContactHBM.getHomeCity(),
					abContactHBM.getHomeState(), abContactHBM.getHomeZip(),
					abContactHBM.getHomeCountry(), abContactHBM.getHomePhone(),
					abContactHBM.getHomeFax(), abContactHBM.getHomeCell(),
					abContactHBM.getHomePager(),
					abContactHBM.getHomeTollFree(),
					abContactHBM.getHomeEmailAddress(),
					abContactHBM.getBusinessCompany(),
					abContactHBM.getBusinessStreet(),
					abContactHBM.getBusinessCity(),
					abContactHBM.getBusinessState(),
					abContactHBM.getBusinessZip(),
					abContactHBM.getBusinessCountry(),
					abContactHBM.getBusinessPhone(),
					abContactHBM.getBusinessFax(),
					abContactHBM.getBusinessCell(),
					abContactHBM.getBusinessPager(),
					abContactHBM.getBusinessTollFree(),
					abContactHBM.getBusinessEmailAddress(),
					abContactHBM.getEmployeeNumber(),
					abContactHBM.getJobTitle(), abContactHBM.getJobClass(),
					abContactHBM.getHoursOfOperation(),
					abContactHBM.getBirthday(), abContactHBM.getTimeZoneId(),
					abContactHBM.getInstantMessenger(),
					abContactHBM.getWebsite(), abContactHBM.getComments());
			ABContactPool.put(abContact.getPrimaryKey(), abContact);
		}

		return abContact;
	}
}