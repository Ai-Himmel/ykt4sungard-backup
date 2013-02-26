package com.sungard.free;

import javax.swing.Timer;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.SimpleDateFormat;
import java.util.Date;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class FreeStatusTimeLabel extends FreeStatusLabel {

    private int delay = 1000;

    public FreeStatusTimeLabel() {
        ActionListener taskPerformer = new ActionListener() {
            public void actionPerformed(ActionEvent evt) {
                SimpleDateFormat dateFormat = new SimpleDateFormat("yyyy/MM/dd HH:mm:ss");
                String dateString = dateFormat.format(new Date());
                setText(dateString);
            }
        };
        new Timer(delay, taskPerformer).start();
    }
}

