<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>

<%@ include file="/pages/common/messages.jsp"%>
<%@ include file="/pages/common/meta.jsp"%>
<html>
<head>
<title>�Ϻ�������ѧ���Ͽ�漰�ִ�����ϵͳ</title>
<meta http-equiv="Content-Type" content="text/html;">

<%@ include file="/pages/components/calendar/calendar.jsp"%>
<link href="<c:url value="/pages/styles/style.css"/>" type="text/css" rel=stylesheet>
<link href="<c:url value="/pages/styles/extremecomponents.css"/>" type="text/css" rel=stylesheet>
<script src="<c:url value="/pages/scripts/admin.js"/>" type="text/javascript"></script>
<script>
function back(){
	eqpsearchForm.action="<c:url value="/lf/untreadAction.do"/>?method=loadUntread4RegSearch";
	eqpsearchForm.submit();
}
</script>
</head>
<body  bgcolor="#FFFFFF" leftmargin="0" topmargin="0">
<br>
<html:form action="/lf/equipmentAction" method="post">
<jodd:form bean="request">
            <input type="hidden" name="ec_i" />
            <input type="hidden" name="ec_p" />
            <input type="hidden" name="ec_crd" />
            <input type="hidden" name="search_untreadId" />
            <input type="hidden" name="search_rtnPName" />
            <input type="hidden" name="search_regTimeStart" />     
            <input type="hidden" name="search_regTimeEnd" />
