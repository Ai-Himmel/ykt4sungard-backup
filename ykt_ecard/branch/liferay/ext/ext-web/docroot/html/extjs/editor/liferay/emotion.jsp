<%
/**
 * Copyright (c) 2000-2005 Liferay, LLC. All rights reserved.
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

<html>

<head>
	<title>Emotion</title>
	<script language="JavaScript">
		function insertEmotion(emotion) {
			opener.insertHTML("<img align=\"absmiddle\" border=\"0\" src=\"../js/editor/liferay/images/emotion_" + emotion + ".gif\">");

			window.close();
		}
	</script>
</head>

<body leftmargin="0" marginheight="0" marginwidth="0" rightmargin="0" topmargin="0">

<table border="0" cellpadding="0" cellspacing="0">
<tr>
	<td valign="top">
		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_smile.gif" vspace="5" width="15" onClick="insertEmotion('smile');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_big_smile.gif" vspace="5" width="15" onClick="insertEmotion('big_smile');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_cool.gif" vspace="5" width="15" onClick="insertEmotion('cool');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_blush.gif" vspace="5" width="15" onClick="insertEmotion('blush');"></td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_tongue.gif" vspace="5" width="15" onClick="insertEmotion('tongue');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_evil.gif" vspace="5" width="15" onClick="insertEmotion('evil');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_wink.gif" vspace="5" width="15" onClick="insertEmotion('wink');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_clown.gif" vspace="5" width="15" onClick="insertEmotion('clown');"></td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_black_eye.gif" vspace="5" width="15" onClick="insertEmotion('black_eye');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_eight_ball.gif" vspace="5" width="15" onClick="insertEmotion('eight_ball');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_sad.gif" vspace="5" width="15" onClick="insertEmotion('sad');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_shy.gif" vspace="5" width="15" onClick="insertEmotion('shy');"></td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_shocked.gif" vspace="5" width="15" onClick="insertEmotion('shocked');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_angry.gif" vspace="5" width="15" onClick="insertEmotion('angry');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_dead.gif" vspace="5" width="15" onClick="insertEmotion('dead');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_sleepy.gif" vspace="5" width="15" onClick="insertEmotion('sleepy');"></td>
		</tr>
		</table>
	</td>
	<td valign="top">
		<table border="0" cellpadding="0" cellspacing="0">
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_kiss.gif" vspace="5" width="15" onClick="insertEmotion('kiss');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_approve.gif" vspace="5" width="15" onClick="insertEmotion('approve');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_disapprove.gif" vspace="5" width="15" onClick="insertEmotion('disapprove');"></td>
		</tr>
		<tr>
			<td><img border="0" height="15" hspace="5" src="images/emotion_question.gif" vspace="5" width="15" onClick="insertEmotion('question');"></td>
		</tr>
		</table>
	</td>
</tr>
</table>

</html>
