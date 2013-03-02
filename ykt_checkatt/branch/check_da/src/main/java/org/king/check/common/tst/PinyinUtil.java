package org.king.check.common.tst;

import net.sourceforge.pinyin4j.PinyinHelper;
import net.sourceforge.pinyin4j.format.HanyuPinyinCaseType;
import net.sourceforge.pinyin4j.format.HanyuPinyinOutputFormat;
import net.sourceforge.pinyin4j.format.HanyuPinyinToneType;
import net.sourceforge.pinyin4j.format.HanyuPinyinVCharType;
import net.sourceforge.pinyin4j.format.exception.BadHanyuPinyinOutputFormatCombination;
import org.apache.commons.lang.CharUtils;
import org.apache.commons.lang.StringUtils;

import java.util.ArrayList;
import java.util.List;

/**
 * .
 * User: Yiming.You
 * Date: 2010-9-19
 */
public class PinyinUtil {
    private static final HanyuPinyinOutputFormat DEFAULT_HANYU_PINYIN_OUTPUT_FORMAT = new HanyuPinyinOutputFormat();

    static {
        DEFAULT_HANYU_PINYIN_OUTPUT_FORMAT.setCaseType(HanyuPinyinCaseType.LOWERCASE);
        DEFAULT_HANYU_PINYIN_OUTPUT_FORMAT.setToneType(HanyuPinyinToneType.WITHOUT_TONE);
        DEFAULT_HANYU_PINYIN_OUTPUT_FORMAT.setVCharType(HanyuPinyinVCharType.WITH_V);
    }

    /**
     * Returns list of Han Yu Pin Yin's prefix of every characters. If the
     * character is an alphabet or numerical, the original character will be
     * used. If there is any error occur during conversion, that particular
     * character will be ignored.
     *
     * @param chinese String to be converted
     * @return List of Han Yu Pin Yin's prefix of every characters.
     */
    public static List<String> toHanyuPinyin(String chinese) {
        // Is this an empty string?
        if (StringUtils.isBlank(chinese)) {
            return new ArrayList<String>();
        }

        // Use StringBuffer instead of String during processing for speed
        // optimization.
        List<StringBuffer> stringBuffers = null;

        for (int i = 0, length = chinese.length(); i < length; i++) {
            final char c = chinese.charAt(i);

            String[] pinyins = null;
            final java.util.Set<Character> set = new java.util.HashSet<Character>();
            // Is this Chinese character?
            if (CharUtils.isAscii(c)) {
                if (CharUtils.isAsciiAlphanumeric(c)) {
                    // We are only interested in 'abc' and '123'.
                    set.add(c);
                }
            } else {
                // This is possible a Chinese character.
                try {
                    pinyins = PinyinHelper.toHanyuPinyinStringArray(c, DEFAULT_HANYU_PINYIN_OUTPUT_FORMAT);
                    if (pinyins != null) {
                        for (String pinyin : pinyins) {
                            set.add(pinyin.charAt(0));
                        }
                    }
                } catch (BadHanyuPinyinOutputFormatCombination ex) {
                    ex.printStackTrace();
                    // No. This is not Chinese character.
                    // Just ignore the error. Continue for the rest of characters.
                    // return new ArrayList<String>();
                }
            }
            //Yiming.You add the judgement on set size to support some special character
            if (set.size() > 0) {
                final List<StringBuffer> tmps = stringBuffers;
                stringBuffers = new ArrayList<StringBuffer>();

                if (tmps == null) {
                    // This will be the first converted character.
                    for (Character character : set) {
                        final StringBuffer me = new StringBuffer();
                        me.append(character);
                        stringBuffers.add(me);
                    }
                } else {
                    for (Character character : set) {
                        for (StringBuffer tmp : tmps) {
                            final StringBuffer me = new StringBuffer();
                            me.append(tmp);
                            me.append(character);
                            stringBuffers.add(me);
                        }
                    }
                }
            }
        }

        List<String> result = new ArrayList<String>();
        // Do we have any converted characters?
        if (stringBuffers != null) {
            for (StringBuffer stringBuffer : stringBuffers) {
                result.add(stringBuffer.toString());
            }
        }

        return result;
    }
}
