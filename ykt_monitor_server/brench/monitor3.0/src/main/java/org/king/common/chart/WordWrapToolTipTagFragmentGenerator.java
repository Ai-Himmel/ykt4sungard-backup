package org.king.common.chart;

import org.jfree.chart.imagemap.StandardToolTipTagFragmentGenerator;

/**
 * 自定义ToolTip生成类.
 * User: Yiming.You
 * Date: 2010-8-18
 */
public class WordWrapToolTipTagFragmentGenerator extends StandardToolTipTagFragmentGenerator {
    @Override
    public String generateToolTipFragment(String toolTipText) {
        return " title=\"" + htmlEscape(toolTipText)
                + "\" alt=\"\"";
    }

    /**
     * 该方法原型为ImageMapUtilities中的方法，修改该方法以实现对title自定义换行的需求
     *
     * @param input
     * @return
     */
    public String htmlEscape(String input) {
        if (input == null) {
            throw new IllegalArgumentException("Null 'input' argument.");
        }
        StringBuffer result = new StringBuffer();
        int length = input.length();
        for (int i = 0; i < length; i++) {
            char c = input.charAt(i);
            /*if (c == '&') {
                result.append("&amp;");
            } else */
            if (c == '\"') {
                result.append("&quot;");
            } else if (c == '<') {
                result.append("&lt;");
            } else if (c == '>') {
                result.append("&gt;");
            } else if (c == '\'') {
                result.append("&#39;");
            } else if (c == '\\') {
                result.append("&#092;");
            } else {
                result.append(c);
            }
        }
        return result.toString();
    }
}
