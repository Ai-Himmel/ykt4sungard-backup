<%@page pageEncoding="GBK"%>

<%@ include file="../tiles/include.jsp"%>

<center>

	<html:form action="gzcheckinmanageAction.do?method=find">
		
		<br>

		<table width="100%" border="0" align="center" cellpadding="0" cellspacing="0">
			<tr>
				<td height="30" align="center" valign="middle" class="tdborder02">
					<strong><font class="medium"> <logic:present name="checkinlist" scope="request">
								<logic:iterate name="checkinlist" id="cl" type="java.util.Map" length="1">
									<bean:write name="cl" property="classNo" />&nbsp;����������Ϣ�Ǽ�
      <input name="classNo" type="hidden" value="<bean:write name="cl" property="classNo"/>">
								</logic:iterate>
							</logic:present> <logic:notPresent name="checkinlist" scope="request">
    ����������Ϣ�Ǽ�
  </logic:notPresent> </font></strong>
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
							<tr align="center" valign=center>
								<td height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									¼ȡ֪ͨ���
								</td>
								<td width="35%" align="left" valign="middle" class="tableHeader3">
									<input name="enrollNo" class="input_box" maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
								</td>
								<td width="15%" align="left" valign="middle" class="tableHeader2">
									ѧ��
								</td>
								<td align="left" valign="middle" class="tableHeader3">
									<input name="studentNo" class="input_box" maxlength=50 value="" onkeydown="if(event.keyCode==13) document.onkeydown();">
								</td>
							</tr>
							<tr align="center" valign=center>
								<td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2">
									�Ա�
								</td>
								<td align="left" valign="middle" class="tableHeader3" >
									<input name="gender" type="radio" value="1">
									��&nbsp;&nbsp;&nbsp;
									<input name="gender" type="radio" value="2">
									Ů&nbsp;&nbsp;&nbsp;
									<input name="gender" type="radio" value="" checked>
									δ֪
								</td>	
								<td width=15% align="right" valign="middle" class="tableHeader2" ><bean:message bundle="checkinmanage" key="checkin.classNo"/></td>
                                <td align="left" valign="middle" class="tableHeader3" >
                                <select name="s_classNo" class="select01">
                                    <logic:present name="classlist" scope="request">
                                        <logic:iterate name="classlist" id="col" type="java.util.Map">
                                        <option value="<bean:write name="col" property="classNo"/>"><bean:write name="col" property="classNo"/></option>
                                        </logic:iterate>
                                    </logic:present>
                                </select>
                               </td>
								<td width="15%" height="30" align="right" valign="middle" bgcolor="#FFFFFF" class="tableHeader2" style="display: none;">
									רҵ
								</td>
								<td align="left" valign="middle" class="tableHeader3" style="display: none;">
									<select name="majorin" class="select01">
										<option value="" checked>
											��ѡ��
										</option>
										<logic:present name="majorinlist" scope="request">
											<logic:iterate name="majorinlist" id="ml" type="java.util.Map">
												<option value="<bean:write name="ml" property="dictValue"/>">
													<bean:write name="ml" property="dictCaption" />
												</option>
											</logic:iterate>
										</logic:present>
									</select>
								</td>							
							</tr>
							<tr align="center" valign=center>
								<td align="left" valign="middle" class="tableHeader2">
									������Ϣ
								</td>
								<td align="left" valign="middle" class="tableHeader3" colspan="3">
									<font size="2.5" color="#990000"><input name="f_ifNeed" type="checkbox" onClick="f6(this)">��Ϊ��ѯ����</font>&nbsp;&nbsp;&nbsp;&nbsp;
									<input name="f_ifCheckedin" type="checkbox" onClick="f1(this)">
									<font size="2.5">�ѱ���&nbsp;&nbsp;&nbsp;&nbsp;<input name="f_ifChecked" type="checkbox" onClick="f2(this)">¼ȡ֪ͨ���Ѻ���&nbsp;&nbsp;&nbsp;&nbsp; <input name="f_ifGotMaterial" type="checkbox" onClick="f3(this)">��������ȡ&nbsp;&nbsp;&nbsp;&nbsp;<input
											name="f_ifGotEcard" type="checkbox" onClick="f4(this)">��ʽһ��ͨ�Ѹ���&nbsp;&nbsp;&nbsp;&nbsp; <input name="f_ifGotStucard" type="checkbox" onClick="f5(this)">ѧ��֤����ȡ</font>

									<input name="fh_ifNeed" type="hidden" value="">
									<input name="fh_ifCheckedin" type="hidden" value="">
									<input name="fh_ifChecked" type="hidden" value="">
									<input name="fh_ifGotMaterial" type="hidden" value="">
									<input name="fh_ifGotEcard" type="hidden" value="">
									<input name="fh_ifGotStucard" type="hidden" value="">
								</td>
							</tr>
							<logic:present name="stuinfo" scope="request">
								<input name="henrollNo" type="hidden" value="<bean:write name="stuinfo" property="enterenceNo"/>">
								<input name="hstudentNo" type="hidden" value="<bean:write name="stuinfo" property="studentNo"/>">
								<input name="hgender" type="hidden" value="<bean:write name="stuinfo" property="gender"/>">
								<input name="hmajorin" type="hidden" value="<bean:write name="stuinfo" property="majorin"/>">
							</logic:present>
							<logic:notPresent name="stuinfo" scope="request">
								<input name="henrollNo" type="hidden" value="">
								<input name="hstudentNo" type="hidden" value="">
								<input name="hgender" type="hidden" value="">
								<input name="hmajorin" type="hidden" value="">
							</logic:notPresent>
							<logic:present name="classNo" scope="request">
                                <input name="hclassNo" type="hidden" value="<bean:write name="classNo" />"> 
                            </logic:present>   
                            <logic:notPresent name="classNo" scope="request">  
                                <input name="hclassNo" type="hidden" value="">
                            </logic:notPresent>
                            <input type="hidden" name="myAction" value="gzcheckinmanageAction.do?method=find">
						</tbody>
					</table>
				</td>
			</tr>
			<tr>
				<td height="30" align="right" valign="middle" class="tdborder02">
					<input name="Submit" type="button" class="button_nor" value="�� ѯ" onClick="DoFind()">
					<input name="Reset" type="button" class="button_nor" value="�� ��" onClick="DoClear()">
				</td>
			</tr>
			<tr>
				<td align="right" valign="middle">
					&nbsp;
				</td>
			</tr>
			<logic:notPresent name="checkinlist" scope="request">
				<font size="2.5" color="#990000"><bean:message bundle="checkinmanage" key="checkin.noright" /></font>
			</logic:notPresent>
			<tr>
				<td align="left" valign="top">
					<table width=100% border=1 align=center cellpadding=1 cellspacing=0 bordercolor=#AA817F bordercolordark=#ffffff id=maintable>
						<tbody>
							<input type="hidden" name="updateid" value="">
							<logic:present name="checkinlist" scope="request">
							<thead>
							<tr align="center" valign=center>
								<td width="4%" rowspan="2" valign="middle" class="tableHeader">
									ȫѡ
									<input type="checkbox" name="checkall" onClick="DoCheckall(this)">
								</td>
								<td width="8%" rowspan="2" align="center" valign="middle" class="tableHeader">
									ѧ��
								</td>

								<td width="8%" rowspan="2" align="center" valign="middle" class="tableHeader">
									����
								</td>

								<td width="8%" valign="middle" class="tableHeader">
									�ѱ���
								</td>
								<td width="8%" height="22" valign="middle" class="tableHeader">
									֪ͨ��
								</td>
								<td width="8%" valign="middle" class="tableHeader">
									����
								</td>
								<td width="10%" valign="middle" class="tableHeader" nowrap>
									��ʽһ��ͨ
								</td>
								<td width="8%" valign="middle" class="tableHeader">
									ѧ��֤
								</td>
								<td width="45%" rowspan="2" valign="middle" class="tableHeader" nowrap>
									δ����ԭ��
								</td>

								<td rowspan="2" valign="middle" class="tableHeader">
									����
								</td>
							</tr>
							<tr align="center" valign="middle">
								<td valign="middle" class="tableHeader">
									<input type="checkbox" name="checkall1" onClick="DoCheckall1(this)">
									<span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall" /></span>
								</td>
								<td height="22" valign="middle" class="tableHeader">
									<input type="checkbox" name="checkall2" onClick="DoCheckall2(this)">
									<span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall" /></span>
								</td>
								<td valign="middle" class="tableHeader">
									<input type="checkbox" name="checkall3" onClick="DoCheckall3(this)">
									<span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall" /></span>
								</td>
								<td valign="middle" class="tableHeader">
									<input type="checkbox" name="checkall4" onClick="DoCheckall4(this)">
									<span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall" /></span>
								</td>
								<td valign="middle" class="tableHeader">
									<input type="checkbox" name="checkall5" onClick="DoCheckall5(this)">
									<span class="small"><bean:message bundle="checkinmanage" key="checkin.selectall" /></span>
								</td>
							</tr>
							</thead>
							<!--page offset start -->
                            <%int listcount=((Integer)request.getAttribute("listcount")).intValue();%>
		                    <pg:pager url="./gzcheckinmanageAction.do" items="<%=listcount%>" index="center" maxPageItems="100" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
                             <%-- keep track of preference --%>
                               <pg:param name="method" />
                               <pg:param name="henrollNo" />
                               <pg:param name="hstudentNo" />
                               <pg:param name="hgender" />                                                          
		                       <pg:param name="hmajorin" />
		                       <pg:param name="hclassNo" />
		   
		                      	<%-- save pager offset during form changes --%>
		                        	<input type="hidden" name="pager.offset" value="<%= offset %>">
								<%int j = 0;%>
								<logic:iterate name="checkinlist" id="cl" type="java.util.Map" indexId="i">
                                   <pg:item>
									<tr align="center" valign=center <%if(j%2!=0){%> bgcolor="#FFFFFF" <%}else{%> bgcolor="#F6F4F5" <%}%>>
										<td align="center" valign="middle">
											<input type="checkbox" name="cbgroup" value="<bean:write name="cl" property="id"/>" onClick="DoSelect(this)">
										</td>
										<td height="24" align="center" valign="middle">
											<a href="javascript:DoView('<bean:write name="cl" property="studentNo"/>')"><bean:write name="cl" property="studentNo" /></a>
										</td>
										<td align="center" valign="middle">
											<bean:write name="cl" property="stuName" />
										</td>

										<logic:notPresent name="checkinsubmin" scope="request">
											<!-- δ�ύ-->
											<td align="center" valign="middle">
												<c:choose>
													<c:when test="${cl.ifCheckedin == '1'}">
														<input type="checkbox" name="ck_ifCheckedin" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
													</c:when>
												</c:choose>
												<c:choose>
													<c:when test="${cl.ifCheckedin == '0'}">
														<input type="checkbox" name="ck_ifCheckedin" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')">
													</c:when>
												</c:choose>
												<input name="ifCheckedin<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifCheckedin"/>">
											</td>
										</logic:notPresent>
										<logic:present name="checkinsubmin" scope="request">
											<logic:iterate name="checkinsubmin" id="cs" type="java.util.Map" length="1">
												<td align="center" valign="middle">
													<c:choose>
														<c:when test="${cs.ifSubmitted == '0'}">
															<!-- δ�ύ ���� ��ɫΪ����Ա-->
															<c:choose>
																<c:when test="${cl.ifCheckedin == '1'}">
																	<input type="checkbox" name="ck_ifCheckedin" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked>
																</c:when>
															</c:choose>
															<c:choose>
																<c:when test="${cl.ifCheckedin == '0'}">
																	<input type="checkbox" name="ck_ifCheckedin" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')">
																</c:when>
															</c:choose>
														</c:when>
													</c:choose>

													<c:choose>
														<c:when test="${cs.ifSubmitted == '1'}">
															<!-- ���ύ ���� ��ɫΪ����Ա-->
															<c:choose>
																<c:when test="${cl.ifCheckedin == '1'}">
																	<input type="checkbox" name="ck_ifCheckedin" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" checked disabled>
																	<script language="JavaScript">
                         document.all.checkall1.disabled=true;
                    </script>
																</c:when>
															</c:choose>
															<c:choose>
																<c:when test="${cl.ifCheckedin == '0'}">
																	<input type="checkbox" name="ck_ifCheckedin" onClick="DoCheck1(this,'<bean:write name="cl" property="id"/>')" disabled>
																	<script language="JavaScript">
                         document.all.checkall1.disabled=true;
                    </script>
																</c:when>
															</c:choose>
														</c:when>
													</c:choose>
													<input name="ifCheckedin<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifCheckedin"/>">
												</td>
											</logic:iterate>
										</logic:present>
										<td align="center" valign="middle">
											<c:choose>
												<c:when test="${cl.ifChecked == '1'}">
													<input type="checkbox" name="ck_ifChecked" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')" checked>
												</c:when>
											</c:choose>
											<c:choose>
												<c:when test="${cl.ifChecked == '0'}">
													<input type="checkbox" name="ck_ifChecked" onClick="DoCheck2(this,'<bean:write name="cl" property="id"/>')">
												</c:when>
											</c:choose>
											<input name="ifChecked<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifChecked"/>">
										</td>
										<td align="center" valign="middle">
											<c:choose>
												<c:when test="${cl.ifGotMaterial == '1'}">
													<input type="checkbox" name="ck_ifGotMaterial" onClick="DoCheck3(this,'<bean:write name="cl" property="id"/>')" checked>
												</c:when>
											</c:choose>
											<c:choose>
												<c:when test="${cl.ifGotMaterial == '0'}">
													<input type="checkbox" name="ck_ifGotMaterial" onClick="DoCheck3(this,'<bean:write name="cl" property="id"/>')">
												</c:when>
											</c:choose>
											<input name="ifGotMaterial<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifGotMaterial"/>">
										</td>
										<td align="center" valign="middle">
											<c:choose>
												<c:when test="${cl.ifGotEcard == '1'}">
													<input type="checkbox" name="ck_ifGotEcard" onClick="DoCheck4(this,'<bean:write name="cl" property="id"/>')" checked>
												</c:when>
											</c:choose>
											<c:choose>
												<c:when test="${cl.ifGotEcard == '0'}">
													<input type="checkbox" name="ck_ifGotEcard" onClick="DoCheck4(this,'<bean:write name="cl" property="id"/>')">
												</c:when>
											</c:choose>
											<input name="ifGotEcard<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifGotEcard"/>">
										</td>
										<td align="center" valign="middle">
											<c:choose>
												<c:when test="${cl.ifGotStucard == '1'}">
													<input type="checkbox" name="ck_ifGotStucard" onClick="DoCheck5(this,'<bean:write name="cl" property="id"/>')" checked>
												</c:when>
											</c:choose>
											<c:choose>
												<c:when test="${cl.ifGotStucard == '0'}">
													<input type="checkbox" name="ck_ifGotStucard" onClick="DoCheck5(this,'<bean:write name="cl" property="id"/>')">
												</c:when>
											</c:choose>
											<input name="ifGotStucard<bean:write name="cl" property="id"/>" type="hidden" value="<bean:write name="cl" property="ifGotStucard"/>">
										</td>
										<logic:notPresent name="checkinsubmin" scope="request">
											<!-- δ�ύ-->
											<td align="left" valign="middle">
												<c:choose>
													<c:when test="${cl.ifCheckedin == '0'}">
														<c:choose>
															<c:when test="${cl.reason == '01'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" checked>���
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01">���
              </c:otherwise>
														</c:choose>
														<c:choose>
															<c:when test="${cl.reason == '02'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" checked>���뱣���ʸ�
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02">���뱣���ʸ�
              </c:otherwise>
														</c:choose>
														<c:choose>
															<c:when test="${cl.reason == '03'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" checked>����ԭ��
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03">����ԭ��
              </c:otherwise>
														</c:choose>
														<c:choose>
															<c:when test="${cl.reason == '00'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" checked>����
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00">����
              </c:otherwise>
														</c:choose>
													</c:when>
												</c:choose>

												<c:choose>
													<c:when test="${cl.ifCheckedin == '1'}">
														<c:choose>
															<c:when test="${cl.reason == '01'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" checked disabled>���
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" disabled>���
              </c:otherwise>
														</c:choose>
														<c:choose>
															<c:when test="${cl.reason == '02'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" checked disabled>���뱣���ʸ�
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" disabled>���뱣���ʸ�
              </c:otherwise>
														</c:choose>
														<c:choose>
															<c:when test="${cl.reason == '03'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" checked disabled>����ԭ��
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" disabled>����ԭ��
              </c:otherwise>
														</c:choose>
														<c:choose>
															<c:when test="${cl.reason == '00'}">
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" checked  disabled>����
              </c:when>
															<c:otherwise>
																<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" disabled>����
              </c:otherwise>
														</c:choose>
													</c:when>
												</c:choose>												
											</td>
										</logic:notPresent>
										<logic:present name="checkinsubmin" scope="request">
											<logic:iterate name="checkinsubmin" id="cs" type="java.util.Map" length="1">
												<td align="left" valign="middle">
													<c:choose>
														<c:when test="${cs.ifSubmitted == '0'}">
															<!-- δ�ύ ���� ��ɫΪ����Ա-->
															<c:choose>
																<c:when test="${cl.ifCheckedin == '0'}">
																	<c:choose>
																		<c:when test="${cl.reason == '01'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" checked>���
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01">���
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '02'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" checked>���뱣���ʸ�
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02">���뱣���ʸ�
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '03'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" checked>����ԭ��
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03">����ԭ��
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '00'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" checked>����
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" >����
              </c:otherwise>
																	</c:choose>
																</c:when>
															</c:choose>

															<c:choose>
																<c:when test="${cl.ifCheckedin == '1'}">
																	<c:choose>
																		<c:when test="${cl.reason == '01'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" checked disabled>���
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" disabled>���
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '02'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" checked disabled>���뱣���ʸ�
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" disabled>���뱣���ʸ�
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '03'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" checked disabled>����ԭ��
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" disabled>����ԭ��
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '00'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" checked disabled>����
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" disabled>����
              </c:otherwise>
																	</c:choose>
																</c:when>
															</c:choose>
														</c:when>
													</c:choose>
													<c:choose>
														<c:when test="${cs.ifSubmitted == '1'}">
															<!-- ���ύ ���� ��ɫΪ����Ա-->
															<c:choose>
																<c:when test="${cl.ifCheckedin == '0'}">
																	<c:choose>
																		<c:when test="${cl.reason == '01'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" checked>���
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" disabled>���
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '02'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" checked>���뱣���ʸ�
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" disabled>���뱣���ʸ�
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '03'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" checked>����ԭ��
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" disabled>����ԭ��
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '00'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" checked>����
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" disabled>����
              </c:otherwise>
																	</c:choose>
																</c:when>
															</c:choose>

															<c:choose>
																<c:when test="${cl.ifCheckedin == '1'}">
																	<c:choose>
																		<c:when test="${cl.reason == '01'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" checked disabled>���
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="01" disabled>���
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '02'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" checked disabled>���뱣���ʸ�
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="02" disabled>���뱣���ʸ�
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '03'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" checked disabled>����ԭ��
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="03" disabled>����ԭ��
              </c:otherwise>
																	</c:choose>
																	<c:choose>
																		<c:when test="${cl.reason == '00'}">
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" checked disabled>����
              </c:when>
																		<c:otherwise>
																			<input name="reason<bean:write name="cl" property="id"/>" type="radio" value="00" disabled>����
              </c:otherwise>
																	</c:choose>
																</c:when>
															</c:choose>
														</c:when>
													</c:choose>
												</td>
											</logic:iterate>
										</logic:present>

										<textarea name="memo<bean:write name="cl" property="id"/>" cols=15 rows=2 style="display:none">
											<bean:write name="cl" property="memo" />
										</textarea>

										<td align="center" valign="middle">
											<input name="save" type="button" class="button_nor" value="����" onClick="DoSave('<bean:write name="cl" property="id"/>')">
										</td>
									</tr>
									<input type="hidden" name="studentNo<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="studentNo"/>">
									<input type="hidden" name="enrollNo<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="enrollNo"/>">
									<input type="hidden" name="enrollYear<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="enrollYear"/>">
									<input type="hidden" name="updatorId<bean:write name="cl" property="id"/>" value="<%=(String)session.getAttribute("userName")%>">
									<input type="hidden" name="ifReserve<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="ifReserve"/>">
									<input type="hidden" name="ifLeaveSchool<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="ifLeaveSchool"/>">
									<input type="hidden" name="ifSubmitted<bean:write name="cl" property="id"/>" value="<bean:write name="cl" property="ifSubmitted"/>">
									<%j = j + 1;%>
								</pg:item> 
								</logic:iterate>
								<jsp:include page="./page.jsp" flush="true" />
		                        </pg:pager>
		                        <!-- page offset end -->
							</logic:present>
							
							<logic:notPresent name="checkinlist" scope="request">
							<!--page offset start -->
		                    <pg:pager url="./checkinlistpageroll.do" items="0" index="center" maxPageItems="50" maxIndexPages="10" isOffset="<%= true %>" export="offset,currentPageNumber=pageNumber" scope="request">
                            <%-- keep track of preference --%>
                             <pg:param name="henrollNo" />
                              <pg:param name="hstudentNo" />
                                <pg:param name="hgender" />                                                            
		                        <pg:param name="hfromProvince" />
		   
		                    	<%-- save pager offset during form changes --%>
		                    	<input type="hidden" name="pager.offset" value="0">			
		                       <jsp:include page="./page.jsp" flush="true" />
		                    </pg:pager>
		                     <!-- page offset end -->
                            </logic:notPresent>
						</tbody>
					</table>
				</td>
			</tr>
			<logic:present name="checkinlist" scope="request">
			<tr> 
             <td height="40" align="left" valign="middle">
                <%int rowcount=((Integer)request.getAttribute("listcount")).intValue();%>        
                <font color="#000000" size="2.5">��<%=rowcount%>����¼</font>
             </td>
            </tr>
			</logic:present>
			<tr>
				<td height="40" align="right" valign="middle">
					<input name="saveall" type="button" class="button_nor" value="��������" onClick="DoSaveAll()">
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
 
