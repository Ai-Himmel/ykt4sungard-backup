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

package com.liferay.portlet.mail.util;

import com.liferay.mail.service.spring.MailServiceUtil;
import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.service.spring.PortletPreferencesServiceUtil;
import com.liferay.portal.service.spring.UserLocalServiceUtil;
import com.liferay.portal.util.Constants;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PortletKeys;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portlet.ActionRequestImpl;
import com.liferay.portlet.RenderRequestImpl;
import com.liferay.portlet.mail.MailAccountsException;
import com.liferay.portlet.mail.model.Content;
import com.liferay.portlet.mail.util.multiaccount.MailAccount;
import com.liferay.portlet.mail.util.multiaccount.MailAccounts;
import com.liferay.portlet.mail.util.multiaccount.MailCache;
import com.liferay.util.GetterUtil;
import com.liferay.util.Html;
import com.liferay.util.JNDIUtil;
import com.liferay.util.SimpleCachePool;
import com.liferay.util.StringPool;
import com.liferay.util.StringUtil;
import com.liferay.util.Validator;
import com.liferay.util.lang.FastStringBuffer;
import com.liferay.util.mail.MailEngine;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;

import java.util.Arrays;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.mail.AuthenticationFailedException;
import javax.mail.BodyPart;
import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.NoSuchProviderException;
import javax.mail.Part;
import javax.mail.Session;
import javax.mail.Store;
import javax.mail.internet.AddressException;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;

import javax.naming.InitialContext;
import javax.naming.NamingException;

import javax.portlet.ActionRequest;
import javax.portlet.PortletPreferences;
import javax.portlet.RenderRequest;

import javax.servlet.http.HttpServletRequest;

import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * <a href="MailUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author  Brian Wing Shun Chan
 * @author  Mirco Tamburini
 * @author  Jorge Ferrer
 * @author  Michael Young
 * @author  Javier Bermejo
 * @version $Revision: 1.66 $
 *
 */
public class MailUtil {

	public static final String SCP_FOLDER_POOL_ID = "portal-ejb.mail_fp.";

	public static final String SCP_STORE_ID = "portal-ejb.mail_store.";

	public static final int ATTACHMENTS_MAX_SIZE = GetterUtil.getInteger(
		PropsUtil.get(PropsUtil.MAIL_ATTACHMENTS_MAX_SIZE));

	public static final double SIZE_DIFFERENTIAL = 0.7483;

	public static final String MAIL_BOX_STYLE =
		PropsUtil.get(PropsUtil.MAIL_BOX_STYLE);

	public static final String MAIL_INBOX_NAME =
		PropsUtil.get(PropsUtil.MAIL_INBOX_NAME);

	public static final String[] DEFAULT_FOLDERS = {
		MAIL_INBOX_NAME, "junk-mail", "sent-mail", "drafts", "trash"
	};

	public static final String[] MOVE_TO_FOLDERS = {
		MAIL_INBOX_NAME, "junk-mail", "sent-mail", "trash"
	};

	public static final String[] LINK_REGEXP = {
		"([^]_a-z0-9-=\"'/])" +
			"((https?|ftp|gopher|news|telnet)://|www\\.)" +
			"([^ \\r\\n\\(\\)\\*\\^\\$!`\"'\\|\\[\\]\\{\\};<>\\.]*)" +
			"((\\.[^ \\r\\n\\(\\)\\*\\^\\$!`\"'\\|\\[\\]\\{\\};<>\\.]+)*)",
		"<a href=\"www\\."
	};

	public static String[] LINK_REPLACEMENT = {
		"$1<a href=\"$2$4$5\" target=\"_blank\">$2$4$5</a>",
		"<a href=\"http://www."
	};

	public static Pattern[] LINK_PATTERN = {
		Pattern.compile(LINK_REGEXP[0]),
		Pattern.compile(LINK_REGEXP[1])
	};

