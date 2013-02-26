package com.sungard.util;

import javax.swing.filechooser.FileFilter;
import java.io.File;

/**
 * .
 * User: Yiming.You
 * Date: 2011-9-26
 */
public class ExportFileFilter extends FileFilter {
    private String extension;
    private String description;

    public ExportFileFilter(String description, String extension) {
        this.description = description;
        this.extension = extension.toLowerCase();
    }


    public boolean accept(File file) {
        String fileName = file.getName().toLowerCase();
        if (file.isDirectory()) {
            return true;
        }
        if (fileName.endsWith(extension)) {
            return true;
        } else {
            return false;
        }
    }

    @Override
    public String getDescription() {
        return description;
    }
}

