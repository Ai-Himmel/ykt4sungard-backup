@echo off
rem cd /opt/sungard/jjlink/bin
java -Xmx1024m -cp %cd%/checkage.jar;%cd%/commons-beanutils-1.7.0.jar;%cd%/commons-codec-1.2.jar;%cd%/commons-digester-1.8.jar;%cd%/commons-lang-2.3.jar;%cd%/commons-logging-1.1.1.jar;%cd%/jta-1.1.jar;%cd%/log4j-1.2.13.jar;%cd%/ojdbc14.jar;%cd%/quartz-all-1.6.6.jar;.  org.king.MainThread jjlink