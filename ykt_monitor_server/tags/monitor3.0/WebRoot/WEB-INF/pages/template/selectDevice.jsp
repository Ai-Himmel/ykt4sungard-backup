<%@ page pageEncoding="GBK" %>
<%@ include file="../tiles/include.jsp" %>

<script type="text/javascript" src="<c:url value="/pages/scripts/json2.js"/>"></script>
<script type="text/javascript" src="<c:url value="/pages/scripts/prototype.js"/>" ></script>
<script type="text/javascript">
    function window.onload() {
        var bindingDevice = document.getElementById('bindingDevice').value;
        var array = eval(bindingDevice);
        for (var i = 0; i < array.length; i++) {
            addSingleContent(array[i][0], array[i][1], document.forms[0].oSel);
        }
    }

    function addSingleContent(p_aVal, p_aText, p_oSel) {
        var nLength = p_oSel.length;
        var bTag = 0;

        for (var i = 0; i < nLength; i++) {
            if ((p_aText == p_oSel.options[i].text) && (p_aVal == p_oSel.options[i].value)) {
                bTag = 1;
                break;
            }
            if ((p_aVal == "") || (p_aText == "")) {
                bTag = 1;
                break;
            }
        }
        if (bTag == 0) {
            p_oSel.options[nLength] = new Option(p_aText, nLength);
            p_oSel.options[nLength].value = p_aVal;
        }
    }

    function addContent(checkData) {
        if (checkData.length == 0) {
            return;
        }

        var sCheckKey = DataFrame.m_oConfig.sCheckKey;
        var sSelKey = "#$#$#$";	// 数据分隔符(显示值text与数据值value)

        var array = checkData.split(sCheckKey);
        for (var i = 0; i < array.length; i++) {
            var record = array[i].split(sSelKey);
            addSingleContent(record[1], record[0], document.forms[0].oSel)
        }
    }

    function deleteContent(p_oSel) {
        for(var i=0;i<p_oSel.length;i++){
            if(p_oSel.options[i].selected==true){
                p_oSel.options.remove(i);
                i--;
            }
        }
    }

    function deleteAllContent(p_oSel) {
        p_oSel.length = 0;
    }

    function doBinding(p_oForm, p_oSel) {
        var array = new Array();
        var nLen = p_oSel.length;
        for (var i = 0; i < nLen; i++) {
            array[i] = p_oSel.options[i].value;
        }
        var data = JSON.stringify(array);
        data = JSON.stringify(array).replace(new RegExp("\\\\\"","gm"),"'");
        data = data.substring(1,data.length-1);
        p_oForm.deviceids.value = data;

        var url = "termdevTemplate.do?method=bindingDevice";
        new Ajax.Request(url,
        {
            method:'post',
            parameters: Form.serialize(p_oForm),
            onSuccess: function(result) {
                alert(result.responseText);
                if (result.responseText.indexOf("error:") != 0) {
                    window.close();
                }
            }
        });
    }
</script>

<form action="grantRoleMenu" styleId="blankForm">
    <input type="hidden" name="bindingDevice" value="<c:out value="${bindingDevice}"/>"/>
    <input type="hidden" name="templateId" value="<c:out value="${templateId}"/>"/>
    <input type="hidden" name="deviceids"/>
    <TABLE width="100%" height="305" border="0" cellspacing="0" cellpadding="0" align='center'>
        <TR>
            <TD width="3%">
                &nbsp;
            </TD>
            <TD width="50%">
                <B>菜单列表</B>
            </TD>
            <TD width="7%">
                &nbsp;
            </TD>
            <TD width="35%">
                <B>已选菜单</B>
            </TD>
            <TD width="3%">
                &nbsp;
            </TD>
        </TR>

        <TR>
            <TD>
                &nbsp;
            </TD>
            <TD height="320">
                <IFRAME name='DataFrame'
                        src="termdevTemplate.do?method=listEnableDevice&templateId=<c:out value="${templateId}"/>"
                        width="400" height="320"
                        SCROLLING="auto"></IFRAME>
            </TD>
            <TD align=left>
                <INPUT onclick='addContent(DataFrame.GetAllCheckData())' type=button value="添加 >>" class="button">
                <BR>
                <BR>
                <BR>
                <INPUT onclick="deleteContent(this.form.oSel);" type=button value="<< 删除" class="button">
                <BR>
                <BR>
                <BR>
                <INPUT onclick="deleteAllContent(this.form.oSel);" type=button value="清 &nbsp;&nbsp; 空" class="button">
            </TD>
            <TD height="320">
                <SELECT name='oSel' size=20 style="width:100%;" ondblclick="delContent(this);" multiple="multiple">
                </SELECT>
            </TD>
            <TD>
                &nbsp;
            </TD>
        </TR>
        <TR height=30>
            <TD colSpan=4 align=center valign=bottom>
                <INPUT onclick="doBinding(this.form, this.form.oSel);" type=button value="确 定" class="button">
                <INPUT onclick="window.close();" type=button value="关 闭" class="button">
            </TD>
        </TR>
    </TABLE>
</form>
