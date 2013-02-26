package com.sungard.util;

import com.jgoodies.looks.plastic.PlasticLookAndFeel;
import com.jgoodies.looks.plastic.theme.ExperienceGreen;
import org.apache.log4j.Logger;

import javax.imageio.ImageIO;
import javax.swing.Icon;
import javax.swing.ImageIcon;
import javax.swing.UIManager;
import javax.swing.plaf.FontUIResource;
import java.awt.Color;
import java.awt.Component;
import java.awt.Dimension;
import java.awt.Font;
import java.awt.Graphics;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.Insets;
import java.awt.Rectangle;
import java.awt.TexturePaint;
import java.awt.Toolkit;
import java.awt.image.BufferedImage;
import java.io.IOException;
import java.util.Locale;

/**
 * .
 * User: Yiming.You
 * Date: 2011-8-31
 */
public class FreeUtil {
    private static final Logger logger = Logger.getLogger(FreeUtil.class);

    public static final int DEFAULT_BUTTON_SIZE = 20;
    public static final Insets ZERO_INSETS = new Insets(0, 0, 0, 0);
    public static final int TABLE_CELL_LEADING_SPACE = 5;
    public static final Color BUTTON_ROVER_COLOR = new Color(196, 196, 197);
    public static final Color TABLE_HEADER_BACKGROUND_COLOR = new Color(239, 240, 241);
    public static final Color TABLE_HEADER_BORDER_BRIGHT_COLOR = Color.white;
    public static final Color TABLE_HEADER_BORDER_DARK_COLOR = new Color(215, 219, 223);
    public static final Color TABLE_ODD_ROW_COLOR = new Color(233, 231, 235);
    public static final Color TABLE_TEXT_COLOR = new Color(74, 74, 81);
    public static final Color TAB_BOTTOM_LINE_COLOR = new Color(167, 173, 175);
    public static final Color CONTENT_PANE_BACKGROUND = new Color(92, 153, 45);
    public static final Color MENUITEM_SELECTED_BACKGROUND = new Color(166, 188, 140);
    public static final Color MENUITEM_BACKGROUND = new Color(228, 235, 218);
    public static final Color DEFAULT_TEXT_COLOR = new Color(37, 81, 54);
    public static final Color NO_COLOR = new Color(0, 0, 0, 0);
    public static final Font TABLE_HEADER_FONT = new Font("微软雅黑", Font.BOLD, 11);
    public static final Font TABLE_CELL_FONT = new Font("微软雅黑", Font.PLAIN, 11);
    public static final Font FONT_14_BOLD = new Font("微软雅黑", Font.BOLD, 14);
    public static final Font FONT_12_BOLD = new Font("微软雅黑", Font.BOLD, 12);
    public static final Font FONT_12_PLAIN = new Font("微软雅黑", Font.PLAIN, 12);
    private static final String IMAGE_URL_PREFIX = "images/";

    public static String getImageURL(String imageName) {
        return IMAGE_URL_PREFIX + imageName;
    }

    /**
     * ClassLoader获得BufferedImage,注意和getClass().getResource()的路径不同
     * 最前面不带/
     *
     * @param @param  imgPath
     * @param @return 参数
     * @return Image    返回类型
     * @throws
     */
    public static Image getImage(String imgPath) {
        BufferedImage img = null;
        try {
            img = ImageIO.read(ClassLoader.getSystemResource(imgPath));
        } catch (IOException e) {
            logger.error("找不到图片: " + imgPath);
        }
        return img;
    }

    public static ImageIcon getImageIcon(String imgPath) {
        ImageIcon icon = null;
        try {
            icon = new ImageIcon(ClassLoader.getSystemResource(imgPath));
            return icon;
        }
        catch (Exception e) {
            logger.error("找不到图片: " + imgPath);
        }
        return icon;
    }

    public static TexturePaint createTexturePaint(String imgPath) {
        ImageIcon icon = getImageIcon(imgPath);
        int imageWidth = icon.getIconWidth();
        int imageHeight = icon.getIconHeight();
        BufferedImage bi = new BufferedImage(imageWidth, imageHeight, 2);
        Graphics2D g2d = bi.createGraphics();
        g2d.drawImage(icon.getImage(), 0, 0, null);
        g2d.dispose();
        return new TexturePaint(bi, new Rectangle(0, 0, imageWidth, imageHeight));
    }

    public static void setupLookAndFeel() {
        Locale.setDefault(new Locale("EN_US"));
        com.jgoodies.looks.plastic.PlasticTheme theme = new ExperienceGreen() {
            public FontUIResource getControlTextFont() {
                return new FontUIResource(new Font("微软雅黑", 0, 12));
            }
        };
        PlasticLookAndFeel.setPlasticTheme(theme);
        try {
            UIManager.setLookAndFeel("com.jgoodies.looks.plastic.Plastic3DLookAndFeel");
        }
        catch (Exception ex) {
            ex.printStackTrace();
        }
        UIManager.put("Menu.selectionBackground", NO_COLOR);
        UIManager.put("MenuItem.selectionBackground", MENUITEM_SELECTED_BACKGROUND);
        UIManager.put("ToolTip.font", FONT_14_BOLD);
        UIManager.put("TabbedPane.contentBorderInsets", ZERO_INSETS);
        UIManager.put("TabbedPane.tabInsets", ZERO_INSETS);
        UIManager.put("TabbedPane.selectedTabPadInsets", ZERO_INSETS);
        UIManager.put("TabbedPane.tabAreaInsets", ZERO_INSETS);
    }

    public static void centerWindow(Component component) {
        Dimension d = Toolkit.getDefaultToolkit().getScreenSize();
        int width = component.getWidth();
        int height = component.getHeight();
        component.setBounds((d.width - width) / 2, (d.height - height) / 2, width, height);
    }

    public static Icon createMovedIcon(Icon icon) {
        return createMovedIcon(icon, 1, 1);
    }

    public static Icon createMovedIcon(final Icon icon, final int offsetX, final int offsetY) {
        return new Icon() {
            public void paintIcon(Component c, Graphics g, int x, int y) {
                icon.paintIcon(c, g, x + offsetX, y + offsetY);
            }

            public int getIconWidth() {
                return icon.getIconWidth();
            }

            public int getIconHeight() {
                return icon.getIconHeight();
            }
        };
    }
}