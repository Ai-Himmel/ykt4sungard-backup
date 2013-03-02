//后台管理界面用到的一些函数

//checkbox中至少有一项被选中
function atleaseOneCheck()
{
    var items = document.all["itemlist"];
    if(items.length>0){
	    for (var i = 0; i < items.length; i++)
	    {
	        if (items[i].checked == true)
	        {
	            return true;
	        }
	    }
	}else{
		if(items.checked == true){
			  return true;		   	 
		}
	}
    return false;
}
function batch_del(form, entityName, action)
{
    if (confirm("确定要删除" + entityName + "?"))
    {
        if (!atleaseOneCheck())
        {
            alert('请至少选择一' + entityName + '！');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
        form.action = action;
        form.submit();
    }
}

function batch_do(form, entityName, action)
{
    if (confirm("确定要" + entityName + "?"))
    {
        if (!atleaseOneCheck())
        {
            alert('请至少选择一' + entityName + '！');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
        form.action = action;
        form.submit();
    }
}

function openwin(url, width, height, scroll)
{
    if (!document.all)
    {
        document.captureEvents(Event.MOUSEMOVE);
        x = e.pageX + width - 30;
        y = e.pageY + height - 30;
    }
    else
    {
        x = document.body.scrollLeft + event.clientX + width - 30;
        y = document.body.scrollTop + event.clientY + height - 30;
    }
    window.open(url, "newWindow", "height=" + height + ", width=" + width + ", toolbar =no, menubar=no, scrollbars=" + scroll + ", resizable=no, location=no, status=no, top=" + y + ", left=" + x + "") //写成一行
}

