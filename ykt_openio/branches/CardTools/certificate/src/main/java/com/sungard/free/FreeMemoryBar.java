package com.sungard.free;

import javax.swing.Timer;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.lang.management.ManagementFactory;
import java.lang.management.MemoryMXBean;
import java.text.NumberFormat;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class FreeMemoryBar extends FreeProgressBar {

    private static final int kilo = 1024;
    private static final String mega = "M";
    private static MemoryMXBean memorymbean = ManagementFactory.getMemoryMXBean();
    private static NumberFormat format = NumberFormat.getInstance();
    private int delay = 2000;

    public FreeMemoryBar() {
        super(0, 0, 100);
        ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                final long usedMemory = memorymbean.getHeapMemoryUsage().getUsed();
                final long totalMemory = memorymbean.getHeapMemoryUsage().getMax();
                updateMemoryUsage(usedMemory, totalMemory);
            }
        };
        new Timer(delay, taskPerformer).start();
    }

    private void updateMemoryUsage(long usedMemory, long totalMemory) {
        int percent = (int) (usedMemory * 100 / totalMemory);
        this.setValue(percent);
        String usedMega = format.format(usedMemory / kilo / kilo) + mega;
        String totalMega = format.format(totalMemory / kilo / kilo) + mega;
        String message = usedMega + "/" + totalMega;
        this.setString(message);

        this.setToolTipText("Memory used " + format.format(usedMemory) + " of total " + format.format(totalMemory));
    }
}
