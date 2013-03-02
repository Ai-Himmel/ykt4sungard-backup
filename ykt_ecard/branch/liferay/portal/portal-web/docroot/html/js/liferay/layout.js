Liferay.Layout = {
	getGroupId: function(objId) {
		var instance = this;

		if ((objId != null) &&
			(objId.indexOf(instance._private) == 0 || objId.indexOf(instance._public) == 0)) {

			return objId.split(instance._separator)[1];
		}

		return 0;
	},

	getLayoutId: function(objId) {
		var instance = this;

		if ((objId != null) &&
			(objId.indexOf(instance._private) == 0 || objId.indexOf(instance._public) == 0)) {

			return objId.split(instance._separator)[2];
		}

		return 0;
	},

	getOwnerId: function(objId) {
		var instance = this;

		if ((objId != null) &&
			(objId.indexOf(instance._private) == 0 || objId.indexOf(instance._public) == 0)) {

			var pos = objId.lastIndexOf(instance._separator);

			if (pos != -1) {
				return objId.substring(0, pos);
			}

			return null;
		}
	},

	_private: 'PRI.',
	_public: 'PUB.',
	_separator: '.'
};