Liferay.Language = {
	get: function(key, extraParams) {
		var instance = this;

		var url = themeDisplay.getPathContext() + '/language/' + themeDisplay.getLanguageId() + '/' + key + '/';

		if (extraParams) {
			if (typeof extraParams == 'string') {
				url += extraParams;
			}
			else if (Liferay.Util.isArray(extraParams)) {
				url += extraParams.join('/');
			}
		}

		var value = instance._cache[url];

		if (value != null) {
			return value;
		}

		var xHR = jQuery.ajax(
			{
				url: url,
				async: false
			}
		);

		value = xHR.responseText;

		instance._cache[url] = value;

		return value;
	},

	_cache: {}
};