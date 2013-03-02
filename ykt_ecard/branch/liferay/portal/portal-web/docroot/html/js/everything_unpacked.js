(function(){
/*
 * jQuery 1.1.4 - New Wave Javascript
 *
 * Copyright (c) 2007 John Resig (jquery.com)
 * Dual licensed under the MIT (MIT-LICENSE.txt)
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 * $Date: 2007-08-23 21:49:27 -0400 (Thu, 23 Aug 2007) $
 * $Rev: 2862 $
 */
// Map over jQuery in case of overwrite
if ( typeof jQuery != "undefined" )
	var _jQuery = jQuery;

var jQuery = window.jQuery = function(a,c) {
	// If the context is global, return a new object
	if ( window == this || !this.init )
		return new jQuery(a,c);
	
	return this.init(a,c);
};

// Map over the $ in case of overwrite
if ( typeof $ != "undefined" )
	var _$ = $;
	
// Map the jQuery namespace to the '$' one
window.$ = jQuery;

var quickExpr = /^[^<]*(<(.|\s)+>)[^>]*$|^#(\w+)$/;

jQuery.fn = jQuery.prototype = {
	init: function(a,c) {
		// Make sure that a selection was provided
		a = a || document;

		// Handle HTML strings
		if ( typeof a  == "string" ) {
			var m = quickExpr.exec(a);
			if ( m && (m[1] || !c) ) {
				// HANDLE: $(html) -> $(array)
				if ( m[1] )
					a = jQuery.clean( [ m[1] ] );

				// HANDLE: $("#id")
				else {
					var tmp = document.getElementById( m[3] );
					if ( tmp )
						// Handle the case where IE and Opera return items
						// by name instead of ID
						if ( tmp.id != m[3] ) {
							return jQuery().find( a );
						}else {
							this[0] = tmp;
							this.length = 1;
							return this;
						}
					else
						a = [];
				}

			// HANDLE: $(expr)
			} else
				return new jQuery( c ).find( a );

		// HANDLE: $(function)
		// Shortcut for document ready
		} else if ( jQuery.isFunction(a) )
			return new jQuery(document)[ jQuery.fn.ready ? "ready" : "load" ]( a );

		return this.setArray(
			// HANDLE: $(array)
			a.constructor == Array && a ||

			// HANDLE: $(arraylike)
			// Watch for when an array-like object is passed as the selector
			(a.jquery || a.length && a != window && !a.nodeType && a[0] != undefined && a[0].nodeType) && jQuery.makeArray( a ) ||

			// HANDLE: $(*)
			[ a ] );
	},
	jquery: "1.1.4",

	size: function() {
		return this.length;
	},
	
	length: 0,

	get: function( num ) {
		return num == undefined ?

			// Return a 'clean' array
			jQuery.makeArray( this ) :

			// Return just the object
			this[num];
	},
	pushStack: function( a ) {
		var ret = jQuery(a);
		ret.prevObject = this;
		return ret;
	},
	setArray: function( a ) {
		this.length = 0;
		Array.prototype.push.apply( this, a );
		return this;
	},
	each: function( fn, args ) {
		return jQuery.each( this, fn, args );
	},
	index: function( obj ) {
		var pos = -1;
		this.each(function(i){
			if ( this == obj ) pos = i;
		});
		return pos;
	},

	attr: function( key, value, type ) {
		var obj = key;
		
		// Look for the case where we're accessing a style value
		if ( key.constructor == String )
			if ( value == undefined )
				return this.length && jQuery[ type || "attr" ]( this[0], key ) || undefined;
			else {
				obj = {};
				obj[ key ] = value;
			}
		
		// Check to see if we're setting style values
		return this.each(function(index){
			// Set all the styles
			for ( var prop in obj )
				jQuery.attr(
					type ? this.style : this,
					prop, jQuery.prop(this, obj[prop], type, index, prop)
				);
		});
	},

	css: function( key, value ) {
		return this.attr( key, value, "curCSS" );
	},

	text: function(e) {
		if ( typeof e != "object" && e != null )
			return this.empty().append( document.createTextNode( e ) );

		var t = "";
		jQuery.each( e || this, function(){
			jQuery.each( this.childNodes, function(){
				if ( this.nodeType != 8 )
					t += this.nodeType != 1 ?
						this.nodeValue : jQuery.fn.text([ this ]);
			});
		});
		return t;
	},

	wrap: function() {
		// The elements to wrap the target around
		var a, args = arguments;

		// Wrap each of the matched elements individually
		return this.each(function(){
			if ( !a )
				a = jQuery.clean(args, this.ownerDocument);

			// Clone the structure that we're using to wrap
			var b = a[0].cloneNode(true);

			// Insert it before the element to be wrapped
			this.parentNode.insertBefore( b, this );

			// Find the deepest point in the wrap structure
			while ( b.firstChild )
				b = b.firstChild;

			// Move the matched element to within the wrap structure
			b.appendChild( this );
		});
	},
	append: function() {
		return this.domManip(arguments, true, 1, function(a){
			this.appendChild( a );
		});
	},
	prepend: function() {
		return this.domManip(arguments, true, -1, function(a){
			this.insertBefore( a, this.firstChild );
		});
	},
	before: function() {
		return this.domManip(arguments, false, 1, function(a){
			this.parentNode.insertBefore( a, this );
		});
	},
	after: function() {
		return this.domManip(arguments, false, -1, function(a){
			this.parentNode.insertBefore( a, this.nextSibling );
		});
	},
	end: function() {
		return this.prevObject || jQuery([]);
	},
	find: function(t) {
		var data = jQuery.map(this, function(a){ return jQuery.find(t,a); });
		return this.pushStack( /[^+>] [^+>]/.test( t ) || t.indexOf("..") > -1 ?
			jQuery.unique( data ) : data );
	},
	clone: function(deep) {
		deep = deep != undefined ? deep : true;
		var $this = this.add(this.find("*"));
		if (jQuery.browser.msie) {
			// Need to remove events on the element and its descendants
			$this.each(function() {
				this._$events = {};
				for (var type in this.$events)
					this._$events[type] = jQuery.extend({},this.$events[type]);
			}).unbind();
		}

		// Do the clone
		var r = this.pushStack( jQuery.map( this, function(a){
			return a.cloneNode( deep );
		}) );

		if (jQuery.browser.msie) {
			$this.each(function() {
				// Add the events back to the original and its descendants
				var events = this._$events;
				for (var type in events)
					for (var handler in events[type])
						jQuery.event.add(this, type, events[type][handler], events[type][handler].data);
				this._$events = null;
			});
		}

		// copy form values over
		if (deep) {
			var inputs = r.add(r.find('*')).filter('select,input[@type=checkbox]');
			$this.filter('select,input[@type=checkbox]').each(function(i) {
				if (this.selectedIndex)
					inputs[i].selectedIndex = this.selectedIndex;
				if (this.checked)
					inputs[i].checked = true;
			});
		}

		// Return the cloned set
		return r;
	},

	filter: function(t) {
		return this.pushStack(
			jQuery.isFunction( t ) &&
			jQuery.grep(this, function(el, index){
				return t.apply(el, [index]);
			}) ||

			jQuery.multiFilter(t,this) );
	},

	not: function(t) {
		return this.pushStack(
			t.constructor == String &&
			jQuery.multiFilter(t, this, true) ||

			jQuery.grep(this, function(a) {
				return ( t.constructor == Array || t.jquery )
					? jQuery.inArray( a, t ) < 0
					: a != t;
			})
		);
	},

	add: function(t) {
		return this.pushStack( jQuery.merge(
			this.get(),
			t.constructor == String ?
				jQuery(t).get() :
				t.length != undefined && (!t.nodeName || t.nodeName == "FORM") ?
					t : [t] )
		);
	},
	is: function(expr) {
		return expr ? jQuery.multiFilter(expr,this).length > 0 : false;
	},

	val: function( val ) {
		return val == undefined ?
			( this.length ? this[0].value : null ) :
			this.attr( "value", val );
	},

	html: function( val ) {
		return val == undefined ?
			( this.length ? this[0].innerHTML : null ) :
			this.empty().append( val );
	},

	slice: function() {
		return this.pushStack( Array.prototype.slice.apply( this, arguments ) );
	},
	domManip: function(args, table, dir, fn){
		var clone = this.length > 1, a; 

		return this.each(function(){
			if ( !a ) {
				a = jQuery.clean(args, this.ownerDocument);
				if ( dir < 0 )
					a.reverse();
			}

			var obj = this;

			if ( table && jQuery.nodeName(this, "table") && jQuery.nodeName(a[0], "tr") )
				obj = this.getElementsByTagName("tbody")[0] || this.appendChild(document.createElement("tbody"));

			jQuery.each( a, function(){
				if ( jQuery.nodeName(this, "script") ) {
					if ( this.src )
						jQuery.ajax({ url: this.src, async: false, dataType: "script" });
					else
						jQuery.globalEval( this.text || this.textContent || this.innerHTML || "" );
				} else
					fn.apply( obj, [ clone ? this.cloneNode(true) : this ] );
			});
		});
	}
};

jQuery.extend = jQuery.fn.extend = function() {
	// copy reference to target object
	var target = arguments[0] || {}, a = 1, al = arguments.length, deep = false;

	// Handle a deep copy situation
	if ( target.constructor == Boolean ) {
		deep = target;
		target = arguments[1] || {};
	}

	// extend jQuery itself if only one argument is passed
	if ( al == 1 ) {
		target = this;
		a = 0;
	}

	var prop;

	for ( ; a < al; a++ )
		// Only deal with non-null/undefined values
		if ( (prop = arguments[a]) != null )
			// Extend the base object
			for ( var i in prop ) {
				// Prevent never-ending loop
				if ( target == prop[i] )
					continue;

				// Recurse if we're merging object values
				if ( deep && typeof prop[i] == 'object' && target[i] )
					jQuery.extend( target[i], prop[i] );

				// Don't bring in undefined values
				else if ( prop[i] != undefined )
					target[i] = prop[i];
			}

	// Return the modified object
	return target;
};

jQuery.extend({
	noConflict: function(deep) {
		window.$ = _$;
		if ( deep )
			window.jQuery = _jQuery;
		return jQuery;
	},

	// This may seem like some crazy code, but trust me when I say that this
	// is the only cross-browser way to do this. --John
	isFunction: function( fn ) {
		return !!fn && typeof fn != "string" && !fn.nodeName && 
			fn.constructor != Array && /function/i.test( fn + "" );
	},
	
	// check if an element is in a XML document
	isXMLDoc: function(elem) {
		return elem.documentElement && !elem.body ||
			elem.tagName && elem.ownerDocument && !elem.ownerDocument.body;
	},

	// Evalulates a script in a global context
	// Evaluates Async. in Safari 2 :-(
	globalEval: function( data ) {
		data = jQuery.trim( data );
		if ( data ) {
			if ( window.execScript )
				window.execScript( data );
			else if ( jQuery.browser.safari )
				// safari doesn't provide a synchronous global eval
				window.setTimeout( data, 0 );
			else
				eval.call( window, data );
		}
	},

	nodeName: function( elem, name ) {
		return elem.nodeName && elem.nodeName.toUpperCase() == name.toUpperCase();
	},
	// args is for internal usage only
	each: function( obj, fn, args ) {
		if ( args ) {
			if ( obj.length == undefined )
				for ( var i in obj )
					fn.apply( obj[i], args );
			else
				for ( var i = 0, ol = obj.length; i < ol; i++ )
					if ( fn.apply( obj[i], args ) === false ) break;

		// A special, fast, case for the most common use of each
		} else {
			if ( obj.length == undefined )
				for ( var i in obj )
					fn.call( obj[i], i, obj[i] );
			else
				for ( var i = 0, ol = obj.length, val = obj[0]; 
					i < ol && fn.call(val,i,val) !== false; val = obj[++i] ){}
		}

		return obj;
	},
	
	prop: function(elem, value, type, index, prop){
			// Handle executable functions
			if ( jQuery.isFunction( value ) )
				value = value.call( elem, [index] );
				
			// exclude the following css properties to add px
			var exclude = /z-?index|font-?weight|opacity|zoom|line-?height/i;

			// Handle passing in a number to a CSS property
			return value && value.constructor == Number && type == "curCSS" && !exclude.test(prop) ?
				value + "px" :
				value;
	},

	className: {
		// internal only, use addClass("class")
		add: function( elem, c ){
			jQuery.each( (c || "").split(/\s+/), function(i, cur){
				if ( !jQuery.className.has( elem.className, cur ) )
					elem.className += ( elem.className ? " " : "" ) + cur;
			});
		},

		// internal only, use removeClass("class")
		remove: function( elem, c ){
			elem.className = c != undefined ?
				jQuery.grep( elem.className.split(/\s+/), function(cur){
					return !jQuery.className.has( c, cur );	
				}).join(" ") : "";
		},

		// internal only, use is(".class")
		has: function( t, c ) {
			return jQuery.inArray( c, (t.className || t).toString().split(/\s+/) ) > -1;
		}
	},
	swap: function(e,o,f) {
		for ( var i in o ) {
			e.style["old"+i] = e.style[i];
			e.style[i] = o[i];
		}
		f.apply( e, [] );
		for ( var i in o )
			e.style[i] = e.style["old"+i];
	},

	css: function(e,p) {
		if ( p == "height" || p == "width" ) {
			var old = {}, oHeight, oWidth, d = ["Top","Bottom","Right","Left"];

			jQuery.each( d, function(){
				old["padding" + this] = 0;
				old["border" + this + "Width"] = 0;
			});

			jQuery.swap( e, old, function() {
				if ( jQuery(e).is(':visible') ) {
					oHeight = e.offsetHeight;
					oWidth = e.offsetWidth;
				} else {
					e = jQuery(e.cloneNode(true))
						.find(":radio").removeAttr("checked").end()
						.css({
							visibility: "hidden", position: "absolute", display: "block", right: "0", left: "0"
						}).appendTo(e.parentNode)[0];

					var parPos = jQuery.css(e.parentNode,"position") || "static";
					if ( parPos == "static" )
						e.parentNode.style.position = "relative";

					oHeight = e.clientHeight;
					oWidth = e.clientWidth;

					if ( parPos == "static" )
						e.parentNode.style.position = "static";

					e.parentNode.removeChild(e);
				}
			});

			return p == "height" ? oHeight : oWidth;
		}

		return jQuery.curCSS( e, p );
	},

	curCSS: function(elem, prop, force) {
		var ret, stack = [], swap = [];

		// A helper method for determining if an element's values are broken
		function color(a){
			if ( !jQuery.browser.safari )
				return false;

			var ret = document.defaultView.getComputedStyle(a,null);
			return !ret || ret.getPropertyValue("color") == "";
		}

		if (prop == "opacity" && jQuery.browser.msie) {
			ret = jQuery.attr(elem.style, "opacity");
			return ret == "" ? "1" : ret;
		}
		
		if (prop.match(/float/i))
			prop = styleFloat;

		if (!force && elem.style[prop])
			ret = elem.style[prop];

		else if (document.defaultView && document.defaultView.getComputedStyle) {

			if (prop.match(/float/i))
				prop = "float";

			prop = prop.replace(/([A-Z])/g,"-$1").toLowerCase();
			var cur = document.defaultView.getComputedStyle(elem, null);

			if ( cur && !color(elem) )
				ret = cur.getPropertyValue(prop);

			// If the element isn't reporting its values properly in Safari
			// then some display: none elements are involved
			else {
				// Locate all of the parent display: none elements
				for ( var a = elem; a && color(a); a = a.parentNode )
					stack.unshift(a);

				// Go through and make them visible, but in reverse
				// (It would be better if we knew the exact display type that they had)
				for ( a = 0; a < stack.length; a++ )
					if ( color(stack[a]) ) {
						swap[a] = stack[a].style.display;
						stack[a].style.display = "block";
					}

				// Since we flip the display style, we have to handle that
				// one special, otherwise get the value
				ret = prop == "display" && swap[stack.length-1] != null ?
					"none" :
					document.defaultView.getComputedStyle(elem,null).getPropertyValue(prop) || "";

				// Finally, revert the display styles back
				for ( a = 0; a < swap.length; a++ )
					if ( swap[a] != null )
						stack[a].style.display = swap[a];
			}

			if ( prop == "opacity" && ret == "" )
				ret = "1";

		} else if (elem.currentStyle) {
			var newProp = prop.replace(/\-(\w)/g,function(m,c){return c.toUpperCase();});
			ret = elem.currentStyle[prop] || elem.currentStyle[newProp];
		}

		return ret;
	},
	
	clean: function(a, doc) {
		var r = [];
		doc = doc || document;

		jQuery.each( a, function(i,arg){
			if ( !arg ) return;

			if ( arg.constructor == Number )
				arg = arg.toString();
			
			// Convert html string into DOM nodes
			if ( typeof arg == "string" ) {
				// Trim whitespace, otherwise indexOf won't work as expected
				var s = jQuery.trim(arg).toLowerCase(), div = doc.createElement("div"), tb = [];

				var wrap =
					// option or optgroup
					!s.indexOf("<opt") &&
					[1, "<select>", "</select>"] ||
					
					!s.indexOf("<leg") &&
					[1, "<fieldset>", "</fieldset>"] ||
					
					s.match(/^<(thead|tbody|tfoot|colg|cap)/) &&
					[1, "<table>", "</table>"] ||
					
					!s.indexOf("<tr") &&
					[2, "<table><tbody>", "</tbody></table>"] ||
					
				 	// <thead> matched above
					(!s.indexOf("<td") || !s.indexOf("<th")) &&
					[3, "<table><tbody><tr>", "</tr></tbody></table>"] ||
					
					!s.indexOf("<col") &&
					[2, "<table><tbody></tbody><colgroup>", "</colgroup></table>"] ||

					// IE can't serialize <link> and <script> tags normally
					jQuery.browser.msie &&
					[1, "div<div>", "</div>"] ||
					
					[0,"",""];

				// Go to html and back, then peel off extra wrappers
				div.innerHTML = wrap[1] + arg + wrap[2];
				
				// Move to the right depth
				while ( wrap[0]-- )
					div = div.lastChild;
				
				// Remove IE's autoinserted <tbody> from table fragments
				if ( jQuery.browser.msie ) {
					
					// String was a <table>, *may* have spurious <tbody>
					if ( !s.indexOf("<table") && s.indexOf("<tbody") < 0 ) 
						tb = div.firstChild && div.firstChild.childNodes;
						
					// String was a bare <thead> or <tfoot>
					else if ( wrap[1] == "<table>" && s.indexOf("<tbody") < 0 )
						tb = div.childNodes;

					for ( var n = tb.length-1; n >= 0 ; --n )
						if ( jQuery.nodeName(tb[n], "tbody") && !tb[n].childNodes.length )
							tb[n].parentNode.removeChild(tb[n]);
	
					// IE completely kills leading whitespace when innerHTML is used	
					if ( /^\s/.test(arg) )	
						div.insertBefore( doc.createTextNode( arg.match(/^\s*/)[0] ), div.firstChild );

				}
				
				arg = jQuery.makeArray( div.childNodes );
			}

			if ( 0 === arg.length && (!jQuery.nodeName(arg, "form") && !jQuery.nodeName(arg, "select")) )
				return;

			if ( arg[0] == undefined || jQuery.nodeName(arg, "form") || arg.options )
				r.push( arg );
			else
				r = jQuery.merge( r, arg );

		});

		return r;
	},
	
	attr: function(elem, name, value){
		var fix = jQuery.isXMLDoc(elem) ? {} : jQuery.props;

		// Safari mis-reports the default selected property of a hidden option
		// Accessing the parent's selectedIndex property fixes it
		if ( name == "selected" && jQuery.browser.safari )
			elem.parentNode.selectedIndex;
		
		// Certain attributes only work when accessed via the old DOM 0 way
		if ( fix[name] ) {
			if ( value != undefined ) elem[fix[name]] = value;
			return elem[fix[name]];
		} else if ( jQuery.browser.msie && name == "style" )
			return jQuery.attr( elem.style, "cssText", value );

		else if ( value == undefined && jQuery.browser.msie && jQuery.nodeName(elem, "form") && (name == "action" || name == "method") )
			return elem.getAttributeNode(name).nodeValue;

		// IE elem.getAttribute passes even for style
		else if ( elem.tagName ) {

			if ( value != undefined ) elem.setAttribute( name, value );
			if ( jQuery.browser.msie && /href|src/.test(name) && !jQuery.isXMLDoc(elem) ) 
				return elem.getAttribute( name, 2 );
			return elem.getAttribute( name );

		// elem is actually elem.style ... set the style
		} else {
			// IE actually uses filters for opacity
			if ( name == "opacity" && jQuery.browser.msie ) {
				if ( value != undefined ) {
					// IE has trouble with opacity if it does not have layout
					// Force it by setting the zoom level
					elem.zoom = 1; 
	
					// Set the alpha filter to set the opacity
					elem.filter = (elem.filter || "").replace(/alpha\([^)]*\)/,"") +
						(parseFloat(value).toString() == "NaN" ? "" : "alpha(opacity=" + value * 100 + ")");
				}
	
				return elem.filter ? 
					(parseFloat( elem.filter.match(/opacity=([^)]*)/)[1] ) / 100).toString() : "";
			}
			name = name.replace(/-([a-z])/ig,function(z,b){return b.toUpperCase();});
			if ( value != undefined ) elem[name] = value;
			return elem[name];
		}
	},
	trim: function(t){
		return (t||"").replace(/^\s+|\s+$/g, "");
	},

	makeArray: function( a ) {
		var r = [];

		// Need to use typeof to fight Safari childNodes crashes
		if ( typeof a != "array" )
			for ( var i = 0, al = a.length; i < al; i++ )
				r.push( a[i] );
		else
			r = a.slice( 0 );

		return r;
	},

	inArray: function( b, a ) {
		for ( var i = 0, al = a.length; i < al; i++ )
			if ( a[i] == b )
				return i;
		return -1;
	},
	merge: function(first, second) {
		// We have to loop this way because IE & Opera overwrite the length
		// expando of getElementsByTagName

		// Also, we need to make sure that the correct elements are being returned
		// (IE returns comment nodes in a '*' query)
		if ( jQuery.browser.msie ) {
			for ( var i = 0; second[i]; i++ )
				if ( second[i].nodeType != 8 )
					first.push(second[i]);
		} else
			for ( var i = 0; second[i]; i++ )
				first.push(second[i]);

		return first;
	},
	unique: function(first) {
		var r = [], num = jQuery.mergeNum++;

		try {
			for ( var i = 0, fl = first.length; i < fl; i++ )
				if ( num != first[i].mergeNum ) {
					first[i].mergeNum = num;
					r.push(first[i]);
				}
		} catch(e) {
			r = first;
		}

		return r;
	},

	mergeNum: 0,
	grep: function(elems, fn, inv) {
		// If a string is passed in for the function, make a function
		// for it (a handy shortcut)
		if ( typeof fn == "string" )
			fn = eval("false||function(a,i){return " + fn + "}");

		var result = [];

		// Go through the array, only saving the items
		// that pass the validator function
		for ( var i = 0, el = elems.length; i < el; i++ )
			if ( !inv && fn(elems[i],i) || inv && !fn(elems[i],i) )
				result.push( elems[i] );

		return result;
	},
	map: function(elems, fn) {
		// If a string is passed in for the function, make a function
		// for it (a handy shortcut)
		if ( typeof fn == "string" )
			fn = eval("false||function(a){return " + fn + "}");

		var result = [];

		// Go through the array, translating each of the items to their
		// new value (or values).
		for ( var i = 0, el = elems.length; i < el; i++ ) {
			var val = fn(elems[i],i);

			if ( val !== null && val != undefined ) {
				if ( val.constructor != Array ) val = [val];
				result = result.concat( val );
			}
		}

		return result;
	}
});
 
/*
 * Whether the W3C compliant box model is being used.
 *
 * @property
 * @name $.boxModel
 * @type Boolean
 * @cat JavaScript
 */
var userAgent = navigator.userAgent.toLowerCase();

// Figure out what browser is being used
jQuery.browser = {
	version: (userAgent.match(/.+(?:rv|it|ra|ie)[\/: ]([\d.]+)/) || [])[1],
	safari: /webkit/.test(userAgent),
	opera: /opera/.test(userAgent),
	msie: /msie/.test(userAgent) && !/opera/.test(userAgent),
	mozilla: /mozilla/.test(userAgent) && !/(compatible|webkit)/.test(userAgent)
};

var styleFloat = jQuery.browser.msie ? "styleFloat" : "cssFloat";
	
jQuery.extend({
	// Check to see if the W3C box model is being used
	boxModel: !jQuery.browser.msie || document.compatMode == "CSS1Compat",
	
	styleFloat: jQuery.browser.msie ? "styleFloat" : "cssFloat",
	
	props: {
		"for": "htmlFor",
		"class": "className",
		"float": styleFloat,
		cssFloat: styleFloat,
		styleFloat: styleFloat,
		innerHTML: "innerHTML",
		className: "className",
		value: "value",
		disabled: "disabled",
		checked: "checked",
		readonly: "readOnly",
		selected: "selected",
		maxlength: "maxLength"
	}
});

jQuery.each({
	parent: "a.parentNode",
	parents: "jQuery.parents(a)",
	next: "jQuery.nth(a,2,'nextSibling')",
	prev: "jQuery.nth(a,2,'previousSibling')",
	siblings: "jQuery.sibling(a.parentNode.firstChild,a)",
	children: "jQuery.sibling(a.firstChild)"
}, function(i,n){
	jQuery.fn[ i ] = function(a) {
		var ret = jQuery.map(this,n);
		if ( a && typeof a == "string" )
			ret = jQuery.multiFilter(a,ret);
		return this.pushStack( jQuery.unique(ret) );
	};
});

jQuery.each({
	appendTo: "append",
	prependTo: "prepend",
	insertBefore: "before",
	insertAfter: "after"
}, function(i,n){
	jQuery.fn[ i ] = function(){
		var a = arguments;
		return this.each(function(){
			for ( var j = 0, al = a.length; j < al; j++ )
				jQuery(a[j])[n]( this );
		});
	};
});

jQuery.each( {
	removeAttr: function( key ) {
		jQuery.attr( this, key, "" );
		this.removeAttribute( key );
	},
	addClass: function(c){
		jQuery.className.add(this,c);
	},
	removeClass: function(c){
		jQuery.className.remove(this,c);
	},
	toggleClass: function( c ){
		jQuery.className[ jQuery.className.has(this,c) ? "remove" : "add" ](this, c);
	},
	remove: function(a){
		if ( !a || jQuery.filter( a, [this] ).r.length )
			this.parentNode.removeChild( this );
	},
	empty: function() {
		while ( this.firstChild )
			this.removeChild( this.firstChild );
	}
}, function(i,n){
	jQuery.fn[ i ] = function() {
		return this.each( n, arguments );
	};
});

// DEPRECATED
jQuery.each( [ "eq", "lt", "gt", "contains" ], function(i,n){
	jQuery.fn[ n ] = function(num,fn) {
		return this.filter( ":" + n + "(" + num + ")", fn );
	};
});

jQuery.each( [ "height", "width" ], function(i,n){
	jQuery.fn[ n ] = function(h) {
		return h == undefined ?
			( this.length ? jQuery.css( this[0], n ) : null ) :
			this.css( n, h.constructor == String ? h : h + "px" );
	};
});

var chars = jQuery.browser.safari && parseInt(jQuery.browser.version) < 417 ?
		"(?:[\\w*_-]|\\\\.)" :
		"(?:[\\w\u0128-\uFFFF*_-]|\\\\.)",
	quickChild = new RegExp("^[/>]\\s*(" + chars + "+)"),
	quickID = new RegExp("^(" + chars + "+)(#)(" + chars + "+)"),
	quickClass = new RegExp("^([#.]?)(" + chars + "*)");

jQuery.extend({
	expr: {
		"": "m[2]=='*'||jQuery.nodeName(a,m[2])",
		"#": "a.getAttribute('id')==m[2]",
		":": {
			// Position Checks
			lt: "i<m[3]-0",
			gt: "i>m[3]-0",
			nth: "m[3]-0==i",
			eq: "m[3]-0==i",
			first: "i==0",
			last: "i==r.length-1",
			even: "i%2==0",
			odd: "i%2",

			// Child Checks
			"first-child": "a.parentNode.getElementsByTagName('*')[0]==a",
			"last-child": "jQuery.nth(a.parentNode.lastChild,1,'previousSibling')==a",
			"only-child": "!jQuery.nth(a.parentNode.lastChild,2,'previousSibling')",

			// Parent Checks
			parent: "a.firstChild",
			empty: "!a.firstChild",

			// Text Check
			contains: "(a.textContent||a.innerText||'').indexOf(m[3])>=0",

			// Visibility
			visible: '"hidden"!=a.type&&jQuery.css(a,"display")!="none"&&jQuery.css(a,"visibility")!="hidden"',
			hidden: '"hidden"==a.type||jQuery.css(a,"display")=="none"||jQuery.css(a,"visibility")=="hidden"',

			// Form attributes
			enabled: "!a.disabled",
			disabled: "a.disabled",
			checked: "a.checked",
			selected: "a.selected||jQuery.attr(a,'selected')",

			// Form elements
			text: "'text'==a.type",
			radio: "'radio'==a.type",
			checkbox: "'checkbox'==a.type",
			file: "'file'==a.type",
			password: "'password'==a.type",
			submit: "'submit'==a.type",
			image: "'image'==a.type",
			reset: "'reset'==a.type",
			button: '"button"==a.type||jQuery.nodeName(a,"button")',
			input: "/input|select|textarea|button/i.test(a.nodeName)",

			// :has()
			has: "jQuery.find(m[3],a).length"
		},
		// DEPRECATED
		"[": "jQuery.find(m[2],a).length"
	},
	
	// The regular expressions that power the parsing engine
	parse: [
		// Match: [@value='test'], [@foo]
		/^\[ *(@)([\w-]+) *([!*$^~=]*) *('?"?)(.*?)\4 *\]/,

		// DEPRECATED
		// Match: [div], [div p]
		/^(\[)\s*(.*?(\[.*?\])?[^[]*?)\s*\]/,

		// Match: :contains('foo')
		/^(:)([\w-]+)\("?'?(.*?(\(.*?\))?[^(]*?)"?'?\)/,

		// Match: :even, :last-chlid, #id, .class
		new RegExp("^([:.#]*)(" + chars + "+)")
	],

	multiFilter: function( expr, elems, not ) {
		var old, cur = [];

		while ( expr && expr != old ) {
			old = expr;
			var f = jQuery.filter( expr, elems, not );
			expr = f.t.replace(/^\s*,\s*/, "" );
			cur = not ? elems = f.r : jQuery.merge( cur, f.r );
		}

		return cur;
	},
	find: function( t, context ) {
		// Quickly handle non-string expressions
		if ( typeof t != "string" )
			return [ t ];

		// Make sure that the context is a DOM Element
		if ( context && !context.nodeType )
			context = null;

		// Set the correct context (if none is provided)
		context = context || document;

		// DEPRECATED
		// Handle the common XPath // expression
		if ( !t.indexOf("//") ) {
			//context = context.documentElement;
			t = t.substr(2,t.length);

		// DEPRECATED
		// And the / root expression
		} else if ( !t.indexOf("/") && !context.ownerDocument ) {
			context = context.documentElement;
			t = t.substr(1,t.length);
			if ( t.indexOf("/") >= 1 )
				t = t.substr(t.indexOf("/"),t.length);
		}

		// Initialize the search
		var ret = [context], done = [], last;

		// Continue while a selector expression exists, and while
		// we're no longer looping upon ourselves
		while ( t && last != t ) {
			var r = [];
			last = t;

			// DEPRECATED
			t = jQuery.trim(t).replace( /^\/\//, "" );

			var foundToken = false;

			// An attempt at speeding up child selectors that
			// point to a specific element tag
			var re = quickChild;
			var m = re.exec(t);

			if ( m ) {
				var nodeName = m[1].toUpperCase();

				// Perform our own iteration and filter
				for ( var i = 0; ret[i]; i++ )
					for ( var c = ret[i].firstChild; c; c = c.nextSibling )
						if ( c.nodeType == 1 && (nodeName == "*" || c.nodeName.toUpperCase() == nodeName.toUpperCase()) )
							r.push( c );

				ret = r;
				t = t.replace( re, "" );
				if ( t.indexOf(" ") == 0 ) continue;
				foundToken = true;
			} else {
				// (.. and /) DEPRECATED
				re = /^((\/?\.\.)|([>\/+~]))\s*(\w*)/i;

				if ( (m = re.exec(t)) != null ) {
					r = [];

					var nodeName = m[4], mergeNum = jQuery.mergeNum++;
					m = m[1];

					for ( var j = 0, rl = ret.length; j < rl; j++ )
						if ( m.indexOf("..") < 0 ) {
							var n = m == "~" || m == "+" ? ret[j].nextSibling : ret[j].firstChild;
							for ( ; n; n = n.nextSibling )
								if ( n.nodeType == 1 ) {
									if ( m == "~" && n.mergeNum == mergeNum ) break;
									
									if (!nodeName || n.nodeName.toUpperCase() == nodeName.toUpperCase() ) {
										if ( m == "~" ) n.mergeNum = mergeNum;
										r.push( n );
									}
									
									if ( m == "+" ) break;
								}
						// DEPRECATED
						} else
							r.push( ret[j].parentNode );

					ret = r;

					// And remove the token
					t = jQuery.trim( t.replace( re, "" ) );
					foundToken = true;
				}
			}

			// See if there's still an expression, and that we haven't already
			// matched a token
			if ( t && !foundToken ) {
				// Handle multiple expressions
				if ( !t.indexOf(",") ) {
					// Clean the result set
					if ( context == ret[0] ) ret.shift();

					// Merge the result sets
					done = jQuery.merge( done, ret );

					// Reset the context
					r = ret = [context];

					// Touch up the selector string
					t = " " + t.substr(1,t.length);

				} else {
					// Optimize for the case nodeName#idName
					var re2 = quickID;
					var m = re2.exec(t);
					
					// Re-organize the results, so that they're consistent
					if ( m ) {
					   m = [ 0, m[2], m[3], m[1] ];

					} else {
						// Otherwise, do a traditional filter check for
						// ID, class, and element selectors
						re2 = quickClass;
						m = re2.exec(t);
					}

					m[2] = m[2].replace(/\\/g, "");

					var elem = ret[ret.length-1];

					// Try to do a global search by ID, where we can
					if ( m[1] == "#" && elem && elem.getElementById && !jQuery.isXMLDoc(elem) ) {
						// Optimization for HTML document case
						var oid = elem.getElementById(m[2]);
						
						// Do a quick check for the existence of the actual ID attribute
						// to avoid selecting by the name attribute in IE
						// also check to insure id is a string to avoid selecting an element with the name of 'id' inside a form
						if ( (jQuery.browser.msie||jQuery.browser.opera) && oid && typeof oid.id == "string" && oid.id != m[2] )
							oid = jQuery('[@id="'+m[2]+'"]', elem)[0];

						// Do a quick check for node name (where applicable) so
						// that div#foo searches will be really fast
						ret = r = oid && (!m[3] || jQuery.nodeName(oid, m[3])) ? [oid] : [];
					} else {
						// We need to find all descendant elements
						for ( var i = 0; ret[i]; i++ ) {
							// Grab the tag name being searched for
							var tag = m[1] != "" || m[0] == "" ? "*" : m[2];

							// Handle IE7 being really dumb about <object>s
							if ( tag == "*" && ret[i].nodeName.toLowerCase() == "object" )
								tag = "param";

							r = jQuery.merge( r, ret[i].getElementsByTagName( tag ));
						}

						// It's faster to filter by class and be done with it
						if ( m[1] == "." )
							r = jQuery.classFilter( r, m[2] );

						// Same with ID filtering
						if ( m[1] == "#" ) {
							var tmp = [];

							// Try to find the element with the ID
							for ( var i = 0; r[i]; i++ )
								if ( r[i].getAttribute("id") == m[2] ) {
									tmp = [ r[i] ];
									break;
								}

							r = tmp;
						}

						ret = r;
					}

					t = t.replace( re2, "" );
				}

			}

			// If a selector string still exists
			if ( t ) {
				// Attempt to filter it
				var val = jQuery.filter(t,r);
				ret = r = val.r;
				t = jQuery.trim(val.t);
			}
		}

		// An error occurred with the selector;
		// just return an empty set instead
		if ( t )
			ret = [];

		// Remove the root context
		if ( ret && context == ret[0] )
			ret.shift();

		// And combine the results
		done = jQuery.merge( done, ret );

		return done;
	},

	classFilter: function(r,m,not){
		m = " " + m + " ";
		var tmp = [];
		for ( var i = 0; r[i]; i++ ) {
			var pass = (" " + r[i].className + " ").indexOf( m ) >= 0;
			if ( !not && pass || not && !pass )
				tmp.push( r[i] );
		}
		return tmp;
	},

	filter: function(t,r,not) {
		var last;

		// Look for common filter expressions
		while ( t  && t != last ) {
			last = t;

			var p = jQuery.parse, m;

			for ( var i = 0; p[i]; i++ ) {
				m = p[i].exec( t );

				if ( m ) {
					// Remove what we just matched
					t = t.substring( m[0].length );

					m[2] = m[2].replace(/\\/g, "");
					break;
				}
			}

			if ( !m )
				break;

			// :not() is a special case that can be optimized by
			// keeping it out of the expression list
			if ( m[1] == ":" && m[2] == "not" )
				r = jQuery.filter(m[3], r, true).r;

			// We can get a big speed boost by filtering by class here
			else if ( m[1] == "." )
				r = jQuery.classFilter(r, m[2], not);

			else if ( m[1] == "@" ) {
				var tmp = [], type = m[3];
				
				for ( var i = 0, rl = r.length; i < rl; i++ ) {
					var a = r[i], z = a[ jQuery.props[m[2]] || m[2] ];
					
					if ( z == null || /href|src|selected/.test(m[2]) )
						z = jQuery.attr(a,m[2]) || '';

					if ( (type == "" && !!z ||
						 type == "=" && z == m[5] ||
						 type == "!=" && z != m[5] ||
						 type == "^=" && z && !z.indexOf(m[5]) ||
						 type == "$=" && z.substr(z.length - m[5].length) == m[5] ||
						 (type == "*=" || type == "~=") && z.indexOf(m[5]) >= 0) ^ not )
							tmp.push( a );
				}
				
				r = tmp;

			// We can get a speed boost by handling nth-child here
			} else if ( m[1] == ":" && m[2] == "nth-child" ) {
				var num = jQuery.mergeNum++, tmp = [],
					test = /(\d*)n\+?(\d*)/.exec(
						m[3] == "even" && "2n" || m[3] == "odd" && "2n+1" ||
						!/\D/.test(m[3]) && "n+" + m[3] || m[3]),
					first = (test[1] || 1) - 0, last = test[2] - 0;

				for ( var i = 0, rl = r.length; i < rl; i++ ) {
					var node = r[i], parentNode = node.parentNode;

					if ( num != parentNode.mergeNum ) {
						var c = 1;

						for ( var n = parentNode.firstChild; n; n = n.nextSibling )
							if ( n.nodeType == 1 )
								n.nodeIndex = c++;

						parentNode.mergeNum = num;
					}

					var add = false;

					if ( first == 1 ) {
						if ( last == 0 || node.nodeIndex == last )
							add = true;
					} else if ( (node.nodeIndex + last) % first == 0 )
						add = true;

					if ( add ^ not )
						tmp.push( node );
				}

				r = tmp;

			// Otherwise, find the expression to execute
			} else {
				var f = jQuery.expr[m[1]];
				if ( typeof f != "string" )
					f = jQuery.expr[m[1]][m[2]];

				// Build a custom macro to enclose it
				f = eval("false||function(a,i){return " + f + "}");

				// Execute it against the current filter
				r = jQuery.grep( r, f, not );
			}
		}

		// Return an array of filtered elements (r)
		// and the modified expression string (t)
		return { r: r, t: t };
	},
	parents: function( elem ){
		var matched = [];
		var cur = elem.parentNode;
		while ( cur && cur != document ) {
			matched.push( cur );
			cur = cur.parentNode;
		}
		return matched;
	},
	nth: function(cur,result,dir,elem){
		result = result || 1;
		var num = 0;

		for ( ; cur; cur = cur[dir] )
			if ( cur.nodeType == 1 && ++num == result )
				break;

		return cur;
	},
	sibling: function( n, elem ) {
		var r = [];

		for ( ; n; n = n.nextSibling ) {
			if ( n.nodeType == 1 && (!elem || n != elem) )
				r.push( n );
		}

		return r;
	}
});
/*
 * A number of helper functions used for managing events.
 * Many of the ideas behind this code orignated from 
 * Dean Edwards' addEvent library.
 */
jQuery.event = {

	// Bind an event to an element
	// Original by Dean Edwards
	add: function(element, type, handler, data) {
		// For whatever reason, IE has trouble passing the window object
		// around, causing it to be cloned in the process
		if ( jQuery.browser.msie && element.setInterval != undefined )
			element = window;
		
		// Make sure that the function being executed has a unique ID
		if ( !handler.guid )
			handler.guid = this.guid++;
			
		// if data is passed, bind to handler 
		if( data != undefined ) { 
        	// Create temporary function pointer to original handler 
			var fn = handler; 

			// Create unique handler function, wrapped around original handler 
			handler = function() { 
				// Pass arguments and context to original handler 
				return fn.apply(this, arguments); 
			};

			// Store data in unique handler 
			handler.data = data;

			// Set the guid of unique handler to the same of original handler, so it can be removed 
			handler.guid = fn.guid;
		}

		// Init the element's event structure
		if (!element.$events)
			element.$events = {};
		
		if (!element.$handle)
			element.$handle = function() {
				// returned undefined or false
				var val;

				// Handle the second event of a trigger and when
				// an event is called after a page has unloaded
				if ( typeof jQuery == "undefined" || jQuery.event.triggered )
				  return val;
				
				val = jQuery.event.handle.apply(element, arguments);
				
				return val;
			};

		// Get the current list of functions bound to this event
		var handlers = element.$events[type];

		// Init the event handler queue
		if (!handlers) {
			handlers = element.$events[type] = {};	
			
			// And bind the global event handler to the element
			if (element.addEventListener)
				element.addEventListener(type, element.$handle, false);
			else
				element.attachEvent("on" + type, element.$handle);
		}

		// Add the function to the element's handler list
		handlers[handler.guid] = handler;

		// Keep track of which events have been used, for global triggering
		this.global[type] = true;
	},

	guid: 1,
	global: {},

	// Detach an event or set of events from an element
	remove: function(element, type, handler) {
		var events = element.$events, ret, index;

		if ( events ) {
			// type is actually an event object here
			if ( type && type.type ) {
				handler = type.handler;
				type = type.type;
			}
			
			if ( !type ) {
				for ( type in events )
					this.remove( element, type );

			} else if ( events[type] ) {
				// remove the given handler for the given type
				if ( handler )
					delete events[type][handler.guid];
				
				// remove all handlers for the given type
				else
					for ( handler in element.$events[type] )
						delete events[type][handler];

				// remove generic event handler if no more handlers exist
				for ( ret in events[type] ) break;
				if ( !ret ) {
					if (element.removeEventListener)
						element.removeEventListener(type, element.$handle, false);
					else
						element.detachEvent("on" + type, element.$handle);
					ret = null;
					delete events[type];
				}
			}

			// Remove the expando if it's no longer used
			for ( ret in events ) break;
			if ( !ret )
				element.$handle = element.$events = null;
		}
	},

	trigger: function(type, data, element) {
		// Clone the incoming data, if any
		data = jQuery.makeArray(data || []);

		// Handle a global trigger
		if ( !element ) {
			// Only trigger if we've ever bound an event for it
			if ( this.global[type] )
				jQuery("*").add([window, document]).trigger(type, data);

		// Handle triggering a single element
		} else {
			var val, ret, fn = jQuery.isFunction( element[ type ] || null );
			
			// Pass along a fake event
			data.unshift( this.fix({ type: type, target: element }) );

			// Trigger the event
			if ( jQuery.isFunction( element.$handle ) )
				val = element.$handle.apply( element, data );
			if ( !fn && element["on"+type] && element["on"+type].apply( element, data ) === false )
				val = false;

			// Liferay
			//if ( fn && val !== false && !(jQuery.nodeName(element, 'a') && type == "click") ) {
			if ( fn && val !== false && !(jQuery.nodeName(element, 'a') && type == "click") && !(type == 'focus' && element.offsetHeight == 0) ) {
				this.triggered = true;
				element[ type ]();
			}

			this.triggered = false;
		}
	},

	handle: function(event) {
		// returned undefined or false
		var val;

		// Empty object is for triggered events with no data
		event = jQuery.event.fix( event || window.event || {} ); 

		var c = this.$events && this.$events[event.type], args = Array.prototype.slice.call( arguments, 1 );
		args.unshift( event );

		for ( var j in c ) {
			// Pass in a reference to the handler function itself
			// So that we can later remove it
			args[0].handler = c[j];
			args[0].data = c[j].data;

			if ( c[j].apply( this, args ) === false ) {
				event.preventDefault();
				event.stopPropagation();
				val = false;
			}
		}

		// Clean up added properties in IE to prevent memory leak
		if (jQuery.browser.msie)
			event.target = event.preventDefault = event.stopPropagation =
				event.handler = event.data = null;

		return val;
	},

	fix: function(event) {
		// store a copy of the original event object 
		// and clone to set read-only properties
		var originalEvent = event;
		event = jQuery.extend({}, originalEvent);
		
		// add preventDefault and stopPropagation since 
		// they will not work on the clone
		event.preventDefault = function() {
			// if preventDefault exists run it on the original event
			if (originalEvent.preventDefault)
				originalEvent.preventDefault();
			// otherwise set the returnValue property of the original event to false (IE)
			originalEvent.returnValue = false;
		};
		event.stopPropagation = function() {
			// if stopPropagation exists run it on the original event
			if (originalEvent.stopPropagation)
				originalEvent.stopPropagation();
			// otherwise set the cancelBubble property of the original event to true (IE)
			originalEvent.cancelBubble = true;
		};
		
		// Fix target property, if necessary
		if ( !event.target && event.srcElement )
			event.target = event.srcElement;
				
		// check if target is a textnode (safari)
		if (jQuery.browser.safari && event.target.nodeType == 3)
			event.target = originalEvent.target.parentNode;

		// Add relatedTarget, if necessary
		if ( !event.relatedTarget && event.fromElement )
			event.relatedTarget = event.fromElement == event.target ? event.toElement : event.fromElement;

		// Calculate pageX/Y if missing and clientX/Y available
		if ( event.pageX == null && event.clientX != null ) {
			var e = document.documentElement, b = document.body;
			event.pageX = event.clientX + (e && e.scrollLeft || b.scrollLeft || 0);
			event.pageY = event.clientY + (e && e.scrollTop || b.scrollTop || 0);
		}
			
		// Add which for key events
		if ( !event.which && (event.charCode || event.keyCode) )
			event.which = event.charCode || event.keyCode;
		
		// Add metaKey to non-Mac browsers (use ctrl for PC's and Meta for Macs)
		if ( !event.metaKey && event.ctrlKey )
			event.metaKey = event.ctrlKey;

		// Add which for click: 1 == left; 2 == middle; 3 == right
		// Note: button is not normalized, so don't use it
		if ( !event.which && event.button )
			event.which = (event.button & 1 ? 1 : ( event.button & 2 ? 3 : ( event.button & 4 ? 2 : 0 ) ));
			
		return event;
	}
};

jQuery.fn.extend({
	bind: function( type, data, fn ) {
		return type == "unload" ? this.one(type, data, fn) : this.each(function(){
			jQuery.event.add( this, type, fn || data, fn && data );
		});
	},
	one: function( type, data, fn ) {
		return this.each(function(){
			jQuery.event.add( this, type, function(event) {
				jQuery(this).unbind(event);
				return (fn || data).apply( this, arguments);
			}, fn && data);
		});
	},
	unbind: function( type, fn ) {
		return this.each(function(){
			jQuery.event.remove( this, type, fn );
		});
	},
	trigger: function( type, data ) {
		return this.each(function(){
			jQuery.event.trigger( type, data, this );
		});
	},
	toggle: function() {
		// Save reference to arguments for access in closure
		var a = arguments;

		return this.click(function(e) {
			// Figure out which function to execute
			this.lastToggle = 0 == this.lastToggle ? 1 : 0;
			
			// Make sure that clicks stop
			e.preventDefault();
			
			// and execute the function
			return a[this.lastToggle].apply( this, [e] ) || false;
		});
	},
	hover: function(f,g) {
		
		// A private function for handling mouse 'hovering'
		function handleHover(e) {
			// Check if mouse(over|out) are still within the same parent element
			var p = e.relatedTarget;
	
			// Traverse up the tree
			while ( p && p != this ) try { p = p.parentNode; } catch(e) { p = this; };
			
			// If we actually just moused on to a sub-element, ignore it
			if ( p == this ) return false;
			
			// Execute the right function
			return (e.type == "mouseover" ? f : g).apply(this, [e]);
		}
		
		// Bind the function to the two event listeners
		return this.mouseover(handleHover).mouseout(handleHover);
	},
	ready: function(f) {
		// Attach the listeners
		bindReady();

		// If the DOM is already ready
		if ( jQuery.isReady )
			// Execute the function immediately
			f.apply( document, [jQuery] );
			
		// Otherwise, remember the function for later
		else
			// Add the function to the wait list
			jQuery.readyList.push( function() { return f.apply(this, [jQuery]); } );
	
		return this;
	}
});

jQuery.extend({
	/*
	 * All the code that makes DOM Ready work nicely.
	 */
	isReady: false,
	readyList: [],
	
	// Handle when the DOM is ready
	ready: function() {
		// Make sure that the DOM is not already loaded
		if ( !jQuery.isReady ) {
			// Remember that the DOM is ready
			jQuery.isReady = true;
			
			// If there are functions bound, to execute
			if ( jQuery.readyList ) {
				// Execute all of them
				jQuery.each( jQuery.readyList, function(){
					this.apply( document );
				});
				
				// Reset the list of functions
				jQuery.readyList = null;
			}
			// Remove event listener to avoid memory leak
			if ( jQuery.browser.mozilla || jQuery.browser.opera )
				document.removeEventListener( "DOMContentLoaded", jQuery.ready, false );
			
			// Remove script element used by IE hack
			if( !window.frames.length ) // don't remove if frames are present (#1187)
				jQuery(window).load(function(){ jQuery("#__ie_init").remove(); });
		}
	}
});

	jQuery.each( ("blur,focus,load,resize,scroll,unload,click,dblclick," +
		"mousedown,mouseup,mousemove,mouseover,mouseout,change,select," + 
		"submit,keydown,keypress,keyup,error").split(","), function(i,o){
		
		// Handle event binding
		jQuery.fn[o] = function(f){
			return f ? this.bind(o, f) : this.trigger(o);
		};
			
	});

var readyBound = false;

function bindReady(){
	if ( readyBound ) return;
	readyBound = true;

	// If Mozilla is used
	if ( jQuery.browser.mozilla || jQuery.browser.opera )
		// Use the handy event callback
		document.addEventListener( "DOMContentLoaded", jQuery.ready, false );
	
	// If IE is used, use the excellent hack by Matthias Miller
	// http://www.outofhanwell.com/blog/index.php?title=the_window_onload_problem_revisited
	else if ( jQuery.browser.msie ) {
	
		// Only works if you document.write() it
		document.write("<scr" + "ipt id=__ie_init defer=true " + 
			"src=//:><\/script>");
	
		// Use the defer script hack
		var script = document.getElementById("__ie_init");
		
		// script does not exist if jQuery is loaded dynamically
		if ( script ) 
			script.onreadystatechange = function() {
				if ( document.readyState != "complete" ) return;
				jQuery.ready();
			};
	
		// Clear from memory
		script = null;
	
	// If Safari  is used
	} else if ( jQuery.browser.safari )
		// Continually check to see if the document.readyState is valid
		jQuery.safariTimer = setInterval(function(){
			// loaded and complete are both valid states
			if ( document.readyState == "loaded" || 
				document.readyState == "complete" ) {
	
				// If either one are found, remove the timer
				clearInterval( jQuery.safariTimer );
				jQuery.safariTimer = null;
	
				// and execute any waiting functions
				jQuery.ready();
			}
		}, 10); 

	// A fallback to window.onload, that will always work
	jQuery.event.add( window, "load", jQuery.ready );
}
jQuery.fn.extend({
	// DEPRECATED
	loadIfModified: function( url, params, callback ) {
		this.load( url, params, callback, 1 );
	},
	load: function( url, params, callback, ifModified ) {
		if ( jQuery.isFunction( url ) )
			return this.bind("load", url);

		callback = callback || function(){};

		// Default to a GET request
		var type = "GET";

		// If the second parameter was provided
		if ( params )
			// If it's a function
			if ( jQuery.isFunction( params ) ) {
				// We assume that it's the callback
				callback = params;
				params = null;

			// Otherwise, build a param string
			} else {
				params = jQuery.param( params );
				type = "POST";
			}

		var self = this;

		// Request the remote document
		jQuery.ajax({
			url: url,
			type: type,
			data: params,
			ifModified: ifModified,
			complete: function(res, status){
				// If successful, inject the HTML into all the matched elements
				if ( status == "success" || !ifModified && status == "notmodified" )
					self.html(res.responseText);

				// Add delay to account for Safari's delay in globalEval
				setTimeout(function(){
					self.each( callback, [res.responseText, status, res] );
				}, 13);
			}
		});
		return this;
	},
	serialize: function() {
		return jQuery.param( this );
	},

	// DEPRECATED
	// This method no longer does anything - all script evaluation is
	// taken care of within the HTML injection methods.
	evalScripts: function(){}

});

// Attach a bunch of functions for handling common AJAX events

jQuery.each( "ajaxStart,ajaxStop,ajaxComplete,ajaxError,ajaxSuccess,ajaxSend".split(","), function(i,o){
	jQuery.fn[o] = function(f){
		return this.bind(o, f);
	};
});

jQuery.extend({
	get: function( url, data, callback, type, ifModified ) {
		// shift arguments if data argument was ommited
		if ( jQuery.isFunction( data ) ) {
			callback = data;
			data = null;
		}
		
		return jQuery.ajax({
			type: "GET",
			url: url,
			data: data,
			success: callback,
			dataType: type,
			ifModified: ifModified
		});
	},
	// DEPRECATED
	getIfModified: function( url, data, callback, type ) {
		return jQuery.get(url, data, callback, type, 1);
	},
	getScript: function( url, callback ) {
		return jQuery.get(url, null, callback, "script");
	},
	getJSON: function( url, data, callback ) {
		return jQuery.get(url, data, callback, "json");
	},
	post: function( url, data, callback, type ) {
		if ( jQuery.isFunction( data ) ) {
			callback = data;
			data = {};
		}

		return jQuery.ajax({
			type: "POST",
			url: url,
			data: data,
			success: callback,
			dataType: type
		});
	},
	// DEPRECATED
	ajaxTimeout: function( timeout ) {
		jQuery.ajaxSettings.timeout = timeout;
	},
	ajaxSetup: function( settings ) {
		jQuery.extend( jQuery.ajaxSettings, settings );
	},

	ajaxSettings: {
		global: true,
		type: "GET",
		timeout: 0,
		contentType: "application/x-www-form-urlencoded",
		processData: true,
		async: true,
		data: null
	},
	
	// Last-Modified header cache for next request
	lastModified: {},
	ajax: function( s ) {
		// Extend the settings, but re-extend 's' so that it can be
		// checked again later (in the test suite, specifically)
		s = jQuery.extend(true, s, jQuery.extend(true, {}, jQuery.ajaxSettings, s));

		// if data available
		if ( s.data ) {
			// convert data if not already a string
			if ( s.processData && typeof s.data != "string" )
				s.data = jQuery.param(s.data);

			// append data to url for get requests
			if ( s.type.toLowerCase() == "get" ) {
				// "?" + data or "&" + data (in case there are already params)
				s.url += (s.url.indexOf("?") > -1 ? "&" : "?") + s.data;

				// IE likes to send both get and post data, prevent this
				s.data = null;
			}
		}

		// Watch for a new set of requests
		if ( s.global && ! jQuery.active++ )
			jQuery.event.trigger( "ajaxStart" );

		var requestDone = false;

		// Create the request object; Microsoft failed to properly
		// implement the XMLHttpRequest in IE7, so we use the ActiveXObject when it is available
		var xml = window.ActiveXObject ? new ActiveXObject("Microsoft.XMLHTTP") : new XMLHttpRequest();

		// Open the socket
		xml.open(s.type, s.url, s.async);

		// Set the correct header, if data is being sent
		if ( s.data )
			xml.setRequestHeader("Content-Type", s.contentType);

		// Set the If-Modified-Since header, if ifModified mode.
		if ( s.ifModified )
			xml.setRequestHeader("If-Modified-Since",
				jQuery.lastModified[s.url] || "Thu, 01 Jan 1970 00:00:00 GMT" );

		// Set header so the called script knows that it's an XMLHttpRequest
		xml.setRequestHeader("X-Requested-With", "XMLHttpRequest");

		// Allow custom headers/mimetypes
		if( s.beforeSend )
			s.beforeSend(xml);
			
		if ( s.global )
		    jQuery.event.trigger("ajaxSend", [xml, s]);

		// Wait for a response to come back
		var onreadystatechange = function(isTimeout){
			// The transfer is complete and the data is available, or the request timed out
			if ( !requestDone && xml && (xml.readyState == 4 || isTimeout == "timeout") ) {
				requestDone = true;
				
				// clear poll interval
				if (ival) {
					clearInterval(ival);
					ival = null;
				}
				
				var status = isTimeout == "timeout" && "timeout" ||
					!jQuery.httpSuccess( xml ) && "error" ||
					s.ifModified && jQuery.httpNotModified( xml, s.url ) && "notmodified" ||
					"success";

				if ( status == "success" ) {
					// Watch for, and catch, XML document parse errors
					try {
						// process the data (runs the xml through httpData regardless of callback)
						var data = jQuery.httpData( xml, s.dataType );
					} catch(e) {
						status = "parsererror";
					}
				}

				// Make sure that the request was successful or notmodified
				if ( status == "success" ) {
					// Cache Last-Modified header, if ifModified mode.
					var modRes;
					try {
						modRes = xml.getResponseHeader("Last-Modified");
					} catch(e) {} // swallow exception thrown by FF if header is not available
	
					if ( s.ifModified && modRes )
						jQuery.lastModified[s.url] = modRes;
	
					// If a local callback was specified, fire it and pass it the data
					if ( s.success )
						s.success( data, status );
	
					// Fire the global callback
					if ( s.global )
						jQuery.event.trigger( "ajaxSuccess", [xml, s] );
				} else
					jQuery.handleError(s, xml, status);

				// The request was completed
				if( s.global )
					jQuery.event.trigger( "ajaxComplete", [xml, s] );

				// Handle the global AJAX counter
				if ( s.global && ! --jQuery.active )
					jQuery.event.trigger( "ajaxStop" );

				// Process result
				if ( s.complete )
					s.complete(xml, status);

				// Stop memory leaks
				if(s.async)
					xml = null;
			}
		};
		
		if ( s.async ) {
			// don't attach the handler to the request, just poll it instead
			var ival = setInterval(onreadystatechange, 13); 

			// Timeout checker
			if ( s.timeout > 0 )
				setTimeout(function(){
					// Check to see if the request is still happening
					if ( xml ) {
						// Cancel the request
						xml.abort();
	
						if( !requestDone )
							onreadystatechange( "timeout" );
					}
				}, s.timeout);
		}
			
		// Send the data
		try {
			xml.send(s.data);
		} catch(e) {
			jQuery.handleError(s, xml, null, e);
		}
		
		// firefox 1.5 doesn't fire statechange for sync requests
		if ( !s.async )
			onreadystatechange();
		
		// return XMLHttpRequest to allow aborting the request etc.
		return xml;
	},

	handleError: function( s, xml, status, e ) {
		// If a local callback was specified, fire it
		if ( s.error ) s.error( xml, status, e );

		// Fire the global callback
		if ( s.global )
			jQuery.event.trigger( "ajaxError", [xml, s, e] );
	},

	// Counter for holding the number of active queries
	active: 0,

	// Determines if an XMLHttpRequest was successful or not
	httpSuccess: function( r ) {
		try {
			return !r.status && location.protocol == "file:" ||
				( r.status >= 200 && r.status < 300 ) || r.status == 304 ||
				jQuery.browser.safari && r.status == undefined;
		} catch(e){}
		return false;
	},

	// Determines if an XMLHttpRequest returns NotModified
	httpNotModified: function( xml, url ) {
		try {
			var xmlRes = xml.getResponseHeader("Last-Modified");

			// Firefox always returns 200. check Last-Modified date
			return xml.status == 304 || xmlRes == jQuery.lastModified[url] ||
				jQuery.browser.safari && xml.status == undefined;
		} catch(e){}
		return false;
	},

	/* Get the data out of an XMLHttpRequest.
	 * Return parsed XML if content-type header is "xml" and type is "xml" or omitted,
	 * otherwise return plain text.
	 * (String) data - The type of data that you're expecting back,
	 * (e.g. "xml", "html", "script")
	 */
	httpData: function( r, type ) {
		var ct = r.getResponseHeader("content-type");
		var xml = type == "xml" || !type && ct && ct.indexOf("xml") >= 0;
		data = xml ? r.responseXML : r.responseText;

		if ( xml && data.documentElement.tagName == "parsererror" )
			throw "parsererror";

		// If the type is "script", eval it in global context
		if ( type == "script" )
			jQuery.globalEval( data );

		// Get the JavaScript object, if JSON is used.
		if ( type == "json" )
			data = eval("(" + data + ")");

		return data;
	},

	// Serialize an array of form elements or a set of
	// key/values into a query string
	param: function( a ) {
		var s = [];

		// If an array was passed in, assume that it is an array
		// of form elements
		if ( a.constructor == Array || a.jquery )
			// Serialize the form elements
			jQuery.each( a, function(){
				s.push( encodeURIComponent(this.name) + "=" + encodeURIComponent( this.value ) );
			});

		// Otherwise, assume that it's an object of key/value pairs
		else
			// Serialize the key/values
			for ( var j in a )
				// If the value is an array then the key names need to be repeated
				if ( a[j] && a[j].constructor == Array )
					jQuery.each( a[j], function(){
						s.push( encodeURIComponent(j) + "=" + encodeURIComponent( this ) );
					});
				else
					s.push( encodeURIComponent(j) + "=" + encodeURIComponent( a[j] ) );

		// Return the resulting serialization
		return s.join("&");
	}

});
jQuery.fn.extend({

	show: function(speed,callback){

		return speed ?
			this.animate({
				height: "show", width: "show", opacity: "show"
			}, speed, callback) :
			
			this.filter(":hidden").each(function(){
				this.style.display = this.oldblock ? this.oldblock : "";
				if ( jQuery.css(this,"display") == "none" )
					this.style.display = "block";
			}).end();
	},

	hide: function(speed,callback){
		return speed ?
			this.animate({
				height: "hide", width: "hide", opacity: "hide"
			}, speed, callback) :
			
			this.filter(":visible").each(function(){
				this.oldblock = this.oldblock || jQuery.css(this,"display");
				if ( this.oldblock == "none" )
					this.oldblock = "block";
				this.style.display = "none";
			}).end();
	},

	// Save the old toggle function
	_toggle: jQuery.fn.toggle,
	toggle: function( fn, fn2 ){
		return jQuery.isFunction(fn) && jQuery.isFunction(fn2) ?
			this._toggle( fn, fn2 ) :
			fn ?
				this.animate({
					height: "toggle", width: "toggle", opacity: "toggle"
				}, fn, fn2) :
				this.each(function(){
					jQuery(this)[ jQuery(this).is(":hidden") ? "show" : "hide" ]();
				});
	},
	slideDown: function(speed,callback){
		return this.animate({height: "show"}, speed, callback);
	},
	slideUp: function(speed,callback){
		return this.animate({height: "hide"}, speed, callback);
	},
	slideToggle: function(speed, callback){
		return this.animate({height: "toggle"}, speed, callback);
	},
	fadeIn: function(speed, callback){
		return this.animate({opacity: "show"}, speed, callback);
	},
	fadeOut: function(speed, callback){
		return this.animate({opacity: "hide"}, speed, callback);
	},
	fadeTo: function(speed,to,callback){
		return this.animate({opacity: to}, speed, callback);
	},
	animate: function( prop, speed, easing, callback ) {
		return this.queue(function(){
			var hidden = jQuery(this).is(":hidden"),
				opt = jQuery.speed(speed, easing, callback),
				self = this;
			
			for ( var p in prop ) {
				if ( prop[p] == "hide" && hidden || prop[p] == "show" && !hidden )
					return jQuery.isFunction(opt.complete) && opt.complete.apply(this);

				if ( p == "height" || p == "width" ) {
					// Store display property
					opt.display = jQuery.css(this, "display");

					// Make sure that nothing sneaks out
					opt.overflow = this.style.overflow;
				}
			}

			if ( opt.overflow != null )
				this.style.overflow = "hidden";

			this.curAnim = jQuery.extend({}, prop);
			
			jQuery.each( prop, function(name, val){
				var e = new jQuery.fx( self, opt, name );
				if ( val.constructor == Number )
					e.custom( e.cur() || 0, val );
				else
					e[ val == "toggle" ? hidden ? "show" : "hide" : val ]( prop );
			});

			// For JS strict compliance
			return true;
		});
	},
	queue: function(type,fn){
		if ( !fn ) {
			fn = type;
			type = "fx";
		}
	
		return this.each(function(){
			if ( !this.queue )
				this.queue = {};
	
			if ( !this.queue[type] )
				this.queue[type] = [];
	
			this.queue[type].push( fn );
		
			if ( this.queue[type].length == 1 )
				fn.apply(this);
		});
	}

});

jQuery.extend({
	
	speed: function(speed, easing, fn) {
		var opt = speed && speed.constructor == Object ? speed : {
			complete: fn || !fn && easing || 
				jQuery.isFunction( speed ) && speed,
			duration: speed,
			easing: fn && easing || easing && easing.constructor != Function && easing
		};

		opt.duration = (opt.duration && opt.duration.constructor == Number ? 
			opt.duration : 
			{ slow: 600, fast: 200 }[opt.duration]) || 400;
	
		// Queueing
		opt.old = opt.complete;
		opt.complete = function(){
			jQuery.dequeue(this, "fx");
			if ( jQuery.isFunction( opt.old ) )
				opt.old.apply( this );
		};
	
		return opt;
	},
	
	easing: {
		linear: function( p, n, firstNum, diff ) {
			return firstNum + diff * p;
		},
		swing: function( p, n, firstNum, diff ) {
			return ((-Math.cos(p*Math.PI)/2) + 0.5) * diff + firstNum;
		}
	},
	
	queue: {},
	
	dequeue: function(elem,type){
		type = type || "fx";
	
		if ( elem.queue && elem.queue[type] ) {
			// Remove self
			elem.queue[type].shift();
	
			// Get next function
			var f = elem.queue[type][0];
		
			if ( f ) f.apply( elem );
		}
	},

	timers: [],

	/*
	 * I originally wrote fx() as a clone of moo.fx and in the process
	 * of making it small in size the code became illegible to sane
	 * people. You've been warned.
	 */
	
	fx: function( elem, options, prop ){

		var z = this;

		// The styles
		var y = elem.style;
		
		// Simple function for setting a style value
		z.a = function(){
			if ( options.step )
				options.step.apply( elem, [ z.now ] );

			if ( prop == "opacity" )
				jQuery.attr(y, "opacity", z.now); // Let attr handle opacity
			else {
				y[prop] = parseInt(z.now) + "px";

				// Set display property to block for height/width animations
				if ( prop == "height" || prop == "width" )
					y.display = "block";
			}
		};

		// Figure out the maximum number to run to
		z.max = function(){
			return parseFloat( jQuery.css(elem,prop) );
		};

		// Get the current size
		z.cur = function(){
			var r = parseFloat( jQuery.curCSS(elem, prop) );
			return r && r > -10000 ? r : z.max();
		};

		// Start an animation from one number to another
		z.custom = function(from,to){
			z.startTime = (new Date()).getTime();
			z.now = from;
			z.a();

			jQuery.timers.push(function(){
				return z.step(from, to);
			});

			if ( jQuery.timers.length == 1 ) {
				var timer = setInterval(function(){
					var timers = jQuery.timers;
					
					for ( var i = 0; i < timers.length; i++ )
						if ( !timers[i]() )
							timers.splice(i--, 1);

					if ( !timers.length )
						clearInterval( timer );
				}, 13);
			}
		};

		// Simple 'show' function
		z.show = function(){
			if ( !elem.orig ) elem.orig = {};

			// Remember where we started, so that we can go back to it later
			elem.orig[prop] = jQuery.attr( elem.style, prop );

			options.show = true;

			// Begin the animation
			z.custom(0, this.cur());

			// Make sure that we start at a small width/height to avoid any
			// flash of content
			if ( prop != "opacity" )
				y[prop] = "1px";
			
			// Start by showing the element
			jQuery(elem).show();
		};

		// Simple 'hide' function
		z.hide = function(){
			if ( !elem.orig ) elem.orig = {};

			// Remember where we started, so that we can go back to it later
			elem.orig[prop] = jQuery.attr( elem.style, prop );

			options.hide = true;

			// Begin the animation
			z.custom(this.cur(), 0);
		};

		// Each step of an animation
		z.step = function(firstNum, lastNum){
			var t = (new Date()).getTime();

			if (t > options.duration + z.startTime) {
				z.now = lastNum;
				z.a();

				if (elem.curAnim) elem.curAnim[ prop ] = true;

				var done = true;
				for ( var i in elem.curAnim )
					if ( elem.curAnim[i] !== true )
						done = false;

				if ( done ) {
					if ( options.display != null ) {
						// Reset the overflow
						y.overflow = options.overflow;
					
						// Reset the display
						y.display = options.display;
						if ( jQuery.css(elem, "display") == "none" )
							y.display = "block";
					}

					// Hide the element if the "hide" operation was done
					if ( options.hide )
						y.display = "none";

					// Reset the properties, if the item has been hidden or shown
					if ( options.hide || options.show )
						for ( var p in elem.curAnim )
							jQuery.attr(y, p, elem.orig[p]);
				}

				// If a callback was provided, execute it
				if ( done && jQuery.isFunction( options.complete ) )
					// Execute the complete function
					options.complete.apply( elem );

				return false;
			} else {
				var n = t - this.startTime;
				// Figure out where in the animation we are and set the number
				var p = n / options.duration;
				
				// Perform the easing function, defaults to swing
				z.now = jQuery.easing[options.easing || (jQuery.easing.swing ? "swing" : "linear")](p, n, firstNum, (lastNum-firstNum), options.duration);

				// Perform the next step of the animation
				z.a();
			}

			return true;
		};
	
	}
});
})();
/**
 * Cookie plugin
 *
 * Copyright (c) 2006 Klaus Hartl (stilbuero.de)
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 *
 */

/**
 * Create a cookie with the given name and value and other optional parameters.
 *
 * @example $.cookie('the_cookie', 'the_value');
 * @desc Set the value of a cookie.
 * @example $.cookie('the_cookie', 'the_value', {expires: 7, path: '/', domain: 'jquery.com', secure: true});
 * @desc Create a cookie with all available options.
 * @example $.cookie('the_cookie', 'the_value');
 * @desc Create a session cookie.
 * @example $.cookie('the_cookie', '', {expires: -1});
 * @desc Delete a cookie by setting a date in the past.
 *
 * @param String name The name of the cookie.
 * @param String value The value of the cookie.
 * @param Object options An object literal containing key/value pairs to provide optional cookie attributes.
 * @option Number|Date expires Either an integer specifying the expiration date from now on in days or a Date object.
 *                             If a negative value is specified (e.g. a date in the past), the cookie will be deleted.
 *                             If set to null or omitted, the cookie will be a session cookie and will not be retained
 *                             when the the browser exits.
 * @option String path The value of the path atribute of the cookie (default: path of page that created the cookie).
 * @option String domain The value of the domain attribute of the cookie (default: domain of page that created the cookie).
 * @option Boolean secure If true, the secure attribute of the cookie will be set and the cookie transmission will
 *                        require a secure protocol (like HTTPS).
 * @type undefined
 *
 * @name $.cookie
 * @cat Plugins/Cookie
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */

/**
 * Get the value of a cookie with the given name.
 *
 * @example $.cookie('the_cookie');
 * @desc Get the value of a cookie.
 *
 * @param String name The name of the cookie.
 * @return The value of the cookie.
 * @type String
 *
 * @name $.cookie
 * @cat Plugins/Cookie
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */
jQuery.cookie = function(name, value, options) {
    if (typeof value != 'undefined') { // name and value given, set cookie
        options = options || {};
        var expires = '';
        if (options.expires && (typeof options.expires == 'number' || options.expires.toGMTString)) {
            var date;
            if (typeof options.expires == 'number') {
                date = new Date();
                date.setTime(date.getTime() + (options.expires * 24 * 60 * 60 * 1000));
            } else {
                date = options.expires;
            }
            expires = '; expires=' + date.toGMTString(); // use expires attribute, max-age is not supported by IE
        }
        var path = options.path ? '; path=' + options.path : '';
        var domain = options.domain ? '; domain=' + options.domain : '';
        var secure = options.secure ? '; secure' : '';
        document.cookie = [name, '=', encodeURIComponent(value), expires, path, domain, secure].join('');
    } else { // only name given, get cookie
        var cookieValue = null;
        if (document.cookie && document.cookie != '') {
            var cookies = document.cookie.split(';');
            for (var i = 0; i < cookies.length; i++) {
                var cookie = jQuery.trim(cookies[i]);
                // Does this cookie string begin with the name we want?
                if (cookie.substring(0, name.length + 1) == (name + '=')) {
                    cookieValue = decodeURIComponent(cookie.substring(name.length + 1));
                    break;
                }
            }
        }
        return cookieValue;
    }
};
/* Copyright (c) 2007 Paul Bakaus (paul.bakaus@googlemail.com) and Brandon Aaron (brandon.aaron@gmail.com || http://brandonaaron.net)
 * Dual licensed under the MIT (http://www.opensource.org/licenses/mit-license.php)
 * and GPL (http://www.opensource.org/licenses/gpl-license.php) licenses.
 *
 * $LastChangedDate: 2007-08-12 22:47:23 -0500 (Sun, 12 Aug 2007) $
 * $Rev: 2669 $
 *
 * Version: 1.1
 *
 * Requires: jQuery 1.1.3+
 */

(function($){

// store a copy of the core height and width methods
var height = $.fn.height,
    width  = $.fn.width;

$.fn.extend({
	/**
	 * If used on document, returns the document's height (innerHeight).
	 * If used on window, returns the viewport's (window) height.
	 * See core docs on height() to see what happens when used on an element.
	 *
	 * @example $("#testdiv").height()
	 * @result 200
	 *
	 * @example $(document).height()
	 * @result 800
	 *
	 * @example $(window).height()
	 * @result 400
	 *
	 * @name height
	 * @type Number
	 * @cat Plugins/Dimensions
	 */
	height: function() {
		if (!this[0]) error();
		if ( this[0] == window )
			if ( ($.browser.mozilla || $.browser.opera) && $(document).width() > self.innerWidth)
				// mozilla and opera both return width + scrollbar width
				return self.innerHeight - getScrollbarWidth();
			else
				return self.innerHeight ||
					$.boxModel && document.documentElement.clientHeight || 
					document.body.clientHeight;
		
		if ( this[0] == document )
			return Math.max( document.body.scrollHeight, document.body.offsetHeight );
		
		return height.apply(this, arguments);
	},
	
	/**
	 * If used on document, returns the document's width (innerWidth).
	 * If used on window, returns the viewport's (window) width.
	 * See core docs on width() to see what happens when used on an element.
	 *
	 * @example $("#testdiv").width()
	 * @result 200
	 *
	 * @example $(document).width()
	 * @result 800
	 *
	 * @example $(window).width()
	 * @result 400
	 *
	 * @name width
	 * @type Number
	 * @cat Plugins/Dimensions
	 */
	width: function() {
		if (!this[0]) error();
		if ( this[0] == window )
			if (($.browser.mozilla || $.browser.opera) && $(document).height() > self.innerHeight)
				// mozilla and opera both return width + scrollbar width
				return self.innerWidth - getScrollbarWidth();
			else
				return self.innerWidth ||
					$.boxModel && document.documentElement.clientWidth ||
					document.body.clientWidth;

		if ( this[0] == document )
			if ($.browser.mozilla) {
				// mozilla reports scrollWidth and offsetWidth as the same
				var scrollLeft = self.pageXOffset;
				self.scrollTo(99999999, self.pageYOffset);
				var scrollWidth = self.pageXOffset;
				self.scrollTo(scrollLeft, self.pageYOffset);
				return document.body.offsetWidth + scrollWidth;
			}
			else 
				return Math.max( document.body.scrollWidth, document.body.offsetWidth );

		return width.apply(this, arguments);
	},
	
	/**
	 * Gets the inner height (excludes the border and includes the padding) for the first matched element.
	 * If used on document, returns the document's height (innerHeight).
	 * If used on window, returns the viewport's (window) height.
	 *
	 * @example $("#testdiv").innerHeight()
	 * @result 210
	 *
	 * @name innerHeight
	 * @type Number
	 * @cat Plugins/Dimensions
	 */
	innerHeight: function() {
		if (!this[0]) error();
		return this[0] == window || this[0] == document ?
			this.height() :
			this.is(':visible') ?
				this[0].offsetHeight - num(this, 'borderTopWidth') - num(this, 'borderBottomWidth') :
				this.height() + num(this, 'paddingTop') + num(this, 'paddingBottom');
	},
	
	/**
	 * Gets the inner width (excludes the border and includes the padding) for the first matched element.
	 * If used on document, returns the document's width (innerWidth).
	 * If used on window, returns the viewport's (window) width.
	 *
	 * @example $("#testdiv").innerWidth()
	 * @result 210
	 *
	 * @name innerWidth
	 * @type Number
	 * @cat Plugins/Dimensions
	 */
	innerWidth: function() {
		if (!this[0]) error();
		return this[0] == window || this[0] == document ?
			this.width() :
			this.is(':visible') ?
				this[0].offsetWidth - num(this, 'borderLeftWidth') - num(this, 'borderRightWidth') :
				this.width() + num(this, 'paddingLeft') + num(this, 'paddingRight');
	},
	
	/**
	 * Gets the outer height (includes the border and padding) for the first matched element.
	 * If used on document, returns the document's height (innerHeight).
	 * If used on window, returns the viewport's (window) height.
	 *
	 * The margin can be included in the calculation by passing an options map with margin
	 * set to true.
	 *
	 * @example $("#testdiv").outerHeight()
	 * @result 220
	 *
	 * @example $("#testdiv").outerHeight({ margin: true })
	 * @result 240
	 *
	 * @name outerHeight
	 * @type Number
	 * @param Map options Optional settings to configure the way the outer height is calculated.
	 * @cat Plugins/Dimensions
	 */
	outerHeight: function(options) {
		if (!this[0]) error();
		options = $.extend({ margin: false }, options || {});
		return this[0] == window || this[0] == document ?
			this.height() :
			this.is(':visible') ?
				this[0].offsetHeight + (options.margin ? (num(this, 'marginTop') + num(this, 'marginBottom')) : 0) :
				this.height() 
					+ num(this,'borderTopWidth') + num(this, 'borderBottomWidth') 
					+ num(this, 'paddingTop') + num(this, 'paddingBottom')
					+ (options.margin ? (num(this, 'marginTop') + num(this, 'marginBottom')) : 0);
	},
	
	/**
	 * Gets the outer width (including the border and padding) for the first matched element.
	 * If used on document, returns the document's width (innerWidth).
	 * If used on window, returns the viewport's (window) width.
	 *
	 * The margin can be included in the calculation by passing an options map with margin
	 * set to true.
	 *
	 * @example $("#testdiv").outerWidth()
	 * @result 1000
	 *
	 * @example $("#testdiv").outerWidth({ margin: true })
	 * @result 1020
	 * 
	 * @name outerHeight
	 * @type Number
	 * @param Map options Optional settings to configure the way the outer width is calculated.
	 * @cat Plugins/Dimensions
	 */
	outerWidth: function(options) {
		if (!this[0]) error();
		options = $.extend({ margin: false }, options || {});
		return this[0] == window || this[0] == document ?
			this.width() :
			this.is(':visible') ?
				this[0].offsetWidth + (options.margin ? (num(this, 'marginLeft') + num(this, 'marginRight')) : 0) :
				this.width() 
					+ num(this, 'borderLeftWidth') + num(this, 'borderRightWidth') 
					+ num(this, 'paddingLeft') + num(this, 'paddingRight')
					+ (options.margin ? (num(this, 'marginLeft') + num(this, 'marginRight')) : 0);
	},
	
	/**
	 * Gets how many pixels the user has scrolled to the right (scrollLeft).
	 * Works on containers with overflow: auto and window/document.
	 *
	 * @example $(window).scrollLeft()
	 * @result 100
	 *
	 * @example $(document).scrollLeft()
	 * @result 100
	 * 
	 * @example $("#testdiv").scrollLeft()
	 * @result 100
	 *
	 * @name scrollLeft
	 * @type Number
	 * @cat Plugins/Dimensions
	 */
	/**
	 * Sets the scrollLeft property for each element and continues the chain.
	 * Works on containers with overflow: auto and window/document.
	 *
	 * @example $(window).scrollLeft(100).scrollLeft()
	 * @result 100
	 * 
	 * @example $(document).scrollLeft(100).scrollLeft()
	 * @result 100
	 *
	 * @example $("#testdiv").scrollLeft(100).scrollLeft()
	 * @result 100
	 *
	 * @name scrollLeft
	 * @param Number value A positive number representing the desired scrollLeft.
	 * @type jQuery
	 * @cat Plugins/Dimensions
	 */
	scrollLeft: function(val) {
		if (!this[0]) error();
		if ( val != undefined )
			// set the scroll left
			return this.each(function() {
				if (this == window || this == document)
					window.scrollTo( val, $(window).scrollTop() );
				else
					this.scrollLeft = val;
			});
		
		// return the scroll left offest in pixels
		if ( this[0] == window || this[0] == document )
			return self.pageXOffset ||
				$.boxModel && document.documentElement.scrollLeft ||
				document.body.scrollLeft;
				
		return this[0].scrollLeft;
	},
	
	/**
	 * Gets how many pixels the user has scrolled to the bottom (scrollTop).
	 * Works on containers with overflow: auto and window/document.
	 *
	 * @example $(window).scrollTop()
	 * @result 100
	 *
	 * @example $(document).scrollTop()
	 * @result 100
	 * 
	 * @example $("#testdiv").scrollTop()
	 * @result 100
	 *
	 * @name scrollTop
	 * @type Number
	 * @cat Plugins/Dimensions
	 */
	/**
	 * Sets the scrollTop property for each element and continues the chain.
	 * Works on containers with overflow: auto and window/document.
	 *
	 * @example $(window).scrollTop(100).scrollTop()
	 * @result 100
	 * 
	 * @example $(document).scrollTop(100).scrollTop()
	 * @result 100
	 *
	 * @example $("#testdiv").scrollTop(100).scrollTop()
	 * @result 100
	 *
	 * @name scrollTop
	 * @param Number value A positive number representing the desired scrollTop.
	 * @type jQuery
	 * @cat Plugins/Dimensions
	 */
	scrollTop: function(val) {
		if (!this[0]) error();
		if ( val != undefined )
			// set the scroll top
			return this.each(function() {
				if (this == window || this == document)
					window.scrollTo( $(window).scrollLeft(), val );
				else
					this.scrollTop = val;
			});
		
		// return the scroll top offset in pixels
		if ( this[0] == window || this[0] == document )
			return self.pageYOffset ||
				$.boxModel && document.documentElement.scrollTop ||
				document.body.scrollTop;

		return this[0].scrollTop;
	},
	
	/** 
	 * Gets the top and left positioned offset in pixels.
	 * The positioned offset is the offset between a positioned
	 * parent and the element itself.
	 *
	 * For accurate calculations make sure to use pixel values for margins, borders and padding.
	 *
	 * @example $("#testdiv").position()
	 * @result { top: 100, left: 100 }
	 *
	 * @example var position = {};
	 * $("#testdiv").position(position)
	 * @result position = { top: 100, left: 100 }
	 * 
	 * @name position
	 * @param Object returnObject Optional An object to store the return value in, so as not to break the chain. If passed in the
	 *                            chain will not be broken and the result will be assigned to this object.
	 * @type Object
	 * @cat Plugins/Dimensions
	 */
	position: function(returnObject) {
		return this.offset({ margin: false, scroll: false, relativeTo: this.offsetParent() }, returnObject);
	},
	
	/**
	 * Gets the location of the element in pixels from the top left corner of the viewport.
	 * The offset method takes an optional map of key value pairs to configure the way
	 * the offset is calculated. Here are the different options.
	 *
	 * (Boolean) margin - Should the margin of the element be included in the calculations? True by default.
	 * (Boolean) border - Should the border of the element be included in the calculations? False by default. 
	 * (Boolean) padding - Should the padding of the element be included in the calculations? False by default. 
	 * (Boolean) scroll - Should the scroll offsets of the parent elements be included in the calculations? True by default.
	 *                    When true it adds the total scroll offsets of all parents to the total offset and also adds two
	 *                    properties to the returned object, scrollTop and scrollLeft.
	 * (Boolean) lite - When true it will use the offsetLite method instead of the full-blown, slower offset method. False by default.
	 *                  Only use this when margins, borders and padding calculations don't matter.
	 * (HTML Element) relativeTo - This should be a parent of the element and should have position (like absolute or relative).
	 *                             It will retreive the offset relative to this parent element. By default it is the body element.
	 *
	 * Also an object can be passed as the second paramater to
	 * catch the value of the return and continue the chain.
	 *
	 * For accurate calculations make sure to use pixel values for margins, borders and padding.
	 * 
	 * Known issues:
	 *  - Issue: A div positioned relative or static without any content before it and its parent will report an offsetTop of 0 in Safari
	 *    Workaround: Place content before the relative div ... and set height and width to 0 and overflow to hidden
	 *
	 * @example $("#testdiv").offset()
	 * @result { top: 100, left: 100, scrollTop: 10, scrollLeft: 10 }
	 *
	 * @example $("#testdiv").offset({ scroll: false })
	 * @result { top: 90, left: 90 }
	 *
	 * @example var offset = {}
	 * $("#testdiv").offset({ scroll: false }, offset)
	 * @result offset = { top: 90, left: 90 }
	 *
	 * @name offset
	 * @param Map options Optional settings to configure the way the offset is calculated.
	 * @param Object returnObject An object to store the return value in, so as not to break the chain. If passed in the
	 *                            chain will not be broken and the result will be assigned to this object.
	 * @type Object
	 * @cat Plugins/Dimensions
	 */
	offset: function(options, returnObject) {
		if (!this[0]) error();
		var x = 0, y = 0, sl = 0, st = 0,
		    elem = this[0], parent = this[0], op, parPos, elemPos = $.css(elem, 'position'),
		    mo = $.browser.mozilla, ie = $.browser.msie, oa = $.browser.opera,
		    sf = $.browser.safari, sf3 = $.browser.safari && parseInt($.browser.version) > 520,
		    absparent = false, relparent = false, 
		    options = $.extend({ margin: true, border: false, padding: false, scroll: true, lite: false, relativeTo: document.body }, options || {});
		
		// Use offsetLite if lite option is true
		if (options.lite) return this.offsetLite(options, returnObject);
		// Get the HTMLElement if relativeTo is a jquery collection
		if (options.relativeTo.jquery) options.relativeTo = options.relativeTo[0];
		
		if (elem.tagName == 'BODY') {
			// Safari 2 is the only one to get offsetLeft and offsetTop properties of the body "correct"
			// Except they all mess up when the body is positioned absolute or relative
			x = elem.offsetLeft;
			y = elem.offsetTop;
			// Mozilla ignores margin and subtracts border from body element
			if (mo) {
				x += num(elem, 'marginLeft') + (num(elem, 'borderLeftWidth')*2);
				y += num(elem, 'marginTop')  + (num(elem, 'borderTopWidth') *2);
			} else
			// Opera ignores margin
			if (oa) {
				x += num(elem, 'marginLeft');
				y += num(elem, 'marginTop');
			} else
			// IE does not add the border in Standards Mode
			if ((ie && jQuery.boxModel)) {
				x += num(elem, 'borderLeftWidth');
				y += num(elem, 'borderTopWidth');
			} else
			// Safari 3 doesn't not include border or margin
			if (sf3) {
				x += num(elem, 'marginLeft') + num(elem, 'borderLeftWidth');
				y += num(elem, 'marginTop')  + num(elem, 'borderTopWidth');
			}
		} else {
			do {
				parPos = $.css(parent, 'position');
			
				x += parent.offsetLeft;
				y += parent.offsetTop;

				// Mozilla and IE do not add the border
				if (mo || ie || sf3) {
					// add borders to offset
					x += num(parent, 'borderLeftWidth');
					y += num(parent, 'borderTopWidth');

					// Mozilla does not include the border on body if an element isn't positioned absolute and is without an absolute parent
					if (mo && parPos == 'absolute') absparent = true;
					// IE does not include the border on the body if an element is position static and without an absolute or relative parent
					if (ie && parPos == 'relative') relparent = true;
				}

				op = parent.offsetParent || document.body;
				if (options.scroll || mo) {
					do {
						if (options.scroll) {
							// get scroll offsets
							sl += parent.scrollLeft;
							st += parent.scrollTop;
						}
						
						// Opera sometimes incorrectly reports scroll offset for elements with display set to table-row or inline
						if (oa && ($.css(parent, 'display') || '').match(/table-row|inline/)) {
							sl = sl - ((parent.scrollLeft == parent.offsetLeft) ? parent.scrollLeft : 0);
							st = st - ((parent.scrollTop == parent.offsetTop) ? parent.scrollTop : 0);
						}
				
						// Mozilla does not add the border for a parent that has overflow set to anything but visible
						if (mo && parent != elem && $.css(parent, 'overflow') != 'visible') {
							x += num(parent, 'borderLeftWidth');
							y += num(parent, 'borderTopWidth');
						}
				
						parent = parent.parentNode;
					} while (parent != op);
				}
				parent = op;
				
				// exit the loop if we are at the relativeTo option but not if it is the body or html tag
				if (parent == options.relativeTo && !(parent.tagName == 'BODY' || parent.tagName == 'HTML'))  {
					// Mozilla does not add the border for a parent that has overflow set to anything but visible
					if (mo && parent != elem && $.css(parent, 'overflow') != 'visible') {
						x += num(parent, 'borderLeftWidth');
						y += num(parent, 'borderTopWidth');
					}
					// Safari 2 and opera includes border on positioned parents
					if ( ((sf && !sf3) || oa) && parPos != 'static' ) {
						x -= num(op, 'borderLeftWidth');
						y -= num(op, 'borderTopWidth');
					}
					break;
				}
				if (parent.tagName == 'BODY' || parent.tagName == 'HTML') {
					// Safari 2 and IE Standards Mode doesn't add the body margin for elments positioned with static or relative
					if (((sf && !sf3) || (ie && $.boxModel)) && elemPos != 'absolute' && elemPos != 'fixed') {
						x += num(parent, 'marginLeft');
						y += num(parent, 'marginTop');
					}
					// Safari 3 does not include the border on body
					// Mozilla does not include the border on body if an element isn't positioned absolute and is without an absolute parent
					// IE does not include the border on the body if an element is positioned static and without an absolute or relative parent
					if ( sf3 || (mo && !absparent && elemPos != 'fixed') || 
					     (ie && elemPos == 'static' && !relparent) ) {
						x += num(parent, 'borderLeftWidth');
						y += num(parent, 'borderTopWidth');
					}
					break; // Exit the loop
				}
			} while (parent);
		}

		var returnValue = handleOffsetReturn(elem, options, x, y, sl, st);

		if (returnObject) { $.extend(returnObject, returnValue); return this; }
		else              { return returnValue; }
	},
	
	/**
	 * Gets the location of the element in pixels from the top left corner of the viewport.
	 * This method is much faster than offset but not as accurate when borders and margins are
	 * on the element and/or its parents. This method can be invoked
	 * by setting the lite option to true in the offset method.
	 * The offsetLite method takes an optional map of key value pairs to configure the way
	 * the offset is calculated. Here are the different options.
	 *
	 * (Boolean) margin - Should the margin of the element be included in the calculations? True by default.
	 * (Boolean) border - Should the border of the element be included in the calculations? False by default. 
	 * (Boolean) padding - Should the padding of the element be included in the calcuations? False by default. 
	 * (Boolean) scroll - Sould the scroll offsets of the parent elements be included int he calculations? True by default.
	 *                    When true it adds the total scroll offsets of all parents to the total offset and also adds two
	 *                    properties to the returned object, scrollTop and scrollLeft.
	 * (HTML Element) relativeTo - This should be a parent of the element and should have position (like absolute or relative).
	 *                             It will retreive the offset relative to this parent element. By default it is the body element.
	 *
	 * @name offsetLite
	 * @param Map options Optional settings to configure the way the offset is calculated.
	 * @param Object returnObject An object to store the return value in, so as not to break the chain. If passed in the
	 *                            chain will not be broken and the result will be assigned to this object.
	 * @type Object
	 * @cat Plugins/Dimensions
	 */
	offsetLite: function(options, returnObject) {
		if (!this[0]) error();
		var x = 0, y = 0, sl = 0, st = 0, parent = this[0], offsetParent, 
		    options = $.extend({ margin: true, border: false, padding: false, scroll: true, relativeTo: document.body }, options || {});
				
		// Get the HTMLElement if relativeTo is a jquery collection
		if (options.relativeTo.jquery) options.relativeTo = options.relativeTo[0];
		
		do {
			x += parent.offsetLeft;
			y += parent.offsetTop;

			offsetParent = parent.offsetParent || document.body;
			if (options.scroll) {
				// get scroll offsets
				do {
					sl += parent.scrollLeft;
					st += parent.scrollTop;
					parent = parent.parentNode;
				} while(parent != offsetParent);
			}
			parent = offsetParent;
		} while (parent && parent.tagName != 'BODY' && parent.tagName != 'HTML' && parent != options.relativeTo);

		var returnValue = handleOffsetReturn(this[0], options, x, y, sl, st);

		if (returnObject) { $.extend(returnObject, returnValue); return this; }
		else              { return returnValue; }
	},
	
	/**
	 * Returns a jQuery collection with the positioned parent of 
	 * the first matched element. This is the first parent of 
	 * the element that has position (as in relative or absolute).
	 *
	 * @name offsetParent
	 * @type jQuery
	 * @cat Plugins/Dimensions
	 */
	offsetParent: function() {
		if (!this[0]) error();
		var offsetParent = this[0].offsetParent;
		while ( offsetParent && (offsetParent.tagName != 'BODY' && $.css(offsetParent, 'position') == 'static') )
			offsetParent = offsetParent.offsetParent;
		return $(offsetParent);
	}
});

/**
 * Throws an error message when no elements are in the jQuery collection
 * @private
 */
var error = function() {
	throw "Dimensions: jQuery collection is empty";
};

/**
 * Handles converting a CSS Style into an Integer.
 * @private
 */
var num = function(el, prop) {
	return parseInt($.css(el.jquery?el[0]:el,prop))||0;
};

/**
 * Handles the return value of the offset and offsetLite methods.
 * @private
 */
var handleOffsetReturn = function(elem, options, x, y, sl, st) {
	if ( !options.margin ) {
		x -= num(elem, 'marginLeft');
		y -= num(elem, 'marginTop');
	}

	// Safari and Opera do not add the border for the element
	if ( options.border && (($.browser.safari && parseInt($.browser.version) < 520) || $.browser.opera) ) {
		x += num(elem, 'borderLeftWidth');
		y += num(elem, 'borderTopWidth');
	} else if ( !options.border && !(($.browser.safari && parseInt($.browser.version) < 520) || $.browser.opera) ) {
		x -= num(elem, 'borderLeftWidth');
		y -= num(elem, 'borderTopWidth');
	}

	if ( options.padding ) {
		x += num(elem, 'paddingLeft');
		y += num(elem, 'paddingTop');
	}
	
	// do not include scroll offset on the element ... opera sometimes reports scroll offset as actual offset
	if ( options.scroll && (!$.browser.opera || elem.offsetLeft != elem.scrollLeft && elem.offsetTop != elem.scrollLeft) ) {
		sl -= elem.scrollLeft;
		st -= elem.scrollTop;
	}

	return options.scroll ? { top: y - st, left: x - sl, scrollTop:  st, scrollLeft: sl }
	                      : { top: y, left: x };
};

/**
 * Gets the width of the OS scrollbar
 * @private
 */
var scrollbarWidth = 0;
var getScrollbarWidth = function() {
	if (!scrollbarWidth) {
		var testEl = $('<div>')
				.css({
					width: 100,
					height: 100,
					overflow: 'auto',
					position: 'absolute',
					top: -1000,
					left: -1000
				})
				.appendTo('body');
		scrollbarWidth = 100 - testEl
			.append('<div>')
			.find('div')
				.css({
					width: '100%',
					height: 200
				})
				.width();
		testEl.remove();
	}
	return scrollbarWidth;
};

})(jQuery);
/**
* hoverIntent is similar to jQuery's built-in "hover" function except that
* instead of firing the onMouseOver event immediately, hoverIntent checks
* to see if the user's mouse has slowed down (beneath the sensitivity
* threshold) before firing the onMouseOver event.
* 
* hoverIntent r5 // 2007.03.27 // jQuery 1.1.2
* <http://cherne.net/brian/resources/jquery.hoverIntent.html>
* 
* hoverIntent is currently available for use in all personal or commercial 
* projects under both MIT and GPL licenses. This means that you can choose 
* the license that best suits your project, and use it accordingly.
* 
* // basic usage (just like .hover) receives onMouseOver and onMouseOut functions
* $("ul li").hoverIntent( showNav , hideNav );
* 
* // advanced usage receives configuration object only
* $("ul li").hoverIntent({
*	sensitivity: 2, // number = sensitivity threshold (must be 1 or higher)
*	interval: 50,   // number = milliseconds of polling interval
*	over: showNav,  // function = onMouseOver callback (required)
*	timeout: 100,   // number = milliseconds delay before onMouseOut function call
*	out: hideNav    // function = onMouseOut callback (required)
* });
* 
* @param  f  onMouseOver function || An object with configuration options
* @param  g  onMouseOut function  || Nothing (use configuration options object)
* @return    The object (aka "this") that called hoverIntent, and the event object
* @author    Brian Cherne <brian@cherne.net>
*/
(function($) {
	$.fn.hoverIntent = function(f,g) {
		// default configuration options
		var cfg = {
			sensitivity: 7,
			interval: 100,
			timeout: 0
		};
		// override configuration options with user supplied object
		cfg = $.extend(cfg, g ? { over: f, out: g } : f );

		// instantiate variables
		// cX, cY = current X and Y position of mouse, updated by mousemove event
		// pX, pY = previous X and Y position of mouse, set by mouseover and polling interval
		var cX, cY, pX, pY;

		// A private function for getting mouse position
		var track = function(ev) {
			cX = ev.pageX;
			cY = ev.pageY;
		};

		// A private function for comparing current and previous mouse position
		var compare = function(ev,ob) {
			ob.hoverIntent_t = clearTimeout(ob.hoverIntent_t);
			// compare mouse positions to see if they've crossed the threshold
			if ( ( Math.abs(pX-cX) + Math.abs(pY-cY) ) < cfg.sensitivity ) {
				$(ob).unbind("mousemove",track);
				// set hoverIntent state to true (so mouseOut can be called)
				ob.hoverIntent_s = 1;
				return cfg.over.apply(ob,[ev]);
			} else {
				// set previous coordinates for next time
				pX = cX; pY = cY;
				// use self-calling timeout, guarantees intervals are spaced out properly (avoids JavaScript timer bugs)
				ob.hoverIntent_t = setTimeout( function(){compare(ev, ob);} , cfg.interval );
			}
		};

		// A private function for delaying the mouseOut function
		var delay = function(ev,ob) {
			ob.hoverIntent_t = clearTimeout(ob.hoverIntent_t);
			ob.hoverIntent_s = 0;
			return cfg.out.apply(ob,[ev]);
		};

		// A private function for handling mouse 'hovering'
		var handleHover = function(e) {
			// next three lines copied from jQuery.hover, ignore children onMouseOver/onMouseOut
			var p = (e.type == "mouseover" ? e.fromElement : e.toElement) || e.relatedTarget;
			while ( p && p != this ) { try { p = p.parentNode; } catch(e) { p = this; } }
			if ( p == this ) { return false; }

			// copy objects to be passed into t (required for event object to be passed in IE)
			var ev = jQuery.extend({},e);
			var ob = this;

			// cancel hoverIntent timer if it exists
			if (ob.hoverIntent_t) { ob.hoverIntent_t = clearTimeout(ob.hoverIntent_t); }

			// else e.type == "onmouseover"
			if (e.type == "mouseover") {
				// set "previous" X and Y position based on initial entry point
				pX = ev.pageX; pY = ev.pageY;
				// update "current" X and Y position based on mousemove
				$(ob).bind("mousemove",track);
				// start polling interval (self-calling timeout) to compare mouse coordinates over time
				if (ob.hoverIntent_s != 1) { ob.hoverIntent_t = setTimeout( function(){compare(ev,ob);} , cfg.interval );}

			// else e.type == "onmouseout"
			} else {
				// unbind expensive mousemove event
				$(ob).unbind("mousemove",track);
				// if hoverIntent state is true, then call the mouseOut function after the specified delay
				if (ob.hoverIntent_s == 1) { ob.hoverIntent_t = setTimeout( function(){delay(ev,ob);} , cfg.timeout );}
			}
		};

		// bind the function to the two event listeners
		return this.mouseover(handleHover).mouseout(handleHover);
	};
})(jQuery);
/**
 * Interface Elements for jQuery
 * Accordion
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 */

/**
 * Create an accordion from a HTML structure
 *
 * @example $('#myAccordion').Accordion(
 *				{
 *					headerSelector	: 'dt',
 *					panelSelector	: 'dd',
 *					activeClass		: 'myAccordionActive',
 *					hoverClass		: 'myAccordionHover',
 *					panelHeight		: 200,
 *					speed			: 300
 *				}
 *			);
 * @desc Converts definition list with id 'myAccordion' into an accordion width dt tags as headers and dd tags as panels
 * 
 * @name Accordion
 * @description Create an accordion from a HTML structure
 * @param Hash hash A hash of parameters
 * @option Integer panelHeight the pannels' height
 * @option String headerSelector selector for header elements
 * @option String panelSelector selector for panel elements
 * @option String activeClass (optional) CSS Class for active header
 * @option String hoverClass (optional) CSS Class for hovered header
 * @option Function onShow (optional) callback called whenever an pannel gets active
 * @option Function onHide (optional) callback called whenever an pannel gets incative
 * @option Function onClick (optional) callback called just before an panel gets active
 * @option Mixed speed (optional) animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
 * @option Integer crrentPanel (otional) the active panel on initialisation
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.iAccordion = {
	build : function(options)
	{
		return this.each(
			function()
			{
				if (!options.headerSelector || !options.panelSelector)
					return;
				var el = this;
				el.accordionCfg = {
					panelHeight			: options.panelHeight||300,
					headerSelector		: options.headerSelector,
					panelSelector		: options.panelSelector,
					activeClass			: options.activeClass||'fakeAccordionClass',
					hoverClass			: options.hoverClass||'fakeAccordionClass',
					onShow				: options.onShow && typeof options.onShow == 'function' ? options.onShow : false,
					onHide				: options.onShow && typeof options.onHide == 'function' ? options.onHide : false,
					onClick				: options.onClick && typeof options.onClick == 'function' ? options.onClick : false,
					headers				: jQuery(options.headerSelector, this),
					panels				: jQuery(options.panelSelector, this),
					speed				: options.speed||400,
					currentPanel		: options.currentPanel||0
				};
				el.accordionCfg.panels
					.hide()
					.css('height', '1px')
					.eq(0)
					.css(
						{
							height: el.accordionCfg.panelHeight + 'px',
							display: 'block'
						}
					)
					.end();
					
				el.accordionCfg.headers
				.each(
					function(nr)
					{
						this.accordionPos = nr;
					}
				)
				.hover(
					function()
					{
						jQuery(this).addClass(el.accordionCfg.hoverClass);
					},
					function()
					{
						jQuery(this).removeClass(el.accordionCfg.hoverClass);
					}
				)
				.bind(
					'click',
					function(e)
					{
						if (el.accordionCfg.currentPanel == this.accordionPos)
							return;
						el.accordionCfg.headers
							.eq(el.accordionCfg.currentPanel)
							.removeClass(el.accordionCfg.activeClass)
							.end()
							.eq(this.accordionPos)
							.addClass(el.accordionCfg.activeClass)
							.end();
						el.accordionCfg.panels
						.eq(el.accordionCfg.currentPanel)
							.animate(
								{height:0},
								el.accordionCfg.speed,
								function()
								{
									this.style.display = 'none';
									if (el.accordionCfg.onHide) {
										el.accordionCfg.onHide.apply(el, [this]);
									}
								}
							)
						.end()
						.eq(this.accordionPos)
							.show()
							.animate (
								{height:el.accordionCfg.panelHeight},
								el.accordionCfg.speed,
								function()
								{
									this.style.display = 'block';
									if (el.accordionCfg.onShow) {
										el.accordionCfg.onShow.apply(el, [this]);
									}
								}
							)
						.end();
						
						if (el.accordionCfg.onClick) {
							el.accordionCfg.onClick.apply(
								el, 
								[
									this, 
									el.accordionCfg.panels.get(this.accordionPos),
									el.accordionCfg.headers.get(el.accordionCfg.currentPanel),
									el.accordionCfg.panels.get(el.accordionCfg.currentPanel)
								]
							);
						}
						el.accordionCfg.currentPanel = this.accordionPos;
					}
				)
				.eq(0)
				.addClass(el.accordionCfg.activeClass)
				.end();
				jQuery(this)
					.css('height', jQuery(this).css('height'))
					.css('overflow', 'hidden');
			}
		);
	}
};

jQuery.fn.Accordion = jQuery.iAccordion.build;/**
 * Interface Elements for jQuery
 * 3D Carousel
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 */
/**
 * Created a 3D Carousel from a list of images, with reflections and animated by mouse position
 * 
 * @example window.onload = 
 *			function()
 *			{
 *				$('#carousel').Carousel(
 *					{
 *						itemWidth: 110,
 *						itemHeight: 62,
 *						itemMinWidth: 50,
 *						items: 'a',
 *						reflections: .5,
 *						rotationSpeed: 1.8
 *					}
 *				);
 *			}
 * HTML
 *			<div id="carousel">
 *				<a href="" title=""><img src="" width="100%" /></a>
 *				<a href="" title=""><img src="" width="100%" /></a>
 *				<a href="" title=""><img src="" width="100%" /></a>
 *				<a href="" title=""><img src="" width="100%" /></a>
 *				<a href="" title=""><img src="" width="100%" /></a>
 *			</div>
 * CSS
 *			#carousel
 *			{
 *				width: 700px;
 *				height: 150px;
 *				background-color: #111;
 *				position: absolute;
 *				top: 200px;
 *				left: 100px;
 *			}
 *			#carousel a
 *			{
 *				position: absolute;
 *				width: 110px;
 *			}
 *
 * @desc Creates a 3D carousel from all images inside div tag with id 'carousel'
 *
 *
 * @name 3D Carousel
 * @description Created a 3D Carousel from a list of images, with reflections and animated by mouse position
 * @param Hash hash A hash of parameters
 * @option String items items selection
 * @option Integer itemWidth the max width for each item
 * @option Integer itemHeight the max height for each item
 * @option Integer itemMinWidth the minimum width for each item, the height is automaticaly calculated to keep proportions
 * @option Float rotationSpeed the speed for rotation animation
 * @option Float reflectionSize the reflection size a fraction from items' height
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.iCarousel = {
	
	build : function(options)
	{
		return this.each(
			function()
			{
				var el = this;
				var increment = 2*Math.PI/360;
				var maxRotation = 2*Math.PI;
				if(jQuery(el).css('position') != 'relative' && jQuery(el).css('position') != 'absolute') {
					jQuery(el).css('position', 'relative');
				}
				el.carouselCfg = {
					items : jQuery(options.items, this),
					itemWidth : options.itemWidth,
					itemHeight : options.itemHeight,
					itemMinWidth : options.itemMinWidth,
					maxRotation : maxRotation,
					size : jQuery.iUtil.getSize(this),
					position : jQuery.iUtil.getPosition(this),
					start : Math.PI/2,
					rotationSpeed : options.rotationSpeed,
					reflectionSize : options.reflections,
					reflections : [],
					protectRotation : false,
					increment: 2*Math.PI/360
				};
				el.carouselCfg.radiusX = (el.carouselCfg.size.w - el.carouselCfg.itemWidth)/2;
				el.carouselCfg.radiusY =  (el.carouselCfg.size.h - el.carouselCfg.itemHeight - el.carouselCfg.itemHeight * el.carouselCfg.reflectionSize)/2;
				el.carouselCfg.step =  2*Math.PI/el.carouselCfg.items.size();
				el.carouselCfg.paddingX = el.carouselCfg.size.w/2;
				el.carouselCfg.paddingY = el.carouselCfg.size.h/2 - el.carouselCfg.itemHeight * el.carouselCfg.reflectionSize;
				var reflexions = document.createElement('div');
				jQuery(reflexions)
					.css(
						{
							position: 'absolute',
							zIndex: 1,
							top: 0,
							left: 0
						}
					);
				jQuery(el).append(reflexions);
				el.carouselCfg.items
					.each(
						function(nr)
						{
							image = jQuery('img', this).get(0);
							height = parseInt(el.carouselCfg.itemHeight*el.carouselCfg.reflectionSize);
							if (jQuery.browser.msie) {
								canvas = document.createElement('img');
								jQuery(canvas).css('position', 'absolute');
								canvas.src = image.src;				
								canvas.style.filter = 'flipv progid:DXImageTransform.Microsoft.Alpha(opacity=60, style=1, finishOpacity=0, startx=0, starty=0, finishx=0)';
					
							} else {
								canvas = document.createElement('canvas');
								if (canvas.getContext) {
									context = canvas.getContext("2d");
									canvas.style.position = 'absolute';
									canvas.style.height = height +'px';
									canvas.style.width = el.carouselCfg.itemWidth+'px';
									canvas.height = height;
									canvas.width = el.carouselCfg.itemWidth;
									context.save();
						
									context.translate(0,height);
									context.scale(1,-1);
									
									context.drawImage(
										image, 
										0, 
										0, 
										el.carouselCfg.itemWidth, 
										height
									);
					
									context.restore();
									
									context.globalCompositeOperation = "destination-out";
									var gradient = context.createLinearGradient(
										0, 
										0, 
										0, 
										height
									);
									
									gradient.addColorStop(1, "rgba(255, 255, 255, 1)");
									gradient.addColorStop(0, "rgba(255, 255, 255, 0.6)");
						
									context.fillStyle = gradient;
									if (navigator.appVersion.indexOf('WebKit') != -1) {
										context.fill();
									} else {
										context.fillRect(
											0, 
											0, 
											el.carouselCfg.itemWidth, 
											height
										);
									}
								}
							}
							
							el.carouselCfg.reflections[nr] = canvas;
							jQuery(reflexions).append(canvas);
						}
					)
					.bind(
						'mouseover',
						function(e)
						{
							el.carouselCfg.protectRotation = true;
							el.carouselCfg.speed = el.carouselCfg.increment*0.1 * el.carouselCfg.speed / Math.abs(el.carouselCfg.speed);
							return false;
						}
					)
					.bind(
						'mouseout',
						function(e)
						{
							el.carouselCfg.protectRotation = false;
							return false;
						}
					);
				jQuery.iCarousel.positionItems(el);
				el.carouselCfg.speed = el.carouselCfg.increment*0.2;
				el.carouselCfg.rotationTimer = window.setInterval(
					function()
					{
						el.carouselCfg.start += el.carouselCfg.speed;
						if (el.carouselCfg.start > maxRotation)
							el.carouselCfg.start = 0;
						jQuery.iCarousel.positionItems(el);
					},
					20
				);
				jQuery(el)
					.bind(
						'mouseout',
						function()
						{
							el.carouselCfg.speed = el.carouselCfg.increment*0.2 * el.carouselCfg.speed / Math.abs(el.carouselCfg.speed);
						}
					)
					.bind(
						'mousemove',
						function(e)
						{
							if (el.carouselCfg.protectRotation == false) {
								pointer = jQuery.iUtil.getPointer(e);
								mousex =  el.carouselCfg.size.w - pointer.x + el.carouselCfg.position.x;
								el.carouselCfg.speed = el.carouselCfg.rotationSpeed * el.carouselCfg.increment * (el.carouselCfg.size.w/2 - mousex) / (el.carouselCfg.size.w/2);
							}
						}
					);
			}
		);
	},

	positionItems : function(el)
	{
		el.carouselCfg.items.each(
			function (nr)
			{
				angle = el.carouselCfg.start+nr*el.carouselCfg.step;
				x = el.carouselCfg.radiusX*Math.cos(angle);
				y = el.carouselCfg.radiusY*Math.sin(angle) ;
				itemZIndex = parseInt(100*(el.carouselCfg.radiusY+y)/(2*el.carouselCfg.radiusY));
				parte = (el.carouselCfg.radiusY+y)/(2*el.carouselCfg.radiusY);
				
				width = parseInt((el.carouselCfg.itemWidth - el.carouselCfg.itemMinWidth) * parte + el.carouselCfg.itemMinWidth);
				height = parseInt(width * el.carouselCfg.itemHeight / el.carouselCfg.itemWidth);
				this.style.top = el.carouselCfg.paddingY + y - height/2 + "px";
	     		this.style.left = el.carouselCfg.paddingX + x - width/2 + "px";
	     		this.style.width = width + "px";
	     		this.style.height = height + "px";
	     		this.style.zIndex = itemZIndex;
				el.carouselCfg.reflections[nr].style.top = parseInt(el.carouselCfg.paddingY + y + height - 1 - height/2) + "px";
				el.carouselCfg.reflections[nr].style.left = parseInt(el.carouselCfg.paddingX + x - width/2) + "px";
				el.carouselCfg.reflections[nr].style.width = width + "px";
				el.carouselCfg.reflections[nr].style.height = parseInt(height * el.carouselCfg.reflectionSize) + "px";
			}
		);
	}
};
jQuery.fn.Carousel = jQuery.iCarousel.build;/**
 * Interface Elements for jQuery
 * Easing formulas
 *
 * http://interface.eyecon.ro
 *
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt)
 * and GPL (GPL-LICENSE.txt) licenses.
 */
 
/**
 * Starting with jQuery 1.1  the fx function accepts easing formulas that can be used with .animation() and most of FX plugins from Interface. The object can be extended to accept new easing formulas
 */
 
 jQuery.extend({	
	/**
	 *
	 * @param Integer p period step in animation
	 * @param Integer n current time
	 * @param Mixed firstNum begin value
	 * @param Mixed delta change in
	 * @param Integer duration duration
	 */
	easing :  {
		linear: function(p, n, firstNum, delta, duration) {
			return ((-Math.cos(p*Math.PI)/2) + 0.5) * delta + firstNum;
		},
		
		easein: function(p, n, firstNum, delta, duration) {
			return delta*(n/=duration)*n*n + firstNum;
		},
		
		easeout: function(p, n, firstNum, delta, duration) {
			return -delta * ((n=n/duration-1)*n*n*n - 1) + firstNum;
		},
		
		easeboth: function(p, n, firstNum, delta, duration) {
			if ((n/=duration/2) < 1)
				return delta/2*n*n*n*n + firstNum;
				return -delta/2 * ((n-=2)*n*n*n - 2) + firstNum;
		},
		
		bounceout: function(p, n, firstNum, delta, duration) {
			if ((n/=duration) < (1/2.75)) {
				return delta*(7.5625*n*n) + firstNum;
			} else if (n < (2/2.75)) {
				return delta*(7.5625*(n-=(1.5/2.75))*n + .75) + firstNum;
			} else if (n < (2.5/2.75)) {
				return delta*(7.5625*(n-=(2.25/2.75))*n + .9375) + firstNum;
			} else {
				return delta*(7.5625*(n-=(2.625/2.75))*n + .984375) + firstNum;
			}
		},
		
		bouncein: function(p, n, firstNum, delta, duration) {
			if (jQuery.easing.bounceout)
				return delta - jQuery.easing.bounceout (p, duration - n, 0, delta, duration) + firstNum;
			return firstNum + delta;
		},
		
		bounceboth: function(p, n, firstNum, delta, duration) {
			if (jQuery.easing.bouncein && jQuery.easing.bounceout)
				if (n < duration/2)
					return jQuery.easing.bouncein(p, n*2, 0, delta, duration) * .5 + firstNum;
				return jQuery.easing.bounceout(p, n*2-duration, 0, delta, duration) * .5 + delta*.5 + firstNum; 
			return firstNum + delta;
		},
		
		elasticin: function(p, n, firstNum, delta, duration) {
			var a, s;
   			if (n == 0)
   				return firstNum;
   			if ((n/=duration)==1)
   				return firstNum+delta;
   			a = delta * 0.3;
   			p=duration*.3;
			if (a < Math.abs(delta)) {
				a=delta;
				s=p/4;
			} else { 
				s = p/(2*Math.PI) * Math.asin (delta/a);
			}
			return -(a*Math.pow(2,10*(n-=1)) * Math.sin( (n*duration-s)*(2*Math.PI)/p )) + firstNum; 
		},
		
		elasticout:function(p, n, firstNum, delta, duration) {
			var a, s;
			if (n==0)
				return firstNum;
			if ((n/=duration/2)==2)
				return firstNum + delta;
   			a = delta * 0.3;
   			p=duration*.3;
			if (a < Math.abs(delta)){
				a = delta;
				s=p/4;
			} else { 
				s = p/(2*Math.PI) * Math.asin (delta/a);
			}
			return a*Math.pow(2,-10*n) * Math.sin( (n*duration-s)*(2*Math.PI)/p ) + delta + firstNum;
		},
		
		elasticboth: function(p, n, firstNum, delta, duration) {
			var a, s;
			if (n==0)
				return firstNum;
			if ((n/=duration/2)==2)
				return firstNum + delta;
   			a = delta * 0.3;
   			p=duration*.3;
			if (a < Math.abs(delta)){
				a = delta;
				s=p/4;
			} else { 
				s = p/(2*Math.PI) * Math.asin (delta/a);
			}
			if (n < 1) {
				return -.5*(a*Math.pow(2,10*(n-=1)) * Math.sin( (n*duration-s)*(2*Math.PI)/p )) + firstNum;
			}
			return a*Math.pow(2,-10*(n-=1)) * Math.sin( (n*duration-s)*(2*Math.PI)/p )*.5 + delta + firstNum; 
		}
	}
});/**
 * Interface Elements for jQuery
 * Fisheye menu
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 */

/**
 * Build a Fisheye menu from a list of links
 *
 * @name Fisheye
 * @description Build a Fisheye menu from a list of links
 * @param Hash hash A hash of parameters
 * @option String items items selection
 * @option String container container element
 * @option Integer itemWidth the minimum width for each item
 * @option Integer maxWidth the maximum width for each item
 * @option String itemsText selection of element that contains the text for each item
 * @option Integer proximity the distance from element that make item to interact
 * @option String valign vertical alignment
 * @option String halign horizontal alignment
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.iFisheye = {
	
	build : function(options)
	{
	
		return this.each(
			function()
			{
				var el = this;
				el.fisheyeCfg = {
					items : jQuery(options.items, this),
					container: jQuery(options.container, this),
					pos : jQuery.iUtil.getPosition(this),
					itemWidth: options.itemWidth,
					itemsText: options.itemsText,
					proximity: options.proximity,
					valign: options.valign,
					halign: options.halign,
					maxWidth : options.maxWidth
				};
				jQuery.iFisheye.positionContainer(el, 0);
				jQuery(window).bind(
					'resize',
					function()
					{
						el.fisheyeCfg.pos = jQuery.iUtil.getPosition(el);
						jQuery.iFisheye.positionContainer(el, 0);
						jQuery.iFisheye.positionItems(el);
					}
				);
				jQuery.iFisheye.positionItems(el);
				el.fisheyeCfg.items
					.bind(
						'mouseover',
						function()
						{
							jQuery(el.fisheyeCfg.itemsText, this).get(0).style.display = 'block';
						}
					)
					.bind(
						'mouseout',
						function()
						{
							jQuery(el.fisheyeCfg.itemsText, this).get(0).style.display = 'none';
						}
					);
				jQuery(document).bind(
					'mousemove',
					function(e)
					{
						var pointer = jQuery.iUtil.getPointer(e);
						var toAdd = 0;
						if (el.fisheyeCfg.halign && el.fisheyeCfg.halign == 'center')
							var posx = pointer.x - el.fisheyeCfg.pos.x - (el.offsetWidth - el.fisheyeCfg.itemWidth * el.fisheyeCfg.items.size())/2 - el.fisheyeCfg.itemWidth/2;
						else if (el.fisheyeCfg.halign && el.fisheyeCfg.halign == 'right')
							var posx = pointer.x - el.fisheyeCfg.pos.x - el.offsetWidth + el.fisheyeCfg.itemWidth * el.fisheyeCfg.items.size();
						else 
							var posx = pointer.x - el.fisheyeCfg.pos.x;
						var posy = Math.pow(pointer.y - el.fisheyeCfg.pos.y - el.offsetHeight/2,2);
						el.fisheyeCfg.items.each(
							function(nr)
							{
								distance = Math.sqrt(
									Math.pow(posx - nr*el.fisheyeCfg.itemWidth, 2)
									+ posy
								);
								distance -= el.fisheyeCfg.itemWidth/2;
								
								distance = distance < 0 ? 0 : distance;
								distance = distance > el.fisheyeCfg.proximity ? el.fisheyeCfg.proximity : distance;
								distance = el.fisheyeCfg.proximity - distance;
								
								extraWidth = el.fisheyeCfg.maxWidth * distance/el.fisheyeCfg.proximity;
								
								this.style.width = el.fisheyeCfg.itemWidth + extraWidth + 'px';
								this.style.left = el.fisheyeCfg.itemWidth * nr + toAdd + 'px';
								toAdd += extraWidth;
							}
						);
						jQuery.iFisheye.positionContainer(el, toAdd);
					}
				);
			}
		)
	},
	
	positionContainer : function(el, toAdd)
	{
		if (el.fisheyeCfg.halign)
			if (el.fisheyeCfg.halign == 'center')
				el.fisheyeCfg.container.get(0).style.left = (el.offsetWidth - el.fisheyeCfg.itemWidth * el.fisheyeCfg.items.size())/2 - toAdd/2 + 'px';
			else if (el.fisheyeCfg.halign == 'left')
				el.fisheyeCfg.container.get(0).style.left =  - toAdd/el.fisheyeCfg.items.size() + 'px';
			else if (el.fisheyeCfg.halign == 'right')
				el.fisheyeCfg.container.get(0).style.left =  (el.offsetWidth - el.fisheyeCfg.itemWidth * el.fisheyeCfg.items.size()) - toAdd/2 + 'px';
		el.fisheyeCfg.container.get(0).style.width = el.fisheyeCfg.itemWidth * el.fisheyeCfg.items.size() + toAdd + 'px';
	},
	
	positionItems : function(el)
	{
		el.fisheyeCfg.items.each(
			function(nr)
			{
				this.style.width = el.fisheyeCfg.itemWidth + 'px';
				this.style.left = el.fisheyeCfg.itemWidth * nr + 'px';
			}
		);
	}
};

jQuery.fn.Fisheye = jQuery.iFisheye.build;/**
 * Interface Elements for jQuery
 * Autocompleter
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *  
 */

/**
 * Attach AJAX driven autocomplete/sugestion box to text input fields.
 *
 * 
 * 
 * @name Autocomplete
 * @description Attach AJAX driven autocomplete/sugestion box to text input fields.
 * @param Hash hash A hash of parameters
 * @option String source the URL to request
 * @option Integer delay (optional) the delayed time to start the AJAX request
 * @option Boolean autofill (optional) when true the first sugested value fills the input
 * @option String helperClass (optional) the CSS class applied to sugestion box
 * @option String selectClass (optional) the CSS class applied to selected/hovered item
 * @option Integer minchars (optional) the number of characters needed before starting AJAX request
 * @option Hash fx (optional) {type:[slide|blind|fade]; duration: integer} the fx type to apply to sugestion box and duration for that fx
 * @option Function onSelect (optional) A function to be executed whenever an item it is selected
 * @option Function onShow (optional) A function to be executed whenever the suggection box is displayed
 * @option Function onHide (optional) A function to be executed whenever the suggection box is hidden
 * @option Function onHighlight (optional) A function to be executed whenever an item it is highlighted
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
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
		window.clearTimeout(jQuery.iAuto.timer);
	},

	update : function ()
	{
		var subject = jQuery.iAuto.subject;
		var subjectValue = jQuery.iAuto.getFieldValues(subject);
		//var selectionStart = jQuery.iAuto.getSelectionStart(subject);
		if (subject && subjectValue.item != jQuery.iAuto.lastValue && subjectValue.item.length >= subject.autoCFG.minchars) {
			jQuery.iAuto.lastValue = subjectValue.item;
			jQuery.iAuto.currentValue = subjectValue.item;

			data = {
				field: jQuery(subject).attr('name')||'field',
				value: subjectValue.item
			};

			jQuery.ajax(
				{
					type: 'POST',
					data: jQuery.param(data),
					success: function(xml)
					{
						subject.autoCFG.lastSuggestion = jQuery('item',xml);
						size = subject.autoCFG.lastSuggestion.size();
						if (size > 0) {
							var toWrite = '';
							subject.autoCFG.lastSuggestion.each(
								function(nr)
								{
									toWrite += '<li rel="' + jQuery('value', this).text() + '" dir="' + nr + '" style="cursor: default;">' + jQuery('text', this).text() + '</li>';
								}
							);
							if (subject.autoCFG.autofill) {
								var valueToAdd = jQuery('value', subject.autoCFG.lastSuggestion.get(0)).text();
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
					},
					url : subject.autoCFG.source
				}
			);
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
		jQuery.iAuto.applyOn(subject,subject.autoCFG.lastSuggestion.get(0), 'onHighlight');
		
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
			
			var toWrite = '';
			subject.autoCFG.lastSuggestion.each(
				function(nr)
				{
					value = jQuery('value', this).text().toLowerCase();
					inputValue = subject.value.toLowerCase();
					if (value.indexOf(inputValue) == 0) {
						toWrite += '<li rel="' + jQuery('value', this).text() + '" dir="' + nr + '" style="cursor: default;">' + jQuery('text', this).text() + '</li>';
					}
				}
			);
			
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
						jQuery.iAuto.applyOn(this,this.autoCFG.lastSuggestion.get(iteration), 'onSelect');
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
			jQuery.iAuto.applyOn(this,this.autoCFG.lastSuggestion.get(jQuery.iAuto.selectedItem||0), 'onHighlight');
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
		if (field.autoCFG[type]) {
			var data = {};
			childs = item.getElementsByTagName('*');
			for(i=0; i<childs.length; i++){
				data[childs[i].tagName] = childs[i].firstChild.nodeValue;
			}
			field.autoCFG[type].apply(field,[data]);
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
			jQuery.iAuto.applyOn(jQuery.iAuto.subject,jQuery.iAuto.subject.autoCFG.lastSuggestion.get(iteration), 'onSelect');
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
jQuery.fn.Autocomplete = jQuery.iAuto.build;/**
 * Interface Elements for jQuery
 * Autoscroller
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Utility object that helps to make custom autoscrollers.
 * 
 * @example
 *		$('div.dragMe').Draggable(
 *			{
 *				onStart : function()
 *				{
 *					$.iAutoscroller.start(this, document.getElementsByTagName('body'));
 *				},
 *				onStop : function()
 *				{
 *					$.iAutoscroller.stop();
 *				}
 *			}
 *		);
 *
 * @description Utility object that helps to make custom autoscrollers
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */

jQuery.iAutoscroller = {
	timer: null,
	elToScroll: null,
	elsToScroll: null,
	step: 10,
	/**
	 * This is called to start autoscrolling
	 * @param DOMElement el the element used as reference
	 * @param Array els collection of elements to scroll
	 * @param Integer step the pixels scroll on each step
	 * @param Integer interval miliseconds between each step
	 */
	start: function(el, els, step, interval)
	{
		jQuery.iAutoscroller.elToScroll = el;
		jQuery.iAutoscroller.elsToScroll = els;
		jQuery.iAutoscroller.step = parseInt(step)||10;
		jQuery.iAutoscroller.timer = window.setInterval(jQuery.iAutoscroller.doScroll, parseInt(interval)||40);
	},
	
	//private function
	doScroll : function()
	{
		for (i=0;i<jQuery.iAutoscroller.elsToScroll.length; i++) {
				if(!jQuery.iAutoscroller.elsToScroll[i].parentData) {
					jQuery.iAutoscroller.elsToScroll[i].parentData = jQuery.extend(
						jQuery.iUtil.getPositionLite(jQuery.iAutoscroller.elsToScroll[i]),
						jQuery.iUtil.getSizeLite(jQuery.iAutoscroller.elsToScroll[i]),
						jQuery.iUtil.getScroll(jQuery.iAutoscroller.elsToScroll[i])
					);
				} else {
					jQuery.iAutoscroller.elsToScroll[i].parentData.t = jQuery.iAutoscroller.elsToScroll[i].scrollTop;
					jQuery.iAutoscroller.elsToScroll[i].parentData.l = jQuery.iAutoscroller.elsToScroll[i].scrollLeft;
				}
				
				if (jQuery.iAutoscroller.elToScroll.dragCfg && jQuery.iAutoscroller.elToScroll.dragCfg.init == true) {
					elementData = {
						x : jQuery.iAutoscroller.elToScroll.dragCfg.nx,
						y : jQuery.iAutoscroller.elToScroll.dragCfg.ny,
						wb : jQuery.iAutoscroller.elToScroll.dragCfg.oC.wb,
						hb : jQuery.iAutoscroller.elToScroll.dragCfg.oC.hb
					};
				} else {
					elementData = jQuery.extend(
						jQuery.iUtil.getPositionLite(jQuery.iAutoscroller.elToScroll),
						jQuery.iUtil.getSizeLite(jQuery.iAutoscroller.elToScroll)
					);
				}
				if (
					jQuery.iAutoscroller.elsToScroll[i].parentData.t > 0
					 && 
					jQuery.iAutoscroller.elsToScroll[i].parentData.y + jQuery.iAutoscroller.elsToScroll[i].parentData.t > elementData.y) {
					jQuery.iAutoscroller.elsToScroll[i].scrollTop -= jQuery.iAutoscroller.step;
				} else if (jQuery.iAutoscroller.elsToScroll[i].parentData.t <= jQuery.iAutoscroller.elsToScroll[i].parentData.h && jQuery.iAutoscroller.elsToScroll[i].parentData.t + jQuery.iAutoscroller.elsToScroll[i].parentData.hb < elementData.y + elementData.hb) {
					jQuery.iAutoscroller.elsToScroll[i].scrollTop += jQuery.iAutoscroller.step;
				}
				if (jQuery.iAutoscroller.elsToScroll[i].parentData.l > 0 && jQuery.iAutoscroller.elsToScroll[i].parentData.x + jQuery.iAutoscroller.elsToScroll[i].parentData.l > elementData.x) {
					jQuery.iAutoscroller.elsToScroll[i].scrollLeft -= jQuery.iAutoscroller.step;
				} else if (jQuery.iAutoscroller.elsToScroll[i].parentData.l <= jQuery.iAutoscroller.elsToScroll[i].parentData.wh && jQuery.iAutoscroller.elsToScroll[i].parentData.l + jQuery.iAutoscroller.elsToScroll[i].parentData.wb < elementData.x + elementData.wb) {
					jQuery.iAutoscroller.elsToScroll[i].scrollLeft += jQuery.iAutoscroller.step;
				}
		}
	},
	/**
	 * This is called to stop autoscrolling
	 */
	stop: function()
	{
		window.clearInterval(jQuery.iAutoscroller.timer);
		jQuery.iAutoscroller.elToScroll = null;
		jQuery.iAutoscroller.elsToScroll = null;
		for (i in jQuery.iAutoscroller.elsToScroll) {
			jQuery.iAutoscroller.elsToScroll[i].parentData = null;
		}
	}
};/**
 * Interface Elements for jQuery
 * Draggable
 *
 * http://interface.eyecon.ro
 *
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt)
 * and GPL (GPL-LICENSE.txt) licenses.
 */
 
/**
 * Create a draggable element with a number of advanced options including callback, Google Maps type draggables,
 * reversion, ghosting, and grid dragging.
 * 
 * @name Draggable
 * @descr Creates draggable elements that can be moved across the page.
 * @param Hash hash A hash of parameters. All parameters are optional.
 * @option String handle (optional) The jQuery selector matching the handle that starts the draggable
 * @option DOMElement handle (optional) The DOM Element of the handle that starts the draggable
 * @option Boolean revert (optional) When true, on stop-drag the element returns to initial position
 * @option Boolean ghosting (optional) When true, a copy of the element is moved
 * @option Integer zIndex (optional) zIndex depth for the element while it is being dragged
 * @option Float opacity (optional) A number between 0 and 1 that indicates the opacity of the element while being dragged
 * @option Integer grid (optional) (optional) A number of pixels indicating the grid that the element should snap to
 * @option Array grid (optional) A number of x-pixels and y-pixels indicating the grid that the element should snap to
 * @option Integer fx (optional) Duration for the effect (like ghosting or revert) applied to the draggable
 * @option String containment (optional) Define the zone where the draggable can be moved. 'parent' moves it inside parent
 *                           element, while 'document' prevents it from leaving the document and forcing additional
 *                           scrolling
 * @option Array containment An 4-element array (left, top, width, height) indicating the containment of the element
 * @option String axis (optional) Set an axis: vertical (with 'vertically') or horizontal (with 'horizontally')
 * @option Function onStart (optional) Callback function triggered when the dragging starts
 * @option Function onStop (optional) Callback function triggered when the dragging stops
 * @option Function onChange (optional) Callback function triggered when the dragging stop *and* the element was moved at least
 *                          one pixel
 * @option Function onDrag (optional) Callback function triggered while the element is dragged. Receives two parameters: x and y
 *                        coordinates. You can return an object with new coordinates {x: x, y: y} so this way you can
 *                        interact with the dragging process (for instance, build your containment)
 * @option Boolean insideParent Forces the element to remain inside its parent when being dragged (like Google Maps)
 * @option Integer snapDistance (optional) The element is not moved unless it is dragged more than snapDistance. You can prevent
 *                             accidental dragging and keep regular clicking enabled (for links or form elements, 
 *                             for instance)
 * @option Object cursorAt (optional) The dragged element is moved to the cursor position with the offset specified. Accepts value
 *                        for top, left, right and bottom offset. Basically, this forces the cursor to a particular
 *                        position during the entire drag operation.
 * @option Boolean autoSize (optional) When true, the drag helper is resized to its content, instead of the dragged element's sizes
 * @option String frameClass (optional) When is set the cloned element is hidden so only a frame is dragged
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */

jQuery.iDrag =	{
	helper : null,
	dragged: null,
	destroy : function()
	{
		return this.each(
			function ()
			{
				if (this.isDraggable) {
					this.dragCfg.dhe.unbind('mousedown', jQuery.iDrag.draginit);
					this.dragCfg = null;
					this.isDraggable = false;
					if(jQuery.browser.msie) {
						this.unselectable = "off";
					} else {
						this.style.MozUserSelect = '';
						this.style.KhtmlUserSelect = '';
						this.style.userSelect = '';
					}
				}
			}
		);
	},
	draginit : function (e)
	{
		if (jQuery.iDrag.dragged != null) {
			jQuery.iDrag.dragstop(e);
			return false;
		}
		var elm = this.dragElem;
		jQuery(document)
			.bind('mousemove', jQuery.iDrag.dragmove)
			.bind('mouseup', jQuery.iDrag.dragstop);
		elm.dragCfg.pointer = jQuery.iUtil.getPointer(e);
		elm.dragCfg.currentPointer = elm.dragCfg.pointer;
		elm.dragCfg.init = false;
		elm.dragCfg.fromHandler = this != this.dragElem;
		jQuery.iDrag.dragged = elm;
		if (elm.dragCfg.si && this != this.dragElem) {
				parentPos = jQuery.iUtil.getPosition(elm.parentNode);
				sliderSize = jQuery.iUtil.getSize(elm);
				sliderPos = {
					x : parseInt(jQuery.css(elm,'left')) || 0,
					y : parseInt(jQuery.css(elm,'top')) || 0
				};
				dx = elm.dragCfg.currentPointer.x - parentPos.x - sliderSize.wb/2 - sliderPos.x;
				dy = elm.dragCfg.currentPointer.y - parentPos.y - sliderSize.hb/2 - sliderPos.y;
				jQuery.iSlider.dragmoveBy(elm, [dx, dy]);
		}
		return jQuery.selectKeyHelper||false;
	},

	dragstart : function(e)
	{
		var elm = jQuery.iDrag.dragged;
		elm.dragCfg.init = true;

		var dEs = elm.style;

		elm.dragCfg.oD = jQuery.css(elm,'display');
		elm.dragCfg.oP = jQuery.css(elm,'position');
		if (!elm.dragCfg.initialPosition)
			elm.dragCfg.initialPosition = elm.dragCfg.oP;

		elm.dragCfg.oR = {
			x : parseInt(jQuery.css(elm,'left')) || 0,
			y : parseInt(jQuery.css(elm,'top')) || 0
		};
		elm.dragCfg.diffX = 0;
		elm.dragCfg.diffY = 0;
		if (jQuery.browser.msie) {
			var oldBorder = jQuery.iUtil.getBorder(elm, true);
			elm.dragCfg.diffX = oldBorder.l||0;
			elm.dragCfg.diffY = oldBorder.t||0;
		}

		elm.dragCfg.oC = jQuery.extend(
			jQuery.iUtil.getPosition(elm),
			jQuery.iUtil.getSize(elm)
		);
		if (elm.dragCfg.oP != 'relative' && elm.dragCfg.oP != 'absolute') {
			dEs.position = 'relative';
		}

		jQuery.iDrag.helper.empty();
		var clonedEl = elm.cloneNode(true);
		
		jQuery(clonedEl).css(
			{
				display:	'block',
				left:		'0px',
				top: 		'0px'
			}
		);
		clonedEl.style.marginTop = '0';
		clonedEl.style.marginRight = '0';
		clonedEl.style.marginBottom = '0';
		clonedEl.style.marginLeft = '0';
		jQuery.iDrag.helper.append(clonedEl);
		
		var dhs = jQuery.iDrag.helper.get(0).style;

		if (elm.dragCfg.autoSize) {
			dhs.width = 'auto';
			dhs.height = 'auto';
		} else {
			dhs.height = elm.dragCfg.oC.hb + 'px';
			dhs.width = elm.dragCfg.oC.wb + 'px';
		}

		dhs.display = 'block';
		dhs.marginTop = '0px';
		dhs.marginRight = '0px';
		dhs.marginBottom = '0px';
		dhs.marginLeft = '0px';

		//remeasure the clone to check if the size was changed by user's functions
		jQuery.extend(
			elm.dragCfg.oC,
			jQuery.iUtil.getSize(clonedEl)
		);

		if (elm.dragCfg.cursorAt) {
			if (elm.dragCfg.cursorAt.left) {
				elm.dragCfg.oR.x += elm.dragCfg.pointer.x - elm.dragCfg.oC.x - elm.dragCfg.cursorAt.left;
				elm.dragCfg.oC.x = elm.dragCfg.pointer.x - elm.dragCfg.cursorAt.left;
			}
			if (elm.dragCfg.cursorAt.top) {
				elm.dragCfg.oR.y += elm.dragCfg.pointer.y - elm.dragCfg.oC.y - elm.dragCfg.cursorAt.top;
				elm.dragCfg.oC.y = elm.dragCfg.pointer.y - elm.dragCfg.cursorAt.top;
			}
			if (elm.dragCfg.cursorAt.right) {
				elm.dragCfg.oR.x += elm.dragCfg.pointer.x - elm.dragCfg.oC.x -elm.dragCfg.oC.hb + elm.dragCfg.cursorAt.right;
				elm.dragCfg.oC.x = elm.dragCfg.pointer.x - elm.dragCfg.oC.wb + elm.dragCfg.cursorAt.right;
			}
			if (elm.dragCfg.cursorAt.bottom) {
				elm.dragCfg.oR.y += elm.dragCfg.pointer.y - elm.dragCfg.oC.y - elm.dragCfg.oC.hb + elm.dragCfg.cursorAt.bottom;
				elm.dragCfg.oC.y = elm.dragCfg.pointer.y - elm.dragCfg.oC.hb + elm.dragCfg.cursorAt.bottom;
			}
		}
		elm.dragCfg.nx = elm.dragCfg.oR.x;
		elm.dragCfg.ny = elm.dragCfg.oR.y;

		if (elm.dragCfg.insideParent || elm.dragCfg.containment == 'parent') {
			parentBorders = jQuery.iUtil.getBorder(elm.parentNode, true);
			elm.dragCfg.oC.x = elm.offsetLeft + (jQuery.browser.msie ? 0 : jQuery.browser.opera ? -parentBorders.l : parentBorders.l);
			elm.dragCfg.oC.y = elm.offsetTop + (jQuery.browser.msie ? 0 : jQuery.browser.opera ? -parentBorders.t : parentBorders.t);
			jQuery(elm.parentNode).append(jQuery.iDrag.helper.get(0));
		}
		if (elm.dragCfg.containment) {
			jQuery.iDrag.getContainment(elm);
			elm.dragCfg.onDragModifier.containment = jQuery.iDrag.fitToContainer;
		}

		if (elm.dragCfg.si) {
			jQuery.iSlider.modifyContainer(elm);
		}

		dhs.left = elm.dragCfg.oC.x - elm.dragCfg.diffX + 'px';
		dhs.top = elm.dragCfg.oC.y - elm.dragCfg.diffY + 'px';
		//resize the helper to fit the clone
		dhs.width = elm.dragCfg.oC.wb + 'px';
		dhs.height = elm.dragCfg.oC.hb + 'px';

		jQuery.iDrag.dragged.dragCfg.prot = false;

		if (elm.dragCfg.gx) {
			elm.dragCfg.onDragModifier.grid = jQuery.iDrag.snapToGrid;
		}
		if (elm.dragCfg.zIndex != false) {
			jQuery.iDrag.helper.css('zIndex', elm.dragCfg.zIndex);
		}
		if (elm.dragCfg.opacity) {
			jQuery.iDrag.helper.css('opacity', elm.dragCfg.opacity);
			if (window.ActiveXObject) {
				jQuery.iDrag.helper.css('filter', 'alpha(opacity=' + elm.dragCfg.opacity * 100 + ')');
			}
		}

		if(elm.dragCfg.frameClass) {
			jQuery.iDrag.helper.addClass(elm.dragCfg.frameClass);
			jQuery.iDrag.helper.get(0).firstChild.style.display = 'none';
		}
		if (elm.dragCfg.onStart)
			elm.dragCfg.onStart.apply(elm, [clonedEl, elm.dragCfg.oR.x, elm.dragCfg.oR.y]);
		if (jQuery.iDrop && jQuery.iDrop.count > 0 ){
			jQuery.iDrop.highlight(elm);
		}
		if (elm.dragCfg.ghosting == false) {
			dEs.display = 'none';
		}
		return false;
	},

	getContainment : function(elm)
	{
		if (elm.dragCfg.containment.constructor == String) {
			if (elm.dragCfg.containment == 'parent') {
				elm.dragCfg.cont = jQuery.extend(
					{x:0,y:0},
					jQuery.iUtil.getSize(elm.parentNode)
				);
				var contBorders = jQuery.iUtil.getBorder(elm.parentNode, true);
				elm.dragCfg.cont.w = elm.dragCfg.cont.wb - contBorders.l - contBorders.r;
				elm.dragCfg.cont.h = elm.dragCfg.cont.hb - contBorders.t - contBorders.b;
			} else if (elm.dragCfg.containment == 'document') {
				var clnt = jQuery.iUtil.getClient();
				elm.dragCfg.cont = {
					x : 0,
					y : 0,
					w : clnt.w,
					h : clnt.h
				};
			}
		} else if (elm.dragCfg.containment.constructor == Array) {
			elm.dragCfg.cont = {
				x : parseInt(elm.dragCfg.containment[0])||0,
				y : parseInt(elm.dragCfg.containment[1])||0,
				w : parseInt(elm.dragCfg.containment[2])||0,
				h : parseInt(elm.dragCfg.containment[3])||0
			};
		}
		elm.dragCfg.cont.dx = elm.dragCfg.cont.x - elm.dragCfg.oC.x;
		elm.dragCfg.cont.dy = elm.dragCfg.cont.y - elm.dragCfg.oC.y;
	},

	hidehelper : function(dragged)
	{
		if (dragged.dragCfg.insideParent || dragged.dragCfg.containment == 'parent') {
			jQuery('body', document).append(jQuery.iDrag.helper.get(0));
		}
		jQuery.iDrag.helper.empty().hide().css('opacity', 1);
		if (window.ActiveXObject) {
			jQuery.iDrag.helper.css('filter', 'alpha(opacity=100)');
		}
	},

	dragstop : function(e)
	{

		jQuery(document)
			.unbind('mousemove', jQuery.iDrag.dragmove)
			.unbind('mouseup', jQuery.iDrag.dragstop);

		if (jQuery.iDrag.dragged == null) {
			return;
		}
		var dragged = jQuery.iDrag.dragged;

		jQuery.iDrag.dragged = null;

		if (dragged.dragCfg.init == false) {
			return false;
		}
		if (dragged.dragCfg.so == true) {
			jQuery(dragged).css('position', dragged.dragCfg.oP);
		}
		var dEs = dragged.style;

		if (dragged.si) {
			jQuery.iDrag.helper.css('cursor', 'move');
		}
		if(dragged.dragCfg.frameClass) {
			jQuery.iDrag.helper.removeClass(dragged.dragCfg.frameClass);
		}

		if (dragged.dragCfg.revert == false) {
			if (dragged.dragCfg.fx > 0) {
				if (!dragged.dragCfg.axis || dragged.dragCfg.axis == 'horizontally') {
					var x = new jQuery.fx(dragged,{duration:dragged.dragCfg.fx}, 'left');
					x.custom(dragged.dragCfg.oR.x,dragged.dragCfg.nRx);
				}
				if (!dragged.dragCfg.axis || dragged.dragCfg.axis == 'vertically') {
					var y = new jQuery.fx(dragged,{duration:dragged.dragCfg.fx}, 'top');
					y.custom(dragged.dragCfg.oR.y,dragged.dragCfg.nRy);
				}
			} else {
				if (!dragged.dragCfg.axis || dragged.dragCfg.axis == 'horizontally')
					dragged.style.left = dragged.dragCfg.nRx + 'px';
				if (!dragged.dragCfg.axis || dragged.dragCfg.axis == 'vertically')
					dragged.style.top = dragged.dragCfg.nRy + 'px';
			}
			jQuery.iDrag.hidehelper(dragged);
			if (dragged.dragCfg.ghosting == false) {
				jQuery(dragged).css('display', dragged.dragCfg.oD);
			}
		} else if (dragged.dragCfg.fx > 0) {
			dragged.dragCfg.prot = true;
			var dh = false;
			if(jQuery.iDrop && jQuery.iSort && dragged.dragCfg.so) {
				dh = jQuery.iUtil.getPosition(jQuery.iSort.helper.get(0));
			}
			jQuery.iDrag.helper.animate(
				{
					left : dh ? dh.x : dragged.dragCfg.oC.x,
					top : dh ? dh.y : dragged.dragCfg.oC.y
				},
				dragged.dragCfg.fx,
				function()
				{
					dragged.dragCfg.prot = false;
					if (dragged.dragCfg.ghosting == false) {
						dragged.style.display = dragged.dragCfg.oD;
					}
					jQuery.iDrag.hidehelper(dragged);
				}
			);
		} else {
			jQuery.iDrag.hidehelper(dragged);
			if (dragged.dragCfg.ghosting == false) {
				jQuery(dragged).css('display', dragged.dragCfg.oD);
			}
		}

		if (jQuery.iDrop && jQuery.iDrop.count > 0 ){
			jQuery.iDrop.checkdrop(dragged);
		}
		if (jQuery.iSort && dragged.dragCfg.so) {
			jQuery.iSort.check(dragged);
		}
		if (dragged.dragCfg.onChange && (dragged.dragCfg.nRx != dragged.dragCfg.oR.x || dragged.dragCfg.nRy != dragged.dragCfg.oR.y)){
			dragged.dragCfg.onChange.apply(dragged, dragged.dragCfg.lastSi||[0,0,dragged.dragCfg.nRx,dragged.dragCfg.nRy]);
		}
		if (dragged.dragCfg.onStop)
			dragged.dragCfg.onStop.apply(dragged);
		return false;
	},

	snapToGrid : function(x, y, dx, dy)
	{
		if (dx != 0)
			dx = parseInt((dx + (this.dragCfg.gx * dx/Math.abs(dx))/2)/this.dragCfg.gx) * this.dragCfg.gx;
		if (dy != 0)
			dy = parseInt((dy + (this.dragCfg.gy * dy/Math.abs(dy))/2)/this.dragCfg.gy) * this.dragCfg.gy;
		return {
			dx : dx,
			dy : dy,
			x: 0,
			y: 0
		};
	},

	fitToContainer : function(x, y, dx, dy)
	{
		dx = Math.min(
				Math.max(dx,this.dragCfg.cont.dx),
				this.dragCfg.cont.w + this.dragCfg.cont.dx - this.dragCfg.oC.wb
			);
		dy = Math.min(
				Math.max(dy,this.dragCfg.cont.dy),
				this.dragCfg.cont.h + this.dragCfg.cont.dy - this.dragCfg.oC.hb
			);

		return {
			dx : dx,
			dy : dy,
			x: 0,
			y: 0
		}
	},

	dragmove : function(e)
	{
		if (jQuery.iDrag.dragged == null || jQuery.iDrag.dragged.dragCfg.prot == true) {
			return;
		}

		var dragged = jQuery.iDrag.dragged;

		dragged.dragCfg.currentPointer = jQuery.iUtil.getPointer(e);
		if (dragged.dragCfg.init == false) {
			distance = Math.sqrt(Math.pow(dragged.dragCfg.pointer.x - dragged.dragCfg.currentPointer.x, 2) + Math.pow(dragged.dragCfg.pointer.y - dragged.dragCfg.currentPointer.y, 2));
			if (distance < dragged.dragCfg.snapDistance){
				return;
			} else {
				jQuery.iDrag.dragstart(e);
			}
		}

		var dx = dragged.dragCfg.currentPointer.x - dragged.dragCfg.pointer.x;
		var dy = dragged.dragCfg.currentPointer.y - dragged.dragCfg.pointer.y;

		for (var i in dragged.dragCfg.onDragModifier) {
			var newCoords = dragged.dragCfg.onDragModifier[i].apply(dragged, [dragged.dragCfg.oR.x + dx, dragged.dragCfg.oR.y + dy, dx, dy]);
			if (newCoords && newCoords.constructor == Object) {
				dx = i != 'user' ? newCoords.dx : (newCoords.x - dragged.dragCfg.oR.x);
				dy = i != 'user' ? newCoords.dy : (newCoords.y - dragged.dragCfg.oR.y);
			}
		}

		dragged.dragCfg.nx = dragged.dragCfg.oC.x + dx - dragged.dragCfg.diffX;
		dragged.dragCfg.ny = dragged.dragCfg.oC.y + dy - dragged.dragCfg.diffY;

		if (dragged.dragCfg.si && (dragged.dragCfg.onSlide || dragged.dragCfg.onChange)) {
			jQuery.iSlider.onSlide(dragged, dragged.dragCfg.nx, dragged.dragCfg.ny);
		}

		if(dragged.dragCfg.onDrag)
			dragged.dragCfg.onDrag.apply(dragged, [dragged.dragCfg.oR.x + dx, dragged.dragCfg.oR.y + dy]);
			
		if (!dragged.dragCfg.axis || dragged.dragCfg.axis == 'horizontally') {
			dragged.dragCfg.nRx = dragged.dragCfg.oR.x + dx;
			jQuery.iDrag.helper.get(0).style.left = dragged.dragCfg.nx + 'px';
		}
		if (!dragged.dragCfg.axis || dragged.dragCfg.axis == 'vertically') {
			dragged.dragCfg.nRy = dragged.dragCfg.oR.y + dy;
			jQuery.iDrag.helper.get(0).style.top = dragged.dragCfg.ny + 'px';
		}
		
		if (jQuery.iDrop && jQuery.iDrop.count > 0 ){
			jQuery.iDrop.checkhover(dragged);
		}
		return false;
	},

	build : function(o)
	{
		if (!jQuery.iDrag.helper) {
			jQuery('body',document).append('<div id="dragHelper"></div>');
			jQuery.iDrag.helper = jQuery('#dragHelper');
			var el = jQuery.iDrag.helper.get(0);
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
				var dhe = o.handle ? jQuery(this).find(o.handle) : jQuery(this);
				if(jQuery.browser.msie) {
					dhe.each(
						function()
						{
							this.unselectable = "on";
						}
					);
				} else {
					dhe.css('-moz-user-select', 'none');
					dhe.css('user-select', 'none');
					dhe.css('-khtml-user-select', 'none');
				}
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
					}
				);
				dhe.bind('mousedown', jQuery.iDrag.draginit);
			}
		)
	}
};

/**
 * Destroy an existing draggable on a collection of elements
 * 
 * @name DraggableDestroy
 * @descr Destroy a draggable
 * @type jQuery
 * @cat Plugins/Interface
 * @example $('#drag2').DraggableDestroy();
 */

jQuery.fn.extend(
	{
		DraggableDestroy : jQuery.iDrag.destroy,
		Draggable : jQuery.iDrag.build
	}
);/**
 * Interface Elements for jQuery
 * Droppables
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * With the Draggables plugin, Droppable allows you to create drop zones for draggable elements.
 *
 * @name Droppable
 * @cat Plugins/Interface
 * @param Hash options A hash of options
 * @option String accept The class name for draggables to get accepted by the droppable (mandatory)
 * @option String activeclass When an acceptable draggable is moved, the droppable gets this class
 * @option String hoverclass When an acceptable draggable is inside the droppable, the droppable gets
 *                           this class
 * @option String tolerance  Choose from 'pointer', 'intersect', or 'fit'. The pointer options means
 *                           that the pointer must be inside the droppable in order for the draggable
 *                           to be dropped. The intersect option means that the draggable must intersect
 *                           the droppable. The fit option means that the entire draggable must be
 *                           inside the droppable.
 * @option Function onDrop   When an acceptable draggable is dropped on a droppable, this callback is
 *                           called. It passes the draggable DOMElement as a parameter.
 * @option Function onHover  When an acceptable draggable is hovered over a droppable, this callback
 *                           is called. It passes the draggable DOMElement as a parameter.
 * @option Function onOut    When an acceptable draggable leaves a droppable, this callback is called.
 *                           It passes the draggable DOMElement as a parameter.
 * @example                  $('#dropzone1').Droppable(
 *                             {
 *                               accept : 'dropaccept', 
 *                               activeclass: 'dropzoneactive', 
 *                               hoverclass:	'dropzonehover',
 *                               ondrop:	function (drag) {
 *                                              alert(this); //the droppable
 *                                              alert(drag); //the draggable
 *                                        },
 *                               fit: true
 *                             }
 *                           )
 */

jQuery.iDrop = {
	fit : function (zonex, zoney, zonew, zoneh)
	{
		return 	zonex <= jQuery.iDrag.dragged.dragCfg.nx && 
				(zonex + zonew) >= (jQuery.iDrag.dragged.dragCfg.nx + jQuery.iDrag.dragged.dragCfg.oC.w) &&
				zoney <= jQuery.iDrag.dragged.dragCfg.ny && 
				(zoney + zoneh) >= (jQuery.iDrag.dragged.dragCfg.ny + jQuery.iDrag.dragged.dragCfg.oC.h) ? true :false;
	},
	intersect : function (zonex, zoney, zonew, zoneh)
	{
		return 	! ( zonex > (jQuery.iDrag.dragged.dragCfg.nx + jQuery.iDrag.dragged.dragCfg.oC.w)
				|| (zonex + zonew) < jQuery.iDrag.dragged.dragCfg.nx 
				|| zoney > (jQuery.iDrag.dragged.dragCfg.ny + jQuery.iDrag.dragged.dragCfg.oC.h) 
				|| (zoney + zoneh) < jQuery.iDrag.dragged.dragCfg.ny
				) ? true :false;
	},
	pointer : function (zonex, zoney, zonew, zoneh)
	{
		return	zonex < jQuery.iDrag.dragged.dragCfg.currentPointer.x
				&& (zonex + zonew) > jQuery.iDrag.dragged.dragCfg.currentPointer.x 
				&& zoney < jQuery.iDrag.dragged.dragCfg.currentPointer.y 
				&& (zoney + zoneh) > jQuery.iDrag.dragged.dragCfg.currentPointer.y
				? true :false;
	},
	overzone : false,
	highlighted : {},
	count : 0,
	zones : {},
	
	highlight : function (elm)
	{
		if (jQuery.iDrag.dragged == null) {
			return;
		}
		var i;
		jQuery.iDrop.highlighted = {};
		var oneIsSortable = false;
		for (i in jQuery.iDrop.zones) {
			if (jQuery.iDrop.zones[i] != null) {
				var iEL = jQuery.iDrop.zones[i].get(0);
				if (jQuery(jQuery.iDrag.dragged).is('.' + iEL.dropCfg.a)) {
					if (iEL.dropCfg.m == false) {
						iEL.dropCfg.p = jQuery.extend(
							jQuery.iUtil.getPositionLite(iEL),
							jQuery.iUtil.getSizeLite(iEL)
						);//jQuery.iUtil.getPos(iEL);
						iEL.dropCfg.m = true;
					}
					if (iEL.dropCfg.ac) {
						jQuery.iDrop.zones[i].addClass(iEL.dropCfg.ac);
					}
					jQuery.iDrop.highlighted[i] = jQuery.iDrop.zones[i];
					//if (jQuery.iSort && jQuery.iDrag.dragged.dragCfg.so) {
					if (jQuery.iSort && iEL.dropCfg.s && jQuery.iDrag.dragged.dragCfg.so) {
						iEL.dropCfg.el = jQuery('.' + iEL.dropCfg.a, iEL);
						elm.style.display = 'none';
						jQuery.iSort.measure(iEL);
						iEL.dropCfg.os = jQuery.iSort.serialize(jQuery.attr(iEL, 'id')).hash;
						elm.style.display = elm.dragCfg.oD;
						oneIsSortable = true;
					}
					if (iEL.dropCfg.onActivate) {
						iEL.dropCfg.onActivate.apply(jQuery.iDrop.zones[i].get(0), [jQuery.iDrag.dragged]);
					}
				}
			}
		}
		//if (jQuery.iSort && jQuery.iDrag.dragged.dragCfg.so) {
		if (oneIsSortable) {
			jQuery.iSort.start();
		}
	},
	/**
	 * remeasure the droppable
	 * 
	 * useful when the positions/dimensions for droppables 
	 * are changed while dragging a element
	 * 
	 * this works for sortables too but with a greate processor 
	 * penality because remeasures each sort items too
	 */
	remeasure : function()
	{
		jQuery.iDrop.highlighted = {};
		for (i in jQuery.iDrop.zones) {
			if (jQuery.iDrop.zones[i] != null) {
				var iEL = jQuery.iDrop.zones[i].get(0);
				if (jQuery(jQuery.iDrag.dragged).is('.' + iEL.dropCfg.a)) {
					iEL.dropCfg.p = jQuery.extend(
						jQuery.iUtil.getPositionLite(iEL),
						jQuery.iUtil.getSizeLite(iEL)
					);
					if (iEL.dropCfg.ac) {
						jQuery.iDrop.zones[i].addClass(iEL.dropCfg.ac);
					}
					jQuery.iDrop.highlighted[i] = jQuery.iDrop.zones[i];
					
					if (jQuery.iSort && iEL.dropCfg.s && jQuery.iDrag.dragged.dragCfg.so) {
						iEL.dropCfg.el = jQuery('.' + iEL.dropCfg.a, iEL);
						elm.style.display = 'none';
						jQuery.iSort.measure(iEL);
						elm.style.display = elm.dragCfg.oD;
					}
				}
			}
		}
	},
	
	checkhover : function (e)
	{
		if (jQuery.iDrag.dragged == null) {
			return;
		}
		jQuery.iDrop.overzone = false;
		var i;
		var applyOnHover = false;
		var hlt = 0;
		for (i in jQuery.iDrop.highlighted)
		{
			var iEL = jQuery.iDrop.highlighted[i].get(0);
			if ( 
					jQuery.iDrop.overzone == false
					 && 
					jQuery.iDrop[iEL.dropCfg.t](
					 	iEL.dropCfg.p.x, 
						iEL.dropCfg.p.y, 
						iEL.dropCfg.p.wb, 
						iEL.dropCfg.p.hb
					)
					 
			) {
				if (iEL.dropCfg.hc && iEL.dropCfg.h == false) {
					jQuery.iDrop.highlighted[i].addClass(iEL.dropCfg.hc);
				}
				//chec if onHover function has to be called
				if (iEL.dropCfg.h == false &&iEL.dropCfg.onHover) {
					applyOnHover = true;
				}
				iEL.dropCfg.h = true;
				jQuery.iDrop.overzone = iEL;
				//if(jQuery.iSort && jQuery.iDrag.dragged.dragCfg.so) {
				if(jQuery.iSort && iEL.dropCfg.s && jQuery.iDrag.dragged.dragCfg.so) {
					jQuery.iSort.helper.get(0).className = iEL.dropCfg.shc;
					jQuery.iSort.checkhover(iEL);
				}
				hlt ++;
			} else if(iEL.dropCfg.h == true) {
				//onOut function
				if (iEL.dropCfg.onOut) {
					iEL.dropCfg.onOut.apply(iEL, [e, jQuery.iDrag.helper.get(0).firstChild, iEL.dropCfg.fx]);
				}
				if (iEL.dropCfg.hc) {
					jQuery.iDrop.highlighted[i].removeClass(iEL.dropCfg.hc);
				}
				iEL.dropCfg.h = false;
			}
		}
		if (jQuery.iSort && !jQuery.iDrop.overzone && jQuery.iDrag.dragged.so) {
			jQuery.iSort.helper.get(0).style.display = 'none';
			//jQuery('body').append(jQuery.iSort.helper.get(0));
		}
		//call onhover
		if(applyOnHover) {
			jQuery.iDrop.overzone.dropCfg.onHover.apply(jQuery.iDrop.overzone, [e, jQuery.iDrag.helper.get(0).firstChild]);
		}
	},
	checkdrop : function (e)
	{
		var i;
		for (i in jQuery.iDrop.highlighted) {
			var iEL = jQuery.iDrop.highlighted[i].get(0);
			if (iEL.dropCfg.ac) {
				jQuery.iDrop.highlighted[i].removeClass(iEL.dropCfg.ac);
			}
			if (iEL.dropCfg.hc) {
				jQuery.iDrop.highlighted[i].removeClass(iEL.dropCfg.hc);
			}
			if(iEL.dropCfg.s) {
				jQuery.iSort.changed[jQuery.iSort.changed.length] = i;
			}
			if (iEL.dropCfg.onDrop && iEL.dropCfg.h == true) {
				iEL.dropCfg.h = false;
				iEL.dropCfg.onDrop.apply(iEL, [e, iEL.dropCfg.fx]);
			}
			iEL.dropCfg.m = false;
			iEL.dropCfg.h  = false;
		}
		jQuery.iDrop.highlighted = {};
	},
	destroy : function()
	{
		return this.each(
			function()
			{
				if (this.isDroppable) {
					if (this.dropCfg.s) {
						id = jQuery.attr(this,'id');
						jQuery.iSort.collected[id] = null;
						jQuery('.' + this.dropCfg.a, this).DraggableDestroy();
					}
					jQuery.iDrop.zones['d' + this.idsa] = null;
					this.isDroppable = false;
					this.f = null;
				}
			}
		);
	},
	build : function (o)
	{
		return this.each(
			function()
			{
				if (this.isDroppable == true || !o.accept || !jQuery.iUtil || !jQuery.iDrag){
					return;
				}
				this.dropCfg = {
					a : o.accept,
					ac: o.activeclass||false, 
					hc:	o.hoverclass||false,
					shc: o.helperclass||false,
					onDrop:	o.ondrop||o.onDrop||false,
					onHover: o.onHover||o.onhover||false,
					onOut: o.onOut||o.onout||false,
					onActivate: o.onActivate||false,
					t: o.tolerance && ( o.tolerance == 'fit' || o.tolerance == 'intersect') ? o.tolerance : 'pointer',
					fx: o.fx ? o.fx : false,
					m: false,
					h: false
				};
				if (o.sortable == true && jQuery.iSort) {
					id = jQuery.attr(this,'id');
					jQuery.iSort.collected[id] = this.dropCfg.a;
					this.dropCfg.s = true;
					if(o.onChange) {
						this.dropCfg.onChange = o.onChange;
						this.dropCfg.os = jQuery.iSort.serialize(id).hash;
					}
				}
				this.isDroppable = true;
				this.idsa = parseInt(Math.random() * 10000);
				jQuery.iDrop.zones['d' + this.idsa] = jQuery(this);
				jQuery.iDrop.count ++;
			}
		);
	}
};

/**
 * Destroy an existing droppable on a collection of elements
 * 
 * @name DroppableDestroy
 * @descr Destroy a droppable
 * @type jQuery
 * @cat Plugins/Interface
 * @example $('#drag2').DroppableDestroy();
 */

jQuery.fn.extend(
	{
		DroppableDestroy : jQuery.iDrop.destroy,
		Droppable : jQuery.iDrop.build
	}
);

 
/**
 * Recalculate all Droppables
 *
 * @name $.recallDroppables
 * @type jQuery
 * @cat Plugins/Interface
 * @example $.recallDroppable();
 */

jQuery.recallDroppables = jQuery.iDrop.remeasure;/**
 * Interface Elements for jQuery
 * Expander
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */
 
/**
 * Expands text and textarea elements while new characters are typed to the a miximum width
 *
 * @name Expander
 * @description Expands text and textarea elements while new characters are typed to the a miximum width
 * @param Mixed limit integer if only expands in width, array if expands in width and height
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */

jQuery.iExpander =
{
	helper : null,
	expand : function()
	{
		
		text = this.value;
		if (!text)
			return;
		style = {
			fontFamily: jQuery(this).css('fontFamily')||'',
			fontSize: jQuery(this).css('fontSize')||'',
			fontWeight: jQuery(this).css('fontWeight')||'',
			fontStyle: jQuery(this).css('fontStyle')||'',
			fontStretch: jQuery(this).css('fontStretch')||'',
			fontVariant: jQuery(this).css('fontVariant')||'',
			letterSpacing: jQuery(this).css('letterSpacing')||'',
			wordSpacing: jQuery(this).css('wordSpacing')||''
		};
		jQuery.iExpander.helper.css(style);
		html = jQuery.iExpander.htmlEntities(text);
		html = html.replace(new RegExp( "\\n", "g" ), "<br />");
		jQuery.iExpander.helper.html('pW');
		spacer = jQuery.iExpander.helper.get(0).offsetWidth;
		jQuery.iExpander.helper.html(html);
		width = jQuery.iExpander.helper.get(0).offsetWidth + spacer;
		if (this.Expander.limit && width > this.Expander.limit[0]) {
			width = this.Expander.limit[0];
		}
		this.style.width = width + 'px';
		if (this.tagName == 'TEXTAREA') {
			height = jQuery.iExpander.helper.get(0).offsetHeight + spacer;
			if (this.Expander.limit && height > this.Expander.limit[1]) {
				height = this.Expander.limit[1];
			}
			this.style.height = height + 'px';
		}
	},
	htmlEntities : function(text)
	{ 
		entities = {
			'&':'&amp;',
			'<':'&lt;',
			'>':'&gt;',
			'"':'&quot;'
		};
		for(i in entities) {
			text = text.replace(new RegExp(i,'g'),entities[i]);
		}
		return text;
	},
	build : function(limit)
	{
		if (jQuery.iExpander.helper == null) {
			jQuery('body', document).append('<div id="expanderHelper" style="position: absolute; top: 0; left: 0; visibility: hidden;"></div>');
			jQuery.iExpander.helper = jQuery('#expanderHelper');
		}
		return this.each(
			function()
			{
				if (/TEXTAREA|INPUT/.test(this.tagName)) {
					if (this.tagName == 'INPUT') {
						elType = this.getAttribute('type');
						if (!/text|password/.test(elType)) {
							return;
						}
					}
					if (limit && (limit.constructor == Number || (limit.constructor == Array && limit.length == 2))) {
						if (limit.constructor == Number)
							limit = [limit, limit];
						else {
							limit[0] = parseInt(limit[0])||400;
							limit[1] = parseInt(limit[1])||400;
						}
						this.Expander = {
							limit : limit
						};
					}
					jQuery(this)
						.blur(jQuery.iExpander.expand)
						.keyup(jQuery.iExpander.expand)
						.keypress(jQuery.iExpander.expand);
					jQuery.iExpander.expand.apply(this);
				}
			}
		);			
	}
};

jQuery.fn.Autoexpand = jQuery.iExpander.build;/**
 * Interface Elements for jQuery
 * FX
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Validates elements that can be animated
 */
jQuery.fxCheckTag = function(e)
{
	if (/^tr$|^td$|^tbody$|^caption$|^thead$|^tfoot$|^col$|^colgroup$|^th$|^body$|^header$|^script$|^frame$|^frameset$|^option$|^optgroup$|^meta$/i.test(e.nodeName) )
		return false;
	else 
		return true;
};

/**
 * Destroy the wrapper used for some animations
 */
jQuery.fx.destroyWrapper = function(e, old)
{
	var c = e.firstChild;
	var cs = c.style;
	cs.position = old.position;
	cs.marginTop = old.margins.t;
	cs.marginLeft = old.margins.l;
	cs.marginBottom = old.margins.b;
	cs.marginRight = old.margins.r;
	cs.top = old.top + 'px';
	cs.left = old.left + 'px';
	e.parentNode.insertBefore(c, e);
	e.parentNode.removeChild(e);
};

/**
 * Builds a wrapper used for some animations
 */
jQuery.fx.buildWrapper = function(e)
{
	if (!jQuery.fxCheckTag(e))
		return false;
	var t = jQuery(e);
	var es = e.style;
	var restoreStyle = false;
	
	if (t.css('display') == 'none') {
		oldVisibility = t.css('visibility');
		t.css('visibility', 'hidden').show();
		restoreStyle = true;
	}
	var oldStyle = {};
	oldStyle.position = t.css('position');
	oldStyle.sizes = jQuery.iUtil.getSize(e);
	oldStyle.margins = jQuery.iUtil.getMargins(e);
	
	var oldFloat = e.currentStyle ? e.currentStyle.styleFloat : t.css('float');
	oldStyle.top = parseInt(t.css('top'))||0;
	oldStyle.left = parseInt(t.css('left'))||0;
	var wid = 'w_' + parseInt(Math.random() * 10000);
	var wr = document.createElement(/^img$|^br$|^input$|^hr$|^select$|^textarea$|^object$|^iframe$|^button$|^form$|^table$|^ul$|^dl$|^ol$/i.test(e.nodeName) ? 'div' : e.nodeName);
	jQuery.attr(wr,'id', wid);
	var wrapEl = jQuery(wr).addClass('fxWrapper');
	var wrs = wr.style;
	var top = 0;
	var left = 0;
	if (oldStyle.position == 'relative' || oldStyle.position == 'absolute'){
		top = oldStyle.top;
		left = oldStyle.left;
	}
	
	wrs.top = top + 'px';
	wrs.left = left + 'px';
	wrs.position = oldStyle.position != 'relative' && oldStyle.position != 'absolute' ? 'relative' : oldStyle.position;
	wrs.height = oldStyle.sizes.hb + 'px';
	wrs.width = oldStyle.sizes.wb + 'px';
	wrs.marginTop = oldStyle.margins.t;
	wrs.marginRight = oldStyle.margins.r;
	wrs.marginBottom = oldStyle.margins.b;
	wrs.marginLeft = oldStyle.margins.l;
	wrs.overflow = 'hidden';
	if (jQuery.browser.msie) {
		wrs.styleFloat = oldFloat;
	} else {
		wrs.cssFloat = oldFloat;
	}
	if (jQuery.browser == "msie") {
		es.filter = "alpha(opacity=" + 0.999*100 + ")";
	}
	es.opacity = 0.999;
	//t.wrap(wr);
	e.parentNode.insertBefore(wr, e);
	wr.appendChild(e);
	es.marginTop = '0px';
	es.marginRight = '0px';
	es.marginBottom = '0px';
	es.marginLeft = '0px';
	es.position = 'absolute';
	es.listStyle = 'none';
	es.top = '0px';
	es.left = '0px';
	if (restoreStyle) {
		t.hide();
		es.visibility = oldVisibility;
	}
	return {oldStyle:oldStyle, wrapper:jQuery(wr)};
};

/**
 * named colors
 */
jQuery.fx.namedColors = {
	aqua:[0,255,255],
	azure:[240,255,255],
	beige:[245,245,220],
	black:[0,0,0],
	blue:[0,0,255],
	brown:[165,42,42],
	cyan:[0,255,255],
	darkblue:[0,0,139],
	darkcyan:[0,139,139],
	darkgrey:[169,169,169],
	darkgreen:[0,100,0],
	darkkhaki:[189,183,107],
	darkmagenta:[139,0,139],
	darkolivegreen:[85,107,47],
	darkorange:[255,140,0],
	darkorchid:[153,50,204],
	darkred:[139,0,0],
	darksalmon:[233,150,122],
	darkviolet:[148,0,211],
	fuchsia:[255,0,255],
	gold:[255,215,0],
	green:[0,128,0],
	indigo:[75,0,130],
	khaki:[240,230,140],
	lightblue:[173,216,230],
	lightcyan:[224,255,255],
	lightgreen:[144,238,144],
	lightgrey:[211,211,211],
	lightpink:[255,182,193],
	lightyellow:[255,255,224],
	lime:[0,255,0],
	magenta:[255,0,255],
	maroon:[128,0,0],
	navy:[0,0,128],
	olive:[128,128,0],
	orange:[255,165,0],
	pink:[255,192,203],
	purple:[128,0,128],
	red:[255,0,0],
	silver:[192,192,192],
	white:[255,255,255],
	yellow:[255,255,0]
};

/**
 * parses a color to an object for reg, green and blue
 */
jQuery.fx.parseColor = function(color, notColor)
{
	if (jQuery.fx.namedColors[color]) 
		return {
			r: jQuery.fx.namedColors[color][0],
			g: jQuery.fx.namedColors[color][1],
			b: jQuery.fx.namedColors[color][2]
		};
	else if (result = /^rgb\(\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*,\s*([0-9]{1,3})\s*\)$/.exec(color))
		return {
			r: parseInt(result[1]),
			g: parseInt(result[2]),
			b: parseInt(result[3])
		};
	else if (result = /rgb\(\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*,\s*([0-9]+(?:\.[0-9]+)?)\%\s*\)$/.exec(color)) 
		return {
			r: parseFloat(result[1])*2.55,
			g: parseFloat(result[2])*2.55,
			b: parseFloat(result[3])*2.55
		};
	else if (result = /^#([a-fA-F0-9])([a-fA-F0-9])([a-fA-F0-9])$/.exec(color))
		return {
			r: parseInt("0x"+ result[1] + result[1]),
			g: parseInt("0x" + result[2] + result[2]),
			b: parseInt("0x" + result[3] + result[3])
		};
	else if (result = /^#([a-fA-F0-9]{2})([a-fA-F0-9]{2})([a-fA-F0-9]{2})$/.exec(color))
		return {
			r: parseInt("0x" + result[1]),
			g: parseInt("0x" + result[2]),
			b: parseInt("0x" + result[3])
		};
	else
		return notColor == true ? false : {r: 255, g: 255, b: 255};
};
/**
 * CSS rules that can be animated
 */
jQuery.fx.cssProps = {
	borderBottomWidth:1,
	borderLeftWidth:1,
	borderRightWidth:1,
	borderTopWidth:1,
	bottom:1,
	fontSize:1,
	height:1,
	left:1,
	letterSpacing:1,
	lineHeight:1,
	marginBottom:1,
	marginLeft:1,
	marginRight:1,
	marginTop:1,
	maxHeight:1,
	maxWidth:1,
	minHeight:1,
	minWidth:1,
	opacity:1,
	outlineOffset:1,
	outlineWidth:1,
	paddingBottom:1,
	paddingLeft:1,
	paddingRight:1,
	paddingTop:1,
	right:1,
	textIndent:1,
	top:1,
    width:1,
	zIndex:1
};
/**
 * CSS color rules that can be animated
 */
jQuery.fx.colorCssProps = {
	backgroundColor:1,
	borderBottomColor:1,
	borderLeftColor:1,
	borderRightColor:1,
	borderTopColor:1,
	color:1,
	outlineColor:1
};

jQuery.fx.cssSides = ['Top', 'Right', 'Bottom', 'Left'];
jQuery.fx.cssSidesEnd = {
	'borderWidth': ['border', 'Width'],
	'borderColor': ['border', 'Color'],
	'margin': ['margin', ''],
	'padding': ['padding', '']
};

/**
 * Overwrite animation to use new FX function
 */
jQuery.fn.extend({
	
	animate: function( prop, speed, easing, callback ) {
		return this.queue(function(){
			var opt = jQuery.speed(speed, easing, callback);
			var e = new jQuery.fxe( this, opt, prop );
			
		});
	},
	pause: function(speed, callback) {
		return this.queue(function(){
			var opt = jQuery.speed(speed, callback);
			var e = new jQuery.pause( this, opt );
		});
	},
	stop : function(step) {
		return this.each(function(){
			if (this.animationHandler)
				jQuery.stopAnim(this, step);
			
		});
	},
	stopAll : function(step) {
		return this.each(function(){
			if (this.animationHandler)
				jQuery.stopAnim(this, step);
			if ( this.queue && this.queue['fx'] )
				this.queue.fx = [];
		});
	}
});
/**
 * Improved FXC function that aniamtes collection of properties per timer. Accepts inline styles and class names to animate
 */
jQuery.extend({
	pause: function(elem, options)
	{
		var z = this, values;
		z.step = function()
		{
			if ( jQuery.isFunction( options.complete ) )
				options.complete.apply( elem );
		};
		z.timer=setInterval(function(){z.step();},options.duration);
		elem.animationHandler = z;
	},
	easing :  {
		linear: function(p, n, firstNum, delta, duration) {
			return ((-Math.cos(p*Math.PI)/2) + 0.5) * delta + firstNum;
		}
	},
	fxe: function( elem, options, prop ){
		var z = this, values;

		// The styles
		var y = elem.style;
		var oldOverflow = jQuery.css(elem, "overflow");
		var oldDisplay= jQuery.css(elem, "display");
		var props = {};
		z.startTime = (new Date()).getTime();
		options.easing = options.easing && jQuery.easing[options.easing] ? options.easing : 'linear';
		
		z.getValues = function(tp, vp)
		{
			if (jQuery.fx.cssProps[tp]) {
				if (vp == 'show' || vp == 'hide' || vp == 'toggle') {
					if ( !elem.orig ) elem.orig = {};
					var r = parseFloat( jQuery.curCSS(elem, tp) );
					elem.orig[tp] = r && r > -10000 ? r : (parseFloat( jQuery.css(elem,tp) )||0);
					vp = vp == 'toggle' ? ( oldDisplay == 'none' ? 'show' : 'hide') : vp;
					options[vp] = true;
					props[tp] = vp == 'show' ? [0, elem.orig[tp]] : [elem.orig[tp], 0];
					if (tp != 'opacity')
						y[tp] = props[tp][0] + (tp != 'zIndex' && tp != 'fontWeight' ? 'px':'');
					else
						jQuery.attr(y, "opacity", props[tp][0]);
				} else {
					props[tp] = [parseFloat( jQuery.curCSS(elem, tp) ), parseFloat(vp)||0];
				}
			} else if (jQuery.fx.colorCssProps[tp])
				props[tp] = [jQuery.fx.parseColor(jQuery.curCSS(elem, tp)), jQuery.fx.parseColor(vp)];
			else if(/^margin$|padding$|border$|borderColor$|borderWidth$/i.test(tp)) {
				var m = vp.replace(/\s+/g, ' ').replace(/rgb\s*\(\s*/g,'rgb(').replace(/\s*,\s*/g,',').replace(/\s*\)/g,')').match(/([^\s]+)/g);
				switch(tp){
					case 'margin':
					case 'padding':
					case 'borderWidth':
					case 'borderColor':
						m[3] = m[3]||m[1]||m[0];
						m[2] = m[2]||m[0];
						m[1] = m[1]||m[0];
						for(var i = 0; i < jQuery.fx.cssSides.length; i++) {
							var nmp = jQuery.fx.cssSidesEnd[tp][0] + jQuery.fx.cssSides[i] + jQuery.fx.cssSidesEnd[tp][1];
							props[nmp] = tp == 'borderColor' ?
								[jQuery.fx.parseColor(jQuery.curCSS(elem, nmp)), jQuery.fx.parseColor(m[i])]
								: [parseFloat( jQuery.curCSS(elem, nmp) ), parseFloat(m[i])];
						}
						break;
					case 'border':
						for(var i = 0; i< m.length; i++) {
							var floatVal = parseFloat(m[i]);
							var sideEnd = !isNaN(floatVal) ? 'Width' : (!/transparent|none|hidden|dotted|dashed|solid|double|groove|ridge|inset|outset/i.test(m[i]) ? 'Color' : false);
							if (sideEnd) {
								for(var j = 0; j < jQuery.fx.cssSides.length; j++) {
									nmp = 'border' + jQuery.fx.cssSides[j] + sideEnd;
									props[nmp] = sideEnd == 'Color' ?
								[jQuery.fx.parseColor(jQuery.curCSS(elem, nmp)), jQuery.fx.parseColor(m[i])]
								: [parseFloat( jQuery.curCSS(elem, nmp) ), floatVal];
								}
							} else {
								y['borderStyle'] = m[i];
							}
						}
						break;
				}
			} else {
				y[tp] = vp;
			}
			return false;
		};
		
		for(p in prop) {
			if (p == 'style') {
				var newStyles = jQuery.parseStyle(prop[p]);
				for (np in newStyles) {
					this.getValues(np, newStyles[np]);
				}
			} else if (p == 'className') {
				if (document.styleSheets)
					for (var i=0; i<document.styleSheets.length; i++){
						var cssRules = document.styleSheets[i].cssRules||document.styleSheets[i].rules||null;
						if (cssRules) {
							for (var j=0; j<cssRules.length; j++) {
								if(cssRules[j].selectorText == '.' + prop[p]) {
									var rule = new RegExp('\.' + prop[p] + ' {');
									var styles = cssRules[j].style.cssText;
									var newStyles = jQuery.parseStyle(styles.replace(rule, '').replace(/}/g, ''));
									for (np in newStyles) {
										this.getValues(np, newStyles[np]);
									}
								}
							}
						}
					}
			} else {
				this.getValues(p, prop[p]);
			}
		}
		y.display = oldDisplay == 'none' ? 'block' : oldDisplay;
		y.overflow = 'hidden';
		
		/*if (options.show)
			y.display = "";*/
		
		z.step = function(){
			var t = (new Date()).getTime();
			if (t > options.duration + z.startTime) {
				clearInterval(z.timer);
				z.timer = null;
				for (p in props) {
					if ( p == "opacity" )
						jQuery.attr(y, "opacity", props[p][1]);
					else if (typeof props[p][1] == 'object')
						y[p] = 'rgb(' + props[p][1].r +',' + props[p][1].g +',' + props[p][1].b +')';
					else 
						y[p] = props[p][1] + (p != 'zIndex' && p != 'fontWeight' ? 'px':'');
				}
				if ( options.hide || options.show )
					for ( var p in elem.orig )
						if (p == "opacity")
							jQuery.attr(y, p, elem.orig[p]);
						else
							y[p] = "";
				y.display = options.hide ? 'none' : (oldDisplay !='none' ? oldDisplay : 'block');
				y.overflow = oldOverflow;
				elem.animationHandler = null;
				if ( jQuery.isFunction( options.complete ) )
					options.complete.apply( elem );
			} else {
				var n = t - this.startTime;
				var pr = n / options.duration;
				for (p in props) {
					if (typeof props[p][1] == 'object') {
						y[p] = 'rgb('
						+ parseInt(jQuery.easing[options.easing](pr, n,  props[p][0].r, (props[p][1].r-props[p][0].r), options.duration))
						+ ','
						+ parseInt(jQuery.easing[options.easing](pr, n,  props[p][0].g, (props[p][1].g-props[p][0].g), options.duration))
						+ ','
						+ parseInt(jQuery.easing[options.easing](pr, n,  props[p][0].b, (props[p][1].b-props[p][0].b), options.duration))
						+')';
					} else {
						var pValue = jQuery.easing[options.easing](pr, n,  props[p][0], (props[p][1]-props[p][0]), options.duration);
						if ( p == "opacity" )
							jQuery.attr(y, "opacity", pValue);
						else 
							y[p] = pValue + (p != 'zIndex' && p != 'fontWeight' ? 'px':'');
					}
				}

			}
		};
	z.timer=setInterval(function(){z.step();},13);
	elem.animationHandler = z;
	},
	stopAnim: function(elem, step)
	{
		if (step)
			elem.animationHandler.startTime -= 100000000;
		else {
			window.clearInterval(elem.animationHandler.timer);
			elem.animationHandler = null;
			jQuery.dequeue(elem, "fx");
		}
	}
}
);

jQuery.parseStyle = function(styles) {
	var newStyles = {};
	if (typeof styles == 'string') {
		styles = styles.toLowerCase().split(';');
		for(var i=0; i< styles.length; i++){
			rule = styles[i].split(':');
			if (rule.length == 2) {
				newStyles[jQuery.trim(rule[0].replace(/\-(\w)/g,function(m,c){return c.toUpperCase();}))] = jQuery.trim(rule[1]);
			}
		}
	}
	return newStyles;
};/**
 * Interface Elements for jQuery
 * FX - blind
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */
 
/**
 * Applies a blinding animation to element
 */
jQuery.fn.extend(
	{
		/**
		 * @name BlindUp
		 * @description blinds the element up
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		BlindUp : function (speed, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.BlindDirection(this, speed, callback, 'up', easing);
			});
		},
		
		/**
		 * @name BlindDown
		 * @description blinds the element down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		BlindDown : function (speed, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.BlindDirection(this, speed, callback, 'down', easing);
			});
		},
		
		/**
		 * @name BlindToggleVertically
		 * @description blinds the element up or down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		BlindToggleVertically : function (speed, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.BlindDirection(this, speed, callback, 'togglever', easing);
			});
		},
		
		/**
		 * @name BlindLeft
		 * @description blinds the element left
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		BlindLeft : function (speed, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.BlindDirection(this, speed, callback, 'left', easing);
			});
		},
		
		/**
		 * @name BlindRight
		 * @description blinds the element right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		BlindRight : function (speed, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.BlindDirection(this, speed, callback, 'right', easing);
			});
		},
		
		/**
		 * @name BlindToggleHorizontally
		 * @description blinds the element left and right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		BlindToggleHorizontally : function (speed, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.BlindDirection(this, speed, callback, 'togglehor', easing);
			});
		}
	}
);

jQuery.fx.BlindDirection = function (e, speed, callback, direction, easing)
{
	if (!jQuery.fxCheckTag(e)) {
		jQuery.dequeue(e, 'interfaceFX');
		return false;
	}
	var z = this;
	z.el = jQuery(e);
	z.size = jQuery.iUtil.getSize(e);
	z.easing = typeof callback == 'string' ? callback : easing||null;
	if (!e.ifxFirstDisplay)
		e.ifxFirstDisplay = z.el.css('display');
	if ( direction == 'togglever') {
		direction = z.el.css('display') == 'none' ? 'down' : 'up';
	} else if (direction == 'togglehor') {
		direction = z.el.css('display') == 'none' ? 'right' : 'left';
	}
	z.el.show();
	z.speed = speed;
	z.callback = typeof callback == 'function' ? callback : null;
	z.fx = jQuery.fx.buildWrapper(e);
	z.direction = direction;
	z.complete = function()
	{
		if (z.callback && z.callback.constructor == Function) {
			z.callback.apply(z.el.get(0));
		}
		if(z.direction == 'down' || z.direction == 'right'){
			z.el.css('display', z.el.get(0).ifxFirstDisplay == 'none' ? 'block' : z.el.get(0).ifxFirstDisplay);
		} else {
			z.el.hide();
		}
		jQuery.fx.destroyWrapper(z.fx.wrapper.get(0), z.fx.oldStyle);
		jQuery.dequeue(z.el.get(0), 'interfaceFX');
	};
	switch (z.direction) {
		case 'up':
			fxh = new jQuery.fx(
				z.fx.wrapper.get(0),
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'height'
			);
			fxh.custom(z.fx.oldStyle.sizes.hb, 0);
		break;
		case 'down':
			z.fx.wrapper.css('height', '1px');
			z.el.show();
			fxh = new jQuery.fx(
				z.fx.wrapper.get(0),
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'height'
			);
			fxh.custom(0, z.fx.oldStyle.sizes.hb);
		break;
		case 'left':
			fxh = new jQuery.fx(
				z.fx.wrapper.get(0),
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'width'
			);
			fxh.custom(z.fx.oldStyle.sizes.wb, 0);
		break;
		case 'right':
			z.fx.wrapper.css('width', '1px');
			z.el.show();
			fxh = new jQuery.fx(
				z.fx.wrapper.get(0),
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'width'
			);
			fxh.custom(0, z.fx.oldStyle.sizes.wb);
		break;
	}
};/**
 * Interface Elements for jQuery
 * FX - bounce
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * @name Bounce
 * @description makes the element to bounce
 * @param Integer hight the hight in pxels for element to jumps to
 * @param Function callback (optional) A function to be executed whenever the animation completes.
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.fn.Bounce = function (hight, callback) {
	return this.queue('interfaceFX', function(){
		if (!jQuery.fxCheckTag(this)) {
			jQuery.dequeue(this, 'interfaceFX');
			return false;
		}
		var e = new jQuery.fx.iBounce(this, hight, callback);
		e.bounce();
	});
};
jQuery.fx.iBounce = function (e, hight, callback)
{
	var z = this;
	z.el = jQuery(e);
	z.el.show();
	z.callback = callback;
	z.hight = parseInt(hight)||40;
	z.oldStyle = {};
	z.oldStyle.position = z.el.css('position');
	z.oldStyle.top = parseInt(z.el.css('top'))||0;
	z.oldStyle.left = parseInt(z.el.css('left'))||0;
	
	if (z.oldStyle.position != 'relative' && z.oldStyle.position != 'absolute') {
		z.el.css('position', 'relative');
	}
	
	z.times = 5;
	z.cnt = 1;
	
	z.bounce = function ()
	{
		z.cnt ++;
		z.e = new jQuery.fx(
			z.el.get(0), 
			{
			 duration: 120,
			 complete : function ()
			 {
				z.e = new jQuery.fx(
					z.el.get(0), 
					{
						duration: 80,
						complete : function ()
						{
							z.hight = parseInt(z.hight/2);
							if (z.cnt <= z.times)
								z.bounce();
							else {
								z.el.css('position', z.oldStyle.position).css('top', z.oldStyle.top + 'px').css('left', z.oldStyle.left + 'px');
								jQuery.dequeue(z.el.get(0), 'interfaceFX');
								if (z.callback && z.callback.constructor == Function) {
									z.callback.apply(z.el.get(0));
								}
							}
						}
					},
					'top'
				);
				z.e.custom (z.oldStyle.top-z.hight, z.oldStyle.top);
			 }
			}, 
			'top'
		);
		z.e.custom (z.oldStyle.top, z.oldStyle.top-z.hight);
	};
		
};/**
 * Interface Elements for jQuery
 * FX - drop
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Applies a dropping effect to element
 */
jQuery.fn.extend(
	{
		/**
		 * @name DropOutDown
		 * @description drops the element out down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropOutDown : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this, speed, callback, 'down', 'out', easing);
			});
		},
		
		/**
		 * @name DropInDown
		 * @description drops the element in down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropInDown : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'down', 'in', easing);
			});
		},
		
		/**
		 * @name DropToggleDown
		 * @description drops the element in/out down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropToggleDown : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'down', 'toggle', easing);
			});
		},
		
		/**
		 * @name DropOutUp
		 * @description drops the element out up
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropOutUp : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this, speed, callback, 'up', 'out', easing);
			});
		},
		
		/**
		 * @name DropInUp
		 * @description drops the element in up
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropInUp : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'up', 'in', easing);
			});
		},
		
		/**
		 * @name DropToggleUp
		 * @description drops the element in/out up
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropToggleUp : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'up', 'toggle', easing);
			});
		},
		
		/**
		 * @name DropOutLeft
		 * @description drops the element out left
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropOutLeft : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this, speed, callback, 'left', 'out', easing);
			});
		},
		
		/**
		 * @name DropInLeft
		 * @description drops the element in left
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropInLeft : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'left', 'in', easing);
			});
		},
		
		/**
		 * @name DropToggleLeft
		 * @description drops the element in/out left
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropToggleLeft : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'left', 'toggle', easing);
			});
		},
		
		/**
		 * @name DropOutRight
		 * @description drops the element out right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropOutRight : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this, speed, callback, 'right', 'out', easing);
			});
		},
		
		/**
		 * @name DropInRight
		 * @description drops the element in right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropInRight : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'right', 'in', easing);
			});
		},
		
		/**
		 * @name DropToggleRight
		 * @description drops the element in/out right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DropToggleRight : function (speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DropOutDirectiont(this,  speed, callback, 'right', 'toggle', easing);
			});
		}
	}
);

jQuery.fx.DropOutDirectiont = function (e, speed, callback, direction, type, easing)
{
	if (!jQuery.fxCheckTag(e)) {
		jQuery.dequeue(e, 'interfaceFX');
		return false;
	}
	var z = this;
	z.el = jQuery(e);
	z.easing = typeof callback == 'string' ? callback : easing||null;
	z.oldStyle = {};
	z.oldStyle.position = z.el.css('position');
	z.oldStyle.top = z.el.css('top');
	z.oldStyle.left = z.el.css('left');
	if (!e.ifxFirstDisplay)
		e.ifxFirstDisplay = z.el.css('display');
	if ( type == 'toggle') {
		type = z.el.css('display') == 'none' ? 'in' : 'out';
	}
	z.el.show();
	
	if (z.oldStyle.position != 'relative' && z.oldStyle.position != 'absolute') {
		z.el.css('position', 'relative');
	}
	z.type = type;
	callback = typeof callback == 'function' ? callback : null;
	/*sizes = ['em','px','pt','%'];
	for(i in sizes) {
		if (z.oldStyle.top.indexOf(sizes[i])>0) {
			z.topUnit = sizes[1];
			z.topSize = parseFloat(z.oldStyle.top)||0;
		}
		if (z.oldStyle.left.indexOf(sizes[i])>0) {
			z.leftUnit = sizes[1];
			z.leftSize = parseFloat(z.oldStyle.left)||0;
		}
	}*/
	
	directionIncrement = 1;
	switch (direction){
		case 'up':
			z.e = new jQuery.fx(z.el.get(0), jQuery.speed(speed - 15, z.easing,callback), 'top');
			z.point = parseFloat(z.oldStyle.top)||0;
			z.unit = z.topUnit;
			directionIncrement = -1;
		break;
		case 'down':
			z.e = new jQuery.fx(z.el.get(0), jQuery.speed(speed - 15, z.easing,callback), 'top');
			z.point = parseFloat(z.oldStyle.top)||0;
			z.unit = z.topUnit;
		break;
		case 'right':
			z.e = new jQuery.fx(z.el.get(0), jQuery.speed(speed - 15, z.easing,callback), 'left');
			z.point = parseFloat(z.oldStyle.left)||0;
			z.unit = z.leftUnit;
		break;
		case 'left':
			z.e = new jQuery.fx(z.el.get(0), jQuery.speed(speed - 15, z.easing,callback), 'left');
			z.point = parseFloat(z.oldStyle.left)||0;
			z.unit = z.leftUnit;
			directionIncrement = -1;
		break;
	}
	z.e2 = new jQuery.fx(
		z.el.get(0),
		jQuery.speed
		(
		 	speed, z.easing,
			function()
			{
				z.el.css(z.oldStyle);
				if (z.type == 'out') {
					z.el.css('display', 'none');
				} else 
					z.el.css('display', z.el.get(0).ifxFirstDisplay == 'none' ? 'block' : z.el.get(0).ifxFirstDisplay);
				
				jQuery.dequeue(z.el.get(0), 'interfaceFX');
			}
		 ),
		'opacity'
	);
	if (type == 'in') {
		z.e.custom(z.point+ 100*directionIncrement, z.point);
		z.e2.custom(0,1);
	} else {
		z.e.custom(z.point, z.point + 100*directionIncrement);
		z.e2.custom(1,0);
	}
};/**
 * Interface Elements for jQuery
 * FX - fold
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Applies a folding animation to element
 */
jQuery.fn.extend(
	{
		/**
		 * @name Fold
		 * @description folds the element
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Integer height the height in pixels to fold element to
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		Fold : function (speed, height, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DoFold(this, speed, height, callback, 'fold', easing);
			});
		},
		
		/**
		 * @name UnFold
		 * @description unfolds the element
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Integer height the height in pixels to unfold element to
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		UnFold : function (speed, height, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DoFold(this, speed, height, callback, 'unfold', easing);
			});
		},
		
		/**
		 * @name FoldToggle
		 * @description folds/unfolds the element
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Integer height the height in pixels to folds/unfolds element to
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		FoldToggle : function (speed, height, callback, easing)
		{
			return this.queue('interfaceFX',function(){
				new jQuery.fx.DoFold(this, speed, height, callback, 'toggle', easing);
			});
		}
	}
);

jQuery.fx.DoFold = function (e, speed, height, callback, type, easing)
{
	if (!jQuery.fxCheckTag(e)) {
		jQuery.dequeue(e, 'interfaceFX');
		return false;
	}
	var z = this;
	z.el = jQuery(e);
	z.easing = typeof callback == 'string' ? callback : easing||null;
	z.callback = typeof callback == 'function' ? callback : null;
	if ( type == 'toggle') {
		type = z.el.css('display') == 'none' ? 'unfold' : 'fold';
	}
	//z.el.show();
	z.speed = speed;
	z.height = height && height.constructor == Number ? height : 20;
	z.fx = jQuery.fx.buildWrapper(e);
	z.type = type;
	z.complete = function()
	{
		if (z.callback && z.callback.constructor == Function) {
			z.callback.apply(z.el.get(0));
		}
		if(z.type == 'unfold'){
			z.el.show();
		} else {
			z.el.hide();
		}
		jQuery.fx.destroyWrapper(z.fx.wrapper.get(0), z.fx.oldStyle);
		jQuery.dequeue(z.el.get(0), 'interfaceFX');
	};
	if ( z.type == 'unfold') {
		z.el.show();
		z.fx.wrapper.css('height', z.height + 'px').css('width', '1px');
		
		z.ef = new jQuery.fx(
				z.fx.wrapper.get(0),
				jQuery.speed (
					z.speed,
					z.easing,
					function()
					{
						z.ef = new jQuery.fx(
							z.fx.wrapper.get(0),
							jQuery.speed(
								z.speed,
								z.easing, 
								z.complete
							),
							'height'
						);
						z.ef.custom(z.height, z.fx.oldStyle.sizes.hb);
					}
				), 
				'width'
			);
		z.ef.custom(0, z.fx.oldStyle.sizes.wb);
	} else {
		z.ef = new jQuery.fx(
				z.fx.wrapper.get(0),
				jQuery.speed(
					z.speed,
					z.easing,
					function()
					{
						z.ef = new jQuery.fx(
							z.fx.wrapper.get(0),
							jQuery.speed(
								z.speed,
								z.easing,
								z.complete
							),
							'width'
						);
						z.ef.custom(z.fx.oldStyle.sizes.wb, 0);
					}
				), 
				'height'
			);
		z.ef.custom(z.fx.oldStyle.sizes.hb, z.height);
	}
};

/**
 * Interface Elements for jQuery
 * FX - Highlight
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */


/**
 * @name Highlight
 * @description Animates the backgroudn color to create a highlight animation
 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
 * @param String color color to highlight from
 * @param Function callback (optional) A function to be executed whenever the animation completes.
 * @param String easing (optional) The name of the easing effect that you want to use.
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.fn.Highlight = function(speed, color, callback, easing) {
	return this.queue(
		'interfaceColorFX',
		function()
		{
			this.oldStyleAttr = jQuery(this).attr("style") || '';
			easing = typeof callback == 'string' ? callback : easing||null;
			callback = typeof callback == 'function' ? callback : null;
			var oldColor = jQuery(this).css('backgroundColor');
			var parentEl = this.parentNode;
			while(oldColor == 'transparent' && parentEl) {
				oldColor = jQuery(parentEl).css('backgroundColor');
				parentEl = parentEl.parentNode;
			}
			jQuery(this).css('backgroundColor', color);
			
			
			/* In IE, style is a object.. */
			if(typeof this.oldStyleAttr == 'object') this.oldStyleAttr = this.oldStyleAttr["cssText"];
			
			jQuery(this).animate(
				{'backgroundColor':oldColor},
				speed,
				easing,
				function() {
					jQuery.dequeue(this, 'interfaceColorFX');
					if(typeof jQuery(this).attr("style") == 'object') {
						jQuery(this).attr("style")["cssText"] = "";
						jQuery(this).attr("style")["cssText"] = this.oldStyleAttr;
					} else {
						jQuery(this).attr("style", this.oldStyleAttr);	
					}
					if (callback)
						callback.apply(this);
				}
		  	);
		}
	);
};/**
 * Interface Elements for jQuery
 * FX - open/close/switch
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Applies an open/close animation to element
 */
jQuery.fn.extend(
	{
		/**
		 * @name CloseVertically
		 * @description closes the element vertically
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		CloseVertically : function (speed, callback, easing) {
			return this.queue('interfaceFX', function(){
				new jQuery.fx.OpenClose(this, speed, callback, 'vertically', 'close', easing);
			});
		},
		
		/**
		 * @name CloseHorizontally
		 * @description closes the element horizontally
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		CloseHorizontally : function (speed, callback, easing) {
			return this.queue('interfaceFX', function(){
				new jQuery.fx.OpenClose(this, speed, callback, 'horizontally', 'close', easing);
			});
		},
		
		/**
		 * @name SwitchHorizontally
		 * @description opens/closes the element horizontally
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SwitchHorizontally : function (speed, callback, easing) 
		{
			return this.queue('interfaceFX', function(){
				if (jQuery.css(this, 'display') == 'none') {
					new jQuery.fx.OpenClose(this, speed, callback, 'horizontally', 'open', easing);
				} else {
					new jQuery.fx.OpenClose(this, speed, callback, 'horizontally', 'close', easing);
				}
			});
		},
		
		/**
		 * @name SwitchVertically
		 * @description opens/closes the element vertically
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SwitchVertically : function (speed, callback, easing) 
		{
			return this.queue('interfaceFX', function(){
				if (jQuery.css(this, 'display') == 'none') {
					new jQuery.fx.OpenClose(this, speed, callback, 'vertically', 'open', easing);
				} else {
					new jQuery.fx.OpenClose(this, speed, callback, 'vertically', 'close', easing);
				}
			});
		},
		
		/**
		 * @name OpenVertically
		 * @description opens the element vertically
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		OpenVertically : function (speed, callback, easing) {
			return this.queue('interfaceFX', function(){
				new jQuery.fx.OpenClose(this, speed, callback, 'vertically', 'open', easing);
			});
		},
		
		/**
		 * @name OpenHorizontally
		 * @description opens the element horizontally
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		OpenHorizontally : function (speed, callback, easing) {
			return this.queue('interfaceFX', function(){
				new jQuery.fx.OpenClose(this, speed, callback, 'horizontally', 'open', easing);
			});
		}
	}
);

jQuery.fx.OpenClose = function (e, speed, callback, direction, type, easing)
{
	if (!jQuery.fxCheckTag(e)) {
		jQuery.dequeue(e, 'interfaceFX');
		return false;
	}
	var z = this;
	var restoreStyle = false;
	z.el = jQuery(e);
	z.easing = typeof callback == 'string' ? callback : easing||null;
	z.callback = typeof callback == 'function' ? callback : null;
	z.type = type;
	z.speed = speed;
	z.oldP = jQuery.iUtil.getSize(e);
	z.oldStyle = {};
	z.oldStyle.position = z.el.css('position');
	z.oldStyle.display = z.el.css('display');
	if (z.oldStyle.display == 'none') {
		oldVisibility = z.el.css('visibility');
		z.el.show();
		restoreStyle = true;
	}
	z.oldStyle.top = z.el.css('top');
	z.oldStyle.left = z.el.css('left');
	if (restoreStyle) {
		z.el.hide();
		z.el.css('visibility', oldVisibility);
	}
	z.oldStyle.width = z.oldP.w + 'px';
	z.oldStyle.height = z.oldP.h + 'px';
	z.oldStyle.overflow = z.el.css('overflow');
	z.oldP.top = parseInt(z.oldStyle.top)||0;
	z.oldP.left = parseInt(z.oldStyle.left)||0;
	//z.el.show();
	
	if (z.oldStyle.position != 'relative' && z.oldStyle.position != 'absolute') {
		z.el.css('position', 'relative');
	}
	z.el.css('overflow', 'hidden')
		.css('height', type == 'open' && direction == 'vertically' ? 1 : z.oldP.h + 'px')
		.css('width', type == 'open' && direction == 'horizontally' ? 1 : z.oldP.w + 'px');
	
	z.complete = function()
	{
		z.el.css(z.oldStyle);
		if (z.type == 'close')
			z.el.hide();
		else 
			z.el.show();
		jQuery.dequeue(z.el.get(0), 'interfaceFX');
	};
	
	switch (direction) {
		case 'vertically':
			z.eh = new jQuery.fx(
				z.el.get(0),
				jQuery.speed(speed-15, z.easing, callback),
				'height'
			);
			z.et = new jQuery.fx(
				z.el.get(0),
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'top'
			);
			if (z.type == 'close') {
				z.eh.custom(z.oldP.h,0);
				z.et.custom(z.oldP.top, z.oldP.top + z.oldP.h/2);
			} else {
				z.eh.custom(0, z.oldP.h);
				z.et.custom(z.oldP.top + z.oldP.h/2, z.oldP.top);
			}
		break;
		case 'horizontally':
			z.eh = new jQuery.fx(
				z.el.get(0),
				jQuery.speed(speed-15, z.easing, callback),
				'width'
			);
			z.et = new jQuery.fx(
				z.el.get(0),
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'left'
			);
			if (z.type == 'close') {
				z.eh.custom(z.oldP.w,0);
				z.et.custom(z.oldP.left, z.oldP.left + z.oldP.w/2);
			} else {
				z.eh.custom(0, z.oldP.w);
				z.et.custom(z.oldP.left + z.oldP.w/2, z.oldP.left);
			}
		break;
	}
};/**
 * Interface Elements for jQuery
 * FX - pulsate
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */
 
/**
 * @name Bounce
 * @description makes the element to pulsate
 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
 * @param Integer times how many times to pulsate
 * @param Function callback (optional) A function to be executed whenever the animation completes.
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.fn.Pulsate = function(speed, times, callback) {
	return this.queue('interfaceFX',function(){
		if (!jQuery.fxCheckTag(this)) {
			jQuery.dequeue(this, 'interfaceFX');
			return false;
		}
		var fx = new jQuery.fx.Pulsate(this, speed, times, callback);
		fx.pulse();
	});
};

jQuery.fx.Pulsate = function (el, speed, times, callback)
{	
	var z = this;
	z.times = times;
	z.cnt = 1;
	z.el = el;
	z.speed = speed;
	z.callback = callback;
	jQuery(z.el).show();
	z.pulse = function()
	{
		z.cnt ++;
		z.e = new jQuery.fx(
			z.el, 
			jQuery.speed(
				z.speed, 
				function(){
					z.ef = new jQuery.fx(
						z.el, 
						jQuery.speed(
							z.speed,
							function()
							{
								if (z.cnt <= z.times)
									z.pulse();
								else {
									jQuery.dequeue(z.el, 'interfaceFX');
									if (z.callback && z.callback.constructor == Function) {
										z.callback.apply(z.el);
									}
								}
							}
						), 
						'opacity'
					);
					z.ef.custom(0,1);
				}
			), 
			'opacity'
		);
		z.e.custom(1,0);
	};
};
/**
 * Interface Elements for jQuery
 * FX - scale/grow/shrink/puff
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */
/**
 * Applies a scallign animation to element
 */
jQuery.fn.extend(
	{
		/**
		 * @name Grow
		 * @description scales the element from 0 to intitial size
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		Grow : function(speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.Scale(this, speed, 1, 100, true, callback, 'grow', easing);
			});
		},
		
		/**
		 * @name Shrink
		 * @description scales the element from intitial size to 0
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		Shrink : function(speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.Scale(this, speed, 100, 1, true, callback, 'shrink', easing);
			});
		},
		
		/**
		 * @name Puff
		 * @description makes element to dispear by scalling to 150% and fading it out
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		Puff : function(speed, callback, easing) {
			return this.queue('interfaceFX',function(){
				var easing = easing || 'easeout';
				new jQuery.fx.Scale(this, speed, 100, 150, true, callback, 'puff', easing);
			});
		},
		
		/**
		 * @name Scale
		 * @description scales the element
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Integer from initial scalling procentage
		 * @param Integer to final scalling procentage
		 * @param Boolean reastore whatever to restore the initital scalling procentage when animation ends
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		Scale : function(speed, from, to, restore, callback, easing) {
			return this.queue('interfaceFX',function(){
				new jQuery.fx.Scale(this, speed, from, to, restore, callback, 'Scale', easing);
			});
		}
	}
);

jQuery.fx.Scale = function (e, speed, from, to, restore, callback, type, easing)
{
	if (!jQuery.fxCheckTag(e)) {
		jQuery.dequeue(e, 'interfaceFX');
		return false;
	}
	var z = this;
	z.el = jQuery(e);
	z.from = parseInt(from) || 100;
	z.to = parseInt(to) || 100;
	z.easing = typeof callback == 'string' ? callback : easing||null;
	z.callback = typeof callback == 'function' ? callback : null;
	z.duration = jQuery.speed(speed).duration;
	z.restore = restore|| null;
	z.oldP = jQuery.iUtil.getSize(e);
	z.oldStyle = {
		width: z.el.css('width'),
		height: z.el.css('height'),
		fontSize: z.el.css('fontSize')||'100%',
		position : z.el.css('position'),
		display : z.el.css('display'),
		top : z.el.css('top'),
		left : z.el.css('left'),
		overflow : z.el.css('overflow'),
		borderTopWidth : z.el.css('borderTopWidth'),
		borderRightWidth : z.el.css('borderRightWidth'),
		borderBottomWidth : z.el.css('borderBottomWidth'),
		borderLeftWidth : z.el.css('borderLeftWidth'),
		paddingTop : z.el.css('paddingTop'),
		paddingRight : z.el.css('paddingRight'),
		paddingBottom : z.el.css('paddingBottom'),
		paddingLeft : z.el.css('paddingLeft')
	};
	z.width = parseInt(z.oldStyle.width)||e.offsetWidth||0;
	z.height = parseInt(z.oldStyle.height)||e.offsetHeight||0;
	z.top = parseInt(z.oldStyle.top)||0;
	z.left = parseInt(z.oldStyle.left)||0;
	sizes = ['em','px','pt','%'];
	for(i in sizes) {
		if (z.oldStyle.fontSize.indexOf(sizes[i])>0) {
			z.fontUnit = sizes[i];
			z.fontSize = parseFloat(z.oldStyle.fontSize);
		}
		if (z.oldStyle.borderTopWidth.indexOf(sizes[i])>0) {
			z.borderTopUnit = sizes[i];
			z.borderTopSize = parseFloat(z.oldStyle.borderTopWidth)||0;
		}
		if (z.oldStyle.borderRightWidth.indexOf(sizes[i])>0) {
			z.borderRightUnit = sizes[i];
			z.borderRightSize = parseFloat(z.oldStyle.borderRightWidth)||0;
		}
		if (z.oldStyle.borderBottomWidth.indexOf(sizes[i])>0) {
			z.borderBottomUnit = sizes[i];
			z.borderBottomSize = parseFloat(z.oldStyle.borderBottomWidth)||0;
		}
		if (z.oldStyle.borderLeftWidth.indexOf(sizes[i])>0) {
			z.borderLeftUnit = sizes[i];
			z.borderLeftSize = parseFloat(z.oldStyle.borderLeftWidth)||0;
		}
		if (z.oldStyle.paddingTop.indexOf(sizes[i])>0) {
			z.paddingTopUnit = sizes[i];
			z.paddingTopSize = parseFloat(z.oldStyle.paddingTop)||0;
		}
		if (z.oldStyle.paddingRight.indexOf(sizes[i])>0) {
			z.paddingRightUnit = sizes[i];
			z.paddingRightSize = parseFloat(z.oldStyle.paddingRight)||0;
		}
		if (z.oldStyle.paddingBottom.indexOf(sizes[i])>0) {
			z.paddingBottomUnit = sizes[i];
			z.paddingBottomSize = parseFloat(z.oldStyle.paddingBottom)||0;
		}
		if (z.oldStyle.paddingLeft.indexOf(sizes[i])>0) {
			z.paddingLeftUnit = sizes[i];
			z.paddingLeftSize = parseFloat(z.oldStyle.paddingLeft)||0;
		}
	}
	
	
	if (z.oldStyle.position != 'relative' && z.oldStyle.position != 'absolute') {
		z.el.css('position', 'relative');
	}
	z.el.css('overflow', 'hidden');
	z.type = type;
	switch(z.type)
	{
		case 'grow':
			z.startTop = z.top + z.oldP.h/2;
			z.endTop = z.top;
			z.startLeft = z.left + z.oldP.w/2;
			z.endLeft = z.left;
			break;
		case 'shrink':
			z.endTop = z.top + z.oldP.h/2;
			z.startTop = z.top;
			z.endLeft = z.left + z.oldP.w/2;
			z.startLeft = z.left;
			break;
		case 'puff':
			z.endTop = z.top - z.oldP.h/4;
			z.startTop = z.top;
			z.endLeft = z.left - z.oldP.w/4;
			z.startLeft = z.left;
			break;
	}
	z.firstStep = false;
	z.t=(new Date).getTime();
	z.clear = function(){clearInterval(z.timer);z.timer=null;};
	z.step = function(){
		if (z.firstStep == false) {
			z.el.show();
			z.firstStep = true;
		}
		var t = (new Date).getTime();
		var n = t - z.t;
		var p = n / z.duration;
		if (t >= z.duration+z.t) {
			setTimeout(
				function(){
						o = 1;	
					if (z.type) {
						t = z.endTop;
						l = z.endLeft;
						if (z.type == 'puff')
							o = 0;
					}
					z.zoom(z.to, l, t, true, o);
				},
				13
			);
			z.clear();
		} else {
			o = 1;
			if (!jQuery.easing || !jQuery.easing[z.easing]) {
				s = ((-Math.cos(p*Math.PI)/2) + 0.5) * (z.to-z.from) + z.from;
			} else {
				s = jQuery.easing[z.easing](p, n, z.from, (z.to-z.from), z.duration);
			}
			if (z.type) {
				if (!jQuery.easing || !jQuery.easing[z.easing]) {
					t = ((-Math.cos(p*Math.PI)/2) + 0.5) * (z.endTop-z.startTop) + z.startTop;
					l = ((-Math.cos(p*Math.PI)/2) + 0.5) * (z.endLeft-z.startLeft) + z.startLeft;
					if (z.type == 'puff')
						o = ((-Math.cos(p*Math.PI)/2) + 0.5) * (-0.9999) + 0.9999;
				} else {
					t = jQuery.easing[z.easing](p, n, z.startTop, (z.endTop-z.startTop), z.duration);
					l = jQuery.easing[z.easing](p, n, z.startLeft, (z.endLeft-z.startLeft), z.duration);
					if (z.type == 'puff')
						o = jQuery.easing[z.easing](p, n, 0.9999, -0.9999, z.duration);
				}
			}
			z.zoom(s, l, t, false, o);
		}
	};
	z.timer=setInterval(function(){z.step();},13);
	z.zoom = function(percent, left, top, finish, opacity)
	{
		z.el
			.css('height', z.height * percent/100 + 'px')
			.css('width', z.width * percent/100 + 'px')
			.css('left', left + 'px')
			.css('top', top + 'px')
			.css('fontSize', z.fontSize * percent /100 + z.fontUnit);
		if (z.borderTopSize)
			z.el.css('borderTopWidth', z.borderTopSize * percent /100 + z.borderTopUnit);
		if (z.borderRightSize)
			z.el.css('borderRightWidth', z.borderRightSize * percent /100 + z.borderRightUnit);
		if (z.borderBottomSize)
			z.el.css('borderBottomWidth', z.borderBottomSize * percent /100 + z.borderBottomUnit);
		if (z.borderLeftSize)
			z.el.css('borderLeftWidth', z.borderLeftSize * percent /100 + z.borderLeftUnit);
		if (z.paddingTopSize)
			z.el.css('paddingTop', z.paddingTopSize * percent /100 + z.paddingTopUnit);
		if (z.paddingRightSize)
			z.el.css('paddingRight', z.paddingRightSize * percent /100 + z.paddingRightUnit);
		if (z.paddingBottomSize)
			z.el.css('paddingBottom', z.paddingBottomSize * percent /100 + z.paddingBottomUnit);
		if (z.paddingLeftSize)
			z.el.css('paddingLeft', z.paddingLeftSize * percent /100 + z.paddingLeftUnit);
		if (z.type == 'puff') {
			if (window.ActiveXObject)
				z.el.get(0).style.filter = "alpha(opacity=" + opacity*100 + ")";
			z.el.get(0).style.opacity = opacity;
		}
		if (finish){
			if (z.restore){
				z.el.css(z.oldStyle);
			}
			if (z.type == 'shrink' || z.type == 'puff'){
				z.el.css('display', 'none');
				if (z.type == 'puff') {
					if (window.ActiveXObject)
						z.el.get(0).style.filter = "alpha(opacity=" + 100 + ")";
					z.el.get(0).style.opacity = 1;
				}
			}else 
				z.el.css('display', 'block');
			if (z.callback)
				z.callback.apply(z.el.get(0));
			
			jQuery.dequeue(z.el.get(0), 'interfaceFX');
		}
	};
};/**
 * Interface Elements for jQuery
 * FX - scroll to
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */
/**
 * Applies a scrolling effect to document until the element gets into viewport
 */
jQuery.fn.extend (
	{
		/**
		 * @name ScrollTo
		 * @description scrolls the document until the lement gets into viewport
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param String axis (optional) whatever to scroll on vertical, horizontal or both axis ['vertical'|'horizontal'|null]
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		ScrollTo : function(speed, axis, easing) {
			o = jQuery.speed(speed);
			return this.queue('interfaceFX',function(){
				new jQuery.fx.ScrollTo(this, o, axis, easing);
			});
		},
		/**
		 * @name ScrollToAnchors
		 * @description all links to '#elementId' will animate scroll
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param String axis (optional) whatever to scroll on vertical, horizontal or both axis ['vertical'|'horizontal'|null]
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		/*inspired by David Maciejewski www.macx.de*/
		ScrollToAnchors : function(speed, axis, easing) {
			return this.each(
				function()
				{
					jQuery('a[@href*="#"]', this).click(
						function(e)
						{
							parts = this.href.split('#');
							jQuery('#' + parts[1]).ScrollTo(speed, axis, easing);
							return false;
						}
					);
				}
			)
		}
	}
);

jQuery.fx.ScrollTo = function (e, o, axis, easing)
{
	var z = this;
	z.o = o;
	z.e = e;
	z.axis = /vertical|horizontal/.test(axis) ? axis : false;
	z.easing = easing;
	p = jQuery.iUtil.getPosition(e);
	s = jQuery.iUtil.getScroll();
	z.clear = function(){clearInterval(z.timer);z.timer=null;jQuery.dequeue(z.e, 'interfaceFX');};
	z.t=(new Date).getTime();
	s.h = s.h > s.ih ? (s.h - s.ih) : s.h;
	s.w = s.w > s.iw ? (s.w - s.iw) : s.w;
	z.endTop = p.y > s.h ? s.h : p.y;
	z.endLeft = p.x > s.w ? s.w : p.x;
	z.startTop = s.t;
	z.startLeft = s.l;
	z.step = function(){
		var t = (new Date).getTime();
		var n = t - z.t;
		var p = n / z.o.duration;
		if (t >= z.o.duration+z.t) {
			z.clear();
			setTimeout(function(){z.scroll(z.endTop, z.endLeft)},13);
		} else {
			if (!z.axis || z.axis == 'vertical') {
				if (!jQuery.easing || !jQuery.easing[z.easing]) {
					st = ((-Math.cos(p*Math.PI)/2) + 0.5) * (z.endTop-z.startTop) + z.startTop;
				} else {
					st = jQuery.easing[z.easing](p, n, z.startTop, (z.endTop - z.startTop), z.o.duration);
				}
			} else {
				st = z.startTop;
			}
			if (!z.axis || z.axis == 'horizontal') {
				if (!jQuery.easing || !jQuery.easing[z.easing]) {
					sl = ((-Math.cos(p*Math.PI)/2) + 0.5) * (z.endLeft-z.startLeft) + z.startLeft;
				} else {
					sl = jQuery.easing[z.easing](p, n, z.startLeft, (z.endLeft - z.startLeft), z.o.duration);
				}
			} else {
				sl = z.startLeft;
			}
			z.scroll(st, sl);
		}
	};
	z.scroll = function (t, l){window.scrollTo(l, t);};
	z.timer=setInterval(function(){z.step();},13);
};/**
 * Interface Elements for jQuery
 * FX - shake
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * @name Shake
 * @description makes the element to shake
 * @param Integer times how many tomes to shake the element
 * @param Function callback (optional) A function to be executed whenever the animation completes.
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.fn.Shake = function (times, callback) {
	return this.queue('interfaceFX',function(){
		if (!jQuery.fxCheckTag(this)) {
			jQuery.dequeue(this, 'interfaceFX');
			return false;
		}
		var e = new jQuery.fx.Shake(this, times, callback);
		e.shake();
	});
};
jQuery.fx.Shake = function (e, times, callback)
{
	var z = this;
	z.el = jQuery(e);
	z.el.show();
	z.times = parseInt(times)||3;
	z.callback = callback;
	z.cnt = 1;
	z.oldStyle = {};
	z.oldStyle.position = z.el.css('position');
	z.oldStyle.top = parseInt(z.el.css('top'))||0;
	z.oldStyle.left = parseInt(z.el.css('left'))||0;
	
	if (z.oldStyle.position != 'relative' && z.oldStyle.position != 'absolute') {
		z.el.css('position', 'relative');
	}
	
	z.shake = function ()
	{
		z.cnt ++;
		
		z.e = new jQuery.fx(
			z.el.get(0), 
			{
				duration: 60,
				complete : function ()
				{
					z.e = new jQuery.fx(
						z.el.get(0), 
						 {
							 duration: 60,
							 complete : function ()
							 {
								z.e = new jQuery.fx(
									e,
									{
										duration: 60, 
										complete: function(){
											if (z.cnt <= z.times)
												z.shake();
											else {
												z.el.css('position', z.oldStyle.position).css('top', z.oldStyle.top + 'px').css('left', z.oldStyle.left + 'px');
												jQuery.dequeue(z.el.get(0), 'interfaceFX');
												if (z.callback && z.callback.constructor == Function) {
													z.callback.apply(z.el.get(0));
												}
											}
										}
									},
									'left'
								);
								z.e.custom (z.oldStyle.left-20, z.oldStyle.left);
							 }
						},
						'left'
					);
					z.e.custom (z.oldStyle.left+20, z.oldStyle.left-20);
				}
			},
			'left'
		);
		z.e.custom (z.oldStyle.left, z.oldStyle.left+20);
	};
		
};/**
 * Interface Elements for jQuery
 * FX - slide
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Slides the element
 */
jQuery.fn.extend(
	{
		/**
		 * @name SlideInUp
		 * @description slides the element in up
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideInUp : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'up', 'in', easing);
			});
		},
		
		/**
		 * @name SlideOutUp
		 * @description slides the element out up
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideOutUp : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'up', 'out', easing);
			});
		},
		
		/**
		 * @name SlideToggleUp
		 * @description slides the element in/out up
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideToggleUp : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'up', 'toggle', easing);
			});
		},
		
		/**
		 * @name SlideInDown
		 * @description slides the element in down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideInDown : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'down', 'in', easing);
			});
		},
		
		/**
		 * @name SlideOutDown
		 * @description slides the element out down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideOutDown : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'down', 'out', easing);
			});
		},
		
		/**
		 * @name SlideToggleDown
		 * @description slides the element in/out down
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideToggleDown : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'down', 'toggle', easing);
			});
		},
		
		/**
		 * @name SlideInLeft
		 * @description slides the element in left
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideInLeft : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'left', 'in', easing);
			});
		},
		
		/**
		 * @name SlideOutLeft
		 * @description slides the element out left
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideOutLeft :  function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'left', 'out', easing);
			});
		},
		
		/**
		 * @name SlideToggleLeft
		 * @description slides the element in/out left
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideToggleLeft : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'left', 'toggle', easing);
			});
		},
		
		/**
		 * @name SlideInRight
		 * @description slides the element in right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideInRight : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'right', 'in', easing);
			});
		},
		
		/**
		 * @name SlideOutRight
		 * @description slides the element out right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideOutRight : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'right', 'out', easing);
			});
		},
		
		/**
		 * @name SlideToggleRight
		 * @description slides the element in/out right
		 * @param Mixed speed animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
		 * @param Function callback (optional) A function to be executed whenever the animation completes.
		 * @param String easing (optional) The name of the easing effect that you want to use.
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SlideToggleRight : function (speed,callback, easing)
		{
			return this.queue('interfaceFX', function(){
				new jQuery.fx.slide(this, speed, callback, 'right', 'toggle', easing);
			});
		}
	}
);

jQuery.fx.slide = function(e, speed, callback, direction, type, easing)
{
	if (!jQuery.fxCheckTag(e)) {
		jQuery.dequeue(e, 'interfaceFX');
		return false;
	}
	var z = this;
	z.el = jQuery(e);
	z.easing = typeof callback == 'string' ? callback : easing||null;
	z.callback = typeof callback == 'function' ? callback : null;
	if ( type == 'toggle') {
		type = z.el.css('display') == 'none' ? 'in' : 'out';
	}
	if (!e.ifxFirstDisplay)
		e.ifxFirstDisplay = z.el.css('display');
	z.el.show();
	
	z.speed = speed;
	z.fx = jQuery.fx.buildWrapper(e);
	
	z.type = type;
	z.direction = direction;
	z.complete = function()
	{
		if(z.type == 'out')
			z.el.css('visibility', 'hidden');
		jQuery.fx.destroyWrapper(z.fx.wrapper.get(0), z.fx.oldStyle);
		if(z.type == 'in'){
			z.el.css('display', z.el.get(0).ifxFirstDisplay == 'none' ? 'block' : z.el.get(0).ifxFirstDisplay);
		} else {
			z.el.css('display', 'none');
			z.el.css('visibility', 'visible');
		}
		if (z.callback && z.callback.constructor == Function) {
			z.callback.apply(z.el.get(0));
		}
		jQuery.dequeue(z.el.get(0), 'interfaceFX');
	};
	switch (z.direction) {
		case 'up':
			z.ef = new jQuery.fx(
				z.el.get(0), 
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'top'
			);
			z.efx = new jQuery.fx(
				z.fx.wrapper.get(0), 
				jQuery.speed(
					z.speed,
					z.easing
				),
				'height'
			);
			if (z.type == 'in') {
				z.ef.custom (-z.fx.oldStyle.sizes.hb, 0);
				z.efx.custom(0, z.fx.oldStyle.sizes.hb);
			} else {
				z.ef.custom (0, -z.fx.oldStyle.sizes.hb);
				z.efx.custom (z.fx.oldStyle.sizes.hb, 0);
			}
		break;
		case 'down':
			z.ef = new jQuery.fx(
				z.el.get(0), 
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'top'
			);
			if (z.type == 'in') {
				z.ef.custom (z.fx.oldStyle.sizes.hb, 0);
			} else {
				z.ef.custom (0, z.fx.oldStyle.sizes.hb);
			}
		break;
		case 'left':
			z.ef = new jQuery.fx(
				z.el.get(0), 
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'left'
			);
			z.efx = new jQuery.fx(
				z.fx.wrapper.get(0), 
				jQuery.speed(
					z.speed,
					z.easing
				),
				'width'
			);
			if (z.type == 'in') {
				z.ef.custom (-z.fx.oldStyle.sizes.wb, 0);
				z.efx.custom (0, z.fx.oldStyle.sizes.wb);
			} else {
				z.ef.custom (0, -z.fx.oldStyle.sizes.wb);
				z.efx.custom (z.fx.oldStyle.sizes.wb, 0);
			}
		break;
		case 'right':
			z.ef = new jQuery.fx(
				z.el.get(0), 
				jQuery.speed(
					z.speed,
					z.easing,
					z.complete
				),
				'left'
			);
			if (z.type == 'in') {
				z.ef.custom (z.fx.oldStyle.sizes.wb, 0);
			} else {
				z.ef.custom (0, z.fx.oldStyle.sizes.wb);
			}
		break;
	}
};
/**
 * Interface Elements for jQuery
 * FX - transfer
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

jQuery.transferHelper = null;
/**
 * 
 * @name TransferTo
 * @description Animates an new build element to simulate a transfer action from one element to other
 * @param Hash hash A hash of parameters
 * @option Mixed to DOMElement or element ID to transfer to
 * @option String className CSS class to apply to transfer element
 * @option String duration animation speed, integer for miliseconds, string ['slow' | 'normal' | 'fast']
 * @option Function callback (optional) A function to be executed whenever the animation completes.
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.fn.TransferTo = function(o)
{
	return this.queue('interfaceFX', function(){
		new jQuery.fx.itransferTo(this, o);
	});
};
jQuery.fx.itransferTo = function(e, o)
{
	
	if(jQuery.transferHelper == null)
	{
		jQuery('body', document).append('<div id="transferHelper"></div>');
		jQuery.transferHelper = jQuery('#transferHelper');
	}
	jQuery.transferHelper.css('display', 'block').css('position', 'absolute');
	
	var z = this;
	z.el = jQuery(e);
	if(!o || !o.to) {
		return;
	}
	
	if (o.to.constructor == String && document.getElementById(o.to)) {
		o.to = document.getElementById(o.to);
	} else if ( !o.to.childNodes ) {
		return;
	}
	
	if (!o.duration) {
		o.duration = 500;
	}
	z.duration = o.duration;
	z.to = o.to;
	z.classname = o.className;
	z.complete = o.complete;
	if (z.classname) {
		jQuery.transferHelper.addClass(z.classname);
	}
	z.diffWidth = 0;
	z.diffHeight = 0;
	
	if(jQuery.boxModel) {
		z.diffWidth = (parseInt(jQuery.transferHelper.css('borderLeftWidth')) || 0 )
					+ (parseInt(jQuery.transferHelper.css('borderRightWidth')) || 0)
					+ (parseInt(jQuery.transferHelper.css('paddingLeft')) || 0)
					+ (parseInt(jQuery.transferHelper.css('paddingRight')) || 0);
		z.diffHeight = (parseInt(jQuery.transferHelper.css('borderTopWidth')) || 0 )
					+ (parseInt(jQuery.transferHelper.css('borderBottomWidth')) || 0)
					+ (parseInt(jQuery.transferHelper.css('paddingTop')) || 0)
					+ (parseInt(jQuery.transferHelper.css('paddingBottom')) || 0);
	}
	z.start = jQuery.extend(
		jQuery.iUtil.getPosition(z.el.get(0)),
		jQuery.iUtil.getSize(z.el.get(0))
	);
	z.end = jQuery.extend(
		jQuery.iUtil.getPosition(z.to),
		jQuery.iUtil.getSize(z.to)
	);
	z.start.wb -= z.diffWidth;
	z.start.hb -= z.diffHeight;
	z.end.wb -= z.diffWidth;
	z.end.hb -= z.diffHeight;
	z.callback = o.complete;

	// Execute the transfer
	jQuery.transferHelper
		.css('width', z.start.wb + 'px')
		.css('height', z.start.hb + 'px')
		.css('top', z.start.y + 'px')
		.css('left', z.start.x + 'px')
		.animate(
			{
				top: z.end.y,
				left: z.end.x,
				width: z.end.wb,
				height: z.end.hb
			},
			z.duration,
			function()
			{
				// Set correct classname
				if(z.classname)
					jQuery.transferHelper.removeClass(z.classname);
				jQuery.transferHelper.css('display', 'none');
	
				// Callback
				if (z.complete && z.complete.constructor == Function) {
					z.complete.apply(z.el.get(0), [z.to]);
				}
				// Done
				jQuery.dequeue(z.el.get(0), 'interfaceFX');
			}
		);
};/**
 * Interface Elements for jQuery
 * ImageBox
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 */

/**
 * This a jQuery equivalent for Lightbox2. Alternative to image popups that will display images in an overlay. All links that have attribute 'rel' starting with 'imagebox' and link to an image will display the image inside the page. Galleries can by build buy giving the value 'imagebox-galname' to attribute 'rel'. Attribute 'title' will be used as caption.
 * Keyboard navigation:
 *  -  next image: arrow right, page down, 'n' key, space
 *  -  previous image: arrow left, page up, 'p' key, backspace
 *  -  close: escape
 *
 * CSS
 *	#ImageBoxOverlay
 *	{
 *		background-color: #000;
 *	}
 *	#ImageBoxCaption
 *	{
 *		background-color: #F4F4EC;
 *	}
 *	#ImageBoxContainer
 *	{
 *		width: 250px;
 *		height: 250px;
 *		background-color: #F4F4EC;
 *	}
 *	#ImageBoxCaptionText
 *	{
 *		font-weight: bold;
 *		padding-bottom: 5px;
 *		font-size: 13px;
 *		color: #000;
 *	}
 *	#ImageBoxCaptionImages
 *	{
 *		margin: 0;
 *	}
 *	#ImageBoxNextImage
 *	{
 *		background-image: url(images/imagebox/spacer.gif);
 *		background-color: transparent;
 *	}
 *	#ImageBoxPrevImage
 *	{
 *		background-image: url(images/imagebox/spacer.gif);
 *		background-color: transparent;
 *	}
 *	#ImageBoxNextImage:hover
 *	{
 *		background-image: url(images/imagebox/next_image.jpg);
 *		background-repeat:	no-repeat;
 *		background-position: right top;
 *	}
 *	#ImageBoxPrevImage:hover
 *	{
 *		background-image: url(images/imagebox/prev_image.jpg);
 *		background-repeat:	no-repeat;
 *		background-position: left bottom;
 *	}
 * 
 * @name Imagebox
 * @description This a jQuery equivalent for Lightbox2. Alternative to image popups that will display images in an overlay. All links that have attribute 'rel' starting with 'imagebox' and link to an image will display the image inside the page. Galleries can by build buy giving the value 'imagebox-galname' to attribute 'rel'. Attribute 'title' will be used as caption.
 * @param Hash hash A hash of parameters
 * @option Integer border border width
 * @option String loaderSRC path to loading image
 * @option String closeHTML path to close overlay image
 * @option Float overlayOpacity opacity for overlay
 * @option String textImage when a galalry it is build then the iteration is displayed
 * @option String textImageFrom when a galalry it is build then the iteration is displayed
 * @option Integer fadeDuration fade duration in miliseconds
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.ImageBox = {
	options : {
		border				: 10,
		loaderSRC			: 'images/loading.gif',
		closeHTML			: '<img src="images/close.jpg" />',
		overlayOpacity		: 0.8,
		textImage			: 'Showing image',
		textImageFrom		: 'from',
		fadeDuration		: 400
	},
	imageLoaded : false,
	firstResize : false,
	currentRel : null,
	animationInProgress : false,
	opened : false,
	
	keyPressed : function(event)
	{
		if(!jQuery.ImageBox.opened || jQuery.ImageBox.animationInProgress)
			return;
		var pressedKey = event.charCode || event.keyCode || -1;
		switch (pressedKey)
		{
			//end
			case 35:
				if (jQuery.ImageBox.currentRel)
					jQuery.ImageBox.start(null, jQuery('a[@rel=' + jQuery.ImageBox.currentRel+ ']:last').get(0));
			break;
			//home
			case 36:
				if (jQuery.ImageBox.currentRel)
					jQuery.ImageBox.start(null, jQuery('a[@rel=' + jQuery.ImageBox.currentRel+ ']:first').get(0));
			break;
			//left
			case 37:
			//backspace
			case 8:
			//page up
			case 33:
			//p
			case 80:
			case 112:
				var prevEl = jQuery('#ImageBoxPrevImage');
				if(prevEl.get(0).onclick != null) {
					prevEl.get(0).onclick.apply(prevEl.get(0));
				}
			break;
			//up
			case 38:
			break;
			//right
			case 39:
			//page down
			case 34:
			//space
			case 32:
			//n
			case 110:
			case 78:
				var nextEl = jQuery('#ImageBoxNextImage');
				if(nextEl.get(0).onclick != null) {
					nextEl.get(0).onclick.apply(nextEl.get(0));
				}
			break;
			//down;
			case 40:
			break;
			//escape
			case 27:
				jQuery.ImageBox.hideImage();
			break;
		}
	},
	
	init : function(options)
	{
		if (options)
			jQuery.extend(jQuery.ImageBox.options, options);
		if (window.event) {
			jQuery('body',document).bind('keyup', jQuery.ImageBox.keyPressed);
		} else {
			jQuery(document).bind('keyup', jQuery.ImageBox.keyPressed);
		}
		jQuery('a').each(
			function()
			{
				el 				= jQuery(this);
				relAttr 		= el.attr('rel')||'';
				hrefAttr 		= el.attr('href')||'';
				imageTypes 		= /\.jpg|\.jpeg|\.png|\.gif|\.bmp/g;
				if (hrefAttr.toLowerCase().match(imageTypes) != null && relAttr.toLowerCase().indexOf('imagebox') == 0) {
					el.bind('click', jQuery.ImageBox.start);
				}
			}
		);
		if (jQuery.browser.msie) {
			iframe = document.createElement('iframe');
			jQuery(iframe)
				.attr(
					{
						id			: 'ImageBoxIframe',
						src			: 'javascript:false;',
						frameborder	: 'no',
						scrolling	: 'no'
					}
				)
				.css (
					{
						display		: 'none',
						position	: 'absolute',
						top			: '0',
						left		: '0',
						filter		: 'progid:DXImageTransform.Microsoft.Alpha(opacity=0)'
					}
				);
			jQuery('body').append(iframe);
		}
		
		overlay	= document.createElement('div');
		jQuery(overlay)
			.attr('id', 'ImageBoxOverlay')
			.css(
				{
					position	: 'absolute',
					display		: 'none',
					top			: '0',
					left		: '0',
					opacity		: 0
				}
			)
			.append(document.createTextNode(' '))
			.bind('click', jQuery.ImageBox.hideImage);
		
		captionText = document.createElement('div');
		jQuery(captionText)
			.attr('id', 'ImageBoxCaptionText')
			.css(
				{
					paddingLeft		: jQuery.ImageBox.options.border + 'px'
				}
			)
			.append(document.createTextNode(' '));
			
		captionImages = document.createElement('div');
		jQuery(captionImages)
			.attr('id', 'ImageBoxCaptionImages')
			.css(
				{
					paddingLeft		: jQuery.ImageBox.options.border + 'px',
					paddingBottom	: jQuery.ImageBox.options.border + 'px'
				}
			)
			.append(document.createTextNode(' '));
			
		closeEl = document.createElement('a');
		jQuery(closeEl)
			.attr(
				{
					id			: 'ImageBoxClose',
					href		: '#'
				}
			)
			.css(
				{
					position	: 'absolute',
					right		: jQuery.ImageBox.options.border + 'px',
					top			: '0'
				}
			)
			.append(jQuery.ImageBox.options.closeHTML)
			.bind('click', jQuery.ImageBox.hideImage);
			
		captionEl = document.createElement('div');
		jQuery(captionEl)
			.attr('id', 'ImageBoxCaption')
			.css(
				{
					position	: 'relative',
					textAlign	: 'left',
					margin		: '0 auto',
					zIndex		: 1
				}
			)
			.append(captionText)
			.append(captionImages)
			.append(closeEl);
		
		loader = document.createElement('img');
		loader.src = jQuery.ImageBox.options.loaderSRC;
		jQuery(loader)
			.attr('id', 'ImageBoxLoader')
			.css(
				{
					position	: 'absolute'
				}
			);
			
		prevImage = document.createElement('a');
		jQuery(prevImage)
			.attr(
				{
					id			: 'ImageBoxPrevImage',
					href		: '#'
				}
			)
			.css(
				{
					position		: 'absolute',
					display			: 'none',
					overflow		: 'hidden',
					textDecoration	: 'none'
				}
			)
			.append(document.createTextNode(' '));
			
		nextImage = document.createElement('a');
		jQuery(nextImage)
			.attr(
				{
					id			: 'ImageBoxNextImage',
					href		: '#'
				}
			)
			.css(
				{
					position		: 'absolute',
					overflow		: 'hidden',
					textDecoration	: 'none'
				}
			)
			.append(document.createTextNode(' '));
		
		container = document.createElement('div');
		jQuery(container)
			.attr('id', 'ImageBoxContainer')
			.css(
				{
					display		: 'none',
					position	: 'relative',
					overflow	: 'hidden',
					textAlign	: 'left',
					margin		: '0 auto',
					top			: '0',
					left		: '0',
					zIndex		: 2
				}
			)
			.append([loader, prevImage, nextImage]);
		
		outerContainer = document.createElement('div');
		jQuery(outerContainer)
			.attr('id', 'ImageBoxOuterContainer')
			.css(
				{
					display		: 'none',
					position	: 'absolute',
					overflow	: 'hidden',
					top			: '0',
					left		: '0',
					textAlign	: 'center',
					backgroundColor : 'transparent',
					lineHeigt	: '0'
				}
			)
			.append([container,captionEl]);
		
		jQuery('body')
			.append(overlay)
			.append(outerContainer);
	},
	
	start : function(e, elm)
	{
		el = elm ? jQuery(elm) : jQuery(this);
		linkRel =  el.attr('rel');
		var totalImages, iteration, prevImage, nextImage;
		if (linkRel != 'imagebox') {
			jQuery.ImageBox.currentRel = linkRel;
			gallery = jQuery('a[@rel=' + linkRel + ']');
			totalImages = gallery.size();
			iteration = gallery.index(elm ? elm : this);
			prevImage = gallery.get(iteration - 1);
			nextImage = gallery.get(iteration + 1);
		}
		imageSrc =  el.attr('href');
		captionText = el.attr('title');
		pageSize = jQuery.iUtil.getScroll();
		overlay = jQuery('#ImageBoxOverlay');
		if (!jQuery.ImageBox.opened) {
			jQuery.ImageBox.opened = true;
			if (jQuery.browser.msie) {
				jQuery('#ImageBoxIframe')
					.css ('height', Math.max(pageSize.ih,pageSize.h) + 'px')
					.css ('width', Math.max(pageSize.iw,pageSize.w) + 'px')
					.show();
			}
			overlay
				.css ('height', Math.max(pageSize.ih,pageSize.h) + 'px')
				.css ('width', Math.max(pageSize.iw,pageSize.w) + 'px')
				.show()
				.fadeTo( 
					300,
					jQuery.ImageBox.options.overlayOpacity,
					function()
					{
						jQuery.ImageBox.loadImage(
							imageSrc, 
							captionText, 
							pageSize, 
							totalImages, 
							iteration,
							prevImage,
							nextImage
						);
					}
				);
			jQuery('#ImageBoxOuterContainer').css ('width', Math.max(pageSize.iw,pageSize.w) + 'px');
		} else {
			jQuery('#ImageBoxPrevImage').get(0).onclick = null;
			jQuery('#ImageBoxNextImage').get(0).onclick = null;
			jQuery.ImageBox.loadImage(
				imageSrc, 
				captionText, 
				pageSize, 
				totalImages, 
				iteration,
				prevImage,
				nextImage
			);
		}
		return false;
	},
		
	loadImage : function(imageSrc, captiontext, pageSize, totalImages, iteration, prevImage, nextImage)
	{
		jQuery('#ImageBoxCurrentImage').remove();
		prevImageEl = jQuery('#ImageBoxPrevImage');
		prevImageEl.hide();
		nextImageEl = jQuery('#ImageBoxNextImage');
		nextImageEl.hide();
		loader = jQuery('#ImageBoxLoader');
		container = jQuery('#ImageBoxContainer');
		outerContainer = jQuery('#ImageBoxOuterContainer');
		captionEl = jQuery('#ImageBoxCaption').css('visibility', 'hidden');
		jQuery('#ImageBoxCaptionText').html(captionText);
		jQuery.ImageBox.animationInProgress = true;
		if (totalImages)
			jQuery('#ImageBoxCaptionImages').html(
				jQuery.ImageBox.options.textImage 
				+ ' ' + (iteration + 1) + ' '
				+ jQuery.ImageBox.options.textImageFrom  
				+ ' ' + totalImages
			);
		if (prevImage) {
			prevImageEl.get(0).onclick = function()
			{
				this.blur();
				jQuery.ImageBox.start(null, prevImage);
				return false;
			};
		}
		if (nextImage) {
			nextImageEl.get(0).onclick =function()
			{
				this.blur();
				jQuery.ImageBox.start(null, nextImage);
				return false;
			};
		}
		loader.show();
		containerSize = jQuery.iUtil.getSize(container.get(0));
		containerW = Math.max(containerSize.wb, loader.get(0).width + jQuery.ImageBox.options.border * 2);
		containerH = Math.max(containerSize.hb, loader.get(0).height + jQuery.ImageBox.options.border * 2);
		loader
			.css(
				{
					left	: (containerW - loader.get(0).width)/2 + 'px',
					top		: (containerH - loader.get(0).height)/2 + 'px'
				}
			);
		container
			.css(
				{
					width	: containerW + 'px',
					height	: containerH + 'px'
				}
			)
			.show();
		clientSize = jQuery.iUtil.getClient();
		outerContainer
			.css('top', pageSize.t +  (clientSize.h / 15) + 'px');
		if (outerContainer.css('display') == 'none') {
			outerContainer
				.show()
				.fadeIn(
					jQuery.ImageBox.options.fadeDuration
				);
		}
		imageEl = new Image;
		jQuery(imageEl)
			.attr('id', 'ImageBoxCurrentImage')
			.bind('load', 
			function()
			{
				containerW = imageEl.width + jQuery.ImageBox.options.border * 2;
				containerH = imageEl.height + jQuery.ImageBox.options.border * 2;
				loader.hide();
				container.animate(
					{
						height		: containerH
					},
					containerSize.hb != containerH ? jQuery.ImageBox.options.fadeDuration : 1,
					function()
					{
						container.animate(
							{
								width		: containerW
							},
							containerSize.wb != containerW ? jQuery.ImageBox.options.fadeDuration : 1,
							function()
							{
								container.prepend(imageEl);
								jQuery(imageEl)
									.css(
										{
											position	: 'absolute',
											left		: jQuery.ImageBox.options.border + 'px',
											top			: jQuery.ImageBox.options.border + 'px'
										}
									)
									.fadeIn(
										jQuery.ImageBox.options.fadeDuration,
										function()
										{
											captionSize = jQuery.iUtil.getSize(captionEl.get(0));
											if (prevImage) {
												prevImageEl
													.css(
														{
															left	: jQuery.ImageBox.options.border + 'px',
															top		: jQuery.ImageBox.options.border + 'px',
															width	: containerW/2 - jQuery.ImageBox.options.border * 3 + 'px',
															height	: containerH - jQuery.ImageBox.options.border * 2 + 'px'
														}
													)
													.show();
											}
											if (nextImage) {
												nextImageEl
													.css(
														{
															left	: containerW/2 + jQuery.ImageBox.options.border * 2 + 'px',
															top		: jQuery.ImageBox.options.border + 'px',
															width	: containerW/2 - jQuery.ImageBox.options.border * 3 + 'px',
															height	: containerH - jQuery.ImageBox.options.border * 2 + 'px'
														}
													)
													.show();
											}
											captionEl
												.css(
													{
														width		: containerW + 'px',
														top			: - captionSize.hb + 'px',
														visibility	: 'visible'
													}
												)
												.animate(
													{
														top		: -1
													},
													jQuery.ImageBox.options.fadeDuration,
													function()
													{
														jQuery.ImageBox.animationInProgress = false;
													}
												);
										}
									);
							}
						);
					}
				);
			}
		);
		imageEl.src = imageSrc;
			
	},
	
	hideImage : function()
	{
		jQuery('#ImageBoxCurrentImage').remove();
		jQuery('#ImageBoxOuterContainer').hide();
		jQuery('#ImageBoxCaption').css('visibility', 'hidden');
		jQuery('#ImageBoxOverlay').fadeTo(
			300, 
			0, 
			function(){
				jQuery(this).hide();
				if (jQuery.browser.msie) {
					jQuery('#ImageBoxIframe').hide();
				}
			}
		);
		jQuery('#ImageBoxPrevImage').get(0).onclick = null;
		jQuery('#ImageBoxNextImage').get(0).onclick = null;
		jQuery.ImageBox.currentRel = null;
		jQuery.ImageBox.opened = false;
		jQuery.ImageBox.animationInProgress = false;
		return false;
	}
};/**
 * Interface Elements for jQuery
 * Resizable
 *
 * http://interface.eyecon.ro
 *
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt)
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 *
 */

jQuery.iResize = {
	resizeElement: null,
	resizeDirection: null,
	dragged: null,
	pointer: null,
	sizes: null,
	position: null,
	/**
	 * internal: Start function
	 */
	startDrag: function(e) {
		jQuery.iResize.dragged = (this.dragEl) ? this.dragEl: this;
		jQuery.iResize.pointer = jQuery.iUtil.getPointer(e);

		// Save original size
		jQuery.iResize.sizes = {
			width: parseInt(jQuery(jQuery.iResize.dragged).css('width')) || 0,
			height: parseInt(jQuery(jQuery.iResize.dragged).css('height')) || 0
		};

		// Save original position
		jQuery.iResize.position = {
			top: parseInt(jQuery(jQuery.iResize.dragged).css('top')) || 0,
			left: parseInt(jQuery(jQuery.iResize.dragged).css('left')) || 0
		};

		// Assign event handlers
		jQuery(document)
			.bind('mousemove', jQuery.iResize.moveDrag)
			.bind('mouseup', jQuery.iResize.stopDrag);

		// Callback?
		if (typeof jQuery.iResize.dragged.resizeOptions.onDragStart === 'function') {
			jQuery.iResize.dragged.resizeOptions.onDragStart.apply(jQuery.iResize.dragged);
		}
		return false;
	},
	/**
	 * internal: Stop function
	 */
	stopDrag: function(e) {
		// Unbind event handlers
		jQuery(document)
			.unbind('mousemove', jQuery.iResize.moveDrag)
			.unbind('mouseup', jQuery.iResize.stopDrag);

		// Callback?
		if (typeof jQuery.iResize.dragged.resizeOptions.onDragStop === 'function') {
			jQuery.iResize.dragged.resizeOptions.onDragStop.apply(jQuery.iResize.dragged);
		}

		// Remove dragged element
		jQuery.iResize.dragged = null;
	},
	/**
	 * internal: Move function
	 */
	moveDrag: function(e) {
		if (!jQuery.iResize.dragged) {
			return;
		}

		pointer = jQuery.iUtil.getPointer(e);

		// Calculate new positions
		newTop = jQuery.iResize.position.top - jQuery.iResize.pointer.y + pointer.y;
		newLeft = jQuery.iResize.position.left - jQuery.iResize.pointer.x + pointer.x;
		newTop = Math.max(
						Math.min(newTop, jQuery.iResize.dragged.resizeOptions.maxBottom - jQuery.iResize.sizes.height),
						jQuery.iResize.dragged.resizeOptions.minTop
					);
		newLeft = Math.max(
						Math.min(newLeft, jQuery.iResize.dragged.resizeOptions.maxRight- jQuery.iResize.sizes.width),
						jQuery.iResize.dragged.resizeOptions.minLeft
					);

		// Callback
		if (typeof jQuery.iResize.dragged.resizeOptions.onDrag === 'function') {
			var newPos = jQuery.iResize.dragged.resizeOptions.onDrag.apply(jQuery.iResize.dragged, [newLeft, newTop]);
			if (typeof newPos == 'array' && newPos.length == 2) {
				newLeft = newPos[0];
				newTop = newPos[1];
			}
		}

		// Update the element
		jQuery.iResize.dragged.style.top = newTop + 'px';
		jQuery.iResize.dragged.style.left = newLeft + 'px';

		return false;
	},
	start: function(e) {
		// Bind event handlers
		jQuery(document)
			.bind('mousemove', jQuery.iResize.move)
			.bind('mouseup', jQuery.iResize.stop);

		// Initialize resizable
		jQuery.iResize.resizeElement = this.resizeElement;
		jQuery.iResize.resizeDirection = this.resizeDirection;
		jQuery.iResize.pointer = jQuery.iUtil.getPointer(e);
		jQuery.iResize.sizes = {
				width: parseInt(jQuery(this.resizeElement).css('width'))||0,
				height: parseInt(jQuery(this.resizeElement).css('height'))||0
			};
		jQuery.iResize.position = {
				top: parseInt(jQuery(this.resizeElement).css('top'))||0,
				left: parseInt(jQuery(this.resizeElement).css('left'))||0
			};

		// Callback function
		if (jQuery.iResize.resizeElement.resizeOptions.onStart) {
			jQuery.iResize.resizeElement.resizeOptions.onStart.apply(jQuery.iResize.resizeElement, [this]);
		}

		return false;
	},
	stop: function() {
		// Unbind event handlers
		jQuery(document)
			.unbind('mousemove', jQuery.iResize.move)
			.unbind('mouseup', jQuery.iResize.stop);

		// Callback function
		if (jQuery.iResize.resizeElement.resizeOptions.onStop) {
			jQuery.iResize.resizeElement.resizeOptions.onStop.apply(jQuery.iResize.resizeElement, [jQuery.iResize.resizeDirection]);
		}

		// Unbind
		jQuery.iResize.resizeElement = null;
		jQuery.iResize.resizeDirection = null;
	},
	getWidth: function(dx, side) {
		return Math.min(
						Math.max(jQuery.iResize.sizes.width + dx * side, jQuery.iResize.resizeElement.resizeOptions.minWidth),
						jQuery.iResize.resizeElement.resizeOptions.maxWidth
					);
	},
	getHeight: function(dy, side) {
		return Math.min(
						Math.max(jQuery.iResize.sizes.height + dy * side, jQuery.iResize.resizeElement.resizeOptions.minHeight),
						jQuery.iResize.resizeElement.resizeOptions.maxHeight
					);
	},
	getHeightMinMax: function(height) {
		return Math.min(
						Math.max(height, jQuery.iResize.resizeElement.resizeOptions.minHeight),
						jQuery.iResize.resizeElement.resizeOptions.maxHeight
					);
	},
	move: function(e) {
		if (jQuery.iResize.resizeElement == null) {
			return;
		}

		pointer = jQuery.iUtil.getPointer(e);
		dx = pointer.x - jQuery.iResize.pointer.x;
		dy = pointer.y - jQuery.iResize.pointer.y;

		newSizes = {
				width: jQuery.iResize.sizes.width,
				height: jQuery.iResize.sizes.height
			};
		newPosition = {
				top: jQuery.iResize.position.top,
				left: jQuery.iResize.position.left
			};

		switch (jQuery.iResize.resizeDirection){
			case 'e':
				newSizes.width = jQuery.iResize.getWidth(dx,1);
				break;
			case 'se':
				newSizes.width = jQuery.iResize.getWidth(dx,1);
				newSizes.height = jQuery.iResize.getHeight(dy,1);
				break;
			case 'w':
				newSizes.width = jQuery.iResize.getWidth(dx,-1);
				newPosition.left = jQuery.iResize.position.left - newSizes.width + jQuery.iResize.sizes.width;
				break;
			case 'sw':
				newSizes.width = jQuery.iResize.getWidth(dx,-1);
				newPosition.left = jQuery.iResize.position.left - newSizes.width + jQuery.iResize.sizes.width;
				newSizes.height = jQuery.iResize.getHeight(dy,1);
				break;
			case 'nw':
				newSizes.height = jQuery.iResize.getHeight(dy,-1);
				newPosition.top = jQuery.iResize.position.top - newSizes.height + jQuery.iResize.sizes.height;
				newSizes.width = jQuery.iResize.getWidth(dx,-1);
				newPosition.left = jQuery.iResize.position.left - newSizes.width + jQuery.iResize.sizes.width;
				break;
			case 'n':
				newSizes.height = jQuery.iResize.getHeight(dy,-1);
				newPosition.top = jQuery.iResize.position.top - newSizes.height + jQuery.iResize.sizes.height;
				break;
			case 'ne':
				newSizes.height = jQuery.iResize.getHeight(dy,-1);
				newPosition.top = jQuery.iResize.position.top - newSizes.height + jQuery.iResize.sizes.height;
				newSizes.width = jQuery.iResize.getWidth(dx,1);
				break;
			case 's':
				newSizes.height = jQuery.iResize.getHeight(dy,1);
				break;
		}

		if (jQuery.iResize.resizeElement.resizeOptions.ratio) {
			if (jQuery.iResize.resizeDirection == 'n' || jQuery.iResize.resizeDirection == 's')
				nWidth = newSizes.height * jQuery.iResize.resizeElement.resizeOptions.ratio;
			else
				nWidth = newSizes.width;
			nHeight = jQuery.iResize.getHeightMinMax(nWidth * jQuery.iResize.resizeElement.resizeOptions.ratio);
			nWidth = nHeight / jQuery.iResize.resizeElement.resizeOptions.ratio;

			switch (jQuery.iResize.resizeDirection){
				case 'n':
				case 'nw':
				case 'ne':
					newPosition.top += newSizes.height - nHeight;
				break;
			}

			switch (jQuery.iResize.resizeDirection){
				case 'nw':
				case 'w':
				case 'sw':
					newPosition.left += newSizes.width - nWidth;
				break;
			}

			newSizes.height = nHeight;
			newSizes.width = nWidth;
		}

		if (newPosition.top < jQuery.iResize.resizeElement.resizeOptions.minTop) {
			nHeight = newSizes.height + newPosition.top - jQuery.iResize.resizeElement.resizeOptions.minTop;
			newPosition.top = jQuery.iResize.resizeElement.resizeOptions.minTop;

			if (jQuery.iResize.resizeElement.resizeOptions.ratio) {
				nWidth = nHeight / jQuery.iResize.resizeElement.resizeOptions.ratio;
				switch (jQuery.iResize.resizeDirection){
					case 'nw':
					case 'w':
					case 'sw':
						newPosition.left += newSizes.width - nWidth;
					break;
				}
				newSizes.width = nWidth;
			}
			newSizes.height = nHeight;
		}

		if (newPosition.left < jQuery.iResize.resizeElement.resizeOptions.minLeft ) {
			nWidth = newSizes.width + newPosition.left - jQuery.iResize.resizeElement.resizeOptions.minLeft;
			newPosition.left = jQuery.iResize.resizeElement.resizeOptions.minLeft;

			if (jQuery.iResize.resizeElement.resizeOptions.ratio) {
				nHeight = nWidth * jQuery.iResize.resizeElement.resizeOptions.ratio;
				switch (jQuery.iResize.resizeDirection){
					case 'n':
					case 'nw':
					case 'ne':
						newPosition.top += newSizes.height - nHeight;
					break;
				}
				newSizes.height = nHeight;
			}
			newSizes.width = nWidth;
		}

		if (newPosition.top + newSizes.height > jQuery.iResize.resizeElement.resizeOptions.maxBottom) {
			newSizes.height = jQuery.iResize.resizeElement.resizeOptions.maxBottom - newPosition.top;
			if (jQuery.iResize.resizeElement.resizeOptions.ratio) {
				newSizes.width = newSizes.height / jQuery.iResize.resizeElement.resizeOptions.ratio;
			}

		}

		if (newPosition.left + newSizes.width > jQuery.iResize.resizeElement.resizeOptions.maxRight) {
			newSizes.width = jQuery.iResize.resizeElement.resizeOptions.maxRight - newPosition.left;
			if (jQuery.iResize.resizeElement.resizeOptions.ratio) {
				newSizes.height = newSizes.width * jQuery.iResize.resizeElement.resizeOptions.ratio;
			}

		}

		var newDimensions = false;
		if (jQuery.iResize.resizeElement.resizeOptions.onResize) {
			newDimensions = jQuery.iResize.resizeElement.resizeOptions.onResize.apply( jQuery.iResize.resizeElement, [ newSizes, newPosition ] );
			if (newDimensions) {
				if (newDimensions.sizes) {
					jQuery.extend(newSizes, newDimensions.sizes);
				}

				if (newDimensions.position) {
					jQuery.extend(newPosition, newDimensions.position);
				}
			}
		}
			elS = jQuery.iResize.resizeElement.style;
			elS.left = newPosition.left + 'px';
			elS.top = newPosition.top + 'px';
			elS.width = newSizes.width + 'px';
			elS.height = newSizes.height + 'px';

		return false;
	},
	/**
	 * Builds the resizable
	 */
	build: function(options) {
		if (!options || !options.handlers || options.handlers.constructor != Object) {
			return;
		}

		return this.each(
			function() {
				var el = this;
				el.resizeOptions = options;
				el.resizeOptions.minWidth = options.minWidth || 10;
				el.resizeOptions.minHeight = options.minHeight || 10;
				el.resizeOptions.maxWidth = options.maxWidth || 3000;
				el.resizeOptions.maxHeight = options.maxHeight || 3000;
				el.resizeOptions.minTop = options.minTop || -1000;
				el.resizeOptions.minLeft = options.minLeft || -1000;
				el.resizeOptions.maxRight = options.maxRight || 3000;
				el.resizeOptions.maxBottom = options.maxBottom || 3000;
				elPosition = jQuery(el).css('position');
				if (!(elPosition == 'relative' || elPosition == 'absolute')) {
					el.style.position = 'relative';
				}

				directions = /n|ne|e|se|s|sw|w|nw/g;
				for (i in el.resizeOptions.handlers) {
					if (i.toLowerCase().match(directions) != null) {
						if (el.resizeOptions.handlers[i].constructor == String) {
							handle = jQuery(el.resizeOptions.handlers[i]);
							if (handle.size() > 0) {
								el.resizeOptions.handlers[i] = handle.get(0);
							}
						}

						if (el.resizeOptions.handlers[i].tagName) {
							el.resizeOptions.handlers[i].resizeElement = el;
							el.resizeOptions.handlers[i].resizeDirection = i;
							jQuery(el.resizeOptions.handlers[i]).bind('mousedown', jQuery.iResize.start);
						}
					}
				}

				if (el.resizeOptions.dragHandle) {
					if (typeof el.resizeOptions.dragHandle === 'string') {
						handleEl = jQuery(el.resizeOptions.dragHandle);
						if (handleEl.size() > 0) {
							handleEl.each(function() {
									this.dragEl = el;
								});
							handleEl.bind('mousedown', jQuery.iResize.startDrag);
						}
					} else if (el.resizeOptions.dragHandle == true) {
						jQuery(this).bind('mousedown', jQuery.iResize.startDrag);
					}
				}
			}
		);
	},
	/**
	 * Destroys the resizable
	 */
	destroy: function() {
		return this.each(
			function() {
				var el = this;

				// Unbind the handlers
				for (i in el.resizeOptions.handlers) {
					el.resizeOptions.handlers[i].resizeElement = null;
					el.resizeOptions.handlers[i].resizeDirection = null;
					jQuery(el.resizeOptions.handlers[i]).unbind('mousedown', jQuery.iResize.start);
				}

				// Remove the draghandle
				if (el.resizeOptions.dragHandle) {
					if (typeof el.resizeOptions.dragHandle === 'string') {
						handle = jQuery(el.resizeOptions.dragHandle);
						if (handle.size() > 0) {
							handle.unbind('mousedown', jQuery.iResize.startDrag);
						}
					} else if (el.resizeOptions.dragHandle == true) {
						jQuery(this).unbind('mousedown', jQuery.iResize.startDrag);
					}
				}

				// Reset the options
				el.resizeOptions = null;
			}
		);
	}
};


jQuery.fn.extend ({
		/**
		 * Create a resizable element with a number of advanced options including callback, dragging
		 * 
		 * @name Resizable
		 * @description Create a resizable element with a number of advanced options including callback, dragging
		 * @param Hash hash A hash of parameters. All parameters are optional.
		 * @option Hash handlers hash with keys for each resize direction (e, es, s, sw, w, nw, n) and value string selection
		 * @option Integer minWidth (optional) the minimum width that element can be resized to
		 * @option Integer maxWidth (optional) the maximum width that element can be resized to
		 * @option Integer minHeight (optional) the minimum height that element can be resized to
		 * @option Integer maxHeight (optional) the maximum height that element can be resized to
		 * @option Integer minTop (optional) the minmum top position to wich element can be moved to
		 * @option Integer minLeft (optional) the minmum left position to wich element can be moved to
		 * @option Integer maxRight (optional) the maximum right position to wich element can be moved to
		 * @option Integer maxBottom (optional) the maximum bottom position to wich element can be moved to
		 * @option Float ratio (optional) the ratio between width and height to constrain elements sizes to that ratio
		 * @option Mixed dragHandle (optional) true to make the element draggable, string selection for drag handle
		 * @option Function onDragStart (optional) A function to be executed whenever the dragging starts
		 * @option Function onDragStop (optional) A function to be executed whenever the dragging stops
		 * @option Function onDrag (optional) A function to be executed whenever the element is dragged
		 * @option Function onStart (optional) A function to be executed whenever the element starts to be resized
		 * @option Function onStop (optional) A function to be executed whenever the element stops to be resized
		 * @option Function onResize (optional) A function to be executed whenever the element is resized
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		Resizable: jQuery.iResize.build,
		/**
		 * Destroy a resizable
		 * 
		 * @name ResizableDestroy
		 * @description Destroy a resizable
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		ResizableDestroy: jQuery.iResize.destroy
	});/**
 * Interface Elements for jQuery
 * Selectables
 *
 * http://interface.eyecon.ro
 *
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt)
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 *
 */

jQuery.selectHelper = null;
jQuery.selectKeyHelper = false;
jQuery.selectdrug = null;
jQuery.selectCurrent = [];	// For current selection
jQuery.selectKeyDown = function(e) {
	var pressedKey = e.charCode || e.keyCode || -1;
	if (pressedKey == 17 || pressedKey == 16) {
		jQuery.selectKeyHelper = true;
	}
};
jQuery.selectKeyUp = function(e) {
	jQuery.selectKeyHelper = false;
};
jQuery.selectstart = function(e) {
	this.f.pointer = jQuery.iUtil.getPointer(e);
	this.f.pos = jQuery.extend(
		jQuery.iUtil.getPosition(this), 
		jQuery.iUtil.getSize(this)
	);
	
	this.f.scr = jQuery.iUtil.getScroll(this);
	this.f.pointer.x -= this.f.pos.x;
	this.f.pointer.y -= this.f.pos.y;
	jQuery(this).append(jQuery.selectHelper.get(0));
	if (this.f.hc)
		jQuery.selectHelper.addClass(this.f.hc).css('display','block');
	jQuery.selectHelper.css(
		{
			display: 'block',
			width: '0px',
			height: '0px'
		}
	);
	if (this.f.o) {
		jQuery.selectHelper.css('opacity', this.f.o);
	}

	jQuery.selectdrug = this;
	jQuery.selectedone = false;
	jQuery.selectCurrent = [];	// For current selection state
	this.f.el.each(
		function ()
		{
			this.pos = {
				x: this.offsetLeft + (this.currentStyle && !jQuery.browser.opera ?parseInt(this.currentStyle.borderLeftWidth)||0:0) + (jQuery.selectdrug.scrollLeft||0), 
				y: this.offsetTop + (this.currentStyle && !jQuery.browser.opera ?parseInt(this.currentStyle.borderTopWidth)||0:0) + (jQuery.selectdrug.scrollTop||0),
				wb: this.offsetWidth,
				hb: this.offsetHeight
			};
			if (this.s == true) {
				if (jQuery.selectKeyHelper == false) {
					this.s = false;
					jQuery(this).removeClass(jQuery.selectdrug.f.sc);
				} else {
					jQuery.selectedone = true;

					// Save current state
					jQuery.selectCurrent[jQuery.selectCurrent.length] = jQuery.attr(this,'id');
				}
			}
		}
	);
	jQuery.selectcheck.apply(this, [e]);
	jQuery(document)
		.bind('mousemove', jQuery.selectcheck)
		.bind('mouseup', jQuery.selectstop);
	return false;
};
jQuery.selectcheck = function(e)
{
	if(!jQuery.selectdrug)
		return;
	jQuery.selectcheckApply.apply(jQuery.selectdrug, [e]);
};
jQuery.selectcheckApply = function(e)
{
	if(!jQuery.selectdrug)
		return;
	var pointer = jQuery.iUtil.getPointer(e);
	
	var scr = jQuery.iUtil.getScroll(jQuery.selectdrug);
	pointer.x += scr.l - this.f.scr.l - this.f.pos.x;
	pointer.y += scr.t - this.f.scr.t - this.f.pos.y;
	
	var sx = Math.min(pointer.x, this.f.pointer.x);
	var sw = Math.min(Math.abs(pointer.x - this.f.pointer.x), Math.abs(this.f.scr.w - sx));
	var sy = Math.min(pointer.y, this.f.pointer.y);
	var sh = Math.min(Math.abs(pointer.y - this.f.pointer.y), Math.abs(this.f.scr.h - sy));
	if (this.scrollTop > 0 && pointer.y - 20 < this.scrollTop) {
		var diff = Math.min(scr.t, 10);
		sy -= diff;
		sh += diff;
		this.scrollTop -= diff;
	} else if (this.scrollTop+ this.f.pos.h < this.f.scr.h && pointer.y + 20 > this.scrollTop + this.f.pos.h) {
		var diff = Math.min(this.f.scr.h - this.scrollTop, 10);
		this.scrollTop += diff;
		if (this.scrollTop != scr.t)
			sh += diff;
	}
	if (this.scrollLeft > 0 && pointer.x - 20 < this.scrollLeft) {
		var diff = Math.min(scr.l, 10);
		sx -= diff;
		sw += diff;
		this.scrollLeft -= diff;
	} else if (this.scrollLeft+ this.f.pos.w < this.f.scr.w && pointer.x + 20 > this.scrollLeft + this.f.pos.w) {
		var diff = Math.min(this.f.scr.w - this.scrollLeft, 10);
		this.scrollLeft += diff;
		if (this.scrollLeft != scr.l)
			sw += diff;
	}
	jQuery.selectHelper.css(
		{
			left:	sx + 'px',
			top:	sy + 'px',
			width:	sw + 'px',
			height:	sh + 'px'
		}
	);
	jQuery.selectHelper.l = sx + this.f.scr.l;
	jQuery.selectHelper.t = sy + this.f.scr.t;
	jQuery.selectHelper.r = jQuery.selectHelper.l + sw;
	jQuery.selectHelper.b = jQuery.selectHelper.t + sh;
	jQuery.selectedone = false;
	this.f.el.each(
		function () {
			// Locate the current element in the current selection
			iIndex = jQuery.selectCurrent.indexOf(jQuery.attr(this, 'id'));
			// In case we are currently OVER an item
			if (
				! ( this.pos.x > jQuery.selectHelper.r
				|| (this.pos.x + this.pos.wb) < jQuery.selectHelper.l
				|| this.pos.y > jQuery.selectHelper.b
				|| (this.pos.y + this.pos.hb) < jQuery.selectHelper.t
				)
			)
			{
				jQuery.selectedone = true;
				if (this.s != true) {
					this.s = true;
					jQuery(this).addClass(jQuery.selectdrug.f.sc);
				}

				// Check to see if this item was previously selected, if so, unselect it
				if (iIndex != -1) {
					this.s = false;
					jQuery(this).removeClass(jQuery.selectdrug.f.sc);
				}
			} else if (
						(this.s == true) &&
						(iIndex == -1)
					) {
				// If the item was marked as selected, but it was not selected when you started dragging unselect it.
				this.s = false;
				jQuery(this).removeClass(jQuery.selectdrug.f.sc);
			} else if (
						(!this.s) &&
						(jQuery.selectKeyHelper == true) &&
						(iIndex != -1)
					) {
				// Reselect the item if:
				// - we ARE multiselecting,
				// - dragged over an allready selected object (so it got unselected)
				// - But then dragged the selection out of it again.
				this.s = true;
				jQuery(this).addClass(jQuery.selectdrug.f.sc);
			}
		}
	);
	return false;
};
jQuery.selectstop = function(e)
{
	if(!jQuery.selectdrug)
		return;
	jQuery.selectstopApply.apply(jQuery.selectdrug, [e]);
};
jQuery.selectstopApply = function(e)
{
	jQuery(document)
		.unbind('mousemove', jQuery.selectcheck)
		.unbind('mouseup', jQuery.selectstop);
	if(!jQuery.selectdrug)
		return;
	jQuery.selectHelper.css('display','none');
	if (this.f.hc)
		jQuery.selectHelper.removeClass(this.f.hc);
	jQuery.selectdrug = false;
	jQuery('body').append(jQuery.selectHelper.get(0));
	//
	// In case we have selected some new items..
	if (jQuery.selectedone == true) {
		if (this.f.onselect)
			this.f.onselect(jQuery.Selectserialize(jQuery.attr(this,'id')));
	} else {
		if (this.f.onselectstop)
			this.f.onselectstop(jQuery.Selectserialize(jQuery.attr(this,'id')));
	}
	// Reset current selection
	jQuery.selectCurrent = [];
};

jQuery.Selectserialize = function(s)
{
	var h = '';
	var o = [];
	if (a = jQuery('#' + s)) {
		a.get(0).f.el.each(
			function ()
			{
				if (this.s == true) {
					if (h.length > 0) {
						h += '&';
					}
					h += s + '[]=' + jQuery.attr(this,'id');
					o[o.length] = jQuery.attr(this,'id');
				}
			}
		);
	}
	return {hash:h, o:o};
};
jQuery.fn.Selectable = function(o)
{
	if (!jQuery.selectHelper) {
		jQuery('body',document).append('<div id="selectHelper"></div>').bind('keydown', jQuery.selectKeyDown).bind('keyup', jQuery.selectKeyUp);
		jQuery.selectHelper = jQuery('#selectHelper');
		jQuery.selectHelper.css(
			{
				position:	'absolute',
				display:	'none'
			}
		);

		if (window.event) {
			jQuery('body',document).bind('keydown', jQuery.selectKeyDown).bind('keyup', jQuery.selectKeyUp);
		} else {
			jQuery(document).bind('keydown', jQuery.selectKeyDown).bind('keyup', jQuery.selectKeyUp);
		}
	}

    if (!o) {
		o = {};
	}
    return this.each(
		function()
		{
			if (this.isSelectable)
				return;
			this.isSelectable = true;
			this.f = {
				a : o.accept,
				o : o.opacity ? parseFloat(o.opacity) : false,
				sc : o.selectedclass ? o.selectedclass : false,
				hc : o.helperclass ? o.helperclass : false,
				onselect : o.onselect ? o.onselect : false,
				onselectstop : o.onselectstop ? o.onselectstop : false
			};
			this.f.el = jQuery('.' + o.accept);
			jQuery(this).bind('mousedown', jQuery.selectstart).css('position', 'relative');
		}
	);
};/**
 * Interface Elements for jQuery
 * Slider
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

jQuery.iSlider = {
	tabindex : 1,
	set : function (values)
	{
		var values = values;
		return this.each(
			function()
			{
				this.slideCfg.sliders.each(
					function (key) 
					{ 
						jQuery.iSlider.dragmoveBy(this,values[key]);
					}
				);
			}
		);
	},
	
	get : function()
	{
		var values = [];
		this.each(
			function(slider)
			{
				if (this.isSlider) {
					values[slider] = [];
					var elm = this;
					var sizes = jQuery.iUtil.getSize(this);
					this.slideCfg.sliders.each(
						function (key) 
						{
							var x = this.offsetLeft;
							var y = this.offsetTop;
							xproc = parseInt(x * 100 / (sizes.w - this.offsetWidth));
							yproc = parseInt(y * 100 / (sizes.h - this.offsetHeight));
							values[slider][key] = [xproc||0, yproc||0, x||0, y||0];
						}
					);
				}
			}
		);
		return values;
	},
	
	modifyContainer : function (elm)
	{
		elm.dragCfg.containerMaxx = elm.dragCfg.cont.w - elm.dragCfg.oC.wb;
		elm.dragCfg.containerMaxy = elm.dragCfg.cont.h - elm.dragCfg.oC.hb;
		if (elm.SliderContainer.slideCfg.restricted ) {
			next = elm.SliderContainer.slideCfg.sliders.get(elm.SliderIteration+1);
			if (next) {
				elm.dragCfg.cont.w = (parseInt(jQuery(next).css('left'))||0) + elm.dragCfg.oC.wb;
				elm.dragCfg.cont.h = (parseInt(jQuery(next).css('top'))||0) + elm.dragCfg.oC.hb;
			}
			prev = elm.SliderContainer.slideCfg.sliders.get(elm.SliderIteration-1);
			if (prev) {
				var prevLeft = parseInt(jQuery(prev).css('left'))||0;
				var prevTop = parseInt(jQuery(prev).css('left'))||0;
				elm.dragCfg.cont.x += prevLeft;
				elm.dragCfg.cont.y += prevTop;
				elm.dragCfg.cont.w -= prevLeft;
				elm.dragCfg.cont.h -= prevTop;
			}
		}
		elm.dragCfg.maxx = elm.dragCfg.cont.w - elm.dragCfg.oC.wb;
		elm.dragCfg.maxy = elm.dragCfg.cont.h - elm.dragCfg.oC.hb;
		if(elm.dragCfg.fractions) {
			elm.dragCfg.gx = ((elm.dragCfg.cont.w - elm.dragCfg.oC.wb)/elm.dragCfg.fractions) || 1;
			elm.dragCfg.gy = ((elm.dragCfg.cont.h - elm.dragCfg.oC.hb)/elm.dragCfg.fractions) || 1;
			elm.dragCfg.fracW = elm.dragCfg.maxx / elm.dragCfg.fractions;
			elm.dragCfg.fracH = elm.dragCfg.maxy / elm.dragCfg.fractions;
		}
		
		elm.dragCfg.cont.dx = elm.dragCfg.cont.x - elm.dragCfg.oR.x;
		elm.dragCfg.cont.dy = elm.dragCfg.cont.y - elm.dragCfg.oR.y;
		
		jQuery.iDrag.helper.css('cursor', 'default');
	},
	
	onSlide : function(elm, x, y)
	{
		if (elm.dragCfg.fractions) {
				xfrac = parseInt(x/elm.dragCfg.fracW);
				xproc = xfrac * 100 / elm.dragCfg.fractions;
				yfrac = parseInt(y/elm.dragCfg.fracH);
				yproc = yfrac * 100 / elm.dragCfg.fractions;
		} else {
			xproc = parseInt(x * 100 / elm.dragCfg.containerMaxx);
			yproc = parseInt(y * 100 / elm.dragCfg.containerMaxy);
		}
		elm.dragCfg.lastSi = [xproc||0, yproc||0, x||0, y||0];
		if (elm.dragCfg.onSlide)
			elm.dragCfg.onSlide.apply(elm, elm.dragCfg.lastSi);
	},
	
	dragmoveByKey : function (event)
	{
		pressedKey = event.charCode || event.keyCode || -1;
		
		switch (pressedKey)
		{
			//end
			case 35:
				jQuery.iSlider.dragmoveBy(this.dragElem, [2000, 2000] );
			break;
			//home
			case 36:
				jQuery.iSlider.dragmoveBy(this.dragElem, [-2000, -2000] );
			break;
			//left
			case 37:
				jQuery.iSlider.dragmoveBy(this.dragElem, [-this.dragElem.dragCfg.gx||-1, 0] );
			break;
			//up
			case 38:
				jQuery.iSlider.dragmoveBy(this.dragElem, [0, -this.dragElem.dragCfg.gy||-1] );
			break;
			//right
			case 39:
				jQuery.iSlider.dragmoveBy(this.dragElem, [this.dragElem.dragCfg.gx||1, 0] );
			break;
			//down;
			case 40:
				jQuery.iDrag.dragmoveBy(this.dragElem, [0, this.dragElem.dragCfg.gy||1] );
			break;
		}
	},
	
	dragmoveBy : function (elm, position) 
	{
		if (!elm.dragCfg) {
			return;
		}
		
		elm.dragCfg.oC = jQuery.extend(
			jQuery.iUtil.getPosition(elm),
			jQuery.iUtil.getSize(elm)
		);
		
		elm.dragCfg.oR = {
			x : parseInt(jQuery.css(elm, 'left'))||0,
			y : parseInt(jQuery.css(elm, 'top'))||0
		};
		
		elm.dragCfg.oP = jQuery.css(elm, 'position');
		if (elm.dragCfg.oP != 'relative' && elm.dragCfg.oP != 'absolute') {
			elm.style.position = 'relative';
		}
		
		jQuery.iDrag.getContainment(elm);
		jQuery.iSlider.modifyContainer(elm);		
		
		dx = parseInt(position[0]) || 0;
		dy = parseInt(position[1]) || 0;
		
		nx = elm.dragCfg.oR.x + dx;
		ny = elm.dragCfg.oR.y + dy;
		if(elm.dragCfg.fractions) {
			newCoords = jQuery.iDrag.snapToGrid.apply(elm, [nx, ny, dx, dy]);
			if (newCoords.constructor == Object) {
				dx = newCoords.dx;
				dy = newCoords.dy;
			}
			nx = elm.dragCfg.oR.x + dx;
			ny = elm.dragCfg.oR.y + dy;
		}
		
		newCoords = jQuery.iDrag.fitToContainer.apply(elm, [nx, ny, dx, dy]);
		if (newCoords && newCoords.constructor == Object) {
			dx = newCoords.dx;
			dy = newCoords.dy;
		}
		
		nx = elm.dragCfg.oR.x + dx;
		ny = elm.dragCfg.oR.y + dy;
		
		if (elm.dragCfg.si && (elm.dragCfg.onSlide || elm.dragCfg.onChange)) {
			jQuery.iSlider.onSlide(elm, nx, ny);
		}
		nx = !elm.dragCfg.axis || elm.dragCfg.axis == 'horizontally' ? nx : elm.dragCfg.oR.x||0;
		ny = !elm.dragCfg.axis || elm.dragCfg.axis == 'vertically' ? ny : elm.dragCfg.oR.y||0;
		elm.style.left = nx + 'px';
		elm.style.top = ny + 'px';
	},
	
	build : function(o) {
		return this.each(
			function()
			{
				if (this.isSlider == true || !o.accept || !jQuery.iUtil || !jQuery.iDrag || !jQuery.iDrop){
					return;
				}
				toDrag = jQuery(o.accept, this);
				if (toDrag.size() == 0) {
					return;
				}
				var params = {
					containment: 'parent',
					si : true,
					onSlide : o.onSlide && o.onSlide.constructor == Function ? o.onSlide : null,
					onChange : o.onChange && o.onChange.constructor == Function ? o.onChange : null,
					handle: this,
					opacity: o.opacity||false
				};
				if (o.fractions && parseInt(o.fractions)) {
					params.fractions = parseInt(o.fractions)||1;
					params.fractions = params.fractions > 0 ? params.fractions : 1;
				}
				if (toDrag.size() == 1)
					toDrag.Draggable(params);
				else {
					jQuery(toDrag.get(0)).Draggable(params);
					params.handle = null;
					toDrag.Draggable(params);
				}
				toDrag.keydown(jQuery.iSlider.dragmoveByKey);
				toDrag.attr('tabindex',jQuery.iSlider.tabindex++);	
				
				this.isSlider = true;
				this.slideCfg = {};
				this.slideCfg.onslide = params.onslide;
				this.slideCfg.fractions = params.fractions;
				this.slideCfg.sliders = toDrag;
				this.slideCfg.restricted = o.restricted ? true : false;
				sliderEl = this;
				sliderEl.slideCfg.sliders.each(
					function(nr)
					{
						this.SliderIteration = nr;
						this.SliderContainer = sliderEl;
					}
				);
				if (o.values && o.values.constructor == Array) {
					for (i = o.values.length -1; i>=0;i--) {
						if (o.values[i].constructor == Array && o.values[i].length == 2) {
							el = this.slideCfg.sliders.get(i);
							if (el.tagName) {
								jQuery.iSlider.dragmoveBy(el, o.values[i]);
							}
						}
					}
				}
			}
		);
	}
};
jQuery.fn.extend(
	{
		/**
		 * Create a slider width options
		 * 
		 * @name Slider
		 * @description Create a slider width options
		 * @param Hash hash A hash of parameters. All parameters are optional.
		 * @option Mixed accepts string to select slider indicators or DOMElement slider indicator
		 * @option Integer factions (optional) number of sgments to divide and snap slider
		 * @option Function onSlide (optional) A function to be executed whenever slider indicator it is moved
		 * @option Function onChanged (optional) A function to be executed whenever slider indicator was moved
		 * @option Array values (optional) Initial values for slider indicators
		 * @option Boolean restricted (optional) if true the slider indicator can not be moved beyond adjacent indicators
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		Slider : jQuery.iSlider.build,
		/**
		 * Set value/position for slider indicators
		 * 
		 * @name SliderSetValues
		 * @description Set value/position for slider indicators
		 * @param Array values array width values for each indicator
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SliderSetValues : jQuery.iSlider.set,
		/**
		 * Get value/position for slider indicators
		 * 
		 * @name SliderSetValues
		 * @description Get value/position for slider indicators
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		SliderGetValues : jQuery.iSlider.get
	}
);/**
 * Interface Elements for jQuery
 * Slideshow
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 */


/**
 * Creates an image slideshow. The slideshow can autoplay slides, each image can have caption, navigation links: next, prev, each slide. A page may have more then one slideshow, eachone working independently. Each slide can be bookmarked. The source images can be defined by JavaScript in slideshow options or by HTML placing images inside container.
 *
 * 
 * 
 * @name Slideshow
 * @description Creates an image slideshow. The slideshow can autoplay slides, each image can have caption, navigation links: next, prev, each slide. A page may have more then one slideshow, eachone working independently. Each slide can be bookmarked. The source images can be defined by JavaScript in slideshow options or by HTML placing images inside container.
 * @param Hash hash A hash of parameters
 * @option String container container ID
 * @option String loader path to loading indicator image
 * @option String linksPosition (optional) images links position ['top'|'bottom'|null]
 * @option String linksClass (optional) images links cssClass
 * @option String linksSeparator (optional) images links separator
 * @option Integer fadeDuration fade animation duration in miliseconds
 * @option String activeLinkClass (optional) active image link CSS class
 * @option String nextslideClass (optional) next image CSS class
 * @option String prevslideClass (optional) previous image CSS class
 * @option String captionPosition (optional) image caption position ['top'|'bottom'|null]
 * @option String captionClass (optional) image caption CSS class
 * @option String autoplay (optional) seconds to wait untill next images is displayed. This option will make the slideshow to autoplay.
 * @option String random (optional) if slideshow autoplayes the images can be randomized
 * @option Array images (optional) array of hash with keys 'src' (path to image) and 'cation' (image caption) for images
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.islideshow = {
	slideshows: [],
	gonext : function()
	{
		this.blur();
		slideshow = this.parentNode;
		id = jQuery.attr(slideshow, 'id');
		if (jQuery.islideshow.slideshows[id] != null) {
			window.clearInterval(jQuery.islideshow.slideshows[id]);
		}
		slide = slideshow.ss.currentslide + 1;
		if (slideshow.ss.images.length < slide) {
			slide = 1;
		}
		images = jQuery('img', slideshow.ss.holder);
		slideshow.ss.currentslide = slide;
		if (images.size() > 0) {
			images.fadeOut(
				slideshow.ss.fadeDuration,
				jQuery.islideshow.showImage
			);
		}
	},
	goprev : function()
	{
		this.blur();
		slideshow = this.parentNode;
		id = jQuery.attr(slideshow, 'id');
		if (jQuery.islideshow.slideshows[id] != null) {
			window.clearInterval(jQuery.islideshow.slideshows[id]);
		}
		slide = slideshow.ss.currentslide - 1;
		images = jQuery('img', slideshow.ss.holder);
		if (slide < 1) {
			slide = slideshow.ss.images.length ;
		}
		slideshow.ss.currentslide = slide;
		if (images.size() > 0) {
			images.fadeOut(
				slideshow.ss.fadeDuration,
				jQuery.islideshow.showImage
			);
		}
	},
	timer : function (c)
	{
		slideshow = document.getElementById(c);
		if (slideshow.ss.random) {
			slide = slideshow.ss.currentslide;
			while(slide == slideshow.ss.currentslide) {
				slide = 1 + parseInt(Math.random() * slideshow.ss.images.length);
			}
		} else {
			slide = slideshow.ss.currentslide + 1;
			if (slideshow.ss.images.length < slide) {
				slide = 1;
			}
		}
		images = jQuery('img', slideshow.ss.holder);
		slideshow.ss.currentslide = slide;
		if (images.size() > 0) {
			images.fadeOut(
				slideshow.ss.fadeDuration,
				jQuery.islideshow.showImage
			);
		}
	},
	go : function(o)
	{
		var slideshow;
		if (o && o.constructor == Object) {
			if (o.loader) {
				slideshow = document.getElementById(o.loader.slideshow);
				url = window.location.href.split("#");
				o.loader.onload = null;
				if (url.length == 2) {
					slide = parseInt(url[1]);
					show = url[1].replace(slide,'');
					if (jQuery.attr(slideshow,'id') != show) {
						slide = 1;
					}
				} else {
					slide = 1;
				}
			}
			if(o.link) {
				o.link.blur();
				slideshow = o.link.parentNode.parentNode;
				id = jQuery.attr(slideshow, 'id');
				if (jQuery.islideshow.slideshows[id] != null) {
					window.clearInterval(jQuery.islideshow.slideshows[id]);
				}
				url = o.link.href.split("#");
				slide = parseInt(url[1]);
				show = url[1].replace(slide,'');
				if (jQuery.attr(slideshow,'id') != show) {
					slide = 1;
				}
			}
			if (slideshow.ss.images.length < slide || slide < 1) {
				slide = 1;
			}
			slideshow.ss.currentslide = slide;
			slidePos = jQuery.iUtil.getSize(slideshow);
			slidePad = jQuery.iUtil.getPadding(slideshow);
			slideBor = jQuery.iUtil.getBorder(slideshow);
			if (slideshow.ss.prevslide) {
				slideshow.ss.prevslide.o.css('display', 'none');
			}
			if (slideshow.ss.nextslide) {
				slideshow.ss.nextslide.o.css('display', 'none');
			}
			
			//center loader
			if (slideshow.ss.loader) {
				y = parseInt(slidePad.t) + parseInt(slideBor.t);
				if (slideshow.ss.slideslinks) {
					if (slideshow.ss.slideslinks.linksPosition == 'top') {
						y += slideshow.ss.slideslinks.dimm.hb;
					} else {
						slidePos.h -= slideshow.ss.slideslinks.dimm.hb;
					}
				}
				if (slideshow.ss.slideCaption) {
					if (slideshow.ss.slideCaption && slideshow.ss.slideCaption.captionPosition == 'top') {
						y += slideshow.ss.slideCaption.dimm.hb;
					} else {
						slidePos.h -= slideshow.ss.slideCaption.dimm.hb;
					}
				}
				if (!slideshow.ss.loaderWidth) {
					slideshow.ss.loaderHeight = o.loader ? o.loader.height : (parseInt(slideshow.ss.loader.css('height'))||0);
					slideshow.ss.loaderWidth = o.loader ? o.loader.width : (parseInt(slideshow.ss.loader.css('width'))||0);
				}
				
				slideshow.ss.loader.css('top', y + (slidePos.h - slideshow.ss.loaderHeight)/2 + 'px');
				slideshow.ss.loader.css('left', (slidePos.wb - slideshow.ss.loaderWidth)/2 + 'px');
				slideshow.ss.loader.css('display', 'block');
			}
			
			//getimage
			images = jQuery('img', slideshow.ss.holder);
			if (images.size() > 0) {
				images.fadeOut(
					slideshow.ss.fadeDuration,
					jQuery.islideshow.showImage
				);
			} else {
				lnk = jQuery('a', slideshow.ss.slideslinks.o).get(slide-1);
				jQuery(lnk).addClass(slideshow.ss.slideslinks.activeLinkClass);
				var img = new Image();
				img.slideshow = jQuery.attr(slideshow,'id');
				img.slide = slide-1;
				img.src = slideshow.ss.images[slideshow.ss.currentslide-1].src ;
				if (img.complete) {
					img.onload = null;
					jQuery.islideshow.display.apply(img);
				} else {
					img.onload = jQuery.islideshow.display;
				}
				//slideshow.ss.holder.html('<img src="' + slideshow.ss.images[slide-1].src + '" />');
				if (slideshow.ss.slideCaption) {
					slideshow.ss.slideCaption.o.html(slideshow.ss.images[slide-1].caption);
				}
				//jQuery('img', slideshow.ss.holder).bind('load',jQuery.slideshowDisplay);
			}
		}
	},
	showImage : function()
	{
		slideshow = this.parentNode.parentNode;
		slideshow.ss.holder.css('display','none');
		if (slideshow.ss.slideslinks.activeLinkClass) {
			lnk = jQuery('a', slideshow.ss.slideslinks.o).removeClass(slideshow.ss.slideslinks.activeLinkClass).get(slideshow.ss.currentslide - 1);
			jQuery(lnk).addClass(slideshow.ss.slideslinks.activeLinkClass);
		}
		//slideshow.ss.holder.html('<img src="' + slideshow.ss.images[slideshow.ss.currentslide - 1].src + '" />');
		
		var img = new Image();
		img.slideshow = jQuery.attr(slideshow,'id');
		img.slide = slideshow.ss.currentslide - 1;
		img.src = slideshow.ss.images[slideshow.ss.currentslide - 1].src ;
		if (img.complete) {
			img.onload = null;
			jQuery.islideshow.display.apply(img);
		} else {
			img.onload = jQuery.islideshow.display;
		}
		if (slideshow.ss.slideCaption) {
			slideshow.ss.slideCaption.o.html(slideshow.ss.images[slideshow.ss.currentslide-1].caption);
		}
		//jQuery('img', slideshow.ss.holder).bind('load',jQuery.slideshowDisplay);
	},
	display : function ()
	{
		slideshow = document.getElementById(this.slideshow);
		if (slideshow.ss.prevslide) {
			slideshow.ss.prevslide.o.css('display', 'none');
		}
		if (slideshow.ss.nextslide) {
			slideshow.ss.nextslide.o.css('display', 'none');
		}
		slidePos = jQuery.iUtil.getSize(slideshow);
		y = 0;
		if (slideshow.ss.slideslinks) {
			if (slideshow.ss.slideslinks.linksPosition == 'top') {
				y += slideshow.ss.slideslinks.dimm.hb;
			} else {
				slidePos.h -= slideshow.ss.slideslinks.dimm.hb;
			}
		}
		if (slideshow.ss.slideCaption) {
			if (slideshow.ss.slideCaption && slideshow.ss.slideCaption.captionPosition == 'top') {
				y += slideshow.ss.slideCaption.dimm.hb;
			} else {
				slidePos.h -= slideshow.ss.slideCaption.dimm.hb;
			}
		}
		par = jQuery('.slideshowHolder', slideshow);
		y = y + (slidePos.h - this.height)/2 ;
		x = (slidePos.wb - this.width)/2;
		slideshow.ss.holder.css('top', y + 'px').css('left', x + 'px').html('<img src="' + this.src + '" />');
		slideshow.ss.holder.fadeIn(slideshow.ss.fadeDuration);
		nextslide = slideshow.ss.currentslide + 1;
		if (nextslide > slideshow.ss.images.length) {
			nextslide = 1;
		}
		prevslide = slideshow.ss.currentslide - 1;
		if (prevslide < 1) {
			prevslide = slideshow.ss.images.length;
		}
		slideshow.ss.nextslide.o
				.css('display','block')
				.css('top', y + 'px')
				.css('left', x + 2 * this.width/3 + 'px')
				.css('width', this.width/3 + 'px')
				.css('height', this.height + 'px')
				.attr('title', slideshow.ss.images[nextslide-1].caption);
		slideshow.ss.nextslide.o.get(0).href = '#' + nextslide + jQuery.attr(slideshow, 'id');
		slideshow.ss.prevslide.o
				.css('display','block')
				.css('top', y + 'px')
				.css('left', x + 'px')
				.css('width', this.width/3 + 'px')
				.css('height', this.height + 'px')
				.attr('title', slideshow.ss.images[prevslide-1].caption);
		slideshow.ss.prevslide.o.get(0).href = '#' + prevslide + jQuery.attr(slideshow, 'id');
	},
	build : function(o)
	{
		if (!o || !o.container || jQuery.islideshow.slideshows[o.container])
			return;
		var container = jQuery('#' + o.container);
		var el = container.get(0);
		
		if (el.style.position != 'absolute' && el.style.position != 'relative') {
			el.style.position = 'relative';
		}
		el.style.overflow = 'hidden';
		if (container.size() == 0)
			return;
		el.ss = {};
		
		el.ss.images = o.images ? o.images : [];
		el.ss.random = o.random && o.random == true || false;
		imgs = el.getElementsByTagName('IMG');
		for(i = 0; i< imgs.length; i++) {
			indic = el.ss.images.length;
			el.ss.images[indic] = {src:imgs[i].src, caption:imgs[i].title||imgs[i].alt||''};
		}
		
		if (el.ss.images.length == 0) {
			return;
		}
		
		el.ss.oP = jQuery.extend(
				jQuery.iUtil.getPosition(el),
				jQuery.iUtil.getSize(el)
			);
		el.ss.oPad = jQuery.iUtil.getPadding(el);
		el.ss.oBor = jQuery.iUtil.getBorder(el);
		t = parseInt(el.ss.oPad.t) + parseInt(el.ss.oBor.t);
		b = parseInt(el.ss.oPad.b) + parseInt(el.ss.oBor.b);
		jQuery('img', el).remove();
		el.ss.fadeDuration = o.fadeDuration ? o.fadeDuration : 500;
		if (o.linksPosition || o.linksClass || o.activeLinkClass) {
			el.ss.slideslinks = {};
			container.append('<div class="slideshowLinks"></div>');
			el.ss.slideslinks.o = jQuery('.slideshowLinks', el);
			if (o.linksClass) {
				el.ss.slideslinks.linksClass = o.linksClass;
				el.ss.slideslinks.o.addClass(o.linksClass);
			}
			if (o.activeLinkClass) {
				el.ss.slideslinks.activeLinkClass = o.activeLinkClass;
			}
			el.ss.slideslinks.o.css('position','absolute').css('width', el.ss.oP.w + 'px');
			if (o.linksPosition && o.linksPosition == 'top') {
				el.ss.slideslinks.linksPosition = 'top';
				el.ss.slideslinks.o.css('top',t + 'px');
			} else {
				el.ss.slideslinks.linksPosition = 'bottom';
				el.ss.slideslinks.o.css('bottom',b + 'px');
			}
			el.ss.slideslinks.linksSeparator = o.linksSeparator ? o.linksSeparator : ' ';
			for (var i=0; i<el.ss.images.length; i++) {
				indic = parseInt(i) + 1;
				el.ss.slideslinks.o.append('<a href="#' + indic + o.container + '" class="slideshowLink" title="' + el.ss.images[i].caption + '">' + indic + '</a>' + (indic != el.ss.images.length ? el.ss.slideslinks.linksSeparator : ''));
			}
			jQuery('a', el.ss.slideslinks.o).bind(
				'click',
				function()
				{
					jQuery.islideshow.go({link:this})
				}
			);
			el.ss.slideslinks.dimm = jQuery.iUtil.getSize(el.ss.slideslinks.o.get(0));
		}
		if (o.captionPosition || o.captionClass) {
			el.ss.slideCaption = {};
			container.append('<div class="slideshowCaption">&nbsp;</div>');
			el.ss.slideCaption.o = jQuery('.slideshowCaption', el);
			if (o.captionClass) {
				el.ss.slideCaption.captionClass = o.captionClass;
				el.ss.slideCaption.o.addClass(o.captionClass);
			}
			el.ss.slideCaption.o.css('position','absolute').css('width', el.ss.oP.w + 'px');
			if (o.captionPosition&& o.captionPosition == 'top') {
				el.ss.slideCaption.captionPosition = 'top';
				el.ss.slideCaption.o.css('top', (el.ss.slideslinks && el.ss.slideslinks.linksPosition == 'top' ? el.ss.slideslinks.dimm.hb + t : t) + 'px');
			} else {
				el.ss.slideCaption.captionPosition = 'bottom';
				el.ss.slideCaption.o.css('bottom', (el.ss.slideslinks && el.ss.slideslinks.linksPosition == 'bottom' ? el.ss.slideslinks.dimm.hb + b : b) + 'px');
			}
			el.ss.slideCaption.dimm = jQuery.iUtil.getSize(el.ss.slideCaption.o.get(0));
		}
		
		if (o.nextslideClass) {
			el.ss.nextslide = {nextslideClass:o.nextslideClass};
			container.append('<a href="#2' + o.container + '" class="slideshowNextSlide">&nbsp;</a>');
			el.ss.nextslide.o = jQuery('.slideshowNextSlide', el);
			el.ss.nextslide.o.css('position', 'absolute').css('display', 'none').css('overflow','hidden').css('fontSize', '30px').addClass(el.ss.nextslide.nextslideClass);
			el.ss.nextslide.o.bind('click', jQuery.islideshow.gonext);
		}
		if (o.prevslideClass) {
			el.ss.prevslide= {prevslideClass:o.prevslideClass};
			container.append('<a href="#0' + o.container + '" class="slideshowPrevslide">&nbsp;</a>');
			el.ss.prevslide.o = jQuery('.slideshowPrevslide', el);
			el.ss.prevslide.o.css('position', 'absolute').css('display', 'none').css('overflow','hidden').css('fontSize', '30px').addClass(el.ss.prevslide.prevslideClass);
			el.ss.prevslide.o.bind('click', jQuery.islideshow.goprev);
		}
		
		container.prepend('<div class="slideshowHolder"></div>');
		el.ss.holder = jQuery('.slideshowHolder', el);
		el.ss.holder.css('position','absolute').css('top','0px').css('left','0px').css('display', 'none');
		if (o.loader) {
			container.prepend('<div class="slideshowLoader" style="display: none;"><img src="' + o.loader + '" /></div>');
			el.ss.loader = jQuery('.slideshowLoader', el);
			el.ss.loader.css('position', 'absolute');
			var img = new Image();
			img.slideshow = o.container;
			img.src = o.loader;
			if (img.complete) {
				img.onload = null;
				jQuery.islideshow.go({loader:img});
			} else {
				img.onload = function()
				{
					jQuery.islideshow.go({loader:this});
				};
			}
		} else {
			jQuery.islideshow.go({container:el});
		}
		
		if(o.autoplay) {
			time = parseInt(o.autoplay) * 1000;
		}
		jQuery.islideshow.slideshows[o.container] = o.autoplay ? window.setInterval('jQuery.islideshow.timer(\'' + o.container + '\')', time) : null;
	}
};
jQuery.slideshow = jQuery.islideshow.build;/**
 * Interface Elements for jQuery
 * Sortables
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Allows you to resort elements within a container by dragging and dropping. Requires
 * the Draggables and Droppables plugins. The container and each item inside the container
 * must have an ID. Sortables are especially useful for lists.
 * 
 * @see Plugins/Interface/Draggable
 * @see Plugins/Interface/Droppable
 * @author Stefan Petre
 * @name Sortable
 * @cat Plugins/Interface
 * @param Hash options        A hash of options
 * @option String accept      The class name for items inside the container (mandatory)
 * @option String activeclass The class for the container when one of its items has started to move
 * @option String hoverclass  The class for the container when an acceptable item is inside it
 * @option String helperclass The helper is used to point to the place where the item will be 
 *                            moved. This is the class for the helper.
 * @option Float opacity      Opacity (between 0 and 1) of the item while being dragged
 * @option Boolean ghosting   When true, the sortable is ghosted when dragged
 * @option String tolerance   Either 'pointer', 'intersect', or 'fit'. See Droppable for more details
 * @option Boolean fit        When true, sortable must be inside the container in order to drop
 * @option Integer fx         Duration for the effect applied to the sortable
 * @option Function onchange  Callback that gets called when the sortable list changed. It takes
 *                            an array of serialized elements
 * @option Boolean floats     True if the sorted elements are floated
 * @option String containment Use 'parent' to constrain the drag to the container
 * @option String axis        Use 'horizontally' or 'vertically' to constrain dragging to an axis
 * @option String handle      The jQuery selector that indicates the draggable handle
 * @option DOMElement handle  The node that indicates the draggable handle
 * @option Function onHover   Callback that is called when an acceptable item is dragged over the
 *                            container. Gets the hovering DOMElement as a parameter
 * @option Function onOut     Callback that is called when an acceptable item leaves the container.
 *                            Gets the leaving DOMElement as a parameter
 * @option Object cursorAt    The mouse cursor will be moved to the offset on the dragged item
 *                            indicated by the object, which takes "top", "bottom", "left", and
 *                            "right" keys
 * @option Function onStart   Callback function triggered when the dragging starts
 * @option Function onStop    Callback function triggered when the dragging stops
 * @example                   $('ul').Sortable(
 *                            	{
 *                            		accept : 'sortableitem',
 *                            		activeclass : 'sortableactive',
 *                             		hoverclass : 'sortablehover',
 *                             		helperclass : 'sorthelper',
 *                             		opacity: 	0.5,
 *                             		fit :	false
 *                             	}
 *                             )
 */

jQuery.iSort = {
	changed : [],
	collected : {},
	helper : false,
	inFrontOf: null,
	
	start : function ()
	{
		if (jQuery.iDrag.dragged == null) {
			return;
		}
		var shs, margins,c, cs;
		
		jQuery.iSort.helper.get(0).className = jQuery.iDrag.dragged.dragCfg.hpc;
		shs = jQuery.iSort.helper.get(0).style;
		shs.display = 'block';
		jQuery.iSort.helper.oC = jQuery.extend(
			jQuery.iUtil.getPosition(jQuery.iSort.helper.get(0)),
			jQuery.iUtil.getSize(jQuery.iSort.helper.get(0))
		);
		
		shs.width = jQuery.iDrag.dragged.dragCfg.oC.wb + 'px';
		shs.height = jQuery.iDrag.dragged.dragCfg.oC.hb + 'px';
		//shs.cssFloat = jQuery.iDrag.dragged.dragCfg.oF;
		margins = jQuery.iUtil.getMargins(jQuery.iDrag.dragged);
		shs.marginTop = margins.t;
		shs.marginRight = margins.r;
		shs.marginBottom = margins.b;
		shs.marginLeft = margins.l;
		if (jQuery.iDrag.dragged.dragCfg.ghosting == true) {
			c = jQuery.iDrag.dragged.cloneNode(true);
			cs = c.style;
			cs.marginTop = '0px';
			cs.marginRight = '0px';
			cs.marginBottom = '0px';
			cs.marginLeft = '0px';
			cs.display = 'block';
			jQuery.iSort.helper.empty().append(c);
		}
		jQuery(jQuery.iDrag.dragged).after(jQuery.iSort.helper.get(0));
		jQuery.iDrag.dragged.style.display = 'none';
	},
	
	check : function (e)
	{
		if (!e.dragCfg.so && jQuery.iDrop.overzone.sortable) {
			if (e.dragCfg.onStop)
				e.dragCfg.onStop.apply(dragged);
			jQuery(e).css('position', e.dragCfg.initialPosition || e.dragCfg.oP);
			jQuery(e).DraggableDestroy();
			jQuery(jQuery.iDrop.overzone).SortableAddItem(e);
		}
		jQuery.iSort.helper.removeClass(e.dragCfg.hpc).html('&nbsp;');
		jQuery.iSort.inFrontOf = null;
		var shs = jQuery.iSort.helper.get(0).style;
		shs.display = 'none';
		jQuery.iSort.helper.after(e);
		if (e.dragCfg.fx > 0) {
			jQuery(e).fadeIn(e.dragCfg.fx);
		}
		jQuery('body').append(jQuery.iSort.helper.get(0));
		var ts = [];
		var fnc = false;
		for(var i=0; i<jQuery.iSort.changed.length; i++){
			var iEL = jQuery.iDrop.zones[jQuery.iSort.changed[i]].get(0);
			var id = jQuery.attr(iEL, 'id');
			var ser = jQuery.iSort.serialize(id);
			if (iEL.dropCfg.os != ser.hash) {
				iEL.dropCfg.os = ser.hash;
				if (fnc == false && iEL.dropCfg.onChange) {
					fnc = iEL.dropCfg.onChange;
				}
				ser.id = id;
				ts[ts.length] = ser;
			}
		}
		jQuery.iSort.changed = [];
		if (fnc != false && ts.length > 0) {
			fnc(ts);
		}
	},
	
	checkhover : function(e,o)
	{
		if (!jQuery.iDrag.dragged)
			return;
		var cur = false;
		var i = 0;
		if ( e.dropCfg.el.size() > 0) {
			for (i = e.dropCfg.el.size(); i >0; i--) {
				if (e.dropCfg.el.get(i-1) != jQuery.iDrag.dragged) {
					if (!e.sortCfg.floats) {
						if ( 
						(e.dropCfg.el.get(i-1).pos.y + e.dropCfg.el.get(i-1).pos.hb/2) > jQuery.iDrag.dragged.dragCfg.ny  
						) {
							cur = e.dropCfg.el.get(i-1);
						} else {
							break;
						}
					} else {
						if (
						(e.dropCfg.el.get(i-1).pos.x + e.dropCfg.el.get(i-1).pos.wb/2) > jQuery.iDrag.dragged.dragCfg.nx && 
						(e.dropCfg.el.get(i-1).pos.y + e.dropCfg.el.get(i-1).pos.hb/2) > jQuery.iDrag.dragged.dragCfg.ny  
						) {
							cur = e.dropCfg.el.get(i-1);
						}
					}
				}
			}
		}
		//helpos = jQuery.iUtil.getPos(jQuery.iSort.helper.get(0));
		if (cur && jQuery.iSort.inFrontOf != cur) {
			jQuery.iSort.inFrontOf = cur;
			jQuery(cur).before(jQuery.iSort.helper.get(0));
		} else if(!cur && (jQuery.iSort.inFrontOf != null || jQuery.iSort.helper.get(0).parentNode != e) ) {
			jQuery.iSort.inFrontOf = null;
			jQuery(e).append(jQuery.iSort.helper.get(0));
		}
		jQuery.iSort.helper.get(0).style.display = 'block';
	},
	
	measure : function (e)
	{
		if (jQuery.iDrag.dragged == null) {
			return;
		}
		e.dropCfg.el.each (
			function ()
			{
				this.pos = jQuery.extend(
					jQuery.iUtil.getSizeLite(this),
					jQuery.iUtil.getPositionLite(this)
				);
			}
		);
	},
	
	serialize : function(s)
	{
		var i;
		var h = '';
		var o = {};
		if (s) {
			if (jQuery.iSort.collected[s] ) {
				o[s] = [];
				jQuery('#' + s + ' .' + jQuery.iSort.collected[s]).each(
					function ()
					{
						if (h.length > 0) {
							h += '&';
						}
						h += s + '[]=' + jQuery.attr(this,'id');
						o[s][o[s].length] = jQuery.attr(this,'id');
					}
				);
			} else {
				for ( a in s) {
					if (jQuery.iSort.collected[s[a]] ) {
						o[s[a]] = [];			
						jQuery('#' + s[a] + ' .' + jQuery.iSort.collected[s[a]]).each(
							function ()
							{
								if (h.length > 0) {
									h += '&';
								}
								h += s[a] + '[]=' + jQuery.attr(this,'id');
								o[s[a]][o[s[a]].length] = jQuery.attr(this,'id');
							}
						);
					}
				}
			}
		} else {
			for ( i in jQuery.iSort.collected){
				o[i] = [];
				jQuery('#' + i + ' .' + jQuery.iSort.collected[i]).each(
					function ()
					{
						if (h.length > 0) {
							h += '&';
						}
						h += i + '[]=' + jQuery.attr(this,'id');
						o[i][o[i].length] = jQuery.attr(this,'id');
					}
				);
			}
		}
		return {hash:h, o:o};
	},
	
	addItem : function (e)
	{
		if ( !e.childNodes ) {
			return;
		}
		return this.each(
			function ()
			{
				if(!this.sortCfg || !jQuery(e).is('.' +  this.sortCfg.accept))
					jQuery(e).addClass(this.sortCfg.accept);
				jQuery(e).Draggable(this.sortCfg.dragCfg);
			}
		);
	},
	
	destroy: function()
	{
		return this.each(
			function()
			{
				jQuery('.' + this.sortCfg.accept).DraggableDestroy();
				jQuery(this).DroppableDestroy();
				this.sortCfg = null;
				this.isSortable = null;
			}
		);
	},
	
	build : function (o)
	{
		if (o.accept && jQuery.iUtil && jQuery.iDrag && jQuery.iDrop) {
			if (!jQuery.iSort.helper) {
				jQuery('body',document).append('<div id="sortHelper">&nbsp;</div>');
				jQuery.iSort.helper = jQuery('#sortHelper');
				jQuery.iSort.helper.get(0).style.display = 'none';
			}
			this.Droppable(
				{
					accept :  o.accept,
					activeclass : o.activeclass ? o.activeclass : false,
					hoverclass : o.hoverclass ? o.hoverclass : false,
					helperclass : o.helperclass ? o.helperclass : false,
					/*onDrop: function (drag, fx) 
							{
								jQuery.iSort.helper.after(drag);
								if (fx > 0) {
									jQuery(drag).fadeIn(fx);
								}
							},*/
					onHover: o.onHover||o.onhover,
					onOut: o.onOut||o.onout,
					sortable : true,
					onChange : 	o.onChange||o.onchange,
					fx : o.fx ? o.fx : false,
					ghosting : o.ghosting ? true : false,
					tolerance: o.tolerance ? o.tolerance : 'intersect'
				}
			);
			
			return this.each(
				function()
				{
					var dragCfg = {
						revert : o.revert? true : false,
						zindex : 3000,
						opacity : o.opacity ? parseFloat(o.opacity) : false,
						hpc : o.helperclass ? o.helperclass : false,
						fx : o.fx ? o.fx : false,
						so : true,
						ghosting : o.ghosting ? true : false,
						handle: o.handle ? o.handle : null,
						containment: o.containment ? o.containment : null,
						onStart : o.onStart && o.onStart.constructor == Function ? o.onStart : false,
						onDrag : o.onDrag && o.onDrag.constructor == Function ? o.onDrag : false,
						onStop : o.onStop && o.onStop.constructor == Function ? o.onStop : false,
						axis : /vertically|horizontally/.test(o.axis) ? o.axis : false,
						snapDistance : o.snapDistance ? parseInt(o.snapDistance)||0 : false,
						cursorAt: o.cursorAt ? o.cursorAt : false
					};
					jQuery('.' + o.accept, this).Draggable(dragCfg);
					this.isSortable = true;
					this.sortCfg = {
						accept :  o.accept,
						revert : o.revert? true : false,
						zindex : 3000,
						opacity : o.opacity ? parseFloat(o.opacity) : false,
						hpc : o.helperclass ? o.helperclass : false,
						fx : o.fx ? o.fx : false,
						so : true,
						ghosting : o.ghosting ? true : false,
						handle: o.handle ? o.handle : null,
						containment: o.containment ? o.containment : null,
						floats: o.floats ? true : false,
						dragCfg : dragCfg
					}
				}
			);
		}
	}
};

jQuery.fn.extend(
	{
		Sortable : jQuery.iSort.build,
		/**
		 * A new item can be added to a sortable by adding it to the DOM and then adding it via
		 * SortableAddItem. 
		 *
		 * @name SortableAddItem
		 * @param DOMElement elem A DOM Element to add to the sortable list
		 * @example $('#sortable1').append('<li id="newitem">new item</li>')
		 *                         .SortableAddItem($("#new_item")[0])
		 * @type jQuery
		 * @cat Plugins/Interface
		 */
		SortableAddItem : jQuery.iSort.addItem,
		/**
		 * Destroy a sortable
		 *
		 * @name SortableDestroy
		 * @example $('#sortable1').SortableDestroy();
		 * @type jQuery
		 * @cat Plugins/Interface
		 */
		SortableDestroy: jQuery.iSort.destroy
	}
);

/**
 * This function returns the hash and an object (can be used as arguments for $.post) for every 
 * sortable in the page or specific sortables. The hash is based on the 'id' attributes of 
 * container and items.
 *
 * @params String sortable The id of the sortable to serialize
 * @name $.SortSerialize
 * @type String
 * @cat Plugins/Interface
 */

jQuery.SortSerialize = jQuery.iSort.serialize;/**
 * Interface Elements for jQuery
 * Tooltip
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 */

/**
 * Creates tooltips using title attribute
 *
 * 
 * 
 * @name ToolTip
 * @description Creates tooltips using title attribute
 * @param Hash hash A hash of parameters
 * @option String position tooltip's position ['top'|'left'|'right'|'bottom'|'mouse']
 * @options Function onShow (optional) A function to be executed whenever the tooltip is displayed
 * @options Function onHide (optional) A function to be executed whenever the tooltip is hidden
 *
 * @type jQuery
 * @cat Plugins/Interface
 * @author Stefan Petre
 */
jQuery.iTooltip = {
	current : null,
	focused : false,
	oldTitle : null,
	focus : function(e)
	{
		jQuery.iTooltip.focused = true;
		jQuery.iTooltip.show(e, this, true);
	},
	hidefocused : function(e)
	{
		if (jQuery.iTooltip.current != this)
			return ;
		jQuery.iTooltip.focused = false;
		jQuery.iTooltip.hide(e, this);
	},
	show : function(e, el, focused)
	{
		if (jQuery.iTooltip.current != null)
			return ;
		if (!el) {
			el = this;
		}
		
		jQuery.iTooltip.current = el;
		pos = jQuery.extend(
			jQuery.iUtil.getPosition(el),
			jQuery.iUtil.getSize(el)
		);
		jEl = jQuery(el);
		title = jEl.attr('title');
		href = jEl.attr('href');
		if (title) {
			jQuery.iTooltip.oldTitle = title;
			jEl.attr('title','');
			jQuery('#tooltipTitle').html(title);
			if (href)
				jQuery('#tooltipURL').html(href.replace('http://', ''));
			else 
				jQuery('#tooltipURL').html('');
			helper = jQuery('#tooltipHelper');
			if(el.tooltipCFG.className){
				helper.get(0).className = el.tooltipCFG.className;
			} else {
				helper.get(0).className = '';
			}
			helperSize = jQuery.iUtil.getSize(helper.get(0));
			filteredPosition = focused && el.tooltipCFG.position == 'mouse' ? 'bottom' : el.tooltipCFG.position;
			
			switch (filteredPosition) {
				case 'top':
					ny = pos.y - helperSize.hb;
					nx = pos.x;
				break;
				case 'left' :
					ny = pos.y;
					nx = pos.x - helperSize.wb;
				break;
				case 'right' :
					ny = pos.y;
					nx = pos.x + pos.wb;
				break;
				case 'mouse' :
					jQuery('body').bind('mousemove', jQuery.iTooltip.mousemove);
					pointer = jQuery.iUtil.getPointer(e);
					ny = pointer.y + 15;
					nx = pointer.x + 15;
				break;
				default :
					ny = pos.y + pos.hb;
					nx = pos.x;
				break;
			}
			helper.css(
				{
					top 	: ny + 'px',
					left	: nx + 'px'
				}
			);
			if (el.tooltipCFG.delay == false) {
				helper.show();
			} else {
				helper.fadeIn(el.tooltipCFG.delay);
			}
			if (el.tooltipCFG.onShow) 
				el.tooltipCFG.onShow.apply(el);
			jEl.bind('mouseout',jQuery.iTooltip.hide)
			   .bind('blur',jQuery.iTooltip.hidefocused);
		}
	},
	mousemove : function(e)
	{
		if (jQuery.iTooltip.current == null) {
			jQuery('body').unbind('mousemove', jQuery.iTooltip.mousemove);
			return;	
		}
		pointer = jQuery.iUtil.getPointer(e);
		jQuery('#tooltipHelper').css(
			{
				top 	: pointer.y + 15 + 'px',
				left	: pointer.x + 15 + 'px'
			}
		);
	},
	hide : function(e, el)
	{
		if (!el) {
			el = this;
		}
		if (jQuery.iTooltip.focused != true && jQuery.iTooltip.current == el) {
			jQuery.iTooltip.current = null;
			jQuery('#tooltipHelper').fadeOut(1);
			jQuery(el)
				.attr('title',jQuery.iTooltip.oldTitle)
				.unbind('mouseout', jQuery.iTooltip.hide)
				.unbind('blur', jQuery.iTooltip.hidefocused);
			if (el.tooltipCFG.onHide) 
				el.tooltipCFG.onHide.apply(el);
			jQuery.iTooltip.oldTitle = null;
		}
	},
	build : function(options)
	{
		if (!jQuery.iTooltip.helper)
		{
			jQuery('body').append('<div id="tooltipHelper"><div id="tooltipTitle"></div><div id="tooltipURL"></div></div>');
			jQuery('#tooltipHelper').css(
				{
					position:	'absolute',
					zIndex:		3000,
					display: 	'none'
				}
			);
			jQuery.iTooltip.helper = true;
		}
		return this.each(
			function(){
				if(jQuery.attr(this,'title')) {
					this.tooltipCFG = {
						position	: /top|bottom|left|right|mouse/.test(options.position) ? options.position : 'bottom',
						className	: options.className ? options.className : false,
						delay		: options.delay ? options.delay : false,
						onShow		: options.onShow && options.onShow.constructor == Function ? options.onShow : false,
						onHide		: options.onHide && options.onHide.constructor == Function ? options.onHide : false
					};
					var el = jQuery(this);
					el.bind('mouseover',jQuery.iTooltip.show);
					el.bind('focus',jQuery.iTooltip.focus);
				}
			}
		);
	}
};

jQuery.fn.ToolTip = jQuery.iTooltip.build;/**
 * Interface Elements for jQuery
 * TTabs
 * 
 * http://interface.eyecon.ro
 * 
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt) 
 * and GPL (GPL-LICENSE.txt) licenses.
 *   
 *
 *
 */

jQuery.iTTabs =
{
	doTab : function(e)
	{
		pressedKey = e.charCode || e.keyCode || -1;
		if (pressedKey == 9) {
			if (window.event) {
				window.event.cancelBubble = true;
				window.event.returnValue = false;
			} else {
				e.preventDefault();
				e.stopPropagation();
			}
			if (this.createTextRange) {
				document.selection.createRange().text="\t";
				this.onblur = function() { this.focus(); this.onblur = null; };
			} else if (this.setSelectionRange) {
				start = this.selectionStart;
				end = this.selectionEnd;
				this.value = this.value.substring(0, start) + "\t" + this.value.substr(end);
				this.setSelectionRange(start + 1, start + 1);
				this.focus();
			}
			return false;
		}
	},
	destroy : function()
	{
		return this.each(
			function()
			{
				if (this.hasTabsEnabled && this.hasTabsEnabled == true) {
					jQuery(this).unbind('keydown', jQuery.iTTabs.doTab);
					this.hasTabsEnabled = false;
				}
			}
		);
	},
	build : function()
	{
		return this.each(
			function()
			{
				if (this.tagName == 'TEXTAREA' && (!this.hasTabsEnabled || this.hasTabsEnabled == false)) {
					jQuery(this).bind('keydown', jQuery.iTTabs.doTab);
					this.hasTabsEnabled = true;
				}
			}
		);			
	}
};

jQuery.fn.extend (
	{
		/**
		 * Enable tabs in textareas
		 * 
		 * @name EnableTabs
		 * @description Enable tabs in textareas
		 *
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		EnableTabs : jQuery.iTTabs.build,
		/**
		 * Disable tabs in textareas
		 * 
		 * @name DisableTabs
		 * @description Disable tabs in textareas
		 *
		 * @type jQuery
		 * @cat Plugins/Interface
		 * @author Stefan Petre
		 */
		DisableTabs : jQuery.iTTabs.destroy
	}
);/**
 * Interface Elements for jQuery
 * utility function
 *
 * http://interface.eyecon.ro
 *
 * Copyright (c) 2006 Stefan Petre
 * Dual licensed under the MIT (MIT-LICENSE.txt)
 * and GPL (GPL-LICENSE.txt) licenses.
 *
 *
 */

jQuery.iUtil = {
	getPosition : function(e)
	{
		var x = 0;
		var y = 0;
		var es = e.style;
		var restoreStyles = false;
		if (jQuery(e).css('display') == 'none') {
			var oldVisibility = es.visibility;
			var oldPosition = es.position;
			restoreStyles = true;
			es.visibility = 'hidden';
			es.display = 'block';
			es.position = 'absolute';
		}
		var el = e;
		while (el){
			x += el.offsetLeft + (el.currentStyle && !jQuery.browser.opera ?parseInt(el.currentStyle.borderLeftWidth)||0:0);
			y += el.offsetTop + (el.currentStyle && !jQuery.browser.opera ?parseInt(el.currentStyle.borderTopWidth)||0:0);
			el = el.offsetParent;
		}
		el = e;
		while (el && el.tagName  && el.tagName.toLowerCase() != 'body')
		{
			x -= el.scrollLeft||0;
			y -= el.scrollTop||0;
			el = el.parentNode;
		}
		if (restoreStyles == true) {
			es.display = 'none';
			es.position = oldPosition;
			es.visibility = oldVisibility;
		}
		return {x:x, y:y};
	},
	getPositionLite : function(el)
	{
		var x = 0, y = 0;
		while(el) {
			x += el.offsetLeft || 0;
			y += el.offsetTop || 0;
			el = el.offsetParent;
		}
		return {x:x, y:y};
	},
	getSize : function(e)
	{
		var w = jQuery.css(e,'width');
		var h = jQuery.css(e,'height');
		var wb = 0;
		var hb = 0;
		var es = e.style;
		if (jQuery(e).css('display') != 'none') {
			wb = e.offsetWidth;
			hb = e.offsetHeight;
		} else {
			var oldVisibility = es.visibility;
			var oldPosition = es.position;
			es.visibility = 'hidden';
			es.display = 'block';
			es.position = 'absolute';
			wb = e.offsetWidth;
			hb = e.offsetHeight;
			es.display = 'none';
			es.position = oldPosition;
			es.visibility = oldVisibility;
		}
		return {w:w, h:h, wb:wb, hb:hb};
	},
	getSizeLite : function(el)
	{
		return {
			wb:el.offsetWidth||0,
			hb:el.offsetHeight||0
		};
	},
	getClient : function(e)
	{
		var h, w, de;
		if (e) {
			w = e.clientWidth;
			h = e.clientHeight;
		} else {
			de = document.documentElement;
			w = window.innerWidth || self.innerWidth || (de&&de.clientWidth) || document.body.clientWidth;
			h = window.innerHeight || self.innerHeight || (de&&de.clientHeight) || document.body.clientHeight;
		}
		return {w:w,h:h};
	},
	getScroll : function (e)
	{
		var t=0, l=0, w=0, h=0, iw=0, ih=0;
		if (e && e.nodeName.toLowerCase() != 'body') {
			t = e.scrollTop;
			l = e.scrollLeft;
			w = e.scrollWidth;
			h = e.scrollHeight;
			iw = 0;
			ih = 0;
		} else  {
			if (document.documentElement) {
				t = document.documentElement.scrollTop;
				l = document.documentElement.scrollLeft;
				w = document.documentElement.scrollWidth;
				h = document.documentElement.scrollHeight;
			} else if (document.body) {
				t = document.body.scrollTop;
				l = document.body.scrollLeft;
				w = document.body.scrollWidth;
				h = document.body.scrollHeight;
			}
			iw = self.innerWidth||document.documentElement.clientWidth||document.body.clientWidth||0;
			ih = self.innerHeight||document.documentElement.clientHeight||document.body.clientHeight||0;
		}
		return { t: t, l: l, w: w, h: h, iw: iw, ih: ih };
	},
	getMargins : function(e, toInteger)
	{
		var el = jQuery(e);
		var t = el.css('marginTop') || '';
		var r = el.css('marginRight') || '';
		var b = el.css('marginBottom') || '';
		var l = el.css('marginLeft') || '';
		if (toInteger)
			return {
				t: parseInt(t)||0,
				r: parseInt(r)||0,
				b: parseInt(b)||0,
				l: parseInt(l)
			};
		else
			return {t: t, r: r,	b: b, l: l};
	},
	getPadding : function(e, toInteger)
	{
		var el = jQuery(e);
		var t = el.css('paddingTop') || '';
		var r = el.css('paddingRight') || '';
		var b = el.css('paddingBottom') || '';
		var l = el.css('paddingLeft') || '';
		if (toInteger)
			return {
				t: parseInt(t)||0,
				r: parseInt(r)||0,
				b: parseInt(b)||0,
				l: parseInt(l)
			};
		else
			return {t: t, r: r,	b: b, l: l};
	},
	getBorder : function(e, toInteger)
	{
		var el = jQuery(e);
		var t = el.css('borderTopWidth') || '';
		var r = el.css('borderRightWidth') || '';
		var b = el.css('borderBottomWidth') || '';
		var l = el.css('borderLeftWidth') || '';
		if (toInteger)
			return {
				t: parseInt(t)||0,
				r: parseInt(r)||0,
				b: parseInt(b)||0,
				l: parseInt(l)||0
			};
		else
			return {t: t, r: r,	b: b, l: l};
	},
	getPointer : function(event)
	{
		var x = event.pageX || (event.clientX + (document.documentElement.scrollLeft || document.body.scrollLeft)) || 0;
		var y = event.pageY || (event.clientY + (document.documentElement.scrollTop || document.body.scrollTop)) || 0;
		return {x:x, y:y};
	},
	traverseDOM : function(nodeEl, func)
	{
		func(nodeEl);
		nodeEl = nodeEl.firstChild;
		while(nodeEl){
			jQuery.iUtil.traverseDOM(nodeEl, func);
			nodeEl = nodeEl.nextSibling;
		}
	},
	purgeEvents : function(nodeEl)
	{
		jQuery.iUtil.traverseDOM(
			nodeEl,
			function(el)
			{
				for(var attr in el){
					if(typeof el[attr] === 'function') {
						el[attr] = null;
					}
				}
			}
		);
	},
	centerEl : function(el, axis)
	{
		var clientScroll = jQuery.iUtil.getScroll();
		var windowSize = jQuery.iUtil.getSize(el);
		if (!axis || axis == 'vertically')
			jQuery(el).css(
				{
					top: clientScroll.t + ((Math.max(clientScroll.h,clientScroll.ih) - clientScroll.t - windowSize.hb)/2) + 'px'
				}
			);
		if (!axis || axis == 'horizontally')
			jQuery(el).css(
				{
					left:	clientScroll.l + ((Math.max(clientScroll.w,clientScroll.iw) - clientScroll.l - windowSize.wb)/2) + 'px'
				}
			);
	},
	fixPNG : function (el, emptyGIF) {
		var images = jQuery('img[@src*="png"]', el||document), png;
		images.each( function() {
			png = this.src;				
			this.src = emptyGIF;
			this.style.filter = "progid:DXImageTransform.Microsoft.AlphaImageLoader(src='" + png + "')";
		});
	}
};

// Helper function to support older browsers!
[].indexOf || (Array.prototype.indexOf = function(v, n){
	n = (n == null) ? 0 : n;
	var m = this.length;
	for (var i=n; i<m; i++)
		if (this[i] == v)
			return i;
	return -1;
});

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
/**
 * jQBrowser? v1.0.1 - Extend jQuery's browser detection capabilities and implement CSS browser selectors
 *   * http://www.alterform.com/resources/jqbrowser-2
 *
 * Built on the shoulders of (and stolen from :) ) giants:
 *   * John Resig <http://jquery.com/>
 *   * Peter-Paul Koch <http://www.quirksmode.org/?/js/detect.html>
 *	 * Dave Cardwell <http://davecardwell.co.uk/>
 *	 * Rafael Lima <http://rafael.adm.br/css_browser_selector/>
 *
 * Copyright (c) 2006 Nate Cavanaugh, dual licensed under the MIT and GPL
 * licenses:
 *   * http://www.opensource.org/licenses/mit-license.php
 *   * http://www.gnu.org/licenses/gpl.txt
 */

var jQBrowser2 = function() {
	var add_selectors = true;
    /**
     * The following functions and attributes form the internal methods and
     * state of the jQBrowser? plugin.  See the relevant function definition
     * later in the source for further information.
     *
     * Private.browser
     * Private.version
     * Private.OS
     *
     * Private.aol
     * Private.camino
     * Private.firefox
     * Private.flock
     * Private.icab
     * Private.konqueror
     * Private.mozilla
     * Private.msie
     * Private.netscape
     * Private.opera
     * Private.safari
     *
     * Private.linux
     * Private.mac
     * Private.win
     */
    var Private = {
        // Initially set to 'Unknown', if detected each of these properties will
        // be updated.
          'browser': 'Unknown',
          'version': {
              'number': undefined,
              'string': 'Unknown'
          },
               'OS': 'Unknown',

        // Initially set to false, if detected one of the following browsers
        // will be updated.
              'aol': false,
           'camino': false,
          'firefox': false,
            'flock': false,
             'icab': false,
        'konqueror': false,
          'mozilla': false,
             'msie': false,
         'netscape': false,
            'opera': false,
           'safari': false,

        // Initially set to false, if detected one of the following operating
        // systems will be updated.
           'iphone': false, 
			'linux': false,
              'mac': false,
              'win': false
    };
	

    /**
     * Loop over the items in 'data' trying to find a browser match with the
     * test in data[i].browser().  Once found, attempt to determine the
     * browser version.
     *
     *       'name': A string containing the full name of the browser.
     * 'identifier': By default this is a lowercase version of 'name', but
     *               this can be overwritten by explicitly defining an
     *               'identifier'.
     *    'browser': A function that returns a boolean value indicating
     *               whether or not the given browser is detected.
     *    'version': An optional function that overwrites the default version
     *               testing.  Must return the result of a .match().
     *
     * Please note that the order of the data array is important, as some
     * browsers contain details of others in their navigator.userAgent string.
     * For example, Flock's contains 'Firefox' so much come before Firefox's
     * test to avoid false positives.
     */
    for( var  i = 0,                    // counter
             ua = navigator.userAgent,  // the navigator's user agent string
             ve = navigator.vendor,     // the navigator's vendor string
           data = [                     // browser tests and data
                { // Safari <http://www.apple.com/safari/>
                          'name': 'Safari',
                       'browser':  /Apple/.test(ve)
                },
                { // Opera <http://www.opera.com/>
                          'name': 'Opera',
                       'browser': window.opera != undefined
                },
                { // iCab <http://www.icab.de/>
                          'name': 'iCab',
                       'browser': /iCab/.test(ve)
                },
                { // Konqueror <http://www.konqueror.org/>
                          'name': 'Konqueror',
                       'browser': /KDE/.test(ve)
                },
                { // AOL Explorer <http://downloads.channel.aol.com/browser>
                    'identifier': 'aol',
                          'name': 'AOL Explorer',
                       'browser': /America Online Browser/.test(ua),
                       'version': ua.match(/rev(\d+(?:\.\d+)+)/)
                },
                { // Flock <http://www.flock.com/>
                          'name': 'Flock',
                       'browser': /Flock/.test(ua)
                },
                { // Camino <http://www.caminobrowser.org/>
                          'name': 'Camino',
                       'browser': /Camino/.test(ve)
                },
                { // Firefox <http://www.mozilla.com/firefox/>
                          'name': 'Firefox',
                       'browser': /Firefox/.test(ua)
                },
                { // Netscape <http://browser.netscape.com/>
                          'name': 'Netscape',
                       'browser': /Netscape/.test(ua)
                },
                { // Internet Explorer <http://www.microsoft.com/windows/ie/>
                  //                   <http://www.microsoft.com/mac/ie/>
                    'identifier': 'msie',
                          'name': 'Internet Explorer',
                       'browser': /MSIE/.test(ua),
                       'version': ua.match(
                                          /MSIE (\d+(?:\.\d+)+(?:b\d*)?)/
                                      )
                },
                { // Mozilla <http://www.mozilla.org/products/mozilla1.x/>
                          'name': 'Mozilla',
                       'browser': /Gecko|Mozilla/.test(ua),
                       'version': ua.match(/rv:(\d+(?:\.\d+)+)/)
                 }
             ];
         i < data.length;
         i++
    ) {
        if( data[i].browser ) { // we have a match
            // If the identifier is not explicitly set, use a lowercase
            // version of the given name.
            var identifier = data[i].identifier ? data[i].identifier
                                                : data[i].name.toLowerCase();

            // Make a note that this browser was detected.
            Private[ identifier ] = true;

            // $.browser.browser() will now return the correct browser.
            Private.browser = data[i].name;

            var result;
            if( data[i].version != undefined && (result = data[i].version) ) {
                // Use the explicitly set test for browser version.
                Private.version.string = result[1];
                Private.version.number = parseFloat( result[1] );
            } else {
                // Otherwise use the default test which searches for the
                // version number after the browser name in the user agent
                // string.
                var re = new RegExp(
                    data[i].name + '(?:\\s|\\/)(\\d+(?:\\.\\d+)+(?:(?:a|b)\\d*)?)'
                );

                result = ua.match(re);
                if( result != undefined ) {
                    Private.version.string = result[1];
                    Private.version.number = parseFloat( result[1] );
                }
            }
			
			//If we're on a Gecko based browser, mark Private.mozilla as true
			if (/firefox|camino|flock|netscape/i.test(Private.browser)) {
				Private.mozilla = true;
			}

            // Once we've detected the browser there is no need to check the
            // others.
            break;
        }
		
    };



    /**
     * Loop over the items in 'data' trying to find a operating system match
     * with the test in data[i].os().
     *
     *       'name': A string containing the full name of the operating
     *               system.
     * 'identifier': By default this is a lowercase version of 'name', but
     *               this can be overwritten by explicitly defining an
     *               'identifier'.
     *         'OS': A function that returns a boolean value indicating
     *               whether or not the given operating system is detected.
     */
    for( var  i = 0,                  // counter
             pl = navigator.platform, // the navigator's platform string
           data = [                   // OS data and tests
                { // Microsoft Windows <http://www.microsoft.com/windows/>
                    'identifier': 'win',
                          'name': 'Windows',
                            'OS': /Win/.test(pl)
                },
                { // Apple Mac OS <http://www.apple.com/macos/>
                          'name': 'Mac',
                            'OS': /Mac/.test(pl)
                },
                { // Linux <http://www.linux.org/>
                          'name': 'Linux',
                            'OS': /Linux/.test(pl)
                },
				{ // iPhone <http://www.apple.com/iphone>
						  'name': 'iPhone',
						    'OS': /iPhone/.test(pl) 
				}
           ];
       i < data.length;
       i++
    ) {
        if( data[i].OS ) { // we have a match
            // If the identifier is not explicitly set, use a lowercase
            // version of the given name.
            var identifier = data[i].identifier ? data[i].identifier
                                                : data[i].name.toLowerCase();

            // Make a note that the OS was detected.
            Private[ identifier ] = true;

            // $.browser.OS() will now return the correct OS.
            Private.OS = data[i].name;

            // Once we've detected the browser there is no need to check the
            // others.
            break;
        }
    };
	/**
     * The following functions and attributes form the Public interface of the
     * jQBrowser? plugin, accessed externally through the $.browser object.
     * See the relevant function definition later in the source for further
     * information.
     *
     * $.browser.browser
     * $.browser.version.number()
     * $.browser.version.string()
	 * * * version.string() and version.number both take arguments ( best to use 'round'), to round out the version number
     * $.browser.OS
     *
     * $.browser.aol
     * $.browser.camino
     * $.browser.firefox
     * $.browser.flock
     * $.browser.icab
     * $.browser.konqueror
     * $.browser.mozilla
     * $.browser.msie
     * $.browser.netscape
     * $.browser.opera
     * $.browser.safari
     *
     * $.browser.linux
     * $.browser.mac
     * $.browser.win
     */
	var Public = {
        // The current browser, its version as a number or a string, and the
        // operating system its running on.
          'browser': Private.browser,
          'version': {
              'number': function() { return !arguments.length ? Private.version.number : Math.floor(Private.version.number); },
              'string': function() { return !arguments.length ? Private.version.string : this.number('round').toString(); }
          },
               'OS': Private.OS,

        // A boolean value indicating whether or not the given browser was
        // detected.
              'aol': Private.aol,
           'camino': Private.camino,
          'firefox': Private.firefox,
            'flock': Private.flock,
             'icab': Private.icab,
        'konqueror': Private.konqueror,
          'mozilla': Private.mozilla,
             'msie': Private.msie,
         'netscape': Private.netscape,
            'opera': Private.opera,
           'safari': Private.safari,

        // A boolean value indicating whether or not the given OS was
        // detected.
		   'iphone': Private.iphone, 
            'linux': Private.linux,
              'mac': Private.mac,
              'win': Private.win
    };
	
	jQuery.browser = Public;
	// Browser selectors
	if(!add_selectors){return;}
	var bn = jQuery.browser.browser.toLowerCase();
	var bv = jQuery.browser.version.string('round');
	var b = jQuery.browser.msie // IE
						? 'ie ie'+jQuery.browser.version.string('round')
						: (jQuery.browser.mozilla) // Gecko
							? 'gecko '+ bn + bv + ' ' + bn
								: (jQuery.browser.opera) // Opera
									? 'opera ' + bn + bv
										: (jQuery.browser.safari) // Safari
											? 'safari ' + bn + bv
												: jQuery.browser.konqueror // Konqueror
													? 'konqueror ' + bn + bv
														: jQuery.browser.icab // iCab
															? 'icab ' + bn + bv
																: jQuery.browser.aol // AOL
																 	? 'aol ' + bn + bv
																	: '',
		os=jQuery.browser.linux?'linux':jQuery.browser.iphone?'iphone':jQuery.browser.mac?'mac':jQuery.browser.win?'win':'';
		jQuery('html').addClass(b).addClass(os).addClass('js');
}();

/*
+-----------------------------------------------------------------------+
| Copyright (c) 2006-2007 Mika Tuupola, Dylan Verheul                   |
| All rights reserved.                                                  |
|                                                                       |
| Redistribution and use in source and binary forms, with or without    |
| modification, are permitted provided that the following conditions    |
| are met:                                                              |
|                                                                       |
| o Redistributions of source code must retain the above copyright      |
|   notice, this list of conditions and the following disclaimer.       |
| o Redistributions in binary form must reproduce the above copyright   |
|   notice, this list of conditions and the following disclaimer in the |
|   documentation and/or other materials provided with the distribution.|
|                                                                       |
| THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS   |
| "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT     |
| LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR |
| A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT  |
| OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, |
| SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT      |
| LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, |
| DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY |
| THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT   |
| (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE |
| OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.  |
|                                                                       |
+-----------------------------------------------------------------------+
*/

/* $Id$ */

/**
  * jQuery inplace editor plugin (version 1.3.x)
  *
  * Based on editable by Dylan Verheul <dylan@dyve.net>
  * http://www.dyve.net/jquery/?editable
  *
  * @name  jEditable
  * @type  jQuery
  * @param String  target             POST URL or function name to send edited content
  * @param Hash    options            additional options 
  * @param String  options[name]      POST parameter name of edited content
  * @param String  options[id]        POST parameter name of edited div id
  * @param String  options[type]      text, textarea or select
  * @param Integer options[rows]      number of rows if using textarea
  * @param Integer options[cols]      number of columns if using textarea
  * @param Mixed   options[height]    'auto' or height in pixels
  * @param Mixed   options[width]     'auto' or width in pixels 
  * @param String  options[loadurl]   URL to fetch content before editing
  * @param String  options[loadtype]  Request type for load url. Should be GET or POST.
  * @param String  options[data]      Or content given as paramameter.
  * @param String  options[indicator] indicator html to show when saving
  * @param String  options[tooltip]   optional tooltip text via title attribute
  * @param String  options[event]     jQuery event such as 'click' of 'dblclick'
  * @param String  options[onblur]    'cancel', 'submit' or 'ignore'
  * @param String  options[submit]    submit button value, empty means no button
  * @param String  options[cancel]    cancel button value, empty means no button
  * @param String  options[cssclass]  CSS class to apply to input form. 'inherit' to copy from parent.
  * @param String  options[style]     Style to apply to input form 'inherit' to copy from parent.
  * @param String  options[select]    true or false, when true text is highlighted
  *             
  */

jQuery.fn.editable = function(target, options, callback) {

    /* prevent elem has no properties error */
    if (this.length == 0) { 
        return(this); 
    };
    
    var settings = {
        target   : target,
        name     : 'value',
        id       : 'id',
        type     : 'text',
        width    : 'auto',
        height   : 'auto',
        event    : 'click',
        onblur   : 'cancel',
        loadtype : 'GET'
    };
        
    if(options) {
        jQuery.extend(settings, options);
    };
    
    var callback = callback || function() { };
      
    jQuery(this).attr('title', settings.tooltip);

    jQuery(this)[settings.event](function(e) {

        /* save this to self because this changes when scope changes */
        var self = this;

        /* prevent throwing an exeption if edit field is clicked again */
        if (self.editing) {
            return;
        }

        /* figure out how wide and tall we are */
        var width = 
            ('auto' == settings.width)  ? jQuery(self).width()  : settings.width;
        var height = 
            ('auto' == settings.height) ? jQuery(self).height() : settings.height;

        self.editing    = true;
        self.revert     = jQuery(self).html();
        self.innerHTML  = '';

        /* create the form object */
        var f = document.createElement('form');
        
        /* apply css or style or both */
        if (settings.cssclass) {
            if ('inherit' == settings.cssclass) {
                jQuery(f).attr('class', jQuery(self).attr('class'));
            } else {
                jQuery(f).attr('class', settings.cssclass);
            }
        }
        
        if (settings.style) {
            if ('inherit' == settings.style) {
                jQuery(f).attr('style', jQuery(self).attr('style'));
                /* IE needs the second line or display wont be inherited */
                jQuery(f).css('display', jQuery(self).css('display'));                
            } else {
                jQuery(f).attr('style', settings.style);
            }
        }
        
        /*  main input element */
        var i;
        switch (settings.type) {
            case 'textarea':
                i = document.createElement('textarea');
                if (settings.rows) {
                    i.rows = settings.rows;
                } else {
                    jQuery(i).height(height);
                }
                if (settings.cols) {
                    i.cols = settings.cols;
                } else {
                    jQuery(i).width(width);
                }   
                break;
            case 'select':
                i = document.createElement('select');
                break;
            default:
                i = document.createElement('input');
                i.type  = settings.type;
                jQuery(i).width(width);
                jQuery(i).height(height);
                /* https://bugzilla.mozilla.org/show_bug.cgi?id=236791 */
                i.setAttribute('autocomplete','off');
        }

        /* maintain bc with 1.1.1 and earlier versions */        
        if (settings.getload) {
            settings.loadurl    = settings.getload;
            settings.loadtype = 'GET';
        } else if (settings.postload) {
            settings.loadurl    = settings.postload;
            settings.loadtype = 'POST';
        }

        /* set input content via POST, GET, given data or existing value */
        if (settings.loadurl) {
            var data = {};
            data[settings.id] = self.id;
            jQuery.ajax({
               type : settings.loadtype,
               url  : settings.loadurl,
               data : data,
               success: function(str) {
                  setInputContent(str);
               }
            });
        } else if (settings.data) {
            setInputContent(settings.data);
        } else { 
            setInputContent(self.revert);
        }

        i.name  = settings.name;
        f.appendChild(i);

        if (settings.submit) {
            var b = document.createElement('input');
            b.type = 'submit';
            b.value = settings.submit;
            f.appendChild(b);
        }

        if (settings.cancel) {
            var b = document.createElement('input');
            b.type = 'button';
            b.value = settings.cancel;
            jQuery(b).click(function() {
                reset();
            });
            f.appendChild(b);
        }

        /* add created form to self */
        self.appendChild(f);

        i.focus();
        
        /* highlight input contents when requested */
        if (settings.select) {
            i.select();
        }
         
        /* discard changes if pressing esc */
        jQuery(i).keydown(function(e) {
            if (e.keyCode == 27) {
                e.preventDefault();
                reset();
            }
        });

        /* discard, submit or nothing with changes when clicking outside */
        /* do nothing is usable when navigating with tab */
        var t;
        if ('cancel' == settings.onblur) {
            jQuery(i).blur(function(e) {
                t = setTimeout(reset, 500)
            });
        } else if ('submit' == settings.onblur) {
            jQuery(i).blur(function(e) {
                jQuery(f).submit();
            });
        } else {
            jQuery(i).blur(function(e) {
              /* TODO: maybe something here */
            });
        }

        jQuery(f).submit(function(e) {

            if (t) { 
                clearTimeout(t);
            }

            /* do no submit */
            e.preventDefault(); 

            /* check if given target is function */
            if (jQuery.isFunction(settings.target)) {
                var str = settings.target.apply(self, [jQuery(i).val(), settings]);
                self.innerHTML = str;
                self.editing = false;
                callback.apply(self, [self.innerHTML, settings]);
            } else {
                /* add edited content and id of edited element to POST */           
                var p = {};
                p[i.name] = jQuery(i).val();
                p[settings.id] = self.id;

                /* show the saving indicator */
                jQuery(self).html(settings.indicator);
                jQuery.post(settings.target, p, function(str) {
                    self.innerHTML = str;
                    self.editing = false;
                    callback.apply(self, [self.innerHTML, settings]);
                });
            }
                        
            return false;
        });

        function reset() {
            self.innerHTML = self.revert;
            self.editing   = false;
        };
        
        function setInputContent(str) {
            if (jQuery.isFunction(str)) {
                var str = str.apply(self, [self.revert, settings]);
            }
            switch (settings.type) { 	 
                case 'select': 	 
                    if (String == str.constructor) { 	 
                        eval ("var json = " + str);
                        for (var key in json) {
                            if ('selected' == key) {
                                continue;
                            } 
                            o = document.createElement('option'); 	 
                            o.value = key;
                            var text = document.createTextNode(json[key]);
                            o.appendChild(text);
                            if (key == json['selected']) {
                                o.selected = true;
                            }
                            i.appendChild(o); 	 
                        }
                    } 	 
                    break; 	 
                default: 	 
                    i.value = str; 	 
                    break; 	 
            } 	 
        }

    });

    return(this);
};
(function ($) {
    var m = {
            '\b': '\\b',
            '\t': '\\t',
            '\n': '\\n',
            '\f': '\\f',
            '\r': '\\r',
            '"' : '\\"',
            '\\': '\\\\'
        },
        s = {
            'array': function (x) {
                var a = ['['], b, f, i, l = x.length, v;
                for (i = 0; i < l; i += 1) {
                    v = x[i];
                    f = s[typeof v];
                    if (f) {
                        v = f(v);
                        if (typeof v == 'string') {
                            if (b) {
                                a[a.length] = ',';
                            }
                            a[a.length] = v;
                            b = true;
                        }
                    }
                }
                a[a.length] = ']';
                return a.join('');
            },
            'boolean': function (x) {
                return String(x);
            },
            'null': function (x) {
                return "null";
            },
            'number': function (x) {
                return isFinite(x) ? String(x) : 'null';
            },
            'object': function (x) {
                if (x) {
                    if (x instanceof Array) {
                        return s.array(x);
                    }
                    var a = ['{'], b, f, i, v;
                    for (i in x) {
                        v = x[i];
                        f = s[typeof v];
                        if (f) {
                            v = f(v);
                            if (typeof v == 'string') {
                                if (b) {
                                    a[a.length] = ',';
                                }
                                a.push(s.string(i), ':', v);
                                b = true;
                            }
                        }
                    }
                    a[a.length] = '}';
                    return a.join('');
                }
                return 'null';
            },
            'string': function (x) {
                if (/["\\\x00-\x1f]/.test(x)) {
                    x = x.replace(/([\x00-\x1f\\"])/g, function(a, b) {
                        var c = m[b];
                        if (c) {
                            return c;
                        }
                        c = b.charCodeAt();
                        return '\\u00' +
                            Math.floor(c / 16).toString(16) +
                            (c % 16).toString(16);
                    });
                }
                return '"' + x + '"';
            }
        };

	$.toJSON = function(v) {
		var f = isNaN(v) ? s[typeof v] : s['number'];
		if (f) return f(v);
	};
	
	$.parseJSON = function(v, safe) {
		if (safe === undefined) safe = $.parseJSON.safe;
		if (safe && !/^("(\\.|[^"\\\n\r])*?"|[,:{}\[\]0-9.\-+Eaeflnr-u \n\r\t])+?$/.test(v))
			return undefined;
		return eval('('+v+')');
	};
	
	$.parseJSON.safe = false;

})(jQuery);

/*
 * jQuery Media Plugin for converting elements into rich media content.
 *
 * Examples and documentation at: http://malsup.com/jquery/media/
 * Copyright (c) 2007 M. Alsup
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 *
 * @author: M. Alsup
 * @version: 0.66 (6/08/2007)
 * @requires jQuery v1.1.2 or later
 *
 * Supported Media Players:
 *    - Flash
 *    - Quicktime
 *    - Real Player
 *    - Silverlight
 *    - Windows Media Player
 *    - iframe
 *
 * Supported Media Formats:
 *   Any types supported by the above players, such as:
 *     Video: asf, avi, flv, mov, mpg, mpeg, mp4, qt, smil, swf, wmv, 3g2, 3gp
 *     Audio: aif, aac, au, gsm, mid, midi, mov, mp3, m4a, snd, rm, wav, wma
 *     Other: bmp, html, pdf, psd, qif, qtif, qti, tif, tiff, xaml
 *
 * Thanks to Mark Hicken for helping me debug this on Safari!
 */
(function($) {

/**
 * Chainable method for converting elements into rich media.
 *
 * @name media
 * @param Object options Options object
 * @param Function callback fn invoked for each matched element before conversion
 * @param Function callback fn invoked for each matched element after conversion
 * @cat Plugins/media
 */
$.fn.media = function(options, f1, f2) {
    return this.each(function() {
        if (typeof options == 'function') {
            f2 = f1;
            f1 = options;
            options = {};
        }
        var o = getSettings(this, options);
        // pre-conversion callback, passes original element and fully populated options
        if (typeof f1 == 'function') f1(this, o);
        
        var r = getTypesRegExp();
        var m = r.exec(o.src) || [''];
        o.type ? m[0] = o.type : m.shift();
        for (var i=0; i < m.length; i++) {
            fn = m[i].toLowerCase();
            if (isDigit(fn[0])) fn = 'fn' + fn; // fns can't begin with numbers
            if (!$.fn.media[fn]) 
                continue;  // unrecognized media type
            // normalize autoplay settings
            var player = $.fn.media[fn+'_player'];
            if (!o.params) o.params = {};
            if (player) {
                var num = player.autoplayAttr == 'autostart';
                o.params[player.autoplayAttr || 'autoplay'] = num ? (o.autoplay ? 1 : 0) : o.autoplay ? true : false;
            }
            var $div = $.fn.media[fn](this, o);

            $div.css('backgroundColor', o.bgColor).width(o.width);
            
            // post-conversion callback, passes original element, new div element and fully populated options
            if (typeof f2 == 'function') f2(this, $div[0], o);
            break;
        }
    });
};

/**
 * Chainable method for preparing elements to display rich media with
 * a page overlay.
 *
 * @name mediabox
 * @param Object options Options object
 * @param Object css values for the media div
 * @cat Plugins/media
 */
$.fn.mediabox = function(options, css) {
    return this.click(function() {
        if (typeof $.blockUI == 'undefined' || typeof $.fn.displayBox == 'undefined') {
            if (typeof $.fn.mediabox.warning != 'undefined') return this; // one warning is enough
            $.fn.mediabox.warning = 1;
            alert('The mediabox method requires blockUI v1.20 or later.');
            return false;
        }
        var o, div=0, $e = $(this).clone();
        $e.appendTo('body').hide().css({margin: 0});
        options = $.extend({}, options, { autoplay: 1 }); // force autoplay in box mode
        $e.media(options, function(){}, function(origEl, newEl, opts) {
            div = newEl;
            o = opts;
        });
        if (!div) return false;
        // don't pull element from the dom on Safari
        var $div = $.browser.safari ? $(div).hide() : $(div).remove();

        if (o.loadingImage)
            $div.css({
                backgroundImage:    'url('+o.loadingImage+')',
                backgroundPosition: 'center center',
                backgroundRepeat:   'no-repeat'
            });
        if (o.boxTitle)
            $div.prepend('<div style="margin:0;padding:0">' + o.boxTitle + '</div>');
        
        if (css) $div.css(css);

        $div.displayBox( { width: o.width, height: o.height }, function(el) {
            // quirkiness; sometimes media doesn't stop when removed from the DOM (especially in IE)
            $(el).find('object,embed').each(function() {
                try { this.Stop();   } catch(e) {}  // quicktime
                try { this.DoStop(); } catch(e) {}  // real
                try { this.controls.stop(); } catch(e) {} // windows media player
            });
        });
        return false;
    });
};

  
/**
 * Non-chainable method for adding or changing file format / player mapping
 * @name mapFormat
 * @param String format File format extension (ie: mov, wav, mp3)
 * @param String player Player name to use for the format (one of: flash, quicktime, realplayer, winmedia, silverlight or iframe
 */
$.fn.media.mapFormat = function(format, player) {
    if (!format || !player || !$.fn.media.defaults.players[player]) return; // invalid
    format = format.toLowerCase();
    if (isDigit(format[0])) format = 'fn' + format;
    $.fn.media[format] = $.fn.media[player];
};


// global defautls; override as needed
$.fn.media.defaults = {
    width:         400,
    height:        400,
    preferMeta:    1,         // true if markup metadata takes precedence over options object
    autoplay:      0,         // normalized cross-player setting
    bgColor:       '#ffffff', // background color
    params:        {},        // added to object element as param elements; added to embed element as attrs
    attrs:         {},        // added to object and embed elements as attrs
    flashvars:     {},        // added to flash content as flashvars param/attr
    flashVersion:  '7',       // required flash version
    
    // MediaBox options
    boxTitle:      null,      // MediaBox titlebar
    loadingImage:  null,      // MediaBox loading indicator
    
    // default flash video and mp3 player (@see: http://jeroenwijering.com/?item=Flash_Media_Player)
    flvPlayer:     'mediaplayer.swf',
    mp3Player:     'mediaplayer.swf',
    
    // @see http://msdn2.microsoft.com/en-us/library/bb412401.aspx
    silverlight: {
        inplaceInstallPrompt: 'true', // display in-place install prompt?
        isWindowless:         'true', // windowless mode (false for wrapping markup)
        framerate:            '24',   // maximum framerate
        version:              '0.9',  // Silverlight version
        onError:              null,   // onError callback
        onLoad:               null,   // onLoad callback
        initParams:           null,   // object init params
        userContext:          null    // callback arg passed to the load callback
    }
};

// Media Players; think twice before overriding
$.fn.media.defaults.players = {
    flash: {
        types:        'flv,mp3,swf',
        oAttrs:   {
            classid:  'clsid:d27cdb6e-ae6d-11cf-96b8-444553540000',
            type:     'application/x-oleobject',
            codebase: 'http://fpdownload.macromedia.com/pub/shockwave/cabs/flash/swflash.cab#version=' + $.fn.media.defaults.flashVersion
        },
        eAttrs: {
            type:         'application/x-shockwave-flash',
            pluginspage:  'http://www.adobe.com/go/getflashplayer'
        }        
    },
    quicktime: {
        types:        'aif,aiff,aac,au,bmp,gsm,mov,mid,midi,mpg,mpeg,mp4,m4a,psd,qt,qtif,qif,qti,snd,tif,tiff,wav,3g2,3gp',
        oAttrs:   {
            classid:  'clsid:02BF25D5-8C17-4B23-BC80-D3488ABDDC6B',
            codebase: 'http://www.apple.com/qtactivex/qtplugin.cab'
        },
        eAttrs: {
            pluginspage:  'http://www.apple.com/quicktime/download/'
        }
    },
    realplayer: {
        types:        'ra,ram,rm,rpm,rv,smi,smil',
        autoplayAttr: 'autostart',
        oAttrs:   {
            classid:  'clsid:CFCDAA03-8BE4-11cf-B84B-0020AFBBCCFA'
        },
        eAttrs: {
            type:         'audio/x-pn-realaudio-plugin',
            pluginspage:  'http://www.real.com/player/'
        }
    },
    winmedia: {
        types:        'asf,avi,wma,wmv',
        autoplayAttr: 'autostart',
        oUrl:         'url',
        oAttrs:   {
            classid:  'clsid:6BF52A52-394A-11d3-B153-00C04F79FAA6',
            type:     'application/x-oleobject'
        },
        eAttrs: {
            type:         'application/x-mplayer2',
            pluginspage:  'http://www.microsoft.com/Windows/MediaPlayer/'
        }        
    },
    // special cases
    iframe: {
        types: 'html,pdf'
    },
    silverlight: {
        types: 'xaml'
    }
};

//
//  everything below here is private
//


var counter = 1;

for (var player in $.fn.media.defaults.players) {
    var types = $.fn.media.defaults.players[player].types;
    $.each(types.split(','), function(i,o) {
        if (isDigit(o[0])) o = 'fn' + o;
        $.fn.media[o] = $.fn.media[player] = getGenerator(player);
        $.fn.media[o+'_player'] = $.fn.media.defaults.players[player];
    });
};

function getTypesRegExp() {
    var types = '';
    for (var player in $.fn.media.defaults.players) {
        if (types.length) types += ',';
        types += $.fn.media.defaults.players[player].types;
    };
    return new RegExp('\\.(' + types.replace(/,/g,'|') + ')\\b');
};

function getGenerator(player) {
    return function(el, options) {
        return generate(el, options, player);
    };
};

function isDigit(c) {
    return '0123456789'.indexOf(c) > -1;
};

// flatten all possible options: global defaults, meta, option obj
function getSettings(el, options) {
    options = options || {};
    var $el = $(el);
    
    var cls = el.className || '';
    var meta = $.meta ? $el.data() : {};
    var w = meta.width  || parseInt(((cls.match(/w:(\d+)/)||[])[1]||0));
    var h = meta.height || parseInt(((cls.match(/h:(\d+)/)||[])[1]||0));
    if (w) meta.width  = w;
    if (h) meta.height = h;
    if (cls) meta.cls = cls;

    var a = $.fn.media.defaults;
    var b = $.meta && $.fn.media.defaults.preferMeta ? options : meta;
    var c = b == options ? meta : options;

    var p = { params: { bgColor: options.bgColor || $.fn.media.defaults.bgColor } };
    var opts = $.extend({}, a, b, c);
    $.each(['attrs','params','flashvars','silverlight'], function(i,o) {
        opts[o] = $.extend({}, p[o] || {}, a[o] || {}, b[o] || {}, c[o] || {});
    });

    if (typeof opts.caption == 'undefined') opts.caption = $el.text();

    // make sure we have a source!
    opts.src = opts.src || $el.attr('href') || $el.attr('src') || 'unknown';
    return opts;
};

//
//  Flash Player
//

// generate flash using SWFObject if possible
$.fn.media.swf = function(el, opts) {
    if (typeof SWFObject == 'undefined') {
        // roll our own
        if (opts.flashvars) {
            var a = [];
            for (var f in opts.flashvars)
                a.push(f + '=' + opts.flashvars[f]);
            if (!opts.params) opts.params = {};
            opts.params.flashvars = a.join('&');
        }
        return generate(el, opts, 'flash');
    }

    var id = el.id ? (' id="'+el.id+'"') : '';
    var cls = opts.cls ? (' class="' + opts.cls + '"') : '';
    var $div = $('<div' + id + cls + '>');
    $(el).after($div).remove();

    var so = new SWFObject(opts.src, 'movie_player_' + counter++, opts.width, opts.height, opts.flashVersion, opts.bgColor);
    for (var p in opts.params)
        if (p != 'bgColor') so.addParam(p, opts.params[p]);
    for (var f in opts.flashvars)
        so.addVariable(f, opts.flashvars[f]);
    so.write($div[0]);

    if (opts.caption) $('<div>').appendTo($div).html(opts.caption);
    return $div;
};

// map flv and mp3 files to the swf player by default
$.fn.media.flv = $.fn.media.mp3 = function(el, opts) {
    var src = opts.src;
    var player = /\.mp3\b/i.test(src) ? $.fn.media.defaults.mp3Player : $.fn.media.defaults.flvPlayer;
    opts.src = player;
    opts.src = opts.src + '?file=' + src;
    opts.flashvars = $.extend({}, { file: src }, opts.flashvars );
    return $.fn.media.swf(el, opts);
};

//
//  Silverlight
//
$.fn.media.xaml = function(el, opts) {
    if (!window.Sys || !window.Sys.Silverlight) {
        if ($.fn.media.xaml.warning) return;
        $.fn.media.xaml.warning = 1;
        alert('You must include the Silverlight.js script.');
        return;
    }

    var props = {
        width: opts.width,
        height: opts.height,
        background: opts.bgColor,
        inplaceInstallPrompt: opts.silverlight.inplaceInstallPrompt,
        isWindowless: opts.silverlight.isWindowless,
        framerate: opts.silverlight.framerate,
        version: opts.silverlight.version
    };
    var events = {
        onError: opts.silverlight.onError,
        onLoad: opts.silverlight.onLoad
    };

    var id1 = el.id ? (' id="'+el.id+'"') : '';
    var id2 = opts.id || 'AG' + counter++;
    // convert element to div
    var cls = opts.cls ? (' class="' + opts.cls + '"') : '';
    var $div = $('<div' + id1 + cls + '>');
    $(el).after($div).remove();
    
    Sys.Silverlight.createObjectEx({
        source: opts.src,
        initParams: opts.silverlight.initParams,
        userContext: opts.silverlight.userContext,
        id: id2,
        parentElement: $div[0],
        properties: props,
        events: events
    });

    if (opts.caption) $('<div>').appendTo($div).html(opts.caption);
    return $div;
};

//
// generate object/embed markup
//
function generate(el, opts, player) {
    var $el = $(el);
    var o = $.fn.media.defaults.players[player];
    
    if (player == 'iframe') {
        var o = $('<iframe' + ' width="' + opts.width + '" height="' + opts.height + '" >');
        o.attr('src', opts.src);
        o.css('backgroundColor', o.bgColor);
    }
    else if ($.browser.msie) {
        var a = ['<object width="' + opts.width + '" height="' + opts.height + '" '];
        for (var key in opts.attrs)
            a.push(key + '="'+opts.attrs[key]+'" ');
        for (var key in o.oAttrs || {})
            a.push(key + '="'+o.oAttrs[key]+'" ');
        a.push('></ob'+'ject'+'>');
        var p = ['<param name="' + (o.oUrl || 'src') +'" value="' + opts.src + '">'];
        for (var key in opts.params)
            p.push('<param name="'+ key +'" value="' + opts.params[key] + '">');
        var o = document.createElement(a.join(''));
        for (var i=0; i < p.length; i++)
            o.appendChild(document.createElement(p[i]));
    }
    else {
        var a = ['<embed width="' + opts.width + '" height="' + opts.height + '" style="display:block"'];
        if (opts.src) a.push(' src="' + opts.src + '" ');
        for (var key in opts.attrs)
            a.push(key + '="'+opts.attrs[key]+'" ');
        for (var key in o.eAttrs || {})
            a.push(key + '="'+o.eAttrs[key]+'" ');
        for (var key in opts.params)
            a.push(key + '="'+opts.params[key]+'" ');
        a.push('></em'+'bed'+'>');
    }
    // convert element to div
    var id = el.id ? (' id="'+el.id+'"') : '';
    var cls = opts.cls ? (' class="' + opts.cls + '"') : '';
    var $div = $('<div' + id + cls + '>');
    $el.after($div).remove();
    ($.browser.msie || player == 'iframe') ? $div.append(o) : $div.html(a.join(''));
    if (opts.caption) $('<div>').appendTo($div).html(opts.caption);
    return $div;
};


})(jQuery);

/**
 * Tabs - jQuery plugin for accessible, unobtrusive tabs
 * @requires jQuery v1.0.3
 *
 * http://stilbuero.de/tabs/
 *
 * Copyright (c) 2006 Klaus Hartl (stilbuero.de)
 * Dual licensed under the MIT and GPL licenses:
 * http://www.opensource.org/licenses/mit-license.php
 * http://www.gnu.org/licenses/gpl.html
 *
 * Version: 2.7.3
 */

(function($) { // block scope

$.extend({
    tabs: {
        remoteCount: 0 // TODO in Tabs 3 this is going to be more cleanly in one single namespace
    }
});

/**
 * Create an accessible, unobtrusive tab interface based on a particular HTML structure.
 *
 * The underlying HTML has to look like this:
 *
 * <div id="container">
 *     <ul>
 *         <li><a href="#fragment-1">Section 1</a></li>
 *         <li><a href="#fragment-2">Section 2</a></li>
 *         <li><a href="#fragment-3">Section 3</a></li>
 *     </ul>
 *     <div id="fragment-1">
 *
 *     </div>
 *     <div id="fragment-2">
 *
 *     </div>
 *     <div id="fragment-3">
 *
 *     </div>
 * </div>
 *
 * Each anchor in the unordered list points directly to a section below represented by one of the
 * divs (the URI in the anchor's href attribute refers to the fragment with the corresponding id).
 * Because such HTML structure is fully functional on its own, e.g. without JavaScript, the tab
 * interface is accessible and unobtrusive.
 *
 * A tab is also bookmarkable via hash in the URL. Use the History/Remote plugin (Tabs will
 * auto-detect its presence) to fix the back (and forward) button.
 *
 * @example $('#container').tabs();
 * @desc Create a basic tab interface.
 * @example $('#container').tabs(2);
 * @desc Create a basic tab interface with the second tab initially activated.
 * @example $('#container').tabs({disabled: [3, 4]});
 * @desc Create a tab interface with the third and fourth tab being disabled.
 * @example $('#container').tabs({fxSlide: true});
 * @desc Create a tab interface that uses slide down/up animations for showing/hiding tab
 *       content upon tab switching.
 *
 * @param Number initial An integer specifying the position of the tab (no zero-based index) that
 *                       gets activated at first (on page load). Two alternative ways to specify
 *                       the active tab will overrule this argument. First a li element
 *                       (representing one single tab) belonging to the selected tab class, e.g.
 *                       set the selected tab class (default: "tabs-selected", see option
 *                       selectedClass) for one of the unordered li elements in the HTML source.
 *                       In addition if a fragment identifier/hash in the URL of the page refers
 *                       to the id of a tab container of a tab interface the corresponding tab will
 *                       be activated and both the initial argument as well as an eventually
 *                       declared class attribute will be overruled. Defaults to 1 if omitted.
 * @param Object settings An object literal containing key/value pairs to provide optional settings.
 * @option Array<Number> disabled An array containing the position of the tabs (no zero-based index)
 *                                that should be disabled on initialization. Default value: null.
 *                                A tab can also be disabled by simply adding the disabling class
 *                                (default: "tabs-disabled", see option disabledClass) to the li
 *                                element representing that particular tab.
 * @option Boolean bookmarkable Boolean flag indicating if support for bookmarking and history (via
 *                              changing hash in the URL of the browser) is enabled. Default value:
 *                              false, unless the History/Remote plugin is included. In that case the
 *                              default value becomes true. @see $.ajaxHistory.initialize
 * @option Boolean remote Boolean flag indicating that tab content has to be loaded remotely from
 *                        the url given in the href attribute of the tab menu anchor elements.
 * @option String spinner The content of this string is shown in a tab while remote content is loading.
 *                        Insert plain text as well as an img here. To turn off this notification
 *                        pass an empty string or null. Default: "Loading&#8230;".
 * @option String hashPrefix A String that is used for constructing the hash the link's href attribute
 *                           of a remote tab gets altered to, such as "#remote-1".
 *                           Default value: "remote-tab-".
 * @option Boolean fxFade Boolean flag indicating whether fade in/out animations are used for tab
 *                        switching. Can be combined with fxSlide. Will overrule fxShow/fxHide.
 *                        Default value: false.
 * @option Boolean fxSlide Boolean flag indicating whether slide down/up animations are used for tab
 *                         switching. Can be combined with fxFade. Will overrule fxShow/fxHide.
 *                         Default value: false.
 * @option String|Number fxSpeed A string representing one of the three predefined speeds ("slow",
 *                               "normal", or "fast") or the number of milliseconds (e.g. 1000) to
 *                               run an animation. Default value: "normal".
 * @option Object fxShow An object literal of the form jQuery's animate function expects for making
 *                       your own, custom animation to reveal a tab upon tab switch. Unlike fxFade
 *                       or fxSlide this animation is independent from an optional hide animation.
 *                       Default value: null. @see animate
 * @option Object fxHide An object literal of the form jQuery's animate function expects for making
 *                       your own, custom animation to hide a tab upon tab switch. Unlike fxFade
 *                       or fxSlide this animation is independent from an optional show animation.
 *                       Default value: null. @see animate
 * @option String|Number fxShowSpeed A string representing one of the three predefined speeds
 *                                   ("slow", "normal", or "fast") or the number of milliseconds
 *                                   (e.g. 1000) to run the animation specified in fxShow.
 *                                   Default value: fxSpeed.
 * @option String|Number fxHideSpeed A string representing one of the three predefined speeds
 *                                   ("slow", "normal", or "fast") or the number of milliseconds
 *                                   (e.g. 1000) to run the animation specified in fxHide.
 *                                   Default value: fxSpeed.
 * @option Boolean fxAutoHeight Boolean flag that if set to true causes all tab heights
 *                              to be constant (being the height of the tallest tab).
 *                              Default value: false.
 * @option Function onClick A function to be invoked upon tab switch, immediatly after a tab has
 *                          been clicked, e.g. before the other's tab content gets hidden. The
 *                          function gets passed three arguments: the first one is the clicked
 *                          tab (e.g. an anchor element), the second one is the DOM element
 *                          containing the content of the clicked tab (e.g. the div), the third
 *                          argument is the one of the tab that gets hidden. If this callback
 *                          returns false, the tab switch is canceled (use to disallow tab
 *                          switching for the reason of a failed form validation for example).
 *                          Default value: null.
 * @option Function onHide A function to be invoked upon tab switch, immediatly after one tab's
 *                         content got hidden (with or without an animation) and right before the
 *                         next tab is revealed. The function gets passed three arguments: the
 *                         first one is the clicked tab (e.g. an anchor element), the second one
 *                         is the DOM element containing the content of the clicked tab, (e.g. the
 *                         div), the third argument is the one of the tab that gets hidden.
 *                         Default value: null.
 * @option Function onShow A function to be invoked upon tab switch. This function is invoked
 *                         after the new tab has been revealed, e.g. after the switch is completed.
 *                         The function gets passed three arguments: the first one is the clicked
 *                         tab (e.g. an anchor element), the second one is the DOM element
 *                         containing the content of the clicked tab, (e.g. the div), the third
 *                         argument is the one of the tab that gets hidden. Default value: null.
 * @option String navClass A CSS class that is used to identify the tabs unordered list by class if
 *                         the required HTML structure differs from the default one.
 *                         Default value: "tabs-nav".
 * @option String selectedClass The CSS class attached to the li element representing the
 *                              currently selected (active) tab. Default value: "tabs-selected".
 * @option String disabledClass The CSS class attached to the li element representing a disabled
 *                              tab. Default value: "tabs-disabled".
 * @option String containerClass A CSS class that is used to identify tab containers by class if
 *                               the required HTML structure differs from the default one.
 *                               Default value: "tabs-container".
 * @option String hideClass The CSS class used for hiding inactive tabs. A class is used instead
 *                          of "display: none" in the style attribute to maintain control over
 *                          visibility in other media types than screen, most notably print.
 *                          Default value: "tabs-hide".
 * @option String loadingClass The CSS class used for indicating that an Ajax tab is currently
 *                             loading, for example by showing a spinner.
 *                             Default value: "tabs-loading".
 * @option String tabStruct @deprecated A CSS selector or basic XPath expression reflecting a
 *                          nested HTML structure that is different from the default single div
 *                          structure (one div with an id inside the overall container holds one
 *                          tab's content). If for instance an additional div is required to wrap
 *                          up the several tab containers such a structure is expressed by "div>div".
 *                          Default value: "div".
 * @type jQuery
 *
 * @name tabs
 * @cat Plugins/Tabs
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */
$.fn.tabs = function(initial, settings) {

    // settings
    if (typeof initial == 'object') settings = initial; // no initial tab given but a settings object
    settings = $.extend({
        initial: (initial && typeof initial == 'number' && initial > 0) ? --initial : 0,
        disabled: null,
        bookmarkable: $.ajaxHistory ? true : false,
        remote: false,
        spinner: 'Loading&#8230;',
        hashPrefix: 'remote-tab-',
        fxFade: null,
        fxSlide: null,
        fxShow: null,
        fxHide: null,
        fxSpeed: 'normal',
        fxShowSpeed: null,
        fxHideSpeed: null,
        fxAutoHeight: false,
        onClick: null,
        onHide: null,
        onShow: null,
        navClass: 'tabs-nav',
        selectedClass: 'tabs-selected',
        disabledClass: 'tabs-disabled',
        containerClass: 'tabs-container',
        hideClass: 'tabs-hide',
        loadingClass: 'tabs-loading',
        tabStruct: 'div'
    }, settings || {});

    $.browser.msie6 = $.browser.msie6 || $.browser.msie && typeof XMLHttpRequest == 'function';

    // helper to prevent scroll to fragment
    function unFocus() {
        scrollTo(0, 0);
    }

    // initialize tabs
    return this.each(function() {

        // remember wrapper for later
        var container = this;

        // setup nav
        var nav = $('ul.' + settings.navClass, container);
        nav = nav.size() && nav || $('>ul:eq(0)', container); // fallback to default structure
        var tabs = $('a', nav);

        // prepare remote tabs
        if (settings.remote) {
            tabs.each(function() {
                var id = settings.hashPrefix + (++$.tabs.remoteCount), hash = '#' + id, url = this.href;
                this.href = hash;
                $('<div id="' + id + '" class="' + settings.containerClass + '"></div>').appendTo(container);

                $(this).bind('loadRemoteTab', function(e, callback) {
                    var $$ = $(this).addClass(settings.loadingClass), span = $('span', this)[0], tabTitle = span.innerHTML;
                    if (settings.spinner) {
                        // TODO if spinner is image
                        span.innerHTML = '<em>' + settings.spinner + '</em>'; // WARNING: html(...) crashes Safari with jQuery 1.1.2
                    }
                    setTimeout(function() { // Timeout is again required in IE, "wait" for id being restored
                        $(hash).load(url, function() {
                            if (settings.spinner) {
                                span.innerHTML = tabTitle; // WARNING: html(...) crashes Safari with jQuery 1.1.2
                            }
                            $$.removeClass(settings.loadingClass);
                            callback && callback();
                        });
                    }, 0);
                });

            });
        }

        // set up containers
        var containers = $('div.' + settings.containerClass, container);
        containers = containers.size() && containers || $('>' + settings.tabStruct, container); // fallback to default structure

        // attach classes for styling if not present
        nav.is('.' + settings.navClass) || nav.addClass(settings.navClass);
        containers.each(function() {
            var $$ = $(this);
            $$.is('.' + settings.containerClass) || $$.addClass(settings.containerClass);
        });

        // try to retrieve active tab from class in HTML
        var hasSelectedClass = $('li', nav).index( $('li.' + settings.selectedClass, nav)[0] );
        if (hasSelectedClass >= 0) {
           settings.initial = hasSelectedClass;
        }

        // try to retrieve active tab from hash in url, will override class in HTML
        if (location.hash) {
            tabs.each(function(i) {
                if (this.hash == location.hash) {
                    settings.initial = i;
                    // prevent page scroll to fragment
                    if (($.browser.msie || $.browser.opera) && !settings.remote) {
                        var toShow = $(location.hash);
                        var toShowId = toShow.attr('id');
                        toShow.attr('id', '');
                        setTimeout(function() {
                            toShow.attr('id', toShowId); // restore id
                        }, 500);
                    }
                    unFocus();
                    return false; // break
                }
            });
        }
        if ($.browser.msie) {
            unFocus(); // fix IE focussing bottom of the page for some unknown reason
        }

        // highlight tab accordingly
        containers.filter(':eq(' + settings.initial + ')').show().end().not(':eq(' + settings.initial + ')').addClass(settings.hideClass);
        $('li', nav).removeClass(settings.selectedClass).eq(settings.initial).addClass(settings.selectedClass); // we need to remove classes eventually if hash takes precedence over class
        // trigger load of initial tab
        tabs.eq(settings.initial).trigger('loadRemoteTab').end();

        // setup auto height
        if (settings.fxAutoHeight) {
            // helper
            var _setAutoHeight = function(reset) {
                // get tab heights in top to bottom ordered array
                var heights = $.map(containers.get(), function(el) {
                    var h, jq = $(el);
                    if (reset) {
                        if ($.browser.msie6) {
                            el.style.removeExpression('behaviour');
                            el.style.height = '';
                            el.minHeight = null;
                        }
                        h = jq.css({'min-height': ''}).height(); // use jQuery's height() to get hidden element values
                    } else {
                        h = jq.height(); // use jQuery's height() to get hidden element values
                    }
                    return h;
                }).sort(function(a, b) {
                    return b - a;
                });
                if ($.browser.msie6) {
                    containers.each(function() {
                        this.minHeight = heights[0] + 'px';
                        this.style.setExpression('behaviour', 'this.style.height = this.minHeight ? this.minHeight : "1px"'); // using an expression to not make print styles useless
                    });
                } else {
                    containers.css({'min-height': heights[0] + 'px'});
                }
            };
            // call once for initialization
            _setAutoHeight();
            // trigger auto height adjustment if needed
            var cachedWidth = container.offsetWidth;
            var cachedHeight = container.offsetHeight;
            var watchFontSize = $('#tabs-watch-font-size').get(0) || $('<span id="tabs-watch-font-size">M</span>').css({display: 'block', position: 'absolute', visibility: 'hidden'}).appendTo(document.body).get(0);
            var cachedFontSize = watchFontSize.offsetHeight;
            setInterval(function() {
                var currentWidth = container.offsetWidth;
                var currentHeight = container.offsetHeight;
                var currentFontSize = watchFontSize.offsetHeight;
                if (currentHeight > cachedHeight || currentWidth != cachedWidth || currentFontSize != cachedFontSize) {
                    _setAutoHeight((currentWidth > cachedWidth || currentFontSize < cachedFontSize)); // if heights gets smaller reset min-height
                    cachedWidth = currentWidth;
                    cachedHeight = currentHeight;
                    cachedFontSize = currentFontSize;
                }
            }, 50);
        }

        // setup animations
        var showAnim = {}, hideAnim = {}, showSpeed = settings.fxShowSpeed || settings.fxSpeed, hideSpeed = settings.fxHideSpeed || settings.fxSpeed;
        if (settings.fxSlide || settings.fxFade) {
            if (settings.fxSlide) {
                showAnim['height'] = 'show';
                hideAnim['height'] = 'hide';
            }
            if (settings.fxFade) {
                showAnim['opacity'] = 'show';
                hideAnim['opacity'] = 'hide';
            }
        } else {
            if (settings.fxShow) {
                showAnim = settings.fxShow;
            } else { // use some kind of animation to prevent browser scrolling to the tab
                showAnim['min-width'] = 0; // avoid opacity, causes flicker in Firefox
                showSpeed = settings.bookmarkable ? 50 : 1; // as little as 50 is sufficient
            }
            if (settings.fxHide) {
                hideAnim = settings.fxHide;
            } else { // use some kind of animation to prevent browser scrolling to the tab
                hideAnim['min-width'] = 0; // avoid opacity, causes flicker in Firefox
                hideSpeed = settings.bookmarkable ? 50 : 1; // as little as 50 is sufficient
            }
        }

        // callbacks
        var onClick = settings.onClick, onHide = settings.onHide, onShow = settings.onShow;

        // attach activateTab event, required for activating a tab programmatically
        tabs.bind('triggerTab', function() {

            // if the tab is already selected or disabled or animation is still running stop here
            var li = $(this).parents('li:eq(0)');
            if (container.locked || li.is('.' + settings.selectedClass) || li.is('.' + settings.disabledClass)) {
                return false;
            }

            var hash = this.hash;

            if ($.browser.msie) {

                $(this).trigger('click');
                if (settings.bookmarkable) {
                    $.ajaxHistory.update(hash);
                    location.hash = hash.replace('#', '');
                }

            } else if ($.browser.safari) {

                // Simply setting location.hash puts Safari into the eternal load state... ugh! Submit a form instead.
                var tempForm = $('<form action="' + hash + '"><div><input type="submit" value="h" /></div></form>').get(0); // no need to append it to the body
                tempForm.submit(); // does not trigger the form's submit event...
                $(this).trigger('click'); // ...thus do stuff here
                if (settings.bookmarkable) {
                    $.ajaxHistory.update(hash);
                }

            } else {

                if (settings.bookmarkable) {
                    location.hash = hash.replace('#', '');
                } else {
                    $(this).trigger('click');
                }

            }

        });

        // attach disable event, required for disabling a tab
        tabs.bind('disableTab', function() {
            var li = $(this).parents('li:eq(0)');
            if ($.browser.safari) { /* Fix opacity of tab after disabling in Safari... */
                li.animate({ opacity: 0 }, 1, function() {
                   li.css({opacity: ''});
                });
            }
            li.addClass(settings.disabledClass);

        });

        // disabled from settings
        if (settings.disabled && settings.disabled.length) {
            for (var i = 0, k = settings.disabled.length; i < k; i++) {
                tabs.eq(--settings.disabled[i]).trigger('disableTab').end();
            }
        };

        // attach enable event, required for reenabling a tab
        tabs.bind('enableTab', function() {
            var li = $(this).parents('li:eq(0)');
            li.removeClass(settings.disabledClass);
            if ($.browser.safari) { /* Fix disappearing tab after enabling in Safari... */
                li.animate({ opacity: 1 }, 1, function() {
                    li.css({opacity: ''});
                });
            }
        });

        // attach click event
        tabs.bind('click', function(e) {

            var trueClick = e.clientX; // add to history only if true click occured, not a triggered click
            var clicked = this, li = $(this).parents('li:eq(0)'), toShow = $(this.hash), toHide = containers.filter(':visible');

            // if animation is still running, tab is selected or disabled or onClick callback returns false stop here
            // check if onClick returns false last so that it is not executed for a disabled tab
            if (container['locked'] || li.is('.' + settings.selectedClass) || li.is('.' + settings.disabledClass) || typeof onClick == 'function' && onClick(this, toShow[0], toHide[0]) === false) {
                this.blur();
                return false;
            }

            container['locked'] = true;

            // show new tab
            if (toShow.size()) {

                // prevent scrollbar scrolling to 0 and than back in IE7, happens only if bookmarking/history is enabled
                if ($.browser.msie && settings.bookmarkable) {
                    var toShowId = this.hash.replace('#', '');
                    toShow.attr('id', '');
                    setTimeout(function() {
                        toShow.attr('id', toShowId); // restore id
                    }, 0);
                }

                // switch tab, animation prevents browser scrolling to the fragment
                function switchTab() {
                    if (settings.bookmarkable && trueClick) { // add to history only if true click occured, not a triggered click
                        $.ajaxHistory.update(clicked.hash);
                    }
                    toHide.animate(hideAnim, hideSpeed, function() { //
                        $(clicked).parents('li:eq(0)').addClass(settings.selectedClass).siblings().removeClass(settings.selectedClass);
                        if (typeof onHide == 'function') {
                            onHide(clicked, toShow[0], toHide[0]);
                        }
                        var resetCSS = { display: '', overflow: '', height: '' };
                        if (!$.browser.msie) { // not in IE to prevent ClearType font issue
                            resetCSS['opacity'] = '';
                        }
                        toHide.addClass(settings.hideClass).css(resetCSS); // maintain flexible height and accessibility in print etc.
                        toShow.removeClass(settings.hideClass).animate(showAnim, showSpeed, function() {
                            toShow.css(resetCSS); // maintain flexible height and accessibility in print etc.
                            if ($.browser.msie) {
                                toHide[0].style.filter = '';
                                toShow[0].style.filter = '';
                            }
                            if (typeof onShow == 'function') {
                                onShow(clicked, toShow[0], toHide[0]);
                            }
                            container['locked'] = null;
                        });
                    });
                }

                if (!settings.remote) {
                    switchTab();
                } else {
                    $(clicked).trigger('loadRemoteTab', [switchTab]);
                }

            } else {
                alert('There is no such container.');
            }

            // Set scrollbar to saved position - need to use timeout with 0 to prevent browser scroll to target of hash
            var scrollX = window.pageXOffset || document.documentElement && document.documentElement.scrollLeft || document.body.scrollLeft || 0;
            var scrollY = window.pageYOffset || document.documentElement && document.documentElement.scrollTop || document.body.scrollTop || 0;
            setTimeout(function() {
                window.scrollTo(scrollX, scrollY);
            }, 0);

            this.blur(); // prevent IE from keeping other link focussed when using the back button

            return settings.bookmarkable && !!trueClick; // convert undefined to Boolean for IE

        });

        // enable history support if bookmarking and history is turned on
        if (settings.bookmarkable) {
            $.ajaxHistory.initialize(function() {
                tabs.eq(settings.initial).trigger('click').end();
            });
        }

    });

};

/**
 * Activate a tab programmatically with the given position (no zero-based index)
 * or its id, e.g. the URL's fragment identifier/hash representing a tab, as if the tab
 * itself were clicked.
 *
 * @example $('#container').triggerTab(2);
 * @desc Activate the second tab of the tab interface contained in <div id="container">.
 * @example $('#container').triggerTab(1);
 * @desc Activate the first tab of the tab interface contained in <div id="container">.
 * @example $('#container').triggerTab();
 * @desc Activate the first tab of the tab interface contained in <div id="container">.
 * @example $('#container').triggerTab('fragment-2');
 * @desc Activate a tab via its URL fragment identifier representation.
 *
 * @param String|Number tab Either a string that matches the id of the tab (the URL's
 *                          fragment identifier/hash representing a tab) or an integer
 *                          specifying the position of the tab (no zero-based index) to
 *                          be activated. If this parameter is omitted, the first tab
 *                          will be activated.
 * @type jQuery
 *
 * @name triggerTab
 * @cat Plugins/Tabs
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */

/**
 * Disable a tab, so that clicking it has no effect.
 *
 * @example $('#container').disableTab(2);
 * @desc Disable the second tab of the tab interface contained in <div id="container">.
 *
 * @param String|Number tab Either a string that matches the id of the tab (the URL's
 *                          fragment identifier/hash representing a tab) or an integer
 *                          specifying the position of the tab (no zero-based index) to
 *                          be disabled. If this parameter is omitted, the first tab
 *                          will be disabled.
 * @type jQuery
 *
 * @name disableTab
 * @cat Plugins/Tabs
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */

/**
 * Enable a tab that has been disabled.
 *
 * @example $('#container').enableTab(2);
 * @desc Enable the second tab of the tab interface contained in <div id="container">.
 *
 * @param String|Number tab Either a string that matches the id of the tab (the URL's
 *                          fragment identifier/hash representing a tab) or an integer
 *                          specifying the position of the tab (no zero-based index) to
 *                          be enabled. If this parameter is omitted, the first tab
 *                          will be enabled.
 * @type jQuery
 *
 * @name enableTab
 * @cat Plugins/Tabs
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */

var tabEvents = ['triggerTab', 'disableTab', 'enableTab'];
for (var i = 0; i < tabEvents.length; i++) {
    $.fn[tabEvents[i]] = (function(tabEvent) {
        return function(tab) {
            return this.each(function() {
                var nav = $('ul.tabs-nav' , this);
                nav = nav.size() && nav || $('>ul:eq(0)', this); // fallback to default structure
                var a;
                if (!tab || typeof tab == 'number') {
                    a = $('li a', nav).eq((tab && tab > 0 && tab - 1 || 0)); // fall back to 0
                } else if (typeof tab == 'string') {
                    a = $('li a[@href$="#' + tab + '"]', nav);
                }
                a.trigger(tabEvent);
            });
        };
    })(tabEvents[i]);
}

/**
 * Get the position of the currently selected tab (no zero-based index).
 *
 * @example $('#container').activeTab();
 * @desc Get the position of the currently selected tab of an interface
 * contained in <div id="container">.
 *
 * @type Number
 *
 * @name activeTab
 * @cat Plugins/Tabs
 * @author Klaus Hartl/klaus.hartl@stilbuero.de
 */

$.fn.activeTab = function() {
    var selectedTabs = [];
    this.each(function() {
        var nav = $('ul.tabs-nav' , this);
        nav = nav.size() && nav || $('>ul:eq(0)', this); //fallback to default structure
        var lis = $('li', nav);
        selectedTabs.push(lis.index( lis.filter('.tabs-selected')[0] ) + 1);
    });
    return selectedTabs[0];
};

})(jQuery);


/*
Class: Class
	The base class object of the <http://mootools.net> framework.
	
Arguments:
	properties - the collection of properties that apply to the class. Creates a new class, its initialize method will fire upon class instantiation.
	
Example:
	>var Cat = new Class({
	>	initialize: function(name){
	>		this.name = name;
	>	}
	>});
	>var myCat = new Cat('Micia');
	>alert myCat.name; //alerts 'Micia'
*/

var Class = function(properties){
	var klass = function(){
		for (var p in this){
			if (this[p]) this[p]._proto_ = this;
		}
		if (arguments[0] != 'noinit' && this.initialize) return this.initialize.apply(this, arguments);
	};
	klass.extend = this.extend;
	klass.implement = this.implement;
	klass.prototype = properties;
	return klass;
};

/*
Property: empty
	Returns an empty function
*/

Class.empty = function(){};

/*
Property: create
	same as new Class. see <Class>
*/

Class.create = function(properties){
	return new Class(properties);
};

Class.prototype = {

	/*
	Property: extend
		Returns the copy of the Class extended with the passed in properties.
		
	Arguments:
		properties - the properties to add to the base class in this new Class.
		
	Example:
		>var Animal = new Class({
		>	initialize: function(age){
		>		this.age = age;
		>	}
		>});
		>var Cat = Animal.extend({
		>	initialize: function(name, age){
		>		this.parent(age); //will call the previous initialize;
		>		this.name = name;
		>	}
		>});
		>var myCat = new Cat('Micia', 20);
		>alert myCat.name; //alerts 'Micia'
		>alert myCat.age; //alerts 20
	*/

	extend: function(properties){
		var pr0t0typ3 = new this('noinit');
		for (var property in properties){
			var previous = pr0t0typ3[property];
			var current = properties[property];
			if (previous && previous != current) current = previous.parentize(current) || current;
			pr0t0typ3[property] = current;
		}
		return new Class(pr0t0typ3);
	},
	
	/*	
	Property: implement
		Implements the passed in properties to the base Class prototypes, altering the base class, unlike <Class.extend>.

	Arguments:
		properties - the properties to add to the base class.
		
	Example:
		>var Animal = new Class({
		>	initialize: function(age){
		>		this.age = age;
		>	}
		>});
		>Animal.implement({
		>	setName: function(name){
		>		this.name = name
		>	}
		>});
		>var myAnimal = new Animal(20);
		>myAnimal.setName('Micia');
		>alert(myAnimal.name); //alerts 'Micia'
	*/
	
	implement: function(properties){
		for (var property in properties) this.prototype[property] = properties[property];
	}

};

/*
Function: Object.Native
	Will add a .extend method to the objects passed as a parameter, equivalent to <Class.implement>

Arguments:
	a number of classes/native javascript objects

*/

Object.Native = function(){
	for (var i = 0; i < arguments.length; i++) arguments[i].extend = Class.prototype.implement;
};

new Object.Native(Function, Array, String, Number);

Function.extend({

	parentize: function(current){
		var previous = this;
		return function(){
			this.parent = previous;
			return current.apply(this, arguments);
		};
	}

});
/**
 * SWFObject v1.5: Flash Player detection and embed - http://blog.deconcept.com/swfobject/
 *
 * SWFObject is (c) 2007 Geoff Stearns and is released under the MIT License:
 * http://www.opensource.org/licenses/mit-license.php
 *
 */
if(typeof deconcept=="undefined"){var deconcept=new Object();}if(typeof deconcept.util=="undefined"){deconcept.util=new Object();}if(typeof deconcept.SWFObjectUtil=="undefined"){deconcept.SWFObjectUtil=new Object();}deconcept.SWFObject=function(_1,id,w,h,_5,c,_7,_8,_9,_a){if(!document.getElementById){return;}this.DETECT_KEY=_a?_a:"detectflash";this.skipDetect=deconcept.util.getRequestParameter(this.DETECT_KEY);this.params=new Object();this.variables=new Object();this.attributes=new Array();if(_1){this.setAttribute("swf",_1);}if(id){this.setAttribute("id",id);}if(w){this.setAttribute("width",w);}if(h){this.setAttribute("height",h);}if(_5){this.setAttribute("version",new deconcept.PlayerVersion(_5.toString().split(".")));}this.installedVer=deconcept.SWFObjectUtil.getPlayerVersion();if(!window.opera&&document.all&&this.installedVer.major>7){deconcept.SWFObject.doPrepUnload=true;}if(c){this.addParam("bgcolor",c);}var q=_7?_7:"high";this.addParam("quality",q);this.setAttribute("useExpressInstall",false);this.setAttribute("doExpressInstall",false);var _c=(_8)?_8:window.location;this.setAttribute("xiRedirectUrl",_c);this.setAttribute("redirectUrl","");if(_9){this.setAttribute("redirectUrl",_9);}};deconcept.SWFObject.prototype={useExpressInstall:function(_d){this.xiSWFPath=!_d?"expressinstall.swf":_d;this.setAttribute("useExpressInstall",true);},setAttribute:function(_e,_f){this.attributes[_e]=_f;},getAttribute:function(_10){return this.attributes[_10];},addParam:function(_11,_12){this.params[_11]=_12;},getParams:function(){return this.params;},addVariable:function(_13,_14){this.variables[_13]=_14;},getVariable:function(_15){return this.variables[_15];},getVariables:function(){return this.variables;},getVariablePairs:function(){var _16=new Array();var key;var _18=this.getVariables();for(key in _18){_16[_16.length]=key+"="+_18[key];}return _16;},getSWFHTML:function(){var _19="";if(navigator.plugins&&navigator.mimeTypes&&navigator.mimeTypes.length){if(this.getAttribute("doExpressInstall")){this.addVariable("MMplayerType","PlugIn");this.setAttribute("swf",this.xiSWFPath);}_19="<embed type=\"application/x-shockwave-flash\" src=\""+this.getAttribute("swf")+"\" width=\""+this.getAttribute("width")+"\" height=\""+this.getAttribute("height")+"\" style=\""+this.getAttribute("style")+"\"";_19+=" id=\""+this.getAttribute("id")+"\" name=\""+this.getAttribute("id")+"\" ";var _1a=this.getParams();for(var key in _1a){_19+=[key]+"=\""+_1a[key]+"\" ";}var _1c=this.getVariablePairs().join("&");if(_1c.length>0){_19+="flashvars=\""+_1c+"\"";}_19+="/>";}else{if(this.getAttribute("doExpressInstall")){this.addVariable("MMplayerType","ActiveX");this.setAttribute("swf",this.xiSWFPath);}_19="<object id=\""+this.getAttribute("id")+"\" classid=\"clsid:D27CDB6E-AE6D-11cf-96B8-444553540000\" width=\""+this.getAttribute("width")+"\" height=\""+this.getAttribute("height")+"\" style=\""+this.getAttribute("style")+"\">";_19+="<param name=\"movie\" value=\""+this.getAttribute("swf")+"\" />";var _1d=this.getParams();for(var key in _1d){_19+="<param name=\""+key+"\" value=\""+_1d[key]+"\" />";}var _1f=this.getVariablePairs().join("&");if(_1f.length>0){_19+="<param name=\"flashvars\" value=\""+_1f+"\" />";}_19+="</object>";}return _19;},write:function(_20){if(this.getAttribute("useExpressInstall")){var _21=new deconcept.PlayerVersion([6,0,65]);if(this.installedVer.versionIsValid(_21)&&!this.installedVer.versionIsValid(this.getAttribute("version"))){this.setAttribute("doExpressInstall",true);this.addVariable("MMredirectURL",escape(this.getAttribute("xiRedirectUrl")));document.title=document.title.slice(0,47)+" - Flash Player Installation";this.addVariable("MMdoctitle",document.title);}}if(this.skipDetect||this.getAttribute("doExpressInstall")||this.installedVer.versionIsValid(this.getAttribute("version"))){var n=(typeof _20=="string")?document.getElementById(_20):_20;n.innerHTML=this.getSWFHTML();return true;}else{if(this.getAttribute("redirectUrl")!=""){document.location.replace(this.getAttribute("redirectUrl"));}}return false;}};deconcept.SWFObjectUtil.getPlayerVersion=function(){var _23=new deconcept.PlayerVersion([0,0,0]);if(navigator.plugins&&navigator.mimeTypes.length){var x=navigator.plugins["Shockwave Flash"];if(x&&x.description){_23=new deconcept.PlayerVersion(x.description.replace(/([a-zA-Z]|\s)+/,"").replace(/(\s+r|\s+b[0-9]+)/,".").split("."));}}else{if(navigator.userAgent&&navigator.userAgent.indexOf("Windows CE")>=0){var axo=1;var _26=3;while(axo){try{_26++;axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash."+_26);_23=new deconcept.PlayerVersion([_26,0,0]);}catch(e){axo=null;}}}else{try{var axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash.7");}catch(e){try{var axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash.6");_23=new deconcept.PlayerVersion([6,0,21]);axo.AllowScriptAccess="always";}catch(e){if(_23.major==6){return _23;}}try{axo=new ActiveXObject("ShockwaveFlash.ShockwaveFlash");}catch(e){}}if(axo!=null){_23=new deconcept.PlayerVersion(axo.GetVariable("$version").split(" ")[1].split(","));}}}return _23;};deconcept.PlayerVersion=function(_29){this.major=_29[0]!=null?parseInt(_29[0]):0;this.minor=_29[1]!=null?parseInt(_29[1]):0;this.rev=_29[2]!=null?parseInt(_29[2]):0;};deconcept.PlayerVersion.prototype.versionIsValid=function(fv){if(this.major<fv.major){return false;}if(this.major>fv.major){return true;}if(this.minor<fv.minor){return false;}if(this.minor>fv.minor){return true;}if(this.rev<fv.rev){return false;}return true;};deconcept.util={getRequestParameter:function(_2b){var q=document.location.search||document.location.hash;if(_2b==null){return q;}if(q){var _2d=q.substring(1).split("&");for(var i=0;i<_2d.length;i++){if(_2d[i].substring(0,_2d[i].indexOf("="))==_2b){return _2d[i].substring((_2d[i].indexOf("=")+1));}}}return "";}};deconcept.SWFObjectUtil.cleanupSWFs=function(){var _2f=document.getElementsByTagName("OBJECT");for(var i=_2f.length-1;i>=0;i--){_2f[i].style.display="none";for(var x in _2f[i]){if(typeof _2f[i][x]=="function"){_2f[i][x]=function(){};}}}};if(deconcept.SWFObject.doPrepUnload){if(!deconcept.unloadSet){deconcept.SWFObjectUtil.prepUnload=function(){__flash_unloadHandler=function(){};__flash_savedUnloadHandler=function(){};window.attachEvent("onunload",deconcept.SWFObjectUtil.cleanupSWFs);};window.attachEvent("onbeforeunload",deconcept.SWFObjectUtil.prepUnload);deconcept.unloadSet=true;}}if(!document.getElementById&&document.all){document.getElementById=function(id){return document.all[id];};}var getQueryParamValue=deconcept.util.getRequestParameter;var FlashObject=deconcept.SWFObject;var SWFObject=deconcept.SWFObject;
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
Liferay.Util = {
	submitCountdown: 0,

	actsAsAspect: function(object) {
		object.yield = null;
		object.rv = {};

		object.before = function(method, f) {
			var original = eval("this." + method);

			this[method] = function() {
				f.apply(this, arguments);

				return original.apply(this, arguments);
			};
		};

		object.after = function(method, f) {
			var original = eval("this." + method);

			this[method] = function() {
				this.rv[method] = original.apply(this, arguments);

				return f.apply(this, arguments);
			};
		};

		object.around = function(method, f) {
			var original = eval("this." + method);

			this[method] = function() {
				this.yield = original;

				return f.apply(this, arguments);
			};
		};
	},

	addInputFocus: function(el) {
		var item = null;

		if (el) {
			if (typeof el == 'object') {
				item = jQuery(el);
			}
			else {
				item = jQuery('#' + el);
			}
		}
		else {
			item = document.body;
		}

		var inputs = jQuery("input[@type=text], input[@type=password], textarea", item);

		inputs.focus(
			function() {
				jQuery(this).addClass('focus');

				if (this.createTextRange) {
					var value = this.value;
					var textRange = this.createTextRange();

					textRange.moveStart('character', value.length);
					textRange.select();
				}
			}
		);

		inputs.blur(
			function() {
				jQuery(this).removeClass('focus');
			}
		);
	},

	addInputType: function(el) {
		var item;

		if (jQuery.browser.msie && jQuery.browser.version.number() < 7) {
			if (el) {
				if (typeof el == 'object') {
					item = jQuery(el);
				}
				else {
					item = jQuery('#' + el);
				}
			}
			else {
				item = document.body;
			}

			jQuery("input", item).each(function() {
				var current = jQuery(this);
				var type = this.type || "text";

				current.addClass(type);
			});
		}
	},

	addParams: function(params, url) {
		var instance = this;

		if (typeof params == 'object') {
			params = jQuery.param(params);
		}
		else {
			params = jQuery.trim(params);
		}

		if (params != '') {
			var loc = url || location.href;
			var anchorHash, finalUrl;

			if (loc.indexOf('#') > -1) {
				var locationPieces = loc.split('#');
				loc = locationPieces[0];
				anchorHash = locationPieces[1];
			}

			if (loc.indexOf('?') == -1) {
				params = '?' + params;
			}
			else {
				params = '&' + params;
			}

			if (loc.indexOf(params) == -1) {
				finalUrl = loc + params;

				if (anchorHash) {
					finalUrl += '#' + anchorHash;
				}
				if (!url) {
					location.href = finalUrl;
				}
				return finalUrl;
			}
		}
	},

	check: function(form, name, checked) {
		jQuery('input[@name=' + name + ']:checkbox',form).attr('checked', checked);
	},

	checkAll: function(form, name, allBox) {
		var inputs;

		if (Liferay.Util.isArray(name)) {
			var names = 'input[@name='+ name.join(']:checkbox,input[@name=') + ']:checkbox';

			inputs = jQuery(names, form);
		}
		else {
			inputs = jQuery('input[@name=' + name + ']:checkbox', form);
		}

		inputs.attr('checked', allBox.checked);
	},

	checkAllBox: function(form, name, allBox) {
		var totalBoxes = 0;
		var totalOn = 0;
		var inputs;

		if (Liferay.Util.isArray(name)) {
			var names = 'input[@name='+ name.join(']:checkbox,input[@name=') + ']:checkbox';

			inputs = jQuery(names, form);
		}
		else {
			inputs = jQuery('input[@name=' + name + ']:checkbox', form);
		}

		inputs = inputs.not(allBox);

		totalBoxes = inputs.length;
		totalOn = inputs.filter(':checked').length;

		allBox.checked = (totalBoxes == totalOn);
	},

	checkMaxLength: function(box, maxLength) {
		if ((box.value.length) >= maxLength) {
			box.value = box.value.substring(0, maxLength - 1);
		}
	},

	checkTab: function(box) {
		if ((document.all) && (event.keyCode == 9)) {
			box.selection = document.selection.createRange();
			setTimeout("Liferay.Util.processTab(\"" + box.id + "\")", 0);
		}
	},

	disableEsc: function() {
		if ((document.all) && (event.keyCode == 27)) {
			event.returnValue = false;
		}
	},

	endsWith: function(str, x) {
		return (str.lastIndexOf(x) === (str.length - x.length));
	},

	evalScripts: function(obj) {
		var instance = this;

		jQuery(obj).find('script').each(
			function(){
				if ( this.src ) {
					jQuery.getScript( this.src );
				}
				else {
					jQuery.globalEval( this.text || this.textContent || this.innerHTML || "" );
				}
			}
		);
	},

	focusFormField: function(el) {
		var interacting = false;

		jQuery(document).one(
			'click',
			function() {
				interacting = true;
			}
		);

		jQuery(
			function() {
				if (el && (el.offsetHeight != 0) && !interacting) {
					var elObj = jQuery(el);

					jQuery('input').trigger('blur');

					elObj.trigger('focus');
				}
			}
		);
	},

	getSelectedIndex: function(col) {
		for (var i = 0; i < col.length; i++) {
			if (col[i].checked == true) {
				return i;
			}
		}

		return -1;
	},

	getSelectedRadioValue: function(col) {
		var i = Liferay.Util.getSelectedIndex(col);

		if (i == -1) {
			var radioValue = col.value;

			if (radioValue == null) {
				radioValue = "";
			}

			return radioValue;
		}
		else {
			return col[i].value;
		}
	},

	getURLWithSessionId: function(url) {
		if (propsUtil.SESSION_ENABLE_PERSISTENT_COOKIES) {
			return url;
		}

		// LEP-4787

		var x = url.indexOf(";");

		if (x != -1) {
			return url;
		}

		x = url.indexOf("?");

		if (x != -1) {
			return url.substring(0, x) + ";jsessionid=" + themeDisplay.getSessionId() + url.substring(x);
		}

		// In IE6, http://www.abc.com;jsessionid=XYZ does not work, but
		// http://www.abc.com/;jsessionid=XYZ does work.

		x = url.indexOf("//");

		if (x != -1) {
			var y = url.lastIndexOf("/");

			if (x + 1 == y) {
				return url + "/;jsessionid=" + themeDisplay.getSessionId();
			}
		}

		return url + ";jsessionid=" + themeDisplay.getSessionId();
	},

	inlineEditor: function(options) {
		var instance = this;

		/*
		button (jQuery selector | DOM element): The button that opens the popup when clicked
		url (String): url to open that sets the editor
		width (Int): The width to set the popup to
		height (Int): The height to set the popup to
		textarea (String): the name of the textarea to auto-resize
		*/

		if (options.url && options.button) {
			var url = options.url;
			var button = options.button;
			var width = options.width || 680;
			var height = options.height || 640;
			var textarea = options.textarea;
			var clicked = false;

			var editorButton = jQuery(button);

			editorButton.click(
				function(event) {
					if (!clicked) {
						var popup = Liferay.Popup(
							{
								height: 640,
								width: 680,
								noCenter: true,
								title: '',
								onClose: function() {
									jQuery(document).unbind('popupResize');
									clicked = false;
								}
							}
						);

						var jPopup = jQuery(popup);
						var resizeDiv = '<div class="portlet-resize-handle"></div>';

						jQuery.ajax(
							{
								url: url + '&rt=' + Liferay.Util.randomInt(),
								success: function(message) {
									jPopup.find('.loading-animation').remove();
									jPopup.append(message);
									jPopup.after(resizeDiv);

									var form = jPopup.find('form');

									form.css(
										{
											height: 340,
											width: 680
										}
									);

									if (textarea) {
										var usingPlainEditor = jPopup.find('.lfr-textarea').length;

										Liferay.Util.resizeTextarea(textarea, !usingPlainEditor, true);
									}

									var handle = jQuery('.portlet-resize-handle')[0];

									var mainPopup = jPopup.parents('.popup:first');

									mainPopup.lResize(
										{
											direction: 'horizontal',
											handle: handle,
											mode: 'add',
											onMove: function(settings) {
												form.css(
													{
														height: settings.browserEvent.clientY - 130,
														width: settings.browserEvent.clientX - 30
													}
												);
												jQuery(document).trigger('popupResize');
											}
										}
									);

									mainPopup.lResize(
										{
											handle: handle,
											direction: "vertical",
											mode: "add"
										}
									);
								}
							}
						);

						clicked = true;
					}
				}
			);
		}
	},

	isArray: function(object) {
		if (!window.Array) {
			return false;
		}
		else {
			return object.constructor == window.Array;
		}
	},

	listChecked: function(form) {
		var s = [];
		var inputs = jQuery('input[@value!=]:checked:checkbox', form);

		inputs.each(
			function() {
				s.push(this.value);
			}
		);

		return s.join(',');
	},

	listCheckedExcept: function(form, except) {
		var s = [];
		var inputs = jQuery('input[@value!=][@name!="' + except + '"]:checked:checkbox', form);

		inputs.each(
			function() {
				s.push(this.value);
			}
		);

		return s.join(',');
	},

	listSelect: function(box, delimeter) {
		var s = [];

		delimeter = delimeter || ',';

		if (box == null) {
			return "";
		}

		var opts = jQuery(box).find('option[@value!=]');

		opts.each(
			function() {
				s.push(this.value);
			}
		);

		if (s[0] == '.none') {
			return '';
		}
		else {
			return s.join(',');
		}
	},

	listUncheckedExcept: function(form, except) {
		var s = [];
		var inputs = jQuery('input[@value!=][@name!="' + except + '"]:checkbox:not(:checked)', form);

		inputs.each(
			function() {
				s.push(this.value);
			}
		);

		return s.join(',');
	},

	moveItem: function(fromBox, toBox, sort) {
		if (fromBox.selectedIndex >= 0) {
			var toSelect = jQuery(toBox);
			var selectedOption = jQuery(fromBox).find('option:selected');

			toSelect.append(selectedOption);
		}

		if (selectedOption.text() != '' && sort == true) {
			Liferay.Util.sortBox(toBox);
		}
	},

	portletTitleEdit: function(options) {
		var instance = this;

		var obj = options.obj;
		var plid = options.plid;
		var doAsUserId = options.doAsUserId;
		var portletId = options.portletId;
		var url = options.url;

		var title = obj.find('.portlet-title');

		if (!title.is('.not-editable')) {
			title.editable(
				function(value, settings) {
					var cruft = settings._LFR_.cruft || [];

					cruft = cruft.join('');

					if (value != settings._LFR_.oldText) {
						Liferay.Util.savePortletTitle(
							{
								plid: plid,
								doAsUserId: doAsUserId,
								portletId: portletId,
								title: value
							}
						);
					}

					obj[0]._LFR_noDrag = null;

					return cruft + value;
				},
				{
					cssclass: 'text',
					data: function(value, settings) {
						var input = jQuery(this);
						var re = new RegExp('<\/?[^>]+>|\n|\r|\t', 'gim');

						var cruft = value.match(re);

						settings._LFR_ = {};
						settings._LFR_.oldText = value;
						settings._LFR_.cruft = cruft;

						value = value.replace(re, '');
						settings._LFR_.oldText = value;
						obj[0]._LFR_noDrag = true;

						return value;
					},
					height: '',
					width: '',
					onblur: 'submit',
					type: 'text',
					select: false,
					style: '',
					submit: ''
				}
			);
		}
	},

	processTab: function(id) {
		document.all[id].selection.text = String.fromCharCode(9);
		document.all[id].focus();
	},

	randomInt: function() {
		return (Math.ceil(Math.random() * (new Date).getTime()));
	},

	randomMinMax: function(min, max) {
		return (Math.round(Math.random() * (max - min))) + min;
	},

	removeItem: function(box, value) {
		var selectEl = jQuery(box);

		if (!value) {
			selectEl.find('option:selected').remove();
		}
		else {
			selectEl.find('option[@value=' + value + ']:selected').remove();
		}
	},

	reorder: function(box, down) {
		var si = box.selectedIndex;

		if (si == -1) {
			box.selectedIndex = 0;
		}
		else {
			sText = box.options[si].text;
			sValue = box.options[si].value;

			if ((box.options[si].value > "") && (si > 0) && (down == 0)) {
				box.options[si].text = box.options[si - 1].text;
				box.options[si].value = box.options[si - 1].value;
				box.options[si - 1].text = sText;
				box.options[si - 1].value = sValue;
				box.selectedIndex--;
			}
			else if ((si < box.length - 1) && (box.options[si + 1].value > "") && (down == 1)) {
				box.options[si].text = box.options[si + 1].text;
				box.options[si].value = box.options[si + 1].value;
				box.options[si + 1].text = sText;
				box.options[si + 1].value = sValue;
				box.selectedIndex++;
			}
			else if (si == 0) {
				for (var i = 0; i < (box.length - 1); i++) {
					box.options[i].text = box.options[i + 1].text;
					box.options[i].value = box.options[i + 1].value;
				}

				box.options[box.length - 1].text = sText;
				box.options[box.length - 1].value = sValue;

				box.selectedIndex = box.length - 1;
			}
			else if (si == (box.length - 1)) {
				for (var j = (box.length - 1); j > 0; j--) {
					box.options[j].text = box.options[j - 1].text;
					box.options[j].value = box.options[j - 1].value;
				}

				box.options[0].text = sText;
				box.options[0].value = sValue;

				box.selectedIndex = 0;
			}
		}
	},

	resizeTextarea: function(elString, usingRichEditor, resizeToInlinePopup) {
		var init = function() {
			var el = jQuery('#' + elString);

			if (!el.length) {
				el = jQuery('textarea[@name=' + elString + ']');
			}

			if (el.length) {
				var pageBody;

				if (resizeToInlinePopup) {
					pageBody = el.parents('.popup:first');
				}
				else {
					pageBody = jQuery('body');
				}

				var resize = function() {
					var pageBodyHeight = pageBody.height();

					if (usingRichEditor) {
						try {
							if (!el.is('iframe')) {
								el = eval(elString);

								if (!el.jquery) {
									el = jQuery(el);
								}
							}
						}
						catch (e) {
						}
					}

					var diff = 150;

					if (!resizeToInlinePopup) {
						diff = 100;
					}

					el.css(
						{
							height: (pageBodyHeight - diff) + "px",
							width: '98%'
						}
					);
				};

				resize();

				if (resizeToInlinePopup) {
					jQuery(document).bind('popupResize', resize);
				}
				else {
					jQuery(window).resize(resize);
				}
			}
		};

		jQuery(init);
	},

	resubmitCountdown: function(formName) {
		if (Liferay.Util.submitCountdown > 0) {
			Liferay.Util.submitCountdown--;

			setTimeout("Liferay.Util.resubmitCountdown('" + formName + "')", 1000);
		}
		else {
			Liferay.Util.submitCountdown = 0;

			if (!Liferay.Browser.is_ns_4) {
				document.body.style.cursor = "auto";
			}

			var form = document.forms[formName];

			for (var i = 0; i < form.length; i++){
				var e = form.elements[i];

				if (e.type && (e.type.toLowerCase() == "button" || e.type.toLowerCase() == "reset" || e.type.toLowerCase() == "submit")) {
					e.disabled = false;
				}
			}
		}
	},

	savePortletTitle: function(params) {
		var defaultParams = {
			plid: 0,
			doAsUserId: 0,
			portletId: 0,
			title: '',
			url: themeDisplay.getPathMain() + '/portlet_configuration/update_title'
		};

		var settings = jQuery.extend(defaultParams, params);

		jQuery.ajax(
			{
				url: settings.url,
				data: {
					p_l_id: settings.plid,
					doAsUserId: settings.doAsUserId,
					portletId: settings.portletId,
					title: settings.title
				}
			}
		);
	},

	selectAndCopy: function(el) {
		el.focus();
		el.select();

		if (document.all) {
			var textRange = el.createTextRange();

			textRange.execCommand("copy");
		}
	},

	setBox: function(oldBox, newBox) {
		for (var i = oldBox.length - 1; i > -1; i--) {
			oldBox.options[i] = null;
		}

		for (var i = 0; i < newBox.length; i++) {
			oldBox.options[i] = new Option(newBox[i].value, i);
		}

		oldBox.options[0].selected = true;
	},

	setSelectedValue: function(col, value) {
		jQuery('option[@value=' + value + ']', col).attr('selected', true);
	},

	showCapsLock: function(event, span) {
		var keyCode = event.keyCode ? event.keyCode : event.which;
		var shiftKey = event.shiftKey ? event.shiftKey : ((keyCode == 16) ? true : false);

		if (((keyCode >= 65 && keyCode <= 90) && !shiftKey) ||
			((keyCode >= 97 && keyCode <= 122) && shiftKey)) {

			document.getElementById(span).style.display = '';
		}
		else {
			document.getElementById(span).style.display = 'none';
		}
	},

	sortBox: function(box) {
		var newBox = [];

		for (var i = 0; i < box.length; i++) {
			newBox[i] = [box[i].value, box[i].text];
		}

		newBox.sort(Liferay.Util.sortByAscending);

		var boxObj = jQuery(box);

		boxObj.find('option').remove();

		jQuery.each(
			newBox,
			function(key, value) {
				boxObj.append('<option value="' + value[0] + '">' + value[1] + '</option>');
			}
		);
	},

	sortByAscending: function(a, b) {
		if (a[1].toLowerCase() > b[1].toLowerCase()) {
			return 1;
		}
		else if (a[1].toLowerCase() < b[1].toLowerCase()) {
			return -1;
		}
		else {
			return 0;
		}
	},

	startsWith: function(str, x) {
		return (str.indexOf(x) === 0);
	},

	switchEditor: function(options) {
		var instance = this;

		/*
		url (String): url to open that sets the editor
		popup (String|DOM|jQuery element): the popup that contains the editor
		textarea (String): the name of the textarea to auto-resize
		*/

		if (options.url && options.popup) {
			var url = options.url;
			var popup = options.popup;
			var textarea = options.textarea;

			if (!popup.jquery) {
				popup = jQuery(popup);
			}

			var popupMessage = popup.find('.popup-message');

			jQuery.ajax(
				{
					url: url,
					beforeSend: function() {
						popupMessage.empty();
						popupMessage.append('<div class="loading-animation"><div>');
					},
				  	success: function(message) {
						popupMessage.empty();
						popupMessage.append(message);

						if (textarea) {
							var usingPlainEditor = popup.find('.lfr-textarea').length;

							Liferay.Util.resizeTextarea(textarea, !usingPlainEditor, true);
						}
				 	}
				}
			);
		}
	},

	toggleByIdSpan: function(obj, id) {
		jQuery('#' + id).toggle();

		var spans = jQuery(obj).find('span');

		spans.toggle();
	},

	toggle: function(obj, returnState, displayType) {
		if (typeof obj == 'string') {
			obj = '#' + obj;
		}

		var el = jQuery(obj);
		var hidden = el.toggle().is(':visible');

		if (displayType) {
			el.css('display', displayType);
			hidden = el.is(':visible');
		}

		if (returnState) {
			return hidden;
		}
	},

	toggleBoxes: function(checkBoxId, toggleBoxId) {
		var checkBox = jQuery('#' + checkBoxId);
		var toggleBox = jQuery('#' + toggleBoxId);

		if (!checkBox.is(':checked')){
			toggleBox.hide();
		}

		checkBox.click(
			function(){
				toggleBox.toggle();
			}
		);
	},

	toJSONObject: function(s) {
		return jQuery.parseJSON(s);
	},

	toJSONString: function (s) {
		var rt = s;
		var m = {
			'\b': '\\b',
			'\t': '\\t',
			'\n': '\\n',
			'\f': '\\f',
			'\r': '\\r',
			'"' : '\\"',
			'\\': '\\\\'
		};

		if (/["\\\x00-\x1f]/.test(s)) {
			rt = s.replace(/([\x00-\x1f\\"])/g, function(a, b) {
				var c = m[b];
				if (c) {
					return c;
				}
				c = b.charCodeAt();
				return '\\u00' +
					Math.floor(c / 16).toString(16) +
					(c % 16).toString(16);
			});
		}

		return rt;
	}
};

Element = {};

Element.disable = function(element) {
	element = jQuery.getOne(element);

	var items = element.getElementsByTagName("*");

	for (var i = 0; i < items.length; i++) {
		var item = items[i];
		var nodeName = item.nodeName.toLowerCase();

		item.onclick = function() {};
		item.onmouseover = function() {};
		item.onmouseout = function() {};

		if (Liferay.Browser.is_ie) {
			item.onmouseenter = function() {};
			item.onmouseleave = function() {};
		}

		if (nodeName == "a") {
			item.href = "javascript: void(0)";
		}
		else if (nodeName == "input" || nodeName == "select" || nodeName == "script") {
			item.disabled = "true";
		}
		else if (nodeName == "form") {
			item.action = "";
			item.onsubmit = function() { return false; };
		}

		item.style.cursor = "default";
	}
};

Element.remove = function(id) {
	var obj = jQuery.getOne(id);

	obj.parentNode.removeChild(obj);
};

function LinkedList() {
	this.head = null;
	this.tail = null;
}

LinkedList.prototype.add = function(obj) {
	obj.listInfo = {};
	var tail = this.tail;
	var head = this.head;

	if (this.head == null) {
		this.head = obj;
		this.tail = obj;
	}
	else {
		this.tail.listInfo.next = obj;
		obj.listInfo.prev = this.tail;
		this.tail = obj;
	}

	obj.listInfo.listObj = this;
};

LinkedList.prototype.remove = function(obj) {
	if (obj.listInfo.listObj == this && this.head) {
		var next = obj.listInfo.next;
		var prev = obj.listInfo.prev;

		if (next) {
			next.listInfo.prev = prev;
		}
		if (prev) {
			prev.listInfo.next = next;
		}
		if (this.head == obj) {
			this.head = next;
		}
		if (this.tail == obj) {
			this.tail = prev;
		}
	}
};

LinkedList.prototype.each = function(func) {
	var cur = this.head;
	var count = 0;

	while (cur){
		count++;
		var next = cur.listInfo.next;

		if (func) {
			func(cur);
		}

		cur = next;
	}

	return count;
};

LinkedList.prototype.size = function() {
	return this.each();
};

function submitForm(form, action, singleSubmit) {
	if (Liferay.Util.submitCountdown == 0) {
		Liferay.Util.submitCountdown = 10;

		setTimeout("Liferay.Util.resubmitCountdown('" + form.name + "')", 1000);

		if (singleSubmit == null || singleSubmit) {
			Liferay.Util.submitCountdown++;

			var inputs = jQuery('input[@type=button], input[@type=reset], input[@type=submit]', form);

			inputs.each(
				function(i, el) {
					var input = jQuery(this);

					input.attr('disabled', true);
					input.fadeTo(50, 0.5);
				}
			);
		}

		if (action != null) {
			form.action = action;
		}

		if (!Liferay.Browser.is_ns_4) {
			document.body.style.cursor = "wait";
		}

		form.submit();
	}
}

var Viewport = {
	frame: function() {
		var x,y;
		if (self.innerHeight) // all except Explorer
		{
			x = self.innerWidth;
			y = self.innerHeight;
		}
		else if (document.documentElement && document.documentElement.clientHeight)
			// Explorer 6 Strict Mode
		{
			x = document.documentElement.clientWidth;
			y = document.documentElement.clientHeight;
		}
		else if (document.body) // other Explorers
		{
			x = document.body.clientWidth;
			y = document.body.clientHeight;
		}

		return (new Coordinate(x,y));
	},

	scroll: function() {
		var x,y;
		if (self.pageYOffset) {
			// all except Explorer
			x = self.pageXOffset;
			y = self.pageYOffset;
		}
		else if (document.documentElement && document.documentElement.scrollTop) {
			// Explorer 6 Strict
			x = document.documentElement.scrollLeft;
			y = document.documentElement.scrollTop;
		}
		else if (document.body) {
			// all other Explorers
			x = document.body.scrollLeft;
			y = document.body.scrollTop;
		}

		return (new Coordinate(x,y));
	},

	page: function() {
		var x,y;
		var test1 = document.body.scrollHeight;
		var test2 = document.body.offsetHeight;
		if (test1 > test2) // all but Explorer Mac
		{
			x = document.body.scrollWidth;
			y = document.body.scrollHeight;
		}
		else // Explorer Mac;
			//would also work in Explorer 6 Strict, Mozilla and Safari
		{
			x = document.body.offsetWidth;
			y = document.body.offsetHeight;
		}

		return (new Coordinate(x,y));
	}
};

String.prototype.trim = jQuery.trim;

// 0-200: Theme Developer
// 200-400: Portlet Developer
// 400+: Liferay

Liferay.zIndex = {
	DOCK:			10,
	DOCK_PARENT:	20,
	ALERT:			430,
	DROP_AREA:		440,
	DROP_POSITION:	450,
	DRAG_ITEM:		460,
	TOOLTIP:		470
};
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
function AjaxRequest(url, options) {

	var xmlHttpReq;
	var opts = options;

	if (window.XMLHttpRequest) {
		xmlHttpReq = new XMLHttpRequest();

		if (xmlHttpReq.overrideMimeType) {
			xmlHttpReq.overrideMimeType("text/html");
		}
	}
	else if (window.ActiveXObject) {
		try {
			xmlHttpReq = new ActiveXObject("Msxml2.XMLHTTP");
		}
		catch (e) {
			try {
				xmlHttpReq = new ActiveXObject("Microsoft.XMLHTTP");
			}
			catch (e) {
				try {
					xmlHttpReq = new XMLHttpRequest();
				}
				catch (e) {
				}
			}
		}
	}

	var returnFunction = function() {
		if (xmlHttpReq.readyState == 4) {
			try {
				if (xmlHttpReq.status == 200) {
					if (opts.update) {
						var el = jQuery.getOne(opts.update);
						el.innerHTML = xmlHttpReq.responseText;
						executeLoadedScript(el);
					}

					if (opts.onComplete) {
						opts.onComplete(xmlHttpReq, opts.returnArgs);
					}

					AjaxUtil.remove(opts.ajaxId);
				}
			}
			catch(e) {
			}
		}
	};

	var send = function(url) {
		url = Liferay.Util.getURLWithSessionId(url);

		var urlArray = url.split("?");
		var path = urlArray[0];
		var query = urlArray[1];

		try {
			if (opts.method == "get") {
				xmlHttpReq.open("GET", url, true);
				xmlHttpReq.onreadystatechange = returnFunction;
				xmlHttpReq.send("");
			}
			else {
				xmlHttpReq.open("POST", path, true);
				xmlHttpReq.setRequestHeader("Method", "POST " + path + " HTTP/1.1");
				xmlHttpReq.setRequestHeader("Content-Type", "application/x-www-form-urlencoded");
				xmlHttpReq.onreadystatechange = returnFunction;
				xmlHttpReq.send(query);
			}
		}
		catch (e) {
		}
	};

	send(url);

	this.resend = function(url, options) {
		opts = options;
		/*
		ajaxId = 0;
		onComplete = opts.onComplete;
		*/
		send(url);
	};

	this.getId = function() {
		return ajaxId;
	};

	this.cleanUp = function() {
		xmlHttpReq.onreadystatechange = function() {};
		returnFunction = null;
		returnArgs = null;
		xmlHttpReq = null;
	};
}

var AjaxUtil = {
	counter : 1,
	requests : [],

	request : function(url, options) {
		/*
		 * OPTIONS:
		 * onComplete (function) - function to call after response is received
		 * returnArgs (object) - object to pass to return function
		 * reverseAjax (boolean) - use reverse ajax. (only one at a time)
		 * method (string) - use "get" or "post". Default is post.
		 */
		var opts = options || {};
		var ajaxId = (opts.reverseAjax) ? 0 : AjaxUtil.getNextId();
		opts.ajaxId = ajaxId;

		var request;

		if (ajaxId == 0 && AjaxUtil.requests[0]) {
			request = AjaxUtil.requests[0];
			request.resend(url, opts);
		}
		else {
			request = new AjaxRequest(url, opts);
			AjaxUtil.requests[ajaxId] = request;
		}

		if (!opts.onComplete && !opts.update) {
			AjaxUtil.remove(ajaxId);
		}
	},

	submit: function(form, options) {
		var url = form.action;
		var inputs = jQuery("input, textarea, select", form);
		var opts = options || {};
		var params = inputs.serialize();

		if (url.indexOf("?") == -1) {
			url = url + "?" + params;
		}

		if (url.lastIndexOf("?") == url.length - 1) {
			url = url + params;
		}
		else {
			url = url + "&" + params;
		}

		if (opts.disable) {
			inputs.attr("disabled", true);
		}

		AjaxUtil.request(url, opts);
	},

	update : function(url, id, options) {
		var opts = options || {};

		opts.update = id;

		AjaxUtil.request(url, opts);
	},

	getNextId : function() {
		var id = AjaxUtil.counter++;

		if (AjaxUtil.counter > 20) {
			/* Reset array in a round-robin fashion */
			/* Reserve index 0 for reverse ajax requests */
			AjaxUtil.counter = 1;
		}

		return id;
	},

	remove : function(id) {
		if (id) {
			var request = AjaxUtil.requests[id];

			if (request) {
				request.cleanUp();
				request = null;
			}
		}
	}
};

var ReverseAjax = {
	initialize: function() {
		jQuery(window).bind('unload', ReverseAjax.release);
		ReverseAjax.request();
	},

	request: function() {
		AjaxUtil.request(
			themeDisplay.getPathMain() + "/portal/reverse_ajax",
			{
				onComplete: ReverseAjax.response,
				reverseAjax: true
			}
		);
	},

	response: function(xmlHttpRequest) {
		var res = Liferay.Util.toJSONObject(xmlHttpRequest.responseText);
		var status = res.status;

		if (status && status != "failure") {
			if (status == "success") {
				if (res.chatMessages) {
					Messaging.getChatsReturn(res.chatMessages);
				}
				if (res.chatRoster) {
					MessagingRoster.getEntriesReturn(res.chatRoster);
				}
			}

			ReverseAjax.request();
		}
	},

	release : function() {
		AjaxUtil.request(themeDisplay.getPathMain() + "/portal/reverse_ajax?release=1", {reverseAjax:true});
	}
};

function executeLoadedScript(el) {
	var scripts = el.getElementsByTagName("script");

	for (var i = 0; i < scripts.length; i++) {
		if (scripts[i].src) {
			var head = document.getElementsByTagName("head")[0];
			var scriptObj = document.createElement("script");

			scriptObj.setAttribute("type", "text/javascript");
			scriptObj.setAttribute("src", scripts[i].src);

			head.appendChild(scriptObj);
		}
		else {
			try {
				if (Liferay.Browser.is_safari) {
					eval(scripts[i].innerHTML);
				}
				else if (Liferay.Browser.is_mozilla) {
					eval(scripts[i].textContent);
				}
				else {
					eval(scripts[i].text);
				}
			}
			catch (e) {}
		}
	}
}

/*
 * NOTE: loadPage() has been depricated.  Use AjaxUtil.request() instead
 */
function loadPage(path, queryString, returnFunction, returnArgs) {
	AjaxUtil.request(
		path + "?" + queryString,
		{
			onComplete: returnFunction,
			returnArgs: returnArgs
		}
	);
}

function printJSON(data) {
	if (data && data.id) {
		var target = document.getElementById(data.id);

		if (target) {
			target.innerHTML = data.toString();
		}
	}
}
Liferay.Animate = function(id, fn, data) {

	/* id - unique identifier for this process
	 * fn - animation function
	 * data - object that is passed to the animation function
	 * data.delay - assign a number (in milliseconds) to this property
	 *				to delay the start of the animation process
	 */
	var lib = Liferay.Animate;

	if (!lib.q[id]) {
		lib.q[id] = {"id": id, "fn": fn, "data": data};
	}

	if (!lib.timer) {
		lib.start();
	}
};

Liferay.Animate.extendNativeFunctionObject({
	q: {},
	timer: 0,

	process: function() {
		var processed = false;
		for (var i in this.q) {
			var item = this.q[i];
			if (item) {
				var rt = item.fn(item.data);

				if (rt == false) {
					this.q[i] = null;
				}
				processed = true;
			}
		}

		if (!processed) {
			this.stop();
		}
	},

	start: function() {
		var lib = Liferay.Animate;
		if (!lib.timer) {
			Liferay.Animate.process();
			Liferay.Animate.timer = setInterval("Liferay.Animate.process()", 30);
		}
	},

	stop: function() {
		clearInterval(Liferay.Animate.timer);
		Liferay.Animate.timer = 0;
	}
});
/**********************************************************
 Very minorly modified from the example by Tim Taylor
 http://tool-man.org/examples/sorting.html

 Added Coordinate.prototype.inside( northwest, southeast );

 **********************************************************/


var Coordinates = {
	ORIGIN : new Coordinate(0, 0),

	coordinatesData: function(element, recurse) {
		var data = {};

		data.recurse = recurse;
		data.size = new Coordinate(element.offsetWidth, element.offsetHeight);
		data.nwOffset = Coordinates.northwestOffset(element, recurse);
		data.seOffset = data.nwOffset.plus(data.size);
		data.midPoint = data.nwOffset.plus(new Coordinate(Math.round(data.size.x/2), Math.round(data.size.y/2)));

		return data;
	},

	northwestPosition : function(element) {
		var x = parseInt(element.style.left);
		var y = parseInt(element.style.top);

		return new Coordinate(isNaN(x) ? 0 : x, isNaN(y) ? 0 : y);
	},

	southeastPosition : function(element) {
		return Coordinates.northwestPosition(element).plus(
				new Coordinate(element.offsetWidth, element.offsetHeight));
	},

	northwestOffset : function(element, isRecursive) {
		var offset = new Coordinate(element.offsetLeft, element.offsetTop);

		if (!isRecursive) return offset;

		var parent = element.offsetParent;
		while (parent) {
			offset = offset.plus(
					new Coordinate(parent.offsetLeft, parent.offsetTop));
			parent = parent.offsetParent;
		}
		return offset;
	},

	southeastOffset : function(element, isRecursive) {
		return Coordinates.northwestOffset(element, isRecursive).plus(
				new Coordinate(element.offsetWidth, element.offsetHeight));
	}
};

function Coordinate(x, y) {
	this.x = x || 0;
	this.y = y || 0;
}

Coordinate.prototype.toString = function() {
	return "(" + this.x + "," + this.y + ")";
};

Coordinate.prototype.plus = function(that) {
	return new Coordinate(this.x + that.x, this.y + that.y);
};

Coordinate.prototype.minus = function(that) {
	return new Coordinate(this.x - that.x, this.y - that.y);
};

Coordinate.prototype.distance = function(that) {
	var deltaX = this.x - that.x;
	var deltaY = this.y - that.y;

	return Math.sqrt(Math.pow(deltaX, 2) + Math.pow(deltaY, 2));
};

Coordinate.prototype.max = function(that) {
	var x = Math.max(this.x, that.x);
	var y = Math.max(this.y, that.y);
	return new Coordinate(x, y);
};

Coordinate.prototype.constrain = function(min, max) {
	if (min.x > max.x || min.y > max.y) return this;

	var x = this.x;
	var y = this.y;

	if (min.x != null) x = Math.max(x, min.x);
	if (max.x != null) x = Math.min(x, max.x);
	if (min.y != null) y = Math.max(y, min.y);
	if (max.y != null) y = Math.min(y, max.y);

	return new Coordinate(x, y);
};

Coordinate.prototype.reposition = function(element) {
	element.style["top"] = this.y + "px";
	element.style["left"] = this.x + "px";
};

Coordinate.prototype.equals = function(that) {
	if (this == that) return true;
	if (!that || that == null) return false;

	return this.x == that.x && this.y == that.y;
};

// returns true of this point is inside specified box
Coordinate.prototype.inside = function(northwest, southeast) {
	if ((this.x >= northwest.x) && (this.x <= southeast.x) &&
		(this.y >= northwest.y) && (this.y <= southeast.y)) {

		return true;
	}
	else {
		return false;
	}
};

Coordinate.prototype.insideObject = function(obj, recurse) {
	var data = Coordinates.coordinatesData(obj);
	data.recurse = recurse;
	data.quadrant = this.insideObjectData(data);

	return data.quadrant ? data : null;
};

Coordinate.prototype.insideObjectData = function(data) {
	var nwOffset = data.nwOffset;
	var seOffset = data.seOffset;
	var rt = 0;

	if (this.inside(nwOffset, seOffset)) {
		var mid = data.midPoint;

		if (this.x <= mid.x && this.y <= mid.y) {
			rt = 1;
		}
		else if (this.x >= mid.x && this.y <= mid.y) {
			rt = 2;
		}
		else if (this.x >= mid.x && this.y >= mid.y) {
			rt = 3;
		}
		else if (this.x <= mid.x && this.y >= mid.y) {
			rt = 4;
		}
	}

	return rt;
};

function MousePos () { };

// Extend the "Coordinate" class
MousePos.prototype = new Coordinate();

MousePos.prototype.update = function(event) {

	if (typeof event == 'undefined') {
		event = window.event;
	}

	var position = new Coordinate(event.clientX, event.clientY);

	var scrollOffset = Viewport.scroll();

	this.x = position.x + scrollOffset.x;
	this.y = position.y + scrollOffset.y;

	if (this.x < 0) this.x = 0;

	if (this.y < 0) this.y = 0;

	return event;
};

// Track mouse's absolute position (counting scrollbars)
var mousePos = new MousePos(0,0);

/*
 * jQuery extension
 */
jQuery.each([
				"coordinatesData",
				"northwestPosition",
				"southeastPosition",
				"northwestOffset",
				"southeastOffset"
			], function(i,n){

	jQuery.fn[ n ] = function(h) {
		return this.length > 0 ? Coordinates[n](this[0], h) : null;
	};
});

jQuery.fn.xySize = function() {
	return new Coordinate(this.width(), this.height());
};
(function($){

	$.fn.lDrag = function(options) {
		this.each(function() {
			$.lDrag.create(this, options);
		});
	};

	$.fn.lDragBind = function(type, fn) {
		this.each(function() {
			$.lDrag.bind(this, type, fn);
		});
	};

	$.fn.lDragUnbind = function(type, fn) {
		this.each(function() {
			$.lDrag.unbind(this, type, fn);
		});
	};


	/* Define lDrag */

	$.lDrag = function(container, options) {
		/* OPTIONS
		 * handle (object): drag handle
		 * onStart (function): excute at start
		 * onMove (function): execute during dragging
		 * onComplete (function):  execute when completed
		 */
		$.lDrag.create(container, options)
	};

	$.lDrag.extendNativeFunctionObject({
		container : null,
		isDragging : false,
		scrollDirection: "",
		scrollTimer: 0,

		bind: function(container, type, fn) {
			if (container.dragSettings && type && fn) {
				if (type == "start") {
					container.dragSettings.onDragStart.push(fn);
				}
				else if (type == "move") {
					container.dragSettings.onDrag.push(fn);
				}
				else if (type == "complete") {
					container.dragSettings.onDragEnd.push(fn);
				}
			}
		},

		unbind: function(container, type, fn) {
			if (container.dragSettings && type && fn) {
				var settings = container.dragSettings;
				var prop = "";

				if (type == "start") {
					prop = "onDragStart";
				}
				else if (type == "move") {
					prop = "onDrag";
				}
				else if (type == "complete") {
					prop = "onDragEnd";
				}

				for (var i = 0; i < settings[prop].length; i++) {
					if (settings[prop][i] == fn) {
						settings[prop].splice(i,1);
					}
				}
			}
		},

		create: function(container, options) {
			options = options || {};
			options.container = container;

		    if (options.handle == null) {
	    		options.handle = container;
    		}
    		else {
    			if (typeof options.handle == "string") {
    				options.handle = $(options.handle)[0];
    			}
				options.handle.dragSettings = options;
    		}
			container.dragSettings = options;

			options.onDragStart = [];
			options.onDrag = [];
			options.onDragEnd = [];

			// Bind event listeners
			if (options.onStart) {
				$.lDrag.bind(container, "start", options.onStart);
			}
			if (options.onMove) {
				$.lDrag.bind(container, "move", options.onMove);
			}
			if (options.onComplete) {
				$.lDrag.bind(container, "complete", options.onComplete);
			}

			jQuery(options.handle).mousedown($.lDrag.onMouseDown);
		},

		scroll: function() {
			Liferay.Animate("layoutDragScroll", $.lDrag.scrollStart);
		},

	    scrollStart: function() {
	        var nwPosition;
	        var container = $.lDrag.container;
	        var jContainer = $($.lDrag.container);
	        var setTimer = false;
	        var scrollSpeed = 20;
	        var scrollTop = Viewport.scroll().y;

	        if ($.lDrag.scrollDirection == "down") {
	            nwPosition = jContainer.northwestPosition();
	            nwPosition.y += scrollSpeed;
	            nwPosition.reposition(container);
	            window.scrollTo(0, scrollTop + scrollSpeed);
	            setTimer = true;
	        }
	        else if ($.lDrag.scrollDirection == "up" && scrollTop > 0) {
	            nwPosition = jContainer.northwestPosition();
	            nwPosition.y -= scrollSpeed;
	            nwPosition.reposition(container);
	            window.scrollTo(0, scrollTop - scrollSpeed);
	            setTimer = true;
	        }
	        else {
	            setTimer = false;
	        }

	        if (!setTimer) {
	            $.lDrag.scrollDirection = "";
	            $.lDrag.scrollTimer = 0;
	            return false;
	        }
	    },

		onMouseDown: function(event) {
			mousePos.update(event);

			var settings = this.dragSettings;
			var container = settings.container;
			var jContainer = $(settings.container);

			if (!container._LFR_noDrag) {
				$.lDrag.container = container;

				var nwOffset = jContainer.northwestOffset(true);
				var seOffset = nwOffset.plus(jContainer.xySize());

				settings.originalZIndex = container.style.zIndex;

				// Offset of the mouse relative to the dragging container
				// This should remain constant.
				settings.mouseNwOffset = mousePos.minus(nwOffset);
				settings.mouseSeOffset = mousePos.minus(seOffset);
				settings.mouseStart = new Coordinate(mousePos.x, mousePos.y);
				settings.browserEvent = event;

				$.lDrag._processListeners(settings, "start");

				$.lDrag._setConstraint(settings);

				jQuery(document).mousemove($.lDrag.onMouseMove);
				jQuery(document).mouseup($.lDrag.onMouseUp);

				return false;
			}
			else {
				return;
			}
		},

		onMouseMove: function(event) {
			mousePos.update(event);
			// Assigning "container" because event is associated with the document
			// and not the dragging obj.  This is for robustness during a drag
			var container = $.lDrag.container;
			var settings = container.dragSettings;

			if (!$.lDrag._isAboveThreshold(settings)) {
				return false;
			}
			else {
				$.lDrag.isDragging = true;
			}

			container = settings.clone ? $.lDrag._createClone(settings) : settings.container;

			var jContainer = $(container);
			var nwOffset = jContainer.northwestOffset(true);
			var nwPosition = jContainer.northwestPosition();
			var size = jContainer.xySize();
			var seOffset = nwOffset.plus(size);
			var sePosition = nwPosition.plus(size);

			$.lDrag._setScrolling(settings);

			// new-pos = cur-pos + (mouse-pos - mouse-offset - screen-offset)
			//
			//	 new-pos: where we want to position the element using styles
			//	 cur-pos: current styled position of container
			//	 mouse-pos: mouse position
			//	 mouse-offset: mouse position relative to the dragging container
			//	 screen-offset: screen position of the current element
			//
			nwPosition = nwPosition.plus(mousePos.minus(nwOffset).minus(settings.mouseNwOffset));

			var offsetBefore = settings.autoCorrect ? jContainer.northwestOffset(true) : null;

			if (!settings.noDrag) {
				nwPosition.reposition(container);
			}

			settings.browserEvent = event;

			$.lDrag._processListeners(settings, "move");

			// once dragging has started, the position of the container
			// relative to the mouse should stay fixed.  They can get out
			// of sync if the DOM is manipulated while dragging, so we
			// correct the error here
			//
			// changed to be recursive/use absolute offset for corrections


			if (settings.autoCorrect) {
				var offsetAfter = jContainer.northwestOffset(true);

				if (!offsetBefore.equals(offsetAfter)) {
					// Position of the container has changed after the onDrag call.
					// Move element to the current mouse position
					var errorDelta = offsetBefore.minus(offsetAfter);
					nwPosition = jContainer.northwestPosition().plus(errorDelta);
					nwPosition.reposition(container);
				}
			}

			return false;
		},

		onMouseUp: function(event) {
			event = mousePos.update(event);
			var container = $.lDrag.container;
			var settings = container.dragSettings;

			if (settings.clone) $.lDrag._destroyClone(settings);

			jQuery(document).unbind("mousemove", $.lDrag.onMouseMove);
			jQuery(document).unbind("mouseup", $.lDrag.onMouseUp);

			settings.browserEvent = event;

			$.lDrag._processListeners(settings, "complete");
			$.lDrag.container = null;
			$.lDrag.isDragging = false;
		},

		_createClone: function(settings) {
			if (!settings.clonedNode) {
				var jClone = $("<div></div>");
				var jContainer = $(settings.container);
				var nwPosition = jContainer.northwestOffset(true);

				jClone.css({
					height: jContainer.height() + "px",
					left: nwPosition.x + "px",
					position: "absolute",
					top: nwPosition.y + "px",
					width: jContainer.width() + "px",
					zIndex: Liferay.zIndex.DRAG_ITEM
				});

				if (settings.opacity) jClone.css("opacity", settings.opacity);
				if (settings.dragClass) jClone.addClass(settings.dragClass);

				jClone[0].dragSettings = settings;
				settings.clonedNode = jClone[0];

				$("body").append(jClone);
			}

			return settings.clonedNode;
		},

		_destroyClone: function(settings) {
			if (settings.clonedNode) {
				var jClone = $(settings.clonedNode);
				var jContainer = $(settings.container);
				var containerPos = jContainer.northwestPosition();
				var newPos = containerPos.plus(mousePos.minus(settings.mouseStart));

				newPos.reposition(settings.container);

				jClone.remove();
				settings.clonedNode = null;
			}
		},

		_isAboveThreshold: function(settings) {
			var rt = true;
			if (!$.lDrag.isDragging && settings.threshold) {
				var distance = settings.mouseStart.distance(mousePos);
				if (distance < settings.threshold) {
					rt = false;
				}
			}

			return rt;
		},

		_processListeners: function(settings, type) {
			var prop = "";

			if (type == "start") {
				prop = "onDragStart";
			}
			else if (type == "move") {
				prop = "onDrag";
			}
			else if (type == "complete") {
				prop = "onDragEnd";
			}

			for (var i = 0; i < settings[prop].length; i++) {
				settings[prop][i](settings);
			}
		},

		_setConstraint: function(settings) {
			// Constraint coordinates are translated to mouse constraint coordinates.
			// The algorithm below will looks at the bounds of the dragging container and
			// makes sure that no part of it extends outside the constraint bounds.

			var minMouseX;
			var minMouseY;
			var maxMouseX;
			var maxMouseY;

			if (settings.minX != null)
				minMouseX = settings.minX + settings.mouseNwOffset.x;
			if (settings.minY != null)
				minMouseY = settings.minY + settings.mouseNwOffset.y;
			if (settings.maxX != null)
				maxMouseX = settings.maxX + settings.mouseSeOffset.x;
			if (settings.maxY != null)
				maxMouseY = settings.maxY + settings.mouseSeOffset.y;

			if (minMouseX && maxMouseX && minMouseX > maxMouseX)
				maxMouseX = minMouseX;
			if (minMouseY && maxMouseY && minMouseY > maxMouseY)
				maxMouseY = minMouseY;

			settings.mouseMin = new Coordinate(minMouseX, minMouseY);
			settings.mouseMax = new Coordinate(maxMouseX, maxMouseY);
		},

		_setScrolling: function(settings) {
			// Automatically scroll the page it drags near the top or bottom
			if (settings.scroll) {
				var scrollZone = 30;
				var scrollSpeed = 5;
				var scrollTop = Viewport.scroll().y;
				var pageHeight = Viewport.page().y;
				var clientHeight = Viewport.frame().y;

				if ((scrollTop + clientHeight + 2 * scrollZone) < pageHeight
						&& mousePos.y > (scrollTop + clientHeight - scrollZone)) {

		            if ($.lDrag.scrollDirection != "down"){
		                $.lDrag.scrollDirection = "down";
		                $.lDrag.scroll();
		            }
				}
				else if (scrollTop > 0 && mousePos.y < (scrollTop + scrollZone)) {
		            if ($.lDrag.scrollDirection != "up"){
		                $.lDrag.scrollDirection = "up";
		                $.lDrag.scroll();
		            }
				}
				else {
		            $.lDrag.scrollDirection = "";
				}
			}
		}
	});
})(jQuery);
(function ($) {
	$.fn.lResize = function(options) {
		this.each(function() {
			$.lResize(this, options);
		});
	};

	$.fn.lResizeBind = $.fn.lDragBind;

	$.fn.lResizeHandleRule = function(options) {
		this.each(function() {
			options.handle = this;
			$.lResize.handleRule(options);
		});
	};

	$.lResize = function(container, options) {
		/* OPTIONS
		 * handle (object): resize handle
		 * onStart (function): execute when start
		 * onMove (function): execute when resizing
		 * onComplete (function): execute when completed
		 */
		$.lResize.create(container, options);
	};

	$.lResize.extendNativeFunctionObject({

		/* Resize direction */
		HORIZONTAL : "horizontal",
		VERTICAL : "vertical",

		/* Resize modes */
		ADD : "add",
		SUBTRACT : "subtract",

		resizeRule: function(container, direction, mode) {
			this.container = container;
			this.direction = direction;
			this.next = null;
			this.origWidth = null;
			this.origHeight = null;
			this.mode = mode;
		},

		handleRule: function(options) {
			var handle = options.handle;

			if (typeof handle == "string") {
				handle = $(handle);
			}

			var settings = handle.resizeSettings;

			if (!settings) {
				$.lResize.create(settings.container, settings)
			}
			else {
				settings.resizeRules.push(new $.lResize.resizeRule(
					settings.container, settings.direction, settings.mode));
			}
		},

		bind: function(container, type, fn) {
			$.lDrag.bind(container, type, fn);
		},

		create: function(container, options) {
			if (options.handle && options.direction && options.mode) {
    			if (typeof options.handle == "string") {
    				options.handle = $(options.handle)[0];
    			}

				var handle = options.handle;

				if (!handle.resizeSettings) {
					handle.resizeSettings = options;
				}

				var settings = handle.resizeSettings;

				if (!handle.dragSettings || !handle.dragSettings.isResizeHandle) {
					$.lDrag.create(handle, {
						onStart: $.lResize.onMouseDown,
						onMove: $.lResize.onResize,
						onComplete: $.lResize.onMouseUp,
						noDrag: !options.drag,
						isResizeHandle: true
					});
				}

				var jHandle = $(handle);
				jHandle.lDragBind("start", options.onStart);
				jHandle.lDragBind("move", options.onMove);
				jHandle.lDragBind("complete", options.onComplete);

				if (!settings.resizeRules) {
					settings.resizeRules = [];
				}

				settings.resizeRules.push(new $.lResize.resizeRule(container, options.direction, options.mode));
			}
		},

		onMouseDown : function() {
			var handle = $.lDrag.container;
			var settings = handle.resizeSettings;
			var mouse = mousePos;

			settings.mouseStart = new Coordinate(mousePos.x, mousePos.y);

			for (var i = 0; i < settings.resizeRules.length; i++) {
				var resizeRule = settings.resizeRules[i];
				var jContainer = $(resizeRule.container);

				resizeRule.origWidth = jContainer.width();
				resizeRule.origHeight = jContainer.height();
			}
		},

		onResize: function() {
			var handle = $.lDrag.container;
			var settings = handle.resizeSettings;
			var mouse = mousePos;
			var mouseDelta = mousePos.minus(settings.mouseStart);

			var newLength;
			var lengthCorrection = 0;
			var noChange = false;

			for (var i = 0; i < settings.resizeRules.length; i++) {
				var resizeRule = settings.resizeRules[i];
				var jContainer = $(resizeRule.container);

				if (resizeRule.direction == $.lResize.HORIZONTAL) {
					resizeRule.prevLength = jContainer.width();

					if (resizeRule.mode == $.lResize.ADD) {
						newLength = resizeRule.origWidth + mouseDelta.x;
					}
					else {
						newLength = resizeRule.origWidth - mouseDelta.x
					}
				}
				else if (resizeRule.direction == $.lResize.VERTICAL) {
					resizeRule.prevLength = jContainer.height();

					if (resizeRule.mode == $.lResize.ADD) {
						newLength = resizeRule.origHeight + mouseDelta.y;
					}
					else {
						newLength = resizeRule.origHeight - mouseDelta.y;
					}
				}

				resizeRule.newLength = newLength;

				if (newLength < 1) {
					lengthCorrection = Math.max(-newLength + 1, lengthCorrection);
					newLength = 1;
				}

				if (newLength == resizeRule.prevLength) {
					noChange = true;
				}
			}

			for (var i = 0; i < settings.resizeRules.length; i++) {
				var resizeRule = settings.resizeRules[i];
				var jContainer = $(resizeRule.container);

				if (!settings.disableStop && noChange) {
					newLength = resizeRule.prevLength;
				}
				else if (resizeRule.newLength < 1) {
					newLength = resizeRule.newLength + lengthCorrection;
				}
				else {
					newLength = resizeRule.newLength - lengthCorrection;
				}

				if (resizeRule.direction == $.lResize.HORIZONTAL) {
						jContainer.width(newLength);
				}
				else if (resizeRule.direction == $.lResize.VERTICAL) {
						jContainer.height(newLength);
				}
			}
		},

		onMouseUp: function() {
			var handle = $.lDrag.container;
			var settings = handle.resizeSettings;

			settings.mouseEnd = new Coordinate(mousePos.x, mousePos.y);
		}
	});
})(jQuery);
(function($){
	$.Popup = function(options) {
		return $.Popup.open(options);
	};

	$.Popup.extendNativeFunctionObject({
		close: function(link) {
			var instance = this;

			jQuery(link).parents(".popup:first").remove();

			var jModal = jQuery("#alert-messages .modal:last");

			if (jModal.length) {
				jModal.before(jQuery("#alert-messages .alert-background"));
			}
			else {
				var jBg = jQuery("#alert-messages .alert-background");

				jBg.fadeTo("normal", 0, function() {
					jBg.remove();
				});

				jQuery(window).unbind("resize", $.Popup.center);
				jQuery(window).unbind("resize", $.Popup.resize);
				jQuery(window).unbind("scroll", $.Popup.center);
			}

			if (jQuery.browser.msie &&
				jQuery.browser.version.number() < 7 &&
				$.Popup.count() == 0) {

				jQuery("select").css("visibility", "visible");
			}

			if (instance.options.onClose) {
				instance.options.onClose();
			}
		},

		count: function() {
			return jQuery("#alert-messages .popup").length;
		},

		open: function(options) {
			/*
			 * OPTIONS:
			 * modal (boolean) - show shaded background
			 * message (string|object) - default HTML/object to display
			 * noCenter (boolean) - prevent re-centering
			 * height (int) - starting height of message box
			 * width (int) - starting width of message box
			 * onClose (function) - executes after closing
			 */

			var instance = this;

			options = options || {};

			instance.options = options;

			var modal = options.modal;
			var myMessage = options.message;
			var myMessageId = options.messageId;
			var msgHeight = options.height;
			var msgWidth = options.width;
			var noCenter = options.noCenter;
			var title = options.title;
			var onClose = options.onClose;

			var jAlertMsgs = jQuery("#alert-messages");

			if (!jAlertMsgs.length) {
				jQuery("body").append("<div id='alert-messages' style='position:absolute; top:0; left:0; z-index:" + Liferay.zIndex.ALERT + "'></div>");
				jAlertMsgs = jQuery("#alert-messages");
			}


			jAlertMsgs.append(
				"<div class='popup " + (modal ? "modal" : "") + "' style='position:absolute; top:0; left:0;'>" +
					"<div class='popup-inner'>" +
						"<div class='popup-header'>" +
							"<span class='popup-title'>" + (title || "&nbsp;") + "</span>" +
							"<img class='popup-close' src='" + themeDisplay.getPathThemeImages() + "/portlet/close.png'/>" +
						"</div>" +
						"<div class='popup-message'></div>" +
					"</div>" +
				"</div>");

			var jPopup = jAlertMsgs.find(".popup:last");
			var jMessage = jPopup.find(".popup-message");

			if (myMessageId) {
				jMessage.attr("id", myMessageId);
			}

			jPopup.find(".popup-close").click(function() {
				$.Popup.close(this);
			});

			if (onClose != null) {
				jPopup.find(".popup-close").click(onClose);
			}

			jPopup[0].alertOptions = options;

			jMessage.append(myMessage || "<div class=\"loading-animation\"></div>");

			if (msgHeight) {
				jMessage.css(jQuery.browser.msie ? "height" : "min-height", msgHeight + "px");
			}

			if (msgWidth) {
				jPopup.css("width", msgWidth + "px");
			}

			jPopup.mousedown(function() {
				if (this != jQuery("#alert-messages .popup:last")[0]) {
					jQuery("#alert-messages").append(this);
				}
			});

			var jBg = jAlertMsgs.find(".alert-background");

			if (modal) {
				if (jBg.length) {
					jPopup.before(jBg[0]);
				}
				else {
					jPopup.before("<div class='alert-background' style='position:absolute; top:0; left:0'></div>");
					jBg = jAlertMsgs.find(".alert-background");
					jBg.css({display: "none", opacity: 0});
				}
			}

			if (jQuery.browser.msie &&
				jQuery.browser.version.number("round") < 7 &&
				$.Popup.count() == 1) {

				jQuery('select').css('visibility', 'hidden');
				jPopup.find('select').css('visibility', 'visible');
			}

			if (jAlertMsgs.find(".popup").length == 1) {
				jQuery(window).resize($.Popup.center);
				jQuery(window).resize($.Popup.resize);
				jQuery(window).scroll($.Popup.center);
			}

			$.Popup.resize();
			jBg.fadeTo("normal", 0.5);

			if (false) {

				// jQuery Draggable is slow

				jPopup.Draggable(
					{
						handle: jPopup.find(".popup-header")[0],
						zIndex: Liferay.zIndex.ALERT + 1
					}
				);
			}
			else {
				jPopup.lDrag(
					{
						handle: jPopup.find(".popup-header")[0],
						threshold: 2,
						dragClass: "drag-indicator"
					}
				);
			}

			if (noCenter) {
				$.Popup.center();
			}
			else {
				$.Popup.center(msgHeight, msgWidth);
			}

			Liferay.Util.addInputType(jPopup[0]);
			Liferay.Util.addInputFocus(jPopup[0]);
			window.focus();

			return jMessage[0];
		},

		iframe : function(url, options) {
			var msgHeight = options.height;
			var msgWidth = options.width;
			var message = $.Popup.open(options);
			var iframe = document.createElement("iframe");

			message.height = "";
			iframe.src = url;
			iframe.frameBorder = 0;

			if (msgWidth) {
				iframe.style.width = "100%";
			}

			message.appendChild(iframe);

			if (!options.noCenter) {
				$.Popup.center(msgHeight, msgWidth);
			}

			return message;
		},

		center : function(height, width) {
			var jPopup = jQuery("#alert-messages .popup:last");
			var jBackground = jQuery(".alert-background");

			jBackground.css(
				{
					top: (Viewport.scroll().y)
				}
			);

			if (!jPopup[0].alertOptions.noCenter) {
				jPopup.css(
					{
						top: (Viewport.scroll().y + (Viewport.frame().y/2 - jPopup.height()/2)) + "px",
						left: (Viewport.scroll().x + (Viewport.frame().x/2 - jPopup.width()/2)) + "px"
					}
				);
			}
		},

	    resize: function() {
			jQuery("#alert-messages .alert-background").css(
				{
					height: Viewport.page().y + "px",
					width: Viewport.page().x + "px"
				}
			);
	    },

	    resizeIframe: function(options) {
	    	if ($.Popup.message && options) {
	    		var iframe = $.Popup.message.getElementsByTagName("iframe")[0];
				var loading = jQuery.getOne(".loading-animation", $.Popup.message);

				if (loading) {
					loading.parentNode.removeChild(loading);
				}

	    		if (iframe) {
		    		if (options.height) {
		    			iframe.height = options.height;
		    		}

		    		if (options.width) {
		    			iframe.width = options.width;
		    		}
	    		}
	    	}

	    	$.Popup.resize();
	    },

	    update: function(link, url) {
	    	var jLink = jQuery(link);

			jLink.empty();
			jLink.append("<div class=\"loading-animation\"></div>");

	    	AjaxUtil.update(url, jLink[0]);
	    }
	});
})(Liferay);
var DragLink = {
	create: function(item, dragId) {
		item.dragId = jQuery.getOne(dragId);
		item.clickLink = item.href;
		item.href = "javascript:void(0)";
		item.onclick = DragLink.onLinkClick;
	},

	onLinkClick: function() {
		if (this.dragId.wasClicked) {
			if (Liferay.Browser.is_ie) {
				setTimeout("window.location = \"" + this.clickLink + "\";", 0);
			}
			else {
				window.location = this.clickLink;
			}
		}
	}
};

var NavFlyout = {
	zIndex: 1,
	initialize: function (nav) {
		var nav = jQuery.getOne(nav);
		var navMapList = jQuery("portlet-nav-map-list", nav);

		navMapList.not(".portlet-nav-map-level_1, .portlet-nav-map-level_2")
			.css({position: "absolute", display: "none"});

		jQuery(".portlet-nav-map-list a", nav).each(function(){
			var item = jQuery(this.parentNode.parentNode);
				if (item.is(".portlet-nav-map-level_1")) {
					item.mouseover(function() {
						NavFlyout.hide(this.parentNode);
					});
				}
				else {
					item.mouseover(NavFlyout.onHoverOver);
				}
		});
	},

	initToggle: function(nav, imgSrc) {
		var nav = jQuery.getOne(nav);
		var navMapList = jQuery(".portlet-nav-map-level_1 > li", nav);
		navMapList.click(NavFlyout.onToggle);
		navMapList.css({ backgroundImage: "url(" + imgSrc + ")" });
	},

	hide: function(listItem) {
		NavFlyout.initialize(listItem.parentNode);
	},

	onHoverOver: function() {
		var listItem = this.parentNode;

		// Hide all other submenus
		if (jQuery(listItem.parentNode).is(".portlet-nav-map-level_2")) {
			NavFlyout.hide(listItem.parentNode.parentNode.parentNode);
		}
		else {
			NavFlyout.hide(listItem);
		}

		// Show current submenu
		jQuery(listItem.childNodes).filter("ul")
			.css({
				display: "block",
				top: "5px",
				left: "100px"
			});

		// Fix Z-Index
		zItem = listItem;
		while (zItem.nodeName.toLowerCase() != "div") {
			if (zItem.nodeName.toLowerCase() == "li") {
				zItem.style.zIndex = NavFlyout.zIndex;
			}
			zItem = zItem.parentNode;
		}

		NavFlyout.zIndex++;
	},

	onToggle: function() {
		var subMenu = jQuery("ul:first", this).get(0);

		if (this.isShowing) {
			subMenu.style.display = "none";
			this.style.backgroundImage = this.style.backgroundImage.replace(/02_minus/, "02_plus");
			this.isShowing = false;
		}
		else {
			subMenu.style.display = "block";
			subMenu.style.backgroundImage = "none";
			this.style.backgroundImage = this.style.backgroundImage.replace(/02_plus/, "02_minus");
			this.isShowing = true;
		}
	}
};

var PortletHeaderBar = {
	mode: {},

	fade: function(data) {
		var count = data.count;
		var id = data.id;

		var changed = false;
		var icons = jQuery("#portlet-header-bar_" + id + " .portlet-small-icon-bar");

		if (PortletHeaderBar.mode[id] == "in") {
			if (count <= 10) {
				if (count >= 0) {
					icons.css({"opacity": (count/10), "display": ""});
				}
				changed = true;
				data.count++;
			}
		}
		else if (PortletHeaderBar.mode[id] == "out") {
			if (count >= 0) {
				if (count <= 10) {
					icons.css("opacity", (count/10));
				}
				data.count--;
				changed = true;
			}
			else {
				icons.css("display", "none");
			}
		}

		return changed;
	},

	hide: function (id) {
		this.mode[id] = "out";
		Liferay.Animate("header-icon-fade_" + id,
			PortletHeaderBar.fade,
			{ count: 15, id: id }
		);
	},

	show: function (id) {
		this.mode[id] = "in";
		Liferay.Animate("header-icon-fade_" + id,
			PortletHeaderBar.fade,
			{ count: -5, id: id }
		);
	}
};

var PhotoSlider = Class.create();
PhotoSlider.prototype = {

	initialize: function (slidingWindow, windowWidth, photos, totalPages, varName) {
		this.TOTAL_FRAMES = 20;
		this.count = 0;
		this.page = 0;
		this.timer = 0;
		this.start = 0;

		this.photos = jQuery.getOne(photos);
		this.photos.style.position = "relative";
		this.photos.style.left = "0px";

		this.slidingWindow = _J$.getOne(slidingWindow);
		this.windowWidth = windowWidth;
		this.totalPages = totalPages;
		this.varName = varName;
	},

	animate: function() {
		if (this.count <= this.TOTAL_FRAMES) {
			var ratio = this.count / this.TOTAL_FRAMES;
			var ratio2 = Math.sin(ratio * (Math.PI/2));
			var delta = -(this.page * this.windowWidth) - this.start;

			this.photos.style.left = this.start + (delta * ratio2);
			this.count++;
			this.timer = setTimeout(this.varName + ".animate()", 30);
		}
		else {
			this.timer = 0;
		}
	},

	left: function() {
		this.start = parseInt(this.photos.style.left);

		if (this.page > 0) {
			this.page--;
			this.count = 0;

			if (!this.timer) {
				this.timer = setTimeout(this.varName + ".animate()", 30);
			}
		}
	},

	right: function() {
		this.start = parseInt(this.photos.style.left);

		if (this.page < (this.totalPages - 1)) {
			this.page++;
			this.count = 0;

			if (!this.timer) {
				this.timer = setTimeout(this.varName + ".animate()", 30);
			}
		}
	}
};

var Tabs = {
	show : function (namespace, names, id) {
		var el = document.getElementById(namespace + id + "TabsId");

		if (el) {
			el.className = "current";
		}

		el = document.getElementById(namespace + id + "TabsSection");

		if (el) {
			el.style.display = "block";
		}

		for (var i = 0; (names.length > 1) && (i < names.length); i++) {
			if (id != names[i]) {
				el = document.getElementById(namespace + names[i] + "TabsId");

				if (el) {
					el.className = "none";
				}

				el = document.getElementById(namespace + names[i] + "TabsSection");

				if (el) {
					el.style.display = "none";
				}
			}
		}
	}
};

var StarRating = new Class({
	initialize: function(id, options) {
		/* OPTIONS
		 * displayOnly: (boolean) non-modifiable display
		 * onComplete: (function) executes when rating is selected
		 * rating: rating to initialize to
		 */
			this.options = options || {};
			this.rating = this.options.rating || 0;
			var item = jQuery("#" + id);
			this.stars = item.find("img");
			var self = this;

			if (!this.options.displayOnly) {
				item.bind("mouseout",  {self: this}, this.onHoverOut);

				this.stars.each(function(index) {
					this.index = index + 1;
					jQuery(this).bind("click", {self: self}, self.onClick)
						   .bind("mouseover", {self: self}, self.onHoverOver);
				})
			}

			this.display(this.rating, "rating");
		}
	});

StarRating.implement({
	display: function(rating, mode) {
		var self = this;
		rating = rating == null ? this.rating : rating;

		var whole = Math.floor(rating);
		var fraction = rating - whole;

		this.stars.each(function(index) {
			image = this;
			if (index < whole) {
				if (mode == "hover") {
					image.src = image.src.replace(/\bstar_.*\./, "star_hover.");
				}
				else {
					image.src = image.src.replace(/\bstar_.*\./, "star_on.");
				}
			}
			else {
				if (fraction < 0.25) {
					image.src = image.src.replace(/\bstar_.*\./, "star_off.");
				}
				else if (fraction < 0.50) {
					image.src = image.src.replace(/\bstar_.*\./, "star_on_quarter.");
				}
				else if (fraction < 0.75) {
					image.src = image.src.replace(/\bstar_.*\./, "star_on_half.");
				}
				else if (fraction < 1.00) {
					image.src = image.src.replace(/\bstar_.*\./, "star_on_threequarters.");
				}
				fraction = 0;
			}
		});
	},

	onHoverOver: function(event) {
		event.data.self.display(this.index, "hover");
	},
	onHoverOut: function(event) {
		event.data.self.display();
	},
	onClick: function(event) {
		var target = this;
		var newRating = target.index;
		var self = event.data.self;
		self.rating = newRating;

		if (self.options.onComplete) {
			self.options.onComplete(newRating);
		}

		self.display(newRating);
	}
});

var ToolTip = {
	container: null,

	show: function(event, obj, text) {
		var instance = this;

		var container = instance.container;
		var currentItem = jQuery(obj);
		var position = currentItem.offset();

		var dimensions = instance._windowCalculation();

		if (!container) {
			container = jQuery('<div class="portal-tool-tip"></div>').appendTo('body');

			instance.container = container;
		}

		container.html(text);

		container.show();

		var boxWidth = container.width();
		var width = currentItem.width();
		var height = currentItem.height();
		var boxHeight = container.height();
		var left = position.left - (boxWidth / 2);
		var top = position.top + height + 5;

		if (left < 0) {
			left = 5;
		}
		else {
			left += 5;
		}

		if (left + boxWidth > dimensions.right) {
			left = (left - (boxWidth / 2 )) + width;
		}

		if (top + boxHeight > dimensions.bottom) {
			top = top - (height + boxHeight + 5);
		}

		container.css(
			{
				cursor: 'default',
				left: left + 'px',
				position: 'absolute',
				top: top + 'px',
				zIndex: Liferay.zIndex.TOOLTIP
			}
		);

		currentItem.one(
			'mouseout',
			function() {
				instance.hide();
			}
		);
	},

	hide: function(event) {
		var instance = this;

		instance.container.hide();
	},

	_windowCalculation: function() {
		var instance = this;

		if (instance._window.right == null) {
			var windowSize = {};
			var body = instance._body;
			if (!body) {
				body = jQuery('body');
				instance._body = body;
			}

			instance._window = {
				bottom: body.height(),
				left: 0,
				right: body.width(),
				top: 0
			};

			jQuery(window).resize(
				function() {
					instance._window.bottom = body.height();
					instance._window.right = body.width();
				}
			);
		}
		return instance._window;
	},
	_body: null,
	_window: {}
};
Liferay.Portlet = {
	fn: {},
	fnAll: [],
	fnLast: [],
	ajaxList: {},
	list: {},

	isAjax: function(id) {
		return (this.ajaxList[id] == 1);
	},

	flagAjax: function(id) {
		this.ajaxList[id] = 1;
	},

	process: function(id) {
		var status = this.list[id];
		var count = 0;

		this.list[id] = 0;

		if (status == 1) {
			this.processPortlet(id);
			this.processAll(id);
		}
		else if (status == 0) {

			// Already processed. Do nothing.

		}
		else {

			// New portlet. Process and mark.

			this.processPortlet(id);
		}

		for (var i in this.list) {
			count += this.list[i];
		}

		if (count == 0) {
			this.processLast(id);
		}
	},

	processAll: function(id) {
		for (var i = 0; i < this.fnAll.length; i++) {
			this.fnAll[i](id, jQuery("#p_p_id_" + id + "_"));
		}
	},

	processPortlet: function(id) {
		if (this.fn[id]) {
			for (var i = 0; i < this.fn[id].length; i++) {
				this.fn[id][i](id, jQuery("#p_p_id_" + id + "_"));
			}
			this.fn[id] = [];
		}
	},

	processLast: function(id) {
		for (var i = 0; i < this.fnLast.length; i++) {
			this.fnLast[i](id);
		}
		this.fnLast = [];
	},

	ready: function(arg1, arg2) {
		if (typeof arg1 == "function") {
			this.fnAll.push(arg1);
		}
		else if (typeof arg1 == "string" && typeof arg2 == "function") {
			if (!this.fn[arg1]) {
				this.fn[arg1] = [];
			}

			this.fn[arg1].push(arg2);
		}
	},

	remove: function(id) {
		this.ajaxList[id] = 0;
		this.list[id] = 1;
		this.fn[id] = [];
	},

	last: function(arg1) {
		this.fnLast.push(arg1);
	},

	/*
	 * Helper methods for portlets
	 */
	findIndex: function(portlet) {
		var index = -1;

		jQuery("> .portlet-boundary", portlet.parentNode).each(
			function(i) {
				if (this == portlet) {
					index = i;
				}
			}
		);

		return index;
	},

	move: function(data) {
		var portlet = data.portlet;
		var neighbor = data.neighbor;
		var quadrant = data.quadrant;
		var container = data.container;

		if (neighbor && quadrant) {
			if (quadrant == 1 || quadrant == 2) {
				jQuery(neighbor).before(portlet);
			}
			else {
				jQuery(neighbor).after(portlet);
			}

			if (portlet && portlet.originalColumn) {
				var oColumn = jQuery(portlet.originalColumn);
				var portlets = oColumn.find('.portlet-boundary:first');

				if (portlets.length == 0) {
					oColumn.addClass('empty');
				}

				oColumn = portlet.originalColumn = null;
			}
		}
		else if (container) {
			jQuery(container).append(portlet).removeClass('empty');
		}

		this.savePosition(portlet);
	},

	savePosition: function(portlet) {
		var currentColumnId = portlet.parentNode.id.replace(/^layout-column_/, '');
		var index = this.findIndex(portlet);
		var portletId = portlet.id.replace(/^(p_p_id_)/, '');
		portletId = portletId.substring(0, portletId.length - 1);

		AjaxUtil.request(themeDisplay.getPathMain() + "/portal/update_layout" +
			"?p_l_id=" + themeDisplay.getPlid() +
			"&p_p_id=" + portletId +
			"&p_p_col_id=" + currentColumnId +
			"&p_p_col_pos=" + index +
			"&doAsUserId=" + themeDisplay.getDoAsUserIdEncoded() +
			"&cmd=move");
	}
};

jQuery.fn.last = function(fn) {
	Liferay.Portlet.last(fn);
};
Liferay.Publisher = {
	publishers: {},

	deliver: function(publisher) {
		var instance = this;

		var scope = window;
		var data;

		if (arguments.length == 2) {
			data = [arguments[1]];
		}
		else {
			data = jQuery.map(arguments,
				function(item, i) {
					 return (i > 0) ? item : null;
				}
			);
		}

		jQuery.each(instance.publishers[publisher],
			function(i, el) {
				var classScope = el.obj || scope;
				el.func.apply(classScope, data);
			}
		);
	},

	register: function(publisher) {
		var instance = this;

		if (!instance.publishers[publisher]) {
			instance.publishers[publisher] = [];
		}
	},

	subscribe: function(publisher, func, obj) {
		var instance = this;

		if (instance.publishers[publisher] == null) {
			instance.register(publisher);
		}

		var alreadyExists = false;

		jQuery.each(instance.publishers[publisher],
			function(i, el) {
				if (el === func) {
					alreadyExists = true;
					return false;
				}
			}
		);

		if (!alreadyExists) {
			var data = {
				func: func,
				obj: obj || null
			};

			instance.publishers[publisher].push(data);
		}

	},

	unsubscribe: function(publisher, func) {
		var instance = this;

		if (!instance.publishers[publisher]) {
			return;
		}

		 jQuery.each(instance.publishers[publisher],
			function(i, el) {
				if (el.func === func) {
					instance.publishers[publisher].pop(el);
					return false;
				}
			}
		);
	}
};
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
(function(lib){
	lib.Columns = function(options) {
		lib.Columns.init(options);
	};

	lib.Columns.extendNativeFunctionObject({
		init: function(options) {
			var instance = this;

			// Set private variables
			instance._columns = options.columnSelector;
			instance._dropPosition = options.positionClass;
			instance._dropArea = options.areaClass;
			instance._grid = jQuery(options.grid);
			instance._handle = options.handleSelector;
			instance._onDrop = options.onComplete;
			instance._portlets = options.boxSelector;
			instance._cache = {};

			jQuery(instance._columns).find(instance._portlets).each(function() {
				var portlet = this;

				if (!portlet.isStatic) {
					instance.add(portlet);
				}
			});
		},

		add: function(portlet, options) {
			if (options || !themeDisplay.isFreeformLayout()) {
				var instance = this;
				var jPortlet = jQuery(portlet);
				var jHandle = jPortlet.find(instance._handle);

				jHandle.css({cursor: "move"});
				jPortlet.css({position: "relative"});

				var defaultOptions = {
					clone: true,
					dragClass: "drag-indicator",
					handle: jPortlet.find(instance._handle)[0],
					onMove: function(s) {instance._onMove(s)},
					onComplete: function(s) {instance._onComplete(s);},
					onStart: function(s) {instance._onStart(s);},
					threshold: 2,
					scroll: true
				};

				if (options) {
					defaultOptions = jQuery.extend(defaultOptions, options);
				}

				jPortlet.lDrag(defaultOptions);
			}
		},

		_clearCache: function() {
			if (this._cache.dropArea) {
				jQuery(this._cache.dropArea).remove();
			}
			if (this._cache.dropPosition) {
				jQuery(this._cache.dropPosition).remove();
			}
			this._cache = {};
		},

		_findContainer: function(coord) {
			var instance = this;
			var jColumns = instance._cache.columns;

			if (!jColumns) {
				instance._grid.addClass('dragging');

				jColumns = instance._cache.columns = jQuery(instance._columns);
				instance._cache.columnData = [];

				jColumns.each(function(i){
					var element = this.parentNode;
					instance._cache.columnData[i] = jQuery(element).coordinatesData(true);
				});
			}

			var data, quadrant, rt = null;

			jColumns.each(function(i) {
				quadrant = coord.insideObjectData(instance._cache.columnData[i]);

				if (quadrant) {
					if (data) {
						if (instance._cache.columnData[i].nwOffset.insideObjectData(data) && instance._cache.columnData[i].seOffset.insideObjectData(data)) {
							data = instance._cache.columnData[i];
							data.quadrant = quadrant;
							rt = this;
						}
					}
					else {
						data = instance._cache.columnData[i];
						data.quadrant = quadrant;
						rt = this;
					}
				}
			});

			return rt ? {area: rt, data: data} : null;
		},

		_findPortlet: function(coord, scope, current) {
			var instance = this;

			if (!instance._cache.portlets) {
				instance._cache.portlets = [];
				instance._cache.portletData = [];
				instance._cache.portletList = [];
			}

			var jPortlets = instance._cache.portlets[scope.id];

			if (!jPortlets) {
				jPortlets = jQuery("> " + instance._portlets, scope);
				instance._cache.portlets[scope.id] = jPortlets;
				instance._cache.portletData[scope.id] = [];
				instance._cache.portletList[scope.id] = new LinkedList();

				jPortlets.each(function(i){
					instance._cache.portletData[scope.id][i] = jQuery(this).coordinatesData(true);
					instance._cache.portletList[scope.id].add(this);
				});
			}

			var data, quadrant, rt = null;

			jPortlets.each(function(i) {
				data = instance._cache.portletData[scope.id][i];
				quadrant = coord.insideObjectData(data);

				if (quadrant) {
					data.quadrant = quadrant;
					rt = this;
					return false;
				}
				else if (coord.y < data.midPoint.y) {
					data.quadrant = 1;
					rt = this;
					return false;
				}
				else if (i == jPortlets.length - 1) {
					data.quadrant = 4;
					rt = this;
					return false;
				}
			});

			return rt ? {position: rt, data: data} : null;
		},

		_showArea: function(container, nwOffset) {
			instance = this;
			var dropArea = instance._cache.dropArea;

			if (!dropArea) {
				jQuery("body:first").append("<div class='" + instance._dropArea + "'></div>");
				instance._cache.dropArea = dropArea = jQuery("." + instance._dropArea + ":first");
				dropArea.css({
					position: "absolute",
					zIndex: Liferay.zIndex.DROP_AREA
				});
			}

			var element = jQuery(container.parentNode.nodeName.toLowerCase() == "td" ? container.parentNode : container.parentNode);
			dropArea.css({
				display: "",
				height: element.height(),
				left: nwOffset.x,
				top: nwOffset.y,
				width: element.width()
			});
		},

		_showPosition: function(portlet, nwOffset, quadrant) {
			instance = this;
			var dropPos = instance._cache.dropPosition;

			if (!dropPos) {
				jQuery("body:first").append("<div class='" + instance._dropPosition + "'></div>");
				dropPos = jQuery("." + instance._dropPosition + ":first");

				dropPos[0].style.position = 'absolute';
				dropPos[0].style.zIndex = Liferay.zIndex.DROP_POSITION;

				instance._cache.dropPosition = dropPos;
			}
			var jDropPos = jQuery(instance._cache.dropPosition);
			var jPortlet = jQuery(portlet);
			var portletWidth = jPortlet.width();
			var portletHeight = jPortlet.height();

			dropPos.css({
				display: "",
				height: portletHeight / 2,
				left: nwOffset.x + "px",
				width: portletWidth + "px"
			});

			if (quadrant == 1 || quadrant == 2) {
				dropPos.css({ top: nwOffset.y + "px" });
				if (dropPos[0].className != "drop-position-top") {
					dropPos[0].className = "drop-position-top";
				}
			}
			else {
				dropPos.css({ top: (nwOffset.y + portletHeight / 2) + "px" });
				if (dropPos[0].className != "drop-position-bottom") {
					dropPos[0].className = "drop-position-bottom";
				}
			}
		},

		_hideArea: function() {
			if (this._cache.dropArea) {
				this._cache.dropArea.css({display: "none"});
			}
		},

		_hidePosition: function() {
			if (this._cache.dropPosition) {
				this._cache.dropPosition.css({display: "none"});
			}
		},

		_hasMoved: function(current, position, quadrant) {
			var instance = this;
			var rt = true;

			if (current == position) {
				rt = false;
			}
			else {
				var portlets = instance._cache.portletList[current.parentNode.id];

				if (portlets) {
					portlets.each(function(item) {
						if (item == position) {
							if ((quadrant == 1 || quadrant == 2) && item.listInfo.prev == current) {
								rt = false;
							}
							else if ((quadrant == 3 || quadrant == 4) && item.listInfo.next == current) {
								rt = false;
							}
						}
					});
				}
			}

			return rt;
		},

		_onMove: function(settings) {
			settings.container.style.top = 0;
			settings.container.style.left = 0;
			var instance = this;
			var foundContainer = instance._findContainer(mousePos);
			var foundPortlet = null;

			if (foundContainer) {
				foundPortlet = instance._findPortlet(mousePos, foundContainer.area, settings.container);
				instance._showArea(foundContainer.area, foundContainer.data.nwOffset);

				if (foundPortlet && foundPortlet.position.isStatic) {
					foundPortlet = null;
				}
			}
			else {
				instance._hideArea();
			}

			if (foundPortlet && settings.container != foundPortlet.position) {
				var cPortlet = foundPortlet.position;
				var data = foundPortlet.data;
				instance._showPosition(cPortlet, data.nwOffset, data.quadrant);
			}
			else {
				instance._hidePosition();
			}
		},

		_onComplete: function(settings) {
			jQuery(settings.container).css({top: 0, left: 0});
			var instance = this;
			var foundContainer = instance._findContainer(mousePos);
			var dropable = true;

			instance._hidePosition();
			instance._hideArea();

			if (instance._onDrop && foundContainer) {
				var foundPortlet = instance._findPortlet(mousePos, foundContainer.area, settings.container);

				if (foundPortlet) {
					if (instance._hasMoved(settings.container, foundPortlet.position, foundPortlet.data.quadrant) && !foundPortlet.position.isStatic) {

						// Move if not in the same position

						instance._onDrop({
							portlet: settings.container,
							neighbor: foundPortlet.position,
							quadrant: foundPortlet.data.quadrant
						});
					}
				}
				else {

					// Add portlet to empty column

					instance._onDrop({
						portlet: settings.container,
						container: foundContainer.area
					});
				}
			}
			else {
				dropable = false;
			}

			instance._grid.removeClass("dragging");
			instance._clearCache();

			return dropable;
		},

		_onStart: function(settings) {
			var instance = this;

			settings.container.originalColumn = settings.container.parentNode;
		}
	});
})(Liferay);
Liferay.Dock = {
	init: function() {
		var instance = this;

		var dock = jQuery('.lfr-dock');

		if (!dock.is('.interactive-mode')) {
			return;
		}

		dock.addClass('lfr-component');

		var dockList = dock.find('.lfr-dock-list');

		if (dockList.length > 0){
			var myPlaces = jQuery('.my-places', dock);

			instance._dock = dock;
			instance._dockList = dockList;
			instance._myPlaces = myPlaces;

			instance._hideCommunities(myPlaces);

			dockList.hide();
			dockList.wrap('<div class="lfr-dock-list-container"></div>');

			var dockData = {
				dock: dock,
				dockList: dockList
			};

			dock.css(
				{
					cursor: 'pointer',
					position: 'absolute',
					zIndex: Liferay.zIndex.DOCK
				}
			);

			var dockOver = function(event) {
				event.data = dockData;

				jQuery(document).one(
					'click',
					function(internalEvent) {
						var currentEl = jQuery(internalEvent.target);
						var dockParent = currentEl.parents('.lfr-dock');

						if ((dockParent.length == 0) && !currentEl.is('.lfr-dock')) {
							instance._toggle(event, 'hide');
						}
					}
				);

				instance._toggle(event, 'show');
			};

			var dockOut = function(event) {
				event.data = dockData;

				instance._toggle(event, 'hide');
			};

			var myPlacesToggle = function(event) {
				event.data = myPlaces;

				instance._togglePlaces(event);
			};

			dock.hoverIntent(
				{
					interval: 0,
					out: dockOut,
					over: dockOver,
					timeout: 500
				}
			);

			myPlaces.hoverIntent(
				{
					interval: 0,
					out: myPlacesToggle,
					over: myPlacesToggle,
					timeout: 250
				}
			);

			myPlaces.find('.my-places-toggle, a[@href=javascript: ;]').click(
				function() {
					return false;
				}
			);

			if (Liferay.Browser.is_ie && Liferay.Browser.version() <= 6) {
				myPlaces.find('>ul').css('zoom', 1);
			}

			var dockParent = dock.parent();

			dockParent.css(
				{
					position: 'relative',
					zIndex: Liferay.zIndex.DOCK_PARENT
				}
			);

			instance._handleDebug();
		}
	},

	_handleDebug: function() {
		var instance = this;

		var dock = instance._dock;
		var dockList = instance._dockList;
		var myPlacesList = instance._myPlaces.find('> ul');

		if (dock.is('.debug')) {
			dock.show();
			dockList.show();
			dockList.addClass('expanded');
			myPlacesList.addClass('show-my-places');
		}
	},

	_hideCommunities: function(jQueryObj) {
		var myPlaces = jQueryObj;

		var communities = myPlaces.find('> ul > li');
		var communityList = communities.find('ul');
		var currentCommunity = communityList.find('li.current');
		var heading = communities.find('h3');

		heading.wrap('<div class="my-places-toggle"></div>');

		heading = heading.parent();

		communityList.hide();
		currentCommunity.parent().show();

		var currentCommunityHeading = currentCommunity.parent().prev();

		currentCommunityHeading.addClass('hide');

		heading.click(
			function() {
				var heading = jQuery(this);

				heading.next("ul").BlindToggleVertically("fast");
				heading.toggleClass('hide');
			}
		);
	},

	_toggle: function(event, state) {
		var params = event.data;

		var dock = params.dock;
		var dockList = params.dockList;

		if (state == 'hide') {
			dockList.hide();
			dock.removeClass('expanded');
		}
		else if (state == 'show') {
			dockList.show();
			dock.addClass('expanded');
		}
		else {
			dockList.toggle();
			dock.toggleClass('expanded');
		}
	},

	_togglePlaces: function(event) {
		var myPlaces = event.data;

		var myPlacesList = myPlaces.find('> ul');

		myPlacesList.toggleClass('show-my-places');

		if (Liferay.Browser.is_ie && Liferay.Browser.version() <= 6) {
			myPlacesList.find('li ul li').css('position', 'relative');
		}
	}
};
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
(function(lib){

	lib.Freeform = function(portlet) {
		lib.Freeform.init(portlet);
	};

	lib.Freeform.extendNativeFunctionObject({
		_current: null,

		init: function(options) {
			var instance = this;

			// Set private variables
			instance._columns = options.columnSelector;
			instance._portlets = options.boxSelector;

			jQuery(instance._columns).find(instance._portlets).each(function() {
				instance.add(this);
			});
		},

		add: function(portlet) {
			var instance = this;
			portlet = jQuery.getOne(portlet);

			var handle = jQuery(".portlet-header-bar, .portlet-title-default, .portlet-topper", portlet).get(0);

			handle.style.cursor = "move";
			portlet.style.position = "absolute";

			jQuery(portlet).lDrag({
				handle: handle,
				portlet: portlet,
				onStart: function(settings) {
					settings.wasClicked = true;
					settings.container.style.zIndex = 99;
				},
				onMove: function(settings) {
					settings.wasClicked = false;
				},
				onComplete: function(settings) {
					var portlet = settings.portlet;

					if (!settings.wasClicked) {
						var left = parseInt(portlet.style.left);
						var top = parseInt(portlet.style.top);

						left = Math.round(left/10) * 10;
						top = Math.round(top/10) * 10;

						portlet.style.left = left + "px";
						portlet.style.top = top + "px";

						instance.moveToTop(portlet);
						instance.savePosition(portlet);
					}
					portlet.style.zIndex = "";
				}
			});

			jQuery(portlet).click(function() {
				if (instance._current != this) {
					instance.moveToTop(this);
					instance.savePosition(this, true);
					instance._current = this;
				}
			});

			var resizeBox = jQuery(".portlet-content-container, .portlet-borderless-container", portlet);
			var resizeHandle = jQuery(".portlet-resize-handle", portlet);

			if (!resizeHandle.length) {
				resizeBox.append("<div style='position:relative'><div class='portlet-resize-handle'></div></div>");
				resizeHandle = jQuery(".portlet-resize-handle", portlet);
			}

			if (resizeBox.length && resizeHandle.length) {
				jQuery(portlet).lResize({
					handle: resizeHandle[0],
					direction: "horizontal",
					mode: "add",
					portlet: portlet,
					onStart: function(settings) {
						instance.moveToTop(settings.container.resizeSettings.portlet);
					},
					onComplete: function(settings) {
						var portlet = settings.container.resizeSettings.portlet;
						var resizeBox = jQuery(portlet).getOne(".portlet-content-container, .portlet-borderless-container");
						var height = parseInt(resizeBox.style.height);
						var width = parseInt(portlet.style.width);

						height = Math.round(height/10) * 10;
						width = Math.round(width/10) * 10;

						resizeBox.style.height = height + "px";
						portlet.style.width = width + "px";
						instance.savePosition(portlet);
					}
				});

				resizeBox.lResize({
					handle: resizeHandle[0],
					direction: "vertical",
					mode: "add"
				});
			}

			if ((parseInt(portlet.style.top) + parseInt(portlet.style.left)) == 0) {
				portlet.style.top = (20 * portlet.columnPos) + "px";
				portlet.style.left = (20 * portlet.columnPos) + "px";
			}
		},

		findPosition: function(portlet) {
			var position = -1;

			jQuery(".portlet-boundary", portlet.parentNode).each(function(i) {
				if (this == portlet) {
					position = i;
				}
			});

			return position;
		},

		moveToTop: function(portlet) {
			var container = portlet.parentNode;
			portlet.oldPosition = this.findPosition(portlet);

			container.removeChild(portlet);
			container.appendChild(portlet);
		},

		savePosition : function(portlet, wasClicked) {
			var instance = this;
			var resizeBox = jQuery(portlet).find(".portlet-content-container, .portlet-borderless-container")[0];
			var newPosition = Liferay.Portlet.findIndex(portlet);
			var cmd;

			if (newPosition != portlet.oldPosition) {
				Liferay.Portlet.savePosition(portlet);
			}

			if (resizeBox && !wasClicked) {
				AjaxUtil.request(themeDisplay.getPathMain() + "/portal/update_layout" +
					"?p_l_id=" + themeDisplay.getPlid() +
					"&height=" + resizeBox.style.height +
					"&width=" + portlet.style.width +
					"&top=" + portlet.style.top +
					"&left=" + portlet.style.left +
					"&p_p_id=" + portlet.portletId +
					"&doAsUserId=" + themeDisplay.getDoAsUserIdEncoded() +
					"&cmd=drag");
			}
		}
	});
})(Liferay);
var LayoutConfiguration = {
	categories : [],
	initialized : false,
	loadingImage : null,
	menu : null,
	menuDiv : null,
	menuIframe : null,
	portlets : [],
	showTimer : 0,
	offsetMenu: true,

	init : function () {
		var instance = this;

		var menu = jQuery('#portal_add_content');

		instance.menu = menu;

		instance._isFreeform = themeDisplay.isFreeformLayout();

		if (menu.length) {
			var list = menu.childNodes;

			instance.menuDiv = menu.find('.portal-add-content');
			instance.menuIframe = menu.find('iframe');

			instance.portlets = menu.find('.lfr-portlet-item');
			instance.categories = menu.find('.lfr-content-category');
			instance.categoryContainers = menu.find('.lfr-add-content');

			instance.initialized = true;

			jQuery('#layout_configuration_content').trigger('focus').addClass('focus');
			jQuery('#layout_configuration_content').keyup(
				function(event) {
					instance.startShowTimer(event, this);
				}
			);
		}

		if (instance._isFreeform) {
			instance._grid = jQuery('body .freeform #column-1:first');
			instance._offsetL = instance._grid[0].offsetLeft;
			instance._offsetT = instance._grid[0].offsetTop;
		}
	},

	toggle : function (plid, ppid, doAsUserId) {
		var instance = this;

		if (!instance.menu) {
			var url = themeDisplay.getPathMain() + "/portal/render_portlet?p_l_id=" + plid + "&p_p_id=" + ppid + "&doAsUserId=" + doAsUserId + "&p_p_state=exclusive";

			var popupWidth = 250;

			if (instance.offsetMenu) {
				var body = jQuery('body');
				var originalPadding = body.css('padding-left');

				body.css('padding-left', popupWidth + 10);
			}

			var popup = Liferay.Popup({
				width: popupWidth,
				noCenter: true,
				title: Liferay.Language.get("add-application"),
				onClose: function() {
					instance.menu = null;

					if (instance.offsetMenu) {
						body.css('padding-left', originalPadding);
					}
				}
			});

			AjaxUtil.update(url, popup,
				{
					onComplete: function() {
						instance._loadContent();
					}
				}
			);
		}
	},

	searchField: function(event, obj) {
		var instance = this;

		var word = jQuery.trim(obj.value).toLowerCase();
		var portlets = instance.portlets;
		var categories = instance.categories;
		var categoryContainers = instance.categoryContainers;

		if (word != '*' && word.length) {
			word = word.match(/[a-zA-Z0-9]*/g).join("");
			portlets.hide();
			categories.hide();
			categoryContainers.hide();
			portlets.each(
				function(i) {
					var name = this.id.toLowerCase();
					if (name.indexOf(word) > -1) {
						var portlet = jQuery(this);
						portlet.show();
						portlet.parents('.lfr-content-category').addClass('visible').removeClass('hidden').show();
						portlet.parents('.lfr-add-content').addClass('expanded').removeClass('collapsed').show();
					}
				}
			);
		}
		else {
			if (!word.length) {
				categories.addClass('hidden').removeClass('visible').css('display', '');
				categoryContainers.addClass('collapsed').removeClass('expanded').css('display', '');
				portlets.css('display', '');
			}
			else if (word == '*') {
				categories.addClass('visible').removeClass('hidden');
				categoryContainers.addClass('expanded').removeClass('collapsed');
				portlets.show();
			}
		}
	},

	startShowTimer : function (event, obj) {
		var instance = this;

		if (instance.showTimer) {
			clearTimeout(instance.showTimer);
			instance.showTimer = 0;
		}

		instance.showTimer = setTimeout(
			function() {
				instance.searchField(event, obj);
			},
			250
		);
	},

	_loadContent: function() {
		var instance = this;

		instance.init();

		Liferay.Util.addInputType();
		Liferay.Util.addInputFocus();

		Liferay.Publisher.subscribe('closePortlet', instance._onPortletClose, instance);

		var clicked = false;

		var portlets = jQuery('.lfr-portlet-item');

		var options = {
			threshold: 10,
			onStart: function(s) {
				var event = s.browserEvent;
				var originalTarget = jQuery(event.originalTarget || event.srcElement);

				if (!originalTarget.is('a')) {
					Liferay.Columns._onStart(s);
				}
				else {
					clicked = true;

					var portlet = originalTarget.parents('.lfr-portlet-item:first');

					if (!portlet.is('.lfr-portlet-used')) {
						var plid = portlet.attr('plid');
						var portletId = portlet.attr('portletId');
						var isInstanceable = (portlet.attr('instanceable') == 'true');

						addPortlet(plid, portletId, themeDisplay.getDoAsUserIdEncoded());

						if (!isInstanceable) {
							portlet.addClass('lfr-portlet-used');
							portlet.unbind('mousedown');
						}
					}
				}

			},
			onMove: function(s) {
				if (!instance._isFreeform) {
					Liferay.Columns._onMove(s);
				}
			},
			onComplete: function(s) {
				if (!clicked) {
					var container = s.container;

					var plid = container.getAttribute('plid');
					var portletId = container.getAttribute('portletId');

					if (plid && portletId) {
						var portlet = jQuery(s.container);
						var isInstanceable = (container.getAttribute('instanceable') == 'true');
						var doAsUserId = themeDisplay.getDoAsUserIdEncoded();
						var portletBound = addPortlet(plid, portletId, doAsUserId, true);

						if (!isInstanceable) {
							if (portletBound) {
								portlet.addClass('lfr-portlet-used');
								portlet.unbind('mousedown');
							}
						}
						else {
							Liferay.Columns.add(portlet, options);
						}

						portlet.css(
							{
								top: 0,
								left: 0
							}
						);

						s.container = portletBound;

						var completed = Liferay.Columns._onComplete(s);

						if (!instance._isFreeform) {
							if (!completed) {
								if (isInstanceable) {
									portletId = portletBound.id;
									portletId = portletId.replace(/^p_p_id_(.*)_$/, '$1');
								}

								closePortlet(plid, portletId, doAsUserId, true);
							}
						}

						if (completed || instance._isFreeform) {
							portlet.Highlight(750, '#ffe98f');
						}

						if (instance._isFreeform) {
							var jPortlet = jQuery(portletBound);

							jPortlet.css(
								{
									left: (mousePos.x - instance._offsetL) + 'px',
									top: (mousePos.y - instance._offsetT) + 'px'
								}
							);
						}
					}
				}

				clicked = false;
			}
		};

		instance._layoutOptions = options;

		portlets.each(
			function() {
				if (this.className.indexOf('lfr-portlet-used') == -1) {
					Liferay.Columns.add(this, options);
				}
			}
		);

		if (Liferay.Browser.is_ie) {
			portlets.hover(
				function() {
					this.className += ' over';
				},
				function() {
					this.className = this.className.replace('over', '');
				}
			);
		}

		jQuery('.lfr-add-content > h2').click(
			function() {
				var heading = jQuery(this).parent();
				var category = heading.find('> .lfr-content-category');

				category.toggleClass('hidden').toggleClass('visible');
				heading.toggleClass('collapsed').toggleClass('expanded');
			}
		);
	},

	_onPortletClose: function(portletData) {
		var instance = this;

		var popup = jQuery('#portal_add_content');
		var item = popup.find('.lfr-portlet-item[@plid=' + portletData.plid + '][@portletId=' + portletData.portletId + '][@instanceable=false]');

		if (item.is('.lfr-portlet-used')) {
			item.removeClass('lfr-portlet-used')
			Liferay.Columns.add(item[0], instance._layoutOptions);
		}
	}
};
Liferay.LayoutExporter = {
	all: function(options) {
		options = options || {};

		var pane = options.pane;
		var obj = options.obj;
		var publish = options.publish;

		if (obj.checked) {
			jQuery(pane).hide();

			if (!publish) {
				jQuery('#publishBtn').show();
				jQuery('#selectBtn').hide();
			}
			else {
				jQuery('#changeBtn').hide();
			}
		}
	},

	details: function(options) {
		options = options || {};

		var toggle = options.toggle;
		var detail = options.detail;

		var img = jQuery(toggle)[0];

		if (jQuery(detail).css('display') == 'none') {
			jQuery(detail).slideDown('normal');
			img.src = Liferay.LayoutExporter.icons.minus;
		}
		else {
			jQuery(detail).slideUp('normal');
			img.src = Liferay.LayoutExporter.icons.plus;
		}
	},

	icons: {
		minus: themeDisplay.getPathThemeImages() + '/arrows/01_minus.png',
		plus: themeDisplay.getPathThemeImages() + '/arrows/01_plus.png'
	},

	publishToLive: function(options) {
		options = options || {};

		var messageId = options.messageId;
		var url = options.url;
		var title = options.title;

		if (!title) {
			title = Liferay.Language.get(messageId);
		}

		var exportLayoutsPopup = Liferay.Popup(
			{
				'title': title,
				modal: true,
				width: 600,
				height: 550,
				overflow: "auto",
				'messageId': messageId
			}
		);

		AjaxUtil.update(url, exportLayoutsPopup);
	},

	selected: function(options) {
		options = options || {};

		var pane = options.pane;
		var obj = options.obj;
		var publish = options.publish;

		if (obj.checked) {
			jQuery(pane).show();

			if (!publish) {
				jQuery('#publishBtn').hide();
				jQuery('#selectBtn').show();
			}
			else {
				jQuery('#changeBtn').show();
			}
		}
	}
};
Liferay.Menu = new Class({
	initialize: function(params) {
		var instance = this;

		instance._button = jQuery(params.button, params.context || document);
		instance._menu = instance._button.find('ul:first');
		instance._trigger = instance._button.find(params.trigger);

		if (instance._menu.length) {
			instance._run();
		}
	},

	_run: function() {
		var instance = this;

		var lastLi = instance._trigger.find('ul:first li:last-child');

		lastLi.addClass('last');

		var off = function(event) {
			instance._button.removeClass('visible');
		}

		var on = function(event) {
			var trigger = jQuery(this);

			var parent = trigger.parent();

			if (parent.is('.visible')) {
				parent.removeClass('visible');
			}
			else {
				instance._button.removeClass('visible');

				parent.addClass('visible');
			}

			jQuery(document).unbind().one(
				'click',
				off
			);

			var originalTarget = jQuery(event.originalTarget || event.srcElement);

			if (!originalTarget.is('a') && !originalTarget.is('img')) {
				return false;
			}
		};

		instance._trigger.unbind().click(on);
	}
});
var Messaging = {
	checkRoster : false,
	currentChatBox : null,
	initialized : false,
	inputCount : 1,
	mainDiv : null,
	msgQueue : [],
	userId : null,
	windowCount : 0,
	zIndex : 1,

	chat : function(msgObj) {
		if (!msgObj && Messaging.msgQueue.length == 0) return;

		var msg = msgObj || Messaging.msgQueue.shift();
		var toDivId = msg.toId.replace(/\./g, "_");
		var chatBox = jQuery("#msg-chat-box_" + toDivId)[0];

		if (!chatBox) {
			var contents =
				"<div class='chat-box' id='msg-chat-box_" + toDivId + "'>" +
					"<input class='to-input-id' type=hidden value='" + msg.toId + "' />" +
					"<div class='chat-area textarea' style='overflow: auto; height: 100px'>" +
						(msg.messages || "") +
					"</div>" +
					"<input class='type-area' style='width: 90%; margin-top: 5px' tabIndex=1 type='text' onKeyPress='Messaging.sendChat(this, event)' />" +
				"</div>";

			chatBox = Liferay.Popup({
				title: msg.toName,
				message: contents,
				noCenter: true,
				width: 300,
				onClose: function() { Messaging.saveCookie(); }
			});

			if (msg.status && msg.status == "unavailable") {
				jQuery(chatBox).append(
					"<img src='" + themeDisplay.getPathThemeImages() + "/chat/add_user.png' " +
						"style='cursor: pointer; margin-top: 2px' " +
						"onclick=\"MessagingRoster.addEntry('" + msg.toId + "'); jQuery(this).remove()\"" +
					"/>"
				);
			}

			Messaging.populateChatBox(chatBox, msg);

			if (msg.top != null && msg.left != null) {
				jQuery(chatBox).parents(".popup:first").css({
					top: msg.top + "px",
					left: msg.left + "px"
				});
			}
			else {
				var count = Liferay.Popup.count();

				jQuery(chatBox).parents(".popup:first").css({
					top: (count * 10) + "px",
					left: (count * 10) + "px"
				});
			}
		}
		else {
			this.populateChatBox(chatBox, msg);
		}
	},

	populateChatBox : function(chatBox, msg) {
		var typeArea = jQuery.getOne(".type-area", chatBox);
		var chatArea = jQuery.getOne(".chat-area", chatBox);

		if (msg.body != null) {
			var name = msg.toName.split(/[ ,.-]/);
			var initials = "";
			for (var i = 0; i < name.length; i++) {
				initials += name[i].charAt(0);
			}
			chatArea.innerHTML += "<span style='color: #FF0000'>" + initials + ": </span>" + msg.body + "<br/>";
			this.saveCookie();
		}

		chatArea.scrollTop = chatArea.scrollHeight;
		typeArea.focus();

		if (Liferay.Browser.is_ie) {
			// need double focus for IE
			typeArea.focus();
		}

		Messaging.chat();
	},

	getChats : function() {
		var url = themeDisplay.getPathMain() + "/messaging/action?cmd=getChats";
		AjaxUtil.request(url, {
			onComplete: function(xmlHttpReq) {
				var msg = eval("(" + xmlHttpReq.responseText + ")");
				Messaging.getChatsReturn(msg);
			}
		});
	},

	getChatsReturn : function(msg) {
		var status = msg.status;

		if (status == "success") {
			var chatMsg = msg.chat;
			if (chatMsg && chatMsg.length > 0) {
				for (var i = 0; i < chatMsg.length; i++) {
					// swap "from" and "to"
					var tmpName = chatMsg[i].fromName;
					var tmpId = chatMsg[i].fromId;
					chatMsg[i].fromName = chatMsg[i].toName;
					chatMsg[i].fromId = chatMsg[i].toId;
					chatMsg[i].toName = tmpName;
					chatMsg[i].toId = tmpId;
					Messaging.msgQueue.push(chatMsg[i]);
				}
				Messaging.chat();
				window.focus();
			}
		}
	},

	error : function() {
		alert("User does not exist");
	},

	init : function(userId) {
		var body = document.getElementsByTagName("body")[0];
		this.userId = userId;

		var msgJSON = jQuery.cookie(this.userId + "_chats");

		if (msgJSON) {
			var chatArray = eval("(" + msgJSON + ")");

			for (var i = 0; i < chatArray.length; i++) {
				Messaging.msgQueue.push(chatArray[i]);
			}

			Messaging.chat();
		}

		this.initialized = true;
		Messaging.getChats();
	},

	maximizeChat : function(id) {
		var chatBox = jQuery.getOne(id);
		var widthDiv = jQuery.getOne(".chat-box-width");
		var chatArea = jQuery.getOne(".chat-area");

		chatBox.style.left = Viewport.scroll().x + "px";
		chatBox.style.top = Viewport.scroll().y + "px";
		widthDiv.style.width = (Viewport.frame().x - 30) + "px";
		chatArea.style.height = (Viewport.frame().y - 100) + "px";
	},

	minimizeChat : function(id) {
		var chatBox = jQuery.getOne(id);
		var widthDiv = jQuery.getOne(".chat-box-width");
		var chatArea = jQuery.getOne(".chat-area");

		widthDiv.style.width = 250 + "px";
		chatArea.style.height = 100 + "px";
	},

	removeChat : function(id) {
		var chatBox = jQuery.getOne(id);

		Element.remove(chatBox);
		this.saveCookie();
	},

	saveCookie : function() {
		var chatList = jQuery(".chat-box");
		var jsonString = "[";

		chatList.each(function(i){
			var item = this;
			var popup = jQuery(item).parents(".popup:first");

			jsonString += "{"
				+ "toName:\"" + popup.find(".popup-title")[0].innerHTML + "\","
				+ "toId:\"" +jQuery(".to-input-id", item)[0].value + "\","
				+ "top:" + parseInt(popup.css("top")) + ","
				+ "left:" + parseInt(popup.css("left")) + ","
				+ "messages:\"" + Liferay.Util.toJSONString(jQuery(".chat-area", item)[0].innerHTML) + "\"}";

			if (i < chatList.length - 1) {
				jsonString += ",";
			}
		});
		jsonString += "]";

		jQuery.cookie(this.userId + "_chats", jsonString);
	},

	sendChat : function(obj, e) {
		var keycode;
		var chatBox = obj.parentNode;
		var toInput;
		var toAddr;
		var typeArea;
		var chatArea;
		var query = "cmd=sendChat";

		if (window.event) keycode = window.event.keyCode;
		else if (e) keycode = e.which;
		else return;

		if (keycode == 13) {
			var inputList = chatBox.getElementsByTagName("input");

			for (var i = 0; i < inputList.length ; i++) {
				if (inputList[i].className) {
					if (inputList[i].className.match("msg-to-input-id")) toInput = inputList[i];
					if (inputList[i].className.match("msg-to-input-addr")) toAddr = inputList[i];
					if (inputList[i].className.match("msg-type-area")) typeArea = inputList[i];
				}
			}

			if (typeArea.value == "") return;

			var divList = chatBox.getElementsByTagName("div");
			for (var i = 0; i < divList.length ; i++) {
				if (divList[i].className && divList[i].className.match("msg-chat-area")) chatArea = divList[i];
			}

			query += "&text=" + encodeURIComponent(typeArea.value);

			if (toAddr != null) {
				query += "&tempId=" + toInput.value + "&toAddr=" + toAddr.value;
			}
			else {
				query += "&toId=" + toInput.value;
			}

			loadPage(themeDisplay.getPathMain() + "/messaging/action", query, Messaging.sendChatReturn);

			chatArea.innerHTML += "<span style='color: #0000FF'>Me: </span>" + typeArea.value + "<br/>";
			chatArea.scrollTop = chatArea.scrollHeight;
			typeArea.value = "";

			Messaging.saveCookie();
		}
	},

	sendChatReturn : function(xmlHttpReq) {
		var msg = eval("(" + xmlHttpReq.responseText + ")");

		if (msg.status == "success") {
			Messaging.populateChatBox(msg);
		}
		else {
			Messaging.error();
		}
	}
};

var MessagingRoster = {
	highlightColor : "",
	lastSelected : null,

	addEntry : function(userId) {
		var url;

		if (userId) {
			url = themeDisplay.getPathMain() + "/chat/roster?cmd=addEntry&userId=" + userId;
		}
		else {
			var email = jQuery.getOne("#portlet-chat-roster-email").value;
			url = themeDisplay.getPathMain() + "/chat/roster?cmd=addEntry&email=" + email
		}

		AjaxUtil.request(url, {onComplete: MessagingRoster.addEntryReturn});
	},

	addEntryReturn : function(xmlHttpReq) {
		try {
			var msg = eval("(" + xmlHttpReq.responseText + ")");

			if (msg.status == "failure") {
				alert("No such user exists");
			}
			else {
				var rosterDiv = jQuery.getOne("#portlet-chat-roster-list");

				if (rosterDiv) {
					var entries = jQuery(".portlet-chat-roster-entry", rosterDiv);
					var userId = msg.user;

					var userExists = entries.filter(function(i){
						return(this.userId == userId);
					});

					if (userExists.length != 0) {
						var entryRow = MessagingRoster.createEntryRow(msg.user, msg.name);

						rosterDiv.appendChild(entryRow);
					}

					MessagingRoster.toggleEmail();
				}
			}
		}
		catch (err) {
		}
	},

	createEntryRow : function (userId, userName, online) {
			var tempDiv = document.createElement("div");
			var tempImg = document.createElement("img");
			var tempLink = document.createElement("a");
			tempImg.align = "absmiddle";
			tempImg.style.marginRight = "5px";

			if (online) {
				tempImg.src = themeDisplay.getPathThemeImages() + "/chat/user_online.png";
			}
			else {
				tempImg.src = themeDisplay.getPathThemeImages() + "/chat/user_offline.png";
			}

			tempLink.innerHTML = userName;
			tempLink.href = "javascript: void(0)";
			tempLink.onclick = MessagingRoster.onEntryLinkClick;

			tempDiv.appendChild(tempImg);
			tempDiv.appendChild(tempLink);
			tempDiv.onclick = MessagingRoster.onEntryClick;
			tempDiv.userId = userId;
			tempDiv.userName = userName;
			tempDiv.style.cursor = "pointer";
			tempDiv.className = "portlet-chat-roster-entry";

			return tempDiv;
	},

	deleteEntries : function () {
		if (MessagingRoster.lastSelected) {
			var userId = MessagingRoster.lastSelected.userId;
			var lastSelected = MessagingRoster.lastSelected;

			lastSelected.parentNode.removeChild(lastSelected);
			MessagingRoster.lastSelected = null;

			loadPage(themeDisplay.getPathMain() + "/chat/roster", "cmd=deleteEntries&entries=" + userId, MessagingRoster.deleteEntriesReturn);
		}
	},

	deleteEntriesReturn : function (xmlHttpReq) {
		try {
			var msg = eval("(" + xmlHttpReq.responseText + ")");
		}
		catch (err) {
		}
	},

	getEntries : function() {
		var url = themeDisplay.getPathMain() + "/chat/roster?cmd=getEntries";
		AjaxUtil.request(url, {
			onComplete: function(xmlHttpReq) {
				var msg = eval("(" + xmlHttpReq.responseText + ")");
				MessagingRoster.getEntriesReturn(msg);
			}
		});
	},

	getEntriesReturn : function(msg) {
		MessagingRoster.updateEntries(msg.roster);
	},

	updateEntries : function(roster) {
		var rosterDiv = jQuery.getOne("#portlet-chat-roster-list");

		if (rosterDiv != null) {
			rosterDiv.innerHTML = "";
		}
		else {
			Messaging.checkRoster = false;
			return;
		}

		for (var i = 0; i < roster.length; i++) {
			var entry = roster[i];
			var tempDiv =
				MessagingRoster.createEntryRow(
					entry.user,
					entry.name,
					entry.status == "available"
				);
			rosterDiv.appendChild(tempDiv);
		}
	},

	onEmailKeypress : function (obj, event) {
		var keyCode;

		if (window.event) keyCode = window.event.keyCode;
		else if (event) keyCode = event.which;
		else return;

		if (keyCode == 13) {
			MessagingRoster.addEntry();
		}
	},

	onEntryClick : function () {
		if (MessagingRoster.lastSelected != null) {
			MessagingRoster.lastSelected.style.backgroundColor = "transparent";
		}

		this.style.backgroundColor = MessagingRoster.highlightColor;

		MessagingRoster.lastSelected = this;
	},

	onEntryLinkClick : function () {
		var parent = this.parentNode;
		Messaging.chat({toId: parent.userId, toName: parent.userName});
	},

	toggleEmail : function() {
		var emailDiv = jQuery.getOne("#portlet-chat-roster-email-div");

		if (emailDiv.style.display == "none") {
			emailDiv.style.display = "block";

			emailInput = jQuery.getOne("#portlet-chat-roster-email");
			emailInput.value = "";
			emailInput.focus();
		}
		else {
			emailDiv.style.display = "none";
		}
	}
};

Liferay.Notice = new Class({
	/* Options:
		closeText: (String) the text to use for the "close" button. Set to false to not have a close button
		content: (String) the HTML or text to insert into.
		toggleText: (Object) the text to use for the "hide" and "show" button. Set to false to not have a hide button
		noticeClass: (String) class to add to the notice toolbar.
		onClose: (fn) a callback to execute when the toolbar is closed
		type: (String) either 'notice' or 'warning', depending on the type of the toolbar. Defaults to notice.
	*/
	initialize: function(params) {
		var instance = this;
		params = params || {};
		instance._noticeType = params.type || 'notice';
		instance._noticeClass = 'popup-alert-notice';
		instance._useCloseButton = true;
		instance._onClose = params.onClose;
		instance._closeText = params.closeText;

		instance._useToggleButton = false;
		instance._hideText = '';
		instance._showText = '';

		if (params.toggleText !== false) {
			instance.toggleText = jQuery.extend(
				{
					hide: null,
					show: null
				},
			params.toggleText);

			instance._useToggleButton = true;
		}

		if (instance._noticeType == 'warning') {
			instance._noticeClass = 'popup-alert-warning';
		}

		if (params.noticeClass) {
			instance._noticeClass += ' ' + params.noticeClass;
		}

		instance._content = params.content || '';

		instance._createHTML();

		return instance._notice;
	},

	setClosing: function() {
		var instance = this;

		var staticAlerts = jQuery('.popup-alert-notice, .popup-alert-warning').not('[@dynamic=true]');

		instance._useCloseButton = true;
		instance._addCloseButton(staticAlerts);
	},

	_createHTML: function() {
		var instance = this;

		var notice = jQuery('<div class="' + instance._noticeClass + '" dynamic="true"><div class="popup-alert-content"></div></div>');

		notice.html(instance._content);

		instance._addCloseButton(notice);
		instance._addToggleButton(notice);

		notice.appendTo('body');

		instance._notice = notice;
	},

	_addCloseButton: function(notice) {
		var instance = this;

		if (instance._closeText !== false) {
			instance._closeText = instance._closeText || Liferay.Language.get('close');
		}
		else {
			instance._useCloseButton = false;
			instance._closeText = '';
		}

		if (instance._useCloseButton) {
			var html = '<input class="submit popup-alert-close" type="submit" value="' + instance._closeText + '" />';

			notice.append(html);

			var closeButton = notice.find('.popup-alert-close');
			closeButton.click(
				function() {
					notice.slideUp('normal',
						function() {
							notice.remove();
						}
					);

					if (instance._onClose) {
						instance._onClose();
					}
				}
			);
		}
	},

	_addToggleButton: function(notice) {
		var instance = this;

		if (instance._useToggleButton) {
			instance._hideText = instance._toggleText.hide || Liferay.Language.get('hide');
			instance._showText = instance._toggleText.show || Liferay.Language.get('show');

			var toggleButton = jQuery('<a class="toggle-button" href="javascript:;"><span>' + instance._hideText + '</span></a>');
			var toggleSpan = toggleButton.find('span');
			var height = 0;

			toggleButton.toggle(
				function() {
					notice.slideUp();
					toggleSpan.text(instance._showText);
				},
				function() {
					notice.slideDown();
					toggleSpan.text(instance._hideText);
				}
			);

			notice.append(toggleButton);
		}
	}
});
Liferay.Navigation = new Class({

	/*
	params.layoutIds: an array of displayable layout ids
	params.navBlock: the selector for the navigation block
	*/
	initialize: function(params) {
		var instance = this;

		instance.params = params;

		instance._navBlock = jQuery(instance.params.navBlock);

		instance._hasPermission = instance.params.hasPermission;
		instance._isModifiable = instance._navBlock.is('.modify-pages');
		instance._isSortable = instance._navBlock.is('.sort-pages') && instance._hasPermission;
		instance._isUseHandle = instance._navBlock.is('.use-handle');

		instance._updateURL = themeDisplay.getPathMain() + '/layout_management/update_page';

		var items = instance._navBlock.find('> ul > li');

		items.each(
			function(i) {
				this._LFR_layoutId = instance.params.layoutIds[i];
			}
		);

		instance._makeAddable();
		instance._makeDeletable();
		instance._makeSortable();
		instance._makeEditable();

		Liferay.Publisher.register('navigation');

		Liferay.Publisher.subscribe('tree', instance._treeCallback, instance);
	},

	_addPage: function(event, obj) {
		var instance = this;

		var navItem = instance._navBlock;
		var addBlock = jQuery('<li>' + instance._enterPage + '</li>');

		var blockInput = addBlock.find('input');

		navItem.find('ul:first').append(addBlock);

		var savePage = addBlock.find('.save-page');
		var cancelPage = addBlock.find('.cancel-page');
		var currentInput = addBlock.find('.enter-page input');

		var pageParents = jQuery(document);

		var pageBlur = function(internalEvent) {
			var currentEl = jQuery(internalEvent.target);
			var liParent = currentEl.parents('ul:eq(0)');

			if ((liParent.length == 0) && !currentEl.is('li') && !currentEl.parents('#add-page').length) {
				cancelPage.trigger('click');
			}
		};

		pageParents.click(pageBlur);

		cancelPage.click(
			function(event) {
				instance._cancelAddingPage(event, addBlock);
				pageParents.unbind('click', pageBlur);
			}
		);

		savePage.click(
			function(event){
				instance._savePage(event, this, instance);
				pageParents.unbind('click', pageBlur);
			}
		);

		currentInput.keyup(
			function(event){
				if (event.keyCode == 13) {
					savePage.trigger('click');
				}
				else if (event.keyCode == 27) {
					cancelPage.trigger('click');
				} else {
					return;
				}

				pageParents.unbind('click', pageBlur);
			}
		);
		blockInput[0].focus();
	},

	_cancelAddingPage: function(event, obj) {
		var instance = this;
		obj.remove();
	},

	_cancelPage: function(event, obj, oldName) {
		var navItem = null;

		if (oldName) {
			navItem = jQuery(obj).parents('li');

			var enterPage = navItem.find('.enter-page');

			enterPage.prev().show();
			enterPage.remove();
		}
		else {
			navItem = jQuery(this).parents('li');

			navItem.remove();
		}
	},

	_deleteButton: function(obj) {
		var instance = this;

		obj.append('<span class="delete-tab">X</span>');

		var deleteTab = obj.find('.delete-tab');

		deleteTab.click(
			function(event) {
				instance._removePage(this, instance);

			}
		);

		deleteTab.hide();

		obj.hover(
			function() {
				jQuery(this).find('.delete-tab').fadeIn('fast');
			},
			function() {
				jQuery(this).find('.delete-tab').fadeOut('fast');
			}
		);
	},

	_makeAddable: function() {
		var instance = this;

		if (instance._isModifiable) {
			var navList = instance._navBlock.find('ul:first');

			instance._enterPage =
				'<div class="enter-page">' +
				'<input type="text" name="new_page" value="" class="text" />' +
				'<a class="cancel-page" href="javascript: ;"></a>' +
				'<a class="save-page" href="javascript: ;">' + Liferay.Language.get('save') + '</a>' +
				'</div>';

			if (instance._hasPermission) {
				navList.after(
					'<div id="add-page">' +
					'<a href="javascript:;">' +
					'<span>' + Liferay.Language.get('add-page') + '</span>' +
					'</a>' +
					'</div>');

				var addPage = navList.parent().find('#add-page a');

				addPage.click(
					function(event){
						instance._addPage(event, this);
					}
				);
			}
		}
	},

	_makeDeletable: function() {
		var instance = this;

		if (instance._isModifiable && instance._hasPermission) {
			var navItems = instance._navBlock.find('li').not('.selected');

			instance._deleteButton(navItems);
		}
	},

	_makeEditable: function() {
		var instance = this;

		if (instance._isModifiable) {
			var currentItem = instance._navBlock.find('li.selected');
			var currentLink = currentItem.find('a');
			var currentSpan = currentLink.find('span');

			currentLink.click(
				function(event) {
					if (event.shiftKey) {
						return false;
					}
				}
			);

			var resetCursor = function() {
				currentSpan.css('cursor', 'pointer');
			};

			currentLink.hover(
				function(event) {
					if (!themeDisplay.isStateMaximized() || event.shiftKey) {
						currentSpan.css('cursor', 'text');
					}
				},
				resetCursor
			);

			currentSpan.click(
				function(event) {
					if (themeDisplay.isStateMaximized() && !event.shiftKey) {
						return;
					}

					var span = jQuery(this);
					var text = span.text();

					span.parent().hide();
					span.parent().after(instance._enterPage);

					var enterPage = span.parent().next();

					var pageParents = enterPage.parents();

					var enterPageInput = enterPage.find('input');

					var pageBlur = function(event) {
						event.stopPropagation();

						if (!jQuery(this).is('li')) {
							cancelPage.trigger('click');
						}

						return false;
					};

					enterPageInput.val(text);

					enterPageInput.trigger('select');

					var savePage = enterPage.find('.save-page');

					savePage.click(
						function(event) {
							instance._savePage(event, this, instance, text);
							pageParents.unbind('blur', pageBlur);
							pageParents.unbind('click', pageBlur);
						}
					);

					var cancelPage = enterPage.find('.cancel-page');

					cancelPage.hide();

					cancelPage.click(
						function(event) {
							instance._cancelPage(event, this, text);
							pageParents.unbind('blur', pageBlur);
							pageParents.unbind('click', pageBlur);
						}
					);

					enterPageInput.keyup(
						function(event) {
							if (event.keyCode == 13) {
								savePage.trigger('click');
								pageParents.unbind('blur', pageBlur);
								pageParents.unbind('click', pageBlur);
							}
							else if (event.keyCode == 27) {
								cancelPage.trigger('click');
								pageParents.unbind('blur', pageBlur);
								pageParents.unbind('click', pageBlur);
							}
						}
					);

					pageParents.click(pageBlur);

					resetCursor();

					return false;
				}
			);
		}
	},

	_makeSortable: function() {
		var instance = this;

		var navBlock = instance._navBlock;
		var navList = navBlock.find('ul:first');

		if (instance._isSortable) {
			var floatStyle = navList.find('> li').css('float');

			var items = navList.find('li');
			var anchors = items.find('a');

			if (instance._isUseHandle) {
				items.append('<span class="sort-handle">+</span>');
			}
			else {
				anchors.css('cursor', 'move');
				anchors.find('span').css('cursor', 'pointer');
			}

			items.addClass('sortable-item');

			instance.sortable = navList.Sortable(
				{
					accept: 'sortable-item',
					helperclass: 'sort-helper',
					activeclass: 'sortableactive',
					hoverclass: 'sortablehover',
					handle: (instance._isUseHandle ? '.sort-handle' : 'a'),
					opacity: 0.8,
					revert:	true,
					floats:	(floatStyle == 'left' || floatStyle == 'right'),
					tolerance: 'pointer',
					snapDistance: 10,
					onStop: function() {
						instance._saveSortables(this);

						Liferay.Publisher.deliver('navigation', this);
					}
				}
			);
		}
	},

	_removePage: function(obj, instance) {
		var tab = jQuery(obj).parents('li');
		var tabText = tab.find('a span').html();

		if (confirm(Liferay.Language.get('are-you-sure-you-want-to-delete-this-page'))) {
			var data = {
				doAsUserId: themeDisplay.getDoAsUserIdEncoded(),
				cmd: 'delete',
				groupId: themeDisplay.getGroupId(),
				privateLayout: themeDisplay.isPrivateLayout(),
				layoutId: tab[0]._LFR_layoutId
			};

			jQuery.ajax(
				{
					data: data,
					success: function() {
						Liferay.Publisher.deliver('navigation', tab, 'delete');

						tab.remove();
					},
					url: instance._updateURL
				}
			);
		}
	},

	_savePage: function(event, obj, instance, oldName) {
		if ((event.type == 'keyup') && (event.keyCode !== 13)) {
			return;
		}

		var data = null;
		var onSuccess = null;

		var newNavItem = jQuery(obj).parents('li');
		var name = newNavItem.find('input').val();
		var enterPage = newNavItem.find('.enter-page');

		if (oldName) {

			// Updating an existing page

			if (name != oldName) {
				data = {
					doAsUserId: themeDisplay.getDoAsUserIdEncoded(),
					cmd: 'name',
					groupId: themeDisplay.getGroupId(),
					privateLayout: themeDisplay.isPrivateLayout(),
					layoutId: themeDisplay.getLayoutId(),
					name: name,
					languageId: themeDisplay.getLanguageId()
				};

				onSuccess = function(data) {
					data = Liferay.Util.toJSONObject(data);

					var currentTab = enterPage.prev();
					var currentSpan = currentTab.find('span');

					currentSpan.text(name);
					currentTab.show();

					enterPage.remove();

					var oldTitle = jQuery(document).attr('title');

					var regex = new RegExp(oldName, 'g');

					newTitle = oldTitle.replace(regex, name);

					jQuery(document).attr('title', newTitle);
				}
			}
			else {

				// The new name is the same as the old one

				var currentTab = enterPage.prev();

				currentTab.show();
				enterPage.remove();

				return false;
			}
		}
		else {

			// Adding a new page

			data = {
				mainPath: themeDisplay.getPathMain(),
				doAsUserId: themeDisplay.getDoAsUserIdEncoded(),
				cmd: 'add',
				groupId: themeDisplay.getGroupId(),
				privateLayout: themeDisplay.isPrivateLayout(),
				parentLayoutId: themeDisplay.getParentLayoutId(),
				name: name
			};

			onSuccess = function(data) {
				data = Liferay.Util.toJSONObject(data);

				var newTab = jQuery('<a href="' + data.url + '"><span>' + name + '</span></a>');

				if (instance._isUseHandle) {
					enterPage.before('<span class="sort-handle">+</span>');
				}
				else {
					newTab.css('cursor', 'move');
				}

				newNavItem[0]._LFR_layoutId = data.layoutId;

				enterPage.before(newTab);
				enterPage.remove();

				instance.sortable.SortableAddItem(newNavItem[0]);
				instance._deleteButton(newNavItem);

				Liferay.Publisher.deliver('navigation', newNavItem);
			}
		}

		jQuery.ajax(
			{
				data: data,
				success: onSuccess,
				url: instance._updateURL
			}
		);
	},

	_saveSortables: function(obj) {
		var instance = this;

		tabs = jQuery('li', instance._navBlock);

		var data = {
			doAsUserId: themeDisplay.getDoAsUserIdEncoded(),
			cmd: 'priority',
			groupId: themeDisplay.getGroupId(),
			privateLayout: themeDisplay.isPrivateLayout(),
			layoutId: obj._LFR_layoutId,
			priority: tabs.index(obj)
		};

		jQuery.ajax(
			{
				data: data,
				url: instance._updateURL
			}
		);
	},

	_treeCallback: function(item, obj) {
		var instance = this;

		var navigation = instance._navBlock.find('> ul');

		if (instance._isSortable) {
			var liItems = navigation.find('> li');

			var droppedItem = jQuery(item);
			var tree = droppedItem.parent();
			var droppedName = droppedItem.find('span:first').text();
			var newParent = jQuery(obj).parents('li:first');

			var liChild = liItems.find('span').not('.delete-tab');

			liChild = liChild.filter(
				function() {
					var currentItem = jQuery(this);

					if (currentItem.text() == droppedName) {
						return true;
					}
					else {
						return false;
					}
				}
			);

			var treeItems = tree.find('> li');

			var newIndex = treeItems.index(item);

			if (liChild.length > 0) {
				var newSibling = liItems.eq(newIndex);
				var parentLi = liChild.parents('li:first');

				if (!newParent.is('.tree-item')) {
					newSibling.after(parentLi);

					if (parentLi.is(':hidden')) {
						parentLi.show();
					}
				}
				else {

					//TODO: add parsing to move child elements around by their layoutId

					parentLi.hide();
				}
			}
			else if (!newParent.is('.tree-item')) {
				var newTab = liItems.lt(1).clone();

				newTab.removeClass('selected');
				newTab.find('.child-menu').remove();

				var newTabLink = newTab.find('a span');

				newTabLink.text(droppedName);
				newTabLink.css('cursor', 'pointer');

				liItems.parent().append(newTab);
			}
		}
	},

	_isSortable: false,
	_isModifiable: false,
	_isUseHandle: false,
	_hasPermission: false,
	_enterPage: '',
	_updateURL: ''
});
Liferay.Session = {
	autoExtend: false,
	sessionTimeout: 0,
	sessionTimeoutWarning: 0,
	redirectOnExpire: false,

	init: function(params) {
		var instance = this;

		params = params || {};
		instance.autoExtend = params.autoExtend || instance.autoExtend;

		instance._timeout = params.timeout || instance.sessionTimeout;
		instance._warning = params.timeoutWarning || instance.sessionTimeoutWarning;

		instance.sessionTimeout = instance._timeout * 60000;
		instance.sessionTimeoutWarning = instance._warning * 60000;
		instance._timeoutDiff = instance.sessionTimeout - instance.sessionTimeoutWarning;

		instance._currentTime = instance.sessionTimeoutWarning;

		instance.redirectOnExpire = params.redirectOnExpire || instance.redirectOnExpire;

		instance._cookieKey = 'LFR_SESSION_STATE_' + themeDisplay.getUserId();

		instance.banner = new jQuery;

		var urlBase = themeDisplay.getPathMain() + '/portal/';
		instance._sessionUrls = {
			expire: urlBase + 'expire_session',
			extend: urlBase + 'extend_session'
		};

		instance._stateCheck = setTimeout(
			function() {
				instance.checkState();
			},
		instance._timeoutDiff);

		var timeoutMinutes = instance._timeout;
		var timeLeft = instance._warning;

		instance._warningText = Liferay.Language.get('warning-your-session-will-expire', ['[$SPAN$]', timeoutMinutes]);
		instance._warningText = instance._warningText.replace(/\[\$SPAN\$\]/, '<span class="countdown-timer"></span>');

		instance._toggleText = {
			hide: Liferay.Language.get('hide'),
			show: Liferay.Language.get('show')
		};

		instance._expiredText = Liferay.Language.get('warning-your-session-has-expired');
		instance._extendText = Liferay.Language.get('extend');

		instance.setCookie();
	},

	checkState: function() {
		var instance = this;

		var currentTime = new Date().getTime();
		var sessionState = instance.getCookie();
		var newWaitTime = instance.sessionTimeoutWarning;
		var timeDiff = 0;

		clearTimeout(instance._stateCheck);
		if (sessionState == 'expired') {
			instance.expire();
		}
		else {
			timeDiff = currentTime - sessionState;

			if (!instance.autoExtend) {
				if ((timeDiff + 100) >= instance.sessionTimeoutWarning) {
						instance.warn();
				}
				else {
					newWaitTime = (instance.sessionTimeoutWarning - timeDiff) + 10000;
					instance._stateCheck = setTimeout(
						function() {
							instance.checkState();
						},
					newWaitTime);
				}
			}
			else {
				instance.extend();
			}
		}
	},

	getCookie: function() {
		var instance = this;

		return jQuery.cookie(instance._cookieKey) || 0;
	},

	expire: function() {
		var instance = this;

		var banner = instance.banner;
		var warningText = banner.find('#sessionWarningText');

		document.title = instance._originalTitle;

		if (warningText.length) {
			var sessionHasExpired = instance._expiredText;
			warningText.html(sessionHasExpired);

			clearTimeout(instance._sessionExpired);

			var okBtn = banner.find('#okBtn');

			okBtn.click(
				function() {
					instance.notice.close();
					window.location = themeDisplay.getURLHome();
				}
			);

			var cancelBtn = banner.find('#cancelBtn');

			cancelBtn.hide();

			jQuery.ajax(
				{
					url: instance._sessionUrls.expire
				}
			);
		}
		instance.setCookie('expired');

		if (instance.redirectOnExpire) {
			location.href = themeDisplay.getURLHome();
		}
	},

	extend: function() {
		var instance = this;

		if (instance._countdownTimer) {
			clearInterval(instance._countdownTimer);
		}
		jQuery.ajax(
			{
				url: instance._sessionUrls.extend
			}
		);
		document.title = instance._originalTitle;

		if (instance._sessionWarning) {
			clearTimeout(instance._sessionWarning);
		}

		instance._sessionWarning = setTimeout(
			function() {
				if (!instance.autoExtend) {
					instance.warn();
				}
				else {
					instance.extend();
				}
			},
			instance.sessionTimeoutWarning
		);

		instance.setCookie();
	},

	setCookie: function(status) {
		var instance = this;

		var currentTime = new Date().getTime();
		jQuery.cookie(instance._cookieKey, status || currentTime);
	},

	warn: function() {
		var instance = this;

		instance.banner = new Liferay.Notice({
			content: instance._warningText,
			closeText: instance._extendText,
			onClose: function() {
				instance.extend();
			},
			toggleText: false
		});

		instance._counter();

		instance._sessionExpired = setTimeout(
			function() {
				instance.expire();
			},
		instance.sessionTimeoutWarning);
	},

	_counter: function() {
		var instance = this;

		var banner = instance.banner;
		if (banner.length) {
			instance._counterText = banner.find('.countdown-timer');
			instance._originalTitle = document.title;
			var interval = 1000;

			instance._counterText.text(instance._setTime());
			document.title = instance.banner.text();

			instance._countdownTimer = setInterval(
				function() {
					var time = instance._setTime();

					instance._currentTime = instance._currentTime - interval;

					if (instance._currentTime > 0) {
						instance._counterText.text(time);
						document.title = instance.banner.text();
					} else {
						instance.banner.html(instance._expiredText);
						instance.banner.toggleClass('popup-alert-notice').toggleClass('popup-alert-warning');

						if (instance._countdownTimer) {
							clearInterval(instance._countdownTimer);
						}
					}
				},
			interval
			);
		}
	},

	_formatNumber: function(num) {
		var instance = this;

		if (!Liferay.Util.isArray(num)) {
			if (num <= 9) {
				num = '0' + num;
			}
		} else {
			num = jQuery.map(num, instance._formatNumber);
		}
		return num;
	},

	_setTime: function() {
		var instance = this;

		var amount = instance._currentTime;

		if(amount <= 0){

		}
		else {
			var days=0, hours=0, minutes=0, seconds=0, output='';

			// Remove the milliseconds
			amount = Math.floor(amount/1000);

			hours = Math.floor(amount/3600);
			amount = amount%3600;

			minutes = Math.floor(amount/60);
			amount = amount%60;

			seconds = Math.floor(amount);

			return instance._formatNumber([hours, minutes, seconds]).join(':');
		}
	},

	_banner: [],
	_countdownTimer: null,
	_currentTime: 0,
	_originalTitle: '',
	_sessionUrls: {},
	_sessionWarning: null,
	_sessionExpired: null,
	_timeout: 0,
	_timeoutDiff: 0,
	_warning: 0
};
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
Liferay.Upload = new Class({
	/*
	 * PARAMETERS:
	 * allowedFileTypes (string) *Required - a comma seperated list of allowable filetypes
	 * container (jQuery Selector | DOM Element) *Required - container where the uploader will be placed
	 * maxFileSize (int) *Required - the maximum file size that can be uploaded
	 * uploadFile (string) *Required - the URL to where the file will be uploaded
	 *
	 * fallbackContainer (jQuery Selector | DOM Element) *Optional - the container holding a fallback (in case flash is not supported)
	 * namespace (string) *Optional - A unique string so that the global callback methods don't collide
	 * fileDescription (string) *Optional - a string describing what files can be uploaded
	 */
	initialize: function(params) {
		var instance = this;

		params = params || {};

		instance._container = jQuery(params.container);
		instance._fallbackContainer = jQuery(params.fallbackContainer || []);
		instance._namespaceId = params.namespace || '_liferay_pns_' + Liferay.Util.randomInt() + '_';
		instance._maxFileSize = params.maxFileSize || 0;
		instance._allowedFileTypes = params.allowedFileTypes;
		instance._uploadFile = params.uploadFile;

		instance._classicUploaderParam = 'uploader=classic';
		instance._newUploaderParam = 'uploader=new';

		// Check for an override via the query string

		var loc = location.href;

		if (loc.indexOf(instance._classicUploaderParam) > -1 && instance._fallbackContainer.length) {
			instance._fallbackContainer.show();

			if (!instance._fallbackIframe) {
				instance._fallbackIframe = instance._fallbackContainer.find('iframe[@id$=-iframe]');

				instance._fallbackIframe.height(300);
			}

			return;
		}

		// Language keys

		instance._browseText = Liferay.Language.get('browse-you-can-select-multiple-files');
		instance._cancelUploadsText = Liferay.Language.get('cancel-all-uploads');
		instance._cancelFileText = Liferay.Language.get('cancel-upload');
		instance._clearRecentUploadsText = Liferay.Language.get('clear-recent-uploads');
		instance._fileListPendingText = Liferay.Language.get('x-files-ready-to-be-uploaded', '0');
		instance._fileListText = Liferay.Language.get('file-list');
		instance._fileTypesDescriptionText = params.fileDescription || instance._allowedFileTypes;
		instance._uploadsCompleteText = Liferay.Language.get('all-uploads-complete');
		instance._uploadStatusText = Liferay.Language.get('uploading-file-x-of-x', ['[$POS$]','[$TOTAL$]']);
		instance._uploadFilesText = Liferay.Language.get('upload-files');

		if (instance._fallbackContainer.length) {
			instance._useFallbackText = Liferay.Language.get('use-the-classic-uploader');
			instance._useNewUploaderText = Liferay.Language.get('use-the-new-uploader');
		}

		instance._setupCallbacks();
		instance._setupUploader();
	},

	 fileAdded: function(file, listLength) {
		var instance = this;

		var listingFiles = instance._fileList;
		var listingUl = listingFiles.find('ul');

		if (!listingUl.length) {
			instance._listInfo.append('<h4>' + instance._fileListText + '</h4>');
			listingFiles.append('<ul></ul>');

			instance._uploadTarget.append(instance._clearUploadsButton);
			instance._clearUploadsButton.hide();

			instance._cancelButton.click(
				function() {
					instance.cancelUploads();
					instance._clearUploadsButton.hide();
				}
			);
		}

		instance._cancelButton.show();
		instance._uploadButton.show();

		listingFiles = listingFiles.find('ul');

		var fileId = instance._namespace(file.id);
		var fileName = file.name;

		var li = jQuery(
			'<li class="upload-file" id="' + fileId + '">' +
				'<span class="file-title">' + fileName + '</span>' +
				'<span class="progress-bar">' +
					'<span class="progress" id="' + fileId + 'progress"></span>' +
				'</span>' +
				'<a class="lfr-button cancel-button" href="javascript: ;" id="' + fileId+ 'cancelButton">' + instance._cancelFileText + '</a>' +
			'</li>');

		li.find('.cancel-button').click(
			function() {
				instance._uploader.cancelFile(file.id);
			}
		);

		var uploadedFiles = listingFiles.find('.upload-complete');

		uploadedFiles = uploadedFiles.filter(':first');

		if (uploadedFiles.length) {
			uploadedFiles.before(li);
		}
		else {
			listingFiles.append(li);
		}

		instance._updateList(listLength);
	},

	fileCancelled: function(file, listLength) {
		var instance = this;

		var fileId = instance._namespace(file.id);
		var fileName = file.name;
		var li = jQuery('#' + fileId);

		instance._updateList(listLength);

		li.fadeOut('slow');
	},

	flashLoaded: function() {
		var instance = this;

		instance._setupControls();
	},

	uploadStart: function(file, position, listLength) {
		var instance = this;

		var currentListText = instance._uploadStatusText.replace('[$POS$]', position).replace('[$TOTAL$]', listLength);
		var fileId = instance._namespace(file.id);

		instance._updateList(listLength, currentListText);

		var li = jQuery('#' + fileId);

		li.addClass('file-uploading');

		return true;
	},

	uploadProgress: function(file, bytesLoaded) {
		var instance = this;
		var fileId = instance._namespace(file.id);
		var progress = document.getElementById(fileId + 'progress');
		var percent = Math.ceil((bytesLoaded / file.size) * 100);

		progress.style.width = percent + '%';
	},

	uploadError: function(errno) {

		// SWFUpload.debug(errno);

	},

	fileUploadComplete: function(file) {
		var instance = this;

		var fileId = instance._namespace(file.id);
		var li = jQuery('#' + fileId);

		li.removeClass('file-uploading').addClass('upload-complete');
	},

	cancelUploads: function() {
		var instance = this;

		instance._uploader.cancelQueue();
		instance._uploadButton.hide();
		instance._cancelButton.hide();
	},

	uploadsComplete: function(file) {
		var instance = this;

		instance._cancelButton.hide();
		instance._updateList(0, instance._uploadsCompleteText);
		instance._uploadButton.hide();

		if (instance._clearUploadsButton.is(':hidden')) {
			instance._clearUploadsButton.show();
		}
	},

	_clearUploads: function() {
		var instance = this;

		var completeUploads = instance._fileList.find('.upload-complete');

		completeUploads.fadeOut('slow',
			function() {
				jQuery(this).remove();
			}
		);

		instance._clearUploadsButton.hide();
	},

	_namespace: function(txt) {
		var instance = this;

		txt = txt || '';

		return instance._namespaceId + txt;

	},

	_setupCallbacks: function() {
		var instance = this;

		// Global callback references

		instance._cancelUploads = instance._namespace('cancelUploads');
		instance._fileAdded = instance._namespace('fileAdded');
		instance._fileCancelled = instance._namespace('fileCancelled');
		instance._flashLoaded = instance._namespace('flashLoaded');
		instance._uploadStart = instance._namespace('uploadStart');
		instance._uploadProgress = instance._namespace('uploadProgress');
		instance._uploadError = instance._namespace('uploadError');
		instance._fileUploadComplete = instance._namespace('fileUploadComplete');
		instance._uploadsComplete = instance._namespace('uploadsComplete');
		instance._uploadsCancelled = instance._namespace('uploadsCancelled');

		// Global swfUpload var

		instance._swfUpload = instance._namespace('cancelUploads');

		window[instance._cancelUploads] = function() {
			instance.cancelUploads.apply(instance, arguments);
		};

		window[instance._fileAdded] = function() {
			instance.fileAdded.apply(instance, arguments);
		};

		window[instance._fileCancelled] = function() {
			instance.fileCancelled.apply(instance, arguments);
		};

		window[instance._uploadStart] = function() {
			instance.uploadStart.apply(instance, arguments);
		};

		window[instance._uploadProgress] = function() {
			instance.uploadProgress.apply(instance, arguments);
		};

		window[instance._uploadError] = function() {
			instance.uploadError.apply(instance, arguments);
		};

		window[instance._fileUploadComplete] = function() {
			instance.fileUploadComplete.apply(instance, arguments);
		};

		window[instance._uploadsComplete] = function() {
			instance.uploadsComplete.apply(instance, arguments);
		};

		window[instance._flashLoaded] = function() {
			instance.flashLoaded.apply(instance, arguments);
		};

	},

	_setupControls: function() {
		var instance = this;

		instance._uploadTargetId = instance._namespace('uploadTarget');
		instance._listInfoId = instance._namespace('listInfo');
		instance._fileListId = instance._namespace('fileList');

		instance._uploadTarget = jQuery('<div id="' + instance._uploadTargetId + '" class="float-container upload-target"></div>');
		instance._listInfo = jQuery('<div id="' + instance._listInfoId + '" class="upload-list-info"></div>');
		instance._fileList = jQuery('<div id="' + instance._fileListId + '" class="upload-list"></div>');
		instance._cancelButton = jQuery('<a class="lfr-button cancel-uploads" href="javascript: ;">' + instance._cancelUploadsText + '</a>');
		instance._clearUploadsButton = jQuery('<a class="lfr-button clear-uploads" href="javascript: ;">' + instance._clearRecentUploadsText + '</a>');

		instance._browseButton = jQuery('<a class="lfr-button browse-button" href="javascript: ;">' + instance._browseText + '</a>');
		instance._uploadButton = jQuery('<a class="lfr-button upload-button" href="javascript: ;">' + instance._uploadFilesText + '</a>');

		instance._container.prepend([instance._uploadTarget[0], instance._listInfo[0], instance._fileList[0]]);
		instance._uploadTarget.append([instance._browseButton[0], instance._uploadButton[0], instance._cancelButton[0]]);

		instance._clearUploadsButton.click(
			function() {
				instance._clearUploads();
			}
		);

		instance._browseButton.click(
			function() {
				instance._uploader.browse();
			}
		);

		instance._uploadButton.click(
			function() {
				instance._uploader.upload();
			}
		);

		instance._uploadButton.hide();
		instance._cancelButton.hide();

		if (instance._fallbackContainer.length) {
			instance._useFallbackButton = jQuery('<a class="use-fallback using-new-uploader" href="javascript: ;">' + instance._useFallbackText + '</a>');
			instance._fallbackContainer.after(instance._useFallbackButton);

			instance._useFallbackButton.click(
				function() {
					var fallback = jQuery(this);
					var newUploaderClass = 'using-new-uploader';
					var fallbackClass = 'using-classic-uploader';

					if (fallback.is('.' + newUploaderClass)) {
						instance._container.hide();
						instance._fallbackContainer.show();

						fallback.text(instance._useNewUploaderText);
						fallback.removeClass(newUploaderClass).addClass(fallbackClass);

						if (!instance._fallbackIframe) {
							instance._fallbackIframe = instance._fallbackContainer.find('iframe[@id$=-iframe]');

							instance._fallbackIframe.height(300);
						}

						var classicUploaderUrl = '';

						if (location.hash.length) {
							classicUploaderUrl = '&';
						}

						location.hash += classicUploaderUrl + instance._classicUploaderParam;
					}
					else {
						instance._container.show();
						instance._fallbackContainer.hide();
						fallback.text(instance._useFallbackText);
						fallback.removeClass(fallbackClass).addClass(newUploaderClass);

						location.hash = location.hash.replace(instance._classicUploaderParam, instance._newUploaderParam);
					}
				}
			);
		}
	},


	_setupUploader: function() {
		var instance = this;

		if (instance._allowedFileTypes.indexOf('*') == -1) {
			var fileTypes = instance._allowedFileTypes.split(',');

			fileTypes = jQuery.map(
				fileTypes,
				function(value, key) {
					var fileType = value;
					if (value.indexOf('*') == -1) {
						fileType = '*' + value;
					}
					return fileType;
				}
			);

			instance._allowedFileTypes = fileTypes.join(';');
		}

		instance._uploader = new SWFUpload({
			upload_script: instance._uploadFile,
			target: instance._uploadTargetId,
			flash_path: '/html/js/misc/swfupload/SWFUpload.swf',
			allowed_filesize: instance._maxFileSize,
			allowed_filetypes: instance._allowedFileTypes,
			allowed_filetypes_description: instance._fileTypesDescriptionText,
			browse_link_innerhtml: instance._browseText,
			upload_link_innerhtml: instance._uploadFilesText,
			browse_link_class: 'browse-button liferay-button',
			upload_link_class: 'upload-button liferay-button',
			flash_loaded_callback: instance._flashLoaded,
			upload_file_queued_callback: instance._fileAdded,
			upload_file_start_callback: instance._uploadStart,
			upload_progress_callback: instance._uploadProgress,
			upload_file_complete_callback: instance._fileUploadComplete,
			upload_file_cancel_callback: instance._fileCancelled,
			upload_queue_complete_callback: instance._uploadsComplete,
			upload_error_callback: instance._uploadError,
			upload_cancel_callback: instance._cancelUploads,
			auto_upload : false,
			upload_field_name: 'file',
			create_ui: true,
			debug: false
		});

		window[instance._swfUpload] = instance._uploader;
	},

	_updateList: function(listLength, message) {
		var instance = this;

		var infoTitle = instance._listInfo.find('h4');
		var listText = '';

		if (!message) {
			listText = instance._fileListPendingText;
			listText = listText.replace(/\d+/g, listLength);
		}
		else {
			listText = message;
		}

		infoTitle.html(listText);
	}
});