</jodd:form>
<table width="99%" border="0" align="center" cellpadding="0" cellspacing="0">
  <tr>
    <td align="left" valign="top"><table width="100%" border="0" cellspacing="0" cellpadding="0">
      <tr>
        <td height="25" align="left" valign="top"><table width="150" height="20" border="0" cellpadding="0" cellspacing="0">
          <tr>
            <td width="10" bgcolor="#0066CA">&nbsp;</td>
            <td bgcolor="#0066CA" class="mediumwhite">�豸��Ϣ</td>
            <td width="27"><img src="<c:url value="/pages/style/default/images/tabletitle.jpg"/>" width="27" height="20"></td>
          </tr>
        </table></td>
        </tr>
      <tr>
        <td height="40" align="center" valign="top"><table 
        width=100% border=1 align=center 
      cellpadding=1 cellspacing=0 bordercolor=#FFFFFF       id=submenu1>
          <tbody><input type="hidden" name="querymode" value="<%=request.getAttribute("querymode")==null?"1":request.getAttribute("querymode")%>">
            <tr align="center" valign=center>
              <td width="15%" height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�豸���</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_bh" styleClass="input_box" maxlength="32" /></td>
              <td width="20%" lign="left" valign="middle" class="tableHeader2" >�豸�ʲ���</td>
              <td width="20%" align="left" valign="middle" class="tableHeader3" ><table border="0" cellspacing="0" cellpadding="0">
                <tr align="center" valign="middle">
                  <td width="35"><html:text property="search_zch" styleClass="input_box" maxlength="50" />
                  </td>
                  <td width="25">&nbsp;</td>
                  <td width="40" align="right">
                  <html:select property="search_haszch" onchange="zchSetup(this)" >
                   <html:option value="">��ѡ��</html:option>
                   <html:option value="1">�����ʲ���</html:option>	
                   <html:option value="0">�����ʲ���</html:option>
                  </html:select>
                  </td>                   
                </tr></table>
              </td>              
              <td width="15%" align="left" valign="middle" class="tableHeader2" >�豸���к�</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_xlh" styleClass="input_box" maxlength="50" />
              </td>
            </tr>
            <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�豸����</td>
              <td align="left" valign="middle" class="tableHeader3" >
               <html:select property="search_wldl" styleClass="select01" onchange="changeXl(this)">
                <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="dllist" labelProperty="dlmc" property="id" />
               </html:select>
              </td>
              <td align="left" valign="middle" class="tableHeader2" >�豸С��</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_wlxl" styleClass="select01">
                <html:option value="">��ѡ��	</html:option>	
				 <html:options collection="xllist" labelProperty="xlmc" property="id" />
               </html:select>
              </td>
              <td align="left" valign="middle" class="tableHeader2" >�豸����</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_wlmc" styleClass="input_box" maxlength="100" /></td>
            </tr>
            <tr align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�豸�ͺ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_xh" styleClass="input_box" maxlength="100" /></td>
              <td align="left" valign="middle" class="tableHeader2" >��ͬ��</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_hth" styleClass="input_box" maxlength="100" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��������</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_sccj" styleClass="select01">
                <html:option value="">��ѡ��	</html:option>	
				  <html:options collection="sccjlist" labelProperty="companyName" property="id" />
               </html:select></td>
            </tr>
            <tr id="tr1" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�豸��Դ</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_ly" styleClass="select01">
                <html:option value="">��ѡ��	</html:option>
				  <html:options collection="sourcelist" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�Ƿ񸽼�</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_fj" styleClass="select01">
                <html:option value="">��ѡ��	</html:option>				
				<html:option value="0">��</html:option>
				<html:option value="1">��</html:option>
              </html:select>
              </td>
              <td align="left" valign="middle" class="tableHeader2" >�ϼ��豸��</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_sjssh" styleClass="input_box" maxlength="50" /></td>              
            </tr>
            <tr id="tr2" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����Ա</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_gly" styleClass="input_box" maxlength="50" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��Ӧ��</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_gys" styleClass="select01">
                <html:option value="">��ѡ��	</html:option>	
				  <html:options collection="gyslist" labelProperty="companyName" property="id" />
              </html:select>
              </td>
              <td align="left" valign="middle" class="tableHeader2" >ά����</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_wxs" styleClass="select01">
                <html:option value="">��ѡ��	</html:option>	
				  <html:options collection="wxslist" labelProperty="companyName" property="id" />
              </html:select>
              </td>              
            </tr>
            <tr id="tr3" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >������</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <html:text property="search_dhh" styleClass="input_box" maxlength="50" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�������ڴ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_dhrqc" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_dhrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��ʼ����" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>              
              <td align="left" valign="middle" class="tableHeader2" >�������ڵ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_dhrqd" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_dhrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>              
            </tr>
            <script type="text/javascript">
                new calendar("search_dhrqc", "select_dhrqc", "%Y-%m-%d");
                new calendar("search_dhrqd", "select_dhrqd", "%Y-%m-%d");
           </script>
            <tr id="tr4" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ɹ����ڴ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_cgrqc" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_cgrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��ʼ����" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�������ڴ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_rzrqc" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_rzrqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>              
              <td align="left" valign="middle" class="tableHeader2" >����Ʊ���ڴ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_dfprqc" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_dfprqc" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>              
            </tr>
            <tr id="tr5" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ɹ����ڵ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_cgrqd" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_cgrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��ʼ����" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�������ڵ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_rzrqd" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_rzrqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>              
              <td align="left" valign="middle" class="tableHeader2" >����Ʊ���ڵ�</td>
              <td align="left" valign="middle" class="tableHeader3" >
                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                  <tr> 
                    <td width="130">
                    <html:text property="search_dfprqd" styleClass="input_box" maxlength="50" readonly="true"/> 
                    </td>
                    <td><img id="select_dfprqd" src="<c:url value="/pages/components/calendar/skins/aqua/cal.gif"/>" border="0" alt="��������" style="cursor:pointer"></td>
                 </tr>
                </table>
              </td>              
            </tr>
            <script type="text/javascript">                
			    new calendar("search_cgrqc", "select_cgrqc", "%Y-%m-%d");
                new calendar("search_cgrqd", "select_cgrqd", "%Y-%m-%d");
                new calendar("search_rzrqc", "select_rzrqc", "%Y-%m-%d");
                new calendar("search_rzrqd", "select_rzrqd", "%Y-%m-%d");
                new calendar("search_dfprqc", "select_dfprqc", "%Y-%m-%d");
                new calendar("search_dfprqd", "select_dfprqd", "%Y-%m-%d");				
            </script>
            <%if(request.getAttribute("ifLimit").equals("0")){%>
            <tr id="tr6" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ɹ����۴�</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_djc" styleClass="input_box" maxlength="50" />&nbsp;Ԫ</td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ɹ����۵�</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_djd" styleClass="input_box" maxlength="50" />&nbsp;Ԫ</td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��Ʊ����</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_fphm" styleClass="input_box" maxlength="50" /></td>
            </tr>
            <%}else{%> 
            <tr id="tr6" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >��Ʊ����</td>
              <td align="left" valign="middle" class="tableHeader3" colspan="5">
              <html:text property="search_fphm" styleClass="input_box" maxlength="50" /></td>
            </tr>
            <%}%>
            <tr id="tr7" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >������Դ</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_jfly" styleClass="input_box" maxlength="50" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ɹ�������</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_cgjbr" styleClass="input_box" maxlength="50" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����������</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_dhjbr" styleClass="input_box" maxlength="50" /></td>
           </tr>
           <tr id="tr8" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >�ɷ�����</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_pfdx" styleClass="select01">
                <html:option value="">��ѡ��</html:option>	
				  <html:options collection="pflist" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����У��</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_xq" styleClass="select01" onchange="changeBd(this)">
                <html:option value="">��ѡ��</html:option>	
				  <html:options collection="arealist" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>
              <td align="left" valign="middle" class="tableHeader2" >����¥��</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_louyu" styleClass="select01">
                <html:option value="">��ѡ��</html:option>	
				  <html:options collection="buildinglist" labelProperty="lymc" property="id" />
              </html:select>
              </td>              
           </tr>
           <tr id="tr9" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����/�ⷿ</td>
              <td align="left" valign="middle" class="tableHeader3" >              
              <html:text property="search_jfkf" styleClass="input_box" maxlength="100" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >������</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_jgbh" styleClass="input_box" maxlength="100" /></td>
              <td align="left" valign="middle" class="tableHeader2" >�豸״̬</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:select property="search_sbzt" styleClass="select01">
                <html:option value="">��ѡ��</html:option>	
				  <html:options collection="eqpstatelist" labelProperty="dictCaption" property="dictValue" />
              </html:select>
              </td>              
           </tr>
           <tr id="tr10" align="center" valign=center>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >IPv4��ַ</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_ipv4dz" styleClass="input_box" maxlength="50" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����������1</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_fwqym1" styleClass="input_box" maxlength="50" /></td>
              <td height="26" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" >����������IP</td>
              <td align="left" valign="middle" class="tableHeader3" >
              <html:text property="search_sljhjip" styleClass="input_box" maxlength="50" /></td>
           </tr>       
          </tbody>
        </table>        </td>
      </tr>
      <tr>
        <td height="40" align="right" valign="middle" class="tdborder02">
