//???????????????????????????????????????

//checkbox???????????????????????????
function atleaseOneCheck()
{
    var items = document.all["itemlist"];
    if(items==null)
        return false;
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
    if (confirm("你确定要删除" + entityName + "?"))
    {
        if (!atleaseOneCheck())
        {
            alert('删除' + entityName + '成功');
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
 if (confirm("你确定要删除" + entityName + "?"))
	{
	 if (!atleaseOneCheck())
        {
            alert('???????' + entityName + '??');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
        form.action = action;
        form.submit();
	}

}

function batch_do_no_confirm(form, entityName, action)
{
        if (!atleaseOneCheck())
        {
            alert('???????' + entityName + '??');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
        form.action = action;
        form.submit();
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
    window.open(url, "newWindow", "height=" + height + ", width=" + width + ", toolbar =no, menubar=no, scrollbars=" + scroll + ", resizable=no, location=no, status=no, top=" + y + ", left=" + x + "") //????????????
}
function batch_do_noconfirm(form, entityName, action)
{
        if (!atleaseOneCheck())
        {
            alert('???????' + entityName + '??');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
        form.action = action;
        form.submit();
}
function batch_delete_leaveInfo(form, entityName, action)
{
	 if (confirm("??????" + entityName + "?"))
	{
		 if (!atleaseOneCheck())
        {
            alert('???????' + entityName + '??');
            return;
        }
        form.ec_ev.value = '';
        form.ec_efn.value = '';
        form.action = action;
        form.submit();
	}

}
function count(obj)
{
  var checkOK = "0123456789";
  var checkStr = obj.value;
  var allValid = true;
  var decPoints = 0;
  var allNum = "";
  var odds,exceptjourney,realjourney;
  exceptjourney=obj.value;
  realjourney=obj.value;
  for (i = 0;  i < checkStr.length;  i++)
  {
    ch = checkStr.charAt(i);
    for (j = 0;  j < checkOK.length;  j++)
      if (ch == checkOK.charAt(j))
        break;
    if (j == checkOK.length)
    {
      allValid = false;
      break;
    }
    if (ch != ",")
      allNum += ch;
  }
  if (!allValid)
  {
    alert("??????????????????????????????");
	obj.value="";
	obj.focus();
    return (false);
  }
}
function check()
{
	var v_add_confName=addConf.add_confName.value;
	var v_add_permitLateTime=addConf.add_permitLateTime.value;
    var v_add_permitEarly=addConf.add_permitEarly.value;
	var v_add_ondutyAdvancedTime=addConf.add_ondutyAdvancedTime.value;
	var v_add_offDutyLastTime=addConf.add_offDutyLastTime.value;	
	if(v_add_confName==''||v_add_permitLateTime==''||v_add_permitEarly==''||v_add_ondutyAdvancedTime==''||v_add_offDutyLastTime=='')
	{
		alert('????????????????????????!');
		return false;
	}
}
