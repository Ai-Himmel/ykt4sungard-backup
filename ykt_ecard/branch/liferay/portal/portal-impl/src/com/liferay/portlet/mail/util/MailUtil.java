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

package com.liferay.portlet.mail.util;

import com.liferay.portal.kernel.servlet.HttpHeaders;
import com.liferay.portal.kernel.util.Constants;
import com.liferay.portal.kernel.util.ContentTypes;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.ParamUtil;
import com.liferay.portal.kernel.util.StringMaker;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.kernel.util.Validator;
import com.liferay.portal.model.Company;
import com.liferay.portal.model.User;
import com.liferay.portal.service.UserLocalServiceUtil;
import com.liferay.portal.theme.ThemeDisplay;
import com.liferay.portal.util.PortalUtil;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.mail.ContentException;
import com.liferay.portlet.mail.ContentPathException;
import com.liferay.portlet.mail.FolderException;
import com.liferay.portlet.mail.MailAccountsException;
import com.liferay.portlet.mail.RecipientException;
import com.liferay.portlet.mail.StoreException;
import com.liferay.portlet.mail.model.MailAttachment;
import com.liferay.portlet.mail.model.MailContent;
import com.liferay.portlet.mail.model.MailEnvelope;
import com.liferay.portlet.mail.model.MailFolder;
import com.liferay.portlet.mail.model.MailMessage;
import com.liferay.portlet.mail.model.RemoteMailAttachment;
import com.liferay.portlet.mail.search.MailDisplayTerms;
import com.liferay.portlet.mail.util.multiaccount.MailAccount;
import com.liferay.portlet.mail.util.multiaccount.MailAccounts;
import com.liferay.portlet.mail.util.multiaccount.MailCache;
import com.liferay.util.Http;
import com.liferay.util.mail.JavaMailUtil;
import com.liferay.util.mail.MailEngine;
import com.liferay.util.mail.MailServerException;

import com.sun.mail.imap.IMAPFolder;

import java.io.IOException;

import java.net.SocketException;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Comparator;
import java.util.Date;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;
import java.util.Set;
import java.util.TreeSet;
import java.util.regex.Matcher;
import java.util.regex.Pattern;

import javax.activation.DataHandler;
import javax.activation.DataSource;

import javax.mail.Address;
import javax.mail.AuthenticationFailedException;
import javax.mail.BodyPart;
import javax.mail.FetchProfile;
import javax.mail.Flags.Flag;
import javax.mail.Flags;
import javax.mail.Folder;
import javax.mail.Message.RecipientType;
import javax.mail.Message;
import javax.mail.MessagingException;
import javax.mail.Multipart;
import javax.mail.Part;
import javax.mail.Session;
import javax.mail.Store;
import javax.mail.Transport;
import javax.mail.UIDFolder.FetchProfileItem;
import javax.mail.internet.InternetAddress;
import javax.mail.internet.MimeBodyPart;
import javax.mail.internet.MimeMessage;
import javax.mail.internet.MimeMultipart;
import javax.mail.search.AndTerm;
import javax.mail.search.BodyTerm;
import javax.mail.search.DateTerm;
import javax.mail.search.FromStringTerm;
import javax.mail.search.OrTerm;
import javax.mail.search.RecipientStringTerm;
import javax.mail.search.SearchTerm;
import javax.mail.search.SentDateTerm;
import javax.mail.search.SubjectTerm;
import javax.mail.util.ByteArrayDataSource;

import javax.naming.NamingException;

import javax.servlet.http.HttpServletRequest;
import javax.servlet.http.HttpSession;

import org.apache.commons.collections.map.MultiValueMap;
import org.apache.commons.logging.Log;
import org.apache.commons.logging.LogFactory;

/**
 * Used as a fascade to the JavaMail API.  All JavaMail objects are wrappered in
 * model classes and returned out of this utility fascade.
 *
 * <a href="MailUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Alexander Chow
 *
 */
public class MailUtil {

	public static final String MAIL_BOX_STYLE =
		PropsUtil.get(PropsUtil.MAIL_BOX_STYLE);

	public static final String MAIL_INBOX_NAME =
		PropsUtil.get(PropsUtil.MAIL_INBOX_NAME);

	public static final String MAIL_DRAFTS_NAME =
		MAIL_BOX_STYLE + PropsUtil.get(PropsUtil.MAIL_DRAFTS_NAME);

	public static final String MAIL_SENT_NAME =
		MAIL_BOX_STYLE + PropsUtil.get(PropsUtil.MAIL_SENT_NAME);

	public static final String MAIL_SPAM_NAME =
		MAIL_BOX_STYLE + PropsUtil.get(PropsUtil.MAIL_SPAM_NAME);

	public static final String MAIL_TRASH_NAME =
		MAIL_BOX_STYLE + PropsUtil.get(PropsUtil.MAIL_TRASH_NAME);

	public static final String[] DEFAULT_FOLDERS = {
		MAIL_INBOX_NAME, MAIL_DRAFTS_NAME, MAIL_SPAM_NAME, MAIL_SENT_NAME,
		MAIL_TRASH_NAME
	};

