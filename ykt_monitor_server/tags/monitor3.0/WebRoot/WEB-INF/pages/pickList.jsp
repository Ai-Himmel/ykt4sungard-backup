<%@ page pageEncoding="GBK"%>
<%@ include file="tiles/include.jsp"%>
<tr>
	<td>
		<select name="<c:out value="${param.leftId}"/>" multiple="multiple" onDblClick="moveSelectedOptions(this,document.getElementById('<c:out value="${param.rightId}"/>'),true)" id="<c:out value="${param.leftId}"/>" size="15" style="width:200 px;">
			<c:if test="${leftList != null}">
				<c:forEach var="list" items="${leftList}" varStatus="status">
					<option value="<c:out value="${list.value}"/>">
						<c:out value="${list.label}" escapeXml="false" />
					</option>
				</c:forEach>
			</c:if>
		</select>
	</td>
	<td class="moveOptions">
		<button name="moveRight" id="moveRight<c:out value="${param.listCount}"/>" type="button" onclick="moveSelectedOptions(document.getElementById('<c:out value="${param.leftId}"/>'),document.getElementById('<c:out value="${param.rightId}"/>'),true)">
			向右 &gt;&gt;
		</button>
		<br />
		<button name="moveAllRight" id="moveAllRight<c:out value="${param.listCount}"/>" type="button" onclick="moveAllOptions(document.getElementById('<c:out value="${param.leftId}"/>'),document.getElementById('<c:out value="${param.rightId}"/>'),true)">
			全部 &gt;&gt;
		</button>
		<br />
		<button name="moveLeft" id="moveLeft<c:out value="${param.listCount}"/>" type="button" onclick="moveSelectedOptions(document.getElementById('<c:out value="${param.rightId}"/>'),document.getElementById('<c:out value="${param.leftId}"/>'),true)">
			向左 &lt;&lt;
		</button>
		<br />
		<button name="moveAllLeft" id="moveAllLeft<c:out value="${param.listCount}"/>" type="button" onclick="moveAllOptions(document.getElementById('<c:out value="${param.rightId}"/>'),document.getElementById('<c:out value="${param.leftId}"/>'),true)">
			全部 &lt;&lt;
		</button>
	</td>
	<td>
		<select name="<c:out value="${param.rightId}"/>" multiple="multiple" id="<c:out value="${param.rightId}"/>" size="15" style="width:200 px;">
			<c:if test="${rightList != null}">
				<c:forEach var="list" items="${rightList}" varStatus="status">
					<option value="<c:out value="${list.value}"/>">
						<c:out value="${list.label}" escapeXml="false" />
					</option>
				</c:forEach>
			</c:if>
		</select>
	</td>
</tr>
