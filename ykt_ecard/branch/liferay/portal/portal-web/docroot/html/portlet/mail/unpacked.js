RecipientSelector = new Class({

	initialize: function(inputId) {
		var instance = this;

		var textInput = jQuery('#' + inputId);

		textInput.Autocomplete(
			{
				source: function(data) {
					var xHR = jQuery.ajax (
						{
							url: themeDisplay.getPathMain() + "/mail/action",
							data: {cmd: "getRecipients", data: data.value},
							dataType: 'json',
							async: false
						}
					);

					return eval(xHR.responseText);
				},
				delay: 0,
				fx: {
					type: 'slide',
					duration: 400
				},
				autofill: true,
				dataSourceType: 'json',
				helperClass: 'autocomplete-box',
				selectClass: 'autocomplete-selected',
				minchars: 1,
				multiple: true,
				multipleSeparator: ",",
				onSelect: function() {},
				onShow: function() {},
				onHide: function() {}
			}
		);
	}

});

function MailSummaryObject(state, sender, subject, date, size, id, read, folderId, index) {
	this.next = null;
	this.prev = null;
	this.selected = false;
	this.state = state;
	this.id = id;
	this.index = index;
	this.folderId = folderId;
	this.selectedIndex = -1;
	this.read = read;
	this.head = sender;
	this.pendingHighlight = false;
	
	this.row = new Array();
	this.row[0] = state;
	this.row[1] = sender;
	this.row[2] = subject;
	this.row[3] = date;
	this.row[4] = size;
	
	sender.parent = this;
	subject.parent = this;
	date.parent = this;
	size.parent = this;
	
	sender.onmousedown = subject.onmousedown = date.onmousedown = size.onmousedown = Mail.onSummaryMouseDown;
	sender.ondblclick = subject.ondblclick = date.ondblclick = size.ondblclick = Mail.onSummaryDblclick;
}