	public static String addQuote(String text, boolean htmlFormat) {
		if (text == null) {
			return StringPool.BLANK;
		}

		if (htmlFormat) {
			FastStringBuffer sb = new FastStringBuffer();

			sb.append("<blockquote style=\"border-left: #C4C4C4 2px solid; ");
			sb.append("margin-left: 5px; padding-left: 5px;\">");
			sb.append("<div>");
			sb.append(text);
			sb.append("</div>");

			return sb.toString();
		}
		else {
			FastStringBuffer sb = new FastStringBuffer(text.length() + 10);

			sb.append(">");

			int x = 0;
			int y = 0;

			while (true) {
				y = text.indexOf(10, x);

				if (y != -1) {
					sb.append(text.substring(x, y + 1));
					sb.append(">");

					x = y + 1;
				}
				else {
					sb.append(text.substring(x, text.length()));

					break;
				}
			}

			return sb.toString();
		}
	}

	public static void clearCache(String userId) {
		if (userId != null) {
			MailCache.clearCache(userId);
		}
	}

	public static Store createStore(HttpServletRequest req, MailAccount account)
		throws MessagingException, NamingException, NoSuchProviderException {

		User user = _getMailUser(req);

		MailCache.removeStore(user.getUserId(), account.getName());

		String login = getLogin(account.getUserId());
		String password = account.getPassword();

		Session session = getSession();

		Store store = session.getStore("imap");
		store.addConnectionListener(new ConnectionListener());

		String imapHost = getIMAPHost();

		try {
			_log.debug("Connecting to IMAP host " + imapHost);
			_log.debug("User login is " + login);
			//_log.debug("User password is " + password);

			store.connect(imapHost, login, password);
		}
		catch (AuthenticationFailedException afe) {
			try {
				MailServiceUtil.updatePassword(user.getUserId(), password);
			}
			catch (Exception e) {
				throw new MessagingException(e.getMessage(), e);
			}

			store.connect(imapHost, login, password);
		}

		MailCache.putStore(user.getUserId(), account.getName(), store);

		account.setStore(store);

		return store;
	}

	public static String formatPlainText(String text) {
		if (text == null) {
			return null;
		}

		text = StringUtil.wrap(text);
		text = Html.formatTo(text);

		Matcher matcher = LINK_PATTERN[0].matcher(text);
		text = matcher.replaceAll(LINK_REPLACEMENT[0]);

		matcher = LINK_PATTERN[1].matcher(text);
		text = matcher.replaceAll(LINK_REPLACEMENT[1]);

		return text;
	}

	public static Content getContent(Part p) {
		try {
			if (p.isMimeType(Constants.TEXT_PLAIN)) {
				String text = (String)p.getContent();

				if (Validator.isHTML(text)) {
					return new Content(text, Constants.TEXT_HTML);
				}
				else {
					return new Content(text, Constants.TEXT_PLAIN);
				}
			}
			else if (p.isMimeType(Constants.TEXT_HTML)) {
				return new Content(
					(String)p.getContent(), Constants.TEXT_HTML);
			}
			else if (p.isMimeType("multipart/*")) {
				Multipart mp = (Multipart)p.getContent();

				/*for (int i = 0; i < mp.getCount(); i++) {
					Part curPart = mp.getBodyPart(i);

					if (curPart.isMimeType(Constants.TEXT_HTML)) {
						if (curPart.getFileName() == null) {
							return getContent(curPart);
						}
					}
				}*/

				return getContent(mp.getBodyPart(0));
			}
			else if (p.isMimeType("message/rfc822")) {
				return getContent((Part)p.getContent());
			}
		}
		catch (Exception e) {
		}

		try {
			BufferedReader br = new BufferedReader(
					new InputStreamReader(p.getInputStream(), "US-ASCII"));

			FastStringBuffer sb = new FastStringBuffer();

			String s = null;

			while ((s = br.readLine()) != null) {
				sb.append(s);
				sb.append("\n");
			}

			return new Content(sb.toString(), Constants.TEXT_PLAIN);
		}
		catch (Exception e) {
		}

		return null;
	}