<input name="bquerymode" type="button" class="button_nor" value="�߼���ѯ" onclick="ChangeQueryMode(this)">
&nbsp;
<input name="Submit" type="button" class="button_nor" value="�� ѯ" onclick="DoFind()">
&nbsp;
<input name="Submit2" type="button" class="button_nor" value="�� ��" onclick="DoClear()"></td>

      </tr>
      </html:form>
      
      <tr>
        <td height="35" align="center" valign="middle" class="mediumblack">�豸�б�</td>
      </tr>
      <jodd:form bean="request">      
      <tr>
        <td height="20" align="center" valign="middle">
         <ec:table items="eqplist" var="eqpJBInfo" rowsDisplayed="10" action="equipmentAction.do?method=search4SBList" >
			
				<ec:exportXls fileName="equipmentList.xls" tooltip="���� Excel" />
				<ec:row>
				    <ec:column property="checkbox" title="ѡ��" sortable="false" viewsAllowed="html" width="30" headerStyle="text-align:center" style="text-align: left">
						<input type="checkbox" name="cbgroup" value="${eqpJBInfo.equipmentNo}" style="border:0px" onClick="doSel(this)" />
					</ec:column>
					<ec:column property="equipmentNo" title="�豸���" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					>
					<a href="javascript:DoView('${eqpJBInfo.equipmentNo}')">${eqpJBInfo.equipmentNo}</a>
					</ec:column>
					<ec:column property="assetNo" title="�ʲ���" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					/>
					<ec:column property="serialNo" title="���к�" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					/>
					<ec:column property="xlmc" title="С��" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="80" 
					/>
					<ec:column property="wlmc" title="����" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="90" 
					/>
					<ec:column property="eqpModel" title="�ͺ�"  
						headerStyle="text-align:center" 
						style="text-align: left"
						width="60" 
					/>
					<ec:column property="deptName" title="�ʲ�����" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="110" 
					/>
					<ec:column property="eqpSource" title="��Դ" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="40" 
					/>
					<ec:column property="managerName" title="����Ա" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="50" 
					/>
					<ec:column property="eqpState" title="״̬" 
					    headerStyle="text-align:center" 
					    style="text-align: left"
					    width="40" 
					/>															
				</ec:row>
			</ec:table>
        </td>
      </tr>
      <%if(((java.util.ArrayList)request.getAttribute("eqplist")).size()>0){%>
              <tr>
                 <td><table width=100% border="0">
        	<tr>
        		<td height="40" align="left" valign="middle">
          			<input name="selectall" type="button" class="button_nor" value="ȫ ѡ" onClick="DoSelectall()" ><input name="notselectall" type="button" class="button_nor" value="ȫ��ѡ" onClick="DoNotselectall()" ><input name="reverseselect" type="button" class="button_nor" value="�� ѡ" onClick="DoReverseselect()" >
        		</td>
        <td height="40" align="right" valign="middle">&nbsp;&nbsp;&nbsp;&nbsp;
          <input name="Submit33" type="button" class="button_nor" value="�˻��Ǽ�" onclick="add()"><input name="Submit31" type="button" class="button_nor" value=" �� ��" onclick="back()"></td>
                    	</tr>
		</table></td>
      </tr>
      <%}%> 
      </jodd:form>
    </table></td>
  </tr>
