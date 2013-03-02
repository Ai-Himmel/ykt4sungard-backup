
function selectIns() {
    if (document.all.deleteX != null) {
        if (document.all.deleteX.length == null) {
            if (document.all.checkSwitch.checked == true) {
                document.all.deleteX.checked = true;
            } else {
                document.all.deleteX.checked = false;
            }
        } else {
            for (var i = 0; i < document.all.deleteX.length; i++) {
                if (document.all.checkSwitch.checked == true) {
                    document.all.deleteX[i].checked = true;
                } else {
                    document.all.deleteX[i].checked = false;
                }
            }
        }
    }
}
/* This function is to select all options in a multi-valued <select> */
function selectAll(elementId) {
    var element = document.getElementById(elementId);
    len = element.length;
    if (len != 0) {
        for (i = 0; i < len; i++) {
            element.options[i].selected = true;
        }
    }
}



function KeyDown() {
	// F5 //82Ctrl + R
    if ((event.keyCode == 13) || (event.keyCode == 114) || (event.keyCode == 116) || (event.ctrlKey && event.keyCode == 82) || event.keyCode == 122) {
	//	alert(window.event.srcElement.type)
        event.keyCode = 0;
        event.returnValue = false;
    }
    if ((event.keyCode == 8)) {
        var sType = window.event.srcElement.type.toUpperCase();
        if (sType == "TEXT" || sType == "PASSWORD" || sType == "TEXTAREA") {
        } else {
            event.keyCode = 0;
            event.returnValue = false;
        }
    }
	//Ctrl+n
    if ((event.ctrlKey) && (event.keyCode == 78)) {
        event.returnValue = false;
    }
	//shift+F10
    if ((event.shiftKey) && (event.keyCode == 121)) {
        event.returnValue = false;
    }

//	if (window.event.srcElement.tagName == "A" && window.event.shiftKey)
//	window.event.returnValue = false; // shift
////
    if ((window.event.altKey) && (window.event.keyCode == 115)) { //Alt+F4
        window.showModelessDialog("about:blank", "", "dialogWidth:1px;dialogheight:1px");
        return false;
    }
}

function createFormElement(element, type, name, id, value, parent) {
    var e = document.createElement(element);
    e.setAttribute("name", name);
    e.setAttribute("type", type);
    e.setAttribute("id", id);
    e.setAttribute("value", value);
    parent.appendChild(e);
}

function confirmDelete(obj) {   
    var msg = "х╥хои╬ЁЩ " + obj + "?";
    ans = confirm(msg);
    if (ans) {
        return true;
    } else {
        return false;
    }
}
