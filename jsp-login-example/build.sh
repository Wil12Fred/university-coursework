#!/usr/bin/env sh
# Compile the servlet classes into WEB-INF/classes and package build/LoginPageJsp.war.
# Usage: SERVLET_API_JAR=/path/to/javax.servlet-api-3.x.jar ./build.sh
set -eu
cd "$(dirname "$0")"
: "${SERVLET_API_JAR:?set SERVLET_API_JAR to a javax.servlet-api 3.x jar}"
javac -source 8 -target 8 -encoding UTF-8 -cp "$SERVLET_API_JAR" -d WEB-INF/classes WEB-INF/classes/*.java
mkdir -p build
rm -f build/LoginPageJsp.war
jar cf build/LoginPageJsp.war *.jsp WEB-INF/web.xml WEB-INF/classes/myPackage
echo "built build/LoginPageJsp.war"
