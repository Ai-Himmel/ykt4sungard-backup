package com.sungard;

import com.sungard.card.KsCardInterfaceUtil;
import com.sungard.common.Configuration;
import com.sungard.free.MedicalForm;
import com.sungard.util.FreeUtil;

import javax.swing.SwingUtilities;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class MedicalClient {
    public static void main(String[] args) {
        Configuration.load();
        KsCardInterfaceUtil.loadLibrary();
        KsCardInterfaceUtil.ksInit();
        SwingUtilities.invokeLater(new Runnable() {
            public void run() {
                FreeUtil.setupLookAndFeel();
                MedicalForm medicalForm = new MedicalForm();
                medicalForm.setVisible(true);
            }
        });
    }
}
