#!/bin/bash
JAVA_HOME=/opt/sungard/jdk1.5
export CLASSPATH=$CLASSPATH;.;$PWD/lib/*;$PWD/lib/ext/*;
export PATH=$JAVA_HOME/bin:$PATH
$JAVA_HOME/bin/java -server -Xms128m -Xmx384m -Djava.library.path=$PWD/lib -Dclass=com.sungard.smartcard.bccsvr.FunctionOne com.sungard.smartcard.bccsvr.ServerBoot