	public static void completeMessage(
			HttpServletRequest req, MailMessage mailMessage, boolean send,
			String originalId, boolean wasDraft)
		throws ContentException, ContentPathException, FolderException,
			   MailServerException, RecipientException, StoreException {

		HttpSession ses = req.getSession();

		try {
			if (send && Validator.isNull(mailMessage.getTo()) &&
				Validator.isNull(mailMessage.getCc()) &&
				Validator.isNull(mailMessage.getBcc())) {

				if (_log.isErrorEnabled()) {
					_log.error("A message with no recipients cannot be sent");
				}

				throw new RecipientException();
			}

			Message message = new MimeMessage(MailEngine.getSession());

			message.setFrom(mailMessage.getFrom());

			if (Validator.isNotNull(mailMessage.getTo())) {
				message.setRecipients(
					Message.RecipientType.TO,
					_resolveAddresses(req, mailMessage.getTo()));
			}

			if (Validator.isNotNull(mailMessage.getCc())) {
				message.setRecipients(
					Message.RecipientType.CC,
					_resolveAddresses(req, mailMessage.getCc()));
			}

			if (Validator.isNotNull(mailMessage.getBcc())) {
				message.setRecipients(
					Message.RecipientType.BCC,
					_resolveAddresses(req, mailMessage.getBcc()));
			}

			if (Validator.isNotNull(mailMessage.getInReplyTo())) {
				message.setHeader("In-Reply-To", mailMessage.getInReplyTo());
			}

			if (Validator.isNotNull(mailMessage.getReferences())) {
				message.setHeader("References", mailMessage.getReferences());
			}

			message.setSubject(mailMessage.getSubject());

			_replaceEmbeddedImages(req, mailMessage, _getAttachmentURL(req));

			Multipart multipart = new MimeMultipart();

			BodyPart bodyPart = new MimeBodyPart();

			bodyPart.setContent(
				mailMessage.getBody(), ContentTypes.TEXT_HTML_UTF8);

			multipart.addBodyPart(bodyPart);

			List attachments = mailMessage.getAttachments();

			Iterator itr = attachments.iterator();

			while (itr.hasNext()) {
				MailAttachment mailAttachment = (MailAttachment)itr.next();

				DataSource dataSource = new ByteArrayDataSource(
					mailAttachment.getContent(),
					mailAttachment.getContentType());

				BodyPart attachment = new MimeBodyPart();

				attachment.setFileName(mailAttachment.getFilename());
				attachment.setDataHandler(new DataHandler(dataSource));

				if (Validator.isNotNull(mailAttachment.getContentId())) {
					attachment.addHeader(
						HttpHeaders.CONTENT_ID, mailAttachment.getContentId());
				}

				multipart.addBodyPart(attachment);
			}

			List remoteAttachments = mailMessage.getRemoteAttachments();

			itr = remoteAttachments.iterator();

			while (itr.hasNext()) {
				RemoteMailAttachment remoteMailAttachment =
					(RemoteMailAttachment)itr.next();

				Object[] parts = getAttachment(
					req, remoteMailAttachment.getContentPath());

				DataSource dataSource = new ByteArrayDataSource(
					(byte[])parts[0], (String)parts[1]);

				BodyPart attachment = new MimeBodyPart();

				attachment.setFileName(remoteMailAttachment.getFilename());
				attachment.setDataHandler(new DataHandler(dataSource));

				multipart.addBodyPart(attachment);
			}

			message.setContent(multipart);
			message.setSentDate(new Date());

			if (send) {
				Transport.send(message);
			}

			try {
				MailSessionLock.lock(req);

				String lastFolderName = getFolderName(req);

				IMAPFolder folder = null;

				if (send) {
					folder = _getFolder(req, MAIL_SENT_NAME);

					message.setFlag(Flag.SEEN, true);
				}
				else {
					folder = _getFolder(req, MAIL_DRAFTS_NAME);
				}

				folder.appendMessages(new Message[] {message});

				long origId = GetterUtil.getLong(originalId);

				if (wasDraft) {
					folder = _getFolder(req, MAIL_DRAFTS_NAME);

					Message msg = folder.getMessageByUID(origId);

					folder.setFlags(
						new Message[] {msg}, new Flags(Flags.Flag.DELETED),
						true);

					folder.expunge();
				}
				else if (origId > 0L) {
					folder = _getFolder(req, lastFolderName);

					Message msg =
						folder.getMessageByUID(origId);

					folder.setFlags(
						new Message[] {msg}, new Flags(Flags.Flag.ANSWERED),
						true);
				}

				// Make sure to explicitly close and open the correct folder

				_closeFolder(ses);

				setFolder(req, lastFolderName);
			}
			finally {
				MailSessionLock.unlock(req);
			}
		}
		catch (MessagingException me) {
			throw new ContentException(me);
		}
		catch (NamingException ne) {
			throw new ContentException(ne);
		}
	}

