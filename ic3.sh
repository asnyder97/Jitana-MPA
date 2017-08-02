#
#Author: Andrew Snyder
#Created Date: July 17th, 2017
#
#

. $(dirname $0)/config.properties

APK_FILE=$1
APP_NAME=$(basename $APK_FILE .apk)
EXIT_CODE=0
LOGFILE=$(mktemp)


echo "Starting IC3 for $APP_NAME"


#Run RetargetedApp.jar
echo "Run RetargetedApp.jar..."
mkdir -p $HOME_FOLDER/Output/$APP_NAME
$JAVA -jar $HOME_FOLDER/db/RetargetedApp.jar $ANDROID_PLATFORMS $APK_FILE $HOME_FOLDER/Output/$APP_NAME 1>>$LOGFILE 2>&1
if [ "$?" -eq "0" ]; then
	echo "[32mSuccess[39m"
else
	echo "[31mFailed[39m"
	exit 1
fi


#Run IC3
echo "Run IC3..."
$JAVA -jar $HOME_FOLDER/db/ic3-0.2.0-full.jar -apkormanifest $APK_FILE -input $HOME_FOLDER/Output/$APP_NAME -cp $ANDROID_PLATFORMS -db $HOME_FOLDER/db/cc.properties 1>>$LOGFILE 2>&1

if [ "$?" -eq "0" ]; then
	echo -e "- Architectural Information: [32mSuccess[39m"
	echo -e "- Outgoing Intents:          [32mSuccess[39m"
else
	echo -e "- Architectural Information: [31mFailed[39m"
	echo -e "- Outgoing Intents:          [31mFailed[39m"
	EXIT_CODE=1
fi

exit $EXIT_CODE