</table>

</body>
</html>

<script>

    var datacount=0;
    dataset=new Array();
    
   <%
   int count=0;
   String[][] resultset=null;
   if(request.getAttribute("dxlist")!=null)
       resultset=(String[][])request.getAttribute("dxlist");//��ȡ��С���Ӧ����
   
   if(resultset!=null){
     for(count=0;count<resultset.length;count++)
     {
     %>
      dataset[<%=count%>] = new Array("<%=resultset[count][0]%>","<%=resultset[count][1]%>","<%=resultset[count][2]%>");//����javascript��ά���飬��ӦС��id��С�����ơ�����id
     <%
     }
   }
   %>
   datacount=<%=count%>;

</script>
<script>

    var datacount2=0;
    dataset2=new Array();
    
   <%
   int count2=0;
   String[][] resultset2=null;
   if(request.getAttribute("ablist")!=null)
       resultset2=(String[][])request.getAttribute("ablist");//��ȡУ����¥���Ӧ����
   
   if(resultset2!=null){
     for(count2=0;count2<resultset2.length;count2++)
     {
     %>
      dataset2[<%=count2%>] = new Array("<%=resultset2[count2][0]%>","<%=resultset2[count2][1]%>","<%=resultset2[count2][2]%>");//����javascript��ά���飬��Ӧ¥��id��¥�����ơ�У��id
     <%
     }
   }
   %>
   datacount2=<%=count2%>;
   
</script>

<SCRIPT language=javascript>

