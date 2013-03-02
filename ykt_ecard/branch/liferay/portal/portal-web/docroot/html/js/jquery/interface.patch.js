// Interface patches

//Autocomplete patch
//Adds support for JSON data retrieval.

jQuery.iAuto = {
	helper : null,
	content : null,
	iframe: null,
	timer : null,
	lastValue: null,
	currentValue: null,
	subject: null,
	selectedItem : null,
	items: null,

	empty : function()
	{
		jQuery.iAuto.content.empty();
		if (jQuery.iAuto.iframe) {
			jQuery.iAuto.iframe.hide();
		}
	},

	clear : function()
	{
		if (jQuery.iAuto.subject) {
			jQuery.iAuto.items = null;
			jQuery.iAuto.selectedItem = null;
			jQuery.iAuto.lastValue = jQuery.iAuto.subject.value;
			if(jQuery.iAuto.helper.css('display') == 'block') {
				if (jQuery.iAuto.subject.autoCFG.fx) {
					switch(jQuery.iAuto.subject.autoCFG.fx.type) {
						case 'fade':
							jQuery.iAuto.helper.fadeOut(jQuery.iAuto.subject.autoCFG.fx.duration, jQuery.iAuto.empty);
							break;
						case 'slide':
							jQuery.iAuto.helper.SlideOutUp(jQuery.iAuto.subject.autoCFG.fx.duration, jQuery.iAuto.empty);
							break;
						case 'blind':
							jQuery.iAuto.helper.BlindUp(jQuery.iAuto.subject.autoCFG.fx.duration, jQuery.iAuto.empty);
							break;
					}
				} else {
					jQuery.iAuto.helper.hide();
				}
				if (jQuery.iAuto.subject.autoCFG.onHide)
					jQuery.iAuto.subject.autoCFG.onHide.apply(jQuery.iAuto.subject, [jQuery.iAuto.helper, jQuery.iAuto.iframe]);
			} else {
				jQuery.iAuto.empty();
			}
		}
		window.clearTimeout(jQuery.iAuto.timer);
	},

	update : function ()
	{
		var subject = jQuery.iAuto.subject;
		var subjectValue = jQuery.iAuto.getFieldValues(subject);

		var dataSource = subject.autoCFG.source;
		var dataSourceType = subject.autoCFG.dataSourceType;
		var isXML = subject.autoCFG.isXML;

		if (subject && subjectValue.item != jQuery.iAuto.lastValue && subjectValue.item.length >= subject.autoCFG.minchars) {
			jQuery.iAuto.lastValue = subjectValue.item;
			jQuery.iAuto.currentValue = subjectValue.item;

			data = {
				field: jQuery(subject).attr('name')||'field',
				value: subjectValue.item
			};
			if (typeof dataSource == 'string') {
				jQuery.ajax(
					{
						type: 'POST',
						data: jQuery.param(data),
						dataType: (isXML) ? 'xml' : 'json',
						success: function(response) {
							jQuery.iAuto.handleData(response, subject, subjectValue, isXML);
						},
						url : dataSource
					}
				);
			} else if(typeof dataSource == 'function') {
				var returnedData = dataSource(data);
				jQuery.iAuto.handleData(returnedData, subject, subjectValue, isXML);
			}
		}
	},

	writeItems : function(subject, toWrite)
	{
		jQuery.iAuto.content.html(toWrite);
		jQuery.iAuto.items = jQuery('li', jQuery.iAuto.content.get(0));
		jQuery.iAuto.items
			.mouseover(jQuery.iAuto.hoverItem)
			.bind('click', jQuery.iAuto.clickItem);
		var position = jQuery.iUtil.getPosition(subject);
		var size = jQuery.iUtil.getSize(subject);
		jQuery.iAuto.helper
			.css('top', position.y + size.hb + 'px')
			.css('left', position.x +  'px')
			.addClass(subject.autoCFG.helperClass);
		if (jQuery.iAuto.iframe) {
			jQuery.iAuto.iframe
				.css('display', 'block')
				.css('top', position.y + size.hb + 'px')
				.css('left', position.x +  'px')
				.css('width', jQuery.iAuto.helper.css('width'))
				.css('height', jQuery.iAuto.helper.css('height'));
		}
		jQuery.iAuto.selectedItem = 0;
		jQuery.iAuto.items.get(0).className = subject.autoCFG.selectClass;
		jQuery.iAuto.applyOn(subject,subject.autoCFG.lastSuggestion[0], 'onHighlight');

		if (jQuery.iAuto.helper.css('display') == 'none') {
			if (subject.autoCFG.inputWidth) {
				var borders = jQuery.iUtil.getPadding(subject, true);
				var paddings = jQuery.iUtil.getBorder(subject, true);
				jQuery.iAuto.helper.css('width', subject.offsetWidth - (jQuery.boxModel ? (borders.l + borders.r + paddings.l + paddings.r) : 0 ) + 'px');
			}
			if (subject.autoCFG.fx) {
				switch(subject.autoCFG.fx.type) {
					case 'fade':
						jQuery.iAuto.helper.fadeIn(subject.autoCFG.fx.duration);
						break;
					case 'slide':
						jQuery.iAuto.helper.SlideInUp(subject.autoCFG.fx.duration);
						break;
					case 'blind':
						jQuery.iAuto.helper.BlindDown(subject.autoCFG.fx.duration);
						break;
				}
			} else {
				jQuery.iAuto.helper.show();
			}

			if (jQuery.iAuto.subject.autoCFG.onShow)
				jQuery.iAuto.subject.autoCFG.onShow.apply(jQuery.iAuto.subject, [jQuery.iAuto.helper, jQuery.iAuto.iframe]);
		}
	},

	checkCache : function()
	{
		var subject = this;
		if (subject.autoCFG.lastSuggestion) {

			jQuery.iAuto.lastValue = subject.value;
			jQuery.iAuto.currentValue = subject.value;

			var isXML = subject.autoCFG.isXML;

			var iterator = function(nr)
				{
					var value, text, testValue;
					if (isXML) {
						value = jQuery('value', this).text();
						text = jQuery('text', this).text();
					} else {
						value = this.value;
						text = this.text;
					}
					testValue = value.toLowerCase();
					inputValue = subject.value.toLowerCase();

					if (testValue.indexOf(inputValue) == 0) {
						toWrite += '<li rel="' + value + '" dir="' + nr + '" style="cursor: default;">' + text + '</li>';
					}
				};

			var toWrite = '';

			if (isXML) {
				subject.autoCFG.lastSuggestion.each(iterator);
			} else {
				jQuery.each(subject.autoCFG.lastSuggestion, iterator);
			}

			if (toWrite != '') {
				jQuery.iAuto.writeItems(subject, toWrite);

				this.autoCFG.inCache = true;
				return;
			}
		}
		subject.autoCFG.lastSuggestion = null;
		this.autoCFG.inCache = false;
	},

	selection : function(field, start, end)
	{
		if (field.createTextRange) {
			var selRange = field.createTextRange();
			selRange.collapse(true);
			selRange.moveStart("character", start);
			selRange.moveEnd("character", - end + start);
			selRange.select();
		} else if (field.setSelectionRange) {
			field.setSelectionRange(start, end);
		} else {
			if (field.selectionStart) {
				field.selectionStart = start;
				field.selectionEnd = end;
			}
		}
		field.focus();
	},

	getSelectionStart : function(field)
	{
		if (field.selectionStart)
			return field.selectionStart;
		else if(field.createTextRange) {
			var selRange = document.selection.createRange();
			var selRange2 = selRange.duplicate();
			return 0 - selRange2.moveStart('character', -100000);
			//result.end = result.start + range.text.length;
			/*var selRange = document.selection.createRange();
			var isCollapsed = selRange.compareEndPoints("StartToEnd", selRange) == 0;
			if (!isCollapsed)
				selRange.collapse(true);
			var bookmark = selRange.getBookmark();
			return bookmark.charCodeAt(2) - 2;*/
		}
	},

	getFieldValues : function(field)
	{
		var fieldData = {
			value: field.value,
			pre: '',
			post: '',
			item: ''
		};

		if(field.autoCFG.multiple) {
			var finishedPre = false;
			var selectionStart = jQuery.iAuto.getSelectionStart(field)||0;
			var chunks = fieldData.value.split(field.autoCFG.multipleSeparator);
			for (var i=0; i<chunks.length; i++) {
				if(
					(fieldData.pre.length + chunks[i].length >= selectionStart
					 ||
					selectionStart == 0)
					 &&
					!finishedPre
				) {
					if (fieldData.pre.length <= selectionStart)
						fieldData.item = chunks[i];
					else
						fieldData.post += chunks[i] + (chunks[i] != '' ? field.autoCFG.multipleSeparator : '');
					finishedPre = true;
				} else if (finishedPre){
					fieldData.post += chunks[i] + (chunks[i] != '' ? field.autoCFG.multipleSeparator : '');
				}
				if(!finishedPre) {
					fieldData.pre += chunks[i] + (chunks.length > 1 ? field.autoCFG.multipleSeparator : '');
				}
			}
		} else {
			fieldData.item = fieldData.value;
		}
		return fieldData;
	},

	autocomplete : function(e)
	{
		window.clearTimeout(jQuery.iAuto.timer);
		var subject = jQuery.iAuto.getFieldValues(this);

		var pressedKey = e.charCode || e.keyCode || -1;
		if (/13|27|35|36|38|40|9/.test(pressedKey) && jQuery.iAuto.items) {
			if (window.event) {
				window.event.cancelBubble = true;
				window.event.returnValue = false;
			} else {
				e.preventDefault();
				e.stopPropagation();
			}
			if (jQuery.iAuto.selectedItem != null)
				jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).className = '';
			else
				jQuery.iAuto.selectedItem = -1;
			switch(pressedKey) {
				//enter
				case 9:
				case 13:
					if (jQuery.iAuto.selectedItem == -1)
						jQuery.iAuto.selectedItem = 0;
					var selectedItem = jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0);
					var valueToAdd = selectedItem.getAttribute('rel');
					this.value = subject.pre + valueToAdd + this.autoCFG.multipleSeparator + subject.post;
					jQuery.iAuto.lastValue = subject.item;
					jQuery.iAuto.selection(
						this,
						subject.pre.length + valueToAdd.length + this.autoCFG.multipleSeparator.length,
						subject.pre.length + valueToAdd.length + this.autoCFG.multipleSeparator.length
					);
					jQuery.iAuto.clear();
					if (this.autoCFG.onSelect) {
						iteration = parseInt(selectedItem.getAttribute('dir'))||0;
						jQuery.iAuto.applyOn(this,this.autoCFG.lastSuggestion[iteration], 'onSelect');
					}
					if (this.scrollIntoView)
						this.scrollIntoView(false);
					return pressedKey != 13;
					break;
				//escape
				case 27:
					this.value = subject.pre + jQuery.iAuto.lastValue + this.autoCFG.multipleSeparator + subject.post;
					this.autoCFG.lastSuggestion = null;
					jQuery.iAuto.clear();
					if (this.scrollIntoView)
						this.scrollIntoView(false);
					return false;
					break;
				//end
				case 35:
					jQuery.iAuto.selectedItem = jQuery.iAuto.items.size() - 1;
					break;
				//home
				case 36:
					jQuery.iAuto.selectedItem = 0;
					break;
				//up
				case 38:
					jQuery.iAuto.selectedItem --;
					if (jQuery.iAuto.selectedItem < 0)
						jQuery.iAuto.selectedItem = jQuery.iAuto.items.size() - 1;
					break;
				case 40:
					jQuery.iAuto.selectedItem ++;
					if (jQuery.iAuto.selectedItem == jQuery.iAuto.items.size())
						jQuery.iAuto.selectedItem = 0;
					break;
			}
			jQuery.iAuto.applyOn(this,this.autoCFG.lastSuggestion[jQuery.iAuto.selectedItem||0], 'onHighlight');
			jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).className = this.autoCFG.selectClass;
			if (jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).scrollIntoView)
				jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).scrollIntoView(false);
			if(this.autoCFG.autofill) {
				var valToAdd = jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).getAttribute('rel');
				this.value = subject.pre + valToAdd + this.autoCFG.multipleSeparator + subject.post;
				if(jQuery.iAuto.lastValue.length != valToAdd.length)
					jQuery.iAuto.selection(
						this,
						subject.pre.length + jQuery.iAuto.lastValue.length,
						subject.pre.length + valToAdd.length
					);
			}
			return false;
		}
		jQuery.iAuto.checkCache.apply(this);

		if (this.autoCFG.inCache == false) {
			if (subject.item != jQuery.iAuto.lastValue && subject.item.length >= this.autoCFG.minchars)
				jQuery.iAuto.timer = window.setTimeout(jQuery.iAuto.update, this.autoCFG.delay);
			if (jQuery.iAuto.items) {
				jQuery.iAuto.clear();
			}
		}
		return true;
	},

	applyOn: function(field, item, type)
	{
		var dataSource = field.autoCFG.source;

		if (field.autoCFG[type]) {
			var data = {};
			if (field.autoCFG.isXML) {
				childs = item.getElementsByTagName('*');
				for(i=0; i<childs.length; i++){
					data[childs[i].tagName] = childs[i].firstChild.nodeValue;
				}
			} else {
				data = item;
			}
			field.autoCFG[type].apply(field, [data]);
		}
	},

	hoverItem : function(e)
	{
		if (jQuery.iAuto.items) {
			if (jQuery.iAuto.selectedItem != null)
				jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).className = '';
			jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).className = '';
			jQuery.iAuto.selectedItem = parseInt(this.getAttribute('dir'))||0;
			jQuery.iAuto.items.get(jQuery.iAuto.selectedItem||0).className = jQuery.iAuto.subject.autoCFG.selectClass;
		}
	},

	clickItem : function(event)
	{
		window.clearTimeout(jQuery.iAuto.timer);

		event = event || jQuery.event.fix( window.event );
		event.preventDefault();
		event.stopPropagation();
		var subject = jQuery.iAuto.getFieldValues(jQuery.iAuto.subject);
		var valueToAdd = this.getAttribute('rel');
		jQuery.iAuto.subject.value = subject.pre + valueToAdd + jQuery.iAuto.subject.autoCFG.multipleSeparator + subject.post;
		jQuery.iAuto.lastValue = this.getAttribute('rel');
		jQuery.iAuto.selection(
			jQuery.iAuto.subject,
			subject.pre.length + valueToAdd.length + jQuery.iAuto.subject.autoCFG.multipleSeparator.length,
			subject.pre.length + valueToAdd.length + jQuery.iAuto.subject.autoCFG.multipleSeparator.length
		);
		jQuery.iAuto.clear();
		if (jQuery.iAuto.subject.autoCFG.onSelect) {
			iteration = parseInt(this.getAttribute('dir'))||0;
			jQuery.iAuto.applyOn(jQuery.iAuto.subject,jQuery.iAuto.subject.autoCFG.lastSuggestion[iteration], 'onSelect');
		}

		return false;
	},

	protect : function(e)
	{
		pressedKey = e.charCode || e.keyCode || -1;
		if (/13|27|35|36|38|40/.test(pressedKey) && jQuery.iAuto.items) {
			if (window.event) {
				window.event.cancelBubble = true;
				window.event.returnValue = false;
			} else {
				e.preventDefault();
				e.stopPropagation();
			}
			return false;
		}
	},

	build : function(options)
	{
		if (!options.source || !jQuery.iUtil) {
			return;
		}

		if (!jQuery.iAuto.helper) {
			if (jQuery.browser.msie) {
				jQuery('body', document).append('<iframe style="display:none;position:absolute;filter:progid:DXImageTransform.Microsoft.Alpha(opacity=0);" id="autocompleteIframe" src="javascript:false;" frameborder="0" scrolling="no"></iframe>');
				jQuery.iAuto.iframe = jQuery('#autocompleteIframe');
			}
			jQuery('body', document).append('<div id="autocompleteHelper" style="position: absolute; top: 0; left: 0; z-index: 30001; display: none;"><ul style="margin: 0;padding: 0; list-style: none; z-index: 30002;">&nbsp;</ul></div>');
			jQuery.iAuto.helper = jQuery('#autocompleteHelper');
			jQuery.iAuto.content = jQuery('ul', jQuery.iAuto.helper);
		}

		return this.each(
			function()
			{
				if (this.tagName != 'INPUT' && this.getAttribute('type') != 'text' )
					return;
				this.autoCFG = {};
				this.autoCFG.source = options.source;
				this.autoCFG.minchars = Math.abs(parseInt(options.minchars)||1);
				this.autoCFG.helperClass = options.helperClass ? options.helperClass : '';
				this.autoCFG.selectClass = options.selectClass ? options.selectClass : '';
				this.autoCFG.onSelect = options.onSelect && options.onSelect.constructor == Function ? options.onSelect : null;
				this.autoCFG.onShow = options.onShow && options.onShow.constructor == Function ? options.onShow : null;
				this.autoCFG.onHide = options.onHide && options.onHide.constructor == Function ? options.onHide : null;
				this.autoCFG.onHighlight = options.onHighlight && options.onHighlight.constructor == Function ? options.onHighlight : null;
				this.autoCFG.inputWidth = options.inputWidth||false;
				this.autoCFG.dataSourceType = options.dataSourceType || 'xml';
				this.autoCFG.dataSourceType = this.autoCFG.dataSourceType.toLowerCase();
				this.autoCFG.isXML = (this.autoCFG.dataSourceType == 'xml');
				this.autoCFG.multiple = options.multiple||false;
				this.autoCFG.multipleSeparator = this.autoCFG.multiple ? (options.multipleSeparator||', '):'';
				this.autoCFG.autofill = options.autofill ? true : false;
				this.autoCFG.delay = Math.abs(parseInt(options.delay)||1000);
				if (options.fx && options.fx.constructor == Object) {
					if (!options.fx.type || !/fade|slide|blind/.test(options.fx.type)) {
						options.fx.type = 'slide';
					}
					if (options.fx.type == 'slide' && !jQuery.fx.slide)
						return;
					if (options.fx.type == 'blind' && !jQuery.fx.BlindDirection)
						return;

					options.fx.duration = Math.abs(parseInt(options.fx.duration)||400);
					if (options.fx.duration > this.autoCFG.delay) {
						options.fx.duration = this.autoCFG.delay - 100;
					}
					this.autoCFG.fx = options.fx;
				}
				this.autoCFG.lastSuggestion = null;
				this.autoCFG.inCache = false;

				jQuery(this)
					.attr('autocomplete', 'off')
					.focus(
						function()
						{
							jQuery.iAuto.subject = this;
							jQuery.iAuto.lastValue = this.value;
						}
					)
					.keypress(jQuery.iAuto.protect)
					.keyup(jQuery.iAuto.autocomplete)

					.blur(
						function()
						{
							jQuery.iAuto.timer = window.setTimeout(jQuery.iAuto.clear, 200);
						}
					);
			}
		);
	}
};

