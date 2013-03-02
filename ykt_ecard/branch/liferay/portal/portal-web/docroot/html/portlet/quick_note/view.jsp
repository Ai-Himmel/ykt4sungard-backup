<%
/**
 * Copyright (c) 2000-2008 Liferay, Inc. All rights reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 */
%>

<%@ include file="/html/portlet/quick_note/init.jsp" %>

<div id="<portlet:namespace />pad" style="background: <%= color %>;">
	<c:if test="<%= portletDisplay.isShowConfigurationIcon() %>">
		<div class="portlet-title-default">
			<table border="0" cellpadding="2" cellspacing="0" width="100%">
			<tr>
				<td>
					<span class="note-color yellow"></span>
					<span class="note-color green"></span>
					<span class="note-color blue"></span>
					<span class="note-color red"></span>
				</td>

				<c:if test="<%= portletDisplay.isShowCloseIcon() %>">
					<td>
						<a border="0" class="close-note" href="<%= portletDisplay.getURLClose() %>"><img src="<%= themeDisplay.getPathThemeImages() %>/portlet/close.png" /></a>
					</td>
				</c:if>
			</tr>
			</table>
		</div>
	</c:if>

	<div id="<portlet:namespace />note"><%= data %></div>
</div>

<c:if test="<%= portletDisplay.isShowConfigurationIcon() %>">
	<script type="text/javascript">
		jQuery(
			function() {
				jQuery('#<portlet:namespace />pad .note-color').click(
					function() {
						var box = jQuery(this);

						var bgColor = box.css('background-color');

						jQuery('#<portlet:namespace />pad').css('background-color', bgColor);

						jQuery.ajax(
							{
								type: 'POST',
								url: '<%= themeDisplay.getPathMain() %>/quick_note/save',
								data: {
									p_l_id: '<%= plid %>',
									portletId: '<%= portletDisplay.getId() %>',
									color: bgColor
								}
							}
						);
					}
				);

				jQuery('#<portlet:namespace />note').editable(
					function(value, settings) {
						var newValue = value.replace(/\n/gi, '<br />');

						if (value != settings._LFR_.oldText) {
							jQuery.ajax(
								{
									url: '<%= themeDisplay.getPathMain() %>/quick_note/save',
									data: {
										p_l_id: '<%= plid %>',
										portletId: '<%= portletDisplay.getId() %>',
										data: newValue
									}
								}
							);
						}
						return newValue;
					},
					{
						data: function(value, settings) {
							var newValue = value.replace(/<br[\s\/]?>/gi, '\n');

							settings._LFR_ = {};
							settings._LFR_.oldText = newValue;

							return newValue;
						},
						onblur: 'submit',
						type: 'textarea',
						select: true,
						submit: ''
					}
				);
			}
		);
	</script>
</c:if>