	public static Folder[] getDefaultFolders(HttpServletRequest req)
		throws MessagingException, NamingException {

		Folder[] folders = new Folder[DEFAULT_FOLDERS.length];

		for (int i = 0; i < DEFAULT_FOLDERS.length; i++) {
			folders[i] = getFolder(req, DEFAULT_FOLDERS[i]);
		}

		return folders;
	}

	public static Folder getFolder(HttpServletRequest req, String folderName)
		throws MessagingException, NamingException {

		Folder folder = null;

		try {
			folder = _getFolder(req, folderName);
		}
		catch (MessagingException me) {
			_log.error(me.getMessage());

			clearCache(PortalUtil.getUserId(req));

			folder = _getFolder(req, folderName);
		}

		return folder;
	}

	public static Folder getFolder(ActionRequest req, String folderName)
		throws MessagingException, NamingException {

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		return getFolder(reqImpl.getHttpServletRequest(), folderName);
	}

	public static Folder getFolder(RenderRequest req, String folderName)
		throws MessagingException, NamingException {

		RenderRequestImpl reqImpl = (RenderRequestImpl)req;

		return getFolder(reqImpl.getHttpServletRequest(), folderName);
	}

	public static FolderPool getFolderPool(HttpServletRequest req) {
		String id = MailCache.getFolderPoolId(PortalUtil.getUserId(req));

		FolderPool folderPool = (FolderPool)SimpleCachePool.get(id);

		if (folderPool == null) {
			folderPool = new FolderPool();
			SimpleCachePool.put(id, folderPool);
		}

		return folderPool;
	}

	public static FolderPool getFolderPool(ActionRequest req) {
		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		return getFolderPool(reqImpl.getHttpServletRequest());
	}

	public static String getIMAPHost() throws NamingException {
		return getSession().getProperty("mail.imap.host");
	}

	public static String getLogin(String userId) {
		String login = userId;
		if (GetterUtil.getBoolean(
				PropsUtil.get(PropsUtil.MAIL_USERNAME_REPLACE))) {
			login = StringUtil.replace(login, ".", "_");
		}

		return login;
	}

	public static Folder[] getMoveToFolders(HttpServletRequest req)
		throws MessagingException, NamingException {

		Folder[] folders = new Folder[MOVE_TO_FOLDERS.length];

		for (int i = 0; i < MOVE_TO_FOLDERS.length; i++) {
			folders[i] = getFolder(req, MOVE_TO_FOLDERS[i]);
		}

		return folders;
	}

	public static Message getNewMessage()
		throws MessagingException, NamingException {

		Message msg = new MimeMessage(getSession());

		msg.setSubject("");

		BodyPart bodyPart = new MimeBodyPart();
		bodyPart.setText("");

		Multipart multipart = new MimeMultipart();
		multipart.addBodyPart(bodyPart);

		msg.setContent(multipart);

		return msg;
	}

	public static String getPOP3Host() throws NamingException {
		return getSession().getProperty("mail.pop3.host");
	}

	public static PortletPreferences getPreferences(HttpServletRequest req)
		throws PortalException, SystemException {

		PortletPreferences prefs = PortletPreferencesServiceUtil.getPreferences(
			PortalUtil.getCompanyId(req),
			PortalUtil.getPortletPreferencesPK(req, PortletKeys.MAIL));

		return prefs;
	}

	public static PortletPreferences getPreferences(ActionRequest req)
		throws PortalException, SystemException {

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		return getPreferences(reqImpl.getHttpServletRequest());
	}

	public static Session getSession() throws NamingException {
		Session session = (Session)JNDIUtil.lookup(
			new InitialContext(), MailEngine.MAIL_SESSION);

		//session.getProperties().list(System.out);

		return session;
	}

