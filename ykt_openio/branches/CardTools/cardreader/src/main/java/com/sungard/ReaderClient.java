package com.sungard;

import com.sungard.card.KsCardInterfaceUtil;
import com.sungard.jform.CardReaderForm;

/**
 * .
 * User: Yiming.You
 * Date: 2011-7-22
 */
public class ReaderClient {
    public static void main(String[] args) {
        KsCardInterfaceUtil.loadLibrary();
        KsCardInterfaceUtil.ksInit();
        CardReaderForm form = new CardReaderForm();
        form.setVisible(true);
    }
}
