Liferay.Util = {
	submitCountdown: 0,

	actsAsAspect: function(object) {
		object.yield = null;
		object.rv = {};

		object.before = function(method, f) {
			var original = eval("this." + method);

			this[method] = function() {
				f.apply(this, arguments);

				return original.apply(this, arguments);
			};
		};

		object.after = function(method, f) {
			var original = eval("this." + method);

			this[method] = function() {
				this.rv[method] = original.apply(this, arguments);

				return f.apply(this, arguments);
			};
		};

		object.around = function(method, f) {
			var original = eval("this." + method);

			this[method] = function() {
				this.yield = original;

				return f.apply(this, arguments);
			};
		};
	},

	addInputFocus: function(el) {
		var item = null;

		if (el) {
			if (typeof el == 'object') {
				item = jQuery(el);
			}
			else {
				item = jQuery('#' + el);
			}
		}
		else {
			item = document.body;
		}

		var inputs = jQuery("input[@type=text], input[@type=password], textarea", item);

		inputs.focus(
			function() {
				jQuery(this).addClass('focus');

				if (this.createTextRange) {
					var value = this.value;
					var textRange = this.createTextRange();

					textRange.moveStart('character', value.length);
					textRange.select();
				}
			}
		);

		inputs.blur(
			function() {
				jQuery(this).removeClass('focus');
			}
		);
	},

	addInputType: function(el) {
		var item;

		if (jQuery.browser.msie && jQuery.browser.version.number() < 7) {
			if (el) {
				if (typeof el == 'object') {
					item = jQuery(el);
				}
				else {
					item = jQuery('#' + el);
				}
			}
			else {
				item = document.body;
			}

			jQuery("input", item).each(function() {
				var current = jQuery(this);
				var type = this.type || "text";

				current.addClass(type);
			});
		}
	},

	addParams: function(params, url) {
		var instance = this;

		if (typeof params == 'object') {
			params = jQuery.param(params);
		}
		else {
			params = jQuery.trim(params);
		}

		if (params != '') {
			var loc = url || location.href;
			var anchorHash, finalUrl;

			if (loc.indexOf('#') > -1) {
				var locationPieces = loc.split('#');
				loc = locationPieces[0];
				anchorHash = locationPieces[1];
			}

			if (loc.indexOf('?') == -1) {
				params = '?' + params;
			}
			else {
				params = '&' + params;
			}

			if (loc.indexOf(params) == -1) {
				finalUrl = loc + params;

				if (anchorHash) {
					finalUrl += '#' + anchorHash;
				}
				if (!url) {
					location.href = finalUrl;
				}
				return finalUrl;
			}
		}
	},

	check: function(form, name, checked) {
		jQuery('input[@name=' + name + ']:checkbox',form).attr('checked', checked);
	},

	checkAll: function(form, name, allBox) {
		var inputs;

		if (Liferay.Util.isArray(name)) {
			var names = 'input[@name='+ name.join(']:checkbox,input[@name=') + ']:checkbox';

			inputs = jQuery(names, form);
		}
		else {
			inputs = jQuery('input[@name=' + name + ']:checkbox', form);
		}

		inputs.attr('checked', allBox.checked);
	},

	checkAllBox: function(form, name, allBox) {
		var totalBoxes = 0;
		var totalOn = 0;
		var inputs;

		if (Liferay.Util.isArray(name)) {
			var names = 'input[@name='+ name.join(']:checkbox,input[@name=') + ']:checkbox';

			inputs = jQuery(names, form);
		}
		else {
			inputs = jQuery('input[@name=' + name + ']:checkbox', form);
		}

		inputs = inputs.not(allBox);

		totalBoxes = inputs.length;
		totalOn = inputs.filter(':checked').length;

		allBox.checked = (totalBoxes == totalOn);
	},

	checkMaxLength: function(box, maxLength) {
		if ((box.value.length) >= maxLength) {
			box.value = box.value.substring(0, maxLength - 1);
		}
	},

	checkTab: function(box) {
		if ((document.all) && (event.keyCode == 9)) {
			box.selection = document.selection.createRange();
			setTimeout("Liferay.Util.processTab(\"" + box.id + "\")", 0);
		}
	},

	disableEsc: function() {
		if ((document.all) && (event.keyCode == 27)) {
			event.returnValue = false;
		}
	},

	endsWith: function(str, x) {
		return (str.lastIndexOf(x) === (str.length - x.length));
	},

	evalScripts: function(obj) {
		var instance = this;

		jQuery(obj).find('script').each(
			function(){
				if ( this.src ) {
					jQuery.getScript( this.src );
				}
				else {
					jQuery.globalEval( this.text || this.textContent || this.innerHTML || "" );
				}
			}
		);
	},

	focusFormField: function(el) {
		var interacting = false;

		jQuery(document).one(
			'click',
			function() {
				interacting = true;
			}
		);

		jQuery(
			function() {
				if (el && (el.offsetHeight != 0) && !interacting) {
					var elObj = jQuery(el);

					jQuery('input').trigger('blur');

					elObj.trigger('focus');
				}
			}
		);
	},

	getSelectedIndex: function(col) {
		for (var i = 0; i < col.length; i++) {
			if (col[i].checked == true) {
				return i;
			}
		}

		return -1;
	},

	getSelectedRadioValue: function(col) {
		var i = Liferay.Util.getSelectedIndex(col);

		if (i == -1) {
			var radioValue = col.value;

			if (radioValue == null) {
				radioValue = "";
			}

			return radioValue;
		}
		else {
			return col[i].value;
		}
	},

	getURLWithSessionId: function(url) {
		if (propsUtil.SESSION_ENABLE_PERSISTENT_COOKIES) {
			return url;
		}

		// LEP-4787

		var x = url.indexOf(";");

		if (x != -1) {
			return url;
		}

		x = url.indexOf("?");

		if (x != -1) {
			return url.substring(0, x) + ";jsessionid=" + themeDisplay.getSessionId() + url.substring(x);
		}

		// In IE6, http://www.abc.com;jsessionid=XYZ does not work, but
		// http://www.abc.com/;jsessionid=XYZ does work.

		x = url.indexOf("//");

		if (x != -1) {
			var y = url.lastIndexOf("/");

			if (x + 1 == y) {
				return url + "/;jsessionid=" + themeDisplay.getSessionId();
			}
		}

		return url + ";jsessionid=" + themeDisplay.getSessionId();
	},

	inlineEditor: function(options) {
		var instance = this;

		/*
		button (jQuery selector | DOM element): The button that opens the popup when clicked
		url (String): url to open that sets the editor
		width (Int): The width to set the popup to
		height (Int): The height to set the popup to
		textarea (String): the name of the textarea to auto-resize
		*/

		if (options.url && options.button) {
			var url = options.url;
			var button = options.button;
			var width = options.width || 680;
			var height = options.height || 640;
			var textarea = options.textarea;
			var clicked = false;

			var editorButton = jQuery(button);

			editorButton.click(
				function(event) {
					if (!clicked) {
						var popup = Liferay.Popup(
							{
								height: 640,
								width: 680,
								noCenter: true,
								title: '',
								onClose: function() {
									jQuery(document).unbind('popupResize');
									clicked = false;
								}
							}
						);

						var jPopup = jQuery(popup);
						var resizeDiv = '<div class="portlet-resize-handle"></div>';

						jQuery.ajax(
							{
								url: url + '&rt=' + Liferay.Util.randomInt(),
								success: function(message) {
									jPopup.find('.loading-animation').remove();
									jPopup.append(message);
									jPopup.after(resizeDiv);

									var form = jPopup.find('form');

									form.css(
										{
											height: 340,
											width: 680
										}
									);

									if (textarea) {
										var usingPlainEditor = jPopup.find('.lfr-textarea').length;

										Liferay.Util.resizeTextarea(textarea, !usingPlainEditor, true);
									}

									var handle = jQuery('.portlet-resize-handle')[0];

									var mainPopup = jPopup.parents('.popup:first');

									mainPopup.lResize(
										{
											direction: 'horizontal',
											handle: handle,
											mode: 'add',
											onMove: function(settings) {
												form.css(
													{
														height: settings.browserEvent.clientY - 130,
														width: settings.browserEvent.clientX - 30
													}
												);
												jQuery(document).trigger('popupResize');
											}
										}
									);

									mainPopup.lResize(
										{
											handle: handle,
											direction: "vertical",
											mode: "add"
										}
									);
								}
							}
						);

						clicked = true;
					}
				}
			);
		}
	},

	isArray: function(object) {
		if (!window.Array) {
			return false;
		}
		else {
			return object.constructor == window.Array;
		}
	},

	listChecked: function(form) {
		var s = [];
		var inputs = jQuery('input[@value!=]:checked:checkbox', form);

		inputs.each(
			function() {
				s.push(this.value);
			}
		);

		return s.join(',');
	},

	listCheckedExcept: function(form, except) {
		var s = [];
		var inputs = jQuery('input[@value!=][@name!="' + except + '"]:checked:checkbox', form);

		inputs.each(
			function() {
				s.push(this.value);
			}
		);

		return s.join(',');
	},

	listSelect: function(box, delimeter) {
		var s = [];

		delimeter = delimeter || ',';

		if (box == null) {
			return "";
		}

		var opts = jQuery(box).find('option[@value!=]');

		opts.each(
			function() {
				s.push(this.value);
			}
		);

		if (s[0] == '.none') {
			return '';
		}
		else {
			return s.join(',');
		}
	},

	listUncheckedExcept: function(form, except) {
		var s = [];
		var inputs = jQuery('input[@value!=][@name!="' + except + '"]:checkbox:not(:checked)', form);

		inputs.each(
			function() {
				s.push(this.value);
			}
		);

		return s.join(',');
	},

	moveItem: function(fromBox, toBox, sort) {
		if (fromBox.selectedIndex >= 0) {
			var toSelect = jQuery(toBox);
			var selectedOption = jQuery(fromBox).find('option:selected');

			toSelect.append(selectedOption);
		}

		if (selectedOption.text() != '' && sort == true) {
			Liferay.Util.sortBox(toBox);
		}
	},

	portletTitleEdit: function(options) {
		var instance = this;

		var obj = options.obj;
		var plid = options.plid;
		var doAsUserId = options.doAsUserId;
		var portletId = options.portletId;
		var url = options.url;

		var title = obj.find('.portlet-title');

		if (!title.is('.not-editable')) {
			title.editable(
				function(value, settings) {
					var cruft = settings._LFR_.cruft || [];

					cruft = cruft.join('');

					if (value != settings._LFR_.oldText) {
						Liferay.Util.savePortletTitle(
							{
								plid: plid,
								doAsUserId: doAsUserId,
								portletId: portletId,
								title: value
							}
						);
					}

					obj[0]._LFR_noDrag = null;

					return cruft + value;
				},
				{
					cssclass: 'text',
					data: function(value, settings) {
						var input = jQuery(this);
						var re = new RegExp('<\/?[^>]+>|\n|\r|\t', 'gim');

						var cruft = value.match(re);

						settings._LFR_ = {};
						settings._LFR_.oldText = value;
						settings._LFR_.cruft = cruft;

						value = value.replace(re, '');
						settings._LFR_.oldText = value;
						obj[0]._LFR_noDrag = true;

						return value;
					},
					height: '',
					width: '',
					onblur: 'submit',
					type: 'text',
					select: false,
					style: '',
					submit: ''
				}
			);
		}
	},

	processTab: function(id) {
		document.all[id].selection.text = String.fromCharCode(9);
		document.all[id].focus();
	},

	randomInt: function() {
		return (Math.ceil(Math.random() * (new Date).getTime()));
	},

	randomMinMax: function(min, max) {
		return (Math.round(Math.random() * (max - min))) + min;
	},

	removeItem: function(box, value) {
		var selectEl = jQuery(box);

		if (!value) {
			selectEl.find('option:selected').remove();
		}
		else {
			selectEl.find('option[@value=' + value + ']:selected').remove();
		}
	},

	reorder: function(box, down) {
		var si = box.selectedIndex;

		if (si == -1) {
			box.selectedIndex = 0;
		}
		else {
			sText = box.options[si].text;
			sValue = box.options[si].value;

			if ((box.options[si].value > "") && (si > 0) && (down == 0)) {
				box.options[si].text = box.options[si - 1].text;
				box.options[si].value = box.options[si - 1].value;
				box.options[si - 1].text = sText;
				box.options[si - 1].value = sValue;
				box.selectedIndex--;
			}
			else if ((si < box.length - 1) && (box.options[si + 1].value > "") && (down == 1)) {
				box.options[si].text = box.options[si + 1].text;
				box.options[si].value = box.options[si + 1].value;
				box.options[si + 1].text = sText;
				box.options[si + 1].value = sValue;
				box.selectedIndex++;
			}
			else if (si == 0) {
				for (var i = 0; i < (box.length - 1); i++) {
					box.options[i].text = box.options[i + 1].text;
					box.options[i].value = box.options[i + 1].value;
				}

				box.options[box.length - 1].text = sText;
				box.options[box.length - 1].value = sValue;

				box.selectedIndex = box.length - 1;
			}
			else if (si == (box.length - 1)) {
				for (var j = (box.length - 1); j > 0; j--) {
					box.options[j].text = box.options[j - 1].text;
					box.options[j].value = box.options[j - 1].value;
				}

				box.options[0].text = sText;
				box.options[0].value = sValue;

				box.selectedIndex = 0;
			}
		}
	},

	resizeTextarea: function(elString, usingRichEditor, resizeToInlinePopup) {
		var init = function() {
			var el = jQuery('#' + elString);

			if (!el.length) {
				el = jQuery('textarea[@name=' + elString + ']');
			}

			if (el.length) {
				var pageBody;

				if (resizeToInlinePopup) {
					pageBody = el.parents('.popup:first');
				}
				else {
					pageBody = jQuery('body');
				}

				var resize = function() {
					var pageBodyHeight = pageBody.height();

					if (usingRichEditor) {
						try {
							if (!el.is('iframe')) {
								el = eval(elString);

								if (!el.jquery) {
									el = jQuery(el);
								}
							}
						}
						catch (e) {
						}
					}

					var diff = 150;

					if (!resizeToInlinePopup) {
						diff = 100;
					}

					el.css(
						{
							height: (pageBodyHeight - diff) + "px",
							width: '98%'
						}
					);
				};

				resize();

				if (resizeToInlinePopup) {
					jQuery(document).bind('popupResize', resize);
				}
				else {
					jQuery(window).resize(resize);
				}
			}
		};

		jQuery(init);
	},

	resubmitCountdown: function(formName) {
		if (Liferay.Util.submitCountdown > 0) {
			Liferay.Util.submitCountdown--;

			setTimeout("Liferay.Util.resubmitCountdown('" + formName + "')", 1000);
		}
		else {
			Liferay.Util.submitCountdown = 0;

			if (!Liferay.Browser.is_ns_4) {
				document.body.style.cursor = "auto";
			}

			var form = document.forms[formName];

			for (var i = 0; i < form.length; i++){
				var e = form.elements[i];

				if (e.type && (e.type.toLowerCase() == "button" || e.type.toLowerCase() == "reset" || e.type.toLowerCase() == "submit")) {
					e.disabled = false;
				}
			}
		}
	},

	savePortletTitle: function(params) {
		var defaultParams = {
			plid: 0,
			doAsUserId: 0,
			portletId: 0,
			title: '',
			url: themeDisplay.getPathMain() + '/portlet_configuration/update_title'
		};

		var settings = jQuery.extend(defaultParams, params);

		jQuery.ajax(
			{
				url: settings.url,
				data: {
					p_l_id: settings.plid,
					doAsUserId: settings.doAsUserId,
					portletId: settings.portletId,
					title: settings.title
				}
			}
		);
	},

	selectAndCopy: function(el) {
		el.focus();
		el.select();

		if (document.all) {
			var textRange = el.createTextRange();

			textRange.execCommand("copy");
		}
	},

	setBox: function(oldBox, newBox) {
		for (var i = oldBox.length - 1; i > -1; i--) {
			oldBox.options[i] = null;
		}

		for (var i = 0; i < newBox.length; i++) {
			oldBox.options[i] = new Option(newBox[i].value, i);
		}

		oldBox.options[0].selected = true;
	},

	setSelectedValue: function(col, value) {
		jQuery('option[@value=' + value + ']', col).attr('selected', true);
	},

	showCapsLock: function(event, span) {
		var keyCode = event.keyCode ? event.keyCode : event.which;
		var shiftKey = event.shiftKey ? event.shiftKey : ((keyCode == 16) ? true : false);

		if (((keyCode >= 65 && keyCode <= 90) && !shiftKey) ||
			((keyCode >= 97 && keyCode <= 122) && shiftKey)) {

			document.getElementById(span).style.display = '';
		}
		else {
			document.getElementById(span).style.display = 'none';
		}
	},

	sortBox: function(box) {
		var newBox = [];

		for (var i = 0; i < box.length; i++) {
			newBox[i] = [box[i].value, box[i].text];
		}

		newBox.sort(Liferay.Util.sortByAscending);

		var boxObj = jQuery(box);

		boxObj.find('option').remove();

		jQuery.each(
			newBox,
			function(key, value) {
				boxObj.append('<option value="' + value[0] + '">' + value[1] + '</option>');
			}
		);
	},

	sortByAscending: function(a, b) {
		if (a[1].toLowerCase() > b[1].toLowerCase()) {
			return 1;
		}
		else if (a[1].toLowerCase() < b[1].toLowerCase()) {
			return -1;
		}
		else {
			return 0;
		}
	},

	startsWith: function(str, x) {
		return (str.indexOf(x) === 0);
	},

	switchEditor: function(options) {
		var instance = this;

		/*
		url (String): url to open that sets the editor
		popup (String|DOM|jQuery element): the popup that contains the editor
		textarea (String): the name of the textarea to auto-resize
		*/

		if (options.url && options.popup) {
			var url = options.url;
			var popup = options.popup;
			var textarea = options.textarea;

			if (!popup.jquery) {
				popup = jQuery(popup);
			}

			var popupMessage = popup.find('.popup-message');

			jQuery.ajax(
				{
					url: url,
					beforeSend: function() {
						popupMessage.empty();
						popupMessage.append('<div class="loading-animation"><div>');
					},
				  	success: function(message) {
						popupMessage.empty();
						popupMessage.append(message);

						if (textarea) {
							var usingPlainEditor = popup.find('.lfr-textarea').length;

							Liferay.Util.resizeTextarea(textarea, !usingPlainEditor, true);
						}
				 	}
				}
			);
		}
	},

	toggleByIdSpan: function(obj, id) {
		jQuery('#' + id).toggle();

		var spans = jQuery(obj).find('span');

		spans.toggle();
	},

	toggle: function(obj, returnState, displayType) {
		if (typeof obj == 'string') {
			obj = '#' + obj;
		}

		var el = jQuery(obj);
		var hidden = el.toggle().is(':visible');

		if (displayType) {
			el.css('display', displayType);
			hidden = el.is(':visible');
		}

		if (returnState) {
			return hidden;
		}
	},

	toggleBoxes: function(checkBoxId, toggleBoxId) {
		var checkBox = jQuery('#' + checkBoxId);
		var toggleBox = jQuery('#' + toggleBoxId);

		if (!checkBox.is(':checked')){
			toggleBox.hide();
		}

		checkBox.click(
			function(){
				toggleBox.toggle();
			}
		);
	},

	toJSONObject: function(s) {
		return jQuery.parseJSON(s);
	},

	toJSONString: function (s) {
		var rt = s;
		var m = {
			'\b': '\\b',
			'\t': '\\t',
			'\n': '\\n',
			'\f': '\\f',
			'\r': '\\r',
			'"' : '\\"',
			'\\': '\\\\'
		};

		if (/["\\\x00-\x1f]/.test(s)) {
			rt = s.replace(/([\x00-\x1f\\"])/g, function(a, b) {
				var c = m[b];
				if (c) {
					return c;
				}
				c = b.charCodeAt();
				return '\\u00' +
					Math.floor(c / 16).toString(16) +
					(c % 16).toString(16);
			});
		}

		return rt;
	}
};

Element = {};

Element.disable = function(element) {
	element = jQuery.getOne(element);

	var items = element.getElementsByTagName("*");

	for (var i = 0; i < items.length; i++) {
		var item = items[i];
		var nodeName = item.nodeName.toLowerCase();

		item.onclick = function() {};
		item.onmouseover = function() {};
		item.onmouseout = function() {};

		if (Liferay.Browser.is_ie) {
			item.onmouseenter = function() {};
			item.onmouseleave = function() {};
		}

		if (nodeName == "a") {
			item.href = "javascript: void(0)";
		}
		else if (nodeName == "input" || nodeName == "select" || nodeName == "script") {
			item.disabled = "true";
		}
		else if (nodeName == "form") {
			item.action = "";
			item.onsubmit = function() { return false; };
		}

		item.style.cursor = "default";
	}
};

Element.remove = function(id) {
	var obj = jQuery.getOne(id);

	obj.parentNode.removeChild(obj);
};

function LinkedList() {
	this.head = null;
	this.tail = null;
}

LinkedList.prototype.add = function(obj) {
	obj.listInfo = {};
	var tail = this.tail;
	var head = this.head;

	if (this.head == null) {
		this.head = obj;
		this.tail = obj;
	}
	else {
		this.tail.listInfo.next = obj;
		obj.listInfo.prev = this.tail;
		this.tail = obj;
	}

	obj.listInfo.listObj = this;
};

LinkedList.prototype.remove = function(obj) {
	if (obj.listInfo.listObj == this && this.head) {
		var next = obj.listInfo.next;
		var prev = obj.listInfo.prev;

		if (next) {
			next.listInfo.prev = prev;
		}
		if (prev) {
			prev.listInfo.next = next;
		}
		if (this.head == obj) {
			this.head = next;
		}
		if (this.tail == obj) {
			this.tail = prev;
		}
	}
};

LinkedList.prototype.each = function(func) {
	var cur = this.head;
	var count = 0;

	while (cur){
		count++;
		var next = cur.listInfo.next;

		if (func) {
			func(cur);
		}

		cur = next;
	}

	return count;
};

LinkedList.prototype.size = function() {
	return this.each();
};

function submitForm(form, action, singleSubmit) {
	if (Liferay.Util.submitCountdown == 0) {
		Liferay.Util.submitCountdown = 10;

		setTimeout("Liferay.Util.resubmitCountdown('" + form.name + "')", 1000);

		if (singleSubmit == null || singleSubmit) {
			Liferay.Util.submitCountdown++;

			var inputs = jQuery('input[@type=button], input[@type=reset], input[@type=submit]', form);

			inputs.each(
				function(i, el) {
					var input = jQuery(this);

					input.attr('disabled', true);
					input.fadeTo(50, 0.5);
				}
			);
		}

		if (action != null) {
			form.action = action;
		}

		if (!Liferay.Browser.is_ns_4) {
			document.body.style.cursor = "wait";
		}

		form.submit();
	}
}

var Viewport = {
	frame: function() {
		var x,y;
		if (self.innerHeight) // all except Explorer
		{
			x = self.innerWidth;
			y = self.innerHeight;
		}
		else if (document.documentElement && document.documentElement.clientHeight)
			// Explorer 6 Strict Mode
		{
			x = document.documentElement.clientWidth;
			y = document.documentElement.clientHeight;
		}
		else if (document.body) // other Explorers
		{
			x = document.body.clientWidth;
			y = document.body.clientHeight;
		}

		return (new Coordinate(x,y));
	},

	scroll: function() {
		var x,y;
		if (self.pageYOffset) {
			// all except Explorer
			x = self.pageXOffset;
			y = self.pageYOffset;
		}
		else if (document.documentElement && document.documentElement.scrollTop) {
			// Explorer 6 Strict
			x = document.documentElement.scrollLeft;
			y = document.documentElement.scrollTop;
		}
		else if (document.body) {
			// all other Explorers
			x = document.body.scrollLeft;
			y = document.body.scrollTop;
		}

		return (new Coordinate(x,y));
	},

	page: function() {
		var x,y;
		var test1 = document.body.scrollHeight;
		var test2 = document.body.offsetHeight;
		if (test1 > test2) // all but Explorer Mac
		{
			x = document.body.scrollWidth;
			y = document.body.scrollHeight;
		}
		else // Explorer Mac;
			//would also work in Explorer 6 Strict, Mozilla and Safari
		{
			x = document.body.offsetWidth;
			y = document.body.offsetHeight;
		}

		return (new Coordinate(x,y));
	}
};

String.prototype.trim = jQuery.trim;

// 0-200: Theme Developer
// 200-400: Portlet Developer
// 400+: Liferay

Liferay.zIndex = {
	DOCK:			10,
	DOCK_PARENT:	20,
	ALERT:			430,
	DROP_AREA:		440,
	DROP_POSITION:	450,
	DRAG_ITEM:		460,
	TOOLTIP:		470
};