	public static int getSize(Message message) throws MessagingException {
		return (int)(message.getSize() * SIZE_DIFFERENTIAL);
	}

	public static int getSize(Message[] messages) throws MessagingException {
		int size = 0;

		for (int i = 0; i < messages.length; i++) {
			size = size + getSize(messages[i]);
		}

		return size;
	}

	public static String getSMTPHost() throws NamingException {
		return getSession().getProperty("mail.smtp.host");
	}

	public static Store getStore(HttpServletRequest req)
		throws MessagingException, NamingException, NoSuchProviderException {

		try {
			MailAccount currentAccount = MailAccounts.getCurrentAccount(req);

			Store store = MailCache.getStore(
				PortalUtil.getUserId(req), currentAccount.getName());

			if (store == null) {
				store = createStore(req, currentAccount);

				_log.debug("New store created " + store);

			}

			currentAccount.setStore(store);

			return store;
		}
		catch (MailAccountsException mae) {
			throw new NoSuchProviderException(mae.getMessage());
		}
	}

	public static boolean hasAttachment(Message msg) {
		try {
			String contentType =
				GetterUtil.getString(msg.getContentType()).toLowerCase();

			int pos = contentType.indexOf("_nextpart");
			if (pos >= 0) {
				return true;
			}

			pos = contentType.indexOf("multipart/mixed");
			if (pos != -1) {
				Multipart multipart = (Multipart)msg.getContent();

				if (multipart.getCount() > 1) {
					return true;
				}
			}
		}
		catch (IOException ioe) {
			_log.error(ioe);
		}
		catch (MessagingException me) {
			_log.error(me);
		}

		return false;
	}

	public static boolean isDefaultFolder(String folderName) {
		if (folderName == null) {
			return false;
		}

		for (int i = 0; i < DEFAULT_FOLDERS.length; i++) {
			if (DEFAULT_FOLDERS[i].equals(folderName)) {
				return true;
			}
		}

		return false;
	}

	public static boolean isValidFolderName(String folderName) {
		if (Validator.isNull(folderName)) {
			return false;
		}

		if (folderName.indexOf(StringPool.PERIOD) != -1) {
			return false;
		}

		if ((folderName.equalsIgnoreCase(MAIL_INBOX_NAME)) ||
			(folderName.equalsIgnoreCase(
				MailUtil.MAIL_BOX_STYLE + MAIL_INBOX_NAME)) ||
			(folderName.equalsIgnoreCase(
				MailUtil.MAIL_BOX_STYLE + "junk-mail")) ||
			(folderName.equalsIgnoreCase(
				MailUtil.MAIL_BOX_STYLE + "sent mail")) ||
			(folderName.equalsIgnoreCase(MailUtil.MAIL_BOX_STYLE + "drafts")) ||
			(folderName.equalsIgnoreCase(MailUtil.MAIL_BOX_STYLE + "trash"))) {

			return false;
		}

		char[] c = folderName.toCharArray();

		for (int i = 0; i < c.length; i++) {
			if ((!Validator.isChar(c[i])) &&
				(!Validator.isDigit(c[i])) &&
				(!Character.isWhitespace(c[i]))) {

				return false;
			}
		}

		return true;
	}

	public static InternetAddress[] parseAddresses(
			HttpServletRequest req, String addresses)
		throws AddressException {

		InternetAddress[] addressesArray = InternetAddress.parse(addresses);

		Company company = null;

		try {
			company = PortalUtil.getCompany(req);
		}
		catch (Exception e) {
			return addressesArray;
		}

		for (int i = 0; i < addressesArray.length; i++) {
			InternetAddress address = addressesArray[i];

			if (address.getPersonal() == null &&
				!Validator.isEmailAddress(address.getAddress())) {

				try {
					User user = UserLocalServiceUtil.getUserByEmailAddress(
						company.getCompanyId(),
						address.getAddress().trim() + "@" + company.getMx());

					if (user != null) {
						addressesArray[i] = new InternetAddress(
							user.getEmailAddress(), user.getFullName());
					}
				}
				catch (Exception e) {
				}
			}
		}

		return addressesArray;
	}

