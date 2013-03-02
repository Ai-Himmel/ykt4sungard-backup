Liferay.Portlet.TagsAdmin = new Class({
	initialize: function(params) {
		var instance = this;

		//Liferay.ServiceAuth.setHeader("2", "test");

		instance._categoriesCount = 0;
		instance._entriesInCurCategoryCount = 0;
		instance._searchFilters = {};

		instance.params = params;

		var addCategoryNameInput = jQuery('#' + params.addCategoryNameInput);
		var addEntryButton = jQuery('#' + params.addEntryButton);
		var addEntryNameInput = jQuery('#' + params.addEntryNameInput);
		var addPropertyButton = jQuery('#' + params.addPropertyButton);
		var addToCategorySpan = jQuery('#' + params.addToCategorySpan);
		var cancelEditEntryButton = jQuery('#' + params.cancelEditEntryButton);
		var deleteEntryButton = jQuery('#' + params.deleteEntryButton);
		var editEntryFields = jQuery('#' + params.editEntryFields);
		var editEntryNameInput = jQuery('#' + params.editEntryNameInput);
		var form = jQuery('#' + params.form);
		var keywordsInput = jQuery('#' + params.keywordsInput);
		var updateEntryButton = jQuery('#' + params.updateEntryButton);

		instance._form = form;

		// Show all entries

		instance._getEntries(instance);

		// Divs

		editEntryFields.hide();

		// Form

		form.submit(
			function() {
				return false;
			}
		);

		// Inputs

		addCategoryNameInput.val('');

		addCategoryNameInput.keypress(
			function(event) {
				if (event.keyCode == 13) {
					instance._addEntry(instance);
				}
			}
		);

		addEntryNameInput.keypress(
			function(event) {
				if (event.keyCode == 13) {
					instance._addEntry(instance);
				}
			}
		);

		editEntryNameInput.keypress(
			function(event) {
				if (event.keyCode == 13) {
					instance._updateEntry(instance);
				}
			}
		);

		keywordsInput.keyup(
			function(event) {
				instance._searchEntries(instance);
			}
		);

		keywordsInput.val('');
		//keywordsInput.focus();

		// Buttons

		addEntryButton.click(
			function() {
				instance._addEntry(instance);
			}
		);

		addPropertyButton.click(
			function() {
				var html = instance._addProperty(instance, '0', '', '');

				instance._addProperties(instance, html);
			}
		);

		cancelEditEntryButton.click(
			function() {
				editEntryFields.hide();
			}
		);

		deleteEntryButton.click(
			function() {
				instance._deleteEntry(instance, instance._entryId);
			}
		);

		updateEntryButton.click(
			function() {
				instance._updateEntry(instance);
			}
		);
	},

	deleteEntry: function(instance, entryId) {
		instance._deleteEntry(instance, entryId);
	},

	editEntry: function(instance, entryId, name) {
		var params = instance.params;

		instance._entryId = entryId;

		var editEntryFields = jQuery('#' + params.editEntryFields);
		var editEntryNameInput = jQuery('#' + params.editEntryNameInput);
		var propertiesTable = jQuery('#' + params.propertiesTable);

		editEntryNameInput.val(name);

		propertiesTable.find('tr').gt(-1).remove();

		Liferay.Service.Tags.TagsProperty.getProperties(
			{
				entryId: entryId
			},
			function(properties) {
				instance._editProperties(instance, properties);
			}
		);

		editEntryFields.show();
	},

	_addEntry: function(instance) {
		var params = instance.params;

		var instanceVar = params.instanceVar;
		var addEntryNameInput = jQuery('#' + params.addEntryNameInput);

		var categorySel = jQuery('#' + instanceVar + 'categorySel');
		var filterSel = jQuery('#' + instanceVar + 'CategoryFilterSel');
		var category = categorySel.val();

		if (category == '[new]') {
			var addCategoryNameInput = jQuery('#' + params.addCategoryNameInput);

			category = jQuery.trim(addCategoryNameInput.val());

			if (category) {
				instance._searchFilters['category'] = category;

				addCategoryNameInput.hide();
			}
			else {
				category = 'no category';
			}
		}

		var properties = new Array('0:category:' + category);

		if (category == '[none]') {
			properties = null;
		}

		Liferay.Service.Tags.TagsEntry.addEntry(
			{
				name: addEntryNameInput.val(),
				properties: properties
			},
			function(json) {
				if (!json.exception) {
					instance._getEntries(instance);
				}
				else {
					if (json.exception.indexOf('com.liferay.portlet.tags.DuplicateEntryException') > -1) {
						instance._sendMessage('error', 'that-tag-already-exists');
					}
					else if (json.exception.indexOf('com.liferay.portlet.tags.EntryNameException') > -1) {
						instance._sendMessage('error', 'one-of-your-fields-contain-invalid-characters');
					}
				}
			}
		);

		instance._resetFields(instance);

		addEntryNameInput.focus();
	},

	_addProperties: function(instance, html) {
		var params = instance.params;

		var instanceVar = params.instanceVar;
		var propertiesTable = jQuery('#' + params.propertiesTable);

		propertiesTable.append(html);

		propertiesTable.find('tr').each(
			function(i, row) {
				jQuery('input[@name=' + instanceVar + 'deletePropertyButton]', row).click(
					instance._deleteProperty
				);

				jQuery('input[@name=' + instanceVar + 'propertyValue]', row).keypress(
					function(event) {
						if (event.keyCode == 13) {
							instance._updateEntry(instance);
						}
					}
				);
			}
		);
	},

	_addProperty: function(instance, propertyId, key, value) {
		var params = instance.params;

		var instanceVar = params.instanceVar;

		var html = '';

		html += '<tr><td>';
		html += '<input name="' + instanceVar + 'propertyId" type="hidden" value="' + propertyId + '" />\n';
		html += '<input';

		if (key == 'category') {
			html += ' disabled';
		}

		html += ' name="' + instanceVar + 'propertyKey" type="text" value="' + key + '" />\n';
		html += '<input name="' + instanceVar + 'propertyValue" type="text" value="' + value + '" />\n';

		if (key != 'category') {
			html += '<input name="' + instanceVar + 'deletePropertyButton" type="button" value="Delete" />\n';
		}

		html += '</td></tr>';

		return html;
	},

	_deleteEntry: function(instance, entryId) {
		var params = instance.params;

		var instanceVar = params.instanceVar;
		var editEntryFields = jQuery('#' + params.editEntryFields);

		Liferay.Service.Tags.TagsEntry.deleteEntry(
			{
				entryId: entryId
			},
			function() {
				if (((instance._searchFilters['category'] != 'all') || (instance._categoriesCount == 1)) &&
					 (instance._entriesInCurCategoryCount == 1)) {

					instance._searchFilters['category'] = 'all';
					jQuery('#' + params.addCategoryNameInput).show();
				}

				instance._getEntries(instance);
			}
		);

		editEntryFields.hide();
	},

	_deleteProperty: function() {
		jQuery(this).parents('tr').eq(0).remove();
	},

	_displayEntries: function(instance, properties, keywords) {
		var params = instance.params;

		var instanceVar = params.instanceVar;
		var searchResultsDiv = jQuery('#' + params.searchResultsDiv);

		var html = '<br />';

		instance._categoriesCount = properties.length;

		searchResultsDiv.html('');

		jQuery.each(
			properties,
			function(i,category) {
				if (instance._searchFilters['category'] == null ||
					instance._searchFilters['category'] == 'all' ||
					instance._searchFilters['category'] == category.value) {

					Liferay.Service.Tags.TagsEntry.search(
						{
							companyId: themeDisplay.getCompanyId(),
							name: keywords,
							properties: 'category:' + category.value
						},
						function(entries) {
							if (category.value != '') {
								html += '<div style="clear: both;"></div><b>' + category.value + '</b><br />';
							}

							html += '<div style="float: left; width: 25%;">';

							jQuery.each(
								entries,
								function(i, entry) {
									var hrefJS = instanceVar + '.editEntry(' + instanceVar + ', ' + entry.entryId + ', \'' + encodeURIComponent(entry.name) + '\');';

									var numEntries = entries.length;

									html += '</div><div style="float: left; width: 25%;">';
									html += ' <a href="javascript: ' + hrefJS + '">' + entry.name + '</a>';
									html += ' <a href="javascript: ' + instanceVar + '.deleteEntry(' + instanceVar + ', ' + entry.entryId + ')">[x]</a>';

									if ((i + 1) < entries.length) {
										html += '<br />';
									}

								}
							);

							html += '</div>';

							if (entries.length == 0) {
								html += Liferay.Language.get('no-tags-found');
							}

							searchResultsDiv.html(html);
						}
					);
				}
			}
		);
	},

	_displayFilters: function(instance, propertyKey, properties) {
		var params = instance.params;

		var instanceVar = params.instanceVar;
		var searchPropertiesSpan = jQuery('#' + params.searchPropertiesSpan);
		var addToCategorySpan = jQuery('#' + params.addToCategorySpan);

		var filterHtml = '';
		var selectHtml = '';

		jQuery.each(
			properties,
			function(i, property) {
				var selected = '';

				if (property.value == instance._searchFilters['category']) {
					selected = ' selected';
				}

				var html = '<option value="' + property.value + '"' + selected + '>' + property.value + '</option>';

				filterHtml += html;

				if (property.value != 'no category') {
					selectHtml += html;
				}
			}
		);


		filterHtml = '<select id="' + instanceVar + propertyKey + 'FilterSel"><option>all</option>' + filterHtml + '</select>';

		var selected = '';

		if (instance._searchFilters['category'] == 'no category') {
			selected = 'selected';
		}

		selectHtml = '<select id="' + instanceVar + propertyKey + 'Sel"><option value="[new]">(New)</option><option value="no category"' + selected + '>(None)</option>' + selectHtml + '</select>';

		searchPropertiesSpan.append('<span style="padding: 0px 5px 0px 10px;">' + propertyKey + '</span>');
		searchPropertiesSpan.append(filterHtml);

		addToCategorySpan.append('<span style="padding: 0px 5px 0px 10px;">' + selectHtml + '</span>');

		var addCategoryNameInput = jQuery('#' + params.addCategoryNameInput);
		var filterSel = jQuery('#' + instanceVar + propertyKey + 'FilterSel');
		var categorySel = jQuery('#' + instanceVar + 'categorySel');

		filterSel.change(
			function() {
				instance._searchFilters[propertyKey] = this.value;

				if (this.value == 'all') {
					categorySel.val('[new]');
					addCategoryNameInput.show();
				}
				else {
					categorySel.val(this.value);
					addCategoryNameInput.hide();
				}

				instance._searchEntries(instance);
			}
		);

		categorySel.change(
			function() {
				instance._searchFilters[propertyKey] = this.value;

				if (this.value == '[new]') {
					filterSel.val('[all]');
					addCategoryNameInput.show();
				}
				else {
					filterSel.val(this.value);
					addCategoryNameInput.hide();
				}

				instance._searchEntries(instance);
			}
		);
	},

	_editProperties: function(instance, properties) {
		var html = '';

		jQuery.each(
			properties,
			function(i, property) {
				html += instance._addProperty(instance, property.propertyId, property.key, property.value);
			}
		);

		if (properties.length == 0) {
			html += instance._addProperty('0', '', '');
		}

		instance._addProperties(instance, html);
	},

	_getEntries: function(instance) {
		instance._resetFields(instance);

		Liferay.Service.Tags.TagsProperty.getPropertyValues(
			{
				companyId: themeDisplay.getCompanyId(),
				key: "category"
			},
			function(properties) {
				instance._displayEntries(instance, properties, '%');
			}
		);

		instance._getFilters(instance);
	},

	_getFilters: function(instance) {
		var params = instance.params;

		var instanceVar = params.instanceVar;

		var searchPropertiesSpan = jQuery('#' + params.searchPropertiesSpan);
		var addToCategorySpan = jQuery('#' + params.addToCategorySpan);

		var propertyKeys = new Array('category');

		if (propertyKeys.length > 0) {
			searchPropertiesSpan.html('Filter By: ');
			addToCategorySpan.html('Add To: ');
		}

		jQuery.each(
			propertyKeys,
			function(i, propertyKey) {
				Liferay.Service.Tags.TagsProperty.getPropertyValues(
					{
						companyId: themeDisplay.getCompanyId(),
						key: propertyKey
					},
					function(properties) {
						instance._displayFilters(instance, propertyKey, properties);
					}
				);
			}
		);
	},

	_resetFields: function(instance) {
		var params = instance.params;

		var addCategoryNameInput = jQuery('#' + params.addCategoryNameInput);
		var addEntryNameInput = jQuery('#' + params.addEntryNameInput);
		var keywordsInput = jQuery('#' + params.keywordsInput);


		addCategoryNameInput.val('');
		addEntryNameInput.val('');
		keywordsInput.val('');
	},

	_searchEntries: function(instance) {
		var params = instance.params;

		var keywordsInput = jQuery('#' + params.keywordsInput);
		var keywords = '%' + keywordsInput.val() + '%';

		var searchResultsDiv = jQuery('#' + params.searchResultsDiv);

		searchResultsDiv.html('');

		Liferay.Service.Tags.TagsProperty.getPropertyValues(
			{
				companyId: themeDisplay.getCompanyId(),
				key: "category"
			},
			function(properties) {
				instance._displayEntries(instance, properties, keywords);
			}
		);
	},

	_sendMessage: function(type, key) {
		var instance = this;

		var msgType = 'portlet-msg-error';

		if (type == 'success') {
			msgType = 'portlet-msg-success';
		}

		var message = Liferay.Language.get(key);

		var currentMsg = jQuery('.lfr-message-response');

		if (currentMsg.length) {
			currentMsg.removeClass('portlet-msg-success').removeClass('portlet-msg-error');
			currentMsg.addClass(msgType);
			currentMsg.fadeIn('fast');
		}
		else {
			currentMsg = jQuery('<div class="' + msgType + ' lfr-message-response">' + message + '</div>');

			instance._form.prepend(currentMsg);
		}

		var fadeOutTimeout = setTimeout(
			function() {
				currentMsg.fadeOut('slow');
				clearTimeout(fadeOutTimeout);
			},
			7000
		);
	},

	_updateEntry: function(instance) {
		var params = instance.params;

		var instanceVar = params.instanceVar;
		var editEntryNameInput = jQuery('#' + params.editEntryNameInput);
		var editEntryFields = jQuery('#' + params.editEntryFields);
		var propertiesTable = jQuery('#' + params.propertiesTable);

		var properties = '';

		var rows = propertiesTable.find('tr');

		rows.each(
			function(i, row) {
				var propertyId = jQuery('input[@name=' + instanceVar + 'propertyId]', row).val();
				var propertyKey = jQuery('input[@name=' + instanceVar + 'propertyKey]', row).val();
				var propertyValue = jQuery('input[@name=' + instanceVar + 'propertyValue]', row).val();

				properties += propertyId + ':' + propertyKey + ':' + propertyValue;

				if ((i + 1) < rows.length) {
					properties += ',';
				}
			}
		);

		Liferay.Service.Tags.TagsEntry.updateEntry(
			{
				entryId: instance._entryId,
				name: editEntryNameInput.val(),
				properties: properties
			},
			function(json) {
				if (!json.exception) {
					instance._getEntries(instance);
				}
				else {
					if (json.exception.indexOf('Exception') > -1) {
						instance._sendMessage('error', 'one-of-your-fields-contain-invalid-characters');
					}
				}
			}
		);

		editEntryFields.hide();
	}
});