<script language="JavaScript">

//setTimeout('DoInit()',10);
window.onload=DoInit;
function DoInit(){
  
  document.all.enrollNo.value=document.all.henrollNo.value;
  document.all.studentNo.value=document.all.hstudentNo.value;  
    
  for(var i=0;i<document.all.gender.length;i++){
       if(document.all.hgender.value==document.all.gender[i].value)
            document.all.gender[i].checked=true;
   
   }  
   
   for(var i=0;i<document.all.majorin.length;i++){
     
      if(document.all.hmajorin.value==document.all.majorin.options[i].value)
          document.all.majorin.options[i].selected=true;
          
  }   
  
  for(var i=0;i<document.all.s_classNo.length;i++){
     
      if(document.all.hclassNo.value==document.all.s_classNo.options[i].value)
          document.all.s_classNo.options[i].selected=true;
          
  }
  
     document.all.f_ifNeed.checked=false;
     document.all.fh_ifNeed.value=='0'
     
     document.all.f_ifCheckedin.checked=false;
     document.all.f_ifChecked.checked=false;
     document.all.f_ifGotMaterial.checked=false;
     document.all.f_ifGotEcard.checked=false;
     document.all.f_ifGotStucard.checked=false;
     
     document.all.fh_ifCheckedin.value="";
     document.all.fh_ifChecked.value="";
     document.all.fh_ifGotMaterial.value="";
     document.all.fh_ifGotEcard.value="";
     document.all.fh_ifGotStucard.value="";
     
      if(document.all.hmsg.value=='0'){
          alert("����ɹ�!");
          
      }
      else if(document.all.hmsg.value=='1')
          alert("����ʧ��!");          
     
}

function DoSave(str){

   document.all.updateid.value=str;  
   //alert(str);
   
   if(eval("document.all.memo"+str+".value.length>300")){
   
       alert("��ע����!");
       return;
   
   }
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=update";
   document.stucheckininfoForm.submit();
}

function DoSaveAll(){

   if(document.all.updateid.value==""){
        //alert("????????????????????????????????????????????????????!");
        alert("��ѡ��Ҫ��������ļ�¼!");
        return;
   }
   
   var x = document.getElementsByTagName('textarea');
   for (var i=0;i<x.length;i++)
   {
      if (x[i].value.length>300){
          alert("��ע����!");
          return;
      }
   }
   
   document.stucheckininfoForm.action="gzcheckinmanageAction.do?method=updateall";
   document.stucheckininfoForm.submit();
  
}
</script>
<script type="text/javascript" charset="gbk" src="<c:url value='/pages/scripts/gzcheckinList.js'/>"></script>
