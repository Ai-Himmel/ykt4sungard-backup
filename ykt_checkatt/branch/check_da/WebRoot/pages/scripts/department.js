function getDepartments(inputId, selectId) {
    var inputObj = document.getElementById(inputId);
    //var divObj = document.getElementById(divId);
    var selectObj = document.getElementById(selectId);

    var ttop = inputObj.offsetTop;    //TT控件的定位点高
    var thei = inputObj.clientHeight;    //TT控件本身的高
    var tleft = inputObj.offsetLeft;   //TT控件的定位点宽
    var tempObj = inputObj.offsetParent;
    while(tempObj != document.body) {
        ttop += tempObj.offsetTop;
        tleft += tempObj.offsetLeft;
        tempObj = tempObj.offsetParent;
    }

    selectObj.style.top = ttop + thei + 2;
    selectObj.style.left = tleft;

    if (Trim(inputObj.value) == "") {
        selectObj.innerHTML = "<LI>请输入班级拼音简称，包含数字</LI>";
    }
    selectObj.style.display = "block";

}
function search(inputId,selectId){
    if (!checkEvent()) {
        return;
    }
    doSearch(inputId,selectId,'1');
}
function doSearch(inputId, selectId,d_page) {
    var inputObj = document.getElementById(inputId);
    var selectObj = document.getElementById(selectId);
    var keywords = inputObj.value;
    selectObj.style.display = "block";
    if (Trim(keywords) == "") {
        selectObj.innerHTML = "<LI>请输入班级拼音简称，包含数字</LI>";
        return;
    }
    var url = "department.do?method=searchDepartment";
    var paras = "keywords=" + keywords + "&d_page=" + d_page;
    new Ajax.Request(url,
    {
        method:'post',
        parameters: paras,
        onSuccess: function(result) {
            if (result.responseText.indexOf("error:") != 0) {
                selectObj.innerHTML = result.responseText;
            }
        }
    });
}
function goToPage(d_page){
    doSearch('departmentName','deptSelect',d_page);
}
function checkEvent() {
    var legal = false;
    if (window.event) {
        //for ie
        var keycode = window.event.keyCode;
        if (keycode >= 65 && keycode <= 90) {
            //a-z
            legal = true;
        } else if (keycode >= 48 && keycode <= 57) {
            //0-9
            legal = true;
        } else if (keycode >= 96 && keycode <= 105) {
            //0-9
            legal = true;
        } else if (keycode == 8 || keycode == 32) {
            //Backspace and Spacebar
            legal = true;
        }
    }
    return legal;
}
function hide(selectId) {
    var selectObj = document.getElementById(selectId);
    selectObj.style.display = "none";
}
function show(selectId) {
    var selectObj = document.getElementById(selectId);
    selectObj.style.visibility = "block";
}

var timeer;
function drop_mouseout(selectId) {
    timer = setTimeout("hide('" + selectId + "')", 1000);
}
function drop_mouseover(selectId) {
    try {
        window.clearTimeout(timer);
    } catch(e) {
    }
}
// 去掉字符串的头空格（左空格）
function LTrim(str) {
    var i;
    for (i = 0; i < str.length; i++) {
        if (str.charAt(i) != " ") break;
    }
    str = str.substring(i, str.length);
    return str;
}
// 去掉字符串的尾空格（右空格）
function RTrim(str) {
    var i;
    for (i = str.length - 1; i >= 0; i--) {
        if (str.charAt(i) != " ") break;
    }
    str = str.substring(0, i + 1);
    return str;
}

// 去掉字符串的头尾空格（左右空格）
function Trim(str) {
    return LTrim(RTrim(str));
}
