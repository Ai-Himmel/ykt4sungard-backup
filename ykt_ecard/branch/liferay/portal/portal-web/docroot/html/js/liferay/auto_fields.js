Liferay.autoFields = new Class({
	/*
	Options
	html (String) HTML to append to the end of the container
	container (String) the jQuery selector of the item(s) you wish to append the HTML to
	addText (String) the text you wish to use for the "Add" link
	removeText (String) the text you wish to use for the "Remove" link
	clearText (String) the text you wish to use for the "Clear" link (this link clears all of the added forms except the very first one, a sort of reset button)
	confirmText (String) the text you wish to use to confirm that the user wishes to clear all of the added buttons (leave empty to not confirm)
	rowType (String) the html tag for the row of fields (eg. fieldset, div or tr)
	onAdd (function) a callback that executes after new fields have been added
	onRemove (function) a callback that executes after fields have been removed
	onClear (function) a callback that executes after the form fields have been returned
	init (function) a callback that executes after the class has fully initialized
	*/
	initialize: function(options) {
		var instance = this;

		options = jQuery.extend(options, {});

		instance._html = jQuery(options.html || '');
		instance._container = jQuery(options.container || '');
		instance._addText = options.addText || '';
		instance._removeText = options.removeText || '';
		instance._clearText = options.clearText || '';
		instance._confirmText = options.confirmText || '';
		instance._rowType = options.rowType || '';
		instance._onAdd = options.onAdd;
		instance._onRemove = options.onRemove;
		instance._onClear = options.onClear;
		instance._init = options.init || false;

		instance._numField = 1;

		instance._run();

		if (instance._init) {
			instance._init();
		}
	},

	_run: function() {
		var instance = this;

		var container = instance._container;

		if (container.length) {
			var html = instance._html;

			var addLink, removeLink, clearLink;
			var links = jQuery('<span class="lfr-control-links"></span>');

			if (instance._addText) {
				addLink = jQuery('<a href="javascript:;">' + instance._addText + '</a>');

				addLink.click(
				   function() {
					   var newField = instance._addFields();
					   if (instance._onAdd) {
							   instance._onAdd(newField);
					   }
				   }
				);

				links.append(addLink);
			}

			if (instance._removeText) {
				removeLink = jQuery('<a href="javascript:;">' + instance._removeText + '</a>');

				removeLink.hide();

				removeLink.click(
				   function() {
					   instance._removeFields();
					   if (instance._onRemove) {
							   instance._onRemove();
					   }
				   }
				);

				links.append(removeLink);
			}

			if (instance._clearText) {
				clearLink = jQuery('<a href="javascript:;">' + instance._clearText + '</a>');

				clearLink.click(
				   function() {
					   instance._clearFields();
					   if (instance._onClear) {
							   instance._onClear();
					   }
				   }
				);

				links.append(clearLink);
			}

			container.after(links);
			instance._controlLinks = links;
		}
	},

	_addFields: function() {
		var instance = this;

		var container = instance._container;
		var html = instance._html.clone();

		container.append(html);

		instance._numField++;

		var removeLink = instance._controlLinks.find('a:eq(1)');

		if (removeLink.is(':hidden')) {
			removeLink.show();
		}

		return html;
	},

	_clearFields: function() {
		var instance = this;

		var container = instance._container;
		var rows = container.find(instance._rowType).not(':first');

		var confirmBox = true;

		if (instance._confirmText) {
			   confirmBox = confirm(instance._confirmText);
		}

		if (confirmBox) {
			   rows.remove();
			   instance._numField = 1;
		}
	},

	_removeFields: function() {
		var instance = this;

		var container = instance._container;
		var lastRow = container.find(instance._rowType + ':last');

		if (instance._numField > 1) {
			   lastRow.remove();
			   --instance._numField;
		}

		if (instance._numField <= 1) {
		   var removeLink = instance._controlLinks.find('a:eq(1)');

		   if (removeLink.is(':visible')) {
				   removeLink.hide();
		   }
		}
	}
});