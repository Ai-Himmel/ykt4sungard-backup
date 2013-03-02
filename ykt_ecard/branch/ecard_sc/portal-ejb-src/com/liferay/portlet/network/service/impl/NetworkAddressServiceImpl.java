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

package com.liferay.portlet.network.service.impl;

import com.liferay.counter.service.spring.CounterServiceUtil;
import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.auth.PrincipalException;
import com.liferay.portal.im.AIMConnector;
import com.liferay.portal.im.ICQConnector;
import com.liferay.portal.im.MSNConnector;
import com.liferay.portal.im.YMConnector;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.service.impl.PrincipalBean;
import com.liferay.portal.service.spring.CompanyServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.ContentUtil;
import com.liferay.portlet.network.AddressNameException;
import com.liferay.portlet.network.AddressURLException;
import com.liferay.portlet.network.model.NetworkAddress;
import com.liferay.portlet.network.service.persistence.NetworkAddressFinder;
import com.liferay.portlet.network.service.persistence.NetworkAddressUtil;
import com.liferay.portlet.network.service.spring.NetworkAddressLocalServiceUtil;
import com.liferay.portlet.network.service.spring.NetworkAddressService;
import com.liferay.util.GetterUtil;
import com.liferay.util.Http;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.mail.MailMessage;

import java.io.FileNotFoundException;

import java.net.MalformedURLException;
import java.net.URL;
import java.net.UnknownHostException;

import java.text.DateFormat;

import java.util.Date;
import java.util.Iterator;
import java.util.List;

import javax.mail.internet.InternetAddress;

import javax.servlet.http.HttpServletResponse;

/**
 * <a href="NetworkAddressServiceImpl.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @version $Revision: 1.4 $
 *
 */
