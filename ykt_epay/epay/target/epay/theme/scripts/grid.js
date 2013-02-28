var highlightcolor = '#D0D0D0';
var clickcolor = '#fff';
function changeto() {
    source = event.srcElement;
    if (source.tagName == "TR" || source.tagName == "TABLE" || source.tagName=="TH") {
        return;
    }
    while (source.tagName != "TD")
        source = source.parentElement;
    source = source.parentElement;
    cs = source.children;
    //alert(cs.length);
    if (cs[1].style.backgroundColor != highlightcolor && source.id != "nc" && cs[1].style.backgroundColor != clickcolor)
        for (i = 0; i < cs.length; i++) {
            cs[i].style.backgroundColor = highlightcolor;
        }
}

function changeback() {
    source = event.srcElement;
    if (source.tagName == "TR" || source.tagName == "TABLE" || source.tagName=="TH") {
        return;
    }
    if (event.fromElement.contains(event.toElement) || source.contains(event.toElement) || source.id == "nc")
        return
    if (event.toElement != source && cs[1].style.backgroundColor != clickcolor)
    //source.style.backgroundColor=originalcolor
        for (i = 0; i < cs.length; i++) {
            cs[i].style.backgroundColor = "";
        }
}

function clickto() {
    source = event.srcElement;
    if (source.tagName == "TR" || source.tagName == "TABLE")
        return;
    while (source.tagName != "TD")
        source = source.parentElement;
    source = source.parentElement;
    cs = source.children;
    //alert(cs.length);
    if (cs[1].style.backgroundColor != clickcolor && source.id != "nc")
        for (i = 0; i < cs.length; i++) {
            cs[i].style.backgroundColor = clickcolor;
        }
    else
        for (i = 0; i < cs.length; i++) {
            cs[i].style.backgroundColor = "";
        }
}

function initEvent(tableId){
    var table = document.getElementById(tableId);
    if(table){
        if(table.attachEvent){
            table.attachEvent('onmousemove', changeto);
            table.attachEvent('onmouseout', changeback);
        }else if (table.addEventListener){
            table.addEventListener('onmousemove', changeto, false);
            table.addEventListener('onmouseout', changeback, false);
        }
    }
}
function displaytagform(formname, fields) {
    var objfrm = document.forms[formname];
    for (j = fields.length - 1; j >= 0; j--) {
        var f = objfrm.elements[fields[j].f];
        if (f) {
            f.value = fields[j].v;
        }
    }
    objfrm.submit();
}
function changePageSize(formname){
    var objfrm = document.forms[formname];
    if(objfrm("page")){
        objfrm("page").value = 1;
    }
    objfrm.submit();
}