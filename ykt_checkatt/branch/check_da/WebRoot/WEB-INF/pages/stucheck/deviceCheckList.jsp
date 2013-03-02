<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
    <head>
        <title>У԰һ��ͨ���ڹ���ϵͳ</title>
        <meta http-equiv="Content-Type" content="text/html;">

        <%@ include file="/pages/common/meta.jsp"%>
        <%@ include file="/pages/components/calendar/calendar.jsp"%>
        <link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
        <link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
        <script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>

        <SCRIPT type="text/javascript">
            function update(url,clerkname) {
                var new_url=url+"&pre_clerkName="+encodeURI(clerkname);
                ec.action=new_url;
                ec.submit();
            }
            function back(){
                window.open('login.htm','_self');
            }
            function on_FD(){
                document.all("sd").click();
            }
            function on_validate(para){
                if(document.all(para).value!=''){
                    document.forms[0].submit();
                }
                else{
                    alert('��ѡ������');

                }
            }
            function validate()
            {
                var startDate=leave.leave_startDate.value;
                var endDate=leave.leave_endDate.value;
                if(startDate==''||endDate=='')
                {
                    alert("�뽫������������");
                    return false;
                }
                if(startDate>endDate)
                {
                    alert("��ʼ���ڲ��ܴ��ڽ���ʱ��");
                    return false;
                }
            }
            <% String msg=(String)request.getAttribute("msg");
            if(msg!=null)
            {
            %>
                alert('<%=msg%>');
            <%}%>
            function viewDetail(deviceid){
                var beginDate = document.getElementById("beginDate").value;
                var endDate = document.getElementById("endDate").value;
                var para = "deviceid=" + deviceid + "&beginDate=" + beginDate + "&endDate="+endDate;
                window.open('/check/deviceCheck.do?method=viewCheckDetail&'+para,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
            }
        </SCRIPT>
    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium"> �豸����ͳ�� </font> </strong>
        </div>
        <div id=lineDiv class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine">   

                    </td>
                </tr>
            </table>
        </div>

        <div id="filterDiv" style="text-align: left;">
       <html:form action="deviceCheck.do?method=list" >
            <table width="100%">
                <tr>
                    <td width="20%">
                         &nbsp;��ʼ���ڣ�
                        <html:text property="beginDate" size="10"readonly="readonly"/>
                        <img id="calBegin" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="beginDate" style="cursor:pointer">
                    </td>
                    <td width="20%">
                        &nbsp;�������ڣ�
                        <html:text property="endDate" size="10" readonly="readonly"/>
                        <img id="calEnd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="endDate" style="cursor:pointer">
                        <script type="text/javascript">
                            new calendar("beginDate", "calBegin", "%Y%m%d");
                            new calendar("endDate", "calEnd", "%Y%m%d");
                        </script>
                    </td>
                    <td width="60%">
                        &nbsp;�豸���ƣ�
                        <html:select property="deviceid">
                            <html:option value="">��ѡ��</html:option>
                            <html:options collection="deviceList" property="deviceid" labelProperty="devicename"/>
                        </html:select>
                        &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                        <input name="Submit" width="50" type="submit" class="button_nor" value="��  ѯ">
                    </td>
                </tr>
            </table>
        </html:form>
        </div>
        <div id=lineDiv class="hrLine">
            <table width="100%" border="0" cellspacing="0" cellpadding="0">
                <tr>
                    <td class="tdborderLine"></td>
                </tr>
            </table>
        </div>
        <div id="tableDiv">
            <ec:table items="deviceCheckList" var="deviceCheck" rowsDisplayed="50" action="deviceCheck.do?method=list" locale="zh_CN" filterable="false">
                <ec:exportXls fileName="deviceCheckList.xls" tooltip="���� Excel" />
                <ec:row>
                    <ec:column property="devicename" title="�豸����" width="60%" />
                    <ec:column property="checknum" title="ˢ������" width="40%" >
                        <a href="#" onclick="viewDetail('${deviceCheck.deviceid}');">${deviceCheck.checknum}</a>
                    </ec:column>
                </ec:row>
            </ec:table>
        </div>
    </body>
</html>
