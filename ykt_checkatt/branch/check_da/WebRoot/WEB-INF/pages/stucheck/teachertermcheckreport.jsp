<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<%@ include file="/pages/common/taglibs.jsp"%>
<%@ page import="java.util.*" %>
<%@ page import="org.king.check.domain.Department"%>
<html>
	<head>
		<title>�Ϻ����У԰һ��ͨ���ڹ���ϵͳ</title>
		<meta http-equiv="Content-Type" content="text/html;">

		<%@ include file="/pages/common/meta.jsp"%>
		<%@ include file="/pages/components/calendar/calendar.jsp"%>
		<link href="<c:url value="/pages/styles/admin.css"/>" type="text/css" rel=stylesheet>
		<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
		<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
		<%boolean issysadmin = Boolean.parseBoolean(session.getAttribute("issysadmin").toString());%>
		<SCRIPT language="javascript">


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
function checkDate(){
	var termId = document.forms[0].termId.value;
	if(termId==null || termId==""){
		alert('��ѡ��ѧ�ڣ�');
		return false;
	}
	var endDate = document.forms[0].endDate.value;
	var year = endDate.substring(0,4);
	var month = endDate.substring(4,6);
	var day = endDate.substring(6,8);

	var date = new Date(year,month-1,day);
	var nowDate = new Date();
	nowDate.setHours(0,0,0);
	if(nowDate.getTime()-date.getTime()<0){
		alert('��ѡ���ѧ�ڻ�û�н���������ѧ�ڽ������ٲ�ѯ��');
		return false;
	}	
	return true;
}
function docheck(){
	if(!checkDate()){
		return;
	}
   document.forms[0].submit();
}
 var subcat = new Array();
 <%List sub = (List)request.getAttribute("dept");
 if(sub!=null){
  for(int i =0 ;i<sub.size();i++) {
  Map  d = (Map)sub.get(i);
  
  %>
  subcat[<%=i%>] = new Array('<%=d.get("id")%>', '<%=d.get("name")%>', '<%=d.get("parentId")%>');
  <%
  }
 }
  %> 
  var selectedvalue="";
   function changeClass(gardno) {
      document.forms[0].classno.length = 0;
      document.forms[0].classno.add(new Option('��ѡ��',''));
        for (var i = 0; i < subcat.length; i++) {
            if (subcat[i][2] == gardno) {
                document.forms[0].classno.add(new Option(subcat[i][1], subcat[i][0]));
            }
          
        }
     
   }
   var termArray = new Array();
   <%
   		List term = (List)request.getAttribute("term");
   		if(term!=null){
   		for(int i=0;i<term.size();i++){
   			Map map = (Map)term.get(i);
   	%>
   		termArray[<%=i%>] = new Array('<%=map.get("termId")%>','<%=map.get("beginDate")%>','<%=map.get("endDate")%>');
   	<%		
   		}
   		}
   %>
   function changeDate(termId){
	   var hasFind;
	   for (var i = 0; i < termArray.length; i++) {
           if (termArray[i][0] == termId) {
               document.forms[0].beginDate.value = termArray[i][1];
               document.forms[0].endDate.value = termArray[i][2];
               hasFind = true;
               break;
           }
       }
       if(!hasFind){
			document.forms[0].beginDate.value = "";	
			document.forms[0].endDate.value = "";
       }   
   }
    var termId = '<%=request.getAttribute("termId")%>';
    function should(para) {
        var url = "/check/teachertermcheckreport.do?method=getTeacherShould&termId="+termId+para;
         window.open(url, "a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
    }
    function other(para){
        var url = "/check/teachertermcheckreport.do?method=getTeacherOther&termId="+termId+para;
         window.open(url,"a","toolbar=no,location=(200,200),directories=no,status=no,menubar=no, scrollbars=yes,resizable=yes,width=800,height=500");
    }
</SCRIPT>
	</head>
	<body bgcolor="#FFFFFF" leftmargin="0" topmargin="0">

		<div id="titleDiv" class="pageTitle">
			<strong> <font class="medium"> ��ʦ���ڱ���(ѧ��) </font> </strong>
		</div>
		<div id=lineDiv class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="filterDiv" style="text-align: left;">
				<html:form action="teachertermcheckreport.do?method=teacherTermReport" method="post" >
                    <table width="100%">
                    <tr>
                        <td width="20%">
                            &nbsp;��ʦ���ţ�
                            <html:text property="stuempNo" maxlength="50"/>
                        </td>
                        <td width="40%">
                            &nbsp;��ʦ������
                            <html:text property="custName" maxlength="50"/>
                        </td>
                        <td width="40%">
                            &nbsp;��&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�̣�
                            <html:select property="courseId">
                                <html:option value="">��ѡ��</html:option>
                                <html:options collection="course" property="COURSEID" labelProperty="COURSENAME"/>
                            </html:select>
                        </td>
                    </tr>
                    <tr>
                        <td>
                            &nbsp;ѧ&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;�ڣ�
                            <html:select property="termId" onchange="changeDate(this.value);">
                                <html:option value="">��ѡ��</html:option>
                                <html:options collection="term" property="termId" labelProperty="termName"/>
                            </html:select>
                        </td>
                        <td>
                            &nbsp;��ʼ���ڣ�
					        <html:text property="beginDate" size="10" readonly="true"/>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
                            �������ڣ�
					        <html:text property="endDate" size="10" readonly="true"/>
                        </td>
                        <td>
                            &nbsp;<input name="Submit" width="50" type="button" class="button_nor" value="��  ѯ" onclick="docheck()">
                        </td>
                    </tr>
                </table>
				</html:form>
		</div>
	
		
		<div id="lineDiv" class="hrLine">
			<table width="100%" border="0" cellspacing="0" cellpadding="0">
				<tr>
					<td class="tdborderLine"></td>
				</tr>
			</table>
		</div>
		<div id="tableDiv">
			<ec:table items="teacherTermCheckList" var="teachercheck"  rowsDisplayed="50" action="teachertermcheckreport.do?method=teacherTermReport">
				<ec:exportXls fileName="teacherTermCheckList.xls"  tooltip="���� Excel" />
				<ec:row>			   
					<ec:column property="coursename" title="�γ�" width="20%" />
					<ec:column property="stuempno" title="ѧ����" width="12%" escapeAutoFormat="true"/>
					<ec:column property="custname" title="����" width="12%" />
					<ec:column property="coursenum" title="Ӧ������" width="7%" >
                        <a href="javascript:void(0);" onclick="should('&type=should&courseId=${teachercheck.courseid}&stuempNo=${teachercheck.stuempno}')">${teachercheck.coursenum}</a>
					</ec:column>
					<ec:column property="checknum" title="ʵ������" width="7%" >
                        <a href="javascript:void(0);" onclick="other('&type=real&courseId=${teachercheck.courseid}&stuempNo=${teachercheck.stuempno}')">${teachercheck.checknum}</a>
					</ec:column>
					<ec:column property="checkrate" title="������" width="7%" />
					<%if(issysadmin==true){ %>
                    <ec:column property="absenceNum" title="ȱ�ڴ���" width="7%" >
                        <a href="javascript:void(0);" onclick="should('&type=nocome&courseId=${teachercheck.courseid}&stuempNo=${teachercheck.stuempno}')">${teachercheck.absenceNum}</a>
					</ec:column>
					<ec:column property="comelatenum" title="�ٵ�����" width="7%" >
                        <a href="javascript:void(0);" onclick="other('&type=late&courseId=${teachercheck.courseid}&stuempNo=${teachercheck.stuempno}')">${teachercheck.comelatenum}</a>
					</ec:column>
					<ec:column property="comelaterate" title="�ٵ���" width="7%" />
					<ec:column property="leaveearlynum" title="���˴���" width="7%" >
                        <a href="javascript:void(0);" onclick="other('&type=leave&courseId=${teachercheck.courseid}&stuempNo=${teachercheck.stuempno}')">${teachercheck.leaveearlynum}</a>
                    </ec:column>
					<ec:column property="leaveearlyrate" title="������" width="7%" />
					<%}%>
				</ec:row>
			</ec:table>

		</div>
		
	</body>
</html>

