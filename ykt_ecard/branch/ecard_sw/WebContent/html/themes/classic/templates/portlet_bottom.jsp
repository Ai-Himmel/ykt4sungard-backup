

<%@ include file="init.jsp" %>
<!--
			</div>
		</div>
	</div>
-->
			<!-- +++++++++++ -->
		</td>
              <td valign="top"><img height=240 
              id="<portlet:namespace />rightImage" src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_r_2.jpg" width="9" ></td>
            </tr>
        <!-- +++++++++++ -->
            <tr>
              <td><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_l_3.jpg" width="9" height="8"></td>
              <td height="8" background="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_foot.jpg"></td>
              <td width="9" height="8"><img src="<%= themeDisplay.getPathThemeRoot() %>/images/ecard/window_blue/k_r_3.jpg" width="9" height="8"></td>
            </tr>
          </table>
          
<!--
</div>
-->
<!-- awkward code -->
<script>
	if ('<portlet:namespace />' == '_querydetail_') {
		<portlet:namespace />rightImage.height = 135;
		<portlet:namespace />leftImage.height = 135;
	}
	
	if ('<portlet:namespace />' == '_ecardlink_') {
		<portlet:namespace />rightImage.height = 130;
		<portlet:namespace />leftImage.height = 130;
	}
	
	if ('<portlet:namespace />' == '_cardinfo_') {
		<portlet:namespace />rightImage.height = 260;
		<portlet:namespace />leftImage.height = 260;
	}	
</script>	
<!-- awkward code end -->