setTimeout('init()',10);
function init(){
  var dl=document.eqpsearchForm.elements["search_wldl"].value;
  var xl=document.eqpsearchForm.elements["search_wlxl"].value;
  
  if(dl!='')
      changeXl(document.eqpsearchForm.elements["search_wldl"]);
  for(var j=0;j<document.eqpsearchForm.elements["search_wlxl"].length;j++){
      if(document.eqpsearchForm.elements["search_wlxl"][j].value==xl)
	     document.eqpsearchForm.elements["search_wlxl"][j].selected=true;
					
  }
  
  var area=document.eqpsearchForm.elements["search_xq"].value;
  var building=document.eqpsearchForm.elements["search_louyu"].value;
  
  if(area!='')
      changeBd(document.eqpsearchForm.elements["search_xq"]);
  for(var j=0;j<document.eqpsearchForm.elements["search_louyu"].length;j++){
      if(document.eqpsearchForm.elements["search_louyu"][j].value==building)
	     document.eqpsearchForm.elements["search_louyu"][j].selected=true;
					
  }
  
  if(document.eqpsearchForm.querymode.value=='1'){
      document.eqpsearchForm.bquerymode.value="�߼���ѯ";
      tr1.style.display='none';
      tr2.style.display='none';
      tr3.style.display='none';       
      tr4.style.display='none';
      tr5.style.display='none';
      tr6.style.display='none';
      tr7.style.display='none';
      tr8.style.display='none';
      tr9.style.display='none';
      tr10.style.display='none';
  }
  else if(document.eqpsearchForm.querymode.value=='2'){
      document.eqpsearchForm.bquerymode.value="�򵥲�ѯ";
      tr1.style.display='';
      tr2.style.display='';
      tr3.style.display=''; 
      tr4.style.display='';
      tr5.style.display='';
      tr6.style.display='';
      tr7.style.display='';
      tr8.style.display='';
      tr9.style.display='';
      tr10.style.display='';
  }
  
}  
function DoFind(){

    if(document.eqpsearchForm.elements["search_djc"]!=null&&document.eqpsearchForm.elements["search_djc"].value!=''&&isNaN(document.eqpsearchForm.elements["search_djc"].value)){
        alert("�ɹ����۴ӱ�����д���֣�");
        return;
    }
    if(document.eqpsearchForm.elements["search_djd"]!=null&&document.eqpsearchForm.elements["search_djd"].value!=''&&isNaN(document.eqpsearchForm.elements["search_djd"].value)){
        alert("�ɹ����۵�������д���֣�");
        return;
    }
    
    eqpsearchForm.action="equipmentAction.do?method=search4SBList";
    eqpsearchForm.submit();

}
function changeXl(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpsearchForm.elements["search_wlxl"].length=1; //���ԭС���б�        
   
   if(id!="")
      for (i=0;i < datacount; i++)
      {
         if (dataset[i][2] == id)
          {   
             document.eqpsearchForm.elements["search_wlxl"].options[document.eqpsearchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount; i++)
      {
          document.eqpsearchForm.elements["search_wlxl"].options[document.eqpsearchForm.elements["search_wlxl"].length]=new Option(dataset[i][1], dataset[i][0]);
        
      }
     
    }
   

}

function changeBd(sel){

   var id;        
   var i;        

   id=sel.options[sel.selectedIndex].value;
        
   document.eqpsearchForm.elements["search_louyu"].length=1; //���ԭ¥���б�        
   
   if(id!="")
      for (i=0;i < datacount2; i++)
      {
         if (dataset2[i][2] == id)
          {   
             document.eqpsearchForm.elements["search_louyu"].options[document.eqpsearchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);              
                
          }
      }
    else{
       for (i=0;i < datacount2; i++)
      {
          document.eqpsearchForm.elements["search_louyu"].options[document.eqpsearchForm.elements["search_louyu"].length]=new Option(dataset2[i][1], dataset2[i][0]);
        
      }
     
    }
   

}

function zchSetup(sel){

   alert(sel.value);

}
function doSel(sel){
//alert(sel.value);
}

function DoSelectall(){

  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=true;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoNotselectall(){
  
  if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
              document.all.cbgroup[i].checked=false;
       }
       
  }
  else if(document.all.cbgroup!=null){
       document.all.cbgroup.checked=false;       
  }
  else{
       alert("��ǰ�޼�¼��");
  }

}

function DoReverseselect(){
   
   if(document.all.cbgroup!=null&&document.all.cbgroup.length>1){   
       for(var i=0;i<document.all.cbgroup.length;i++){
           if(document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=false;
           else if(!document.all.cbgroup[i].checked)
              document.all.cbgroup[i].checked=true;
       }
       
  }
  else if(document.all.cbgroup!=null){
      if(document.all.cbgroup.checked)
          document.all.cbgroup.checked=false; 
      else if(!document.all.cbgroup.checked)
          document.all.cbgroup.checked=true;    
  }
  else{
       alert("��ǰ�޼�¼��");
  }
  

}

function DoUpdate(){
 
   var sflag=0;
   
   if(document.all.cbgroup.length>1){
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag==0){
              alert("��ѡ��Ҫ�޸ĵ��豸��¼��");
              return;
          } 
   }
   else{
        if(!document.all.cbgroup.checked){
              alert("��ѡ��Ҫ�޸ĵ��豸��¼��");
              return;        
        }
   }
   
   document.forms.ec.action="equipmentAction.do?method=load4update";       
   document.forms.ec.submit();
   
  
  
}

function DoView(eno){

    window.open("../gyf/equipmentAction.do?method=load4view&equipmentNo="+eno,"detailInfo","height=600,width=800,top=0,left=0,toolbar=no,menubar=no,scrollbars=yes, resizable=yes,location=no, status=yes");
   
}

