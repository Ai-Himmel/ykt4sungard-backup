var Messaging = {
	checkRoster : false,
	currentChatBox : null,
	initialized : false,
	inputCount : 1,
	mainDiv : null,
	msgQueue : [],
	userId : null,
	windowCount : 0,
	zIndex : 1,

	chat : function(msgObj) {
		if (!msgObj && Messaging.msgQueue.length == 0) return;

		var msg = msgObj || Messaging.msgQueue.shift();
		var toDivId = msg.toId.replace(/\./g, "_");
		var chatBox = jQuery("#msg-chat-box_" + toDivId)[0];

		if (!chatBox) {
			var contents =
				"<div class='chat-box' id='msg-chat-box_" + toDivId + "'>" +
					"<input class='to-input-id' type=hidden value='" + msg.toId + "' />" +
					"<div class='chat-area textarea' style='overflow: auto; height: 100px'>" +
						(msg.messages || "") +
					"</div>" +
					"<input class='type-area' style='width: 90%; margin-top: 5px' tabIndex=1 type='text' onKeyPress='Messaging.sendChat(this, event)' />" +
				"</div>";

			chatBox = Liferay.Popup({
				title: msg.toName,
				message: contents,
				noCenter: true,
				width: 300,
				onClose: function() { Messaging.saveCookie(); }
			});

			if (msg.status && msg.status == "unavailable") {
				jQuery(chatBox).append(
					"<img src='" + themeDisplay.getPathThemeImages() + "/chat/add_user.png' " +
						"style='cursor: pointer; margin-top: 2px' " +
						"onclick=\"MessagingRoster.addEntry('" + msg.toId + "'); jQuery(this).remove()\"" +
					"/>"
				);
			}

			Messaging.populateChatBox(chatBox, msg);

			if (msg.top != null && msg.left != null) {
				jQuery(chatBox).parents(".popup:first").css({
					top: msg.top + "px",
					left: msg.left + "px"
				});
			}
			else {
				var count = Liferay.Popup.count();

				jQuery(chatBox).parents(".popup:first").css({
					top: (count * 10) + "px",
					left: (count * 10) + "px"
				});
			}
		}
		else {
			this.populateChatBox(chatBox, msg);
		}
	},

	populateChatBox : function(chatBox, msg) {
		var typeArea = jQuery.getOne(".type-area", chatBox);
		var chatArea = jQuery.getOne(".chat-area", chatBox);

		if (msg.body != null) {
			var name = msg.toName.split(/[ ,.-]/);
			var initials = "";
			for (var i = 0; i < name.length; i++) {
				initials += name[i].charAt(0);
			}
			chatArea.innerHTML += "<span style='color: #FF0000'>" + initials + ": </span>" + msg.body + "<br/>";
			this.saveCookie();
		}

		chatArea.scrollTop = chatArea.scrollHeight;
		typeArea.focus();

		if (Liferay.Browser.is_ie) {
			// need double focus for IE
			typeArea.focus();
		}

		Messaging.chat();
	},

	getChats : function() {
		var url = themeDisplay.getPathMain() + "/messaging/action?cmd=getChats";
		AjaxUtil.request(url, {
			onComplete: function(xmlHttpReq) {
				var msg = eval("(" + xmlHttpReq.responseText + ")");
				Messaging.getChatsReturn(msg);
			}
		});
	},

	getChatsReturn : function(msg) {
		var status = msg.status;

		if (status == "success") {
			var chatMsg = msg.chat;
			if (chatMsg && chatMsg.length > 0) {
				for (var i = 0; i < chatMsg.length; i++) {
					// swap "from" and "to"
					var tmpName = chatMsg[i].fromName;
					var tmpId = chatMsg[i].fromId;
					chatMsg[i].fromName = chatMsg[i].toName;
					chatMsg[i].fromId = chatMsg[i].toId;
					chatMsg[i].toName = tmpName;
					chatMsg[i].toId = tmpId;
					Messaging.msgQueue.push(chatMsg[i]);
				}
				Messaging.chat();
				window.focus();
			}
		}
	},

	error : function() {
		alert("User does not exist");
	},

	init : function(userId) {
		var body = document.getElementsByTagName("body")[0];
		this.userId = userId;

		var msgJSON = jQuery.cookie(this.userId + "_chats");

		if (msgJSON) {
			var chatArray = eval("(" + msgJSON + ")");

			for (var i = 0; i < chatArray.length; i++) {
				Messaging.msgQueue.push(chatArray[i]);
			}

			Messaging.chat();
		}

		this.initialized = true;
		Messaging.getChats();
	},

	maximizeChat : function(id) {
		var chatBox = jQuery.getOne(id);
		var widthDiv = jQuery.getOne(".chat-box-width");
		var chatArea = jQuery.getOne(".chat-area");

		chatBox.style.left = Viewport.scroll().x + "px";
		chatBox.style.top = Viewport.scroll().y + "px";
		widthDiv.style.width = (Viewport.frame().x - 30) + "px";
		chatArea.style.height = (Viewport.frame().y - 100) + "px";
	},

	minimizeChat : function(id) {
		var chatBox = jQuery.getOne(id);
		var widthDiv = jQuery.getOne(".chat-box-width");
		var chatArea = jQuery.getOne(".chat-area");

		widthDiv.style.width = 250 + "px";
		chatArea.style.height = 100 + "px";
	},

	removeChat : function(id) {
		var chatBox = jQuery.getOne(id);

		Element.remove(chatBox);
		this.saveCookie();
	},

	saveCookie : function() {
		var chatList = jQuery(".chat-box");
		var jsonString = "[";

		chatList.each(function(i){
			var item = this;
			var popup = jQuery(item).parents(".popup:first");

			jsonString += "{"
				+ "toName:\"" + popup.find(".popup-title")[0].innerHTML + "\","
				+ "toId:\"" +jQuery(".to-input-id", item)[0].value + "\","
				+ "top:" + parseInt(popup.css("top")) + ","
				+ "left:" + parseInt(popup.css("left")) + ","
				+ "messages:\"" + Liferay.Util.toJSONString(jQuery(".chat-area", item)[0].innerHTML) + "\"}";

			if (i < chatList.length - 1) {
				jsonString += ",";
			}
		});
		jsonString += "]";

		jQuery.cookie(this.userId + "_chats", jsonString);
	},

	sendChat : function(obj, e) {
		var keycode;
		var chatBox = obj.parentNode;
		var toInput;
		var toAddr;
		var typeArea;
		var chatArea;
		var query = "cmd=sendChat";

		if (window.event) keycode = window.event.keyCode;
		else if (e) keycode = e.which;
		else return;

		if (keycode == 13) {
			var inputList = chatBox.getElementsByTagName("input");

			for (var i = 0; i < inputList.length ; i++) {
				if (inputList[i].className) {
					if (inputList[i].className.match("msg-to-input-id")) toInput = inputList[i];
					if (inputList[i].className.match("msg-to-input-addr")) toAddr = inputList[i];
					if (inputList[i].className.match("msg-type-area")) typeArea = inputList[i];
				}
			}

			if (typeArea.value == "") return;

			var divList = chatBox.getElementsByTagName("div");
			for (var i = 0; i < divList.length ; i++) {
				if (divList[i].className && divList[i].className.match("msg-chat-area")) chatArea = divList[i];
			}

			query += "&text=" + encodeURIComponent(typeArea.value);

			if (toAddr != null) {
				query += "&tempId=" + toInput.value + "&toAddr=" + toAddr.value;
			}
			else {
				query += "&toId=" + toInput.value;
			}

			loadPage(themeDisplay.getPathMain() + "/messaging/action", query, Messaging.sendChatReturn);

			chatArea.innerHTML += "<span style='color: #0000FF'>Me: </span>" + typeArea.value + "<br/>";
			chatArea.scrollTop = chatArea.scrollHeight;
			typeArea.value = "";

			Messaging.saveCookie();
		}
	},

	sendChatReturn : function(xmlHttpReq) {
		var msg = eval("(" + xmlHttpReq.responseText + ")");

		if (msg.status == "success") {
			Messaging.populateChatBox(msg);
		}
		else {
			Messaging.error();
		}
	}
};

