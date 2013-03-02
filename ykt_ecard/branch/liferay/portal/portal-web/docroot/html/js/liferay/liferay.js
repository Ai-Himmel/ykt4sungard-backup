$ = null;

Function.prototype.extendNativeFunctionObject = jQuery.extend;

jQuery.getOne = function(s, context) {
	var rt;

	if (typeof s == 'object') {
		rt = s;
	}
	else if (typeof s == 'string') {
		if (s.search(/^[#.]/) == -1) {
			s = '#' + s;
		}

		if (context == null) {
			rt = jQuery(s);
		}
		else {
			rt = jQuery(s, context);
		}

		if (rt.length > 0) {
			rt = rt.get(0);
		}
		else {
			rt = null;
		}
	}

	return rt;
};

jQuery.fn.getOne = function(s) {
	return jQuery.getOne(s, this);
};

jQuery.ajaxOld = jQuery.ajax;

jQuery.ajax = function(options) {
	options.url = Liferay.Util.getURLWithSessionId(options.url);

	return jQuery.ajaxOld(options);
};

Liferay = function() {
	var $ = jQuery;

	return {};
}();

Liferay.Service = {
	actionUrl: themeDisplay.getPathMain() + "/portal/json_service",

	tunnelUrl: themeDisplay.getPathContext() + "/tunnel-web/secure/json",

	classNameSuffix: "ServiceJSON",

	ajax: function(params, callback) {
		var instance = this;

		var serviceUrl = instance.actionUrl;

		if (Liferay.ServiceAuth.header) {
			serviceUrl = instance.tunnelUrl;
		}

		params.serviceParameters = Liferay.Service.getParameters(params);

		if (callback) {
			jQuery.ajax(
				{
					type: 'GET',
					url: serviceUrl,
					data: params,
					dataType: 'json',
					beforeSend: function(xHR) {
						if (Liferay.ServiceAuth.header) {
							xHR.setRequestHeader('Authorization', Liferay.ServiceAuth.header);
						}
					},
					success: callback
				}
			);
		}
		else {
			var xHR = jQuery.ajax(
				{
					url: serviceUrl,
					data: params,
					dataType: 'json',
					async: false
				}
			);

			return eval("(" + xHR.responseText + ")");
		}
	},

	getParameters: function(params) {
		var serviceParameters = "";

		for (var key in params) {
			if ((key != "serviceClassName") && (key != "serviceMethodName")) {
				serviceParameters += key + ",";
			}
		}

		if (Liferay.Util.endsWith(serviceParameters, ",")) {
			serviceParameters = serviceParameters.substring(0, serviceParameters.length - 1);
		}

		return serviceParameters;
	}
};

Liferay.ServiceAuth = {
	header: null,

	setHeader: function(userId, password) {
		var instance = this;

		instance.header = "Basic " + Liferay.Base64.encode(userId + ':' + password);
	}
};

/*
http://www.webtoolkit.info/
*/
Liferay.Base64 = {
	encode: function(input) {
		var instance = this;

		var output = "";
		var chr1, chr2, chr3, enc1, enc2, enc3, enc4;
		var i = 0;

		input = instance._utf8Encode(input);

		while (i < input.length) {
			chr1 = input.charCodeAt(i++);
			chr2 = input.charCodeAt(i++);
			chr3 = input.charCodeAt(i++);

			enc1 = chr1 >> 2;
			enc2 = ((chr1 & 3) << 4) | (chr2 >> 4);
			enc3 = ((chr2 & 15) << 2) | (chr3 >> 6);
			enc4 = chr3 & 63;

			if (isNaN(chr2)) {
				enc3 = enc4 = 64;
			}
			else if (isNaN(chr3)) {
				enc4 = 64;
			}

			output = output + this._keyStr.charAt(enc1) + this._keyStr.charAt(enc2) + this._keyStr.charAt(enc3) + this._keyStr.charAt(enc4);
		}

		return output;
	},

	decode: function(input) {
		var instance = this;

		var output = "";
		var chr1, chr2, chr3;
		var enc1, enc2, enc3, enc4;
		var i = 0;

		input = input.replace(/[^A-Za-z0-9\+\/\=]/g, "");

		while (i < input.length) {
			enc1 = this._keyStr.indexOf(input.charAt(i++));
			enc2 = this._keyStr.indexOf(input.charAt(i++));
			enc3 = this._keyStr.indexOf(input.charAt(i++));
			enc4 = this._keyStr.indexOf(input.charAt(i++));

			chr1 = (enc1 << 2) | (enc2 >> 4);
			chr2 = ((enc2 & 15) << 4) | (enc3 >> 2);
			chr3 = ((enc3 & 3) << 6) | enc4;

			output = output + String.fromCharCode(chr1);

			if (enc3 != 64) {
				output = output + String.fromCharCode(chr2);
			}

			if (enc4 != 64) {
				output = output + String.fromCharCode(chr3);
			}
		}

		output = instance._utf8Decode(output);

		return output;
	},

	_utf8Encode: function(string) {
		string = string.replace(/\r\n/g,"\n");

		var utftext = "";

		for (var n = 0; n < string.length; n++) {
			var c = string.charCodeAt(n);

			if (c < 128) {
				utftext += String.fromCharCode(c);
			}
			else if((c > 127) && (c < 2048)) {
				utftext += String.fromCharCode((c >> 6) | 192);
				utftext += String.fromCharCode((c & 63) | 128);
			}
			else {
				utftext += String.fromCharCode((c >> 12) | 224);
				utftext += String.fromCharCode(((c >> 6) & 63) | 128);
				utftext += String.fromCharCode((c & 63) | 128);
			}

		}

		return utftext;
	},

	_utf8Decode: function(utftext) {
		var string = "";
		var i = 0;
		var c = c1 = c2 = 0;

		while (i < utftext.length) {
			c = utftext.charCodeAt(i);

			if (c < 128) {
				string += String.fromCharCode(c);
				i++;
			}
			else if((c > 191) && (c < 224)) {
				c2 = utftext.charCodeAt(i+1);
				string += String.fromCharCode(((c & 31) << 6) | (c2 & 63));
				i += 2;
			}
			else {
				c2 = utftext.charCodeAt(i+1);
				c3 = utftext.charCodeAt(i+2);
				string += String.fromCharCode(((c & 15) << 12) | ((c2 & 63) << 6) | (c3 & 63));
				i += 3;
			}
		}

		return string;
	},

	_keyStr: "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/="
};

jQuery.fn.exactHeight = jQuery.fn.height;
jQuery.fn.exactWidth = jQuery.fn.width;

jQuery.each(
	['height', 'width'],
	function(i, n) {
	jQuery.fn[n] = function(h) {
		return h == undefined ?
			(this.length ? (n == 'height' ? this[0].offsetHeight : this[0].offsetWidth) : null) :
			this.css(n, h.constructor == String ? h : h + "px");
	};
});