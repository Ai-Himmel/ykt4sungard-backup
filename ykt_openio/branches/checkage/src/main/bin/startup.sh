#!/bin/bash
cd /opt/sungard/jjlink/bin
/opt/sungard/jdk1.5/bin/java -Xmx1024m -cp $PWD/checkage.jar:$PWD/commons-beanutils-1.7.0.jar:$PWD/commons-codec-1.2.jar:$PWD/commons-digester-1.8.jar:$PWD/commons-lang-2.3.jar:$PWD/commons-logging-1.1.1.jar:$PWD/jta-1.1.jar:$PWD/log4j-1.2.13.jar:$PWD/ojdbc14.jar:$PWD/quartz-all-1.6.6.jar:.  org.king.MainThread jjlink
