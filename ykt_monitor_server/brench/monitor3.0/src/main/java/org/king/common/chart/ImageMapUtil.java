package org.king.common.chart;

import org.jfree.chart.ChartRenderingInfo;
import org.jfree.chart.imagemap.ImageMapUtilities;
import org.jfree.chart.imagemap.OverLIBToolTipTagFragmentGenerator;
import org.jfree.chart.imagemap.StandardURLTagFragmentGenerator;
import org.jfree.chart.imagemap.ToolTipTagFragmentGenerator;

import java.io.IOException;
import java.io.PrintWriter;

/**
 * .该类用于生成html map
 * 以下方法可以在jfreechart的ChartUtilities类中找到，采用自定义的ToolTipTagFragmentGenerator来生成map
 * User: Yiming.You
 * Date: 2010-8-18
 */
public class ImageMapUtil {
    public static void writeImageMap(PrintWriter writer, String name, ChartRenderingInfo info, boolean useOverLibForToolTips) throws IOException {
        ToolTipTagFragmentGenerator toolTipTagFragmentGenerator;
        if (useOverLibForToolTips) {
            toolTipTagFragmentGenerator = new OverLIBToolTipTagFragmentGenerator();
        } else {
            toolTipTagFragmentGenerator = new WordWrapToolTipTagFragmentGenerator();
        }
        ImageMapUtilities.writeImageMap(writer, name, info, toolTipTagFragmentGenerator, new StandardURLTagFragmentGenerator());
    }
}
