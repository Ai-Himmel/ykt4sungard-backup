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
        <script type='text/javascript' src='<c:url value="/dwr/engine.js"/>'></script>   
        <script type='text/javascript' src='<c:url value="/dwr/util.js"/>'></script> 
        <script type='text/javascript' src='<c:url value="/dwr/interface/OPT.js"/>'></script>

        <SCRIPT language=javascript>

function update(url,clerkname)
{
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
function changeArea(){
	var schoolarea = document.forms[0].schoolarea.value;
	OPT.getBuildList(schoolarea,changeAreaCallback);  
}
function changeBuild(){
	var build = document.forms[0].build.value;
	OPT.getRoomnameList(build,changeBuildCallback);
}
function changeAreaCallback(result){
	DWRUtil.removeAllOptions("build");
	DWRUtil.removeAllOptions("roomname");
	DWRUtil.addOptions("build", { '':'��ѡ��'});
	DWRUtil.addOptions("roomname", { '':'��ѡ��'});
	DWRUtil.addOptions("build", result);
}
function changeBuildCallback(result){
	DWRUtil.removeAllOptions("roomname");
	DWRUtil.addOptions("roomname", { '':'��ѡ��'});
	DWRUtil.addOptions("roomname", result);
}
</SCRIPT>

    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium"> �����豸�� </font> </strong>
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
       <html:form action="classdev.do?method=list" >
                    У����
                    <html:select property="schoolarea" onchange="changeArea();">
                        <html:option value="">��ѡ��</html:option>
                        <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                    </html:select>
                    ¥��
                     <aa:zone name="buildzone" >
                    <html:select property="build" onchange="changeBuild();">
                        <html:option value="">��ѡ��</html:option>
                        <html:options collection="buildList" property="build" labelProperty="build"/>
                    </html:select>
                    </aa:zone>
                    ����  
                     <aa:zone name="roomnamezone">
                    <html:select property="roomname">
                        <html:option value="">��ѡ��</html:option>
                        <html:options collection="roomnameList" property="roomname" labelProperty="roomname"/>
                    </html:select>
                    </aa:zone>
                    <html:submit property="csb">�� ѯ</html:submit>
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
            <ec:table items="classDevList" var="classdev" rowsDisplayed="50" action="classdev.do?method=list">
                <ec:exportXls fileName="classdevList.xls" tooltip="���� Excel" />
                <ec:row>
                    <ec:column property="areaname" title="У��" width="60" />
                    <ec:column property="build" title="¥��" width="60" />
                    <ec:column property="roomname" title="����" width="80" />
                    <ec:column property="devname" title="�豸����" width="300" />
                    <ec:column property="update" title="�޸�" width="40" sortable="false">
                        <a href="classdev.do?method=edit&roomid=${classdev.roomid}">�޸�</a>
                    </ec:column>
                </ec:row>
            </ec:table>

        </div>
    </body>
    
</html>
