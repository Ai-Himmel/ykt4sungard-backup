<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<html>
    <head>
        <title>校园一卡通考勤管理系统</title>
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
        alert('请选择日期');
        
    }
}
function validate()
{
    var startDate=leave.leave_startDate.value;
    var endDate=leave.leave_endDate.value;
    if(startDate==''||endDate=='')
    {
        alert("请将日期输入完整");
        return false;
    }
    if(startDate>endDate)
    {       
        alert("开始日期不能大于结束时间");
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
	DWRUtil.addOptions("build", { '':'请选择'});
	DWRUtil.addOptions("roomname", { '':'请选择'});
	DWRUtil.addOptions("build", result);
}
function changeBuildCallback(result){
	DWRUtil.removeAllOptions("roomname");
	DWRUtil.addOptions("roomname", { '':'请选择'});
	DWRUtil.addOptions("roomname", result);
}
</SCRIPT>

    </head>
    <body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

        <div id="titleDiv" class="pageTitle">
            <strong> <font class="medium"> 教室设备绑定 </font> </strong>
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
                    校区：
                    <html:select property="schoolarea" onchange="changeArea();">
                        <html:option value="">请选择</html:option>
                        <html:options collection="areaList" property="AREACODE" labelProperty="AREANAME"/>
                    </html:select>
                    楼宇
                     <aa:zone name="buildzone" >
                    <html:select property="build" onchange="changeBuild();">
                        <html:option value="">请选择</html:option>
                        <html:options collection="buildList" property="build" labelProperty="build"/>
                    </html:select>
                    </aa:zone>
                    教室  
                     <aa:zone name="roomnamezone">
                    <html:select property="roomname">
                        <html:option value="">请选择</html:option>
                        <html:options collection="roomnameList" property="roomname" labelProperty="roomname"/>
                    </html:select>
                    </aa:zone>
                    <html:submit property="csb">查 询</html:submit>
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
                <ec:exportXls fileName="classdevList.xls" tooltip="导出 Excel" />
                <ec:row>
                    <ec:column property="areaname" title="校区" width="60" />
                    <ec:column property="build" title="楼宇" width="60" />
                    <ec:column property="roomname" title="教室" width="80" />
                    <ec:column property="devname" title="设备名称" width="300" />
                    <ec:column property="update" title="修改" width="40" sortable="false">
                        <a href="classdev.do?method=edit&roomid=${classdev.roomid}">修改</a>
                    </ec:column>
                </ec:row>
            </ec:table>

        </div>
    </body>
    
</html>
