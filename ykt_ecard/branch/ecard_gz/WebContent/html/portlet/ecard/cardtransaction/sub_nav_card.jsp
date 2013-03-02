<%@ include file="/html/portlet/ecard/cardtransaction/init.jsp" %>


<td width="166" class="text_brown">&nbsp;
<%
	String customerId = (String) request.getSession().getAttribute(WebKeys.USER_ID);
	List availableCards = CardUtil.getAvailableCards(customerId);
	for (int i = 0; i < availableCards.size(); i++) {
%>
	<a id="card<%= i+1%>" 
	<c:if test="<%= i == 0%>">
	class="text_blue_12_c" 
	</c:if>
	<c:if test="<%= i != 0%>">
	class="brown_link" 
	</c:if>
	href="javascript:showCard('<%= i+1%>', <%= availableCards.size()%>);">
	<bean:message key="ecard.account" /><%= i + 1%></a>
	<c:if test="<%= (i+1) != availableCards.size()%>">
	·
	</c:if>
	<%%>
<%}%>
<script>
	function showCard(visibleDivId, totalDivs) {		
		for (var i = 1; i <= totalDivs; i++) {
			var tmp = document.getElementById('cardcontent' + i);
			var tmptag = document.getElementById('card' + i);
			if (visibleDivId == i) {
				tmp.style.visibility= 'visible';
				tmptag.className = 'text_blue_12_c';
			} else {
				tmp.style.visibility= 'hidden';
				tmptag.className = 'brown_link';
			}
		}
	}
</script>
</td>