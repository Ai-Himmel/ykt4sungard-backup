function AjaxRequest(url, options) {

	var xmlHttpReq;
	var opts = options;

	if (window.XMLHttpRequest) {
		xmlHttpReq = new XMLHttpRequest();

		if (xmlHttpReq.overrideMimeType) {
			xmlHttpReq.overrideMimeType("text/html");
		}
	}
	else if (window.ActiveXObject) {
		try {
			xmlHttpReq = new ActiveXObject("Msxml2.XMLHTTP");
		}
		catch (e) {
			try {
				xmlHttpReq = new ActiveXObject("Microsoft.XMLHTTP");
			}
			catch (e) {
				try {
					xmlHttpReq = new XMLHttpRequest();
				}
				catch (e) {
				}
			}
		}
	}

	var returnFunction = function() {
		if (xmlHttpReq.readyState == 4) {
			try {
				if (xmlHttpReq.status == 200) {
					if (opts.update) {
						var el = jQuery.getOne(opts.update);
						el.innerHTML = xmlHttpReq.responseText;
						executeLoadedScript(el);
					}

					if (opts.onComplete) {
						opts.onComplete(xmlHttpReq, opts.returnArgs);
					}

					AjaxUtil.remove(opts.ajaxId);
				}
			}
			catch(e) {
			}
		}
	};

	var send = function(url) {
		url = Liferay.Util.getURLWithSessionId(url);

		var urlArray = url.split("?");
		var path = urlArray[0];
		var query = urlArray[1];

		try {
			if (opts.method == "get") {
				xmlHttpReq.open("GET", url, true);
				xmlHttpReq.onreadystatechange = returnFunction;
				xmlHttpReq.send("");
			}
			else {
				xmlHttpReq.open("POST", path, true);
				xmlHttpReq.setRequestHeader("Method", "POST " + path + " HTTP/1.1");
				xmlHttpReq.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
				xmlHttpReq.onreadystatechange = returnFunction;
				xmlHttpReq.send(query);
			}
		}
		catch (e) {
		}
	};

	send(url);

	this.resend = function(url, options) {
		opts = options;
		/*
		ajaxId = 0;
		onComplete = opts.onComplete;
		*/
		send(url);
	};

	this.getId = function() {
		return ajaxId;
	};

	this.cleanUp = function() {
		xmlHttpReq.onreadystatechange = function() {};
		returnFunction = null;
		returnArgs = null;
		xmlHttpReq = null;
	};
}

var AjaxUtil = {
	counter : 1,
	requests : [],

	request : function(url, options) {
		/*
		 * OPTIONS:
		 * onComplete (function) - function to call after response is received
		 * returnArgs (object) - object to pass to return function
		 * reverseAjax (boolean) - use reverse ajax. (only one at a time)
		 * method (string) - use "get" or "post". Default is post.
		 */
		var opts = options || {};
		var ajaxId = (opts.reverseAjax) ? 0 : AjaxUtil.getNextId();
		opts.ajaxId = ajaxId;

		var request;

		if (ajaxId == 0 && AjaxUtil.requests[0]) {
			request = AjaxUtil.requests[0];
			request.resend(url, opts);
		}
		else {
			request = new AjaxRequest(url, opts);
			AjaxUtil.requests[ajaxId] = request;
		}

		if (!opts.onComplete && !opts.update) {
			AjaxUtil.remove(ajaxId);
		}
	},

	submit: function(form, options) {
		var url = form.action;
		var inputs = jQuery("input, textarea, select", form);
		var opts = options || {};
		var params = inputs.serialize();

		if (url.indexOf("?") == -1) {
			url = url + "?" + params;
		}

		if (url.lastIndexOf("?") == url.length - 1) {
			url = url + params;
		}
		else {
			url = url + "&" + params;
		}

		if (opts.disable) {
			inputs.attr("disabled", true);
		}

		AjaxUtil.request(url, opts);
	},

	update : function(url, id, options) {
		var opts = options || {};

		opts.update = id;

		AjaxUtil.request(url, opts);
	},

	getNextId : function() {
		var id = AjaxUtil.counter++;

		if (AjaxUtil.counter > 20) {
			/* Reset array in a round-robin fashion */
			/* Reserve index 0 for reverse ajax requests */
			AjaxUtil.counter = 1;
		}

		return id;
	},

	remove : function(id) {
		if (id) {
			var request = AjaxUtil.requests[id];

			if (request) {
				request.cleanUp();
				request = null;
			}
		}
	}
};

var ReverseAjax = {
	initialize: function() {
		jQuery(window).bind('unload', ReverseAjax.release);
		ReverseAjax.request();
	},

	request: function() {
		AjaxUtil.request(
			themeDisplay.getPathMain() + "/portal/reverse_ajax",
			{
				onComplete: ReverseAjax.response,
				reverseAjax: true
			}
		);
	},

	response: function(xmlHttpRequest) {
		var res = Liferay.Util.toJSONObject(xmlHttpRequest.responseText);
		var status = res.status;

		if (status && status != "failure") {
			if (status == "success") {
				if (res.chatMessages) {
					Messaging.getChatsReturn(res.chatMessages);
				}
				if (res.chatRoster) {
					MessagingRoster.getEntriesReturn(res.chatRoster);
				}
			}

			ReverseAjax.request();
		}
	},

	release : function() {
		AjaxUtil.request(themeDisplay.getPathMain() + "/portal/reverse_ajax?release=1", {reverseAjax:true});
	}
};

function executeLoadedScript(el) {
	var scripts = el.getElementsByTagName("script");

	for (var i = 0; i < scripts.length; i++) {
		if (scripts[i].src) {
			var head = document.getElementsByTagName("head")[0];
			var scriptObj = document.createElement("script");

			scriptObj.setAttribute("type", "text/javascript");
			scriptObj.setAttribute("src", scripts[i].src);

			head.appendChild(scriptObj);
		}
		else {
			try {
				if (Liferay.Browser.is_safari) {
					eval(scripts[i].innerHTML);
				}
				else if (Liferay.Browser.is_mozilla) {
					eval(scripts[i].textContent);
				}
				else {
					eval(scripts[i].text);
				}
			}
			catch (e) {}
		}
	}
}

/*
 * NOTE: loadPage() has been depricated.  Use AjaxUtil.request() instead
 */
function loadPage(path, queryString, returnFunction, returnArgs) {
	AjaxUtil.request(
		path + "?" + queryString,
		{
			onComplete: returnFunction,
			returnArgs: returnArgs
		}
	);
}

function printJSON(data) {
	if (data && data.id) {
		var target = document.getElementById(data.id);

		if (target) {
			target.innerHTML = data.toString();
		}
	}
}