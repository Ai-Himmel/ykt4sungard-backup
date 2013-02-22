<%@page pageEncoding="GBK"%>
<%@ include file="../tiles/include.jsp"%>
<script type="text/javascript" src="<c:url value='/pages/datepicker/WdatePicker.js'/>"></script>

<body onload="init()">
<center>

	<html:form action="testAction.do?method=search4List">
		<html:errors />
		<br>
		<table width="90%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium">考试添加</font></strong>
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					&nbsp;
				</td>
			</tr>
			<tr>
				<td align="center" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#FFFFFF id=submenu1>
						<tbody>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试类别名称
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<select name="testCatId" class="select01">
									<option value="" >请选择</option>
									<logic:present name="tclist" scope="request">
                                        <logic:iterate name="tclist" id="ml" type="java.util.Map">
                                        <option value="<bean:write name="ml" property="id"/>"><bean:write name="ml" property="testCatName"/></option>
                                        </logic:iterate>
                                    </logic:present>									
									</select>								    
								</td>
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									报名开始日期
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
								    <table width="100%" border="0" cellspacing="0" cellpadding="0"><tr><td width="130">
                                    <input class="Wdate" type="text" name="bmTest.bmBeginDate" onfocus="new WdatePicker(this)" readonly="readonly"/>
                                    </td></tr></table>
                                </td> 
                                <td width="15%" align="left" valign="middle" class="tableHeader2">
									报名开始时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
                                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                <tr>                   
                                <td width="25">
                                <select name="bhour" class="select01">
                                <option value="00" >00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" selected>08</option>
                                <option value="09" >09</option>
                                <option value="10" >10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" >18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                </select>
                                </td>
                                <td width="5" align="left">:</td>
                                <td width="25">
                                <select name="bminute" class="select01">
                                <option value="00" selected>00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" >08</option>
                                <option value="09" >09</option>
                                <option value="10" >10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" >18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                <option value="24" >24</option>
                                <option value="25" >25</option>
                                <option value="26" >26</option>
                                <option value="27" >27</option>
                                <option value="28" >28</option>
                                <option value="29" >29</option>
                                <option value="30" >30</option>
                                <option value="31" >31</option>
                                <option value="32" >32</option>
                                <option value="33" >33</option>
                                <option value="34" >34</option>
                                <option value="35" >35</option>
                                <option value="36" >36</option>
                                <option value="37" >37</option>
                                <option value="38" >38</option>
                                <option value="39" >39</option>
                                <option value="40" >40</option>
                                <option value="41" >41</option>
                                <option value="42" >42</option>
                                <option value="43" >43</option>
                                <option value="44" >44</option>
                                <option value="45" >45</option>
                                <option value="46" >46</option>
                                <option value="47" >47</option>
                                <option value="48" >48</option>
                                <option value="49" >49</option>
                                <option value="50" >50</option>
                                <option value="51" >51</option>
                                <option value="52" >52</option>
                                <option value="53" >53</option>
                                <option value="54" >54</option>
                                <option value="55" >55</option>
                                <option value="56" >56</option>
                                <option value="57" >57</option>
                                <option value="58" >58</option>
                                <option value="59" >59</option>               
                                </select>
                                </td>
                                <td width="130"> <input name="bmTest.bmBeginTime" type="hidden"  value=""> 
                                </td>
                               </tr>
                               </table></td>                                             							
							</tr>
							<tr align="center" valign="middle">	
							    <td width="15%" align="left" valign="middle" class="tableHeader2">
									报名结束日期
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<table width="100%" border="0" cellspacing="0" cellpadding="0"><tr><td width="130">
                                    <input class="Wdate" type="text" name="bmTest.bmEndDate" onfocus="new WdatePicker(this)" readonly="readonly"/>
                                    </td></tr></table>							    
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									报名结束时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
                                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                <tr>                   
                                <td width="25">
                                <select name="ehour" class="select01">
                                <option value="00" >00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" >08</option>
                                <option value="09" >09</option>
                                <option value="10" >10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" selected>18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                </select>
                                </td>
                                <td width="5" align="left">:</td>
                                <td width="25">
                                <select name="eminute" class="select01">
                                <option value="00" selected>00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" >08</option>
                                <option value="09" >09</option>
                                <option value="10" >10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" >18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                <option value="24" >24</option>
                                <option value="25" >25</option>
                                <option value="26" >26</option>
                                <option value="27" >27</option>
                                <option value="28" >28</option>
                                <option value="29" >29</option>
                                <option value="30" >30</option>
                                <option value="31" >31</option>
                                <option value="32" >32</option>
                                <option value="33" >33</option>
                                <option value="34" >34</option>
                                <option value="35" >35</option>
                                <option value="36" >36</option>
                                <option value="37" >37</option>
                                <option value="38" >38</option>
                                <option value="39" >39</option>
                                <option value="40" >40</option>
                                <option value="41" >41</option>
                                <option value="42" >42</option>
                                <option value="43" >43</option>
                                <option value="44" >44</option>
                                <option value="45" >45</option>
                                <option value="46" >46</option>
                                <option value="47" >47</option>
                                <option value="48" >48</option>
                                <option value="49" >49</option>
                                <option value="50" >50</option>
                                <option value="51" >51</option>
                                <option value="52" >52</option>
                                <option value="53" >53</option>
                                <option value="54" >54</option>
                                <option value="55" >55</option>
                                <option value="56" >56</option>
                                <option value="57" >57</option>
                                <option value="58" >58</option>
                                <option value="59" >59</option>               
                                </select>
                                </td>
                                <td width="130"> <input name="bmTest.bmEndTime" type="hidden"  value=""> 
                                </td>
                               </tr>
                               </table></td> 
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试日期
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
								    <table width="100%" border="0" cellspacing="0" cellpadding="0"><tr><td width="130">
                                    <input class="Wdate" type="text" name="bmTest.testDate" onfocus="new WdatePicker(this)" readonly="readonly"/>
                                    </td></tr></table>
                                </td> 
                            </tr>
                            <tr align="center" valign="middle">	
							    <td width="15%" align="left" valign="middle" class="tableHeader2">
									考试开始时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
							    <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                 <tr>                   
                                <td width="25">
                                <select name="tbhour" class="select01">
                                <option value="00" >00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" selected>08</option>
                                <option value="09" >09</option>
                                <option value="10" >10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" >18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                </select>
                                </td>
                                <td width="5" align="left">:</td>
                                <td width="25">
                                <select name="tbminute" class="select01">
                                <option value="00" selected>00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" >08</option>
                                <option value="09" >09</option>
                                <option value="10" >10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" >18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                <option value="24" >24</option>
                                <option value="25" >25</option>
                                <option value="26" >26</option>
                                <option value="27" >27</option>
                                <option value="28" >28</option>
                                <option value="29" >29</option>
                                <option value="30" >30</option>
                                <option value="31" >31</option>
                                <option value="32" >32</option>
                                <option value="33" >33</option>
                                <option value="34" >34</option>
                                <option value="35" >35</option>
                                <option value="36" >36</option>
                                <option value="37" >37</option>
                                <option value="38" >38</option>
                                <option value="39" >39</option>
                                <option value="40" >40</option>
                                <option value="41" >41</option>
                                <option value="42" >42</option>
                                <option value="43" >43</option>
                                <option value="44" >44</option>
                                <option value="45" >45</option>
                                <option value="46" >46</option>
                                <option value="47" >47</option>
                                <option value="48" >48</option>
                                <option value="49" >49</option>
                                <option value="50" >50</option>
                                <option value="51" >51</option>
                                <option value="52" >52</option>
                                <option value="53" >53</option>
                                <option value="54" >54</option>
                                <option value="55" >55</option>
                                <option value="56" >56</option>
                                <option value="57" >57</option>
                                <option value="58" >58</option>
                                <option value="59" >59</option>               
                                </select>
                                </td>
                                <td width="130"> <input name="bmTest.testBeginTime" type="hidden"  value=""> 
                                </td>
                               </tr>
                               </table>
                               </td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试结束时间
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
                                <table width="100%" border="0" cellspacing="0" cellpadding="0">
                                <tr>                   
                                <td width="25">
                                <select name="tehour" class="select01">
                                <option value="00" >00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" >08</option>
                                <option value="09" >09</option>
                                <option value="10" selected>10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" >18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                </select>
                                </td>
                                <td width="5" align="left">:</td>
                                <td width="25">
                                <select name="teminute" class="select01">
                                <option value="00" selected>00</option>
                                <option value="01" >01</option>
                                <option value="02" >02</option>
                                <option value="03" >03</option>
                                <option value="04" >04</option>
                                <option value="05" >05</option>
                                <option value="06" >06</option>
                                <option value="07" >07</option>
                                <option value="08" >08</option>
                                <option value="09" >09</option>
                                <option value="10" >10</option>
                                <option value="11" >11</option>
                                <option value="12" >12</option>
                                <option value="13" >13</option>
                                <option value="14" >14</option>
                                <option value="15" >15</option>
                                <option value="16" >16</option>
                                <option value="17" >17</option>
                                <option value="18" >18</option>
                                <option value="19" >19</option>
                                <option value="20" >20</option>
                                <option value="21" >21</option>
                                <option value="22" >22</option>
                                <option value="23" >23</option>
                                <option value="24" >24</option>
                                <option value="25" >25</option>
                                <option value="26" >26</option>
                                <option value="27" >27</option>
                                <option value="28" >28</option>
                                <option value="29" >29</option>
                                <option value="30" >30</option>
                                <option value="31" >31</option>
                                <option value="32" >32</option>
                                <option value="33" >33</option>
                                <option value="34" >34</option>
                                <option value="35" >35</option>
                                <option value="36" >36</option>
                                <option value="37" >37</option>
                                <option value="38" >38</option>
                                <option value="39" >39</option>
                                <option value="40" >40</option>
                                <option value="41" >41</option>
                                <option value="42" >42</option>
                                <option value="43" >43</option>
                                <option value="44" >44</option>
                                <option value="45" >45</option>
                                <option value="46" >46</option>
                                <option value="47" >47</option>
                                <option value="48" >48</option>
                                <option value="49" >49</option>
                                <option value="50" >50</option>
                                <option value="51" >51</option>
                                <option value="52" >52</option>
                                <option value="53" >53</option>
                                <option value="54" >54</option>
                                <option value="55" >55</option>
                                <option value="56" >56</option>
                                <option value="57" >57</option>
                                <option value="58" >58</option>
                                <option value="59" >59</option>               
                                </select>
                                </td>
                                <td width="130"> <input name="bmTest.testEndTime" type="hidden"  value=""> 
                                </td>
                               </tr>
                               </table></td> 
							</tr>
							<tr align="center" valign="middle">							
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									考试说明
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
								<textarea name="bmTest.testMemo" cols="70" rows="4"></textarea>
								</td>
							</tr>
						</tbody>
					</table>
				</td>
			</tr>
			<tr>
				<td height="40" align="right" valign="middle">
					<input name="Submit" type="button" class="button_nor" value="保 存" onClick="DoCheck()">
					&nbsp;&nbsp;&nbsp;
                    <input name="cancel" type="submit" class="button_nor" value="取 消">
				</td>
			</tr>
		</table>
