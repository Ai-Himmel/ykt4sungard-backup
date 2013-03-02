package com.kingstar.math;

import java.math.BigDecimal;

/**
 * 类Round.java的实现描述：提供精确的小数位四舍五入处理 
 */
public class Round
{
    /**
     * 提供精确的小数位四舍五入处理。
     * @param v 需要四舍五入的数字
     * @param scale 小数点后保留几位
     * @return 四舍五入后的结果
     */
    private double round(double v, int scale)
    {
        if (scale < 0)
        {
            throw new IllegalArgumentException(
                    "The scale must be a positive integer or zero");
        }

        BigDecimal b = new BigDecimal(Double.toString(v));
        BigDecimal one = new BigDecimal("1");
        return b.divide(one, scale, BigDecimal.ROUND_HALF_UP).doubleValue();
    }

    /**
     * 
     * 非四舍五入取整处理
     * @param v
     * @return
     */
    public int roundDown(double v)
    {
        BigDecimal b = new BigDecimal(Double.toString(v));
        BigDecimal one = new BigDecimal("1");
        return b.divide(one, 0, BigDecimal.ROUND_DOWN).intValue();
    }

    /**
     * 
     * 四舍五入取整处理
     * @param v
     * @return
     */
    public int roundUp(double v)
    {
        BigDecimal b = new BigDecimal(Double.toString(v));
        BigDecimal one = new BigDecimal("1");
        return b.divide(one, 0, BigDecimal.ROUND_UP).intValue();
    }

    public static void main(String[] args)
    {
        Round round = new Round();
        
        System.out.println(round.round(00.45656, 4));
        
        System.out.println(round.roundDown(18.567));
        
        System.out.println(round.roundUp(18.567));
        
        double doubleValue = 18.567;
        
        int intValue = (int)doubleValue;
        
        System.out.println(intValue);
              System.out.println(Integer.MAX_VALUE);
              System.out.println(Long.MAX_VALUE);

    }
}