var Mail = {
	INBOX_NAME : null,
	DRAFTS_NAME : null,
	SENT_NAME : null,
	SPAM_NAME : null,
	TRASH_NAME : null,
	DEFAULT_FOLDERS : null,
	currentFolder : null,
	currentFolderId : "",
	currentMessageId : null,
	displayingMessage : false,
	dragging : false,
	dragIndicator : null,
	dragStart : null,
	foldersList : null,
	groupStart : null,
	lastSelected : null,
	mailObject : null,
	messageTimer : null,
	previewLast: -1,
	previewHeight: 0,
	searchResults : false,
	searchCount : 0,
	selectedArray : null,
	selectedClassName: "portlet-section-selected",
	scrollTimer : null,
	sortBy : null,
	summaryList : { head : null, tail : null },

	buildChain : function(chain, link) {
		if (chain == null) {
			return new Array(link);
		}
		else {
			chain[chain.length] = link;
			return chain;
		}
	},
	
	checkFolderLocation : function(coord, update) {
		var folderPane = document.getElementById("portlet-mail-folder-pane");
		var folderList = folderPane.getElementsByTagName("li");
		var foundInside = false;
		
		for (var i = 0; i < folderList.length; i++) {
			var folderItem = folderList[i];

			if (folderItem.id == "folder_management") {
				continue;
			}
			
			if (update == true) {
				folderItem.nwOffset = Coordinates.northwestOffset(folderItem, true);
				folderItem.seOffset = Coordinates.southeastOffset(folderItem, true);
			}
			
			if (Mail.isMoveAllowed(folderItem.folder.id)) {
				if (coord.inside(folderItem.nwOffset, folderItem.seOffset)) {
						jQuery(folderItem).addClass(Mail.selectedClassName);
						foundInside = true;
				}
				else {
					jQuery(folderItem).removeClass(Mail.selectedClassName);
				}
			}
		}
		
		if (Mail.dragIndicator != null) {
			var indicator = Mail.dragIndicator.getElementsByTagName("span")[0];
			if (foundInside) {
				indicator.innerHTML = "&laquo;";
				indicator.style.color = "#55FF55";
			}
			else {
				indicator.innerHTML = "X";
				indicator.style.color = "#FF5555";
			}
		}
	},
	
	clearPreview : function() {
		if (!Mail.summaryList) {
			return;
		}
		
		var msgsState = document.getElementById("portlet-mail-msgs-state");
		var msgsSender = document.getElementById("portlet-mail-msgs-from");
		var msgsSubject = document.getElementById("portlet-mail-msgs-subject");
		var msgsDate = document.getElementById("portlet-mail-msgs-received");
		var msgsSize = document.getElementById("portlet-mail-msgs-size");
		
		Mail.summaryList.head = null;
		Mail.summaryList.tail = null;
		
		msgsState.innerHTML = "";
		msgsSender.innerHTML = "";
		msgsSubject.innerHTML = "";
		msgsDate.innerHTML = "";
		msgsSize.innerHTML = "";
	},

	decrementCount : function (reverse) {
		var spanList = Mail.currentFolder.li.getElementsByTagName("span");
		
		if (spanList.length > 0) {
			spanList[0].parentNode.removeChild(spanList[0]);
			
			if (reverse) {
				Mail.currentFolder.li.newCount++;
				Mail.currentFolder.newCount++;
			}
			else {
				Mail.currentFolder.li.newCount--;
				Mail.currentFolder.newCount--;
			}
			
			var countNum = Mail.currentFolder.li.newCount;
			
			if (countNum > 0) {
				var element = document.createElement("span");
				element.innerHTML = "&nbsp;(" + countNum + ")";
				element.className = "font-small";
				Mail.currentFolder.li.appendChild(element);
			}
		}
	},
	
	deleteSelectedMessages : function(skipConfirm) {
		clearTimeout(Mail.messageTimer);

		var folderName;
		if (Mail.searchResults) {
			folderName = "search results";
		}
		else {
			folderName = Mail.currentFolder.name;
		}

		var deleteList = Mail.getSelectedMessages();

		var confirmMsg = "Delete " + deleteList.length + " message" +
			(deleteList.length > 1 ? "s" : "") + " from " + folderName + "?";

		if (deleteList.length > 0 && (skipConfirm || confirm(confirmMsg))) {
			loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=deleteMessages&messages=" + deleteList);
			Mail.getFolders();

			Mail.removeSelectedMessages();
			Mail.searchCount -= deleteList.length;
		}
	},

	dragToFolder : function(coord) {
		var folderPane = document.getElementById("portlet-mail-folder-pane");
		var folderList = folderPane.getElementsByTagName("li");
		
		for (var i = 0; i < folderList.length; i++) {
			var folderItem = folderList[i];
			if (folderItem.id == "folder_management") {
				continue;
			}

			var foundFolder = coord.inside(
					Coordinates.northwestOffset(folderItem, true),
					Coordinates.southeastOffset(folderItem, true));
					
			if (foundFolder) {
				Mail.moveToFolder(folderItem.folder.id);
			}
		}
	},

	resetLastSelected : function() {
		Mail.lastSelected = null;
		Mail.groupStart = null;
	},
	
	removeSelectedMessages : function() {
		var detailsFrame = document.getElementById("portlet-mail-msg-detailed-frame");
		var nextObj;
		
		if (Mail.lastSelected == null) {
			Mail.lastSelected = Mail.findLastSelected();
		}
		
		nextObj = Mail.lastSelected.next;
		detailsFrame.src = "";
		
		while (nextObj && nextObj.selected) {
			nextObj = nextObj.next;
		}
		
		Mail.getSelectedMessages(Mail.removeSummary);
		Mail.selectedArray = null;
		Mail.resetLastSelected();
		
		/* Hightlight next message */
		if (nextObj != null) {
			Mail.summaryHighlight(nextObj);
			Mail.groupStart = nextObj;
		}
		else {
			Mail.getFolderDetails();
		}
	},
	
	removeSummary : function(msObj) {
		var nextMs = msObj.next;
		var prevMs = msObj.prev;
		var row = msObj.row;
		
		var sArray = Mail.selectedArray;
		if (sArray != null) {
			sArray[msObj.selectedIndex] = null;
		}
			
		for (var i = 0; i < row.length; i++) {
			var field = row[i];

			field.parentNode.removeChild(field);
			field.onmousedown = null;
			field.next = null;
			field = null;
		}
		
		/* Reconnect doubly-linked list */
		if (nextMs != null) {
			nextMs.prev = prevMs;
		}
		if (prevMs != null) {
			prevMs.next = nextMs;
		}
		
		if (Mail.summaryList.tail == msObj) {
			Mail.summaryList.tail = prevMs;
		}
		if (Mail.summaryList.head == msObj) {
			Mail.summaryList.head = nextMs;
		}
		
		msObj = null;
	},
	
	submitCompose : function(action, form) {
		var selList = Mail.getSelectedMessages();
		
		if (selList.length == 1) {
			document.getElementById("portlet-mail-compose-action").value = action;
			document.getElementById("portlet-mail-folder-id").value = selList[0][0];
			document.getElementById("portlet-mail-message-id").value = selList[0][1];

			submitForm(form);
		}
		else {
			alert("Please select a single message");
		}
	},
	
	getFolderDetails : function() {
		var detailsFrame = document.getElementById("portlet-mail-msg-detailed-frame");
		var mailHeader = document.getElementById("portlet-mail-msg-header-div");
		var folderDiv = document.createElement("div");
		var totalDiv = document.createElement("div");
		var unreadDiv = document.createElement("div");

		if (Mail.searchResults) {
			folderDiv.innerHTML = "Search Results";
			folderDiv.style.fontWeight = "bold";
			folderDiv.className = "font-xx-large";
			totalDiv.innerHTML = Mail.searchCount + "&nbsp;Total";
		}
		else {
			folderDiv.innerHTML = Mail.currentFolder.name;
			folderDiv.style.fontWeight = "bold";
			folderDiv.className = "font-xx-large";
			if (Mail.currentFolder.newCount > 0) {
				unreadDiv.innerHTML = Mail.currentFolder.newCount + "&nbsp;Unread";
			}
			totalDiv.innerHTML = Mail.currentFolder.totalCount + "&nbsp;Total";
		}

		detailsFrame.src = "";
		mailHeader.innerHTML = "";
		mailHeader.appendChild(folderDiv);
		mailHeader.appendChild(unreadDiv);
		mailHeader.appendChild(totalDiv);
	},
	
	emptyFolderReturn : function(xmlHttpReq) {
		var jsonObj = Liferay.Util.toJSONObject(xmlHttpReq.responseText);

		Mail.getFolders();

		if (jsonObj.folderId == Mail.currentFolderId) {
			Mail.getFolderDetails();
			Mail.clearPreview();
		}
	},
	
	findLastSelected : function() {
		var foundLast = null;
		if (Mail.selectedArray != null) {
			var sArray = Mail.selectedArray;
			for (var i = sArray.length - 1; i >= 0; i--) {
				var msObj = sArray[i];
				if (msObj != null && msObj.selected) {
					foundLast = msObj;
					break;
				}
			}
		}
		
		return foundLast;
	},

	getFolders : function(checkMail) {
		loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=getFolders", Mail.getFoldersReturn, checkMail);
	},
	
	getFoldersReturn : function(xmlHttpReq, checkMail) {
		var foldersObject = Liferay.Util.toJSONObject(xmlHttpReq.responseText);
		var folderPane = document.getElementById("portlet-mail-folder-pane");
		var folderList = document.createElement("ul");
		var folders = foldersObject.folders;
		var selectedFolder = null;
		Mail.foldersList = folders;
		
		var animation = folderPane.getElementsByTagName("div");
		if (animation != null && animation.length == 1) {
			folderPane.removeChild(animation[0]);
		}

		var list = folderPane.getElementsByTagName("ul");
		if (list != null && list.length == 1) {
			folderPane.removeChild(list[0]);
		}

		if (!Mail.searchResults) {
			selectedFolder = folders[0];
		}
		
		for (var i = 0; i < folders.length; i++) {
			var folder = folders[i];
			var folderItem = document.createElement("li");
			var folderName = document.createElement("a");
			var newCount = document.createElement("span");
			
			if (folder.newCount > 0) {
				newCount.innerHTML = "&nbsp;(" + folder.newCount + ")";
			}
			newCount.className = "font-small";
			
			folderName.innerHTML = folder.name;
			folderName.appendChild(newCount);
			folderName.href = "javascript:void(0)";
			folderName.onclick = Mail.onFolderSelect;
			
			folderItem.folder = folder;
			folderItem.newCount = folder.newCount;
			
			folderItem.appendChild(folderName);

			if (folder.id == Mail.TRASH_NAME || folder.id == Mail.SPAM_NAME) {
				var emptyFolder = document.createElement("a");
				emptyFolder.href = "javascript:void(0)";
				emptyFolder.className = "font-x-small";
				emptyFolder.innerHTML = "[Empty]";
				emptyFolder.onclick = Mail.onEmptyClick;

				folderItem.appendChild(document.createTextNode(" "));
				folderItem.appendChild(emptyFolder);
			}

			folderList.appendChild(folderItem);
			
			if (folder.id == Mail.currentFolderId) {
				/* Previous folder ID was set */
				selectedFolder = folder;
				jQuery(folderItem).addClass(Mail.selectedClassName);
			}
			
			if (i == Mail.DEFAULT_FOLDERS.length - 1) {
				var manageItem = document.createElement("li");
				manageItem.id = "folder_management";

				var manageIcon = document.createElement("a");
				manageIcon.href = "javascript:void(0)";
				manageIcon.onclick = Mail.onFolderAdd;
				manageIcon.innerHTML = "<img src=\"" + themeDisplay.getPathThemeImages() + "/mail/add_folder.png" + "\" />";
				manageItem.appendChild(manageIcon);
				
				if (Mail.DEFAULT_FOLDERS.length != folders.length) {
					manageIcon = document.createElement("a");
					manageIcon.href = "javascript:void(0)";
					manageIcon.onclick = Mail.onFolderRename;
					manageIcon.innerHTML = "<img src=\"" + themeDisplay.getPathThemeImages() + "/mail/rename_folder.png" + "\" />";
					manageItem.appendChild(manageIcon);

					manageIcon = document.createElement("a");
					manageIcon.href = "javascript:void(0)";
					manageIcon.onclick = Mail.onFolderDelete;
					manageIcon.innerHTML = "<img src=\"" + themeDisplay.getPathThemeImages() + "/mail/delete_folder.png" + "\" />";
					manageItem.appendChild(manageIcon);
				}
				
				folderList.appendChild(manageItem);
			}
		}
		
		folderPane.appendChild(folderList);
		
		if (Mail.searchResults == true) {
			Mail.getFolderDetails();
		}
		else if (Mail.currentFolder == null ||
			Mail.currentFolderId != selectedFolder.id || checkMail) {
			
			Mail.setCurrentFolder(selectedFolder);
			Mail.getPreview();
		}
	},

	getMessageDetails : function(messageId, folderId) {
		if (!Mail.displayingMessage || messageId != Mail.currentMessageId) {
			loadPage(themeDisplay.getPathMain() + "/mail/action",
				"cmd=getMessage&messageId=" + messageId + "&folderId=" + folderId,
				Mail.getMessageDetailsReturn, messageId);
		}
	},

	getMessageDetailsReturn : function(xmlHttpReq, messageId) {
		var mailObject = Liferay.Util.toJSONObject(xmlHttpReq.responseText);

		Mail.currentMessageId = mailObject.id;
		Mail.displayingMessage = true;

		if (Mail.lastSelected != null && !Mail.lastSelected.read) {
			Mail.decrementCount();

			var stateImg = Mail.lastSelected.state.getElementsByTagName("img")[0];
			stateImg.src = themeDisplay.getPathThemeImages() + "/mail/read.png";

			var row = Mail.lastSelected.row;

			for (var i = 0; i < row.length; i++) {
				var field = row[i];
				field.style.fontWeight = "normal";
			}
		
			Mail.lastSelected.read = true;
		}

		var iframe = document.getElementById("portlet-mail-msg-detailed-frame");

		iframe.src = "";
		iframe.src = themeDisplay.getPathMain() + "/mail/view_message?noCache=" + (new Date()).getTime();
		return;
	},
	
	getPreview : function () {
		Mail.clearPreview();
		
		loadPage(themeDisplay.getPathMain() + "/mail/action",
			"cmd=getPreview&folderId=" + Mail.currentFolderId +
			"&sortBy=" + Mail.sortBy.value +
			"&asc=" + Mail.sortBy.asc,
			Mail.getPreviewReturn);
	},
	
	getPreviewReturn : function(xmlHttpReq) {
		var mailObject = Liferay.Util.toJSONObject(xmlHttpReq.responseText);

		Mail.searchResults = false;

		if (mailObject.folderId == Mail.currentFolderId &&
			mailObject.headers.length > 0) {
			Mail.previewLast = -1;
			Mail.mailObject = mailObject;
			Mail.renderPreviewSection();
		}
	},

	getSearchReturn : function(xmlHttpReq) {
		var mailObject = Liferay.Util.toJSONObject(xmlHttpReq.responseText);

		Mail.currentMessageId = null;
		Mail.mailObject = mailObject;
		Mail.searchResults = true;
		Mail.searchCount = mailObject.headers.length;
		Mail.setCurrentFolder();
		Mail.clearPreview();
		Mail.renderPreviewSection();
		Mail.summaryUnhighlightAll();
		Mail.getFolderDetails();
	},

	getSelectedMessages : function(processFunction) {
		var msObj;
		var msgArray = new Array();
		var nextMs;
		var sArray = Mail.selectedArray;
		
		if (sArray != null) {
			for (var i = 0; i < sArray.length; i++) {
				msObj = sArray[i];
				
				if (msObj != null && msObj.selected) {
					msgArray.push(new Array(msObj.folderId, msObj.id));
					
					if (processFunction) {
						processFunction(msObj);
					}
				}
			}
		}

		return(msgArray);
	},
	
	init : function(inbox, drafts, sent, spam, trash) {
		Mail.INBOX_NAME = inbox;
		Mail.DRAFTS_NAME = drafts;
		Mail.SENT_NAME = sent;
		Mail.SPAM_NAME = spam;
		Mail.TRASH_NAME = trash;
		Mail.DEFAULT_FOLDERS = new Array(inbox, drafts, sent, spam, trash);

		/* Vertical main folder bar */
		jQuery("#portlet-mail-folder-pane").lResize({
			handle: "#portlet-mail-handle",
			direction: "horizontal",
			mode: "add",
			onComplete: Mail.updateFolderWidth
		});

		jQuery("#portlet-mail-msgs-preview").lResize({
			handle: "#portlet-mail-handle",
			direction: "horizontal",
			mode: "subtract"
		});
		
		jQuery("#portlet-mail-msg-detailed-pane").lResize({
			handle: "#portlet-mail-handle",
			direction: "horizontal",
			mode: "subtract"
		});

		jQuery("#portlet-mail-msg-header").lResize({
			handle: "#portlet-mail-handle",
			direction: "horizontal",
			mode: "subtract"
		});
		
		/* Horizontal message bar */
		jQuery("#portlet-mail-msgs-preview-pane").lResize({
			handle: "#portlet-mail-msgs-handle",
			direction: "vertical",
			mode: "add",
			onComplete: Mail.updatePreviewHeight
		});

		jQuery("#portlet-mail-msg-detailed-frame").lResize({
			handle: "#portlet-mail-msgs-handle",
			direction: "vertical",
			mode: "subtract"
		});

		/* Preview headers - From */
		jQuery("#portlet-mail-msgs-title-from").lResize({
			handle: "#portlet-mail-msgs-from-handle",
			direction: "horizontal",
			mode: "add",
			onComplete: Mail.updateFromWidth
		});
		
		jQuery("#portlet-mail-msgs-from").lResize({
			handle: "#portlet-mail-msgs-from-handle",
			direction: "horizontal",
			mode: "add"
		});
		
		jQuery("#portlet-mail-msgs-title-subject").lResize({
			handle: "#portlet-mail-msgs-from-handle",
			direction: "horizontal",
			mode: "subtract"
		});
		
		jQuery("#portlet-mail-msgs-subject").lResize({
			handle: "#portlet-mail-msgs-from-handle",
			direction: "horizontal",
			mode: "subtract"
		});

		/* Preview headers - Subject */
		jQuery("#portlet-mail-msgs-title-subject").lResize({
			handle: "#portlet-mail-msgs-subject-handle",
			direction: "horizontal",
			mode: "add",
			onComplete: Mail.updateSubjectWidth
		});
		
		jQuery("#portlet-mail-msgs-subject").lResize({
			handle: "#portlet-mail-msgs-subject-handle",
			direction: "horizontal",
			mode: "add"
		});

		jQuery("#portlet-mail-msgs-title-received").lResize({
			handle: "#portlet-mail-msgs-subject-handle",
			direction: "horizontal",
			mode: "subtract"
		});
		
		jQuery("#portlet-mail-msgs-received").lResize({
			handle: "#portlet-mail-msgs-subject-handle",
			direction: "horizontal",
			mode: "subtract"
		});
		
		/* Preview headers - Received */
		jQuery("#portlet-mail-msgs-title-received").lResize({
			handle: "#portlet-mail-msgs-received-handle",
			direction: "horizontal",
			mode: "add",
			onComplete: Mail.updateReceivedWidth
		});
		
		jQuery("#portlet-mail-msgs-received").lResize({
			handle: "#portlet-mail-msgs-received-handle",
			direction: "horizontal",
			mode: "add"
		});
		
		jQuery("#portlet-mail-msgs-title-size").lResize({
			handle: "#portlet-mail-msgs-received-handle",
			direction: "horizontal",
			mode: "subtract"
		});

		jQuery("#portlet-mail-msgs-size").lResize({
			handle: "#portlet-mail-msgs-received-handle",
			direction: "horizontal",
			mode: "subtract"
		});
		
		/* Bottom handle */
		jQuery("#portlet-mail-msg-detailed-frame").lResize({
			handle: "#portlet-mail-bottom-handle",
			direction: "vertical",
			mode: "add",
			onComplete: Mail.updateDetailedHeight
		});
		
				
		var msgsTitleState = document.getElementById("portlet-mail-msgs-title-state");
		var msgsTitleFrom = document.getElementById("portlet-mail-msgs-title-from");
		var msgsTitleFromHandle = document.getElementById("portlet-mail-msgs-from-handle");
		var msgsTitleSubject = document.getElementById("portlet-mail-msgs-title-subject");
		var msgsTitleSubjectHandle = document.getElementById("portlet-mail-msgs-subject-handle");
		var msgsTitleReceived = document.getElementById("portlet-mail-msgs-title-received");
		var msgsTitleReceivedHandle = document.getElementById("portlet-mail-msgs-received-handle");
		var msgsTitleSize = document.getElementById("portlet-mail-msgs-title-size");
		
		msgsTitleState.asc = true;
		msgsTitleState.value = "state";
		msgsTitleFrom.asc = true;
		msgsTitleFrom.value = "name";
		msgsTitleSubject.asc = true;
		msgsTitleSubject.value = "subject";
		msgsTitleReceived.asc = false;
		msgsTitleReceived.value = "date";
		msgsTitleSize.asc = false;
		msgsTitleSize.value = "size";
		msgsTitleState.onclick = msgsTitleFrom.onclick = msgsTitleSubject.onclick = msgsTitleReceived.onclick = msgsTitleSize.onclick = Mail.onSortClick;
		Mail.sortBy = msgsTitleReceived;
		Mail.updateSortArrow();
		
		jQuery(document).keydown(Mail.onMailKeyPress);
		
		var previewPane = jQuery("#portlet-mail-msgs-preview-pane");
		previewPane[0].onselectstart = function() {return false;}; // ie
		previewPane.mousedown(function() {this.focus(); return false;}); // mozilla
		previewPane.scroll(Mail.onPreviewScroll);

		/* Memory cleanup */
		jQuery(window).unload(Mail.clearPreview);
		
		Mail.getFolders();
	},
	
	isMoveAllowed : function (toFolderId) {
		/* Mail cannot be moved to the same folder
		 * Mail cannot be moved to Drafts
		 * Drafts can only be move to Trash
		 */
		 
		if (Mail.currentFolderId == toFolderId ||
			toFolderId == Mail.DRAFTS_NAME ||
			(Mail.currentFolderId == Mail.DRAFTS_NAME && toFolderId != Mail.TRASH_NAME)) {
			
			return false;
		}
		else {
			return true;
		}
	},

	moveToFolder : function(folderId) {
		var moveList = Mail.getSelectedMessages();
		
		if (moveList.length <= 0) {
			alert("Please select messages to move");
		}
		else if (!Mail.isMoveAllowed(folderId)) {
			alert("You cannot move to " + folderId);
		}
		else {
			confirmMsg = "Move " + moveList.length + " message" +
				(moveList.length > 1 ? "s" : "") + " to " + folderId + "?";

			if (confirm(confirmMsg)) {
				loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=moveMessages&folderId=" + folderId + "&messages=" + moveList);

				Mail.removeSelectedMessages();
				Mail.searchCount -= moveList.length;
				Mail.getFolders();
			}
		}

	},
	
	onEmptyClick : function() {
		folder = this.parentNode.folder;

		confirmMsg = "Are you sure you want to empty the folder " + folder.id + "?";

		if (confirm(confirmMsg)) {
			loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=emptyFolder&folderId=" + folder.id, Mail.emptyFolderReturn);
			Mail.getFolders();
		}
	},
	
	onFolderAdd : function() {
		var entry = prompt("Please enter the name of a new folder.", "");
		
		if (entry != null && entry != "") {
			for (var i = 0; i < Mail.foldersList.length; i++) {
				if (entry.toLowerCase() == Mail.foldersList[i].name.toLowerCase()) {
					alert("The folder '" + Mail.foldersList[i].name + "' already exists.");
					return;
				}
			}
			
			loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=addFolder&folderId=" + entry, Mail.getFolders);
		}
	},
	
	onFolderDelete : function() {
		for (var i = 0 ; i < Mail.DEFAULT_FOLDERS.length; i++) {
			if (Mail.DEFAULT_FOLDERS[i] == Mail.currentFolderId) {
				alert("The folder '" + Mail.currentFolderId + "' cannot be deleted.");
				return;
			}
		}

		if (confirm("Are you sure you want to delete the folder '" + Mail.currentFolderId + "' and all its messages?")) {
			loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=deleteFolder&folderId=" + Mail.currentFolderId, Mail.getFolders);
			Mail.setCurrentFolder(Mail.foldersList[0]);
		}
	},
	
	onFolderRename : function() {
		for (var i = 0 ; i < Mail.DEFAULT_FOLDERS.length; i++) {
			if (Mail.DEFAULT_FOLDERS[i] == Mail.currentFolderId) {
				alert("The folder '" + Mail.currentFolderId + "' cannot be edited.");
				return;
			}
		}
		
		var entry = prompt("Please enter a new name for the folder '" + Mail.currentFolderId + "'.", "");
		
		if (entry != null && entry != "" && entry != Mail.currentFolderId) {
			loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=renameFolder&folderId=" + Mail.currentFolderId + "&newFolderId=" + entry, Mail.getFolders);
		}
	},
	
	onFolderSelect : function() {
		var folder = this.parentNode.folder;

		if (Mail.currentFolderId != folder.id) {
			Mail.searchResults = false;
			Mail.displayingMessage = false;
			Mail.currentMessageId = null;
			
			Mail.setCurrentFolder(folder);
			Mail.getPreview();
		}
	},
	
	onMailKeyPress : function(event) {
		var Key = {
			SHIFT	: 16,
			ESC		: 27,
			UP		: 38,
			DOWN	: 40,
			DELETE	: 46,
			A		: 65,
			D		: 68
		};
		
		if (!event) {
			event = window.event;
		}
		/*
		event.altKey
		event.ctrlKey || event.metaKey
		event.shiftKey 
		*/

		var keycode = event.keyCode;
		
		if ((keycode == Key.UP || keycode == Key.DOWN) &&
			 Mail.summaryList.head != null) {
			 
			var lastObj = Mail.lastSelected;
			var nextObj;
			var prevObj;
			
			if (Mail.lastSelected == null) {
				Mail.lastSelected = Mail.groupStart = Mail.summaryList.head;
				nextObj = prevObj = Mail.lastSelected;
			}
			else if (keycode == Key.DOWN) {
				nextObj = lastObj.next;
				prevObj = lastObj.prev;
			}
			else if (keycode == Key.UP) {
				nextObj = lastObj.prev;
				prevObj = lastObj.next;
			}
			
			if (Mail.groupStart == null) {
				Mail.groupStart = Mail.lastSelected;
			}

			if (event.shiftKey) {
				var action = "";
				
				if (Mail.lastSelected.index < Mail.groupStart.index) {
					if (keycode == Key.DOWN) {
						action = "unhl";
					}
					else {
						action = "hl";
					}
				}
				else if (Mail.lastSelected.index > Mail.groupStart.index) {
					if (keycode == Key.UP) {
						action = "unhl";
					}
					else {
						action = "hl"
					}
				}
				else {
					action = "hl"
				}
				
				if (action == "hl" && nextObj) {
					Mail.summaryHighlight(nextObj, true);
				}
				else if (action == "unhl") {
					Mail.summaryUnhighlight(Mail.lastSelected);
					Mail.lastSelected = nextObj;
				}
				
			}
			else if (nextObj) {
				Mail.summaryUnhighlightAll();
				Mail.summaryHighlight(nextObj, event.shiftKey);
				Mail.groupStart = Mail.lastSelected;
			}
			
			Mail.scrollToSelected();
			return false;
		}
		else if (keycode == Key.DELETE) {
			Mail.deleteSelectedMessages();
		}
		else if (keycode == Key.ESC) {
			Mail.summaryUnhighlightAll();
			Mail.getFolderDetails();
		}
		else if (event.ctrlKey || event.metaKey) {
			if (keycode == Key.A) {
				Mail.summaryHighlightAll();
				return false;
			}
			if (keycode == Key.D) {
				Mail.deleteSelectedMessages(true);
			}
		}
	},
	
	onMessageSelect : function() {
		alert(this.id);
	},
	
	onMoveFolderChange : function() {
		if (this.selectedIndex != 0) {
			Mail.moveToFolder(this.options[this.selectedIndex].innerHTML);
		}
		
		this.selectedIndex = 0;
	},
	
	onPreviewScroll : function() {
		if (this.scrollTimer) {
			clearTimeout(this.scrollTimer);
		}
		
		this.scrollTimer = setTimeout("Mail.renderPreviewSection()", 500);
	},
	
	onSortClick : function() {
		if (Mail.sortBy == this) {
			this.asc = this.asc ? false : true;
		}

		Mail.sortBy = this;
		Mail.updateSortArrow();

		if (Mail.searchResults == true) {
			loadPage(themeDisplay.getPathMain() + "/mail/action", 
				"cmd=getSearchCached" +
				"&sortBy=" + Mail.sortBy.value +
				"&asc=" + Mail.sortBy.asc,
				Mail.getSearchReturn);
		}
		else {
			Mail.getPreview();
		}
	},
	
	onSummaryDblclick : function() {
		msObj = this.parent;
		if (Mail.currentMessageId == msObj.id) {
			Mail.previewPopup();
		}
	},
	
	onSummaryMouseDown : function(event) {
		event = mousePos.update(event);

		var obj = this;
		var msObj = obj.parent;
		
		msObj.pendingHighlight = true;
		Mail.lastSelected = msObj;
		
		document.onmousemove = Mail.onSummaryMouseMove;
		document.onmouseup = Mail.onSummaryMouseUp;

		Mail.dragStart = new Coordinate(mousePos.x, mousePos.y);
		Mail.checkFolderLocation(mousePos, true);

		return false;
	},
	
	onSummaryMouseMove : function(event) {
		mousePos.update(event);
		
		var numOfSelected = Mail.getSelectedMessages().length;
		
		if ((numOfSelected > 0 && mousePos.distance(Mail.dragStart) > 20) || Mail.dragging) {
			Mail.dragging = true;
			Mail.lastSelected.pendingHighlight = false;
			
			var dragIndicator = Mail.dragIndicator;
			
			if (dragIndicator == null) {
				dragIndicator = document.createElement("div");
				document.getElementsByTagName("body")[0].appendChild(dragIndicator);
				dragIndicator.id = "portlet-mail-drag-indicator";
				dragIndicator.onselectstart = function() {return false;};
				dragIndicator.onmousedown = function() {return false;};
				Mail.dragIndicator = dragIndicator;
			}
			
			dragIndicator.innerHTML = "<span>&nbsp;</span>&nbsp;" + numOfSelected + " message" +
				(numOfSelected != 1 ? "s" : "");
			dragIndicator.style.display = "block";
			dragIndicator.style.top = (mousePos.y - 15) + "px";
			dragIndicator.style.left = (mousePos.x - 5) + "px";
			
			Mail.checkFolderLocation(mousePos);
		}
	},
	
	onSummaryMouseUp : function(event) {
		event = mousePos.update(event);
		
		var dragIndicator = Mail.dragIndicator;
		if (dragIndicator != null) {
			dragIndicator.style.display = "none";
		}
		
		if (Mail.lastSelected.pendingHighlight) {
			if (event.ctrlKey || event.metaKey) {
				if (Mail.lastSelected.selected) {
					/* Toggle if selected */
					Mail.summaryUnhighlight(Mail.lastSelected);
					Mail.resetLastSelected();
				}
				else {
					Mail.summaryHighlight(Mail.lastSelected, true);
					Mail.groupStart = Mail.lastSelected;
				}
			}
			else if (event.shiftKey) {
				if (Mail.groupStart == null) {
					/* Try to find group */
					Mail.groupStart = Mail.findLastSelected();
				}
				
				Mail.summaryHighlight(Mail.lastSelected, true);

				if (Mail.groupStart == null) {
					/* Unable to find group start. Set to current */
					Mail.groupStart = Mail.lastSelected;
				}
				else {
					var nextObj;
					var searchDown = true;
					var lastSelected = Mail.lastSelected;
					
					if (Mail.lastSelected.index > Mail.groupStart.index) {
						searchDown = false;
					}
					
					nextObj = searchDown ? Mail.lastSelected.next : Mail.lastSelected.prev;
					
					while (nextObj != Mail.groupStart) {
						Mail.summaryHighlight(nextObj, event.shiftKey);
						nextObj = searchDown ? nextObj.next : nextObj.prev;
					}
					
					Mail.lastSelected = lastSelected;
				}
			}
			else {
				Mail.summaryUnhighlightAll();
				Mail.groupStart = Mail.lastSelected;
				Mail.summaryHighlight(Mail.lastSelected);
			}
		}
		
		document.onmousemove = null;
		document.onmouseup = null;
		
		
		if (Mail.dragging) {
			//Mail.checkFolderLocation(new Coordinate());
			Mail.dragToFolder(mousePos);
			Mail.dragging = false;
		}
	},
	
	print : function() {
		var printWindow = Mail.previewPopup();
			
		if (printWindow != null && printWindow.print) {
			printWindow.print();
		}
		else {
			alert("Please select a message");
		}
	},
	
	previewPopup : function() {
		var popup = null;
		
		if (Mail.currentMessageId) {
			var frameSrc = themeDisplay.getPathMain() + "/mail/view_message?header=true&messageId=" + Mail.currentMessageId;
			popup = window.open(frameSrc, "Print", "menubar=yes,width=640,height=480,toolbar=no,resizable=yes,scrollbars=yes");
		}
		
		return popup;
	},
	
	renderPreviewSection : function() {
		var mailObject = Mail.mailObject;
		var totalMsgs = mailObject.headers.length;

		var msgsState = document.getElementById("portlet-mail-msgs-state");
		var msgsSender = document.getElementById("portlet-mail-msgs-from");
		var msgsSubject = document.getElementById("portlet-mail-msgs-subject");
		var msgsDate = document.getElementById("portlet-mail-msgs-received");
		var msgsSize = document.getElementById("portlet-mail-msgs-size");
		var summaryList = Mail.summaryList;
		
		var SECTION_SIZE = 25;
		var begin = Mail.previewLast + 1;
		var end = 25;

		if (Mail.previewHeight) {
			var previewPane = document.getElementById("portlet-mail-msgs-preview-pane");
			end = Math.ceil(previewPane.scrollTop / Mail.previewHeight) + 25;
			if (end > (totalMsgs - 1)) {
				end = totalMsgs - 1;
			}
			if (end <= Mail.previewLast) {
				return;
			}
		}

		for (var i = begin; i <= end; i++) { 
			var header = mailObject.headers[i];
			var state = document.createElement("div");
			var stateImg = document.createElement("img");
			var sender = document.createElement("div");
			var subject = document.createElement("div");
			var date = document.createElement("div");
			var size = document.createElement("div");
			var msObj = new MailSummaryObject(state, sender, subject, date, size, header.id, header.read, header.folderId, i);

			stateImg.src = themeDisplay.getPathThemeImages() + "/mail/read.png";
			sender.innerHTML = header.email;
			date.innerHTML = header.date;
			size.innerHTML = header.size;
			subject.innerHTML = header.subject;

			if (Mail.searchResults) {
				subject.innerHTML = "<span class='portlet-mail-folder-text'>" + header.folderId + "</span>" + subject.innerHTML;
			}
			
			if (!header.read) {
				stateImg.src = themeDisplay.getPathThemeImages() + "/mail/unread.png";

				sender.style.fontWeight = "bold";
				subject.style.fontWeight = "bold";
				date.style.fontWeight = "bold";
				size.style.fontWeight = "bold";
			}
			else if (header.replied) {
				stateImg.src = themeDisplay.getPathThemeImages() + "/mail/replied.png";
			}
			
			if (summaryList.head == null) {
				summaryList.head = msObj;
				summaryList.tail = summaryList.head;
			}
			else {
				summaryList.tail.next = msObj;
				msObj.prev = summaryList.tail;
				summaryList.tail = msObj;
			}

			state.appendChild(stateImg);
			msgsState.appendChild(state);
			msgsSender.appendChild(sender);
			msgsSubject.appendChild(subject);
			msgsDate.appendChild(date);
			msgsSize.appendChild(size);
			
			if (Mail.currentMessageId == msObj.id) {
				/* Previous message selected */
				Mail.summaryHighlight(msObj);
				Mail.lastSelected = msObj;
				Mail.scrollToSelected();
			}
		}
		
		if (end < (totalMsgs - 1)) {
			var rowHeight = summaryList.head.head.offsetHeight;
			Mail.previewHeight = rowHeight;
			msgsSender.style.height = (totalMsgs * rowHeight) + "px";
			//setTimeout("Mail.renderPreviewSection(" + (count + 1) + ")", 1);
		}
		else {
			msgsSender.style.height = "auto";
		}
		
		Mail.previewLast = end;
	},

	scrollToSelected : function() {
		var element = Mail.lastSelected.row[1];
		
		if (element) {
			var previewPane = document.getElementById("portlet-mail-msgs-preview-pane");
			var previewTitle = document.getElementById("portlet-mail-msgs-preview-pane-title");
			
			var paneTop = Coordinates.southeastOffset(previewTitle, true).y;
			var paneBottom = paneTop + previewPane.offsetHeight;
			
			var elTop = Coordinates.northwestOffset(element, true).y - previewPane.scrollTop;
			var elBottom = elTop + element.offsetHeight;
	
			if (elTop < paneTop) {
				previewPane.scrollTop -= paneTop - elTop;
			}
			
			if (elBottom > paneBottom) {
				previewPane.scrollTop += (elBottom - paneBottom);
			}
		}
	},

	setCurrentFolder : function(folder) {
		Mail.currentFolder = folder;

		if (folder != null) {
			Mail.currentFolderId = folder.id;
			Mail.getFolderDetails();
		}
		else {
			Mail.currentFolderId = null;
		}
		
		var folderPane = document.getElementById("portlet-mail-folder-pane");
		var folderList = folderPane.getElementsByTagName("li");
		
		for (var i = 0; i < folderList.length; i++) {
			var folderItem = folderList[i];
			
			if (folderItem.id == "folder_management") {
				continue;
			}
			else if (Mail.currentFolderId == folderItem.folder.id) {
				jQuery(folderItem).addClass(Mail.selectedClassName);
				Mail.currentFolder.li = folderItem;
			}
			else {
				jQuery(folderItem).removeClass(Mail.selectedClassName);
			}
		}

		var fromTitleText = document.getElementById("portlet-mail-msgs-title-from");
		var fromTitle = fromTitleText.getElementsByTagName("span");
		var mainToolbar = document.getElementById("portlet-mail-main-toolbar");
		var draftsToolbar = document.getElementById("portlet-mail-drafts-toolbar");
		var emptyFolder = document.getElementById("portlet-mail-empty-folder");

		if (folder == null) {
			fromTitle[0].style.display = "none";
			fromTitle[1].style.display = "none";
			fromTitle[2].style.display = "";
		}
		else if (Mail.currentFolderId == Mail.SENT_NAME || Mail.currentFolderId == Mail.DRAFTS_NAME) {
			fromTitle[0].style.display = "none";
			fromTitle[1].style.display = "";
			fromTitle[2].style.display = "none";
		}
		else {
			fromTitle[0].style.display = "";
			fromTitle[1].style.display = "none";
			fromTitle[2].style.display = "none";
		}
		
		if (Mail.currentFolderId == Mail.DRAFTS_NAME) {
			mainToolbar.style.display = "none";
			draftsToolbar.style.display = "block";
		}
		else {
			mainToolbar.style.display = "block";
			draftsToolbar.style.display = "none";
		}
	},
	
	summaryHighlight : function(msObj, skipDetails, setOff) {
		
		msObj.pendingHighlight = false;
		
		if (Mail.messageTimer) {
			clearTimeout(Mail.messageTimer);
		}
		
		if (setOff == true) {
			/* Unhighlight & unselect */
			msObj.selected = false;
			
			if (msObj.selectedIndex >= 0) {
				Mail.selectedArray[msObj.selectedIndex] = null;
				msObj.selectedIndex = -1;
			}
		}
		else {
			/* Highlight & select */
			msObj.selected = true;
			Mail.lastSelected = msObj;

			if (Mail.selectedArray == null) {
				Mail.selectedArray = new Array();
			}

			msObj.selectedIndex = (Mail.selectedArray.push(msObj)) - 1;

			if (!skipDetails) {
				Mail.messageTimer = setTimeout("Mail.getMessageDetails("+msObj.id+",'"+msObj.folderId+"')", 500);
			}
		}
		
		var row = msObj.row;
		for (var i = 0; i < row.length; i++) {
			if (setOff) {
				jQuery(row[i]).removeClass(Mail.selectedClassName);
			}
			else {
				jQuery(row[i]).addClass(Mail.selectedClassName);
			}
		}
	},
	
	summaryHighlightAll : function() {
		var msObj = Mail.summaryList.head;
		
		while (msObj) {
			Mail.summaryHighlight(msObj, true);
		}
	},
	
	summaryUnhighlight : function(msObj) {
		Mail.summaryHighlight(msObj, null, true);
	},
	
	summaryUnhighlightAll : function() {
		var msObj = Mail.summaryList.head;
		var sArray = Mail.selectedArray;
		
		if (sArray != null) {
			for (var i = 0; i < sArray.length; i++) {
				if (sArray[i] != null) {
					Mail.summaryUnhighlight(sArray[i]);
				}
			}
		}
		
		Mail.selectedArray = null;
	},
	
	updateDetailedHeight : function(keychain, valuechain) {
		var detailedFrame = document.getElementById("portlet-mail-msg-detailed-frame");

		keychain = Mail.buildChain(keychain, "detailed-frame-height");
		valuechain = Mail.buildChain(valuechain, detailedFrame.style.height);
		
		Mail.updatePreferences(keychain, valuechain);
	},

	updateFolderWidth : function() {
		var folderPane = document.getElementById("portlet-mail-folder-pane");
		Mail.updatePreferences("folder-pane-width", folderPane.style.width);
	},

	updateFromWidth : function() {
		var fromTitle = document.getElementById("portlet-mail-msgs-title-from");
		Mail.updateSubjectWidth(new Array("from-title-width"), new Array(fromTitle.style.width));
	},
	
	updateSubjectWidth : function(keychain, valuechain) {
		var subjectTitle = document.getElementById("portlet-mail-msgs-title-subject");

		keychain = Mail.buildChain(keychain, "subject-title-width");
		valuechain = Mail.buildChain(valuechain, subjectTitle.style.width);

		Mail.updateReceivedWidth(keychain, valuechain);
	},
	
	updateReceivedWidth : function(keychain, valuechain) {
		var receivedTitle = document.getElementById("portlet-mail-msgs-title-received");

		keychain = Mail.buildChain(keychain, "received-title-width");
		valuechain = Mail.buildChain(valuechain, receivedTitle.style.width);

		Mail.updatePreferences(keychain, valuechain);
	},

	updatePreferences : function(key, value) {
		loadPage(themeDisplay.getPathMain() + "/mail/action", "cmd=updatePreferences&key=" + key + "&value=" + value);
	},
	
	updatePreviewHeight : function() {
		var previewPane = document.getElementById("portlet-mail-msgs-preview-pane");
		Mail.updateDetailedHeight(new Array("preview-pane-height"), new Array(previewPane.style.height));
	},

	updateSortArrow : function() {
		var sortTitles = new Array();
		sortTitles[0] = document.getElementById("portlet-mail-msgs-title-from");
		sortTitles[1] = document.getElementById("portlet-mail-msgs-title-subject");
		sortTitles[2] = document.getElementById("portlet-mail-msgs-title-received");
		sortTitles[3] = document.getElementById("portlet-mail-msgs-title-size");
		
		for (var i = 0; i < sortTitles.length; i++) {
			var title = sortTitles[i];
			var titleDiv = title.getElementsByTagName("div")[0];
			var imageList = titleDiv.getElementsByTagName("img");
			var image;
			
			if (imageList.length > 0) {
				image = imageList[0];
				titleDiv.removeChild(image);
			}
			
			if (Mail.sortBy == title && title != "state") {
				image = document.createElement("img");
				
				if (title.asc) {
					image.src = themeDisplay.getPathThemeImages() + "/arrows/01_up.png";
				}
				else {
					image.src = themeDisplay.getPathThemeImages() + "/arrows/01_down.png";
				}
				
				titleDiv.appendChild(image);
			}
		}
	}
}