<logic:present name="msg" scope="request">
  <input name="hmsg" type="hidden" value="<bean:write name="msg" />"> 
  </logic:present>
  <logic:notPresent name="msg" scope="request">
  <input name="hmsg" type="hidden" value=""> 
</logic:notPresent>
	</html:form>
</center>
</body>

<script language="JavaScript">

function init(){
    
    if(document.all.hmsg.value=='1')
        alert("保存失败！");
    else if(document.all.hmsg.value=='2')
        alert("已存在相同考试，保存失败！");
}

function DoCheck(){
 
   if(document.all.testCatId.value==''){
      alert("请选择考试名称！");      
      return; 
   }
   if(document.forms[0].elements["bmTest.bmBeginDate"].value==''){
      alert("请选择报名开始日期！");
      return;
   }
   if(document.forms[0].elements["bmTest.bmEndDate"].value==''){
      alert("请选择报名结束日期！");
      return;
   }
   if(document.forms[0].elements["bmTest.testDate"].value==''){
      alert("请选择考试日期！");
      return;
   }
   
   document.forms[0].elements["bmTest.bmBeginTime"].value=document.all.bhour.value+":"+document.all.bminute.value;
   document.forms[0].elements["bmTest.bmEndTime"].value=document.all.ehour.value+":"+document.all.eminute.value;
   document.forms[0].elements["bmTest.testBeginTime"].value=document.all.tbhour.value+":"+document.all.tbminute.value;
   document.forms[0].elements["bmTest.testEndTime"].value=document.all.tehour.value+":"+document.all.teminute.value;
       
   if(document.forms[0].elements["bmTest.bmBeginDate"].value!=''&&document.forms[0].elements["bmTest.bmEndDate"].value!=''){
       var bdatetime=document.forms[0].elements["bmTest.bmBeginDate"].value+document.forms[0].elements["bmTest.bmBeginTime"].value;
       var edatetime=document.forms[0].elements["bmTest.bmEndDate"].value+document.forms[0].elements["bmTest.bmEndTime"].value;
       if(bdatetime>edatetime){
           alert("报名结束时间不能早于报名开始时间！");      
           return;
       }       
   }
   if(document.forms[0].elements["bmTest.bmEndDate"].value!=''&&document.forms[0].elements["bmTest.testDate"].value!=''){
       var edatetime=document.forms[0].elements["bmTest.bmEndDate"].value+document.forms[0].elements["bmTest.bmEndTime"].value;
       var tdatetime=document.forms[0].elements["bmTest.testDate"].value+document.forms[0].elements["bmTest.testBeginTime"].value;
       if(edatetime>tdatetime){
           alert("考试开始时间不能早于报名结束时间！");      
           return;       
       }
   }
   if(document.forms[0].elements["bmTest.testBeginTime"].value>document.forms[0].elements["bmTest.testEndTime"].value){
       alert("考试结束时间不能早于考试开始时间！");      
       return;   
   }
   
   if(document.forms[0].elements["bmTest.testMemo"].value.length>150){   
       alert("考试说明超长!");
       document.forms[0].elements["bmTest.testMemo"].select();
       document.forms[0].elements["bmTest.testMemo"].focus();
       return;   
   }
   
   
   document.testForm.action="testAction.do?method=add";
   document.testForm.submit();     
}

</script>