function ChangeQueryMode(btn){

    if(btn.value=='�߼���ѯ'){
       document.eqpsearchForm.querymode.value="2";
       btn.value='�򵥲�ѯ';
       tr1.style.display='';
       tr2.style.display='';
       tr3.style.display='';
       tr4.style.display='';
       tr5.style.display='';
       tr6.style.display='';
       tr7.style.display='';
       tr8.style.display='';
       tr9.style.display='';
       tr10.style.display='';
    }
    else if(btn.value=='�򵥲�ѯ'){
       document.eqpsearchForm.querymode.value="1";
       btn.value='�߼���ѯ';
       tr1.style.display='none';
       tr2.style.display='none';
       tr3.style.display='none'; 
       tr4.style.display='none';
       tr5.style.display='none';
       tr6.style.display='none';
       tr7.style.display='none';
       tr8.style.display='none';
       tr9.style.display='none';
       tr10.style.display='none';
    }

}
function add(){
	  var sflag = 0;
  if(document.all.cbgroup.checked==true){
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=addUntread";
	ec.submit();
  }else{
          for(var i=0;i<document.all.cbgroup.length;i++){
              if(document.all.cbgroup[i].checked){
                   sflag=sflag+1;                                                   
              }
          }           
         if(sflag>1){
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=addUntread";
	ec.submit();
          }else if(sflag<1){
          	  alert("��ѡ��������Ϣ��");
          }else{
    ec.action = "<c:url value="/lf/untreadAction.do"/>?method=addUntread";
	ec.submit();
          } 
  }
}
function DoClear(){

    document.eqpsearchForm.elements["search_bh"].value="";
    document.eqpsearchForm.elements["search_zch"].value="";
    document.eqpsearchForm.elements["search_haszch"].value="";
    document.eqpsearchForm.elements["search_haszch"].options[0].selected=true;
    document.eqpsearchForm.elements["search_xlh"].value="";
    document.eqpsearchForm.elements["search_wldl"].value="";
    document.eqpsearchForm.elements["search_wldl"].options[0].selected=true;
    document.eqpsearchForm.elements["search_wlxl"].value="";
    document.eqpsearchForm.elements["search_wlxl"].options[0].selected=true;
    document.eqpsearchForm.elements["search_wlmc"].value="";
    document.eqpsearchForm.elements["search_xh"].value="";
    document.eqpsearchForm.elements["search_hth"].value="";
    document.eqpsearchForm.elements["search_sccj"].value="";
    document.eqpsearchForm.elements["search_sccj"].options[0].selected=true;
    
    document.eqpsearchForm.elements["search_ly"].value="";
    document.eqpsearchForm.elements["search_ly"].options[0].selected=true;
    document.eqpsearchForm.elements["search_fj"].value="";
    document.eqpsearchForm.elements["search_fj"].options[0].selected=true;
    document.eqpsearchForm.elements["search_sjssh"].value="";
    document.eqpsearchForm.elements["search_gly"].value="";
    document.eqpsearchForm.elements["search_gys"].value="";
    document.eqpsearchForm.elements["search_gys"].options[0].selected=true;
    document.eqpsearchForm.elements["search_wxs"].value="";
    document.eqpsearchForm.elements["search_wxs"].options[0].selected=true;    
    document.eqpsearchForm.elements["search_dhh"].value="";
    document.eqpsearchForm.elements["search_dhrqc"].value="";
    document.eqpsearchForm.elements["search_dhrqd"].value="";
    document.eqpsearchForm.elements["search_cgrqc"].value="";
    document.eqpsearchForm.elements["search_rzrqc"].value="";
    document.eqpsearchForm.elements["search_dfprqc"].value="";
    document.eqpsearchForm.elements["search_cgrqd"].value="";
    document.eqpsearchForm.elements["search_rzrqd"].value="";
    document.eqpsearchForm.elements["search_dfprqd"].value="";
    document.eqpsearchForm.elements["search_djc"].value="";
    document.eqpsearchForm.elements["search_djd"].value="";
    document.eqpsearchForm.elements["search_fphm"].value="";
    document.eqpsearchForm.elements["search_jfly"].value="";
    document.eqpsearchForm.elements["search_cgjbr"].value="";
    document.eqpsearchForm.elements["search_dhjbr"].value="";
    document.eqpsearchForm.elements["search_pfdx"].value="";
    document.eqpsearchForm.elements["search_pfdx"].options[0].selected=true;
    document.eqpsearchForm.elements["search_xq"].value="";
    document.eqpsearchForm.elements["search_xq"].options[0].selected=true;
    document.eqpsearchForm.elements["search_louyu"].value="";
    document.eqpsearchForm.elements["search_louyu"].options[0].selected=true;
    document.eqpsearchForm.elements["search_jfkf"].value="";
    document.eqpsearchForm.elements["search_jgbh"].value="";
    document.eqpsearchForm.elements["search_sbzt"].value="";
    document.eqpsearchForm.elements["search_sbzt"].options[0].selected=true;
    document.eqpsearchForm.elements["search_ipv4dz"].value="";
    document.eqpsearchForm.elements["search_fwqym1"].value="";
    document.eqpsearchForm.elements["search_sljhjip"].value="";
}

</SCRIPT>

