<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>

<html:html>
<head>
	<title>校园一卡通考勤管理系统</title>
	<meta http-equiv="Content-Type" content="text/html;">

	<%@ include file="/pages/common/meta.jsp"%>
	<%@ include file="/pages/components/calendar/calendar.jsp"%>
	<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css"
		rel="stylesheet">
	<link href="<c:url value="/pages/styles/extremecomponents.css"/>"
		type="text/css" rel="stylesheet">
	<script src="<c:url value="/pages/scripts/admin.js"/>"
		type="text/javascript"></script>
</head>
<body>
	<html:form action="classdev.do?method=save">
		<table width="98%" border="0" align="center" cellpadding="0"
			cellspacing="0">


			<div id="titleDiv" class="pageTitle">
				<strong> <font class="medium"> 教室设备绑定 </font> </strong>
			</div>
			<div id=lineDiv class="hrLine">
				<table width="100%" border="0" cellspacing="0" cellpadding="0">
					<tr>
						<td class="tdborderLine"></td>
					</tr>
				</table>
			</div>
			<tr>
				<td>
					<table width=100% border=1 align="center" cellpadding=1
						cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
						<tbody>
							<tr align="center" valign="center">
								<td>
									<table width=100% border=1 align="center" cellpadding=1
										cellspacing=0 bordercolor="#FFFFFF" id="submenu1">
										<tr>
											<td width="22%" height="26" align="right" valign="middle"
												bgcolor="#D1DAE9">
												<span class="medium">教室</span>
											</td>
											<td width="78%" align="left" valign="middle"
												bgcolor="#E7F1F5" colspan="2">
												<html:select property="schoolarea">
                                                    <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                                                </html:select>
                                                <html:text property="build" size="20" maxlength="100"/> <html:text property="roomname" size="20" maxlength="100"/>
												<html:hidden property="roomid"/>
												<font color="#ff0000">*</font>
											</td>
										</tr>
									</table>
							</tr>


							<tr>
								<td>
									<table width=100% border=1 align="center" cellpadding=1
										cellspacing=0 bordercolor="#FFFFFF">
										<tr>
											<td align="center" valign="top" bgcolor="#ECE6E6" width="40%">
												--可选择设备--
												<br>
												<html:select property="unbinddevice" multiple="multiple"
													size="20" ondblclick="javascript: transferOption(this.form.unbinddevice, this.form.binddevice,false);">
													<html:option value="">------------------------------------</html:option>
													<html:options collection="unbinddevList"
														property="deviceid" labelProperty="devicename" />
												</html:select>

											</td>
											<td align="center" width="10%">
												<p>
													<button name="moveRight" id="moveRight" type="button"
														class="button_nor"
														onclick="javascript: transferOption(this.form.unbinddevice, this.form.binddevice,false);">
														<bean:message bundle="check" key="classBinding.right" />
													</button>
													<br />
													<br />
													<button name="moveLeft" id="moveLeft" type="button"
														class="button_nor"
														onclick="javascript: returnOption(this.form.binddevice, this.form.unbinddevice,false);">
														<bean:message bundle="check" key="classBinding.left" />
													</button>
													<br />
												</p>
											</td>
											<td width="40%" align="center" valign="top" bgcolor="#ECE6E6">
											--已绑定设备--
												<br>

												<html:select property="binddevice" multiple="multiple"
													size="20" ondblclick="javascript: returnOption(this.form.binddevice, this.form.unbinddevice,false);">
													<html:option value="">------------------------------------</html:option>
													<html:options collection="binddevList" property="deviceid"
														labelProperty="devicename" />
												</html:select>
											</td>
										</tr>
									</table>
								</td>
							</tr>

							<tr>
								<td height="30" align="right" valign="middle">
									&nbsp;&nbsp;
									<html:button property="bnt_return" onclick="SelectAll()" >保存</html:button>
									<html:button property="bnt_return" onclick="history.back();">返回 </html:button>
								</td>
							</tr>
						</tbody>
					</table>
				</td>
			</tr>
		</table>
	</html:form>
</body>
<script language="JavaScript">

function SelectAll(){
	for(var i=0;i<document.forms[0].binddevice.length;i++){
  		document.forms[0].binddevice.options[i].selected=true;
	}
	document.forms[0].submit();
}

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
                    items[index].style.color = 'black';
                    tgt[i] = null;
                    break;
                }
            }
        }
        else {
                index = uiCommon_findSelectOption(src, tgt[i]);
                // some target items don't exist in the source item collection
                if(index >= 0) {
                    src[index].disabled = false;
                    src[index].selected = true;
                    // because we change the option's color earlier, we need to
                    // to reset it
                    src[index].style.color = 'black';
                    tgt[i] = null;
                }else{
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
            src[index].style.color = 'gray';
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

function transferOption(e1,e2,all){
    var src = e1.options;
    var obj;
    var index;
    for(var i = 0; i < src.length; ++i) {
            if((all || src[i].selected) && !src[i].disabled) {
                uiOptionTransfer_putTgtItem(e2, src[i]);
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
    item.style.color = 'gray';

    var tgt = e2.options;
    tgt.add(clone);
}

function uiCommon_cloneSelectOption(opt) {
  return new Option(opt.text, opt.value,
                    opt.defaultSelected, opt.selected);
}

</script>

</html:html>
