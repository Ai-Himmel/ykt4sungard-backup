@echo off
setLocal EnableDelayedExpansion
set CLASSPATH="
for /R . %%a in (*.jar) do (
  set CLASSPATH=!CLASSPATH!;%%a
)
set CLASSPATH=!CLASSPATH!"
rem echo %CLASSPATH%
java -Xmx1024m  com.sungard.ticketsys.IndexFrame