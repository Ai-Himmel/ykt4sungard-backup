Liferay.TagsSelector = new Class({

	/*
	params.instanceVar: the instance variable for this class
	params.hiddenInput: the hidden input used to pass in the current tags
	params.textInput: the text input for users to add tags
	params.summarySpan: the summary span tos how the current tags
	params.curTags: comma delimited string of current tags
	params.focus: true if the text input should be focused
	*/
	initialize: function(params) {
		var instance = this;

		instance._curTags = [];

		instance.params = params;

		var hiddenInput = jQuery('#' + params.hiddenInput);

		hiddenInput.attr('name', hiddenInput.attr('id'));

		var textInput = jQuery('#' + params.textInput);

		textInput.Autocomplete(
			{
				source: instance._getTags,
				delay: 0,
				fx: {
					type: 'slide',
					duration: 400
				},
				autofill: false,
				dataSourceType: 'json',
				helperClass: 'autocomplete-box',
				selectClass: 'autocomplete-selected',
				multiple: true,
				mutipleSeparator: ',',
				minchars: 1,
				onSelect: function(option) {
					if (this.createTextRange) {
						var value = this.value;
						var textRange = this.createTextRange();

						textRange.moveStart('character', value.length);
						textRange.select();
					}
				},
				onShow: function() {
					jQuery(this).addClass('showing-list');
				},
				onHide: function() {
					jQuery(this).removeClass('showing-list');
				}
			}
		);

		instance._popupVisible = false;

		instance._setupSelectTags();

		var addTagButton = jQuery('#' + params.addTagButton);

		addTagButton.click(
			function() {
					var curTags = instance._curTags;
					var newTags = textInput.val().split(",");

					jQuery.each(
						newTags,
						function (i, n) {
							n = jQuery.trim(n);

							if (curTags.indexOf(n) == -1) {
								if (n != "") {
									curTags.push(n);

									if (instance._popupVisible) {
										jQuery('input[@type=checkbox][@value$=' + n + ']', instance.selectTagPopup).attr('checked', true);
									}
								}
							}
						}
					);

					curTags = curTags.sort();
					textInput.val('');

					instance._update();
				}
		);

		textInput.keypress(
			function(event) {
				if ((event.keyCode == 13) && !jQuery(this).is('.showing-list')) {
					addTagButton.trigger('click');

					return false;
				}
			}
		);

		if (params.focus) {
			textInput.focus();
		}

		if (params.curTags != '') {
			instance._curTags = params.curTags.split(',');

			instance._update();
		}

		Liferay.Util.actsAsAspect(window);

		window.before(
			'submitForm',
			function() {
				var val = jQuery.trim(textInput.val());

				if (val.length) {
					addTagButton.trigger('click');
				}
			}
		);
	},

	deleteTag: function(id) {
		var instance = this;

		var params = instance.params;
		var curTags = instance._curTags;

		jQuery('#' + params.instanceVar + 'CurTags' + id).remove();

		var value = curTags.splice(id, 1);

		if (instance._popupVisible) {
			jQuery('input[@type=checkbox][@value$=' + value + ']', instance.selectTagPopup).attr('checked', false);
		}

		instance._update();
	},

	_getTags: function(data) {
		var beginning = data.start || 0;
		var end = data.end || 20;

		data.value = data.value || '';

		return Liferay.Service.Tags.TagsEntry.searchAutocomplete(
			{
				companyId: themeDisplay.getCompanyId(),
				name: "%" + data.value + "%",
				properties: "",
				begin: beginning,
				end: end
			}
		);
	},

	_setupSelectTags: function() {
		var instance = this;

		var params = instance.params;
		var ns = params.instanceVar;

		var input = jQuery('#' + ns + 'selectTag');

		input.click(
			function() {
				instance._showSelectPopup();
			}
		);
	},

	_showSelectPopup: function() {
		var instance = this;

		var params = instance.params;
		var ns = params.instanceVar;
		var mainContainer = jQuery('<div class="lfr-tag-select-container"></div>');
		var container = jQuery('<div class="lfr-tag-container"></div>');

		var categories = Liferay.Service.Tags.TagsProperty.getPropertyValues(
			{
				companyId: themeDisplay.getCompanyId(),
				key: "category"
			}
		);

		jQuery.each(
			categories,
			function(i, category) {
				var tags = Liferay.Service.Tags.TagsEntry.search(
					{
						companyId: themeDisplay.getCompanyId(),
						name: '%',
						properties: 'category:' + category.value
					}
				);

				var label = '';

				jQuery.each(
					tags,
					function(j, tag) {
						if (j == 0) {
							if (i > 0) {
								label += '</fieldset>';
							}
							label += '<fieldset><legend>' + category.value + '</legend>';
						}

						var checked = (instance._curTags.indexOf(tag.name) > -1) ? ' checked="checked"' : '';

						label +=
							'<label title="' + tag.name + '">' +
								'<input' + checked + ' type="checkbox" name="' + ns + 'input' + j + '" id="' + ns + 'input' + j + '" value="' + tag.name + '" />' +
								'<a class="lfr-label-text" href="javascript: ;">' + tag.name + '</a>' +
							'</label>';

					}
				);

				container.append(label);
			}
		);

		var saveBtn = jQuery('<input class="submit lfr-save-button" id="' + ns + 'saveButton" type="submit" value="' + Liferay.Language.get('save') + '" />');

		saveBtn.click(
			function() {
				instance._curTags = [];

				container.find('input:checked').each(
					function(){
						instance._curTags.push(this.value);
					}
				);

				instance._update();
				Liferay.Popup.close(instance.selectTagPopup);
				instance._popupVisible = false;
			}
		);

		mainContainer.append(container).append(saveBtn);

		var popup = Liferay.Popup(
			{
				modal: false,
				height: 300,
				width: 400,
				message: mainContainer[0],
				onClose: function() {
					instance._popupVisible = false;
				}
			}
		);

		instance.selectTagPopup = popup;
		instance._popupVisible = true;

		if (Liferay.Browser.is_ie) {
			jQuery('.lfr-label-text', popup).click(
				function() {
					var input = jQuery(this.previousSibling);
					var checkedState = !input.is(':checked');
					input.attr('checked', checkedState);
				}
			);
		}
	},

	_update: function() {
		var instance = this;

		instance._updateHiddenInput();
		instance._updateSummarySpan();
	},

	_updateHiddenInput: function() {
		var instance = this;

		var params = instance.params;
		var curTags = instance._curTags;

		var hiddenInput = jQuery('#' + params.hiddenInput);

		hiddenInput.val(curTags.join(','));
	},

	_updateSummarySpan: function() {
		var instance = this;

		var params = instance.params;
		var curTags = instance._curTags;

		var html = '';

		jQuery(curTags).each(
			function(i, curTag) {
				html += '<span id="' + params.instanceVar + 'CurTags' + i + '">';
				html += curTag + ' ';
				html += '[<a href="javascript: ' + params.instanceVar + '.deleteTag(' + i + ');">x</a>]';

				if ((i + 1) < curTags.length) {
					html += ', ';
				}

				html += '</span>';
			}
		);

		var tagsSummary = jQuery('#' + params.summarySpan);

		tagsSummary.html(html);
	}
});