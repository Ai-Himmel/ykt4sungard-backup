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

package com.liferay.portlet.messaging.util;

import com.liferay.portal.PortalException;
import com.liferay.portal.SystemException;
import com.liferay.portal.kernel.util.GetterUtil;
import com.liferay.portal.kernel.util.StringPool;
import com.liferay.portal.kernel.util.StringUtil;
import com.liferay.portal.model.User;
import com.liferay.portal.util.PropsUtil;
import com.liferay.portal.util.PropsValues;
import com.liferay.portal.util.WebKeys;
import com.liferay.portlet.chat.model.RosterUpdateListener;
import com.liferay.portlet.messaging.model.JabberSession;
import com.liferay.portlet.messaging.model.MessageListener;
import com.liferay.portlet.messaging.util.comparator.NameComparator;

import java.util.ArrayList;
import java.util.Collections;
import java.util.Iterator;
import java.util.List;

import javax.servlet.http.HttpSession;

import org.jivesoftware.smack.AccountManager;
import org.jivesoftware.smack.Chat;
import org.jivesoftware.smack.PacketCollector;
import org.jivesoftware.smack.Roster;
import org.jivesoftware.smack.RosterEntry;
import org.jivesoftware.smack.XMPPConnection;
import org.jivesoftware.smack.XMPPException;
import org.jivesoftware.smack.filter.PacketFilter;
import org.jivesoftware.smack.filter.PacketTypeFilter;
import org.jivesoftware.smack.packet.Message;
import org.jivesoftware.smack.packet.Presence;
import org.jivesoftware.smack.packet.RosterPacket;

import org.json.JSONArray;
import org.json.JSONObject;

/**
 * <a href="MessagingUtil.java.html"><b><i>View Source</i></b></a>
 *
 * @author Ming-Gih Lam
 *
 */
public class MessagingUtil {

	public static String SERVER_ADDRESS = GetterUtil.getString(
		PropsUtil.get(PropsUtil.JABBER_XMPP_SERVER_ADDRESS), "localhost");

	public static int SERVER_PORT = GetterUtil.getInteger(
		PropsUtil.get(PropsUtil.JABBER_XMPP_SERVER_PORT), 5222);

	public static String USER_PASSWORD = GetterUtil.getString(
		PropsUtil.get(PropsUtil.JABBER_XMPP_USER_PASSWORD), "liferayllc");

	public static JSONObject addRosterEntry(HttpSession ses, User user)
		throws PortalException, SystemException, XMPPException {

		JSONObject jo = new JSONObject();

		Roster roster = getRoster(ses);

		String smackId = getXmppId(user);
		String name = user.getFullName();

		try {
			XMPPConnection con = new XMPPConnection(
				SERVER_ADDRESS, SERVER_PORT);

			AccountManager accountManager = con.getAccountManager();

			try {
				accountManager.createAccount(
					String.valueOf(user.getUserId()), USER_PASSWORD);
			}
			catch (XMPPException xmppe) {
			}

			con.close();
		}
		catch (XMPPException xmppe) {
		}

		roster.createEntry(smackId, name, null);

		jo.put("name", name);
		jo.put("user", user.getUserId());
		jo.put("status", "success");

		return jo;
	}

	public static void closeXMPPConnection(HttpSession ses) {
		if (isJabberEnabled()) {
			JabberSession jabberSes = (JabberSession)ses.getAttribute(
				WebKeys.JABBER_XMPP_SESSION);

			if (jabberSes != null) {
				Roster roster = jabberSes.getRoster();

				roster.removeRosterListener(jabberSes.getRosterListener());

				XMPPConnection con = jabberSes.getConnection();

				con.removePacketListener(jabberSes.getMessageListener());

				con.close();

				ses.removeAttribute(WebKeys.JABBER_XMPP_SESSION);
			}
		}
	}

	public static void createXMPPConnection(HttpSession ses, long userId)
		throws XMPPException {

		createXMPPConnection(ses, String.valueOf(userId));
	}

	public static void createXMPPConnection(HttpSession ses, String userId)
		throws XMPPException {

		if (isJabberEnabled()) {
			XMPPConnection con = null;

			try {
				con = new XMPPConnection(SERVER_ADDRESS, SERVER_PORT);
			}
			catch (XMPPException e) {
				return;
			}

			try {
				con.login(userId, USER_PASSWORD, ses.getId());
			}
			catch (XMPPException xmppe) {
				AccountManager accountManager = con.getAccountManager();

				accountManager.createAccount(userId, USER_PASSWORD);

				con.close();

				con = new XMPPConnection(SERVER_ADDRESS, SERVER_PORT);

				con.login(userId, USER_PASSWORD, ses.getId());
			}

			PacketFilter filter = new PacketTypeFilter(Message.class);

			PacketCollector collector = con.createPacketCollector(filter);

			MessageListener msgListener = new MessageListener(ses);

			con.addPacketListener(msgListener, filter);

			Roster roster = con.getRoster();

			//roster.setSubscriptionMode(Roster.SUBSCRIPTION_ACCEPT_ALL);

			RosterUpdateListener rosterListener = new RosterUpdateListener(ses);

			roster.addRosterListener(rosterListener);

			JabberSession jabberSes = new JabberSession();

			jabberSes.setConnection(con);
			jabberSes.setCollector(collector);
			jabberSes.setMessageListener(msgListener);
			jabberSes.setRoster(roster);
			jabberSes.setRosterListener(rosterListener);

			ses.setAttribute(WebKeys.JABBER_XMPP_SESSION, jabberSes);
		}
	}

