Liferay.Browser = {

	init: function() {
		var instance = this;

		var version = instance.version();
		var exactVersion = instance.version(true);

		instance._browserVars = {
			agent: '',

			is_ie: false,
			is_ie_4: false,
			is_ie_5: false,
			is_ie_5_5: false,
			is_ie_5_up: false,
			is_ie_6: false,
			is_ie_7: false,

			is_mozilla: false,
			is_mozilla_1_3_up: false,

			is_ns_4: false,

			is_rtf: false,

			is_safari: false,
			is_opera: false
		};

		instance._browserVars.agent = instance.browser().toLowerCase();

		instance._browserVars.is_ie = jQuery.browser.msie;
		instance._browserVars.is_ie_4 = (instance.is_ie && version == 4);
		instance._browserVars.is_ie_5 = (instance.is_ie && version == 5);
		instance._browserVars.is_ie_5_5 = (instance.is_ie && exactVersion == 5.5);
		instance._browserVars.is_ie_5_up = (instance.is_ie && version >= 5);
		instance._browserVars.is_ie_6 = (instance.is_ie && version == 6);
		instance._browserVars.is_ie_7 = (instance.is_ie && version == 7);

		instance._browserVars.is_mozilla = (jQuery.browser.mozilla);
		instance._browserVars.is_mozilla_1_3_up = (instance.is_mozilla && exactVersion > 1.3);

		instance._browserVars.is_ns_4 = (jQuery.browser.netscape && version == 4);

		instance._browserVars.is_rtf = (instance.is_ie_5_5_up || instance.is_mozilla_1_3_up);

		instance._browserVars.is_safari = jQuery.browser.safari;
		instance._browserVars.is_opera = jQuery.browser.opera;

		jQuery.extend(instance, instance._browserVars);
	},

	browser: function() {
		var instance = this;

		return jQuery.browser.browser;
	},

	compat: function() {
		var instance = this;

		for (var i in instance._browserVars){
			if (!window[i]) {
				window[i] = instance._browserVars[i];
			}
		}
	},

	version: function(exact) {
		var instance = this;

		if (!exact) {
			return jQuery.browser.version.string(true);
		}
		else {
			return jQuery.browser.version.string();
		}
	},

	_browserVars: {}
};

jQuery(
	function() {
		Liferay.Browser.init();
		//Uncomment the following line if you wish to have the original global variables set (eg. is_ie6, is_mozilla, etc)
		// Liferay.Browser.compat();
	}
);