	public static InternetAddress[] parseAddresses(
			ActionRequest req, String addresses)
		throws AddressException {

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		return parseAddresses(reqImpl.getHttpServletRequest(), addresses);
	}

	public static void renameFolder(
			HttpServletRequest req, String folderName, String newFolderName)
		throws MessagingException, NamingException {

		if ((Validator.isNotNull(folderName)) &&
			(Validator.isNotNull(newFolderName))) {

			if (!folderName.equals(MAIL_INBOX_NAME)) {
				if (!folderName.startsWith(MailUtil.MAIL_BOX_STYLE)) {
					folderName = MailUtil.MAIL_BOX_STYLE + folderName;
				}
			}

			if (!newFolderName.startsWith(MailUtil.MAIL_BOX_STYLE)) {
				newFolderName = MailUtil.MAIL_BOX_STYLE + newFolderName;
			}

			Store store = getStore(req);
			FolderPool folderPool = getFolderPool(req);
			Folder folder = folderPool.get(
				MailCache.getFolderCacheId(folderName, store));

			if (folder == null) {
				folder = store.getFolder(folderName);
			}
			else {
				folderPool.remove(folderName);
			}

			if (folder.exists()) {
				if ((!folderName.equals(MAIL_INBOX_NAME)) &&
					(!folderName.equals(
						MailUtil.MAIL_BOX_STYLE + "sent-mail")) &&
					(!folderName.equals(MailUtil.MAIL_BOX_STYLE + "drafts")) &&
					(!folderName.equals(MailUtil.MAIL_BOX_STYLE + "trash"))) {

					if (!folder.isOpen()) {
						folder.open(Folder.READ_WRITE);
					}

					Folder newFolder = store.getFolder(newFolderName);

					if (newFolder.exists()) {
						newFolder.delete(false);
					}

					newFolder.create(Folder.HOLDS_MESSAGES);
					newFolder.open(Folder.READ_WRITE);

					Message[] messages = folder.getMessages();

					// Try and rename the folder for better performance

					newFolder.appendMessages(messages);

					folder.setFlags(
						messages, new Flags(Flags.Flag.DELETED), true);
					folder.expunge();

					folder.close(false);
					folder.delete(false);
				}
			}
		}
	}

	public static void renameFolder(
			ActionRequest req, String folderName, String newFolderName)
		throws MessagingException, NamingException {

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		renameFolder(
			reqImpl.getHttpServletRequest(), folderName, newFolderName);
	}

	public static void removeFolder(HttpServletRequest req, String folderName)
		throws MessagingException, NamingException {

		if (Validator.isNotNull(folderName)) {
			if (!folderName.equals(MAIL_INBOX_NAME)) {
				if (!folderName.startsWith(MailUtil.MAIL_BOX_STYLE)) {
					folderName = MailUtil.MAIL_BOX_STYLE + folderName;
				}
			}

			Store store = getStore(req);
			FolderPool folderPool = getFolderPool(req);
			Folder folder = folderPool.get(
				MailCache.getFolderCacheId(folderName, store));

			if (folder == null) {
				folder = store.getFolder(folderName);
			}
			else {
				folderPool.remove(folderName);
			}

			if (folder.exists()) {
				if ((!folderName.equals(MAIL_INBOX_NAME)) &&
					(!folderName.equals(
						MailUtil.MAIL_BOX_STYLE + "sent-mail")) &&
					(!folderName.equals(MailUtil.MAIL_BOX_STYLE + "drafts")) &&
					(!folderName.equals(MailUtil.MAIL_BOX_STYLE + "trash"))) {

					if (folder.isOpen()) {
						folder.close(false);
					}

					folder.delete(false);
				}
			}
		}
	}

