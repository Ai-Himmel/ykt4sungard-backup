Liferay.DynamicSelect = new Class({

	/*
	array: an array of params
	params.select: a select box
	params.selectId: JSON object field name for an option value
	params.selectDesc: JSON object field name for an option description
	params.selectVal: selected value of the select box
	params.selectData: function that returns a JSON array to populate the next select box
	*/
	initialize: function(array) {
		var instance = this;

		instance.array = array;

		jQuery.each(
			array,
			function(i, params) {
				var select = jQuery('#' + params.select);
				var selectData = params.selectData;

				var prevSelectVal = null;

				if (i > 0) {
					prevSelectVal = array[i - 1].selectVal;
				}

				selectData(
					function(list) {
						instance._updateSelect(instance, i, list);
					},
					prevSelectVal
				);

				select.attr('name', select.attr('id'));

				select.bind(
					'change',
					function() {
						instance._callSelectData(instance, i);
					}
				);
			}
		);
	},

	_callSelectData: function(instance, i) {
		var array = instance.array;

		if ((i + 1) < array.length) {
			var curSelect = jQuery('#' + array[i].select);
			var nextSelectData = array[i + 1].selectData;

			nextSelectData(
				function(list) {
					instance._updateSelect(instance, i + 1, list);
				},
				curSelect.val()
			);
		}
	},

	_updateSelect: function(instance, i, list) {
		var params = instance.array[i];

		var select = jQuery('#' + params.select);
		var selectId = params.selectId;
		var selectDesc = params.selectDesc;
		var selectVal = params.selectVal;
		var selectNullable = params.selectNullable || true;

		var options = '';

		if (selectNullable) {
			options += '<option value="0"></option>';
		}

		jQuery.each(
			list,
			function(i, obj) {
				eval('var key = obj.' + selectId + ';');
				eval('var value = obj.' + selectDesc + ';');

				options += '<option value="' + key + '">' + value + '</option>';
			}
		);

		select.html(options);
		select.find('option[@value=' + selectVal + ']').attr('selected', 'selected');

		if (jQuery.browser.msie && jQuery.browser.version.number() <= 7) {
			select.css('width', 'auto');
		}
	}
});