public class NetworkAddressServiceImpl
	extends PrincipalBean implements NetworkAddressService {

	// Business methods

	public NetworkAddress addAddress(
			String name, String url, String comments, String notifyBy,
			long interval, boolean active)
		throws PortalException, SystemException {

		_validate(name, url);

		String addressId = Long.toString(CounterServiceUtil.increment(
			NetworkAddress.class.getName()));

		NetworkAddress address = NetworkAddressUtil.create(addressId);

		Date now = new Date();

		address.setUserId(getUserId());
		address.setCreateDate(now);
		address.setModifiedDate(now);
		address.setName(name);
		address.setUrl(url);
		address.setComments(comments);
		address.setNotifyBy(notifyBy);
		address.setInterval(interval);
		address.setActive(active);

		NetworkAddressUtil.update(address);

		checkAddress(address);

		return address;
	}

	public void checkAddress(NetworkAddress address) throws SystemException {
		if (address.isActive()) {
			Date now = new Date();

			address.setModifiedDate(now);

			String oldContent = address.getContent();
			String newContent = null;

			int oldStatus = address.getStatus();
			int newStatus = HttpServletResponse.SC_OK; // 200

			try {
				newContent = Http.URLtoString(address.getUrl());
				address.setContent(newContent);
			}
			catch (FileNotFoundException fnfe) {
				newStatus = HttpServletResponse.SC_NOT_FOUND; // 404
			}
			catch (UnknownHostException uhe) {
				newStatus = HttpServletResponse.SC_BAD_REQUEST; // 400
			}
			catch (Exception e) {
				newStatus = HttpServletResponse.SC_REQUEST_TIMEOUT; // 408
			}

			if (newContent != null && !newContent.equals(oldContent)) {
				address.setLastUpdated(now);

				_notifyUser(address, true);
			}

			if (newStatus != oldStatus) {
				address.setStatus(newStatus);

				if (oldStatus != 0) {
					_notifyUser(address, false);
				}
			}

			NetworkAddressUtil.update(address);
		}
	}

	public void checkAddresses(long interval) throws SystemException {
		Iterator itr = getAddresses(interval).iterator();

		while (itr.hasNext()) {
			NetworkAddress address = (NetworkAddress)itr.next();

			checkAddress(address);
		}
	}

	public void deleteAddress(String addressId)
		throws PortalException, SystemException {

		NetworkAddress address = NetworkAddressUtil.findByPrimaryKey(addressId);

		if (!address.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		NetworkAddressLocalServiceUtil.deleteAddress(addressId);
	}

	public NetworkAddress getAddress(String addressId)
		throws PortalException, SystemException {

		NetworkAddress address = NetworkAddressUtil.findByPrimaryKey(addressId);

		if (!address.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		return address;
	}

	public List getAddresses() throws PortalException, SystemException {
		return NetworkAddressUtil.findByUserId(getUserId());
	}

	public List getAddresses(long interval) throws SystemException {
		return getAddresses(interval, true);
	}

	public List getAddresses(long interval, boolean active)
		throws SystemException {

		return NetworkAddressFinder.findByI_A(interval, active);
	}

	public int getAddressesSize()
		throws PortalException, SystemException {

		return NetworkAddressUtil.countByUserId(getUserId());
	}

	public NetworkAddress updateAddress(
			String addressId, String name, String url, String comments,
			String notifyBy, long interval, boolean active)
		throws PortalException, SystemException {

		_validate(name, url);

		NetworkAddress address = NetworkAddressUtil.findByPrimaryKey(addressId);

		if (!address.getUserId().equals(getUserId())) {
			throw new PrincipalException();
		}

		address.setModifiedDate(new Date());
		address.setName(name);
		address.setUrl(url);
		address.setComments(comments);
		address.setNotifyBy(notifyBy);
		address.setInterval(interval);
		address.setActive(active);

		NetworkAddressUtil.update(address);

		checkAddress(address);

		return address;
	}

	// Private methods

	private void _notifyUser(NetworkAddress address, boolean lastUpdated) {
		String notifyBy = GetterUtil.getString(address.getNotifyBy());

		if (notifyBy.equals(NetworkAddress.NOTIFY_BY_NONE)) {
			return;
		}

		try {
			User user = UserLocalServiceUtil.getUserById(address.getUserId());

			Company company =
				CompanyServiceUtil.getCompany(user.getCompanyId());

			String emailSubject = company.getName() + " URL Tracker";

			DateFormat dateFormat = DateFormat.getDateTimeInstance(
				DateFormat.LONG, DateFormat.LONG, user.getLocale());
			dateFormat.setTimeZone(user.getTimeZone());

			String emailBodyFileSuffix = Integer.toString(address.getStatus());
			if (lastUpdated) {
				emailBodyFileSuffix = "last_updated";
			}

			String emailBody = ContentUtil.get(
				"content/en_US/network_address_" + emailBodyFileSuffix +
					".tmpl");
			emailBody = StringUtil.replace(
				emailBody,
				new String[] {"[$USER_NAME$]",
							  "[$ADMIN_NAME$]", "[$ADMIN_EMAIL_ADDRESS$]",
							  "[$COMPANY_NAME$]",
							  "[$ADDRESS_NAME$]", "[$ADDRESS_URL$]",
							  "[$ADDRESS_MODIFIED_DATE$]"},
				new String[] {user.getFullName(),
							  company.getAdminName(), company.getEmailAddress(),
							  company.getShortName(),
							  address.getName(), address.getUrl(),
							  dateFormat.format(address.getModifiedDate())});

			InternetAddress emailTo = null;

			if (notifyBy.equals(NetworkAddress.NOTIFY_BY_EMAIL)) {
				emailTo = new InternetAddress(
					user.getEmailAddress(), user.getFullName());
			}
			else if (notifyBy.equals(NetworkAddress.NOTIFY_BY_SMS)) {
				emailTo = new InternetAddress(
					user.getSmsId(), user.getFullName());
			}

			if (emailTo != null) {
				MailServiceUtil.sendEmail(new MailMessage(
					new InternetAddress(
						company.getEmailAddress(), company.getAdminName()),
					emailTo, emailSubject, emailBody));
			}

			if (notifyBy.equals(NetworkAddress.NOTIFY_BY_AIM) &&
				Validator.isNotNull(user.getAimId())) {

				AIMConnector.send(user.getAimId(), emailBody);
			}
			else if (notifyBy.equals(NetworkAddress.NOTIFY_BY_ICQ) &&
					 Validator.isNotNull(user.getIcqId())) {

				ICQConnector.send(user.getIcqId(), emailBody);
			}
			else if (notifyBy.equals(NetworkAddress.NOTIFY_BY_MSN) &&
					 Validator.isNotNull(user.getMsnId())) {

				MSNConnector.send(user.getMsnId(), emailBody);
			}
			else if (notifyBy.equals(NetworkAddress.NOTIFY_BY_YM) &&
					 Validator.isNotNull(user.getYmId())) {

				YMConnector.send(user.getYmId(), emailBody);
			}
		}
		catch (Exception e) {
			e.printStackTrace();
		}
	}

	private void _validate(String name, String url) throws PortalException {
		if (Validator.isNull(name)) {
			throw new AddressNameException();
		}

		if (Validator.isNull(url)) {
			throw new AddressURLException();
		}
		else {
			try {
				new URL(url);
			}
			catch (MalformedURLException murle) {
				throw new AddressURLException();
			}
		}
	}

}