	public static void createFolder(HttpServletRequest req, String folderName)
		throws FolderException, MailServerException, StoreException {

		Folder folder = null;

		try {
			MailSessionLock.lock(req);

			Iterator itr = getFolders(req).iterator();

			while (itr.hasNext()) {
				MailFolder mailFolder = (MailFolder)itr.next();

				if (mailFolder.getName().equals(folderName)) {
					throw new FolderException(
						"Folder " + folderName + " already exists");
				}
			}

			Store store = _getStore(req);

			folderName = _getResolvedFolderName(folderName);

			folder = store.getFolder(folderName);

			folder.create(Folder.HOLDS_MESSAGES);
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
		finally {
			try {
				if ((folder != null) && folder.isOpen()) {
					folder.close(false);
				}
			}
			catch (Exception e) {
			}

			MailSessionLock.unlock(req);
		}
	}

	public static void deleteMessages(
			HttpServletRequest req, MultiValueMap msgMap)
		throws FolderException, MailServerException, StoreException {

		deleteMessages(req, msgMap, false);
	}

	public static void deleteMessages(
			HttpServletRequest req, MultiValueMap msgMap, boolean permanently)
		throws FolderException, MailServerException, StoreException {

		try {
			MailSessionLock.lock(req);

			Iterator itr = msgMap.keySet().iterator();

			while (itr.hasNext()) {
				String key = (String)itr.next();

				IMAPFolder folder = _getFolder(req);

				String folderName = _getResolvedFolderName(folder.getName());

				if (permanently || folderName.equals(MAIL_TRASH_NAME)) {
					Message[] messages =
						folder.getMessagesByUID(_getMessageIds(msgMap, key));

					folder.setFlags(
						messages, new Flags(Flags.Flag.DELETED), true);

					folder.expunge();

					msgMap.remove(key);
				}
			}

			if (!msgMap.isEmpty()) {
				moveMessages(req, msgMap, MAIL_TRASH_NAME);
			}
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static void emptyFolder(HttpServletRequest req, String folderName)
		throws FolderException, MailServerException, StoreException {

		try {
			MailSessionLock.lock(req);

			String lastFolderName = getFolderName(req);

			IMAPFolder folder = _getFolder(req, folderName);

			long[] ids = new long[0];

			try {
				Message[] msgs = folder.getMessages();

				FetchProfile fetchProfile = new FetchProfile();

				fetchProfile.add(FetchProfile.Item.ENVELOPE);

				folder.fetch(msgs, fetchProfile);

				ids = new long[msgs.length];

				for (int i = 0; i < msgs.length; i++) {
					ids[i] = folder.getUID(msgs[i]);
				}

				Message[] messages = folder.getMessagesByUID(ids);

				folder.setFlags(messages, new Flags(Flags.Flag.DELETED), true);

				folder.expunge();
			}
			catch (MessagingException me) {
				throw new FolderException(me);
			}
			finally {
				setFolder(req, lastFolderName);
			}
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static Object[] getAttachment(
			HttpServletRequest req, String contentPath)
		throws ContentException, ContentPathException, FolderException,
			   MailServerException, StoreException {

		Object[] parts = null;

		try {
			MailSessionLock.lock(req);

			String[] path = RemoteMailAttachment.parsePath(contentPath);

			String folderName = path[0];
			long messageId = GetterUtil.getLong(path[1]);
			String mimePath = path[2];

			IMAPFolder folder = _getFolder(req, folderName);

			Message message = folder.getMessageByUID(messageId);

			parts = _getAttachmentFromPath(message, mimePath);
		}
		catch (ContentPathException cpe) {
			throw cpe;
		}
		catch (IOException ioe) {
			throw new ContentException(ioe);
		}
		catch (MessagingException me) {
			throw new ContentException(me);
		}
		finally {
			MailSessionLock.unlock(req);
		}

		return parts;
	}

	public static Set getEnvelopes(
			HttpServletRequest req, Comparator comparator)
		throws FolderException {

		Set envelopes = new TreeSet(comparator);

		try {
			MailSessionLock.lock(req);

			IMAPFolder folder = _getFolder(req);

			String folderName = _getResolvedFolderName(folder.getName());

			Message[] messages = folder.getMessages();

			FetchProfile fetchProfile = new FetchProfile();

			fetchProfile.add(IMAPFolder.FetchProfileItem.SIZE);
			fetchProfile.add(FetchProfile.Item.ENVELOPE);
			fetchProfile.add(FetchProfile.Item.FLAGS);
			fetchProfile.add(FetchProfileItem.UID);

			folder.fetch(messages, fetchProfile);

			_convertEnvelopes(folder, folderName, messages, envelopes);

			return envelopes;
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static MailFolder getFolder(HttpServletRequest req)
		throws FolderException, MailServerException, MessagingException,
			   StoreException {

		try {

			// Make sure a store has been retrieved first

			_getStore(req);

			MailSessionLock.lock(req);

			IMAPFolder folder = _getFolder(req);

			List list = new ArrayList();

			_getFolders(list, new IMAPFolder[] {folder});

			return (MailFolder)list.get(0);
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static String getFolderName(HttpServletRequest req)
		throws FolderException, StoreException {

		try {
			MailSessionLock.lock(req);

			IMAPFolder folder = _getFolder(req);

			return folder.getName();
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static List getFolders(HttpServletRequest req)
		throws FolderException, MailServerException, StoreException {

		List list = new ArrayList();

		IMAPFolder root = null;

		try {
			List tempList = new ArrayList();

			Store store = _getStore(req);

			root = (IMAPFolder)store.getDefaultFolder();

			Folder[] folders = root.list();

			_getFolders(tempList, folders);

			for (int i = 0; i < DEFAULT_FOLDERS.length; i++) {
				ListIterator itr = tempList.listIterator();

				while (itr.hasNext()){
					MailFolder mailFolder = (MailFolder)itr.next();

					if (DEFAULT_FOLDERS[i].equals(
							_getResolvedFolderName(mailFolder.getName()))) {

						list.add(mailFolder);

						itr.remove();

						break;
					}
				}
			}

			list.addAll(tempList);
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
		finally {
			try {
				if ((root != null) && root.isOpen()) {
					root.close(false);
				}
			}
			catch (Exception ex) {
			}
		}

		return list;
	}

	public static MailMessage getMessage(HttpServletRequest req)
		throws ContentException, FolderException, StoreException {

		try {
			MailSessionLock.lock(req);

			long messageId = getMessageId(req);

			if (messageId != -1L) {
				return getMessage(req, messageId);
			}
			else {
				return null;
			}
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static MailMessage getMessage(HttpServletRequest req, long messageId)
		throws ContentException, FolderException, StoreException {

		HttpSession ses = req.getSession();

		MailMessage mailMessage = new MailMessage();

		try {
			MailSessionLock.lock(req);

			IMAPFolder folder = _getFolder(req);

			Message message = folder.getMessageByUID(messageId);

			mailMessage.setMessageId(messageId);

			if (Validator.isNotNull(message.getFrom())) {
				mailMessage.setFrom(message.getFrom()[0]);
			}

			mailMessage.setTo(message.getRecipients(RecipientType.TO));
			mailMessage.setCc(message.getRecipients(RecipientType.CC));
			mailMessage.setBcc(message.getRecipients(RecipientType.BCC));
			mailMessage.setReplyTo(message.getReplyTo());

			String[] messageIdHeader = message.getHeader("Message-ID");
			String[] referencesHeader = message.getHeader("References");

			if (Validator.isNotNull(messageIdHeader)) {
				mailMessage.setInReplyTo(messageIdHeader[0]);

				if (Validator.isNull(referencesHeader)) {
					mailMessage.setReferences(messageIdHeader[0]);
				}
				else {
					mailMessage.setReferences(
						referencesHeader[0] + StringPool.SPACE +
							messageIdHeader[0]);
				}
			}
			else {
				if (Validator.isNotNull(referencesHeader[0])) {
					mailMessage.setReferences(referencesHeader[0]);
				}
			}

			mailMessage.setSubject(message.getSubject());
			mailMessage.setSentDate(message.getSentDate());

			String contentPath = RemoteMailAttachment.buildContentPath(
				folder.getName(), messageId);

			MailContent content = new MailContent();

			mailMessage = _getContent(
				message, mailMessage, content, contentPath);

			mailMessage.setMailContent(content);

			if (_log.isDebugEnabled()) {
				_log.debug("Body before replacing content ids\n" + content);
			}

			_replaceContentIds(
				content, mailMessage.getRemoteAttachments(),
				_getAttachmentURL(req));

			if (_log.isDebugEnabled()) {
				_log.debug("Body after replacing content ids\n" + content);
			}

			mailMessage.purgeDirtyRemoteAttachments();

			ses.setAttribute(WebKeys.MAIL_MESSAGE_ID, new Long(messageId));

			return mailMessage;
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static long getMessageId(HttpServletRequest req)
		throws ContentException, FolderException, StoreException {

		HttpSession ses = req.getSession();

		try {
			MailSessionLock.lock(req);

			Long messageId = (Long)ses.getAttribute(WebKeys.MAIL_MESSAGE_ID);

			if (messageId != null) {
				return messageId.longValue();
			}
			else {
				return -1L;
			}
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static void moveMessages(
			HttpServletRequest req, MultiValueMap msgMap, String toFolderName)
		throws FolderException, MailServerException, StoreException {

		IMAPFolder toFolder = null;

		toFolderName = _getResolvedFolderName(toFolderName);

		try {
			MailSessionLock.lock(req);

			Iterator itr = msgMap.keySet().iterator();

			while (itr.hasNext()) {
				String folderName = (String)itr.next();

				long[] messageIds = _getMessageIds(msgMap, folderName);

				IMAPFolder folder = _getFolder(req, folderName);

				folderName = _getResolvedFolderName(folder.getName());

				if (folderName.equals(toFolderName)) {
					continue;
				}

				if ((folderName.equals(MAIL_DRAFTS_NAME) ||
						toFolderName.equals(MAIL_DRAFTS_NAME)) &&
					(!toFolderName.equals(MAIL_TRASH_NAME))) {

					continue;
				}

				Store store = _getStore(req);

				toFolder = (IMAPFolder)store.getFolder(toFolderName);

				toFolder.open(IMAPFolder.READ_WRITE);

				Message[] messages = folder.getMessagesByUID(messageIds);

				folder.copyMessages(messages, toFolder);

				folder.setFlags(messages, new Flags(Flags.Flag.DELETED), true);

				folder.expunge();
			}
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
		finally {
			try {
				if ((toFolder != null) && toFolder.isOpen()) {
					toFolder.close(true);
				}
			}
			catch (Exception e) {
			}

			MailSessionLock.unlock(req);
		}
	}

	public static void removeFolder(HttpServletRequest req, String folderName)
		throws FolderException, MailServerException, StoreException {

		try {
			folderName = _getResolvedFolderName(folderName);

			for (int i = 0; i < DEFAULT_FOLDERS.length; i++) {
				if (DEFAULT_FOLDERS[i].equals(folderName)) {
					if (_log.isErrorEnabled()) {
						_log.error(
							"Folder " + folderName +
								" is a system folder and cannot be changed");
					}

					throw new FolderException();
				}
			}

			try {
				MailSessionLock.lock(req);

				setFolder(req, MAIL_INBOX_NAME);

				Store store = _getStore(req);

				Folder folder = store.getFolder(folderName);

				if (!folder.exists()) {
					if (_log.isErrorEnabled()) {
						_log.error("Folder " + folderName + " does not exist");
					}

					throw new FolderException();
				}

				folder.delete(true);
			}
			finally {
				MailSessionLock.unlock(req);
			}
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
	}

	public static void renameFolder(
			HttpServletRequest req, String oldFolderName, String newFolderName)
		throws FolderException, MailServerException, StoreException {

		try {
			oldFolderName = _getResolvedFolderName(oldFolderName);
			newFolderName = _getResolvedFolderName(newFolderName);

			for (int i = 0; i < DEFAULT_FOLDERS.length; i++) {
				if (DEFAULT_FOLDERS[i].equals(oldFolderName)) {
					if (_log.isErrorEnabled()) {
						_log.error(
							"Folder " + oldFolderName +
								" is a system folder and cannot be changed");
					}

					throw new FolderException();
				}
				else if (DEFAULT_FOLDERS[i].equals(newFolderName)) {
					if (_log.isErrorEnabled()) {
						_log.error(
							"Folder " + newFolderName +
								" is a system folder and cannot be changed");
					}

					throw new FolderException();
				}
			}

			try {
				MailSessionLock.lock(req);

				setFolder(req, MAIL_INBOX_NAME);

				Store store = _getStore(req);

				Folder oldFolder = store.getFolder(oldFolderName);
				Folder newFolder = store.getFolder(newFolderName);

				if (!oldFolder.exists()) {
					if (_log.isErrorEnabled()) {
						_log.error(
							"Folder " + oldFolderName + " does not exist");
					}

					throw new FolderException();
				}
				else if (newFolder.exists()) {
					if (_log.isErrorEnabled()) {
						_log.error(
							"Folder " + newFolderName + " already exists");
					}

					throw new FolderException();
				}

				oldFolder.renameTo(newFolder);
			}
			finally {
				MailSessionLock.unlock(req);
			}
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
	}

	public static Set search(
			HttpServletRequest req, MailDisplayTerms displayTerms,
			Comparator comparator)
		throws FolderException, MailServerException, StoreException {

		Set results = new TreeSet(comparator);

		if (Validator.isNotNull(displayTerms.getFolderName())) {
			_search(req, displayTerms, results);
		}
		else {
			List folders = getFolders(req);

			Iterator itr = folders.iterator();

			while (itr.hasNext()) {
				MailFolder mailFolder = (MailFolder)itr.next();

				String resolvedName =
					_getResolvedFolderName(mailFolder.getName());

				if (resolvedName.equals(MAIL_SPAM_NAME) ||
					resolvedName.equals(MAIL_TRASH_NAME)) {

					continue;
				}

				displayTerms.setFolderName(mailFolder.getName());

				_search(req, displayTerms, results);
			}
		}

		return results;
	}

	public static void setAccount(HttpServletRequest req) {
		String accountName = ParamUtil.getString(req, Constants.MAIL_ACCOUNT);

		try {
			if (Validator.isNotNull(accountName)) {
				MailAccounts.setAccount(req, accountName);
			}
		}
		catch (MailAccountsException e) {
			if (_log.isWarnEnabled()) {
				_log.warn("Error setting account " + accountName, e);
			}
		}
	}

	public static void setFolder(HttpServletRequest req, String folderName)
		throws FolderException, MailServerException, StoreException {

		try {
			MailSessionLock.lock(req);

			_getFolder(req, folderName);
		}
		finally {
			MailSessionLock.unlock(req);
		}
	}

	public static void setMessageId(HttpServletRequest req, long messageId) {
		HttpSession ses = req.getSession();

		ses.setAttribute(WebKeys.MAIL_MESSAGE_ID, new Long(messageId));
	}

	protected static void cleanUp(HttpSession ses) throws StoreException {
		try {
			_closeFolder(ses);

			MailCache.clearCache(ses);

			ses.removeAttribute(WebKeys.MAIL_MESSAGE_ID);
		}
		catch (MessagingException me) {
			throw new StoreException(me);
		}
	}

	private static SearchTerm _appendSearchTerm(
			SearchTerm fullTerm, SearchTerm term, boolean isAndOperator) {

		if (fullTerm == null) {
			return term;
		}

		if (isAndOperator) {
			return new AndTerm(fullTerm, term);
		}
		else {
			return new OrTerm(fullTerm, term);
		}
	}

	private static void _closeFolder(HttpSession ses) {
		IMAPFolder folder = (IMAPFolder)ses.getAttribute(WebKeys.MAIL_FOLDER);

		if ((folder != null) && folder.isOpen()) {
			try {
				folder.close(false);
			}
			catch (MessagingException me) {
				if (_log.isWarnEnabled()) {
					_log.warn(me);
				}
			}

			ses.removeAttribute(WebKeys.MAIL_FOLDER);
		}
	}

	private static void _convertEnvelopes(
			IMAPFolder folder, String folderName, Message[] messages,
			Set envelopes)
		throws MessagingException {

		for (int i = 0; i < messages.length; i++) {
			Message message = messages[i];

			if (message.isExpunged()) {
				continue;
			}

			MailEnvelope mailEnvelope = new MailEnvelope();

			mailEnvelope.setMessageId(folder.getUID(message));
			mailEnvelope.setFolderName(folder.getName());

			if (MAIL_SENT_NAME.equals(folderName) ||
				MAIL_DRAFTS_NAME.equals(folderName)) {

				Address[] recipients = message.getAllRecipients();

				StringMaker sm = new StringMaker();

				if (Validator.isNotNull(recipients)) {
					for (int j = 0; j < recipients.length; j++) {
						InternetAddress address =
							(InternetAddress)recipients[j];

						String recipient = GetterUtil.getString(
							address.getPersonal(), address.getAddress());

						sm.append(recipient);

						if (j < (recipients.length - 1)) {
							sm.append(", ");
						}
					}
				}

				if (sm.length() > 0) {
					mailEnvelope.setRecipient(sm.toString());
				}
			}
			else {
				Address[] from = message.getFrom();

				if (Validator.isNotNull(from)) {
					InternetAddress address = (InternetAddress)from[0];

					String recipient = GetterUtil.getString(
						address.getPersonal(), address.getAddress());

					mailEnvelope.setRecipient(recipient);
				}
			}

			mailEnvelope.setSubject(message.getSubject());
			mailEnvelope.setDate(message.getSentDate());
			mailEnvelope.setSize(
				(int)(message.getSize() * _ENCODING_FACTOR));
			mailEnvelope.setRead(message.isSet(Flag.SEEN));
			mailEnvelope.setFlagged(message.isSet(Flag.FLAGGED));
			mailEnvelope.setAnswered(message.isSet(Flag.ANSWERED));

			envelopes.add(mailEnvelope);
		}
	}

	private static Store _createStore(
			HttpServletRequest req, MailAccount account)
		throws FolderException, MailServerException, MessagingException,
			   NamingException, StoreException {

		HttpSession ses = req.getSession();

		Session session = MailEngine.getSession();

		Store store = session.getStore("imap");

		String serviceName =
			account.getUserId() + StringPool.COLON + WebKeys.MAIL_STORE;

		store.addConnectionListener(new ConnectionListener(serviceName));

		String imapHost = session.getProperty("mail.imap.host");

		store.connect(imapHost, account.getUserId(), account.getPassword());

		MailCache.putStore(ses, account.getName(), store);

		List list = getFolders(req);

		for (int i = 0; i < DEFAULT_FOLDERS.length; i++) {
			boolean exists = false;

			Iterator itr = list.iterator();

			while (itr.hasNext()) {
				MailFolder mailFolder = (MailFolder)itr.next();

				if (DEFAULT_FOLDERS[i].equals(mailFolder.getName())) {
					exists = true;

					break;
				}
			}

			if (!exists) {
				createFolder(req, DEFAULT_FOLDERS[i]);
			}
		}

		if (ses.getAttribute(WebKeys.MAIL_FOLDER) == null) {
			setFolder(req, MAIL_INBOX_NAME);
		}

		return store;
	}

	private static String _customizeHtml(String html) {
		for (int i = 0; i < _HTML_START_TAGS.length; i++) {
			Pattern startPattern = Pattern.compile(
				_HTML_START_TAGS[i], Pattern.CASE_INSENSITIVE);

			Matcher startMatcher = startPattern.matcher(html);

			while (startMatcher.find()) {
				int start = startMatcher.start();
				int end = html.indexOf(">", start);

				if (end == -1) {
					html = StringUtil.replace(
						html, html.substring(start), StringPool.BLANK);
				}
				else {
					html = StringUtil.replace(
						html, html.substring(start, end + 1), StringPool.BLANK);
				}

				if (i < _HTML_END_TAGS.length) {
					Pattern endPattern = Pattern.compile(
						_HTML_END_TAGS[i], Pattern.CASE_INSENSITIVE);

					Matcher endMatcher = endPattern.matcher(html);

					html = endMatcher.replaceFirst(StringPool.BLANK);
				}
				else {
					startMatcher.reset(html);
				}
			}
		}

		return html.trim();
	}

	private static Object[] _getAttachmentFromPath(Part part, String mimePath)
		throws ContentPathException, IOException, MessagingException {

		int index = GetterUtil.getInteger(
			StringUtil.split(mimePath.substring(1), StringPool.PERIOD)[0]);

		if (part.getContent() instanceof Multipart) {
			String prefix = String.valueOf(index) + StringPool.PERIOD;

			Multipart multipart = (Multipart)part.getContent();

			for (int i = 0; i < multipart.getCount(); i++) {
				if (index == i) {
					return _getAttachmentFromPath(
						multipart.getBodyPart(i),
						mimePath.substring(prefix.length()));
				}
			}

			throw new ContentPathException();
		}
		else if (index != -1) {
			throw new ContentPathException();
		}

		byte[] byteArray = JavaMailUtil.getBytes(part);

		return new Object[] {byteArray, part.getContentType()};
	}

	private static String _getAttachmentURL(HttpServletRequest req) {
		ThemeDisplay themeDisplay =
			(ThemeDisplay)req.getAttribute(WebKeys.THEME_DISPLAY);

		return themeDisplay.getPathMain() + "/mail/get_attachment?";
	}

	private static MailMessage _getContent(
			Part part, MailMessage mailMessage, MailContent content,
			String contentPath)
		throws ContentException {

		try {
			String contentType = part.getContentType().toLowerCase();

			boolean attachment = true;

			if (part.getContent() instanceof Multipart) {
				attachment = false;

				Multipart multipart = (Multipart)part.getContent();

				for (int i = 0; i < multipart.getCount(); i++) {
					Part curPart = multipart.getBodyPart(i);

					mailMessage = _getContent(
						curPart, mailMessage, content,
						contentPath + StringPool.PERIOD + i);
				}
			}
			else if (Validator.isNull(part.getFileName())) {
				attachment = false;

				if (contentType.startsWith(ContentTypes.TEXT_PLAIN)) {
					content.appendPlainBody((String)part.getContent());
				}
				else if (contentType.startsWith(ContentTypes.TEXT_HTML)) {
					content.appendHtmlBody(
						_customizeHtml((String)part.getContent()));
				}
				else if (contentType.startsWith(ContentTypes.MESSAGE_RFC822)) {
					MailContent subContent = new MailContent();

					mailMessage = _getContent(
						(Part)part.getContent(), mailMessage, subContent,
						contentPath + StringPool.PERIOD + 0);

					content.appendSubContent(subContent);
				}
			}

			if (attachment) {
				mailMessage.appendRemoteAttachment(
					_getRemoteAttachment(
						part, contentPath + StringPool.PERIOD + -1));
			}
		}
		catch (IOException ioe) {
			throw new ContentException(ioe);
		}
		catch (MessagingException me) {
			throw new ContentException(me);
		}

		return mailMessage;
	}

	private static IMAPFolder _getFolder(HttpServletRequest req)
		throws FolderException {

		HttpSession ses = req.getSession();

		IMAPFolder folder = (IMAPFolder)ses.getAttribute(WebKeys.MAIL_FOLDER);

		if (folder != null) {
			return folder;
		}
		else {
			throw new FolderException();
		}
	}

	private static IMAPFolder _getFolder(
			HttpServletRequest req, String folderName)
		throws FolderException, MailServerException, StoreException {

		HttpSession ses = req.getSession();

		try {
			folderName = _getResolvedFolderName(folderName);

			IMAPFolder folder = (IMAPFolder)ses.getAttribute(
				WebKeys.MAIL_FOLDER);

			if (folder != null) {
				String currFolderName =
					_getResolvedFolderName(folder.getName());

				if (!currFolderName.equals(folderName)) {
					_closeFolder(ses);

					folder = null;
				}
				else if (!folder.isOpen()) {
					if (_log.isInfoEnabled()) {
						_log.info(
							"The folder is closed and needs to be reopened");
					}

					_closeFolder(ses);

					folder = null;
				}
			}

			if (folder == null) {
				Long userIdObj = (Long)ses.getAttribute(WebKeys.USER_ID);

				String serviceName = userIdObj + StringPool.COLON +
					WebKeys.MAIL_FOLDER + StringPool.PERIOD + folderName;

				Store store = _getStore(req);

				folder = (IMAPFolder)store.getFolder(folderName);

				folder.addConnectionListener(
					new ConnectionListener(serviceName));

				folder.open(IMAPFolder.READ_WRITE);

				ses.setAttribute(WebKeys.MAIL_FOLDER, folder);

				ses.removeAttribute(WebKeys.MAIL_MESSAGE_ID);
			}

			return folder;
		}
		catch (MessagingException me) {
			throw new FolderException(me);
		}
	}

	private static void _getFolders(List list, Folder[] folders) {
		for (int i = 0; i < folders.length; i++) {
			Folder folder = folders[i];

			try {
				int folderType = folder.getType();

				if ((folderType & IMAPFolder.HOLDS_MESSAGES) != 0) {
					MailFolder mailFolder = new MailFolder(
						folder.getName(), folder.getMessageCount(),
						folder.getUnreadMessageCount());

					list.add(mailFolder);
				}

				if ((folderType & IMAPFolder.HOLDS_FOLDERS) != 0) {
					_getFolders(list, folder.list());
				}
			}
			catch (MessagingException me) {
				_log.error("Skipping IMAP folder because " + me.getMessage());
			}
		}
	}

	private static long[] _getMessageIds(
			MultiValueMap msgMap, String folderName) {

		Collection messages = msgMap.getCollection(folderName);

		long[] messageIds = new long[messages.size()];

		Iterator msgItr = messages.iterator();

		for (int i = 0; msgItr.hasNext(); i++) {
			messageIds[i] = GetterUtil.getLong((String)msgItr.next());
		}

		return messageIds;
	}

	private static RemoteMailAttachment _getRemoteAttachment(
			Part part, String contentPath)
		throws ContentException {

		RemoteMailAttachment remoteMailAttachment = new RemoteMailAttachment();

		try {
			remoteMailAttachment.setFilename(part.getFileName());
			remoteMailAttachment.setContentPath(contentPath);

			String[] contentId = part.getHeader(HttpHeaders.CONTENT_ID);

			if ((contentId != null) && (contentId.length == 1)) {
				remoteMailAttachment.setContentId(contentId[0]);
			}
		}
		catch (MessagingException me) {
			if (_log.isErrorEnabled()) {
				_log.error(
					"Unable to properly get file name of MIME attachment");
			}

			throw new ContentException(me);
		}

		return remoteMailAttachment;
	}

	private static String _getResolvedFolderName(String folderName) {
		String resolvedName = folderName;

		if (Validator.isNull(folderName)) {
			resolvedName = MAIL_INBOX_NAME;
		}
		else if (!folderName.equals(MAIL_INBOX_NAME) &&
				 !folderName.startsWith(MAIL_BOX_STYLE)) {

			resolvedName = MAIL_BOX_STYLE + folderName;
		}

		return resolvedName;
	}

	private static Store _getStore(HttpServletRequest req)
		throws FolderException, MailServerException, StoreException {

		HttpSession ses = req.getSession();

		MailAccount currentAccount = MailAccounts.getCurrentAccount(req);

		try {
			Store store = MailCache.getStore(ses, currentAccount.getName());

			if (store != null && !store.isConnected()) {
				if (_log.isInfoEnabled()) {
					_log.info("The store needs to be reconnected");
				}

				cleanUp(ses);

				store = null;
			}

			if (store == null) {
				store = _createStore(req, currentAccount);
			}

			return store;
		}
		catch (AuthenticationFailedException afe) {
			_log.error(
				"Failed to authenticate the userId " +
					currentAccount.getUserId());

			throw new StoreException(afe);
		}
		catch (MessagingException me) {
			Exception e = me.getNextException();

			if (e instanceof SocketException) {
				if (_log.isWarnEnabled()) {
					_log.warn(
						"Failed to connect to a valid mail server. Please " +
							"make sure one is properly configured.");
				}

				throw new MailServerException(e);
			}
			else {
				throw new StoreException(me);
			}
		}
		catch (NamingException ne) {
			throw new StoreException(ne);
		}
	}

	private static void _replaceContentIds(
		MailContent content, List rmas, String url) {

		String body = content.getHtmlBody();

		for (int i = 0; i < rmas.size(); i++) {
			RemoteMailAttachment rma = (RemoteMailAttachment)rmas.get(i);

			if (Validator.isNotNull(rma.getContentId())) {
				String contentId = rma.getContentId();

				if (contentId.startsWith(StringPool.LESS_THAN) &&
					contentId.endsWith(StringPool.GREATER_THAN)) {

					contentId =
						"cid:" + contentId.substring(1, contentId.length() - 1);
				}

				String remotePath =
					url + "fileName=" + rma.getFilename() + "&contentPath=" +
						rma.getContentPath();

				body = StringUtil.replace(body, contentId, remotePath);

				rma.setDirty(true);
			}
		}

		content.setHtmlBody(body);

		for (int i = 0; i < content.getSubContent().size(); i++) {
			_replaceContentIds(
				(MailContent)content.getSubContent().get(i), rmas, url);
		}
	}

	private static void _replaceEmbeddedImages(
			HttpServletRequest req, MailMessage mailMessage, String url)
		throws ContentException, ContentPathException, FolderException,
			   MailServerException, StoreException {

		HttpSession ses = req.getSession();

		String prefix = ses.getId() + System.currentTimeMillis();

		int count = 0;

		String body = mailMessage.getBody();

		if (_log.isDebugEnabled()) {
			_log.debug("Body before replacing embedded images\n" + body);
		}

		int x = body.indexOf(url);

		while (x >= 0) {
			int y = body.indexOf("-1", x);

			if (y > 0) {
				y += 2;

				String attachmentPath = body.substring(x, y);

				String fileName = Http.getParameter(attachmentPath, "fileName");
				String contentPath = Http.getParameter(
					attachmentPath, "contentPath");

				String contentId = prefix + count;

				Object[] parts = getAttachment(req, contentPath);

				MailAttachment mailAttachment = new MailAttachment();

				mailAttachment.setFilename(fileName);
				mailAttachment.setContent((byte[])parts[0]);
				mailAttachment.setContentType((String)parts[1]);
				mailAttachment.setContentId(
					StringPool.LESS_THAN + contentId + StringPool.GREATER_THAN);

				mailMessage.appendAttachment(mailAttachment);

				body = StringUtil.replace(
					body, attachmentPath, "cid:" + contentId);

				count++;

				x = body.indexOf(url);
			}
			else {
				x = body.indexOf(url, x + 1);
			}
		}

		if (count > 0) {
			mailMessage.setBody(body);
		}

		if (_log.isDebugEnabled()) {
			_log.debug("Body after replacing embedded images\n" + body);
		}
	}

	private static Address[] _resolveAddresses(
			HttpServletRequest req, Address[] addresses)
		throws RecipientException {

		Company company = null;

		try {
			company = PortalUtil.getCompany(req);
		}
		catch (Exception e) {
			return addresses;
		}

		for (int i = 0; i < addresses.length; i++) {
			InternetAddress address = (InternetAddress)addresses[i];

			if ((address.getPersonal() == null) &&
				!Validator.isEmailAddress(address.getAddress())) {

				try {
					User user = UserLocalServiceUtil.getUserByEmailAddress(
						company.getCompanyId(), address.getAddress().trim() +
							StringPool.AT + company.getMx());

					addresses[i] = new InternetAddress(
						user.getEmailAddress(), user.getFullName());
				}
				catch (Exception e) {
					if (_log.isErrorEnabled()) {
						_log.error(
							"Problems found trying to resolve email address " +
								address);
					}

					throw new RecipientException(e);
				}
			}
		}

		return addresses;
	}

	private static void _search(
			HttpServletRequest req, MailDisplayTerms displayTerms, Set results)
		throws FolderException, MailServerException, StoreException {

		Store store = _getStore(req);

		SearchTerm fullTerm = null;

		if (Validator.isNotNull(displayTerms.getFrom())) {
			fullTerm = new FromStringTerm(displayTerms.getFrom());
		}

		if (Validator.isNotNull(displayTerms.getTo())) {
			SearchTerm to = new RecipientStringTerm(
				Message.RecipientType.TO, displayTerms.getTo());
			SearchTerm cc = new RecipientStringTerm(
				Message.RecipientType.CC, displayTerms.getTo());
			SearchTerm bcc = new RecipientStringTerm(
				Message.RecipientType.BCC, displayTerms.getTo());

			SearchTerm term = to;
			term = _appendSearchTerm(term, cc, false);
			term = _appendSearchTerm(term, bcc, false);

			fullTerm = _appendSearchTerm(
				fullTerm, term, displayTerms.isAndOperator());
		}

		if (Validator.isNotNull(displayTerms.getSubject())) {
			SearchTerm term = new SubjectTerm(displayTerms.getSubject());

			fullTerm = _appendSearchTerm(
				fullTerm, term, displayTerms.isAndOperator());
		}

		if (Validator.isNotNull(displayTerms.getEntireMessage())) {
			String em = displayTerms.getEntireMessage();

			SearchTerm from = new FromStringTerm(em);
			SearchTerm to = new RecipientStringTerm(
				Message.RecipientType.TO, em);
			SearchTerm cc = new RecipientStringTerm(
				Message.RecipientType.CC, em);
			SearchTerm bcc = new RecipientStringTerm(
				Message.RecipientType.BCC, em);
			SearchTerm subject = new SubjectTerm(em);
			SearchTerm body = new BodyTerm(em);

			SearchTerm term = from;
			term = _appendSearchTerm(term, to, false);
			term = _appendSearchTerm(term, cc, false);
			term = _appendSearchTerm(term, bcc, false);
			term = _appendSearchTerm(term, subject, false);
			term = _appendSearchTerm(term, body, false);

			fullTerm = _appendSearchTerm(
				fullTerm, term, displayTerms.isAndOperator());
		}

		if (displayTerms.hasDate()) {
			SearchTerm startDate =
				new SentDateTerm(DateTerm.GE, displayTerms.getStartDate());
			SearchTerm endDate =
				new SentDateTerm(DateTerm.LE, displayTerms.getEndDate());

			SearchTerm term = startDate;
			term = _appendSearchTerm(term, endDate, true);

			fullTerm = _appendSearchTerm(
				fullTerm, term, displayTerms.isAndOperator());
		}

		if (fullTerm != null) {
			try {
				IMAPFolder folder = (IMAPFolder)store.getFolder(
					_getResolvedFolderName(displayTerms.getFolderName()));

				folder.open(IMAPFolder.READ_ONLY);

				Message[] messages = folder.search(fullTerm);

				_convertEnvelopes(
					folder, displayTerms.getFolderName(), messages, results);
			}
			catch (MessagingException me) {
				throw new FolderException(me);
			}
		}
	}

	private static final String[] _HTML_START_TAGS = new String[] {
		"<html", "<head", "<body", "<meta", "<o:SmartTagType"
	};

	private static final String[] _HTML_END_TAGS = new String[] {
		"</html>", "</head>", "</body>"
	};

	private static final double _ENCODING_FACTOR = 0.65;

	private static Log _log = LogFactory.getLog(MailUtil.class);

}