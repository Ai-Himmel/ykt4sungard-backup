package com.kingstar.version;


public final class Version
{
    public static final  String VERSION = "1.0";
    public static final  String BUILD = "build";
    public static final  String YEAR    = "2008";
    public static final  String PRODUCT = "SUNGARD BenchMark Rate System";

    private static String VersionTemplate = "[product] version [version].[build] - SunGard [year] Copyright (c) ";

    private static String VersionString   = null;

    static
    {
        VersionString = StringManip.replaceString( "[product]", PRODUCT, VersionTemplate );
        VersionString = StringManip.replaceString( "[version]", VERSION, VersionString );
        VersionString = StringManip.replaceString( "[build]", BUILD, VersionString );
        VersionString = StringManip.replaceString( "[year]", YEAR, VersionString );

        System.out.println( "===== " + getVersion() + " =====" );
    }

    public static String getVersion()
    {

        return VersionString;
    }

    public static String getVersionNumber()
    {
        return VERSION;
    }
	public static void main(String[] args) {

		System.out.println(Version.getVersion());

	}

}
