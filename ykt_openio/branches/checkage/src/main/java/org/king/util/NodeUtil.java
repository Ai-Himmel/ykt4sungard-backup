package org.king.util;


import org.apache.commons.lang.StringUtils;
import org.w3c.dom.Node;

import java.util.regex.Matcher;
import java.util.regex.Pattern;

/**
 * .
 * User: Yiming.You
 * Date: 2011-4-28
 */
public class NodeUtil {
    public static String[] getNodeValue(String tag, String content) {
        String returnValue[] = new String[2];
        String regex = "<" + tag + ">(.*)</" + tag + ">";
        Pattern pattern = Pattern.compile(regex);
        Matcher matcher = pattern.matcher(content);
        while (matcher.find()) {
            returnValue[0] = matcher.group(1);
        }
        return returnValue;
    }

    public static String getNodeText(Node node) {
        String text = "";
        Node firstChild = node.getFirstChild();
        if (firstChild != null) {
            text = firstChild.getNodeValue();
        }
        if (StringUtils.isNotBlank(text)) {
            text = text.trim();
        }
        return text;
    }
}