	public static void removeFolder(ActionRequest req, String folderName)
		throws MessagingException, NamingException {

		ActionRequestImpl reqImpl = (ActionRequestImpl)req;

		removeFolder(reqImpl.getHttpServletRequest(), folderName);
	}

	public static void removeFolderPool(HttpServletRequest req) {
		getFolderPool(req).clear();
	}

	public static void sort(
		String folderName, Message[] messages, PortletPreferences prefs) {

		String orderByCol = prefs.getValue("order-by-col", StringPool.BLANK);
		String orderByType = prefs.getValue("order-by-type", StringPool.BLANK);

		if ((folderName != null) &&
			(folderName.equals("drafts") ||
				folderName.equals("sent-mail"))) {

			if (orderByCol.equals("f")) {
				if (orderByType.equals("asc")) {
					Arrays.sort(messages, new ToComparator(true));
				}
				else {
					Arrays.sort(messages, new ToComparator(false));
				}

				return;
			}
		}

		if (orderByCol.equals("d")) {
			if (orderByType.equals("desc")) {
				Arrays.sort(messages, new DateComparator());
			}
		}
		else if (orderByCol.equals("f")) {
			if (orderByType.equals("asc")) {
				Arrays.sort(messages, new FromComparator(true));
			}
			else {
				Arrays.sort(messages, new FromComparator(false));
			}
		}
		else if (orderByCol.equals("n")) {
			if (orderByType.equals("asc")) {
				Arrays.sort(messages, new NewComparator(true));
			}
			else {
				Arrays.sort(messages, new NewComparator(false));
			}
		}
		else if (orderByCol.equals("s")) {
			if (orderByType.equals("asc")) {
				Arrays.sort(messages, new SubjectComparator(true));
			}
			else {
				Arrays.sort(messages, new SubjectComparator(false));
			}
		}
		else if (orderByCol.equals("z")) {
			if (orderByType.equals("asc")) {
				Arrays.sort(messages, new SizeComparator(true));
			}
			else {
				Arrays.sort(messages, new SizeComparator(false));
			}
		}
	}

	public static String toString(InternetAddress ia) {
		if (ia == null) {
			return "";
		}

		String address = ia.getAddress();
		if (address == null) {
			address = "";
		}

		if (ia.getPersonal() == null) {
			return address;
		}
		else {
			return ia.getPersonal() + "<" + address + ">";
		}
	}

	private static Folder _getFolder(HttpServletRequest req, String folderName)
		throws MessagingException, NamingException {

		if (Validator.isNull(folderName)) {
			folderName = MAIL_INBOX_NAME;
		}
		else if (!folderName.equals(MAIL_INBOX_NAME)) {
			if (!folderName.startsWith(MailUtil.MAIL_BOX_STYLE)) {
				folderName = MailUtil.MAIL_BOX_STYLE + folderName;
			}
		}

		Store store = getStore(req);
		FolderPool folderPool = getFolderPool(req);
		Folder folder = folderPool.get(
			MailCache.getFolderCacheId(folderName, store));

		if (folder == null) {
			folder = store.getFolder(folderName);

			if (!folder.exists()) {
				folder.create(Folder.HOLDS_MESSAGES);
			}

			folderPool.put(
				MailCache.getFolderCacheId(folderName, store), folder);
		}

		if (!folder.isOpen()) {
			folder.open(Folder.READ_WRITE);
		}

		return folder;
	}

	private static User _getMailUser(HttpServletRequest req)
		throws MessagingException {

		User user = null;

		try {
			user = PortalUtil.getUser(req);
		}
		catch (Exception e) {
			throw new MessagingException(e.getMessage(), e);
		}

		return user;
	}

	private static final Log _log = LogFactory.getLog(MailUtil.class);

}