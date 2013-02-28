/**
 * Copyright 2006 options
 * transfer scr select to a tgt select
 * add it by hanjiwei
 */
 
function returnOption(e1,e2,all){
  	var catArr = e1.categories;
  	var src = e2.options;
  	var tgt = e1.options;
  	var items;
  	var index;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) {
      	if (catArr != null) {
        	for (var j = 0; j < catArr.length; ++j) {
          		items = catArr[j].items;
          		index = uiCommon_findSelectOption(items, tgt[i]);

          		// some target items don't exist in the source item collection
          		if(index >= 0) {
	            	items[index].disabled = false;
	            	items[index].selected = true;
	            	// because we change the option's color earlier, we need to
	            	// to reset it
	            	items[index].style.color = 'red';	           	 	
	           	 	uiOptionReturn_putArrayItem(tgt[i].value);
	           	 	tgt[i] = null;
	            	break;
          		}else{
          			 clone = uiCommon_cloneSelectOption(tgt[i]);
          			 src.add(clone);
          			 uiOptionReturn_putArrayItem(tgt[i].value);
          			 tgt[i] = null;
          			 break;
          		}
        	}
      	}else {
        		index = uiCommon_findSelectOption(src, tgt[i]);
        		// some target items don't exist in the source item collection
        		if(index >= 0) {
	          		src[index].disabled = false;
	          		src[index].selected = true;
	          		// because we change the option's color earlier, we need to
	          		// to reset it
	          		src[index].style.color = 'red';
	          		uiOptionReturn_putArrayItem(tgt[i].value);
	          		tgt[i] = null;
        		}else{
        			clone = uiCommon_cloneSelectOption(tgt[i]);
          			src.add(clone);
          			uiOptionReturn_putArrayItem(tgt[i].value);
          			tgt[i] = null;
        		}
      		}
    	}
  	}
}



function showSelected(e1,e2){
  	var src = e2.options;
  	var tgt = e1.options;
  	var index;
  	for (var i = 0; i = tgt.length - 1; ++i) {
  		index = uiCommon_findSelectOption(src, tgt[i]);
  		if(index >= 0) {
      		src[index].disabled = false;
      		src[index].selected = true;
      		// because we change the option's color earlier, we need to
      		// to reset it
      		src[index].style.color = 'green';
  		}
  	}	
}
// Returns the location (index) of opt in list. If not found, -1 is returned.
function uiCommon_findSelectOption(list, opt) {
  for(var i = 0; i < list.length; ++i) {
    if(list[i].value == opt.value &&
       list[i].text == opt.text) {
      return i;
    }
  }
  return -1;
}

function transferOption(e1,e2,e3,all){
	var src = e1.options;
	var index = e3.selectedIndex;
	var classes = e3.options;
	var obj;
	for(var i = 0; i < src.length; ++i) {
		if((all || src[i].selected) && !src[i].disabled) {
			uiOptionTransfer_putTgtItem(e2, src[i]);
			uiOptionTransfer_putArrayItem(src[i].value, classes[index].value);
		}
	}
}
// Puts an item into the target select box
function uiOptionTransfer_putTgtItem(e2, item) {
	clone = uiCommon_cloneSelectOption(item);

  	item.disabled = true;
  	item.selected = false;
  	// store the previous color first
  	e2.optionColor = item.style.color;
  	// IE does not disable the option, so we simulate it by
  	// changing the color
  	item.style.color = 'green';

  	var tgt = e2.options;
  	tgt.add(clone);
  	
}


function uiCommon_cloneSelectOption(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}




//==================================dormAlert page used new ======================================================

function returnOption_dorm(e1,e2,all){
  	var catArr = e1.categories;
  	var src = e2.options;
  	var tgt = e1.options;
  	var items;
  	var index;
  	for (var i = tgt.length - 1; i >= 0; --i) {
    	if (all || tgt[i].selected) {
      	if (catArr != null) {
        	for (var j = 0; j < catArr.length; ++j) {
          		items = catArr[j].items;
          		index = uiCommon_findSelectOption_dorm(items, tgt[i]);

          		// some target items don't exist in the source item collection
          		if(index >= 0) {
	            	items[index].disabled = false;
	            	items[index].selected = true;
	            	// because we change the option's color earlier, we need to
	            	// to reset it
	            	items[index].style.color = 'red';	           	 	
	           	 	uiOptionReturn_putArrayItem_dorm(tgt[i].value);
	           	 	tgt[i] = null;
	            	break;
          		}else{
          			 clone = uiCommon_cloneSelectOption_dorm(tgt[i]);
          			 src.add(clone);
          			 uiOptionReturn_putArrayItem_dorm(tgt[i].value);
          			 tgt[i] = null;
          			 break;
          		}
        	}
      	}else {
        		index = uiCommon_findSelectOption_dorm(src, tgt[i]);
        		// some target items don't exist in the source item collection
        		if(index >= 0) {
	          		src[index].disabled = false;
	          		src[index].selected = true;
	          		// because we change the option's color earlier, we need to
	          		// to reset it
	          		src[index].style.color = 'red';
	          		uiOptionReturn_putArrayItem_dorm(tgt[i].value);
	          		tgt[i] = null;
        		}else{
        			clone = uiCommon_cloneSelectOption_dorm(tgt[i]);
          			src.add(clone);
          			uiOptionReturn_putArrayItem_dorm(tgt[i].value);
          			tgt[i] = null;
        		}
      		}
    	}
  	}
}



function showSelected_dorm(e1,e2){
  	var src = e2.options;
  	var tgt = e1.options;
  	var index;
  	for (var i = 0; i = tgt.length - 1; ++i) {
  		index = uiCommon_findSelectOption_dorm(src, tgt[i]);
  		if(index >= 0) {
      		src[index].disabled = false;
      		src[index].selected = true;
      		// because we change the option's color earlier, we need to
      		// to reset it
      		src[index].style.color = 'green';
  		}
  	}	
}
// Returns the location (index) of opt in list. If not found, -1 is returned.
function uiCommon_findSelectOption_dorm(list, opt) {
  for(var i = 0; i < list.length; ++i) {
    if(list[i].value == opt.value &&
       list[i].text == opt.text) {
      return i;
    }
  }
  return -1;
}

function transferOption_dorm(e1,e2,all){
	var src = e1.options;
	for(var i = 0; i < src.length; ++i) {
		if((all || src[i].selected) && !src[i].disabled) {
			uiOptionTransfer_putTgtItem_dorm(e2, src[i]);
			uiOptionTransfer_putArrayItem_dorm(src[i].value);
		}
	}
}
// Puts an item into the target select box
function uiOptionTransfer_putTgtItem_dorm(e2, item) {
	clone = uiCommon_cloneSelectOption_dorm(item);

  	item.disabled = true;
  	item.selected = false;
  	// store the previous color first
  	e2.optionColor = item.style.color;
  	// IE does not disable the option, so we simulate it by
  	// changing the color
  	item.style.color = 'green';
  	var tgt = e2.options;
  	tgt.add(clone);
  	
}


function uiCommon_cloneSelectOption_dorm(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}