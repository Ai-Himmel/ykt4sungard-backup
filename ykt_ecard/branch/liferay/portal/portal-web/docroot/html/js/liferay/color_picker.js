Liferay.ColorPicker = new Class({

	/*
	context (Object): A DOM object which specifies the context in which to search for the item
	hasImage: (Boolean) If set to true, it uses the "item" param or whatever image has the .use-color-picker class as the image
	item: (Object|String): A DOM object or a jQuery Selector string that specifies which field to insert the selected value into
	onChange (Function): A function that will get called whenever the color changes
	onClose (Function): A function that will get called when the color picker is closed
	*/
	initialize: function(params) {
		var instance = this;

		params = params || {};

		instance._onClose = params.onClose || null;
		instance._onChange = params.onChange || null;
		instance._context = params.context || document.body;
		instance._hasImage = params.hasImage || false;
		instance._item = jQuery(params.item || '.use-color-picker', instance._context);

		instance._baseColor = {r:255, g:0, b:0};
		instance._currentColor = {r:255, g:255, b:255};
		instance._lastValues = [0,0];

		instance._insertImages();

		instance._buildHTML();

		instance._activatePicker();
	},

	_activatePicker: function() {
		var instance = this;

		var currentColor = instance._currentColor;

		var onChange = function() {
			var r = instance._currentColor.r;
			var g = instance._currentColor.g;
			var b = instance._currentColor.b;

			var backgroundColor = 'rgb(' + r + ', ' + g + ', ' + b + ')';

			instance._baseDiv.find('.lfr-old-color').css('background-color', backgroundColor);

			if (instance._onChange) {
				instance._onChange(instance._currentColor);
			}
		};

		instance._baseDiv.find('.lfr-color').Slider(
			{
				accept : '.lfr-color-indic',
				onSlide : function(cordx, cordy, x, y) {
					instance._lastValues = [parseInt(cordx * 255 / 100), parseInt(cordy * 255 / 100)];
					instance._setGradientColor();
				},
				onChange : onChange
			}
		);

		instance._baseDiv.find('.lfr-hue').Slider(
			{
				accept : '.lfr-hue-indic',
				onSlide : function( cordx, cordy,x, y) {
					instance._setVertColor(parseInt(cordy * 255 / 100));
					instance._setGradientColor();
				},
				onChange : onChange
			}
		);
	},

	_buildHTML: function() {
		var instance = this;

		var baseDiv = jQuery('<div class="lfr-color-picker"></div>');
		var color = jQuery('<div class="lfr-color"><div class="lfr-color-indic"></div></div>');
		var hue = jQuery('<div class="lfr-hue"><div class="lfr-hue-indic"></div></div>');
		var currentColor = jQuery('<div class="lfr-current-color"><div class="lfr-old-color"></div></div>');
		var closeButton = jQuery('<div class="lfr-color-picker-close">X</div>');

		closeButton.click(
			function(event) {
				instance._toggle(event, this);
			}
		);

		baseDiv.append(color).append(hue).append(currentColor).append(closeButton);

		baseDiv.appendTo('body');

		baseDiv.hide();

		baseDiv.css(
			{
				position: 'absolute',
				zIndex: Liferay.zIndex.ALERT + 1
			}
		);

		instance._baseDiv = baseDiv;
	},

	_insertImages: function() {
		var instance = this;

		var context = instance._context;

		var items = instance._item;

		var colorPickerImgHTML = '<img class="lfr-color-picker-img" src="' + themeDisplay.getPathThemeImages() + '/color_picker/color_picker.png" />';

		if (items.length == 1) {
			var colorPickerImg;

			if (instance._hasImage) {
				colorPickerImg = items;
			}
			else {
				colorPickerImg = jQuery(colorPickerImgHTML);

				items.after(colorPickerImg);
			}

			colorPickerImg.click(
				function(event) {
					instance._toggle(event, this);
				}
			);
		}
		else {
			items.each(
				function() {
					var item = jQuery(this);
					var colorPickerImg;

					if (!instance._hasImage) {
						colorPickerImg = jQuery(colorPickerImgHTML);
					}
					else {
						colorPickerImg = item;
					}

					colorPickerImg.click(
						function(event) {
							instance._toggle(event, this);
						}
					);

					item.after(colorPickerImg);
				}
			);
		}
	},

	_setVertColor: function(indic) {
		var instance = this;

		var num = 256 / 6;
		var num2 = 256 / num;
		var color = indic;
		var color2 = color % num;

		var red = 255;
		var green = 255 - color2 * num2;
		var blue = 0;

		if (color < (num * 5)) {
			red = color2 * num2;
			green = 255;

			if (color < (num * 4)) {
				red = 0;
				blue = 255 - color2 * num2;

				if (color < (num * 3)) {
					green = color2 * num2;
					blue = 255;

					if (color < (num * 2)) {
						red = 255 - color2 * num2;
						green = 0;

						if (color < num) {
							red = 255;
							blue = color2 * num2;
						}
					}
				}
			}
		}

		instance._baseColor = {
			r: parseInt(red),
			g: parseInt(green),
			b: parseInt(blue)
		};

		instance._baseDiv.find('.lfr-color').css('background-color', 'rgb(' + instance._baseColor.r + ', ' + instance._baseColor.g + ', ' + instance._baseColor.b + ')');
	},

	_setGradientColor: function() {
		var instance = this;

		var baseColor = instance._baseColor;
		var lastValues = instance._lastValues;

		var r = instance._toBase(baseColor.r);
		var g = instance._toBase(baseColor.g);
		var b = instance._toBase(baseColor.b);

		var rX = instance._toHex(r);
		var gX = instance._toHex(g);
		var bX = instance._toHex(b);

		instance._baseDiv.find('.lfr-current-color').css('background-color', 'rgb(' + r + ', ' + g + ', ' + b + ')');

		instance._hexColor = '#' + (rX + gX + bX).toUpperCase();

		instance._currentInput.val(instance._hexColor);

		instance._currentColor = {r: r, g: g, b: b};
	},

	_toggle: function(event, obj) {
		var instance = this;

		var item = jQuery(obj);

		var dimensions = item.offset();

		instance._currentInput = item.prev();

		var baseDiv = instance._baseDiv;

		if (baseDiv.is(':visible')) {
			baseDiv.hide();

			if (instance._item.is('input')) {
				instance._item.trigger('blur');
			}

			if (instance._onClose) {
				instance._onClose();
			}
		}
		else {
			baseDiv.show();

			if (instance._item.is('input')) {
				instance._item.trigger('focus');
			}

			baseDiv.css(
				{
					top: dimensions.top + 'px',
					left: dimensions.left + 25 + 'px'
				}
			);
		}
	},

	_toBase: function(colorVal) {
		var instance = this;

		var lastValues = instance._lastValues;

		return Math.round((1 - (1 - (colorVal / 255)) * (lastValues[0] / 255)) * (255 - lastValues[1]));
	},

	_toHex: function(color) {
		var instance = this;

		color = parseInt(color).toString(16);

		if (color.length < 2) {
			return "0" + color;
		}
		else {
			return color;
		}
	},

	_toRGB: function(color) {
		var instance = this;

		color = color.replace('#', '');

		if (color.length == 6 || color.length == 3) {
			var r, g, b;

			if (color.length == 6) {
				r = color.substring(0, 2);
				g = color.substring(2, 4);
				b = color.substring(4, 6);
			}
			else if (color.length == 3) {
				r = color.substring(0, 1);
				g = color.substring(1, 2);
				b = color.substring(2, 3);

				r = r + r;
				g = g + g;
				b = b + b;
			}

			r = parseInt(r, 16);
			g = parseInt(g, 16);
			b = parseInt(b, 16);

			return {r: r, g: g, b: b};
		}

		return null;
	}
});