jQuery.iAuto.handleData = function(response, subject, subjectValue, isXML) {

	if (response.length == 0) {
		return;
	}

	if (isXML) {
		subject.autoCFG.lastSuggestion = jQuery('item',response);
	} else {
		subject.autoCFG.lastSuggestion = response;
	}
	size = subject.autoCFG.lastSuggestion.length;
	if (size > 0) {
		var toWrite = '';

		var iterator = function(nr)
			{
				var text, value;
				if (isXML) {
					text = jQuery('text', this).text();
					value = jQuery('value', this).text();
				} else {
					text = this.text;
					value = this.value;
				}
				toWrite += '<li rel="' + value + '" dir="' + nr + '" style="cursor: default;">' + text + '</li>';
		};

		if (isXML) {
			subject.autoCFG.lastSuggestion.each(iterator);
		} else {
			jQuery.each(response, iterator);
		}

		if (subject.autoCFG.autofill) {
			var valueToAdd;

			if (isXML) {
				valueToAdd = jQuery('value', subject.autoCFG.lastSuggestion[0]).text();
			} else {
				valueToAdd = subject.autoCFG.lastSuggestion[0].value;
			}
			subject.value = subjectValue.pre + valueToAdd + subject.autoCFG.multipleSeparator + subjectValue.post;
			jQuery.iAuto.selection(
				subject,
				subjectValue.item.length != valueToAdd.length ? (subjectValue.pre.length + subjectValue.item.length) : valueToAdd.length,
				subjectValue.item.length != valueToAdd.length ? (subjectValue.pre.length + valueToAdd.length) : valueToAdd.length
			);
		}

		if (size > 0) {
			jQuery.iAuto.writeItems(subject, toWrite);
		} else {
			jQuery.iAuto.clear();
		}
	} else {
		jQuery.iAuto.clear();
	}
};