var MessagingRoster = {
	highlightColor : "",
	lastSelected : null,

	addEntry : function(userId) {
		var url;

		if (userId) {
			url = themeDisplay.getPathMain() + "/chat/roster?cmd=addEntry&userId=" + userId;
		}
		else {
			var email = jQuery.getOne("#portlet-chat-roster-email").value;
			url = themeDisplay.getPathMain() + "/chat/roster?cmd=addEntry&email=" + email
		}

		AjaxUtil.request(url, {onComplete: MessagingRoster.addEntryReturn});
	},

	addEntryReturn : function(xmlHttpReq) {
		try {
			var msg = eval("(" + xmlHttpReq.responseText + ")");

			if (msg.status == "failure") {
				alert("No such user exists");
			}
			else {
				var rosterDiv = jQuery.getOne("#portlet-chat-roster-list");

				if (rosterDiv) {
					var entries = jQuery(".portlet-chat-roster-entry", rosterDiv);
					var userId = msg.user;

					var userExists = entries.filter(function(i){
						return(this.userId == userId);
					});

					if (userExists.length != 0) {
						var entryRow = MessagingRoster.createEntryRow(msg.user, msg.name);

						rosterDiv.appendChild(entryRow);
					}

					MessagingRoster.toggleEmail();
				}
			}
		}
		catch (err) {
		}
	},

	createEntryRow : function (userId, userName, online) {
			var tempDiv = document.createElement("div");
			var tempImg = document.createElement("img");
			var tempLink = document.createElement("a");
			tempImg.align = "absmiddle";
			tempImg.style.marginRight = "5px";

			if (online) {
				tempImg.src = themeDisplay.getPathThemeImages() + "/chat/user_online.png";
			}
			else {
				tempImg.src = themeDisplay.getPathThemeImages() + "/chat/user_offline.png";
			}

			tempLink.innerHTML = userName;
			tempLink.href = "javascript: void(0)";
			tempLink.onclick = MessagingRoster.onEntryLinkClick;

			tempDiv.appendChild(tempImg);
			tempDiv.appendChild(tempLink);
			tempDiv.onclick = MessagingRoster.onEntryClick;
			tempDiv.userId = userId;
			tempDiv.userName = userName;
			tempDiv.style.cursor = "pointer";
			tempDiv.className = "portlet-chat-roster-entry";

			return tempDiv;
	},

	deleteEntries : function () {
		if (MessagingRoster.lastSelected) {
			var userId = MessagingRoster.lastSelected.userId;
			var lastSelected = MessagingRoster.lastSelected;

			lastSelected.parentNode.removeChild(lastSelected);
			MessagingRoster.lastSelected = null;

			loadPage(themeDisplay.getPathMain() + "/chat/roster", "cmd=deleteEntries&entries=" + userId, MessagingRoster.deleteEntriesReturn);
		}
	},

	deleteEntriesReturn : function (xmlHttpReq) {
		try {
			var msg = eval("(" + xmlHttpReq.responseText + ")");
		}
		catch (err) {
		}
	},

	getEntries : function() {
		var url = themeDisplay.getPathMain() + "/chat/roster?cmd=getEntries";
		AjaxUtil.request(url, {
			onComplete: function(xmlHttpReq) {
				var msg = eval("(" + xmlHttpReq.responseText + ")");
				MessagingRoster.getEntriesReturn(msg);
			}
		});
	},

	getEntriesReturn : function(msg) {
		MessagingRoster.updateEntries(msg.roster);
	},

	updateEntries : function(roster) {
		var rosterDiv = jQuery.getOne("#portlet-chat-roster-list");

		if (rosterDiv != null) {
			rosterDiv.innerHTML = "";
		}
		else {
			Messaging.checkRoster = false;
			return;
		}

		for (var i = 0; i < roster.length; i++) {
			var entry = roster[i];
			var tempDiv =
				MessagingRoster.createEntryRow(
					entry.user,
					entry.name,
					entry.status == "available"
				);
			rosterDiv.appendChild(tempDiv);
		}
	},

	onEmailKeypress : function (obj, event) {
		var keyCode;

		if (window.event) keyCode = window.event.keyCode;
		else if (event) keyCode = event.which;
		else return;

		if (keyCode == 13) {
			MessagingRoster.addEntry();
		}
	},

	onEntryClick : function () {
		if (MessagingRoster.lastSelected != null) {
			MessagingRoster.lastSelected.style.backgroundColor = "transparent";
		}

		this.style.backgroundColor = MessagingRoster.highlightColor;

		MessagingRoster.lastSelected = this;
	},

	onEntryLinkClick : function () {
		var parent = this.parentNode;
		Messaging.chat({toId: parent.userId, toName: parent.userName});
	},

	toggleEmail : function() {
		var emailDiv = jQuery.getOne("#portlet-chat-roster-email-div");

		if (emailDiv.style.display == "none") {
			emailDiv.style.display = "block";

			emailInput = jQuery.getOne("#portlet-chat-roster-email");
			emailInput.value = "";
			emailInput.focus();
		}
		else {
			emailDiv.style.display = "none";
		}
	}
};