	public static void deleteRosterEntries(HttpSession ses, String[] userId)
		throws XMPPException {

		Roster roster = getRoster(ses);

		for (int i = 0; i < userId.length; i++) {
			RosterEntry entry = roster.getEntry(getXmppId(userId[i]));

			roster.removeEntry(entry);
		}
	}

	public static JSONObject getChatMessages(HttpSession ses) {
		JSONArray ja = new JSONArray();
		JSONObject jo = new JSONObject();
		PacketCollector collector = getCollector(ses);
		Message message = getNextMessage(collector);
		Roster roster = getRoster(ses);

		while (message != null) {
			JSONObject jMsg = new JSONObject();
			String fromId = (String)message.getProperty("fromId");

			jMsg.put("body", message.getBody());
			jMsg.put("category", message.getProperty("category"));
			jMsg.put("toId", message.getProperty("toId"));
			jMsg.put("toName", message.getProperty("toName"));
			jMsg.put("fromId", fromId);
			jMsg.put("fromName", message.getProperty("fromName"));
			jMsg.put(
				"status", getPresence(roster.getPresence(getXmppId(fromId))));

			ja.put(jMsg);

			message = getNextMessage(collector);
		}

		jo.put("chat", ja);
		jo.put("status", "success");

		return jo;
	}

	public static PacketCollector getCollector(HttpSession ses) {
		JabberSession jabberSes = (JabberSession)ses.getAttribute(
			WebKeys.JABBER_XMPP_SESSION);

		return jabberSes.getCollector();
	}

	public static XMPPConnection getConnection(HttpSession ses) {
		JabberSession jabberSes = (JabberSession)ses.getAttribute(
			WebKeys.JABBER_XMPP_SESSION);

		return jabberSes.getConnection();
	}

	public static Message getNextMessage(PacketCollector collector) {
		Message message = (Message)collector.pollResult();

		return message;
	}

	public static String getPresence(Presence presence) {
		String status = "unavailable";

		if (presence != null) {
			status = presence.getType().toString();
		}

		return status;
	}

	public static Roster getRoster(HttpSession ses) {
		JabberSession jabberSes = (JabberSession)ses.getAttribute(
			WebKeys.JABBER_XMPP_SESSION);

		return jabberSes.getRoster();
	}

	public static JSONObject getRosterEntries(HttpSession ses) {
		JSONObject jo = new JSONObject();
		Roster roster = getRoster(ses);
		List rosterList = new ArrayList();

		Iterator rosterEntries = roster.getEntries();
		JSONArray ja = new JSONArray();

		while (rosterEntries.hasNext()) {
			RosterEntry entry = (RosterEntry)rosterEntries.next();

			if (entry.getType() != RosterPacket.ItemType.FROM) {
				rosterList.add(entry);
			}
		}

		if (rosterList.size() > 0) {
			Collections.sort(rosterList, new NameComparator());

			for (int i = 0; i < rosterList.size(); i++) {

				JSONObject jEntry = new JSONObject();
				RosterEntry entry = (RosterEntry)rosterList.get(i);

				jEntry.put("user", getUserId(entry));
				jEntry.put("name", entry.getName());
				jEntry.put("status", getPresence(roster
					.getPresence(entry.getUser())));
				ja.put(jEntry);
			}
		}

		jo.put("roster", ja);

		return jo;
	}

	public static String getUserId(RosterEntry entry) {
		String userId = entry.getUser();

		String serverName = GetterUtil.getString(PropsUtil.get(
			PropsUtil.JABBER_XMPP_SERVER_NAME), "localhost");

		userId = StringUtil.replace(
			userId, StringPool.AT + serverName, StringPool.BLANK);

		return userId;
	}

	public static String getXmppId(String userId) {
		String serverName = GetterUtil.getString(PropsUtil.get(
			PropsUtil.JABBER_XMPP_SERVER_NAME), "localhost");

		String xmppId = userId + StringPool.AT + serverName;

		return xmppId;
	}

	public static String getXmppId(User user) {
		String xmppId = getXmppId(String.valueOf(user.getUserId()));

		return xmppId;
	}

	public static boolean isJabberEnabled() {
		return PropsValues.JABBER_XMPP_SERVER_ENABLED;
	}

	public static void sendMessage(
			HttpSession ses, String fromId, String fromName, String toId,
			String toName, String bodyText)
		throws XMPPException {

		XMPPConnection con = getConnection(ses);

		Chat chat = con.createChat(getXmppId(toId));

		Message message = chat.createMessage();

		message.setBody(bodyText);
		message.setProperty("category", "private");
		message.setProperty("fromId", fromId);
		message.setProperty("fromName", fromName);
		message.setProperty("toId", toId);
		message.setProperty("toName", toName);

		chat.sendMessage(message);
	}

}