jQuery.fn.Autocomplete = jQuery.iAuto.build;

/* ---------- Patches related to the jQuery 1.1.3 bug in 'find' method ---------- */

jQuery.iDrag.build = function(o)
	{
		if (!jQuery.iDrag.helper) {
			jQuery('body',document).append('<div id="dragHelper"></div>');
			jQuery.iDrag.helper = jQuery('#dragHelper');
			var el = jQuery.iDrag.helper[0];
			var els = el.style;
			els.position = 'absolute';
			els.display = 'none';
			els.cursor = 'move';
			els.listStyle = 'none';
			els.overflow = 'hidden';
			if (window.ActiveXObject) {
				el.unselectable = "on";
			} else {
				els.mozUserSelect = 'none';
				els.userSelect = 'none';
				els.KhtmlUserSelect = 'none';
			}
		}
		if (!o) {
			o = {};
		}

		return this.each(
			function()
			{
				if (this.isDraggable || !jQuery.iUtil)
					return;
				if (window.ActiveXObject) {
					this.onselectstart = function(){return false;};
					this.ondragstart = function(){return false;};
				}
				var el = this;
				var dhe = o.handle ? jQuery(o.handle, this) : jQuery(this);

				this.dragCfg = {
					dhe: dhe,
					revert : o.revert ? true : false,
					ghosting : o.ghosting ? true : false,
					so : o.so ? o.so : false,
					si : o.si ? o.si : false,
					insideParent : o.insideParent ? o.insideParent : false,
					zIndex : o.zIndex ? parseInt(o.zIndex)||0 : false,
					opacity : o.opacity ? parseFloat(o.opacity) : false,
					fx : parseInt(o.fx)||null,
					hpc : o.hpc ? o.hpc : false,
					onDragModifier : {},
					pointer : {},
					onStart : o.onStart && o.onStart.constructor == Function ? o.onStart : false,
					onStop : o.onStop && o.onStop.constructor == Function ? o.onStop : false,
					onChange : o.onChange && o.onChange.constructor == Function ? o.onChange : false,
					axis : /vertically|horizontally/.test(o.axis) ? o.axis : false,
					snapDistance : o.snapDistance ? parseInt(o.snapDistance)||0 : 0,
					cursorAt: o.cursorAt ? o.cursorAt : false,
					autoSize : o.autoSize ? true : false,
					frameClass : o.frameClass || false

				};
				if (o.onDragModifier && o.onDragModifier.constructor == Function)
					this.dragCfg.onDragModifier.user = o.onDragModifier;
				if (o.onDrag && o.onDrag.constructor == Function)
					this.dragCfg.onDrag = o.onDrag;
				if (o.containment && ((o.containment.constructor == String && (o.containment == 'parent' || o.containment == 'document')) || (o.containment.constructor == Array && o.containment.length == 4) )) {
					this.dragCfg.containment = o.containment;
				}
				if(o.fractions) {
					this.dragCfg.fractions = o.fractions;
				}
				if(o.grid){
					if(typeof o.grid == 'number'){
						this.dragCfg.gx = parseInt(o.grid)||1;
						this.dragCfg.gy = parseInt(o.grid)||1;
					} else if (o.grid.length == 2) {
						this.dragCfg.gx = parseInt(o.grid[0])||1;
						this.dragCfg.gy = parseInt(o.grid[1])||1;
					}
				}
				if (o.onSlide && o.onSlide.constructor == Function) {
					this.dragCfg.onSlide = o.onSlide;
				}

				this.isDraggable = true;
				dhe.each(
					function(){
						this.dragElem = el;

						if (jQuery.browser.msie) {
							this.unselectable = "on";
						}
						else {
							this.style.MozUserSelect = 'none';
							this.style.userSelect = 'none';
							this.style.KhtmlUserSelect = 'none';
						}
					}
				);
				dhe.bind('mousedown', jQuery.iDrag.draginit);
			}
		)
	};
jQuery.fn.Draggable = jQuery.iDrag.build;